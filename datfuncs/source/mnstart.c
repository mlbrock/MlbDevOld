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
								specified month.

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

	NAME			:	mnstart

	SYNOPSIS		:	start_of_month = mnstart(in_year, in_month);

						JULIAN start_of_month;

						int    in_year;

						int    in_month;

	DESCRIPTION	:	Gets the ''JULIAN'' date for the first day of the
						specified month.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which this function is to
						determine the start of the month.

						(.) ``in_month`` is the month of ``in_year`` for which this
						function is to determine the start of the month.

   RETURNS     :  Returns the ''JULIAN'' date equivalent of the start of the
						month specified by the ``in_year`` and ``in_month``
						parameters.

	NOTES			:	Use ``mnend`` to get the last day of the month.

	CAVEATS		:	

	SEE ALSO		:	mnend
						yrstart
						qtrstart
						wkstart

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2014 Michael L. Brock

	OUTPUT INDEX:	mnstart
						Date Functions:Start/End Determination Functions:mnstart
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	mnstart

	PUBLISH NAME:	mnstart

	ENTRY CLASS	:	Date Functions:Start/End Determination Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN mnstart(int in_year, int in_month)
#else
JULIAN mnstart(in_year, in_month)
int in_year;
int in_month;
#endif /* #ifndef NARGS */
{
	return(ymdtojul(in_year, in_month, 1));
}
/* *********************************************************************** */

