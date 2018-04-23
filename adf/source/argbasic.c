/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Argument-parsing support for all ADF executables.

	Revision History	:	1995-05-19 --- Creation.
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

#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DECL const ADF_AREA ADF_AreaNameList[];
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int ADF_BARG_CludeListAlloc,
	(const char *data_ptr,
	ADF_CLUDE *clude_ptr, unsigned int *clude_count, int lower_case_flag,
	char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_CheckOnlyFlag(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *check_only_flag, int *error_code, char *error_text)
#else
int ADF_BARG_CheckOnlyFlag(in_arg_ptr, in_arg_length, in_data_ptr,
	check_only_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *check_only_flag;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	int            error_flag;
	char           genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*error_code = ADF_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, check_only_flag,
		genfuncs_error_text, arg_length, data_ptr, "-CHECK=", "-CHECK_ONLY=",
		"-CHECK_FLAG=", "-CHECK_ONLY_FLAG=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (error_flag == GENFUNCS_TRUE) {
			nstrcpy(error_text, genfuncs_error_text, ADF_MAX_ERROR_TEXT - 1);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_CludeEntry(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, ADF_CONTROL *control_ptr, int *error_code,
	char *error_text)
#else
int ADF_BARG_CludeEntry(in_arg_ptr, in_arg_length, in_data_ptr, control_ptr,
	error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
ADF_CONTROL   *control_ptr;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_TRUE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

#ifdef __MSDOS__
#endif /* #ifdef __MSDOS__ */

	*error_code = ADF_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-INCLUDE_NAME=",
		"-INCLUDE_NAMES=", NULL) == GENFUNCS_TRUE)
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			&control_ptr->entry_clude[ADF_CLUDE_BASIS_INCLUDE]
			[ADF_CLUDE_TYPE_BASE_NAME], &control_ptr->entry_include_count,
			ADF_FALSE, error_text);
	else if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-EXCLUDE_NAME=",
		"-EXCLUDE_NAMES=", NULL) == GENFUNCS_TRUE)
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			&control_ptr->entry_clude[ADF_CLUDE_BASIS_EXCLUDE]
			[ADF_CLUDE_TYPE_BASE_NAME], &control_ptr->entry_exclude_count,
			ADF_FALSE, error_text);
	else if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-INCLUDE_FILE=",
		"-INCLUDE_FILES=", NULL) == GENFUNCS_TRUE)
#ifdef __MSDOS__
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			&control_ptr->entry_clude[ADF_CLUDE_BASIS_INCLUDE]
			[ADF_CLUDE_TYPE_FILE_NAME], &control_ptr->entry_include_count,
			ADF_TRUE, error_text);
#else
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			&control_ptr->entry_clude[ADF_CLUDE_BASIS_INCLUDE]
			[ADF_CLUDE_TYPE_FILE_NAME], &control_ptr->entry_include_count,
			ADF_FALSE, error_text);
#endif /* #ifdef __MSDOS__ */
	else if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-EXCLUDE_FILE=",
		"-EXCLUDE_FILES=", NULL) == GENFUNCS_TRUE)
#ifdef __MSDOS__
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			&control_ptr->entry_clude[ADF_CLUDE_BASIS_EXCLUDE]
			[ADF_CLUDE_TYPE_FILE_NAME], &control_ptr->entry_exclude_count,
			ADF_TRUE, error_text);
#else
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			&control_ptr->entry_clude[ADF_CLUDE_BASIS_EXCLUDE]
			[ADF_CLUDE_TYPE_FILE_NAME], &control_ptr->entry_exclude_count,
			ADF_FALSE, error_text);
