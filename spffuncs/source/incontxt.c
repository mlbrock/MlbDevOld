/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes 'SPF_CONTEXT' structures.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
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
void SPF_INIT_Context(SPF_CONTEXT *ptr)
#else
void SPF_INIT_Context(ptr)
SPF_CONTEXT *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->file_count          = 0;
	ptr->file_list           = NULL;
	ptr->include_count       = 0;
	ptr->include_list        = NULL;
	ptr->current_file_index  = 0;
	ptr->user_data_ptr       = NULL;
	ptr->user_data_free_func = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_INIT_ContextList(unsigned int count, SPF_CONTEXT *list)
#else
void SPF_INIT_ContextList(count, list)
unsigned int  count;
SPF_CONTEXT  *list;
#endif /* #ifndef NARGS */
{
	while (count--)
		SPF_INIT_Context(list++);
}
/*	***********************************************************************	*/

