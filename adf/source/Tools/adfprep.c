/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Run-time logic for the executable 'adfprep'.

	Revision History	:	1995-07-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <errno.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "adfrun.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define ADF_RUN_PREP_VERSION_NUMBER		"01.00.00A"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
static const ADF_RUN_USAGE ADF_RUN_PREP_UsageFuncList[] = {
	{	ADF_TRUE,	ADF_BUSE_Help,						NULL	},
	{	ADF_TRUE,	ADF_BUSE_Version,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_CheckOnlyFlag,			NULL	},
	{	ADF_TRUE,	ADF_PUSE_ADFDefFile,				NULL	},
	{	ADF_FALSE,	ADF_PUSE_PrepADFFile,			NULL	},
	{	ADF_TRUE,	ADF_PUSE_PrepADFFileMode,		NULL	},
	{	ADF_TRUE,	ADF_BUSE_LogFlag,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_LogDir,					NULL	},
	{	ADF_TRUE,	ADF_BUSE_DuplicateType,			NULL	},
	{	ADF_TRUE,	ADF_BUSE_QuietFlag,				NULL	},
	{	ADF_TRUE,	ADF_BUSE_ContOnErrorFlag,		NULL	},
	{	ADF_TRUE,	ADF_PUSE_IgnoreBadCmntFlag,	NULL	},
	{	ADF_TRUE,	ADF_BUSE_SortOrderType,			NULL	},
	{	ADF_TRUE,	ADF_BUSE_CludeEntry,				NULL	},
	{	ADF_TRUE,	ADF_BUSE_CludeHText,				NULL	},
	{	ADF_TRUE,	ADF_BUSE_IgnoreSection,			NULL	}
};
static const unsigned int  ADF_RUN_PREP_UsageFuncCount  =
	sizeof(ADF_RUN_PREP_UsageFuncList) / sizeof(ADF_RUN_PREP_UsageFuncList[0]);
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
COMPAT_FN_DECL_STATIC(int  ADF_RUN_PREP_ProcessSources,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_PREP_DoEither,
	(ADF_CONTROL *control_ptr, unsigned int domain_count,
	const ADF_DOMAIN *domain_list, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_PREP_DoCreate,
	(ADF_CONTROL *control_ptr, unsigned int domain_count,
	const ADF_DOMAIN *domain_list, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_PREP_DoUpdate,
	(ADF_CONTROL *control_ptr, unsigned int domain_count,
	const ADF_DOMAIN *domain_list, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_PREP_GetParams,
	(ADF_CONTROL *control_ptr, unsigned int argc, char **argv,
	char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_PREP_CreateUsageList,
	(ADF_CONTROL *control_ptr, unsigned int *usage_count, char ***usage_list,
	char *error_text));
COMPAT_FN_DECL_STATIC(void ADF_RUN_PREP_ShowSettings,
	(const ADF_CONTROL *control_ptr));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_PREP_CheckParams,
	(ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_RUN_PREP_Parse,
	(ADF_CONTROL *control_ptr, unsigned int argc, char **argv, int init_flag,
	unsigned int current_arg, char *error_text));
COMPAT_FN_DECL_STATIC(void ADF_RUN_PREP_End,
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

	if ((return_code = ADF_RUN_PREP_GetParams(&control_data,
		((unsigned int) argc), argv, error_text)) == ADF_SUCCESS) {
		if (!control_data.in_file_name_count) {
			strcpy(error_text,
				"No source files were specified on the command line.");
				return_code = ADF_BAD_ARGS_FAILURE;
		}
		else
			return_code = ADF_RUN_PREP_ProcessSources(&control_data,
				error_text);
		if ((return_code != ADF_SUCCESS) &&
			(control_data.log_flag == ADF_TRUE))
			MLOG_LogErr(control_data.mlog_ptr, "%s\n", error_text);
		ADF_RUN_PREP_End(&control_data, 0, NULL, NULL);
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
static int ADF_RUN_PREP_ProcessSources(ADF_CONTROL *control_ptr,
	char *error_text)
#else
static int ADF_RUN_PREP_ProcessSources(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  domain_count;
	ADF_DOMAIN   *domain_list;

	if (!control_ptr->domain_count) {
		ADF_GetDefaultDefSpec(&domain_count, &domain_list);
		if (control_ptr->log_flag == ADF_TRUE)
			MLOG_LogInfo(control_ptr->mlog_ptr,
				"Initialized program with internal ADF definition.\n");
		else if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr,
				"Initialized program with internal ADF definition.\n");
	}
	else {
		domain_count = control_ptr->domain_count;
		domain_list  = control_ptr->domain_list;
	}

	if (control_ptr->prep_adf_file_mode == ADF_PREP_FILE_MODE_CREATE)
		return_code = ADF_RUN_PREP_DoCreate(control_ptr, domain_count,
			domain_list, error_text);
	else if (control_ptr->prep_adf_file_mode == ADF_PREP_FILE_MODE_UPDATE)
		return_code = ADF_RUN_PREP_DoUpdate(control_ptr, domain_count,
			domain_list, error_text);
	else
		return_code = ADF_RUN_PREP_DoEither(control_ptr, domain_count,
			domain_list, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_PREP_DoEither(ADF_CONTROL *control_ptr,
	unsigned int domain_count, const ADF_DOMAIN *domain_list, char *error_text)
#else
static int ADF_RUN_PREP_DoEither(control_ptr, domain_count, domain_list,
	error_text)
ADF_CONTROL      *control_ptr;
unsigned int      domain_count;
const ADF_DOMAIN *domain_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code    = ADF_SUCCESS;
	struct stat stat_data;

	if (stat(control_ptr->prep_adf_file_name, &stat_data)) {
		if (errno == ENOENT) {
			control_ptr->prep_adf_file_mode = ADF_PREP_FILE_MODE_CREATE;
			return_code = ADF_RUN_PREP_DoCreate(control_ptr, domain_count,
				domain_list, error_text);
		}
		else {
			sprintf(error_text,
				"Unable to 'stat()' ADF database file '%-.500s': ",
				control_ptr->prep_adf_file_name);
			ADF_GetLastErrorString(error_text);
			return_code = ADF_SYSTEM_FAILURE;
		}
	}
	else {
		control_ptr->prep_adf_file_mode = ADF_PREP_FILE_MODE_UPDATE;
		return_code = ADF_RUN_PREP_DoUpdate(control_ptr, domain_count,
			domain_list, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_PREP_DoCreate(ADF_CONTROL *control_ptr,
	unsigned int domain_count, const ADF_DOMAIN *domain_list, char *error_text)
#else
static int ADF_RUN_PREP_DoCreate(control_ptr, domain_count, domain_list,
	error_text)
ADF_CONTROL      *control_ptr;
unsigned int      domain_count;
const ADF_DOMAIN *domain_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	int          tmp_return_code;
	unsigned int count_1;
	char         tmp_error_text[ADF_MAX_ERROR_TEXT];

	if ((control_ptr->check_only_flag != ADF_TRUE) && ((return_code =
		ADF_OpenADFFilePrep(control_ptr, control_ptr->prep_adf_file_name,
		error_text)) != ADF_SUCCESS))
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < control_ptr->in_file_name_count; count_1++) {
		if ((return_code = ADF_DoSource(control_ptr, domain_count, domain_list,
			control_ptr->in_file_name_list[count_1], error_text)) !=
			ADF_SUCCESS) {
			if ((return_code != ADF_PARSE_FAILURE) ||
				((return_code == ADF_PARSE_FAILURE) &&
				(control_ptr->ignore_bad_cmnt_flag != ADF_TRUE) &&
				(control_ptr->cont_on_error_flag != ADF_TRUE)))
				break;
			return_code = ADF_SUCCESS;
		}
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now write the directories at the end of the ADF database file.	*/
	/*	*****************************************************************	*/
	if ((control_ptr->check_only_flag != ADF_TRUE) &&
		((tmp_return_code = ADF_WriteTrailer(control_ptr,
		control_ptr->prep_entry_count, control_ptr->prep_entry_list,
		control_ptr->prep_htext_count, control_ptr->prep_htext_list,
		tmp_error_text)) != ADF_SUCCESS) && (return_code == ADF_SUCCESS)) {
		strcpy(error_text, tmp_error_text);
		return_code = tmp_return_code;
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_PREP_DoUpdate(ADF_CONTROL *control_ptr,
	unsigned int domain_count, const ADF_DOMAIN *domain_list, char *error_text)
#else
static int ADF_RUN_PREP_DoUpdate(control_ptr, domain_count, domain_list,
	error_text)
ADF_CONTROL      *control_ptr;
unsigned int      domain_count;
const ADF_DOMAIN *domain_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int               return_code        = ADF_SUCCESS;
	char             *tmp_path_name      = NULL;
	unsigned int      publish_xref_count = 0;
	char            **publish_xref_list  = NULL;
	unsigned int      count_1;
	unsigned int      count_2;
	char             *tmp_ptr;
	ADF_ENTRY        *entry_ptr;
	struct stat       stat_data;
	ADF_SOURCE_DATA   area_list[ADF_AREA_COUNT];
	ADF_FILE_HEADER   tmp_header;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Check accessibility of the original ADF database file . . .		*/
	/*	*****************************************************************	*/
	if (stat(control_ptr->prep_adf_file_name, &stat_data)) {
		sprintf(error_text, "Unable to 'stat()' ADF database file '%-.500s': ",
			control_ptr->prep_adf_file_name);
		ADF_GetLastErrorString(error_text);
		return_code = ADF_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (!(stat_data.st_mode & S_IFREG)) {
		sprintf(error_text,
			"Specified ADF database file '%-.500s' is not a regular file.",
			control_ptr->prep_adf_file_name);
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (!(stat_data.st_mode & S_IREAD)) {
		sprintf(error_text,
			"Specified ADF database file '%-.500s' is not readable.",
			control_ptr->prep_adf_file_name);
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (!(stat_data.st_mode & S_IWRITE)) {
		sprintf(error_text,
			"Specified ADF database file '%-.500s' is not readable.",
			control_ptr->prep_adf_file_name);
		return_code = ADF_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Construct a copy of the ADF database file path to be used in	*/
	/*	creating a temporary ADF database file . . .								*/
	/*	*****************************************************************	*/
	if ((tmp_path_name = strdup(control_ptr->prep_adf_file_name)) == NULL) {
		STR_AllocMsgItem(strlen(control_ptr->prep_adf_file_name) + 1,
			error_text, "Unable to copy the ADF database file name");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	tmp_ptr = tmp_path_name + (strlen(tmp_path_name) - 1);
#ifdef __MSDOS__
	while (tmp_ptr >= tmp_path_name) {
		if ((*tmp_ptr == '\\') || (*tmp_ptr == '/') || (*tmp_ptr == ':')) {
			*(tmp_ptr + 1) = '\0';
			break;
		}
		tmp_ptr--;
	}
#elif _VMS_
	while (tmp_ptr >= tmp_path_name) {
		if (*tmp_ptr == ']') {
			*(tmp_ptr + 1) = '\0';
			break;
		}
		tmp_ptr--;
	}
#else
	while (tmp_ptr >= tmp_path_name) {
		if (*tmp_ptr == '/') {
			*(tmp_ptr + 1) = '\0';
			break;
		}
		tmp_ptr--;
	}
#endif /* #ifdef __MSDOS__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now create a temporary ADF database file name . . .				*/
	/*	*****************************************************************	*/
	if ((control_ptr->prep_tmp_file_name = tempnam(tmp_path_name, "ADF")) ==
		NULL) {
		strcpy(error_text,
			"Unable to construct a temporary ADF database file name.");
		ADF_GetLastErrorString(error_text);
		return_code = ADF_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Open the original ADF database file and read its directories.	*/
	/*	*****************************************************************	*/
	if ((return_code = ADF_OpenADFFileIn(control_ptr,
		control_ptr->prep_adf_file_name, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Open the temporary ADF database file for output . . .				*/
	/*	*****************************************************************	*/
	if ((control_ptr->check_only_flag != ADF_TRUE) && ((return_code =
		ADF_OpenADFFilePrep(control_ptr, control_ptr->prep_tmp_file_name,
		error_text)) != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Allocate memory for the hyper-text list which we loaded from	*/
	/*	the original ADF database file . . .										*/
	/*	*****************************************************************	*/
	if (control_ptr->in_entry_count && ((publish_xref_list =
		((char **) malloc(control_ptr->in_entry_count * sizeof(char *)))) ==
		NULL)) {
		STR_AllocMsgList(control_ptr->in_entry_count, sizeof(char *),
			error_text, "Unable to construct a temporary hyper-text list");
		return_code = ADF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Process all of the source files on the command-line . . .		*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < control_ptr->in_file_name_count; count_1++) {
		if ((return_code = ADF_DoSource(control_ptr, domain_count, domain_list,
			control_ptr->in_file_name_list[count_1], error_text)) !=
			ADF_SUCCESS) {
			if ((return_code != ADF_PARSE_FAILURE) ||
				((return_code == ADF_PARSE_FAILURE) &&
				(control_ptr->ignore_bad_cmnt_flag != ADF_TRUE) &&
				(control_ptr->cont_on_error_flag != ADF_TRUE)))
				break;
			return_code = ADF_SUCCESS;
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If '-CHECK_ONLY=' is 'ON', then we're done . . .					*/
	/*	*****************************************************************	*/
	if (control_ptr->check_only_flag == ADF_TRUE)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If we haven't added any entries to the temporary ADF database	*/
	/*	file, then we're done . . .													*/
	/*	*****************************************************************	*/
	if (!control_ptr->prep_entry_count)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Write any remaining entries in the original ADF database file	*/
	/*	to the temporary ADF database file . . .									*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < control_ptr->in_entry_count; count_1++) {
		entry_ptr          = control_ptr->in_entry_list + count_1;
		publish_xref_count = 0;
		for (count_2 = 0; count_2 < control_ptr->in_htext_count; count_2++) {
			if ((control_ptr->in_htext_list[count_2].file_index ==
				entry_ptr->file_index) &&
				(control_ptr->in_htext_list[count_2].entry_index ==
				entry_ptr->entry_index))
				publish_xref_list[publish_xref_count++] =
					control_ptr->in_htext_list[count_2].hyper_text;
		}
		if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr, "COPY:%s(%s)\n", entry_ptr->base_name,
				entry_ptr->file_name);
		if ((return_code = ADF_ReadEntry(control_ptr, entry_ptr, NULL,
			area_list, error_text)) != ADF_SUCCESS)
			break;
		if ((return_code = ADF_AddToPrepList(control_ptr, entry_ptr->base_name,
			entry_ptr->file_name, entry_ptr->core_name, entry_ptr->full_name,
			entry_ptr->file_type, entry_ptr->man_page, &entry_ptr->file_date,
			&entry_ptr->prep_date, NULL, area_list, publish_xref_count,
			publish_xref_list, error_text)) != ADF_SUCCESS)
			break;
		else if (control_ptr->log_flag == ADF_TRUE)
			MLOG_LogInfo(control_ptr->mlog_ptr,
				"%s: %s '%s' in ADF database file '%s'.\n",
				area_list[ADF_AREA_SOURCE_FILE_FULL_NAME].line_data,
				"Copied ADF comment for base name", entry_ptr->base_name,
				control_ptr->prep_adf_file_name);
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now write the directories at the end of the ADF database file.	*/
	/*	*****************************************************************	*/
	if ((return_code = ADF_WriteTrailer(control_ptr,
		control_ptr->prep_entry_count, control_ptr->prep_entry_list,
		control_ptr->prep_htext_count, control_ptr->prep_htext_list,
		error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Set the creation date in the temporary ADF database file			*/
	/*	header equal to the creation date in the original ADF database		*/
	/*	file . . .																			*/
	/*	*****************************************************************	*/
	ADF_fseek(control_ptr->prep_adf_file, ((unsigned long) ADF_FILE_PAGE_SIZE),
		SEEK_SET);
	if ((return_code = ADF_FRead(&tmp_header, sizeof(tmp_header), 1,
		control_ptr->prep_adf_file, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	tmp_header.creation_date = control_ptr->in_file_list->header.creation_date;
	ADF_fseek(control_ptr->prep_adf_file, ((unsigned long) ADF_FILE_PAGE_SIZE),
		SEEK_SET);
	if ((return_code = ADF_FWrite(&tmp_header, sizeof(tmp_header), 1,
		control_ptr->prep_adf_file, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	ADF_fflush(control_ptr->prep_adf_file);
	if ((return_code = ADF_WriteADFHumanHeader(control_ptr->prep_adf_file,
		&tmp_header, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Do the final work here:														*/
	/*																							*/
	/*		1) Close the original ADF database file.								*/
	/*																							*/
	/*		2) Close the temporary ADF database file.								*/
	/*																							*/
	/*		3) Unlink the original ADF database file.								*/
	/*																							*/
	/*		4) Rename the temporary ADF database file to the original		*/
	/*			ADF database file.														*/
	/*	*****************************************************************	*/
	ADF_FreeInFileList(control_ptr);
	ADF_CloseADFFilePrep(control_ptr);
	if (unlink(control_ptr->prep_adf_file_name)) {
		sprintf(error_text, "Unable to 'unlink()' old ADF database file '%s': ",
			control_ptr->prep_adf_file_name);
		ADF_GetLastErrorString(error_text);
		return_code = ADF_SYSTEM_FAILURE;
	}
	else if (rename(control_ptr->prep_tmp_file_name,
		control_ptr->prep_adf_file_name)) {
		sprintf(error_text, "Unable to 'rename()' %s '%-.300s' %s '%-.300s': ",
			"temporary ADF database file", control_ptr->prep_tmp_file_name,
			"to the old ADF database file", control_ptr->prep_adf_file_name);
		ADF_GetLastErrorString(error_text);
		return_code = ADF_SYSTEM_FAILURE;
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	ADF_FreeInFileList(control_ptr);

	if (control_ptr->prep_adf_file != NULL) {
		ADF_CloseADFFilePrep(control_ptr);
		unlink(control_ptr->prep_tmp_file_name);
		free(control_ptr->prep_tmp_file_name);
		control_ptr->prep_tmp_file_name = NULL;
	}

	if (tmp_path_name != NULL)
		free(tmp_path_name);

	if (publish_xref_list != NULL)
		free(publish_xref_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_PREP_GetParams(ADF_CONTROL *control_ptr, unsigned int argc,
	char **argv, char *error_text)
#else
static int ADF_RUN_PREP_GetParams(control_ptr, argc, argv, error_text)
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
		ADF_RUN_PREP_End, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = ADF_CopyDefaultDefSpec(&control_ptr->domain_count,
		&control_ptr->domain_list, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = ADF_RUN_PREP_CreateUsageList(control_ptr,
		&usage_count, &usage_list, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

#ifndef NARGS
	if ((return_code = ADF_GetParams(control_ptr,
		((unsigned int) argc), argv, &control_ptr->help_flag,
		&control_ptr->version_flag,
		((int (*)(void *, unsigned int, char **, int, unsigned int, char *))
		ADF_RUN_PREP_Parse), error_text)) == ADF_SUCCESS) {
#else
	else if ((return_code = ADF_GetParams(control_ptr,
		((unsigned int) argc), argv, &control_ptr->help_flag,
		&control_ptr->version_flag, ADF_RUN_PREP_Parse, error_text)) ==
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
				ADF_RUN_PREP_VERSION_NUMBER);
			exit(0);
		}
		else if ((return_code = ADF_RUN_PREP_CheckParams(control_ptr,
			error_text)) == ADF_SUCCESS) {
			if (control_ptr->log_flag == ADF_TRUE) {
				if (control_ptr->quiet_flag == ADF_TRUE)
					MLOG_SetFlagFile(control_ptr->mlog_ptr, 0, NULL);
				if ((return_code = ADF_RUN_OpenLogFile(control_ptr,
					error_text)) == ADF_SUCCESS)
					ADF_RUN_PREP_ShowSettings(control_ptr);
			}
		}
		if (return_code != ADF_SUCCESS)
			ADF_RUN_PREP_End(control_ptr, 0, NULL, NULL);
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
static int ADF_RUN_PREP_CreateUsageList(ADF_CONTROL *control_ptr,
	unsigned int *usage_count, char ***usage_list, char *error_text)
#else
static int ADF_RUN_PREP_CreateUsageList(control_ptr, usage_count, usage_list,
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

	sprintf(buffer, "\tThis is version %s of %s.", ADF_RUN_PREP_VERSION_NUMBER,
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

	for (count_1 = 0; count_1 < ADF_RUN_PREP_UsageFuncCount; count_1++) {
		if (((return_code =
			(*ADF_RUN_PREP_UsageFuncList[count_1].usage_function)(NULL,
			ADF_RUN_PREP_UsageFuncList[count_1].optional_flag, NULL, usage_count,
			usage_list, error_text)) != ADF_SUCCESS) ||
			((ADF_RUN_PREP_UsageFuncList[count_1].added_text != NULL) &&
			((return_code = ADF_BUSE_AppendLine(
			ADF_RUN_PREP_UsageFuncList[count_1].added_text, usage_count,
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
static void ADF_RUN_PREP_ShowSettings(const ADF_CONTROL *control_ptr)
#else
static void ADF_RUN_PREP_ShowSettings(control_ptr)
const ADF_CONTROL *control_ptr;
#endif /* #ifndef NARGS */
{
	MLOG_DoSepStart(control_ptr->mlog_ptr);

	MLOG_LogInfo(control_ptr->mlog_ptr, "Program Name       : %s\n",
		control_ptr->program_name);
	MLOG_LogInfo(control_ptr->mlog_ptr, "Version Number     : %s\n",
		ADF_RUN_PREP_VERSION_NUMBER);
	MLOG_LogInfo(control_ptr->mlog_ptr, "Host Name          : %s\n",
		control_ptr->host_name);
	MLOG_LogInfo(control_ptr->mlog_ptr, "Process ID         : %u\n",
		control_ptr->process_id);
	MLOG_LogInfo(control_ptr->mlog_ptr, "Current Directory  : %s\n",
		control_ptr->current_dir);
	MLOG_LogInfo(control_ptr->mlog_ptr, "Log File Name      : %s\n",
		control_ptr->log_file_name);

	MLOG_DoSepHyphen(control_ptr->mlog_ptr);

	MLOG_LogInfo(control_ptr->mlog_ptr, "ADF Definition File: %s\n",
		(control_ptr->adf_def_file_name == NULL) ? "*** NONE ***" :
		control_ptr->adf_def_file_name);
	MLOG_LogInfo(control_ptr->mlog_ptr, "ADF Database File  : %s\n",
		control_ptr->prep_adf_file_name);

	MLOG_DoSepEqual(control_ptr->mlog_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_PREP_CheckParams(ADF_CONTROL *control_ptr, char *error_text)
#else
static int ADF_RUN_PREP_CheckParams(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_BAD_ARGS_FAILURE;

	if (control_ptr->prep_adf_file_name == NULL)
		sprintf(error_text, "%s '-ADF_DATA_BASE_FILE=' parameter.",
			"Output ADF database file not specified with the");
	else if (!control_ptr->in_file_name_count)
		strcpy(error_text,
			"No source files were specified on the command line.");
	else
		return_code = ADF_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RUN_PREP_Parse(ADF_CONTROL *control_ptr, unsigned int argc,
	char **argv, int init_flag, unsigned int current_arg, char *error_text)
#else
static int ADF_RUN_PREP_Parse(control_ptr, argc, argv, init_flag, current_arg,
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
		if (ADF_PARG_ADFDefFile(this_arg, &arg_length, &data_ptr,
			&control_ptr->adf_def_file_name, &return_code, error_text) ==
			ADF_TRUE) {
			fprintf(stderr, "Reading ADF definition file '%s' --- ",
				control_ptr->adf_def_file_name);
			if ((return_code = ADF_ReadDefinitionFile(control_ptr,
				control_ptr->adf_def_file_name, error_text)) == ADF_SUCCESS)
				fprintf(stderr, "OK\n");
			else
				fprintf(stderr, "ERROR: %s\n", error_text);
		}
		else if (ADF_PARG_PrepADFFile(this_arg, &arg_length, &data_ptr,
			&control_ptr->prep_adf_file_name, &return_code, error_text) ==
			ADF_TRUE)
			;
		else if (ADF_PARG_PrepADFFileMode(this_arg, &arg_length, &data_ptr,
			&control_ptr->prep_adf_file_mode, &return_code, error_text) ==
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
		else if (ADF_PARG_IgnoreBadCmntFlag(this_arg, &arg_length, &data_ptr,
			&control_ptr->ignore_bad_cmnt_flag, &return_code, error_text) ==
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
				"Unable to allocate memory for the source file list.");
			return_code = ADF_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RUN_PREP_End(ADF_CONTROL *control_ptr, int signal_number,
	int *exit_code_ptr, const char *message_buffer)
#else
static void ADF_RUN_PREP_End(control_ptr, signal_number, exit_code_ptr,
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

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Remove the temporary ADF database file if it's present.		*/
	/*	**************************************************************	*/
	if ((control_ptr->prep_tmp_file_name != NULL) &&
		(control_ptr->prep_adf_file != NULL)) {
		ADF_CloseADFFilePrep(control_ptr);
		unlink(control_ptr->prep_tmp_file_name);
		free(control_ptr->prep_tmp_file_name);
		control_ptr->prep_tmp_file_name = NULL;
	}
	/*	**************************************************************	*/

	ADF_RUN_EndFinish(control_ptr);
}
/*	***********************************************************************	*/

