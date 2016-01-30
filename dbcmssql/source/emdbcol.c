/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs 'DBC_MSSQL_DB_COL' structures to the specified
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

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_DBColumnList

   SYNOPSIS    :	void DBC_MSSQL_EMIT_DBColumnList(count, list, output_function,
							output_control);

						unsigned int            count;

						const DBC_MSSQL_DB_COL *list;

						STR_FUNC_TYPE_fprintf   output_function;

						void                   *output_control;

   DESCRIPTION :	Emits a list of ''DBC_MSSQL_DB_COL'' structures to the
						specified output handler. The structure members are emitted
						in human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DBC_MSSQL_DB_COL''
						structures which is to be emitted by this function.

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

   NOTES       :	This function emits the list of ''DBC_MSSQL_DB_COL''
						structures with column headers and trailers. If you do not
						want this behavior, you must call the related function
						``DBC_MSSQL_EMIT_DBColumn`` for each array element.

						You can emit the list of ''DBC_MSSQL_DB_COL'' structures
						prefaced by the index within the list by using the related
						function ``DBC_MSSQL_EMIT_DBColumnListIdx``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_DBColumnListIdx
						DBC_MSSQL_EMIT_DBColumn
						DBC_MSSQL_EMIT_DBColumnHeader
						DBC_MSSQL_EMIT_DBColumnTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_DBColumnList
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_DBColumnList
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_DBColumnList

   PUBLISH XREF:	DBC_MSSQL_EMIT_DBColumnList

   PUBLISH NAME:	DBC_MSSQL_EMIT_DBColumnList

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_DBColumnList(count, list, output_function, output_control)
unsigned int            count;
const DBC_MSSQL_DB_COL *list;
STR_FUNC_TYPE_fprintf   output_function;
void                   *output_control;
{
	DBC_MSSQL_EMIT_DBColumnHeader(output_function, output_control);
	DBC_MSSQL_EMIT_DBColumnTrailer(output_function, output_control);

	while (count--)
		DBC_MSSQL_EMIT_DBColumn(list++, output_function, output_control);

	DBC_MSSQL_EMIT_DBColumnTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_DBColumnListIdx

   SYNOPSIS    :	void DBC_MSSQL_EMIT_DBColumnListIdx(count, list,
							output_function, output_control);

						unsigned int            count;

						const DBC_MSSQL_DB_COL *list;

						STR_FUNC_TYPE_fprintf   output_function;

						void                   *output_control;

   DESCRIPTION :	Emits a list of ''DBC_MSSQL_DB_COL'' structures to the
						specified output handler. The structure members are emitted
						in human-readable columnar output.

						Each element of ``list`` is emited by this function prefaced
						by the six-digit, zero-filled index of the element in the
						``list``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DBC_MSSQL_DB_COL'' structures
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

   NOTES       :	You can emit the list of ''DBC_MSSQL_DB_COL'' structures
						without the prefaced index by using the related function
						``DBC_MSSQL_EMIT_DBColumnList``.
	
   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_DBColumnList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_DBColumnListIdx
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_DBColumnListIdx
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_DBColumnListIdx

   PUBLISH XREF:	DBC_MSSQL_EMIT_DBColumnListIdx

   PUBLISH NAME:	DBC_MSSQL_EMIT_DBColumnListIdx

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_DBColumnListIdx(count, list, output_function,
	output_control)
unsigned int            count;
const DBC_MSSQL_DB_COL *list;
STR_FUNC_TYPE_fprintf   output_function;
void                   *output_control;
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "Index  ");
	DBC_MSSQL_EMIT_DBColumnHeader(output_function, output_control);

	(*output_function)(output_control, "------ ");
	DBC_MSSQL_EMIT_DBColumnTrailer(output_function, output_control);

	for (count_1 = 0; count_1 < count; count_1++) {
		(*output_function)(output_control, "%06u ", count_1);
		DBC_MSSQL_EMIT_DBColumn(list++, output_function, output_control);
	}

	(*output_function)(output_control, "------ ");
	DBC_MSSQL_EMIT_DBColumnTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_DBColumn

   SYNOPSIS    :	void DBC_MSSQL_EMIT_DBColumn(ptr, output_function,
							output_control);

						const DBC_MSSQL_DB_COL *ptr;

						STR_FUNC_TYPE_fprintf   output_function;

						void                   *output_control;

   DESCRIPTION :	Emits a single ''DBC_MSSQL_DB_COL'' structure to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` is a pointer to the ''DBC_MSSQL_DB_COL'' structure
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

   NOTES       :	To emit an array of ''DBC_MSSQL_DB_COL'' structures, use the
						related function ``DBC_MSSQL_EMIT_DBColumnList``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_DBColumnList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_DBColumn
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_DBColumn
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_DBColumn

   PUBLISH XREF:	DBC_MSSQL_EMIT_DBColumn

   PUBLISH NAME:	DBC_MSSQL_EMIT_DBColumn

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_DBColumn(ptr, output_function, output_control)
const DBC_MSSQL_DB_COL *ptr;
STR_FUNC_TYPE_fprintf   output_function;
void                   *output_control;
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%4u %10u %9d %-*.*s %6u %-*.*s %6d %-*.*s %-*.*s %6u %11d\n",
		((unsigned int) ptr->type),
		((unsigned int) ptr->table_type),
		((short) ptr->user_type),
   	sizeof(ptr->name) - 1,
   	sizeof(ptr->name) - 1,
		ptr->name,
		((unsigned int) ptr->length),
		sizeof(ptr->type_name) - 1,
		sizeof(ptr->type_name) - 1,
		ptr->type_name,
		((short) ptr->offset),
		sizeof(ptr->default_name) - 1,
		sizeof(ptr->default_name) - 1,
		ptr->default_name,
		sizeof(ptr->rule_name) - 1,
		sizeof(ptr->rule_name) - 1,
		ptr->rule_name,
		((unsigned int) ptr->status),
		ptr->basic_type);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_DBColumnHeader

   SYNOPSIS    :	void DBC_MSSQL_EMIT_DBColumnHeader(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column header suitable for use with the output
						which results from the functions ``DBC_MSSQL_EMIT_DBColumn``,
						``DBC_MSSQL_EMIT_DBColumnList`` and
						``DBC_MSSQL_EMIT_DBColumnListIdx``.

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
						``DBC_MSSQL_EMIT_DBColumnTrailer``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_DBColumnTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_DBColumnHeader
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_DBColumnHeader
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_DBColumnHeader

   PUBLISH XREF:	DBC_MSSQL_EMIT_DBColumnHeader

   PUBLISH NAME:	DBC_MSSQL_EMIT_DBColumnHeader

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_DBColumnHeader(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-4.4s %-10.10s %-9.9s %-*.*s %-6.6s %-*.*s %-6.6s %-*.*s %-*.*s \
%-6.6s %-11.11s\n",
		"Type",
		"Table Type",
		"User Type",
   	STR_sizeof(DBC_MSSQL_DB_COL, name) - 1,
   	STR_sizeof(DBC_MSSQL_DB_COL, name) - 1,
		"Col Name",
		"Length",
		STR_sizeof(DBC_MSSQL_DB_COL, type_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_COL, type_name) - 1,
		"Type Name",
		"Offset",
		STR_sizeof(DBC_MSSQL_DB_COL, default_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_COL, default_name) - 1,
		"Column Default",
		STR_sizeof(DBC_MSSQL_DB_COL, rule_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_COL, rule_name) - 1,
		"Column Rule",
		"Col Status",
		"Basic Type");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_DBColumnTrailer

   SYNOPSIS    :	void DBC_MSSQL_EMIT_DBColumnTrailer(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column trailer suitable for use with the output
						which results from the functions ``DBC_MSSQL_EMIT_DBColumn``,
						``DBC_MSSQL_EMIT_DBColumnList`` and
						``DBC_MSSQL_EMIT_DBColumnListIdx``.

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
						``DBC_MSSQL_EMIT_DBColumnHeader``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_DBColumnHeader

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_DBColumnTrailer
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_DBColumnTrailer
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_DBColumnTrailer

   PUBLISH XREF:	DBC_MSSQL_EMIT_DBColumnTrailer

   PUBLISH NAME:	DBC_MSSQL_EMIT_DBColumnTrailer

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_DBColumnTrailer(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
{
	STR_EMIT_CharSpace('-', 4, output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-',  9, output_function, output_control);
   STR_EMIT_CharSpace('-',
		STR_sizeof(DBC_MSSQL_DB_COL, name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-',  6, output_function, output_control);
	STR_EMIT_CharSpace('-',
		STR_sizeof(DBC_MSSQL_DB_COL, type_name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-',  6, output_function, output_control);
	STR_EMIT_CharSpace('-',
		STR_sizeof(DBC_MSSQL_DB_COL, default_name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-',
		STR_sizeof(DBC_MSSQL_DB_COL, rule_name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-',  6, output_function, output_control);
	STR_EMIT_CharLine('-', 11, output_function, output_control);
}
/*	***********************************************************************	*/

