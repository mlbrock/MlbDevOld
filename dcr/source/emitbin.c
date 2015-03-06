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

	Revision History	:	1994-05-14 --- Creation.
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

/*
   CAVEAT(S): This function assumes that the 'offset' specified by the
combination of the ``output_function`` and ``output_control`` parameters
is at a location which meets the alignment requirements of the first field
to be emitted.  The function guarantees that subsequent fields (and records)
will be aligned appropriately for the execution architecture.

   You have been warned.
*/
int DCR_EmitBinaryData(cache_ptr, index_method, reverse_flag,
	max_records, field_spec_count, field_spec_list, data_line_count,
	output_function, output_control, error_text)
DCR_CACHE      *cache_ptr;
unsigned int    index_method;
int             reverse_flag;
unsigned int    max_records;
unsigned int   *data_line_count;
unsigned int    field_spec_count;
char          **field_spec_list;
#ifndef NARGS
int           (*output_function)(void *, unsigned int, unsigned int, void *);
#else
int           (*output_function)();
#endif /* #ifndef NARGS */
void           *output_control;
char           *error_text;
{
	int               return_code   = DCR_SUCCESS;
	unsigned int      count_1;
	unsigned int      count_2;
	unsigned int      index_element;
	int               index_increment;
	void              *record_ptr;
	unsigned int      tmp_data_line_count;
   unsigned int      out_field_count;
	DCR_FIELD  *out_field_list;
	unsigned int      output_offset;
	unsigned int      align_fix;
	char              align_padding[DCR_ALIGNMENT_SIZE];

	index_element    = (reverse_flag != DCR_TRUE) ? 0 :
		cache_ptr->record_count - 1;
	index_increment  = (reverse_flag != DCR_TRUE) ? 1 : -1;

	data_line_count  = (data_line_count == NULL) ?
		&tmp_data_line_count : data_line_count;
	*data_line_count = 0;

	if ((return_code = DCR_GetSpecifiedFieldList(cache_ptr->field_count,
		cache_ptr->field_list, cache_ptr->field_name_count,
		cache_ptr->field_name_list, field_spec_count, field_spec_list,
		&out_field_count, &out_field_list, error_text)) == DCR_SUCCESS) {
		/*	********************************************************	*/
		/*	********************************************************	*/
		/*		An optimization for those requests where the entire	*/
		/*	cache record is to be emitted with all fields in the		*/
		/*	order as within the cache.											*/
		/*	********************************************************	*/
		if ((cache_ptr->field_count == out_field_count) &&
			(!memcmp(cache_ptr->field_list, out_field_list,
			out_field_count * sizeof(*out_field_list)))) {
			for (count_1 = 0; count_1 < cache_ptr->record_count; count_1++) {
				record_ptr     = DCR_IELE_TO_RPTR(cache_ptr, index_method,
					index_element);
				index_element += index_increment;
				(*output_function)(record_ptr, cache_ptr->actual_data_record_size,
					1, output_control);
				++(*data_line_count);
				if (max_records && (*data_line_count >= max_records))
					break;
			}
		}
		/*	********************************************************	*/
		/*	********************************************************	*/
		/*		Otherwise, we do it field-by-field . . .					*/
		/*	********************************************************	*/
		else {
			memset(align_padding, '\0', sizeof(align_padding));
			for (count_1 = 0; count_1 < cache_ptr->record_count; count_1++) {
				record_ptr     = DCR_IELE_TO_RPTR(cache_ptr, index_method,
					index_element);
				index_element += index_increment;
				output_offset  = 0;
				for (count_2 = 0; count_2 < out_field_count; count_2++) {
					if ((align_fix = (output_offset % GEN_AlignList[cache_ptr->
						field_align_list[out_field_list[count_2].
						primitive_list_index].type].type_align)) > 0) {
						(*output_function)(align_padding, align_fix, sizeof(char),
							output_control);
						output_offset += align_fix;
					}
					(*output_function)(((char *) record_ptr) +
						out_field_list[count_2].data_offset,
						out_field_list[count_2].data_length, 1, output_control);
					output_offset += out_field_list[count_2].data_length;
				}
				++(*data_line_count);
				if (max_records && (*data_line_count >= max_records))
					break;
			}
		}
		/*	********************************************************	*/
		mema_remove_all(&out_field_count, ((void **) &out_field_list));
	}

	return(return_code);
}
/*	***********************************************************************	*/

