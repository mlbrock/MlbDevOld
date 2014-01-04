/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees an ADF pattern.

	Revision History	:	1995-08-15 --- Creation.
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

#include <stdlib.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_FREE_Pattern(ADF_PATTERN *ptr)
#else
void ADF_FREE_Pattern(ptr)
ADF_PATTERN *ptr;
#endif /* #ifndef NARGS */
{
	strl_remove_all(&ptr->pattern_count, &ptr->pattern_list);

	if (ptr->pattern_optimization != NULL)
		free(ptr->pattern_optimization);

	ADF_INIT_Pattern(ptr);
}
/*	***********************************************************************	*/

