/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Processes configuration lines from a file.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2016.
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

#include <genfuncs.h>
#include <tfread.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
int PCFF_ProcessFromFile(PCFF_CFG *cfg_ptr, PCFF_FLAG flags,
	const char *in_file, unsigned int *include_stack_count,
	char ***include_stack_list, char *error_text)
{
	int            return_code;
	int            stack_added_flag = PCFF_FALSE;
	unsigned int   tmp_line_count   = 0;
	char         **tmp_line_list    = NULL;
	char          *tmp_file         = NULL;
	unsigned int   count_1;
	char           gen_error_text[GENFUNCS_MAX_ERROR_TEXT];
	char           tfread_error_text[TFREAD_MAX_ERROR_TEXT];

	if ((return_code = GEN_ExpandToFullPathName(in_file, &tmp_file,
		gen_error_text)) != GENFUNCS_SUCCESS) {
		strcat(strcpy(error_text,
			"Unable to expand parameter include file name: "), gen_error_text);
		return_code = PCFF_MAP_ERROR_GEN(return_code);
	}

	for (count_1 = 0; count_1 < *include_stack_count; count_1++) {
		if (!strcmp(tmp_file, (*include_stack_list)[count_1])) {
			sprintf(error_text, "Parameter include file '%-.500s' %s.", tmp_file,
				"may not be included more than once");
			return_code = GENFUNCS_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	if (strl_append(include_stack_count, include_stack_list, tmp_file) !=
		STRFUNCS_SUCCESS) {
		STR_AllocMsgItem(strlen(tmp_file) + 1, error_text, "%s '%-.500s' %s",
			"Unable to add the parameter include file", tmp_file,
			"to the stack of included files");
		return_code = PCFF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	stack_added_flag = PCFF_TRUE;

	if ((return_code = TFREAD_ReadLines(tmp_file, &tmp_line_count,
		&tmp_line_list, tfread_error_text)) != PCFF_SUCCESS) {
		nstrcpy(error_text, tfread_error_text, PCFF_MAX_ERROR_TEXT - 1);
		return_code = PCFF_MAP_ERROR_TFREAD(return_code);
		goto EXIT_FUNCTION;
	}

	return_code = PCFF_ProcessFromList(cfg_ptr, flags, tmp_file,
		tmp_line_count, tmp_line_list, include_stack_count, include_stack_list,
		error_text);

EXIT_FUNCTION:

	if (tmp_file != NULL)
		free(tmp_file);

	strl_remove_all(&tmp_line_count, &tmp_line_list);

	if (stack_added_flag == GENFUNCS_TRUE)
		strl_remove(include_stack_count, include_stack_list,
			*include_stack_count - 1, 1);

	return(return_code);
}
/* *********************************************************************** */


