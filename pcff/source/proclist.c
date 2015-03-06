/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Processes configuration lines from a list.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <string.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
int PCFF_ProcessFromList(PCFF_CFG *cfg_ptr, PCFF_FLAG flags,
	const char *source_name, unsigned int in_line_count, char **in_line_list,
	unsigned int *include_stack_count, char ***include_stack_list,
	char *error_text)
{
	int           return_code = PCFF_SUCCESS;
	unsigned int  line_number = 0;
	char         *this_line   = NULL;
	unsigned int  count_1;
	char         *value_ptr;
	char          tmp_error_text[PCFF_MAX_ERROR_TEXT];

	source_name = (source_name != NULL) ? source_name : "<<<UNKNOWN SOURCE>>>";

	for (count_1 = 0; count_1 < in_line_count; count_1++) {
		line_number++;
		if (in_line_list[count_1] == NULL)
			continue;
		if ((this_line = strdup(in_line_list[count_1])) == NULL) {
			STR_AllocMsgItem(strlen(in_line_list[count_1]) + 1, tmp_error_text,
				"Unable to allocate memory for a copy of the configuration line");
			return_code = PCFF_FAILURE;
			break;
		}
		trim(this_line);
		if ((!this_line[0]) || (this_line[0] == '#'))
			;
		else if ((value_ptr = str_space(this_line, 1)) == NULL) {
			sprintf(tmp_error_text, "%s ('%-.100s'), %s.",
				"The configuration parameter name was located", this_line,
				"but no corresponding value found");
			return_code = PCFF_FAILURE;
			break;
		}
		else {
			*value_ptr++ = '\0';
			if (!(*ltrim(value_ptr))) {
				sprintf(tmp_error_text, "%s ('%-.100s'), %s.",
					"The configuration parameter name was located", this_line,
					"but no corresponding value found");
				return_code = PCFF_FAILURE;
				break;
			}
			if (!stricmp("INCLUDE_FILE", this_line)) {
				if ((return_code = PCFF_ProcessFromFile(cfg_ptr, flags,
					value_ptr, include_stack_count, include_stack_list,
					tmp_error_text)) != PCFF_SUCCESS)
					break;
			}
			else if ((return_code = PCFF_AddItem(cfg_ptr, flags, source_name,
				line_number, this_line, value_ptr, tmp_error_text)) !=
				PCFF_SUCCESS)
				break;
		}
		free(this_line);
		this_line = NULL;
	}

	if (return_code != PCFF_SUCCESS)
		sprintf(error_text, "%s '%-.500s' at line number %u: %s",
			"Error encountered while reading configuration file lines from",
			source_name, line_number, tmp_error_text);

	if (this_line != NULL)
		free(this_line);

	return(return_code);
}
/* *********************************************************************** */


