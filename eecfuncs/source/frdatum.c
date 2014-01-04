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
void EEC_FREE_DatumPtr(EEC_DATUM *ptr)
#else
void EEC_FREE_DatumPtr(ptr)
EEC_DATUM *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->flags & (EEC_EVAL_FLAG_TYPE_STRING | EEC_EVAL_FLAG_ALLOCED))
		free(ptr->datum.string.data);

	EEC_INIT_EEC_DATUM(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void EEC_FREE_DatumList(unsigned int *count, EEC_DATUM **list)
#else
void EEC_FREE_DatumList(count, list)
unsigned int  *count;
EEC_DATUM    **list;
#endif /* #ifndef NARGS */
{
	while (*count)
		EEC_FREE_DatumPtr(*list + --(*count));

	if (*list != NULL)
		free(*list);

	*count = 0;
	*list  = NULL;
}
/*	***********************************************************************	*/

