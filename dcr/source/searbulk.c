/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a highly-optimized search/merge into a cache.

	Revision History	:	1995-02-17 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
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

int DCR_SearchBulk(cache_ptr, in_record_count, in_record_list,
	in_record_size, update_count, insert_count, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   in_record_count;
const void    *in_record_list;
unsigned int   in_record_size;
unsigned int  *update_count;
unsigned int  *insert_count;
char          *error_text;
{
	return(DCR_SearchBulkBasic(cache_ptr, DCR_INSERT_ALLOC_FULL,
		in_record_count, in_record_list, in_record_size, update_count,
		insert_count, error_text));
}
/*	***********************************************************************	*/

int DCR_SearchBulkBasic(cache_ptr, insert_method, in_record_count,
	in_record_list, in_record_size, update_count, insert_count, error_text)
DCR_CACHE     *cache_ptr;
int            insert_method;
unsigned int   in_record_count;
const void    *in_record_list;
unsigned int   in_record_size;
unsigned int  *update_count;
unsigned int  *insert_count;
char          *error_text;
{
	int              return_code = DCR_SUCCESS;
	unsigned int     ins_count   = 0;
	DCR_INS_2 *ins_list    = NULL;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     old_record_count;
	char            *record_ptr;
	int              found_flag;
	unsigned int     index_element;
	unsigned int     record_element;
	unsigned long    record_offset;
	unsigned int     tmp_update_count;
	unsigned int     tmp_insert_count;
	DTIME            current_update_date;
	DBC_FUNCS        dbc_funcs;
	char             dbc_error_text[DBC_MAX_ERROR_TEXT];

	update_count  = (update_count == NULL) ? &tmp_update_count : update_count;
	insert_count  = (insert_count == NULL) ? &tmp_insert_count : insert_count;

	*update_count = 0;
	*insert_count = 0;

	DBC_AttachFacility(&dbc_funcs);
	if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
		(dbc_funcs.date_to_dtime == NULL)) {
		strcat(strcpy(error_text, "Unable to locate the DBC database "),
			"'date-to-DTIME conversion function.");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Initialize the statistic values and perform call-backs . . .	*/
	/*	*****************************************************************	*/
	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_BULK_SEARCH);
	if ((cache_ptr->call_back_mask & DCR_CB_BULK_SEARCH) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_BULK_SEARCH,
		DCR_FALSE, 0, 0, in_record_count, ((void *) in_record_list), NULL,
		return_code, error_text);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Check some parameters . . .												*/
	/*	*****************************************************************	*/
	if (!in_record_size) {
		strcpy(error_text, "Bulk search record size is zero (0).");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (in_record_size < cache_ptr->header_ptr->actual_data_record_size) {
		sprintf(error_text, "%s (%u) %s (%u).",
			"The bulk search record size", in_record_size,
			"is less than the actual data record size for this cache",
			cache_ptr->header_ptr->actual_data_record_size);
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If no records on which to work then we're done . . .				*/
	/*	*****************************************************************	*/
	if (!in_record_count)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If there are not records already in the cache, this should be	*/
	/*	a 'bulk insert' instead.														*/
	/*	*****************************************************************	*/
	if (!cache_ptr->record_count) {
		return_code   = DCR_InsertBulk(cache_ptr, in_record_count,
			in_record_list, in_record_size, error_text);
		*insert_count = cache_ptr->record_count;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Attempt to allocate enough records to record the relative		*/
	/*	position of each record for which the search is to be performed	*/
	/*	using each each index method.													*/
	/*																							*/
	/*		If we can't allocate the memory, then just loop over each		*/
	/*	record and try to insert it . . .											*/
	/*	*****************************************************************	*/
	if ((ins_list = ((DCR_INS_2 *) calloc(in_record_count *
		cache_ptr->index_count, sizeof(DCR_INS_2)))) == NULL) {
		for (count_1 = 0; count_1 < in_record_count; count_1++,
			in_record_list = (((char *) in_record_list) + in_record_size)) {
			old_record_count = cache_ptr->record_count;
			if ((return_code = DCR_SearchRecord(cache_ptr, in_record_list,
				NULL, NULL, error_text)) != DCR_SUCCESS)
				break;
			if (old_record_count == cache_ptr->record_count)
				(*update_count)++;
			else
				(*insert_count)++;
		}
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Try to locate each record in the cache uniquely. If found,		*/
	/*	then update it place. Otherwise, store it's relative position.		*/
	/*	*****************************************************************	*/
	for (count_1 = 0, record_ptr = ((char *) in_record_list);
		count_1 < in_record_count; count_1++, record_ptr += in_record_size) {
		if ((return_code = DCR_FindRecordUnique(cache_ptr, record_ptr,
			&found_flag, &record_element, &record_offset, error_text)) !=
			DCR_SUCCESS)
			break;
		if (found_flag == DCR_TRUE) {
			DCR_LockRecord(cache_ptr, record_offset, error_text);
			memcpy(DCR_ROFF_TO_RPTR(cache_ptr, record_offset),
				record_ptr, cache_ptr->actual_data_record_size);
			DCR_UnLockRecord(cache_ptr, record_offset, error_text);
			if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
				((*dbc_funcs.date_to_dtime)(cache_ptr->field_list[
				cache_ptr->update_date_field_index].db_type,
				((char *) record_ptr) + cache_ptr->update_date_field_offset,
				&current_update_date, dbc_error_text) == DBC_SUCCESS) &&
				(DTIME_Compare(&cache_ptr->max_update_date,
				&current_update_date) < 0))
				DCR_SetMaxUpdateDate(cache_ptr, record_element,
					&current_update_date, error_text);
			(*update_count)++;
		}
		else {
			for (count_2 = 0; count_2 < cache_ptr->index_count; count_2++) {
				if (DCR_Find(cache_ptr, count_2, NULL, NULL, record_ptr,
					cache_ptr->record_count, DCR_INDEX_AREA_PTR(cache_ptr,
					count_2), DCR_FIND_BOTTOM, &index_element, NULL, NULL,
					NULL) == DCR_RECORD_FOUND)
					index_element++;
				ins_list[(count_2 * in_record_count) + ins_count].index_element =
					index_element;
				ins_list[(count_2 * in_record_count) + ins_count].record_offset =
					DCR_RELE_TO_ROFF(cache_ptr, cache_ptr->record_count +
					ins_count);
				ins_list[(count_2 * in_record_count) + ins_count].record_ptr    =
					record_ptr;
			}
			ins_count++;
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If all records were found to be in the cache, then we're done.	*/
	/*	*****************************************************************	*/
	if (!ins_count)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_InsListControl(cache_ptr, insert_method,
		in_record_count, in_record_list, in_record_size, DCR_FALSE, ins_count,
		ins_list, error_text)) == DCR_SUCCESS)
		*insert_count = ins_count;
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (ins_list != NULL)
		free(ins_list);

	cache_ptr->last_search_update_count = *update_count;
	cache_ptr->last_search_insert_count = *insert_count;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Update the final statistic values and perform any required		*/
	/*	call-backs . . .																	*/
	/*	*****************************************************************	*/
	DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_BULK_SEARCH, ((unsigned long) in_record_count));
	if ((cache_ptr->call_back_mask & DCR_CB_BULK_SEARCH) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_BULK_SEARCH,
		DCR_TRUE, 0, 0, in_record_count, ((void *) in_record_list),
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_BULK_SEARCH, return_code, error_text);
	/*	*****************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

