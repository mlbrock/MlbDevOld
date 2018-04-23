/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs 'DBC_MSSQL_DB_IDX' structures to the specified
								output handler.

	Revision History	:	1996-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
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

   NAME        :	DBC_MSSQL_EMIT_DBIndexList

   SYNOPSIS    :	void DBC_MSSQL_EMIT_DBIndexList(count, list, output_function,
							output_control);

						unsigned int            count;

						const DBC_MSSQL_DB_IDX *list;

						STR_FUNC_TYPE_fprintf   output_function;

						void                   *output_control;

   DESCRIPTION :	Emits a list of ''DBC_MSSQL_DB_IDX'' structures to the
						specified output handler. The structure members are emitted
						in human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DBC_MSSQL_DB_IDX'' structures
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

   NOTES       :	This function emits the list of ''DBC_MSSQL_DB_IDX''
						structures with column headers and trailers. If you do not
						want this behavior, you must call the related function
						``DBC_MSSQL_EMIT_DBIndex`` for each array element.

						You can emit the list of ''DBC_MSSQL_DB_IDX'' structures
						prefaced by the index within the list by using the related
						function ``DBC_MSSQL_EMIT_DBIndexListIdx``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_DBIndexListIdx
						DBC_MSSQL_EMIT_DBIndex
						DBC_MSSQL_EMIT_DBIndexHeader
						DBC_MSSQL_EMIT_DBIndexTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_DBIndexList
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_DBIndexList
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_DBIndexList

   PUBLISH XREF:	DBC_MSSQL_EMIT_DBIndexList

   PUBLISH NAME:	DBC_MSSQL_EMIT_DBIndexList

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_DBIndexList(count, list, output_function, output_control)
unsigned int            count;
const DBC_MSSQL_DB_IDX *list;
STR_FUNC_TYPE_fprintf   output_function;
void                   *output_control;
{
	DBC_MSSQL_EMIT_DBIndexHeader(output_function, output_control);
	DBC_MSSQL_EMIT_DBIndexTrailer(output_function, output_control);

	while (count--)
		DBC_MSSQL_EMIT_DBIndex(list++, output_function, output_control);

	DBC_MSSQL_EMIT_DBIndexTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_DBIndexListIdx

   SYNOPSIS    :	void DBC_MSSQL_EMIT_DBIndexListIdx(count, list,
							output_function, output_control);

						unsigned int            count;

						const DBC_MSSQL_DB_IDX *list;

						STR_FUNC_TYPE_fprintf   output_function;

						void                   *output_control;

   DESCRIPTION :	Emits a list of ''DBC_MSSQL_DB_IDX'' structures to the
						specified output handler. The structure members are emitted
						in human-readable columnar output.

						Each element of ``list`` is emited by this function prefaced
						by the six-digit, zero-filled index of the element in the
						``list``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DBC_MSSQL_DB_IDX'' structures
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

   NOTES       :	You can emit the list of ''DBC_MSSQL_DB_IDX'' structures
						without the prefaced index by using the related function
						``DBC_MSSQL_EMIT_DBIndexList``.
	
   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_DBIndexList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_DBIndexListIdx
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_DBIndexListIdx
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_DBIndexListIdx

   PUBLISH XREF:	DBC_MSSQL_EMIT_DBIndexListIdx

   PUBLISH NAME:	DBC_MSSQL_EMIT_DBIndexListIdx

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_DBIndexListIdx(count, list, output_function, output_control)
unsigned int            count;
const DBC_MSSQL_DB_IDX *list;
STR_FUNC_TYPE_fprintf   output_function;
void                   *output_control;
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "Index  ");
	DBC_MSSQL_EMIT_DBIndexHeader(output_function, output_control);

	(*output_function)(output_control, "------ ");
	DBC_MSSQL_EMIT_DBIndexTrailer(output_function, output_control);

	for (count_1 = 0; count_1 < count; count_1++) {
		(*output_function)(output_control, "%06u ", count_1);
		DBC_MSSQL_EMIT_DBIndex(list++, output_function, output_control);
	}

	(*output_function)(output_control, "------ ");
	DBC_MSSQL_EMIT_DBIndexTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_DBIndex

   SYNOPSIS    :	void DBC_MSSQL_EMIT_DBIndex(ptr, output_function,
							output_control);

						const DBC_MSSQL_DB_IDX *ptr;

						STR_FUNC_TYPE_fprintf   output_function;

						void                   *output_control;

   DESCRIPTION :	Emits a single ''DBC_MSSQL_DB_IDX'' structure to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` is a pointer to the ''DBC_MSSQL_DB_IDX'' structure
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

   NOTES       :	To emit an array of ''DBC_MSSQL_DB_IDX'' structures, use the
						related function ``DBC_MSSQL_EMIT_DBIndexList``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_DBIndexList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_DBIndex
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_DBIndex
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_DBIndex

   PUBLISH XREF:	DBC_MSSQL_EMIT_DBIndex

   PUBLISH NAME:	DBC_MSSQL_EMIT_DBIndex

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_DBIndex(ptr, output_function, output_control)
const DBC_MSSQL_DB_IDX *ptr;
STR_FUNC_TYPE_fprintf   output_function;
void                   *output_control;
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %8d %7d %-*.*s %5u %6u %6d %6d %-*.*s\n",
		sizeof(ptr->index_name) - 1,
		sizeof(ptr->index_name) - 1,
		ptr->index_name,
		ptr->index_id,
		ptr->key_count,
		sizeof(ptr->column_name) - 1,
		sizeof(ptr->column_name) - 1,
		ptr->column_name,
		ptr->column_order,
		ptr->column_id,
		ptr->status,
		ptr->segment_number,
		sizeof(ptr->segment_name) - 1,
		sizeof(ptr->segment_name) - 1,
		ptr->segment_name);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_DBIndexHeader

   SYNOPSIS    :	void DBC_MSSQL_EMIT_DBIndexHeader(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column header suitable for use with the output
						which results from the functions ``DBC_MSSQL_EMIT_DBIndex``,
						``DBC_MSSQL_EMIT_DBIndexList`` and
						``DBC_MSSQL_EMIT_DBIndexListIdx``.

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
						``DBC_MSSQL_EMIT_DBIndexTrailer``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_DBIndexTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_DBIndexHeader
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_DBIndexHeader
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_DBIndexHeader

   PUBLISH XREF:	DBC_MSSQL_EMIT_DBIndexHeader

   PUBLISH NAME:	DBC_MSSQL_EMIT_DBIndexHeader

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_DBIndexHeader(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %-8.8s %-7.7s %-*.*s %-5.5s %-6.6s %-6.6s %-6.6s %-*.*s\n",
		STR_sizeof(DBC_MSSQL_DB_IDX, index_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_IDX, index_name) - 1,
		"Index Name",
		"Index Id",
		"Key Cnt",
		STR_sizeof(DBC_MSSQL_DB_IDX, column_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_IDX, column_name) - 1,
		"Column Name",
		"Order",
		"Col Id",
		"Status",
		"Segment #",
		STR_sizeof(DBC_MSSQL_DB_IDX, segment_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_IDX, segment_name) - 1,
		"Segment Name");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_EMIT_DBIndexTrailer

   SYNOPSIS    :	void DBC_MSSQL_EMIT_DBIndexTrailer(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column trailer suitable for use with the output
						which results from the functions ``DBC_MSSQL_EMIT_DBIndex``,
						``DBC_MSSQL_EMIT_DBIndexList`` and
						``DBC_MSSQL_EMIT_DBIndexListIdx``.

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
						``DBC_MSSQL_EMIT_DBIndexHeader``.

   CAVEATS     :	

   SEE ALSO    :	DBC_MSSQL_EMIT_DBIndexHeader

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_EMIT_DBIndexTrailer
						Emit Functions:Data Cache Functions:DBC_MSSQL_EMIT_DBIndexTrailer
						Data Cache Functions:Emit Functions:DBC_MSSQL_EMIT_DBIndexTrailer

   PUBLISH XREF:	DBC_MSSQL_EMIT_DBIndexTrailer

   PUBLISH NAME:	DBC_MSSQL_EMIT_DBIndexTrailer

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_EMIT_DBIndexTrailer(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
{
   STR_EMIT_CharSpace('-',
		STR_sizeof(DBC_MSSQL_DB_IDX, index_name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-',  8, output_function, output_control);
	STR_EMIT_CharSpace('-',  7, output_function, output_control);
   STR_EMIT_CharSpace('-',
		STR_sizeof(DBC_MSSQL_DB_IDX, column_name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-',  5, output_function, output_control);
	STR_EMIT_CharSpace('-',  6, output_function, output_control);
	STR_EMIT_CharSpace('-',  6, output_function, output_control);
	STR_EMIT_CharSpace('-',  6, output_function, output_control);
   STR_EMIT_CharLine('-',
		STR_sizeof(DBC_MSSQL_DB_IDX, segment_name) - 1,
		output_function, output_control);
}
/*	***********************************************************************	*/

