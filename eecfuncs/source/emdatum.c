/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Expression Evaluation Calculator Library (EECFUNCS) Library Module		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1996-02-07 --- Version 5.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <ctype.h>
#include <stdio.h>

#include "eecfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EMIT_DatumPtr(const EEC_DATUM *datum_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void EEC_EMIT_DatumPtr(datum_ptr, output_function, output_control)
const EEC_DATUM       *datum_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "%6.6s ",
		(datum_ptr->flags & EEC_EVAL_FLAG_TYPE_NUMBER) ? "Number" :
		(datum_ptr->flags & EEC_EVAL_FLAG_TYPE_STRING) ? "String" : "N/A");
	(*output_function)(output_control, "%c   /%c /%c  /%c     ",
		(datum_ptr->flags & EEC_EVAL_FLAG_TYPE_NULL) ? 'Y' : 'N',
		(datum_ptr->flags & EEC_EVAL_FLAG_TYPE_NA)   ? 'Y' : 'N',
		(datum_ptr->flags & EEC_EVAL_FLAG_TYPE_ERR)  ? 'Y' : 'N',
		(datum_ptr->flags & EEC_EVAL_FLAG_ALLOCED)   ? 'Y' : 'N');
	if (datum_ptr->flags & EEC_EVAL_FLAG_TYPE_STRING) {
		(*output_function)(output_control, "%6u ",
			datum_ptr->datum.string.length);
		EEC_EMIT_HumanString(datum_ptr->datum.string.length,
			datum_ptr->datum.string.data, EEC_FALSE, 39, output_function,
			output_control);
	}
	else {
		(*output_function)(output_control, "N/A    ");
		if (datum_ptr->flags & EEC_EVAL_FLAG_TYPE_NUMBER)
			(*output_function)(output_control, "%39.9f",
				datum_ptr->datum.number);
	}
	(*output_function)(output_control, "\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EMIT_DatumStack(unsigned int datum_count, const EEC_DATUM *datum_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void EEC_EMIT_DatumStack(datum_count, datum_list, output_function,
	output_control)
unsigned int           datum_count;
const EEC_DATUM       *datum_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	EEC_EMIT_DatumHeader(output_function, output_control);

	while (datum_count) {
		(*output_function)(output_control, "%05u ", datum_count - 1);
		EEC_EMIT_DatumPtr(datum_list + (datum_count - 1), output_function,
			output_control);
		datum_count--;
	}

	EEC_EMIT_DatumTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EMIT_DatumList(unsigned int datum_count, const EEC_DATUM *datum_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void EEC_EMIT_DatumList(datum_count, datum_list, output_function,
	output_control)
unsigned int           datum_count;
const EEC_DATUM       *datum_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	EEC_EMIT_DatumHeader(output_function, output_control);

	for (count_1 = 0; count_1 < datum_count; count_1++) {
		(*output_function)(output_control, "%05u ", count_1);
		EEC_EMIT_DatumPtr(datum_list + datum_count, output_function,
			output_control);
	}

	EEC_EMIT_DatumTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EMIT_DatumHeader(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void EEC_EMIT_DatumHeader(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "%s\n",
		"Index Type   NULL/NA/ERR/ALLOC Length Value");
	EEC_EMIT_DatumTrailer(output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EMIT_DatumTrailer(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void EEC_EMIT_DatumTrailer(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	STR_EMIT_CharSpace('-',  5, output_function, output_control);
	STR_EMIT_CharSpace('-',  6, output_function, output_control);
	STR_EMIT_CharSpace('-', 17, output_function, output_control);
	STR_EMIT_CharSpace('-',  6, output_function, output_control);
	STR_EMIT_CharLine('-', 39, output_function, output_control);
}
/*	***********************************************************************	*/

