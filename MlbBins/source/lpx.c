/*T=3*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	H-P printer formatting for source code.

	Revision History	:	1990-07-01 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1990 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .															*/
/*	***********************************************************************	*/

#ifdef __MSDOS__
#include <io.h>								/* for 'isatty()' --- MSC 5.10	*/
#endif /* #ifdef __MSDOS__ */

#include <limits.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/types.h>						/* Not 'sys' on VAX */
#include <sys/stat.h>						/* Not 'sys' on VAX */

#include <strfuncs.h>

/*	***********************************************************************	*/

/* **************************
		NOTES:
			1)		Check 'isatty()' usage.
**************************	*/
/*
	@<file-name>												Read parameters from <file-name>
	-																Use stdin for input
	-reset														Reset to default settings
	-resetenv													Reset to environment settings
	-debug														Show current settings
	-help (or -h or -?)										Display help text
	-ts=<number>												Tab setting
	-of=<file-name>											Output file name
	-po={PORTRAIT|LANDSCAPE}								Page orientation
	-pt={EXEC|LETTER|LEGAL|A4|MONARC|COM-10|DL|C5}	Paper type
	-fn={COURIER|LINEPRINTER}								Font name
	-lm=<number>												Left-margin setting
	-rm=<number>												Right-margin setting
	-lp=<number>												Left-margin padding
	-rp=<number>												Right-margin padding
	-fp=<number>												First page number
	-fl=<number>												First line number
	-cc={ON|OFF}												Use C code defaults
	-cp={ON|OFF}												Continuous page numbering
	-cl={ON|OFF}												Continuous line numbering
	-hf={ON|OFF}												Page header & footer toggle
	-ph={ON|OFF}												Page header toggle
	-pf={ON|OFF}												Page footer toggle
	-ln={ON|OFF}												Line numbering
	-li={ON|OFF}												Line intepretation
	-bh={ON|OFF}												Bold headers
	-bf={ON|OFF}												Bold footers
	-bl={ON|OFF}												Bold line numbers
	-bt={ON|OFF}												Bold text
	-ub={ON|OFF}												Use bold-face (bh,bf,bl)
	-cc={ON|OFF}												Use C code defaults
*/
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Manifest constants used by this program . . .								*/
/*	***********************************************************************	*/

#define CODE_FALSE							0
#define CODE_TRUE								1

#define CODE_SUCCESS							0
#define CODE_FAILURE							-1
#define CODE_EXIT								1

#define PRT_NOT_FOUND						0
#define PRT_FOUND								1
#define PRT_ADD_ERROR						2

/*
1234567890123456789012345678901234567890
*/

#define PRT_MAXIMUM_ROW_COUNT				256
#define PRT_MAXIMUM_COL_COUNT				1024

#define PRT_ORIENTATION_PORTRAIT			0
#define PRT_ORIENTATION_LANDSCAPE		1
#define PRT_ORIENTATION_DEFAULT			PRT_ORIENTATION_PORTRAIT

#define PRT_PAPER_TYPE_DEFAULT			1

#define PRT_FONT_NAME_DEFAULT				1

#define PRT_TAB_SETTING_MINIMUM			1.0
#define PRT_TAB_SETTING_MAXIMUM			20.0
#define PRT_TAB_SETTING_DEFAULT			8
#define PRT_TAB_SETTING_DEFAULT_C		3

#define PRT_MARGIN_MINIMUM					0
#define PRT_MARGIN_MAXIMUM					20
#define PRT_MARGIN_LEFT_DEFAULT_C		10
#define PRT_MARGIN_RIGHT_DEFAULT_C		10

#define PRT_PADDING_MINIMUM				0
#define PRT_PADDING_MAXIMUM				20
#define PRT_PADDING_LEFT_DEFAULT_C		5
#define PRT_PADDING_RIGHT_DEFAULT_C		5

#define PRT_PAGE_NUMBER_MINIMUM			((double) ((unsigned long) 0L))
#define PRT_PAGE_NUMBER_MAXIMUM			((double) ((unsigned long) LONG_MAX))

#define PRT_LINE_NUMBER_MINIMUM			((double) ((unsigned long) 0L))
#define PRT_LINE_NUMBER_MAXIMUM			((double) ((unsigned long) LONG_MAX))
#define PRT_LINE_NUMBER_LENGTH			13
#define PRT_LINE_NUMBER_FORMAT			"%010lu   "

#define PRT_INPUT_BUFFER_SIZE				2048

#define PRT_SINGLE_POINT_SIZE				(1.0 / 72.0)

#define PRT_HELP_TEXT_LINE_LENGTH		78

#define PRT_ENVIRONMENT_NAME				"PRT_SETTINGS"

#define PRT_ENVIRONMENT_DONE				"*** PRT_SETTINGS DONE ***"

/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Structures used by this program . . .											*/
/*	***********************************************************************	*/

typedef struct {
	char          *in_file_name;
	char          *out_file_name;
	FILE          *in_file_ptr;
	FILE          *out_file_ptr;
	char          *page_footer_format;
	int            page_orientation;
	int            paper_type;
	int            font_name;
	int            tab_setting;
	unsigned long  first_page_number;
	unsigned long  first_line_number;
	unsigned long  current_page_number;
	unsigned long  current_line_number;
	int            current_row;
	int            current_col;
	int            actual_page_rows;
	unsigned int   actual_page_cols;
	int            working_page_rows;
	int            working_page_cols;
	unsigned int   left_margin;
	int            right_margin;
	unsigned int   left_padding;
	int            right_padding;
	int            cont_page_number_flag;
	int            cont_line_number_flag;
	int            page_header_flag;
	int            page_footer_flag;
	int            line_number_flag;
	int            line_interpret_flag;
	int            bold_header_flag;
	int            bold_footer_flag;
	int            bold_line_number_flag;
	int            bold_text_flag;
	int            first_page_flag;
	int            last_page_flag;
} PRT_CONTROL_ITEM;

typedef struct {
	char   *paper_name;
	char   *paper_long_name;
	double  paper_width;
	double  paper_length;
	char   *paper_command;
} PRT_PAPER_TYPE_ITEM;

typedef struct {
	char *orientation_name;
	char *orientation_command;
} PRT_ORIENTATION_ITEM;

typedef struct {
	char   *font_name;
	double  font_CPI;
	double  font_HMI;
	double  font_points;					/* One point = 1/72 inch = .01388889	*/
	double  font_LPI;
	char   *font_command;
} PRT_FONT_NAME_ITEM;

/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Data used within this module . . .												*/
/*	***********************************************************************	*/

static char PRT_FooterBuffer[PRT_MAXIMUM_COL_COUNT + 1];

static const PRT_PAPER_TYPE_ITEM PRT_PaperTypeList[] = {
	{	"EXEC",		"Executive",			 7.250,	10.500	,	"\033&l1A"	},
	{	"LETTER",	"Letter",				 8.500,	11.000	,	"\033&l2A"	},
	{	"LEGAL",		"Legal",					 8.500,	14.000	,	"\033&l3A"	},
	{	"A4",			"A4",						 8.268,	11.693	,	"\033&l26A"	},
	{	"MONARC",	"Monarch",				 3.875,	 7.500	,	"\033&l80A"	},
	{	"COM-10",	"Commercial 10",		 4.125,	 9.500	,	"\033&l81A"	},
	{	"DL",			"International DL",	 4.331,	 8.661	,	"\033&l90A"	},
	{	"C5",			"International C5",	 6.378,	 9.016	,	"\033&l91A"	},
};

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		RESET PRINTER COMMAND														*/
	/*		CLEAR MARGIN																	*/
	/*		PUSH POSITION																	*/
	/*		PRIMARY SYMBOL SET    = IBM-PC (USA)									*/
	/*		PRIMARY SPACING       = FIXED												*/
	/*		PRIMARY STYLE         = UPRIGHT											*/
	/*		PRIMARY STROKE WEIGHT = MEDIUM											*/
	/*		UNDERLINE             = OFF												*/
	/*		END-OF-LINE-WRAP      = DISABLED											*/
	/*		NUMBER OF COPIES      = 1													*/
	/*		PERFORATION SKIP      = ENABLED											*/
	/*		LINE TERMINATION      = CR=CR, LF=LF, and FF=FF						*/
	/*		POP POSITION																	*/
	/*	*****************************************************************	*/
/*
	ADF NOTE: MS VC++ 6.x reports:
		warning C4125: decimal digit terminates octal escape sequence
static const char *GenericString     =
"\033E\0339\033&f0S\033(10U\033(s0P\033(s0S\033(s0B\033&d@\033&s1C\033&l1X\033&l1L\033&k0G\033&f1S";
*/
static const char *GenericString     =
"\033E\033\0x39\033&f0S\033(10U\033(s0P\033(s0S\033(s0B\033&d@\033&s1C\033&l1X\033&l1L\033&k0G\033&f1S";

static const PRT_ORIENTATION_ITEM PRT_OrientationList[] = {
	{	"PORTRAIT",		"\033&l0O"	},
	{	"LANDSCAPE",	"\033&l1O"	}
};

