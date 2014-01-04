/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether the specified year is valid.

	Revision History	:	1994-02-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
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

	NAME			:	yearok

	SYNOPSIS		:	truth_flag = yearok(in_year);

						int truth_flag;

						int in_year;

	DESCRIPTION	:	Determines whether a specified year is valid.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year to be validated.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_TRUE'' if the year is valid.

						(.) ''DATFUNCS_FALSE'' if the year is not valid.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	fixed_yearok
						monthok
						hourok
						minuteok
						secondok
						millisecondok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	yearok
						Date Functions:Check Date Functions:yearok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	yearok

	PUBLISH NAME:	yearok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int yearok(int in_year)
#else
int yearok(in_year)
int in_year;
#endif /* #ifndef NARGS */
{
	return(((in_year < DATFUNCS_MIN_YEAR) || (in_year > DATFUNCS_MAX_YEAR)) ?
		DATFUNCS_FALSE : DATFUNCS_TRUE);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	fixed_yearok

	SYNOPSIS		:	truth_flag = fixed_yearok(in_year, implied_century,
							implied_year_break);

						int truth_flag;

						int in_year;

						int implied_century;

						int implied_year_break;

	DESCRIPTION	:	Validates a year after fixing the year to include the
						century.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year to be validated.

						(.) ``implied_century`` is the century to be added to the
						year if the year is less than that specified by the
						``implied_year_break`` parameter.

						(.) ``implied_year_break`` specifies the fulcrum year at
						which the determination as to which century a year belongs.

						(-) Years less than ``implied_year_break`` will be fixed so
						as to be in the century specified by ``implied_century``.

						(-) Years greater than or equal to ``implied_year_break``
						will be fixed so as to be in the century before that
						specified by implied century.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_TRUE'' if the year is valid.

						(.) ''DATFUNCS_FALSE'' if the year is not valid.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	yearok
						monthok
						hourok
						minuteok
						secondok
						millisecondok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	fixed_yearok
						Date Functions:Check Date Functions:fixed_yearok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	fixed_yearok

	PUBLISH NAME:	fixed_yearok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int fixed_yearok(int in_year, int implied_century, int implied_year_break)
#else
int fixed_yearok(in_year, implied_century, implied_year_break)
int in_year;
int implied_century;
int implied_year_break;
#endif /* #ifndef NARGS */
{
	return(yearok(fixyear(in_year, implied_century, implied_year_break)));
}
/* *********************************************************************** */

