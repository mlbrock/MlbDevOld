/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Fixes a year value so as to include the century.

	Revision History	:	1994-02-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
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

	NAME			:	fixyear

	SYNOPSIS		:	fixed_year_value = fixyear(in_year, implied_century,
							implied_year_break);

						int  fixed_year_value;

						int in_year;

						int implied_century;

						int implied_year_break;

	DESCRIPTION	:	Fixes an year value so as to include the century.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year to be fixed.

						(.) ``implied_century`` is the century to be added to the
						year if the year is less than that specified by the
						``implied_year_break`` parameter.

						(.) ``implied_year_break`` specifies the fulcrum year at
						which the determination as to which century a year belongs.

						(-) Years less than ``implied_year_break`` will be fixed so
						as to be in the century specified by ``implied_century``.

   RETURNS     :  Returns from this function are as follow:

						(.) If no error occurs, the fixed year is returned.

						(.) Otherwise, zero is returned.

						If the year already includes the century, the year is
						returned unchanged.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

	OUTPUT INDEX:	fixyear
						Date Functions:Date/Time Adjustment Functions:fixyear
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	fixyear

	PUBLISH NAME:	fixyear

	ENTRY CLASS	:	Date Functions:Date/Time Adjustment Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int fixyear(int in_year, int implied_century, int implied_year_break)
#else
int fixyear(in_year, implied_century, implied_year_break)
int in_year;
int implied_century;
int implied_year_break;
#endif /* #ifndef NARGS */
{
	return(((implied_century > DATFUNCS_MIN_YEAR) &&
		(implied_century <= (DATFUNCS_MAX_YEAR + 1)) &&
		(((implied_century / 100) * 100) == implied_century) &&
		(implied_year_break >= 0) && (implied_year_break < 99)) ?
		((in_year > 99) ? in_year :
		(in_year + ((in_year < implied_year_break) ? implied_century :
		(implied_century - 100)))) : 0);
}
/* *********************************************************************** */

