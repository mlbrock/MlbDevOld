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
								executable man-page-specific parameters.

	Revision History	:	1996-09-12 --- Creation.
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
COMPAT_FN_DECL_STATIC(int ADF_OUSE_MAN_SectionName,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
   char ***usage_list, char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_OUSE_MAN_OwnerName,
	(const char *base_arg_ptr,
	int optional_flag, char **extra_usage_list, unsigned int *usage_count,
   char ***usage_list, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static const GEN_USAGE_PARAM ADF_OUSE_MAN_ParamList[] = {
	{	GENFUNCS_TRUE, ADF_OUSE_MAN_SectionName,	NULL	},
	{	GENFUNCS_TRUE, ADF_OUSE_MAN_OwnerName,		NULL	}
};

static const unsigned int    ADF_OUSE_MAN_ParamCount  =
	sizeof(ADF_OUSE_MAN_ParamList) / sizeof(ADF_OUSE_MAN_ParamList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUSE_MAN_ParseOutParam(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_MAN_ParseOutParam(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	return(GEN_BUSE_CreateUsageList(ADF_OUSE_MAN_ParamCount,
		ADF_OUSE_MAN_ParamList, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_OUSE_MAN_SectionName(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
static int ADF_OUSE_MAN_SectionName(base_arg_ptr, optional_flag,
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
		"-MAN[_PAGE[S]]:SECTION_NAME[S]=[<string>]";
	static char       *arg_usage_list[] = {
	"		Defines the variable to be used in the man page header.",
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
static int ADF_OUSE_MAN_OwnerName(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
static int ADF_OUSE_MAN_OwnerName(base_arg_ptr, optional_flag,
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
		"-MAN[_PAGE[S]]:OWNER_NAME[S]=[<string>]";
	static char       *arg_usage_list[] = {
	"		Defines the variable to be used in the man page footer.",
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

