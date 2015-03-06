/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Re-maps a cache.

	Revision History	:	1994-10-03 --- Creation.
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
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_ReMapCache(cache_ptr, error_text)
DCR_CACHE *cache_ptr;
char      *error_text;
{
	int                   return_code   = DCR_SUCCESS;
	unsigned int          data_map_size = 0;
	void                 *data_map_ptr  = NULL;
	unsigned int          count_1;
	unsigned int          count_2;
	unsigned int          tmp_record_count;
	DCR_INDEX      *index_ptr;
	DCR_INDEX_DATA *index_data_list;
	DCR_HEADER     *saved_header_ptr;
	DCR_LOCK              saved_lock_status;

	if (cache_ptr->cache_access_type == DCR_I_AM_WRITER)
		DCR_BindHeader(cache_ptr, cache_ptr->header_ptr);
	else if ((index_data_list = memdup(cache_ptr->index_data_list,
		cache_ptr->index_data_count * sizeof(cache_ptr->index_data_list[0]))) ==
		NULL) {
		sprintf(error_text, "%s (%u elements * %u size = %u total bytes).",
			"Unable to allocate memory for the temporary index data items",
			cache_ptr->index_data_count, sizeof(cache_ptr->index_data_list[0]),
			cache_ptr->index_data_count * sizeof(cache_ptr->index_data_list[0]));
		return_code = DCR_MEMORY_FAILURE;
	}
	else {
		saved_header_ptr = cache_ptr->tmp_saved_header_ptr;
		for (count_1 = 0; count_1 < cache_ptr->index_data_count; count_1++) {
			cache_ptr->index_data_list[count_1].mmap_size = 0;
			cache_ptr->index_data_list[count_1].mmap_ptr  = NULL;
		}
		for (count_1 = 0; count_1 < cache_ptr->cycle_retry_count; ) {
			do {
				saved_lock_status = cache_ptr->header_ptr->cache_lock_status;
				memcpy(saved_header_ptr,
					((DCR_HEADER *) cache_ptr->header_ptr),
					cache_ptr->header_area_size);
			} while ((saved_lock_status.lock_count !=
				cache_ptr->header_ptr->cache_lock_status.lock_count) ||
				(saved_lock_status.lock_flag !=
				cache_ptr->header_ptr->cache_lock_status.lock_flag));
			if (!(saved_lock_status.lock_flag & DCR_STATUS_CRITICAL)) {
				return_code   = DCR_SUCCESS;
				data_map_size = saved_header_ptr->header_area_size +
					saved_header_ptr->data_area_size;
/*
	CODE NOTE: To be removed.
re_map_size   = saved_header_ptr->total_cache_size;
*/
				if ((cache_ptr->record_mmap_ptr != NULL) &&
					(((int) (data_map_ptr = ((void *) mmap(NULL,
					((int) data_map_size), PROT_READ, MAP_SHARED,
					cache_ptr->file_handle, 0)))) == -1)) {
					sprintf(error_text, "%s to %u %s 0 failed: ",
						"Attempt to 'mmap()' the cache data area",
						data_map_size, "bytes starting at offset");
					DCR_GEN_AppendLastErrorString(error_text);
					data_map_ptr = NULL;
					return_code  = DCR_SYSTEM_FAILURE;
				}
/*
	CODE NOTE: To be replaced with logic which re-maps indices intelligently.
*/
if (0) {
				if (return_code == DCR_SUCCESS) {
					for (count_2 = 0; count_2 < cache_ptr->index_data_count;
						count_2++) {
						index_ptr                                   =
							((DCR_INDEX *) (((char *) saved_header_ptr) +
							saved_header_ptr->area_list[DCR_AREA_INDEX].
							offset)) + count_2;
						index_data_list[count_2].index_entry_offset =
							index_ptr->index_area_offset;
						index_data_list[count_2].index_entry_size   =
							index_ptr->index_area_size;
						index_data_list[count_2].mmap_size          =
							index_ptr->index_area_size;
						if ((cache_ptr->index_data_list[count_2].mmap_ptr !=
							NULL) && (((int) (index_data_list[count_2].mmap_ptr =
							((void *) mmap(NULL, ((int) index_ptr->index_area_size),
							PROT_READ, MAP_PRIVATE, cache_ptr->file_handle,
							((int) index_ptr->index_area_offset))))) == -1)) {
							sprintf(error_text,
								"%s %u named '%s' to %lu %s %lu (0X%08lX) failed: ",
								"Attempt to 'mmap()' the cache index number",
								count_2, index_ptr->index_name,
								index_ptr->index_area_size,
								"bytes starting at offset",
								index_ptr->index_area_offset,
								index_ptr->index_area_offset);
							DCR_GEN_AppendLastErrorString(error_text);
							index_data_list[count_2].mmap_ptr = NULL;
							return_code                       = DCR_SYSTEM_FAILURE;
							break;
						}
					}
				}
}
				tmp_record_count = cache_ptr->header_ptr->record_count;
				if ((return_code == DCR_SUCCESS) &&
					(!(cache_ptr->header_ptr->cache_lock_status.lock_flag &
					DCR_STATUS_CRITICAL)) &&
					(saved_header_ptr->total_cache_size ==
					cache_ptr->header_ptr->total_cache_size)) {
					saved_header_ptr->record_count = tmp_record_count;
					DCR_UnMapData(cache_ptr);
					DCR_UnMapAllIndices(cache_ptr);
					DCR_BindHeader(cache_ptr, saved_header_ptr);
					cache_ptr->record_mmap_size = data_map_size;
					cache_ptr->record_mmap_ptr  = data_map_ptr;
					for (count_2 = 0; count_2 < cache_ptr->index_data_count;
						count_2++) {
						cache_ptr->index_data_list[count_2].mmap_size =
							index_data_list[count_2].mmap_size;
						cache_ptr->index_data_list[count_2].mmap_ptr  =
							index_data_list[count_2].mmap_ptr;
					}
					break;
				}
				if (data_map_ptr != NULL)
					munmap(data_map_ptr, ((int) data_map_size));
				data_map_size = 0;
				data_map_ptr  = NULL;
				for (count_2 = 0; count_2 < cache_ptr->index_data_count;
					count_2++) {
					if (index_data_list[count_2].mmap_size &&
						(index_data_list[count_2].mmap_ptr != NULL))
						munmap(index_data_list[count_2].mmap_ptr,
							((int) index_data_list[count_2].mmap_size));
					index_data_list[count_2].mmap_size = 0;
					index_data_list[count_2].mmap_ptr  = NULL;
				}
				if (return_code != DCR_SUCCESS)
					break;
			}
			if ((saved_lock_status.lock_count !=
				cache_ptr->header_ptr->cache_lock_status.lock_count) ||
				(saved_lock_status.lock_flag !=
				cache_ptr->header_ptr->cache_lock_status.lock_flag)) {
				count_1 = 0;
				continue;
			}
			else if (++count_1 == cache_ptr->cycle_retry_count) {
				sprintf(error_text,
					"Unable to acquire reader lock on cache '%s' for re-map.",
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
		free(index_data_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

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
	DCR_CONTROL   cache_control_data;
	DCR_CACHE          *cache_ptr;
	unsigned int        cache_index;
	char                error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for function 'DCR_ReMapCache()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------------------\n\n");

	memset(&cache_control_data, '\0', sizeof(cache_control_data));

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "Help request with '%s' noted . . .\n\n",
				argv[count_1]);
			fprintf(stderr, "USAGE:\n   %s %s\n\n", argv[0],
				"<input-cache-file-name> [<re-map-attempt-count>]");
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

	fprintf(stderr, "Will attempt to re-map the cache %u times.\n\n",
		test_count);

	fprintf(stderr, "Progress Report: [");
	for (count_1 = 0; count_1 < test_count; count_1++) {
		if ((return_code = DCR_ReMapCache(cache_ptr, error_text)) !=
			DCR_SUCCESS)
			break;
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

