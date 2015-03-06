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
								executable FrameMaker-specific parameters.

	Revision History	:	1996-09-08 --- Creation.
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
COMPAT_FN_DECL_STATIC(int ADF_OUSE_FRAME_DocumentName,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
   char ***usage_list, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OUSE_FRAME_OwnerName,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
   char ***usage_list, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OUSE_FRAME_Copyright,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
   char ***usage_list, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OUSE_FRAME_CoverName_1,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
   char ***usage_list, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OUSE_FRAME_CoverName_2,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
   char ***usage_list, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OUSE_FRAME_LongName,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
   char ***usage_list, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OUSE_FRAME_ShortName,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static const GEN_USAGE_PARAM ADF_OUSE_FRAME_ParamList[] = {
	{	GENFUNCS_TRUE, ADF_OUSE_FRAME_DocumentName,	NULL	},
	{	GENFUNCS_TRUE, ADF_OUSE_FRAME_OwnerName,		NULL	},
	{	GENFUNCS_TRUE, ADF_OUSE_FRAME_Copyright,		NULL	},
	{	GENFUNCS_TRUE, ADF_OUSE_FRAME_CoverName_1,	NULL	},
	{	GENFUNCS_TRUE, ADF_OUSE_FRAME_CoverName_2,	NULL	},
	{	GENFUNCS_TRUE,	ADF_OUSE_FRAME_LongName,		NULL	},
	{	GENFUNCS_TRUE, ADF_OUSE_FRAME_ShortName,		NULL	}
};

static const unsigned int    ADF_OUSE_FRAME_ParamCount  =
	sizeof(ADF_OUSE_FRAME_ParamList) / sizeof(ADF_OUSE_FRAME_ParamList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUSE_FRAME_ParseOutParam(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_FRAME_ParseOutParam(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_BUSE_CreateUsageList(ADF_OUSE_FRAME_ParamCount,
		ADF_OUSE_FRAME_ParamList, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OUSE_FRAME_DocumentName(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
static int ADF_OUSE_FRAME_DocumentName(base_arg_ptr, optional_flag,
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
		"-FRAME[[_]MAKER]:DOC[UMENT]_NAME[S]=[<string>]";
	static char       *arg_usage_list[] = {
	"		Defines the FrameMaker variable 'DocumentName' to be equal to \
the string <string>.",
	"\n",
	"		If the <string> component of this parameter is not present in the \
parameter, the variable will be reset to 'NULL'.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OUSE_FRAME_OwnerName(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
static int ADF_OUSE_FRAME_OwnerName(base_arg_ptr, optional_flag,
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
		"-FRAME[[_]MAKER]:OWNER_NAME[S]=[<string>]";
	static char       *arg_usage_list[] = {
	"		Defines the FrameMaker variable 'OwnerName' to be equal to \
the string <string>.",
	"\n",
	"		If the <string> component of this parameter is not present in the \
parameter, the variable will be reset to 'NULL'.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OUSE_FRAME_Copyright(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
static int ADF_OUSE_FRAME_Copyright(base_arg_ptr, optional_flag,
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
		"-FRAME[[_]MAKER]:COPYRIGHT_NAME[S]=[<string>]";
	static char       *arg_usage_list[] = {
	"		Defines the FrameMaker variable 'Copyright' to be equal to \
the string <string>.",
	"\n",
	"		If the <string> component of this parameter is not present in the \
parameter, the variable will be reset to 'NULL'.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OUSE_FRAME_CoverName_1(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
static int ADF_OUSE_FRAME_CoverName_1(base_arg_ptr, optional_flag,
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
		"-FRAME[[_]MAKER]:COVER_NAME[S]_1=[<string>]";
	static char       *arg_usage_list[] = {
	"		Defines the FrameMaker variable 'CoverName_1' to be equal to \
the string <string>.",
	"\n",
	"		If the <string> component of this parameter is not present in the \
parameter, the variable will be reset to 'NULL'.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OUSE_FRAME_CoverName_2(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
static int ADF_OUSE_FRAME_CoverName_2(base_arg_ptr, optional_flag,
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
		"-FRAME[[_]MAKER]:COVER_NAME[S]_2=[<string>]";
	static char       *arg_usage_list[] = {
	"		Defines the FrameMaker variable 'CoverName_2' to be equal to \
the string <string>.",
	"\n",
	"		If the <string> component of this parameter is not present in the \
parameter, the variable will be reset to 'NULL'.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OUSE_FRAME_LongName(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
static int ADF_OUSE_FRAME_LongName(base_arg_ptr, optional_flag,
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
		"-FRAME[[_]MAKER]:LONG_NAME[S]=[<string>]";
	static char       *arg_usage_list[] = {
	"		Defines the FrameMaker variable 'LongDocumentName' to be equal to \
the string <string>.",
	"\n",
	"		If the <string> component of this parameter is not present in the \
parameter, the variable will be reset to 'NULL'.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OUSE_FRAME_ShortName(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
static int ADF_OUSE_FRAME_ShortName(base_arg_ptr, optional_flag,
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
		"-FRAME[[_]MAKER]:SHORT_NAME[S]=[<string>]";
	static char       *arg_usage_list[] = {
	"		Defines the FrameMaker variable 'ShortDocumentName' to be equal to \
the string <string>.",
	"\n",
	"		If the <string> component of this parameter is not present in the \
parameter, the variable will be reset to 'NULL'.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

