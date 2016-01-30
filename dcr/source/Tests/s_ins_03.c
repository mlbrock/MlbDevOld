/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Test Module											*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1995-02-28 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <memory.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
int  OLD_DCR_InsertBulk(DCR_CACHE *cache_ptr,
	unsigned int in_record_count, const void *in_record_list,
	unsigned int in_record_size, char *error_text);
void OLD_DCR_IndexCache(DCR_CACHE *cache_ptr);
#else
int  OLD_DCR_InsertBulk();
void OLD_DCR_IndexCache();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
void DCR_IndexEmbeddedFast(DCR_CACHE *cache_ptr,
	unsigned int index_method, DCR_INS_1 *ins_list, void *entry_list);
void DCR_IndexIndirectFast(DCR_CACHE *cache_ptr,
	unsigned int index_method, DCR_INS_1 *ins_list, void *entry_list);
#else
void DCR_IndexEmbeddedFast();
void DCR_IndexIndirectFast();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static void DCR_EmitAllIndexLists(DCR_CACHE *cache_ptr);
static void DCR_EmitOneIndexList(DCR_CACHE *cache_ptr,
	unsigned int index_method);
#else
static void DCR_EmitAllIndexLists();
static void DCR_EmitOneIndexList();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static int Test_CallBack(DCR_CACHE *cache_ptr, unsigned long call_back_type,
	int post_operation_flag, unsigned int index_method, int operation_flags,
	unsigned int operation_count, void *operation_ptr,
	DCR_STAT *stat_ptr, int return_code, char *error_text);
#else
static int Test_CallBack();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static const unsigned long Test_CallBackMask =
	DCR_CB_BULK_INSERT  |
	DCR_CB_BULK_SEARCH  |
	DCR_CB_INDEX_CACHE  |
	DCR_CB_RESIZE_CACHE |
	DCR_CB_INITIAL_LOAD |
	DCR_CB_RELOAD       |
	DCR_CB_UPDATE       |
	DCR_CB_ALLOC_CHUNK;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