#endif /* #ifdef __MSDOS__ */
	else if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-INCLUDE_TYPE=",
		"-INCLUDE_TYPES=", NULL) == GENFUNCS_TRUE)
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			&control_ptr->entry_clude[ADF_CLUDE_BASIS_INCLUDE]
			[ADF_CLUDE_TYPE_FILE_TYPE], &control_ptr->entry_include_count,
			ADF_FALSE, error_text);
	else if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-EXCLUDE_TYPE=",
		"-EXCLUDE_TYPES=", NULL) == GENFUNCS_TRUE)
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			&control_ptr->entry_clude[ADF_CLUDE_BASIS_EXCLUDE]
			[ADF_CLUDE_TYPE_FILE_TYPE], &control_ptr->entry_exclude_count,
			ADF_FALSE, error_text);
	else if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-INCLUDE_MAN=",
		"-INCLUDE_MANS=", "-INCLUDE_MAN_PAGE=", "-INCLUDE_MAN_PAGES=", NULL) ==
		GENFUNCS_TRUE)
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			&control_ptr->entry_clude[ADF_CLUDE_BASIS_INCLUDE]
			[ADF_CLUDE_TYPE_MAN_PAGE], &control_ptr->entry_include_count,
			ADF_FALSE, error_text);
	else if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-EXCLUDE_MAN=",
		"-EXCLUDE_MANS=", "-EXCLUDE_MAN_PAGE=", "-EXCLUDE_MAN_PAGES=", NULL) ==
		GENFUNCS_TRUE)
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			&control_ptr->entry_clude[ADF_CLUDE_BASIS_EXCLUDE]
			[ADF_CLUDE_TYPE_MAN_PAGE], &control_ptr->entry_exclude_count,
			ADF_FALSE, error_text);
	else
		return_code = ADF_FALSE;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_CludeHText(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, ADF_CONTROL *control_ptr, int *error_code,
	char *error_text)
#else
int ADF_BARG_CludeHText(in_arg_ptr, in_arg_length, in_data_ptr, control_ptr,
	error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
ADF_CONTROL   *control_ptr;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_TRUE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = ADF_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-INCLUDE_HYPER=",
		"-INCLUDE_HYPERTEXT=", "-INCLUDE_HYPER_TEXT=", NULL) == GENFUNCS_TRUE)
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			control_ptr->htext_clude + ADF_CLUDE_BASIS_INCLUDE,
			&control_ptr->htext_include_count, ADF_FALSE, error_text);
	else if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-EXCLUDE_HYPER=",
		"-EXCLUDE_HYPERTEXT=", "-EXCLUDE_HYPER_TEXT=", NULL) == GENFUNCS_TRUE)
		*error_code = ADF_BARG_CludeListAlloc(*data_ptr,
			control_ptr->htext_clude + ADF_CLUDE_BASIS_EXCLUDE,
			&control_ptr->htext_exclude_count, ADF_FALSE, error_text);
	else
		return_code = ADF_FALSE;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_ContOnErrorFlag(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *cont_on_error_flag,
	int *error_code, char *error_text)
