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

#include <stdlib.h>

#include "eecfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_FREE_Control(EEC_CONTROL *control_ptr)
#else
void EEC_FREE_Control(control_ptr)
EEC_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	if (control_ptr->sub_expr_list != NULL)
		free(control_ptr->sub_expr_list);

	EEC_FREE_OpAliasList(&control_ptr->op_alias_count,
		&control_ptr->op_alias_list);

	EEC_FREE_FuncDefList(&control_ptr->func_def_count,
		&control_ptr->func_def_list);

	EEC_FREE_EvalData(&control_ptr->eval_data);

	EEC_INIT_EEC_CONTROL(control_ptr);
}
/*	***********************************************************************	*/

