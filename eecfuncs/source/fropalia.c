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

	Revision History	:	1996-03-02 --- Creation.
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
void EEC_FREE_OpAliasPtr(EEC_PARSE_OP_ALIAS *ptr)
#else
void EEC_FREE_OpAliasPtr(ptr)
EEC_PARSE_OP_ALIAS *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->operator_alias != NULL)
		free(ptr->operator_alias);

	EEC_INIT_EEC_PARSE_OP_ALIAS(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_FREE_OpAliasList(unsigned int *count, EEC_PARSE_OP_ALIAS **list)
#else
void EEC_FREE_OpAliasList(count, list)
unsigned int        *count;
EEC_PARSE_OP_ALIAS **list;
#endif /* #ifndef NARGS */
{
	while (*count)
		EEC_FREE_OpAliasPtr(*list + --(*count));

	if (*list != NULL)
		free(*list);

	*count = 0;
	*list  = NULL;
}
/*	***********************************************************************	*/

