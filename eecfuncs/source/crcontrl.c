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

	Revision History	:	1996-03-01 --- Creation.
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

#include <stdlib.h>
#include <string.h>

#include "eecfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_CreateControl(EEC_CONTROL *control_ptr, char *error_text)
#else
int EEC_CreateControl(control_ptr, error_text)
EEC_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	return(EEC_CreateControlBasic(control_ptr, EEC_FALSE, NULL, 0, 0, NULL,
		0, NULL, NULL, NULL, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#if 0
int EEC_CreateControlBasic(control_ptr, optimize_flag, decimal_point,
	sub_expr_gran, op_alias_count, op_alias_list, func_resolve_ptr,
	symbol_resolve_ptr, error_text)
EEC_CONTROL              *control_ptr;
int                       optimize_flag;
const char               *decimal_point;
unsigned int              sub_expr_gran;
unsigned int              op_alias_count;
const EEC_PARSE_OP_ALIAS *op_alias_list;
const EEC_FUNC_RESOLVE   *func_resolve_ptr;
const EEC_SYMBOL_RESOLVE *symbol_resolve_ptr;
char                     *error_text;
{
	int              return_code = EEC_SUCCESS;
	EEC_CONTROL      control_data;
	EEC_FUNC_RESOLVE func_resolve;

	EEC_INIT_EEC_CONTROL(&control_data);

	if (EEC_ControlIsInit(control_ptr) == EEC_TRUE) {
		strcpy(error_text, "Control structure is already initialized.");
		return_code = EEC_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((op_alias_count && (op_alias_list == NULL)) ||
		((!op_alias_count) && (op_alias_list != NULL))) {
		sprintf(error_text, "%s %s, %s %s.",
			"User operator alias count is",
			(op_alias_count) ? "non-zero" : "zero",
			"but the associated user operator alias list is",
			(op_alias_count) ? "NULL" : "not NULL");
		return_code = EEC_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (func_resolve_ptr == NULL) {
		EEC_INIT_EEC_FUNC_RESOLVE(&func_resolve);
		func_resolve.builtin_count = EEC_FunctionDefCount;
		func_resolve.builtin_list  = EEC_FunctionDefList;
		func_resolve_ptr           = &func_resolve;
	}

	sub_expr_gran = (sub_expr_gran) ? sub_expr_gran : EEC_EXPR_LIST_GRAN;
	optimize_flag = (optimize_flag) ? EEC_TRUE : EEC_FALSE;

	if (op_alias_count && ((return_code = EEC_COPY_OpAliasList(op_alias_count,
		op_alias_list, &control_data.op_alias_count,
		&control_data.op_alias_list, error_text)) != EEC_SUCCESS))
		goto EXIT_FUNCTION;

	if ((return_code = EEC_COPY_FuncResolvePtr(func_resolve_ptr,
		&control_data.func_resolve, error_text)) != EEC_SUCCESS))
		goto EXIT_FUNCTION;

	if ((symbol_resolve_ptr != NULL) &&
		((return_code = EEC_COPY_SymbolResolvePtr(symbol_resolve_ptr,
		&control_data.symbol_resolve, error_text)) != EEC_SUCCESS))
		goto EXIT_FUNCTION;

	*control_ptr                   = control_data;

	control_ptr->init_head         = EEC_CONTROL_INIT_HEAD;
	control_ptr->decimal_point     = (decimal_point == NULL) ? '\0' :
		*decimal_point;
	control_ptr->decimal_point_ptr = (decimal_point == NULL) ? NULL :
		&control_ptr->decimal_point;
	control_ptr->sub_expr_gran     = sub_expr_gran;
	control_ptr->optimize_flag     = optimize_flag;
	control_ptr->init_tail         = EEC_CONTROL_INIT_TAIL;

	EEC_INIT_EEC_CONTROL(&control_data);

EXIT_FUNCTION:

	if (return_code != EEC_SUCCESS)
		EEC_FREE_Control(&control_data);

	return(return_code);
}
#else
/*
	CODE NOTE: To be removed.
*/
#ifndef NARGS
int EEC_CreateControlBasic(EEC_CONTROL *control_ptr, int optimize_flag,
	const char *decimal_point, unsigned int sub_expr_gran,
	unsigned int op_alias_count, const EEC_PARSE_OP_ALIAS *op_alias_list,
	unsigned int func_def_count, const EEC_FUNC_DEF *func_def_list,
	int (*func_resolve_func)(const char *, const EEC_FUNC_DEF *, unsigned int,
		unsigned int, unsigned int, unsigned int *, char *),
	EEC_SymbolParseFunc symbol_parse_func, char *error_text)
#else
int EEC_CreateControlBasic(control_ptr, optimize_flag, decimal_point,
	sub_expr_gran, op_alias_count, op_alias_list, func_def_count,
	func_def_list, func_resolve_func, symbol_parse_func, error_text)
EEC_CONTROL               *control_ptr;
int                        optimize_flag;
const char                *decimal_point;
unsigned int               sub_expr_gran;
unsigned int               op_alias_count;
const EEC_PARSE_OP_ALIAS  *op_alias_list;
unsigned int               func_def_count;
const EEC_FUNC_DEF        *func_def_list;
# ifndef NARGS
int                      (*func_resolve_func)(const char *,
									const EEC_FUNC_DEF *, unsigned int, unsigned int,
									unsigned int, unsigned int *, char *);
# else
int                      (*func_resolve_func)();
# endif /* #ifndef NARGS */
EEC_SymbolParseFunc        symbol_parse_func;
char                      *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code = EEC_SUCCESS;
	EEC_CONTROL control_data;

	EEC_INIT_EEC_CONTROL(&control_data);

	if (EEC_ControlIsInit(control_ptr) == EEC_TRUE) {
		strcpy(error_text, "Control structure is already initialized.");
		return_code = EEC_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((op_alias_count && (op_alias_list == NULL)) ||
		((!op_alias_count) && (op_alias_list != NULL))) {
		sprintf(error_text, "%s %s, %s %s.",
			"User operator alias count is",
			(op_alias_count) ? "non-zero" : "zero",
			"but the associated user operator alias list is",
			(op_alias_count) ? "NULL" : "not NULL");
		return_code = EEC_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((func_def_count && (func_def_list == NULL)) ||
		((!func_def_count) && (func_def_list != NULL))) {
		sprintf(error_text, "%s %s, %s %s.",
			"User function definition count is",
			(func_def_count) ? "non-zero" : "zero",
			"but the associated user function definition list is",
			(func_def_count) ? "NULL" : "not NULL");
		return_code = EEC_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	sub_expr_gran = (sub_expr_gran) ? sub_expr_gran : EEC_EXPR_LIST_GRAN;
	optimize_flag = (optimize_flag) ? EEC_TRUE : EEC_FALSE;

	if (op_alias_count && ((return_code = EEC_COPY_OpAliasList(op_alias_count,
		op_alias_list, &control_data.op_alias_count,
		&control_data.op_alias_list, error_text)) != EEC_SUCCESS))
		goto EXIT_FUNCTION;

	if (func_def_count && ((return_code = EEC_COPY_FuncDefList(func_def_count,
		func_def_list, &control_data.func_def_count,
		&control_data.func_def_list, error_text)) != EEC_SUCCESS))
		goto EXIT_FUNCTION;

	*control_ptr                     = control_data;

	control_ptr->init_head           = EEC_CONTROL_INIT_HEAD;
	control_ptr->decimal_point       = ((char) ((decimal_point == NULL) ? '\0' :
		*decimal_point));
	control_ptr->decimal_point_ptr   = (decimal_point == NULL) ? NULL :
		&control_ptr->decimal_point;
	control_ptr->sub_expr_gran       = sub_expr_gran;
	control_ptr->optimize_flag       = optimize_flag;
	control_ptr->func_resolve_func   = func_resolve_func;
	control_ptr->symbol_parse_func   = symbol_parse_func;
	control_ptr->init_tail           = EEC_CONTROL_INIT_TAIL;

	EEC_INIT_EEC_CONTROL(&control_data);

EXIT_FUNCTION:

	if (return_code != EEC_SUCCESS)
		EEC_FREE_Control(&control_data);

	return(return_code);
}
#endif /* if 0 */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int EEC_ControlIsInit(const EEC_CONTROL *control_ptr)
#else
int EEC_ControlIsInit(control_ptr)
const EEC_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	return(((control_ptr->init_head == EEC_CONTROL_INIT_HEAD) &&
		(control_ptr->init_tail == EEC_CONTROL_INIT_TAIL)) ? EEC_TRUE :
		EEC_FALSE);
}
/*	***********************************************************************	*/

