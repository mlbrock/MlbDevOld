/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Run-time logic for the executable 'adfcomb'.

	Revision History	:	1995-08-25 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "adfrun.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define ADF_RUN_COMB_VERSION_NUMBER		"01.00.00A"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
static const ADF_RUN_USAGE ADF_RUN_COMB_UsageFuncList[] = {
	{	ADF_TRUE,	ADF_BUSE_Help,						NULL	},
	{	ADF_TRUE,	ADF_BUSE_Version,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_CheckOnlyFlag,			NULL	},
	{	ADF_FALSE,	ADF_PUSE_PrepADFFile,			NULL	},
	{	ADF_TRUE,	ADF_BUSE_LogFlag,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_LogDir,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_DuplicateType,			NULL	},
	{	ADF_TRUE,	ADF_BUSE_QuietFlag,				NULL	},
	{	ADF_TRUE,	ADF_BUSE_SortOrderType,			NULL	},
	{	ADF_TRUE,	ADF_BUSE_ContOnErrorFlag,		NULL	},
	{	ADF_TRUE,	ADF_BUSE_CludeEntry,				NULL	},
	{	ADF_TRUE,	ADF_BUSE_CludeHText,				NULL	},
	{	ADF_TRUE,	ADF_BUSE_IgnoreSection,			NULL	}
};
static const unsigned int  ADF_RUN_COMB_UsageFuncCount  =
	sizeof(ADF_RUN_COMB_UsageFuncList) / sizeof(ADF_RUN_COMB_UsageFuncList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 32000;
#endif /* __MSDOS__ */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL(int main, (int argc, char **argv));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_COMB_DoCombine,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_COMB_GetParams,
	(ADF_CONTROL *control_ptr, unsigned int argc, char **argv,
	char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_COMB_CreateUsageList,
	(ADF_CONTROL *control_ptr, unsigned int *usage_count, char ***usage_list,
	char *error_text));
COMPAT_FN_DECL_STATIC(void ADF_RUN_COMB_ShowSettings,
	(const ADF_CONTROL *control_ptr));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_COMB_CheckParams,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_COMB_Parse,
	(ADF_CONTROL *control_ptr, unsigned int argc, char **argv,
	int init_flag, unsigned int current_arg, char *error_text));
COMPAT_FN_DECL_STATIC(void ADF_RUN_COMB_End,
	(ADF_CONTROL *control_ptr, int signal_number, int *exit_code_ptr,
	 const char *message_buffer));

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int         return_code;
	ADF_CONTROL control_data;
	char        error_text[ADF_MAX_ERROR_TEXT];

	memset(&control_data, '\0', sizeof(control_data));

	if ((return_code = ADF_RUN_COMB_GetParams(&control_data,
		((unsigned int) argc), argv, error_text)) == ADF_SUCCESS) {
		if ((return_code = ADF_LoadInFileList(&control_data, error_text)) ==
			ADF_SUCCESS) {
			if (!control_data.in_file_count) {
				strcpy(error_text,
					"No ADF database files were specified on the command line.");
				return_code = ADF_BAD_ARGS_FAILURE;
			}
			else if ((return_code = ADF_FinalizeEntries(&control_data,
				error_text)) == ADF_SUCCESS)
				return_code = ADF_RUN_COMB_DoCombine(&control_data,
					error_text);
		}
		if ((return_code != ADF_SUCCESS) &&
			(control_data.log_flag == ADF_TRUE))
			MLOG_LogErr(control_data.mlog_ptr, "%s\n", error_text);
		ADF_RUN_COMB_End(&control_data, 0, NULL, NULL);
		GEN_SIGNAL_SignalDefault();
	}

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n%s", error_text,
			(return_code != ADF_BAD_ARGS_FAILURE) ? "" :
			"       Help is available with the '-HELP' parameter.\n\n");

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_COMB_DoCombine(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_COMB_DoCombine(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int                  return_code = ADF_SUCCESS;
	unsigned int         count_1;
	unsigned int         count_2;
	ADF_ENTRY           *entry_ptr;
	ADF_ENTRY            entry_data;
	ADF_SOURCE_DATA      area_list[ADF_AREA_COUNT];
	ADF_ENTRY_DATA_FILE  file_entry_data;

	if ((control_ptr->check_only_flag != ADF_TRUE) && ((return_code =
		ADF_OpenADFFilePrep(control_ptr, control_ptr->prep_adf_file_name,
		error_text)) != ADF_SUCCESS))
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < control_ptr->in_entry_count; count_1++) {
		entry_ptr = control_ptr->in_entry_order_list[count_1];
		if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr, "%s(%s) --- ", entry_ptr->base_name,
				entry_ptr->file_name);
		if ((return_code = ADF_ReadEntry(control_ptr, entry_ptr,
			&file_entry_data, area_list, error_text)) != ADF_SUCCESS)
			break;
		entry_data             = *entry_ptr;
		entry_data.file_index  = 0;
		entry_data.entry_index = count_1;
		if ((control_ptr->check_only_flag != ADF_TRUE) && ((return_code =
			ADF_WriteEntry(control_ptr, &entry_data, area_list, error_text)) !=
			ADF_SUCCESS))
			break;
		for (count_2 = 0; count_2 < control_ptr->in_htext_count; count_2++) {
			if ((control_ptr->in_htext_list[count_2].file_index ==
				entry_ptr->file_index) &&
				(control_ptr->in_htext_list[count_2].entry_index ==
				entry_ptr->entry_index)) {
				control_ptr->in_htext_list[count_2].file_index  = 0;
				control_ptr->in_htext_list[count_2].entry_index = count_1;
			}
		}
		*entry_ptr = entry_data;
		if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr, "OK\n");
	}

	if (return_code == ADF_SUCCESS) {
		if (control_ptr->check_only_flag != ADF_TRUE)
			return_code = ADF_WriteTrailer(control_ptr,
				control_ptr->in_entry_count, control_ptr->in_entry_list,
				control_ptr->in_htext_count, control_ptr->in_htext_list,
				error_text);
	}
	else if (control_ptr->quiet_flag == ADF_TRUE)
		fprintf(stderr, "ERROR: %s\n", error_text);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_COMB_GetParams(ADF_CONTROL *control_ptr, unsigned int argc,
	char **argv, char *error_text)
