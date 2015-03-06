/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Argument usage description support for the 'adfout'
								executable HTML-specific parameters.

	Revision History	:	1996-07-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
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
COMPAT_FN_DECL_STATIC(int ADF_OUSE_HTML_LinkAuthor,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
   char ***usage_list, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OUSE_HTML_LinkCopyright,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
   char ***usage_list, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OUSE_HTML_HeadingLevel,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static const GEN_USAGE_PARAM ADF_OUSE_HTML_ParamList[] = {
	{	GENFUNCS_TRUE, ADF_OUSE_HTML_LinkAuthor,		NULL	},
	{	GENFUNCS_TRUE,	ADF_OUSE_HTML_LinkCopyright,	NULL	},
	{	GENFUNCS_TRUE, ADF_OUSE_HTML_HeadingLevel,	NULL	}
};

static const unsigned int    ADF_OUSE_HTML_ParamCount  =
	sizeof(ADF_OUSE_HTML_ParamList) / sizeof(ADF_OUSE_HTML_ParamList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUSE_HTML_ParseOutParam(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_HTML_ParseOutParam(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_BUSE_CreateUsageList(ADF_OUSE_HTML_ParamCount,
		ADF_OUSE_HTML_ParamList, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OUSE_HTML_LinkAuthor(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
static int ADF_OUSE_HTML_LinkAuthor(base_arg_ptr, optional_flag,
	extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         =
		"-HTML:AUTHOR[S]_LINK[S]=<URL>[=[<match-string>]]";
	static char       *arg_usage_list[] = {
	"		Specifies that the paragraphs in the 'AUTHORS' area of ADF \
entries are to be linked to the specified URL.",
	"\n",
	"		If the <match-string> component of this parameter is present, then \
only those paragraphs which contain <match-string> will be so linked.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OUSE_HTML_LinkCopyright(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
static int ADF_OUSE_HTML_LinkCopyright(base_arg_ptr, optional_flag,
	extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         =
		"-HTML:COPYRIGHT[S]_LINK[S]=<URL>[=[<match-string>]]";
	static char       *arg_usage_list[] = {
	"		Specifies that the paragraphs in the 'COPYRIGHTS' area of ADF \
entries are to be linked to the specified URL.",
	"\n",
	"		If the <match-string> component of this parameter is present, then \
only those paragraphs which contain <match-string> will be so linked.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OUSE_HTML_HeadingLevel(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
static int ADF_OUSE_HTML_HeadingLevel(base_arg_ptr, optional_flag,
	extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         =
		"-HTML:HEAD[ER|ING]_LEVEL={1|2|3|4|5|6}";
	static char       *arg_usage_list[] = {
	"		Specifies the HTML heading level to be used when emitting ADF \
section names.",
	"\n",
	"		For example, if the value of this parameter is '3', then the \
program will emit ADF section names with the HTML tag '<H3>'.",
	"\n",
	"		The default used if this parameter is not specified is '<H1>'.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

