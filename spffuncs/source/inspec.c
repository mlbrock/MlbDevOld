/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'SPF_SPEC' structures.

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

#include <memory.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_INIT_Spec(SPF_SPEC *ptr)
#else
void SPF_INIT_Spec(ptr)
SPF_SPEC *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->type       = 0;
	ptr->min_count  = 0;
	ptr->max_count  = 0;
	ptr->min_length = 0;
	ptr->max_length = 0;
	ptr->min_value  = 0.0;
	ptr->max_value  = 0.0;
	ptr->offset_1   = 0;
	ptr->offset_2   = 0;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_INIT_SpecList(unsigned int count, SPF_SPEC *list)
#else
void SPF_INIT_SpecList(count, list)
unsigned int  count;
SPF_SPEC    *list;
#endif /* #ifndef NARGS */
{
	while (count--)
		SPF_INIT_Spec(list++);
}
/*	***********************************************************************	*/

