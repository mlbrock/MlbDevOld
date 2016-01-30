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

	Revision History	:	1994-03-14 --- Creation.
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

#include <memory.h>

#include "dcr.h"

/*	***********************************************************************	*/

#define TEST_RECORD_FILE					"CACHE.REC"

#define TEST_CACHE_FILE						"TESTFILE.SCF"

#define START_ALLOC_SIZE					4096
#define END_ALLOC_SIZE						4096
#define ALLOC_SIZE							4096

#include "datatest.h"						/* For the test meta-data . . .		*/

static char          *TestCommandList[] = {
	"Program Name",
	"INDIRECT",
	"EMBEDDED",
	NULL
};

static unsigned int   TestCommandCount  =
	(sizeof(TestCommandList) / sizeof(TestCommandList[0])) - 1;

static unsigned long  TestCallBackMask  =
	DCR_CB_BULK_INSERT  |
	DCR_CB_SORT_CACHE  |
	DCR_CB_RESIZE_CACHE;

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

#ifndef NARGS
static int TestStress(DCR_CONTROL *cache_control_ptr,
	unsigned int argc, char **argv, char *error_text);
static int DoStress(DCR_CONTROL *cache_control_ptr,
	unsigned int initial_alloc_size, unsigned int alloc_size, int force_flag,
	unsigned int issue_id_count, ISSUE_ID *issue_id_list,
	int indirect_index_flag, char *error_text);
static int TestCallBack(DCR_CACHE *cache_ptr, unsigned long call_back_type,
	int post_operation_flag, unsigned int index_method, int operation_flags,
	unsigned int operation_count, void *operation_ptr,
	DCR_STAT *stat_ptr, int return_code, char *error_text);
#else
static int TestStress();
static int DoStress();
static int TestCallBack();
#endif /* #ifndef NARGS */

