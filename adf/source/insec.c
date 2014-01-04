/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes an ADF section specification.

	Revision History	:	1994-06-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_INIT_Section(ADF_SECTION *ptr)
#else
void ADF_INIT_Section(ptr)
ADF_SECTION *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->section_name        = NULL;
	ptr->output_section_name = NULL;
	ptr->required_flag       = ADF_FALSE;
	ptr->wrap_flag           = ADF_FALSE;
	ptr->ltrim_flag          = ADF_FALSE;
	ptr->rtrim_flag          = ADF_FALSE;
	ptr->squeeze_flag        = ADF_FALSE;
	ptr->para_format_flag    = ADF_FALSE;
	ptr->char_format_flag    = ADF_FALSE;

	ADF_INIT_Pattern(&ptr->match_pattern);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_INIT_SectionList(unsigned int in_count, ADF_SECTION *in_list)
#else
void ADF_INIT_SectionList(in_count, in_list)
unsigned int  in_count;
ADF_SECTION  *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		ADF_INIT_Section(in_list++);
}
/*	***********************************************************************	*/

