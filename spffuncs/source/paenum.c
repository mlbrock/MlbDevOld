/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses an SPF boolean string.

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
#include <string.h>

#include <strfuncs.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_Enum(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned int enum_count, const SPF_ENUM *enum_list,
	unsigned int *found_index, char *error_text)
#else
int SPF_PARSE_Enum(spec_ptr, parse_ptr, enum_count, enum_list, found_index,
	error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
unsigned int     enum_count;
const SPF_ENUM  *enum_list;
unsigned int    *found_index;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code;
	SPF_PARSE    tmp_parse;
	unsigned int count_1;
	char         tmp_error_text[SPF_MAX_ERROR_TEXT];

	if ((return_code = SPF_GetSubParse(parse_ptr, &tmp_parse, error_text)) ==
		SPF_SUCCESS) {
		return_code  = SPF_PARSE_FAILURE;
		for (count_1 = 0; count_1 < enum_count; count_1++) {
			if ((tmp_parse.length == strlen(enum_list[count_1].text)) &&
				(!memicmp(tmp_parse.text, enum_list[count_1].text,
				tmp_parse.length))) {
				if (found_index != NULL)
					*found_index = count_1;
				return_code  = SPF_SUCCESS;
				break;
			}
		}
		if (return_code != SPF_SUCCESS) {
			SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text);
			sprintf(error_text,
				"%s '%s()' %s ('%-.*s') %s is invalid --- expected { ",
				"The string contained in the", spec_ptr->name, "definition",
				(tmp_parse.length > 500) ? 500 : ((int) tmp_parse.length),
				tmp_parse.text, tmp_error_text);
			for (count_1 = 0; count_1 < enum_count; count_1++) {
				if ((strlen(error_text) + strlen(enum_list[count_1].text) + 10) >=
					(SPF_MAX_ERROR_TEXT - 10)) {
					strcat(error_text, " ... }.");
					break;
				}
				else
					strcat(strcat(error_text, enum_list[count_1].text),
						(count_1 < (enum_count - 1)) ? " | " : " }.");
			}
		}
		SPF_FREE_Parse(&tmp_parse);
	}

	return(return_code);
}
/*	***********************************************************************	*/

