/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts three integers representing year, month, and
								day to a JULIAN date.

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

	NAME			:	ymdtojul

	SYNOPSIS		:	julian_date = ymdtojul(in_year, in_month, in_day);

						JULIAN julian_date;

						int    in_year;

						int    in_month;

						int    in_day;

	DESCRIPTION	:	Converts three integers representing year, month, and
						day to a ''JULIAN'' date.

						(.) ``in_year`` is the year to be converted by this
						function.

						(.) ``in_month`` is the month to be converted by this
						function.

						(.) ``in_day`` is the day to be converted by this function.

   PARAMETERS  :  Parameters to this function are as follow:

   RETURNS     :  Returns the ''JULIAN'' equivalent of the date represented
						by the ``in_year``, ``in_month``, and ``in_day`` parameters.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	jultoymd
						fixed_ymdtojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	ymdtojul
						Date Functions:Conversion Functions:ymdtojul
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	ymdtojul

	PUBLISH NAME:	ymdtojul

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN ymdtojul(int in_year, int in_month, int in_day)
#else
JULIAN ymdtojul(in_year, in_month, in_day)
int in_year;
int in_month;
int in_day;
#endif /* #ifndef NARGS */
{
	JULIAN tmp_julian = ((JULIAN) 0);
	int    tmp_year   = 1900;
	int    tmp_month  = 1;

	if (ymdok(in_year, in_month, in_day) == DATFUNCS_TRUE) {
		while (((tmp_year - 100) >= DATFUNCS_MIN_YEAR) &&
			(in_year <= (tmp_year - 100))) {
			tmp_julian -= ((JULIAN) cndaycnt(tmp_year - 100));
			tmp_year   -= 100;
		}
		while (((tmp_year + 100) <= DATFUNCS_MAX_YEAR) &&
			(in_year >= (tmp_year + 100))) {
			tmp_julian += ((JULIAN) cndaycnt(tmp_year));
			tmp_year   += 100;
		}
		while (in_year < tmp_year)
			tmp_julian -= ((JULIAN) yrdaycnt(--tmp_year));
		while (in_year > tmp_year)
			tmp_julian += ((JULIAN) yrdaycnt(tmp_year++));
		while (in_month > tmp_month)
			tmp_julian += ((JULIAN) mndaycnt(tmp_year, tmp_month++));
		tmp_julian += ((JULIAN) ((((tmp_year == DATFUNCS_GREGORIAN_YEAR) &&
			(tmp_month == DATFUNCS_GREGORIAN_MONTH) &&
			(in_day > DATFUNCS_GREGORIAN_LAST_DAY)) ?
			(in_day - DATFUNCS_GREGORIAN_MISSING) : in_day) - 1));
	}

	return(tmp_julian);
}
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	fixed_ymdtojul

	SYNOPSIS		:	julian_date = fixed_ymdtojul(in_year, in_month, in_day,
							implied_century, implied_year_break);

						JULIAN julian_date;

						int    in_year;

						int    in_month;

						int    in_day;

						int    implied_century;

						int    implied_year_break;

	DESCRIPTION	:	Converts three integers representing year, month, and
						day to a ''JULIAN'' date.

						If the ``year`` value does not contain the century
						portion, this function will use the ``implied_century``
						and ``implied_year_break`` parameters to determine the
						century.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year to be converted by this
						function.

						(.) ``in_month`` is the month to be converted by this
						function.

						(.) ``in_day`` is the day to be converted by this function.

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

   RETURNS     :  Returns the ''JULIAN'' equivalent of the date represented
						by the ``in_year``, ``in_month``, and ``in_day`` parameters.

	NOTES			:	This function should check for the special case of
						February 29th as this could, in some cases, determine
						definitively the century to which a date belongs. This
						will be changed in a later release.

	CAVEATS		:	

	SEE ALSO		:	ymdtojul
						jultoymd

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	fixed_ymdtojul
						Date Functions:Conversion Functions:fixed_ymdtojul
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	fixed_ymdtojul

	PUBLISH NAME:	fixed_ymdtojul

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN fixed_ymdtojul(int in_year, int in_month, int in_day,
	int implied_century, int implied_year_break)
#else
JULIAN fixed_ymdtojul(in_year, in_month, in_day, implied_century,
	implied_year_break)
