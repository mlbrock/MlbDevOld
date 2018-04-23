/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Argument usage description support for all ADF
								executables.

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
typedef struct {
	char *parameter;
	char *component;
	char *type;
} ADF_CLUDE_BUSE_SPEC;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
const ADF_CLUDE_BUSE_SPEC ADF_BUSE_CludeEntryList[] = {
	{	"FILE[S]",		"file-name", 		"entry file name"			},
	{	"NAME[S]",		"entry-name",		"entry name"				},
	{	"TYPE[S]",		"file-extension",	"entry file extension"	},
	{	"MAN_PAGE[S]",	"entry-man-page",	"entry man page"			}
};
const unsigned int        ADF_BUSE_CludeEntryCount  =
	sizeof(ADF_BUSE_CludeEntryList) / sizeof(ADF_BUSE_CludeEntryList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_CheckOnlyFlag(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_CheckOnlyFlag(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "-CHECK[_ONLY][_FLAG]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to initialize itself, perform \
basic operations (exclusive of producing any output), and exit. This option \
permits system administrators to check the validity of the command-line \
parameters used by the program.",
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
int ADF_BUSE_CludeEntry(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_CludeEntry(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;
	unsigned int count_2;
	char         buffer[4096];

	for (count_1 = 0; count_1 < ADF_CLUDE_BASIS_COUNT; count_1++) {
		for (count_2 = 0; count_2 < ADF_CLUDE_TYPE_COUNT; count_2++) {
			sprintf(buffer, "\t%s%s%s=<%s>[,<%s> ...]%s",
				(optional_flag == ADF_TRUE) ? "[" : "",
				(count_1 == ADF_CLUDE_BASIS_INCLUDE) ? "-INCLUDE_" : "-EXCLUDE_",
				ADF_BUSE_CludeEntryList[count_2].parameter,
				ADF_BUSE_CludeEntryList[count_2].component,
				ADF_BUSE_CludeEntryList[count_2].component,
				(optional_flag == ADF_TRUE) ? "]" : "");
			if ((return_code = ADF_BUSE_AppendLine(buffer, usage_count,
				usage_list, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			sprintf(buffer, "\t\tSpecifies the %ss to be %s by the program.",
				ADF_BUSE_CludeEntryList[count_2].type,
				(count_1 == ADF_CLUDE_BASIS_INCLUDE) ? "included" : "excluded");
			if ((return_code = ADF_BUSE_AppendLine(buffer, usage_count,
				usage_list, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			if ((return_code = ADF_BUSE_AppendNL(usage_count, usage_list,
				error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			sprintf(buffer, "\t\tIf the <%s> %s, %s %ss %s %s will be deleted.",
				ADF_BUSE_CludeEntryList[count_2].component,
				"component of this parameter is not present or is empty",
				"the list of", ADF_BUSE_CludeEntryList[count_2].type, "to be",
				(count_1 == ADF_CLUDE_BASIS_INCLUDE) ? "included" : "excluded");
			if ((return_code = ADF_BUSE_AppendLine(buffer, usage_count,
				usage_list, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			if ((return_code = ADF_BUSE_AppendNL(usage_count, usage_list,
				error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_CludeHText(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_CludeHText(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;
	char         buffer[4096];

	for (count_1 = 0; count_1 < ADF_CLUDE_BASIS_COUNT; count_1++) {
		sprintf(buffer, "\t%s%s%s=<%s>[,<%s> ...]%s",
			(optional_flag == ADF_TRUE) ? "[" : "",
			(count_1 == ADF_CLUDE_BASIS_INCLUDE) ? "-INCLUDE_" : "-EXCLUDE_",
			"HYPER[[_]TEXT]", "base-name", "base-name",
			(optional_flag == ADF_TRUE) ? "]" : "");
		if ((return_code = ADF_BUSE_AppendLine(buffer, usage_count,
			usage_list, error_text)) != ADF_SUCCESS)
			break;
		sprintf(buffer, "\t\tSpecifies the %ss to be %s by the program.",
			"hyper text name",
			(count_1 == ADF_CLUDE_BASIS_INCLUDE) ? "included" : "excluded");
		if ((return_code = ADF_BUSE_AppendLine(buffer, usage_count,
			usage_list, error_text)) != ADF_SUCCESS)
			break;
		if ((return_code = ADF_BUSE_AppendNL(usage_count, usage_list,
			error_text)) != ADF_SUCCESS)
			break;
		sprintf(buffer, "\t\tIf the <%s> %s, %s %ss %s %s will be deleted.",
			"hyper-text-name",
			"component of this parameter is not present or is empty",
			"the list of", "hyper text name", "to be",
			(count_1 == ADF_CLUDE_BASIS_INCLUDE) ? "included" : "excluded");
		if ((return_code = ADF_BUSE_AppendLine(buffer, usage_count,
			usage_list, error_text)) != ADF_SUCCESS)
			break;
		if ((return_code = ADF_BUSE_AppendNL(usage_count, usage_list,
			error_text)) != ADF_SUCCESS)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_ContOnErrorFlag(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_ContOnErrorFlag(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-CONT[INUE]_ON_ERROR[_FLAG]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to continue operation after \
encountering a non-fatal error.",
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
int ADF_BUSE_DuplicateType(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_DuplicateType(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-DUP[LICATE][S][_HANDLING]=<duplicate-handling-type>";
	static char       *arg_usage_list[] = {
	"		Specifies how the program is to handle duplicate ADF base names.",
	"\n",
	"		The <duplicate-handling-type> component of this parameter has the \
following syntax:",
	"\n",
	"			o NONE",
	"				Specifies to the program that encountering a duplicate ADF \
base name should result in a program error.",
	"\n",
	"			o FIRST",
	"				Specifies that only the first base name is to be processed by \
the program. Any subsequent entries with same base name will be ignored.",
	"\n",
	"			o LAST",
	"				Specifies that only the last entry having a particular base \
name is to be processed.",
	"\n",
	"		The default for this parameter is 'NONE'.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_Help(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_Help(base_arg_ptr, optional_flag, extra_usage_list, usage_count,
	usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "-H[ELP]";
	static char       *arg_usage_list[] = {
	"		Displays this text.",
	"\n",
	"		Note that if this parameter appears on the command-line, the \
program will exit after displaying the help text.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_IgnoreSection(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_IgnoreSection(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-IGNORE_{AREA|SECTION}[S]=<area-name>[,<area_name> . . .]";
	static char       *arg_usage_list[] = {
	"		Specifies that the program is to ignore the indicated ADF sections.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_LogDir(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_LogDir(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-LOG[GING]_DIR[ECTORY]=<log-file-dir-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the directory within which the log file is to be created.",
	"\n",
	"		If this parameter is not specified, the log file will be created \
in the current directory ('./').",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_LogFlag(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_LogFlag(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "-LOG[GING][_FLAG]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to emit its progress to a log \
file.",
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
int ADF_BUSE_QuietFlag(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_QuietFlag(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "-QUIET[_FLAG]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to supress the emission of \
indicators of its progress to 'stderr'.",
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
int ADF_BUSE_SortOrderType(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_SortOrderType(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-SORT[S|ING][_ORDER]=<sort-order-type>";
	static char       *arg_usage_list[] = {
	"		Specifies how the program is to order ADF entries.",
	"\n",
	"		The <sort-order-type> component of this parameter has the \
following syntax:",
	"\n",
	"			o NONE",
	"				Specifies that no order is to be imposed upon the entries.",
	"\n",
	"			o [BASE_]NAME",
	"				Specifies that the entries are to be sorted by the ADF base \
names.",
	"\n",
	"			o FILE[_NAME]",
	"				Specifies that the entries are to be sorted by the names of \
the source files from which the ADF entries were extracted.",
	"\n",
	"			o CORE[_NAME]",
	"				Specifies that the entries are to be sorted by the 'core' \
names of the source files from which the ADF entries were extracted --- \
that is, the names of the files without pathnames or trailing extensions.",
	"\n",
	"			o [FILE_]TYPE",
	"				Specifies that the entries are to be sorted by the types \
(that is, the extensions) of the files from which the ADF entries were \
extracted.",
	"\n",
	"			o MAN[_PAGE]",
	"				Specifies that the entries are to be sorted by the 'man' \
page sections to which the entries belong.",
	"\n",
	"		The default for this parameter is 'NONE'.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_Version(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_Version(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "-V[ER[SION][S]]]";
	static char       *arg_usage_list[] = {
	"		Displays the version of this program.",
	"\n",
	"		Note that if this parameter appears on the command-line, the \
program will exit after displaying the version information.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_AppendParamText(unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int ADF_BUSE_AppendParamText(usage_count, usage_list, error_text)
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static       char *tmp_ptr          = NULL;
	static const char *arg_name         = "@<parameter-include-file-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the name of a parameter include file from which are to \
be parameters to this program. Parameter include files may themselves \
contain parameter include file specifications.",
	"\n",
	"		When a parameter include file is encountered on the command line, \
the program will attempt to open it for reading. It is an error if the file \
so specified does not exist or can not be read.",
	"\n",
	"		Each line of the parameter include file is parsed for its \
parameters just as if those parameters were entered on the command line \
except for the following rules:",
	"\n",
	"			o A line in which the first non-whitespace character is a \
number-sign ('#') is considered to be the start of a comment and is ignored.",
	"\n",
	"			o Blank lines (that is, lines which are empty or which consist \
wholly of whitespace) are ignored.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(NULL, arg_name, ADF_TRUE,
		arg_usage_list, &tmp_ptr, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_AppendLine(const char *in_line, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_AppendLine(in_line, usage_count, usage_list, error_text)
const char     *in_line;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_SUCCESS;

	if (strl_append(usage_count, usage_list, in_line) != STRFUNCS_SUCCESS) {
		strcpy(error_text, "Unable to allocate memory for the usage text.");
		return_code = ADF_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_AppendNL(unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int ADF_BUSE_AppendNL(usage_count, usage_list, error_text)
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_SUCCESS;

	if (strl_append(usage_count, usage_list, "\n") != STRFUNCS_SUCCESS) {
		strcpy(error_text, "Unable to allocate memory for the usage text.");
		return_code = ADF_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_AppendNULL(unsigned int *usage_count, char ***usage_list,
	char *error_text)
#else
int ADF_BUSE_AppendNULL(usage_count, usage_list, error_text)
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_SUCCESS;

	if (strl_append(usage_count, usage_list, "") != STRFUNCS_SUCCESS) {
		strcpy(error_text, "Unable to allocate memory for the usage text.");
		return_code = ADF_MEMORY_FAILURE;
	}
	else {
		free((*usage_list)[*usage_count - 1]);
		(*usage_list)[*usage_count - 1] = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_BUSE_BasicConstruct(const char *base_arg_ptr, const char *arg_ptr,
	int optional_flag, char **arg_usage_list,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_BUSE_BasicConstruct(base_arg_ptr, arg_ptr, optional_flag,
	arg_usage_list, extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
const char     *arg_ptr;
int             optional_flag;
char **arg_usage_list;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	char         *tmp_arg_data;
	unsigned int  old_usage_count;

	base_arg_ptr = (base_arg_ptr == NULL) ? "" : base_arg_ptr;

	if ((tmp_arg_data = ((char *) malloc((1 + 1 + strlen(base_arg_ptr) +
		strlen(arg_ptr) + 1 + 1) * sizeof(char)))) == NULL)
		return_code = ADF_MEMORY_FAILURE;
	else {
		old_usage_count = *usage_count;
		strcat(strcat(strcat(strcpy(tmp_arg_data, (optional_flag == ADF_TRUE) ?
		"\t[" : "\t"), base_arg_ptr), arg_ptr), (optional_flag == ADF_TRUE) ?
		"]" : "");
		if (strl_append(usage_count, usage_list, tmp_arg_data) !=
			STRFUNCS_SUCCESS)
			return_code = ADF_MEMORY_FAILURE;
		else {
			while (*arg_usage_list != NULL) {
				if (strl_append(usage_count, usage_list, *arg_usage_list) !=
					STRFUNCS_SUCCESS) {
					return_code = ADF_MEMORY_FAILURE;
					break;
				}
				arg_usage_list++;
			}
			if ((return_code == ADF_SUCCESS) && (extra_usage_list != NULL)) {
				while (*extra_usage_list != NULL) {
					if (strl_append(usage_count, usage_list, *extra_usage_list) !=
						STRFUNCS_SUCCESS) {
						return_code = ADF_MEMORY_FAILURE;
						break;
					}
					extra_usage_list++;
				}
			}
		}
		if (return_code != ADF_SUCCESS)
			strl_remove(usage_count, usage_list, old_usage_count, *usage_count);
		free(tmp_arg_data);
	}

	if (return_code != ADF_SUCCESS)
		strcpy(error_text, "Unable to allocate memory for the usage text.");

	return(return_code);
}
/*	***********************************************************************	*/

