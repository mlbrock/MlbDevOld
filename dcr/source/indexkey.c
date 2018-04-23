/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages cache index key lists.

	Revision History	:	1994-12-05 --- Creation.
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

#include <memory.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_AddIndexKeyList(cache_ptr, in_index_key_count,
	in_index_key_list, error_text)
DCR_CACHE                 *cache_ptr;
unsigned int               in_index_key_count;
const DCR_INDEX_KEY *in_index_key_list;
char                      *error_text;
{
	int                  return_code     = DCR_SUCCESS;
	unsigned int         index_key_count = 0;
	DCR_INDEX_KEY *index_key_list  = NULL;

	if ((return_code = DCR_CopyIndexKeyList(in_index_key_count,
		in_index_key_list, &index_key_count, &index_key_list, error_text)) ==
		DCR_SUCCESS) {
		DCR_FreeIndexKeyList(cache_ptr->index_key_count,
			cache_ptr->index_key_list);
		cache_ptr->index_key_count = index_key_count;
		cache_ptr->index_key_list  = index_key_list;
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_CopyIndexKeyList(in_index_key_count, in_index_key_list,
   out_index_key_count, out_index_key_list, error_text)
unsigned int                in_index_key_count;
const DCR_INDEX_KEY  *in_index_key_list;
unsigned int               *out_index_key_count;
DCR_INDEX_KEY       **out_index_key_list;
char                       *error_text;
{
	int                  return_code     = DCR_SUCCESS;
	unsigned int         index_key_count = 0;
	DCR_INDEX_KEY *index_key_list  = NULL;
	unsigned int         count_1;
	unsigned int        *tmp_ptr;

	*out_index_key_count = 0;
	*out_index_key_list  = NULL;

	if (in_index_key_count) {
		if ((index_key_list = ((DCR_INDEX_KEY *)
			calloc(in_index_key_count, sizeof(DCR_INDEX_KEY)))) == NULL) {
			sprintf(error_text, "%s (%u elements * %u size = %u total bytes).",
				"Unable to copy the specified index key list",
				in_index_key_count, sizeof(DCR_INDEX_KEY),
				in_index_key_count * sizeof(DCR_INDEX_KEY));
			return_code = DCR_MEMORY_FAILURE;
		}
		else {
			index_key_count = in_index_key_count;
			for (count_1 = 0; count_1 < in_index_key_count; count_1++) {
				index_key_list[count_1] = in_index_key_list[count_1];
				tmp_ptr                 =
					(index_key_list[count_1].field_count >
					index_key_list[count_1].record_cmp.align_count) ?
					&index_key_list[count_1].record_cmp.align_count :
					(index_key_list[count_1].field_count >
					index_key_list[count_1].index_cmp.align_count) ?
					&index_key_list[count_1].index_cmp.align_count : NULL;
				if (tmp_ptr != NULL) {
					sprintf(error_text, "%s %u %s (%u) %s %s %s (%u).",
						"Cache index key list index", count_1, "field count",
						in_index_key_list[count_1].field_count,
						"is greater than the", (tmp_ptr ==
						&index_key_list[count_1].record_cmp.align_count) ?
						"record" : "index", "comparison descriptor align count",
						 *tmp_ptr);
					return_code = DCR_FAILURE;
					break;
				}
				index_key_list[count_1].record_cmp.ignore_case_flag =
					index_key_list[count_1].ignore_case_flag;
				index_key_list[count_1].index_cmp.ignore_case_flag  =
					index_key_list[count_1].ignore_case_flag;
				if (mema_copy(in_index_key_list[count_1].record_cmp.align_count,
					in_index_key_list[count_1].record_cmp.align_list,
					sizeof(GEN_ALIGN),
					&index_key_list[count_1].record_cmp.align_count,
					((void **) &index_key_list[count_1].record_cmp.align_list)) !=
					STRFUNCS_SUCCESS) {
					tmp_ptr     = &index_key_list[count_1].record_cmp.align_count;
					return_code = DCR_MEMORY_FAILURE;
				}
				else if (mema_copy(
					in_index_key_list[count_1].index_cmp.align_count,
					in_index_key_list[count_1].index_cmp.align_list,
					sizeof(GEN_ALIGN),
					&index_key_list[count_1].index_cmp.align_count,
					((void **) &index_key_list[count_1].index_cmp.align_list)) !=
					STRFUNCS_SUCCESS) {
					mema_remove_all(
						&index_key_list[count_1].record_cmp.align_count,
						((void **) &index_key_list[count_1].record_cmp.align_list));
					tmp_ptr     = &index_key_list[count_1].index_cmp.align_count;
					return_code = DCR_MEMORY_FAILURE;
				}
				if (return_code != DCR_SUCCESS) {
					if (count_1)
						DCR_FreeIndexKeyList(count_1, index_key_list);
					index_key_list = NULL;
					sprintf(error_text,
						"%s %u %s %s (%u elements * %u size = %u total bytes).",
						"Unable to allocate memory for cache index key list index",
						count_1, (tmp_ptr ==
						&index_key_list[count_1].record_cmp.align_count) ?
						"record" : "index", "comparison descriptor",
						 *tmp_ptr, sizeof(GEN_ALIGN), *tmp_ptr * sizeof(GEN_ALIGN));
					break;
				}
			}
			if (return_code == DCR_SUCCESS) {
				*out_index_key_count = index_key_count;
				*out_index_key_list  = index_key_list;
			}
			else if (index_key_list != NULL)
				free(index_key_list);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

void DCR_FreeCacheIndexKeyList(cache_ptr)
DCR_CACHE *cache_ptr;
{
	DCR_FreeIndexKeyList(cache_ptr->index_key_count,
		cache_ptr->index_key_list);

	cache_ptr->index_key_count = 0;
	cache_ptr->index_key_list  = NULL;
}
/*	***********************************************************************	*/

void DCR_FreeIndexKeyList(index_key_count, index_key_list)
unsigned int         index_key_count;
DCR_INDEX_KEY *index_key_list;
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < index_key_count; count_1++) {
		mema_remove_all(&index_key_list[count_1].record_cmp.align_count,
			((void **) &index_key_list[count_1].record_cmp.align_list));
		mema_remove_all(&index_key_list[count_1].index_cmp.align_count,
			((void **) &index_key_list[count_1].index_cmp.align_list));
	}

	mema_remove_all(&index_key_count, ((void **) &index_key_list));
}
/*	***********************************************************************	*/

DCR_INDEX_KEY *DCR_GetIndexKeyPtr(cache_ptr, index_key_element)
const DCR_CACHE *cache_ptr;
unsigned int     index_key_element;
{
	return((index_key_element < cache_ptr->index_key_count) ?
		(cache_ptr->index_key_list + index_key_element) : NULL);
}
/*	***********************************************************************	*/

