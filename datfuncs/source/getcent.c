/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Get the number of the century of a given JULIAN date.

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

	NAME			:	getcentury

	SYNOPSIS		:	century = getcentury(in_julian);

						int    century;

						JULIAN in_julian;

	DESCRIPTION	:	Determines the number of the century of a given JULIAN date.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the JULIAN for which the century
						number is to be determined.

   RETURNS     :  Returns from this function are as follow:

	NOTES			:	

	CAVEATS		:	This function may return results which are at odds with the
						expectations of those persons untutored in the vagaries of
						the European calendar. This is because of the following
						historical reasons:

						(.) The first year of the Christian era (that is, A.D.,
						``anno Domini``, or ``After Dark``) is year 1, not zero.
						Therefore, the last year of a century is not the year numbered
						``99``, but the year following that year. The 21st century
						will therefore begin on January 1st, 2001.

						(.) Centuries are numbered beginning at 1, not zero. The
						first year of the Christian era (1 A.D.) is in the first
						century, not the ``zero``th one. This is the reason that
						the year ``1950`` is considered to be within the 20th
						century.

						For example, dates falling within the inclusive range of
						1801-01-01 through 1900-12-31 are part of the 19th century.
						Dates falling within the inclusive range of 1901-01-01
						through 2000-12-31 are part of the 20th century.

						You have been warned.

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	getcentury
						Date Functions:Get Date/Time Component Functions:getcentury
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	getcentury

	PUBLISH NAME:	getcentury

	ENTRY CLASS	:	Date Functions:Get Date/Time Component Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int getcentury(JULIAN in_julian)
#else
int getcentury(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	int tmp_year = getyear(in_julian);

	return(((tmp_year - 1) / 100) + 1);
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
	int          century;
	int          base_century;

	fprintf(stderr, "Test routine for function 'getcentury()'\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-PRINT")) {
			print_flag = DATFUNCS_TRUE;
			break;
		}
	}

	for (count_1 = DATFUNCS_MIN_YEAR; count_1 <= DATFUNCS_MAX_YEAR; count_1++) {
		base_century  = ((count_1 - 1) / 100) + 1;
		if ((century = getcentury(ymdtojul(count_1, 1, 1))) != base_century) {
			printf("Year %04d --- century = %2d --- FAILED (should be %2d)\n",
				count_1, century, base_century);
			failure_count++;
			return_code = DATFUNCS_FAILURE;
		}
		else if (print_flag == DATFUNCS_TRUE)
			printf("Year %04d --- century = %2d\n", count_1, century);
	}

	if (return_code != DATFUNCS_SUCCESS)
		fprintf(stderr, "Test FAILED (%u failures).\n", failure_count);
	else
		fprintf(stderr, "Test SUCCEEDED.\n");

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