int main(argc, argv)
int    argc;
char **argv;
{
	int                 return_code      = DCR_SUCCESS;
	unsigned int        max_rows         = UINT_MAX;
	int                 insert_method    = 0;
	int                 show_index_flag  = DCR_FALSE;
	unsigned int        count_1;
	DCR_CONTROL   cache_control_data;
	DCR_CACHE          *cache_ptr;
	MFILE              *mfile_ptr_1;
	MFILE              *mfile_ptr_2;
	unsigned int        cache_index;
	char                error_text[DCR_MAX_ERROR_TEXT];
	unsigned int        record_count;
	void               *record_list = NULL;
	unsigned int        record_size;

	fprintf(stderr,
		"Test routine for cache insertion and indexing logic number 03'\n");
	fprintf(stderr,
		"---- ------- --- ----- --------- --- -------- ----- ------ --\n\n");

	memset(&cache_control_data, '\0', sizeof(cache_control_data));

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "Help request with '%s' noted . . .\n\n",
				argv[count_1]);
			fprintf(stderr, "USAGE:\n   %s %s %s %s\n\n", argv[0],
				"<input-cache-file-name> <output-cache-file-name>",
				"-MAX_ROWS=<row-count>",
				"[-INSERT_METHOD={NEW|OLD}] [-SHOW_INDEX={OFF|ON}]");
			goto EXIT_FUNCTION;
		}
		else if (!strnicmp(argv[count_1], "-MAX_ROWS=", strlen("-MAX_ROWS=")))
			max_rows = atoi(argv[count_1] + strlen("-MAX_ROWS="));
		else if (!stricmp(argv[count_1], "-INSERT_METHOD=OLD"))
			insert_method = -1;
		else if (!stricmp(argv[count_1], "-INSERT_METHOD=NEW"))
			insert_method = 0;
		else if (!stricmp(argv[count_1], "-SHOW_INDEX=ON"))
			show_index_flag = DCR_TRUE;
		else if (!stricmp(argv[count_1], "-SHOW_INDEX=OFF"))
			show_index_flag = DCR_FALSE;
	}

	if (argc < 3) {
		sprintf(error_text, "%s (%s) --- use '-HELP' for help.",
			"Expected a command-line parameter", "the cache file name");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((return_code = DCR_AllocCacheControl(&cache_control_data,
		100, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Allocated the cache control structure.\n");

	if ((return_code = DCR_OpenRead(&cache_control_data, argv[1],
		0, 0L, 0, 0L, &cache_ptr, &cache_index, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Opened cache '%s' for reading.\n", argv[1]);

	if ((mfile_ptr_1 = mopen(cache_ptr->cache_file_name, "r")) == NULL) {
		sprintf(error_text, "Unable to 'mopen()' cache '%s' for reading: ",
			argv[1]);
		DCR_GEN_AppendLastErrorString(error_text);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "'mopen()' of cache '%s' for reading succeeded.\n",
		argv[1]);

	if ((mfile_ptr_2 = mopen(argv[2], "w")) == NULL) {
		sprintf(error_text, "Unable to 'mopen()' cache '%s' for writing: ",
			argv[2]);
		DCR_GEN_AppendLastErrorString(error_text);
		mclose(mfile_ptr_1);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "'mopen()' of cache '%s' for writing succeeded.\n",
		argv[2]);

	if (mtruncate_safe(mfile_ptr_2, cache_ptr->total_cache_size)) {
		sprintf(error_text,
			"Unable to 'mtruncate_safe()' cache '%s' to %u bytes: ",
			argv[2], cache_ptr->total_cache_size);
		DCR_GEN_AppendLastErrorString(error_text);
		mclose(mfile_ptr_1);
		munlink(mfile_ptr_2);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "Truncation of cache '%s' to %u bytes succeeded.\n",
		argv[2], cache_ptr->total_cache_size);

	madvise(((void *) mfile_ptr_1->mmap_ptr), mfile_ptr_1->mmap_size,
		MADV_SEQUENTIAL);
	madvise(((void *) mfile_ptr_2->mmap_ptr), mfile_ptr_2->mmap_size,
		MADV_SEQUENTIAL);

	bcopy(((void *) mfile_ptr_1->mmap_ptr), ((void *) mfile_ptr_2->mmap_ptr),
		cache_ptr->total_cache_size);

	fprintf(stderr, "Copied cache '%s' to cache '%s'\n", argv[1], argv[2]);

	DCR_CloseOneCache(cache_ptr);
	mclose(mfile_ptr_1);
	mclose(mfile_ptr_2);

	if ((return_code = DCR_OpenWrite(&cache_control_data, argv[2],
		&cache_ptr, &cache_index, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Opened cache '%s' for writing.\n", argv[1]);

	DCR_SetUserCallBack(cache_ptr, &Test_CallBackMask, Test_CallBack);

	if ((max_rows != UINT_MAX) && (max_rows < cache_ptr->record_count)) {
		cache_ptr->header_ptr->record_count = max_rows;
		cache_ptr->record_count             = max_rows;
		DCR_IndexCache(cache_ptr);
	}

	fprintf(stdout, "%s\n",
"==========================================================================");

	memset(cache_ptr->header_ptr->stat_list, '\0',
		sizeof(cache_ptr->header_ptr->stat_list));

	record_count = cache_ptr->record_count;
	record_size  = cache_ptr->total_record_size;
	if ((record_list = calloc(cache_ptr->record_count, record_size)) == NULL) {
		strcpy(error_text, "Unable to allocate record list.");
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	bcopy(DCR_RELE_TO_RPTR(cache_ptr, 0), record_list,
		record_count * record_size);

	if (insert_method == -1) {
		if ((return_code = OLD_DCR_InsertBulk(cache_ptr,
			record_count, record_list, record_size,
			error_text)) != DCR_SUCCESS)
			goto EXIT_FUNCTION;
	}
	else {
		if ((return_code = DCR_InsertBulk(cache_ptr,
			record_count, record_list, record_size,
			error_text)) != DCR_SUCCESS)
			goto EXIT_FUNCTION;
	}

#ifndef NARGS
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Record Insert Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		DCR_STAT_BULK_INSERT, ((void (*)(void *, char *, ...)) fprintf),
		stdout);
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Record Index Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		DCR_STAT_INDEX, ((void (*)(void *, char *, ...)) fprintf),
		stdout);
#else
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Record Insert Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		DCR_STAT_BULK_INSERT, fprintf, stdout);
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Record Insert Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		DCR_STAT_INDEX, fprintf, stdout);
#endif /* #ifndef NARGS */

	if (show_index_flag == DCR_TRUE) {
		fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
		DCR_EmitAllIndexLists(cache_ptr);
	}
	fprintf(stdout, "%s\n",
"==========================================================================");

	fprintf(stderr, "Checking indices in cache file '%s' . . .",
		cache_ptr->cache_file_name);
	if (DCR_CheckIndicesElements(cache_ptr, error_text) == DCR_SUCCESS)
		fprintf(stderr, " OK\n");
	else
		fprintf(stderr, " ERROR: %s\n", error_text);

EXIT_FUNCTION:

	if (record_list != NULL)
		free(record_list);

	DCR_CloseAllCaches(&cache_control_data);

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

static void DCR_EmitAllIndexLists(cache_ptr)
DCR_CACHE *cache_ptr;
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
		fprintf(stdout, "Index Number %u\n", count_1);
		fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
		DCR_EmitOneIndexList(cache_ptr, count_1);
		fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	}
}

static void DCR_EmitOneIndexList(cache_ptr, index_method)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
{
	unsigned int count_1;
	char         *tmp_ptr;

	for (count_1 = 0; count_1 < cache_ptr->record_count; count_1++) {
		printf("[%010u]:%10u:", count_1,
			DCR_IELE_TO_ROFF(cache_ptr, index_method, count_1));
		tmp_ptr = DCR_IELE_TO_IPTR(cache_ptr, index_method, count_1);
		switch (index_method) {
			case 0	:
				printf("[%11d]\n", *((int *) tmp_ptr));
				break;
			case 1	:
				printf("[%-20.20s][%11d][%11d]\n", tmp_ptr,
					*((int *) (tmp_ptr + 20)), *((int *) (tmp_ptr + 24)));
				break;
			case 2	:
				printf("[%11d][%11d]\n", *((int *) tmp_ptr),
					*((int *) (tmp_ptr + 4)));
				break;
			default	:
				printf("\n");
				break;
		}
	}
}
/*	***********************************************************************	*/

int OLD_DCR_InsertBulk(cache_ptr, in_record_count, in_record_list,
	in_record_size, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   in_record_count;
const void    *in_record_list;
unsigned int   in_record_size;
char          *error_text;
{
	int              return_code = DCR_SUCCESS;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned long    old_cache_status;
	unsigned long    record_offset;
	char            *in_record_ptr;
	char            *out_record_ptr;
	unsigned int     current_record;
	const DCR_FIELD *update_date_field_ptr;
	char            *update_date_ptr;
	unsigned int     max_update_date_record;
	DTIME            max_update_date;
	DTIME            current_update_date;
	DBC_FUNCS        dbc_funcs;
	char             dbc_error_text[DBC_MAX_ERROR_TEXT];

	DBC_AttachFacility(&dbc_funcs);
	if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
		(dbc_funcs.date_to_dtime == NULL)) {
		strcat(strcpy(error_text, "Unable to locate the DBC database "),
			"'date-to-DTIME conversion function.");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_BULK_INSERT);
	if ((cache_ptr->call_back_mask & DCR_CB_BULK_INSERT) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_BULK_INSERT,
		DCR_FALSE, 0, 0, in_record_count, in_record_list, NULL, return_code,
		error_text);

	if (!in_record_size) {
		strcpy(error_text, "Bulk insert record size is zero (0).");
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if (in_record_size < cache_ptr->header_ptr->actual_data_record_size) {
		sprintf(error_text, "%s (%u) %s (%u).",
			"The bulk insert record size", in_record_size,
			"is less than the actual data record size for this cache",
			cache_ptr->header_ptr->actual_data_record_size);
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if (in_record_count &&
		(((cache_ptr->header_ptr->record_count + in_record_count) <=
		cache_ptr->header_ptr->allocated_record_count) ||
		((return_code = DCR_ResizeCache(cache_ptr,
		cache_ptr->record_count + in_record_count, DCR_TRUE, error_text)) ==
		DCR_SUCCESS))) {
		old_cache_status                                   =
			cache_ptr->header_ptr->cache_lock_status.lock_flag;
		cache_ptr->header_ptr->cache_lock_status.lock_flag =
			(cache_ptr->header_ptr->cache_lock_status.lock_flag &
			DCR_STATUS_CRITICAL) | DCR_STATUS_ADDING;
		cache_ptr->header_ptr->cache_status                =
			cache_ptr->header_ptr->cache_lock_status.lock_flag;
		record_offset  = cache_ptr->data_area_offset +
			(cache_ptr->record_count * cache_ptr->total_record_size);
		in_record_ptr  = ((char *) in_record_list);
		out_record_ptr = ((char *) cache_ptr->mmap_ptr) + record_offset;
		current_record = cache_ptr->record_count;
		if (cache_ptr->max_update_date_known == DCR_TRUE) {
			max_update_date        = cache_ptr->max_update_date;
			max_update_date_record = cache_ptr->max_update_date_record;
			update_date_ptr        = ((char *) in_record_ptr) +
				cache_ptr->update_date_field_offset;
		}
		memset(out_record_ptr, '\0',
			in_record_count * cache_ptr->total_record_size);
		for (count_1 = 0; count_1 < in_record_count; count_1++) {
			bcopy(in_record_ptr, out_record_ptr,
				cache_ptr->header_ptr->actual_data_record_size);
			for (count_2 = 0; count_2 < cache_ptr->index_count; count_2++) {
				if (DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE)
					memcpy(((char *) cache_ptr->index_data_list[count_2].
						index_entry_list) + (current_record * 
						DCR_INDEX_ENTRY_SIZE(cache_ptr, count_2)),
						&record_offset,
						DCR_INDEX_ENTRY_SIZE(cache_ptr, count_2));
				else
					DCR_CopyEmbedded(cache_ptr, count_2, record_offset,
						in_record_ptr,
						((char *) cache_ptr->index_data_list[count_2].
						index_entry_list) + (current_record *
						DCR_INDEX_ENTRY_SIZE(cache_ptr, count_2)));
			}
			if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
				((*dbc_funcs.date_to_dtime)(update_date_field_ptr->db_type,
				update_date_ptr, &current_update_date, dbc_error_text) ==
				DBC_SUCCESS) && (DTIME_Compare(&cache_ptr->max_update_date,
				current_update_date) < 0)) {
				max_update_date        = current_update_date;
				max_update_date_record = current_record;
			}
			in_record_ptr   += in_record_size;
			out_record_ptr  += cache_ptr->total_record_size;
			record_offset   += cache_ptr->total_record_size;
			update_date_ptr += cache_ptr->total_record_size;
			current_record++;
		}
		if (cache_ptr->critical_call_back_function != NULL)
			(*cache_ptr->critical_call_back_function)(cache_ptr,
				DCR_CB_BULK_INSERT, DCR_FALSE, 0, 1, in_record_ptr,
				return_code, error_text);
		cache_ptr->header_ptr->cache_lock_status.lock_flag |=
			DCR_STATUS_CRITICAL;
		cache_ptr->header_ptr->cache_status                 =
			cache_ptr->header_ptr->cache_lock_status.lock_flag;
		for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++)
			DCR_Sort(cache_ptr, count_1, current_record,
				cache_ptr->index_data_list[count_1].index_entry_list);
		cache_ptr->header_ptr->record_count                = current_record;
		cache_ptr->record_count                            = current_record;
		cache_ptr->header_ptr->cache_lock_status.lock_count++;
		cache_ptr->header_ptr->cache_lock_status.lock_flag = old_cache_status;
		cache_ptr->header_ptr->cache_status                = old_cache_status;
		if (cache_ptr->max_update_date_known == DCR_TRUE) {
			cache_ptr->max_update_date_record = max_update_date_record;
			cache_ptr->max_update_date        = max_update_date;
		}
		if (cache_ptr->critical_call_back_function != NULL)
			(*cache_ptr->critical_call_back_function)(cache_ptr,
				DCR_CB_BULK_INSERT, DCR_TRUE, 0, 1, in_record_ptr,
				return_code, error_text);
	}

	DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_BULK_INSERT, ((unsigned long) in_record_count));
	if ((cache_ptr->call_back_mask & DCR_CB_BULK_INSERT) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_BULK_INSERT,
		DCR_TRUE, 0, 0, in_record_count, in_record_list,
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_BULK_INSERT, return_code, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_InsertBulk(cache_ptr, in_record_count, in_record_list,
	in_record_size, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   in_record_count;
const void    *in_record_list;
unsigned int   in_record_size;
char          *error_text;
{
	int           return_code = DCR_SUCCESS;
	unsigned int  count_1;
	char         *in_record_ptr;
	char         *record_ptr;
	unsigned int  total_record_count;
	DCR_INS_2    *ins_list;
	DTIME         current_update_date;
	DBC_FUNCS     dbc_funcs;
	char          dbc_error_text[DBC_MAX_ERROR_TEXT];

	DBC_AttachFacility(&dbc_funcs);
	if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
		(dbc_funcs.date_to_dtime == NULL)) {
		strcat(strcpy(error_text, "Unable to locate the DBC database "),
			"'date-to-DTIME conversion function.");
		return_code = DCR_FAILURE;
		return(return_code);
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Initialize the statistic values and perform call-backs . . .	*/
	/*	*****************************************************************	*/
	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_BULK_INSERT);
	if ((cache_ptr->call_back_mask & DCR_CB_BULK_INSERT) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_BULK_INSERT,
		DCR_FALSE, 0, 0, in_record_count, in_record_list, NULL, return_code,
		error_text);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Check some parameters . . .												*/
	/*	*****************************************************************	*/
	if (!in_record_size) {
		strcpy(error_text, "Bulk insert record size is zero (0).");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (in_record_size < cache_ptr->header_ptr->actual_data_record_size) {
		sprintf(error_text, "%s (%u) %s (%u).",
			"The bulk insert record size", in_record_size,
			"is less than the actual data record size for this cache",
			cache_ptr->header_ptr->actual_data_record_size);
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If no records on which to work then we're done . . .				*/
	/*	*****************************************************************	*/
	if (!in_record_count)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If all goes well, this'll be the number of records in the		*/
	/*	when we're finished.																*/
	/*	*****************************************************************	*/
	total_record_count = cache_ptr->record_count + in_record_count;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We may have to re-size the cache in order to accomodate the		*/
	/*	new records.																		*/
	/*	*****************************************************************	*/
	if ((total_record_count > cache_ptr->header_ptr->allocated_record_count) &&
		((return_code = DCR_ResizeCache(cache_ptr, total_record_count,
		DCR_TRUE, error_text)) != DCR_SUCCESS))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If there are not records already in the cache, this should be	*/
	/*	easy --- just put the records into the cache data area and then	*/
	/*	index them . . .																	*/
	/*	*****************************************************************	*/
	if (!cache_ptr->record_count) {
		in_record_ptr = ((char *) in_record_list);
		record_ptr    = DCR_RELE_TO_RPTR(cache_ptr, 0);
		for (count_1 = 0; count_1 < in_record_count; count_1++,
			in_record_ptr += in_record_size,
			record_ptr += cache_ptr->total_record_size)
			memcpy(record_ptr, in_record_ptr,
				cache_ptr->actual_data_record_size);
		cache_ptr->header_ptr->record_count += in_record_count;
		cache_ptr->record_count             += in_record_count;
		DCR_IndexCache(cache_ptr);
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Attempt to allocate enough records to record the relative		*/
	/*	position of each record for which the search is to be performed	*/
	/*	using each index method.														*/
	/*																							*/
	/*		If we can allocate the memory, then we just invoke the logic	*/
	/*	which will merge the records into the cache . . .						*/
	/*	*****************************************************************	*/
	if ((ins_list = ((DCR_INS_2 *) calloc(in_record_count *
		cache_ptr->index_count, sizeof(DCR_INS_2)))) != NULL) {
		return_code = DCR_InsListControl(cache_ptr,
			DCR_INSERT_ALLOC_FULL, in_record_count, in_record_list,
			in_record_size, DCR_TRUE, in_record_count, ins_list, error_text);
      free(ins_list);
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Otherwise, we'll just add the records to the cache and the		*/
	/*	re-index the entire thing . . .												*/
	/*	*****************************************************************	*/
	in_record_ptr = ((char *) in_record_list);
	record_ptr    = DCR_RELE_TO_RPTR(cache_ptr, cache_ptr->record_count);
	for (count_1 = 0; count_1 < in_record_count; count_1++,
		in_record_ptr += in_record_size,
		record_ptr += cache_ptr->total_record_size) {
		memcpy(record_ptr, in_record_ptr,
			cache_ptr->actual_data_record_size);
		if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
			((*dbc_funcs.date_to_dtime)(cache_ptr->field_list[
			cache_ptr->update_date_field_index].db_type,
			record_ptr + cache_ptr->update_date_field_offset,
			&current_update_date, dbc_error_text) == DBC_SUCCESS) &&
			(DTIME_Compare(&cache_ptr->max_update_date,
			&current_update_date) < 0))
			DCR_SetMaxUpdateDate(cache_ptr, cache_ptr->record_count + count_1,
				&current_update_date, error_text);
	}
	cache_ptr->header_ptr->record_count += in_record_count;
	cache_ptr->record_count             += in_record_count;
	DCR_IndexCache(cache_ptr);
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Update the final statistic values and perform any required		*/
	/*	call-backs . . .																	*/
	/*	*****************************************************************	*/
	DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_BULK_INSERT, ((unsigned long) in_record_count));
	if ((cache_ptr->call_back_mask & DCR_CB_BULK_INSERT) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_BULK_INSERT,
		DCR_TRUE, 0, 0, in_record_count, in_record_list,
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_BULK_INSERT, return_code, error_text);
	/*	*****************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

void OLD_DCR_IndexCache(cache_ptr)
DCR_CACHE *cache_ptr;
{
	unsigned int count_1;

	if (cache_ptr->record_count) {
		for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
			if (DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE)
				DCR_IndexIndirect(cache_ptr, count_1,
					cache_ptr->index_data_list[count_1].index_entry_list);
			else
				DCR_IndexEmbedded(cache_ptr, count_1,
					cache_ptr->index_data_list[count_1].index_entry_list);
		}
	}
}
/*	***********************************************************************	*/

void DCR_IndexCache(cache_ptr)
DCR_CACHE *cache_ptr;
{
	unsigned int     count_1;
	DCR_INS_1 *ins_list;

	if (cache_ptr->record_count) {
		if ((ins_list = ((DCR_INS_1 *) calloc(cache_ptr->record_count,
			sizeof(DCR_INS_1)))) != NULL) {
			for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
				if (DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE)
					DCR_IndexIndirectFast(cache_ptr, count_1, ins_list,
						cache_ptr->index_data_list[count_1].index_entry_list);
				else
					DCR_IndexEmbeddedFast(cache_ptr, count_1, ins_list,
						cache_ptr->index_data_list[count_1].index_entry_list);
			}
			free(ins_list);
		}
		else {
			for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
				if (DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE)
					DCR_IndexIndirect(cache_ptr, count_1,
						cache_ptr->index_data_list[count_1].index_entry_list);
				else
					DCR_IndexEmbedded(cache_ptr, count_1,
						cache_ptr->index_data_list[count_1].index_entry_list);
			}
		}
	}
}
/*	***********************************************************************	*/

void DCR_IndexEmbeddedFast(cache_ptr, index_method, ins_list,
	entry_list)
DCR_CACHE       *cache_ptr;
unsigned int     index_method;
DCR_INS_1 *ins_list;
void            *entry_list;
{
	unsigned int   count_1;
	unsigned long  old_cache_status;
	char          *index_ptr;
	unsigned int   record_offset;
	char          *record_ptr;

	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_INDEX);
	if ((cache_ptr->call_back_mask & DCR_CB_INDEX_CACHE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_INDEX_CACHE,
		DCR_FALSE, index_method, 0, cache_ptr->record_count, entry_list, NULL,
		DCR_SUCCESS, NULL);

	record_offset = DCR_RELE_TO_ROFF(cache_ptr, 0);
	record_ptr    = DCR_RELE_TO_RPTR(cache_ptr, 0);

	for (count_1 = 0; count_1 < cache_ptr->record_count; count_1++,
		record_offset += cache_ptr->total_record_size,
		record_ptr += cache_ptr->total_record_size) {
		ins_list[count_1].record_offset = record_offset;
		ins_list[count_1].record_ptr    = record_ptr;
	}

	DCR_SortOne_INS_1(cache_ptr, index_method, cache_ptr->record_count,
		ins_list);

	old_cache_status                                   =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	cache_ptr->header_ptr->cache_lock_status.lock_flag =
		DCR_STATUS_INDEXING | DCR_STATUS_CRITICAL;
	cache_ptr->header_ptr->cache_status                =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;

	for (count_1 = 0, index_ptr = entry_list;
		count_1 < cache_ptr->record_count; count_1++,
		index_ptr += cache_ptr->index_list[index_method].index_entry_size)
		DCR_CopyEmbedded(cache_ptr, index_method,
			ins_list[count_1].record_offset, ins_list[count_1].record_ptr,
			index_ptr);

	cache_ptr->header_ptr->cache_lock_status.lock_count++;
	cache_ptr->header_ptr->cache_lock_status.lock_flag = old_cache_status;
	cache_ptr->header_ptr->cache_status                = old_cache_status;

	DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_INDEX, ((unsigned long) cache_ptr->record_count));
	if ((cache_ptr->call_back_mask & DCR_CB_INDEX_CACHE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_INDEX_CACHE,
		DCR_TRUE, index_method, 0, cache_ptr->record_count, entry_list,
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_INDEX, DCR_SUCCESS, NULL);
}
/*	***********************************************************************	*/

void DCR_IndexIndirectFast(cache_ptr, index_method, ins_list,
	entry_list)
DCR_CACHE       *cache_ptr;
unsigned int     index_method;
DCR_INS_1 *ins_list;
void            *entry_list;
{
	unsigned int   count_1;
	unsigned long  old_cache_status;
	unsigned int  *index_ptr;
	unsigned int   record_offset;
	char          *record_ptr;

	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_INDEX);
	if ((cache_ptr->call_back_mask & DCR_CB_INDEX_CACHE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_INDEX_CACHE,
		DCR_FALSE, index_method, 0, cache_ptr->record_count, entry_list, NULL,
		DCR_SUCCESS, NULL);

	record_offset = DCR_RELE_TO_ROFF(cache_ptr, 0);
	record_ptr    = DCR_RELE_TO_RPTR(cache_ptr, 0);

	for (count_1 = 0; count_1 < cache_ptr->record_count; count_1++,
		record_offset += cache_ptr->total_record_size,
		record_ptr += cache_ptr->total_record_size) {
		ins_list[count_1].record_offset = record_offset;
		ins_list[count_1].record_ptr    = record_ptr;
	}

	DCR_SortOne_INS_1(cache_ptr, index_method, cache_ptr->record_count,
		ins_list);

	old_cache_status                                   =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	cache_ptr->header_ptr->cache_lock_status.lock_flag =
		DCR_STATUS_INDEXING | DCR_STATUS_CRITICAL;
	cache_ptr->header_ptr->cache_status                =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;

	for (count_1 = 0, index_ptr = entry_list;
		count_1 < cache_ptr->record_count; count_1++, index_ptr++)
		*index_ptr = ins_list[count_1].record_offset;

	cache_ptr->header_ptr->cache_lock_status.lock_count++;
	cache_ptr->header_ptr->cache_lock_status.lock_flag = old_cache_status;
	cache_ptr->header_ptr->cache_status                = old_cache_status;

	DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_INDEX, ((unsigned long) cache_ptr->record_count));
	if ((cache_ptr->call_back_mask & DCR_CB_INDEX_CACHE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_INDEX_CACHE,
		DCR_TRUE, index_method, 0, cache_ptr->record_count, entry_list,
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_INDEX, DCR_SUCCESS, NULL);
}
/*	***********************************************************************	*/

static int Test_CallBack(cache_ptr, call_back_type, post_operation_flag,
	index_method, operation_flags, operation_count, operation_ptr, stat_ptr,
	return_code, error_text)
DCR_CACHE      *cache_ptr;
unsigned long   call_back_type;
int             post_operation_flag;
unsigned int    index_method;
int             operation_flags;
unsigned int    operation_count;
void           *operation_ptr;
DCR_STAT *stat_ptr;
int             return_code;
char           *error_text;
{
	struct timeval tmp_timeval;
	char           tmp_buffer_1[100];
	char           tmp_buffer_2[100];

	if (call_back_type == DCR_CB_BULK_INSERT) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			fprintf(stderr,
				"Bulk inserted %u records in %s time (%s %s).\n",
				operation_count,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_BULK_SEARCH) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			fprintf(stderr,
				"Bulk searched %u records (%u %s, %u %s) in %s time (%s %s).\n",
				operation_count, cache_ptr->last_search_update_count, "inserted",
				cache_ptr->last_search_insert_count, "updated",
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_INDEX_CACHE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			fprintf(stderr,
				"Indexed %u %s %u in %s time (%s %s).\n",
				operation_count, "records on index number", index_method,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_SORT_CACHE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			fprintf(stderr,
				"Indexed %u %s %u in %s time (%s %s).\n",
				operation_count, "records on index number", index_method,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_RESIZE_CACHE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			fprintf(stderr,
				"Re-sized the cache file to %lu bytes.\n",
				((DCR_HEADER *) cache_ptr->header_ptr)->total_cache_size);
	}
	else if (call_back_type == DCR_CB_INITIAL_LOAD) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			fprintf(stderr,
				"Performed an database initial load of %u records.\n",
				operation_count);
	}
	else if (call_back_type == DCR_CB_RELOAD) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			fprintf(stderr,
				"Performed an database re-load of %u records.\n",
				operation_count);
	}
	else if (call_back_type == DCR_CB_UPDATE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			fprintf(stderr,
				"%s %u %s '%s' %s '%s'.\n",
				"Performed an database update load of", operation_count,
				"records with an", cache_ptr->update_date_field_name,
				"column greater than or equal to",
				DBC_SYB_FMT_SYBDATETIME_SQL(&cache_ptr->old_max_update_date,
					tmp_buffer_1));
	}
	else if (call_back_type == DCR_CB_ALLOC_CHUNK) {
		;
	}

	return(DCR_SUCCESS);
}
/*	***********************************************************************	*/

