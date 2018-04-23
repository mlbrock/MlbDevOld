/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the month portion of a given JULIAN date.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2018.
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

	NAME			:	getmonth

	SYNOPSIS		:	month_of_year = getmonth(in_julian);

						int    month_of_year;

						JULIAN in_julian;

	DESCRIPTION	:	Determines the month of a specified JULIAN date.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the JULIAN for which the month is to
						be determined.

   RETURNS     :  The month of the JULIAN date ``in_julian`` in the inclusive
						range 1 through 12.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	getmonth
						Date Functions:Get Date/Time Component Functions:getmonth
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getmonth

	PUBLISH NAME:	getmonth

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int getmonth(JULIAN in_julian)
#else
int getmonth(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	int tmp_year;
	int tmp_month;
	int tmp_day;

	jultoymd(in_julian, &tmp_year, &tmp_month, &tmp_day);

	return(tmp_month);
}
/* *********************************************************************** */