#else
static int ADF_RUN_COMB_GetParams(control_ptr, argc, argv, error_text)
ADF_CONTROL   *control_ptr;
unsigned int   argc;
char         **argv;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   usage_count = 0;
	char         **usage_list  = NULL;

	if ((return_code = ADF_RUN_GetParamsInit(control_ptr, argc, argv,
		ADF_RUN_COMB_End, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = ADF_RUN_COMB_CreateUsageList(control_ptr,
		&usage_count, &usage_list, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

#ifndef NARGS
	if ((return_code = ADF_GetParams(control_ptr,
		((unsigned int) argc), argv, &control_ptr->help_flag,
		&control_ptr->version_flag,
		((int (*)(void *, unsigned int, char **, int, unsigned int, char *))
		ADF_RUN_COMB_Parse), error_text)) == ADF_SUCCESS) {
#else
	else if ((return_code = ADF_GetParams(control_ptr,
		((unsigned int) argc), argv, &control_ptr->help_flag,
		&control_ptr->version_flag, ADF_RUN_COMB_Parse, error_text)) ==
		ADF_SUCCESS) {
#endif /* #ifndef NARGS */
		if (control_ptr->help_flag == ADF_TRUE) {
			ADF_FREE_Control(control_ptr);
			GEN_SIGNAL_SignalDefault();
			ADF_DoFormatUsage(return_code, argv[0],
				"Help request with '-HELP' noted . . .", usage_list);
		}
		else if (control_ptr->version_flag == ADF_TRUE) {
			ADF_FREE_Control(control_ptr);
			GEN_SIGNAL_SignalDefault();
			fprintf(stderr, "%s Version Number %s\n", argv[0],
				ADF_RUN_COMB_VERSION_NUMBER);
			exit(0);
		}
		else if ((return_code = ADF_RUN_COMB_CheckParams(control_ptr,
			error_text)) == ADF_SUCCESS) {
			if (control_ptr->log_flag == ADF_TRUE) {
				if (control_ptr->quiet_flag == ADF_TRUE)
					MLOG_SetFlagFile(control_ptr->mlog_ptr, 0, NULL);
				if ((return_code = ADF_RUN_OpenLogFile(control_ptr,
					error_text)) == ADF_SUCCESS)
					ADF_RUN_COMB_ShowSettings(control_ptr);
			}
		}
		if (return_code != ADF_SUCCESS)
			ADF_RUN_COMB_End(control_ptr, 0, NULL, NULL);
	}

EXIT_FUNCTION:

	SDTIF_GetTimeUSecs(&control_ptr->overhead_end_time);

	strl_remove_all(&usage_count, &usage_list);

	if (return_code != ADF_SUCCESS)
		ADF_FREE_Control(control_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_COMB_CreateUsageList(ADF_CONTROL *control_ptr,
	unsigned int *usage_count, char ***usage_list, char *error_text)
#else
static int ADF_RUN_COMB_CreateUsageList(control_ptr, usage_count, usage_list,
	error_text)
ADF_CONTROL    *control_ptr;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_MEMORY_FAILURE;
	unsigned int count_1;
	char         buffer[4096];

	*usage_count = 0;
	*usage_list  = NULL;

	*error_text  = '\0';

	sprintf(buffer, "\t%s [<a mixture of '-' parameters, and '@' commands>]",
		control_ptr->short_program_name);
	if (strl_append(usage_count, usage_list, "Usage:") != STRFUNCS_SUCCESS)
		goto EXIT_FUNCTION;
	else if (strl_append(usage_count, usage_list, "------") !=
		STRFUNCS_SUCCESS)
		goto EXIT_FUNCTION;
	else if (strl_append(usage_count, usage_list, buffer) != STRFUNCS_SUCCESS)
		goto EXIT_FUNCTION;
	else if (strl_append(usage_count, usage_list, "\n") != STRFUNCS_SUCCESS)
		goto EXIT_FUNCTION;
	else if (strl_append(usage_count, usage_list, "Description:") !=
		STRFUNCS_SUCCESS)
		goto EXIT_FUNCTION;
	else if (strl_append(usage_count, usage_list, "------------") !=
		STRFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	sprintf(buffer, "\tThis is version %s of %s.", ADF_RUN_COMB_VERSION_NUMBER,
		control_ptr->short_program_name);
	if (strl_append(usage_count, usage_list, buffer) != STRFUNCS_SUCCESS)
		goto EXIT_FUNCTION;
	else if (strl_append(usage_count, usage_list, "\n") != STRFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	if (strl_append(usage_count, usage_list, "Parameters:") !=
		STRFUNCS_SUCCESS)
		goto EXIT_FUNCTION;
	else if (strl_append(usage_count, usage_list, "-----------") !=
		STRFUNCS_SUCCESS)
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < ADF_RUN_COMB_UsageFuncCount; count_1++) {
		if (((return_code =
			(*ADF_RUN_COMB_UsageFuncList[count_1].usage_function)(NULL,
			ADF_RUN_COMB_UsageFuncList[count_1].optional_flag, NULL, usage_count,
			usage_list, error_text)) != ADF_SUCCESS) ||
			((ADF_RUN_COMB_UsageFuncList[count_1].added_text != NULL) &&
			((return_code = ADF_BUSE_AppendLine(
			ADF_RUN_COMB_UsageFuncList[count_1].added_text, usage_count,
			usage_list, error_text)) != ADF_SUCCESS)))
			goto EXIT_FUNCTION;
	}

	if ((return_code = ADF_BUSE_AppendParamText(usage_count, usage_list,
		error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	return_code = ADF_BUSE_AppendNULL(usage_count, usage_list, error_text);

EXIT_FUNCTION:

	if (return_code != ADF_SUCCESS) {
		strl_remove_all(usage_count, usage_list);
		if (!(*error_text))
			strcpy(error_text, "Unable to allocate memory for the usage text.");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RUN_COMB_ShowSettings(const ADF_CONTROL *control_ptr)
#else
static void ADF_RUN_COMB_ShowSettings(control_ptr)
const ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	MLOG_DoSepStart(control_ptr->mlog_ptr);

	MLOG_LogInfo(control_ptr->mlog_ptr,
		"Program Name       : %s\n", control_ptr->program_name);
	MLOG_LogInfo(control_ptr->mlog_ptr,
		"Version Number     : %s\n", ADF_RUN_COMB_VERSION_NUMBER);
	MLOG_LogInfo(control_ptr->mlog_ptr,
		"Host Name          : %s\n", control_ptr->host_name);
	MLOG_LogInfo(control_ptr->mlog_ptr,
		"Process ID         : %u\n", control_ptr->process_id);
	MLOG_LogInfo(control_ptr->mlog_ptr,
		"Current Directory  : %s\n", control_ptr->current_dir);
	MLOG_LogInfo(control_ptr->mlog_ptr,
		"Log File Name      : %s\n", control_ptr->log_file_name);

	MLOG_DoSepEqual(control_ptr->mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_COMB_CheckParams(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_COMB_CheckParams(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_BAD_ARGS_FAILURE;
	unsigned int count_1;

	if (control_ptr->prep_adf_file_name == NULL)
		sprintf(error_text, "%s '-ADF_DATA_BASE_FILE=' parameter.",
			"Output ADF database file not specified with the");
	else if (!control_ptr->in_file_name_count)
		strcpy(error_text,
			"No ADF database files were specified on the command line.");
	else {
		return_code = ADF_SUCCESS;
		for (count_1 = 0; count_1 < control_ptr->in_file_name_count;
			count_1++) {
			if (!strcmp(control_ptr->prep_adf_file_name,
				control_ptr->in_file_name_list[count_1])) {
				sprintf(error_text, "%s '%-.500s' %s file (using '%s') %s.",
					"The ADF database file named", control_ptr->prep_adf_file_name,
					"was specified on the command line both as the output ADF",
					"-ADF_DATA_BASE_FILE=", "and an input ADF database file");
				return_code = ADF_BAD_ARGS_FAILURE;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_COMB_Parse(ADF_CONTROL *control_ptr, unsigned int argc,
	char **argv, int init_flag, unsigned int current_arg, char *error_text)
#else
static int ADF_RUN_COMB_Parse(control_ptr, argc, argv, init_flag, current_arg,
	error_text)
ADF_CONTROL   *control_ptr;
unsigned int   argc;
char         **argv;
int            init_flag;
unsigned int   current_arg;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	char         *this_arg;
	char         *data_ptr;
	unsigned int  arg_length;

	if (init_flag != ADF_TRUE) {
		this_arg = argv[current_arg];
		if (ADF_PARG_PrepADFFile(this_arg, &arg_length, &data_ptr,
			&control_ptr->prep_adf_file_name, &return_code, error_text) ==
			ADF_TRUE)
			;
		else if (ADF_BARG_CheckOnlyFlag(this_arg, &arg_length, &data_ptr,
			&control_ptr->check_only_flag, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_BARG_DuplicateType(this_arg, &arg_length, &data_ptr,
			&control_ptr->duplicate_handling_type, &return_code, error_text) ==
			ADF_TRUE)
			;
		else if (ADF_BARG_LogFlag(this_arg, &arg_length, &data_ptr,
			&control_ptr->log_flag, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_BARG_LogDir(this_arg, &arg_length, &data_ptr,
			&control_ptr->log_dir, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_BARG_QuietFlag(this_arg, &arg_length, &data_ptr,
			&control_ptr->quiet_flag, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_BARG_SortOrderType(this_arg, &arg_length, &data_ptr,
			&control_ptr->sort_order_type, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_BARG_ContOnErrorFlag(this_arg, &arg_length, &data_ptr,
			&control_ptr->cont_on_error_flag, &return_code, error_text) ==
			ADF_TRUE)
			;
		else if (ADF_BARG_CludeEntry(this_arg, &arg_length, &data_ptr,
			control_ptr, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_BARG_CludeHText(this_arg, &arg_length, &data_ptr,
			control_ptr, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_BARG_IgnoreSection(this_arg, &arg_length, &data_ptr,
			control_ptr->ignore_section_list, &return_code, error_text) ==
			ADF_TRUE)
			;
		else if (strl_append(&control_ptr->in_file_name_count,
			&control_ptr->in_file_name_list, this_arg) != STRFUNCS_SUCCESS) {
			strcpy(error_text,
				"Unable to allocate memory for the ADF database file list.");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RUN_COMB_End(ADF_CONTROL *control_ptr, int signal_number,
	int *exit_code_ptr, const char *message_buffer)
#else
static void ADF_RUN_COMB_End(control_ptr, signal_number, exit_code_ptr,
	message_buffer)
ADF_CONTROL *control_ptr;
int          signal_number;
int         *exit_code_ptr;
const char  *message_buffer;
#endif /* #ifndef NARGS */
{
	if (control_ptr->shut_down_flag == GENFUNCS_TRUE)
		return;

	ADF_RUN_EndStart(control_ptr, message_buffer);
	ADF_RUN_EndFinish(control_ptr);
}
/*	***********************************************************************	*/

