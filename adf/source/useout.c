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
								executable.

	Revision History	:	1995-07-27 --- Creation.
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
int ADF_OUSE_AreaName(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_AreaName(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-{AREA|SECTION}_NAME[S]=<area-name>,<string>";
	static char       *arg_usage_list[] = {
	"		Specifies that the indicated <area-name> is to be replaced be the \
<string> sub-component during output.",
	"\n",
	"		Note that this option over-rides to '-AREA_NAME_TYPE=' option.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUSE_AreaNameType(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_AreaNameType(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-{AREA|SECTION}_NAME_TYPE[S]=<area-name-type>";
	static char       *arg_usage_list[] = {
	"		Specifies the area names to be used when emitting ADF entries. The \
following <area-name-type> components are available:",
	"\n",
	"			o DEF[INITION]",
	"				Specifies that the ADF entry area names to be used are those \
specified by the ADF definition which was used to parse the source file.",
	"\n",
	"			o INTERNAL",
	"				Specifies that the ADF entry area names to be used are those \
specified by the internal list of valid ADF area names.",
	"\n",
	"		If this parameter is not specified, the program will use the \
'INTERNAL' area name type.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUSE_AreaOrderType(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_AreaOrderType(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-{AREA|SECTION}_ORDER[_TYPE][S]=<area-order-type>";
	static char       *arg_usage_list[] = {
	"		Specifies the order in which areas in ADF entries are to be \
emitted. The following <area-order-type> components are available:",
	"\n",
	"			o DEF[INITION]",
	"				Specifies that ADF entry areas are to be emitted in the order \
specified by the ADF definition which was used to parse the source file.",
	"\n",
	"			o INTERNAL",
	"				Specifies that ADF entry areas are to be emitted in the order \
specified by the internal list of valid ADF entries.",
	"\n",
	"			o SOURCE[_FILE]",
	"				Specifies that ADF entry areas are to be emitted in the order \
in which they were encountered in the source file from which the entry was \
derived.",
	"\n",
	"		If this parameter is not specified, the program will use the \
'INTERNAL' area order type.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUSE_ExternalHTextRef(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_ExternalHTextRef(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-EXTERN[AL]_REF[ERENCE][S]=<ADF-database-name>=<hyper-text-ref>";
	static char       *arg_usage_list[] = {
	"		Specifies the use of an ADF database file to resolve external \
hyper-text references.",
	"\n",
	"		The <ADF-database-name> component of this parameter is the name of \
the ADF database file to be used as the source of the hyper-text.",
	"\n",
	"		The <hyper-text-ref> component of this parameter is the string to \
be used to resolve hyper-text links to the entries in the ADF database file \
<ADF-database-name>.",
	"\n",
	"		For '-OUTPUT_TYPE=HTML', the <hyper-text-ref> component should be \
the directory in which reside the HTML pages constructed from the entries in \
the ADF database file <ADF-database-name>.",
	"\n",
	"		For '-OUTPUT_TYPE=FRAME_MAKER', the <hyper-text-ref> component \
should be the name of the FrameMaker document file in which resides the \
text constructed from the entries in the ADF database file \
<ADF-database-name>.",
	"\n",
	"		This option has no effect on other output types, as they do not \
include hyper-text links in their output.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUSE_GenerateType(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_GenerateType(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-GEN[ERATE|ERATION][_TYPE]=<generate-type>";
	static char       *arg_usage_list[] = {
	"		Specifies the type of output the program is to generate. The \
following <generate-type> components are available:",
	"\n",
	"			o {ENTRY|ENTRIES}",
	"				Specifies that ADF entries are to be generated.",
	"\n",
	"			o {TABLE_OF_CONTENT|TOC}[S]",
	"				Specifies that a table of contents is to generated.",
	"\n",
	"			o [ENTRY_]CLASS_{TABLE_OF_CONTENT|TOC}[S]",
	"				Specifies that a table of contents by entry class is to be \
generated.",
	"\n",
	"			o {TABLE_OF_FILE|TOF}[S]",
	"				Specifies that a table of files is to generated.",
	"\n",
	"			o {INDEX[[E]S]|INDICES|IDX}",
	"				Specifies that an index is to be generated.",
	"\n",
	"			o PERM[UTATE[D]][_{INDEX[[E]S]|INDICES|IDX}]",
	"				Specifies that a permutated index is to be generated.",
	"\n",
	"		Note that the table of contents and index generate types are always \
output to 'stdout'.",
	"\n",
	"		If this parameter is not specified, the program will use the \
'ENTRY' generate type.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUSE_HyperTextFlag(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_HyperTextFlag(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "-HYPER[_]TEXT[_FLAG]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to include resolved hyper-text \
references in the output emitted.",
	"\n",
	"		This option is useful only when the '-OUTPUT_TYPE=' parameter is \
either 'FRAME_MAKER' or 'HTML'.",
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
int ADF_OUSE_KeepBadSeeAlso(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_KeepBadSeeAlso(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "-KEEP[_BAD]_SEE_ALSO[S]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies that names in the 'SEE ALSO' section of output entries \
which cannot be resolved to other ADF entries will be emitted in the output. \
The default behavior is to remove such entries from the output.",
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
int ADF_OUSE_OutputByFileFlag(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_OutputByFileFlag(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-OUTPUT_BY_FILE[_NAME][_FLAG]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to emit to files prefixed with \
the name of the file from which the ADF comment was derived instead of \
prefixed with the base name (which is the default).",
	"\n",
	"		The <boolean> component of this parameter has the following syntax:",
	"\n",
	"			{ ON | OFF | TRUE | FALSE | YES | NO }",
	"\n",
	"		Note that if this parameter is set to 'ON', then any sort order \
specified by the '-SORT_ORDER=' parameter will be over-ridden and the ADF \
entries will be sorted by their file names.",
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
int ADF_OUSE_OutputDir(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_OutputDir(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-OUTPUT_DIR[ECTORY]=<output-dir-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the directory within which output files will be \
created.",
	"\n",
	"		The specified directory must already exist.",
	"\n",
	"		Note that when the '-OUTPUT_TYPE=' parameter is 'MAN_PAGE', the \
man page files output will be sent to the file specified by the combination \
of the '-OUTPUT_DIRECTORY=' parameter, the first character of the man page \
section being created, the base name of the ADF comment entry, and a suffix \
consisting of the man page section being created.",
	"\n",
	"		If this parameter is not specified, and the '-OUTPUT_TYPE=' \
setting is not 'MAN_PAGE', the output of the program will be placed in the \
current directory ('./'). If the '-OUTPUT_TYPE' setting is 'MAN_PAGE', the \
man pages output by the program will be placed in the appropriate \
sub-directory of the directory ('./man').",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUSE_OutputToStdoutFlag(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_OutputToStdoutFlag(base_arg_ptr, optional_flag, extra_usage_list,
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
		"-[OUTPUT_TO_]STDOUT[_FLAG]=<boolean>";
	static char       *arg_usage_list[] = {
	"		Specifies whether the program is to emit the output to 'stdout'.",
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
int ADF_OUSE_OutputType(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_OutputType(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	static const char *arg_name         = "-OUTPUT[_TYPE]=<output-type>";
	static char       *arg_usage_list[] = {
	"		Specifies the type of output formatting to be performed. The \
following <output-type> components are available:",
	"\n",
	"			o ASC[II]",
	"				For the 'ASCII' <output-type> component, some 'bare-bones' \
formatting is done. No special formatting such as bold-facing, italics, \
underlining, et cetera is available. 'ASCII' output is sent to 'stdout'.",
	"\n",
	"			o FRAME[[_]MAKER]",
	"				For the 'FRAME_MAKER' <output-type> component, a FrameMaker \
MIF is emitted to 'stdout'. Final FrameMaker formatting must be done by \
using all but the paragraph formats from an existing FrameMaker file.",
	"\n",
	"				Note the the 'FRAME_MAKER' <output-type> component is not \
supported at this time.",
	"\n",
	"			o HTML",
	"				For the 'HTML' <output-type> component, an HTML file is \
created with the formatting attributes available within the HTML subset \
of SGML. 'HTML' output is sent to the file specified by the combination \
of the '-OUTPUT_DIRECTORY=' parameter, the base name of the ADF comment \
entry, and the suffix '.html'.",
	"\n",
	"			o MAN[[_]PAGE]",
	"				For the 'MAN' <output-type> component, a man page is created \
with the formatting attributes available within the 'man' macro package. \
'MAN' output is sent to the file specified by the combination of the \
'-OUTPUT_DIRECTORY=' parameter, the first character of the man page section \
being created, the base name of the ADF comment entry, and a suffix \
consisting of the man page section being created.",
	"\n",
	"			o {POST[_]SCRIPT|PS}",
	"				For the 'POST_SCRIPT' <output-type> component, a PostScript \
file is created with the formatting attributes available using PostScript. \
'POST_SCRIPT' output is sent to the file specified by the combination \
of the '-OUTPUT_DIRECTORY=' parameter, the base name of the ADF comment \
entry, and the suffix '.ps'.",
	"\n",
	"			o {RICH_TEXT[_FORMAT]|RTF}",
	"				For the 'RICH_TEXT_FORMAT' <output-type> component, a file \
is created with the formatting attributes available using the Microsoft \
Rich Text Format. 'RICH_TEXT_FORMAT' output is sent to the file specified by \
the combination of the '-OUTPUT_DIRECTORY=' parameter, the base name of the \
ADF comment entry, and the suffix '.rtf'.",
	"\n",
	"		If this parameter is not specified, the program will use the \
'ASCII' output type.",
	"\n",
	NULL
};

	return(ADF_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_OUSE_ParseOutParam(const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text)
#else
int ADF_OUSE_ParseOutParam(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = ADF_OUSE_FRAME_ParseOutParam(base_arg_ptr,
		optional_flag, extra_usage_list, usage_count, usage_list,
		error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = ADF_OUSE_HTML_ParseOutParam(base_arg_ptr,
		optional_flag, extra_usage_list, usage_count, usage_list,
		error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = ADF_OUSE_MAN_ParseOutParam(base_arg_ptr,
		optional_flag, extra_usage_list, usage_count, usage_list,
		error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

