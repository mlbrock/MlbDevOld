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

#include <stdlib.h>

#include "eecfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_FREE_FuncResolvePtr(EEC_FUNC_RESOLVE *ptr)
#else
void EEC_FREE_FuncResolvePtr(ptr)
EEC_FUNC_RESOLVE *ptr;
#endif /* #ifndef NARGS */
{
	EEC_FREE_FuncDefList(&ptr->user_count, &ptr->user_list);
	EEC_FREE_FuncDefList(&ptr->builtin_count, &ptr->builtin_list);

	EEC_INIT_EEC_FUNC_RESOLVE(ptr);
}
/*	***********************************************************************	*/

