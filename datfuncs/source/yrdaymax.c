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
								year.

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

	NAME			:	yrdaymax

	SYNOPSIS		:	max_day_of_year = yrdaymax(in_year);

						int max_day_of_year;

						int in_year;

	DESCRIPTION	:	Returns the maximum day number of the specified year.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_year`` is the year for which the maximum day of
						the year is to be returned.

   RETURNS     :  Returns from this function are as follow:

   					If the ``in_year`` parameter is valid, the maximum day of
						the year is returned.

						Otherwise, zero is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	yrdaycnt
						cndaymax
						mndaymax

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	yrdaymax
						Date Functions:Day Count Functions:yrdaymax
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	yrdaymax

	PUBLISH NAME:	yrdaymax

	ENTRY CLASS	:	Date Functions:Day Count Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int yrdaymax(int in_year)
#else
int yrdaymax(in_year)
int in_year;
#endif /* #ifndef NARGS */
{
	return((yearok(in_year) == DATFUNCS_FALSE) ? 0 :
		(365 + ((isleapyr(in_year)) ? 1 : 0)));
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
	int          max_year_day;
	int          base_max_year_day;

	fprintf(stderr, "Test routine for function 'yrdaymax()'\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-PRINT")) {
			print_flag = DATFUNCS_TRUE;
			break;
		}
	}

	for (count_1 = DATFUNCS_MIN_YEAR; count_1 <= DATFUNCS_MAX_YEAR; count_1++) {
		base_max_year_day  = 365 + ((isleapyr(count_1)) ? 1 : 0);
		if ((max_year_day = yrdaymax(count_1)) != base_max_year_day) {
			printf("Year %04d --- max year day = %3d --- FAILED (should be %3d)\n",
				count_1, max_year_day, base_max_year_day);
			failure_count++;
			return_code = DATFUNCS_FAILURE;
		}
		else if (print_flag == DATFUNCS_TRUE)
			printf("Year %04d --- max year day = %3d\n", count_1, max_year_day);
	}

	if (return_code != DATFUNCS_SUCCESS)
		fprintf(stderr, "Test FAILED (%u failures).\n", failure_count);
	else
		fprintf(stderr, "Test SUCCEEDED.\n");

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

