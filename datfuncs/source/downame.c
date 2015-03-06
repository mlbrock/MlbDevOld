/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the name of the day of the week.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <string.h>

#include "datfunci.h"

/*	*********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */

static const char *DATFUNCS_DayOfWeekNameList[7] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* NOTE:BOH

	NAME			:	downame

	SYNOPSIS		:	day_of_week_name = downame(dow_number, text);

						char *day_of_week_name;

						int   dow_number;

						char *text;

	DESCRIPTION	:	

   PARAMETERS  :  Parameters to this function are as follow:

   RETURNS     :  Returns from this function are as follow:

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	downame
						Date Functions:Get Date/Time Component Functions:downame
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	downame

	PUBLISH NAME:	downame

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *downame(int dow_number, char *text)
#else
char *downame(dow_number, text)
int   dow_number;
char *text;
#endif /* #ifndef NARGS */
{
	return(((dow_number >= 0) && (dow_number <= 6)) ?
		strcpy(text, DATFUNCS_DayOfWeekNameList[dow_number]) :
		strcpy(text, ""));
}
/*	*********************************************************************** */

