/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies an ADF pattern.

	Revision History	:	1995-08-29 --- Creation.
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
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_COPY_Pattern(const ADF_PATTERN *in_ptr, ADF_PATTERN *out_ptr,
	char *error_text)
#else
int ADF_COPY_Pattern(in_ptr, out_ptr, error_text)
const ADF_PATTERN *in_ptr;
ADF_PATTERN       *out_ptr;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_SUCCESS;

	ADF_INIT_Pattern(out_ptr);

	if (strl_copy(in_ptr->pattern_count, in_ptr->pattern_list,
		&out_ptr->pattern_count, &out_ptr->pattern_list) !=
		STRFUNCS_SUCCESS)
		return_code = ADF_MEMORY_FAILURE;
	else if ((in_ptr->pattern_optimization != NULL) &&
		((out_ptr->pattern_optimization =
		strdup(in_ptr->pattern_optimization)) == NULL))
		return_code = ADF_MEMORY_FAILURE;

	if (return_code != ADF_SUCCESS) {
		ADF_FREE_Pattern(out_ptr);
		if (!(*error_text))
			strcpy(error_text, "Insufficent memory to copy pattern.");
	}

	return(return_code);
}
/*	***********************************************************************	*/

