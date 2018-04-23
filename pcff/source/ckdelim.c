/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks the names and values in a configuration
								against the specified delimiters.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2018.
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
int PCFF_CheckDelimiters(PCFF_CFG *cfg_ptr, PCFF_PARSE_SPEC *parse_spec_ptr,
	char *error_text)
{
	return(PCFF_CheckDelimitersBasic(cfg_ptr, parse_spec_ptr->name_left,
		parse_spec_ptr->name_right, parse_spec_ptr->value_left,
		parse_spec_ptr->value_right, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_CheckDelimitersBasic(PCFF_CFG *cfg_ptr, const char *name_left,
	const char *name_right, const char *value_left, const char *value_right,
	char *error_text)
{
	int           return_code = PCFF_SUCCESS;
	int           this_idx;
	unsigned int  count_1;
	unsigned int  name_length;
	unsigned int  value_length;
	unsigned int  this_length;
	PCFF_ITEM    *item_ptr;
	PCFF_SRC     *src_ptr;

	name_left   = (name_left  != NULL) ? name_left  : "";
	name_right  = (name_right != NULL) ? name_right : "";
	value_left  = (value_left != NULL) ? value_left : "";
	value_right = (value_right!= NULL) ? value_right: "";

	if ((name_length = strlen(name_left)) != strlen(name_right)) {
		sprintf(error_text, "%s %s (%u) %s %s (%u).",
			"The length of the left-side name delimiter",
			"character specification", name_length,
			"is not the same as he length of the right-side name delimiter",
			"character specification", strlen(name_right));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((value_length = strlen(value_left)) != strlen(value_right)) {
		sprintf(error_text, "%s %s (%u) %s %s (%u).",
			"The length of the left-side value delimiter",
			"character specification", value_length,
			"is not the same as he length of the right-side value delimiter",
			"character specification", strlen(value_right));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0, item_ptr = cfg_ptr->item_list;
		count_1 < cfg_ptr->item_count; count_1++, item_ptr++) {
		if (item_ptr->src_count > 1) {
			strcpy(error_text, "Configuration has not been flattened.");
			return_code = PCFF_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	if (name_length) {
		for (count_1 = 0, item_ptr = cfg_ptr->item_list;
			count_1 < cfg_ptr->item_count; count_1++, item_ptr++) {
			src_ptr = item_ptr->src_list;
			if ((this_length = strlen(item_ptr->name)) < 2) {
				sprintf(error_text, "%s %u %s '%-.500s' (%s=%s) %s (%u).",
					"The configuration parameter name loaded from line number",
					src_ptr->line_number, "in file", src_ptr->file_name,
					item_ptr->name, item_ptr->value,
					"is too short to contain name delimiters", this_length);
				return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if ((this_idx = idxchr(name_left, *item_ptr->name)) == -1) {
				sprintf(error_text,
					"%s %u %s '%-.500s' (%s=%s) %s ('%c') %s ('%s').",
					"The configuration parameter name loaded from line number",
					src_ptr->line_number, "in file", src_ptr->file_name,
					item_ptr->name, item_ptr->value,
					"begins with a character", *item_ptr->name,
					"which is not in the list of valid left name delimiters",
					name_left);
				return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if (name_right[this_idx] != item_ptr->name[this_length - 1]) {
				sprintf(error_text,
					"%s %u %s '%-.500s' (%s=%s) %s ('%c') %s ('%c') %s ('%c').",
					"The configuration parameter name loaded from line number",
					src_ptr->line_number, "in file", src_ptr->file_name,
					item_ptr->name, item_ptr->value,
					"ends with a character", item_ptr->name[this_length - 1],
					"which is different from the expected right name delimiter",
					name_right[this_idx],
					"for the corresponding left name delimiter",
					name_left[this_idx]);
				return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if ((this_length = strlen(item_ptr->value)) < 2) {
				sprintf(error_text, "%s %u %s '%-.500s' (%s=%s) %s (%u).",
					"The configuration parameter value loaded from line number",
					src_ptr->line_number, "in file", src_ptr->file_name,
					item_ptr->name, item_ptr->value,
					"is too short to contain value delimiters", this_length);
				return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if ((this_idx = idxchr(value_left, *item_ptr->value)) == -1) {
				sprintf(error_text,
					"%s %u %s '%-.500s' (%s=%s) %s ('%c') %s ('%s').",
					"The configuration parameter value loaded from line number",
					src_ptr->line_number, "in file", src_ptr->file_name,
					item_ptr->name, item_ptr->value,
					"begins with a character", *item_ptr->value,
					"which is not in the list of valid left value delimiters",
					value_left);
				return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if (value_right[this_idx] != item_ptr->value[this_length - 1]) {
				sprintf(error_text,
					"%s %u %s '%-.500s' (%s=%s) %s ('%c') %s ('%c') %s ('%c').",
					"The configuration parameter value loaded from line number",
					src_ptr->line_number, "in file", src_ptr->file_name,
					item_ptr->name, item_ptr->value,
					"ends with a character", item_ptr->value[this_length - 1],
					"which is different from the expected right value delimiter",
					value_right[this_idx],
					"for the corresponding left value delimiter",
					value_left[this_idx]);
				return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */


