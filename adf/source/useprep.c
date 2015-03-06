/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Argument usage description support for the 'adfprep'
								executable.

	Revision History	:	1995-08-05 --- Creation.
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
int ADF_PUSE_ADFDefFile(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int ADF_PUSE_ADFDefFile(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         =
		"-ADF_DEF[INITION][_FILE]=<adf-definition-file-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the name of the ADF definition file to be used to parse \
source files for ADF comments.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PUSE_IgnoreBadCmntFlag(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int ADF_PUSE_IgnoreBadCmntFlag(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         =
		"-IGNORE_BAD_COMMENT[S][_FLAG]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies the name of the ADF database file to which ADF entries \
are to be written by the program.",
	"\n",
	"		The <boolean> component of this parameter has the following syntax:",
	"\n",
	"			{ ON | OFF | TRUE | FALSE | YES | NO }",
	"\n",
	"		The default for this parameter is 'OFF'.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PUSE_PrepADFFile(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_PUSE_PrepADFFile(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         =
		"-ADF_{DB|DATA[_]BASE}[_FILE]=<adf-database-file-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the name of the ADF database file to which ADF entries \
are to be written by the program.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PUSE_PrepADFFileMode(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_PUSE_PrepADFFileMode(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         =
		"-ADF_{DB|DATA[_]BASE}_MODE=<adf-database-mode>";
	static char       *arg_usage_list[] = {
	"		Specifies the mode in which the ADF database file specified by the \
'-ADF_DATABASE_FILE=' parameter is to be updated.",
	"\n",
	"		The <adf-database-mode> component of this parameter has the \
following syntax:",
	"\n",
	"			o {CREATE_OR_UPDATE|EITHER}",
	"				The 'CREATE_OR_UPDATE' mode specifies that if the ADF \
database file already exists it will be opened in 'UPDATE' mode. Otherwise, \
the ADF database file will be created (as in 'CREATE' mode).",
	"\n",
	"			o CREATE",
	"				The 'CREATE' mode specifies that the ADF database file is to \
be created. If the file already exists, it will be over-written.",
	"\n",
	"			o UPDATE",
	"				The 'UPDATE' mode specifies that new or changed entries will \
be written to the ADF database file. Existing entries which have not changed \
will not be affected. The file must already exists.",
	"\n",
	"		If this parameter is not specified, the program will default to \
the 'CREATE_OR_UPDATE' mode behavior.",
	"\n",

	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

