/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Supporting logic to perform intelligent cache record
								insertions.

	Revision History	:	1995-02-26 --- Creation.
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

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static void DCR_SearchMerge(DCR_CACHE *cache_ptr,
	unsigned int index_method, unsigned int ins_count,
	const DCR_INS_2 *ins_list, char *merge_area_ptr);
static int  DCR_CMP_INS_1(DCR_CACHE *cache_ptr,
	const DCR_INS_1 *ins_ptr_1,
	const DCR_INS_1 *ins_ptr_2, size_t data_length);
static int  DCR_CMP_INS_2(DCR_CACHE *cache_ptr,
	const DCR_INS_2 *ins_ptr_1,
	const DCR_INS_2 *ins_ptr_2, size_t data_length);
#else
static void DCR_SearchMerge();
static int  DCR_CMP_INS_1();
static int  DCR_CMP_INS_2();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

int DCR_InsListControl(cache_ptr, insert_method, in_record_count,
	in_record_list, in_record_size, assign_ins_list_flag, ins_count, ins_list,
	error_text)
DCR_CACHE       *cache_ptr;
int              insert_method;
unsigned int     in_record_count;
const void      *in_record_list;
unsigned int     in_record_size;
int              assign_ins_list_flag;
unsigned int     ins_count;
DCR_INS_2 *ins_list;
char            *error_text;
{
	int            return_code = DCR_SUCCESS;
	unsigned int   count_1;
	unsigned int   count_2;
	char          *record_ptr;
	unsigned int   index_element;
	unsigned int   total_record_count;
	DTIME          current_update_date;
	DBC_FUNCS      dbc_funcs;
	char           dbc_error_text[DBC_MAX_ERROR_TEXT];

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
	/*		If not already done by the caller of this function, determine	*/
	/*	the relative position in each index for every record.					*/
	/*	*****************************************************************	*/
	if (assign_ins_list_flag == DCR_TRUE) {
		ins_count = 0;
		for (count_1 = 0, record_ptr = ((char *) in_record_list);
			count_1 < in_record_count; count_1++, record_ptr += in_record_size) {
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
	/*		If all goes well, this'll be the number of records in the		*/
	/*	when we're finished.																*/
	/*	*****************************************************************	*/
	total_record_count = cache_ptr->record_count + ins_count;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We may have to re-size the cache in order to accomodate the		*/
	/*	new records.																		*/
	/*	*****************************************************************	*/
	if ((total_record_count > cache_ptr->header_ptr->allocated_record_count) &&
		((return_code = DCR_ResizeCache(cache_ptr, total_record_count,
		DCR_TRUE, error_text)) != DCR_SUCCESS))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Copy the records to be inserted into the data area of the		*/
	/*	cache . . .																			*/
	/*	*****************************************************************	*/
	record_ptr = DCR_RELE_TO_RPTR(cache_ptr, cache_ptr->record_count);
	for (count_1 = 0; count_1 < ins_count; count_1++,
		record_ptr += cache_ptr->total_record_size) {
		memcpy(record_ptr, ins_list[count_1].record_ptr,
			cache_ptr->actual_data_record_size);
		if ((cache_ptr->max_update_date_known == DCR_TRUE) &&
			((*dbc_funcs.date_to_dtime)(cache_ptr->field_list[
			cache_ptr->update_date_field_index].db_type,
			((char *) record_ptr) + cache_ptr->update_date_field_offset,
			&current_update_date, dbc_error_text) == DBC_SUCCESS) &&
			(DTIME_Compare(&cache_ptr->max_update_date,
			&current_update_date) < 0))
			DCR_SetMaxUpdateDate(cache_ptr, cache_ptr->record_count + count_1,
				&current_update_date, error_text);
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Sort the list of records to be inserted . . .						*/
	/*	*****************************************************************	*/
	DCR_SortAll_INS_2(cache_ptr, in_record_count, ins_count, ins_list);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now we invoke the function which will update the index area of	*/
	/*	the cache with index entries for the inserted records. We try		*/
	/*	different methods of updating the index area, falling back to		*/
	/*	methods which use less memory if the function fails.					*/
	/*	*****************************************************************	*/
	insert_method = ((insert_method == DCR_INSERT_ALLOC_NONE) ||
		(insert_method == DCR_INSERT_ALLOC_PART) ||
		(insert_method == DCR_INSERT_ALLOC_FULL)) ? insert_method :
		DCR_INSERT_ALLOC_FULL;
	while (1) {
		if (insert_method == DCR_INSERT_ALLOC_NONE) {
			return_code = DCR_InsListAllocNone(cache_ptr, in_record_count,
				in_record_list, ins_count, ins_list, error_text);
			break;
		}
		else if (insert_method == DCR_INSERT_ALLOC_PART) {
			if (((return_code = DCR_InsListAllocPart(cache_ptr,
				in_record_count, in_record_list, ins_count, ins_list,
				error_text)) == DCR_SUCCESS) ||
				(return_code != DCR_MEMORY_FAILURE))
				break;
			insert_method = DCR_INSERT_ALLOC_NONE;
		}
		else if (insert_method == DCR_INSERT_ALLOC_FULL) {
			if (((return_code = DCR_InsListAllocFull(cache_ptr,
				in_record_count, in_record_list, ins_count, ins_list,
				error_text)) == DCR_SUCCESS) ||
				(return_code != DCR_MEMORY_FAILURE))
				break;
			insert_method = DCR_INSERT_ALLOC_PART;
		}
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_InsListAllocFull(cache_ptr, in_record_count, in_record_list,
	ins_count, ins_list, error_text)
DCR_CACHE             *cache_ptr;
unsigned int           in_record_count;
const void            *in_record_list;
unsigned int           ins_count;
const DCR_INS_2 *ins_list;
char                  *error_text;
{
	int            return_code    = DCR_SUCCESS;
	char          *merge_area_ptr = NULL;
	unsigned int   count_1;
	unsigned int   total_record_count;
	unsigned long  old_cache_status;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If no records on which to work then we're done . . .				*/
	/*	*****************************************************************	*/
	if (!in_record_count)
		goto EXIT_FUNCTION;
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
	/*		If all goes well, this'll be the number of records in the		*/
	/*	when we're finished.																*/
	/*	*****************************************************************	*/
	total_record_count = cache_ptr->record_count + ins_count;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Attempt to allocate enough space for the entire cache index		*/
	/*	area.																					*/
	/*																							*/
	/*		If we succeed, then we can merge the existing cache index		*/
	/*	entries and the index entries for the new records into this area,	*/
	/*	and then copy them back --- thus the time during which the cache	*/
	/*	is exclusively locked to readers is very short.							*/
	/*	*****************************************************************	*/
	if ((merge_area_ptr = ((char *)
		calloc(((unsigned int) cache_ptr->index_area_size), sizeof(char)))) ==
		NULL) {
		sprintf(error_text, "%s (%u %s * %u %s = %u total bytes).",
			"Unable to allocate memory for a full index merge area",
			total_record_count, "index entries",
			cache_ptr->index_count, "index methods",
			((unsigned int) cache_ptr->index_area_size));
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Merge the index entries for the records to be inserted.			*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++)
		DCR_SearchMerge(cache_ptr, count_1, ins_count,
			ins_list + (count_1 * in_record_count), merge_area_ptr +
			((unsigned int)
			(cache_ptr->index_list[count_1].index_area_offset -
			cache_ptr->index_area_offset)));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Set-up flags --- we're entering a critical section.				*/
	/*	*****************************************************************	*/
	old_cache_status                                   =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	cache_ptr->header_ptr->cache_lock_status.lock_flag =
		(cache_ptr->header_ptr->cache_lock_status.lock_flag &
		DCR_STATUS_CRITICAL) | DCR_STATUS_ADDING;
	cache_ptr->header_ptr->cache_status                =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	if (cache_ptr->critical_call_back_function != NULL)
		(*cache_ptr->critical_call_back_function)(cache_ptr,
			DCR_CB_BULK_SEARCH, DCR_FALSE, 0, in_record_count,
			in_record_list, return_code, error_text);
	cache_ptr->header_ptr->cache_lock_status.lock_flag |=
		DCR_STATUS_CRITICAL;
	cache_ptr->header_ptr->cache_status                 =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Copy the merged index entries and update the counts.				*/
	/*	*****************************************************************	*/
	memcpy(DCR_INDEX_AREA_PTR(cache_ptr, 0), merge_area_ptr,
		((unsigned int) cache_ptr->index_area_size));
	cache_ptr->header_ptr->record_count                += ins_count;
	cache_ptr->record_count                            += ins_count;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		End of the critical section.												*/
	/*	*****************************************************************	*/
	cache_ptr->header_ptr->cache_lock_status.lock_count++;
	cache_ptr->header_ptr->cache_lock_status.lock_flag  = old_cache_status;
	cache_ptr->header_ptr->cache_status                 = old_cache_status;
	if (cache_ptr->critical_call_back_function != NULL)
		(*cache_ptr->critical_call_back_function)(cache_ptr,
			DCR_CB_BULK_SEARCH, DCR_TRUE, 0, in_record_count,
			in_record_list, return_code, error_text);
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (merge_area_ptr != NULL)
		free(merge_area_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_InsListAllocPart(cache_ptr, in_record_count, in_record_list,
	ins_count, ins_list, error_text)
DCR_CACHE             *cache_ptr;
unsigned int           in_record_count;
const void            *in_record_list;
unsigned int           ins_count;
const DCR_INS_2 *ins_list;
char                  *error_text;
{
	int            return_code    = DCR_SUCCESS;
	char          *merge_area_ptr = NULL;
	unsigned int   count_1;
	unsigned int   total_record_count;
	unsigned long  old_cache_status;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If no records on which to work then we're done . . .				*/
	/*	*****************************************************************	*/
	if (!in_record_count)
		goto EXIT_FUNCTION;
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
	/*		If all goes well, this'll be the number of records in the		*/
	/*	when we're finished.																*/
	/*	*****************************************************************	*/
	total_record_count = cache_ptr->record_count + ins_count;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If we couldn't allocate memory for the entire index area, we	*/
	/*	try to allocate enough memory to store the index entries for the	*/
	/*	largest index entry size for all of the records.						*/
	/*																							*/
	/*		If we succeed, then we can merge the existing cache index		*/
	/*	entries and the index entries for the new records into this area	*/
	/*	one index method at a time.													*/
	/*	*****************************************************************	*/
	if ((merge_area_ptr = ((char *) calloc(total_record_count *
		cache_ptr->header_ptr->max_entry_length, sizeof(char)))) == NULL) {
		sprintf(error_text, "%s (%u %s * %u %s = %u total bytes).",
			"Unable to allocate memory for an index merge area",
			total_record_count, "index entries",
			cache_ptr->header_ptr->max_entry_length, "largest index entry size",
			total_record_count * cache_ptr->header_ptr->max_entry_length);
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Set-up flags --- we're entering a critical section.				*/
	/*	*****************************************************************	*/
	old_cache_status                                   =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	cache_ptr->header_ptr->cache_lock_status.lock_flag =
		(cache_ptr->header_ptr->cache_lock_status.lock_flag &
		DCR_STATUS_CRITICAL) | DCR_STATUS_ADDING;
	cache_ptr->header_ptr->cache_status                =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	if (cache_ptr->critical_call_back_function != NULL)
		(*cache_ptr->critical_call_back_function)(cache_ptr,
			DCR_CB_BULK_SEARCH, DCR_FALSE, 0, in_record_count,
			in_record_list, return_code, error_text);
	cache_ptr->header_ptr->cache_lock_status.lock_flag |=
		DCR_STATUS_CRITICAL;
	cache_ptr->header_ptr->cache_status                 =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Merge the index entries for the records to be inserted			*/
	/*	and copy those merged index entries.										*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		DCR_SearchMerge(cache_ptr, count_1, ins_count,
			ins_list + (count_1 * in_record_count), merge_area_ptr);
		cache_ptr->header_ptr->cache_lock_status.lock_count++;
		memcpy(DCR_INDEX_AREA_PTR(cache_ptr, count_1), merge_area_ptr,
			total_record_count *
			DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1));
		cache_ptr->header_ptr->cache_lock_status.lock_count++;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Update the counts.															*/
	/*	*****************************************************************	*/
	cache_ptr->header_ptr->record_count += ins_count;
	cache_ptr->record_count             += ins_count;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		End of the critical section.												*/
	/*	*****************************************************************	*/
	cache_ptr->header_ptr->cache_lock_status.lock_count++;
	cache_ptr->header_ptr->cache_lock_status.lock_flag  = old_cache_status;
	cache_ptr->header_ptr->cache_status                 = old_cache_status;
	if (cache_ptr->critical_call_back_function != NULL)
		(*cache_ptr->critical_call_back_function)(cache_ptr,
			DCR_CB_BULK_SEARCH, DCR_TRUE, 0, in_record_count,
			in_record_list, return_code, error_text);
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (merge_area_ptr != NULL)
		free(merge_area_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_InsListAllocNone(cache_ptr, in_record_count, in_record_list,
	ins_count, ins_list, error_text)
DCR_CACHE             *cache_ptr;
unsigned int           in_record_count;
const void            *in_record_list;
unsigned int           ins_count;
const DCR_INS_2 *ins_list;
char                  *error_text;
{
	int                    return_code = DCR_SUCCESS;
	const DCR_INS_2 *ins_ptr;
	unsigned int           count_1;
	unsigned int           count_2;
	unsigned int           index_element;
	unsigned int           index_offset;
	unsigned long          old_cache_status;
	unsigned int           copy_index;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If no records on which to work then we're done . . .				*/
	/*	*****************************************************************	*/
	if (!in_record_count)
		goto EXIT_FUNCTION;
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
	/*		Set-up flags --- we're entering a critical section.				*/
	/*	*****************************************************************	*/
	old_cache_status                                   =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	cache_ptr->header_ptr->cache_lock_status.lock_flag =
		(cache_ptr->header_ptr->cache_lock_status.lock_flag &
		DCR_STATUS_CRITICAL) | DCR_STATUS_ADDING;
	cache_ptr->header_ptr->cache_status                =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	if (cache_ptr->critical_call_back_function != NULL)
		(*cache_ptr->critical_call_back_function)(cache_ptr,
			DCR_CB_BULK_SEARCH, DCR_FALSE, 0, in_record_count,
			in_record_list, return_code, error_text);
	cache_ptr->header_ptr->cache_lock_status.lock_flag |=
		DCR_STATUS_CRITICAL;
	cache_ptr->header_ptr->cache_status                 =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		copy_index = cache_ptr->record_count - 1;
		for (count_2 = ins_count; count_2; ) {
			count_2--;
			ins_ptr       = ins_list + (count_1 * in_record_count) + count_2;
			index_element = ins_ptr->index_element + count_2;
			index_offset  = index_element *
				DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1);
			while ((copy_index < cache_ptr->record_count) &&
				(copy_index >= ins_ptr->index_element)) {
				bcopy(DCR_IELE_TO_IPTR(cache_ptr, count_1, copy_index),
					DCR_IELE_TO_IPTR(cache_ptr, count_1, copy_index +
					count_2 + 1), DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1));
				if (!copy_index--)
					break;
			}
			if (DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE)
				*((unsigned int *) (DCR_INDEX_AREA_PTR(cache_ptr, count_1) +
					index_offset)) = ins_ptr->record_offset;
			else
				DCR_CopyEmbedded(cache_ptr, count_1,
					ins_ptr->record_offset, ins_ptr->record_ptr,
					DCR_INDEX_AREA_PTR(cache_ptr, count_1) + index_offset);
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Update the counts.															*/
	/*	*****************************************************************	*/
	cache_ptr->header_ptr->record_count += ins_count;
	cache_ptr->record_count             += ins_count;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		End of the critical section.												*/
	/*	*****************************************************************	*/
	cache_ptr->header_ptr->cache_lock_status.lock_count++;
	cache_ptr->header_ptr->cache_lock_status.lock_flag  = old_cache_status;
	cache_ptr->header_ptr->cache_status                 = old_cache_status;
	if (cache_ptr->critical_call_back_function != NULL)
		(*cache_ptr->critical_call_back_function)(cache_ptr,
			DCR_CB_BULK_SEARCH, DCR_TRUE, 0, in_record_count,
			in_record_list, return_code, error_text);
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

void DCR_SortOne_INS_1(cache_ptr, index_method, ins_count, ins_list)
DCR_CACHE       *cache_ptr;
unsigned int     index_method;
unsigned int     ins_count;
DCR_INS_1 *ins_list;
{
	cache_ptr->current_index_method = index_method;

#ifndef NARGS
	STR_ARRAY_qsort(cache_ptr, ins_count, ins_list, sizeof(DCR_INS_1),
		((int (*)(void *, const void *, const void *, size_t))
		DCR_CMP_INS_1));
#else
	STR_ARRAY_qsort(cache_ptr, ins_count, ins_list, sizeof(DCR_INS_1),
		DCR_CMP_INS_1);
#endif /* #ifndef NARGS */
}
/*	***********************************************************************	*/

void DCR_SortAll_INS_2(cache_ptr, in_record_count, ins_count,
	ins_list)
DCR_CACHE       *cache_ptr;
unsigned int     in_record_count;
unsigned int     ins_count;
DCR_INS_2 *ins_list;
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++)
		DCR_SortOne_INS_2(cache_ptr, count_1, ins_count,
			ins_list + (count_1 * in_record_count));
}
/*	***********************************************************************	*/

void DCR_SortOne_INS_2(cache_ptr, index_method, ins_count, ins_list)
DCR_CACHE       *cache_ptr;
unsigned int     index_method;
unsigned int     ins_count;
DCR_INS_2 *ins_list;
{
	cache_ptr->current_index_method = index_method;

#ifndef NARGS
	STR_ARRAY_qsort(cache_ptr, ins_count, ins_list, sizeof(DCR_INS_2),
		((int (*)(void *, const void *, const void *, size_t))
		DCR_CMP_INS_2));
#else
	STR_ARRAY_qsort(cache_ptr, ins_count, ins_list, sizeof(DCR_INS_2),
		DCR_CMP_INS_2);
#endif /* #ifndef NARGS */
}
/*	***********************************************************************	*/

static void DCR_SearchMerge(cache_ptr, index_method, ins_count,
	ins_list, merge_area_ptr)
DCR_CACHE             *cache_ptr;
unsigned int           index_method;
unsigned int           ins_count;
const DCR_INS_2 *ins_list;
char                  *merge_area_ptr;
{
	unsigned int  count_1;
	unsigned int  entry_size;
	unsigned int  copy_count;
   unsigned int  copy_bytes;
	unsigned int  copy_idx;
	char         *copy_ptr;
	char         *merge_ptr;

	entry_size = DCR_INDEX_ENTRY_SIZE(cache_ptr, index_method);
	copy_ptr   = DCR_IELE_TO_IPTR(cache_ptr, index_method, 0);
	copy_idx   = 0;
	merge_ptr  = ((char *) merge_area_ptr);

	for (count_1 = 0; count_1 < ins_count; count_1++) {
		if ((copy_idx < cache_ptr->record_count) &&
			(copy_idx < ins_list[count_1].index_element)) {
			copy_count =
				((ins_list[count_1].index_element < cache_ptr->record_count) ?
				ins_list[count_1].index_element : cache_ptr->record_count) -
				copy_idx;
			memcpy(merge_ptr, copy_ptr, copy_bytes = copy_count * entry_size);
			copy_idx  += copy_count;
			copy_ptr  += copy_bytes;
			merge_ptr += copy_bytes;
		}
		if (DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE)
			*((unsigned int *) merge_ptr) = ins_list[count_1].record_offset;
		else
			DCR_CopyEmbedded(cache_ptr, index_method,
				ins_list[count_1].record_offset, ins_list[count_1].record_ptr,
				merge_ptr);
		merge_ptr += entry_size;
	}

	if (copy_idx < cache_ptr->record_count)
		memcpy(merge_ptr, copy_ptr,
			(cache_ptr->record_count - copy_idx) * entry_size);
}
/*	***********************************************************************	*/

static int DCR_CMP_INS_1(cache_ptr, ins_ptr_1, ins_ptr_2,
	data_length)
DCR_CACHE             *cache_ptr;
const DCR_INS_1 *ins_ptr_1;
const DCR_INS_1 *ins_ptr_2;
size_t                 data_length;
{
/*
	int cmp;

	if (!(cmp = GEN_ALIGN_CompareList(cache_ptr->index_data_list[cache_ptr->
		current_index_method].record_align_cmp_ptr, ins_ptr_1->record_ptr,
		ins_ptr_2->record_ptr, data_length)))
		cmp = ((ins_ptr_1->record_ptr > ins_ptr_2->record_ptr) ? 1 :
			(ins_ptr_1->record_ptr < ins_ptr_2->record_ptr) ? -1 : 0);

	return(cmp);
*/
	return(GEN_ALIGN_CompareList(cache_ptr->index_data_list[cache_ptr->
		current_index_method].record_align_cmp_ptr, ins_ptr_1->record_ptr,
		ins_ptr_2->record_ptr, data_length));
}
/*	***********************************************************************	*/

static int DCR_CMP_INS_2(cache_ptr, ins_ptr_1, ins_ptr_2,
	data_length)
DCR_CACHE             *cache_ptr;
const DCR_INS_2 *ins_ptr_1;
const DCR_INS_2 *ins_ptr_2;
size_t                 data_length;
{
	int cmp;

	if (!(cmp = ((ins_ptr_1->index_element > ins_ptr_2->index_element) ? 1 :
		(ins_ptr_1->index_element < ins_ptr_2->index_element) ? -1 : 0))) {
		if (!(cmp = GEN_ALIGN_CompareList(cache_ptr->index_data_list[cache_ptr->
			current_index_method].record_align_cmp_ptr, ins_ptr_1->record_ptr,
			ins_ptr_2->record_ptr, data_length)))
			cmp = ((ins_ptr_1->record_ptr > ins_ptr_2->record_ptr) ? 1 :
				(ins_ptr_1->record_ptr < ins_ptr_2->record_ptr) ? -1 : 0);
	}

	return(cmp);

}
/*	***********************************************************************	*/

