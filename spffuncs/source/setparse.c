/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes an SPF parse item.

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

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_SetContextParse(const SPF_CONTEXT *context_ptr, SPF_PARSE *parse_ptr)
#else
void SPF_SetContextParse(context_ptr, parse_ptr)
const SPF_CONTEXT *context_ptr;
SPF_PARSE         *parse_ptr;
#endif /* #ifndef NARGS */
{
	parse_ptr->file =
		(context_ptr->current_file_index < context_ptr->file_count) ?
		context_ptr->file_list[context_ptr->current_file_index] :
		SPF_PARSE_FILE_FAKE_NAME;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void SPF_SetContextParseList(const SPF_CONTEXT *context_ptr,
	unsigned int parse_count, SPF_PARSE *parse_list)
#else
void SPF_SetContextParseList(context_ptr, parse_count, parse_list)
const SPF_CONTEXT *context_ptr;
unsigned int       parse_count;
SPF_PARSE         *parse_list;
#endif /* #ifndef NARGS */
{
	while (parse_count)
		SPF_SetContextParse(context_ptr, parse_list + --parse_count);
}
/*	***********************************************************************	*/