int main(argc, argv)
int    argc;
char **argv;
{
	int               return_code;
	DCR_CONTROL cache_control_data;
	char              error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for the DCR cache functions 01\n");
	fprintf(stderr, "---- ------- --- --- --- ----- --------- --\n\n");

	fprintf(stderr, "USAGE:\n%s %s %s %s %s %s\n\n", argv[0],
		"[<record-count>]", "[INDIRECT|EMBEDDED]", "[INITIAL_ALLOC=<count>]",
		"[ALLOC=<count>]", "[FORCE|NO[_]FORCE]");

	if ((return_code = DCR_AllocCacheControl(&cache_control_data,
		100, error_text)) == DCR_SUCCESS) {
		if (argc > 1)
			return_code = TestStress(&cache_control_data, ((unsigned int) argc),
				argv, error_text);
		else
			return_code = TestStress(&cache_control_data, TestCommandCount,
				TestCommandList, error_text);
	}

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

static int TestStress(cache_control_ptr, argc, argv, error_text)
DCR_CONTROL  *cache_control_ptr;
unsigned int        argc;
char              **argv;
char               *error_text;
{
	int           return_code = DCR_SUCCESS;
	unsigned int  count_1;
	unsigned int  issue_id_count;
	ISSUE_ID     *issue_id_list;
	MFILE        *in_mfile_ptr;
	int           indirect_index_flag;
	unsigned int  initial_alloc_size;
	unsigned int  alloc_size;
	int           force_flag;
	unsigned int  tmp_issue_id_count;

	if ((in_mfile_ptr = mopen(TEST_RECORD_FILE, "r")) == NULL) {
		sprintf(error_text,
			"Unable to open DCR cache test record file '%-.500s' for reading: ",
			TEST_RECORD_FILE);
		DCR_GEN_AppendLastErrorString(error_text);
		return_code = DCR_SYSTEM_FAILURE;
	}
	else {
		if (in_mfile_ptr->file_size % sizeof(ISSUE_ID)) {
			sprintf(error_text, "%s '%-.500s' (%lu) %s (%u).",
				"The size of the DCR cache test record file", TEST_RECORD_FILE,
				in_mfile_ptr->file_size,
				"is not an integral multiple of the 'ISSUE_ID' structure size",
				sizeof(ISSUE_ID));
			return_code = DCR_FAILURE;
		}
		else if (!(issue_id_count =
			(in_mfile_ptr->file_size / sizeof(ISSUE_ID)))) {
			sprintf(error_text, "%s '%-.500s' (file size = %lu).",
				"There are zero records in the DCR cache test record file",
				TEST_RECORD_FILE, in_mfile_ptr->file_size);
			return_code = DCR_FAILURE;
		}
		else {
			madvise(in_mfile_ptr->mmap_ptr, in_mfile_ptr->file_size,
				MADV_SEQUENTIAL);
			issue_id_list       = ((ISSUE_ID *) in_mfile_ptr->mmap_ptr);
			indirect_index_flag = DCR_TRUE;
			initial_alloc_size  = 4096;
			alloc_size          = 4096;
			force_flag          = DCR_FALSE;
			tmp_issue_id_count  = issue_id_count;
			fprintf(stderr, "%s\n",
"==========================================================================");
			for (count_1 = 1; count_1 < argc; count_1++) {
				if (!stricmp(argv[count_1], "INDIRECT"))
					indirect_index_flag = DCR_TRUE;
				else if (!stricmp(argv[count_1], "EMBEDDED"))
					indirect_index_flag = DCR_FALSE;
				else if ((!strnicmp(argv[count_1], "INITIAL_ALLOC=", 14)) &&
					isdigit(argv[count_1][14])) {
					initial_alloc_size = atoi(argv[count_1] + 14);
				}
				else if ((!strnicmp(argv[count_1], "ALLOC=", 6)) &&
					isdigit(argv[count_1][6])) {
					alloc_size = atoi(argv[count_1] + 6);
				}
				else if (!stricmp(argv[count_1], "FORCE"))
					force_flag = DCR_TRUE;
				else if ((!stricmp(argv[count_1], "NO_FORCE")) ||
					(!stricmp(argv[count_1], "NOFORCE")))
					force_flag = DCR_FALSE;
				else if (isdigit(argv[count_1][0])) {
					tmp_issue_id_count = atoi(argv[count_1]);
					tmp_issue_id_count = (tmp_issue_id_count > issue_id_count) ?
						issue_id_count : tmp_issue_id_count;
				}
				else {
					fprintf(stderr,
						"INVALID COMMAND-LINE PARAMETER '%s' --- IGNORED\n",
						argv[count_1]);
					continue;
				}
				fprintf(stderr, "Starting Test %10u\n", count_1);
				fprintf(stderr, "-------- ---- ----------\n");
				fprintf(stderr, ">>> Index Type             : %s\n",
					(indirect_index_flag == DCR_TRUE) ? "INDIRECT" : "EMBEDDED");
				fprintf(stderr, ">>> Initial Allocation Size: %10u\n",
					initial_alloc_size);
				fprintf(stderr, ">>> Allocation Size        : %10u\n",
					alloc_size);
				fprintf(stderr, ">>> Input Record Count     : %10u\n",
					tmp_issue_id_count);
				fprintf(stderr, "%s\n",
"--------------------------------------------------------------------------");
				if ((return_code = DoStress(cache_control_ptr, initial_alloc_size,
					alloc_size, force_flag, tmp_issue_id_count, issue_id_list,
					indirect_index_flag, error_text)) != DCR_SUCCESS)
					break;
				fprintf(stderr, "%s\n",
"==========================================================================");
			}
		}
		mclose(in_mfile_ptr);
	}

	return(return_code);
}

static int DoStress(cache_control_ptr, initial_alloc_size, alloc_size,
	force_flag, issue_id_count, issue_id_list, indirect_index_flag, error_text)
DCR_CONTROL *cache_control_ptr;
unsigned int       initial_alloc_size;
unsigned int       alloc_size;
int                force_flag;
unsigned int       issue_id_count;
ISSUE_ID          *issue_id_list;
int                indirect_index_flag;
char              *error_text;
{
	int               return_code;
	unsigned int      count_1;
	DCR_CACHE        *cache_ptr;
	DCR_CACHE         cache_data;
	DCR_HEADER *cache_header_ptr;
	unsigned int      cache_index;
	unsigned int      record_element;
	unsigned long     record_offset;
	int               errno_code;
	int               open_failure_flag;
	int               mmap_failure_flag;
	struct timeval    start_time;
	struct timeval    end_time;
	struct timeval    total_time;
	char              time_buffer[100];


	if ((return_code = DCR_MakeHeader("TEST_CACHE_NAME", "TEST_DB",
		"TEST_OWNER", "TEST_TABLE", "mlds", "mlds", initial_alloc_size,
		alloc_size, LogicalTypeCount, LogicalTypeList, LogicalFieldCount,
		LogicalFieldList, LogicalFormCount, LogicalFormList, DataLocationCount,
		DataLocationList, LogicalServerCount, LogicalServerList,
		indirect_index_flag, 0, NULL, IndexSpecCount, IndexSpecList,
		&cache_header_ptr, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	if (force_flag == DCR_TRUE) {
		cache_header_ptr->initial_allocation_size = initial_alloc_size;
		cache_header_ptr->allocation_size         = alloc_size;
	}

	fprintf(stderr, ">>> Initial Allocation Size: %10u\n",
		cache_header_ptr->initial_allocation_size);
	fprintf(stderr, ">>> Allocation Size        : %10u\n",
		cache_header_ptr->allocation_size);
	fprintf(stderr, "%s\n",
"--------------------------------------------------------------------------");

	memset(&cache_data, '\0', sizeof(cache_data));

	cache_data.open_flag   = O_RDWR | O_CREAT | O_TRUNC;
	cache_data.mmap_prot   = PROT_READ | PROT_WRITE;
	cache_data.mmap_flag   = MAP_SHARED;
	cache_data.file_handle = -1;
	cache_data.mmap_ptr    = NULL;
	cache_data.mmap_size   = cache_header_ptr->header_area_size;

	if ((return_code = DCR_AddACache(cache_control_ptr, TEST_CACHE_FILE,
		&cache_data, &cache_ptr, &cache_index, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = DCR_AllocCache(cache_ptr, cache_header_ptr,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	cache_ptr->cache_access_type                       = DCR_I_AM_WRITER;
	cache_ptr->header_ptr->cache_lock_status.lock_flag =
		DCR_STATUS_BUILDING | DCR_STATUS_CRITICAL;
	cache_ptr->header_ptr->cache_status                =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;

	SDTIF_GetTimeUSecs(&((DCR_HEADER *) cache_ptr->header_ptr)->
		cache_creation_time);

	cache_ptr->call_back_mask           = TestCallBackMask;
	cache_ptr->call_back_function       = TestCallBack;

	if ((return_code = DCR_OpenRaw(cache_ptr->cache_file_name,
		cache_ptr->open_flag, DCR_CREATE_MODE, cache_ptr->mmap_prot,
		cache_ptr->mmap_flag, &cache_ptr->file_handle, &cache_ptr->mmap_ptr,
		&cache_ptr->mmap_size, &errno_code, &open_failure_flag,
		&mmap_failure_flag, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = DCR_TruncateCache(cache_ptr,
		cache_header_ptr->header_area_size, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	memcpy(((void *) cache_ptr->mmap_ptr), cache_header_ptr,
		((unsigned int) cache_header_ptr->header_area_size));
	DCR_BindHeader(cache_ptr, cache_ptr->header_ptr);

/* NOTE: Should happen in header construction routine. */
cache_ptr->header_ptr->allocated_record_count = 0;

	if ((return_code = DCR_ResizeCache(cache_ptr,
		cache_ptr->header_ptr->initial_allocation_size, DCR_FALSE,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
madvise(((char *) cache_ptr->mmap_ptr) + cache_ptr->data_area_offset,
	cache_ptr->data_area_size, MADV_RANDOM);
madvise(((char *) cache_ptr->mmap_ptr) +
	cache_ptr->header_ptr->index_area_offset,
	cache_ptr->header_ptr->index_area_size, MADV_RANDOM);

	cache_ptr->header_ptr = ((DCR_HEADER *) cache_ptr->mmap_ptr);

	DCR_BindHeader(cache_ptr, cache_ptr->header_ptr);

	cache_ptr->header_ptr->cache_lock_status.lock_count++;
	cache_ptr->header_ptr->cache_lock_status.lock_flag = DCR_STATUS_OK;
	cache_ptr->header_ptr->cache_status                =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;

#if 0
	fprintf(stdout, "Before adding records\n");
#ifndef NARGS
	DCR_EmitHeader(cache_ptr, NULL,
		((void (*)(void *, char *, ...)) fprintf), stdout);
#else
	DCR_EmitHeader(cache_ptr, NULL, fprintf, stdout);
#endif /* #ifndef NARGS */
	fprintf(stdout, "\f");
#endif /* #if 0 */

	if ((return_code = DCR_InsertBulk(cache_ptr, issue_id_count,
		issue_id_list, sizeof(*issue_id_list), error_text)) != DCR_SUCCESS) {
		fprintf(stderr, "\n");
		goto EXIT_FUNCTION;
	}

#if 0
	fprintf(stderr, "Adding records (progress report per thousand) [");
	SDTIF_GetTimeUSecs(&start_time);
	for (count_1 = 0; count_1 < issue_id_count; count_1++) {
		if ((return_code = DCR_InsertRecord(cache_ptr,
			issue_id_list + count_1, &record_element, &record_offset,
			error_text)) != DCR_SUCCESS) {
			fprintf(stderr, "\n");
			goto EXIT_FUNCTION;
		}
		if (count_1 && (!(count_1 % 1000)))
			fprintf(stderr, ".");
	}
	SDTIF_GetTimeUSecs(&end_time);
	if (!(issue_id_count % 1000))
		fprintf(stderr, ".");
	fprintf(stderr, "]\n");
	fprintf(stderr, "done\n");
	fprintf(stderr, ">>> Total time     : %s\n",
		SDTIF_FormatInterval_timeval(SDTIF_GetInterval_timeval(&start_time,
		&end_time, &total_time), time_buffer));
	fprintf(stderr, ">>> Time per record: %s\n", SDTIF_FormatInterval_timeval(
		SDTIF_GetPerInterval_timeval(SDTIF_GetInterval_timeval(&start_time,
		&end_time, &total_time), ((unsigned long) issue_id_count),
		&total_time), time_buffer));
#endif /* #if 0 */

	fprintf(stderr, "Checking indices --- ");
	SDTIF_GetTimeUSecs(&start_time);
	if ((return_code = DCR_CheckIndicesElements(cache_ptr, error_text)) !=
		DCR_SUCCESS) {
		fprintf(stderr, "\n");
		goto EXIT_FUNCTION;
	}
	SDTIF_GetTimeUSecs(&end_time);
	fprintf(stderr, "done\n");
	fprintf(stderr, ">>> Total time     : %s\n",
		SDTIF_FormatInterval_timeval(SDTIF_GetInterval_timeval(&start_time,
		&end_time, &total_time), time_buffer));
	fprintf(stderr, ">>> Time per record: %s\n", SDTIF_FormatInterval_timeval(
		SDTIF_GetPerInterval_timeval(SDTIF_GetInterval_timeval(&start_time,
		&end_time, &total_time), ((unsigned long) issue_id_count),
		&total_time), time_buffer));

#if 0
	fprintf(stdout, "After adding records\n");
#ifndef NARGS
	DCR_EmitHeader(cache_ptr, NULL,
		((void (*)(void *, char *, ...)) fprintf), stdout);
#else
	DCR_EmitHeader(cache_ptr, NULL, fprintf, stdout);
#endif /* #ifndef NARGS */
	fprintf(stdout, "\f");
#endif /* #if 0 */

#if 0
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
#ifndef NARGS
		if ((return_code = DCR_EmitData(cache_ptr, count_1,
			DCR_FALSE, DCR_TRUE, 0, 60, " ", "-", "\f", "", "\n", 0, NULL, NULL,
			NULL, NULL, ((void (*)(void *, char *, ...)) fprintf), stdout,
			error_text)) != DCR_SUCCESS)
#else
		if ((return_code = DCR_EmitData(cache_ptr, count_1, DCR_FALSE,
			DCR_TRUE, 0, 60, " ", "-", "\f", "", "\n", 0, NULL, NULL, NULL, NULL,
			fprintf, stdout, error_text)) != DCR_SUCCESS)
#endif /* #ifndef NARGS */
			break;
	}
#endif /* #if 0 */

	DCR_CloseOneCache(cache_ptr);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

static int TestCallBack(cache_ptr, call_back_type, post_operation_flag,
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
			fprintf(stdout, "Bulk inserted %u records in %s time (%s %s).\n",
				operation_count,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_SORT_CACHE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			fprintf(stdout, "Indexed %u %s %u in %s time (%s %s).\n",
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
			fprintf(stdout, "Re-sized the cache file to %lu bytes.\n",
				cache_ptr->total_cache_size);
	}

	return(DCR_SUCCESS);
}
/*	***********************************************************************	*/

