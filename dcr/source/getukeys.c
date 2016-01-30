/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns a list of the records in a cache which are
								unique relative to the specified index key.

	Revision History	:	1994-12-06 --- Creation.
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

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_GetUniqueKeys(cache_ptr, index_method, record_cmp_ptr,
	index_cmp_ptr, alloc_granularity, unique_key_count, unique_key_list,
	error_text)
DCR_CACHE            *cache_ptr;
unsigned int          index_method;
GEN_ALIGN_CMP        *record_cmp_ptr;
GEN_ALIGN_CMP        *index_cmp_ptr;
unsigned int          alloc_granularity;
unsigned int         *unique_key_count;
DCR_KEY_COUNT **unique_key_list;
char                 *error_text;
{
	int                  return_code;
	unsigned int         count_1;
	unsigned int         alloc_size;
	unsigned int         align_cmp_size;
	GEN_ALIGN_CMP       *align_cmp_ptr;
	void                *old_record_ptr;
	void                *new_record_ptr;
	DCR_KEY_COUNT *unique_key_ptr;
	DCR_KEY_COUNT *tmp_ptr;

	*unique_key_count = 0;
	*unique_key_list  = NULL;

	alloc_granularity = (!alloc_granularity) ? 1000 : alloc_granularity;

	if (((return_code = DCR_MapDataAndIndex(cache_ptr, NULL, NULL,
		index_method, NULL, NULL, error_text)) == DCR_SUCCESS) &&
		cache_ptr->record_count) {
		alloc_size     = alloc_granularity;
		record_cmp_ptr = (record_cmp_ptr != NULL) ? record_cmp_ptr :
			&cache_ptr->index_data_list[index_method].record_align_cmp_data;
		index_cmp_ptr  = (index_cmp_ptr  != NULL) ? index_cmp_ptr  :
			&cache_ptr->index_data_list[index_method].index_align_cmp_data;
		align_cmp_size =
			(cache_ptr->header_ptr->indirect_index_flag == DCR_TRUE) ?
			cache_ptr->total_record_size :
			cache_ptr->index_list[index_method].index_entry_size;
		align_cmp_ptr  =
			(cache_ptr->header_ptr->indirect_index_flag == DCR_TRUE) ?
			record_cmp_ptr : index_cmp_ptr;
		old_record_ptr =
			(cache_ptr->header_ptr->indirect_index_flag == DCR_TRUE) ?
			DCR_IELE_TO_RPTR(cache_ptr, index_method, 0) :
			DCR_IELE_TO_IPTR(cache_ptr, index_method, 0);
		if ((*unique_key_list = ((DCR_KEY_COUNT *)
			malloc(alloc_size * sizeof(DCR_KEY_COUNT)))) == NULL)
			return_code = DCR_MEMORY_FAILURE;
		else {
			(*unique_key_list)[*unique_key_count].key_index = 0;
			(*unique_key_list)[*unique_key_count].key_count = 1;
			*unique_key_count                               = 1;
			unique_key_ptr                                  = *unique_key_list;
			for (count_1 = 1; count_1 < cache_ptr->record_count; count_1++) {
				new_record_ptr =
					(cache_ptr->header_ptr->indirect_index_flag == DCR_TRUE) ?
					DCR_IELE_TO_RPTR(cache_ptr, index_method, count_1) :
					DCR_IELE_TO_IPTR(cache_ptr, index_method, count_1);
				if (!GEN_ALIGN_CompareList(align_cmp_ptr, old_record_ptr,
					new_record_ptr, align_cmp_size))
					unique_key_ptr->key_count++;
				else {
					if (*unique_key_count == alloc_size) {
						alloc_size += alloc_granularity;
						if ((tmp_ptr = ((DCR_KEY_COUNT *)
							realloc(*unique_key_list, alloc_size *
							sizeof(DCR_KEY_COUNT)))) == NULL) {
							return_code = DCR_MEMORY_FAILURE;
							break;
						}
						*unique_key_list = tmp_ptr;
					}
					unique_key_ptr            =
						*unique_key_list + (*unique_key_count)++;
					unique_key_ptr->key_index = count_1;
					unique_key_ptr->key_count = 1;
					old_record_ptr            = new_record_ptr;
				}
			}
		}
		if (return_code != DCR_SUCCESS) {
			sprintf(error_text,
				"%s %s%s (%u elements * %u size = %u total bytes).",
				"Unable to", (!(*unique_key_count)) ? "" : "re-",
				"allocate the unique key list", alloc_size,
				sizeof(DCR_KEY_COUNT),
				alloc_size * sizeof(DCR_KEY_COUNT));
			if (*unique_key_list != NULL) {
				free(*unique_key_list);
				*unique_key_count = 0;
				*unique_key_list  = NULL;
			}
		}
		else if (*unique_key_count && (*unique_key_count < alloc_size))
			*unique_key_list = ((DCR_KEY_COUNT *) realloc(*unique_key_list,
				*unique_key_count * sizeof(DCR_KEY_COUNT)));
	}

	return(return_code);
}
/*	***********************************************************************	*/

