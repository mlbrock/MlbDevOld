/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether a man page string is valid.

	Revision History	:	1995-09-27 --- Creation.
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

#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
static const char   *ADF_ManPageSectionList[][2]   = {
	{	"1",	"User Commands"											},
	{	"1c",	"Communication with Other System User Commands"	},
	{	"1g",	"Graphic and CAD User Commands"						},
	{	"1s",	"User Commands"											},
	{	"1v",	"System V User Commands"								},
	{	"2",	"System Calls"												},
	{	"2v",	"System V / Posix System Call"						},
	{	"3",	"Library Functions"										},
	{	"3c",	"Compatibility Functions"								},
	{	"3f",	"Fortran Library Functions"							},
	{	"3k",	"Kernel VM Library Functions"							},
	{	"3l",	"Lightweight Process Library Functions"			},
	{	"3m",	"Math Library Functions"								},
	{	"3n",	"Network Library Functions"							},
	{	"3r",	"RPC Services Library Functions"						},
	{	"3s",	"Standard I/O Functions"								},
	{	"3v",	"System V / Posix Library Functions"				},
	{	"3x",	"Miscellaneous Library Functions"					},
	{	"4",	"Device and Network Interfaces"						},
	{	"4f",	"Protocol Families"										},
	{	"4i",	"Device and Network Interfaces"						},
	{	"4m",	"STREAMS Module Interfaces"							},
	{	"4n",	"Network Interfaces"										},
	{	"4p",	"Protocols / Raw Interfaces"							},
	{	"4s",	"SunOS-specific Device Drivers"						},
	{	"4v",	"System V / Posix Interfaces"							},
	{	"5",	"File Formats"												},
	{	"5v",	"System V / Posix File Formats"						},
	{	"6",	"Games and Demos"											},
	{	"7",	"Environments / Tables / troff Macros"				},
	{	"7V",	"System V Environments / Tables / troff Macros"	},
	{	"8",	"Maintenance Commands"									},
	{	"8c",	"Maintenance Commands"									},
	{	"8v",	"System V / Posix Maintenance Commands"			},
	{	"9",	"Other Commands"											},
	{	"n",	"New Commands"												},
	{	"l",	"Local Commands"											},
	{	"o",	"Old Commands"												},
	{	"p",	"Public Commands"											}
};

static const unsigned int  ADF_ManPageSectionCount =
	sizeof(ADF_ManPageSectionList) / sizeof(ADF_ManPageSectionList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_ValidateManPage(const char *man_page, char *error_text)
#else
int ADF_ValidateManPage(man_page, error_text)
const char *man_page;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (strchr(ADF_VALID_MAN_PAGE_STRING, *man_page) != NULL)
		return_code = ADF_SUCCESS;
	else {
		sprintf(error_text,
			"The man page '%-.100s' is not valid --- expected one of '%s'.",
			man_page, ADF_VALID_MAN_PAGE_STRING);
		return_code = ADF_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
char *ADF_GetDefaultManSection(const char *man_page, char *man_section)
#else
char *ADF_GetDefaultManSection(man_page, man_section)
const char *man_page;
char       *man_section;
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	const char   *tmp_ptr = NULL;

	for (count_1 = 0; count_1 < ADF_ManPageSectionCount; count_1++) {
		if (!stricmp(man_page, ADF_ManPageSectionList[count_1][0])) {
			tmp_ptr = ADF_ManPageSectionList[count_1][1];
			goto EXIT_FUNCTION;
		}
	}

	if (*(man_page + 1)) {
		for (count_1 = 0; count_1 < ADF_ManPageSectionCount; count_1++) {
			if ((STRFUNCS_toupper(*man_page) ==
				STRFUNCS_toupper(ADF_ManPageSectionList[count_1][0][0])) &&
				(!ADF_ManPageSectionList[count_1][0][1])) {
				tmp_ptr = ADF_ManPageSectionList[count_1][1];
				break;
			}
		}
	}

EXIT_FUNCTION:

	return((tmp_ptr == NULL) ? NULL : strcpy(man_section, tmp_ptr));
}
/*	***********************************************************************	*/

