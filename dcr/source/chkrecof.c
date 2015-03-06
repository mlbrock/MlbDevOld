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

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_CheckRecordElement(cache_ptr, record_element, error_text)
const DCR_CACHE *cache_ptr;
unsigned int     record_element;
char            *error_text;
{
	int return_code = DCR_SUCCESS;

	if (record_element >= cache_ptr->record_count) {
		sprintf(error_text, "%s (%u) %s (%u).",
			"The specified record element", record_element,
			"is equal to or greater than the cache record count",
			cache_ptr->record_count);
		return_code = DCR_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_CheckRecordOffset(cache_ptr, record_offset, error_text)
const DCR_CACHE *cache_ptr;
unsigned long   record_offset;
char           *error_text;
{
	int return_code = DCR_SUCCESS;

	if ((record_offset < cache_ptr->data_area_offset) ||
		(record_offset >=
		(cache_ptr->data_area_offset + cache_ptr->data_area_size))) {
		sprintf(error_text,
"%s (0X%08lX = %10lu) %s (from 0X%08lX = %10lu to 0X%08lX = %10lu, %s).",
			"The specified record offset", record_offset, record_offset,
			"is not within the cache data area",
			cache_ptr->data_area_offset, cache_ptr->data_area_offset,
			(cache_ptr->data_area_offset + cache_ptr->data_area_size) - 1L,
			(cache_ptr->data_area_offset + cache_ptr->data_area_size) - 1L,
			"inclusive");
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if ((record_offset - cache_ptr->data_area_offset) %
		cache_ptr->total_record_size) {
		sprintf(error_text, "%s (0X%08lX = %10lu) %s (%u) %s.",
			"The specified record offset", record_offset, record_offset,
			"is not located at an integral multiple of the total record size",
			cache_ptr->total_record_size, "within the cache data area");
		return_code = DCR_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

