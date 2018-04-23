/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the JULIAN date of the last day of a given
								JULIAN date.

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

	NAME			:	get1231

	SYNOPSIS		:	last_julian_of_year = get1231(in_julian)

						JULIAN last_julian_of_year;

						JULIAN in_julian;

	DESCRIPTION	:	Determines the last day of the year as a JULIAN for a
						specified JULIAN date.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the JULIAN for which the last day
						of the year is to be determined.

   RETURNS     :  The JULIAN date which represents the last day of the year.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	get0101

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	get1231
						Date Functions:Start/End Determination Functions:get1231
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	get1231

	PUBLISH NAME:	get1231

	ENTRY CLASS	:	Date Functions:Start/End Determination Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN get1231(JULIAN in_julian)
#else
JULIAN get1231(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	return(ymdtojul(getyear(in_julian), 12, 31));
}
/* *********************************************************************** */

