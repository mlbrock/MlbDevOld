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

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static int DCR_InitialDBLoad(DCR_CACHE *cache_ptr,
	unsigned int max_load_rows, unsigned int db_load_granularity,
	char *error_text);
#else
static int DCR_InitialDBLoad();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

int DCR_CreateCache(cache_control_ptr, cache_file_name, cache_name,
	db_spec_string, table_name, max_load_rows, db_load_granularity,
	initial_allocation_size, allocation_size, load_data_flag,
	indirect_index_flag, added_field_count, added_field_list, index_spec_count,
	index_spec_list, sql_group_by_clause, sql_order_by_clause,
	sql_where_clause, call_back_mask, call_back_function, user_data_ptr_list,
	out_cache_ptr, out_cache_index, error_text)
DCR_CONTROL    *cache_control_ptr;
const char           *cache_file_name;
const char           *cache_name;
const char           *db_spec_string;
const char           *table_name;
unsigned int          max_load_rows;
unsigned int          db_load_granularity;
unsigned int          initial_allocation_size;
unsigned int          allocation_size;
int                   load_data_flag;
int                   indirect_index_flag;
unsigned int          added_field_count;
char                **added_field_list;
unsigned int          index_spec_count;
char                **index_spec_list;
const char           *sql_group_by_clause;
const char           *sql_order_by_clause;
const char           *sql_where_clause;
const unsigned long  *call_back_mask;
#ifndef NARGS
int                 (*call_back_function)(DCR_CACHE *, unsigned long, int,
	unsigned int, int, unsigned int, void *, DCR_STAT *, int, char *);
