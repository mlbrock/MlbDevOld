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

	Revision History	:	1994-05-07 --- Creation.
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

#include "dcr.h"

/*	***********************************************************************	*/

void DCR_IndexIndirect(cache_ptr, index_method, entry_list)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
void         *entry_list;
{
	unsigned int   count_1;
	unsigned long  old_cache_status;
	unsigned long *index_ptr;
	unsigned long  record_offset;

	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_INDEX);
	if ((cache_ptr->call_back_mask & DCR_CB_INDEX_CACHE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_INDEX_CACHE,
		DCR_FALSE, index_method, 0, cache_ptr->record_count, entry_list, NULL,
		DCR_SUCCESS, NULL);

	old_cache_status                                   =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	cache_ptr->header_ptr->cache_lock_status.lock_flag =
		DCR_STATUS_INDEXING | DCR_STATUS_CRITICAL;
	cache_ptr->header_ptr->cache_status                =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	index_ptr                                          = entry_list;
	record_offset                                      =
		cache_ptr->data_area_offset;

	for (count_1 = 0; count_1 < cache_ptr->record_count; count_1++,
		index_ptr++, record_offset += cache_ptr->total_record_size)
		*index_ptr = record_offset;

	DCR_SortIndirect(cache_ptr, index_method, cache_ptr->record_count,
		entry_list);

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

void DCR_SortIndirect(cache_ptr, index_method, entry_count, entry_list)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
unsigned int  entry_count;
void         *entry_list;
{
	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_SORT);
	if ((cache_ptr->call_back_mask & DCR_CB_SORT_CACHE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_SORT_CACHE,
		DCR_FALSE, index_method, 0, cache_ptr->record_count, entry_list, NULL,
		DCR_SUCCESS, NULL);

	cache_ptr->current_index_method                               =
		index_method;
	cache_ptr->index_data_list[index_method].record_align_cmp_ptr =
		&cache_ptr->index_data_list[index_method].record_align_cmp_data;
	cache_ptr->index_data_list[index_method].index_align_cmp_ptr  =
		&cache_ptr->index_data_list[index_method].index_align_cmp_data;

#ifndef NARGS
	STR_ARRAY_qsort(cache_ptr, entry_count, entry_list,
		DCR_INDEX_ENTRY_SIZE(cache_ptr, index_method),
		((int (*)(void *, const void *, const void *, size_t))
		DCR_CompareIndirect));
#else
	STR_ARRAY_qsort(cache_ptr, entry_count, entry_list,
		DCR_INDEX_ENTRY_SIZE(cache_ptr, index_method),
		DCR_CompareIndirect);
#endif /* #ifndef NARGS */

	DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_SORT, ((unsigned long) entry_count));
	if ((cache_ptr->call_back_mask & DCR_CB_SORT_CACHE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_SORT_CACHE,
		DCR_TRUE, index_method, 0, entry_count, entry_list,
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_SORT, DCR_SUCCESS, NULL);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

#include <memory.h>
#include <string.h>

#ifndef NARGS
int main(void);
#else
int main();
#endif /* #ifndef NARGS */

#include "datatest.h"						/* For the test meta-data . . .		*/

int main()
{
	int                return_code;
	unsigned int       count_1;
	unsigned int       count_2;
	DCR_HEADER  *cache_header_ptr = NULL;
	char              *data_list        = NULL;
	void             **index_list       = NULL;
	DCR_CACHE          cache_data;
	unsigned int       index_element;
	unsigned int       record_element;
	unsigned long      record_offset;
	char               error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'DCR_SortIndirect()'\n");
	fprintf(stderr, "---- ------- --- --------------------------\n\n");

	memset(&cache_data, '\0', sizeof(cache_data));

	if ((return_code = DCR_MakeHeader("TEST_CACHE_NAME",
		"TEST_SERVER,TEST_DB,TEST_OWNER,mlds,mlds", "TEST_SERVER",
		"TEST_DB", "TEST_OWNER", "mlds", "mlds", "TEST_TABLE", 4096, 4096,
		DCR_TRUE, MemberCount, MemberList, 0, NULL,
		IndexSpecCount, IndexSpecList, &cache_header_ptr, error_text)) !=
		DCR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = DCR_AllocCache(&cache_data, cache_header_ptr,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	cache_header_ptr->record_count = DataCount;
	DCR_BindHeader(&cache_data, cache_header_ptr);

	if ((data_list = ((char *) calloc(cache_data.record_count,
		cache_data.total_record_size))) == NULL) {
		sprintf(error_text, "%s (%u elements * %u size = %u total bytes).",
			"Unable to allocate the complete record lists",
			cache_data.record_count, cache_data.total_record_size,
			cache_data.record_count * cache_data.total_record_size);
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	cache_data.data_area_offset = 0L;
	cache_data.mmap_ptr         = data_list;
	cache_data.record_mmap_ptr  = data_list;

	for (count_1 = 0; count_1 < cache_data.record_count; count_1++)
		memcpy(data_list + (count_1 * cache_data.total_record_size),
			DataList + count_1, sizeof(DataList[0]));

	if ((index_list = ((void **) calloc(cache_data.index_count,
		sizeof(void **)))) == NULL) {
		sprintf(error_text, "%s (%u indices * %u size = %u total bytes).",
			"Unable to allocate the array of pointers to index lists",
			cache_data.index_count, sizeof(void *),
			cache_data.index_count * sizeof(void *));
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
		if ((index_list[count_1] = calloc(cache_data.record_count,
			DCR_INDEX_ENTRY_SIZE(&cache_data, count_1))) == NULL) {
			sprintf(error_text,
				"%s %u (%u records * %u size = %u total bytes).",
				"Unable to allocate index list number", count_1,
				cache_data.record_count,
				DCR_INDEX_ENTRY_SIZE(&cache_data, count_1),
				cache_data.record_count *
				DCR_INDEX_ENTRY_SIZE(&cache_data, count_1));
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Because we allocate memory for this test instead of using a	*/
	/*	memory-mapped file, we have to fix-up the index area offsets.	*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
		cache_data.index_list[count_1].index_area_offset       = 0L;
		cache_data.index_data_list[count_1].index_entry_offset = 0L;
		cache_data.index_data_list[count_1].index_entry_list   =
			index_list[count_1];
		cache_data.index_data_list[count_1].mmap_ptr           =
      	index_list[count_1];
	}
	/*	**************************************************************	*/

	DCR_IndexCache(&cache_data);

	printf("=======================================================\n");
	for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
		if (count_1)
			printf("-------------------------------------------------------\n");
		printf("Index Number %u (", count_1);
		for (count_2 = 0; count_2 < cache_data.index_list[count_1].field_count;
			count_2++)
			printf("%s%s", cache_data.field_list[cache_data.
				index_field_list[cache_data.index_list[count_1].field_index +
				count_2]].db_column_name,
				(count_2 < (cache_data.index_list[count_1].field_count - 1)) ?
				", " : ")\n");
		printf("-------------------------------------------------------\n");
#ifndef NARGS
		if ((return_code = DCR_EmitData(&cache_data, count_1, DCR_FALSE,
			DCR_TRUE, 0, 60, " ", "-", "\f", "", "\n", 0, NULL, NULL, NULL, NULL,
			((void (*)(void *, char *, ...)) fprintf), stdout, error_text)) !=
			DCR_SUCCESS)
#else
		if ((return_code = DCR_EmitData(&cache_data, count_1, DCR_FALSE,
			DCR_TRUE, 0, 60, " ", "-", "\f", "", "\n", 0, NULL, NULL, NULL, NULL,
			fprintf, stdout, error_text)) != DCR_SUCCESS)
#endif /* #ifndef NARGS */
			goto EXIT_FUNCTION;
	}
	printf("=======================================================\n");

	return_code = DCR_CheckIndices(&cache_data, error_text);

	for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
		for (count_2 = 0; count_2 < cache_data.record_count; count_2++) {
			if (DCR_Find(&cache_data, count_1, NULL, NULL,
				DataList + count_2, cache_data.record_count,
				cache_data.index_data_list[count_1].index_entry_list,
				DCR_FIND_TOP, &index_element, NULL, &record_element,
				&record_offset) != DCR_RECORD_FOUND) {
				sprintf(error_text, "%s %u %s %u (%s %u at offset %lu).",
					"Unable to locate data record number", count_2,
					"using cache index number", count_1, "nearest record is",
					record_element, record_offset);
				return_code = DCR_FAILURE;
				goto EXIT_FUNCTION;
			}
			printf("Index: %5u|Record %5u|Index:%6u|Record:%6u:%6lu\n",
				count_1, count_2, index_element, record_element, record_offset);
		}
	}

EXIT_FUNCTION:

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	if (data_list != NULL)
		free(data_list);

	if (index_list != NULL) {
		for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
			if (index_list[count_1] != NULL)
				free(index_list[count_1]);
		}
		free(index_list);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

