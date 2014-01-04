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

		Copyright Michael L. Brock 1994 - 2014.
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

void DCR_BindHeader(cache_ptr, cache_header_ptr)
DCR_CACHE                 *cache_ptr;
volatile DCR_HEADER *cache_header_ptr;
{
	unsigned int count_1;

	cache_ptr->mmap_ptr = (cache_ptr->mmap_ptr != NULL) ? cache_ptr->mmap_ptr :
		cache_header_ptr;

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Bind some varying scalars . . .										*/
	/*	**************************************************************	*/
	cache_ptr->record_count           = cache_header_ptr->record_count;
	cache_ptr->allocated_record_count =
		cache_header_ptr->allocated_record_count;
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
	/*	**************************************************************	*/
	if (cache_ptr->cache_access_type == DCR_I_AM_WRITER) {
		cache_ptr->record_mmap_size = cache_ptr->header_area_size +
			cache_ptr->data_area_size;
		cache_ptr->record_mmap_ptr  = ((void *) cache_ptr->mmap_ptr);
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Copy the index description area . . .								*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		cache_ptr->index_list[count_1] = ((DCR_INDEX *)
			(((char *) cache_header_ptr) +
			cache_header_ptr->area_list[DCR_AREA_INDEX].offset))[count_1];
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Bind dynamic index-related data . . .								*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		cache_ptr->index_data_list[count_1].index_entry_offset =
			cache_ptr->index_list[count_1].index_area_offset;
		cache_ptr->index_data_list[count_1].index_entry_size   =
			cache_ptr->index_list[count_1].index_area_size;
		cache_ptr->index_data_list[count_1].index_entry_list   =
			((char *) cache_ptr->mmap_ptr) +
			((unsigned int) cache_ptr->index_list[count_1].index_area_offset);
		if (cache_ptr->cache_access_type == DCR_I_AM_WRITER) {
			cache_ptr->index_data_list[count_1].mmap_size =
				cache_ptr->index_data_list[count_1].index_entry_size;
			cache_ptr->index_data_list[count_1].mmap_ptr  =
				cache_ptr->index_data_list[count_1].index_entry_list;
		}
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
}
/*	***********************************************************************	*/

