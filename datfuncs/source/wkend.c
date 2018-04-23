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
								specified week.

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

	NAME			:	wkend

	SYNOPSIS		:	end_of_week = wkend(in_year, in_week);

						int end_of_week;

						int in_year;

						int in_week;

	DESCRIPTION	:	Gets the ''JULIAN'' date for the last day of the
						specified week.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which this function is to
						determine the end of the week.

						(.) ``in_week`` is the week of ``in_year`` for which
						this function is to determine the end of the week.

						(-) Weeks are numbered beginning with ''1''. The number of
						weeks in a year may vary from year to year.

   RETURNS     :  Returns the ''JULIAN'' date equivalent of the end of the
						week specified by the ``in_year`` and ``in_week``
						parameters.

	NOTES			:	Use ``wkstart`` to get the first day of the week.

	CAVEATS		:	

	SEE ALSO		:	wkstart
						yrend
						qtrend
						mnend

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	wkend
						Date Functions:Start/End Determination Functions:wkend
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	wkend

	PUBLISH NAME:	wkend

	ENTRY CLASS	:	Date Functions:Start/End Determination Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN wkend(int in_year, int in_week)
#else
JULIAN wkend(in_year, in_week)
int in_year;
int in_week;
#endif /* #ifndef NARGS */
{
	int    tmp_week;
	JULIAN tmp_julian = ymdtojul(in_year, 12, 31);

	return(((in_week < 1) || ((tmp_week = getweek(tmp_julian)) < in_week)) ?
		((JULIAN) 0) : (in_week == tmp_week) ? tmp_julian :
		(wkstart(in_year, in_week + 1) - ((JULIAN) 1)));
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
	int          return_code   = DATFUNCS_SUCCESS;
	unsigned int failure_count = 0;
	int          print_flag    = DATFUNCS_FALSE;
	int          count_1;
	int          count_2;
	JULIAN       tmp_julian;
	int          max_week_count;
	int          week_number;
	int          dow;

	fprintf(stderr, "Test routine for function 'wkend()'\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-PRINT")) {
			print_flag = DATFUNCS_TRUE;
			break;
		}
	}

	for (count_1 = DATFUNCS_MIN_YEAR; count_1 <= DATFUNCS_MAX_YEAR; count_1++) {
		max_week_count = getweek(ymdtojul(count_1, 12, 31));
		for (count_2 = 1; count_2 <= max_week_count; count_2++) {
			tmp_julian = wkend(count_1, count_2);
			dow        = getdow(tmp_julian);
			if ((week_number = getweek(tmp_julian)) != count_2) {
				printf("Week %02d of %04d --- JULIAN = %11ld, week = %2d --- FAILED (week should be %2d)\n",
					count_2, count_1, tmp_julian, week_number, count_2);
				failure_count++;
				return_code = DATFUNCS_FAILURE;
			}
			else if ((count_2 == max_week_count) &&
				(tmp_julian != get1231(tmp_julian))) {
				printf("Week %02d of %04d --- JULIAN = %11ld, week = %2d, DOW = %d --- FAILED (JULIAN should be %11ld)\n",
					count_2, count_1, tmp_julian, week_number, dow,
					get1231(tmp_julian));
				failure_count++;
				return_code = DATFUNCS_FAILURE;
			}
			else if ((count_2 == max_week_count) &&
				(dow != getdow(get1231(tmp_julian)))) {
				printf("Week %02d of %04d --- JULIAN = %11ld, week = %2d, DOW = %d --- FAILED (DOW should be %2d)\n",
					count_2, count_1, tmp_julian, week_number, dow,
					getdow(get1231(tmp_julian)));
				failure_count++;
				return_code = DATFUNCS_FAILURE;
			}
			else if ((count_2 < max_week_count) &&
				((dow = getdow(tmp_julian)) > 0)) {
				printf("Week %02d of %04d --- JULIAN = %11ld, week = %2d, DOW = %d --- FAILED (DOW should be %2d)\n",
					count_2, count_1, tmp_julian, week_number, dow, 6);
				failure_count++;
				return_code = DATFUNCS_FAILURE;
			}
			else if (print_flag == DATFUNCS_TRUE)
				printf("Week %02d of %04d --- JULIAN = %11ld, week = %2d, DOW = %d\n",
					count_2, count_1, tmp_julian, week_number, dow);
		}
	}

	if (return_code != DATFUNCS_SUCCESS)
		fprintf(stderr, "Test FAILED (%u failures).\n", failure_count);
	else
		fprintf(stderr, "Test SUCCEEDED.\n");

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

