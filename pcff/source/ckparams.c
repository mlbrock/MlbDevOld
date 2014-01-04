/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a 'PCFF_PARAM_SPEC' structure.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2014.
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

/*	***********************************************************************	*/
int PCFF_CheckParamSpec(const PCFF_PARAM_SPEC *param_spec_ptr,
	char *error_text)
{
	int               return_code = PCFF_SUCCESS;
	unsigned int     *used_list   = NULL;
	unsigned int      count_1;
	unsigned int      count_2;
	unsigned int      bad_field;
	const PCFF_PARAM *param_ptr;
	char              param_text_1[PCFF_MAX_ERROR_TEXT];
	char              param_text_2[PCFF_MAX_ERROR_TEXT];


	if (!param_spec_ptr->structure_size) {
		strcpy(error_text, "Parameter data structure size is zero (0).");
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (param_spec_ptr->param_count > (UINT_MAX - 2)) {
		sprintf(error_text,
			"The number of parameters (%u) exceeds the maximum (%u).",
			param_spec_ptr->param_count, UINT_MAX - 2);
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (!param_spec_ptr->param_count)
		goto EXIT_FUNCTION;

	if ((return_code = PCFF_CheckParamList(param_spec_ptr->param_count,
		param_spec_ptr->param_list, error_text)) != PCFF_SUCCESS)
		goto EXIT_FUNCTION;

	for (count_1 = 0, param_ptr = param_spec_ptr->param_list;
		count_1 < param_spec_ptr->param_count; count_1++, param_ptr++) {
		/* ***********************************************************
			***********************************************************
			Check the field offset to ensure that the field begins
			within the size of parameter data structure . . .
			*********************************************************** */
		if (param_ptr->field_offset >= param_spec_ptr->structure_size) {
			sprintf(error_text, "%s %s: %s (%u) --- %s %u.",
				"Error encountered in",
				PCFF_GetParamTextIndex(param_ptr, count_1, param_text_1),
				"Invalid field offset", param_ptr->field_offset,
				"the maximum field offset within the parameter data structure is",
				param_spec_ptr->structure_size - 1);
			return_code = PCFF_FAILURE;
			goto EXIT_FUNCTION;
		}
		/* ***********************************************************
			***********************************************************
			Check the total of field offset and the field length to
			ensure that the field falls entirely within the size of
			parameter data structure . . .
			*********************************************************** */
		if ((param_ptr->field_offset + param_ptr->field_length) >
			param_spec_ptr->structure_size) {
			sprintf(error_text, "%s %s: %s (%u + %u = %u) %s (%u).",
				"Error encountered in",
				PCFF_GetParamTextIndex(param_ptr, count_1, param_text_1),
				"The total of the field offset and the field length",
				param_ptr->field_offset, param_ptr->field_length,
				param_ptr->field_offset + param_ptr->field_length,
				"exceeds the length of the parameter data structure",
				param_spec_ptr->structure_size);
			return_code = PCFF_FAILURE;
			goto EXIT_FUNCTION;
		}
		/* ***********************************************************	*/
	}

	/* *****************************************************************
		*****************************************************************
		Set-up the memory used list for the 'PCFF_CFG' structure . . .
		***************************************************************** */
	if ((used_list = ((unsigned int *) calloc(param_spec_ptr->structure_size,
		sizeof(unsigned int)))) == NULL) {
		STR_AllocMsgList(param_spec_ptr->structure_size, sizeof(unsigned int),
			error_text,
			"Unable to allocate memory for the used parameter data bytes list");
		return_code = PCFF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* *****************************************************************	*/

	/* *****************************************************************
		*****************************************************************
		Ensure that parameter members do not overlap within the structure.
		***************************************************************** */
	for (count_1 = 0, param_ptr = param_spec_ptr->param_list;
		count_1 < param_spec_ptr->param_count; count_1++, param_ptr++) {
		for (count_2 = 0; count_2 < param_ptr->field_length; count_2++) {
			if (!used_list[param_ptr->field_offset + count_2])
				used_list[param_ptr->field_offset + count_2] = count_1 + 1;
			else {
				bad_field = used_list[param_ptr->field_offset + count_2] - 1;
				sprintf(error_text, "%s %u %s: %s %s and %s.",
					"Overlapping parameters detected beginning at offset",
					param_ptr->field_offset + count_2,
					"within the parameter data structure",
					"Overlapped parameters are",
					PCFF_GetParamTextIndex(param_ptr, count_1, param_text_1),
					PCFF_GetParamTextIndex(param_spec_ptr->param_list + bad_field,
						bad_field, param_text_2));
					return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
	}
	/* *****************************************************************	*/

EXIT_FUNCTION:

	if (used_list != NULL)
		free(used_list);

	return(return_code);
}
/*	***********************************************************************	*/


