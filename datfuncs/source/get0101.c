/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the JULIAN date of the first day of a given
								JULIAN date.

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

	NAME			:	get0101

	SYNOPSIS		:	first_julian_of_year = get0101(in_julian);

						JULIAN first_julian_of_year;

						JULIAN in_julian;

	DESCRIPTION	:	Determines the first day of the year as a JULIAN for a
						specified JULIAN date.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the JULIAN for which the first day
						of the year is to be determined.

   RETURNS     :  The JULIAN date which represents the first day of the year.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	get1231

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	get0101
						Date Functions:Start/End Determination Functions:get0101
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	get0101

	PUBLISH NAME:	get0101

	ENTRY CLASS	:	Date Functions:Start/End Determination Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN get0101(JULIAN in_julian)
#else
JULIAN get0101(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	return(ymdtojul(getyear(in_julian), 1, 1));
}
/* *********************************************************************** */

