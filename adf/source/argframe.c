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
								FrameMaker-specific parameters.

	Revision History	:	1996-09-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
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
COMPAT_FN_DECL_STATIC(int ADF_OARG_FRAME_DocumentName,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OARG_FRAME_OwnerName,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OARG_FRAME_Copyright,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OARG_FRAME_CoverName_1,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OARG_FRAME_CoverName_2,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OARG_FRAME_LongName,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OARG_FRAME_ShortName,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OARG_FRAME_ParseOutParam(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text)
#else
int ADF_OARG_FRAME_ParseOutParam(in_arg_ptr, in_arg_length, in_data_ptr,
	frame_data_ptr, error_code, error_text)
const char      *in_arg_ptr;
unsigned int    *in_arg_length;
char           **in_data_ptr;
ADF_FRAME_DATA  *frame_data_ptr;
int             *error_code;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = ADF_OARG_FRAME_DocumentName(in_arg_ptr,
		in_arg_length, in_data_ptr, frame_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	else if (((return_code = ADF_OARG_FRAME_OwnerName(in_arg_ptr,
		in_arg_length, in_data_ptr, frame_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	else if (((return_code = ADF_OARG_FRAME_Copyright(in_arg_ptr,
		in_arg_length, in_data_ptr, frame_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	else if (((return_code = ADF_OARG_FRAME_CoverName_1(in_arg_ptr,
		in_arg_length, in_data_ptr, frame_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	else if (((return_code = ADF_OARG_FRAME_CoverName_2(in_arg_ptr,
		in_arg_length, in_data_ptr, frame_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	else if (((return_code = ADF_OARG_FRAME_LongName(in_arg_ptr,
		in_arg_length, in_data_ptr, frame_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	else if (((return_code = ADF_OARG_FRAME_ShortName(in_arg_ptr,
		in_arg_length, in_data_ptr, frame_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OARG_FRAME_DocumentName(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text)
#else
static int ADF_OARG_FRAME_DocumentName(in_arg_ptr, in_arg_length, in_data_ptr,
	frame_data_ptr, error_code, error_text)
const char      *in_arg_ptr;
unsigned int    *in_arg_length;
char           **in_data_ptr;
ADF_FRAME_DATA  *frame_data_ptr;
int             *error_code;
char            *error_text;
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
		"-FRAME_MAKER:DOCUMENT_NAME=", "-FRAME_MAKER:DOCUMENT_NAMES=",
		"-FRAMEMAKER:DOCUMENT_NAME=", "-FRAMEMAKER:DOCUMENT_NAMES=",
		"-FRAME:DOCUMENT_NAME=", "-FRAME:DOCUMENT_NAMES=",
		"-FRAME_MAKER:DOC_NAME=", "-FRAME_MAKER:DOC_NAMES=",
		"-FRAMEMAKER:DOC_NAME=", "-FRAMEMAKER:DOC_NAMES=",
		"-FRAME:DOC_NAME=", "-FRAME:DOC_NAMES=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (frame_data_ptr->document_name != NULL) {
			free(frame_data_ptr->document_name);
			frame_data_ptr->document_name = NULL;
		}
		if (**data_ptr)
			*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
				*data_ptr, &frame_data_ptr->document_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OARG_FRAME_OwnerName(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text)
#else
static int ADF_OARG_FRAME_OwnerName(in_arg_ptr, in_arg_length, in_data_ptr,
	frame_data_ptr, error_code, error_text)
const char      *in_arg_ptr;
unsigned int    *in_arg_length;
char           **in_data_ptr;
ADF_FRAME_DATA  *frame_data_ptr;
int             *error_code;
char            *error_text;
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
		"-FRAME_MAKER:OWNER_NAME=", "-FRAME_MAKER:OWNER_NAMES=",
		"-FRAMEMAKER:OWNER_NAME=", "-FRAMEMAKER:OWNER_NAMES=",
		"-FRAME:OWNER_NAME=", "-FRAME:OWNER_NAMES=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (frame_data_ptr->owner_name != NULL) {
			free(frame_data_ptr->owner_name);
			frame_data_ptr->owner_name = NULL;
		}
		if (**data_ptr)
			*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
				*data_ptr, &frame_data_ptr->owner_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OARG_FRAME_Copyright(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text)
#else
static int ADF_OARG_FRAME_Copyright(in_arg_ptr, in_arg_length, in_data_ptr,
	frame_data_ptr, error_code, error_text)
const char      *in_arg_ptr;
unsigned int    *in_arg_length;
char           **in_data_ptr;
ADF_FRAME_DATA  *frame_data_ptr;
int             *error_code;
char            *error_text;
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
		"-FRAME_MAKER:COPYRIGHT_NAME=", "-FRAME_MAKER:COPYRIGHT_NAMES=",
		"-FRAMEMAKER:COPYRIGHT_NAME=", "-FRAMEMAKER:COPYRIGHT_NAMES=",
		"-FRAME:COPYRIGHT_NAME=", "-FRAME:COPYRIGHT_NAMES=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (frame_data_ptr->copyright != NULL) {
			free(frame_data_ptr->copyright);
			frame_data_ptr->copyright = NULL;
		}
		if (**data_ptr)
			*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
				*data_ptr, &frame_data_ptr->copyright, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OARG_FRAME_CoverName_1(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text)
#else
static int ADF_OARG_FRAME_CoverName_1(in_arg_ptr, in_arg_length, in_data_ptr,
	frame_data_ptr, error_code, error_text)
const char      *in_arg_ptr;
unsigned int    *in_arg_length;
char           **in_data_ptr;
ADF_FRAME_DATA  *frame_data_ptr;
int             *error_code;
char            *error_text;
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
		"-FRAME_MAKER:COVER_NAME_1=", "-FRAME_MAKER:COVER_NAMES_1=",
		"-FRAMEMAKER:COVER_NAME_1=", "-FRAMEMAKER:COVER_NAMES_1=",
		"-FRAME:COVER_NAME_1=", "-FRAME:COVER_NAMES_1=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (frame_data_ptr->cover_name_1 != NULL) {
			free(frame_data_ptr->cover_name_1);
			frame_data_ptr->cover_name_1 = NULL;
		}
		if (**data_ptr)
			*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
				*data_ptr, &frame_data_ptr->cover_name_1, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OARG_FRAME_CoverName_2(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text)
#else
static int ADF_OARG_FRAME_CoverName_2(in_arg_ptr, in_arg_length, in_data_ptr,
	frame_data_ptr, error_code, error_text)
const char      *in_arg_ptr;
unsigned int    *in_arg_length;
char           **in_data_ptr;
ADF_FRAME_DATA  *frame_data_ptr;
int             *error_code;
char            *error_text;
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
		"-FRAME_MAKER:COVER_NAME_2=", "-FRAME_MAKER:COVER_NAMES_2=",
		"-FRAMEMAKER:COVER_NAME_2=", "-FRAMEMAKER:COVER_NAMES_2=",
		"-FRAME:COVER_NAME_2=", "-FRAME:COVER_NAMES_2=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (frame_data_ptr->cover_name_2 != NULL) {
			free(frame_data_ptr->cover_name_2);
			frame_data_ptr->cover_name_2 = NULL;
		}
		if (**data_ptr)
			*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
				*data_ptr, &frame_data_ptr->cover_name_2, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OARG_FRAME_LongName(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text)
#else
static int ADF_OARG_FRAME_LongName(in_arg_ptr, in_arg_length, in_data_ptr,
	frame_data_ptr, error_code, error_text)
const char      *in_arg_ptr;
unsigned int    *in_arg_length;
char           **in_data_ptr;
ADF_FRAME_DATA  *frame_data_ptr;
int             *error_code;
char            *error_text;
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
		"-FRAME_MAKER:LONG_NAME=", "-FRAME_MAKER:LONG_NAMES=",
		"-FRAMEMAKER:LONG_NAME=", "-FRAMEMAKER:LONG_NAMES=",
		"-FRAME:LONG_NAME=", "-FRAME:LONG_NAMES=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (frame_data_ptr->long_name != NULL) {
			free(frame_data_ptr->long_name);
			frame_data_ptr->long_name = NULL;
		}
		if (**data_ptr)
			*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
				*data_ptr, &frame_data_ptr->long_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
#ifndef NARGS
static int ADF_OARG_FRAME_ShortName(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *frame_data_ptr, int *error_code, char *error_text)
#else
static int ADF_OARG_FRAME_ShortName(in_arg_ptr, in_arg_length, in_data_ptr,
	frame_data_ptr, error_code, error_text)
const char      *in_arg_ptr;
unsigned int    *in_arg_length;
char           **in_data_ptr;
ADF_FRAME_DATA  *frame_data_ptr;
int             *error_code;
char            *error_text;
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
		"-FRAME_MAKER:SHORT_NAME=", "-FRAME_MAKER:SHORT_NAMES=",
		"-FRAMEMAKER:SHORT_NAME=", "-FRAMEMAKER:SHORT_NAMES=",
		"-FRAME:SHORT_NAME=", "-FRAME:SHORT_NAMES=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if (frame_data_ptr->short_name != NULL) {
			free(frame_data_ptr->short_name);
			frame_data_ptr->short_name = NULL;
		}
		if (**data_ptr)
			*error_code = ADF_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
				*data_ptr, &frame_data_ptr->short_name, error_text);
	}

	return(return_code);
}
/* *********************************************************************** */

