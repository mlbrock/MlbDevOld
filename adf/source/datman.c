/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages use man-page-specific data.

	Revision History	:	1996-09-12 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
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
#include <stdlib.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_InitDataMAN(ADF_MAN_DATA *man_data_ptr)
#else
void ADF_InitDataMAN(man_data_ptr)
ADF_MAN_DATA *man_data_ptr;
#endif /* #ifndef NARGS */
{
	memset(man_data_ptr, '\0', sizeof(*man_data_ptr));

	man_data_ptr->section_name = NULL;
	man_data_ptr->owner_name   = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FreeDataMAN(ADF_MAN_DATA *man_data_ptr)
#else
void ADF_FreeDataMAN(man_data_ptr)
ADF_MAN_DATA *man_data_ptr;
#endif /* #ifndef NARGS */
{
	if (man_data_ptr->section_name != NULL)
		free(man_data_ptr->section_name);

	if (man_data_ptr->owner_name != NULL)
		free(man_data_ptr->owner_name);

	ADF_InitDataMAN(man_data_ptr);
}
/*	***********************************************************************	*/