static const PRT_FONT_NAME_ITEM   PRT_FontNameList[] = {
	{	"COURIER",		10.00,	.12000000000000000,	12.00,	6.0,
		"\033(s10.00H\033(s10.0V\033(s3T\033&l6D"	},
	{	"LINEPRINTER",	16.66,	.07202881152460984,	 8.50,	8.0,
		"\033(s16.66H\033(s08.5V\033(s0T\033&l8D"	}
};

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		PRIMARY PITCH                       = 10 CHARACTERS/INCH			*/
	/*		PRIMARY POINT SIZE                  = 10 POINT						*/
	/*		PRIMARY TYPEFACE                    = COURIER						*/
	/*		PRIMARY VERTICAL MOTION INDEX (VMI) = 6 LINES/INCH					*/
	/*	*****************************************************************	*/
static const char *CourierString     =
	"\033(s10.00H\033(s10.0V\033(s3T\033&l6D";

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		PRIMARY PITCH                       = 16.66 CHARACTERS/INCH		*/
	/*		PRIMARY POINT SIZE                  = 8.5 POINT						*/
	/*		PRIMARY TYPEFACE                    = LINEPRINTER					*/
	/*		PRIMARY VERTICAL MOTION INDEX (VMI) = 8 LINES/INCH					*/
	/*	*****************************************************************	*/
static const char *LineprinterString =
	"\033(s16.66H\033(s08.5V\033(s0T\033&l8D";

static const char *DocText[] = {
	"    HPF files are named in accordance with the following scheme:",
	" ",
	"      <orientation-specifier><font-specifier><attribute-specifier>.HPF",
	" ",
	" where the components have the following meanings:",
	" ",
	"    o <orientation-specifier> is one of the following:",
	"        o 'P' (for 'portrait')",
	"        o 'L' (for 'landscape')",
	" ",
	"    o <font-specifier> is one of the following:",
	"        o 'C' (for 'courier')",
	"        o 'L' (for 'lineprinter')",
	" ",
	"    o <attribute-specifier> is either one the eight paper types",
	"      supported by the LaserJet Series II:",
	" ",
	"        o 'EXEC'   (for 'Executive'),        size  7.250\" X 10.500\"",
	"        o 'LETTER' (for 'Letter'),           size  8.500\" X 11.000\"",
	"        o 'LEGAL'  (for 'Legal'),            size  8.500\" X 14.000\"",
	"        o 'A4'     (for 'A4'),               size  8.268\" X 11.693\"",
	"        o 'MONARC' (for 'Monarch'),          size  3.875\" X  7.500\"",
	"        o 'COM-10' (for 'Commercial 10'),    size  4.125\" X  9.500\"",
	"        o 'DL'     (for 'International DL'), size  4.331\" X  8.661\"",
	"        o 'C5'     (for 'International C5'), size  6.378\" X  9.016\"",
	" ",
	"      or one of the fonts modified for Phillip Brothers, Incorporated",
	"      to fit more characters on a line:",
	" ",
	"        o 'PBI08'  (Courier font allowing 119 characters per line",
	"          in portrait mode, and 158 characters per line in landscape",
	"          mode",
	"        o 'PBI09'  (Courier font allowing 106 characters per line",
	"          in portrait mode, and 141 characters per line in landscape",
	"          mode",
	"        o 'PBI06'  (Lineprinter font allowing 159 characters per line",
	"          in portrait mode, and 211 characters per line in landscape",
	"          mode",
	"        o 'PBI07'  (Lineprinter font allowing 137 characters per line",
	"          in portrait mode, and 181 characters per line in landscape",
	"          mode",
	" ",
	"      Note that other members of the HP LaserJet printer family may",
	"      handle paper sizes not included in the above list.  For example,",
	"      the top-of-the-line HP LaserJet 2000 handles 11\" X 17\" paper.",
	" ",
	" ",
};

/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static const char *HelpText[] = {
" ",
" ",
"   Usage:",
"   ------",
" ",
"      lp [<a mixture of '-' options, '@' commands, and filenames>]",
" ",
" ",
"   Description:",
"   ------------",
"		This program provides a formatted printing facility designed \
primarily for the printing of C source code on Hewlett-Packard \
LaserJet printers and compatibles.  It is, however, sufficiently \
flexible to permit its use with other types of input files and \
output devices.",
" ",
"		Invocation of the program may include any number of parameters \
which may be used to specify the nature of the resulting output. \
There are three types of parameters:",
" ",
"		o  '-'-prefaced options, which specify any one of a number of \
options (which are described in the 'Options', below);",
" ",
"		o  '@'-prefaced file names, which indicate that the indicated \
file name is to be parsed for parameters, and;",
" ",
"		o  all parameters not prefaced with '-' or '@', which are \
taken to be the names of files to be read for input.",
" ",
" ",
"   Operation:",
"   ----------",
"		Program operation is as follows:",
" ",
"		o  The program initializes itself to the default settings (these \
are the same settings described in the 'Options' section \
under the description of the '-reset' parameter).",
" ",
"		o  The environment is searched for an environment variable with \
the name 'PRT_SETTINGS' (under VMS, the symbol table is \
searched).  If found, the program sets itself to each option \
in the environment string, where the options are separated by \
whitespace.",
" ",
"		o  The command line is scanned for options.",
" ",
"		Every time a valid parameter is encountered, it immediately \
becomes active.  Thus it is possible to print multiple files with \
different settings, simply by interleaving the appropriate parameters \
in the correct order",
" ",
"		If an '@' option is encountered, the indicated file is read \
as if its lines had been placed on the command line UNLESS the \
indicated file is in the current hierarchy of '@' files, in which \
case it is ignored.  Similarly, requests to re-read the environment \
settings (by use of the '-resetenv' parameter) will be ignored if \
the said request is in a hierarchy descended from '-resetenv'.",
" ",
"		Command files may, however, be read more than once, so long as \
no invocation of a particular command file results in the invocation \
of itself.",
" ",
" ",
"   Options:",
"   --------",
"      -",
"		Use stdin for input.  This is the default setting before any file \
names are encountered on the command line and after a '-reset' \
specification.",
" ",
"      -reset",
"		Resets the state of the program to the default settings, as follow:",
" ",
"			o  output device is 'stdout'",
"			o  input device is 'stdin'",
"			o  -ts=8",
"			o  -po=PORTRAIT",
"			o  -pt=LETTER",
"			o  -fn=LINEPRINTER",
"			o  -lm=0",
"			o  -rm=0",
"			o  -lp=0",
"			o  -rp=0",
"			o  -fp=1",
"			o  -fl=1",
"			o  -cp=OFF",
"			o  -cl=OFF",
"			o  -ph=OFF",
"			o  -pf=OFF",
"			o  -ln=OFF",
"			o  -li=OFF",
"			o  -bh=OFF",
"			o  -bf=OFF",
"			o  -bl=OFF",
"			o  -bt=OFF",
" ",
"      -resetenv",
"		Sets the state of the program to the settings described within the \
environment variable 'PRT_SETTINGS'.  No error is registered if this \
variable is not in the environment.  See the section 'Environment' \
below for a description of how to set parameters using environment \
variable.",
" ",
"      -debug",
"		Shows the current settings, after which the program will return \
to the operating system.",
" ",
"      -help",
"		Display help text --- displays this text.  You may also request \
help by using '-h' or '-?'.  After the help text is printed, the \
program will return to the operating system.",
" ",
"      -ts=<number>",
"		Sets the tab expansion setting to the specified number, which must \
be in the range of 1 through 20, inclusive.  The default value for \
this setting is 8.",
" ",
"      -of=<file-name>",
"		Specifies the destination for output.  The default for output is, \
of course, 'stdout'.  To return to the use of 'stdout' after using \
this parameter, specify '-of=' without a file name.",
" ",
"      -po={PORTRAIT|LANDSCAPE}",
"		Specifies the page orientation",
" ",
"      -pt={EXEC|LETTER|LEGAL|A4|MONARC|COM-10|DL|C5}",
"		Specifies the paper type to be used for output.  The paper types \
supported at this time are as follow:",
" ",
"			o 'EXEC'   (for 'Executive'),        size  7.250\" X 10.500\"",
"			o 'LETTER' (for 'Letter'),           size  8.500\" X 11.000\"",
"			o 'LEGAL'  (for 'Legal'),            size  8.500\" X 14.000\"",
"			o 'A4'     (for 'A4'),               size  8.268\" X 11.693\"",
"			o 'MONARC' (for 'Monarch'),          size  3.875\" X  7.500\"",
"			o 'COM-10' (for 'Commercial 10'),    size  4.125\" X  9.500\"",
"			o 'DL'     (for 'International DL'), size  4.331\" X  8.661\"",
"			o 'C5'     (for 'International C5'), size  6.378\" X  9.016\"",
" ",
"		Note that other members of the HP LaserJet printer family may handle \
paper sizes not included in the above list.  For example, the top-of- \
the-line HP LaserJet 2000 handles 11\" X 17\" paper.",
" ",
"      -fn={COURIER|LINEPRINTER}",
"		Font name",
" ",
"      -lm=<number>",
"		Left-margin setting",
" ",
"      -rm=<number>",
"		Right-margin setting",
" ",
"      -lp=<number>",
"		Left-margin padding",
" ",
"      -rp=<number>",
"		Right-margin padding",
" ",
"      -fp=<number>",
"		First page number",
" ",
"      -fl=<number>",
"		First line number",
" ",
"      -cp={ON|OFF}",
"		Continuous page numbering",
" ",
"      -cl={ON|OFF}",
"		Continuous line numbering",
" ",
"      -hf={ON|OFF}",
"		Page header & footer toggle",
" ",
"      -ph={ON|OFF}",
"		Page header toggle",
" ",
"      -pf={ON|OFF}",
"		Page footer toggle",
" ",
"      -ln={ON|OFF}",
"		Line numbering",
" ",
"      -li={ON|OFF}",
"		Line intepretation",
" ",
"      -bh={ON|OFF}",
"		Use bold face headers (if the '-ph' flag is 'ON').",
" ",
"      -bf={ON|OFF}",
"		Use bold face footers (if the '-pf' flag is 'ON').",
" ",
"      -bl={ON|OFF}",
"		Use bold face line numbers (if the '-ln' flag is 'ON').",
" ",
"      -bt={ON|OFF}",
"		Use bold face text.",
" ",
"      -ub={ON|OFF}",
"		Use bold-face headers, footers, and line numbers only.",
" ",
"      -cc={ON|OFF}",
"		Use C source code defaults for printing.  The defaults for printing \
C source code are as follow:",
" ",
"			o  -ts=3",
"			o  -po=PORTRAIT",
"			o  -pt=LETTER",
"			o  -fn=LINEPRINTER",
"			o  -lm=10",
"			o  -rm=10",
"			o  -lp=5",
"			o  -rp=5",
"			o  -fp=1",
"			o  -fl=1",
"			o  -cp=OFF",
"			o  -cl=OFF",
"			o  -ph=ON",
"			o  -pf=ON",
"			o  -ln=ON",
"			o  -li=ON",
"			o  -bh=ON",
"			o  -bf=ON",
"			o  -bl=ON",
"			o  -bt=OFF",
" ",
""
};

