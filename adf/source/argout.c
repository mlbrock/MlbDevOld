/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Argument-parsing support for the 'adfout' executable.

	Revision History	:	1995-07-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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
int ADF_OARG_AreaName(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, char **area_name_list, int *error_code, char *error_text)
#else
int ADF_OARG_AreaName(in_arg_ptr, in_arg_length, in_data_ptr, area_name_list,
	error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **area_name_list;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_FALSE;
	char          *tmp_string;
	char          *tmp_ptr;
	unsigned int   found_index;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = ADF_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-AREA_NAME=",
		"-AREA_NAMES=", "-SECTION_NAME=", "-SECTION_NAMES=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if ((tmp_ptr = strchr(*data_ptr, ',')) == NULL) {
			sprintf(error_text,
				"%s '%-*.*s' parameter ('%-.500s') --- expected <%s>,<%s>.",
				"Invalid", ((int) *arg_length), ((int) *arg_length),
				in_arg_ptr, *data_ptr,
				"one of the valid ADF area names",
				"area name replacement string");
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
		else if ((tmp_string = strdup(*data_ptr)) == NULL) {
			STR_AllocMsgItem(strlen(tmp_string), error_text,
				"Unable to allocate temporary string for the '%-*.*s' parameter",
				((int) *arg_length), ((int) *arg_length), in_arg_ptr);
			*error_code = ADF_MEMORY_FAILURE;
		}
		else {
			tmp_ptr    = strchr(tmp_string, ',');
			*tmp_ptr++ = '\0';
			trim(oneblank(ctltospc(tmp_string)));
			trim(oneblank(ctltospc(tmp_ptr)));
			if (ADF_FIND_AreaByName(tmp_string, &found_index) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' parameter ('%-.500s') --- expected %s.",
					"Invalid", ((int) *arg_length), ((int) *arg_length),
					in_arg_ptr, *data_ptr,
					"one of the valid ADF area names");
				*error_code = ADF_BAD_ARGS_FAILURE;
			}
			else if (!(*tmp_ptr)) {
				sprintf(error_text,
					"%s '%-*.*s' parameter ('%-.500s') --- expected <%s>,<%s>.",
					"Invalid", ((int) *arg_length), ((int) *arg_length),
					in_arg_ptr, *data_ptr,
					"one of the valid ADF area names",
					"area name replacement string");
				*error_code = ADF_BAD_ARGS_FAILURE;
			}
			else {
				if (area_name_list[found_index] != NULL) {
					free(area_name_list[found_index]);
					area_name_list[found_index] = NULL;
				}
				*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
					tmp_ptr, area_name_list + found_index, error_text);
			}
			free(tmp_string);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OARG_AreaNameType(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *area_name_type, int *error_code, char *error_text)
