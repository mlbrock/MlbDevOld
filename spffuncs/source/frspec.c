/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees 'SPF_SPEC' structures.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
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
void SPF_FREE_Spec(SPF_SPEC *ptr)
#else
void SPF_FREE_Spec(ptr)
SPF_SPEC *ptr;
#endif /* #ifndef NARGS */
{
	SPF_INIT_Spec(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_FREE_SpecList(unsigned int *count, SPF_SPEC **list)
#else
void SPF_FREE_SpecList(count, list)
unsigned int  *count;
SPF_SPEC    **list;
#endif /* #ifndef NARGS */
{
	while (*count)
		SPF_FREE_Spec(*list + --(*count));

	if (*list != NULL)
		free(*list);

	*count = 0;
	*list  = NULL;
}
/*	***********************************************************************	*/

