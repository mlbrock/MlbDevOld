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

	Revision History	:	1991-11-27 --- Creation.
									Michael L. Brock
								1993-04-04 --- Version 4 changes.
									Michael L. Brock
								1996-01-29 --- Version 5 changes.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <string.h>

#include "parsedat.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EMIT_SubExprList(unsigned int count, const EEC_SUB_EXPR *list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void EEC_EMIT_SubExprList(count, list, output_function, output_control)
unsigned int           count;
const EEC_SUB_EXPR    *list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control,
"Index Expr Spec  Start      End        Type                        Flags\n");
	(*output_function)(output_control,
"----- ---------- ---------- ---------- --------------------------- -----\n");

	for (count_1 = 0; count_1 < count; count_1++) {
		(*output_function)(output_control, "%05u ", count_1);
		EEC_EMIT_SubExpr(list + count_1, output_function, output_control);
	}

	(*output_function)(output_control,
"----- ---------- ---------- ---------- --------------------------- -----\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EMIT_SubExpr(const EEC_SUB_EXPR *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void EEC_EMIT_SubExpr(ptr, output_function, output_control)
const EEC_SUB_EXPR    *ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	char type_buffer[64];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	if (ptr->expr_type == EEC_TYPE_BEGIN)
		strcpy(type_buffer, "Begin");
	else if (ptr->expr_type == EEC_TYPE_NUMBER)
		strcpy(type_buffer, "Number");
	else if (ptr->expr_type == EEC_TYPE_STRING)
		strcpy(type_buffer, "String");
	else if (ptr->expr_type ==
		(EEC_TYPE_OPERATOR | EEC_TYPE_NUMBER_OP | EEC_TYPE_NUMBER))
		sprintf(type_buffer, "NumberOp %s",
		EEC_OperatorList[((unsigned int) ptr->expr_spec)].preferred_operator);
	else if (ptr->expr_type == (EEC_TYPE_OPERATOR | EEC_TYPE_REL_OP))
		sprintf(type_buffer, "RelationalOp %s",
		EEC_OperatorList[((unsigned int) ptr->expr_spec)].preferred_operator);
	else if (ptr->expr_type == (EEC_TYPE_OPERATOR | EEC_TYPE_BOOL_OP))
		sprintf(type_buffer, "BooleanOp %s",
		EEC_OperatorList[((unsigned int) ptr->expr_spec)].preferred_operator);
	else if (ptr->expr_type ==
		(EEC_TYPE_OPERATOR | EEC_TYPE_STRING_OP | EEC_TYPE_STRING))
		sprintf(type_buffer, "StringOp %s",
		EEC_OperatorList[((unsigned int) ptr->expr_spec)].preferred_operator);
	else if (ptr->expr_type == EEC_TYPE_OPERATOR)
		strcpy(type_buffer, "Op");
	else if (ptr->expr_type == (EEC_TYPE_NUMBER | EEC_TYPE_FUNCTION))
		strcpy(type_buffer, "Numeric Function");
	else if (ptr->expr_type == (EEC_TYPE_STRING | EEC_TYPE_FUNCTION))
		strcpy(type_buffer, "String Function");
	else if (ptr->expr_type == EEC_TYPE_FUNCTION)
		strcpy(type_buffer, "? Function");
	else if (ptr->expr_type == (EEC_TYPE_NUMBER | EEC_TYPE_SYMBOL))
		strcpy(type_buffer, "Numeric Symbol");
	else if (ptr->expr_type == (EEC_TYPE_STRING | EEC_TYPE_SYMBOL))
		strcpy(type_buffer, "String Symbol");
	else if (ptr->expr_type == EEC_TYPE_SYMBOL)
		strcpy(type_buffer, "? Symbol");
	else if (ptr->expr_type == (EEC_TYPE_NUMBER | EEC_TYPE_PAREND))
		strcpy(type_buffer, "Numeric ()");
	else if (ptr->expr_type == (EEC_TYPE_STRING | EEC_TYPE_PAREND))
		strcpy(type_buffer, "String ()");
	else if (ptr->expr_type == EEC_TYPE_PAREND)
		strcpy(type_buffer, "? ()");
	else if (ptr->expr_type == EEC_TYPE_ANY)
		strcpy(type_buffer, "*******ANY*******");
	else if (ptr->expr_type == (EEC_TYPE_NUMBER | EEC_TYPE_POSTFIX))
		strcpy(type_buffer, "Numeric Post-fix");
	else if (ptr->expr_type == (EEC_TYPE_STRING | EEC_TYPE_POSTFIX))
		strcpy(type_buffer, "String Post-fix");
	else
		center(strcpy(type_buffer, "???"), 27);

	(*output_function)(output_control, "%10lu ", ptr->expr_spec);
	(*output_function)(output_control, "%10u ", ptr->start_index);
	(*output_function)(output_control, "%10u ", ptr->end_index);
	(*output_function)(output_control, "%-27.27s ", type_buffer);
	(*output_function)(output_control, "%5u\n", ptr->expr_flags);
}
/*	***********************************************************************	*/

