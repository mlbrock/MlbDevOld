/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees an ADF section.

	Revision History	:	1994-06-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FREE_SectionList(unsigned int *in_count, ADF_SECTION **in_list)
#else
void ADF_FREE_SectionList(in_count, in_list)
unsigned int   *in_count;
ADF_SECTION   **in_list;
#endif /* #ifndef NARGS */
{
	while (*in_count)
		ADF_FREE_Section(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FREE_Section(ADF_SECTION *ptr)
#else
void ADF_FREE_Section(ptr)
ADF_SECTION *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->section_name != NULL)
		free(ptr->section_name);

	if (ptr->output_section_name != NULL)
		free(ptr->output_section_name);

	ADF_FREE_Pattern(&ptr->match_pattern);

	ADF_INIT_Section(ptr);
}
/*	***********************************************************************	*/

