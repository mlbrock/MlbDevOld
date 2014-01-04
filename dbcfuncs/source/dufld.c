/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Dumps a single database facility field in text format.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include "dbcfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DumpField

   SYNOPSIS    :	void DBC_DumpField(type_count, type_list,
							member_ptr, record_ptr, null_flag, intra_field_sep,
							null_string, overflow_char, user_data_ptr,
							output_function, output_control);

						const DBC_CONTEXT  *dbc_context_ptr;

						unsigned int        type_count;

						const DTA_TYPE     *type_list;

						const MDDL         *member_ptr;

						const void         *record_ptr;

						int                 null_flag;

						const char         *null_string;

						const char         *intra_field_sep;

						const char         *overflow_char;

						void               *user_data_ptr;

						void              (*output_function)(void *, char *, ...);

						void               *output_control;

   DESCRIPTION :	Dumps a single database facility field in text format.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` is a pointer to the
						''DBC_CONTEXT'' structure which contains the facility
						to be used.

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

						<->``output_function``(void *, ``format_string``, ``...``);

						(-) Functions of this form include the C standard library
						function ``fprintf``. The memory-mapped library function
						``mprintf`` may also be used.

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

   SEE ALSO    :	MDDL_DumpField

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_DumpField
						Dump Functions:DBC_DumpField
						Database Functions:Facility Functions:DBC_DumpField
						DBC Functions:Dump Functions:DBC_DumpField

   PUBLISH XREF:	DBC_DumpField

   PUBLISH NAME:	DBC_DumpField

	ENTRY CLASS	:	Dump Functions
						Database Functions:Facility Functions
						DBC Functions:Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_DumpField(const DBC_CONTEXT *dbc_context_ptr, unsigned int type_count,
	const DTA_TYPE *type_list, const MDDL *member_ptr, const void *record_ptr,
	int null_flag, const char *intra_field_sep, const char *null_string,
	const char *overflow_char, void *user_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void DBC_DumpField(dbc_context_ptr, type_count, type_list, member_ptr,
	record_ptr, null_flag, null_string, intra_field_sep, overflow_char,
	user_data_ptr, output_function, output_control)
const DBC_CONTEXT     *dbc_context_ptr;
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
	if (DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.dump_field), NULL) ==
		DBC_SUCCESS)
		(*dbc_context_ptr->dbc_funcs.dump_field)(type_count, type_list,
			member_ptr, record_ptr, null_flag, null_string, intra_field_sep,
			overflow_char, user_data_ptr, output_function, output_control);
}
/*	***********************************************************************	*/

