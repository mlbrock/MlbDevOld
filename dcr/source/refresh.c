/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Refreshes the image of a cache header, data, and
								indices.

	Revision History	:	1994-03-12 --- Creation.
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

#include <memory.h>
#include <stdio.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

#ifndef NARGS
static int DCR_RefreshWriter(DCR_CACHE *cache_ptr,
	unsigned int *record_count, void **record_list, unsigned int index_method,
	unsigned int *entry_count, void **entry_list, char *error_text);
static int DCR_RefreshReader(DCR_CACHE *cache_ptr,
	unsigned int *record_count, void **record_list, unsigned int index_method,
	unsigned int *entry_count, void **entry_list, char *error_text);
#else
static int DCR_RefreshWriter();
static int DCR_RefreshReader();
#endif /* #ifndef NARGS */

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DCR_Refresh(cache_ptr, record_count, record_list, index_method,
	entry_count, entry_list, error_text)
DCR_CACHE     *cache_ptr;
unsigned int  *record_count;
void         **record_list;
unsigned int   index_method;
unsigned int  *entry_count;
void         **entry_list;
char          *error_text;
{
	int return_code = DCR_FAILURE;

	if ((record_count == NULL) && (record_list != NULL)) {
		strcat(strcat(strcpy(error_text, "Bad cache refresh parameters: "),
			"the data area size pointer is 'NULL', "),
			"but the data area pointer is not 'NULL'.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((record_count != NULL) && (record_list == NULL)) {
		strcat(strcat(strcpy(error_text, "Bad cache refresh parameters: "),
			"the data area size pointer is not 'NULL', "),
			"but the data area pointer is 'NULL'.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((entry_count == NULL) && (entry_list != NULL)) {
		strcat(strcat(strcpy(error_text, "Bad cache refresh parameters: "),
			"the index entry count pointer is 'NULL', "),
			"but the index entry list pointer is not 'NULL'.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((entry_count != NULL) && (entry_list == NULL)) {
		strcat(strcat(strcpy(error_text, "Bad cache refresh parameters: "),
			"the index entry count pointer is not 'NULL', "),
			"but the index entry list pointer is 'NULL'.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((entry_count != NULL) && (entry_list != NULL) &&
		((return_code = DCR_ValidateIndexMethod(cache_ptr, index_method,
		error_text)) != DCR_SUCCESS))
		goto EXIT_FUNCTION;

	if (cache_ptr->cache_access_type == DCR_I_AM_WRITER)
		return_code = DCR_RefreshWriter(cache_ptr, record_count,
			record_list, index_method, entry_count, entry_list, error_text);
	else
		return_code = DCR_RefreshReader(cache_ptr, record_count,
			record_list, index_method, entry_count, entry_list, error_text);

EXIT_FUNCTION:

	if (return_code != DCR_SUCCESS) {
		if (record_count != NULL)
			*record_count = 0;
		if (record_list != NULL)
			*record_list = NULL;
		if (entry_count != NULL)
			*entry_count = 0;
		if (entry_list != NULL)
			*entry_list = NULL;
	}

	return(return_code);
}
/* *********************************************************************** */

static int DCR_RefreshWriter(cache_ptr, record_count, record_list,
	index_method, entry_count, entry_list, error_text)
DCR_CACHE     *cache_ptr;
unsigned int  *record_count;
void         **record_list;
unsigned int   index_method;
unsigned int  *entry_count;
void         **entry_list;
char          *error_text;
{
	int return_code = DCR_SUCCESS;

	if (record_count != NULL) {
		cache_ptr->record_mmap_size = cache_ptr->header_area_size +
			cache_ptr->data_area_size;
		cache_ptr->record_mmap_ptr  = ((void *) cache_ptr->mmap_ptr);
		*record_count               = cache_ptr->record_mmap_size;
		*record_list                = cache_ptr->record_mmap_ptr;
	}

	if (entry_count != NULL) {
		cache_ptr->index_data_list[index_method].mmap_size =
			cache_ptr->index_list[index_method].index_area_size;
		cache_ptr->index_data_list[index_method].mmap_ptr  =
			((char *) cache_ptr->mmap_ptr) + ((unsigned int)
			cache_ptr->index_list[index_method].index_area_offset);
		*entry_count                                       =
			cache_ptr->record_count;
		*entry_list                                        =
			cache_ptr->index_data_list[index_method].mmap_ptr;
	}

	*error_text = '\0';

	return(return_code);
}
/* *********************************************************************** */

static int DCR_RefreshReader(cache_ptr, record_count, record_list,
	index_method, entry_count, entry_list, error_text)
DCR_CACHE     *cache_ptr;
unsigned int  *record_count;
void         **record_list;
unsigned int   index_method;
unsigned int  *entry_count;
void         **entry_list;
char          *error_text;
{
	int                   return_code        = DCR_FAILURE;
	int                   size_changed_flag  = DCR_FALSE;
	unsigned int          total_cache_size;
	unsigned int          tmp_record_count;
	unsigned int          tmp_record_mmap_size;
	void                 *tmp_record_mmap_ptr;
	void                 *tmp_entry_list;
	DCR_INDEX      *index_ptr;
	DCR_INDEX_DATA *index_data_ptr;
	int                   mapped_data_flag;
	int                   mapped_index_flag;
	unsigned int          count_1;
	unsigned int          cycle_retry_count;
	DCR_LOCK              saved_lock_status;

	cycle_retry_count = cache_ptr->cycle_retry_count;

	for (count_1 = 0; count_1 < cycle_retry_count; ) {
		do {
			saved_lock_status = cache_ptr->header_ptr->cache_lock_status;
			total_cache_size  = cache_ptr->header_ptr->total_cache_size;
		} while ((saved_lock_status.lock_count !=
			cache_ptr->header_ptr->cache_lock_status.lock_count) ||
			(saved_lock_status.lock_flag !=
			cache_ptr->header_ptr->cache_lock_status.lock_flag));
		if (!(saved_lock_status.lock_flag & DCR_STATUS_CRITICAL)) {
			if (cache_ptr->total_cache_size != total_cache_size) {
				size_changed_flag = DCR_TRUE;
				if ((return_code = DCR_ReMapCache(cache_ptr, error_text)) ==
					DCR_SUCCESS)
					continue;
				else if (return_code != DCR_LOCK_ACQ_FAILURE)
					break;
				usleep(cache_ptr->cycle_retry_time_out);
				count_1 = 0;
				continue;
			}
			mapped_data_flag  = DCR_FALSE;
			mapped_index_flag = DCR_FALSE;
			if (record_count != NULL) {
				tmp_record_mmap_size = cache_ptr->header_area_size +
					cache_ptr->data_area_size;
				if ((cache_ptr->record_mmap_ptr != NULL) &&
					(size_changed_flag == DCR_FALSE))
					tmp_record_mmap_ptr = cache_ptr->record_mmap_ptr;
				else if (((int) (tmp_record_mmap_ptr =
					((void *) mmap(NULL, ((int) tmp_record_mmap_size), PROT_READ,
					MAP_SHARED, cache_ptr->file_handle, 0)))) == -1) {
					sprintf(error_text, "%s to %u %s 0 failed: ",
						"Attempt to 'mmap()' the cache data area",
						tmp_record_mmap_size, "bytes starting at offset");
					DCR_GEN_AppendLastErrorString(error_text);
					tmp_record_mmap_ptr = NULL;
					return_code         = DCR_SYSTEM_FAILURE;
					break;
				}
				else
					mapped_data_flag = DCR_TRUE;
			}
			if (entry_count != NULL) {
				index_ptr      = cache_ptr->index_list + index_method;
				index_data_ptr = cache_ptr->index_data_list + index_method;
				if ((index_data_ptr->mmap_ptr != NULL) &&
					(size_changed_flag == DCR_FALSE))
					tmp_entry_list = index_data_ptr->mmap_ptr;
				else if (((int) (tmp_entry_list = ((void *) mmap(NULL,
					((int) index_ptr->index_area_size), PROT_READ, MAP_PRIVATE,
					cache_ptr->file_handle,
					((int) index_ptr->index_area_offset))))) == -1) {
					if (mapped_data_flag == DCR_TRUE)
						munmap(tmp_record_mmap_ptr, ((int) tmp_record_mmap_size));
					sprintf(error_text,
						"%s %u named '%s' to %lu %s %lu (0X%08lX) failed: ",
						"Attempt to 'mmap()' the cache index number",
						index_method, index_ptr->index_name,
						index_ptr->index_area_size,
						"bytes starting at offset",
						index_ptr->index_area_offset,
						index_ptr->index_area_offset);
					DCR_GEN_AppendLastErrorString(error_text);
					tmp_entry_list = NULL;
					return_code    = DCR_SYSTEM_FAILURE;
					break;
				}
				else
					mapped_index_flag = DCR_TRUE;
			}
			tmp_record_count = cache_ptr->header_ptr->record_count;
			if ((!(cache_ptr->header_ptr->cache_lock_status.lock_flag &
				DCR_STATUS_CRITICAL)) &&
				(total_cache_size == cache_ptr->header_ptr->total_cache_size)) {
				cache_ptr->record_count = tmp_record_count;
				if (record_count != NULL) {
					if (mapped_data_flag == DCR_TRUE)
						DCR_UnMapData(cache_ptr);
					cache_ptr->record_mmap_size = tmp_record_mmap_size;
					cache_ptr->record_mmap_ptr  = tmp_record_mmap_ptr;
					*record_count               = cache_ptr->record_count;
					*record_list                = tmp_record_mmap_ptr;
				}
				if (entry_count != NULL) {
					if (mapped_index_flag == DCR_TRUE)
						DCR_UnMapIndex(cache_ptr, index_method, error_text);
					index_data_ptr->mmap_size = index_ptr->index_area_size;
					index_data_ptr->mmap_ptr  = tmp_entry_list;
					*entry_count              = cache_ptr->record_count;
					*entry_list               = tmp_entry_list;
				}
				return_code = DCR_SUCCESS;
				break;
			}
			if (mapped_data_flag == DCR_TRUE)
				munmap(tmp_record_mmap_ptr, ((int) tmp_record_mmap_size));
			if (mapped_index_flag == DCR_TRUE)
				munmap(tmp_entry_list, ((int) index_ptr->index_area_size));
		}
		cycle_retry_count =
			((saved_lock_status.lock_flag & DCR_STATUS_RESIZING) ||
			(cache_ptr->header_ptr->cache_lock_status.lock_flag &
			DCR_STATUS_RESIZING)) ? (cache_ptr->cycle_retry_count * 10) :
			cache_ptr->cycle_retry_count;
		if ((saved_lock_status.lock_count !=
			cache_ptr->header_ptr->cache_lock_status.lock_count) ||
			(saved_lock_status.lock_flag !=
			cache_ptr->header_ptr->cache_lock_status.lock_flag)) {
			count_1 = 0;
			continue;
		}
		else if (++count_1 == cycle_retry_count) {
			sprintf(error_text,
				"Unable to acquire reader lock on cache '%s' for refresh.",
				cache_ptr->header_ptr->cache_name);
			return_code = DCR_LOCK_ACQ_FAILURE;
			break;
		}
		usleep(cache_ptr->cycle_retry_time_out);
		if ((saved_lock_status.lock_count !=
			cache_ptr->header_ptr->cache_lock_status.lock_count) ||
			(saved_lock_status.lock_flag !=
			cache_ptr->header_ptr->cache_lock_status.lock_flag))
			count_1 = 0;
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

int main(argc, argv)
int    argc;
char **argv;
{
	int                 return_code = DCR_SUCCESS;
	unsigned int        test_count  = 10000;
	unsigned int        count_1;
	unsigned int        count_2;
	DCR_CONTROL   cache_control_data;
	DCR_CACHE          *cache_ptr;
	unsigned int        cache_index;
	char                error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for function 'DCR_Refresh()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------------------\n\n");

	memset(&cache_control_data, '\0', sizeof(cache_control_data));

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "Help request with '%s' noted . . .\n\n",
				argv[count_1]);
			fprintf(stderr, "USAGE:\n   %s %s\n\n", argv[0],
				"<input-cache-file-name> [<map-attempt-count>]");
			goto EXIT_FUNCTION;
		}
	}

	if (argc < 2) {
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

	fprintf(stderr, "Opened cache '%s' for reading (%u %s).\n", argv[1],
		cache_ptr->index_count, (cache_ptr->index_count == 1) ? "index" :
		"indices");

	if ((argc > 2) && (atoi(argv[2]) > 0))
		test_count = ((unsigned int) atoi(argv[2]));

	fprintf(stderr, "Will attempt to map the cache %u times.\n\n", test_count);

	fprintf(stderr, "Progress Report: [");
	for (count_1 = 0; count_1 < test_count; count_1++) {
		if ((return_code = DCR_MapData(cache_ptr, NULL, NULL,
			error_text)) != DCR_SUCCESS)
			break;
		for (count_2 = 0; count_2 < cache_ptr->index_count; count_2++) {
			if ((return_code = DCR_MapIndex(cache_ptr, count_2, NULL,
				NULL, error_text)) != DCR_SUCCESS)
				goto EXIT_FUNCTION;
			DCR_UnMapIndex(cache_ptr, count_2, error_text);
		}
		DCR_UnMapData(cache_ptr);
		if (count_1 && (!(count_1 % 1000)))
			fprintf(stderr, ".");
	}
	fprintf(stderr, "%s]\n", (count_1 % 1000) ? "." : "");

EXIT_FUNCTION:

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

#endif /* #ifdef TEST_MAIN */

