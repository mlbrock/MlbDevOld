/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs 'DBC_SYB_DB_DB' structures to the specified
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

#include "dbcsybi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_SYB_EMIT_DBDBList

   SYNOPSIS    :	void DBC_SYB_EMIT_DBDBList(count, list, output_function,
							output_control);

						unsigned int           count;

						const DBC_SYB_DB_DB   *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a list of ''DBC_SYB_DB_DB'' structures to the
						specified output handler. The structure members are emitted
						in human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DBC_SYB_DB_DB'' structures
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

   NOTES       :	This function emits the list of ''DBC_SYB_DB_DB'' structures
						with column headers and trailers. If you do not want this
						behavior, you must call the related function
						``DBC_SYB_EMIT_DBDB`` for each array element.

						You can emit the list of ''DBC_SYB_DB_DB'' structures
						prefaced by the index within the list by using the related
						function ``DBC_SYB_EMIT_DBDBListIdx``.

   CAVEATS     :	

   SEE ALSO    :	DBC_SYB_EMIT_DBDBListIdx
						DBC_SYB_EMIT_DBDB
						DBC_SYB_EMIT_DBDBHeader
						DBC_SYB_EMIT_DBDBTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_SYB_EMIT_DBDBList
						Emit Functions:Data Cache Functions:DBC_SYB_EMIT_DBDBList
						Data Cache Functions:Emit Functions:DBC_SYB_EMIT_DBDBList

   PUBLISH XREF:	DBC_SYB_EMIT_DBDBList

   PUBLISH NAME:	DBC_SYB_EMIT_DBDBList

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_SYB_EMIT_DBDBList(unsigned int count, const DBC_SYB_DB_DB *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void DBC_SYB_EMIT_DBDBList(count, list, output_function, output_control)
unsigned int           count;
const DBC_SYB_DB_DB   *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	DBC_SYB_EMIT_DBDBHeader(output_function, output_control);
	DBC_SYB_EMIT_DBDBTrailer(output_function, output_control);

	while (count--)
		DBC_SYB_EMIT_DBDB(list++, output_function, output_control);

	DBC_SYB_EMIT_DBDBTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_SYB_EMIT_DBDBListIdx

   SYNOPSIS    :	void DBC_SYB_EMIT_DBDBListIdx(count, list, output_function,
							output_control);

						unsigned int           count;

						const DBC_SYB_DB_DB   *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a list of ''DBC_SYB_DB_DB'' structures to the
						specified output handler. The structure members are emitted
						in human-readable columnar output.

						Each element of ``list`` is emited by this function prefaced
						by the six-digit, zero-filled index of the element in the
						``list``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DBC_SYB_DB_DB'' structures
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

   NOTES       :	You can emit the list of ''DBC_SYB_DB_DB'' structures
						without the prefaced index by using the related function
						``DBC_SYB_EMIT_DBDBList``.
	
   CAVEATS     :	

   SEE ALSO    :	DBC_SYB_EMIT_DBDBList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_SYB_EMIT_DBDBListIdx
						Emit Functions:Data Cache Functions:DBC_SYB_EMIT_DBDBListIdx
						Data Cache Functions:Emit Functions:DBC_SYB_EMIT_DBDBListIdx

   PUBLISH XREF:	DBC_SYB_EMIT_DBDBListIdx

   PUBLISH NAME:	DBC_SYB_EMIT_DBDBListIdx

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_SYB_EMIT_DBDBListIdx(unsigned int count,
	const DBC_SYB_DB_DB *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void DBC_SYB_EMIT_DBDBListIdx(count, list, output_function, output_control)
unsigned int           count;
const DBC_SYB_DB_DB   *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "Index  ");
	DBC_SYB_EMIT_DBDBHeader(output_function, output_control);

	(*output_function)(output_control, "------ ");
	DBC_SYB_EMIT_DBDBTrailer(output_function, output_control);

	for (count_1 = 0; count_1 < count; count_1++) {
		(*output_function)(output_control, "%06u ", count_1);
		DBC_SYB_EMIT_DBDB(list++, output_function, output_control);
	}

	(*output_function)(output_control, "------ ");
	DBC_SYB_EMIT_DBDBTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_SYB_EMIT_DBDB

   SYNOPSIS    :	void DBC_SYB_EMIT_DBDB(ptr, output_function, output_control);

						const DBC_SYB_DB_DB   *ptr;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a single ''DBC_SYB_DB_DB'' structure to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` is a pointer to the ''DBC_SYB_DB_DB'' structure
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

   NOTES       :	To emit an array of ''DBC_SYB_DB_DB'' structures, use the
						related function ``DBC_SYB_EMIT_DBDBList``.

   CAVEATS     :	

   SEE ALSO    :	DBC_SYB_EMIT_DBDBList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_SYB_EMIT_DBDB
						Emit Functions:Data Cache Functions:DBC_SYB_EMIT_DBDB
						Data Cache Functions:Emit Functions:DBC_SYB_EMIT_DBDB

   PUBLISH XREF:	DBC_SYB_EMIT_DBDB

   PUBLISH NAME:	DBC_SYB_EMIT_DBDB

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_SYB_EMIT_DBDB(const DBC_SYB_DB_DB *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void DBC_SYB_EMIT_DBDB(ptr, output_function, output_control)
const DBC_SYB_DB_DB   *ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %5u %7u %6u %7u 0X%08lX %-18.18s %-18.18s\n",
		sizeof(ptr->name) - 1,
		sizeof(ptr->name) - 1,
		ptr->name,
		((unsigned short) ptr->dbid),
		((unsigned short) ptr->suid),
		((unsigned short) ptr->status),
		((unsigned short) ptr->version),
		((unsigned long) ptr->logptr),
		"CREATION-DATE",
		"DUMP-TRANS-DATE");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_SYB_EMIT_DBDBHeader

   SYNOPSIS    :	void DBC_SYB_EMIT_DBDBHeader(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column header suitable for use with the output
						which results from the functions ``DBC_SYB_EMIT_DBDB``,
						``DBC_SYB_EMIT_DBDBList`` and ``DBC_SYB_EMIT_DBDBListIdx``.

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
						``DBC_SYB_EMIT_DBDBTrailer``.

   CAVEATS     :	

   SEE ALSO    :	DBC_SYB_EMIT_DBDBTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_SYB_EMIT_DBDBHeader
						Emit Functions:Data Cache Functions:DBC_SYB_EMIT_DBDBHeader
						Data Cache Functions:Emit Functions:DBC_SYB_EMIT_DBDBHeader

   PUBLISH XREF:	DBC_SYB_EMIT_DBDBHeader

   PUBLISH NAME:	DBC_SYB_EMIT_DBDBHeader

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_SYB_EMIT_DBDBHeader(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void DBC_SYB_EMIT_DBDBHeader(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-*.*s %-5.5s %-7.7s %-6.6s %-7.7s %-10.10s %-18.18s %-18.18s\n",
		STR_sizeof(DBC_SYB_DB_DB, name) - 1,
		STR_sizeof(DBC_SYB_DB_DB, name) - 1,
		"Name",
		"Id",
		"User ID",
		"Status",
		"Version",
		"Log Ptr",
		"Creation Date",
		"Dump Trans Date");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_SYB_EMIT_DBDBTrailer

   SYNOPSIS    :	void DBC_SYB_EMIT_DBDBTrailer(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column trailer suitable for use with the output
						which results from the functions ``DBC_SYB_EMIT_DBDB``,
						``DBC_SYB_EMIT_DBDBList`` and ``DBC_SYB_EMIT_DBDBListIdx``.

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
						``DBC_SYB_EMIT_DBDBHeader``.

   CAVEATS     :	

   SEE ALSO    :	DBC_SYB_EMIT_DBDBHeader

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_SYB_EMIT_DBDBTrailer
						Emit Functions:Data Cache Functions:DBC_SYB_EMIT_DBDBTrailer
						Data Cache Functions:Emit Functions:DBC_SYB_EMIT_DBDBTrailer

   PUBLISH XREF:	DBC_SYB_EMIT_DBDBTrailer

   PUBLISH NAME:	DBC_SYB_EMIT_DBDBTrailer

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_SYB_EMIT_DBDBTrailer(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void DBC_SYB_EMIT_DBDBTrailer(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_CharSpace('-', STR_sizeof(DBC_SYB_DB_DB, name) - 1,
		output_function, output_control);
	STR_EMIT_CharSpace('-',  5, output_function, output_control);
	STR_EMIT_CharSpace('-',  7, output_function, output_control);
	STR_EMIT_CharSpace('-',  6, output_function, output_control);
	STR_EMIT_CharSpace('-',  7, output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-', 18, output_function, output_control);
	STR_EMIT_CharLine('-', 18, output_function, output_control);
}
/*	***********************************************************************	*/

