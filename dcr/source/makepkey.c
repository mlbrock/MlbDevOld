/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Constructs partial-key descriptors for the specified
								index method.

	Revision History	:	1994-08-06 --- Creation.
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

int DCR_MakePartialKey(cache_ptr, index_method, field_count,
	record_align_cmp_ptr, index_align_cmp_ptr, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
unsigned int   field_count;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
char          *error_text;
{
	int                   return_code;
	unsigned int          count_1;
	DCR_INDEX      *index_ptr;
	DCR_INDEX_DATA *index_data_ptr;

	if ((return_code = DCR_ValidateIndexMethod(cache_ptr, index_method,
		error_text)) == DCR_SUCCESS) {
		index_ptr      = cache_ptr->index_list + index_method;
		index_data_ptr = cache_ptr->index_data_list + index_method;
		if (field_count > index_ptr->field_count) {
			sprintf(error_text, "%s %s %u named '%s' (%u) %s (%u).",
				"The requested number of fields for the construction of a",
				"partial key on index number", index_method,
				index_ptr->index_name, field_count,
				"exceeds the number of fields participating in the index",
				index_ptr->field_count);
			return_code = DCR_BAD_ARGS_FAILURE;
		}
		else {
			record_align_cmp_ptr->align_count = 0;
			record_align_cmp_ptr->align_list  =
				index_data_ptr->record_align_cmp_data.align_list;
			index_align_cmp_ptr->align_count  = 0;
			index_align_cmp_ptr->align_list   =
				index_data_ptr->index_align_cmp_data.align_list;
			for (count_1 = 0; count_1 < field_count; count_1++) {
				record_align_cmp_ptr->align_count += cache_ptr->field_list[
					cache_ptr->index_field_list[index_ptr->field_index + count_1]].
					primitive_list_count;
				index_align_cmp_ptr->align_count  += cache_ptr->field_list[
					cache_ptr->index_field_list[index_ptr->field_index + count_1]].
					primitive_list_count;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

