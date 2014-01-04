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

	Revision History	:	1995-02-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
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
	unsigned int        max_rows         = 0;
	int                 insert_method    = DCR_INSERT_ALLOC_FULL;
	int                 show_index_flag  = DCR_FALSE;
	int                 update_flag      = DCR_FALSE;
	unsigned int        load_granularity = 0;
	unsigned int        count_1;
	DCR_CONTROL   cache_control_data;
	DCR_CACHE          *cache_ptr;
	MFILE              *mfile_ptr_1;
	MFILE              *mfile_ptr_2;
	unsigned int        cache_index;
	char                error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for function 'DCR_SearchBulk()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------------------\n\n");

	memset(&cache_control_data, '\0', sizeof(cache_control_data));

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "Help request with '%s' noted . . .\n\n",
				argv[count_1]);
			fprintf(stderr, "USAGE:\n   %s %s %s %s %s\n\n", argv[0],
				"<input-cache-file-name> <output-cache-file-name>",
				"-MAX_ROWS=<row-count>",
				"[-INSERT_METHOD={FULL|OLD|NONE|PART}] [-SHOW_INDEX={OFF|ON}]",
				"[-UPDATE={OFF|ON}] [-GRANULARITY=<row-count>]");
			goto EXIT_FUNCTION;
		}
		else if (!strnicmp(argv[count_1], "-MAX_ROWS=", strlen("-MAX_ROWS=")))
			max_rows = atoi(argv[count_1] + strlen("-MAX_ROWS="));
		else if (!stricmp(argv[count_1], "-INSERT_METHOD=OLD"))
			insert_method=-1;
		else if (!stricmp(argv[count_1], "-INSERT_METHOD=NONE"))
			insert_method=DCR_INSERT_ALLOC_NONE;
		else if (!stricmp(argv[count_1], "-INSERT_METHOD=PART"))
			insert_method=DCR_INSERT_ALLOC_PART;
		else if (!stricmp(argv[count_1], "-INSERT_METHOD=FULL"))
			insert_method=DCR_INSERT_ALLOC_FULL;
		else if (!stricmp(argv[count_1], "-SHOW_INDEX=ON"))
			show_index_flag = DCR_TRUE;
		else if (!stricmp(argv[count_1], "-SHOW_INDEX=OFF"))
			show_index_flag = DCR_FALSE;
		else if (!stricmp(argv[count_1], "-UPDATE=ON"))
			update_flag = DCR_TRUE;
		else if (!stricmp(argv[count_1], "-UPDATE=OFF"))
			update_flag = DCR_FALSE;
		else if (!strnicmp(argv[count_1], "-GRANULARITY=",
			strlen("-GRANULARITY=")))
			load_granularity = atoi(argv[count_1] + strlen("-GRANULARITY="));
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

	if ((return_code = DCR_MapDataAndIndices(cache_ptr,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Mapped data area and %u indices for cache '%s'.\n",
		cache_ptr->index_count, cache_ptr->cache_file_name);

	fprintf(stdout, "%s\n",
"==========================================================================");

	memset(cache_ptr->header_ptr->stat_list, '\0',
		sizeof(cache_ptr->header_ptr->stat_list));

	if (insert_method == -1) {
		if (update_flag != DCR_TRUE)
			return_code = OLD_DCR_DoCacheReload(cache_ptr, DCR_TRUE,
				DCR_FALSE, NULL, NULL, max_rows, load_granularity, error_text);
		else
			return_code = OLD_DCR_DoCacheUpdate(cache_ptr, "updatedate",
				max_rows, load_granularity, error_text);
		if (return_code != DCR_SUCCESS)
			goto EXIT_FUNCTION;
	}
	else {
		if (update_flag != DCR_TRUE)
			return_code = DCR_DoCacheReload(cache_ptr, insert_method,
				DCR_TRUE, DCR_FALSE, NULL, NULL, max_rows, load_granularity,
				error_text);
		else
			return_code = DCR_DoCacheUpdate(cache_ptr, insert_method,
				"updatedate", max_rows, load_granularity, error_text);
		if (return_code != DCR_SUCCESS)
			goto EXIT_FUNCTION;
	}

#ifndef NARGS
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Data Load Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		((update_flag == DCR_TRUE) ? DCR_STAT_DB_UPDATE :
		DCR_STAT_DB_RELOAD), ((void (*)(void *, char *, ...)) fprintf),
		stdout);
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Record Search Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		((insert_method == -1) ? DCR_STAT_SEARCH :
		DCR_STAT_BULK_SEARCH), ((void (*)(void *, char *, ...)) fprintf),
		stdout);
#else
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Data Load Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		((update_flag == DCR_TRUE) ? DCR_STAT_DB_UPDATE :
		DCR_STAT_DB_RELOAD), fprintf, stdout);
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Record Search Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		((insert_method == -1) ? DCR_STAT_SEARCH :
		DCR_STAT_BULK_SEARCH), fprintf, stdout);
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
/*	***********************************************************************	*/

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

