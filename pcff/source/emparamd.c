/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits the structure members and their associated
								configuration parameters.

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

#include <memory.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions private to this module . . .			*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void PCFF_EmitParam,
	(const PCFF_PARAM *param_ptr, const PCFF_ITEM *item_ptr,
	const void *data_ptr, unsigned int name_length, unsigned int member_length,
	unsigned int value_length, unsigned int number_length,
	unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control));
COMPAT_FN_DECL_STATIC(void PCFF_EmitParamSpecDataHeader,
	(unsigned int name_length, unsigned int member_length,
	unsigned int value_length, unsigned int number_length,
	unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control));
COMPAT_FN_DECL_STATIC(void PCFF_EmitParamSpecDataTrailer,
	(unsigned int name_length, unsigned int member_length,
	unsigned int value_length, unsigned int number_length,
	unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control));
COMPAT_FN_DECL_STATIC(void PCFF_EmitParamSpecDataHeader1,
	(unsigned int name_length, unsigned int member_length,
	unsigned int value_length, unsigned int number_length,
	unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control));
COMPAT_FN_DECL_STATIC(void PCFF_EmitParamSpecDataHeader2,
	(unsigned int name_length, unsigned int member_length,
	unsigned int value_length, unsigned int number_length,
	unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control));
COMPAT_FN_DECL_STATIC(void PCFF_EmitParamSpecDataHeader3,
	(unsigned int name_length, unsigned int member_length,
	unsigned int value_length, unsigned int number_length,
	unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control));
/* *********************************************************************** */

