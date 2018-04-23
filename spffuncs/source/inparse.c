/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'SPF_PARSE' structures.

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

#include <memory.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_INIT_Parse(SPF_PARSE *ptr)
#else
void SPF_INIT_Parse(ptr)
SPF_PARSE *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->file       = NULL;
	ptr->line       = 0L;
	ptr->length     = 0;
	ptr->text       = NULL;
	ptr->spec_type  = SPF_TYPE_NONE;
	ptr->spec_index = 0;
	ptr->list_index = 0;
	ptr->flags      = SPF_FALSE;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_INIT_ParseList(unsigned int count, SPF_PARSE *list)
#else
void SPF_INIT_ParseList(count, list)
unsigned int  count;
SPF_PARSE    *list;
#endif /* #ifndef NARGS */
{
	while (count--)
		SPF_INIT_Parse(list++);
}
/*	***********************************************************************	*/