#else
int ADF_OARG_AreaNameType(in_arg_ptr, in_arg_length, in_data_ptr,
	area_name_type, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *area_name_type;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-AREA_NAME_TYPE=",
		"-AREA_NAME_TYPES=", "-SECTION_NAME_TYPE=", "-SECTION_NAME_TYPES=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if ((!stricmp("DEF", *data_ptr)) || (!stricmp("DEFINITION", *data_ptr)))
			*area_name_type = ADF_AREA_NAME_TYPE_DEF;
		else if (!stricmp("INTERNAL", *data_ptr))
			*area_name_type = ADF_AREA_NAME_TYPE_INTERNAL;
		else {
			ADF_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
				"'{DEF[INITION]|INTERNAL}'", error_text);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OARG_AreaOrderType(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *area_order_type, int *error_code, char *error_text)
#else
int ADF_OARG_AreaOrderType(in_arg_ptr, in_arg_length, in_data_ptr,
	area_order_type, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *area_order_type;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-AREA_ORDER=",
		"-AREA_ORDERS=", "-AREA_ORDER_TYPE=", "-AREA_ORDER_TYPES=",
		"-SECTION_ORDER=", "-SECTION_ORDERS=", "-SECTION_ORDER_TYPE=",
		"-SECTION_ORDER_TYPES=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if ((!stricmp("DEF", *data_ptr)) || (!stricmp("DEFINITION", *data_ptr)))
			*area_order_type = ADF_AREA_ORDER_TYPE_DEF;
		else if (!stricmp("INTERNAL", *data_ptr))
			*area_order_type = ADF_AREA_ORDER_TYPE_INTERNAL;
		else if ((!stricmp("SOURCE", *data_ptr)) ||
			(!stricmp("SOURCE_FILE", *data_ptr)))
			*area_order_type = ADF_AREA_ORDER_TYPE_SOURCE;
		else {
			ADF_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
				"'{DEF[INITION]|INTERNAL|SOURCE[_FILE]}'", error_text);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OARG_ExternalHTextRef(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, char **external_ref, int *error_code, char *error_text)
#else
int ADF_OARG_ExternalHTextRef(in_arg_ptr, in_arg_length, in_data_ptr,
	external_ref, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **external_ref;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-EXTERN_REF=",
		"-EXTERN_REFS=", "-EXTERN_REFERENCE=", "-EXTERN_REFERENCES=",
		"-EXTERNAL_REF=", "-EXTERNAL_REFS=", "-EXTERNAL_REFERENCE=",
		"-EXTERNAL_REFERENCES=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
			*data_ptr, external_ref, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OARG_GenerateType(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *generate_type, int *error_code, char *error_text)
#else
int ADF_OARG_GenerateType(in_arg_ptr, in_arg_length, in_data_ptr,
	generate_type, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *generate_type;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-GEN=", "-GEN_TYPE=",
		"-GENERATE=", "-GENERATE_TYPE=", "-GENERATION=", "-GENERATION_TYPE=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if ((!stricmp("ENTRY", *data_ptr)) ||
			(!stricmp("ENTRIES", *data_ptr)))
			*generate_type = ADF_GENERATE_TYPE_ENTRY;
		else if ((!stricmp("TABLE_OF_CONTENT", *data_ptr)) ||
			(!stricmp("TABLE_OF_CONTENTS", *data_ptr))      ||
			(!stricmp("TOC", *data_ptr))                    ||
			(!stricmp("TOCS", *data_ptr)))
			*generate_type = ADF_GENERATE_TYPE_TOC;
		else if ((!stricmp("CLASS_TABLE_OF_CONTENT", *data_ptr))  ||
			(!stricmp("CLASS_TABLE_OF_CONTENTS", *data_ptr))       ||
			(!stricmp("CLASS_TOC", *data_ptr))                     ||
			(!stricmp("CLASS_TOCS", *data_ptr))                    ||
			(!stricmp("ENTRY_CLASS_TABLE_OF_CONTENT", *data_ptr))  ||
			(!stricmp("ENTRY_CLASS_TABLE_OF_CONTENTS", *data_ptr)) ||
			(!stricmp("ENTRY_CLASS_TOC", *data_ptr))               ||
			(!stricmp("ENTRY_CLASS_TOCS", *data_ptr)))
			*generate_type = ADF_GENERATE_TYPE_CLASS_TOC;
		else if ((!stricmp("TABLE_OF_FILE", *data_ptr)) ||
			(!stricmp("TABLE_OF_FILES", *data_ptr))      ||
			(!stricmp("TOF", *data_ptr))                    ||
			(!stricmp("TOFS", *data_ptr)))
			*generate_type = ADF_GENERATE_TYPE_TOF;
		else if ((!stricmp("INDEX", *data_ptr)) ||
			(!stricmp("INDEXS", *data_ptr))      ||
			(!stricmp("INDEXES", *data_ptr))     ||
			(!stricmp("INDICES", *data_ptr))     ||
			(!stricmp("IDX", *data_ptr)))
			*generate_type = ADF_GENERATE_TYPE_INDEX;
		else if ((!stricmp("PERMUTATED_INDEX", *data_ptr)) ||
			(!stricmp("PERMUTATE_INDEX", *data_ptr))        ||
			(!stricmp("PERM_INDEX", *data_ptr))             ||
			(!stricmp("PERMUTATED_INDEXS", *data_ptr))      ||
			(!stricmp("PERMUTATE_INDEXS", *data_ptr))       ||
			(!stricmp("PERM_INDEXS", *data_ptr))            ||
			(!stricmp("PERMUTATED_INDEXES", *data_ptr))     ||
			(!stricmp("PERMUTATE_INDEXES", *data_ptr))      ||
			(!stricmp("PERM_INDEXES", *data_ptr))           ||
			(!stricmp("PERMUTATED_INDICES", *data_ptr))     ||
			(!stricmp("PERMUTATE_INDICES", *data_ptr))      ||
			(!stricmp("PERM_INDICES", *data_ptr))           ||
			(!stricmp("PERMUTATED_IDX", *data_ptr))         ||
			(!stricmp("PERMUTATE_IDX", *data_ptr))          ||
			(!stricmp("PERM_IDX", *data_ptr))               ||
			(!stricmp("PERMUTATED", *data_ptr))             ||
			(!stricmp("PERMUTATE", *data_ptr))              ||
			(!stricmp("PERM", *data_ptr)))
			*generate_type = ADF_GENERATE_TYPE_PERM_INDEX;
		else {
			ADF_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
				"'{ {ENTRY|ENTRIES} | {TABLE_OF_CONTENT|TOC}[S] | \
[ENTRY_]CLASS_{TABLE_OF_CONTENT|TOC}[S] | {INDEX[[E]S]|INDICES|IDX} | \
PERM[UTATE[D]][_{INDEX[[E]S]|INDICES|IDX}] }'",
				error_text);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OARG_HyperTextFlag(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *hyper_text_flag, int *error_code, char *error_text)
#else
int ADF_OARG_HyperTextFlag(in_arg_ptr, in_arg_length, in_data_ptr,
	hyper_text_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *hyper_text_flag;
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

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, hyper_text_flag,
		genfuncs_error_text, arg_length, data_ptr, "-HYPERTEXT=",
		"-HYPER_TEXT=", "-HYPERTEXT_FLAG=", "-HYPER_TEXT_FLAG=", NULL) ==
		GENFUNCS_TRUE) {
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
int ADF_OARG_KeepBadSeeAlso(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *keep_bad_see_also_flag, int *error_code,
	char *error_text)
#else
int ADF_OARG_KeepBadSeeAlso(in_arg_ptr, in_arg_length, in_data_ptr,
	keep_bad_see_also_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *keep_bad_see_also_flag;
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

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, keep_bad_see_also_flag,
		genfuncs_error_text, arg_length, data_ptr, "-KEEP_SEE_ALSO=",
		"-KEEP_SEE_ALSOS=", "-KEEP_BAD_SEE_ALSO=", "-KEEP_BAD_SEE_ALSOS=",
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
int ADF_OARG_OutputByFileFlag(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *output_by_file_flag,
	int *error_code, char *error_text)
#else
int ADF_OARG_OutputByFileFlag(in_arg_ptr, in_arg_length, in_data_ptr,
	output_by_file_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *output_by_file_flag;
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

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, output_by_file_flag,
		genfuncs_error_text, arg_length, data_ptr, "-OUTPUT_BY_FILE=",
		"-OUTPUT_BY_FILE_NAME=", "-OUTPUT_BY_FILE_FLAG=",
		"-OUTPUT_BY_FILE_NAME_FLAG=", NULL) == GENFUNCS_TRUE) {
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
int ADF_OARG_OutputDir(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, char **output_dir, char **output_dir_basic,
	int *error_code, char *error_text)
#else
int ADF_OARG_OutputDir(in_arg_ptr, in_arg_length, in_data_ptr, output_dir,
	output_dir_basic, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **output_dir;
char         **output_dir_basic;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-OUTPUT_DIR=",
		"-OUTPUT_DIRECTORY=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (*output_dir != NULL) {
			fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
				"The output directory specification has changed", *output_dir,
				*data_ptr);
			free(*output_dir);
			*output_dir = NULL;
		}
		if (*output_dir_basic != NULL) {
			free(*output_dir_basic);
			*output_dir_basic = NULL;
		}
		if ((*error_code = ADF_BARG_BasicPathExpand(in_arg_ptr, *arg_length,
			*data_ptr, output_dir, error_text)) == ADF_SUCCESS) {
			if (**data_ptr == '~')
				*error_code = ADF_BARG_BasicPathExpand(in_arg_ptr, *arg_length,
					*data_ptr, output_dir_basic, error_text);
			else
				*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
					*data_ptr, output_dir_basic, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OARG_OutputToStdoutFlag(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *output_to_stdout_flag,
	int *error_code, char *error_text)
#else
int ADF_OARG_OutputToStdoutFlag(in_arg_ptr, in_arg_length, in_data_ptr,
	output_to_stdout_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *output_to_stdout_flag;
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

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, output_to_stdout_flag,
		genfuncs_error_text, arg_length, data_ptr, "-STDOUT=", "-STDOUT_FLAG=",
		"-OUTPUT_TO_STDOUT=", "-OUTPUT_TO_STDOUT_FLAG=", NULL) ==
		GENFUNCS_TRUE) {
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
int ADF_OARG_OutputType(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *output_type, int *error_code, char *error_text)
#else
int ADF_OARG_OutputType(in_arg_ptr, in_arg_length, in_data_ptr, output_type,
	error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *output_type;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-OUTPUT=",
		"-OUTPUT_TYPE=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (ADF_GetOutputTypeFromString(*data_ptr, output_type, error_text) !=
			ADF_SUCCESS) {
			ADF_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
				"'{ASC[II]|MAN[_PAGE[S]]|FRAME[[_]MAKER]|HTML|{POST[_]SCRIPT|PS}|\
{RICH_TEXT[_FORMAT]|RTF}'",
				error_text);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
#ifndef NARGS
int ADF_OARG_ParseOutParam(const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, ADF_CONTROL *control_ptr, int *error_code,
	char *error_text)
#else
int ADF_OARG_ParseOutParam(in_arg_ptr, in_arg_length, in_data_ptr,
	control_ptr, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
ADF_CONTROL   *control_ptr;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = ADF_OARG_FRAME_ParseOutParam(in_arg_ptr,
		in_arg_length, in_data_ptr, &control_ptr->frame_data, error_code,
		error_text)) == ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	else if (((return_code = ADF_OARG_HTML_ParseOutParam(in_arg_ptr,
		in_arg_length, in_data_ptr, &control_ptr->html_data, error_code,
		error_text)) == ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	else if (((return_code = ADF_OARG_MAN_ParseOutParam(in_arg_ptr,
		in_arg_length, in_data_ptr, &control_ptr->man_data, error_code,
		error_text)) == ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

