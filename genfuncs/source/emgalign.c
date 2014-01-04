/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs 'GEN_ALIGN' structures to the specified
								output handler.

	Revision History	:	1992-02-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_EMIT_AlignList

   SYNOPSIS    :	void GEN_EMIT_AlignList(count, list, output_function,
							output_control);

						unsigned int      count;

						const GEN_ALIGN  *list;

						void            (*output_function)(void *, char *, ...);

						void             *output_control;

   DESCRIPTION :	Emits a list of ''GEN_ALIGN'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''GEN_ALIGN'' which is to be
						emitted by this function.

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

   NOTES       :	This function emits the list of ''GEN_ALIGN'' structures
						with column headers and trailers. If you do not want this
						behavior, you must call the related function
						``GEN_EMIT_Align`` for each array element.

						You can emit the list of ''GEN_ALIGN'' structures prefaced
						by the index within the list by using
						``GEN_EMIT_AlignListIdx``.

   CAVEATS     :	

   SEE ALSO    :	GEN_EMIT_AlignListIdx
						GEN_EMIT_Align
						GEN_EMIT_AlignHeader
						GEN_EMIT_AlignTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_EMIT_AlignList
						Emit Functions:GEN_EMIT_AlignList
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_EMIT_AlignList

   PUBLISH NAME:	GEN_EMIT_AlignList

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_EMIT_AlignList(unsigned int count, const GEN_ALIGN *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void GEN_EMIT_AlignList(count, list, output_function, output_control)
unsigned int           count;
const GEN_ALIGN       *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	GEN_EMIT_AlignHeader(output_function, output_control);
	GEN_EMIT_AlignTrailer(output_function, output_control);

	while (count--)
		GEN_EMIT_Align(list++, output_function, output_control);

	GEN_EMIT_AlignTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_EMIT_AlignListIdx

   SYNOPSIS    :	void GEN_EMIT_AlignListIdx(count, list,
							output_function, output_control);

						unsigned int      count;

						const GEN_ALIGN  *list;

						void            (*output_function)(void *, char *, ...);

						void             *output_control;

   DESCRIPTION :	Emits a list of ''GEN_ALIGN'' structures to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

						Each element of ``list`` is emited by this function prefaced
						by the six-digit, zero-filled index of the element in the
						``list``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``count`` is the number of elements in the array
						``list``.

						(.) ``list`` is the array of ''GEN_ALIGN'' which is to be
						emitted by this function.

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

   NOTES       :	You can emit the list of ''GEN_ALIGN'' structures without
						the prefaced index by using ``GEN_EMIT_AlignList``.

   CAVEATS     :	

   SEE ALSO    :	GEN_EMIT_AlignList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_EMIT_AlignListIdx
						Emit Functions:GEN_EMIT_AlignListIdx
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_EMIT_AlignListIdx

   PUBLISH NAME:	GEN_EMIT_AlignListIdx

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_EMIT_AlignListIdx(unsigned int count, const GEN_ALIGN *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void GEN_EMIT_AlignListIdx(count, list, output_function,
	output_control)
unsigned int           count;
const GEN_ALIGN       *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "Index  ");
	GEN_EMIT_AlignHeader(output_function, output_control);

	(*output_function)(output_control, "------ ");
	GEN_EMIT_AlignTrailer(output_function, output_control);

	for (count_1 = 0; count_1 < count; count_1++) {
		(*output_function)(output_control, "%06u ", count_1);
		GEN_EMIT_Align(list++, output_function, output_control);
	}

	(*output_function)(output_control, "------ ");
	GEN_EMIT_AlignTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_EMIT_Align

   SYNOPSIS    :	void GEN_EMIT_Align(ptr, output_function,
							output_control);

						const GEN_ALIGN  *ptr;

						void            (*output_function)(void *, char *, ...);

						void             *output_control;

   DESCRIPTION :	Emits a single ''GEN_ALIGN'' structure to the specified
						output handler. The structure members are emitted in
						human-readable columnar output.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``ptr`` is a pointer to the ''GEN_ALIGN'' structure
						which is to be emitted by this function.

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

   NOTES       :	To emit an array of ''GEN_ALIGN'' structures, use the
						related function ``GEN_EMIT_AlignList``.

   CAVEATS     :	

   SEE ALSO    :	GEN_EMIT_AlignList

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_EMIT_Align
						Emit Functions:GEN_EMIT_Align
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_EMIT_Align

   PUBLISH NAME:	GEN_EMIT_Align

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_EMIT_Align(const GEN_ALIGN *ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void GEN_EMIT_Align(ptr, output_function, output_control)
const GEN_ALIGN       *ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
		"%10u %-16.16s %c         %10u %10u %10u\n",
		ptr->type,
		GEN_ALIGN_TypeList[ptr->type].type_name,
		GEN_ALIGN_TypeList[ptr->type].type_abbreviation,
		ptr->array_length,
		ptr->offset,
		ptr->length);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_EMIT_AlignHeader

   SYNOPSIS    :	void GEN_EMIT_AlignHeader(output_function,
							output_control);

						void (*output_function)(void *, char *, ...);

						void  *output_control;

   DESCRIPTION :	Emits a column header suitable for use with the output
						which results from the functions ``GEN_EMIT_Align``
						and ``GEN_EMIT_Align``.

   PARAMETERS  :	Parameters to this function are as follow:

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

   NOTES       :	You can emit a trailer by calling the related function
						``GEN_EMIT_AlignTrailer``.

   CAVEATS     :	

   SEE ALSO    :	GEN_EMIT_AlignTrailer

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_EMIT_AlignHeader
						Emit Functions:GEN_EMIT_AlignHeader
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_EMIT_AlignHeader

   PUBLISH NAME:	GEN_EMIT_AlignHeader

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_EMIT_AlignHeader(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void GEN_EMIT_AlignHeader(output_function, output_control)
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

   NAME        :	GEN_EMIT_AlignTrailer

   SYNOPSIS    :	void GEN_EMIT_AlignTrailer(output_function,
							output_control);

						void (*output_function)(void *, char *, ...);

						void  *output_control;

   DESCRIPTION :	Emits a column trailer suitable for use with the output
						which results from the functions ``GEN_EMIT_Align``
						and ``GEN_EMIT_Align``.

   PARAMETERS  :	Parameters to this function are as follow:

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

   NOTES       :	You can emit a headerer by calling the related function
						``GEN_EMIT_AlignHeader``.

   CAVEATS     :	

   SEE ALSO    :	GEN_EMIT_AlignHeader

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_EMIT_AlignTrailer
						Emit Functions:GEN_EMIT_AlignTrailer
						General Functions:see GENFUNCS

   PUBLISH XREF:	GEN_EMIT_AlignTrailer

   PUBLISH NAME:	GEN_EMIT_AlignTrailer

	ENTRY CLASS	:	Emit Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_EMIT_AlignTrailer(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void GEN_EMIT_AlignTrailer(output_function, output_control)
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

