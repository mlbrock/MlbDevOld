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

	Revision History	:	1991-12-22 --- Creation.
									Michael L. Brock
								1993-04-04 --- Version 4 changes.
									Michael L. Brock
								1996-01-30 --- Version 5 initial cut.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
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
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsedat.h"
#include "evaldefs.h"
#include "eecfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Old Sun compiler doesn't prototype 'strtod()'.								*/
/*	***********************************************************************	*/
#ifdef sparc
COMPAT_FN_DECL(double strtod, (const char *string, char **end_ptr));
#endif /* #ifdef sparc */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int                 EEC_DoBasicParse,
	(const char *formula_ptr,
	EEC_SUB_EXPR *this_expr, int optimize_flag, const char *decimal_point,
	unsigned int op_alias_count, const EEC_PARSE_OP_ALIAS *op_alias_list,
	unsigned int func_def_count, const EEC_FUNC_DEF *func_def_list,
	int (*func_resolve_func)(const char *, const EEC_FUNC_DEF *, unsigned int,
		unsigned int, unsigned int, unsigned int *, char *),
	EEC_SymbolParseFunc symbol_parse_func, void *symbol_parse_data,
	unsigned int *sub_expr_count, EEC_SUB_EXPR **sub_expr_list,
	unsigned int *sub_expr_alloc, unsigned int sub_expr_gran,
	EEC_EVAL_DATA *eval_ptr, unsigned int *parse_index, char *error_text));
COMPAT_FN_DECL_STATIC(int                 EEC_ResolveFunc,
	(const char *formula_ptr,
	EEC_SUB_EXPR *this_expr, int optimize_flag, const char *decimal_point,
	unsigned int op_alias_count, const EEC_PARSE_OP_ALIAS *op_alias_list,
	unsigned int func_def_count, const EEC_FUNC_DEF *func_def_list,
	int (*func_resolve_func)(const char *, const EEC_FUNC_DEF *, unsigned int,
		unsigned int, unsigned int, unsigned int *, char *),
	EEC_SymbolParseFunc symbol_parse_func, void *symbol_parse_data,
	unsigned int *sub_expr_count, EEC_SUB_EXPR **sub_expr_list,
	unsigned int *sub_expr_alloc, unsigned int sub_expr_gran,
	EEC_EVAL_DATA *eval_ptr, unsigned int *parse_index, char *error_text));
COMPAT_FN_DECL_STATIC(int                 EEC_AssemblePostFix,
	(const char *formula_ptr,
	EEC_SUB_EXPR *this_expr, int optimize_flag, unsigned int sub_expr_count,
	EEC_SUB_EXPR *sub_expr_list, EEC_EVAL_DATA *eval_ptr,
	unsigned int *parse_index, char *error_text));
COMPAT_FN_DECL_STATIC(int                 EEC_OptimizeExpr,
	(const char *formula_ptr,
	EEC_SUB_EXPR *this_expr, unsigned int sub_expr_count,
	EEC_SUB_EXPR *sub_expr_list, EEC_EVAL_DATA *eval_ptr,
	unsigned int *parse_index, char *error_text));
