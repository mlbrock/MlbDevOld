/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Argument-parsing support for the 'adfprep' executable.

	Revision History	:	1995-08-05 --- Creation.
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

#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PARG_ADFDefFile(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, char **adf_def_file_name, int *error_code,
	char *error_text)
#else
int ADF_PARG_ADFDefFile(in_arg_ptr, in_arg_length, in_data_ptr,
	adf_def_file_name, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **adf_def_file_name;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-ADF_DEF=",
		"-ADF_DEF_FILE=", "-ADF_DEFINITION=", "-ADF_DEFINITION_FILE=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (*adf_def_file_name != NULL) {
			free(*adf_def_file_name);
			*adf_def_file_name = NULL;
		}
		*error_code = ADF_BARG_BasicPathExpand(in_arg_ptr, *arg_length,
			*data_ptr, adf_def_file_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PARG_IgnoreBadCmntFlag(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *ignore_bad_cmnt_flag,
	int *error_code, char *error_text)
#else
int ADF_PARG_IgnoreBadCmntFlag(in_arg_ptr, in_arg_length, in_data_ptr,
	ignore_bad_cmnt_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *ignore_bad_cmnt_flag;
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

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, ignore_bad_cmnt_flag,
		genfuncs_error_text, arg_length, data_ptr, "-IGNORE_BAD_COMMENT=",
		"-IGNORE_BAD_COMMENTS=", "-IGNORE_BAD_COMMENT_FLAG=",
		"-IGNORE_BAD_COMMENTS_FLAG=", NULL) == GENFUNCS_TRUE) {
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
int ADF_PARG_PrepADFFile(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, char **prep_adf_file_name, int *error_code,
	char *error_text)
#else
int ADF_PARG_PrepADFFile(in_arg_ptr, in_arg_length, in_data_ptr,
	prep_adf_file_name, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **prep_adf_file_name;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-ADF_DB=",
		"-ADF_DB_FILE=", "-ADF_DATABASE=", "-ADF_DATABASE_FILE=",
		"-ADF_DATA_BASE=", "-ADF_DATA_BASE_FILE=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (*prep_adf_file_name != NULL) {
			free(*prep_adf_file_name);
			*prep_adf_file_name = NULL;
		}
		*error_code = ADF_BARG_BasicPathExpand(in_arg_ptr, *arg_length,
			*data_ptr, prep_adf_file_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PARG_PrepADFFileMode(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *prep_adf_file_mode,
	int *error_code, char *error_text)
#else
int ADF_PARG_PrepADFFileMode(in_arg_ptr, in_arg_length, in_data_ptr,
	prep_adf_file_mode, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *prep_adf_file_mode;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-ADF_DB_MODE=",
		"-ADF_DATABASE_MODE=", "-ADF_DATA_BASE_MODE=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if ((!stricmp("CREATE_OR_UPDATE", *data_ptr)) ||
			(!stricmp("EITHER", *data_ptr)))
			*prep_adf_file_mode = ADF_PREP_FILE_MODE_EITHER;
		else if (!stricmp("CREATE", *data_ptr))
			*prep_adf_file_mode = ADF_PREP_FILE_MODE_CREATE;
		else if (!stricmp("UPDATE", *data_ptr))
			*prep_adf_file_mode = ADF_PREP_FILE_MODE_UPDATE;
		else {
			ADF_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
				"'{{CREATE_OR_UPDATE|EITHER}|CREATE|UPDATE}'", error_text);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

