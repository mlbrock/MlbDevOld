/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Run-time logic for the executable 'adfdiff'.

	Revision History	:	1996-04-05 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
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
#define ADF_RUN_DIFF_VERSION_NUMBER		"01.00.00A"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
static const ADF_RUN_USAGE ADF_RUN_DIFF_UsageFuncList[] = {
	{	ADF_TRUE,	ADF_BUSE_Help,						NULL	},
	{	ADF_TRUE,	ADF_BUSE_Version,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_CheckOnlyFlag,			NULL	},
	{	ADF_TRUE,	ADF_BUSE_LogFlag,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_LogDir,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_QuietFlag,				NULL	},
	{	ADF_TRUE,	ADF_BUSE_ContOnErrorFlag,		NULL	},
	{	ADF_TRUE,	ADF_BUSE_CludeEntry,				NULL	},
	{	ADF_TRUE,	ADF_BUSE_CludeHText,				NULL	},
	{	ADF_TRUE,	ADF_OUSE_AreaOrderType,			NULL	},
	{	ADF_TRUE,	ADF_BUSE_IgnoreSection,			NULL	}
};
static const unsigned int  ADF_RUN_DIFF_UsageFuncCount  =
	sizeof(ADF_RUN_DIFF_UsageFuncList) / sizeof(ADF_RUN_DIFF_UsageFuncList[0]);
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
COMPAT_FN_DECL_STATIC(int  ADF_RUN_DIFF_DoDiff,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_DIFF_OpenADFFiles,
	(ADF_CONTROL *control_ptr, unsigned int *entry_count_1,
	ADF_ENTRY **entry_list_1, unsigned int *entry_count_2,
	ADF_ENTRY **entry_list_2, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_DIFF_GetParams,
	(ADF_CONTROL *control_ptr, unsigned int argc, char **argv,
	char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_DIFF_CreateUsageList,
	(ADF_CONTROL *control_ptr, unsigned int *usage_count, char ***usage_list,
	char *error_text));
COMPAT_FN_DECL_STATIC(void ADF_RUN_DIFF_ShowSettings,
	(const ADF_CONTROL *control_ptr));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_DIFF_CheckParams,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_DIFF_Parse,
	(ADF_CONTROL *control_ptr, unsigned int argc, char **argv, int init_flag,
	unsigned int current_arg, char *error_text));
COMPAT_FN_DECL_STATIC(void ADF_RUN_DIFF_End,
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

	if ((return_code = ADF_RUN_DIFF_GetParams(&control_data,
		((unsigned int) argc), argv, error_text)) == ADF_SUCCESS) {
		if (control_data.check_only_flag != ADF_TRUE)
			return_code = ADF_RUN_DIFF_DoDiff(&control_data, error_text);
		if ((return_code != ADF_SUCCESS) &&
			(control_data.log_flag == ADF_TRUE))
			MLOG_LogErr(control_data.mlog_ptr, "%s\n", error_text);
		ADF_RUN_DIFF_End(&control_data, 0, NULL, NULL);
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
static int ADF_RUN_DIFF_DoDiff(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_DIFF_DoDiff(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int                    return_code   = ADF_SUCCESS;
	unsigned int           entry_count_1 = 0;
	ADF_ENTRY             *entry_list_1  = NULL;
	unsigned int           entry_count_2 = 0;
	ADF_ENTRY             *entry_list_2  = NULL;
	unsigned int           not_found_1   = 0;
	unsigned int           not_found_2   = 0;
	unsigned int           no_match      = 0;
	unsigned int           diff_area_index;
	unsigned int           diff_para_index;
	unsigned int           count_1;
	unsigned int           found_index;
	ADF_ENTRY_DATA         entry_data_list_1[ADF_AREA_COUNT];
	ADF_ENTRY_DATA         entry_data_list_2[ADF_AREA_COUNT];
	STR_FUNC_TYPE_fprintf  output_function;
	void                  *output_control;

	output_function = STR_FUNC_TYPE_fprintf_CAST(fprintf);
	output_control  = stdout;

	control_ptr->keep_bad_see_also_flag = ADF_TRUE;

	ADF_INIT_AreaDataList(entry_data_list_1);
	ADF_INIT_AreaDataList(entry_data_list_2);

	if ((return_code = ADF_RUN_DIFF_OpenADFFiles(control_ptr, &entry_count_1,
		&entry_list_1, &entry_count_2, &entry_list_2, error_text)) !=
		ADF_SUCCESS)
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < entry_count_1; ) {
		if (ADF_FIND_FindEntryByBaseName(entry_count_2, entry_list_2,
			entry_list_1[count_1].base_name, &found_index) !=
			STRFUNCS_ITEM_FOUND) {
			if (!not_found_1++) {
				printf("Entries in '%s', but not in '%s':\n",
					control_ptr->in_file_name_list[0],
					control_ptr->in_file_name_list[1]);
				printf("------- -- ");
				STR_EMIT_Char('-', strlen(control_ptr->in_file_name_list[0]) + 2,
					output_function, output_control);
				printf("  --- --- -- ");
				STR_EMIT_CharLine('-',
					strlen(control_ptr->in_file_name_list[1]) + 3, output_function,
					output_control);
			}
			printf("Base name '%s' in source file '%s'\n",
				entry_list_1[count_1].base_name, entry_list_1[count_1].file_name);
			mema_remove(&entry_count_1, ((void **) &entry_list_1),
				sizeof(*entry_list_1), count_1, 1);
		}
		else
			count_1++;
	}

	for (count_1 = 0; count_1 < entry_count_2; ) {
		if (ADF_FIND_FindEntryByBaseName(entry_count_1, entry_list_1,
			entry_list_2[count_1].base_name, &found_index) !=
			STRFUNCS_ITEM_FOUND) {
			if (!not_found_2++) {
				if (not_found_1)
					STR_EMIT_CharLine('=', 78, output_function, output_control);
				printf("Entries in '%s', but not in '%s':\n",
					control_ptr->in_file_name_list[1],
					control_ptr->in_file_name_list[0]);
				printf("------- -- ");
				STR_EMIT_Char('-',
					strlen(control_ptr->in_file_name_list[1]) + 2, output_function,
					output_control);
				printf("  --- --- -- ");
				STR_EMIT_CharLine('-',
					strlen(control_ptr->in_file_name_list[0]) + 3, output_function,
					output_control);
			}
			printf("Base name '%s' in source file '%s'\n",
				entry_list_2[count_1].base_name, entry_list_2[count_1].file_name);
			mema_remove(&entry_count_2, ((void **) &entry_list_2),
				sizeof(*entry_list_2), count_1, 1);
		}
		else
			count_1++;
	}

	for (count_1 = 0; count_1 < entry_count_1; count_1++) {
		ADF_FREE_AreaDataList(entry_data_list_1);
		ADF_INIT_AreaDataList(entry_data_list_2);
		if ((return_code = ADF_GetEntry(control_ptr, entry_list_1 + count_1,
			entry_data_list_2, error_text)) != ADF_SUCCESS)
			break;
		if ((return_code = ADF_COPY_EntryDataList(entry_data_list_2,
			entry_data_list_1, error_text)) != ADF_SUCCESS)
			break;
		ADF_INIT_AreaDataList(entry_data_list_2);
		ADF_FIND_FindEntryByBaseName(entry_count_2, entry_list_2,
			entry_list_1[count_1].base_name, &found_index);
		if ((return_code = ADF_GetEntry(control_ptr, entry_list_2 + found_index,
			entry_data_list_2, error_text)) != ADF_SUCCESS)
			break;
		if (control_ptr->area_order_type != ADF_AREA_ORDER_TYPE_INTERNAL) {
			ADF_SORT_EntrySections(control_ptr->area_order_type,
				entry_data_list_1);
			ADF_SORT_EntrySections(control_ptr->area_order_type,
				entry_data_list_2);
		}
		if (ADF_CMP_EntryDataList(entry_data_list_1, entry_data_list_2,
			&diff_area_index, &diff_para_index) != 0) {
			if (!no_match++) {
				if (not_found_1 || not_found_2)
					STR_EMIT_CharLine('=', 78, output_function, output_control);
				printf("Entries in '%s', different in '%s':\n",
					control_ptr->in_file_name_list[0],
					control_ptr->in_file_name_list[1]);
				printf("------- -- ");
				STR_EMIT_Char('-', strlen(control_ptr->in_file_name_list[0]) + 2,
					output_function, output_control);
				printf("  --------- -- ");
				STR_EMIT_CharLine('-',
					strlen(control_ptr->in_file_name_list[1]) + 3, output_function,
					output_control);
			}
			printf("Base name '%s', from file '%s'/'%s'.\n",
				entry_list_1[count_1].base_name,
				entry_list_1[count_1].file_name, entry_list_2[count_1].file_name);
		}
	}

	if (not_found_1 || not_found_2 || no_match)
		STR_EMIT_CharLine('=', 78, output_function, output_control);

EXIT_FUNCTION:

	mema_remove_all(&entry_count_1, ((void **) &entry_list_1));
	mema_remove_all(&entry_count_2, ((void **) &entry_list_2));

	ADF_FREE_AreaDataList(entry_data_list_1);
	ADF_INIT_AreaDataList(entry_data_list_2);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_DIFF_OpenADFFiles(ADF_CONTROL *control_ptr,
	unsigned int *entry_count_1, ADF_ENTRY **entry_list_1,
	unsigned int *entry_count_2, ADF_ENTRY **entry_list_2, char *error_text)
#else
static int ADF_RUN_DIFF_OpenADFFiles(control_ptr, entry_count_1, entry_list_1,
	entry_count_2, entry_list_2, error_text)
ADF_CONTROL   *control_ptr;
unsigned int  *entry_count_1;
ADF_ENTRY    **entry_list_1;
unsigned int  *entry_count_2;
ADF_ENTRY    **entry_list_2;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;

	*entry_count_1 = 0;
	*entry_list_1  = NULL;
	*entry_count_2 = 0;
	*entry_list_2  = NULL;

	for (count_1 = 0; count_1 < 2; count_1++) {
		if ((return_code = ADF_OpenADFFileIn(control_ptr,
			control_ptr->in_file_name_list[count_1], error_text)) !=
			ADF_SUCCESS) {
			if (count_1)
				mema_remove_all(entry_count_1, ((void **) entry_list_1));
			break;
		}
		ADF_SORT_EntryList(ADF_SORT_ENTRY_BASE_NAME,
			control_ptr->in_entry_count, control_ptr->in_entry_list);
		if (!count_1) {
			*entry_count_1 = control_ptr->in_entry_count;
			*entry_list_1  = control_ptr->in_entry_list;
		}
		else {
			*entry_count_2 = control_ptr->in_entry_count;
			*entry_list_2  = control_ptr->in_entry_list;
		}
		control_ptr->in_entry_count = 0;
		control_ptr->in_entry_list  = NULL;
		mema_remove_all(&control_ptr->in_htext_count,
			((void **) &control_ptr->in_htext_list));
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_DIFF_GetParams(ADF_CONTROL *control_ptr, unsigned int argc,
	char **argv, char *error_text)
#else
static int ADF_RUN_DIFF_GetParams(control_ptr, argc, argv, error_text)
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
		ADF_RUN_DIFF_End, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = ADF_RUN_DIFF_CreateUsageList(control_ptr,
		&usage_count, &usage_list, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

#ifndef NARGS
	if ((return_code = ADF_GetParams(control_ptr,
		((unsigned int) argc), argv, &control_ptr->help_flag,
		&control_ptr->version_flag,
		((int (*)(void *, unsigned int, char **, int, unsigned int, char *))
		ADF_RUN_DIFF_Parse), error_text)) == ADF_SUCCESS) {
#else
	else if ((return_code = ADF_GetParams(control_ptr,
		((unsigned int) argc), argv, &control_ptr->help_flag,
		&control_ptr->version_flag, ADF_RUN_DIFF_Parse, error_text)) ==
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
				ADF_RUN_DIFF_VERSION_NUMBER);
			exit(0);
		}
		else if ((return_code = ADF_RUN_DIFF_CheckParams(control_ptr,
			error_text)) == ADF_SUCCESS) {
			if (control_ptr->log_flag == ADF_TRUE) {
				if (control_ptr->quiet_flag == ADF_TRUE)
					MLOG_SetFlagFile(control_ptr->mlog_ptr, 0, NULL);
				if ((return_code = ADF_RUN_OpenLogFile(control_ptr,
					error_text)) == ADF_SUCCESS)
					ADF_RUN_DIFF_ShowSettings(control_ptr);
			}
		}
		if (return_code != ADF_SUCCESS)
			ADF_RUN_DIFF_End(control_ptr, 0, NULL, NULL);
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
static int ADF_RUN_DIFF_CreateUsageList(ADF_CONTROL *control_ptr,
	unsigned int *usage_count, char ***usage_list, char *error_text)
#else
static int ADF_RUN_DIFF_CreateUsageList(control_ptr, usage_count, usage_list,
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

	sprintf(buffer, "\tThis is version %s of %s.", ADF_RUN_DIFF_VERSION_NUMBER,
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

	for (count_1 = 0; count_1 < ADF_RUN_DIFF_UsageFuncCount; count_1++) {
		if (((return_code =
			(*ADF_RUN_DIFF_UsageFuncList[count_1].usage_function)(NULL,
			ADF_RUN_DIFF_UsageFuncList[count_1].optional_flag, NULL, usage_count,
			usage_list, error_text)) != ADF_SUCCESS) ||
			((ADF_RUN_DIFF_UsageFuncList[count_1].added_text != NULL) &&
			((return_code = ADF_BUSE_AppendLine(
			ADF_RUN_DIFF_UsageFuncList[count_1].added_text, usage_count,
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
static void ADF_RUN_DIFF_ShowSettings(const ADF_CONTROL *control_ptr)
#else
static void ADF_RUN_DIFF_ShowSettings(control_ptr)
const ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	MLOG_DoSepStart(control_ptr->mlog_ptr);

	MLOG_LogInfo(control_ptr->mlog_ptr, "Program Name       : %s\n",
		control_ptr->program_name);
	MLOG_LogInfo(control_ptr->mlog_ptr, "Version Number     : %s\n",
		ADF_RUN_DIFF_VERSION_NUMBER);
	MLOG_LogInfo(control_ptr->mlog_ptr, "Host Name          : %s\n",
		control_ptr->host_name);
	MLOG_LogInfo(control_ptr->mlog_ptr, "Process ID         : %u\n",
		control_ptr->process_id);
	MLOG_LogInfo(control_ptr->mlog_ptr, "Current Directory  : %s\n",
		control_ptr->current_dir);
	MLOG_LogInfo(control_ptr->mlog_ptr, "Log File Name      : %s\n",
		control_ptr->log_file_name);

	MLOG_DoSepEqual(control_ptr->mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_DIFF_CheckParams(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_DIFF_CheckParams(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_BAD_ARGS_FAILURE;

	if (!control_ptr->in_file_name_count)
		strcpy(error_text,
			"No ADF database files were specified on the command line.");
	else if (control_ptr->in_file_name_count == 1)
		strcpy(error_text,
			"Two ADF database files are required to perform the 'diff'.");
	else if (control_ptr->in_file_name_count > 2)
		strcpy(error_text,
			"Only two ADF database files are requireed to perform the 'diff'.");
	else
		return_code = ADF_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_DIFF_Parse(ADF_CONTROL *control_ptr, unsigned int argc,
	char **argv, int init_flag, unsigned int current_arg, char *error_text)
#else
static int ADF_RUN_DIFF_Parse(control_ptr, argc, argv, init_flag, current_arg,
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
		if (ADF_BARG_CheckOnlyFlag(this_arg, &arg_length, &data_ptr,
			&control_ptr->check_only_flag, &return_code, error_text) == ADF_TRUE)
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
		else if (ADF_OARG_AreaOrderType(this_arg, &arg_length, &data_ptr,
			&control_ptr->area_order_type, &return_code, error_text) == ADF_TRUE)
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
static void ADF_RUN_DIFF_End(ADF_CONTROL *control_ptr, int signal_number,
	int *exit_code_ptr, const char *message_buffer)
#else
static void ADF_RUN_DIFF_End(control_ptr, signal_number, exit_code_ptr,
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

