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

#include <memory.h>
#include <string.h>

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

int DCR_SearchRecord(cache_ptr, in_record_ptr, out_record_element,
	out_record_offset, error_text)
DCR_CACHE     *cache_ptr;
const void    *in_record_ptr;
unsigned int  *out_record_element;
unsigned long *out_record_offset;
char          *error_text;
{
	int            return_code;
	unsigned int   count_1;
	int            found_flag;
	unsigned int   tmp_record_element;
	unsigned long  tmp_record_offset;
	unsigned int  *record_element_ptr;
	unsigned long *record_offset_ptr;
	DTIME          current_update_date;
	DBC_FUNCS      dbc_funcs;
	char           dbc_error_text[DBC_MAX_ERROR_TEXT];
	char           tmp_error_text[DCR_MAX_ERROR_TEXT];

	DBC_AttachFacility(&dbc_funcs);
	if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
		(dbc_funcs.date_to_dtime == NULL)) {
		strcat(strcpy(error_text, "Unable to locate the DBC database "),
			"'date-to-DTIME conversion function.");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	record_offset_ptr  = (out_record_offset == NULL)  ? &tmp_record_offset  :
		out_record_offset;
	record_element_ptr = (out_record_element == NULL) ? &tmp_record_element :
		out_record_element;

	if ((return_code = DCR_AssertAccessType(cache_ptr,
		DCR_I_AM_WRITER, error_text)) == DCR_SUCCESS) {
		DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
			DCR_STAT_SEARCH);
		if ((cache_ptr->call_back_mask & DCR_CB_SEARCH) &&
			(cache_ptr->call_back_function != NULL))
			(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_SEARCH,
			DCR_FALSE, 0, 0, 1, in_record_ptr, NULL, return_code, error_text);
		found_flag = DCR_TRUE;
		for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
			if (!(cache_ptr->index_data_list[count_1].search_count =
				DCR_BasicGetCount(cache_ptr, count_1, NULL, NULL,
				DCR_COMPARE_TYPE_EQ, DCR_FIND_TOP,
				DCR_RECORD_FLAG_ALL, cache_ptr->record_count,
				cache_ptr->index_data_list[count_1].index_entry_list,
				in_record_ptr,
				&cache_ptr->index_data_list[count_1].search_index, NULL))) {
				found_flag = DCR_FALSE;
				break;
			}
		}
		if (found_flag == DCR_TRUE) {
			if (cache_ptr->index_count == 1)
				*record_offset_ptr = DCR_IELE_TO_ROFF(cache_ptr, 0,
					cache_ptr->index_data_list->search_index);
			else {
				for (count_1 = 0;
					count_1 < cache_ptr->index_data_list->search_count;
					count_1++) {
					*record_offset_ptr = DCR_IELE_TO_ROFF(cache_ptr, 0,
						cache_ptr->index_data_list->search_index + count_1);
					if ((found_flag = DCR_SearchForCongruence(cache_ptr, 1,
						*record_offset_ptr)) == DCR_TRUE)
						break;
            }
			}
		}
		if (found_flag == DCR_TRUE) {
			*record_element_ptr = ((unsigned int) (*record_offset_ptr -
				cache_ptr->data_area_offset)) / cache_ptr->total_record_size;
			DCR_LockRecord(cache_ptr, *record_offset_ptr, error_text);
			memcpy(((char *) cache_ptr->mmap_ptr) + *record_offset_ptr,
				in_record_ptr, cache_ptr->actual_data_record_size);
			DCR_UnLockRecord(cache_ptr, *record_offset_ptr, error_text);
			if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
				((*dbc_funcs.date_to_dtime)(cache_ptr->field_list[
				cache_ptr->update_date_field_index].db_type,
				((char *) in_record_ptr) + cache_ptr->update_date_field_offset,
				&current_update_date, dbc_error_text) == DBC_SUCCESS) &&
				(DTIME_Compare(&cache_ptr->max_update_date,
				&current_update_date) < 0))
				DCR_SetMaxUpdateDate(cache_ptr, *record_element_ptr,
					&current_update_date, tmp_error_text);
		}
		else
			return_code = DCR_InsertRecord(cache_ptr, in_record_ptr,
				record_element_ptr, out_record_offset, error_text);
		DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
			DCR_STAT_SEARCH, 1L);
		if ((cache_ptr->call_back_mask & DCR_CB_SEARCH) &&
			(cache_ptr->call_back_function != NULL))
			(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_SEARCH,
			DCR_TRUE, 0, 0, 1, in_record_ptr,
			((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
			DCR_STAT_SEARCH, return_code, error_text);
	}

EXIT_FUNCTION:

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

