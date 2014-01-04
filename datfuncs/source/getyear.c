/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the year portion of a given JULIAN date.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2014.
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

	NAME			:	getyear

	SYNOPSIS		:	year_value = getyear(in_julian);

						int    year_value;

						JULIAN in_julian;

	DESCRIPTION	:	Determines the year of a specified JULIAN date.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the JULIAN for which the year is to
						be determined.

   RETURNS     :  The year of the JULIAN date ``in_julian``.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2014 Michael L. Brock

	OUTPUT INDEX:	getyear
						Date Functions:Get Date/Time Component Functions:getyear
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getyear

	PUBLISH NAME:	getyear

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int getyear(JULIAN in_julian)
#else
int getyear(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	int tmp_year;
	int tmp_month;
	int tmp_day;

	jultoymd(in_julian, &tmp_year, &tmp_month, &tmp_day);

	return(tmp_year);
}
/* *********************************************************************** */

