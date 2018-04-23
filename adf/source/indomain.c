/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Intializes an ADF domain specification.

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

#include <memory.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_INIT_Domain(ADF_DOMAIN *ptr)
#else
void ADF_INIT_Domain(ptr)
ADF_DOMAIN *ptr;
#endif /* #ifndef NARGS */
{
	memset(ptr, '\0', sizeof(*ptr));

	ptr->domain_name        = NULL;
	ptr->domain_description = NULL;
	ptr->file_type_count    = 0;
	ptr->file_type_list     = NULL;
	ptr->section_count      = 0;
	ptr->section_list       = NULL;

	ADF_INIT_Pattern(&ptr->boh_pattern);
	ADF_INIT_Pattern(&ptr->eoh_pattern);
	ADF_INIT_Pattern(&ptr->bol_pattern);
	ADF_INIT_Pattern(&ptr->eol_pattern);
	ADF_INIT_Pattern(&ptr->empty_line_pattern);
	ADF_INIT_Pattern(&ptr->strip_pattern);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_INIT_DomainList(unsigned int in_count, ADF_DOMAIN *in_list)
#else
void ADF_INIT_DomainList(in_count, in_list)
unsigned int  in_count;
ADF_DOMAIN   *in_list;
#endif /* #ifndef NARGS */
{
	while (in_count--)
		ADF_INIT_Domain(in_list++);
}
/*	***********************************************************************	*/

