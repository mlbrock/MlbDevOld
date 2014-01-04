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

		Copyright Michael L. Brock 1996 - 2014.
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
void EEC_FREE_FuncDefPtr(EEC_FUNC_DEF *ptr)
#else
void EEC_FREE_FuncDefPtr(ptr)
EEC_FUNC_DEF *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->func_name != NULL)
		free(ptr->func_name);

	EEC_INIT_EEC_FUNC_DEF(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_FREE_FuncDefList(unsigned int *count, EEC_FUNC_DEF **list)
#else
void EEC_FREE_FuncDefList(count, list)
unsigned int  *count;
EEC_FUNC_DEF **list;
#endif /* #ifndef NARGS */
{
	while (*count)
		EEC_FREE_FuncDefPtr(*list + --(*count));

	if (*list != NULL)
		free(*list);

	*count = 0;
	*list  = NULL;
}
/*	***********************************************************************	*/

