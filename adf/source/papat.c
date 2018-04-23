/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses an ADF pattern specification.

	Revision History	:	1995-08-15 --- Creation.
									Michael L. Brock
								1997-04-03 --- Revised for new parsing logic.
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

#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PARSE_Pattern(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	ADF_PATTERN *pattern_ptr, char *error_text)
#else
int ADF_PARSE_Pattern(spec_ptr, parse_ptr, pattern_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
ADF_PATTERN     *pattern_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int       return_code;
	char     *string_ptr;
	SPF_SPEC  tmp_spec;
	char      tmp_error_text[SPF_MAX_ERROR_TEXT];

	tmp_spec            = *spec_ptr;
	tmp_spec.min_length = 1;
	tmp_spec.max_length = UINT_MAX;

	if ((return_code = SPF_PARSE_StringML(&tmp_spec, parse_ptr, &string_ptr,
		error_text)) == SPF_SUCCESS) {
		if (strl_append(&pattern_ptr->pattern_count, &pattern_ptr->pattern_list,
			upper(string_ptr)) != STRFUNCS_SUCCESS) {
			STR_AllocMsgItem(strlen(string_ptr) + 1, error_text,
				"%s '%s()' %s ('%-.500s') %s",
				"Unable to allocate memory for a pattern list element of a",
				spec_ptr->name, "definition", string_ptr,
				SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text));
			return_code = SPF_MEMORY_FAILURE;
		}
		free(string_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

