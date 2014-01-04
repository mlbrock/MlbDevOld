/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the actual number of days for the specified
								combination of year and month.

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

	NAME			:	mndaycnt

	SYNOPSIS		:	max_day_of_month = mndaycnt(in_year, in_month);

						int max_day_of_month;

						int in_year;

						int in_month;

	DESCRIPTION	:	Determines the number of days in the specified month and
						year.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which the number of days in
						the month is to be returned.

						(.) ``in_month`` is the month in the year ``in_year`` for
						which the number of days is to be returned.

   RETURNS     :  Returns from this function are as follow:

   					If the ``in_year`` and ``in_month`` parameters are valid,
						the number of days in the month is returned.

						Otherwise, zero is returned.

	NOTES			:	

	CAVEATS		:	For the month of September, 1752 this function returns a
						number which may be at odds with your expectations.

	SEE ALSO		:	mndaymax
						cndaycnt
						yrdaycnt

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2014 Michael L. Brock

	OUTPUT INDEX:	mndaycnt
						Date Functions:Day Count Functions:mndaycnt
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	mndaycnt

	PUBLISH NAME:	mndaycnt

	ENTRY CLASS	:	Date Functions:Day Count Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int mndaycnt(int in_year, int in_month)
#else
int mndaycnt(in_year, in_month)
int in_year;
int in_month;
#endif /* #ifndef NARGS */
{
	return(mndaymax(in_year, in_month) -
		(((in_year == DATFUNCS_GREGORIAN_YEAR) &&
		(in_month == DATFUNCS_GREGORIAN_MONTH)) ?
		DATFUNCS_GREGORIAN_MISSING : 0));
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
	int          days_in_month;
	int          base_days_in_month;

	fprintf(stderr, "Test routine for function 'mndaycnt()'\n\n");

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
				base_days_in_month = 31;
			else if ((count_2 == 4) || (count_2 == 6) || (count_2 == 9) ||
				(count_2 == 11))
				base_days_in_month = 30;
			else
				base_days_in_month = 28 + isleapyr(count_1);
			base_days_in_month -= ((count_1 == DATFUNCS_GREGORIAN_YEAR) &&
				(count_2 == DATFUNCS_GREGORIAN_MONTH)) ?
				DATFUNCS_GREGORIAN_MISSING : 0;
			if ((days_in_month = mndaycnt(count_1, count_2)) !=
				base_days_in_month) {
				printf(
			"Month %02u/%04d --- days in month = %2d --- FAILED (should be %2d)\n",
					count_2, count_1, days_in_month, base_days_in_month);
				failure_count++;
				return_code = DATFUNCS_FAILURE;
			}
			else if (print_flag == DATFUNCS_TRUE)
				printf("Month %02u/%04d --- days in month = %2d\n",
					count_2, count_1, days_in_month);
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