/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions within this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL(int  main,
	(int, char **));
COMPAT_FN_DECL_STATIC(int  PRT_ParseParams,
	(PRT_CONTROL_ITEM *, int, char **, unsigned int *, char ***, char *));
COMPAT_FN_DECL_STATIC(int  PRT_GetParamsFromFile,
	(PRT_CONTROL_ITEM *, char *, unsigned int *, char ***, char *));
COMPAT_FN_DECL_STATIC(int  PRT_GetParamsFromEnviron,
	(PRT_CONTROL_ITEM *, unsigned int *, char ***, char *));
COMPAT_FN_DECL_STATIC(int  PRT_GetParamsFromString,
	(PRT_CONTROL_ITEM *, char *, unsigned int *, char ***, char *));
COMPAT_FN_DECL_STATIC(int  PRT_FindParsedItem,
	(char *, unsigned int *, char ***, unsigned int *, char *));
COMPAT_FN_DECL_STATIC(void PRT_DebugShowControl,
	(PRT_CONTROL_ITEM *));
COMPAT_FN_DECL_STATIC(int  PRT_SetDefaults,
	(PRT_CONTROL_ITEM *, char *));
COMPAT_FN_DECL_STATIC(int  PRT_SetCDefaults,
	(PRT_CONTROL_ITEM *, char *));
COMPAT_FN_DECL_STATIC(int  PRT_SetParameters,
	(PRT_CONTROL_ITEM *, char *));
COMPAT_FN_DECL_STATIC(int  PRT_SetFooter,
	(PRT_CONTROL_ITEM *, char *));
COMPAT_FN_DECL_STATIC(int  PRT_EmitFile,
	(PRT_CONTROL_ITEM *, char *));
COMPAT_FN_DECL_STATIC(void PRT_DoLinePreface,
	(PRT_CONTROL_ITEM *, int, char *, char **));
COMPAT_FN_DECL_STATIC(void PRT_DoLine,
	(PRT_CONTROL_ITEM *, char *, char *, char *));
COMPAT_FN_DECL_STATIC(void PRT_LineControl,
	(PRT_CONTROL_ITEM *));
COMPAT_FN_DECL_STATIC(void PRT_PageControl,
	(PRT_CONTROL_ITEM *));
COMPAT_FN_DECL_STATIC(void PRT_DoBold,
	(PRT_CONTROL_ITEM *, char *));
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int                return_code = CODE_SUCCESS;
	unsigned int       parse_count = 0;
	char             **parse_list  = NULL;
	char              *node        = argv[0];
	char               error_text[512 + 1];
	char               buffer[512 + 1];
	PRT_CONTROL_ITEM   control_data;

#ifdef VMS
	node = (strrchr(node, ']')) ? strrchr(node, ']') + 1 : node;
#endif /* #ifdef VMS */
#if VMS || MSDOS
	node = (strrchr(node, ':')) ? strrchr(node, ':') + 1 : node;
# ifdef MSDOS
	node = (strrchr(node, '\\')) ? strrchr(node, '\\') + 1 : node;
# endif /* # ifdef MSDOS */
	if (strrchr(node, '.'))
		*(strrchr(node, '.')) = '\0';
#else /* We assume UNIX here . . . */
	node = (strrchr(node, '/')) ? strrchr(node, '/') + 1 : node;
