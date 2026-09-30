/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Run-time logic for the executable 'adfout'.

	Revision History	:	1995-07-27 --- Creation.
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

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "adfrun.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define ADF_RUN_OUT_VERSION_NUMBER		"01.00.00A"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
static const ADF_RUN_USAGE ADF_RUN_OUT_UsageFuncList[] = {
	{	ADF_TRUE,	ADF_BUSE_Help,						NULL	},
	{	ADF_TRUE,	ADF_BUSE_Version,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_CheckOnlyFlag,			NULL	},
	{	ADF_TRUE,	ADF_BUSE_LogFlag,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_LogDir,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_DuplicateType,			NULL	},
	{	ADF_TRUE,	ADF_BUSE_QuietFlag,				NULL	},
	{	ADF_TRUE,	ADF_BUSE_SortOrderType,			NULL	},
	{	ADF_TRUE,	ADF_OUSE_HyperTextFlag,			NULL	},
	{	ADF_TRUE,	ADF_BUSE_ContOnErrorFlag,		NULL	},
	{	ADF_TRUE,	ADF_OUSE_OutputDir,				NULL	},
	{	ADF_TRUE,	ADF_OUSE_OutputType,				NULL	},
	{	ADF_TRUE,	ADF_OUSE_OutputByFileFlag,		NULL	},
	{	ADF_TRUE,	ADF_OUSE_OutputToStdoutFlag,	NULL	},
	{	ADF_TRUE,	ADF_OUSE_GenerateType,			NULL	},
	{	ADF_TRUE,	ADF_BUSE_CludeEntry,				NULL	},
	{	ADF_TRUE,	ADF_BUSE_CludeHText,				NULL	},
	{	ADF_TRUE,	ADF_OUSE_AreaNameType,			NULL	},
	{	ADF_TRUE,	ADF_OUSE_AreaOrderType,			NULL	},
	{	ADF_TRUE,	ADF_OUSE_AreaName,				NULL	},
	{	ADF_TRUE,	ADF_BUSE_IgnoreSection,			NULL	},
	{	ADF_TRUE,	ADF_OUSE_KeepBadSeeAlso,		NULL	},
	{	ADF_TRUE,	ADF_OUSE_ExternalHTextRef,		NULL	},
	{	ADF_TRUE,	ADF_OUSE_ParseOutParam,			NULL	}
};
static const unsigned int  ADF_RUN_OUT_UsageFuncCount  =
	sizeof(ADF_RUN_OUT_UsageFuncList) / sizeof(ADF_RUN_OUT_UsageFuncList[0]);
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
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_DoByEntry,
	(ADF_CONTROL *control_ptr,	char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_DoToStdout,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_DoByFile,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_DoTOC,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_DoClassTOC,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_DoTOF,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_DoIndex,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_DoPermIndex,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_GetParams,
	(ADF_CONTROL *control_ptr, unsigned int argc, char **argv,
	char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_CreateUsageList,
	(ADF_CONTROL *control_ptr, unsigned int *usage_count, char ***usage_list,
	char *error_text));
COMPAT_FN_DECL_STATIC(void ADF_RUN_OUT_ShowSettings,
	(const ADF_CONTROL *control_ptr));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_CheckParams,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_OUT_Parse,
	(ADF_CONTROL *control_ptr, unsigned int argc, char **argv, int init_flag,
	unsigned int current_arg, char *error_text));
