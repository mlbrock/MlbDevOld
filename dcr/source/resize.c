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

#include <stdio.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_ResizeCache(cache_ptr, allocated_record_count, move_index_flag,
	error_text)
DCR_CACHE    *cache_ptr;
unsigned int  allocated_record_count;
int           move_index_flag;
char         *error_text;
{
	int            return_code = DCR_SUCCESS;
	unsigned int   count_1;
	unsigned long  old_cache_status;
	unsigned long  data_area_offset;
	unsigned long  data_area_size;
	unsigned long  index_area_offset;
	unsigned long  index_area_size;
	unsigned long  total_cache_size;
	unsigned long  move_count;
	unsigned long  move_index;
	char          *from_index_ptr;
	char          *to_index_ptr;
	DCR_INDEX *index_list;

	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_RESIZE);
	if ((cache_ptr->call_back_mask & DCR_CB_RESIZE_CACHE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_RESIZE_CACHE,
		DCR_FALSE, 0, 0, 0, NULL, NULL, return_code, error_text);

	old_cache_status                                   =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	cache_ptr->header_ptr->cache_lock_status.lock_flag =
		(cache_ptr->header_ptr->cache_lock_status.lock_flag &
		DCR_STATUS_CRITICAL) | DCR_STATUS_RESIZING;
	cache_ptr->header_ptr->cache_status                =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;

	if (allocated_record_count <=
		cache_ptr->header_ptr->allocated_record_count)
		goto EXIT_FUNCTION;
	else if ((allocated_record_count >
		cache_ptr->header_ptr->allocated_record_count) && ((return_code =
		DCR_CalculateSizes(cache_ptr->header_ptr->header_area_size,
		cache_ptr->header_ptr->allocation_size,
		cache_ptr->header_ptr->max_records_in_cache,
		cache_ptr->header_ptr->total_record_size,
		cache_ptr->header_ptr->indirect_index_flag,
		cache_ptr->index_count, ((DCR_INDEX *)
		(((char *) cache_ptr->mmap_ptr) +
		cache_ptr->header_ptr->area_list[DCR_AREA_INDEX].offset)),
		&allocated_record_count, &data_area_offset, &data_area_size,
		&index_area_offset, &index_area_size, &total_cache_size, error_text)) !=
		DCR_SUCCESS))
		goto EXIT_FUNCTION;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Perform a critical section call-back (if required).				*/
	/*	*****************************************************************	*/
	if (cache_ptr->critical_call_back_function != NULL)
		(*cache_ptr->critical_call_back_function)(cache_ptr,
			DCR_CB_RESIZE_CACHE, DCR_FALSE, 0, allocated_record_count,
			NULL, return_code, error_text);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Set the critical section flag.											*/
	/*	*****************************************************************	*/
	cache_ptr->header_ptr->cache_lock_status.lock_flag |=
		DCR_STATUS_CRITICAL;
	cache_ptr->header_ptr->cache_status                 =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	/*	*****************************************************************	*/

	if ((return_code = DCR_TruncateCache(cache_ptr, total_cache_size,
		error_text)) == DCR_SUCCESS) {
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Re-construct the cache header.									*/
		/*	***********************************************************	*/
		DCR_BindHeader(cache_ptr, cache_ptr->header_ptr);
		cache_ptr->header_ptr->allocated_record_count = allocated_record_count;
		cache_ptr->header_ptr->data_area_offset       = data_area_offset;
		cache_ptr->header_ptr->data_area_size         = data_area_size;
		cache_ptr->header_ptr->index_area_offset      = index_area_offset;
		cache_ptr->header_ptr->index_area_size        = index_area_size;
		cache_ptr->header_ptr->total_cache_size       = total_cache_size;
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		If indices are to be moved in re-sizing of the cache,		*/
		/*	we do so here.																*/
		/*																					*/
		/*		Because portions of the new index areas may overlap with	*/
		/* portions of the old index areas, we move the indices in		*/
		/*	reverse order (first index number one, then index number		*/
		/*	zero), and each index entry is moved started with the last	*/
		/* entry and proceeding backwards to the first.						*/
		/*	***********************************************************	*/
		if (move_index_flag == DCR_TRUE) {
			for (count_1 = cache_ptr->index_count; count_1; ) {
				cache_ptr->header_ptr->cache_lock_status.lock_count++;
				count_1--;
				move_count     = cache_ptr->record_count *
					DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1);
				from_index_ptr = (((char *) cache_ptr->mmap_ptr) + move_count +
					cache_ptr->index_list[count_1].index_area_offset) - 1;
				to_index_ptr   = (((char *) cache_ptr->mmap_ptr) + move_count +
					cache_ptr->index_list[count_1].tmp_index_area_offset) - 1;
				for (move_index = 0L; move_index < move_count; move_index++)
					*to_index_ptr-- = *from_index_ptr--;
				cache_ptr->header_ptr->cache_lock_status.lock_count++;
			}
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Update the individual index area descriptions for each	*/
		/*	index.																		*/
		/*	***********************************************************	*/
		index_list = ((DCR_INDEX *) (((char *) cache_ptr->mmap_ptr) +
			cache_ptr->header_ptr->area_list[DCR_AREA_INDEX].offset));
		for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
			index_list[count_1].index_area_offset      =
				index_list[count_1].tmp_index_area_offset;
			index_list[count_1].actual_index_area_size =
				index_list[count_1].tmp_actual_index_area_size;
			index_list[count_1].index_area_size        =
				index_list[count_1].tmp_index_area_size;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Do a final bind of the cache header data.						*/
		/*	***********************************************************	*/
		DCR_BindHeader(cache_ptr, cache_ptr->header_ptr);
		/*	***********************************************************	*/
	}

	cache_ptr->header_ptr->cache_lock_status.lock_count++;
	cache_ptr->header_ptr->cache_lock_status.lock_flag = old_cache_status;
	cache_ptr->header_ptr->cache_status                = old_cache_status;

	if (cache_ptr->critical_call_back_function != NULL)
		(*cache_ptr->critical_call_back_function)(cache_ptr,
			DCR_CB_RESIZE_CACHE, DCR_TRUE, 0, allocated_record_count,
			NULL, return_code, error_text);

EXIT_FUNCTION:

	cache_ptr->header_ptr->cache_lock_status.lock_flag = old_cache_status;
	cache_ptr->header_ptr->cache_status                = old_cache_status;

	DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_RESIZE, 1L);
	if ((cache_ptr->call_back_mask & DCR_CB_RESIZE_CACHE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_RESIZE_CACHE,
		DCR_TRUE, 0, 0, 0, NULL,
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_RESIZE, return_code, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

