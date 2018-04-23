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

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <memory.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DCR_CheckEmbedded(cache_ptr, index_method, entry_count, entry_list,
	error_text)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
unsigned int  entry_count;
const void   *entry_list;
char         *error_text;
{
	int             return_code      = DCR_SUCCESS;
	void           *this_index_entry = NULL;
	void           *last_index_entry = NULL;
	unsigned int    count_1;
   unsigned long   record_offset;
	DCR_STAT  tmp_stat;
	char            tmp_error_text[DCR_MAX_ERROR_TEXT];

	if ((cache_ptr->call_back_mask & DCR_CB_CHECK_INDEX_1) &&
		(cache_ptr->call_back_function != NULL)) {
		memset(&tmp_stat, '\0', sizeof(tmp_stat));
		DCR_StatStartTime(&tmp_stat);
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_CHECK_INDEX_1,
			DCR_FALSE, index_method, 0, entry_count, ((void *) entry_list), NULL,
			DCR_SUCCESS, NULL);
	}

	cache_ptr->current_index_method                               =
		index_method;
	cache_ptr->index_data_list[index_method].record_align_cmp_ptr =
		&cache_ptr->index_data_list[index_method].record_align_cmp_data;
	cache_ptr->index_data_list[index_method].index_align_cmp_ptr  =
		&cache_ptr->index_data_list[index_method].index_align_cmp_data;

	for (count_1 = 0; count_1 < entry_count; count_1++) {
		if ((return_code = DCR_CheckRecordOffset(cache_ptr,
			record_offset = DCR_IELE_TO_ROFF_P(cache_ptr, index_method,
			entry_count, entry_list, count_1), tmp_error_text)) != DCR_SUCCESS)
			break;
		DCR_CopyEmbedded(cache_ptr, index_method, record_offset,
			DCR_ROFF_TO_RPTR(cache_ptr, record_offset),
			cache_ptr->embedded_index_buffer);
		if (GEN_ALIGN_CompareList(&cache_ptr->index_data_list[index_method].
			index_align_cmp_data, cache_ptr->embedded_index_buffer,
			this_index_entry = DCR_IELE_TO_IPTR_P(cache_ptr, index_method,
			entry_count, entry_list, count_1),
			cache_ptr->index_list[index_method].index_entry_size)) {
			strcat(strcpy(tmp_error_text,
				"The embedded index field value calculated for this entry is "),
				"different from that contained in the data record.");
			return_code = DCR_FAILURE;
			break;
		}
		if (count_1 &&
			(GEN_ALIGN_CompareList(&cache_ptr->index_data_list[index_method].
			index_align_cmp_data, this_index_entry, last_index_entry,
			cache_ptr->index_list[index_method].index_entry_size) < 0)) {
			sprintf(tmp_error_text, "%s (%s %lu, %s %u) %s (%s %lu %s %u).",
				"The embedded index value calculated for this index entry",
				"at record element",
				DCR_IELE_TO_RELE_P(cache_ptr, index_method, entry_count,
				entry_list, count_1),
				"record offset",
				DCR_IELE_TO_ROFF_P(cache_ptr, index_method, entry_count,
				entry_list, count_1),
				"is less than the previous index entry embedded index value",
				"at record element",
				DCR_IELE_TO_RELE_P(cache_ptr, index_method, entry_count,
				entry_list, count_1 - 1),
				"record offset",
				DCR_IELE_TO_ROFF_P(cache_ptr, index_method, entry_count,
				entry_list, count_1 - 1));
			return_code = DCR_FAILURE;
			break;
		}
		last_index_entry = this_index_entry;
	}

	if (return_code != DCR_SUCCESS) {
		sprintf(error_text, "Error in index number %u, index entry number %u: ",
			index_method, count_1);
		nstrcat(error_text, tmp_error_text,
			DCR_MAX_ERROR_TEXT - (strlen(error_text) + 1));
	}

	if ((cache_ptr->call_back_mask & DCR_CB_CHECK_INDEX_1) &&
		(cache_ptr->call_back_function != NULL)) {
		DCR_StatEndTime(&tmp_stat, ((unsigned long) entry_count));
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_CHECK_INDEX_1,
			DCR_TRUE, index_method, 0, entry_count, ((void *) entry_list),
			&tmp_stat, return_code, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DCR_CheckEmbeddedElements(cache_ptr, index_method, entry_count,
	entry_list, element_list, error_text)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
unsigned int  entry_count;
const void   *entry_list;
unsigned int *element_list;
char         *error_text;
{
	int             return_code      = DCR_SUCCESS;
	void           *this_index_entry = NULL;
	void           *last_index_entry = NULL;
	unsigned int    count_1;
	unsigned int    record_element;
   unsigned long   record_offset;
	DCR_STAT  tmp_stat;
	char            tmp_error_text[DCR_MAX_ERROR_TEXT];

	if ((cache_ptr->call_back_mask & DCR_CB_CHECK_INDEX_2) &&
		(cache_ptr->call_back_function != NULL)) {
		memset(&tmp_stat, '\0', sizeof(tmp_stat));
		DCR_StatStartTime(&tmp_stat);
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_CHECK_INDEX_2,
			DCR_FALSE, index_method, 0, entry_count, ((void *) entry_list), NULL,
			DCR_SUCCESS, NULL);
	}

	cache_ptr->current_index_method                               =
		index_method;
	cache_ptr->index_data_list[index_method].record_align_cmp_ptr =
		&cache_ptr->index_data_list[index_method].record_align_cmp_data;
	cache_ptr->index_data_list[index_method].index_align_cmp_ptr  =
		&cache_ptr->index_data_list[index_method].index_align_cmp_data;

	for (count_1 = 0; count_1 < entry_count; count_1++)
		element_list[count_1] = UINT_MAX;

	for (count_1 = 0; count_1 < entry_count; count_1++) {
		if ((return_code = DCR_CheckRecordOffset(cache_ptr,
			record_offset = DCR_IELE_TO_ROFF_P(cache_ptr, index_method,
			entry_count, entry_list, count_1), tmp_error_text)) != DCR_SUCCESS)
			break;
		record_element = DCR_ROFF_TO_RELE(cache_ptr, record_offset);
		if (element_list[record_element] != UINT_MAX) {
			sprintf(tmp_error_text, "%s %u %s %lu %s %u.",
				"Record at record element", record_element, "at record offset",
				record_offset, "is also referenced by index element",
				element_list[record_element]);
			return_code = DCR_FAILURE;
			break;
		}
		element_list[record_element] = count_1;
		DCR_CopyEmbedded(cache_ptr, index_method, record_offset,
			DCR_ROFF_TO_RPTR(cache_ptr, record_offset),
			cache_ptr->embedded_index_buffer);
		if (GEN_ALIGN_CompareList(&cache_ptr->index_data_list[index_method].
			index_align_cmp_data, cache_ptr->embedded_index_buffer,
			this_index_entry = DCR_IELE_TO_IPTR_P(cache_ptr, index_method,
			entry_count, entry_list, count_1),
			cache_ptr->index_list[index_method].index_entry_size)) {
			strcat(strcpy(tmp_error_text,
				"The embedded index field value calculated for this entry is "),
				"different from that contained in the data record.");
			return_code = DCR_FAILURE;
			break;
		}
		if (count_1 &&
			(GEN_ALIGN_CompareList(&cache_ptr->index_data_list[index_method].
			index_align_cmp_data, this_index_entry, last_index_entry,
			cache_ptr->index_list[index_method].index_entry_size) < 0)) {
			sprintf(tmp_error_text, "%s (%s %lu, %s %u) %s (%s %lu %s %u).",
				"The embedded index value calculated for this index entry",
				"at record element",
				DCR_IELE_TO_RELE_P(cache_ptr, index_method, entry_count,
				entry_list, count_1),
				"record offset",
				DCR_IELE_TO_ROFF_P(cache_ptr, index_method, entry_count,
				entry_list, count_1),
				"is less than the previous index entry embedded index value",
				"at record element",
				DCR_IELE_TO_RELE_P(cache_ptr, index_method, entry_count,
				entry_list, count_1 - 1),
				"record offset",
				DCR_IELE_TO_ROFF_P(cache_ptr, index_method, entry_count,
				entry_list, count_1 - 1));
			return_code = DCR_FAILURE;
			break;
		}
		last_index_entry = this_index_entry;
	}

	if (return_code != DCR_SUCCESS) {
		sprintf(error_text, "Error in index number %u, index entry number %u: ",
			index_method, count_1);
		nstrcat(error_text, tmp_error_text,
			DCR_MAX_ERROR_TEXT - (strlen(error_text) + 1));
	}

	if ((cache_ptr->call_back_mask & DCR_CB_CHECK_INDEX_2) &&
		(cache_ptr->call_back_function != NULL)) {
		DCR_StatEndTime(&tmp_stat, ((unsigned long) entry_count));
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_CHECK_INDEX_2,
			DCR_TRUE, index_method, 0, entry_count, ((void *) entry_list),
			&tmp_stat, return_code, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

