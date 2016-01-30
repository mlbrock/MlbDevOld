/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a fully-specified date/time value (year,
								month, day, hour, minute, second, millisecond) to a
								DTIME structure.

	Revision History	:	1994-02-06 --- Creation.
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

#include <stdio.h>

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DTIME_YYYYMMDDhhmmsslllToDate

	SYNOPSIS		:	return_code = DTIME_YYYYMMDDhhmmsslllToDate(in_year,
							in_month, in_day, in_hour, in_minute, in_second,
							in_millisecond, dtime_ptr, error_text);

						int    return_code;

						int    in_year;

						int    in_month;

						int    in_day;

						int    in_hour;

						int    in_minute;

						int    in_second;

						int    in_millisecond;

						DTIME *dtime_ptr;

						char  *error_text;

	DESCRIPTION	:	Converts a date represented as discrete year, month,
						day, hour, minute, second, and millisecond values into
						a ''DTIME'' structure.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year.

						(.) ``in_month`` is the month.

						(.) ``in_day`` is the day.

						(.) ``in_hour`` is the hour.

						(.) ``in_minute`` is the minute.

						(.) ``in_second`` is the second.

						(.) ``in_millisecond`` is the millisecond.

						(.) ``dtime_ptr`` is the pointer to a ''DTIME'' structure
						into which this function will place the converted
						date/time value.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at
						least ''DATFUNCS_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero DATFUNCS return codes if an error
						occurs.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	ymdtojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

	OUTPUT INDEX:	DTIME_YYYYMMDDhhmmsslllToDate
						Date Functions:Conversion Functions:DTIME_YYYYMMDDhhmmsslllToDate
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_YYYYMMDDhhmmsslllToDate

	PUBLISH NAME:	DTIME_YYYYMMDDhhmmsslllToDate

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DTIME_YYYYMMDDhhmmsslllToDate(int in_year, int in_month, int in_day,
	int in_hour, int in_minute, int in_second, int in_millisecond,
	DTIME *dtime_ptr, char *error_text)
#else
int DTIME_YYYYMMDDhhmmsslllToDate(in_year, in_month, in_day, in_hour,
	in_minute, in_second, in_millisecond, dtime_ptr, error_text)
int    in_year;
int    in_month;
int    in_day;
int    in_hour;
int    in_minute;
int    in_second;
int    in_millisecond;
DTIME *dtime_ptr;
char  *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((ymdok(in_year, in_month, in_day) != DATFUNCS_TRUE) ||
		(hourok(in_hour) != DATFUNCS_TRUE)                   ||
		(minuteok(in_minute) != DATFUNCS_TRUE)               ||
		(secondok(in_second) != DATFUNCS_TRUE)               ||
		(millisecondok(in_millisecond) != DATFUNCS_TRUE)) {
		if (error_text != NULL) {
			if (yearok(in_year) != DATFUNCS_TRUE)
				sprintf(error_text, "Invalid year (%d).", in_year);
			else if (monthok(in_month) != DATFUNCS_TRUE)
				sprintf(error_text, "Invalid month (%d).", in_month);
			else if (ymdok(in_year, in_month, in_day) != DATFUNCS_TRUE)
				sprintf(error_text, "Invalid day (%d) for year %d, month %d.",
					in_day, in_year, in_month);
			else if (hourok(in_hour) != DATFUNCS_TRUE)
				sprintf(error_text, "Invalid hour (%d).", in_hour);
			else if (minuteok(in_minute) != DATFUNCS_TRUE)
				sprintf(error_text, "Invalid minute (%d).", in_minute);
			else if (secondok(in_second) != DATFUNCS_TRUE)
				sprintf(error_text, "Invalid second (%d).", in_second);
			else
				sprintf(error_text, "Invalid millisecond (%d).", in_millisecond);
		}
		return_code = DATFUNCS_FAILURE;
	}
	else {
		dtime_ptr->julian_date  = ymdtojul(in_year, in_month, in_day);
		dtime_ptr->milliseconds =
			(((unsigned long) in_hour) * (60L * 60L * 1000L)) +
			(((unsigned long) in_minute) * (60L * 1000L)) +
			(((unsigned long) in_second) * 1000L) +
			((unsigned long) in_millisecond);
		return_code             = DATFUNCS_SUCCESS;
	}

	return(return_code);
}
/* *********************************************************************** */

