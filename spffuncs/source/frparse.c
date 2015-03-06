/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'SPF_PARSE' structures.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_FREE_Parse(SPF_PARSE *ptr)
#else
void SPF_FREE_Parse(ptr)
SPF_PARSE *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->flags && (ptr->text != NULL))
		free(ptr->text);

	SPF_INIT_Parse(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_FREE_ParseList(unsigned int *count, SPF_PARSE **list)
#else
void SPF_FREE_ParseList(count, list)
unsigned int  *count;
SPF_PARSE    **list;
#endif /* #ifndef NARGS */
{
	while (*count)
		SPF_FREE_Parse(*list + --(*count));

	if (*list != NULL)
		free(*list);

	*count = 0;
	*list  = NULL;
}
/*	***********************************************************************	*/

