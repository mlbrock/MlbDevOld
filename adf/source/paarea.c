/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses an ADF area specification.

	Revision History	:	1994-06-15 --- Creation.
									Michael L. Brock
								1997-04-03 --- Revised for new parsing logic.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PARSE_AreaName(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned int *area_name_ptr, char *error_text)
#else
int ADF_PARSE_AreaName(spec_ptr, parse_ptr, area_name_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
unsigned int    *area_name_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int       return_code;
	char     *tmp_ptr;
	SPF_SPEC  tmp_spec;
	char      tmp_error_text[SPF_MAX_ERROR_TEXT];

	tmp_spec            = *spec_ptr;
	tmp_spec.min_length = 1;
	tmp_spec.max_length = UINT_MAX;

	if ((return_code = SPF_PARSE_Text(&tmp_spec, parse_ptr, &tmp_ptr,
		error_text)) == SPF_SUCCESS) {
		ADF_AreaToParseArea(tmp_ptr);
		if (ADF_FIND_AreaByName(tmp_ptr, area_name_ptr) == NULL) {
			sprintf(error_text,
				"%s '%s()' %s ('%-.500s') %s is invalid: %-.500s",
				"The area name contained in the", spec_ptr->name, "definition",
				tmp_ptr, SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text),
				"expected one of the valid ADF area names");
			return_code = SPF_PARSE_FAILURE;
		}
		free(tmp_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

