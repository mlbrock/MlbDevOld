/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the number of the quarter of a given JULIAN date.

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

	NAME			:	getqtr

	SYNOPSIS		:	quarter_of_year = getqtr(in_julian);

						int    quarter_of_year;

						JULIAN in_julian;

	DESCRIPTION	:	Determines the calendar quarter of a specified JULIAN date.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the JULIAN for which the calendar
						quarter is to be determined.

   RETURNS     :  The calendar quarter of the JULIAN date ``in_julian`` in
						the inclusive range 1 through 4.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	getqtr
						Date Functions:Get Date/Time Component Functions:getqtr
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getqtr

	PUBLISH NAME:	getqtr

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int getqtr(JULIAN in_julian)
#else
int getqtr(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	int tmp_year;
	int tmp_month;
	int tmp_day;

	jultoymd(in_julian, &tmp_year, &tmp_month, &tmp_day);

	return((tmp_month < 4) ? 1 : (tmp_month < 7) ? 2 :
		(tmp_month < 10) ? 3 : 4);
}
/* *********************************************************************** */