#else
int ADF_BARG_ContOnErrorFlag(in_arg_ptr, in_arg_length, in_data_ptr,
	cont_on_error_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *cont_on_error_flag;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	int            error_flag;
	char           genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*error_code = ADF_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, cont_on_error_flag,
		genfuncs_error_text, arg_length, data_ptr, "-CONT_ON_ERROR=",
		"-CONT_ON_ERROR_FLAG=", "-CONTINUE_ON_ERROR=",
		"-CONTINUE_ON_ERROR_FLAG=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (error_flag == GENFUNCS_TRUE) {
			nstrcpy(error_text, genfuncs_error_text, ADF_MAX_ERROR_TEXT - 1);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_DuplicateType(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *dup_handling_type,
	int *error_code, char *error_text)
#else
int ADF_BARG_DuplicateType(in_arg_ptr, in_arg_length, in_data_ptr,
	dup_handling_type, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *dup_handling_type;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = ADF_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-DUP=", "-DUPS=",
		"-DUP_HANDLING=", "-DUPS_HANDLING=", "-DUPLICATE_HANDLING=",
		"-DUPLICATES_HANDLING=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (!stricmp("NONE", *data_ptr))
			*dup_handling_type = ADF_DUP_HANDLER_NONE;
		else if (!stricmp("FIRST", *data_ptr))
			*dup_handling_type = ADF_DUP_HANDLER_FIRST;
		else if (!stricmp("LAST", *data_ptr))
			*dup_handling_type = ADF_DUP_HANDLER_LAST;
		else {
			ADF_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
				"'{NONE|FIRST|LAST}'", error_text);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_IgnoreSection(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *ignore_section_list,
	int *error_code, char *error_text)
#else
int ADF_BARG_IgnoreSection(in_arg_ptr, in_arg_length, in_data_ptr,
	ignore_section_list, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *ignore_section_list;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_FALSE;
	unsigned int   tmp_count   = 0;
	char         **tmp_list    = NULL;
	char          *tmp_string;
	unsigned int   count_1;
	unsigned int   found_index;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = ADF_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-IGNORE_AREA=",
		"-IGNORE_AREAS=", "-IGNORE_SECTION=", "-IGNORE_SECTIONS=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if ((tmp_string = strdup(*data_ptr)) == NULL) {
			STR_AllocMsgItem(strlen(tmp_string), error_text,
				"Unable to allocate temporary string for the '%-*.*s' parameter",
				((int) *arg_length), ((int) *arg_length), in_arg_ptr);
			*error_code = ADF_MEMORY_FAILURE;
		}
		else {
			if (sepwordx(noblank(tmp_string), ",", &tmp_count, &tmp_list) !=
				STRFUNCS_SUCCESS) {
				STR_AllocMsgPtrList(chrcnt(tmp_string, ',') + 1,
					strlen(tmp_string) + chrcnt(tmp_string, ',') + 1, error_text,
					"%s '%-*.*s' parameter",
					"Unable to allocate temporary area name list for the",
					((int) *arg_length), ((int) *arg_length), in_arg_ptr);
				*error_code = ADF_MEMORY_FAILURE;
			}
			else {
				for (count_1 = 0; count_1 < tmp_count; count_1++) {
					if (ADF_FIND_AreaByName(tmp_list[count_1], &found_index) !=
						NULL) {
						if (ADF_AreaNameList[found_index].required_flag != ADF_TRUE)
							ignore_section_list[found_index] = ADF_TRUE;
						else {
							sprintf(error_text,
								"%s '%-*.*s' parameter ('%-.500s') --- %s.",
								"Invalid", ((int) *arg_length), ((int) *arg_length),
								in_arg_ptr, tmp_list[count_1],
								"this ADF area name may not be ignored");
							*error_code = ADF_BAD_ARGS_FAILURE;
						}
					}
					else {
						sprintf(error_text,
							"%s '%-*.*s' parameter ('%-.500s') --- expected %s.",
							"Invalid", ((int) *arg_length), ((int) *arg_length),
							in_arg_ptr, tmp_list[count_1],
							"one of the valid ADF area names");
						*error_code = ADF_BAD_ARGS_FAILURE;
					}
				}
				strl_remove_all(&tmp_count, &tmp_list);
			}
			free(tmp_string);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_LogDir(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, char **log_dir,
	int *error_code, char *error_text)
#else
int ADF_BARG_LogDir(in_arg_ptr, in_arg_length, in_data_ptr, log_dir,
	error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **log_dir;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = ADF_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-LOG_DIR=",
		"-LOGGING_DIR=", "-LOG_DIRECTORY=", "-LOGGING_DIRECTORY=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (*log_dir != NULL) {
			fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
				"The log directory specification has changed", *log_dir,
				*data_ptr);
			free(*log_dir);
			*log_dir = NULL;
		}
		*error_code = ADF_BARG_BasicPathExpand(in_arg_ptr, *arg_length,
			*data_ptr, log_dir, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_LogFlag(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *log_flag,
	int *error_code, char *error_text)
#else
int ADF_BARG_LogFlag(in_arg_ptr, in_arg_length, in_data_ptr, log_flag,
	error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *log_flag;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	int            error_flag;
	char           genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*error_code = ADF_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, log_flag,
		genfuncs_error_text, arg_length, data_ptr, "-LOG=", "-LOGGING=",
		"-LOG_FLAG=", "-LOGGING_FLAG=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (error_flag == GENFUNCS_TRUE) {
			nstrcpy(error_text, genfuncs_error_text, ADF_MAX_ERROR_TEXT - 1);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_QuietFlag(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *quiet_flag,
	int *error_code, char *error_text)
#else
int ADF_BARG_QuietFlag(in_arg_ptr, in_arg_length, in_data_ptr, quiet_flag,
	error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *quiet_flag;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	int            error_flag;
	char           genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*error_code = ADF_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, quiet_flag,
		genfuncs_error_text, arg_length, data_ptr, "-QUIET=", "-QUIET_FLAG=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (error_flag == GENFUNCS_TRUE) {
			nstrcpy(error_text, genfuncs_error_text, ADF_MAX_ERROR_TEXT - 1);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_SortOrderType(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *sort_order_type, int *error_code, char *error_text)
#else
int ADF_BARG_SortOrderType(in_arg_ptr, in_arg_length, in_data_ptr,
	sort_order_type, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *sort_order_type;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = ADF_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-SORT=", "-SORTS=",
		"-SORTING=", "-SORT_ORDER=", "-SORTS_ORDER=", "-SORTING_ORDER=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (!stricmp("NONE", *data_ptr))
			*sort_order_type = ADF_SORT_ENTRY_ENTRY;
		else if ((!stricmp("BASE_NAME", *data_ptr)) ||
			(!stricmp("NAME", *data_ptr)))
			*sort_order_type = ADF_SORT_ENTRY_BASE_NAME;
		else if ((!stricmp("FILE_NAME", *data_ptr)) ||
			(!stricmp("FILE", *data_ptr)))
			*sort_order_type = ADF_SORT_ENTRY_FILE_NAME;
		else if ((!stricmp("CORE_NAME", *data_ptr)) ||
			(!stricmp("CORE", *data_ptr)))
			*sort_order_type = ADF_SORT_ENTRY_CORE_NAME;
		else if ((!stricmp("FILE_TYPE", *data_ptr)) ||
			(!stricmp("TYPE", *data_ptr)))
			*sort_order_type = ADF_SORT_ENTRY_FILE_TYPE;
		else if ((!stricmp("MAN_PAGE", *data_ptr)) ||
			(!stricmp("MAN", *data_ptr)))
			*sort_order_type = ADF_SORT_ENTRY_MAN_PAGE;
		else {
			ADF_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
		"'{NONE|[BASE_]NAME]|FILE[_NAME]|CORE[_NAME]|[FILE_]TYPE|MAN[_PAGE]}'",
				error_text);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_BasicParamAlloc(const char *in_arg_ptr, unsigned int arg_length,
	const char *data_ptr, char **alloc_ptr, char *error_text)
#else
int ADF_BARG_BasicParamAlloc(in_arg_ptr, arg_length, data_ptr, alloc_ptr,
	error_text)
const char    *in_arg_ptr;
unsigned int   arg_length;
const char    *data_ptr;
char         **alloc_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_SUCCESS;

	if (!(*data_ptr))
		*alloc_ptr = NULL;
	else if ((*alloc_ptr = strdup(data_ptr)) == NULL) {
		sprintf(error_text,
			"%s '%-*.*s' parameter ('%-.500s') --- %u bytes required.",
			"Unable to allocate memory for the", ((int) arg_length),
			((int) arg_length), in_arg_ptr, data_ptr, strlen(data_ptr) + 1);
		return_code = ADF_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BARG_BasicPathExpand(const char *in_arg_ptr, unsigned int arg_length,
	const char *data_ptr, char **alloc_ptr, char *error_text)
#else
int ADF_BARG_BasicPathExpand(in_arg_ptr, arg_length, data_ptr, alloc_ptr,
	error_text)
const char    *in_arg_ptr;
unsigned int   arg_length;
const char    *data_ptr;
char         **alloc_ptr;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = ADF_SUCCESS;
	int  genfuncs_return_code;
	char genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if (!(*data_ptr))
		*alloc_ptr = NULL;
	else if ((genfuncs_return_code = GEN_ExpandToFullPathName(data_ptr,
		alloc_ptr, genfuncs_error_text)) != GENFUNCS_SUCCESS) {
		sprintf(error_text, "%s '%-*.*s' parameter ('%-.500s'): %-.400s",
			"Unable to determine the fully-qualified path name for the",
			((int) arg_length), ((int) arg_length), in_arg_ptr, data_ptr,
			genfuncs_error_text);
		return_code = (genfuncs_return_code == GENFUNCS_MEMORY_FAILURE) ?
			ADF_MEMORY_FAILURE :
			(genfuncs_return_code == GENFUNCS_SYSTEM_FAILURE) ?
			ADF_SYSTEM_FAILURE : ADF_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_BARG_BadComponentMsg(const char *in_arg_ptr, unsigned int arg_length,
	const char *data_ptr, const char *expected_string, char *error_text)
#else
void ADF_BARG_BadComponentMsg(in_arg_ptr, arg_length, data_ptr,
	expected_string, error_text)
const char    *in_arg_ptr;
unsigned int   arg_length;
const char    *data_ptr;
const char    *expected_string;
char          *error_text;
#endif /* #ifndef NARGS */
{
	sprintf(error_text, "Invalid '%-*.*s' parameter ('%-.500s')",
		((int) arg_length), ((int) arg_length), in_arg_ptr, data_ptr);

	if (expected_string != NULL)
		strcat(strcat(error_text, " --- expected "), expected_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_BARG_CludeListAlloc(const char *data_ptr, ADF_CLUDE *clude_ptr,
	unsigned int *clude_count, int lower_case_flag, char *error_text)
#else
static int ADF_BARG_CludeListAlloc(data_ptr, clude_ptr, clude_count,
	lower_case_flag, error_text)
const char   *data_ptr;
ADF_CLUDE    *clude_ptr;
unsigned int *clude_count;
int           lower_case_flag;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	int            strfuncs_code;
	unsigned int   count_1;
	unsigned int   tmp_u_int;
	char          *tmp_string;
	unsigned int   tmp_count;
	char         **tmp_list;

	if ((tmp_string = strdup(data_ptr)) == NULL) {
		STR_AllocMsgItem(strlen(data_ptr), error_text,
			"Unable to allocate memory for temporary 'clude' string");
		return_code = ADF_MEMORY_FAILURE;
	}
	else {
		if (lower_case_flag == ADF_TRUE)
			lower(tmp_string);
		if (sepwordx(trim(oneblank(ctltospc(tmp_string))), ",", &tmp_count,
			&tmp_list) != STRFUNCS_SUCCESS) {
			STR_AllocMsgPtrList(chrcnt(tmp_string, ','), strlen(tmp_string),
				error_text, "Unable to allocate memory for 'clude' list");
			return_code = ADF_MEMORY_FAILURE;
		}
		else {
			for (count_1 = 0; count_1 < tmp_count; ) {
				if (!(*trim(tmp_list[count_1])))
					strl_remove(&tmp_count, &tmp_list, count_1, 1);
				else
					count_1++;
			}
			if (!tmp_count) {
				*clude_count -= clude_ptr->clude_count;
				strl_remove_all(&clude_ptr->clude_count, &clude_ptr->clude_list);
			}
			else {
				for (count_1 = 0; count_1 < tmp_count; count_1++) {
					if ((strfuncs_code = strl_search(&clude_ptr->clude_count,
						&clude_ptr->clude_list, tmp_list[count_1], &tmp_u_int)) ==
						STRFUNCS_FAILURE) {
						strcpy(error_text,
							"Unable to allocate memory for the 'clude' data.");
						return_code = ADF_MEMORY_FAILURE;
						break;
					}
					else if (strfuncs_code == STRFUNCS_ITEM_NOT_FOUND)
						(*clude_count)++;
				}
			}
			strl_remove_all(&tmp_count, &tmp_list);
		}
		free(tmp_string);
	}

	return(return_code);
}
/*	***********************************************************************	*/

