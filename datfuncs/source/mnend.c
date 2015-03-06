/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the JULIAN date for the last day of the specified
								month.

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

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	mnend

	SYNOPSIS		:	end_of_month = mnend(in_year, in_month);

						JULIAN end_of_month;

						int    in_year;

						int    in_month;

	DESCRIPTION	:	Gets the ''JULIAN'' date for the last day of the specified
						month.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which this function is to
						determine the end of the month.

						(.) ``in_month`` is the month of ``in_year`` for which this
						function is to determine the end of the month.

   RETURNS     :  Returns the ''JULIAN'' date equivalent of the end of the
						month specified by the ``in_year`` and ``in_month``
						parameters.

	NOTES			:	Use ``mnstart`` to get the first day of the month.

	CAVEATS		:	

	SEE ALSO		:	mnstart
						yrend
						qtrend
						wkend

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	mnend
						Date Functions:Start/End Determination Functions:mnend
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	mnend

	PUBLISH NAME:	mnend

	ENTRY CLASS	:	Date Functions:Start/End Determination Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN mnend(int in_year, int in_month)
#else
JULIAN mnend(in_year, in_month)
int in_year;
int in_month;
#endif /* #ifndef NARGS */
{
   return(ymdtojul(in_year, in_month, mndaymax(in_year, in_month)));
}
/* *********************************************************************** */

