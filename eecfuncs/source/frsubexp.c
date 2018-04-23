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

	Revision History	:	1996-02-01 --- Creation.
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
void EEC_FREE_SubExprPtr(EEC_SUB_EXPR *ptr)
#else
void EEC_FREE_SubExprPtr(ptr)
EEC_SUB_EXPR *ptr;
#endif /* #ifndef NARGS */
{
	EEC_FREE_PostFixPtr(&ptr->postfix);

	EEC_INIT_EEC_SUB_EXPR(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_FREE_SubExprList(unsigned int *count, EEC_SUB_EXPR **list)
#else
void EEC_FREE_SubExprList(count, list)
unsigned int  *count;
EEC_SUB_EXPR **list;
#endif /* #ifndef NARGS */
{
	while (*count)
		EEC_FREE_SubExprPtr(*list + --(*count));

	if (*list != NULL)
		free(*list);

	*count = 0;
	*list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_CLEAR_SubExprList(unsigned int count, EEC_SUB_EXPR *list)
#else
void EEC_CLEAR_SubExprList(count, list)
unsigned int  count;
EEC_SUB_EXPR *list;
#endif /* #ifndef NARGS */
{
	while (count)
		EEC_FREE_SubExprPtr(list + --count);
}
/*	***********************************************************************	*/