int in_year;
int in_month;
int in_day;
int implied_century;
int implied_year_break;
#endif /* #ifndef NARGS */
{
	return(ymdtojul(fixyear(in_year, implied_century, implied_year_break),
		in_month, in_day));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

#include <strfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int            return_code   = DATFUNCS_SUCCESS;
	int            first_year    = DATFUNCS_MIN_YEAR;
	int            last_year     = DATFUNCS_MAX_YEAR;
	unsigned int   failure_count = 0;
	int            print_flag    = DATFUNCS_FALSE;
	unsigned long  century_days  = 0L;
	unsigned long  total_days    = 0L;
	double         total_time    = 0.0;
	double         century_time;
	JULIAN         previous_year;
	JULIAN         tmp_julian;
	int            count_1;
	int            count_2;
	int            count_3;
	JDATE          tmp_jdate;
	struct timeval start_time;
	struct timeval end_time;

	fprintf(stderr, "Test routine for function 'ymdtojul()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-PRINT")) {
			print_flag = DATFUNCS_TRUE;
			break;
		}
	}

	fprintf(stderr, "Minimum Julian Date: %11ld (%4d-01-01)\n",
		ymdtojul(first_year, 1, 1), first_year);
	fprintf(stderr, "Maximum Julian Date: %11ld (%4d-12-31)\n",
		ymdtojul(last_year, 12, 31), last_year);
	fprintf(stderr, "\n");

	previous_year = first_year;

	fprintf(stderr, "%s\n",
		"=== ===== ==== == ==== == =========== = =========== === ===");

	SDTIF_GetTimeUSecs(&start_time);

	for (count_1 = first_year; count_1 <= last_year; count_1++) {
		for (count_2 = 1; count_2 <= 12; count_2++) {
			for (count_3 = 1; count_3 <= mndaymax(count_1, count_2); count_3++) {
				if ((count_1 == DATFUNCS_GREGORIAN_YEAR) &&
					(count_2 == DATFUNCS_GREGORIAN_MONTH) &&
					(count_3 >= DATFUNCS_GREGORIAN_FIRST_DAY) &&
					(count_3 <= DATFUNCS_GREGORIAN_LAST_DAY))
					continue;
				century_days++;
				jultodat(tmp_julian = ymdtojul(count_1, count_2, count_3),
					&tmp_jdate);
				if ((count_1 != tmp_jdate.year) || (count_2 != tmp_jdate.month) ||
					(count_3 != tmp_jdate.day)) {
					printf(
"Date %04d-%02d-%02d --- julian = %11ld --- FAILED (returned %04d-%02d-%02d)\n",
						count_1, count_2, count_3, tmp_julian,
						tmp_jdate.year, tmp_jdate.month, tmp_jdate.day);
					failure_count++;
					return_code = DATFUNCS_FAILURE;
				}
				else if (print_flag == DATFUNCS_TRUE)
					printf("Date %04d-%02d-%02d --- julian = %11ld\n",
						count_1, count_2, count_3, tmp_julian);
			}
		}
		if ((((count_1 / 100) * 100) == count_1) &&
			(previous_year != count_1)) {
			SDTIF_GetTimeUSecs(&end_time);
			end_time.tv_sec   -= start_time.tv_sec;
			start_time.tv_sec  = 0L;
			century_time       = (((double) SDTIF_GET_TIMEVAL_USECS(&end_time)) -
				((double) SDTIF_GET_TIMEVAL_USECS(&start_time))) / 1000000.0;
			total_days        += century_days;
			total_time        += century_time;
			fprintf(stderr,
				"Did years %4ld to %4d in %11.6f / %11.6f per day\n",
				((long) previous_year), count_1, century_time,
				century_time / ((double) century_days));
			previous_year = count_1 + 1;
			century_days  = 0;
			SDTIF_GetTimeUSecs(&start_time);
		}
	}

	if ((((count_1 / 100) * 100) != count_1) &&
		(previous_year != count_1)) {
		SDTIF_GetTimeUSecs(&end_time);
		end_time.tv_sec   -= start_time.tv_sec;
		start_time.tv_sec  = 0L;
		century_time       = (((double) SDTIF_GET_TIMEVAL_USECS(&end_time)) -
			((double) SDTIF_GET_TIMEVAL_USECS(&start_time))) / 1000000.0;
		total_days        += century_days;
		total_time        += century_time;
		fprintf(stderr,
			"Did years %4d to %4d in %11.6f / %11.6f per day\n",
			previous_year, count_1, century_time,
			century_time / ((double) century_days));
	}

	fprintf(stderr, "%s\n",
		"--- ----- ---- -- ---- -- ----------- - ----------- --- ---");
	fprintf(stderr,
		"Did years %4d to %4d in %11.6f / %11.6f per day\n",
		first_year, last_year, total_time, total_time / ((double) total_days));
	fprintf(stderr, "%s\n",
		"=== ===== ==== == ==== == =========== = =========== === ===");

	if (return_code != DATFUNCS_SUCCESS)
		fprintf(stderr, "Test FAILED (%u failures).\n", failure_count);
	else
		fprintf(stderr, "Test SUCCEEDED.\n");

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

