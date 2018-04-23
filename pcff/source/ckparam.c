/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks 'PCFF_PARAM' structures.

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

#include <strfuncs.h>
#include <sdtif.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CheckParam(const PCFF_PARAM *param_ptr, char *error_text)
{
	int  return_code = PCFF_SUCCESS;
	char param_text[PCFF_MAX_ERROR_TEXT];

	/* ***********************************************************
		***********************************************************
		Check the field type to ensure its validity.
		*********************************************************** */
	if (PCFF_FLD_TYPE_IS_ANY(param_ptr->field_type) != PCFF_TRUE) {
		sprintf(error_text, "%s %s: Invalid field type (%d).",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			param_ptr->field_type);
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	if (PCFF_FLD_TYPE_IS_SET(param_ptr->field_type) != PCFF_TRUE) {
		sprintf(error_text, "%s %s: Invalid field type (%d = '%s').",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			param_ptr->field_type,
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		Check the parameter name to ensure that it's not empty.
		*********************************************************** */
	else if (!param_ptr->param_name[0]) {
		sprintf(error_text, "%s %s: Empty parameter name.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		Check the member name to ensure that it's not empty and
		that it is a valid C/C++ symbol . . .
		*********************************************************** */
	else if (!param_ptr->member_name[0]) {
		sprintf(error_text, "%s %s: Empty member name.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (!iscsymf(*param_ptr->member_name)) {
		sprintf(error_text, "%s %s: Invalid C/C++ symbol name.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		Check the field length to ensure that it's not '0'.
		*********************************************************** */
	else if (!param_ptr->field_length) {
		sprintf(error_text, "%s %s: Invalid field length (0).",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a char field, check the length.
		*********************************************************** */
	else if (((param_ptr->field_type == PCFF_FLD_TYPE_SCHAR) ||
		(param_ptr->field_type == PCFF_FLD_TYPE_UCHAR)) &&
		(param_ptr->field_length != sizeof(char))) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- it should be equal to %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, sizeof(char));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a short field, check the length.
		*********************************************************** */
	else if (((param_ptr->field_type == PCFF_FLD_TYPE_SSHORT) ||
		(param_ptr->field_type == PCFF_FLD_TYPE_USHORT)) &&
		(param_ptr->field_length != sizeof(short))) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- it should be equal to %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, sizeof(short));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a int field, check the length.
		*********************************************************** */
	else if (((param_ptr->field_type == PCFF_FLD_TYPE_SINT) ||
		(param_ptr->field_type == PCFF_FLD_TYPE_UINT)) &&
		(param_ptr->field_length != sizeof(int))) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- it should be equal to %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, sizeof(int));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a long field, check the length.
		*********************************************************** */
	else if (((param_ptr->field_type == PCFF_FLD_TYPE_SLONG) ||
		(param_ptr->field_type == PCFF_FLD_TYPE_ULONG)) &&
		(param_ptr->field_length != sizeof(long))) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- it should be equal to %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, sizeof(long));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a float field, check the length.
		*********************************************************** */
	else if ((param_ptr->field_type == PCFF_FLD_TYPE_FLOAT) &&
		(param_ptr->field_length != sizeof(float))) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- it should be equal to %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, sizeof(float));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a double field, check the length.
		*********************************************************** */
	else if ((param_ptr->field_type == PCFF_FLD_TYPE_DOUBLE) &&
		(param_ptr->field_length != sizeof(double))) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- it should be equal to %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, sizeof(double));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a string field, check the length.
		*********************************************************** */
	else if ((param_ptr->field_type & PCFF_FLD_TYPE_STRING) &&
		(param_ptr->field_length < 2)) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- the minimum is %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, 2);
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a string pointer field, check the length.
		*********************************************************** */
	else if ((param_ptr->field_type & PCFF_FLD_TYPE_STRING_PTR) &&
		(param_ptr->field_length != sizeof(char *))) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- it should be equal to %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, sizeof(char *));
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a date field, check the length.
		*********************************************************** */
	else if ((param_ptr->field_type == PCFF_FLD_TYPE_DATE_STR) &&
		(param_ptr->field_length <= SDTIF_DATE_YYYY_MM_DD_LEN)) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- the minimum is %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, SDTIF_DATE_YYYY_MM_DD_LEN + 1);
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a time field, check the length.
		*********************************************************** */
	else if ((param_ptr->field_type == PCFF_FLD_TYPE_TIME_STR) &&
		(param_ptr->field_length <= SDTIF_TIME_HH_MM_SS_LEN)) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- the minimum is %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, SDTIF_TIME_HH_MM_SS_LEN + 1);
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a timeval field, check the length.
		*********************************************************** */
	else if ((param_ptr->field_type == PCFF_FLD_TYPE_TIMEVAL_STR) &&
		(param_ptr->field_length <= SDTIF_DATE_TIME_TIMEVAL_LEN)) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- the minimum is %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, SDTIF_DATE_TIME_TIMEVAL_LEN + 1);
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* ***********************************************************
		***********************************************************
		If the field is a timespec field, check the length.
		*********************************************************** */
	else if ((param_ptr->field_type == PCFF_FLD_TYPE_TIMESPEC_STR) &&
		(param_ptr->field_length <= SDTIF_DATE_TIME_TIMESPEC_LEN)) {
		sprintf(error_text, "%s %s: %s '%s' (%u) --- the minimum is %u.",
			"Error encountered in", PCFF_GetParamText(param_ptr, param_text),
			"Invalid field length for parameter field type",
			PCFF_GET_FLD_TYPE_NAME_LONG(param_ptr->field_type),
			param_ptr->field_length, SDTIF_DATE_TIME_TIMESPEC_LEN + 1);
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/* *****************************************************************	*/

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int PCFF_CheckParamList(unsigned int param_count, const PCFF_PARAM *param_list,
	char *error_text)
{
	int          return_code = PCFF_SUCCESS;
	unsigned int count_1;
	unsigned int count_2;
	unsigned int ref_index;
	char         param_text_1[PCFF_MAX_ERROR_TEXT];
	char         param_text_2[PCFF_MAX_ERROR_TEXT];

	if (!param_count)
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < param_count; count_1++) {
		if ((return_code = PCFF_CheckParam(param_list + count_1,
			error_text)) != PCFF_SUCCESS)
			goto EXIT_FUNCTION;
		if ((param_list[count_1].field_type == PCFF_FLD_TYPE_FILE_NAME) ||
			(param_list[count_1].field_type == PCFF_FLD_TYPE_FILE_NAME_PTR)) {
			if ((ref_index = param_list[count_1].ref_index) >= count_1) {
				sprintf(error_text, "%s '%s' %s %s (%u): %s %u.",
					"Invalid", 
					PCFF_GET_FLD_TYPE_NAME_LONG(param_list[count_1].field_type),
					"parameter type reference index in",
					PCFF_GetParamTextIndex(param_list + count_1, count_1,
					param_text_1),
					param_list[count_1].ref_index,
					"The parameter reference index must be less than", count_1);
				return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
			}
			if ((param_list[ref_index].field_type != PCFF_FLD_TYPE_PATH_NAME) &&
				(param_list[ref_index].field_type != PCFF_FLD_TYPE_PATH_NAME_PTR)) {
				sprintf(error_text, "%s '%s' %s %s (%u): %s (%s) %s '%s'.",
					"Invalid", 
					PCFF_GET_FLD_TYPE_NAME_LONG(param_list[count_1].field_type),
					"parameter type reference index in",
					PCFF_GetParamTextIndex(param_list + count_1, count_1,
					param_text_1),
					param_list[count_1].ref_index,
					"The parameter to which the reference index refers",
					PCFF_GetParamTextIndex(param_list + ref_index, ref_index,
					param_text_1), "has a type of",
					PCFF_GET_FLD_TYPE_NAME_LONG(param_list[ref_index].field_type));
				return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
	}

	/* *****************************************************************
		*****************************************************************
		Ensure that no parameters are duplicated within the parameter
		list . . .
		***************************************************************** */
	for (count_1 = 0; count_1 < (param_count - 1); count_1++) {
		for (count_2 = (count_1 + 1); count_2 < param_count; count_2++) {
			if (!stricmp(param_list[count_1].member_name,
				param_list[count_2].member_name)) {
				PCFF_GetParamTextIndex(param_list + count_1, count_1,
					param_text_1);
				PCFF_GetParamTextIndex(param_list + count_2, count_2,
					param_text_2);
				sprintf(error_text, "Duplicate member names in %s and %s.",
					PCFF_GetParamTextIndex(param_list + count_1, count_1,
					param_text_1),
					PCFF_GetParamTextIndex(param_list + count_2, count_2,
					param_text_2));
				return_code = PCFF_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
	}
	/* *****************************************************************	*/

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

