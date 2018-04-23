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

	NAME			:	wkstart

	SYNOPSIS		:	start_of_week = wkstart(in_year, in_week);

						int start_of_week;

						int in_year;

						int in_week;

	DESCRIPTION	:	Gets the ''JULIAN'' date for the first day of the
						specified week.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which this function is to
						determine the start of the week.

						(.) ``in_week`` is the week of ``in_year`` for which
						this function is to determine the start of the week.

						(-) Weeks are numbered beginning with ''1''. The number of
						weeks in a year may vary from year to year.

   RETURNS     :  Returns the ''JULIAN'' date equivalent of the start of the
						week specified by the ``in_year`` and ``in_week``
						parameters.

	NOTES			:	Use ``wkend`` to get the last day of the week.

	CAVEATS		:	

	SEE ALSO		:	wkend
						yrstart
						qtrstart
						mnstart

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	wkstart
						Date Functions:Start/End Determination Functions:wkstart
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	wkstart

	PUBLISH NAME:	wkstart

	ENTRY CLASS	:	Date Functions:Start/End Determination Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN wkstart(int in_year, int in_week)
#else
JULIAN wkstart(in_year, in_week)
int in_year;
int in_week;
#endif /* #ifndef NARGS */
{
	JULIAN tmp_julian = ymdtojul(in_year, 1, 1);

	return(((in_week < 1) ||
		(getweek(tmp_julian + ((JULIAN) (yrdaycnt(in_year) - 1))) < in_week)) ?
		((JULIAN) 0) : (in_week == 1) ? tmp_julian :
		(tmp_julian + ((JULIAN) (((in_week - 1) * 7) - getdow(tmp_julian)))));
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

	fprintf(stderr, "Test routine for function 'wkstart()'\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-PRINT")) {
			print_flag = DATFUNCS_TRUE;
			break;
		}
	}

	for (count_1 = DATFUNCS_MIN_YEAR; count_1 <= DATFUNCS_MAX_YEAR; count_1++) {
		max_week_count = getweek(ymdtojul(count_1, 12, 31));
		for (count_2 = 1; count_2 <= max_week_count; count_2++) {
			tmp_julian = wkstart(count_1, count_2);
			dow        = getdow(tmp_julian);
			if ((week_number = getweek(tmp_julian)) != count_2) {
				printf("Week %02d of %04d --- JULIAN = %11ld, week = %2d --- FAILED (week should be %2d)\n",
					count_2, count_1, tmp_julian, week_number, count_2);
				failure_count++;
				return_code = DATFUNCS_FAILURE;
			}
			else if ((count_2 == 1) && (tmp_julian != get0101(tmp_julian))) {
				printf("Week %02d of %04d --- JULIAN = %11ld, week = %2d, DOW = %d --- FAILED (JULIAN should be %11ld)\n",
					count_2, count_1, tmp_julian, week_number, dow,
					get0101(tmp_julian));
				failure_count++;
				return_code = DATFUNCS_FAILURE;
			}
			else if ((count_2 == 1) && (dow != getdow(get0101(tmp_julian)))) {
				printf("Week %02d of %04d --- JULIAN = %11ld, week = %2d, DOW = %d --- FAILED (DOW should be %2d)\n",
					count_2, count_1, tmp_julian, week_number, dow,
					getdow(get0101(tmp_julian)));
				failure_count++;
				return_code = DATFUNCS_FAILURE;
			}
			else if ((count_2 > 1) && ((dow = getdow(tmp_julian)) > 0)) {
				printf("Week %02d of %04d --- JULIAN = %11ld, week = %2d, DOW = %d --- FAILED (DOW should be %2d)\n",
					count_2, count_1, tmp_julian, week_number, dow, 0);
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

