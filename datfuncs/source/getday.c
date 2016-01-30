/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the day-of-month portion of a given JULIAN date.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	getday

	SYNOPSIS		:	day_of_month = getday(in_julian);

						int    day_of_year;

						JULIAN in_julian;

	DESCRIPTION	:	Determines the day of the month of the specified JULIAN
						date.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the JULIAN for which the day of the
						month is to be determined.

   RETURNS     :  The day of the month for the JULIAN.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	getday
						Date Functions:Get Date/Time Component Functions:getday
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getday

	PUBLISH NAME:	getday

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int getday(JULIAN in_julian)
#else
int getday(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	int tmp_year;
	int tmp_month;
	int tmp_day;

	jultoymd(in_julian, &tmp_year, &tmp_month, &tmp_day);

	return(tmp_day);
}
/* *********************************************************************** */

