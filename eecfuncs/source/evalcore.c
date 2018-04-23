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

	Revision History	:	1991-12-12 --- Creation.
									Michael L. Brock
								1993-04-04 --- Version 4 changes.
									Michael L. Brock
								1996-02-05 --- Version 5 initial cut.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <math.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsedat.h"
#include "evaldefs.h"
#include "eecfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	To avoid Visual C++ 6.0 warnings about removed inline functions . . .	*/
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(disable:4514)
#endif /* #ifdef _MSC_VER */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_EvalIt(EEC_CONTROL *control_ptr, const EEC_POSTFIX *postfix_ptr,
	EEC_DATUM *result_ptr, char *error_text)
#else
int EEC_EvalIt(control_ptr, postfix_ptr, result_ptr, error_text)
EEC_CONTROL       *control_ptr;
const EEC_POSTFIX *postfix_ptr;
EEC_DATUM         *result_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	EEC_INIT_EEC_DATUM(result_ptr);

	if ((!postfix_ptr) || (!(*postfix_ptr->data)) || (!postfix_ptr->length)) {
		strcpy(error_text, "Empty formula expansion encountered.");
		return_code = EEC_FAILURE;
	}
	else {
		control_ptr->eval_data.eval_stack_top     =
			control_ptr->eval_data.eval_stack;
		control_ptr->eval_data.eval_stack_count   = 0;
		control_ptr->eval_data.postfix_ptr        = postfix_ptr;
		control_ptr->eval_data.postfix_data_index = 0;
		control_ptr->eval_data.postfix_data_ptr   = postfix_ptr->data;
		if ((return_code = EEC_EvalLoop(&control_ptr->eval_data, result_ptr)) !=
			EEC_SUCCESS)
			strcpy(error_text, control_ptr->eval_data.error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_EvalControl(const EEC_POSTFIX *postfix_ptr, EEC_DATUM *result_ptr,
	char *error_text)
#else
int EEC_EvalControl(postfix_ptr, result_ptr, error_text)
const EEC_POSTFIX *postfix_ptr;
EEC_DATUM         *result_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	EEC_EVAL_DATA eval_data;

	EEC_INIT_EEC_DATUM(result_ptr);

	if ((!postfix_ptr) || (!(*postfix_ptr->data)) || (!postfix_ptr->length)) {
		strcpy(error_text, "Empty formula expansion encountered.");
		return_code = EEC_FAILURE;
	}
	else {
		eval_data.eval_stack         = NULL;
		eval_data.eval_stack_top     = NULL;
		eval_data.error_text[0]      = '\0';
		eval_data.eval_stack_alloc   = 0;
		eval_data.eval_stack_count   = 0;
		eval_data.postfix_ptr        = postfix_ptr;
		eval_data.postfix_data_index = 0;
		eval_data.postfix_data_ptr   = eval_data.postfix_ptr->data;
		if ((return_code = EEC_EvalLoop(&eval_data, result_ptr)) !=
			EEC_SUCCESS)
			strcpy(error_text, eval_data.error_text);
		if (eval_data.eval_stack)
			free(eval_data.eval_stack);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_EvalLoop(EEC_EVAL_DATA *eval_ptr, EEC_DATUM *result_ptr)
#else
int EEC_EvalLoop(eval_ptr, result_ptr)
EEC_EVAL_DATA *eval_ptr;
EEC_DATUM     *result_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = EEC_SUCCESS;

	EEC_INIT_EEC_DATUM(result_ptr);

	if (!eval_ptr->postfix_ptr->length)
		result_ptr->flags = EEC_EVAL_FLAG_TYPE_NULL;
	else if ((return_code = EEC_EvalBasic(eval_ptr)) == EEC_SUCCESS) {
		if (eval_ptr->eval_stack_count != 1) {
			sprintf(eval_ptr->error_text, "%s %u %s.",
				"Evaluation of formula resulted in",
				(eval_ptr->eval_stack_count) ?
				eval_ptr->eval_stack_count + 1 : 0,
				"items remaining on evaluation stack");
			return_code = EEC_FAILURE;
		}
		else {
			if (EEC_EVAL_TOP_IS_STATIC(eval_ptr) == EEC_TRUE)
				EEC_EVAL_StaticToAlloced(eval_ptr, eval_ptr->eval_stack_top);
			*result_ptr                = *eval_ptr->eval_stack;
			eval_ptr->eval_stack_count = 0;
			eval_ptr->eval_stack_top   = eval_ptr->eval_stack;
			return_code                = EEC_SUCCESS;
		}
	}

	EEC_EVAL_StackClear(eval_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4611)
#endif /* #ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int EEC_EvalBasic(EEC_EVAL_DATA *eval_ptr)
#else
int EEC_EvalBasic(eval_ptr)
EEC_EVAL_DATA *eval_ptr;
#endif /* #ifndef NARGS */
{
	int                 return_code;
	unsigned short      arg_count;
	unsigned short      tmp_short;
	unsigned int        tmp_int;
   unsigned long       tmp_long;
	unsigned int        size;
	unsigned int        tmp_length;
	char               *tmp_ptr;
	double              tmp_double;
	unsigned int        builtin_func_def_count;
	const EEC_FUNC_DEF *builtin_func_def_list;

	eval_ptr->postfix_data_index = 0;
	eval_ptr->postfix_data_ptr   = eval_ptr->postfix_ptr->data;

	if ((return_code = setjmp(eval_ptr->jump_context)) != EEC_SUCCESS) {
		return_code = eval_ptr->return_code;
		goto EXIT_FUNCTION;
	}

	EEC_GetBuiltInFuncDefs(&builtin_func_def_count, &builtin_func_def_list);

	while (eval_ptr->postfix_data_index < eval_ptr->postfix_ptr->length) {
		size = 0;
		switch (*eval_ptr->postfix_data_ptr) {
			case	EEC_PFIX_TYPE_NUMBER		:
				ECC_GET_PFIX_NUMBER(eval_ptr->postfix_data_ptr, &tmp_double);
				EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				size = sizeof(double);
				break;
			case	EEC_PFIX_TYPE_STRING		:
				EEC_GET_PFIX_STRING(eval_ptr->postfix_data_ptr, &tmp_int,
					&tmp_ptr);
				EEC_EVAL_PUSH_STRING_STATIC(eval_ptr, tmp_int, tmp_ptr);
				size = sizeof(unsigned int) + tmp_int + 1;
				break;
			case	EEC_PFIX_TYPE_FUNCTION	:
				EEC_GET_PFIX_FUNCTION(eval_ptr->postfix_data_ptr, &tmp_long,
					&arg_count, &tmp_short, &tmp_ptr);
				if (tmp_long > ((unsigned long) USHRT_MAX)) {
					sprintf(eval_ptr->error_text, "%s '%-*.*s' failed --- %s.",
						"Attempt to invoke externally-defined function",
						((int) tmp_short), ((int) tmp_short), tmp_ptr,
						"externally-defined functions not yet implemented");
					return_code = EEC_FAILURE;
					goto EXIT_FUNCTION;
				}
				if (tmp_long >= ((unsigned long) builtin_func_def_count)) {
					sprintf(eval_ptr->error_text,
						"%s '%-*.*s' failed --- id is %lu, maximum is %u.",
						"Attempt to invoke built-in function",
						((int) tmp_short), ((int) tmp_short), tmp_ptr,
						tmp_long, builtin_func_def_count);
					return_code = EEC_FAILURE;
					goto EXIT_FUNCTION;
				}
				(*builtin_func_def_list[((unsigned int) tmp_long)].func_ptr)
					(eval_ptr, ((unsigned int) arg_count));
/*
fprintf(stderr, "ERROR      : Function encountered.\n");
fprintf(stderr, "ID         : %10lu\n", tmp_long);
fprintf(stderr, "ARG COUNT  : %10u\n", ((unsigned int) arg_count));
fprintf(stderr, "NAME LENGTH: %10u\n", ((unsigned int) tmp_short));
fprintf(stderr, "NAME STRING: %-*.*s\n",
	((int) tmp_short), ((int) tmp_short), tmp_ptr);
exit(-1);
*/
				size = sizeof(unsigned long) + (sizeof(unsigned short) * 2) +
					tmp_short;
				break;
			case	EEC_PFIX_TYPE_SYMBOL		:
				EEC_GET_PFIX_SYMBOL(eval_ptr->postfix_data_ptr, &tmp_long,
					&tmp_short, &tmp_ptr);
/*
fprintf(stderr, "ERROR      : Foreign name encountered.\n");
fprintf(stderr, "ID         : %10lu\n", tmp_long);
fprintf(stderr, "NAME LENGTH: %10u\n", ((unsigned int) tmp_short));
fprintf(stderr, "NAME STRING: %-*.*s\n",
	((int) tmp_short), ((int) tmp_short), tmp_ptr);
exit(-1);
*/
				if (eval_ptr->symbol_eval_func == NULL) {
					sprintf(eval_ptr->error_text, "Symbol id %lu %s.", tmp_long,
						"was encountered without a symbol evaluation function");
					return_code = EEC_FAILURE;
					goto EXIT_FUNCTION;
				}
				else if ((return_code = (*eval_ptr->symbol_eval_func)(eval_ptr,
					tmp_long, ((unsigned int) tmp_short), tmp_ptr,
					eval_ptr->symbol_eval_data, eval_ptr->error_text)) !=
					EEC_SUCCESS)
					goto EXIT_FUNCTION;
				size = sizeof(unsigned long) + sizeof(unsigned short) + tmp_short;
				break;
			case EEC_OPERATOR_OR			:
				/*	***********************************************************	*/
				/*	***********************************************************	*/
				/*		Note that we short-circuit 'OR' evaluation . . .			*/
				/*	***********************************************************	*/
				if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else if (EEC_EVAL_TREF_IS_NOT_EMPTY(eval_ptr, -1)) {
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, 1.0);
				}
				else if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else {
					tmp_double = (EEC_EVAL_TOP_IS_NOT_EMPTY(eval_ptr)) ? 1.0 : 0.0;
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_AND			:
				/*	***********************************************************	*/
				/*	***********************************************************	*/
				/*		Note that we short-circuit 'AND' evaluation . . .			*/
				/*	***********************************************************	*/
				if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else if (EEC_EVAL_TREF_IS_EMPTY(eval_ptr, -1)) {
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, 0.0);
				}
				else if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else {
					tmp_double = (EEC_EVAL_TOP_IS_NOT_EMPTY(eval_ptr)) ? 1.0 : 0.0;
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_NE			:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					if (eval_ptr->eval_stack_top->flags & EEC_TYPE_NUMBER)
						tmp_double = (eval_ptr->eval_stack_top[-1].datum.number !=
							eval_ptr->eval_stack_top->datum.number) ? 1.0 : 0.0;
					else
						tmp_double = ((double) EEC_EVAL_StringCmp(eval_ptr));
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_EQ			:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					if (eval_ptr->eval_stack_top->flags & EEC_TYPE_NUMBER)
						tmp_double = (eval_ptr->eval_stack_top[-1].datum.number ==
							eval_ptr->eval_stack_top->datum.number) ? 1.0 : 0.0;
					else
						tmp_double = (EEC_EVAL_StringCmp(eval_ptr)) ? 0.0 : 1.0;
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_LT			:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					if (eval_ptr->eval_stack_top->flags & EEC_TYPE_NUMBER)
						tmp_double = (eval_ptr->eval_stack_top[-1].datum.number <
							eval_ptr->eval_stack_top->datum.number) ? 1.0 : 0.0;
					else
						tmp_double = (EEC_EVAL_StringCmp(eval_ptr) < 0) ? 1.0 : 0.0;
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_LE			:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					if (eval_ptr->eval_stack_top->flags & EEC_TYPE_NUMBER)
						tmp_double = (eval_ptr->eval_stack_top[-1].datum.number <=
							eval_ptr->eval_stack_top->datum.number) ? 1.0 : 0.0;
					else
						tmp_double = (EEC_EVAL_StringCmp(eval_ptr) <= 0) ? 1.0 : 0.0;
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_GT			:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					if (eval_ptr->eval_stack_top->flags & EEC_TYPE_NUMBER)
						tmp_double = (eval_ptr->eval_stack_top[-1].datum.number >
							eval_ptr->eval_stack_top->datum.number) ? 1.0 : 0.0;
					else
						tmp_double = (EEC_EVAL_StringCmp(eval_ptr) > 0) ? 1.0 : 0.0;
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_GE			:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					if (eval_ptr->eval_stack_top->flags & EEC_TYPE_NUMBER)
						tmp_double = (eval_ptr->eval_stack_top[-1].datum.number >=
							eval_ptr->eval_stack_top->datum.number) ? 1.0 : 0.0;
					else
						tmp_double = (EEC_EVAL_StringCmp(eval_ptr) >= 0) ? 1.0 : 0.0;
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_MINUS		:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					tmp_double = eval_ptr->eval_stack_top[-1].datum.number -
						eval_ptr->eval_stack_top->datum.number;
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_PLUS			:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					tmp_double = eval_ptr->eval_stack_top[-1].datum.number +
						eval_ptr->eval_stack_top->datum.number;
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_MOD			:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					tmp_double = fmod(eval_ptr->eval_stack_top[-1].datum.number,
						eval_ptr->eval_stack_top->datum.number);
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_INT_DIVIDE	:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					if (!eval_ptr->eval_stack_top->datum.number)
						EEC_EVAL_ErrorJmp(eval_ptr, "EEC_EvalBasic",
							EEC_FAILURE, "Integer divide by zero attempt.");
					tmp_double = eval_ptr->eval_stack_top[-1].datum.number /
						eval_ptr->eval_stack_top->datum.number;
					tmp_double = (tmp_double < 0.0) ? ceil(tmp_double) :
						floor(tmp_double);
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_DIVIDE		:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					if (!eval_ptr->eval_stack_top->datum.number)
						EEC_EVAL_ErrorJmp(eval_ptr, "EEC_EvalBasic",
							EEC_FAILURE, "Divide by zero attempt.");
					tmp_double = eval_ptr->eval_stack_top[-1].datum.number /
						eval_ptr->eval_stack_top->datum.number;
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_MULTIPLY  	:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					tmp_double = eval_ptr->eval_stack_top[-1].datum.number *
						eval_ptr->eval_stack_top->datum.number;
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case EEC_OPERATOR_POWER		:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					tmp_double = pow(eval_ptr->eval_stack_top[-1].datum.number,
						eval_ptr->eval_stack_top->datum.number);
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, tmp_double);
				}
				break;
			case	EEC_OPERATOR_CONCAT		:
				if (EEC_EVAL_TOP_IS_SFLAG(eval_ptr)) {
					EEC_EVAL_StackSwap(eval_ptr);
					EEC_EVAL_StackPop(eval_ptr, 1);
				}
				else if (EEC_EVAL_TREF_IS_SFLAG(eval_ptr, -1))
					EEC_EVAL_StackPop(eval_ptr, 1);
				else {
					tmp_ptr = EEC_EVAL_StringAlloc(eval_ptr, tmp_length =
						(eval_ptr->eval_stack_top[-1].datum.string.length +
						eval_ptr->eval_stack_top->datum.string.length));
					memcpy(tmp_ptr,
						eval_ptr->eval_stack_top[-1].datum.string.data,
						eval_ptr->eval_stack_top[-1].datum.string.length);
					memcpy(tmp_ptr +
						eval_ptr->eval_stack_top[-1].datum.string.length,
						eval_ptr->eval_stack_top->datum.string.data,
						eval_ptr->eval_stack_top->datum.string.length);
					EEC_EVAL_StackPop(eval_ptr, 2);
					EEC_EVAL_ADD_STACK_INDEX(eval_ptr);
					eval_ptr->eval_stack_top->datum.string.length = tmp_length;
					eval_ptr->eval_stack_top->datum.string.data   = tmp_ptr;
					eval_ptr->eval_stack_top->flags               =
						EEC_EVAL_FLAG_TYPE_STRING | EEC_EVAL_FLAG_ALLOCED;
				}
				break;
			default	:
				sprintf(eval_ptr->error_text, "%s (character = %u).",
					"Unknown item encountered in post-fix string",
					((unsigned int)
					*((unsigned char *) eval_ptr->postfix_data_ptr)));
				return_code = EEC_FAILURE;
				goto EXIT_FUNCTION;
		}
		eval_ptr->postfix_data_index += size + 1;
		eval_ptr->postfix_data_ptr   += size + 1;
/*
EEC_EMIT_DatumStack(eval_ptr->eval_stack_count, eval_ptr->eval_stack,
	NULL, NULL);
*/
	}

EXIT_FUNCTION:

	eval_ptr->return_code = return_code;

	return(return_code);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4611)
#endif /* #ifdef _MSC_VER */

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_EVAL_StringCmp(EEC_EVAL_DATA *eval_ptr)
#else
int EEC_EVAL_StringCmp(eval_ptr)
EEC_EVAL_DATA *eval_ptr;
#endif /* #ifndef NARGS */
{
	char         *ptr_1;
	char         *ptr_2;
	unsigned int  length;

	ptr_1  = eval_ptr->eval_stack_top[-1].datum.string.data;
	ptr_2  = eval_ptr->eval_stack_top->datum.string.data;
	length = (eval_ptr->eval_stack_top[-1].datum.string.length <
		eval_ptr->eval_stack_top->datum.string.length) ?
		eval_ptr->eval_stack_top[-1].datum.string.length :
		eval_ptr->eval_stack_top->datum.string.length;

	for ( ; length; length--, ptr_1++, ptr_2++) {
		if (*ptr_1 != *ptr_2)
			return((*ptr_1 > *ptr_2) ? 1 : -1);
	}

	return((eval_ptr->eval_stack_top[-1].datum.string.length >
		eval_ptr->eval_stack_top->datum.string.length) ? 1 :
		(eval_ptr->eval_stack_top[-1].datum.string.length <
		eval_ptr->eval_stack_top->datum.string.length) ? -1 : 0);
}
/*	***********************************************************************	*/

/* stkbasic routines */
/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_StackExchange(EEC_EVAL_DATA *eval_ptr, unsigned int index_1,
	unsigned int index_2)
#else
void EEC_EVAL_StackExchange(eval_ptr, index_1, index_2)
EEC_EVAL_DATA *eval_ptr;
unsigned int   index_1;
unsigned int   index_2;
#endif /* #ifndef NARGS */
{
	EEC_DATUM tmp_stack_item;
	char      error_text[EEC_MAX_ERROR_TEXT];

	if ((index_1 > eval_ptr->eval_stack_count) ||
		 (index_2 > eval_ptr->eval_stack_count)) {
		sprintf(error_text,
			"%s (index one = %u, index two = %u, stack count = %u).",
			"Invalid index/indices in stack element exchange request",
			index_1, index_2, eval_ptr->eval_stack_count);
		EEC_EVAL_ErrorJmp(eval_ptr, "EEC_EVAL_StackExchange", EEC_FAILURE,
			error_text);
	}

	tmp_stack_item                = eval_ptr->eval_stack[index_1];
	eval_ptr->eval_stack[index_1] = eval_ptr->eval_stack[index_2];
	eval_ptr->eval_stack[index_2] = tmp_stack_item;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_StackSwap(EEC_EVAL_DATA *eval_ptr)
#else
void EEC_EVAL_StackSwap(eval_ptr)
EEC_EVAL_DATA *eval_ptr;
#endif /* #ifndef NARGS */
{
	if (eval_ptr->eval_stack_count < 2)
		EEC_EVAL_ErrorJmp(eval_ptr, "EEC_EVAL_StackSwap", EEC_FAILURE,
			"Stack swap request with fewer than 2 items on stack.");

	EEC_EVAL_StackExchange(eval_ptr, eval_ptr->eval_stack_count - 1,
		eval_ptr->eval_stack_count - 2);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_StackPushNumberFlag(EEC_EVAL_DATA *eval_ptr, unsigned int flags)
#else
void EEC_EVAL_StackPushNumberFlag(eval_ptr, flags)
EEC_EVAL_DATA *eval_ptr;
unsigned int   flags;
#endif /* #ifndef NARGS */
{
	EEC_EVAL_StackPushNumber(eval_ptr, 0.0);

	(eval_ptr)->eval_stack_top->flags |= (flags & EEC_EVAL_FLAG_FLAGS_SPECIAL);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_StackPushStringFlag(EEC_EVAL_DATA *eval_ptr, unsigned int flags)
#else
void EEC_EVAL_StackPushStringFlag(eval_ptr, flags)
EEC_EVAL_DATA *eval_ptr;
unsigned int   flags;
#endif /* #ifndef NARGS */
{
	EEC_EVAL_StackPushStringEmpty(eval_ptr);

	(eval_ptr)->eval_stack_top->flags |= (flags & EEC_EVAL_FLAG_FLAGS_SPECIAL);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_StackPushNumber(EEC_EVAL_DATA *eval_ptr, double value)
#else
void EEC_EVAL_StackPushNumber(eval_ptr, value)
EEC_EVAL_DATA *eval_ptr;
double         value;
#endif /* #ifndef NARGS */
{
	if (EEC_EVAL_NEED_MORE_STACK(eval_ptr) == EEC_TRUE)
		EEC_EVAL_StackAlloc(eval_ptr);

	EEC_EVAL_ADD_STACK_INDEX(eval_ptr);

	(eval_ptr)->eval_stack_top->flags        = EEC_TYPE_NUMBER;
	(eval_ptr)->eval_stack_top->datum.number = value;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *EEC_EVAL_StackPushString(EEC_EVAL_DATA *eval_ptr, const char *string_ptr,
	unsigned int string_length)
#else
char *EEC_EVAL_StackPushString(eval_ptr, string_ptr, string_length)
EEC_EVAL_DATA *eval_ptr;
const char    *string_ptr;
unsigned int   string_length;
#endif /* #ifndef NARGS */
{
	if (EEC_EVAL_NEED_MORE_STACK(eval_ptr) == EEC_TRUE)
		EEC_EVAL_StackAlloc(eval_ptr);

	EEC_EVAL_ADD_STACK_INDEX(eval_ptr);

	eval_ptr->eval_stack_top->flags                =
		EEC_EVAL_FLAG_TYPE_STRING;
	eval_ptr->eval_stack_top->datum.string.data    =
		EEC_EVAL_StringAlloc(eval_ptr, string_length);
	eval_ptr->eval_stack_top->datum.string.length  = string_length;
	eval_ptr->eval_stack_top->flags               |= EEC_EVAL_FLAG_ALLOCED;
	memcpy(eval_ptr->eval_stack_top->datum.string.data, string_ptr,
		string_length);

	return(eval_ptr->eval_stack_top->datum.string.data);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *EEC_EVAL_StackPushStringZ(EEC_EVAL_DATA *eval_ptr, const char *string_ptr)
#else
char *EEC_EVAL_StackPushStringZ(eval_ptr, string_ptr)
EEC_EVAL_DATA *eval_ptr;
const char    *string_ptr;
#endif /* #ifndef NARGS */
{
	return(EEC_EVAL_StackPushString(eval_ptr, string_ptr, strlen(string_ptr)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *EEC_EVAL_StackPushStringStatic(EEC_EVAL_DATA *eval_ptr,
	const char *string_ptr, unsigned int string_length)
#else
char *EEC_EVAL_StackPushStringStatic(eval_ptr, string_ptr, string_length)
EEC_EVAL_DATA *eval_ptr;
const char    *string_ptr;
unsigned int   string_length;
#endif /* #ifndef NARGS */
{
	if (EEC_EVAL_NEED_MORE_STACK(eval_ptr) == EEC_TRUE)
		EEC_EVAL_StackAlloc(eval_ptr);

	EEC_EVAL_ADD_STACK_INDEX(eval_ptr);

	eval_ptr->eval_stack_top->flags               =
		EEC_EVAL_FLAG_TYPE_STRING;
	eval_ptr->eval_stack_top->datum.string.length = string_length;
	eval_ptr->eval_stack_top->datum.string.data   = ((char *) string_ptr);

	return(eval_ptr->eval_stack_top->datum.string.data);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *EEC_EVAL_StackPushStringZStatic(EEC_EVAL_DATA *eval_ptr,
	const char *string_ptr)
#else
char *EEC_EVAL_StackPushStringZStatic(eval_ptr, string_ptr)
EEC_EVAL_DATA *eval_ptr;
const char    *string_ptr;
#endif /* #ifndef NARGS */
{
	return(EEC_EVAL_StackPushStringStatic(eval_ptr, string_ptr,
		strlen(string_ptr)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *EEC_EVAL_StackPushStringEmpty(EEC_EVAL_DATA *eval_ptr)
#else
char *EEC_EVAL_StackPushStringEmpty(eval_ptr)
EEC_EVAL_DATA *eval_ptr;
#endif /* #ifndef NARGS */
{
	if (EEC_EVAL_NEED_MORE_STACK(eval_ptr) == EEC_TRUE)
		EEC_EVAL_StackAlloc(eval_ptr);

	EEC_EVAL_ADD_STACK_INDEX(eval_ptr);

	eval_ptr->eval_stack_top->flags               =
		EEC_EVAL_FLAG_TYPE_STRING;
	eval_ptr->eval_stack_top->datum.string.length = 0;
	eval_ptr->eval_stack_top->datum.string.data   = EEC_EVAL_EMPTY_STRING;

	return(eval_ptr->eval_stack_top->datum.string.data);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_StackPush(EEC_EVAL_DATA *eval_ptr, int datum_type,
	const void *datum_ptr, unsigned int datum_length)
#else
void EEC_EVAL_StackPush(eval_ptr, datum_type, datum_ptr, datum_length)
EEC_EVAL_DATA *eval_ptr;
int            datum_type;
const void    *datum_ptr;
unsigned int   datum_length;
#endif /* #ifndef NARGS */
{
	EEC_DATUM tmp_datum;
	char      error_text[EEC_MAX_ERROR_TEXT];

	EEC_INIT_EEC_DATUM(&tmp_datum);

	if (datum_type == EEC_EVAL_FLAG_TYPE_NUMBER) {
		tmp_datum.flags        = EEC_EVAL_FLAG_TYPE_NUMBER;
		tmp_datum.datum.number = *((double *) datum_ptr);
	}
	else if (datum_type == EEC_EVAL_FLAG_TYPE_STRING) {
		EEC_EVAL_StringAllocDatum(eval_ptr, datum_length, &tmp_datum);
		memcpy(tmp_datum.datum.string.data, datum_ptr, datum_length);
	}
	else {
		sprintf(error_text, "%s (%u) expected either '%s' or '%s'.",
			"Invalid EEC evaluation type",  datum_type,
			"EEC_EVAL_FLAG_TYPE_NUMBER", "EEC_EVAL_FLAG_TYPE_STRING");
		EEC_EVAL_ErrorJmp(eval_ptr, "EEC_EVAL_StackPush", EEC_FAILURE,
			error_text);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_StackPushDatum(EEC_EVAL_DATA *eval_ptr, EEC_DATUM *datum_ptr)
#else
void EEC_EVAL_StackPushDatum(eval_ptr, datum_ptr)
EEC_EVAL_DATA *eval_ptr;
EEC_DATUM     *datum_ptr;
#endif /* #ifndef NARGS */
{
	if (EEC_EVAL_NEED_MORE_STACK(eval_ptr) == EEC_TRUE)
		EEC_EVAL_StackAlloc(eval_ptr);

	EEC_EVAL_ADD_STACK_INDEX(eval_ptr);

	*eval_ptr->eval_stack_top = *datum_ptr;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_StackAlloc(EEC_EVAL_DATA *eval_ptr)
#else
void EEC_EVAL_StackAlloc(eval_ptr)
EEC_EVAL_DATA *eval_ptr;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char error_text[EEC_MAX_ERROR_TEXT];

	if (EEC_EVAL_NEED_MORE_STACK(eval_ptr) == EEC_TRUE) {
		if ((return_code = EEC_EVAL_StackAllocBasic(eval_ptr, error_text)) !=
			EEC_SUCCESS)
			EEC_EVAL_ErrorJmp(eval_ptr, "EEC_EVAL_StackAlloc", return_code,
				error_text);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_EVAL_StackAllocBasic(EEC_EVAL_DATA *eval_ptr, char *error_text)
#else
int EEC_EVAL_StackAllocBasic(eval_ptr, error_text)
EEC_EVAL_DATA *eval_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int        return_code = EEC_SUCCESS;
	EEC_DATUM *tmp_ptr;

	if (EEC_EVAL_NEED_MORE_STACK(eval_ptr) == EEC_TRUE) {
		if (!eval_ptr->eval_stack_alloc) {
			if ((tmp_ptr = ((EEC_DATUM *) calloc(EEC_STACK_GRANULARITY,
				sizeof(EEC_DATUM)))) == NULL) {
				sprintf(error_text, "%s (requested allocation = %lu).",
					"Unable to allocate initial evaluation stack memory",
					((unsigned long) EEC_STACK_GRANULARITY) *
					((unsigned long) sizeof(EEC_DATUM)));
				return_code = EEC_MEMORY_FAILURE;
			}
			else
				eval_ptr->eval_stack = tmp_ptr;
		}
		else if (!(eval_ptr->eval_stack_alloc % EEC_STACK_GRANULARITY)) {
			if ((tmp_ptr = ((EEC_DATUM *) realloc(eval_ptr->eval_stack,
				(sizeof(EEC_DATUM) * eval_ptr->eval_stack_alloc) +
				(sizeof(EEC_DATUM) * EEC_STACK_GRANULARITY)))) == NULL) {
				sprintf(error_text,
					"%s (count = %u, %s = %lu, %s = %lu, %s = %lu).",
					"Unable to allocate additional evaluation stack memory",
					eval_ptr->eval_stack_alloc, "current allocation",
					((unsigned long) sizeof(EEC_DATUM)) *
					((unsigned long) eval_ptr->eval_stack_alloc),
					"requested allocation",
					((unsigned long) sizeof(EEC_DATUM)) *
					((unsigned long) EEC_STACK_GRANULARITY), "new total allocation",
					(((unsigned long) sizeof(EEC_DATUM)) *
					((unsigned long) eval_ptr->eval_stack_alloc)) +
					(((unsigned long) sizeof(EEC_DATUM)) *
					((unsigned long) EEC_STACK_GRANULARITY)));
				return_code = EEC_MEMORY_FAILURE;
			}
			else {
				eval_ptr->eval_stack = tmp_ptr;
				memset(eval_ptr->eval_stack + eval_ptr->eval_stack_alloc,
					'\0', sizeof(EEC_DATUM) * EEC_STACK_GRANULARITY);
			}
		}
		if (return_code == EEC_SUCCESS)
			eval_ptr->eval_stack_alloc += EEC_STACK_GRANULARITY;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_EVAL_PopIfSFlagsNumber(EEC_EVAL_DATA *eval_ptr,
	unsigned int datum_count)
#else
int EEC_EVAL_PopIfSFlagsNumber(eval_ptr, datum_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   datum_count;
#endif /* #ifndef NARGS */
{
	return(EEC_EVAL_PopIfSFlags(eval_ptr, datum_count,
		EEC_EVAL_FLAG_TYPE_NUMBER));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_EVAL_PopIfSFlagsString(EEC_EVAL_DATA *eval_ptr,
	unsigned int datum_count)
#else
int EEC_EVAL_PopIfSFlagsString(eval_ptr, datum_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   datum_count;
#endif /* #ifndef NARGS */
{
	return(EEC_EVAL_PopIfSFlags(eval_ptr, datum_count,
		EEC_EVAL_FLAG_TYPE_STRING));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_EVAL_PopIfSFlags(EEC_EVAL_DATA *eval_ptr, unsigned int datum_count,
	unsigned int datum_type)
#else
int EEC_EVAL_PopIfSFlags(eval_ptr, datum_count, datum_type)
EEC_EVAL_DATA *eval_ptr;
unsigned int   datum_count;
unsigned int   datum_type;
#endif /* #ifndef NARGS */
{
	unsigned int flags;
	unsigned int found_index;

	if ((flags = EEC_EVAL_FindSFlags(eval_ptr,
		eval_ptr->eval_stack_count - datum_count, eval_ptr->eval_stack_count - 1,
		EEC_EVAL_FLAG_FLAGS_SPECIAL, EEC_FALSE, &found_index)) != 0) {
		EEC_EVAL_StackPop(eval_ptr, datum_count);
		if (datum_type == EEC_EVAL_FLAG_TYPE_STRING)
			EEC_EVAL_StackPushStringFlag(eval_ptr, flags);
		else
			EEC_EVAL_StackPushNumberFlag(eval_ptr, flags);
	}

	return(flags);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_EVAL_FindSFlags(EEC_EVAL_DATA *eval_ptr, unsigned int index_1,
	unsigned int index_2, unsigned int flags, int find_highest_flag,
	unsigned int *found_index)
#else
int EEC_EVAL_FindSFlags(eval_ptr, index_1, index_2, flags,
	find_highest_flag, found_index)
EEC_EVAL_DATA *eval_ptr;
unsigned int   index_1;
unsigned int   index_2;
unsigned int   flags;
int            find_highest_flag;
unsigned int  *found_index;
#endif /* #ifndef NARGS */
{
	unsigned int flag_value = 0;
	char         error_text[EEC_MAX_ERROR_TEXT];

	if (index_1 > index_2) {
		sprintf(error_text, "%s (index one = %u, index two = %u).",
			"Invalid index/indices in stack element exchange request",
			index_1, index_2);
		EEC_EVAL_ErrorJmp(eval_ptr, "EEC_EVAL_CheckFlags", EEC_FAILURE,
			error_text);
	}
	else if (index_2 >= eval_ptr->eval_stack_count) {
		sprintf(error_text,
			"%s (index one = %u, index two = %u, stack count = %u).",
			"Invalid index/indices in stack element exchange request",
			index_1, index_2, eval_ptr->eval_stack_count);
		EEC_EVAL_ErrorJmp(eval_ptr, "EEC_EVAL_CheckFlags", EEC_FAILURE,
			error_text);
	}
	else {
		flags &= EEC_EVAL_FLAG_FLAGS_SPECIAL;
		while (index_1 <= index_2) {
			if (eval_ptr->eval_stack[index_1].flags & flags) {
				if (!find_highest_flag) {
					if (found_index != NULL)
						*found_index = index_1;
					flag_value = eval_ptr->eval_stack[index_1].flags & flags;
					break;
				}
				if ((eval_ptr->eval_stack[index_1].flags & flags) > flag_value) {
					if (found_index != NULL)
						*found_index = index_1;
					flag_value = eval_ptr->eval_stack[index_1].flags & flags;
				}
			}
			index_1++;
		}
	}

	return(flag_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_StaticToAlloced(EEC_EVAL_DATA *eval_ptr, EEC_DATUM *datum_ptr)
#else
void EEC_EVAL_StaticToAlloced(eval_ptr, datum_ptr)
EEC_EVAL_DATA *eval_ptr;
EEC_DATUM     *datum_ptr;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;

	if (EEC_EVAL_DATUM_IS_STATIC(datum_ptr) == EEC_TRUE) {
		memcpy(tmp_ptr = EEC_EVAL_StringAlloc(eval_ptr,
			datum_ptr->datum.string.length), datum_ptr->datum.string.data,
			datum_ptr->datum.string.length);
		datum_ptr->datum.string.data  = tmp_ptr;
		datum_ptr->flags             |= EEC_EVAL_FLAG_ALLOCED;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *EEC_EVAL_StringAllocDatum(EEC_EVAL_DATA *eval_ptr,
	unsigned int string_length, EEC_DATUM *datum_ptr)
#else
char *EEC_EVAL_StringAllocDatum(eval_ptr, string_length, datum_ptr)
EEC_EVAL_DATA *eval_ptr;
unsigned int   string_length;
EEC_DATUM     *datum_ptr;
#endif /* #ifndef NARGS */
{
	EEC_INIT_EEC_DATUM(datum_ptr);

	datum_ptr->datum.string.data   = EEC_EVAL_StringAlloc(eval_ptr,
		string_length);
	datum_ptr->datum.string.length = string_length;
	datum_ptr->flags               = EEC_EVAL_FLAG_TYPE_STRING |
		EEC_EVAL_FLAG_ALLOCED;

	return(datum_ptr->datum.string.data);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *EEC_EVAL_StringAlloc(EEC_EVAL_DATA *eval_ptr, unsigned int string_length)
#else
char *EEC_EVAL_StringAlloc(eval_ptr, string_length)
EEC_EVAL_DATA *eval_ptr;
unsigned int   string_length;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;
	char  text[EEC_MAX_ERROR_TEXT];

	if ((tmp_ptr = ((char *) malloc((string_length + 1) * sizeof(char)))) ==
		NULL)
		EEC_EVAL_ErrorJmp(eval_ptr, "EEC_EVAL_StringAlloc", EEC_MEMORY_FAILURE,
			STR_AllocMsgItem(string_length + 1, text,
			"Unable to allocate string datum memory."));
	else
		tmp_ptr[string_length] = '\0';

	return(tmp_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
EEC_DATUM *EEC_EVAL_StackPop(EEC_EVAL_DATA *eval_ptr, unsigned int pop_count)
#else
EEC_DATUM *EEC_EVAL_StackPop(eval_ptr, pop_count)
EEC_EVAL_DATA *eval_ptr;
unsigned int   pop_count;
#endif /* #ifndef NARGS */
{
	char text[EEC_MAX_ERROR_TEXT];

	if ((!pop_count) || ((pop_count - 1) > eval_ptr->eval_stack_count)) {
		sprintf(text, "%s (request count = %u, stack depth = %u).",
			"Invalid stack pop request pop count", pop_count,
			eval_ptr->eval_stack_count);
		EEC_EVAL_ErrorJmp(eval_ptr, "EEC_EVAL_StackPop",
			EEC_FAILURE, text);
	}

	while (pop_count--) {
		if ((eval_ptr->eval_stack_top->flags &
			EEC_EVAL_FLAG_TYPE_STRING) &&
			(eval_ptr->eval_stack_top->flags & EEC_EVAL_FLAG_ALLOCED))
			free(eval_ptr->eval_stack_top->datum.string.data);
		if (eval_ptr->eval_stack_top > eval_ptr->eval_stack)
			eval_ptr->eval_stack_top--;
		eval_ptr->eval_stack_count--;
	}

	return((eval_ptr->eval_stack_count) ? (eval_ptr->eval_stack_top + 1) :
		eval_ptr->eval_stack_top);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
EEC_DATUM *EEC_EVAL_StackPopTop(EEC_EVAL_DATA *eval_ptr)
#else
EEC_DATUM *EEC_EVAL_StackPopTop(eval_ptr)
EEC_EVAL_DATA *eval_ptr;
#endif /* #ifndef NARGS */
{
	return(EEC_EVAL_StackPop(eval_ptr, 1));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
double EEC_EVAL_StackPopNumber(EEC_EVAL_DATA *eval_ptr)
#else
double EEC_EVAL_StackPopNumber(eval_ptr)
EEC_EVAL_DATA *eval_ptr;
#endif /* #ifndef NARGS */
{
	EEC_DATUM *datum_ptr;

	return(((datum_ptr = EEC_EVAL_StackPopTop(eval_ptr))->flags &
		EEC_EVAL_FLAG_TYPE_NUMBER) ? datum_ptr->datum.number : 0.0);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_StackClear(EEC_EVAL_DATA *eval_ptr)
#else
void EEC_EVAL_StackClear(eval_ptr)
EEC_EVAL_DATA *eval_ptr;
#endif /* #ifndef NARGS */
{
	if (eval_ptr->eval_stack_count)
		EEC_EVAL_StackPop(eval_ptr, eval_ptr->eval_stack_count);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_EVAL_ErrorJmp(EEC_EVAL_DATA *eval_ptr, char *function,
	int return_code, char *descriptive_text)
#else
void EEC_EVAL_ErrorJmp(eval_ptr, function, return_code, descriptive_text)
EEC_EVAL_DATA *eval_ptr;
char          *function;
int            return_code;
char          *descriptive_text;
#endif /* #ifndef NARGS */
{
	eval_ptr->return_code = (return_code == EEC_SUCCESS) ? EEC_FAILURE :
		return_code;

	sprintf(eval_ptr->error_text, "%s '%s()' (return code = %d): %s",
		"Evaluation error in function", function, return_code,
		descriptive_text);

	longjmp(eval_ptr->jump_context, -1);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code;
	unsigned int  count_1;
	unsigned int  parse_index;
	EEC_CONTROL   control_data;
	EEC_POSTFIX   postfix_data;
	EEC_DATUM     result;
	char          in_text[512];
	char          tmp_in_text[512];
	char          error_text[EEC_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'EEC_EvalControl()'\n");
	fprintf(stderr, "---- ------- --- -------------------\n\n");

	fprintf(stderr, "USAGE:\n------\n%s%s\n",
		"   Enter an expression to be parsed.\n",
		"   Enter 'QUIT' or 'EXIT' to exit.\n");

	EEC_INIT_EEC_CONTROL(&control_data);

	return_code = EEC_CreateControl(&control_data, error_text);

	while (return_code == EEC_SUCCESS) {
		do {
			*in_text = '\0';
			fprintf(stderr, ">");
			fgets(in_text, sizeof(in_text) - 1, stdin);
			while (*in_text && (in_text[strlen(in_text) - 1] == '\n'))
				in_text[strlen(in_text) - 1] = '\0';
		} while ((!(*in_text)) && (!feof(stdin)) && (!ferror(stdin)));
		trim(strcpy(tmp_in_text, in_text));
		if ((!stricmp(tmp_in_text, "QUIT")) ||
			(!stricmp(tmp_in_text, "EXIT")) || feof(stdin) || ferror(stdin))
			break;
		STR_EMIT_CharLine('=', 78, NULL, stderr);
		if ((return_code = EEC_ParseIt(&control_data, strlen(in_text), in_text,
			NULL, &postfix_data, &parse_index, error_text)) == EEC_SUCCESS) {
			if ((return_code = EEC_EvalIt(&control_data, &postfix_data, &result,
				error_text)) == EEC_SUCCESS) {
				if (result.flags & EEC_EVAL_FLAG_TYPE_NULL)
					printf("Flag  : NULL\n");
				else if (result.flags & EEC_EVAL_FLAG_TYPE_NA)
					printf("Flag  : NA\n");
				else if (result.flags & EEC_EVAL_FLAG_TYPE_ERR)
					printf("Flag  : ERR\n");
				else if (result.flags & EEC_EVAL_FLAG_TYPE_NUMBER)
					printf("Number: %20.6f\n", result.datum.number);
				else {
					printf("String: ");
					EEC_EMIT_HumanString(result.datum.string.length,
						result.datum.string.data, EEC_TRUE, 0, NULL, NULL);
					printf("\n");
				}
				EEC_FREE_DatumPtr(&result);
			}
			else
				fprintf(stderr, "EVALUATION ERROR: %s\n", error_text);
			EEC_FREE_PostFixPtr(&postfix_data);
		}
		else {
			fprintf(stderr, "%s\n", in_text);
			for (count_1 = 0; count_1 < strlen(in_text); count_1++)
				tmp_in_text[count_1] = ((char)
					((strchr("\n\r\f\t\b", in_text[count_1]) == NULL) ?
					((char) ' ') : in_text[count_1]));
			tmp_in_text[parse_index]     = '^';
			tmp_in_text[parse_index + 1] = '\0';
			fprintf(stderr, "%s\n", tmp_in_text);
			STR_EMIT_CharLine('-', 78, NULL, stderr);
			fprintf(stderr, "PARSE ERROR: %s\n", error_text);
		}
		STR_EMIT_CharLine('=', 78, NULL, stderr);
	}

	EEC_FREE_Control(&control_data);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

