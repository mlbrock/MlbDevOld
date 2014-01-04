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
								specified calendar quarter.

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

	NAME			:	qtrend

	SYNOPSIS		:	end_of_quarter = qtrend(in_year, in_quarter);

						JULIAN end_of_quarter;

						int    in_year;

						int    in_quarter;

	DESCRIPTION	:	Gets the ''JULIAN'' date for the last day of the
						specified calendar quarter.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which this function is to
						determine the end of the quarter.

						(.) ``in_quarter`` is the quarter of ``in_year`` for which
						this function is to determine the end of the quarter.

						(-) Quarters are numbered from ''1'' to ''4'', inclusive.

   RETURNS     :  Returns the ''JULIAN'' date equivalent of the end of the
						quarter specified by the ``in_year`` and ``in_quarter``
						parameters.

	NOTES			:	Use ``qtrstart`` to get the first day of the quarter.

	CAVEATS		:	

	SEE ALSO		:	qtrstart
						yrend
						mnend
						wkend

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2014 Michael L. Brock

	OUTPUT INDEX:	qtrend
						Date Functions:Start/End Determination Functions:qtrend
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	qtrend

	PUBLISH NAME:	qtrend

	ENTRY CLASS	:	Date Functions:Start/End Determination Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN qtrend(int in_year, int in_quarter)
#else
JULIAN qtrend(in_year, in_quarter)
int in_year;
int in_quarter;
#endif /* #ifndef NARGS */
{
   return((in_quarter == 1) ? ymdtojul(in_year, 1, 31) : (in_quarter == 2) ?
      ymdtojul(in_year, 6, 30) : (in_quarter == 3) ? ymdtojul(in_year, 9, 30) :
      (in_quarter == 4) ? ymdtojul(in_year, 12, 31) : ((JULIAN) 0));
}
/* *********************************************************************** */

