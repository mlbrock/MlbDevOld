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

	Revision History	:	1994-07-29 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
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

int DCR_DoCacheLoad(cache_ptr, sql_command, max_load_rows,
	db_load_granularity, error_text)
DCR_CACHE    *cache_ptr;
const char   *sql_command;
unsigned int  max_load_rows;
unsigned int  db_load_granularity;
char         *error_text;
{
	int           return_code;
	unsigned int  tmp_row_count = 0;
	void         *tmp_row_ptr;
	unsigned int  allocation_size;
	DBC_CONTEXT   dbc_context_data;
	DBC_GETROWS   get_rows;
	char          dbc_error_text[DBC_MAX_ERROR_TEXT];

	db_load_granularity = (!db_load_granularity) ? 10000 : db_load_granularity;

	if (cache_ptr->record_count) {
		sprintf(error_text, "%s '%-.500s' %s %u, not zero.",
			"Unable to perform a database record load directly into cache file",
			cache_ptr->cache_file_name,
			"because the record count is", cache_ptr->record_count);
		return_code = DCR_FAILURE;
	}
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
			cache_ptr->saved_header_ptr->total_record_size;
		get_rows.data_row_size     =
			cache_ptr->saved_header_ptr->actual_data_record_size;
		get_rows.data_row_offset   = 0;
		get_rows.max_row_count     = max_load_rows;
		get_rows.alloc_granularity = db_load_granularity;
		get_rows.alloc_control_ptr = cache_ptr;
		get_rows.user_data_ptr     = cache_ptr;
		get_rows.per_row           = NULL;
		get_rows.alloc             =
			((int (*)(void *, void **, unsigned int)) DCR_ALLOC_Rows);
		get_rows.realloc           =
			((int (*)(void *, void **, unsigned int, unsigned int))
			DCR_REALLOC_Rows);
		get_rows.free              =
			((void (*)(void *, void **, unsigned int)) DCR_FREE_Rows);
		get_rows.per_row_free      = NULL;
		if ((return_code = DBC_GetRowsBasic(&dbc_context_data, &get_rows,
			&tmp_row_count, ((void **) &tmp_row_ptr), dbc_error_text)) !=
			DBC_SUCCESS) {
			nstrcpy(error_text, dbc_error_text, DCR_MAX_ERROR_TEXT - 1);
			return_code = DCR_MAP_ERROR_DBC_TO_DCR(return_code);
		}
		else {
			DCR_BindHeader(cache_ptr, cache_ptr->header_ptr);
			if (return_code == DCR_SUCCESS) {
				cache_ptr->header_ptr->record_count           = tmp_row_count;
				cache_ptr->header_ptr->allocated_record_count = 0;
				allocation_size                               =
					(tmp_row_count <
					cache_ptr->header_ptr->initial_allocation_size) ?
					cache_ptr->header_ptr->initial_allocation_size : tmp_row_count;
				DCR_BindHeader(cache_ptr, cache_ptr->header_ptr);
				if ((return_code = DCR_ResizeCache(cache_ptr, allocation_size,
					DCR_FALSE, error_text)) == DCR_SUCCESS)
					DCR_IndexCache(cache_ptr);
			}
		}
		DBC_Close(&dbc_context_data);
	}
	
	return(return_code);
}
/*	***********************************************************************	*/

