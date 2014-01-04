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

	Revision History	:	1994-05-19 --- Creation.
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

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_IndexEntryLocate(cache_ptr, index_method, entry_count,
	entry_list, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
unsigned int   entry_count;
const void    *entry_list;
char          *error_text;
{
	int          return_code = DCR_FAILURE;
	unsigned int count_1;

	if (!cache_ptr->index_location_list[index_method].index_record_ptr)
		sprintf(error_text,
			"No previous 'get' call performed for index number %u.",
			index_method);
	else if (cache_ptr->index_location_list[index_method].index_element >
		entry_count)
		sprintf(error_text, "%s %u (%u) %s (%u).",
			"The saved 'get' data for index number", index_method,
			cache_ptr->index_location_list[index_method].index_element,
			"refers to an index entry element greater than the current maximum",
			entry_count);
	else if (cache_ptr->index_location_list[index_method].index_element <
		entry_count) {
		for (count_1 = cache_ptr->index_location_list[index_method].
			index_element; count_1 < entry_count; count_1++) {
			if (cache_ptr->index_location_list[index_method].index_record_ptr ==
				DCR_IELE_TO_ROFF_P(cache_ptr, index_method, entry_count,
				entry_list, count_1)) {
				cache_ptr->index_location_list[index_method].index_element =
					count_1;
				return_code                                                =
					DCR_SUCCESS;
				break;
			}
		}
		if (return_code != DCR_SUCCESS)
			sprintf(error_text, "%s %u %s %lu %s %u.",
				"Unable to determine the new location of the index entry element",
				cache_ptr->index_location_list[index_method].index_element,
				"which pointed to record at offset",
				cache_ptr->index_location_list[index_method].index_record_ptr,
				"in index number", index_method);
	}

	return(return_code);
}
/*	***********************************************************************	*/

