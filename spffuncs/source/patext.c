/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses text.

	Revision History	:	1995-08-21 --- Creation.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_TextList(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned int *text_count, char ***text_list, char *error_text)
#else
int SPF_PARSE_TextList(spec_ptr, parse_ptr, text_count, text_list, error_text)
const SPF_SPEC    *spec_ptr;
const SPF_PARSE   *parse_ptr;
unsigned int      *text_count;
char            ***text_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code;
	char *text_ptr;
	char  tmp_error_text[SPF_MAX_ERROR_TEXT];

	if ((return_code = SPF_PARSE_Text(spec_ptr, parse_ptr, &text_ptr,
		error_text)) == SPF_SUCCESS) {
		if (strl_append(text_count, text_list, text_ptr) != STRFUNCS_SUCCESS) {
			STR_AllocMsgItem(strlen(text_ptr), error_text,
				"%s '%s()' %s ('%-.500s') %s.",
				"Unable to allocate memory for a string list element of a",
				spec_ptr->name, "definition", text_ptr,
				SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text));
			return_code = SPF_MEMORY_FAILURE;
		}
		free(text_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_Text(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	char **text_ptr, char *error_text)
#else
int SPF_PARSE_Text(spec_ptr, parse_ptr, text_ptr, error_text)
const SPF_SPEC   *spec_ptr;
const SPF_PARSE  *parse_ptr;
char            **text_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int       return_code;
	SPF_PARSE tmp_parse;
	char      tmp_error_text[SPF_MAX_ERROR_TEXT];

	*text_ptr = NULL;

	if ((return_code = SPF_GetSubParse(parse_ptr, &tmp_parse, error_text)) ==
		SPF_SUCCESS) {
		if ((tmp_parse.length < spec_ptr->min_length) ||
			(tmp_parse.length > spec_ptr->max_length)) {
			SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text);
			sprintf(error_text,
				"%s '%s()' %s '%-.*s' (%u) %s %s %u and %u, inclusive.",
				"The length of the string contained in the", spec_ptr->name,
				"definition", (tmp_parse.length > 500) ? 500 :
				((int) tmp_parse.length), tmp_parse.text, tmp_parse.length,
				tmp_error_text, "is invalid --- permissible lengths are between",
				spec_ptr->min_length, spec_ptr->max_length);
			return_code = SPF_PARSE_FAILURE;
		}
		else if ((return_code = SPF_ALLC_Parse(&tmp_parse, error_text)) ==
			SPF_SUCCESS)
			*text_ptr = tmp_parse.text;
		if (return_code != SPF_SUCCESS)
			SPF_FREE_Parse(&tmp_parse);
	}

	return(return_code);
}
/*	***********************************************************************	*/

