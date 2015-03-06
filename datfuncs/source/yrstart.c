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
								specified year.

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

	NAME			:	yrstart

	SYNOPSIS		:	start_of_year = yrstart(in_year);

						JULIAN start_of_year;

						int    in_year;

	DESCRIPTION	:	Gets the ''JULIAN'' date for the first day of the
						specified year.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which this function is to
						determine the start of the year.

   RETURNS     :  Returns the ''JULIAN'' date equivalent of the start of the
						year specified by the ``in_year`` parameter.

	NOTES			:	Use ``yrend`` to get the last day of the year.

	CAVEATS		:	

	SEE ALSO		:	yrend
						mnstart
						qtrstart
						wkstart

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:	yrstart
						Date Functions:Start/End Determination Functions:yrstart
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	yrstart

	PUBLISH NAME:	yrstart

	ENTRY CLASS	:	Date Functions:Start/End Determination Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN yrstart(int in_year)
#else
JULIAN yrstart(in_year)
int in_year;
#endif /* #ifndef NARGS */
{
	return(ymdtojul(in_year, 1, 1));
}
/* *********************************************************************** */

