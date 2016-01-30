/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the day of the month of a JULIAN.

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

	NAME			:	dayofmon

	SYNOPSIS		:	day_of_month = dayofmon(in_julian);

						int    day_of_month;

						JULIAN in_julian;

	DESCRIPTION	:	Determines the day of the month of the specified JULIAN
						date.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the JULIAN for which the day of the
						month is to be determined.

   RETURNS     :  The day of the month for the JULIAN.

	NOTES			:	This function has been superseded by the function
						``getday``. It is retained for compatibility with older
						versions of this library.

	CAVEATS		:	

	SEE ALSO		:	getday

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	dayofmon
						Date Functions:Get Date/Time Component Functions:dayofmon
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	dayofmon

	PUBLISH NAME:	dayofmon

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int dayofmon(JULIAN in_julian)
#else
int dayofmon(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	return(getday(in_julian));
}
/*	*********************************************************************** */

