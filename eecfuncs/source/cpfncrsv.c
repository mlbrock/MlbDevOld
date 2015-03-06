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
int EEC_COPY_FuncResolvePtr(const EEC_FUNC_RESOLVE *in_ptr,
	EEC_FUNC_RESOLVE *out_ptr, char *error_text)
#else
int EEC_COPY_FuncResolvePtr(in_ptr, out_ptr, error_text)
const EEC_FUNC_RESOLVE *in_ptr;
EEC_FUNC_RESOLVE       *out_ptr;
char                   *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	EEC_INIT_EEC_FUNC_RESOLVE(out_ptr);

	if ((return_code = EEC_COPY_FuncDefList(in_ptr->user_count,
		in_ptr->user_list, &out_ptr->user_count, &out_ptr->user_list,
		error_text)) != EEC_SUCCESS)
		strinst(error_text,
			"Unable to copy the 'EEC_FUNC_RESOLVE' user list", 0);
	else if ((return_code = EEC_COPY_FuncDefList(in_ptr->builtin_count,
		in_ptr->builtin_list, &out_ptr->builtin_count,
		&out_ptr->builtin_list, error_text)) != EEC_SUCCESS) {
		EEC_FREE_FuncResolvePtr(out_ptr);
		strinst(error_text,
			"Unable to copy the 'EEC_FUNC_RESOLVE' built-in list", 0);
	}

	return(return_code);
}
/*	***********************************************************************	*/

