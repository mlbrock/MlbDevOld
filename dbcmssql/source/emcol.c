/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs 'DBC_MSSQL_COL' structures to the specified
								output handler.

	Revision History	:	1996-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <genfuncs.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_ColumnList

   SYNOPSIS    :	void DBC_MSSQL_EMIT_ColumnList(count, list, output_function,
							output_control);

						unsigned int           count;

						const DBC_MSSQL_COL   *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a list of ''DBC_MSSQL_COL'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DBC_MSSQL_COL'' structures
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

   NOTES       :	This function emits the list of ''DBC_MSSQL_COL''
						structures with column headers and trailers. If you do
						not want this behavior, you must call the related function
						``DBC_MSSQL_EMIT_Column`` for each array element.

						You can emit the list of ''DBC_MSSQL_COL'' structures
						prefaced by the index within the list by using the related
						function ``DBC_MSSQL_EMIT_ColumnListIdx``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_ColumnListIdx
						DBC_MSSQL_EMIT_Column
						DBC_MSSQL_EMIT_ColumnHeader
						DBC_MSSQL_EMIT_ColumnTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_ColumnList
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_ColumnList
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_ColumnList

   PUBLISH XREF:	DBC_MSSQL_EMIT_ColumnList

   PUBLISH NAME:	DBC_MSSQL_EMIT_ColumnList

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_ColumnList(count, list, output_function, output_control)
unsigned int           count;
const DBC_MSSQL_COL   *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
{
	DBC_MSSQL_EMIT_ColumnHeader(output_function, output_control);
	DBC_MSSQL_EMIT_ColumnTrailer(output_function, output_control);

	while (count--)
		DBC_MSSQL_EMIT_Column(list++, output_function, output_control);

	DBC_MSSQL_EMIT_ColumnTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_ColumnListIdx

   SYNOPSIS    :	void DBC_MSSQL_EMIT_ColumnListIdx(count, list,
							output_function, output_control);

						unsigned int           count;

						const DBC_MSSQL_COL   *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a list of ''DBC_MSSQL_COL'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

						Each element of ``list`` is emited by this function prefaced
						by the six-digit, zero-filled index of the element in the
						``list``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DBC_MSSQL_COL'' structures
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

   NOTES       :	You can emit the list of ''DBC_MSSQL_COL'' structures
						without the prefaced index by using the related function
						``DBC_MSSQL_EMIT_ColumnList``.
	
   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_ColumnList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_ColumnListIdx
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_ColumnListIdx
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_ColumnListIdx

   PUBLISH XREF:	DBC_MSSQL_EMIT_ColumnListIdx

   PUBLISH NAME:	DBC_MSSQL_EMIT_ColumnListIdx

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_ColumnListIdx(count, list, output_function, output_control)
unsigned int           count;
const DBC_MSSQL_COL   *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "Index  ");
	DBC_MSSQL_EMIT_ColumnHeader(output_function, output_control);

	(*output_function)(output_control, "------ ");
	DBC_MSSQL_EMIT_ColumnTrailer(output_function, output_control);

	for (count_1 = 0; count_1 < count; count_1++) {
		(*output_function)(output_control, "%06u ", count_1);
		DBC_MSSQL_EMIT_Column(list++, output_function, output_control);
	}

	(*output_function)(output_control, "------ ");
	DBC_MSSQL_EMIT_ColumnTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_Column

   SYNOPSIS    :	void DBC_MSSQL_EMIT_Column(ptr, output_function,
							output_control);

						const DBC_MSSQL_COL   *ptr;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a single ''DBC_MSSQL_COL'' structure to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` is a pointer to the ''DBC_MSSQL_COL'' structure
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

   NOTES       :	To emit an array of ''DBC_MSSQL_COL'' structures, use the
						related function ``DBC_MSSQL_EMIT_ColumnList``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_ColumnList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_Column
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_Column
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_Column

   PUBLISH XREF:	DBC_MSSQL_EMIT_Column

   PUBLISH NAME:	DBC_MSSQL_EMIT_Column

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_Column(ptr, output_function, output_control)
const DBC_MSSQL_COL   *ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %-*.*s %-*.*s %11d %11d %11d %-4.4s %-4.4s %8u %10u %-*.*s\n",
		sizeof(ptr->name) - 1,
		sizeof(ptr->name) - 1,
		ptr->name,
		sizeof(ptr->type_name) - 1,
		sizeof(ptr->type_name) - 1,
		ptr->type_name,
		sizeof(ptr->bind_name) - 1,
		sizeof(ptr->bind_name) - 1,
		ptr->bind_name,
		ptr->type,
		ptr->length,
		ptr->array_length,
		(ptr->vary) ? "YES" : "NO",
		(ptr->nullable_flag) ? "YES" : "NO",
		ptr->flag_bit_position,
		ptr->type_count,
		sizeof(ptr->type_spec) - 1,
		sizeof(ptr->type_spec) - 1,
		ptr->type_spec);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_ColumnHeader

   SYNOPSIS    :	void DBC_MSSQL_EMIT_ColumnHeader(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column header suitable for use with the output
						which results from the functions ``DBC_MSSQL_EMIT_Column``,
						``DBC_MSSQL_EMIT_ColumnList`` and
						``DBC_MSSQL_EMIT_ColumnListIdx``.

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
						``DBC_MSSQL_EMIT_ColumnTrailer``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_ColumnTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_ColumnHeader
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_ColumnHeader
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_ColumnHeader

   PUBLISH XREF:	DBC_MSSQL_EMIT_ColumnHeader

   PUBLISH NAME:	DBC_MSSQL_EMIT_ColumnHeader

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_ColumnHeader(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %-*.*s %-*.*s %-11.11s %-11.11s %-11.11s %-4.4s %-4.4s \
%-8.8s %-10.10s %-*.*s\n",
		STR_sizeof(DBC_MSSQL_COL, name) - 1,
		STR_sizeof(DBC_MSSQL_COL, name) - 1,
		"Name",
		STR_sizeof(DBC_MSSQL_COL, type_name) - 1,
		STR_sizeof(DBC_MSSQL_COL, type_name) - 1,
		"Type Name",
		STR_sizeof(DBC_MSSQL_COL, bind_name) - 1,
		STR_sizeof(DBC_MSSQL_COL, bind_name) - 1,
		"Bind Name",
		"Type",
		"Length",
		"Array Length",
		"Vary",
		"NULL",
		"Flag Bit",
		"Type Count",
		STR_sizeof(DBC_MSSQL_COL, type_spec) - 1,
		STR_sizeof(DBC_MSSQL_COL, type_spec) - 1,
		"Type Spec");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_ColumnTrailer

   SYNOPSIS    :	void DBC_MSSQL_EMIT_ColumnTrailer(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column trailer suitable for use with the output
						which results from the functions ``DBC_MSSQL_EMIT_Column``,
						``DBC_MSSQL_EMIT_ColumnList`` and
						``DBC_MSSQL_EMIT_ColumnListIdx``.

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
						``DBC_MSSQL_EMIT_ColumnHeader``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_ColumnHeader

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_ColumnTrailer
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_ColumnTrailer
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_ColumnTrailer

   PUBLISH XREF:	DBC_MSSQL_EMIT_ColumnTrailer

   PUBLISH NAME:	DBC_MSSQL_EMIT_ColumnTrailer

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_ColumnTrailer(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
{
	STR_EMIT_CharSpace('-', STR_sizeof(DBC_MSSQL_COL, name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-', STR_sizeof(DBC_MSSQL_COL, type_name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-', STR_sizeof(DBC_MSSQL_COL, bind_name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-',  4, output_function, output_control);
	STR_EMIT_CharSpace('-',  4, output_function, output_control);
	STR_EMIT_CharSpace('-',  8, output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharLine('-', STR_sizeof(DBC_MSSQL_COL, type_spec) - 1,
		output_function, output_control);
}
/*	***********************************************************************	*/

