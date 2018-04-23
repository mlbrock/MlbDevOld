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
void EEC_FREE_SymbolPtr(EEC_SYMBOL *ptr)
#else
void EEC_FREE_SymbolPtr(ptr)
EEC_SYMBOL *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->name != NULL)
		free(ptr->name);

	EEC_FREE_PostFixPtr(&ptr->postfix);
	EEC_FREE_DatumPtr(&ptr->value);

	EEC_INIT_EEC_SYMBOL(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_FREE_SymbolList(unsigned int *count, EEC_SYMBOL **list)
#else
void EEC_FREE_SymbolList(count, list)
unsigned int  *count;
EEC_SYMBOL   **list;
#endif /* #ifndef NARGS */
{
	while (*count)
		EEC_FREE_SymbolPtr(*list + --(*count));

	if (*list != NULL)
		free(*list);

	*count = 0;
	*list  = NULL;
}
/*	***********************************************************************	*/

