/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Locates a record unique in all of the cache indices.

	Revision History	:	1994-12-05 --- Creation.
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

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions local to this module . . .			*/
/*	***********************************************************************	*/

#ifndef NARGS
static int DCR_SearchForCongruence(DCR_CACHE *cache_ptr,
	unsigned int index_method, unsigned long record_offset_ptr);
#else
static int DCR_SearchForCongruence();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

int DCR_FindRecordUnique(cache_ptr, in_record_ptr, found_flag,
	out_record_element, out_record_offset, error_text)
DCR_CACHE     *cache_ptr;
const void    *in_record_ptr;
int           *found_flag;
unsigned int  *out_record_element;
unsigned long *out_record_offset;
char          *error_text;
{
	int            return_code = DCR_SUCCESS;
	unsigned int   count_1;
	unsigned long  tmp_record_offset;
	unsigned long *record_offset_ptr;

	*found_flag       = (cache_ptr->index_count) ? DCR_TRUE : DCR_FALSE;
	record_offset_ptr = (out_record_offset == NULL) ? &tmp_record_offset :
		out_record_offset;

	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		if ((return_code = DCR_GetCount(cache_ptr, count_1, NULL, NULL,
			DCR_COMPARE_TYPE_EQ, DCR_FIND_TOP,
			DCR_RECORD_FLAG_ALL, in_record_ptr,
			&cache_ptr->index_data_list[count_1].search_count,
			&cache_ptr->index_data_list[count_1].search_index, NULL,
			error_text)) != DCR_SUCCESS) {
			*found_flag = DCR_FALSE;
			break;
		}
		else if (!cache_ptr->index_data_list[count_1].search_count) {
			*found_flag = DCR_FALSE;
			break;
		}
	}

	if ((return_code == DCR_SUCCESS) && (*found_flag == DCR_TRUE)) {
		if (cache_ptr->index_count == 1)
			*record_offset_ptr = DCR_IELE_TO_ROFF(cache_ptr, 0,
				cache_ptr->index_data_list->search_index);
		else {
			for (count_1 = 0; count_1 < cache_ptr->index_data_list->search_count;
				count_1++) {
				*record_offset_ptr = DCR_IELE_TO_ROFF(cache_ptr, 0,
					cache_ptr->index_data_list->search_index + count_1);
				if ((*found_flag = DCR_SearchForCongruence(cache_ptr, 1,
					*record_offset_ptr)) == DCR_TRUE)
					break;
			}
		}
		if ((*found_flag == DCR_TRUE) && (out_record_element != NULL))
			*out_record_element = ((unsigned int) ((*record_offset_ptr -
				cache_ptr->data_area_offset) / cache_ptr->total_record_size));
	}

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_SearchForCongruence(cache_ptr, index_method,
	record_offset_ptr)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
unsigned long  record_offset_ptr;
{
	int                   found_flag = DCR_FALSE;
	unsigned int          count_1;
	unsigned int          search_index;
	DCR_INDEX_DATA *index_data_ptr;

	index_data_ptr = cache_ptr->index_data_list + index_method;

	for (count_1 = 0, search_index = index_data_ptr->search_index;
		count_1 < index_data_ptr->search_count; count_1++, search_index++) {
		if (record_offset_ptr == DCR_IELE_TO_ROFF(cache_ptr, index_method,
			search_index)) {
			found_flag = (index_method == (cache_ptr->index_count - 1)) ?
				DCR_TRUE : DCR_SearchForCongruence(cache_ptr,
				index_method + 1, record_offset_ptr);
			break;
		}
	}

	return(found_flag);
}
/*	***********************************************************************	*/

