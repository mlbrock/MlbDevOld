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

int DCR_InsertBulk(cache_ptr, in_record_count, in_record_list, in_record_size,
	error_text)
DCR_CACHE    *cache_ptr;
unsigned int  in_record_count;
const void   *in_record_list;
unsigned int  in_record_size;
char         *error_text;
{
	int              return_code = DCR_SUCCESS;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned long    old_cache_status;
	unsigned long    record_offset;
	char            *in_record_ptr;
	char            *out_record_ptr;
	unsigned int     current_record;
	const DCR_FIELD *update_date_field_ptr;
	char            *update_date_ptr;
	unsigned int     max_update_date_record;
	DTIME            max_update_date;
	DTIME            current_update_date;
	DBC_FUNCS        dbc_funcs;
	char             dbc_error_text[DBC_MAX_ERROR_TEXT];

	DBC_AttachFacility(&dbc_funcs);
	if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
		(dbc_funcs.date_to_dtime == NULL)) {
		strcat(strcpy(error_text, "Unable to locate the DBC database "),
			"'date-to-DTIME conversion function.");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_BULK_INSERT);
	if ((cache_ptr->call_back_mask & DCR_CB_BULK_INSERT) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_BULK_INSERT,
		DCR_FALSE, 0, 0, in_record_count, in_record_list, NULL, return_code,
		error_text);

	if (!in_record_size) {
		strcpy(error_text, "Bulk insert record size is zero (0).");
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if (in_record_size < cache_ptr->header_ptr->actual_data_record_size) {
		sprintf(error_text, "%s (%u) %s (%u).",
			"The bulk insert record size", in_record_size,
			"is less than the actual data record size for this cache",
			cache_ptr->header_ptr->actual_data_record_size);
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if (in_record_count &&
		(((cache_ptr->header_ptr->record_count + in_record_count) <=
		cache_ptr->header_ptr->allocated_record_count) ||
		((return_code = DCR_ResizeCache(cache_ptr,
		cache_ptr->record_count + in_record_count, DCR_TRUE, error_text)) ==
		DCR_SUCCESS))) {
		old_cache_status                                   =
			cache_ptr->header_ptr->cache_lock_status.lock_flag;
		cache_ptr->header_ptr->cache_lock_status.lock_flag =
			(cache_ptr->header_ptr->cache_lock_status.lock_flag &
			DCR_STATUS_CRITICAL) | DCR_STATUS_ADDING;
		cache_ptr->header_ptr->cache_status                =
			cache_ptr->header_ptr->cache_lock_status.lock_flag;
		record_offset  = cache_ptr->data_area_offset +
			(cache_ptr->record_count * cache_ptr->total_record_size);
		in_record_ptr  = ((char *) in_record_list);
		out_record_ptr = ((char *) cache_ptr->mmap_ptr) + record_offset;
		current_record = cache_ptr->record_count;
		if (cache_ptr->max_update_date_known == DCR_TRUE) {
			update_date_field_ptr  = cache_ptr->field_list +
				cache_ptr->update_date_field_index;
			max_update_date        = cache_ptr->max_update_date;
			max_update_date_record = cache_ptr->max_update_date_record;
			update_date_ptr        = ((char *) in_record_ptr) +
				cache_ptr->update_date_field_offset;
		}
		memset(out_record_ptr, '\0',
			in_record_count * cache_ptr->total_record_size);
		for (count_1 = 0; count_1 < in_record_count; count_1++) {
			bcopy(in_record_ptr, out_record_ptr,
				cache_ptr->header_ptr->actual_data_record_size);
			for (count_2 = 0; count_2 < cache_ptr->index_count; count_2++) {
				if (DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE)
					memcpy(((char *) cache_ptr->index_data_list[count_2].
						index_entry_list) + (current_record * 
						DCR_INDEX_ENTRY_SIZE(cache_ptr, count_2)),
						&record_offset,
						DCR_INDEX_ENTRY_SIZE(cache_ptr, count_2));
				else
					DCR_CopyEmbedded(cache_ptr, count_2, record_offset,
						in_record_ptr,
						((char *) cache_ptr->index_data_list[count_2].
						index_entry_list) + (current_record *
						DCR_INDEX_ENTRY_SIZE(cache_ptr, count_2)));
			}
			if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
				((*dbc_funcs.date_to_dtime)(update_date_field_ptr->db_type,
				update_date_ptr, &current_update_date, dbc_error_text) ==
				DBC_SUCCESS) && (DTIME_Compare(&cache_ptr->max_update_date,
				&current_update_date) < 0)) {
				max_update_date        = current_update_date;
				max_update_date_record = current_record;
			}
			in_record_ptr   += in_record_size;
			out_record_ptr  += cache_ptr->total_record_size;
			record_offset   += cache_ptr->total_record_size;
			update_date_ptr += cache_ptr->total_record_size;
			current_record++;
		}
		if (cache_ptr->critical_call_back_function != NULL)
			(*cache_ptr->critical_call_back_function)(cache_ptr,
				DCR_CB_BULK_INSERT, DCR_FALSE, 0, 1, in_record_ptr,
				return_code, error_text);
		cache_ptr->header_ptr->cache_lock_status.lock_flag |=
			DCR_STATUS_CRITICAL;
		cache_ptr->header_ptr->cache_status                 =
			cache_ptr->header_ptr->cache_lock_status.lock_flag;
		for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++)
			DCR_Sort(cache_ptr, count_1, current_record,
				cache_ptr->index_data_list[count_1].index_entry_list);
		cache_ptr->header_ptr->record_count                = current_record;
		cache_ptr->record_count                            = current_record;
		cache_ptr->header_ptr->cache_lock_status.lock_count++;
		cache_ptr->header_ptr->cache_lock_status.lock_flag = old_cache_status;
		cache_ptr->header_ptr->cache_status                = old_cache_status;
		if (cache_ptr->max_update_date_known == DCR_TRUE) {
			cache_ptr->max_update_date_record = max_update_date_record;
			cache_ptr->max_update_date        = max_update_date;
		}
		if (cache_ptr->critical_call_back_function != NULL)
			(*cache_ptr->critical_call_back_function)(cache_ptr,
				DCR_CB_BULK_INSERT, DCR_TRUE, 0, 1, in_record_ptr,
				return_code, error_text);
	}

	DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_BULK_INSERT, ((unsigned long) in_record_count));
	if ((cache_ptr->call_back_mask & DCR_CB_BULK_INSERT) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_BULK_INSERT,
		DCR_TRUE, 0, 0, in_record_count, in_record_list,
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_BULK_INSERT, return_code, error_text);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

