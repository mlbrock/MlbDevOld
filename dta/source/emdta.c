/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Type Alignment (DTA) Functions Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs 'DTA' structures to the specified
								output handler.

	Revision History	:	1992-02-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dtai.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DTA_BASIC_EmitAlignList

   SYNOPSIS    :	void DTA_BASIC_EmitAlignList(type_count, type_list, count,
							list, output_function, output_control);

						unsigned int           type_count;

						const DTA_TYPE        *type_list;

						unsigned int           count;

						const DTA             *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a list of ''DTA'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''DTA_TYPE''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``dtadata.c``
						under the names ``DTA_TypeCount`` and ``DTA_TypeList``.

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DTA'' which is to be
						emitted by this function.

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

   NOTES       :	This function emits the list of ''DTA'' structures
						with column headers and trailers. If you do not want this
						behavior, you must call the related function
						``DTA_BASIC_EmitAlign`` for each array element.

						You can emit the list of ''DTA'' structures prefaced
						by the index within the list by using
						``DTA_BASIC_EmitAlignListIdx``.

   CAVEATS     :	

   SEE ALSO    :	DTA_EmitAlignList
						DTA_BASIC_EmitAlignListIdx
						DTA_BASIC_EmitAlign
						DTA_EmitAlignHeader
						DTA_EmitAlignTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_EmitAlignList
						Data Type Alignment Functions:DTA_BASIC_EmitAlignList
						Emit Functions:DTA_BASIC_EmitAlignList

   PUBLISH XREF:	DTA_BASIC_EmitAlignList

   PUBLISH NAME:	DTA_BASIC_EmitAlignList

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DTA_BASIC_EmitAlignList(unsigned int type_count, const DTA_TYPE *type_list,
	unsigned int count, const DTA *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void DTA_BASIC_EmitAlignList(type_count, type_list, count, list,
	output_function, output_control)
unsigned int           type_count;
const DTA_TYPE        *type_list;
unsigned int           count;
const DTA             *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	DTA_EmitAlignHeader(output_function, output_control);
	DTA_EmitAlignTrailer(output_function, output_control);

	while (count--)
		DTA_BASIC_EmitAlign(type_count, type_list, list++, output_function,
			output_control);

	DTA_EmitAlignTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DTA_BASIC_EmitAlignListIdx

   SYNOPSIS    :	void DTA_BASIC_EmitAlignListIdx(type_count, type_list,
							count, list, output_function, output_control);

						unsigned int           type_count;

						const DTA_TYPE        *type_list;

						unsigned int           count;

						const DTA             *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a list of ''DTA'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

						Each element of ``list`` is emited by this function prefaced
						by the six-digit, zero-filled index of the element in the
						``list``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''DTA_TYPE''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``dtadata.c``
						under the names ``DTA_TypeCount`` and ``DTA_TypeList``.

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DTA'' which is to be
						emitted by this function.

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

   NOTES       :	You can emit the list of ''DTA'' structures without
						the prefaced index by using ``DTA_BASIC_EmitAlignList``.

   CAVEATS     :	

   SEE ALSO    :	DTA_EmitAlignListIdx
						DTA_BASIC_EmitAlignList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_EmitAlignListIdx
						Data Type Alignment Functions:DTA_BASIC_EmitAlignListIdx
						Emit Functions:DTA_BASIC_EmitAlignListIdx

   PUBLISH XREF:	DTA_BASIC_EmitAlignListIdx

   PUBLISH NAME:	DTA_BASIC_EmitAlignListIdx

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DTA_BASIC_EmitAlignListIdx(unsigned int type_count,
	const DTA_TYPE *type_list, unsigned int count, const DTA *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void DTA_BASIC_EmitAlignListIdx(type_count, type_list, count, list,
	output_function, output_control)
unsigned int           type_count;
const DTA_TYPE        *type_list;
unsigned int           count;
const DTA             *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "Index  ");
	DTA_EmitAlignHeader(output_function, output_control);

	(*output_function)(output_control, "------ ");
	DTA_EmitAlignTrailer(output_function, output_control);

	for (count_1 = 0; count_1 < count; count_1++) {
		(*output_function)(output_control, "%06u ", count_1);
		DTA_BASIC_EmitAlign(type_count, type_list, list++, output_function,
			output_control);
	}

	(*output_function)(output_control, "------ ");
	DTA_EmitAlignTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DTA_BASIC_EmitAlign

   SYNOPSIS    :	void DTA_BASIC_EmitAlign(type_ptr, ptr, output_function,
							output_control);

						unsigned int           type_count;

						const DTA_TYPE        *type_list;

						const DTA             *ptr;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a single ''DTA'' structure to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``type_count`` is the number of elements in the array
						represented by the ``type_list`` parameter.

						(.) ``type_list`` is an array of ''DTA_TYPE''
						structures which describe a machine architecture in terms
						of the primitive data types available on that architecture.

						(-) If ``type_count`` is ''0'' and ``type_list`` is
						''NULL'', the function will use the built-in primitive
						data type list compiled into the module ``dtadata.c``
						under the names ``DTA_TypeCount`` and ``DTA_TypeList``.

						(.) ``ptr`` is a pointer to the ''DTA'' structure
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

   NOTES       :	To emit an array of ''DTA'' structures, use the
						related function ``DTA_BASIC_EmitAlignList``.

   CAVEATS     :	

   SEE ALSO    :	DTA_EmitAlign
						DTA_BASIC_EmitAlignList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_BASIC_EmitAlign
						Data Type Alignment Functions:DTA_BASIC_EmitAlign
						Emit Functions:DTA_BASIC_EmitAlign

   PUBLISH XREF:	DTA_BASIC_EmitAlign

   PUBLISH NAME:	DTA_BASIC_EmitAlign

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DTA_BASIC_EmitAlign(unsigned int type_count, const DTA_TYPE *type_list,
	const DTA *ptr, STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void DTA_BASIC_EmitAlign(type_count, type_list, ptr, output_function,
	output_control)
unsigned int           type_count;
const DTA_TYPE        *type_list;
const DTA             *ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	DTA_GetTypeInfo(&type_count, &type_list);

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%10u %-16.16s %c         %10u %10u %10u\n",
		ptr->type,
		(ptr->type < type_count) ? type_list[ptr->type].type_name         :
			"*INVALID*",
		(ptr->type < type_count) ? type_list[ptr->type].type_abbreviation :
			'?',
		ptr->array_length,
		ptr->offset,
		ptr->length);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DTA_EmitAlignList

   SYNOPSIS    :	void DTA_EmitAlignList(count, list, output_function,
							output_control);

						unsigned int           count;

						const DTA             *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a list of ''DTA'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DTA'' which is to be
						emitted by this function.

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

   NOTES       :	This function emits the list of ''DTA'' structures
						with column headers and trailers. If you do not want this
						behavior, you must call the related function
						``DTA_EmitAlign`` for each array element.

						You can emit the list of ''DTA'' structures prefaced
						by the index within the list by using
						``DTA_EmitAlignListIdx``.

   CAVEATS     :	

   SEE ALSO    :	DTA_BASIC_EmitAlignList
						DTA_EmitAlignListIdx
						DTA_EmitAlign
						DTA_EmitAlignHeader
						DTA_EmitAlignTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_EmitAlignList
						Data Type Alignment Functions:DTA_EmitAlignList
						Emit Functions:DTA_EmitAlignList

   PUBLISH XREF:	DTA_EmitAlignList

   PUBLISH NAME:	DTA_EmitAlignList

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DTA_EmitAlignList(unsigned int count, const DTA *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void DTA_EmitAlignList(count, list, output_function, output_control)
unsigned int           count;
const DTA             *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	DTA_BASIC_EmitAlignList(0, NULL, count, list, output_function,
		output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DTA_EmitAlignListIdx

   SYNOPSIS    :	void DTA_EmitAlignListIdx(count, list,
							output_function, output_control);

						unsigned int           count;

						const DTA             *list;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a list of ''DTA'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

						Each element of ``list`` is emited by this function prefaced
						by the six-digit, zero-filled index of the element in the
						``list``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''DTA'' which is to be
						emitted by this function.

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

   NOTES       :	You can emit the list of ''DTA'' structures without
						the prefaced index by using ``DTA_EmitAlignList``.

   CAVEATS     :	

   SEE ALSO    :	DTA_BASIC_EmitAlignListIdx
						DTA_EmitAlignList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_EmitAlignListIdx
						Data Type Alignment Functions:DTA_EmitAlignListIdx
						Emit Functions:DTA_EmitAlignListIdx

   PUBLISH XREF:	DTA_EmitAlignListIdx

   PUBLISH NAME:	DTA_EmitAlignListIdx

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DTA_EmitAlignListIdx(unsigned int count, const DTA *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void DTA_EmitAlignListIdx(count, list, output_function,
	output_control)
unsigned int           count;
const DTA             *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	DTA_BASIC_EmitAlignListIdx(0, NULL, count, list, output_function,
		output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DTA_EmitAlign

   SYNOPSIS    :	void DTA_EmitAlign(ptr, output_function,
							output_control);

						const DTA             *ptr;

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a single ''DTA'' structure to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` is a pointer to the ''DTA'' structure
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

   NOTES       :	To emit an array of ''DTA'' structures, use the
						related function ``DTA_EmitAlignList``.

   CAVEATS     :	

   SEE ALSO    :	DTA_BASIC_EmitAlign
						DTA_EmitAlignList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_EmitAlign
						Data Type Alignment Functions:DTA_EmitAlign
						Emit Functions:DTA_EmitAlign

   PUBLISH XREF:	DTA_EmitAlign

   PUBLISH NAME:	DTA_EmitAlign

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DTA_EmitAlign(const DTA *ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void DTA_EmitAlign(ptr, output_function, output_control)
const DTA             *ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	DTA_BASIC_EmitAlign(0, NULL, ptr, output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DTA_EmitAlignHeader

   SYNOPSIS    :	void DTA_EmitAlignHeader(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column header suitable for use with the output
						which results from the functions ``DTA_EmitAlign``
						and ``DTA_EmitAlign``.

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
						``DTA_EmitAlignTrailer``.

   CAVEATS     :	

   SEE ALSO    :	DTA_EmitAlignTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_EmitAlignHeader
						Data Type Alignment Functions:DTA_EmitAlignHeader
						Emit Functions:DTA_EmitAlignHeader

   PUBLISH XREF:	DTA_EmitAlignHeader

   PUBLISH NAME:	DTA_EmitAlignHeader

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DTA_EmitAlignHeader(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void DTA_EmitAlignHeader(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%-10.10s %-16.16s %-9.9s %-10.10s %-10.10s %-10.10s\n",
		"Type Index",
		"Type Name",
		"Type Char",
		"Array Len",
		"Offset",
		"Length");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DTA_EmitAlignTrailer

   SYNOPSIS    :	void DTA_EmitAlignTrailer(output_function,
							output_control);

						STR_FUNC_TYPE_fprintf  output_function;

						void                  *output_control;

   DESCRIPTION :	Emits a column trailer suitable for use with the output
						which results from the functions ``DTA_EmitAlign``
						and ``DTA_EmitAlign``.

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

   NOTES       :	You can emit a headerer by calling the related function
						``DTA_EmitAlignHeader``.

   CAVEATS     :	

   SEE ALSO    :	DTA_EmitAlignHeader

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	DTA_EmitAlignTrailer
						Data Type Alignment Functions:DTA_EmitAlignTrailer
						Emit Functions:DTA_EmitAlignTrailer

   PUBLISH XREF:	DTA_EmitAlignTrailer

   PUBLISH NAME:	DTA_EmitAlignTrailer

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DTA_EmitAlignTrailer(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void DTA_EmitAlignTrailer(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-', 16, output_function, output_control);
	STR_EMIT_CharSpace('-',  9, output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharSpace('-', 10, output_function, output_control);
	STR_EMIT_CharLine('-', 10, output_function, output_control);
}
/*	***********************************************************************	*/

