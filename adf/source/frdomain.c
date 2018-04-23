/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees an ADF domain.

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
void ADF_FREE_Domain(ADF_DOMAIN *ptr)
#else
void ADF_FREE_Domain(ptr)
ADF_DOMAIN *ptr;
#endif /* #ifndef NARGS */
{
	if (ptr->domain_name != NULL)
		free(ptr->domain_name);

	if (ptr->domain_description != NULL)
		free(ptr->domain_description);

	strl_remove_all(&ptr->file_type_count,
		&ptr->file_type_list);

	ADF_FREE_Pattern(&ptr->boh_pattern);

	ADF_FREE_Pattern(&ptr->eoh_pattern);

	ADF_FREE_Pattern(&ptr->bol_pattern);

	ADF_FREE_Pattern(&ptr->eol_pattern);

	ADF_FREE_Pattern(&ptr->empty_line_pattern);

	ADF_FREE_Pattern(&ptr->strip_pattern);

	ADF_FREE_SectionList(&ptr->section_count, &ptr->section_list);

	ADF_INIT_Domain(ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FREE_DomainList(unsigned int *in_count, ADF_DOMAIN **in_list)
#else
void ADF_FREE_DomainList(in_count, in_list)
unsigned int  *in_count;
ADF_DOMAIN   **in_list;
#endif /* #ifndef NARGS */
{
	while (*in_count)
		ADF_FREE_Domain(*in_list + --(*in_count));

	if (*in_list != NULL)
		free(*in_list);

	*in_count = 0;
	*in_list  = NULL;
}
/*	***********************************************************************	*/

