/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Dumps a single record field.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <string.h>

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_DumpField

   SYNOPSIS    :	void MDDL_DumpField(type_count, type_list,
							member_ptr, record_ptr, null_flag, intra_field_sep,
							null_string, overflow_char, user_data_ptr,
							output_function, output_control);

						unsigned int           type_count;

						const DTA_TYPE        *type_list;

						const MDDL            *member_ptr;

						const void            *record_ptr;

						int                    null_flag;

						const char            *intra_field_sep;

						const char            *null_string;

						const char            *overflow_char;

						void                  *user_data_ptr;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Dumps a single field in text format.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''DTA_TYPE''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``dtadata.c``
						under the names ``DTA_TypeCount`` and
						``DTA_TypeList``.

						(.) ``member_ptr`` points to the ''MDDL'' structure
						which describes the member data within the record to be
						dumped by this function.

						(.) ``record_ptr`` points to the record which contains the
						member data to be dumped.

						(.) ``null_flag`` specifies how ''NULL'' fields are to be
						dumped by the program.

						(..) If ``null_flag`` is zero, ''NULL'' fields will have
						no special handling --- that is, character fields will be
						dumped as spaces and numeric fields will be dumped as the
						value ''0'' (or ''0.0000'' for floating-point numeric
						fields).

						(..) If ``null_flag`` is non-zero, this function will take
						one of the following actions:

						(...) If ``null_string`` is a not ''NULL'', ''NULL'' fields
						will be dumped as the string contained within
						``null_string``.

						(...) If ``null_string`` is ''NULL'', ''NULL'' fields will
						be dumped as a sufficient number of spaces to align the
						field with its neighbors.

						(.) ``null_string`` is the string to be used to indicate
						that a member of a record contains a ''NULL'' value. See
						the description of the ``null_flag`` parameter (above) for
						further details.

						(.) ``intra_field_sep`` is the string to be used to
						separate the elements of fields which have an array data
						type or which are comprised of more than one primitive
						data type.

						(-) If ``intra_field_sep`` is ''NULL'' or equal to
						zero-length string, array elements of fields will not be
						separated in the dumped output.

						(-) ``intra_field_sep`` is usually equal to a hyphen (''-'')
						character.

						(.) ``overflow_char`` points to the single character to be
						used if the emitted data should overflow its determined
						field width.

						(-) If ``overflow_char`` is ''NULL'' or is equal to the
						empty string (''""''), the asterisk character (''*'') will
						be used.

						(.) ``user_data_ptr`` is a pointer to ''void'' which the
						application programmer may use in order to attach
						application-specific knowledge to the structure.

						(.) ``output_function`` is a pointer to the function which
						handles output. The function should take arguments of the
						general form:

						<->''int'' ``output_function``(''void *'', ''const char'' ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The MFILE memory-mapped library
						function ``mprintf`` may also be used.

						(-) If the ``output_function`` parameter is ''NULL'', the
						function will set it to ``fprintf``.

						(.) ``output_control`` is the pointer which will be used by
						this function as the first parameter to the function
						specified by the ``output_function`` parameter.

						(-) For example, if ``output_function`` points to the
						function ``fprintf``, then ``output_control`` should be
						a pointer to a structure of type ''FILE''.

						(-) If the `` output_control`` parameter is ''NULL'', the
						function will set it to ``stdout``.

   RETURNS     :	Void.

   NOTES       :	This function is usually called from
						''MDDL_DumpRecord''.

   CAVEATS     :	

   SEE ALSO    :	MDDL_DumpRecord

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	MDDL_DumpField
						Dump Functions:MDDL_DumpField
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_DumpField

   PUBLISH NAME:	MDDL_DumpField

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_DumpField(unsigned int type_count, const DTA_TYPE *type_list,
	const MDDL *member_ptr, const void *record_ptr, int null_flag,
	const char *null_string, const char *intra_field_sep,
	const char *overflow_char, void *user_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void MDDL_DumpField(type_count, type_list, member_ptr, record_ptr,
	null_flag, null_string, intra_field_sep, overflow_char, user_data_ptr,
	output_function, output_control)
unsigned int           type_count;
const DTA_TYPE        *type_list;
const MDDL            *member_ptr;
const void            *record_ptr;
int                    null_flag;
const char            *intra_field_sep;
const char            *null_string;
const char            *overflow_char;
void                  *user_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int  output_length = 0;
	unsigned int  intra_sep_length;
	unsigned int  count_1;
	unsigned int  count_2;
	const void   *data_ptr;
	const DTA    *align_ptr;
	char          printf_buffer[1024];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	DTA_GetTypeInfo(&type_count, &type_list);

	intra_sep_length = ((intra_field_sep != NULL) && *intra_field_sep) ?
		strlen(intra_field_sep) : 0;

	overflow_char    = (overflow_char == NULL) ? "*" : overflow_char;

	/*	*****************************************************************
		*****************************************************************
		We may be instructed to handle NULL fields specially . . .
		*****************************************************************	*/
	if (null_flag) {
		(*output_function)(output_control, "%-*.*s",
			member_ptr->display_length, member_ptr->display_length,
			(null_string == NULL) ? "" : null_string);
		return;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		This member may have its own dump function . . .
		*****************************************************************	*/
	if ((member_ptr->dump_function != NULL) &&
		(member_ptr->dump_function != MDDL_DumpField)) {
		(*member_ptr->dump_function)(type_count, type_list, member_ptr,
			record_ptr, null_flag, intra_field_sep, null_string, overflow_char,
			user_data_ptr, output_function, output_control);
		return;
	}
	/*	*****************************************************************	*/

	for (count_1 = 0, align_ptr = member_ptr->align_list;
		count_1 < member_ptr->align_count; count_1++, align_ptr++) {
		data_ptr = ((const void *) (((char *) record_ptr) + member_ptr->offset));
		if (count_1 && (intra_field_sep != NULL) && *intra_field_sep) {
			(*output_function)(output_control, "%s", intra_field_sep);
			output_length += intra_sep_length;
		}
		if (align_ptr->type == DTA_C_unsigned_byte) {
			(*output_function)(output_control, "0X");
			for (count_2 = 0; count_2 < align_ptr->array_length; count_2++)
				(*output_function)(output_control, "%02X",
					((unsigned int) ((unsigned char *) data_ptr)[count_2]));
			output_length += 2 + (align_ptr->array_length * 2);
		}
		else if ((align_ptr->type == DTA_C_unsigned_char) ||
			(align_ptr->type == DTA_C_char)) {
			(*output_function)(output_control, "%-*.*s",
				align_ptr->array_length - 1, align_ptr->array_length - 1,
				data_ptr);
			output_length += align_ptr->array_length - 1;
		}
		else if ((!count_1) && (member_ptr->align_count == 1) &&
			(align_ptr->array_length == 1)) {
			if ((member_ptr->display_length - output_length) >
				type_list[align_ptr->type].printf_length) {
				STR_EMIT_Char(' ',
					(member_ptr->display_length - output_length) -
					type_list[align_ptr->type].printf_length,
					output_function, output_control);
				output_length += (member_ptr->display_length - output_length) -
					type_list[align_ptr->type].printf_length;
			}
			switch (align_ptr->type) {
				case DTA_C_short				:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						((int) *((short *) data_ptr)));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case DTA_C_unsigned_short	:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						((unsigned int) *((unsigned short *) data_ptr)));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case DTA_C_int					:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						*((int *) data_ptr));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case DTA_C_unsigned_int		:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						*((unsigned int *) data_ptr));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case DTA_C_long				:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						*((long *) data_ptr));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case DTA_C_unsigned_long	:
					(*output_function)(output_control,
						type_list[align_ptr->type].printf_format,
						*((unsigned long *) data_ptr));
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case DTA_C_float				:
					sprintf(printf_buffer,
						type_list[align_ptr->type].printf_format,
						*((float *) data_ptr));
					if (type_list[align_ptr->type].printf_length >=
						strlen(printf_buffer))
						(*output_function)(output_control, "%*.*s",
							type_list[align_ptr->type].printf_length,
							type_list[align_ptr->type].printf_length,
							printf_buffer);
					else
						STR_EMIT_Char(*overflow_char,
							type_list[align_ptr->type].printf_length,
							output_function, output_control);
					output_length += type_list[align_ptr->type].printf_length;
					break;
				case DTA_C_double				:
					sprintf(printf_buffer,
						type_list[align_ptr->type].printf_format,
						*((double *) data_ptr));
					if (type_list[align_ptr->type].printf_length >=
						strlen(printf_buffer))
						(*output_function)(output_control, "%*.*s",
							type_list[align_ptr->type].printf_length,
							type_list[align_ptr->type].printf_length,
							printf_buffer);
					else
						STR_EMIT_Char(*overflow_char,
							type_list[align_ptr->type].printf_length,
							output_function, output_control);
					output_length += type_list[align_ptr->type].printf_length;
					break;
				default							:
					break;
			}
		}
		else {
			for (count_2 = 0; count_2 < align_ptr->array_length; count_2++) {
				if (count_2 && (intra_field_sep != NULL) && *intra_field_sep) {
					(*output_function)(output_control, "%s", intra_field_sep);
					output_length += intra_sep_length;
				}
				switch (align_ptr->type) {
					case DTA_C_short				:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							((int) *((short *) data_ptr)));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case DTA_C_unsigned_short	:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							((unsigned int) *((unsigned short *) data_ptr)));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case DTA_C_int					:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							*((int *) data_ptr));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case DTA_C_unsigned_int		:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							*((unsigned int *) data_ptr));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case DTA_C_long				:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							*((long *) data_ptr));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case DTA_C_unsigned_long	:
						(*output_function)(output_control,
							type_list[align_ptr->type].printf_format,
							*((unsigned long *) data_ptr));
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case DTA_C_float				:
						sprintf(printf_buffer,
							type_list[align_ptr->type].printf_format,
							*((float *) data_ptr));
						if (type_list[align_ptr->type].printf_length >=
							strlen(printf_buffer))
							(*output_function)(output_control, "%*.*s",
								type_list[align_ptr->type].printf_length,
								type_list[align_ptr->type].printf_length,
								printf_buffer);
						else
							STR_EMIT_Char(*overflow_char,
								type_list[align_ptr->type].printf_length,
								output_function, output_control);
						output_length += type_list[align_ptr->type].printf_length;
						break;
					case DTA_C_double				:
						sprintf(printf_buffer,
							type_list[align_ptr->type].printf_format,
							*((double *) data_ptr));
						if (type_list[align_ptr->type].printf_length >=
							strlen(printf_buffer))
							(*output_function)(output_control, "%*.*s",
								type_list[align_ptr->type].printf_length,
								type_list[align_ptr->type].printf_length,
								printf_buffer);
						else
							STR_EMIT_Char(*overflow_char,
								type_list[align_ptr->type].printf_length,
								output_function, output_control);
						output_length += type_list[align_ptr->type].printf_length;
						break;
					default							:
						break;
				}
				data_ptr = ((const void *) (((const char *) data_ptr) +
					type_list[align_ptr->type].type_length));
			}
		}
	}

	if (member_ptr->display_length > output_length)
		STR_EMIT_Char(' ', member_ptr->display_length - output_length,
			output_function, output_control);
}
/*	***********************************************************************	*/

