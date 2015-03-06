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

	Revision History	:	1994-05-15 --- Creation.
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
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_InsertRecord(cache_ptr, in_record_ptr, out_record_element,
	out_record_offset, error_text)
DCR_CACHE     *cache_ptr;
const void    *in_record_ptr;
unsigned int  *out_record_element;
unsigned long *out_record_offset;
char          *error_text;
{
	int            return_code = DCR_SUCCESS;
	unsigned int   count_1;
	unsigned long  old_cache_status;
unsigned long  tmp_record_offset;
	unsigned long  record_offset;
	void          *record_ptr;
	unsigned int   index_element;
	unsigned long  index_offset;
	void          *index_entry_ptr;
	unsigned long  move_count;
	DTIME          current_update_date;
	DBC_FUNCS      dbc_funcs;
	char           tmp_error_text[DCR_MAX_ERROR_TEXT];
	char           dbc_error_text[DBC_MAX_ERROR_TEXT];

	DBC_AttachFacility(&dbc_funcs);
	if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
		(dbc_funcs.date_to_dtime == NULL)) {
		strcat(strcpy(error_text, "Unable to locate the DBC database "),
			"'date-to-DTIME conversion function.");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_RECORD_INSERT);
	if ((cache_ptr->call_back_mask & DCR_CB_REC_INSERT) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_REC_INSERT,
		DCR_FALSE, 0, 0, 1, in_record_ptr, NULL, return_code, error_text);

	if (((cache_ptr->header_ptr->record_count + 1) <=
		cache_ptr->header_ptr->allocated_record_count) ||
		((return_code = DCR_ResizeCache(cache_ptr,
		cache_ptr->record_count + 1, DCR_TRUE, error_text)) == DCR_SUCCESS)) {
		old_cache_status                                   =
			cache_ptr->header_ptr->cache_lock_status.lock_flag;
		cache_ptr->header_ptr->cache_lock_status.lock_flag =
			(cache_ptr->header_ptr->cache_lock_status.lock_flag &
			DCR_STATUS_CRITICAL) | DCR_STATUS_ADDING;
		cache_ptr->header_ptr->cache_status                =
			cache_ptr->header_ptr->cache_lock_status.lock_flag;
		/* NOTE: Need lock initialization call here: DCR_LOCK_InitLock() */
		record_offset = cache_ptr->record_count * cache_ptr->total_record_size;
		record_ptr    = ((char *) cache_ptr->mmap_ptr) +
			cache_ptr->data_area_offset + record_offset;
		memset(record_ptr, '\0', cache_ptr->total_record_size);
		memcpy(record_ptr, in_record_ptr, cache_ptr->actual_data_record_size);
		if (cache_ptr->critical_call_back_function != NULL)
			(*cache_ptr->critical_call_back_function)(cache_ptr,
				DCR_CB_REC_INSERT, DCR_FALSE, 0, 1, in_record_ptr,
				return_code, error_text);
		cache_ptr->header_ptr->cache_lock_status.lock_flag |=
			DCR_STATUS_CRITICAL;
		cache_ptr->header_ptr->cache_status                 =
			cache_ptr->header_ptr->cache_lock_status.lock_flag;
		for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
			if (DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE) {
				if (DCR_FindIndirect(cache_ptr, count_1, NULL, NULL,
					in_record_ptr, cache_ptr->record_count,
					cache_ptr->index_data_list[count_1].index_entry_list,
					DCR_FIND_BOTTOM, &index_element, &index_offset, NULL,
					NULL) == DCR_RECORD_FOUND) {
					index_element++;
					index_offset += DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1);
				}
				tmp_record_offset = record_offset +
					cache_ptr->data_area_offset;
				index_entry_ptr   = &tmp_record_offset;
			}
			else {
				tmp_record_offset = record_offset +
					cache_ptr->data_area_offset;
				if (DCR_FindEmbedded(cache_ptr, count_1, NULL, NULL,
					in_record_ptr, cache_ptr->record_count,
					cache_ptr->index_data_list[count_1].index_entry_list,
					DCR_FIND_BOTTOM, &index_element, &index_offset, NULL,
					NULL) == DCR_RECORD_FOUND) {
					index_element++;
					index_offset += DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1);
				}
				DCR_CopyEmbedded(cache_ptr, count_1, tmp_record_offset,
					in_record_ptr, cache_ptr->embedded_index_buffer);
				index_entry_ptr = cache_ptr->embedded_index_buffer;
			}
			if (index_element < cache_ptr->record_count) {
				move_count     = (cache_ptr->record_count - index_element) *
					DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1);
				bcopy(((char *) cache_ptr->mmap_ptr) +
					cache_ptr->index_list[count_1].index_area_offset +
					index_offset, ((char *) cache_ptr->mmap_ptr) +
					cache_ptr->index_list[count_1].index_area_offset +
					index_offset + DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1),
					move_count);
			}
			memcpy(((char *) cache_ptr->index_data_list[count_1].
				index_entry_list) + index_offset, index_entry_ptr,
				DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1));
			if (out_record_element != NULL)
				*out_record_element = cache_ptr->record_count;
			if (out_record_offset != NULL)
				*out_record_offset = record_offset +
					cache_ptr->data_area_offset;
		}
		cache_ptr->record_count                            =
			++cache_ptr->header_ptr->record_count;
		cache_ptr->header_ptr->cache_lock_status.lock_count++;
		cache_ptr->header_ptr->cache_lock_status.lock_flag = old_cache_status;
		cache_ptr->header_ptr->cache_status                = old_cache_status;
		if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
			((*dbc_funcs.date_to_dtime)(cache_ptr->field_list[
			cache_ptr->update_date_field_index].db_type,
			((char *) in_record_ptr) + cache_ptr->update_date_field_offset,
			&current_update_date, dbc_error_text) == DBC_SUCCESS) &&
			(DTIME_Compare(&cache_ptr->max_update_date,
			&current_update_date) < 0))
			DCR_SetMaxUpdateDate(cache_ptr, cache_ptr->record_count - 1,
				&current_update_date, tmp_error_text);
		if (cache_ptr->critical_call_back_function != NULL)
			(*cache_ptr->critical_call_back_function)(cache_ptr,
				DCR_CB_REC_INSERT, DCR_TRUE, 0, 1, in_record_ptr,
				return_code, error_text);
	}

	DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_RECORD_INSERT, 1L);
	if ((cache_ptr->call_back_mask & DCR_CB_REC_INSERT) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_REC_INSERT,
		DCR_TRUE, 0, 0, 1, in_record_ptr,
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_RECORD_INSERT, return_code, error_text);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

