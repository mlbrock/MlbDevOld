/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the number of the last day of the specified
								combination of year and month.

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

	NAME			:	mndaymax

	SYNOPSIS		:	max_day_of_month = mndaymax(in_year, in_month);

						int max_day_of_month;

						int in_year;

						int in_month;

	DESCRIPTION	:	Returns the maximum day number of the specified month and
						year.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which the maximum day of
						the month is to be returned.

						(.) ``in_month`` is the month in the year ``in_year`` for
						which the maximum day of the month is to be returned.

   RETURNS     :  Returns from this function are as follow:

   					If the ``in_year`` and ``in_month`` parameters are valid,
						the maximum day of the month is returned.

						Otherwise, zero is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	mndaycnt
						cndaymax
						yrdaymax

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	mndaymax
						Date Functions:Day Count Functions:mndaymax
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	mndaymax

	PUBLISH NAME:	mndaymax

	ENTRY CLASS	:	Date Functions:Day Count Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mndaymax(int in_year, int in_month)
#else
int mndaymax(in_year, in_month)
int in_year;
int in_month;
#endif /* #ifndef NARGS */
{
	return(((yearok(in_year) == DATFUNCS_FALSE) ||
		(monthok(in_month) == DATFUNCS_FALSE)) ? 0 :
		(((in_month == 1) || (in_month == 3) ||
		(in_month == 5) || (in_month == 7) || (in_month == 8) ||
		(in_month == 10) || (in_month == 12)) ? 31 : ((in_month == 4) ||
		(in_month == 6) || (in_month == 9) || (in_month == 11)) ? 30 :
		(28 + ((isleapyr(in_year) == DATFUNCS_TRUE) ? 1 : 0))));
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
	int          max_month_day;
	int          base_max_month_day;

	fprintf(stderr, "Test routine for function 'mndaymax()'\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-PRINT")) {
			print_flag = DATFUNCS_TRUE;
			break;
		}
	}

	for (count_1 = DATFUNCS_MIN_YEAR; count_1 <= DATFUNCS_MAX_YEAR; count_1++) {
		for (count_2 = 1; count_2 <= 12; count_2++) {
			if ((count_2 == 1) || (count_2 == 3) || (count_2 == 5) ||
				(count_2 == 7) || (count_2 == 8) || (count_2 == 10) ||
				(count_2 == 12))
				base_max_month_day = 31;
			else if ((count_2 == 4) || (count_2 == 6) || (count_2 == 9) ||
				(count_2 == 11))
				base_max_month_day = 30;
			else
				base_max_month_day = 28 + ((isleapyr(count_1)) ? 1 : 0);
			if ((max_month_day = mndaymax(count_1, count_2)) !=
				base_max_month_day) {
				printf(
	"Month %02u/%04d --- max month day = %2d --- FAILED (should be %2d)\n",
					count_2, count_1, max_month_day, base_max_month_day);
				failure_count++;
				return_code = DATFUNCS_FAILURE;
			}
			else if (print_flag == DATFUNCS_TRUE)
				printf("Month %02u/%04d --- max month day = %2d\n",
					count_2, count_1, max_month_day);
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