#else
int                 (*call_back_function)();
#endif /* #ifndef NARGS */
const void          **user_data_ptr_list;
DCR_CACHE           **out_cache_ptr;
unsigned int         *out_cache_index;
char                 *error_text;
{
	int           return_code;
	DCR_HEADER   *cache_header_ptr = NULL;
	unsigned int  member_count     = 0;
	GEN_MEMBER   *member_list      = NULL;
	DCR_CACHE     cache_data;
	DBC_CONTEXT   dbc_context_data;
	int           errno_code;
	int           open_failure_flag;
	int           mmap_failure_flag;
	DCR_STAT      tmp_create_stat;
	char          dbc_error_text[DBC_MAX_ERROR_TEXT];

	DBC_INIT_DBContext(&dbc_context_data);

	memset(&tmp_create_stat, '\0', sizeof(tmp_create_stat));

	if ((db_spec_string != NULL) && *db_spec_string) {
		DBC_AttachFacility(NULL);
		if ((return_code = DBC_Open(&dbc_context_data, NULL,
			"DCR:TableData", db_spec_string, NULL, DBC_FLAG_DEBUG_NORMAL, NULL,
			dbc_error_text)) != DBC_SUCCESS) {
			nstrcpy(error_text, dbc_error_text, DCR_MAX_ERROR_TEXT - 1);
			return_code = DCR_MAP_ERROR_DBC_TO_DCR(return_code);
			goto EXIT_FUNCTION;
		}
		return_code = DBC_TableToMembers(&dbc_context_data, table_name, NULL,
			&member_count, &member_list, dbc_error_text);
		DBC_Close(&dbc_context_data);
		if (return_code != DCR_SUCCESS) {
			nstrcpy(error_text, dbc_error_text, DCR_MAX_ERROR_TEXT - 1);
			return_code = DCR_MAP_ERROR_DBC_TO_DCR(return_code);
			goto EXIT_FUNCTION;
		}
	}

	DCR_StatStartTime(&tmp_create_stat);

	*out_cache_ptr   = NULL;
	*out_cache_index = 0;

/*
	CODE NOTE: To be fixed.
	if ((return_code = DCR_MakeHeader(cache_name, db_spec_string,
		dbc_context_data.server_name, dbc_context_data.database_name,
		dbc_context_data.owner_name, dbc_context_data.user_name,
		dbc_context_data.pass_word, table_name, initial_allocation_size,
		allocation_size, indirect_index_flag, member_count, member_list,
		added_field_count, added_field_list, index_spec_count, index_spec_list,
		&cache_header_ptr, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
*/
	if ((return_code = DCR_MakeHeader(cache_name, db_spec_string,
		NULL, NULL, NULL, NULL, NULL,
		table_name, initial_allocation_size,
		allocation_size, indirect_index_flag, member_count, member_list,
		added_field_count, added_field_list, index_spec_count, index_spec_list,
		&cache_header_ptr, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;


	memset(&cache_data, '\0', sizeof(cache_data));

	cache_data.open_flag   = O_RDWR | O_CREAT | O_TRUNC;
	cache_data.mmap_prot   = PROT_READ | PROT_WRITE;
	cache_data.mmap_flag   = MAP_SHARED;
	cache_data.file_handle = -1;
	cache_data.mmap_ptr    = NULL;
	cache_data.mmap_size   = cache_header_ptr->header_area_size;

	if ((return_code = DCR_AddACache(cache_control_ptr, cache_file_name,
		&cache_data, out_cache_ptr, out_cache_index, error_text)) !=
		DCR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = DCR_AllocCache(*out_cache_ptr, cache_header_ptr,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = DCR_SetSQLGroupByClause(*out_cache_ptr,
	   sql_group_by_clause, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = DCR_SetSQLOrderByClause(*out_cache_ptr,
	   sql_order_by_clause, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = DCR_SetSQLWhereClause(*out_cache_ptr,
	   sql_where_clause, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	(*out_cache_ptr)->cache_access_type                       =
		DCR_I_AM_WRITER;
	(*out_cache_ptr)->header_ptr->cache_lock_status.lock_flag =
		DCR_STATUS_BUILDING | DCR_STATUS_CRITICAL;
	(*out_cache_ptr)->header_ptr->cache_status                =
		DCR_STATUS_BUILDING | DCR_STATUS_CRITICAL;

	SDTIF_GetTimeUSecs(&((DCR_HEADER *) (*out_cache_ptr)->header_ptr)->
		cache_creation_time);

	if (user_data_ptr_list != NULL)
		memcpy(&(*out_cache_ptr)->user_data_ptr_list, user_data_ptr_list,
			sizeof((*out_cache_ptr)->user_data_ptr_list));

	DCR_SetUserCallBack(*out_cache_ptr, call_back_mask,
		call_back_function);

	if ((return_code = DCR_OpenRaw(cache_file_name,
		(*out_cache_ptr)->open_flag, DCR_CREATE_MODE,
		(*out_cache_ptr)->mmap_prot, (*out_cache_ptr)->mmap_flag,
		&(*out_cache_ptr)->file_handle, &(*out_cache_ptr)->mmap_ptr,
		&(*out_cache_ptr)->mmap_size, &errno_code, &open_failure_flag,
		&mmap_failure_flag, error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_TruncateCache(*out_cache_ptr,
			cache_header_ptr->header_area_size, error_text)) == DCR_SUCCESS) {
			memcpy(((void *) (*out_cache_ptr)->mmap_ptr), cache_header_ptr,
				((unsigned int) cache_header_ptr->header_area_size));
			DCR_BindHeader((*out_cache_ptr),
				(*out_cache_ptr)->header_ptr);
/* CODE NOTE: Should happen in header construction routine. */
(*out_cache_ptr)->header_ptr->allocated_record_count = 0;
			if (load_data_flag == DCR_TRUE)
				return_code = DCR_InitialDBLoad(*out_cache_ptr,
					max_load_rows, db_load_granularity, error_text);
			else
				return_code = DCR_ResizeCache(*out_cache_ptr,
					(*out_cache_ptr)->header_ptr->initial_allocation_size,
					DCR_FALSE, error_text);
			if (return_code == DCR_SUCCESS) {
				(*out_cache_ptr)->header_ptr->cache_lock_status.lock_count++;
				(*out_cache_ptr)->header_ptr->cache_lock_status.lock_flag =
					DCR_STATUS_OK;
				(*out_cache_ptr)->header_ptr->cache_status                =
					DCR_STATUS_OK;
			}
		}
	}

EXIT_FUNCTION:

	GEN_FREE_MemberList(&member_count, &member_list);

	if (return_code != DCR_SUCCESS) {
		if (*out_cache_ptr != NULL)
			DCR_CloseOneCache(*out_cache_ptr);
		*out_cache_ptr   = NULL;
		*out_cache_index = 0;
	}

	if (cache_header_ptr != NULL)
		free(cache_header_ptr);

	if (return_code == DCR_SUCCESS) {
		DCR_StatEndTime(&tmp_create_stat, 1L);
		(*out_cache_ptr)->header_ptr->stat_list[DCR_STAT_CREATE]    =
			tmp_create_stat;
	}

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_InitialDBLoad(cache_ptr, max_load_rows,
	db_load_granularity, error_text)
DCR_CACHE    *cache_ptr;
unsigned int  max_load_rows;
unsigned int  db_load_granularity;
char         *error_text;
{
	int   return_code = DCR_SUCCESS;
	char *sql_command = NULL;

	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_INITIAL_DB_LOAD);
	if ((cache_ptr->call_back_mask & DCR_CB_INITIAL_LOAD) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_INITIAL_LOAD,
		DCR_FALSE, 0, 0, 0, NULL, NULL, return_code, error_text);

	if ((return_code = DCR_MakeSQL(cache_ptr, DCR_FALSE, NULL, NULL,
		&sql_command, error_text)) == DCR_SUCCESS) {
		return_code = DCR_DoCacheLoad(cache_ptr, sql_command,
			max_load_rows, db_load_granularity, error_text);
		free(sql_command);
	}

	DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_INITIAL_DB_LOAD,
		((unsigned long) cache_ptr->record_count));
	if ((cache_ptr->call_back_mask & DCR_CB_INITIAL_LOAD) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_INITIAL_LOAD,
		DCR_TRUE, 0, 0, cache_ptr->record_count, NULL,
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_INITIAL_DB_LOAD, return_code, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define TEST_RECORD_FILE					"CACHE.REC"

#define START_ALLOC_SIZE					4096
#define END_ALLOC_SIZE						4096
#define ALLOC_SIZE							4096

static char *IndexSpecList[] = {
	"FirstIndex=issue_id_value,issue_id_type,issue_id_exchange",
	"SecondIndex=issue_key",
	"ThirdIndex=issue_key,issue_id_type"
};

static unsigned int IndexSpecCount =
	sizeof(IndexSpecList) / sizeof(IndexSpecList[0]);

#ifndef NARGS
int main(void);
#else
int main();
#endif /* #ifndef NARGS */

#ifndef NARGS
static int TestDBData(DCR_CONTROL *cache_control_ptr, char *error_text);
#else
static int TestDBData();
#endif /* #ifndef NARGS */

int main()
{
	int               return_code;
	DCR_CONTROL cache_control_data;
	char              error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'DCR_CreateCache()'\n");
	fprintf(stderr, "---- ------- --- -------------------\n");

	if ((return_code = DCR_AllocCacheControl(&cache_control_data,
		100, error_text)) == DCR_SUCCESS)
		return_code = TestDBData(&cache_control_data, error_text);

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

static int TestDBData(cache_control_ptr, error_text)
DCR_CONTROL *cache_control_ptr;
char              *error_text;
{
	int           return_code;
	DCR_CACHE    *cache_ptr;
	unsigned int  cache_index;

	fprintf(stderr, "Loading rows from database --- ");

	if ((return_code = DCR_CreateCache(cache_control_ptr,
		"TESTFILE.SCF", "TEST_SCF", "SPS_PROD,control,dbo,mlds,mlds",
		"issue_id", 10000, 0, 4096, 4096, DCR_TRUE, DCR_TRUE, 0, NULL,
		IndexSpecCount, IndexSpecList, NULL, NULL, NULL, NULL, NULL, NULL,
		&cache_ptr, &cache_index, error_text)) == DCR_SUCCESS) {
		fprintf(stderr, "%u rows loaded\n", cache_ptr->record_count);
		fprintf(stderr, "Writing the cache header description output --- ");
#ifndef NARGS
		DCR_EmitHeader(cache_ptr, NULL,
			((void (*)(void *, char *, ...)) fprintf), stdout);
#else
		DCR_EmitHeader(cache_ptr, NULL, fprintf, stdout);
#endif /* #ifndef NARGS */
		fprintf(stderr, "done\n");
		fprintf(stderr, "Checking indices --- ");
		if ((return_code = DCR_CheckIndices(cache_ptr, error_text)) ==
			DCR_SUCCESS) {
			fprintf(stdout, "\f");
			fprintf(stderr, "done\n");
		}
		DCR_CloseAllCaches(cache_control_ptr);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

