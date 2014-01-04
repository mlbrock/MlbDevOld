/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs 'DBC_SYB_IDX' structures to the specified
								output handler.

	Revision History	:	1996-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dbcsybi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_SYB_EMIT_IndexList

   SYNOPSIS    :	void DBC_SYB_EMIT_IndexList(count, list, output_function,
							output_control);

						unsigned int           count;

						const DBC_SYB_IDX     *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a list of ''DBC_SYB_IDX'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DBC_SYB_IDX'' structures
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

   NOTES       :	This function emits the list of ''DBC_SYB_IDX'' structures
						with column headers and trailers. If you do not want this
						behavior, you must call the related function
						``DBC_SYB_EMIT_Index`` for each array element.

						You can emit the list of ''DBC_SYB_IDX'' structures prefaced
						by the index within the list by using the related function
						``DBC_SYB_EMIT_IndexListIdx``.

   CAVEATS     :	

   SEE ALSO    :	DBC_SYB_EMIT_IndexListIdx
						DBC_SYB_EMIT_Index
						DBC_SYB_EMIT_IndexHeader
						DBC_SYB_EMIT_IndexTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_SYB_EMIT_IndexList
						Emit Functions:Data Cache Functions:DBC_SYB_EMIT_IndexList
						Data Cache Functions:Emit Functions:DBC_SYB_EMIT_IndexList

   PUBLISH XREF:	DBC_SYB_EMIT_IndexList

   PUBLISH NAME:	DBC_SYB_EMIT_IndexList

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_SYB_EMIT_IndexList(unsigned int count, const DBC_SYB_IDX *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void DBC_SYB_EMIT_IndexList(count, list, output_function, output_control)
unsigned int           count;
const DBC_SYB_IDX     *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	DBC_SYB_EMIT_IndexHeader(output_function, output_control);
	DBC_SYB_EMIT_IndexTrailer(output_function, output_control);

	while (count--)
		DBC_SYB_EMIT_Index(list++, output_function, output_control);

	DBC_SYB_EMIT_IndexTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_SYB_EMIT_IndexListIdx

   SYNOPSIS    :	void DBC_SYB_EMIT_IndexListIdx(count, list, output_function,
							output_control);

						unsigned int           count;

						const DBC_SYB_IDX     *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a list of ''DBC_SYB_IDX'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

						Each element of ``list`` is emited by this function prefaced
						by the six-digit, zero-filled index of the element in the
						``list``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DBC_SYB_IDX'' structures
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

   NOTES       :	You can emit the list of ''DBC_SYB_IDX'' structures without
						the prefaced index by using the related function
						``DBC_SYB_EMIT_IndexList``.
	
   CAVEATS     :	

   SEE ALSO    :	DBC_SYB_EMIT_IndexList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_SYB_EMIT_IndexListIdx
						Emit Functions:Data Cache Functions:DBC_SYB_EMIT_IndexListIdx
						Data Cache Functions:Emit Functions:DBC_SYB_EMIT_IndexListIdx

   PUBLISH XREF:	DBC_SYB_EMIT_IndexListIdx

   PUBLISH NAME:	DBC_SYB_EMIT_IndexListIdx

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_SYB_EMIT_IndexListIdx(unsigned int count,
	const DBC_SYB_IDX *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void DBC_SYB_EMIT_IndexListIdx(count, list, output_function, output_control)
unsigned int           count;
const DBC_SYB_IDX     *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "Index  ");
	DBC_SYB_EMIT_IndexHeader(output_function, output_control);

	(*output_function)(output_control, "------ ");
	DBC_SYB_EMIT_IndexTrailer(output_function, output_control);

	for (count_1 = 0; count_1 < count; count_1++) {
		(*output_function)(output_control, "%06u ", count_1);
		DBC_SYB_EMIT_Index(list++, output_function, output_control);
	}

	(*output_function)(output_control, "------ ");
	DBC_SYB_EMIT_IndexTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_SYB_EMIT_Index

   SYNOPSIS    :	void DBC_SYB_EMIT_Index(ptr, output_function,
							output_control);

						const DBC_SYB_IDX     *ptr;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a single ''DBC_SYB_IDX'' structure to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` is a pointer to the ''DBC_SYB_IDX'' structure
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

   NOTES       :	To emit an array of ''DBC_SYB_IDX'' structures, use the
						related function ``DBC_SYB_EMIT_IndexList``.

   CAVEATS     :	

   SEE ALSO    :	DBC_SYB_EMIT_IndexList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_SYB_EMIT_Index
						Emit Functions:Data Cache Functions:DBC_SYB_EMIT_Index
						Data Cache Functions:Emit Functions:DBC_SYB_EMIT_Index

   PUBLISH XREF:	DBC_SYB_EMIT_Index

   PUBLISH NAME:	DBC_SYB_EMIT_Index

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_SYB_EMIT_Index(const DBC_SYB_IDX *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void DBC_SYB_EMIT_Index(ptr, output_function, output_control)
const DBC_SYB_IDX     *ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %11d %11d %11d %-6.6s %-5.5s %-13.13s %-13.13s %-12.12s %11d \
%-*.*s %11u %10u\n",
		sizeof(ptr->index_name) - 1,
		sizeof(ptr->index_name) - 1,
		ptr->index_name,
		ptr->index_id,
		ptr->key_count,
		ptr->status,
		(ptr->unique_index_flag)    ? "YES" : "NO",
		(ptr->clustered_index_flag) ? "YES" : "NO",
		(ptr->ignore_dup_key_flag)  ? "YES" : "NO",
		(ptr->ignore_dup_row_flag)  ? "YES" : "NO",
		(ptr->allow_dup_row_flag)   ? "YES" : "NO",
		ptr->segment_number,
		sizeof(ptr->segment_name) - 1,
		sizeof(ptr->segment_name) - 1,
		ptr->segment_name,
		ptr->fill_factor,
		ptr->column_count);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_SYB_EMIT_IndexHeader

   SYNOPSIS    :	void DBC_SYB_EMIT_IndexHeader(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column header suitable for use with the output
						which results from the functions ``DBC_SYB_EMIT_Index``,
						``DBC_SYB_EMIT_IndexList`` and
						``DBC_SYB_EMIT_IndexListIdx``.

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
						``DBC_SYB_EMIT_IndexTrailer``.

   CAVEATS     :	

   SEE ALSO    :	DBC_SYB_EMIT_IndexTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_SYB_EMIT_IndexHeader
						Emit Functions:Data Cache Functions:DBC_SYB_EMIT_IndexHeader
						Data Cache Functions:Emit Functions:DBC_SYB_EMIT_IndexHeader

   PUBLISH XREF:	DBC_SYB_EMIT_IndexHeader

   PUBLISH NAME:	DBC_SYB_EMIT_IndexHeader

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_SYB_EMIT_IndexHeader(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void DBC_SYB_EMIT_IndexHeader(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %-11.11s %-11.11s %-11.11s %-6.6s %-5.5s %-13.13s %-13.13s \
%-12.12s %-11.11s %-*.*s %-11.11s %-10.10s\n",
		STR_sizeof(DBC_SYB_IDX, index_name) - 1,
		STR_sizeof(DBC_SYB_IDX, index_name) - 1,
		"Index Name",
		"Index Id",
		"Key Count",
		"Status",
		"Unique",
		"Clust",
		"Ignore DupKey",
		"Ignore DupRow",
		"Allow DupRow",
		"Segment #",
		STR_sizeof(DBC_SYB_IDX, segment_name) - 1,
		STR_sizeof(DBC_SYB_IDX, segment_name) - 1,
		"Segment Name",
		"Fill Factor",
		"Columns");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_SYB_EMIT_IndexTrailer

   SYNOPSIS    :	void DBC_SYB_EMIT_IndexTrailer(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column trailer suitable for use with the output
						which results from the functions ``DBC_SYB_EMIT_Index``,
						``DBC_SYB_EMIT_IndexList`` and
						``DBC_SYB_EMIT_IndexListIdx``.

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
						``DBC_SYB_EMIT_IndexHeader``.

   CAVEATS     :	

   SEE ALSO    :	DBC_SYB_EMIT_IndexHeader

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_SYB_EMIT_IndexTrailer
						Emit Functions:Data Cache Functions:DBC_SYB_EMIT_IndexTrailer
						Data Cache Functions:Emit Functions:DBC_SYB_EMIT_IndexTrailer

   PUBLISH XREF:	DBC_SYB_EMIT_IndexTrailer

   PUBLISH NAME:	DBC_SYB_EMIT_IndexTrailer

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_SYB_EMIT_IndexTrailer(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void DBC_SYB_EMIT_IndexTrailer(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_CharSpace('-', STR_sizeof(DBC_SYB_IDX, index_name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-',  6, output_function, output_control);
	STR_EMIT_CharSpace('-',  5, output_function, output_control);
	STR_EMIT_CharSpace('-', 13, output_function, output_control);
	STR_EMIT_CharSpace('-', 13, output_function, output_control);
	STR_EMIT_CharSpace('-', 12, output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharSpace('-', STR_sizeof(DBC_SYB_IDX, segment_name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-', 11, output_function, output_control);
	STR_EMIT_CharLine('-', 10, output_function, output_control);
}
/*	***********************************************************************	*/

