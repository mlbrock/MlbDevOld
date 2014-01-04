/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Dumps a single record as described by MDDL
								structures.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_DumpRecord

   SYNOPSIS    :	void MDDL_DumpRecord(type_count, type_list,
							member_count, member_list, record_ptr, null_string,
							inter_field_sep, intra_field_sep, overflow_char,
							user_data_ptr, output_function, output_control);

						unsigned int           type_count;

						const DTA_TYPE        *type_list;

						unsigned int           member_count;

						const MDDL            *member_list;

						const void            *record_ptr;

						const char            *null_string;

						const char            *inter_field_sep;

						const char            *intra_field_sep;

						const char            *overflow_char;

						void                  *user_data_ptr;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Dumps a single record in text format.

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

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is the array of ''MDDL''
						structures which describes the member data of the record
						to be dumped by this function.

						(.) ``record_ptr`` points to the record to be dumped.

						(.) ``null_string`` is the string to be used to indicate
						that a member of a record contains a ''NULL'' value.

						(.) ``inter_field_sep`` is the string to be used to
						separate columns in the dumped output.

						(-) If ``inter_field_sep`` is ''NULL'' or equal to
						zero-length string, columns will not be separated in the
						dumped output.

						(-) ``inter_field_sep`` is usually equal to a single space
						character.

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
						''MDDL_DumpTextBasic''.

   CAVEATS     :	

   SEE ALSO    :	MDDL_DumpField

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL_DumpRecord
						Cache Functions:MDDL_DumpRecord
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_DumpRecord

   PUBLISH NAME:	MDDL_DumpRecord

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_DumpRecord(unsigned int type_count, const DTA_TYPE *type_list,
	unsigned int member_count, const MDDL *member_list, const void *record_ptr,
	const char *null_string, const char *inter_field_sep,
	const char *intra_field_sep, const char *overflow_char,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void MDDL_DumpRecord(type_count, type_list, member_count,
	member_list, record_ptr, null_string, inter_field_sep, intra_field_sep,
	overflow_char, user_data_ptr, output_function, output_control)
unsigned int           type_count;
const DTA_TYPE        *type_list;
unsigned int           member_count;
const MDDL            *member_list;
const void            *record_ptr;
const char            *null_string;
const char            *inter_field_sep;
const char            *intra_field_sep;
const char            *overflow_char;
void                  *user_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	for (count_1 = 0; count_1 < member_count; count_1++) {
		if (count_1 && (inter_field_sep != NULL) && *inter_field_sep)
			(*output_function)(output_control, "%s", inter_field_sep);
		MDDL_DumpField(type_count, type_list, member_list + count_1,
			record_ptr, 0, null_string, intra_field_sep, overflow_char,
			user_data_ptr, output_function, output_control);
	}
}
/*	***********************************************************************	*/