COMPAT_FN_DECL_STATIC(void ADF_RUN_OUT_End,
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

	if ((return_code = ADF_RUN_OUT_GetParams(&control_data,
		((unsigned int) argc), argv, error_text)) == ADF_SUCCESS) {
		if ((return_code = ADF_LoadInFileList(&control_data, error_text)) ==
			ADF_SUCCESS) {
			if ((return_code = ADF_LoadHTextRefFileList(&control_data,
				error_text)) == ADF_SUCCESS) {
				if (control_data.check_only_flag != ADF_TRUE) {
					if ((return_code = ADF_FinalizeEntries(&control_data,
						error_text)) == ADF_SUCCESS) {
						if (control_data.generate_type == ADF_GENERATE_TYPE_TOC)
							return_code = ADF_RUN_OUT_DoTOC(&control_data,
								error_text);
						else if (control_data.generate_type ==
							ADF_GENERATE_TYPE_CLASS_TOC)
							return_code = ADF_RUN_OUT_DoClassTOC(&control_data,
								error_text);
						else if (control_data.generate_type ==
							ADF_GENERATE_TYPE_TOF)
							return_code = ADF_RUN_OUT_DoTOF(&control_data,
								error_text);
						else if (control_data.generate_type ==
							ADF_GENERATE_TYPE_INDEX)
							return_code = ADF_RUN_OUT_DoIndex(&control_data,
								error_text);
						else if (control_data.generate_type ==
							ADF_GENERATE_TYPE_PERM_INDEX)
							return_code = ADF_RUN_OUT_DoPermIndex(&control_data,
								error_text);
						else if (control_data.output_by_file_flag == ADF_TRUE)
							return_code = ADF_RUN_OUT_DoByFile(&control_data,
								error_text);
						else if (control_data.output_to_stdout_flag == ADF_TRUE)
							return_code = ADF_RUN_OUT_DoToStdout(&control_data,
								error_text);
						else
							return_code = ADF_RUN_OUT_DoByEntry(&control_data,
								error_text);
					}
				}
			}
		}
		if ((return_code != ADF_SUCCESS) &&
			(control_data.log_flag == ADF_TRUE))
			MLOG_LogErr(control_data.mlog_ptr, "%s\n", error_text);
		ADF_RUN_OUT_End(&control_data, 0, NULL, NULL);
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
static int ADF_RUN_OUT_DoByEntry(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_OUT_DoByEntry(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	char          output_type_string[ADF_OUTPUT_TYPE_NAME_LENGTH + 1];
#ifndef NARGS
	int          (*init_function)(ADF_CONTROL *, char *);
	int          (*by_entry_function)(ADF_CONTROL *, const ADF_ENTRY *, char *);
#else
	int          (*init_function)();
	int          (*by_entry_function)();
#endif /* #ifndef NARGS */

	if ((return_code = ADF_GetOutputFunctions(control_ptr->output_type,
		&init_function, &by_entry_function, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	else if (by_entry_function == NULL) {
		sprintf(error_text, "The %s output type may not be emitted 'by-entry'.",
			ADF_GetOutputTypeString(control_ptr->output_type,
			output_type_string));
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((init_function != NULL) &&
		((return_code = (*init_function)(control_ptr, error_text)) !=
		ADF_SUCCESS))
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < control_ptr->in_entry_order_count; count_1++) {
		if ((return_code = (*by_entry_function)(control_ptr,
			control_ptr->in_entry_order_list[count_1], error_text)) !=
			ADF_SUCCESS)
			break;
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_OUT_DoToStdout(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_OUT_DoToStdout(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	unsigned int   count_1;
	time_t         output_date;
	char           output_type_string[ADF_OUTPUT_TYPE_NAME_LENGTH + 1];
#ifndef NARGS
	int          (*init_function)(ADF_CONTROL *, char *);
	int          (*to_stdout_function)(ADF_CONTROL *, const ADF_ENTRY *,
						const time_t *, char *);
	void         (*output_start_function)(ADF_CONTROL *contrl_ptr,
		const char *output_name, const time_t *output_date_ptr,
		STR_FUNC_TYPE_fprintf output_function, void *output_control);
	void         (*output_end_function)(ADF_CONTROL *contrl_ptr,
		STR_FUNC_TYPE_fprintf output_function, void *output_control);
	void         (*output_between_function)(ADF_CONTROL *contrl_ptr,
		const ADF_ENTRY *entry_ptr, const char *output_name,
		STR_FUNC_TYPE_fprintf output_function, void *output_control);
#else
	int          (*init_function)();
	int          (*to_stdout_function)();
	void         (*output_start_function);
	void         (*output_end_function);
	void         (*output_between_function);
#endif /* #ifndef NARGS */

	if ((return_code = ADF_GetOutputFunctions(control_ptr->output_type,
		&init_function, NULL, &to_stdout_function, NULL, NULL, NULL, NULL, NULL,
		NULL, &output_start_function, &output_end_function,
		&output_between_function, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	else if (to_stdout_function == NULL) {
		sprintf(error_text,
			"The %s output type may not be emitted to <stdout>.",
			ADF_GetOutputTypeString(control_ptr->output_type,
			output_type_string));
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((init_function != NULL) &&
		((return_code = (*init_function)(control_ptr, error_text)) !=
		ADF_SUCCESS))
		goto EXIT_FUNCTION;

	output_date = time(NULL);

	if (output_start_function != NULL)
		(*output_start_function)(control_ptr, "Output to <stdout>",
			&output_date, STR_FUNC_TYPE_fprintf_CAST(fprintf), stdout);

	for (count_1 = 0; count_1 < control_ptr->in_entry_order_count; count_1++) {
		if (count_1 && (output_between_function != NULL))
			(*output_between_function)(control_ptr,
				control_ptr->in_entry_order_list[count_1], "Output to <stdout>",
				STR_FUNC_TYPE_fprintf_CAST(fprintf), stdout);
		if ((return_code = (*to_stdout_function)(control_ptr,
			control_ptr->in_entry_order_list[count_1], &output_date,
			error_text)) != ADF_SUCCESS)
			break;
	}

	if (output_end_function != NULL)
		(*output_end_function)(control_ptr, STR_FUNC_TYPE_fprintf_CAST(fprintf),
			stdout);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_OUT_DoByFile(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_OUT_DoByFile(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	char          output_type_string[ADF_OUTPUT_TYPE_NAME_LENGTH + 1];
#ifndef NARGS
	int          (*init_function)(ADF_CONTROL *, char *);
	int          (*by_file_function)(ADF_CONTROL *, unsigned int *, char *);
#else
	int          (*init_function)();
	int          (*by_file_function)();
#endif /* #ifndef NARGS */

	if ((return_code = ADF_GetOutputFunctions(control_ptr->output_type,
		&init_function, NULL, NULL, &by_file_function, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	else if (by_file_function == NULL) {
		sprintf(error_text, "The %s output type may not be emitted 'by-file'.",
			ADF_GetOutputTypeString(control_ptr->output_type,
			output_type_string));
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((init_function != NULL) &&
		((return_code = (*init_function)(control_ptr, error_text)) !=
		ADF_SUCCESS))
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < control_ptr->in_entry_order_count; ) {
		if ((return_code = (*by_file_function)(control_ptr, &count_1,
			error_text)) != ADF_SUCCESS)
			break;
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_OUT_DoTOC(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_OUT_DoTOC(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code = ADF_SUCCESS;
	char   output_type_string[ADF_OUTPUT_TYPE_NAME_LENGTH + 1];
#ifndef NARGS
	int  (*init_function)(ADF_CONTROL *, char *);
	int  (*toc_function)(ADF_CONTROL *, char *);
#else
	int  (*init_function)();
	int  (*toc_function)();
#endif /* #ifndef NARGS */

	if ((return_code = ADF_GetOutputFunctions(control_ptr->output_type,
		&init_function, NULL, NULL, NULL, &toc_function, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, error_text)) == ADF_SUCCESS) {
		if (toc_function == NULL) {
			sprintf(error_text, "The %s output type does not support %s.",
				ADF_GetOutputTypeString(control_ptr->output_type,
				output_type_string), "table-of-contents generation");
			return_code = ADF_FAILURE;
		}
		else if ((init_function == NULL) || ((init_function != NULL) &&
			((return_code = (*init_function)(control_ptr, error_text)) ==
			ADF_SUCCESS)))
			return_code = (*toc_function)(control_ptr, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_OUT_DoClassTOC(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_OUT_DoClassTOC(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code = ADF_SUCCESS;
	char   output_type_string[ADF_OUTPUT_TYPE_NAME_LENGTH + 1];
#ifndef NARGS
	int  (*init_function)(ADF_CONTROL *, char *);
	int  (*class_toc_function)(ADF_CONTROL *, char *);
#else
	int  (*init_function)();
	int  (*class_toc_function)();
#endif /* #ifndef NARGS */

	if ((return_code = ADF_GetOutputFunctions(control_ptr->output_type,
		&init_function, NULL, NULL, NULL, NULL, &class_toc_function, NULL,
		NULL, NULL, NULL, NULL, NULL, error_text)) == ADF_SUCCESS) {
		if (class_toc_function == NULL) {
			sprintf(error_text, "The %s output type does not support %s.",
				ADF_GetOutputTypeString(control_ptr->output_type,
				output_type_string), "entry class table-of-contents generation");
			return_code = ADF_FAILURE;
		}
		else if ((init_function == NULL) || ((init_function != NULL) &&
			((return_code = (*init_function)(control_ptr, error_text)) ==
			ADF_SUCCESS)))
			return_code = (*class_toc_function)(control_ptr, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_OUT_DoTOF(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_OUT_DoTOF(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code = ADF_SUCCESS;
	char   output_type_string[ADF_OUTPUT_TYPE_NAME_LENGTH + 1];
#ifndef NARGS
	int  (*init_function)(ADF_CONTROL *, char *);
	int  (*tof_function)(ADF_CONTROL *, char *);
#else
	int  (*init_function)();
	int  (*tof_function)();
#endif /* #ifndef NARGS */

	if ((return_code = ADF_GetOutputFunctions(control_ptr->output_type,
		&init_function, NULL, NULL, NULL, NULL, NULL, &tof_function, NULL, NULL,
		NULL, NULL, NULL, error_text)) == ADF_SUCCESS) {
		if (tof_function == NULL) {
			sprintf(error_text, "The %s output type does not support %s.",
				ADF_GetOutputTypeString(control_ptr->output_type,
				output_type_string), "table-of-files generation");
			return_code = ADF_FAILURE;
		}
		else if ((init_function == NULL) || ((init_function != NULL) &&
			((return_code = (*init_function)(control_ptr, error_text)) ==
			ADF_SUCCESS)))
			return_code = (*tof_function)(control_ptr, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_OUT_DoIndex(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_OUT_DoIndex(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code = ADF_SUCCESS;
	char   output_type_string[ADF_OUTPUT_TYPE_NAME_LENGTH + 1];
#ifndef NARGS
	int  (*init_function)(ADF_CONTROL *, char *);
	int  (*index_function)(ADF_CONTROL *, char *);
#else
	int  (*init_function)();
	int  (*index_function)();
#endif /* #ifndef NARGS */

	if ((return_code = ADF_GetOutputFunctions(control_ptr->output_type,
		&init_function, NULL, NULL, NULL, NULL, NULL, NULL, &index_function,
		NULL, NULL, NULL, NULL, error_text)) == ADF_SUCCESS) {
		if (index_function == NULL) {
			sprintf(error_text, "The %s output type does not support %s.",
				ADF_GetOutputTypeString(control_ptr->output_type,
				output_type_string), "index generation");
			return_code = ADF_FAILURE;
		}
		else if ((init_function == NULL) || ((init_function != NULL) &&
			((return_code = (*init_function)(control_ptr, error_text)) ==
			ADF_SUCCESS)))
			return_code = (*index_function)(control_ptr, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_OUT_DoPermIndex(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_OUT_DoPermIndex(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code = ADF_SUCCESS;
	char   output_type_string[ADF_OUTPUT_TYPE_NAME_LENGTH + 1];
#ifndef NARGS
	int  (*init_function)(ADF_CONTROL *, char *);
	int  (*perm_index_function)(ADF_CONTROL *, char *);
#else
	int  (*init_function)();
	int  (*perm_index_function)();
#endif /* #ifndef NARGS */

	if ((return_code = ADF_GetOutputFunctions(control_ptr->output_type,
		&init_function, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		&perm_index_function, NULL, NULL, NULL, error_text)) == ADF_SUCCESS) {
		if (perm_index_function == NULL) {
			sprintf(error_text, "The %s output type does not support %s.",
				ADF_GetOutputTypeString(control_ptr->output_type,
				output_type_string), "permutated index generation");
			return_code = ADF_FAILURE;
		}
		else if ((init_function == NULL) || ((init_function != NULL) &&
			((return_code = (*init_function)(control_ptr, error_text)) ==
			ADF_SUCCESS)))
			return_code = (*perm_index_function)(control_ptr, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_OUT_GetParams(ADF_CONTROL *control_ptr, unsigned int argc,
	char **argv, char *error_text)
#else
static int ADF_RUN_OUT_GetParams(control_ptr, argc, argv, error_text)
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
		ADF_RUN_OUT_End, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = ADF_RUN_OUT_CreateUsageList(control_ptr,
		&usage_count, &usage_list, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

#ifndef NARGS
	if ((return_code = ADF_GetParams(control_ptr,
		((unsigned int) argc), argv, &control_ptr->help_flag,
		&control_ptr->version_flag,
		((int (*)(void *, unsigned int, char **, int, unsigned int, char *))
		ADF_RUN_OUT_Parse), error_text)) == ADF_SUCCESS) {
#else
	else if ((return_code = ADF_GetParams(control_ptr,
		((unsigned int) argc), argv, &control_ptr->help_flag,
		&control_ptr->version_flag, ADF_RUN_OUT_Parse, error_text)) ==
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
				ADF_RUN_OUT_VERSION_NUMBER);
			exit(0);
		}
		else if ((return_code = ADF_RUN_OUT_CheckParams(control_ptr,
			error_text)) == ADF_SUCCESS) {
			if (control_ptr->log_flag == ADF_TRUE) {
				if (control_ptr->quiet_flag == ADF_TRUE)
					MLOG_SetFlagFile(control_ptr->mlog_ptr, 0, NULL);
				if ((return_code = ADF_RUN_OpenLogFile(control_ptr,
					error_text)) == ADF_SUCCESS)
					ADF_RUN_OUT_ShowSettings(control_ptr);
			}
		}
		if (return_code != ADF_SUCCESS)
			ADF_RUN_OUT_End(control_ptr, 0, NULL, NULL);
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
static int ADF_RUN_OUT_CreateUsageList(ADF_CONTROL *control_ptr,
	unsigned int *usage_count, char ***usage_list, char *error_text)
#else
static int ADF_RUN_OUT_CreateUsageList(control_ptr, usage_count, usage_list,
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

	sprintf(buffer, "\tThis is version %s of %s.", ADF_RUN_OUT_VERSION_NUMBER,
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

	for (count_1 = 0; count_1 < ADF_RUN_OUT_UsageFuncCount; count_1++) {
		if (((return_code =
			(*ADF_RUN_OUT_UsageFuncList[count_1].usage_function)(NULL,
			ADF_RUN_OUT_UsageFuncList[count_1].optional_flag, NULL, usage_count,
			usage_list, error_text)) != ADF_SUCCESS) ||
			((ADF_RUN_OUT_UsageFuncList[count_1].added_text != NULL) &&
			((return_code = ADF_BUSE_AppendLine(
			ADF_RUN_OUT_UsageFuncList[count_1].added_text, usage_count,
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
static void ADF_RUN_OUT_ShowSettings(const ADF_CONTROL *control_ptr)
#else
static void ADF_RUN_OUT_ShowSettings(control_ptr)
const ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	MLOG_DoSepStart(control_ptr->mlog_ptr);

	MLOG_LogInfo(control_ptr->mlog_ptr, "Program Name       : %s\n",
		control_ptr->program_name);
	MLOG_LogInfo(control_ptr->mlog_ptr, "Version Number     : %s\n",
		ADF_RUN_OUT_VERSION_NUMBER);
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
static int ADF_RUN_OUT_CheckParams(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_OUT_CheckParams(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_BAD_ARGS_FAILURE;

	if ((control_ptr->output_by_file_flag == ADF_TRUE) &&
		(control_ptr->output_to_stdout_flag == ADF_TRUE))
		sprintf(error_text,
			"Parameter conflict detected --- both the %s and the %s are 'TRUE'.",
			"'-OUTPUT_BY_FILE=' parameter", "'-OUTPUT_TO_STDOUT=' parameter");
	else if (!control_ptr->in_file_name_count)
		strcpy(error_text,
			"No ADF database files were specified on the command line.");
	else
		return_code = ADF_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_OUT_Parse(ADF_CONTROL *control_ptr, unsigned int argc,
	char **argv, int init_flag, unsigned int current_arg, char *error_text)
#else
static int ADF_RUN_OUT_Parse(control_ptr, argc, argv, init_flag, current_arg,
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
	char         *tmp_string;

	if (init_flag != ADF_TRUE) {
		this_arg = argv[current_arg];
		if (ADF_BARG_CheckOnlyFlag(this_arg, &arg_length, &data_ptr,
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
		else if (ADF_OARG_HyperTextFlag(this_arg, &arg_length, &data_ptr,
			&control_ptr->hyper_text_flag, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_OARG_OutputDir(this_arg, &arg_length, &data_ptr,
			&control_ptr->output_dir, &control_ptr->output_dir_basic,
			&return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_OARG_OutputType(this_arg, &arg_length, &data_ptr,
			&control_ptr->output_type, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_OARG_OutputByFileFlag(this_arg, &arg_length, &data_ptr,
			&control_ptr->output_by_file_flag, &return_code, error_text) ==
			ADF_TRUE)
			;
		else if (ADF_OARG_OutputToStdoutFlag(this_arg, &arg_length, &data_ptr,
			&control_ptr->output_to_stdout_flag, &return_code, error_text) ==
			ADF_TRUE)
			;
		else if (ADF_OARG_GenerateType(this_arg, &arg_length, &data_ptr,
			&control_ptr->generate_type, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_BARG_CludeEntry(this_arg, &arg_length, &data_ptr,
			control_ptr, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_BARG_CludeHText(this_arg, &arg_length, &data_ptr,
			control_ptr, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_OARG_AreaNameType(this_arg, &arg_length, &data_ptr,
			&control_ptr->area_name_type, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_OARG_AreaOrderType(this_arg, &arg_length, &data_ptr,
			&control_ptr->area_order_type, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_OARG_AreaName(this_arg, &arg_length, &data_ptr,
			control_ptr->area_name_list, &return_code, error_text) == ADF_TRUE)
			;
		else if (ADF_BARG_IgnoreSection(this_arg, &arg_length, &data_ptr,
			control_ptr->ignore_section_list, &return_code, error_text) ==
			ADF_TRUE)
			;
		else if (ADF_OARG_KeepBadSeeAlso(this_arg, &arg_length, &data_ptr,
			&control_ptr->keep_bad_see_also_flag, &return_code, error_text) ==
			ADF_TRUE)
			;
		else if (ADF_OARG_ExternalHTextRef(this_arg, &arg_length, &data_ptr,
			&tmp_string, &return_code, error_text) == ADF_TRUE) {
			if (return_code == ADF_SUCCESS) {
				if (strl_append(&control_ptr->htext_ref_file_name_count,
					&control_ptr->htext_ref_file_name_list, tmp_string) !=
					STRFUNCS_SUCCESS) {
					STR_AllocMsgItem(strlen(tmp_string) + 1, error_text,
						"Unable to copy the external reference string '%-.500s'",
						tmp_string);
					return_code = ADF_MEMORY_FAILURE;
				}
				free(tmp_string);
			}
		}
		else if (ADF_OARG_ParseOutParam(this_arg, &arg_length, &data_ptr,
			control_ptr, &return_code, error_text) == ADF_TRUE)
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
static void ADF_RUN_OUT_End(ADF_CONTROL *control_ptr, int signal_number,
	int *exit_code_ptr, const char *message_buffer)
#else
static void ADF_RUN_OUT_End(control_ptr, signal_number, exit_code_ptr,
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

