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

#include "dcr.h"

/*	***********************************************************************	*/

void DCR_EmitRecord(field_count, field_list, field_align_list,
	data_length_list, total_length_list, inter_field_separator,
	intra_field_separator, record_ptr, output_function, output_control)
unsigned int      field_count;
DCR_FIELD  *field_list;
GEN_ALIGN        *field_align_list;
unsigned int     *data_length_list;
unsigned int     *total_length_list;
char             *inter_field_separator;
char             *intra_field_separator;
char             *record_ptr;
#ifndef NARGS
void            (*output_function)(void *, char *, ...);
#else
void            (*output_function)();
#endif /* #ifndef NARGS */
void             *output_control;
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < field_count; count_1++) {
		DCR_EmitField(field_list + count_1,
			field_list[count_1].primitive_list_count,
			field_align_list + field_list[count_1].primitive_list_index,
			data_length_list[count_1], total_length_list[count_1],
			intra_field_separator, record_ptr, output_function, output_control);
		if ((count_1 < (field_count - 1)) && (*inter_field_separator))
			(*output_function)(output_control, "%s", inter_field_separator);
	}
}
/*	***********************************************************************	*/

