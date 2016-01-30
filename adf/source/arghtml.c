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
								HTML-specific parameters.

	Revision History	:	1996-07-03 --- Creation.
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
COMPAT_FN_DECL_STATIC(int ADF_OARG_HTML_LinkAuthor,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_HTML_DATA *html_data_ptr, int *error_code, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OARG_HTML_LinkCopyright,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_HTML_DATA *html_data_ptr, int *error_code, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OARG_HTML_HeadingLevel,
	(const char *in_arg_ptr, unsigned int *in_arg_length, char **in_data_ptr,
	ADF_HTML_DATA *html_data_ptr, int *error_code, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OARG_HTML_ParseOutParam(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_HTML_DATA *html_data_ptr, int *error_code, char *error_text)
#else
int ADF_OARG_HTML_ParseOutParam(in_arg_ptr, in_arg_length, in_data_ptr,
	html_data_ptr, error_code, error_text)
const char     *in_arg_ptr;
unsigned int   *in_arg_length;
char          **in_data_ptr;
ADF_HTML_DATA  *html_data_ptr;
int            *error_code;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (((return_code = ADF_OARG_HTML_LinkAuthor(in_arg_ptr,
		in_arg_length, in_data_ptr, html_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	else if (((return_code = ADF_OARG_HTML_LinkCopyright(in_arg_ptr,
		in_arg_length, in_data_ptr, html_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;
	else if (((return_code = ADF_OARG_HTML_HeadingLevel(in_arg_ptr,
		in_arg_length, in_data_ptr, html_data_ptr, error_code, error_text)) ==
		ADF_TRUE) || (*error_code != ADF_SUCCESS))
		goto EXIT_FUNCTION;

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OARG_HTML_LinkAuthor(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_HTML_DATA *html_data_ptr, int *error_code, char *error_text)
#else
static int ADF_OARG_HTML_LinkAuthor(in_arg_ptr, in_arg_length, in_data_ptr,
	html_data_ptr, error_code, error_text)
const char     *in_arg_ptr;
unsigned int   *in_arg_length;
char          **in_data_ptr;
ADF_HTML_DATA  *html_data_ptr;
int            *error_code;
char           *error_text;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-HTML:AUTHOR_LINK=",
		"-HTML:AUTHOR_LINKS=", "-HTML:AUTHORS_LINK=", "-HTML:AUTHORS_LINKS=",
		NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if ((*error_code = ADF_StringPairParse("-HTML:AUTHOR_LINK=", *data_ptr,
			&html_data_ptr->author_link_count, &html_data_ptr->author_link_list,
			error_text)) == ADF_SUCCESS) {
			if ((html_data_ptr->author_link_list
				[html_data_ptr->author_link_count - 1].ptr_1 == NULL) ||
				(!html_data_ptr->author_link_list
				[html_data_ptr->author_link_count - 1].ptr_1[0])) {
				ADF_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
					"<URL>[=[<match-string>]], but the URL is blank.", error_text);
				*error_code = ADF_BAD_ARGS_FAILURE;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OARG_HTML_LinkCopyright(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_HTML_DATA *html_data_ptr, int *error_code, char *error_text)
#else
static int ADF_OARG_HTML_LinkCopyright(in_arg_ptr, in_arg_length, in_data_ptr,
	html_data_ptr, error_code, error_text)
const char     *in_arg_ptr;
unsigned int   *in_arg_length;
char          **in_data_ptr;
ADF_HTML_DATA  *html_data_ptr;
int            *error_code;
char           *error_text;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-HTML:COPYRIGHT_LINK=",
		"-HTML:COPYRIGHT_LINKS=", "-HTML:COPYRIGHTS_LINK=",
		"-HTML:COPYRIGHTS_LINKS=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if ((*error_code = ADF_StringPairParse("-HTML:COPYRIGHT_LINK=",
			*data_ptr, &html_data_ptr->copyright_link_count,
			&html_data_ptr->copyright_link_list, error_text)) == ADF_SUCCESS) {
			if ((html_data_ptr->copyright_link_list
				[html_data_ptr->copyright_link_count - 1].ptr_1 == NULL) ||
				(!html_data_ptr->copyright_link_list
				[html_data_ptr->copyright_link_count - 1].ptr_1[0])) {
				ADF_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
					"<URL>[=[<match-string>]], but the URL is blank.", error_text);
				*error_code = ADF_BAD_ARGS_FAILURE;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
#ifndef NARGS
static int ADF_OARG_HTML_HeadingLevel(const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_HTML_DATA *html_data_ptr, int *error_code, char *error_text)
#else
static int ADF_OARG_HTML_HeadingLevel(in_arg_ptr, in_arg_length, in_data_ptr,
	html_data_ptr, error_code, error_text)
const char     *in_arg_ptr;
unsigned int   *in_arg_length;
char          **in_data_ptr;
ADF_HTML_DATA  *html_data_ptr;
int            *error_code;
char           *error_text;
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

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-HTML:HEAD_LEVEL=",
		"-HTML:HEADER_LEVEL=", "-HTML:HEADING_LEVEL=", NULL) == GENFUNCS_TRUE) {
		return_code = ADF_TRUE;
		if ((strlen(*data_ptr) == 1) && (atoi(*data_ptr) >= 1) &&
			(atoi(*data_ptr) <= 6))
			nstrcpy(html_data_ptr->html_heading_level, *data_ptr,
				sizeof(html_data_ptr->html_heading_level) - 1);
		else {
			ADF_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
				"{ 1 | 2 | 3 | 4 | 5 | 6 }.", error_text);
			*error_code = ADF_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

