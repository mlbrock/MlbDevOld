/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Translates between the manifest constants for the
								various ADF output types and their equivalent text
								strings.

	Revision History	:	1995-12-22 --- Creation.
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

#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_GetOutputTypeFromString(const char *output_type_string,
	int *output_type, char *error_text)
#else
int ADF_GetOutputTypeFromString(output_type_string, output_type, error_text)
const char *output_type_string;
int        *output_type;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = ADF_SUCCESS;

	if ((!stricmp("ASCII", output_type_string)) ||
		(!stricmp("ASC", output_type_string)))
		*output_type = ADF_OUTPUT_TYPE_ASCII;
	else if ((!stricmp("FRAME_MAKER", output_type_string)) ||
		(!stricmp("FRAMEMAKER", output_type_string))        ||
		(!stricmp("FRAME", output_type_string)))
		*output_type = ADF_OUTPUT_TYPE_FRAME;
	else if (!stricmp("HTML", output_type_string))
		*output_type = ADF_OUTPUT_TYPE_HTML;
	else if ((!stricmp("MAN_PAGES", output_type_string)) ||
		(!stricmp("MAN_PAGES", output_type_string))       ||
		(!stricmp("MANPAGE", output_type_string))         ||
		(!stricmp("MAN", output_type_string)))
		*output_type = ADF_OUTPUT_TYPE_MAN;
	else if ((!stricmp("POST_SCRIPT", output_type_string)) ||
		(!stricmp("PS", output_type_string)))
		*output_type = ADF_OUTPUT_TYPE_PS;
	else if ((!stricmp("RICH_TEXT_FORMAT", output_type_string)) ||
		(!stricmp("RICH_TEXT", output_type_string))              ||
		(!stricmp("RTF", output_type_string)))
		*output_type = ADF_OUTPUT_TYPE_RTF;
	else {
		sprintf(error_text, "%s --- expected '{%s|%s}'.",
			"Invalid output type string encountered",
			"{ASC[II]|MAN[_PAGE[S]]|FRAME[[_]MAKER]|HTML|{POST[_]SCRIPT|PS}",
			"{RICH_TEXT[_FORMAT]|RTF}");
		return_code = ADF_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *ADF_GetOutputTypeString(int output_type, char *output_type_string)
#else
char *ADF_GetOutputTypeString(output_type, output_type_string)
int   output_type;
char *output_type_string;
#endif /* #ifndef NARGS */
{
	if (output_type == ADF_OUTPUT_TYPE_ASCII)
		strcpy(output_type_string, "ASCII");
	else if (output_type == ADF_OUTPUT_TYPE_FRAME)
		strcpy(output_type_string, "FrameMaker");
	else if (output_type == ADF_OUTPUT_TYPE_HTML)
		strcpy(output_type_string, "Hyper-Text Markup Language (HTML)");
	else if (output_type == ADF_OUTPUT_TYPE_MAN)
		strcpy(output_type_string, "Man Page");
	else if (output_type == ADF_OUTPUT_TYPE_PS)
		strcpy(output_type_string, "PostScript");
	else if (output_type == ADF_OUTPUT_TYPE_RTF)
		strcpy(output_type_string, "Rich Text Format (RTF)");
	else
		strcpy(output_type_string, "*** UNKNOWN Output Type ***");

	return(output_type_string);
}
/*	***********************************************************************	*/

