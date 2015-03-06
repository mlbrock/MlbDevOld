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

	Revision History	:	1994-08-15 --- Creation.
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

#include "dcr.h"

/*	***********************************************************************	*/

void DCR_BindInit(cache_ptr, cache_header_ptr)
DCR_CACHE                 *cache_ptr;
volatile DCR_HEADER *cache_header_ptr;
{
	unsigned int count_1;
	unsigned int area_count_offset[DCR_AREA_COUNT];
	unsigned int area_list_offset[DCR_AREA_COUNT];

	cache_ptr->mmap_ptr = (cache_ptr->mmap_ptr != NULL) ? cache_ptr->mmap_ptr :
		cache_header_ptr;

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Get the list of cache area descriptors . . .						*/
	/*	**************************************************************	*/
	DCR_GetAreaCountOffset(area_count_offset);
	DCR_GetAreaListOffset(area_list_offset);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Bind some varying scalars . . .										*/
	/*	**************************************************************	*/
	cache_ptr->record_count            = cache_header_ptr->record_count;
	cache_ptr->allocated_record_count  =
		cache_header_ptr->allocated_record_count;
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Bind some unvarying scalars . . .									*/
	/*	**************************************************************	*/
	cache_ptr->actual_data_record_size =
		cache_header_ptr->actual_data_record_size;
	cache_ptr->data_record_size        = cache_header_ptr->data_record_size;
	cache_ptr->total_record_size       = cache_header_ptr->total_record_size;
	cache_ptr->basic_header_area_size  =
		cache_header_ptr->basic_header_area_size;
	cache_ptr->header_area_size        = cache_header_ptr->header_area_size;
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Bind the data area location information . . .					*/
	/*	**************************************************************	*/
	cache_ptr->data_area_offset  = cache_header_ptr->data_area_offset;
	cache_ptr->data_area_size    = cache_header_ptr->data_area_size;
	cache_ptr->data_area_ptr     = ((char *) cache_ptr->mmap_ptr) +
		((unsigned int) cache_ptr->data_area_offset);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Bind the index area location information . . .					*/
	/*	**************************************************************	*/
	cache_ptr->index_area_offset = cache_header_ptr->index_area_offset;
	cache_ptr->index_area_size   = cache_header_ptr->index_area_size;
	cache_ptr->index_area_ptr    = ((char *) cache_ptr->mmap_ptr) +
		((unsigned int) cache_ptr->index_area_offset);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Bind the cache size information . . .								*/
	/*	**************************************************************	*/
	cache_ptr->total_cache_size      = cache_header_ptr->total_cache_size;
	cache_ptr->total_used_cache_size = cache_header_ptr->total_used_cache_size;
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Bind static area data . . .											*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < DCR_AREA_COUNT; count_1++) {
		*((unsigned int *) (((char *) cache_ptr) +
			area_count_offset[count_1]))                                 =
			DCR_GET_AREA_COUNT(cache_header_ptr, count_1);
		memcpy(*((void **) (((char *) cache_ptr) + area_list_offset[count_1])),
			((char *) cache_header_ptr) +
			((unsigned int) cache_header_ptr->area_list[count_1].offset),
			((unsigned int) cache_header_ptr->area_list[count_1].actual_size));
	}
	/*	**************************************************************	*/

	cache_ptr->index_data_count = cache_ptr->index_count;

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Copy the index description area . . .								*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		cache_ptr->index_list[count_1] = ((DCR_INDEX *)
			(((char *) cache_ptr->mmap_ptr) +
			cache_header_ptr->area_list[DCR_AREA_INDEX].offset))[count_1];
	}
	/*	**************************************************************	*/

#if 0
	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Copy the index description area . . .								*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		cache_ptr->index_list[count_1].index_area_offset = (!count_1) ?
			cache_ptr->index_area_offset :
			(cache_ptr->index_list[count_1 - 1].index_area_offset +
			cache_ptr->index_list[count_1 - 1].index_area_size);
		index_list[count_1].actual_index_area_size       =
			((unsigned long) cache_ptr->allocated_record_count) *
			((unsigned long) ((indirect_index_flag == DCR_TRUE) ?
			sizeof(unsigned long) : index_list[count_1].index_entry_size));
		index_list[count_1].index_area_size              =
			STRFUNCS_ADJUST_SIZE(index_list[count_1].actual_index_area_size,
			DCR_HEADER_PAGE_SIZE);
	}
	/*	**************************************************************	*/
#endif /* #if 0 */

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Bind static index-related data . . .								*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		cache_ptr->index_data_list[count_1].record_align_cmp_data.align_count =
			cache_ptr->index_list[count_1].record_align_count;
		cache_ptr->index_data_list[count_1].record_align_cmp_data.align_list  =
			cache_ptr->index_align_list +
			cache_ptr->index_list[count_1].record_align_index;
		cache_ptr->index_data_list[count_1].record_align_cmp_ptr              =
			&cache_ptr->index_data_list[count_1].record_align_cmp_data;
		cache_ptr->index_data_list[count_1].index_align_cmp_data.align_count  =
			cache_ptr->index_list[count_1].index_align_count;
		cache_ptr->index_data_list[count_1].index_align_cmp_data.align_list   =
			cache_ptr->index_align_list +
			cache_ptr->index_list[count_1].index_align_index;
		cache_ptr->index_data_list[count_1].index_align_cmp_ptr               =
			&cache_ptr->index_data_list[count_1].index_align_cmp_data;
		cache_ptr->index_data_list[count_1].index_entry_offset                =
			cache_ptr->index_list[count_1].index_area_offset;
		cache_ptr->index_data_list[count_1].index_entry_size                  =
			cache_ptr->index_list[count_1].index_area_size;
		cache_ptr->index_data_list[count_1].index_entry_list                  =
			((char *) cache_ptr->mmap_ptr) +
			((unsigned int) cache_ptr->index_list[count_1].index_area_offset);
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Copy the cache header data to the saved header area . . .	*/
	/*	**************************************************************	*/
	if (cache_header_ptr != cache_ptr->saved_header_ptr)
		memcpy(cache_ptr->saved_header_ptr,
			((DCR_HEADER *) cache_header_ptr),
			cache_ptr->header_area_size);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Bind the remaining header data . . .								*/
	/*	**************************************************************	*/
	DCR_BindHeader(cache_ptr, cache_header_ptr);
	/*	**************************************************************	*/
}
/*	***********************************************************************	*/

