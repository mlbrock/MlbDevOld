/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses strings with line continuation.

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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_StringMLList(const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, unsigned int *string_count, char ***string_list,
	char *error_text)
#else
int SPF_PARSE_StringMLList(spec_ptr, parse_ptr, string_count, string_list,
	error_text)
const SPF_SPEC    *spec_ptr;
const SPF_PARSE   *parse_ptr;
unsigned int      *string_count;
char            ***string_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code;
	char *string_ptr;
	char  tmp_error_text[SPF_MAX_ERROR_TEXT];

	if ((return_code = SPF_PARSE_StringML(spec_ptr, parse_ptr, &string_ptr,
		error_text)) == SPF_SUCCESS) {
		if (strl_append(string_count, string_list, string_ptr) !=
			STRFUNCS_SUCCESS) {
			STR_AllocMsgItem(strlen(string_ptr), error_text,
				"%s '%s()' %s ('%-.500s') %s.",
				"Unable to allocate memory for a string list element of a",
				spec_ptr->name, "definition", string_ptr,
				SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text));
			return_code = SPF_MEMORY_FAILURE;
		}
		free(string_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_StringML(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	char **string_ptr, char *error_text)
#else
int SPF_PARSE_StringML(spec_ptr, parse_ptr, string_ptr, error_text)
const SPF_SPEC   *spec_ptr;
const SPF_PARSE  *parse_ptr;
char            **string_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code;
	unsigned int sub_length;
   unsigned int count_1;
	SPF_SPEC     tmp_spec;
	char         tmp_error_text[SPF_MAX_ERROR_TEXT];

	tmp_spec            = *spec_ptr;
	tmp_spec.min_length = 0;
	tmp_spec.max_length = UINT_MAX;

	if ((return_code = SPF_PARSE_TextML(&tmp_spec, parse_ptr, string_ptr,
		error_text)) == SPF_SUCCESS) {
		if (((sub_length = strlen(*string_ptr)) < 2) ||
			(**string_ptr != '\"') || ((*string_ptr)[sub_length - 1] != '\"')) {
			SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text);
			sprintf(error_text, "%s '%s()' %s ('%-.500s') %s %s.",
				"The string contained in the", spec_ptr->name, "definition",
				*string_ptr, tmp_error_text, "was not enclosed in quotes ('\"')");
			return_code = SPF_PARSE_FAILURE;
		}
		else {
			for (count_1 = 0; count_1 < sub_length; count_1++)
				(*string_ptr)[count_1] = (*string_ptr)[count_1 + 1];
			sub_length                -= 2;
			(*string_ptr)[sub_length]  = '\0';
			if ((sub_length < spec_ptr->min_length) ||
				(sub_length > spec_ptr->max_length)) {
				SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text);
				sprintf(error_text,
					"%s '%s()' %s '%-.500s' (%u) %s %s %u and %u, inclusive.",
					"The length of the string contained in the", spec_ptr->name,
					"definition", *string_ptr, sub_length, tmp_error_text,
					"is invalid --- permissible lengths are between",
					spec_ptr->min_length, spec_ptr->max_length);
				return_code = SPF_PARSE_FAILURE;
			}
		}
		if ((return_code != SPF_SUCCESS) && (*string_ptr != NULL)) {
			free(*string_ptr);
			*string_ptr = NULL;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

