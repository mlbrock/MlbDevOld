/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the JULIAN date for the first day of the
								specified calendar quarter.

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

	NAME			:	qtrstart

	SYNOPSIS		:	start_of_quarter = qtrstart(in_year, in_quarter);

						JULIAN start_of_quarter;

						int    in_year;

						int    in_quarter;

	DESCRIPTION	:	Gets the ''JULIAN'' date for the first day of the
						specified calendar quarter.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which this function is to
						determine the start of the quarter.

						(.) ``in_quarter`` is the quarter of ``in_year`` for which
						this function is to determine the start of the quarter.

						(-) Quarters are numbered from ''1'' to ''4'', inclusive.

   RETURNS     :  Returns the ''JULIAN'' date equivalent of the start of the
						quarter specified by the ``in_year`` and ``in_quarter``
						parameters.

	NOTES			:	Use ``qtrend`` to get the last day of the quarter.

	CAVEATS		:	

	SEE ALSO		:	qtrend
						yrstart
						mnstart
						wkstart

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	qtrstart
						Date Functions:Start/End Determination Functions:qtrstart
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	qtrstart

	PUBLISH NAME:	qtrstart

	ENTRY CLASS	:	Date Functions:Start/End Determination Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN qtrstart(int in_year, int in_quarter)
#else
JULIAN qtrstart(in_year, in_quarter)
int in_year;
int in_quarter;
#endif /* #ifndef NARGS */
{
	return((in_quarter == 1) ? ymdtojul(in_year, 1, 1) : (in_quarter == 2) ?
		ymdtojul(in_year, 4, 1) : (in_quarter == 3) ? ymdtojul(in_year, 7, 1) :
		(in_quarter == 4) ? ymdtojul(in_year, 10, 1) : ((JULIAN) 0));
}
/* *********************************************************************** */

