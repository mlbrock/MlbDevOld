/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Dumps record headers as described by MDDL
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

   NAME        :	MDDL_DumpHeader

   SYNOPSIS    :	void MDDL_DumpHeader(member_count, member_list,
							index_flag, inter_field_sep, record_leader,
							record_trailer, output_function, output_control);

						unsigned int           member_count;

						const MDDL            *member_list;

						int                    index_flag;

						const char            *inter_field_sep;

						const char            *record_leader;

						const char            *record_trailer;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Dumps a column header suitable for use with the output
						which results from the function ``MDDL_DumpText``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is the array of ''MDDL''
						structures which describes the member data of the header
						to be dumped by this function.

						(.) ``index_flag`` specifies whether the header should be
						dumped with a column for the record index.

						(..) If ``index_flag`` is zero, this function will not
						prepend the header with an index column.

						(..) If ``index_flag`` is not zero, this function will
						prepend the header with a 10 character column for the index.

						(.) ``inter_field_sep`` is the string to be used to
						separate columns in the dumped output.

						(-) If ``inter_field_sep`` is ''NULL'' or equal to
						zero-length string, columns will not be separated in the
						dumped output.

						(-) ``inter_field_sep`` is usually equal to a single space
						character.

						(.) ``record_leader`` is the string which is to be
						prepended to the header dumped by this function.

						(-) ``record_leader`` is usually equal to ''NULL''.

						(.) ``record_trailer`` is the string which is to be
						appended to the header dumped by this function.

						(-) ``record_trailer`` is usually equal to a line-feed
						(''\n'') character.

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

   NOTES       :	You can dump a trailer by calling the related function
						``MDDL_DumpTrailer``.

   CAVEATS     :	

   SEE ALSO    :	MDDL_DumpTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	MDDL_DumpHeader
						Dump Functions:MDDL_DumpHeader
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_DumpHeader

   PUBLISH NAME:	MDDL_DumpHeader

	ENTRY CLASS	:	Dump Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_DumpHeader(unsigned int member_count, const MDDL *member_list,
	int index_flag, const char *inter_field_sep, const char *record_leader,
	const char *record_trailer, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void MDDL_DumpHeader(member_count, member_list, index_flag,
	inter_field_sep, record_leader, record_trailer, output_function,
	output_control)
unsigned int           member_count;
const MDDL            *member_list;
int                    index_flag;
const char            *inter_field_sep;
const char            *record_leader;
const char            *record_trailer;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	if (record_leader != NULL)
		(*output_function)(output_control, "%s", record_leader);

	if (index_flag)
		(*output_function)(output_control, "%-*.*s%s", 10, 10, "Index",
			(inter_field_sep != NULL) ? inter_field_sep : "");

	while (member_count--) {
		(*output_function)(output_control, "%-*.*s%s",
			member_list->display_length, member_list->display_length,
			((member_list->display_name != NULL) && *member_list->display_name) ?
			member_list->display_name : member_list->name,
			(member_count && (inter_field_sep != NULL)) ? inter_field_sep : "");
		member_list++;
	}

	if (record_trailer != NULL)
		(*output_function)(output_control, "%s", record_trailer);
}
/*	***********************************************************************	*/