/* *********************************************************************** */
void PCFF_EmitParamSpecData(const PCFF_CFG *cfg_ptr,
	const PCFF_PARAM_SPEC *param_spec_ptr, const void *data_ptr, int full_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
{
	PCFF_EmitParamSpecDataBasic(cfg_ptr, param_spec_ptr, data_ptr, full_flag,
		NULL, output_function, output_control);
}
/* *********************************************************************** */

/* *********************************************************************** */
void PCFF_EmitParamSpecDataBasic(const PCFF_CFG *cfg_ptr,
	const PCFF_PARAM_SPEC *param_spec_ptr, const void *data_ptr, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control)
{
	unsigned int      count_1;
	unsigned int      item_index;
	const PCFF_PARAM *param_ptr;
	const PCFF_ITEM  *item_ptr;
	unsigned int      used_item_count;
	char             *used_flag_ptr = NULL;
	char              used_flag_buffer[1024];
	unsigned int      name_length;
	unsigned int      value_length;
	unsigned int      number_length;
	unsigned int      file_length;
	unsigned int      member_length;

	STR_EMIT_SetDefaults(&output_function_text, &output_control);

	name_length     = PCFF_GetLongestName(cfg_ptr);
	member_length   = PCFF_GetLongestMemberName(param_spec_ptr);
	value_length    = PCFF_GetLongestValue(cfg_ptr);
	number_length   = PCFF_GetLongestLineNumber(cfg_ptr);
	file_length     = PCFF_GetLongestFileName(cfg_ptr);

	name_length     = (name_length > 9)    ? name_length   :  9;
	member_length   = (member_length > 6)  ? member_length :  6;
	value_length    = (value_length > 31)  ? value_length  : 31;
	number_length   = (number_length > 6)  ? number_length :  6;
	file_length     = (file_length > 4)    ? file_length   :  4;

	used_item_count = cfg_ptr->item_count;

	if (cfg_ptr->item_count <=
		(sizeof(used_flag_buffer) / sizeof(used_flag_buffer[0])))
		used_flag_ptr = used_flag_buffer;
	else if ((used_flag_ptr = ((char *) calloc(cfg_ptr->item_count,
		sizeof(char)))) != NULL)
		used_item_count = cfg_ptr->item_count;
	else {
		used_item_count = sizeof(used_flag_buffer) /
			sizeof(used_flag_buffer[0]);
		used_flag_ptr   = used_flag_buffer;
	}

	memset(used_flag_ptr, '\0', used_item_count * sizeof(char));

	if (output_function_lead != NULL)
		(*output_function_lead)(output_control);
	STR_EMIT_CharLine('=',  name_length + 1 + member_length + 1 +
		value_length + 1 + number_length + 1 + file_length,
		output_function_text, output_control);

	PCFF_EmitParamSpecDataHeader(name_length, member_length, value_length,
		number_length, file_length, full_flag, output_function_lead,
		output_function_text, output_control);

	for (count_1 = 0, param_ptr = param_spec_ptr->param_list;
		count_1 < param_spec_ptr->param_count; count_1++, param_ptr++) {
		if (((item_ptr = PCFF_FindItem(cfg_ptr, param_ptr->param_name,
			&item_index)) != NULL) && (item_index < used_item_count))
			used_flag_ptr[item_index] = 1;
		PCFF_EmitParam(param_ptr, item_ptr, data_ptr, name_length, member_length,
			value_length, number_length, file_length, full_flag,
			output_function_lead, output_function_text, output_control);
	}

	for (count_1 = 0, item_ptr = cfg_ptr->item_list;
		count_1 < used_item_count; count_1++, item_ptr++) {
		if (!used_flag_ptr[count_1]) {
			if (output_function_lead != NULL)
				(*output_function_lead)(output_control);
			(*output_function_text)(output_control,
				"%-*.*s %-*.*s %-*.*s %*u %-.*s\n",
				name_length, name_length, item_ptr->name,
				member_length, member_length, "",
				value_length, value_length, item_ptr->value,
				number_length, item_ptr->src_list->line_number,
				file_length, item_ptr->src_list->file_name);
		}
	}

	PCFF_EmitParamSpecDataTrailer(name_length, member_length, value_length,
		number_length, file_length, full_flag, output_function_lead,
		output_function_text, output_control);

	if (output_function_lead != NULL)
		(*output_function_lead)(output_control);
	STR_EMIT_CharLine('=',  name_length + 1 + member_length + 1 +
		value_length + 1 + number_length + 1 + file_length,
		output_function_text, output_control);

	if ((used_flag_ptr != NULL) && (used_flag_ptr != used_flag_buffer))
		free(used_flag_ptr);
}
/* *********************************************************************** */

/* *********************************************************************** */
static void PCFF_EmitParam(const PCFF_PARAM *param_ptr,
	const PCFF_ITEM *item_ptr, const void *data_ptr, unsigned int name_length,
	unsigned int member_length, unsigned int value_length,
	unsigned int number_length, unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control)
{
	const void *this_ptr;
	const char *tmp_ptr;

	if (output_function_lead != NULL)
		(*output_function_lead)(output_control);

	(*output_function_text)(output_control, "%-*.*s ",
		name_length, name_length, (item_ptr != NULL) ? item_ptr->name : "");

	(*output_function_text)(output_control, "%-*.*s ",
		member_length, member_length, param_ptr->member_name);

	this_ptr =
		((const void *) (((const char *) data_ptr) + param_ptr->field_offset));

	switch (param_ptr->field_type) {
		case PCFF_FLD_TYPE_SCHAR			:
			(*output_function_text)(output_control, "%*d", value_length,
				((int) *((const signed char *) this_ptr)));
			break;
		case PCFF_FLD_TYPE_UCHAR			:
			(*output_function_text)(output_control, "%*u", value_length,
				((unsigned int) *((const unsigned char *) this_ptr)));
			break;
		case PCFF_FLD_TYPE_SSHORT			:
			(*output_function_text)(output_control, "%*d", value_length,
				((int) *((const signed short *) this_ptr)));
			break;
		case PCFF_FLD_TYPE_USHORT			:
			(*output_function_text)(output_control, "%*u", value_length,
				((unsigned int) *((const unsigned short *) this_ptr)));
			break;
		case PCFF_FLD_TYPE_SINT				:
			(*output_function_text)(output_control, "%*d", value_length,
				*((const signed int *) this_ptr));
			break;
		case PCFF_FLD_TYPE_UINT				:
			(*output_function_text)(output_control, "%*u", value_length,
				*((const unsigned int *) this_ptr));
			break;
		case PCFF_FLD_TYPE_SLONG			:
			(*output_function_text)(output_control, "%*ld", value_length,
				*((const signed long *) this_ptr));
			break;
		case PCFF_FLD_TYPE_ULONG			:
			(*output_function_text)(output_control, "%*lu", value_length,
				*((const unsigned long *) this_ptr));
			break;
		case PCFF_FLD_TYPE_FLOAT			:
			(*output_function_text)(output_control, "%*f", value_length,
				((double) *((const float *) this_ptr)));
			break;
		case PCFF_FLD_TYPE_DOUBLE			:
			(*output_function_text)(output_control, "%*f", value_length,
				*((const double *) this_ptr));
			break;
		case PCFF_FLD_TYPE_BOOLEAN			:
			(*output_function_text)(output_control, "%-*.*s",
				value_length, value_length,
				(*((const int *) this_ptr)) ? "TRUE" : "FALSE");
			break;
		case PCFF_FLD_TYPE_IP_HSP			:
		case PCFF_FLD_TYPE_IP_PHS			:
			(*output_function_text)(output_control, "%-*.*s",
				value_length, value_length,
				(((const PCFF_IP_HSP *) this_ptr)->spec_string != NULL) ?
				((const PCFF_IP_HSP *) this_ptr)->spec_string : "");
			break;
			break;
		case PCFF_FLD_TYPE_NONE				:
		case PCFF_FLD_TYPE_STRING			:
		case PCFF_FLD_TYPE_STRING_PTR		:
		case PCFF_FLD_TYPE_DATE_STR		:
		case PCFF_FLD_TYPE_TIME_STR		:
		case PCFF_FLD_TYPE_TIMEVAL_STR	:
		case PCFF_FLD_TYPE_TIMESPEC_STR	:
		case PCFF_FLD_TYPE_PATH_NAME		:
		case PCFF_FLD_TYPE_PATH_NAME_PTR	:
		case PCFF_FLD_TYPE_FILE_NAME		:
		case PCFF_FLD_TYPE_FILE_NAME_PTR	:
		case PCFF_FLD_TYPE_HOST_SPEC		:
		case PCFF_FLD_TYPE_HOST_SPEC_PTR	:
		case PCFF_FLD_TYPE_SERVICE			:
		case PCFF_FLD_TYPE_SERVICE_PTR	:
		case PCFF_FLD_TYPE_PROTOCOL		:
		case PCFF_FLD_TYPE_PROTOCOL_PTR	:
		default									:
			tmp_ptr = (PCFF_FLD_TYPE_IS_STR(param_ptr->field_type)) ?
				((const char *) this_ptr) :
				(PCFF_FLD_TYPE_IS_PTR(param_ptr->field_type)) ?
				*((const char **) this_ptr) : "";
			tmp_ptr = (tmp_ptr != NULL) ? tmp_ptr : "";
			(*output_function_text)(output_control, "%-*.*s",
				value_length, value_length, tmp_ptr);
			break;
	}

	if (full_flag && (item_ptr != NULL)) {
		(*output_function_text)(output_control, " ");
		(*output_function_text)(output_control, "%*u",
			number_length, item_ptr->src_list->line_number);
		(*output_function_text)(output_control, " ");
		(*output_function_text)(output_control, "%-*.*s",
			file_length, file_length, item_ptr->src_list->file_name);
	}

	(*output_function_text)(output_control, "\n");
}
/* *********************************************************************** */

/*	***********************************************************************	*/
static void PCFF_EmitParamSpecDataHeader(unsigned int name_length,
	unsigned int member_length, unsigned int value_length,
	unsigned int number_length, unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control)
{
	STR_EMIT_SetDefaults(&output_function_text, &output_control);

	PCFF_EmitParamSpecDataHeader1(name_length, member_length, value_length,
		number_length, file_length, full_flag, output_function_lead,
		output_function_text, output_control);
	PCFF_EmitParamSpecDataHeader2(name_length, member_length, value_length,
		number_length, file_length, full_flag, output_function_lead,
		output_function_text, output_control);
	PCFF_EmitParamSpecDataHeader3(name_length, member_length, value_length,
		number_length, file_length, full_flag, output_function_lead,
		output_function_text, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void PCFF_EmitParamSpecDataTrailer(unsigned int name_length,
	unsigned int member_length, unsigned int value_length,
	unsigned int number_length, unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control)
{
	STR_EMIT_SetDefaults(&output_function_text, &output_control);

	if (output_function_lead != NULL)
		(*output_function_lead)(output_control);

	STR_EMIT_CharSpace('-',  name_length,
		output_function_text, output_control);
	STR_EMIT_CharSpace('-',  member_length,
		output_function_text, output_control);
	STR_EMIT_Char('-',  value_length,
		output_function_text, output_control);

	if (full_flag) {
		(*output_function_text)(output_control, " ");
		STR_EMIT_CharSpace('-',  number_length,
			output_function_text, output_control);
		STR_EMIT_Char('-',  file_length,
			output_function_text, output_control);
	}

	(*output_function_text)(output_control, "\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void PCFF_EmitParamSpecDataHeader1(unsigned int name_length,
	unsigned int member_length, unsigned int value_length,
	unsigned int number_length, unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control)
{
	STR_EMIT_SetDefaults(&output_function_text, &output_control);

	if (output_function_lead != NULL)
		(*output_function_lead)(output_control);

	(*output_function_text)(output_control, "%-*.*s",
		name_length, name_length, "Parameter");
	(*output_function_text)(output_control, " ");
	(*output_function_text)(output_control, "%-*.*s",
		member_length, member_length, "Member");
	(*output_function_text)(output_control, " ");
	(*output_function_text)(output_control, "%-*.*s",
		value_length, value_length, "Parameter/Member");

	if (full_flag) {
		(*output_function_text)(output_control, " ");
		(*output_function_text)(output_control, "%-*.*s",
			number_length, number_length, "Line");
		(*output_function_text)(output_control, " ");
		(*output_function_text)(output_control, "%-*.*s",
			file_length, file_length, "File");
	}

	(*output_function_text)(output_control, "\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void PCFF_EmitParamSpecDataHeader2(unsigned int name_length,
	unsigned int member_length, unsigned int value_length,
	unsigned int number_length, unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *),
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control)
{
	STR_EMIT_SetDefaults(&output_function_text, &output_control);

	if (output_function_lead != NULL)
		(*output_function_lead)(output_control);

	(*output_function_text)(output_control, "%-*.*s",
		name_length, name_length, "Name");
	(*output_function_text)(output_control, " ");
	(*output_function_text)(output_control, "%-*.*s",
		member_length, member_length, "Name");
	(*output_function_text)(output_control, " ");
	(*output_function_text)(output_control, "%-*.*s",
		value_length, value_length, "Value");

	if (full_flag) {
		(*output_function_text)(output_control, " ");
		(*output_function_text)(output_control, "%-*.*s",
			number_length, number_length, "Number");
		(*output_function_text)(output_control, " ");
		(*output_function_text)(output_control, "%-*.*s",
			file_length, file_length, "Name");
	}

	(*output_function_text)(output_control, "\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void PCFF_EmitParamSpecDataHeader3(unsigned int name_length,
	unsigned int member_length, unsigned int value_length,
	unsigned int number_length, unsigned int file_length, int full_flag,
	int (*output_function_lead)(void *), 
	STR_FUNC_TYPE_fprintf output_function_text, void *output_control)
{
	STR_EMIT_SetDefaults(&output_function_text, &output_control);

	PCFF_EmitParamSpecDataTrailer(name_length, member_length, value_length,
		number_length, file_length, full_flag, output_function_lead,
		output_function_text, output_control);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

#include <mlog.h>

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

#define TEST_MLOG_FILE_NAME				"TEST_PCFF_LogParamSpecData.txt"
COMPAT_FN_DECL(int  main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int                     return_code = PCFF_SUCCESS;
	MLOG                   *mlog_ptr    = NULL;
	unsigned int            count_1;
	unsigned int            line_count;
	char                  **line_list;
	PCFF_CFG                cfg_data;
	PCFF_PARSE_SPEC         parse_spec;
	PCFF_PARAM_SPEC         param_spec;
	PCFF_PARAM_SPEC         tmp_param_spec;
	PCFF_TEST_TARGET_DATA   test_data;
	char                    error_text[PCFF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for 'PCFF_EmitParamSpecData()'\n");
	fprintf(stderr, "                 'PCFF_EmitParamSpecDataBasic()'\n");
	fprintf(stderr, "---- ------- --- -------------------------------\n\n");

	PCFF_InitCfg(&cfg_data);
	PCFF_InitParamSpec(&param_spec);
	PCFF_TEST_InitData(&test_data);

	if ((mlog_ptr = MLOG_FOpenDefault(TEST_MLOG_FILE_NAME)) == NULL) {
		sprintf(error_text, "Unable to open test file '%s'.\n",
			TEST_MLOG_FILE_NAME);
		return_code = PCFF_FAILURE;
		goto EXIT_FUNCTION;
	}

	PCFF_TEST_GetTestDataParam(&line_count, &line_list, &parse_spec,
		&tmp_param_spec);
	if ((return_code = PCFF_CreateParamSpec(tmp_param_spec.structure_size,
		tmp_param_spec.param_count, tmp_param_spec.param_list, &param_spec,
		error_text)) != PCFF_SUCCESS)
		goto EXIT_FUNCTION;

	if (argc == 1) {
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		printf("Configuration File: %s\n", "<<<INTERNAL LIST>>>");
		if ((return_code = PCFF_LoadFromList(&cfg_data, PCFF_FLAG_NONE,
			"<<<INTERNAL LIST>>>", line_count, line_list, error_text)) ==
			PCFF_SUCCESS) {
			parse_spec.flags = PCFF_FLAG_UNKNOWN_OK;
			if ((return_code = PCFF_PostProcess(&cfg_data, &parse_spec,
				error_text)) != PCFF_SUCCESS)
				goto EXIT_FUNCTION;
			if ((return_code = PCFF_DoParams(&cfg_data, PCFF_FLAG_NONE,
				&param_spec, &test_data, error_text)) != PCFF_SUCCESS)
				goto EXIT_FUNCTION;
			PCFF_EmitParamSpecDataBasic(&cfg_data, &param_spec, &test_data,
				PCFF_TRUE, STR_EMIT_LEAD_CAST(MLOG_LogLeaderInfo),
				STR_EMIT_TEXT_CAST(MLOG_LogTextInfo), mlog_ptr);
			PCFF_TEST_FreeData(&test_data);
			PCFF_FreeCfg(&cfg_data);
		}
		else
			goto EXIT_FUNCTION;
	}

	PCFF_InitParse(&parse_spec);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		printf("Configuration File: %s\n", argv[count_1]);
		if ((return_code = PCFF_LoadFromFile(&cfg_data, PCFF_FLAG_NONE,
			argv[count_1], error_text)) != PCFF_SUCCESS)
			break;
		parse_spec.flags = PCFF_FLAG_UNKNOWN_OK;
		if ((return_code = PCFF_PostProcess(&cfg_data, &parse_spec,
			error_text)) != PCFF_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = PCFF_DoParams(&cfg_data, PCFF_FLAG_NONE,
			&param_spec, &test_data, error_text)) != PCFF_SUCCESS)
			goto EXIT_FUNCTION;
		PCFF_EmitParamSpecDataBasic(&cfg_data, &param_spec, &test_data,
			PCFF_TRUE, STR_EMIT_LEAD_CAST(MLOG_LogLeaderInfo),
			STR_EMIT_TEXT_CAST(MLOG_LogTextInfo), mlog_ptr);
		PCFF_TEST_FreeData(&test_data);
		PCFF_FreeCfg(&cfg_data);
	}

EXIT_FUNCTION:

	MLOG_Close(mlog_ptr, NULL);

	PCFF_FreeCfg(&cfg_data);
	PCFF_FreeParamSpec(&param_spec);
	PCFF_TEST_FreeData(&test_data);

	if (return_code != PCFF_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */


