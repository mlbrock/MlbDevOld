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
								year.

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

	NAME			:	yrdaycnt

	SYNOPSIS		:	days_in_year = yrdaycnt(in_year);

						int days_in_year;

						int in_year;

	DESCRIPTION	:	Determines the number of days in the specified year.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which the number of days in
						the year is to be returned.

   RETURNS     :  Returns from this function are as follow:

   					If the ``in_year`` parameter is valid, the number of days
						in the year is returned.

						Otherwise, zero is returned.

	NOTES			:	

	CAVEATS		:	For the year 1752 this function returns a number which
						may be at odds with your expectations.

	SEE ALSO		:	yrdaymax
						cndaycnt
						mndaycnt

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	yrdaycnt
						Date Functions:Day Count Functions:yrdaycnt
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	yrdaycnt

	PUBLISH NAME:	yrdaycnt

	ENTRY CLASS	:	Date Functions:Day Count Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int yrdaycnt(int in_year)
#else
int yrdaycnt(in_year)
int in_year;
#endif /* #ifndef NARGS */
{
	return(yrdaymax(in_year) - ((in_year == DATFUNCS_GREGORIAN_YEAR) ?
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
	int          days_in_year;
	int          base_days_in_year;

	fprintf(stderr, "Test routine for function 'yrdaycnt()'\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-PRINT")) {
			print_flag = DATFUNCS_TRUE;
			break;
		}
	}

	for (count_1 = DATFUNCS_MIN_YEAR; count_1 <= DATFUNCS_MAX_YEAR; count_1++) {
		base_days_in_year  = 365 + ((isleapyr(count_1)) ? 1 : 0);
		base_days_in_year -= (count_1 == DATFUNCS_GREGORIAN_YEAR) ?
			DATFUNCS_GREGORIAN_MISSING : 0;
		if ((days_in_year = yrdaycnt(count_1)) != base_days_in_year) {
			printf("Year %04d --- days in year = %3d --- FAILED (should be %3d)\n",
				count_1, days_in_year, base_days_in_year);
			failure_count++;
			return_code = DATFUNCS_FAILURE;
		}
		else if (print_flag == DATFUNCS_TRUE)
			printf("Year %04d --- days in year = %3d\n", count_1, days_in_year);
	}

	if (return_code != DATFUNCS_SUCCESS)
		fprintf(stderr, "Test FAILED (%u failures).\n", failure_count);
	else
		fprintf(stderr, "Test SUCCEEDED.\n");

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

