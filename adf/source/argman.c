/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Argument-parsing support for the 'adfout' executable
								man-page-specific parameters.

	Revision History	:	1996-09-12 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
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
COMPAT_FN_DECL_STATIC(int ADF_OARG_MAN_SectionName,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_MAN_DATA *man_data_ptr, int *error_code, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OARG_MAN_OwnerName,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_MAN_DATA *man_data_ptr, int *error_code, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OARG_MAN_ParseOutParam(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, ADF_MAN_DATA *man_data_ptr,
	int *error_code, char *error_text)
#else
int ADF_OARG_MAN_ParseOutParam(in_arg_ptr, in_arg_length, in_data_ptr,
	man_data_ptr, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
ADF_MAN_DATA  *man_data_ptr;
int           *error_code;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = ADF_OARG_MAN_SectionName(in_arg_ptr,
		in_arg_length, in_data_ptr, man_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	else if (((return_code = ADF_OARG_MAN_OwnerName(in_arg_ptr,
		in_arg_length, in_data_ptr, man_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OARG_MAN_SectionName(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, ADF_MAN_DATA *man_data_ptr,
	int *error_code, char *error_text)
#else
static int ADF_OARG_MAN_SectionName(in_arg_ptr, in_arg_length, in_data_ptr,
	man_data_ptr, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
ADF_MAN_DATA  *man_data_ptr;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr,
		"-MAN_PAGES:SECTION_NAME=", "-MAN_PAGES:SECTION_NAMES=",
		"-MAN_PAGE:SECTION_NAME=", "-MAN_PAGE:SECTION_NAMES=",
		"-MAN:SECTION_NAME=", "-MAN:SECTION_NAMES=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (man_data_ptr->section_name != NULL) {
			free(man_data_ptr->section_name);
			man_data_ptr->section_name = NULL;
		}
		if (**data_ptr)
			*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
				*data_ptr, &man_data_ptr->section_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OARG_MAN_OwnerName(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, ADF_MAN_DATA *man_data_ptr,
	int *error_code, char *error_text)
#else
static int ADF_OARG_MAN_OwnerName(in_arg_ptr, in_arg_length, in_data_ptr,
	man_data_ptr, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
ADF_MAN_DATA  *man_data_ptr;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr,
		"-MAN_PAGES:OWNER_NAME=", "-MAN_PAGES:OWNER_NAMES=",
		"-MAN_PAGE:OWNER_NAME=", "-MAN_PAGE:OWNER_NAMES=",
		"-MAN:OWNER_NAME=", "-MAN:OWNER_NAMES=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (man_data_ptr->owner_name != NULL) {
			free(man_data_ptr->owner_name);
			man_data_ptr->owner_name = NULL;
		}
		if (**data_ptr)
			*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
				*data_ptr, &man_data_ptr->owner_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

