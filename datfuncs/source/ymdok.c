/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether three integers representing year,
								month, and day are valid.

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

	NAME			:	ymdok

	SYNOPSIS		:	truth_flag = ymdok(in_year, in_month, in_day);

						int truth_flag;

						int in_year;

						int in_month;

						int in_day;

	DESCRIPTION	:	Determines whether three integers representing year,
						month, and day are valid.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year to validated.

						(.) ``in_month`` is the month to validated.

						(.) ``in_day`` is the day to validated.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_TRUE'' if the date is valid.

						(.) ''DATFUNCS_FALSE'' if the date is not valid.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	fixed_ymdok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	ymdok
						Date Functions:Check Date Functions:ymdok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	ymdok

	PUBLISH NAME:	ymdok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int ymdok(int in_year, int in_month, int in_day)
#else
int ymdok(in_year, in_month, in_day)
int in_year;
int in_month;
int in_day;
#endif /* #ifndef NARGS */
{
	return(((in_month >= 1) && (in_month <= 12) &&
		(in_day >= 1) && (in_day <= mndaymax(in_year, in_month)) &&
		((in_year != DATFUNCS_GREGORIAN_YEAR) ||
		(in_month != DATFUNCS_GREGORIAN_MONTH) ||
		(in_day < DATFUNCS_GREGORIAN_FIRST_DAY) ||
		(in_day > DATFUNCS_GREGORIAN_LAST_DAY))) ? DATFUNCS_TRUE :
		DATFUNCS_FALSE);
}
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	fixed_ymdok

	SYNOPSIS		:	truth_flag = fixed_ymdok(in_year, in_month, in_day,
							implied_century, implied_year_break);

						int truth_flag;

						int in_year;

						int in_month;

						int in_day;

						int implied_century;

						int implied_year_break;

	DESCRIPTION	:	Validates a year, month, and day after fixing the year to
						include the century.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_day`` is the day to validated.

						(.) ``implied_century`` is the century to be added to the
						date if the year is less than that specified by the
						``implied_year_break`` parameter.

						(.) ``implied_year_break`` specifies the fulcrum year at
						which the determination as to which century a date belongs.

						(-) Dates less than ``implied_year_break`` will be fixed so
						as to be in the century specified by ``implied_century``.

						(-) Dates greater than or equal to ``implied_year_break``
						will be fixed so as to be in the century before that
						specified by implied century.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_TRUE'' if the date is valid.

						(.) ''DATFUNCS_FALSE'' if the date is not valid.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	ymdok

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	fixed_ymdok
						Date Functions:Check Date Functions:fixed_ymdok
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	fixed_ymdok

	PUBLISH NAME:	fixed_ymdok

	ENTRY CLASS	:	Date Functions:Check Date Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int fixed_ymdok(int in_year, int in_month, int in_day, int implied_century,
	int implied_year_break)
#else
int fixed_ymdok(in_year, in_month, in_day, implied_century,
	implied_year_break)
int in_year;
int in_month;
int in_day;
int implied_century;
int implied_year_break;
#endif /* #ifndef NARGS */
{
	return(ymdok(fixyear(in_year, implied_century, implied_year_break),
		in_month, in_day));
}
/*	*********************************************************************** */

