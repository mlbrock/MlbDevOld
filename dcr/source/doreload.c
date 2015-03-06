/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1994-03-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static int DCR_DoBasicCacheReload(DCR_CACHE *cache_ptr,
	int insert_method, const char *sql_command, unsigned int max_load_rows,
	unsigned int db_load_granularity, unsigned int *row_count,
	char *error_text);
#else
static int DCR_BasicCacheReload();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

int DCR_DoCacheReload(cache_ptr, insert_method, stat_capture_flag,
	update_flag, update_column, update_date, max_load_rows,
	db_load_granularity, error_text)
DCR_CACHE    *cache_ptr;
int           insert_method;
int           stat_capture_flag;
int           update_flag;
char         *update_column;
DTIME        *update_date;
unsigned int  max_load_rows;
unsigned int  db_load_granularity;
char         *error_text;
{
	int           return_code = DCR_SUCCESS;
	char         *sql_command = NULL;
	unsigned int  row_count   = 0;

	if (stat_capture_flag == DCR_TRUE) {
		DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
			DCR_STAT_DB_RELOAD);
		if ((cache_ptr->call_back_mask & DCR_CB_RELOAD) &&
			(cache_ptr->call_back_function != NULL))
			(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_RELOAD,
			DCR_FALSE, 0, 0, 0, NULL, NULL, return_code, error_text);
	}

	if ((return_code = DCR_MakeSQL(cache_ptr, update_flag,
		update_column, update_date, &sql_command, error_text)) == DCR_SUCCESS) {
		if (!cache_ptr->record_count) {
			return_code = DCR_DoCacheLoad(cache_ptr, sql_command,
				max_load_rows, db_load_granularity, error_text);
			row_count   = cache_ptr->record_count;
		}
		else
			return_code = DCR_DoBasicCacheReload(cache_ptr, insert_method,
				sql_command, max_load_rows, db_load_granularity, &row_count,
				error_text);
		free(sql_command);
	}
		
	if (stat_capture_flag == DCR_TRUE) {
		DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
			DCR_STAT_DB_RELOAD, ((unsigned long) row_count));
		if ((cache_ptr->call_back_mask & DCR_CB_RELOAD) &&
			(cache_ptr->call_back_function != NULL))
			(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_RELOAD,
			DCR_TRUE, 0, 0, row_count, NULL,
			((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
			DCR_STAT_DB_RELOAD, return_code, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_DoBasicCacheReload(cache_ptr, insert_method, sql_command,
	max_load_rows, db_load_granularity, row_count, error_text)
DCR_CACHE    *cache_ptr;
int           insert_method;
const char   *sql_command;
unsigned int  max_load_rows;
unsigned int  db_load_granularity;
unsigned int *row_count;
char         *error_text;
{
	int           return_code = DCR_SUCCESS;
	char         *row_list;
	unsigned int  update_count;
	unsigned int  insert_count;
	DBC_CONTEXT   dbc_context_data;
	DBC_GETROWS   get_rows;
	char          dbc_error_text[DBC_MAX_ERROR_TEXT];

	*row_count          = 0;
	db_load_granularity = (!db_load_granularity) ? 10000 : db_load_granularity;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DCR:Load",
		cache_ptr->saved_header_ptr->db_spec_string, NULL,
		DBC_FLAG_DEBUG_NORMAL, NULL, dbc_error_text)) != DBC_SUCCESS) {
		nstrcpy(error_text, dbc_error_text, DCR_MAX_ERROR_TEXT - 1);
		return_code = DCR_MAP_ERROR_DBC_TO_DCR(return_code);
	}
	else {
		DBC_INIT_DBCGetRows(&get_rows);
		get_rows.member_count      = 0;		/* CODE NOTE: Fix me!!!				*/
		get_rows.member_list       = NULL;	/* CODE NOTE: Fix me!!!				*/
		get_rows.sql_command       = ((char *) sql_command);
		get_rows.table_name        =
			((char *) cache_ptr->saved_header_ptr->table_name);
		get_rows.out_row_size      =
			cache_ptr->saved_header_ptr->actual_data_record_size;
		get_rows.data_row_size     =
			cache_ptr->saved_header_ptr->actual_data_record_size;
		get_rows.data_row_offset   = 0;
		get_rows.max_row_count     = max_load_rows;
		get_rows.alloc_granularity = db_load_granularity;
		get_rows.alloc_control_ptr = cache_ptr->reload_mfile_ptr;
		get_rows.user_data_ptr     = cache_ptr;
		get_rows.per_row           = NULL;
		get_rows.alloc             =
			((int (*)(void *, void **, unsigned int)) DBC_MFILE_ALLOC_Rows);
		get_rows.realloc           =
			((int (*)(void *, void **, unsigned int, unsigned int))
			DBC_MFILE_REALLOC_Rows);
		get_rows.free              =
			((void (*)(void *, void **, unsigned int)) DBC_MFILE_FREE_Rows);
		get_rows.per_row_free      = NULL;
		if ((cache_ptr->reload_mfile_ptr = mtmpfile(NULL,
			DCR_MTMPFILE_PREFIX)) == NULL) {
			sprintf(error_text,
				"Temporary file 'mtmpfile(NULL, \"%s\")' error: ",
				DCR_MTMPFILE_PREFIX);
			DCR_GEN_AppendLastErrorString(error_text);
			return_code = DCR_SYSTEM_FAILURE;
		}
		else if ((return_code = DBC_GetRowsBasic(&dbc_context_data, &get_rows,
			row_count, ((void **) &row_list), dbc_error_text)) != DBC_SUCCESS) {
			nstrcpy(error_text, dbc_error_text, DCR_MAX_ERROR_TEXT - 1);
			return_code = DCR_MAP_ERROR_DBC_TO_DCR(return_code);
		}
		else {
			return_code = DCR_SearchBulkBasic(cache_ptr, insert_method,
				*row_count, row_list,
				cache_ptr->header_ptr->actual_data_record_size,
				&update_count, &insert_count, error_text);
			*row_count  = update_count + insert_count;
		}
		if (cache_ptr->reload_mfile_ptr != NULL) {
			munlink(cache_ptr->reload_mfile_ptr);
			cache_ptr->reload_mfile_ptr = NULL;
		}
		DBC_Close(&dbc_context_data);
	}
		
	return(return_code);
}
/*	***********************************************************************	*/