#endif /* #ifdefn VMS || MSDOS */

	if ((return_code = PRT_SetDefaults(&control_data, buffer)) !=
		CODE_SUCCESS)
		sprintf(error_text, "Error setting control data elements:\n>>> %s\n",
			error_text);
	else if ((return_code = PRT_GetParamsFromEnviron(&control_data,
		&parse_count, &parse_list, buffer)) != CODE_SUCCESS)
		sprintf(error_text,
			"Error getting parameters from environment variable '%s':\n>>> %s",
			PRT_ENVIRONMENT_NAME, buffer);
	else if ((return_code = PRT_ParseParams(&control_data, argc - 1, argv + 1,
		&parse_count, &parse_list, error_text)) == CODE_SUCCESS) {
		if ((control_data.in_file_ptr == stdin) && (!feof(stdin))) {
			if ((return_code = PRT_EmitFile(&control_data, buffer)) !=
				CODE_SUCCESS)
				sprintf(error_text,
					"Error emitting data from 'stdin':\n>>> %s\n", buffer);
		}
	}

	if (control_data.in_file_ptr != stdin)
		fclose(control_data.in_file_ptr);
	if (control_data.out_file_ptr != stdout)
		fclose(control_data.out_file_ptr);

	if (return_code == CODE_FAILURE)
		fprintf(stderr, "\n\n%s: %s\n", node, error_text);

	return((return_code == CODE_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static int PRT_ParseParams(PRT_CONTROL_ITEM *control_ptr, int argc, char **argv,
	unsigned int *parse_count, char ***parse_list, char *error_text)
#else
static int PRT_ParseParams(control_ptr, argc, argv, parse_count, parse_list,
	error_text)
PRT_CONTROL_ITEM   *control_ptr;
int                 argc;
char              **argv;
unsigned int       *parse_count;
char             ***parse_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code = CODE_SUCCESS;
	int   count_1;
	int   count_2;
	int   current_row;
	const char *tmp_ptr    = NULL;
	int  *int_ptr    = NULL;
	char  buffer[512 + 1];

	int   current_col = 0;
	int   tab_count   = 0;
	char  last_char;

	for (count_1 = 0; count_1 < argc; count_1++) {
		if (argv[count_1][0] == '@') {
			if (!argv[count_1][1]) {
				sprintf(error_text, "File name parameter expected after '@'.");
				return_code = CODE_FAILURE;
				break;
			}
			if ((return_code = PRT_GetParamsFromFile(control_ptr,
				argv[count_1] + 1, parse_count, parse_list, error_text)) !=
				CODE_SUCCESS)
				break;
		}
		else if (argv[count_1][0] == '-') {
			if ((!stricmp(argv[count_1], "?"))  ||
				 (!stricmp(argv[count_1], "-?")) ||
				 (!stricmp(argv[count_1], "-h")) ||
				 (!stricmp(argv[count_1], "-help"))) {
				count_2     = 0;
				current_row = 0;
				while (HelpText[count_2][0]) {
					if (!tmp_ptr) {
						tmp_ptr     = HelpText[count_2++];
						current_col = 0;
					}
					if ((tmp_ptr = strwrap(tmp_ptr, &current_col, 77, &tab_count,
						3, 1, &last_char, buffer)) == NULL)
						continue;
					printf("%s\n", buffer);
					if ((++current_row == 23) && HelpText[count_2][0]) {
						printf("*** MORE ***");
						fgetc(stdin);
						printf("\033[2J");
						current_row = 0;
					}
				}
#if 0
				count_2     = 0;
				current_row = 0;
				while (HelpText[count_2][0]) {
					printf("%s\n", HelpText[count_2++]);
/*
					if ((++current_row == 23) && HelpText[count_2][0] &&
						isatty(stdout)) {
*/
					if ((++current_row == 23) && HelpText[count_2][0]) {
						printf("*** MORE ***");
						fgetc(stdin);
						printf("\033[2J");
						current_row = 0;
					}
				}
#endif /* #if 0 */
				return_code = CODE_EXIT;
				break;
			}
			else if (!stricmp(argv[count_1], "-debug")) {
				PRT_DebugShowControl(control_ptr);
				return_code = CODE_EXIT;
				break;
			}
			else if (!strcmp(argv[count_1], "-")) {
				if (control_ptr->in_file_ptr != stdin)
					fclose(control_ptr->in_file_ptr);
				if (control_ptr->out_file_ptr != stdout)
					fclose(control_ptr->out_file_ptr);
				if ((PRT_SetDefaults(control_ptr, buffer)) != CODE_SUCCESS) {
					sprintf(error_text,
						"Error setting control data elements:\n>>> %s", buffer);
					break;
				}
				if ((return_code = PRT_EmitFile(control_ptr, buffer)) !=
					CODE_SUCCESS) {
					fclose(control_ptr->in_file_ptr);
					sprintf(error_text,
						"Error emitting data from 'stdin':\n>>> %s", buffer);
					break;
				}
			}
			else if (!stricmp(argv[count_1], "-reset")) {
				if (control_ptr->in_file_ptr != stdin)
					fclose(control_ptr->in_file_ptr);
				if (control_ptr->out_file_ptr != stdout)
					fclose(control_ptr->out_file_ptr);
				if ((PRT_SetDefaults(control_ptr, buffer)) != CODE_SUCCESS) {
					sprintf(error_text,
						"Error setting control data elements:\n>>> %s", buffer);
					break;
				}
			}
			else if (!stricmp(argv[count_1], "-resetenv")) {
				if ((return_code = PRT_GetParamsFromEnviron(control_ptr,
					parse_count, parse_list, buffer)) != CODE_SUCCESS) {
					sprintf(error_text,
			"Error getting parameters from environment variable '%s':\n>>> %s",
						PRT_ENVIRONMENT_NAME, buffer);
					break;
				}
			}
			else if (!strnicmp(argv[count_1], "-ts=", 4)) {
				if ((atof(argv[count_1] + 4) < PRT_TAB_SETTING_MINIMUM) ||
					(atof(argv[count_1] + 4) > PRT_TAB_SETTING_MAXIMUM)) {
					sprintf(error_text, "%s (%.0f) is %s than the %s (%.0f).",
						"The requested tab setting", atof(argv[count_1]),
						(atof(argv[count_1] + 4) < PRT_TAB_SETTING_MINIMUM) ?
						"less" : "greater",
						(atof(argv[count_1] + 4) < PRT_TAB_SETTING_MINIMUM) ?
						"minimum" : "maximum",
						(atof(argv[count_1] + 4) < PRT_TAB_SETTING_MINIMUM) ?
						PRT_TAB_SETTING_MINIMUM : PRT_TAB_SETTING_MAXIMUM);
					return_code = CODE_FAILURE;
					break;
				}
				control_ptr->tab_setting = atoi(argv[count_1] + 4);
			}
			else if (!strnicmp(argv[count_1], "-of=", 4)) {
				if (control_ptr->out_file_ptr != stdout)
					fclose(control_ptr->out_file_ptr);
				if (!argv[count_1][4]) {
					control_ptr->out_file_name = "stdout";
					control_ptr->out_file_ptr  = stdout;
				}
				else if ((control_ptr->out_file_ptr =
					fopen(argv[count_1] + 4, "w")) == NULL) {
					sprintf(error_text, "Error opening output file '%s'.",
						argv[count_1] + 4);
					return_code = CODE_FAILURE;
					break;
				}
				else
					control_ptr->out_file_name = argv[count_1] + 4;
			}
			else if (!strnicmp(argv[count_1], "-po=", 4)) {
				return_code = CODE_FAILURE;
				for (count_2 = 0; count_2 <
					(sizeof(PRT_OrientationList) / sizeof(PRT_OrientationList[0]));
					count_2++) {
					if (!stricmp(argv[count_1] + 4,
						PRT_OrientationList[count_2].orientation_name)) {
						return_code = CODE_SUCCESS;
						break;
					}
				}
				if (return_code != CODE_SUCCESS) {
					sprintf(error_text,
						"Invalid page orientation specification ('%s').",
						argv[count_1]);
					break;
				}
				control_ptr->page_orientation = count_2;
			}
			else if (!strnicmp(argv[count_1], "-pt=", 4)) {
				return_code = CODE_FAILURE;
				for (count_2 = 0; count_2 <
					(sizeof(PRT_PaperTypeList) / sizeof(PRT_PaperTypeList[0]));
					count_2++) {
					if (!stricmp(argv[count_1] + 4,
						PRT_PaperTypeList[count_2].paper_name)) {
						return_code = CODE_SUCCESS;
						break;
					}
				}
				if (return_code != CODE_SUCCESS) {
					sprintf(error_text,
						"Invalid paper type specification ('%s').",
						argv[count_1]);
					break;
				}
				control_ptr->paper_type = count_2;
			}
			else if (!strnicmp(argv[count_1], "-fn=", 4)) {
				return_code = CODE_FAILURE;
				for (count_2 = 0; count_2 <
					(sizeof(PRT_FontNameList) / sizeof(PRT_FontNameList[0]));
					count_2++) {
					if (!stricmp(argv[count_1] + 4,
						PRT_FontNameList[count_2].font_name)) {
						return_code = CODE_SUCCESS;
						break;
					}
				}
				if (return_code != CODE_SUCCESS) {
					sprintf(error_text,
						"Invalid font name specification ('%s').",
						argv[count_1]);
					break;
				}
				control_ptr->font_name = count_2;
			}
			else if (!strnicmp(argv[count_1], "-lm=", 4)) {
				if ((atol(argv[count_1] + 4) < ((long) PRT_MARGIN_MINIMUM)) ||
					(atol(argv[count_1] + 4) > ((long) PRT_MARGIN_MAXIMUM))) {
					sprintf(error_text,
						"%s ('%s') --- range is %u to %u, inclusive.",
						"Invalid left margin count", argv[count_1],
						PRT_MARGIN_MINIMUM, PRT_MARGIN_MAXIMUM);
					return_code = CODE_FAILURE;
					break;
				}
				control_ptr->left_margin = atoi(argv[count_1] + 4);
			}
			else if (!strnicmp(argv[count_1], "-rm=", 4)) {
				if ((atol(argv[count_1] + 4) < ((long) PRT_MARGIN_MINIMUM)) ||
					(atol(argv[count_1] + 4) > ((long) PRT_MARGIN_MAXIMUM))) {
					sprintf(error_text,
						"%s ('%s') --- range is %u to %u, inclusive.",
						"Invalid right margin count", argv[count_1],
						PRT_MARGIN_MINIMUM, PRT_MARGIN_MAXIMUM);
					return_code = CODE_FAILURE;
					break;
				}
				control_ptr->right_margin = atoi(argv[count_1] + 4);
			}
			else if (!strnicmp(argv[count_1], "-lp=", 4)) {
				if ((atol(argv[count_1] + 4) < ((long) PRT_PADDING_MINIMUM)) ||
					(atol(argv[count_1] + 4) > ((long) PRT_PADDING_MAXIMUM))) {
					sprintf(error_text,
						"%s ('%s') --- range is %u to %u, inclusive.",
						"Invalid left text padding count", argv[count_1],
						PRT_PADDING_MINIMUM, PRT_PADDING_MAXIMUM);
					return_code = CODE_FAILURE;
					break;
				}
				control_ptr->left_padding = atoi(argv[count_1] + 4);
			}
			else if (!strnicmp(argv[count_1], "-rp=", 4)) {
				if ((atol(argv[count_1] + 4) < ((long) PRT_PADDING_MINIMUM)) ||
					(atol(argv[count_1] + 4) > ((long) PRT_PADDING_MAXIMUM))) {
					sprintf(error_text,
						"%s ('%s') --- range is %u to %u, inclusive.",
						"Invalid right text padding count", argv[count_1],
						PRT_PADDING_MINIMUM, PRT_PADDING_MAXIMUM);
					return_code = CODE_FAILURE;
					break;
				}
				control_ptr->right_padding = atoi(argv[count_1] + 4);
			}
			else if (!strnicmp(argv[count_1], "-fp=", 4)) {
				if ((atof(argv[count_1] + 4) < PRT_PAGE_NUMBER_MINIMUM) ||
					(atof(argv[count_1] + 4) > PRT_PAGE_NUMBER_MAXIMUM)) {
					sprintf(error_text,
						"%s (%.0f) --- range is %.0f to %.0f, inclusive.",
						"Invalid first page number", atof(argv[count_1] + 4),
						PRT_PAGE_NUMBER_MINIMUM, PRT_PAGE_NUMBER_MAXIMUM);
					return_code = CODE_FAILURE;
					break;
				}
				control_ptr->first_page_number =
					((unsigned long) atof(argv[count_1] + 4));
			}
			else if (!strnicmp(argv[count_1], "-fl=", 4)) {
				if ((atof(argv[count_1] + 4) < PRT_LINE_NUMBER_MINIMUM) ||
					(atof(argv[count_1] + 4) > PRT_LINE_NUMBER_MAXIMUM)) {
					sprintf(error_text,
						"%s (%.0f) --- range is %.0f to %.0f, inclusive.",
						"Invalid first line number", atof(argv[count_1] + 4),
						PRT_LINE_NUMBER_MINIMUM, PRT_LINE_NUMBER_MAXIMUM);
					return_code = CODE_FAILURE;
					break;
				}
				control_ptr->first_line_number =
					((unsigned long) atof(argv[count_1] + 4));
			}
			else if ((!stricmp(argv[count_1], "-cc=ON"))  ||
				(!stricmp(argv[count_1],       "-cc=YES")) ||
				(!stricmp(argv[count_1],       "-cc=TRUE"))) {
				if ((return_code = PRT_SetCDefaults(control_ptr, buffer)) !=
					CODE_SUCCESS) {
					sprintf(error_text, "%s:\n>>> %s",
						"Error setting parameters for C source files", buffer);
					break;
				}
			}
			else if ((!stricmp(argv[count_1], "-cc=OFF")) ||
				(!stricmp(argv[count_1],       "-cc=NO"))  ||
				(!stricmp(argv[count_1],       "-cc=FALSE")))
				;							/* Do nothing --- params remain in effect	*/
			else if ((!stricmp(argv[count_1], "-hf=ON"))  ||
				(!stricmp(argv[count_1],       "-hf=YES")) ||
				(!stricmp(argv[count_1],       "-hf=TRUE"))) {
				control_ptr->page_header_flag = CODE_TRUE;
				control_ptr->page_footer_flag = CODE_TRUE;
			}
			else if ((!stricmp(argv[count_1], "-hf=OFF")) ||
				(!stricmp(argv[count_1],       "-hf=NO"))  ||
				(!stricmp(argv[count_1],       "-hf=FALSE"))) {
				control_ptr->page_header_flag = CODE_FALSE;
				control_ptr->page_footer_flag = CODE_FALSE;
			}
			else if ((!stricmp(argv[count_1], "-ub=ON"))  ||
				(!stricmp(argv[count_1],       "-ub=YES")) ||
				(!stricmp(argv[count_1],       "-ub=TRUE"))) {
				control_ptr->bold_header_flag      = CODE_TRUE;
				control_ptr->bold_footer_flag      = CODE_TRUE;
				control_ptr->bold_line_number_flag = CODE_TRUE;
				control_ptr->bold_text_flag        = CODE_FALSE;
			}
			else if ((!stricmp(argv[count_1], "-ub=OFF")) ||
				(!stricmp(argv[count_1],       "-ub=NO"))  ||
				(!stricmp(argv[count_1],       "-ub=FALSE"))) {
				control_ptr->bold_header_flag      = CODE_FALSE;
				control_ptr->bold_footer_flag      = CODE_FALSE;
				control_ptr->bold_line_number_flag = CODE_FALSE;
				control_ptr->bold_text_flag        = CODE_FALSE;
			}
			else if (((count_2 =
				idxistrn("-cp=-cl=-ph=-pf=-ln=-li=-bh=-bf=-bl=-bt=",
				argv[count_1], 4)) > -1) && (!(count_2 % 4))) {
				count_2 /= 4;
 				int_ptr = (!count_2) ? &control_ptr->cont_page_number_flag :
					(count_2 == 1) ? &control_ptr->cont_line_number_flag :
					(count_2 == 2) ? &control_ptr->page_header_flag      :
					(count_2 == 3) ? &control_ptr->page_footer_flag      :
					(count_2 == 4) ? &control_ptr->line_number_flag      :
					(count_2 == 5) ? &control_ptr->line_interpret_flag   :
					(count_2 == 6) ? &control_ptr->bold_header_flag      :
					(count_2 == 7) ? &control_ptr->bold_footer_flag      :
					(count_2 == 8) ? &control_ptr->bold_line_number_flag :
					&control_ptr->bold_text_flag;
				if ((!stricmp(argv[count_1] + 4, "ON")) ||
					(!stricmp(argv[count_1] + 4, "YES")) ||
					(!stricmp(argv[count_1] + 4, "TRUE")))
					*int_ptr = CODE_TRUE;
				else if ((!stricmp(argv[count_1] + 4, "OFF")) ||
					(!stricmp(argv[count_1] + 4, "NO")) ||
					(!stricmp(argv[count_1] + 4, "FALSE")))
					*int_ptr = CODE_FALSE;
				else {
					sprintf(error_text,
						"%s ('%s') --- 'ON' or 'OFF' expected.",
						"Invalid boolean value in command-line flag", argv[count_1]);
					return_code = CODE_FAILURE;
					break;
				}
			}
			else {
				sprintf(error_text, "Invalid parameter encountered ('%.100s').",
					argv[count_1]);
				return_code = CODE_FAILURE;
				break;
			}
		}
		else {
			if (control_ptr->in_file_ptr != stdin)
				fclose(control_ptr->in_file_ptr);
			if ((control_ptr->in_file_ptr = fopen(argv[count_1], "r")) == NULL) {
				sprintf(error_text, "Unable to open input file '%s'.",
					argv[count_1]);
				return_code = CODE_FAILURE;
				break;
			}
			control_ptr->in_file_name = argv[count_1];
			if ((return_code = PRT_EmitFile(control_ptr, buffer)) !=
				CODE_SUCCESS) {
				sprintf(error_text,
					"Error emitting file '%s':\n>>> %s",
					control_ptr->in_file_name, buffer);
				break;
			}
		}
		if ((return_code = PRT_SetParameters(control_ptr, buffer)) !=
			CODE_SUCCESS) {
			sprintf(error_text, "Error setting parameters:\n>>> %s", buffer);
			break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static int PRT_GetParamsFromFile(PRT_CONTROL_ITEM *control_ptr,
	char *in_file_name, unsigned int *parse_count, char ***parse_list,
	char *error_text)
#else
static int PRT_GetParamsFromFile(control_ptr, in_file_name, parse_count,
	parse_list, error_text)
PRT_CONTROL_ITEM   *control_ptr;
char               *in_file_name;
unsigned int       *parse_count;
char             ***parse_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	unsigned int  add_index;
	FILE         *in_file_ptr = NULL;
	char          buffer[512 + 1];

	if ((return_code = PRT_FindParsedItem(in_file_name, parse_count,
		parse_list, &add_index, error_text)) == PRT_ADD_ERROR)
		return_code = CODE_FAILURE;
	else if (return_code == PRT_FOUND)
		return_code = CODE_SUCCESS;
	else {
		if ((in_file_ptr = fopen(in_file_name, "r")) == NULL) {
			sprintf(error_text,
				"Unable to open parameter file '%s' for input.", in_file_name);
			return_code = CODE_FAILURE;
		}
		else {
			return_code = CODE_SUCCESS;
			while (!feof(in_file_ptr)) {
				*buffer = '\0';
				fgets(buffer, sizeof(buffer) - 2, in_file_ptr);
				while (*buffer && (buffer[strlen(buffer) - 1] == '\n'))
					buffer[strlen(buffer) - 1] = '\0';
				if ((return_code = PRT_GetParamsFromString(control_ptr, buffer,
					parse_count, parse_list, error_text)) != CODE_SUCCESS)
					break;
			}
			fclose(in_file_ptr);
		}
		strldel(parse_count, parse_list, add_index, 1);
	}

	return(return_code);
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static int PRT_GetParamsFromEnviron(PRT_CONTROL_ITEM *control_ptr,
	unsigned int *parse_count, char ***parse_list, char *error_text)
#else
static int PRT_GetParamsFromEnviron(control_ptr, parse_count, parse_list,
	error_text)
PRT_CONTROL_ITEM   *control_ptr;
unsigned int       *parse_count;
char             ***parse_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = CODE_SUCCESS;
	unsigned int  add_index;
	char         *env_ptr;

	if ((env_ptr = getenv(PRT_ENVIRONMENT_NAME)) != NULL) {
		if ((return_code = PRT_FindParsedItem(PRT_ENVIRONMENT_DONE, parse_count,
			parse_list, &add_index, error_text)) == PRT_ADD_ERROR)
			return_code = CODE_FAILURE;
		else if (return_code == PRT_FOUND)
			return_code = CODE_SUCCESS;
		else {
			return_code = PRT_GetParamsFromString(control_ptr, env_ptr,
				parse_count, parse_list, error_text);
			strldel(parse_count, parse_list, add_index, 1);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static int PRT_GetParamsFromString(PRT_CONTROL_ITEM *control_ptr,
	char *in_string, unsigned int *parse_count, char ***parse_list,
	char *error_text)
#else
static int PRT_GetParamsFromString(control_ptr, in_string, parse_count,
	parse_list, error_text)
PRT_CONTROL_ITEM   *control_ptr;
char               *in_string;
unsigned int       *parse_count;
char             ***parse_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code  = CODE_SUCCESS;
	char *tmp_settings = NULL;
	char *tmp_ptr_1;
	char *tmp_ptr_2;

	if (in_string && *in_string) {
		if ((tmp_settings = strdup(in_string)) == NULL) {
			strcpy(error_text, "Unable to copy parameter data string.");
			return_code = CODE_FAILURE;
		}
		else {
			tmp_ptr_1 = trim(oneblank(tmp_settings));
			while (*tmp_ptr_1) {
				if ((tmp_ptr_2 = strchr(tmp_ptr_1, ' ')) != NULL)
					*tmp_ptr_2++ = '\0';
				else
					tmp_ptr_2 = tmp_ptr_1 + strlen(tmp_ptr_1);
				if ((return_code = PRT_ParseParams(control_ptr, 1, &tmp_ptr_1,
					parse_count, parse_list, error_text)) != CODE_SUCCESS)
					break;
				tmp_ptr_1 = tmp_ptr_2;
			}
			free(tmp_settings);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static int PRT_FindParsedItem(char *name, unsigned int *parse_count,
	char ***parse_list, unsigned int *add_index, char *error_text)
#else
static int PRT_FindParsedItem(name, parse_count, parse_list, add_index,
	error_text)
char           *name;
unsigned int   *parse_count;
char         ***parse_list;
unsigned int   *add_index;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = PRT_FOUND;

	for (*add_index = 0; *add_index < *parse_count; (*add_index)++) {
		if (!stricmp(name, (*parse_list)[*add_index]))
			goto EXIT_FUNCTION;
	}

	if (!strlapp(parse_count, parse_list, name)) {
		*add_index  = *parse_count - 1;
		return_code = PRT_NOT_FOUND;
	}
	else {
		sprintf(error_text, "Error adding '%.40s' to parse list (item %d).",
			name, *parse_count + 1);
		return_code = PRT_ADD_ERROR;
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static void PRT_DebugShowControl(PRT_CONTROL_ITEM *control_ptr)
#else
static void PRT_DebugShowControl(control_ptr)
PRT_CONTROL_ITEM *control_ptr;
#endif /* #ifndef NARGS */
{
	fprintf(stdout, "in_file_name          : %s\n",
		control_ptr->in_file_name);
	fprintf(stdout, "out_file_name         : %s\n",
		control_ptr->out_file_name);
	fprintf(stdout, "page_footer_format    : %s\n",
		control_ptr->page_footer_format);

	fprintf(stdout, "page_orientation      : %s\n",
		PRT_OrientationList[control_ptr->page_orientation].orientation_name);
	fprintf(stdout, "paper_type            : %s\n",
		PRT_PaperTypeList[control_ptr->paper_type].paper_name);
	fprintf(stdout, "font_name             : %s\n",
		PRT_FontNameList[control_ptr->font_name].font_name);

	fprintf(stdout, "tab_setting           : %u\n",
		control_ptr->tab_setting);
	fprintf(stdout, "first_page_number     : %lu\n",
		control_ptr->first_page_number);
	fprintf(stdout, "first_line_number     : %lu\n",
		control_ptr->first_line_number);
	fprintf(stdout, "current_page_number   : %lu\n",
		control_ptr->current_page_number);
	fprintf(stdout, "current_line_number   : %lu\n",
		control_ptr->current_line_number);

	fprintf(stdout, "current_row           : %u\n",
		control_ptr->current_row);
	fprintf(stdout, "current_col           : %u\n",
		control_ptr->current_col);
	fprintf(stdout, "actual_page_rows      : %u\n",
		control_ptr->actual_page_rows);
	fprintf(stdout, "actual_page_cols      : %u\n",
		control_ptr->actual_page_cols);
	fprintf(stdout, "working_page_rows     : %u\n",
		control_ptr->working_page_rows);
	fprintf(stdout, "working_page_cols     : %u\n",
		control_ptr->working_page_cols);
	fprintf(stdout, "left_margin           : %u\n",
		control_ptr->left_margin);
	fprintf(stdout, "right_margin          : %u\n",
		control_ptr->right_margin);
	fprintf(stdout, "left_padding          : %u\n",
		control_ptr->left_padding);
	fprintf(stdout, "right_padding         : %u\n",
		control_ptr->right_padding);

	fprintf(stdout, "cont_page_number_flag : %s\n",
		(control_ptr->cont_page_number_flag == CODE_TRUE) ? "TRUE" : "FALSE");
	fprintf(stdout, "cont_line_number_flag : %s\n",
		(control_ptr->cont_line_number_flag == CODE_TRUE) ? "TRUE" : "FALSE");
	fprintf(stdout, "page_header_flag      : %s\n",
		(control_ptr->page_header_flag == CODE_TRUE) ? "TRUE" : "FALSE");
	fprintf(stdout, "page_footer_flag      : %s\n",
		(control_ptr->page_footer_flag == CODE_TRUE) ? "TRUE" : "FALSE");
	fprintf(stdout, "line_number_flag      : %s\n",
		(control_ptr->line_number_flag == CODE_TRUE) ? "TRUE" : "FALSE");
	fprintf(stdout, "line_interpret_flag   : %s\n",
		(control_ptr->line_interpret_flag == CODE_TRUE) ? "TRUE" : "FALSE");
	fprintf(stdout, "bold_header_flag      : %s\n",
		(control_ptr->bold_header_flag == CODE_TRUE) ? "TRUE" : "FALSE");
	fprintf(stdout, "bold_footer_flag      : %s\n",
		(control_ptr->bold_footer_flag == CODE_TRUE) ? "TRUE" : "FALSE");
	fprintf(stdout, "bold_line_number_flag : %s\n",
		(control_ptr->bold_line_number_flag == CODE_TRUE) ? "TRUE" : "FALSE");
	fprintf(stdout, "bold_text_flag        : %s\n",
		(control_ptr->bold_text_flag == CODE_TRUE) ? "TRUE" : "FALSE");
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static int PRT_SetDefaults(PRT_CONTROL_ITEM *control_ptr, char *error_text)
#else
static int PRT_SetDefaults(control_ptr, error_text)
PRT_CONTROL_ITEM *control_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	memset(control_ptr, '\0', sizeof(*control_ptr));

	control_ptr->in_file_name          = "stdin";
	control_ptr->out_file_name         = "stdout";
	control_ptr->in_file_ptr           = stdin;
	control_ptr->out_file_ptr          = stdout;
	control_ptr->page_footer_format    = "";
	control_ptr->page_orientation      = PRT_ORIENTATION_DEFAULT;
	control_ptr->paper_type            = PRT_PAPER_TYPE_DEFAULT;
	control_ptr->font_name             = PRT_FONT_NAME_DEFAULT;
	control_ptr->tab_setting           = PRT_TAB_SETTING_DEFAULT;
	control_ptr->first_page_number     = 1L;
	control_ptr->first_line_number     = 1L;
	control_ptr->current_page_number   = 1L;
	control_ptr->current_line_number   = 1L;
	control_ptr->current_row           = 0;
	control_ptr->current_col           = 0;
	control_ptr->actual_page_rows      = 0;
	control_ptr->actual_page_cols      = 0;
	control_ptr->working_page_rows     = 0;
	control_ptr->working_page_cols     = 0;
	control_ptr->left_margin           = 0;
	control_ptr->right_margin          = 0;
	control_ptr->left_padding          = 0;
	control_ptr->right_padding         = 0;
	control_ptr->cont_page_number_flag = CODE_FALSE;
	control_ptr->cont_line_number_flag = CODE_FALSE;
	control_ptr->page_header_flag      = CODE_FALSE;
	control_ptr->page_footer_flag      = CODE_FALSE;
	control_ptr->line_number_flag      = CODE_FALSE;
	control_ptr->line_interpret_flag   = CODE_FALSE;
	control_ptr->bold_header_flag      = CODE_FALSE;
	control_ptr->bold_footer_flag      = CODE_FALSE;
	control_ptr->bold_line_number_flag = CODE_FALSE;
	control_ptr->bold_text_flag        = CODE_FALSE;

	return_code = PRT_SetParameters(control_ptr, error_text);

	return(return_code);
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static int PRT_SetCDefaults(PRT_CONTROL_ITEM *control_ptr, char *error_text)
#else
static int PRT_SetCDefaults(control_ptr, error_text)
PRT_CONTROL_ITEM *control_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	control_ptr->page_footer_format    = "";
	control_ptr->page_orientation      = PRT_ORIENTATION_PORTRAIT;
	control_ptr->paper_type            = PRT_PAPER_TYPE_DEFAULT;
	control_ptr->font_name             = PRT_FONT_NAME_DEFAULT;
	control_ptr->tab_setting           = PRT_TAB_SETTING_DEFAULT_C;
	control_ptr->first_page_number     = 1L;
	control_ptr->first_line_number     = 1L;
	control_ptr->current_page_number   = 1L;
	control_ptr->current_line_number   = 1L;
	control_ptr->current_row           = 0;
	control_ptr->current_col           = 0;
	control_ptr->actual_page_rows      = 0;
	control_ptr->actual_page_cols      = 0;
	control_ptr->working_page_rows     = 0;
	control_ptr->working_page_cols     = 0;
	control_ptr->left_margin           = PRT_MARGIN_LEFT_DEFAULT_C;
	control_ptr->right_margin          = PRT_MARGIN_RIGHT_DEFAULT_C;
	control_ptr->left_padding          = PRT_PADDING_LEFT_DEFAULT_C;
	control_ptr->right_padding         = PRT_PADDING_RIGHT_DEFAULT_C;

	control_ptr->cont_page_number_flag = CODE_FALSE;
	control_ptr->cont_line_number_flag = CODE_FALSE;
	control_ptr->page_header_flag      = CODE_TRUE;
	control_ptr->page_footer_flag      = CODE_TRUE;
	control_ptr->line_number_flag      = CODE_TRUE;
	control_ptr->line_interpret_flag   = CODE_TRUE;
	control_ptr->bold_header_flag      = CODE_TRUE;
	control_ptr->bold_footer_flag      = CODE_TRUE;
	control_ptr->bold_line_number_flag = CODE_TRUE;
	control_ptr->bold_text_flag        = CODE_FALSE;

	return_code = PRT_SetParameters(control_ptr, error_text);

	return(return_code);
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static int PRT_SetParameters(PRT_CONTROL_ITEM *control_ptr, char *error_text)
#else
static int PRT_SetParameters(control_ptr, error_text)
PRT_CONTROL_ITEM *control_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code = CODE_SUCCESS;
	double row_count;
	double col_count;

	row_count = (((control_ptr->page_orientation == PRT_ORIENTATION_PORTRAIT) ?
		PRT_PaperTypeList[control_ptr->paper_type].paper_length :
		PRT_PaperTypeList[control_ptr->paper_type].paper_width) - .5) *
		PRT_FontNameList[control_ptr->font_name].font_LPI;

	col_count = (((control_ptr->page_orientation == PRT_ORIENTATION_PORTRAIT) ?
		PRT_PaperTypeList[control_ptr->paper_type].paper_width  :
		PRT_PaperTypeList[control_ptr->paper_type].paper_length) - .5) *
		PRT_FontNameList[control_ptr->font_name].font_CPI;

/*
	CODE NOTE: To be removed.
	control_ptr->actual_page_rows  = ((int) fabs(row_count)) - 1;
	control_ptr->actual_page_cols  = ((int) fabs(col_count)) - 1;
*/
	control_ptr->actual_page_rows  = ((int) row_count) - 1;
	control_ptr->actual_page_cols  = ((int) col_count) - 1;
	control_ptr->actual_page_cols -=
		control_ptr->left_margin + control_ptr->right_margin;

	control_ptr->working_page_rows = control_ptr->actual_page_rows -
		(((control_ptr->page_header_flag == CODE_TRUE) ? 7 : 0) +
		 ((control_ptr->page_footer_flag == CODE_TRUE) ? 7 : 0));

	control_ptr->working_page_cols = control_ptr->actual_page_cols -
		(control_ptr->left_padding + control_ptr->right_padding +
		((control_ptr->line_number_flag) ? PRT_LINE_NUMBER_LENGTH : 0));

	if (control_ptr->cont_page_number_flag != CODE_TRUE)
		control_ptr->current_page_number = control_ptr->first_page_number;

	if (control_ptr->cont_line_number_flag != CODE_TRUE)
		control_ptr->current_line_number = control_ptr->first_line_number;

	if (control_ptr->working_page_rows < 2) {
		strcpy(error_text, "Insufficient rows for output.");
		return_code = CODE_FAILURE;
	}
	else if (control_ptr->working_page_cols < 2) {
		strcpy(error_text, "Insufficient columns for output.");
		return_code = CODE_FAILURE;
	}
	else
		return_code = PRT_SetFooter(control_ptr, error_text);

	return(return_code);
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static int PRT_SetFooter(PRT_CONTROL_ITEM *control_ptr, char *error_text)
#else
static int PRT_SetFooter(control_ptr, error_text)
PRT_CONTROL_ITEM *control_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code  = CODE_SUCCESS;
	unsigned int  total_length = 0;
	int           page_number_length;
	time_t        file_time;
	struct stat   file_stat;
	struct tm    *tm_ptr;
	char          date_time_buffer[100];
	char          page_number_format[100];

	if (control_ptr->page_footer_flag == CODE_TRUE) {
		if (control_ptr->in_file_ptr == stdin)
			file_time = time((time_t *) 0);
		else {
			stat(control_ptr->in_file_name, &file_stat);
			file_time = file_stat.st_mtime;
		}
		tm_ptr = localtime(&file_time);
		strcpy(page_number_format, "Page: %010lu");
		page_number_length = 6 + 10;
		sprintf(date_time_buffer,
			"Date: %02u/%02u/%04u   Time: %02u:%02u:%02u",
			tm_ptr->tm_mon + 1, tm_ptr->tm_mday, tm_ptr->tm_year + 1900,
			tm_ptr->tm_hour,    tm_ptr->tm_min,  tm_ptr->tm_sec);
		if ((total_length = (strlen(date_time_buffer) + page_number_length)) <
			control_ptr->actual_page_cols)
			goto EXIT_FUNCTION;
		sprintf(date_time_buffer,
			"Date: %02u/%02u/%04u   %02u:%02u:%02u",
			tm_ptr->tm_mon + 1, tm_ptr->tm_mday, tm_ptr->tm_year + 1900,
			tm_ptr->tm_hour,    tm_ptr->tm_min,  tm_ptr->tm_sec);
		if ((total_length = (strlen(date_time_buffer) + page_number_length)) <
			control_ptr->actual_page_cols)
			goto EXIT_FUNCTION;
		sprintf(date_time_buffer,
			"Date: %02u/%02u/%02u   %02u:%02u:%02u",
			tm_ptr->tm_mon + 1, tm_ptr->tm_mday, tm_ptr->tm_year + 1900,
			tm_ptr->tm_hour,    tm_ptr->tm_min,  tm_ptr->tm_sec);
		if ((total_length = (strlen(date_time_buffer) + page_number_length)) <
			control_ptr->actual_page_cols)
			goto EXIT_FUNCTION;
		sprintf(date_time_buffer,
			"Date: %02u/%02u/%02u %02u:%02u:%02u",
			tm_ptr->tm_mon + 1, tm_ptr->tm_mday, tm_ptr->tm_year + 1900,
			tm_ptr->tm_hour,    tm_ptr->tm_min,  tm_ptr->tm_sec);
		if ((total_length = (strlen(date_time_buffer) + page_number_length)) <
			control_ptr->actual_page_cols)
			goto EXIT_FUNCTION;
		sprintf(date_time_buffer,
			"%02u/%02u/%02u %02u:%02u:%02u",
			tm_ptr->tm_mon + 1, tm_ptr->tm_mday, tm_ptr->tm_year + 1900,
			tm_ptr->tm_hour,    tm_ptr->tm_min,  tm_ptr->tm_sec);
		if ((total_length = (strlen(date_time_buffer) + page_number_length)) <
			control_ptr->actual_page_cols)
			goto EXIT_FUNCTION;
		sprintf(date_time_buffer,
			"%02u/%02u/%02u",
			tm_ptr->tm_mon + 1, tm_ptr->tm_mday, tm_ptr->tm_year + 1900);
		if ((total_length = (strlen(date_time_buffer) + page_number_length)) <
			control_ptr->actual_page_cols)
			goto EXIT_FUNCTION;
		strcat(page_number_format, "%010.010lu");
		page_number_length = 10;
		if ((total_length = (strlen(date_time_buffer) + page_number_length)) <
			control_ptr->actual_page_cols)
			goto EXIT_FUNCTION;
		strcat(page_number_format, "%05.05lu");
		page_number_length = 5;
		if ((total_length = (strlen(date_time_buffer) + page_number_length)) <
			control_ptr->actual_page_cols)
			goto EXIT_FUNCTION;
		sprintf(error_text, "Not enough columns to permit footer text (%u).",
			control_ptr->actual_page_cols);
		return_code = CODE_FAILURE;
	}

EXIT_FUNCTION:

	if ((control_ptr->page_footer_flag == CODE_TRUE) &&
		(return_code == CODE_SUCCESS)) {
		nstrset(PRT_FooterBuffer, ' ', control_ptr->left_margin);
		strcat(PRT_FooterBuffer, date_time_buffer);
		nstrset(PRT_FooterBuffer + strlen(PRT_FooterBuffer), ' ',
			control_ptr->actual_page_cols - total_length);
		strcat(PRT_FooterBuffer, page_number_format);
		control_ptr->page_footer_format = PRT_FooterBuffer;
	}

	return(return_code);
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static int PRT_EmitFile(PRT_CONTROL_ITEM *control_ptr, char *error_text)
#else
static int PRT_EmitFile(control_ptr, error_text)
PRT_CONTROL_ITEM *control_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int               return_code = CODE_SUCCESS;
	char              buffer[PRT_INPUT_BUFFER_SIZE + 1];
	char              out_buffer[PRT_MAXIMUM_COL_COUNT + 1];
	char             *out_buffer_ptr;
	PRT_CONTROL_ITEM  tmp_control_data;

	tmp_control_data = *control_ptr;
	if (control_ptr->bold_text_flag == CODE_TRUE)
		control_ptr->bold_line_number_flag = CODE_TRUE;

	if ((return_code = PRT_SetParameters(control_ptr, error_text)) !=
		CODE_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(control_ptr->out_file_ptr, "\033&f0S%s%s%s%s\033&f1S",
		GenericString,
		PRT_OrientationList[control_ptr->page_orientation].orientation_command,
		PRT_FontNameList[control_ptr->font_name].font_command,
		PRT_PaperTypeList[control_ptr->paper_type].paper_command);

	control_ptr->first_page_flag = CODE_TRUE;
	control_ptr->last_page_flag  = CODE_FALSE;
	control_ptr->current_row     = 0;
	control_ptr->current_col     = 0;
	PRT_PageControl(control_ptr);

	while (!feof(control_ptr->in_file_ptr)) {
		*buffer = '\0';
		fgets(buffer, sizeof(buffer) - 2, control_ptr->in_file_ptr);
		if ((control_ptr->line_interpret_flag == CODE_TRUE)    &&
			(!strncmp(buffer, "/*", 2)) && (strlen(buffer) > 3) &&
			(!strcmp(buffer + (strlen(buffer) - 3), "*/\n"))) {
			if (!stricmp(buffer, "/*FF*/\n")) {
				PRT_PageControl(control_ptr);
				continue;
			}
			else if ((!strnicmp(buffer, "/*T=", 4))             &&
				((strlen(buffer) == 8) || (strlen(buffer) == 9)) &&
				(!strcmp(buffer + (strlen(buffer) - 3), "*/\n")) &&
				((atof(buffer + 4) >= PRT_TAB_SETTING_MINIMUM)   &&
				(atof(buffer + 4) <= PRT_TAB_SETTING_MAXIMUM))) {
				control_ptr->tab_setting = atoi(buffer + 4);
				continue;
			}
		}
		PRT_DoLinePreface(control_ptr, CODE_TRUE, out_buffer, &out_buffer_ptr);
		PRT_DoLine(control_ptr, buffer, out_buffer, out_buffer_ptr);
	}

	control_ptr->first_page_flag = CODE_FALSE;
	control_ptr->last_page_flag  = CODE_TRUE;
	PRT_PageControl(control_ptr);

	fprintf(control_ptr->out_file_ptr, "%s", GenericString);

EXIT_FUNCTION:

	control_ptr->bold_line_number_flag =
		tmp_control_data.bold_line_number_flag;

	return(return_code);
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static void PRT_DoLinePreface(PRT_CONTROL_ITEM *control_ptr,
	int line_number_flag, char *out_buffer, char **out_buffer_ptr)
#else
static void PRT_DoLinePreface(control_ptr, line_number_flag, out_buffer,
	out_buffer_ptr)
PRT_CONTROL_ITEM  *control_ptr;
int                line_number_flag;
char              *out_buffer;
char             **out_buffer_ptr;
#endif /* #ifndef NARGS */
{
	*out_buffer     = '\0';
	*out_buffer_ptr = out_buffer;

	if (control_ptr->left_margin || control_ptr->left_padding ||
		control_ptr->line_number_flag) {
		nstrset(out_buffer, ' ', control_ptr->left_margin);
		nstrset(out_buffer + strlen(out_buffer), ' ', control_ptr->left_padding);
		if (control_ptr->line_number_flag) {
			if (line_number_flag == CODE_TRUE)
				sprintf(out_buffer + strlen(out_buffer),
					PRT_LINE_NUMBER_FORMAT, control_ptr->current_line_number);
			else
				nstrset(out_buffer + strlen(out_buffer), ' ',
					PRT_LINE_NUMBER_LENGTH);
		}
		if ((control_ptr->bold_line_number_flag == CODE_TRUE) &&
			 (control_ptr->line_number_flag      == CODE_TRUE) &&
			 (control_ptr->bold_text_flag        != CODE_TRUE)) {
			PRT_DoBold(control_ptr, out_buffer);
			*out_buffer = '\0';
		}
		else if (((control_ptr->bold_line_number_flag != CODE_TRUE) ||
			 (control_ptr->line_number_flag      != CODE_TRUE)) &&
			 (control_ptr->bold_text_flag        == CODE_TRUE)) {
			fprintf(control_ptr->out_file_ptr, "%s", out_buffer);
			*out_buffer = '\0';
		}
		*out_buffer_ptr = out_buffer + strlen(out_buffer);
	}
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static void PRT_DoLine(PRT_CONTROL_ITEM *control_ptr, char *in_string,
	char *out_buffer, char *out_buffer_ptr)
#else
static void PRT_DoLine(control_ptr, in_string, out_buffer, out_buffer_ptr)
PRT_CONTROL_ITEM *control_ptr;
char             *in_string;
char             *out_buffer;
char             *out_buffer_ptr;
#endif /* #ifndef NARGS */
{
	int tab_count;

	while (*in_string) {
		if (*in_string == '\t') {
			tab_count = control_ptr->tab_setting -
				(control_ptr->current_col % control_ptr->tab_setting);
			while (tab_count) {
				*out_buffer_ptr++ = ' ';
				if (++control_ptr->current_col == control_ptr->working_page_cols) {
					*out_buffer_ptr = '\0';
					if (control_ptr->bold_text_flag == CODE_TRUE)
						PRT_DoBold(control_ptr, out_buffer);
					else
						fprintf(control_ptr->out_file_ptr, "%s", out_buffer);
					PRT_LineControl(control_ptr);
					PRT_DoLinePreface(control_ptr, CODE_FALSE, out_buffer,
						&out_buffer_ptr);
				}
				tab_count--;
			}
		}
		else if (*in_string == '\n') {
			*out_buffer_ptr = '\0';
			if (control_ptr->bold_text_flag == CODE_TRUE)
				PRT_DoBold(control_ptr, out_buffer);
			else
				fprintf(control_ptr->out_file_ptr, "%s", out_buffer);
			out_buffer_ptr = out_buffer;
			PRT_LineControl(control_ptr);
			control_ptr->current_line_number++;
		}
		else if (*in_string == '\f') {
			*out_buffer_ptr = '\0';
			if (control_ptr->bold_text_flag == CODE_TRUE)
				PRT_DoBold(control_ptr, out_buffer);
			else
				fprintf(control_ptr->out_file_ptr, "%s", out_buffer);
			out_buffer_ptr = out_buffer;
			PRT_PageControl(control_ptr);
		}
		else {
			*out_buffer_ptr++ = *in_string;
			if (*in_string == '\r')
				control_ptr->current_col = 0;
			else if (*in_string == '\b')
				control_ptr->current_col--;
			if (++control_ptr->current_col == control_ptr->working_page_cols) {
				*out_buffer_ptr = '\0';
				if (control_ptr->bold_text_flag == CODE_TRUE)
					PRT_DoBold(control_ptr, out_buffer);
				else
					fprintf(control_ptr->out_file_ptr, "%s", out_buffer);
				PRT_LineControl(control_ptr);
				PRT_DoLinePreface(control_ptr, CODE_FALSE, out_buffer,
					&out_buffer_ptr);
			}
		}
		in_string++;
	}
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static void PRT_LineControl(PRT_CONTROL_ITEM *control_ptr)
#else
static void PRT_LineControl(control_ptr)
PRT_CONTROL_ITEM *control_ptr;
#endif /* #ifndef NARGS */
{
	fprintf(control_ptr->out_file_ptr, "\n");
	if (++control_ptr->current_row == control_ptr->working_page_rows)
		PRT_PageControl(control_ptr);
	control_ptr->current_col = 0;
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static void PRT_PageControl(PRT_CONTROL_ITEM *control_ptr)
#else
static void PRT_PageControl(control_ptr)
PRT_CONTROL_ITEM *control_ptr;
#endif /* #ifndef NARGS */
{
	char buffer[PRT_MAXIMUM_COL_COUNT + 1];

	if ((control_ptr->page_footer_flag == CODE_TRUE) &&
		(control_ptr->first_page_flag != CODE_TRUE)) {
		fprintf(control_ptr->out_file_ptr, "\n");
		while (control_ptr->current_row++ < control_ptr->working_page_rows)
			fprintf(control_ptr->out_file_ptr, "\n");
		fprintf(control_ptr->out_file_ptr, "\n\n");
		sprintf(buffer, control_ptr->page_footer_format,
			control_ptr->current_page_number);
		if (control_ptr->bold_footer_flag == CODE_TRUE)
			PRT_DoBold(control_ptr, buffer);
		else
			fprintf(control_ptr->out_file_ptr, "%s", buffer);
		fprintf(control_ptr->out_file_ptr, "\n\f");
		control_ptr->current_page_number++;
	}

	if ((control_ptr->page_header_flag == CODE_TRUE) &&
		(control_ptr->last_page_flag != CODE_TRUE)) {
		if (control_ptr->first_page_flag == CODE_FALSE)
			fprintf(control_ptr->out_file_ptr, "\n");
		fprintf(control_ptr->out_file_ptr, "\n\n");
		nstrset(buffer, ' ', control_ptr->left_margin);
		sprintf(buffer + strlen(buffer), "File: %s", control_ptr->in_file_name);
		if (control_ptr->bold_header_flag == CODE_TRUE)
			PRT_DoBold(control_ptr, buffer);
		else
			fprintf(control_ptr->out_file_ptr, "%s", buffer);
		fprintf(control_ptr->out_file_ptr, "\n\n");
	}

	control_ptr->first_page_flag = CODE_FALSE;
	control_ptr->last_page_flag  = CODE_FALSE;
	control_ptr->current_row     = 0;
	control_ptr->current_col     = 0;
}
/*	***********************************************************************	*/
/*FF*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
static void PRT_DoBold(PRT_CONTROL_ITEM *control_ptr, char *in_string)
#else
static void PRT_DoBold(control_ptr, in_string)
PRT_CONTROL_ITEM *control_ptr;
char             *in_string;
#endif /* #ifndef NARGS */
{
	int count_1;

	fprintf(control_ptr->out_file_ptr, "%s", in_string);
	for (count_1 = 0; count_1 < 3; count_1++)
		fprintf(control_ptr->out_file_ptr,
			"\033&a-%uC\033*p2X%s", strlen(in_string), in_string);
	fprintf(control_ptr->out_file_ptr, "\033*p-6X");
}
/*	***********************************************************************	*/

