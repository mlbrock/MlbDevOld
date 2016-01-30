/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Source Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits MDDL structure data.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "mddli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_EmitMemberList

   SYNOPSIS    :	void MDDL_EmitMemberList(count, list, output_function,
							output_control);

						unsigned int           count;

						const MDDL            *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;


   DESCRIPTION :	Emits a list of ''MDDL'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''MDDL'' structures which
						is to be emitted by this function.

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

   NOTES       :	This function emits the list of ''MDDL'' structures
						with column headers and trailers. If you do not want this
						behavior, you must call the related function
						``MDDL_EmitMember`` for each array element.

						You can emit the list of ''MDDL'' structures prepended
						by the index within the list by using the related function
						``MDDL_EmitMemberListIdx``.

   CAVEATS     :	

   SEE ALSO    :	MDDL_EmitMemberListIdx
						MDDL_EmitMember
						MDDL_EmitMemberHeader
						MDDL_EmitMemberTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	MDDL_EmitMemberList
						Emit Functions:MDDL_EmitMemberList
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_EmitMemberList

   PUBLISH NAME:	MDDL_EmitMemberList

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_EmitMemberList(unsigned int count, const MDDL *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void MDDL_EmitMemberList(count, list, output_function, output_control)
unsigned int           count;
const MDDL            *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	MDDL_EmitMemberHeader(output_function, output_control);
	MDDL_EmitMemberTrailer(output_function, output_control);

	while (count--)
		MDDL_EmitMember(list++, output_function, output_control);

	MDDL_EmitMemberTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_EmitMemberListIdx

   SYNOPSIS    :	void MDDL_EmitMemberListIdx(count, list, output_function,
							output_control);

						unsigned int           count;

						const MDDL            *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;


   DESCRIPTION :	Emits a list of ''MDDL'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

						Each element of ``list`` is emited by this function prepended
						by the six-digit, zero-filled index of the element in the
						``list``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''MDDL'' structures which
						is to be emitted by this function.

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

   NOTES       :	You can emit the list of ''MDDL'' structures without
						the prepended index by using the related function
						``MDDL_EmitMemberList``.
	
   CAVEATS     :	

   SEE ALSO    :	MDDL_EmitMemberList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	MDDL_EmitMemberListIdx
						Emit Functions:MDDL_EmitMemberListIdx
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_EmitMemberListIdx

   PUBLISH NAME:	MDDL_EmitMemberListIdx

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_EmitMemberListIdx(unsigned int count, const MDDL *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void MDDL_EmitMemberListIdx(count, list, output_function, output_control)
unsigned int           count;
const MDDL            *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "Index  ");
	MDDL_EmitMemberHeader(output_function, output_control);

	(*output_function)(output_control, "------ ");
	MDDL_EmitMemberTrailer(output_function, output_control);

	for (count_1 = 0; count_1 < count; count_1++) {
		(*output_function)(output_control, "%06u ", count_1);
		MDDL_EmitMember(list++, output_function, output_control);
	}

	(*output_function)(output_control, "------ ");
	MDDL_EmitMemberTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_EmitMember

   SYNOPSIS    :	void MDDL_EmitMember(ptr, output_function, output_control);

						const MDDL            *ptr;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;


   DESCRIPTION :	Emits a single ''MDDL'' structure to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` is a pointer to the ''MDDL'' structure
						which is to be emitted by this function.

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

   NOTES       :	To emit an array of ''MDDL'' structures, use the
						related function ``MDDL_EmitMemberList``.

   CAVEATS     :	

   SEE ALSO    :	MDDL_EmitMemberList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	MDDL_EmitMember
						Emit Functions:MDDL_EmitMember
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_EmitMember

   PUBLISH NAME:	MDDL_EmitMember

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_EmitMember(const MDDL *ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void MDDL_EmitMember(ptr, output_function, output_control)
const MDDL            *ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %10u %10u %10u %10u %-*.*s %11u %11u %11u %11u %08lX %08lX\n",
		sizeof(ptr->name) - 1,
		sizeof(ptr->name) - 1, ptr->name,
		ptr->data_length,
		ptr->length,
		ptr->offset,
		ptr->type_count,
		sizeof(ptr->type_spec) - 1,
		sizeof(ptr->type_spec) - 1, ptr->type_spec,
		ptr->align_count,
		ptr->dbc_type,
		ptr->user_int_1,
		ptr->user_int_2,
		((unsigned long) ptr->user_ptr_1),
		((unsigned long) ptr->user_ptr_2));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_EmitMemberHeader

   SYNOPSIS    :	void MDDL_EmitMemberHeader(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;


   DESCRIPTION :	Emits a column header suitable for use with the output
						which results from the functions ``MDDL_EmitMember``,
						``MDDL_EmitMemberList`` and ``MDDL_EmitMemberListIdx``.

   PARAMETERS  :	Parameters to this function are as follow:

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

   NOTES       :	You can emit a trailer by calling the related function
						``MDDL_EmitMemberTrailer``.

   CAVEATS     :	

   SEE ALSO    :	MDDL_EmitMemberTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	MDDL_EmitMemberHeader
						Emit Functions:MDDL_EmitMemberHeader
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_EmitMemberHeader

   PUBLISH NAME:	MDDL_EmitMemberHeader

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_EmitMemberHeader(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void MDDL_EmitMemberHeader(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %-10.10s %-10.10s %-10.10s %-10.10s %-*.*s %-11.11s %-11.11s \
%-11.11s %-11.11s %-8.8s %-8.8s\n",
		STR_sizeof(MDDL, name) - 1,
		STR_sizeof(MDDL, name) - 1, "Name",
		"Data Len",
		"Length",
		"Offset",
		"Type Count",
		STR_sizeof(MDDL, type_spec) - 1,
		STR_sizeof(MDDL, type_spec) - 1, "Type Spec",
		"Align Count",
		"DBC Type",
		"User Int 1",
		"User Int 2",
		"User Ptr 1",
		"User Ptr 2");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MDDL_EmitMemberTrailer

   SYNOPSIS    :	void MDDL_EmitMemberTrailer(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;


   DESCRIPTION :	Emits a column trailer suitable for use with the output
						which results from the functions ``MDDL_EmitMember``,
						``MDDL_EmitMemberList`` and ``MDDL_EmitMemberListIdx``.

   PARAMETERS  :	Parameters to this function are as follow:

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

   NOTES       :	You can emit a header by calling the related function
						``MDDL_EmitMemberHeader``.

   CAVEATS     :	

   SEE ALSO    :	MDDL_EmitMemberHeader

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	MDDL_EmitMemberTrailer
						Emit Functions:MDDL_EmitMemberTrailer
						Member Data Definition Functions:see MDDL

   PUBLISH XREF:	MDDL_EmitMemberTrailer

   PUBLISH NAME:	MDDL_EmitMemberTrailer

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MDDL_EmitMemberTrailer(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void MDDL_EmitMemberTrailer(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_CharSpace('-', STR_sizeof(MDDL, name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-', STR_sizeof(MDDL, type_spec) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-',  8, output_function, output_control);
	STR_EMIT_CharLine('-',   8, output_function, output_control);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

static const MDDL   TEST_List[] = {
	{
		"name",
		STR_sizeof(MDDL, name) - 1,
		STR_sizeof(MDDL, name),
		offsetof(MDDL, name),
		STR_sizeof(MDDL, name) - 1,
		"c",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"data_length",
		STR_sizeof(MDDL, data_length),
		STR_sizeof(MDDL, data_length),
		offsetof(MDDL, data_length),
		1,
		"I",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"length",
		STR_sizeof(MDDL, length),
		STR_sizeof(MDDL, length),
		offsetof(MDDL, length),
		1,
		"I",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"offset",
		STR_sizeof(MDDL, offset),
		STR_sizeof(MDDL, offset),
		offsetof(MDDL, offset),
		1,
		"I",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"type_count",
		STR_sizeof(MDDL, type_count),
		STR_sizeof(MDDL, type_count),
		offsetof(MDDL, type_count),
		1,
		"I",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"type_spec",
		STR_sizeof(MDDL, type_spec) - 1,
		STR_sizeof(MDDL, type_spec),
		offsetof(MDDL, type_spec),
		STR_sizeof(MDDL, type_spec) - 1,
		"c",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"align_count",
		STR_sizeof(MDDL, align_count),
		STR_sizeof(MDDL, align_count),
		offsetof(MDDL, align_count),
		1,
		"I",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
/*
	{
		"align_list",
		STR_sizeof(MDDL, align_list),
		STR_sizeof(MDDL, align_list),
		offsetof(MDDL, align_list),
		MDDL_MAX_DTA_COUNT,
		"I[4]",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
*/
	{
		"display_length",
		STR_sizeof(MDDL, display_length),
		STR_sizeof(MDDL, display_length),
		offsetof(MDDL, display_length),
		1,
		"I",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
/*
	{
		"display_name",
		STR_sizeof(MDDL, display_name),
		STR_sizeof(MDDL, display_name),
		offsetof(MDDL, display_name),
		STR_sizeof(MDDL, display_name),
		"B",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
*/
	{
		"dbc_type",
		STR_sizeof(MDDL, dbc_type),
		STR_sizeof(MDDL, dbc_type),
		offsetof(MDDL, dbc_type),
		1,
		"i",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"length_function",
		STR_sizeof(MDDL, length_function),
		STR_sizeof(MDDL, length_function),
		offsetof(MDDL, length_function),
		STR_sizeof(MDDL, length_function),
		"B",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"dump_function",
		STR_sizeof(MDDL, dump_function),
		STR_sizeof(MDDL, dump_function),
		offsetof(MDDL, dump_function),
		STR_sizeof(MDDL, dump_function),
		"B",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_int_1",
		STR_sizeof(MDDL, user_int_1),
		STR_sizeof(MDDL, user_int_1),
		offsetof(MDDL, user_int_1),
		1,
		"i",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_int_2",
		STR_sizeof(MDDL, user_int_2),
		STR_sizeof(MDDL, user_int_2),
		offsetof(MDDL, user_int_2),
		1,
		"i",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_ptr_1",
		STR_sizeof(MDDL, user_ptr_1),
		STR_sizeof(MDDL, user_ptr_1),
		offsetof(MDDL, user_ptr_1),
		STR_sizeof(MDDL, user_ptr_1),
		"B",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_ptr_2",
		STR_sizeof(MDDL, user_ptr_2),
		STR_sizeof(MDDL, user_ptr_2),
		offsetof(MDDL, user_ptr_2),
		STR_sizeof(MDDL, user_ptr_2),
		"B",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		0,
		NULL,
		NULL,
		0,
		0,
		NULL,
		NULL
	}
};

static const unsigned int TEST_Count  =
	sizeof(TEST_List) / sizeof(TEST_List[0]);

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code;
	unsigned int  member_count = 0;
	MDDL         *member_list  = NULL;
	char          error_text[MDDL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'MDDL' Functions\n");
	fprintf(stderr, "---- ------- --- ------ ---------\n\n");

	if ((return_code = MDDL_CopyMemberList(TEST_Count, TEST_List,
		&member_count, &member_list, error_text)) != MDDL_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = MDDL_SetAlignArrayList(0, NULL, member_count,
		member_list, error_text)) != MDDL_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = MDDL_CreateDisplayNameList(member_count,
		member_list, error_text)) != MDDL_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = MDDL_SetDisplayLengthList(0, NULL, member_count,
		member_list, MDDL_TRUE, strlen("*NULL*"), strlen("-"), NULL,
		error_text)) != MDDL_SUCCESS)
		goto EXIT_FUNCTION;

	MDDL_EmitMemberList(member_count, member_list, NULL, NULL);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

EXIT_FUNCTION:

	MDDL_FreeMemberList(&member_count, &member_list);

	if (return_code != MDDL_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