COMPAT_FN_DECL_STATIC(int                 EEC_OptimizeSubExpr,
	(EEC_POSTFIX *postfix_ptr,
	EEC_SUB_EXPR *sub_expr_ptr, EEC_EVAL_DATA *eval_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int                 EEC_AppStackToPostFix,
	(unsigned int stack_count,
	const EEC_DATUM *stack_list, EEC_POSTFIX *postfix_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int                 EEC_AddPostFix,
	(EEC_POSTFIX *postfix_ptr,
	const char *formula_ptr, EEC_SUB_EXPR *this_expr,
	unsigned int argument_count, char *error_text));
COMPAT_FN_DECL_STATIC(int                 EEC_AllocPostFix,
	(EEC_POSTFIX *postfix_ptr,
	unsigned int added_length, char *error_text));
COMPAT_FN_DECL_STATIC(const EEC_FUNC_DEF *EEC_FindFuncDef,
	(unsigned int func_def_count,
	const EEC_FUNC_DEF *func_def_list, const char *func_name,
	unsigned int *func_index));
COMPAT_FN_DECL_STATIC(int                 EEC_DetermineArgString,
	(const char *formula_ptr,
	unsigned int start_index, unsigned int end_index,
	unsigned int *new_end_index, char *error_text));
COMPAT_FN_DECL_STATIC(int                 EEC_DetermineParendString,
	(const char *formula_ptr,
	unsigned int start_index, unsigned int end_index,
	unsigned int *new_end_index, char *error_text));
COMPAT_FN_DECL_STATIC(int                 EEC_DetermineQuotedString,
	(const char *formula_ptr,
	unsigned int start_index, unsigned int end_index,
	unsigned int *new_end_index, char *error_text));
COMPAT_FN_DECL_STATIC(int                 EEC_DetermineNumberString,
	(const char *formula_ptr,
	unsigned int start_index, unsigned int end_index,
	const char *decimal_point, unsigned int *new_end_index));
COMPAT_FN_DECL_STATIC(int                 EEC_AddSubExpression,
	(unsigned int *sub_expr_count,
	EEC_SUB_EXPR **sub_expr_list, unsigned int *sub_expr_alloc,
	unsigned int sub_expr_gran, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_ParseIt(EEC_CONTROL *control_ptr, unsigned int formula_length,
	const char *formula_ptr, unsigned int *expr_type, EEC_POSTFIX *postfix_ptr,
	unsigned int *parse_index, char *error_text)
#else
int EEC_ParseIt(control_ptr, formula_length, formula_ptr, expr_type,
	postfix_ptr, parse_index, error_text)
EEC_CONTROL  *control_ptr;
unsigned int  formula_length;
const char   *formula_ptr;
unsigned int *expr_type;
EEC_POSTFIX  *postfix_ptr;
unsigned int *parse_index;
char         *error_text;
#endif /* #ifndef NARGS */
{
	return(EEC_ParseItBasic(formula_length, formula_ptr,
		control_ptr->optimize_flag, control_ptr->decimal_point_ptr,
		control_ptr->op_alias_count, control_ptr->op_alias_list,
		control_ptr->func_def_count, control_ptr->func_def_list,
		control_ptr->func_resolve_func, control_ptr->symbol_parse_func,
		control_ptr->symbol_parse_data, &control_ptr->sub_expr_alloc,
		&control_ptr->sub_expr_list, control_ptr->sub_expr_gran,
		&control_ptr->eval_data, expr_type, postfix_ptr, parse_index,
		error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_ParseItBasic(unsigned int formula_length, const char *formula_ptr,
	int optimize_flag, const char *decimal_point, unsigned int op_alias_count,
	const EEC_PARSE_OP_ALIAS *op_alias_list, unsigned int func_def_count,
	const EEC_FUNC_DEF *func_def_list,
	int (*func_resolve_func)(const char *, const EEC_FUNC_DEF *, unsigned int,
		unsigned int, unsigned int, unsigned int *, char *),
	EEC_SymbolParseFunc symbol_parse_func, void *symbol_parse_data,
	unsigned int *sub_expr_alloc, EEC_SUB_EXPR **sub_expr_list,
	unsigned int sub_expr_gran, EEC_EVAL_DATA *eval_ptr,
	unsigned int *expr_type, EEC_POSTFIX *postfix_ptr,
	unsigned int *parse_index, char *error_text)
#else
int EEC_ParseItBasic(formula_length, formula_ptr, optimize_flag,
	decimal_point, op_alias_count, op_alias_list, func_def_count,
	func_def_list, func_resolve_func, symbol_parse_func, symbol_parse_data,
	sub_expr_alloc, sub_expr_list, sub_expr_gran, eval_ptr, expr_type,
	postfix_ptr, parse_index, error_text)
unsigned int               formula_length;
const char                *formula_ptr;
int                        optimize_flag;
const char                *decimal_point;
unsigned int               op_alias_count;
const EEC_PARSE_OP_ALIAS  *op_alias_list;
unsigned int               func_def_count;
const EEC_FUNC_DEF        *func_def_list;
#ifndef NARGS
int                      (*func_resolve_func)(const char *,
									const EEC_FUNC_DEF *, unsigned int, unsigned int,
									unsigned int, unsigned int *, char *);
#else
int                      (*func_resolve_func)();
#endif /* #ifndef NARGS */
EEC_SymbolParseFunc        symbol_parse_func;
void                      *symbol_parse_data;
unsigned int              *sub_expr_alloc;
EEC_SUB_EXPR             **sub_expr_list;
unsigned int               sub_expr_gran;
EEC_EVAL_DATA             *eval_ptr;
unsigned int              *expr_type;
EEC_POSTFIX               *postfix_ptr;
unsigned int              *parse_index;
char                      *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code        = EEC_SUCCESS;
	unsigned int   tmp_sub_expr_count = 0;
	unsigned int   tmp_sub_expr_alloc = 0;
	EEC_SUB_EXPR  *tmp_sub_expr_list  = NULL;
	unsigned int   tmp_expr_type;
	unsigned int   tmp_parse_index;
	EEC_SUB_EXPR   tmp_expr;
	EEC_EVAL_DATA  eval_data;
	struct lconv  *locale_ptr;

	EEC_INIT_EEC_POSTFIX(postfix_ptr);

	if (expr_type != NULL)
		*expr_type = EEC_TYPE_NONE;
	if (parse_index != NULL)
		*parse_index = 0;

	if ((op_alias_count && (op_alias_list == NULL)) ||
		((!op_alias_count) && (op_alias_list != NULL))) {
		sprintf(error_text, "%s %s, %s %s.",
			"User operator alias count is",
			(op_alias_count) ? "non-zero" : "zero",
			"but the associated user operator alias list is",
			(op_alias_count) ? "NULL" : "not NULL");
		return_code = EEC_BAD_ARGS_FAILURE;
	}
	else if ((func_def_count && (func_def_list == NULL)) ||
		((!func_def_count) && (func_def_list != NULL))) {
		sprintf(error_text, "%s %s, %s %s.",
			"User function definition count is",
			(func_def_count) ? "non-zero" : "zero",
			"but the associated user function definition list is",
			(func_def_count) ? "NULL" : "not NULL");
		return_code = EEC_BAD_ARGS_FAILURE;
	}
	else if (((sub_expr_alloc != NULL) && (sub_expr_list == NULL)) ||
		((sub_expr_alloc == NULL) && (sub_expr_list != NULL))) {
		sprintf(error_text,
			"Sub-expression allocation pointer is %s, but sub-expression list \
pointer is %s.",
			(sub_expr_alloc != NULL) ? "not NULL" : "NULL",
			(sub_expr_alloc != NULL) ? "NULL" : "not NULL");
		return_code = EEC_BAD_ARGS_FAILURE;
	}
	else if ((*sub_expr_alloc && (*sub_expr_list == NULL)) ||
		((!(*sub_expr_alloc)) && (*sub_expr_list != NULL))) {
		sprintf(error_text,
			"Sub-expression allocation is %s, but sub-expression list is %s.",
			(*sub_expr_alloc) ? "non-zero" : "zero",
			(*sub_expr_alloc) ? "NULL" : "not NULL");
		return_code = EEC_BAD_ARGS_FAILURE;
	}
	else if (formula_length) {
		if (decimal_point == NULL) {
			if ((locale_ptr = localeconv()) != NULL)
				decimal_point = locale_ptr->decimal_point;
			else
				decimal_point = ".";
		}
		op_alias_count  = (op_alias_count) ? op_alias_count :
			EEC_OperatorAliasCount;
		op_alias_list   = (op_alias_count) ? op_alias_list  :
			EEC_OperatorAliasList;
		sub_expr_alloc  = (sub_expr_alloc != NULL) ? sub_expr_alloc :
			&tmp_sub_expr_alloc;
		sub_expr_list   = (sub_expr_list  != NULL) ? sub_expr_list  :
			&tmp_sub_expr_list;
		sub_expr_gran   = (sub_expr_gran) ? sub_expr_gran : EEC_EXPR_LIST_GRAN;
		expr_type       = (expr_type != NULL) ? expr_type : &tmp_expr_type;
		parse_index     = (parse_index != NULL) ? parse_index : &tmp_parse_index;
		EEC_INIT_EEC_SUB_EXPR(&tmp_expr);
		tmp_expr.start_index = 0;
		tmp_expr.end_index   = formula_length - 1;
		if (eval_ptr == NULL)
			EEC_INIT_EEC_EVAL_DATA(eval_ptr = &eval_data);
		if ((return_code = EEC_DoBasicParse(formula_ptr, &tmp_expr,
			optimize_flag, decimal_point, op_alias_count, op_alias_list,
			func_def_count, func_def_list, func_resolve_func,
			symbol_parse_func, symbol_parse_data, &tmp_sub_expr_count,
			sub_expr_list, sub_expr_alloc, sub_expr_gran, eval_ptr, parse_index,
			error_text)) == EEC_SUCCESS) {
			if (tmp_expr.postfix.length % EEC_POSTFIX_GRAN)
				tmp_expr.postfix.data = ((char *) realloc(tmp_expr.postfix.data,
					tmp_expr.postfix.length));
			*expr_type        = (!tmp_expr.postfix.length) ? EEC_TYPE_NONE :
				(tmp_expr.expr_type & EEC_TYPE_NUMBER) ? EEC_TYPE_NUMBER :
				EEC_TYPE_STRING;
			*postfix_ptr      = tmp_expr.postfix;
			postfix_ptr->type = *expr_type;
		}
		if (eval_ptr == &eval_data)
			EEC_FREE_EvalData(&eval_data);
		if (sub_expr_alloc == &tmp_sub_expr_alloc) {
			if (*sub_expr_list != NULL)
				free(*sub_expr_list);
			*sub_expr_list  = NULL;
			*sub_expr_alloc = 0;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_DoBasicParse(const char *formula_ptr, EEC_SUB_EXPR *this_expr,
	int optimize_flag, const char *decimal_point, unsigned int op_alias_count,
	const EEC_PARSE_OP_ALIAS *op_alias_list, unsigned int func_def_count,
	const EEC_FUNC_DEF *func_def_list,
	int (*func_resolve_func)(const char *, const EEC_FUNC_DEF *, unsigned int,
		unsigned int, unsigned int, unsigned int *, char *),
	EEC_SymbolParseFunc symbol_parse_func, void *symbol_parse_data,
	unsigned int *sub_expr_count, EEC_SUB_EXPR **sub_expr_list,
	unsigned int *sub_expr_alloc, unsigned int sub_expr_gran,
	EEC_EVAL_DATA *eval_ptr, unsigned int *parse_index, char *error_text)
#else
static int EEC_DoBasicParse(formula_ptr, this_expr, optimize_flag,
	decimal_point, op_alias_count, op_alias_list, func_def_count,
	func_def_list, func_resolve_func, symbol_parse_func, symbol_parse_data,
	sub_expr_count, sub_expr_list, sub_expr_alloc, sub_expr_gran, eval_ptr,
	parse_index, error_text)
const char                *formula_ptr;
EEC_SUB_EXPR              *this_expr;
int                        optimize_flag;
const char                *decimal_point;
unsigned int               op_alias_count;
const EEC_PARSE_OP_ALIAS  *op_alias_list;
unsigned int               func_def_count;
const EEC_FUNC_DEF        *func_def_list;
#ifndef NARGS
int                      (*func_resolve_func)(const char *,
									const EEC_FUNC_DEF *, unsigned int, unsigned int,
									unsigned int, unsigned int *, char *);
#else
int                      (*func_resolve_func)();
#endif /* #ifndef NARGS */
EEC_SymbolParseFunc        symbol_parse_func;
void                      *symbol_parse_data;
unsigned int              *sub_expr_count;
EEC_SUB_EXPR             **sub_expr_list;
unsigned int              *sub_expr_alloc;
unsigned int               sub_expr_gran;
EEC_EVAL_DATA             *eval_ptr;
unsigned int              *parse_index;
char                      *error_text;
#endif /* #ifndef NARGS */
{

	int                       return_code   = EEC_SUCCESS;
	int                       last_context  = EEC_TYPE_BEGIN;
	EEC_SUB_EXPR             *this_sub_expr = NULL;
	unsigned int              current_index = 0;
	unsigned int              old_sub_expr_count;
	unsigned int              start_index;
	unsigned int              end_index;
	unsigned int              count_1;
	unsigned int              tmp_expr_type;
	unsigned long             tmp_expr_spec;
	const char               *start_ptr;
	unsigned int              this_sub_index;
	EEC_SUB_EXPR              tmp_sub_expr;
	const EEC_PARSE_CANON_OP *this_op;

	*parse_index       = this_expr->start_index;

	old_sub_expr_count = *sub_expr_count;
	start_index        = this_expr->start_index;
	start_ptr          = formula_ptr + this_expr->start_index;
	end_index          = this_expr->end_index;

	while (start_index <= end_index) {
		if (isspace(*start_ptr)) {
			start_index++;
			start_ptr++;
			continue;
		}
		else if (*start_ptr == ',') {
			strcpy(error_text,
				"Function argument separator outside of function.");
			return_code = EEC_FAILURE;
			goto EXIT_FUNCTION;
		}
		if ((return_code = EEC_AddSubExpression(sub_expr_count, sub_expr_list,
			sub_expr_alloc, sub_expr_gran, error_text)) != EEC_SUCCESS)
			goto EXIT_FUNCTION;
		this_sub_index             = *sub_expr_count - 1;
		this_sub_expr              = *sub_expr_list + this_sub_index;
		this_sub_expr->start_index = start_index;
		if (((last_context == EEC_TYPE_BEGIN) ||
			(last_context & EEC_TYPE_NUMBER_OP) ||
			(last_context & EEC_TYPE_REL_OP) ||
			(last_context & EEC_TYPE_BOOL_OP)) &&
			(EEC_DetermineNumberString(formula_ptr, start_index, end_index,
			decimal_point, &current_index) == EEC_TRUE)) {
			if (((current_index - start_index) + 1) > EEC_MAX_NUMBER_LENGTH) {
				sprintf(error_text,
					"Numeric value exceeds the maximum length (%u).",
					EEC_MAX_NUMBER_LENGTH);
				return_code = EEC_FAILURE;
				goto EXIT_FUNCTION;
			}
			this_sub_expr->end_index  = current_index;
			this_sub_expr->expr_type  = EEC_TYPE_NUMBER;
			this_sub_expr->expr_spec  = 0L;
			this_sub_expr->expr_flags = EEC_SUB_EXPR_FLAG_NONE;
			last_context              = EEC_TYPE_NUMBER;
		}
		else if (*start_ptr == '\"') {
			if ((last_context != EEC_TYPE_BEGIN) &&
				(!(last_context & EEC_TYPE_STRING_OP)) &&
				(!(last_context & EEC_TYPE_REL_OP)) &&
				(!(last_context & EEC_TYPE_BOOL_OP))) {
				strcpy(error_text, "String value must either begin a sub-\
expression or follow a string, relational, or boolean operator.");
				return_code = EEC_FAILURE;
				goto EXIT_FUNCTION;
			}
			if ((return_code = EEC_DetermineQuotedString(formula_ptr,
				start_index, end_index, &current_index, error_text)) !=
				EEC_SUCCESS) {
				start_index = current_index;
				goto EXIT_FUNCTION;
			}
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		Note that because the parser considers an empty		*/
			/*	string --- "" --- to be a valid token, the arithmetic	*/
			/*	below will, in such a case, result in:						*/
			/*																			*/
			/*		end_index = start_index - 1								*/
			/*																			*/
			/*		The other code in the EEC library is designed to	*/
			/*	handle this situation without barfing.						*/
			/*	*****************************************************	*/
			this_sub_expr->start_index = start_index + 1;
			this_sub_expr->end_index   = current_index - 1;
			this_sub_expr->expr_type   = EEC_TYPE_STRING;
			this_sub_expr->expr_spec   = 0L;
			this_sub_expr->expr_flags  = EEC_SUB_EXPR_FLAG_NONE;
			last_context               = EEC_TYPE_STRING;
			/*	*****************************************************	*/
		}
		else if (*start_ptr == '(') {
			if ((last_context != EEC_TYPE_BEGIN) &&
				(!(last_context & EEC_TYPE_NUMBER_OP)) &&
				(!(last_context & EEC_TYPE_REL_OP)) &&
				(!(last_context & EEC_TYPE_BOOL_OP))) {
				strcpy(error_text, "Parenthetical expression must either \
begin a sub-expression or follow a numeric or relational operator.");
				return_code = EEC_FAILURE;
				goto EXIT_FUNCTION;
			}
			if ((return_code = EEC_DetermineParendString(formula_ptr,
				start_index, end_index, &current_index, error_text)) !=
				EEC_SUCCESS) {
				start_index = current_index;
				goto EXIT_FUNCTION;
			}
			if (start_index == (current_index - 1)) {
				strcpy(error_text, "Empty parenthetical expression.");
				return_code = EEC_FAILURE;
				goto EXIT_FUNCTION;
			}
			this_sub_expr->start_index = start_index + 1;
			this_sub_expr->end_index   = current_index - 1;
			this_sub_expr->expr_spec   = 0L;
			this_sub_expr->expr_flags  = EEC_SUB_EXPR_FLAG_NONE;
			tmp_sub_expr               = *this_sub_expr;
			if ((return_code = EEC_DoBasicParse(formula_ptr, &tmp_sub_expr,
				optimize_flag, decimal_point, op_alias_count, op_alias_list,
				func_def_count, func_def_list, func_resolve_func,
				symbol_parse_func, symbol_parse_data, sub_expr_count,
				sub_expr_list, sub_expr_alloc, sub_expr_gran, eval_ptr,
				&current_index, error_text)) != EEC_SUCCESS) {
				start_index = current_index;
				goto EXIT_FUNCTION;
			}
			if (!tmp_sub_expr.postfix.length) {
				strcpy(error_text, "Empty parenthetical expression.");
				return_code = EEC_FAILURE;
				goto EXIT_FUNCTION;
			}
			this_sub_expr              = *sub_expr_list + this_sub_index;
			*this_sub_expr             = tmp_sub_expr;
			this_sub_expr->expr_flags &= EEC_SUB_EXPR_FLAG_VOLATILE;
			last_context               = this_sub_expr->expr_type;
		}
		else if (*start_ptr == ')') {
			strcpy(error_text, "Unopened parenthetical expression.");
			return_code = EEC_FAILURE;
			goto EXIT_FUNCTION;
		}
		else if (*start_ptr == '@') {
			this_sub_expr->end_index = end_index;
			tmp_sub_expr             = *this_sub_expr;
			if ((return_code = EEC_ResolveFunc(formula_ptr, &tmp_sub_expr,
				optimize_flag, decimal_point, op_alias_count, op_alias_list,
				func_def_count, func_def_list, func_resolve_func,
				symbol_parse_func, symbol_parse_data, sub_expr_count,
				sub_expr_list, sub_expr_alloc, sub_expr_gran, eval_ptr,
				&current_index, error_text)) != EEC_SUCCESS) {
				start_index = current_index;
				goto EXIT_FUNCTION;
			}
			this_sub_expr  = *sub_expr_list + this_sub_index;
			*this_sub_expr = tmp_sub_expr;
			last_context   = this_sub_expr->expr_type;
		}
		else if (strchr("^*/\\%+-<>=&|#!", *start_ptr)) {
			if ((last_context == EEC_TYPE_BEGIN) ||
				(last_context & EEC_TYPE_OPERATOR)) {
				strcpy(error_text,
					"Operator must follow a numeric or string sub-expression.");
				return_code = EEC_FAILURE;
				goto EXIT_FUNCTION;
			}
			return_code = EEC_FAILURE;
			for (count_1 = 0; count_1 < EEC_OperatorAliasCount; count_1++) {
				if (!strnicmp(start_ptr,
					EEC_OperatorAliasList[count_1].operator_alias,
					EEC_OperatorAliasList[count_1].operator_alias_length)) {
					this_op = EEC_OperatorList +
						EEC_OperatorAliasList[count_1].operator_index;
					if ((last_context & EEC_TYPE_NUMBER) &&
						(this_op->operator_type & EEC_TYPE_STRING)) {
						strcpy(error_text, "String operators may be applied only \
to string values.");
						return_code = EEC_FAILURE;
						goto EXIT_FUNCTION;
					}
					else if ((last_context & EEC_TYPE_STRING) &&
						(this_op->operator_type & EEC_TYPE_NUMBER)) {
						strcpy(error_text, "Numeric operators may be applied only \
to numeric values.");
						return_code = EEC_FAILURE;
						goto EXIT_FUNCTION;
					}
					current_index             = (start_index +
						EEC_OperatorAliasList[count_1].operator_alias_length) - 1;
					this_sub_expr->end_index  = current_index;
					this_sub_expr->expr_type  = this_op->operator_type;
					this_sub_expr->expr_spec  =
						((unsigned long) EEC_OperatorAliasList[count_1].
						operator_index);
					this_sub_expr->expr_flags = EEC_SUB_EXPR_FLAG_NONE;
					last_context              = this_op->operator_type;
					return_code               = EEC_SUCCESS;
					break;
				}
			}
			if (return_code != EEC_SUCCESS) {
				sprintf(error_text, "Invalid or unknown token encountered.");
				goto EXIT_FUNCTION;
			}
		}
		else if ((symbol_parse_func != NULL) && ((return_code =
			(*symbol_parse_func)(formula_ptr + this_sub_expr->start_index,
			(end_index - this_sub_expr->start_index) + 1, symbol_parse_data,
			&tmp_expr_type, &tmp_expr_spec, &current_index, error_text)) ==
			EEC_SUCCESS)) {
			current_index            = (this_sub_expr->start_index +
				current_index) - 1;
			this_sub_expr->expr_spec = tmp_expr_spec;
			this_sub_expr->end_index = current_index;
			this_sub_expr->expr_type = tmp_expr_type | EEC_TYPE_SYMBOL;
			last_context             = this_sub_expr->expr_type;
		}
		else {
			strcpy(error_text, "Invalid or unknown token encountered.");
			return_code = EEC_FAILURE;
			goto EXIT_FUNCTION;
		}
		start_index = current_index + 1;
		start_ptr   = formula_ptr + start_index;
	}

	if (last_context & EEC_TYPE_OPERATOR) {
		sprintf(error_text,
			"%s operator ('%-*.*s') must be followed by a %ssub-expression.",
			EEC_OperatorList[((unsigned int) this_sub_expr->expr_spec)].
			operator_name,
			((int) ((this_sub_expr->end_index - this_sub_expr->start_index) + 1)),
			((int) ((this_sub_expr->end_index - this_sub_expr->start_index) + 1)),
			formula_ptr + this_sub_expr->start_index,
			(last_context & EEC_TYPE_NUMBER) ? "numeric " :
			(last_context & EEC_TYPE_STRING) ? "string " : "");
		*error_text = STRFUNCS_toupper(*error_text);
		start_index = this_sub_expr->start_index;
		return_code = EEC_FAILURE;
	}
	else if ((return_code = EEC_AssemblePostFix(formula_ptr, this_expr,
		optimize_flag, *sub_expr_count - old_sub_expr_count,
		*sub_expr_list + old_sub_expr_count, eval_ptr, &start_index,
		error_text)) == EEC_SUCCESS) {
		while (*sub_expr_count > old_sub_expr_count)
			EEC_FREE_SubExprPtr(*sub_expr_list + --(*sub_expr_count));
	}

EXIT_FUNCTION:

	if (return_code != EEC_SUCCESS) {
		while (*sub_expr_count > old_sub_expr_count)
			EEC_FREE_SubExprPtr(*sub_expr_list + --(*sub_expr_count));
	}

	*parse_index = start_index;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_ResolveFunc(const char *formula_ptr, EEC_SUB_EXPR *this_expr,
	int optimize_flag, const char *decimal_point, unsigned int op_alias_count,
	const EEC_PARSE_OP_ALIAS *op_alias_list, unsigned int func_def_count,
	const EEC_FUNC_DEF *func_def_list,
	int (*func_resolve_func)(const char *, const EEC_FUNC_DEF *, unsigned int,
		unsigned int, unsigned int, unsigned int *, char *),
	EEC_SymbolParseFunc symbol_parse_func, void *symbol_parse_data,
	unsigned int *sub_expr_count, EEC_SUB_EXPR **sub_expr_list,
	unsigned int *sub_expr_alloc, unsigned int sub_expr_gran,
	EEC_EVAL_DATA *eval_ptr, unsigned int *parse_index, char *error_text)
#else
static int EEC_ResolveFunc(formula_ptr, this_expr, optimize_flag,
	decimal_point, op_alias_count, op_alias_list, func_def_count,
	func_def_list, func_resolve_func, symbol_parse_func, symbol_parse_data,
	sub_expr_count, sub_expr_list, sub_expr_alloc, sub_expr_gran, eval_ptr,
	parse_index, error_text)
const char                *formula_ptr;
EEC_SUB_EXPR              *this_expr;
int                        optimize_flag;
const char                *decimal_point;
unsigned int               op_alias_count;
const EEC_PARSE_OP_ALIAS  *op_alias_list;
unsigned int               func_def_count;
const EEC_FUNC_DEF        *func_def_list;
#ifndef NARGS
int                      (*func_resolve_func)(const char *,
									const EEC_FUNC_DEF *, unsigned int, unsigned int,
									unsigned int, unsigned int *, char *);
#else
int                      (*func_resolve_func)();
#endif /* #ifndef NARGS */
EEC_SymbolParseFunc        symbol_parse_func;
void                      *symbol_parse_data;
unsigned int              *sub_expr_count;
EEC_SUB_EXPR             **sub_expr_list;
unsigned int              *sub_expr_alloc;
unsigned int               sub_expr_gran;
EEC_EVAL_DATA             *eval_ptr;
unsigned int              *parse_index;
char                      *error_text;
#endif /* #ifndef NARGS */
{
	int                 return_code;
	unsigned int        arg_count     = 0;
	unsigned int        last_arg_type = 0;
	unsigned int        start_index;
	unsigned int        end_index;
	unsigned int        current_index;
	unsigned int        end_arg_index;
	unsigned int        func_name_length;
	EEC_SUB_EXPR        tmp_expr;
	EEC_POSTFIX         tmp_postfix;
	const EEC_FUNC_DEF *func_def_ptr;
	EEC_FUNC_DEF        func_data;
	unsigned int        func_index;
   const char         *tmp_ptr;
	char                tmp_func_name[EEC_MAX_FUNC_NAME_LENGTH + 1];
	unsigned int        func_type;
	unsigned int        expected_arg_type_1;
	unsigned int        expected_arg_type_2;
	unsigned int        builtin_func_def_count;
	const EEC_FUNC_DEF *builtin_func_def_list;

	current_index = this_expr->start_index;
	end_index     = this_expr->end_index;

	EEC_INIT_EEC_POSTFIX(&tmp_postfix);

	EEC_GetBuiltInFuncDefs(&builtin_func_def_count, &builtin_func_def_list);

	if (this_expr->start_index == this_expr->end_index) {
		strcpy(error_text, "Expected function name in expression.");
		return_code = EEC_FAILURE;
		goto EXIT_FUNCTION;
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		To determine the name of the function, we start after the '@'	*/
	/* at-sign and proceed until we find the opening parenthesis ('(')	*/
	/*	which contains the function arguments.										*/
	/*																							*/
	/*		While doing this, we check for valid characters in the name.	*/
	/*	*****************************************************************	*/
	start_index = this_expr->start_index + 1;
	tmp_ptr     = formula_ptr + start_index;
	if (*tmp_ptr == '(') {
		strcpy(error_text, "Function name expected.");
		current_index = start_index;
		return_code   = EEC_FAILURE;
		goto EXIT_FUNCTION;
	}
	while ((start_index <= this_expr->end_index) && (*tmp_ptr != '(')) {
		if ((!isalnum(*tmp_ptr)) && (*tmp_ptr != '_') && (*tmp_ptr != '-') &&
			(*tmp_ptr != '$')) {
			strcpy(error_text,
				"Invalid characters encountered in function name.");
			current_index = start_index;
			return_code   = EEC_FAILURE;
			goto EXIT_FUNCTION;
		}
		start_index++;
		tmp_ptr++;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If we got to the end of the formula without finding the opening*/
	/*	parenthesis, something's wrong . . .										*/
	/*	*****************************************************************	*/
	if (*tmp_ptr != '(') {
		strcpy(error_text, "Function opening parenthesis not found.");
		return_code = EEC_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Otherwise, we can now determine the length of the name of the	*/
	/*	function --- which could be empty (viz. '@()') or longer than the	*/
	/*	maximum function name length.													*/
	/*	*****************************************************************	*/
	if ((func_name_length =
		((start_index - this_expr->start_index) - 1)) == 0) {
		strcpy(error_text, "Function name expected.");
		return_code = EEC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (func_name_length > EEC_MAX_FUNC_NAME_LENGTH) {
		strcpy(error_text, "Unknown function name encountered.");
		return_code = EEC_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now we go looking for the end of the parenthetical expression	*/
	/*	opened by the function.															*/
	/*	*****************************************************************	*/
	if ((return_code = EEC_DetermineParendString(formula_ptr, start_index,
		this_expr->end_index, &current_index, error_text)) != EEC_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Here we go looking to see if we can find the function . . .		*/
	/*	*****************************************************************	*/
	nstrcpy(tmp_func_name, formula_ptr + this_expr->start_index + 1,
		func_name_length);
	if ((func_def_ptr = EEC_FindFuncDef(builtin_func_def_count,
		builtin_func_def_list, tmp_func_name, &func_index)) != NULL) {
		func_data           = *func_def_ptr;
		func_data.func_spec = ((unsigned long) func_index);
		func_def_ptr        = &func_data;
	}
	else if (((func_def_ptr = EEC_FindFuncDef(func_def_count, func_def_list,
		tmp_func_name, &func_index)) != NULL) && (func_resolve_func != NULL)) {
		if ((return_code = (*func_resolve_func)(formula_ptr, func_def_ptr,
			this_expr->start_index, this_expr->end_index, start_index - 1,
			&current_index, error_text)) != EEC_SUCCESS)
			goto EXIT_FUNCTION;
	}
	if (func_def_ptr == NULL) {
		sprintf(error_text, "Unknown function name encountered ('%s').",
			tmp_func_name);
		current_index = this_expr->start_index;
		return_code   = EEC_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Here we perform some checking of the function definition type	*/
	/*	and argument specifications so that we needn't do the checking		*/
	/*	within the argument parsing logic:											*/
	/*																							*/
	/*		1)	Ensure that the first argument (if any) doesn't specify		*/
	/*			that its type is the same as the previous argument.			*/
	/*																							*/
	/*		2) Ensure that if the return type of the function is				*/
	/*			specified as the type of one of the function arguments		*/
	/*			said argument is required (that is, within the set of			*/
	/*			the minimum number of arguments required).						*/
	/*																							*/
	/*		3)	Ensure that the return type of the function is valid.			*/
	/*	*****************************************************************	*/
	if (func_def_ptr->func_max_args &&
		(func_def_ptr->func_args[0] == EEC_FUNC_ARG_TYPE_PREVIOUS)) {
		sprintf(error_text, "%s: %s '%s' %s.", "Invalid function specification",
			"the first argument type for function", tmp_func_name,
			"is specified as being the same as the previous argument");
		current_index = this_expr->start_index;
		return_code   = EEC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((func_def_ptr->func_type == EEC_FUNC_ARG_TYPE_ANY) &&
		(func_def_ptr->func_type_arg >= func_def_ptr->func_min_args)) {
		sprintf(error_text, "%s: %s '%s' %s.", "Invalid function specification",
			"the return type for function", tmp_func_name,
			"is specified as being the same as the ");
		ordinal_full(((unsigned long) func_def_ptr->func_type_arg) + 1L,
			error_text + strlen(error_text));
		sprintf(error_text + strlen(error_text), " argument, %s is %u.",
			"but the minimum number of arguments", func_def_ptr->func_min_args);
		current_index = this_expr->start_index;
		return_code   = EEC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((func_def_ptr->func_type != EEC_FUNC_ARG_TYPE_ANY) &&
		(func_def_ptr->func_type != EEC_FUNC_ARG_TYPE_NUMBER) &&
		(func_def_ptr->func_type != EEC_FUNC_ARG_TYPE_STRING)) {
		sprintf(error_text, "%s: %s '%s' %s (%u).",
			"Invalid function specification", "the return type for function",
			tmp_func_name, "is invalid", func_def_ptr->func_type);
		current_index = this_expr->start_index;
		return_code   = EEC_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Fix-up the current expression to refer to the function.			*/
	/*																							*/
	/*		Note that the indices of the expression ('start_index' and		*/
	/*	'end_index') are the first and last characters respectively of		*/
	/*	the function name --- NOT the first and last characters of the		*/
	/*	entire function invocation.													*/
	/*	*****************************************************************	*/
	this_expr->start_index++;
	this_expr->end_index  = start_index - 1;
	this_expr->expr_spec  = func_def_ptr->func_spec;
	this_expr->expr_flags = ((unsigned char)
		((func_def_ptr->volatile_flag == EEC_TRUE) ?
		EEC_SUB_EXPR_FLAG_VOLATILE : EEC_SUB_EXPR_FLAG_NONE));
	func_type             = func_def_ptr->func_type;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now we're ready to locate the function arguments.					*/
	/*	*****************************************************************	*/
/*
	Do argument parsing here.
*/
	while (return_code == EEC_SUCCESS) {
		if ((return_code = EEC_DetermineArgString(formula_ptr, start_index,
			end_index, &end_arg_index, error_text)) != EEC_SUCCESS) {
			start_index = current_index;
			goto EXIT_FUNCTION;
		}
		current_index = end_arg_index;
		tmp_ptr       = formula_ptr + current_index;
		if ((start_index + 1) > (current_index - 1)) {
			if (*tmp_ptr == ',') {
				strcpy(error_text, "Empty function argument encountered.");
				return_code = EEC_FAILURE;
				goto EXIT_FUNCTION;
			}
			break;
		}
		tmp_expr                = *this_expr;
		tmp_expr.start_index    = start_index + 1;
		tmp_expr.end_index      = current_index - 1;
		tmp_expr.expr_spec      = 0L;
		tmp_expr.expr_flags     = EEC_SUB_EXPR_FLAG_NONE;
		if ((return_code = EEC_DoBasicParse(formula_ptr, &tmp_expr,
			optimize_flag, decimal_point, op_alias_count, op_alias_list,
			func_def_count, func_def_list, func_resolve_func,
			symbol_parse_func, symbol_parse_data, sub_expr_count, sub_expr_list,
			sub_expr_alloc, sub_expr_gran, eval_ptr, &current_index,
			error_text)) != EEC_SUCCESS)
			goto EXIT_FUNCTION;
		if (this_expr->postfix.length == tmp_expr.postfix.length) {
			if (arg_count || (*tmp_ptr == ',')) {
				strcpy(error_text, "Empty function argument encountered.");
				return_code = EEC_FAILURE;
				goto EXIT_FUNCTION;
			}
			break;
		}
/*
	COMMENT: Assignment of the function argument post-fix string must be
				done here so that a subsequent failure (such as an incorrect
				argument type) results in de-allocation of the post-fix
				memory.
*/
		this_expr->postfix = tmp_expr.postfix;
		if (tmp_expr.expr_flags & EEC_SUB_EXPR_FLAG_VOLATILE)
			this_expr->expr_flags |= EEC_SUB_EXPR_FLAG_VOLATILE;
		if ((func_type == EEC_FUNC_ARG_TYPE_ANY) &&
			(arg_count == func_def_ptr->func_type_arg))
			func_type = tmp_expr.expr_type & EEC_TYPE_BASE_TYPE_MASK;
		if (++arg_count > func_def_ptr->func_max_args)
			break;
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		First determine what sort of argument we expect . . .		*/
		/*	***********************************************************	*/
		expected_arg_type_1 = (arg_count > EEC_FUNC_MAX_FIXED_ARGS) ?
			last_arg_type : func_def_ptr->func_args[arg_count - 1];
		expected_arg_type_2 = (expected_arg_type_1 == EEC_FUNC_ARG_TYPE_ANY) ?
			(tmp_expr.expr_type & EEC_TYPE_BASE_TYPE_MASK) :
			(expected_arg_type_1 == EEC_FUNC_ARG_TYPE_PREVIOUS) ? last_arg_type :
			expected_arg_type_1;
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Determine whether the argument is of the correct type.	*/
		/*	***********************************************************	*/
		if ((expected_arg_type_1 == EEC_FUNC_ARG_TYPE_PREVIOUS) &&
			(expected_arg_type_2 !=
			(tmp_expr.expr_type & EEC_TYPE_BASE_TYPE_MASK))) {
			strcpy(error_text, "Invalid argument: expected the ");
			ordinal_full(((unsigned long) arg_count),
				error_text + strlen(error_text));
			sprintf(error_text + strlen(error_text), "%s '@%s()' %s (%s %s %s).",
				" argument to the function", tmp_func_name,
				"to be the same type as the previous argument", "that is, a",
				(expected_arg_type_2 == EEC_FUNC_ARG_TYPE_NUMBER) ? "numeric" :
				"string", "sub-expression");
			current_index = tmp_expr.start_index;
			return_code   = EEC_FAILURE;
			goto EXIT_FUNCTION;
		}
		else if (((expected_arg_type_2 == EEC_FUNC_ARG_TYPE_NUMBER) &&
			(!(tmp_expr.expr_type & EEC_TYPE_NUMBER))) ||
			((expected_arg_type_2 == EEC_FUNC_ARG_TYPE_STRING) &&
			(!(tmp_expr.expr_type & EEC_TYPE_STRING)))) {
			strcpy(error_text, "Invalid argument: expected the ");
			ordinal_full(((unsigned long) arg_count),
				error_text + strlen(error_text));
			sprintf(error_text + strlen(error_text),
				" argument to the function '@%s()' to be a %s sub-expression.",
				tmp_func_name, (expected_arg_type_2 == EEC_FUNC_ARG_TYPE_NUMBER) ?
				"numeric" : "string");
			current_index = tmp_expr.start_index;
			return_code   = EEC_FAILURE;
			goto EXIT_FUNCTION;
		}
		/*	***********************************************************	*/
		last_arg_type      = expected_arg_type_2;
		start_index        = end_arg_index;
		if (*tmp_ptr == ')')
			break;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Final checks on the number of function arguments . . .			*/
	/*	*****************************************************************	*/
	if (arg_count < func_def_ptr->func_min_args) {
		sprintf(error_text,
			"Expected%s %u %s %s '@%s()', but only %u %s encountered.",
			(func_def_ptr->func_min_args == func_def_ptr->func_max_args) ? "" :
			" a minimum of", func_def_ptr->func_min_args,
			(func_def_ptr->func_min_args == 1) ? "argument" : "arguments",
			"in function", tmp_func_name, arg_count, (arg_count == 1) ? "was" :
			"were");
		return_code = EEC_FAILURE;
	}
	else if (arg_count > func_def_ptr->func_max_args) {
		sprintf(error_text,
			"Expected%s %u %s %s '@%s()', but %u %s encountered.",
			(func_def_ptr->func_min_args == func_def_ptr->func_max_args) ? "" :
			" a maximum of", func_def_ptr->func_max_args,
			(func_def_ptr->func_max_args == 1) ? "argument" : "arguments",
			"in function", tmp_func_name, arg_count, (arg_count == 1) ? "was" :
			"were");
		return_code = EEC_FAILURE;
	}
	else {
		this_expr->expr_type = func_type | EEC_TYPE_FUNCTION;
		tmp_expr             = *this_expr;
		if ((return_code = EEC_AddPostFix(&this_expr->postfix, formula_ptr,
			&tmp_expr, arg_count, error_text)) != EEC_SUCCESS)
			goto EXIT_FUNCTION;
		this_expr->expr_type   = func_type | EEC_TYPE_POSTFIX;
		this_expr->expr_flags &= EEC_SUB_EXPR_FLAG_VOLATILE;
		if ((optimize_flag == EEC_TRUE) &&
			(!(this_expr->expr_flags & EEC_SUB_EXPR_FLAG_VOLATILE)) &&
			((return_code = EEC_OptimizeSubExpr(&tmp_postfix, this_expr,
			eval_ptr, error_text)) == EEC_SUCCESS))
			this_expr->postfix = tmp_postfix;
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (return_code != EEC_SUCCESS)
		EEC_FREE_PostFixPtr(&this_expr->postfix);

	*parse_index = current_index;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_AssemblePostFix(const char *formula_ptr, EEC_SUB_EXPR *this_expr,
	int optimize_flag, unsigned int sub_expr_count, EEC_SUB_EXPR *sub_expr_list,
	EEC_EVAL_DATA *eval_ptr, unsigned int *parse_index, char *error_text)
#else
static int EEC_AssemblePostFix(formula_ptr, this_expr, optimize_flag,
	sub_expr_count, sub_expr_list, eval_ptr, parse_index, error_text)
const char    *formula_ptr;
EEC_SUB_EXPR  *this_expr;
int            optimize_flag;
unsigned int   sub_expr_count;
EEC_SUB_EXPR  *sub_expr_list;
EEC_EVAL_DATA *eval_ptr;
unsigned int  *parse_index;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int                       return_code = EEC_SUCCESS;
	const char               *tmp_ptr;
	unsigned int              count_1;
	unsigned int              count_2;
	unsigned int              count_3;
	unsigned int              count_4;
	EEC_SUB_EXPR             *this_sub_expr;
	EEC_SUB_EXPR              tmp_sub_expr;
	const EEC_PARSE_CANON_OP *operator_ptr;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Re-order any sub-expressions by operator precedence.				*/
	/*																							*/
	/*		1) For each of the defined precedence levels, check to see		*/
	/*			any operators at that level are used in the expression.		*/
	/*			We start at the highest precedence level and work our way	*/
	/*			downward.																	*/
	/*																							*/
	/*		2)	For each sub-expression using an operator having the			*/
	/*			current precedence level, re-order the terms of the sub-		*/
	/*			expression from infix to postfix notation by moving the		*/
	/*			'EEC_SUB_EXPR' element representing the operator to follow	*/
	/*			the second sub-expression operand.									*/
	/*																							*/
	/*		When the loop is finished, the expression has re-ordered each	*/
	/*	term in the order needed to generate the postfix string.				*/
	/*	*****************************************************************	*/
	if (sub_expr_count > 2) {
		for (count_1 = (EEC_OPERATOR_PRECEDENCE_HIGH + 1);
			count_1 > EEC_OPERATOR_PRECEDENCE_LOW; ) {
			count_1--;
			for (count_2 = 1; count_2 < (sub_expr_count - 1); count_2++) {
				this_sub_expr = sub_expr_list + count_2;
				if ((!(this_sub_expr->expr_flags & EEC_SUB_EXPR_FLAG_DONE)) &&
					(this_sub_expr->expr_type & EEC_TYPE_OPERATOR) &&
					(EEC_OperatorList[((unsigned int) this_sub_expr->expr_spec)].
					precedence == count_1)) {
					for (count_3 = (count_2 + 1); count_3 < sub_expr_count;
						count_3++) {
						if (!(sub_expr_list[count_3].expr_flags &
							EEC_SUB_EXPR_FLAG_DONE))
							break;
					}
					if (count_2 == (count_3 - 1)) {
						tmp_sub_expr           = sub_expr_list[count_2];
						sub_expr_list[count_2] = sub_expr_list[count_3];
						sub_expr_list[count_3] = tmp_sub_expr;
						sub_expr_list[count_2 - 1].expr_flags |=
							EEC_SUB_EXPR_FLAG_DONE;
						sub_expr_list[count_2].expr_flags     |=
							EEC_SUB_EXPR_FLAG_DONE;
						sub_expr_list[count_3].expr_flags     |=
							EEC_SUB_EXPR_FLAG_DONE;
					}
					else if (count_3 < sub_expr_count) {
						tmp_sub_expr = sub_expr_list[count_2];
						for (count_4 = count_2; count_4 < count_3; count_4++)
							sub_expr_list[count_4] = sub_expr_list[count_4 + 1];
						sub_expr_list[count_3]                 = tmp_sub_expr;
						sub_expr_list[count_2 - 1].expr_flags |=
							EEC_SUB_EXPR_FLAG_DONE;
						sub_expr_list[count_2].expr_flags     |=
							EEC_SUB_EXPR_FLAG_DONE;
						sub_expr_list[count_3].expr_flags     |=
							EEC_SUB_EXPR_FLAG_DONE;
					}
					else {
						tmp_sub_expr = sub_expr_list[count_2];
						for (count_4 = count_2; count_4 < (count_3 - 1); count_4++)
							sub_expr_list[count_4] = sub_expr_list[count_4 + 1];
						sub_expr_list[--count_3]               = tmp_sub_expr;
						sub_expr_list[count_2 - 1].expr_flags |=
							EEC_SUB_EXPR_FLAG_DONE;
						sub_expr_list[count_2].expr_flags     |=
							EEC_SUB_EXPR_FLAG_DONE;
						sub_expr_list[count_3].expr_flags     |=
							EEC_SUB_EXPR_FLAG_DONE;
					}
				}
			}
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Check operand types by processing them on an evaluation stack.	*/
	/*																							*/
	/*	We don't actually do any real work, we just push the types onto	*/
	/*	the stack and then check for each operator type that the correct	*/
	/*	types are available . . .														*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < sub_expr_count; count_1++) {
		if (sub_expr_list[count_1].expr_type & EEC_TYPE_OPERATOR) {
			operator_ptr = EEC_OperatorList +
				((unsigned int) sub_expr_list[count_1].expr_spec);
			tmp_ptr      = NULL;
			if (operator_ptr->operator_type & EEC_TYPE_REL_OP) {
				if (EEC_EVAL_TOP_IS_NUMBER(eval_ptr) !=
					EEC_EVAL_TREF_IS_NUMBER(eval_ptr, -1)) {
					tmp_ptr     = "sub-expressions of the same type";
					return_code = EEC_FAILURE;
				}
				else {
					EEC_EVAL_POP(eval_ptr);
					EEC_EVAL_POP(eval_ptr);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, 0.0);
				}
			}
			else if (operator_ptr->operator_type & EEC_TYPE_BOOL_OP) {
				EEC_EVAL_POP(eval_ptr);
				EEC_EVAL_POP(eval_ptr);
				EEC_EVAL_PUSH_NUMBER(eval_ptr, 0.0);
			}
			else if (operator_ptr->operator_type & EEC_TYPE_NUMBER_OP) {
				if ((!EEC_EVAL_TOP_IS_NUMBER(eval_ptr)) ||
					(!EEC_EVAL_TREF_IS_NUMBER(eval_ptr, -1))) {
					tmp_ptr     = "numeric sub-expressions";
					return_code = EEC_FAILURE;
				}
				else {
					EEC_EVAL_POP(eval_ptr);
					EEC_EVAL_POP(eval_ptr);
					EEC_EVAL_PUSH_NUMBER(eval_ptr, 0.0);
				}
			}
			else if (operator_ptr->operator_type & EEC_TYPE_STRING_OP) {
				if ((!EEC_EVAL_TOP_IS_STRING(eval_ptr)) ||
					(!EEC_EVAL_TREF_IS_STRING(eval_ptr, -1))) {
					tmp_ptr     = "string sub-expressions";
					return_code = EEC_FAILURE;
				}
				else {
					EEC_EVAL_POP(eval_ptr);
					EEC_EVAL_POP(eval_ptr);
					EEC_EVAL_PUSH_STRING_EMPTY(eval_ptr);
				}
			}
			else {								/*	We can't determine the operator!	*/
				tmp_ptr = (tmp_ptr != NULL) ? tmp_ptr : "unknown";
				sprintf(error_text, "%s ('%*.*s') --- operator type = %u.",
					"Unknown operator encountered in sub-expression",
					((int) (sub_expr_list[count_1].end_index -
					sub_expr_list[count_1].start_index)) + 1,
					((int) (sub_expr_list[count_1].end_index -
					sub_expr_list[count_1].start_index)) + 1, formula_ptr +
					sub_expr_list[count_1].start_index,
					operator_ptr->operator_type);
				*parse_index = sub_expr_list[count_1].start_index;
				goto EXIT_FUNCTION;
			}
			if (return_code != EEC_SUCCESS) {
				sprintf(error_text, "%s %s %s %s ('%*.*s') operator.",
					"Expected two", tmp_ptr, "on either side of the",
					operator_ptr->operator_name,
					((int) (sub_expr_list[count_1].end_index -
					sub_expr_list[count_1].start_index)) + 1,
					((int) (sub_expr_list[count_1].end_index -
					sub_expr_list[count_1].start_index)) + 1, formula_ptr +
					sub_expr_list[count_1].start_index);
				*parse_index = sub_expr_list[count_1].start_index;
				goto EXIT_FUNCTION;
			}
		}
		else if ((EEC_EVAL_NEED_MORE_STACK(eval_ptr) == EEC_TRUE) &&
			((return_code = EEC_EVAL_StackAllocBasic(eval_ptr,
			error_text)) != EEC_SUCCESS)) {
			*parse_index = sub_expr_list[count_1].start_index;
			goto EXIT_FUNCTION;
		}
		else if (sub_expr_list[count_1].expr_type & EEC_TYPE_NUMBER)
			EEC_EVAL_PUSH_NUMBER(eval_ptr, 0.0);
		else
			EEC_EVAL_PUSH_STRING_EMPTY(eval_ptr);
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		The type of this sub-expression is now on the stack . . .		*/
	/*	*****************************************************************	*/
	this_expr->expr_type  |= (!sub_expr_count) ? 0 :
		(eval_ptr->eval_stack_top->flags | EEC_TYPE_POSTFIX);
	this_expr->expr_flags &= EEC_SUB_EXPR_FLAG_DONE;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If requested, optimize the expression . . .							*/
	/*	*****************************************************************	*/
	if ((optimize_flag == EEC_TRUE) && sub_expr_count) {
		return_code = EEC_OptimizeExpr(formula_ptr, this_expr, sub_expr_count,
			sub_expr_list, eval_ptr, parse_index, error_text);
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Generate the post-fix string . . .										*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < sub_expr_count; count_1++) {
		if ((return_code = EEC_AddPostFix(&this_expr->postfix, formula_ptr,
			sub_expr_list + count_1, 0, error_text)) != EEC_SUCCESS) {
			*parse_index = sub_expr_list[count_1].start_index;
			goto EXIT_FUNCTION;
		}
		this_expr->expr_flags |= sub_expr_list[count_1].expr_flags;
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		This is the place that we would normally place a call to the	*/
	/*	function 'EEC_EVAL_StackClear()', but as we happen to know that	*/
	/*	no strings have been allocated on the stack, we just reset the		*/
	/*	stack indicators.																	*/
	/*	*****************************************************************	*/
	eval_ptr->eval_stack_count = 0;
	eval_ptr->eval_stack_top   = eval_ptr->eval_stack;
	/*	*****************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_OptimizeExpr(const char *formula_ptr, EEC_SUB_EXPR *this_expr,
	unsigned int sub_expr_count, EEC_SUB_EXPR *sub_expr_list,
	EEC_EVAL_DATA *eval_ptr, unsigned int *parse_index, char *error_text)
#else
static int EEC_OptimizeExpr(formula_ptr, this_expr, sub_expr_count,
	sub_expr_list, eval_ptr, parse_index, error_text)
const char    *formula_ptr;
EEC_SUB_EXPR  *this_expr;
unsigned int   sub_expr_count;
EEC_SUB_EXPR  *sub_expr_list;
EEC_EVAL_DATA *eval_ptr;
unsigned int  *parse_index;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code;
	unsigned int operand_count = 0;
	int          volatile_flag = EEC_FALSE;
	unsigned int count_1;
	EEC_POSTFIX  tmp_postfix;
	EEC_SUB_EXPR tmp_sub_expr;

	EEC_EVAL_StackClear(eval_ptr);

	EEC_INIT_EEC_POSTFIX(&tmp_postfix);
	EEC_INIT_EEC_SUB_EXPR(&tmp_sub_expr);

	tmp_sub_expr.expr_type = EEC_TYPE_POSTFIX;

	for (count_1 = 0; count_1 < sub_expr_count; count_1++, sub_expr_list++) {
		if (sub_expr_list->expr_type & EEC_TYPE_OPERATOR) {
			if ((return_code = EEC_AddPostFix(&tmp_sub_expr.postfix, formula_ptr,
				sub_expr_list, 0, error_text)) != EEC_SUCCESS) {
				*parse_index = sub_expr_list->start_index;
				goto EXIT_FUNCTION;
			}
			if (operand_count > 1) {
				if ((return_code = EEC_OptimizeSubExpr(&tmp_postfix,
					&tmp_sub_expr, eval_ptr, error_text)) != EEC_SUCCESS) {
					*parse_index = sub_expr_list->start_index;
					goto EXIT_FUNCTION;
				}
				tmp_sub_expr.postfix = tmp_postfix;
				EEC_INIT_EEC_POSTFIX(&tmp_postfix);
				operand_count--;
			}
			else {
				if ((return_code = EEC_AddPostFix(&this_expr->postfix,
					formula_ptr, &tmp_sub_expr, 0, error_text)) != EEC_SUCCESS) {
					*parse_index = sub_expr_list->start_index;
					goto EXIT_FUNCTION;
				}
				operand_count = 0;
			}
		}
		else if (sub_expr_list->expr_flags & EEC_SUB_EXPR_FLAG_VOLATILE) {
			if ((return_code = EEC_OptimizeSubExpr(&this_expr->postfix,
				&tmp_sub_expr, eval_ptr, error_text)) != EEC_SUCCESS) {
				*parse_index = sub_expr_list->start_index;
				goto EXIT_FUNCTION;
			}
			if ((return_code = EEC_AddPostFix(&this_expr->postfix, formula_ptr,
				sub_expr_list, 0, error_text)) != EEC_SUCCESS) {
				*parse_index = sub_expr_list->start_index;
				goto EXIT_FUNCTION;
			}
			volatile_flag = EEC_TRUE;
			operand_count = 0;
		}
		else if ((return_code = EEC_AddPostFix(&tmp_sub_expr.postfix,
			formula_ptr, sub_expr_list, 0, error_text)) != EEC_SUCCESS) {
			*parse_index = sub_expr_list->start_index;
			goto EXIT_FUNCTION;
		}
		else
			operand_count++;
	}

	return_code = EEC_OptimizeSubExpr(&this_expr->postfix, &tmp_sub_expr,
		eval_ptr, error_text);

	this_expr->expr_flags |= (volatile_flag != EEC_TRUE) ? 0 :
		EEC_SUB_EXPR_FLAG_VOLATILE;

EXIT_FUNCTION:

	EEC_FREE_PostFixPtr(&tmp_sub_expr.postfix);

	EEC_EVAL_StackClear(eval_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_OptimizeSubExpr(EEC_POSTFIX *postfix_ptr,
	EEC_SUB_EXPR *sub_expr_ptr, EEC_EVAL_DATA *eval_ptr, char *error_text)
#else
static int EEC_OptimizeSubExpr(postfix_ptr, sub_expr_ptr, eval_ptr,
	error_text)
EEC_POSTFIX   *postfix_ptr;
EEC_SUB_EXPR  *sub_expr_ptr;
EEC_EVAL_DATA *eval_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = EEC_SUCCESS;

	if (sub_expr_ptr->postfix.length) {
		eval_ptr->postfix_ptr        = &sub_expr_ptr->postfix;
		eval_ptr->postfix_data_index = 0;
		eval_ptr->postfix_data_ptr   = sub_expr_ptr->postfix.data;
		if ((return_code = EEC_EvalBasic(eval_ptr)) != EEC_SUCCESS)
			strcpy(error_text, eval_ptr->error_text);
		else
			return_code =
				EEC_AppStackToPostFix(eval_ptr->eval_stack_count,
				eval_ptr->eval_stack, postfix_ptr, error_text);
		EEC_FREE_PostFixPtr(&sub_expr_ptr->postfix);
		EEC_EVAL_StackClear(eval_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_AppStackToPostFix(unsigned int stack_count,
	const EEC_DATUM *stack_list, EEC_POSTFIX *postfix_ptr, char *error_text)
#else
static int EEC_AppStackToPostFix(stack_count, stack_list, postfix_ptr,
	error_text)
unsigned int     stack_count;
const EEC_DATUM *stack_list;
EEC_POSTFIX     *postfix_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code  = EEC_SUCCESS;
	unsigned int  added_length = 0;
	unsigned int  count_1;
	unsigned int  length;
	char         *pfix_ptr;

	for (count_1 = 0; count_1 < stack_count; count_1++)
		added_length += (EEC_EVAL_DATUM_IS_NUMBER(stack_list + count_1)) ?
			(1 + sizeof(double)) : (1 + sizeof(unsigned int) +
			stack_list[count_1].datum.string.length + 1);

	if (added_length) {
		if ((return_code = EEC_AllocPostFix(postfix_ptr, added_length,
			error_text)) == EEC_SUCCESS) {
			pfix_ptr = postfix_ptr->data + postfix_ptr->length;
			for (count_1 = 0; count_1 < stack_count; count_1++, stack_list++) {
				if (EEC_EVAL_DATUM_IS_NUMBER(stack_list)) {
					*pfix_ptr = EEC_PFIX_TYPE_NUMBER;
					memcpy(pfix_ptr + 1, &stack_list->datum.number, sizeof(double));
					length = 1 + sizeof(double);
				}
				else {
					*pfix_ptr = EEC_PFIX_TYPE_STRING;
					memcpy(pfix_ptr + 1, &stack_list->datum.string.length,
						sizeof(unsigned int));
					memcpy(pfix_ptr + 1 + sizeof(unsigned int),
						stack_list->datum.string.data,
						stack_list->datum.string.length + 1);
					length = 1 + sizeof(unsigned int) +
						stack_list->datum.string.length + 1;
				}
				postfix_ptr->length += length;
				pfix_ptr            += length;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_AddPostFix(EEC_POSTFIX *postfix_ptr, const char *formula_ptr,
	EEC_SUB_EXPR *this_expr, unsigned int argument_count, char *error_text)
#else
static int EEC_AddPostFix(postfix_ptr, formula_ptr, this_expr, argument_count,
	error_text)
EEC_POSTFIX  *postfix_ptr;
const char   *formula_ptr;
EEC_SUB_EXPR *this_expr;
unsigned int  argument_count;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code;
	unsigned int    tmp_length;
	unsigned int    tmp_int;
	unsigned short  tmp_short;
	double          tmp_value;
   unsigned short  tmp_arg_count;
	char           *value_end_ptr;
	char            number_buffer[EEC_MAX_NUMBER_LENGTH + 1];

	if (this_expr->expr_type == EEC_TYPE_NUMBER) {
		nstrcpy(number_buffer, formula_ptr + this_expr->start_index,
			(this_expr->end_index - this_expr->start_index) + 1);
		tmp_value = strtod(number_buffer, &value_end_ptr);
		if (value_end_ptr != (number_buffer +
			(this_expr->end_index - this_expr->start_index) + 1)) {
			sprintf(error_text, "%s %s '%s' --- %s %s: '%s'.",
				"Internal logic and 'strtod()' disagree about the end of the",
				"numeric value", number_buffer,
				"'strtod()' reports that the following string does not",
				"constitute part of the numeric value", value_end_ptr);
			return_code = EEC_FAILURE;
		}
		else if ((return_code = EEC_AllocPostFix(postfix_ptr,
			1 + sizeof(double), error_text)) == EEC_SUCCESS) {
			postfix_ptr->data[postfix_ptr->length++] = EEC_PFIX_TYPE_NUMBER;
			memcpy(postfix_ptr->data + postfix_ptr->length, &tmp_value,
				sizeof(double));
			postfix_ptr->length += sizeof(double);
		}
	}
	else if (this_expr->expr_type == EEC_TYPE_STRING) {
		tmp_int   = (this_expr->end_index < this_expr->start_index) ? 0 :
			((unsigned int) ((this_expr->end_index -
			this_expr->start_index) + 1));
		tmp_length = (!tmp_int) ? 0 : cstr2mem_basic_length(tmp_int,
			formula_ptr + this_expr->start_index, 0);
		if ((return_code = EEC_AllocPostFix(postfix_ptr,
			1 + sizeof(unsigned int) + tmp_length + 1, error_text)) ==
			EEC_SUCCESS) {
			postfix_ptr->data[postfix_ptr->length++] = EEC_PFIX_TYPE_STRING;
			memcpy(postfix_ptr->data + postfix_ptr->length, &tmp_length,
				sizeof(unsigned int));
			postfix_ptr->length += sizeof(unsigned int);
			if (tmp_int) {
				cstr2mem_basic(tmp_int, formula_ptr + this_expr->start_index,
					0, NULL, postfix_ptr->data + postfix_ptr->length);
				postfix_ptr->length += tmp_length;
			}
			postfix_ptr->data[postfix_ptr->length++] = '\0';
		}
	}
	else if (this_expr->expr_type & EEC_TYPE_FUNCTION) {
		tmp_short = ((unsigned short)
			((this_expr->end_index - this_expr->start_index) + 1));
		if ((return_code = EEC_AllocPostFix(postfix_ptr, ((unsigned int)
			(1 + sizeof(unsigned long) + (sizeof(unsigned short) * 2) +
			tmp_short)), error_text)) == EEC_SUCCESS) {
			postfix_ptr->data[postfix_ptr->length++] = EEC_PFIX_TYPE_FUNCTION;
			memcpy(postfix_ptr->data + postfix_ptr->length,
				&this_expr->expr_spec, sizeof(unsigned long));
			postfix_ptr->length += sizeof(unsigned long);
			tmp_arg_count        = ((unsigned short) argument_count);
			memcpy(postfix_ptr->data + postfix_ptr->length, &tmp_arg_count,
				sizeof(unsigned short));
			postfix_ptr->length += sizeof(unsigned short);
			memcpy(postfix_ptr->data + postfix_ptr->length, &tmp_short,
				sizeof(unsigned short));
			postfix_ptr->length += sizeof(unsigned short);
			memcpy(postfix_ptr->data + postfix_ptr->length,
				formula_ptr + this_expr->start_index, ((unsigned int) tmp_short));
			postfix_ptr->length += ((unsigned int) tmp_short);
		}
#ifdef EEC_DEBUG_PRINT
printf("@-Function  : @%-*.*s()\n",
	((int) ((this_expr->end_index - this_expr->start_index) - 1)),
	((int) ((this_expr->end_index - this_expr->start_index) - 1)),
	formula_ptr + this_expr->start_index + 1);
#endif /* #ifdef EEC_DEBUG_PRINT */
	}
	else if (this_expr->expr_type & EEC_TYPE_SYMBOL) {
		tmp_short = ((unsigned short)
			((this_expr->end_index - this_expr->start_index) + 1));
		if ((return_code = EEC_AllocPostFix(postfix_ptr, ((unsigned int)
			(1 + sizeof(unsigned long) + sizeof(unsigned short) + tmp_short)),
			error_text)) == EEC_SUCCESS) {
			postfix_ptr->data[postfix_ptr->length++] = EEC_PFIX_TYPE_SYMBOL;
			memcpy(postfix_ptr->data + postfix_ptr->length,
				&this_expr->expr_spec, sizeof(unsigned long));
			postfix_ptr->length += sizeof(unsigned long);
			memcpy(postfix_ptr->data + postfix_ptr->length, &tmp_short,
				sizeof(unsigned short));
			postfix_ptr->length += sizeof(unsigned short);
			memcpy(postfix_ptr->data + postfix_ptr->length,
				formula_ptr + this_expr->start_index, ((unsigned int) tmp_short));
			postfix_ptr->length += ((unsigned int) tmp_short);
		}
	}
	else if (this_expr->expr_type & EEC_TYPE_OPERATOR) {
		if ((return_code = EEC_AllocPostFix(postfix_ptr, 1, error_text)) ==
			EEC_SUCCESS)
			postfix_ptr->data[postfix_ptr->length++] =
				((char) this_expr->expr_spec);
	}
	else if (this_expr->expr_type & EEC_TYPE_POSTFIX) {
		if ((return_code = EEC_AllocPostFix(postfix_ptr,
			this_expr->postfix.length, error_text)) == EEC_SUCCESS) {
			memcpy(postfix_ptr->data + postfix_ptr->length,
				this_expr->postfix.data, this_expr->postfix.length);
			postfix_ptr->length += this_expr->postfix.length;
			EEC_FREE_PostFixPtr(&this_expr->postfix);
		}
	}
	else {
		sprintf(error_text, "%s: invalid expression type encountered (%u).",
			"Internal error on post-fix expansion", this_expr->expr_type);
		return_code = EEC_FAILURE;
	}

	if (return_code == EEC_SUCCESS)
		this_expr->expr_flags &= EEC_SUB_EXPR_FLAG_DONE;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_AllocPostFix(EEC_POSTFIX *postfix_ptr, unsigned int added_length,
	char *error_text)
#else
static int EEC_AllocPostFix(postfix_ptr, added_length, error_text)
EEC_POSTFIX  *postfix_ptr;
unsigned int  added_length;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = EEC_SUCCESS;
	unsigned long  old_length;
	unsigned long  new_length;
	char          *tmp_ptr;

	old_length = postfix_ptr->length;
	old_length = ((old_length / ((unsigned long) EEC_POSTFIX_GRAN)) +
		((old_length % ((unsigned long) EEC_POSTFIX_GRAN)) ? 1L : 0L)) *
		((unsigned long) EEC_POSTFIX_GRAN);
	new_length = ((unsigned long) postfix_ptr->length) +
		((unsigned long) added_length);
	new_length = ((new_length / ((unsigned long) EEC_POSTFIX_GRAN)) +
		((new_length % ((unsigned long) EEC_POSTFIX_GRAN)) ? 1L : 0L)) *
		((unsigned long) EEC_POSTFIX_GRAN);

#ifdef __MSDOS__
	if (new_length > ((unsigned long) (UINT_MAX - 15))) {
		sprintf(error_text,
			"%s --- %s (%u) (%s = %u, %s = %u, %s = %lu, %s = %lu).",
			"Unable to allocate memory for the post-fix string",
			"maximum MS-DOS allocation reached", (UINT_MAX - 15),
			"post-fix string allocation granularity", EEC_POSTFIX_GRAN,
			"old post-fix bytes used", postfix_ptr->length,
			"old post-fix bytes allocated", old_length,
			"new post-fix bytes allocated", new_length);
		return_code = EEC_MEMORY_FAILURE;
	}
	else
#endif /* #ifdef __MSDOS__ */
	if (new_length > old_length) {
		if ((tmp_ptr = ((char *) ((!postfix_ptr->length) ?
			malloc(((unsigned int) new_length)) :
			realloc(postfix_ptr->data, ((unsigned int) new_length))))) == NULL) {
			sprintf(error_text,
				"%s --- (%s = %u, %s = %u, %s = %lu, %s = %lu).",
				"Unable to allocate memory for the post-fix string",
				"post-fix string allocation granularity", EEC_POSTFIX_GRAN,
				"old post-fix bytes used", postfix_ptr->length,
				"old post-fix bytes allocated", old_length,
				"new post-fix bytes allocated", new_length);
			return_code = EEC_MEMORY_FAILURE;
		}
		else
			postfix_ptr->data = tmp_ptr;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static const EEC_FUNC_DEF *EEC_FindFuncDef(unsigned int func_def_count,
	const EEC_FUNC_DEF *func_def_list, const char *func_name,
	unsigned int *func_index)
#else
static const EEC_FUNC_DEF *EEC_FindFuncDef(func_def_count, func_def_list,
	func_name, func_index)
unsigned int        func_def_count;
const EEC_FUNC_DEF *func_def_list;
const char         *func_name;
unsigned int       *func_index;
#endif /* #ifndef NARGS */
{
	unsigned int        count_1;
	const EEC_FUNC_DEF *func_def_ptr = NULL;

	for (count_1 = 0; count_1 < func_def_count; count_1++, func_def_list++) {
		if (!stricmp(func_def_list->func_name, func_name)) {
			func_def_ptr = func_def_list;
			*func_index  = count_1;
			break;
		}
	}

	return(func_def_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_DetermineArgString(const char *formula_ptr,
	unsigned int start_index, unsigned int end_index,
	unsigned int *new_end_index, char *error_text)
#else
static int EEC_DetermineArgString(formula_ptr, start_index, end_index,
	new_end_index, error_text)
const char   *formula_ptr;
unsigned int  start_index;
unsigned int  end_index;
unsigned int *new_end_index;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = EEC_SUCCESS;
	unsigned int tmp_end_index;

	*new_end_index = start_index + 1;

	while (*new_end_index <= end_index) {
		if (*(formula_ptr + *new_end_index) == '\"') {
			if ((return_code = EEC_DetermineQuotedString(formula_ptr,
				*new_end_index, end_index, &tmp_end_index, error_text)) !=
				EEC_SUCCESS) {
				*new_end_index = tmp_end_index;
				break;
			}
			*new_end_index = tmp_end_index;
		}
		else if (*(formula_ptr + *new_end_index) == '(') {
			if ((return_code = EEC_DetermineParendString(formula_ptr,
				*new_end_index, end_index, &tmp_end_index, error_text)) !=
				EEC_SUCCESS) {
				*new_end_index = tmp_end_index;
				break;
			}
			*new_end_index = tmp_end_index;
		}
		else if ((*(formula_ptr + *new_end_index) == ',') ||
			(*(formula_ptr + *new_end_index) == ')'))
			break;
		(*new_end_index)++;
	}

	if (return_code == EEC_SUCCESS) {
		if (*new_end_index > end_index) {
			strcpy(error_text, "Unterminated function argument.");
			*new_end_index = start_index;
			return_code    = EEC_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_DetermineParendString(const char *formula_ptr,
	unsigned int start_index, unsigned int end_index,
	unsigned int *new_end_index, char *error_text)
#else
static int EEC_DetermineParendString(formula_ptr, start_index, end_index,
	new_end_index, error_text)
const char   *formula_ptr;
unsigned int  start_index;
unsigned int  end_index;
unsigned int *new_end_index;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code  = EEC_SUCCESS;
	unsigned int parend_count = 1;
	unsigned int tmp_end_index;

	*new_end_index = start_index + 1;

	while ((*new_end_index <= end_index) && parend_count) {
		if (*(formula_ptr + *new_end_index) == '\"') {
			if ((return_code = EEC_DetermineQuotedString(formula_ptr,
				*new_end_index, end_index, &tmp_end_index, error_text)) !=
				EEC_SUCCESS) {
				*new_end_index = tmp_end_index;
				break;
			}
			*new_end_index = tmp_end_index;
		}
		else
			parend_count += (*(formula_ptr + *new_end_index) == '(') ? 1 :
				(*(formula_ptr + *new_end_index) == ')') ? -1 : 0;
		(*new_end_index)++;
	}

	if (return_code == EEC_SUCCESS) {
		if (parend_count) {
			strcpy(error_text, "Unterminated parenthetical expression.");
			*new_end_index = start_index;
			return_code    = EEC_FAILURE;
		}
		else
			(*new_end_index)--;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_DetermineQuotedString(const char *formula_ptr,
	unsigned int start_index, unsigned int end_index,
	unsigned int *new_end_index, char *error_text)
#else
static int EEC_DetermineQuotedString(formula_ptr, start_index, end_index,
	new_end_index, error_text)
const char   *formula_ptr;
unsigned int  start_index;
unsigned int  end_index;
unsigned int *new_end_index;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code = EEC_SUCCESS;
	const char *current_ptr = formula_ptr + start_index + 1;

	*new_end_index = start_index + 1;

	while ((*new_end_index <= end_index) && (*current_ptr != '\"')) {
		if ((*current_ptr == '\\') && (*(current_ptr + 1) == '\"')) {
			current_ptr++;
			(*new_end_index)++;
		}
		current_ptr++;
		(*new_end_index)++;
	}

	if (*new_end_index > end_index) {
		strcpy(error_text, "Unterminated string constant encountered.");
		*new_end_index = start_index;
		return_code    = EEC_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_DetermineNumberString(const char *formula_ptr,
	unsigned int start_index, unsigned int end_index, const char *decimal_point,
	unsigned int *new_end_index)
#else
static int EEC_DetermineNumberString(formula_ptr, start_index, end_index,
	decimal_point, new_end_index)
const char   *formula_ptr;
unsigned int  start_index;
unsigned int  end_index;
const char   *decimal_point;
unsigned int *new_end_index;
#endif /* #ifndef NARGS */
{
	int         number_flag = EEC_FALSE;
	const char *current_ptr = formula_ptr + start_index;

	*new_end_index = start_index;

	if ((*current_ptr == '+') || (*current_ptr == '-')) {
		(*new_end_index)++;
		current_ptr++;
	}
	if (*new_end_index > end_index)
		goto EXIT_FUNCTION;

	while (*new_end_index <= end_index) {
		if (!isdigit(*current_ptr))
			break;
		number_flag = EEC_TRUE;
		(*new_end_index)++;
		current_ptr++;
	}
	if (*new_end_index > end_index)
		goto EXIT_FUNCTION;

	if (*current_ptr == *decimal_point) {
		if (++(*new_end_index) > end_index)
			goto EXIT_FUNCTION;
		current_ptr++;
	}

	while (*new_end_index <= end_index) {
		if (!isdigit(*current_ptr))
			break;
		number_flag = EEC_TRUE;
		(*new_end_index)++;
		current_ptr++;
	}
	if ((*new_end_index > end_index) || (number_flag != EEC_TRUE))
		goto EXIT_FUNCTION;

	if (((*new_end_index + 2) <= end_index) &&
		((*current_ptr == 'e') || (*current_ptr == 'E')) &&
		((current_ptr[1] == '+') || (current_ptr[1] == '-')) &&
		isdigit(current_ptr[2])) {
		*new_end_index += 3;
		current_ptr    += 3;
		while (*new_end_index <= end_index) {
			if (!isdigit(*current_ptr))
				break;
			(*new_end_index)++;
			current_ptr++;
		}
	}

EXIT_FUNCTION:

	(*new_end_index)--;

	return(number_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int EEC_AddSubExpression(unsigned int *sub_expr_count,
	EEC_SUB_EXPR **sub_expr_list, unsigned int *sub_expr_alloc,
	unsigned int sub_expr_gran, char *error_text)
#else
static int EEC_AddSubExpression(sub_expr_count, sub_expr_list, sub_expr_alloc,
	sub_expr_gran, error_text)
unsigned int  *sub_expr_count;
EEC_SUB_EXPR **sub_expr_list;
unsigned int  *sub_expr_alloc;
unsigned int   sub_expr_gran;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = EEC_SUCCESS;
	unsigned long  used_bytes;
	unsigned long  current_bytes;
	unsigned long  alloc_bytes;
	EEC_SUB_EXPR  *tmp_ptr;

	used_bytes    = ((unsigned long) sizeof(EEC_SUB_EXPR)) *
		((unsigned long) *sub_expr_count);
	current_bytes = ((unsigned long) *sub_expr_alloc) * sizeof(EEC_SUB_EXPR);
	current_bytes = ((current_bytes / ((unsigned long) sub_expr_gran)) +
		((current_bytes % ((unsigned long) sub_expr_gran)) ? 1L : 0L)) *
		((unsigned long) sub_expr_gran);

	if (used_bytes == current_bytes) {
		alloc_bytes = current_bytes + (((unsigned long) sub_expr_gran) *
			((unsigned long) sizeof(EEC_SUB_EXPR)));
#ifdef __MSDOS__
		if (alloc_bytes > ((unsigned long) (UINT_MAX - 15))) {
			sprintf(error_text,
				"%s --- %s (%u) (%s = %u, %s = %u, %s = %lu, %s = %lu, %s = %lu).",
				"Unable to allocate memory for sub-expression node list",
				"maximum MS-DOS allocation reached", (UINT_MAX - 15),
				"new sub-expression node count", *sub_expr_count + 1,
				"sub-expression node allocation granularity", sub_expr_gran,
				"used bytes", used_bytes, "allocated bytes", current_bytes,
				"new allocation size in bytes", alloc_bytes);
			return_code = EEC_MEMORY_FAILURE;
		}
		else
#endif /* #ifdef __MSDOS__ */
		if ((tmp_ptr = ((EEC_SUB_EXPR *) ((!used_bytes) ?
			malloc(((unsigned int) alloc_bytes)) :
			realloc(*sub_expr_list, ((unsigned int) alloc_bytes))))) == NULL) {
			sprintf(error_text,
				"%s --- (%s = %u, %s = %u, %s = %lu, %s = %lu, %s = %lu).",
				"Unable to allocate memory for sub-expression node list",
				"new sub-expression node count", *sub_expr_count + 1,
				"sub-expression node allocation granularity", sub_expr_gran,
				"used bytes", used_bytes, "allocated bytes", current_bytes,
				"new allocation size in bytes", alloc_bytes);
			return_code = EEC_MEMORY_FAILURE;
		}
		else {
			*sub_expr_list  = tmp_ptr;
			*sub_expr_alloc = ((unsigned int) alloc_bytes) / sizeof(EEC_SUB_EXPR);
		}
	}

	if (return_code == EEC_SUCCESS) {
		EEC_INIT_EEC_SUB_EXPR(*sub_expr_list + *sub_expr_count);
		(*sub_expr_count)++;
		return_code = EEC_SUCCESS;
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = EEC_SUCCESS;
	unsigned int  count_1;
	unsigned int  parse_index;
	EEC_CONTROL   control_data;
	EEC_POSTFIX   postfix_data;
	char          in_text[512];
	char          tmp_in_text[512];
	char          error_text[EEC_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'EEC_ParseIt()'\n");
	fprintf(stderr, "---- ------- --- ---------------\n\n");

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
		printf("[%s]\n", in_text);
		STR_EMIT_CharLine('-', 78, NULL, stderr);
		if ((return_code = EEC_ParseIt(&control_data, strlen(in_text), in_text,
			NULL, &postfix_data, &parse_index, error_text)) == EEC_SUCCESS) {
			EEC_EMIT_PostFix(&postfix_data, NULL, NULL);
			EEC_FREE_PostFixPtr(&postfix_data);
		}
		else {
			for (count_1 = 0; count_1 < strlen(in_text); count_1++)
				tmp_in_text[count_1] = ((char)
					((strchr("\n\r\f\t\b", in_text[count_1]) == NULL) ? ' ' :
					in_text[count_1]));
			tmp_in_text[parse_index]     = '^';
			tmp_in_text[parse_index + 1] = '\0';
			fprintf(stderr, "[%s]\n", tmp_in_text);
			STR_EMIT_CharLine('-', 78, NULL, stderr);
			fprintf(stderr, "PARSE ERROR: %s\n", error_text);
		}
		STR_EMIT_CharLine('=', 78, NULL, stderr);
	}

	EEC_FREE_Control(&control_data);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

