/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies 'SPF_CONTEXT' structures.

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

#include <strfuncs.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_FREE_Context(SPF_CONTEXT *ptr)
#else
void SPF_FREE_Context(ptr)
SPF_CONTEXT *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->user_data_free_func != NULL)
		(*ptr->user_data_free_func)(ptr->user_data_ptr);

	strl_remove_all(&ptr->file_count, &ptr->file_list);

	strl_remove_all(&ptr->include_count, &ptr->include_list);

	SPF_INIT_Context(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_FREE_ContextList(unsigned int *count, SPF_CONTEXT **list)
#else
void SPF_FREE_ContextList(count, list)
unsigned int  *count;
SPF_CONTEXT  **list;
#endif /* #ifndef NARGS */
{
	while (*count)
		SPF_FREE_Context(*list + --(*count));

	if (*list != NULL)
		free(*list);

	*count = 0;
	*list  = NULL;
}
/*	***********************************************************************	*/

