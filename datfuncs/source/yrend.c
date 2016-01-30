/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the JULIAN date for the last day of the
								specified year.

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

	NAME			:	yrend

	SYNOPSIS		:	end_of_year = yrend(in_year);

						JULIAN end_of_year;

						int    in_year;

	DESCRIPTION	:	Gets the ''JULIAN'' date for the last day of the
						specified year.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which this function is to
						determine the end of the year.

   RETURNS     :  Returns the ''JULIAN'' date equivalent of the end of the
						year specified by the ``in_year`` parameter.

	NOTES			:	Use ``yrstart`` to get the first day of the year.

	CAVEATS		:	

	SEE ALSO		:	yrstart
						mnend
						qtrend
						wkend

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	yrend
						Date Functions:Start/End Determination Functions:yrend
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	yrend

	PUBLISH NAME:	yrend

	ENTRY CLASS	:	Date Functions:Start/End Determination Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN yrend(int in_year)
#else
JULIAN yrend(in_year)
int in_year;
#endif /* #ifndef NARGS */
{
   return(ymdtojul(in_year, 12, 31));
}
/* *********************************************************************** */

