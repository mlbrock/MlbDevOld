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
								century.

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

	NAME			:	cndaymax

	SYNOPSIS		:	max_day_of_century = cndaymax(in_century);

						long max_day_of_century;

						int  in_century;

	DESCRIPTION	:	Returns the maximum day number of the specified century.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_century`` is the century for which maximum day
						of the century is to be returned.

   RETURNS     :  Returns from this function are as follow:

   					If the ``in_century`` parameter is valid, the maximum day
						of the century is returned.

						Otherwise, zero is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	cndaycnt
						mndaymax
						yrdaymax

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2014 Michael L. Brock

	OUTPUT INDEX:	cndaymax
						Date Functions:Day Count Functions:cndaymax
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	cndaymax

	PUBLISH NAME:	cndaymax

	ENTRY CLASS	:	Date Functions:Day Count Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
long cndaymax(int in_century)
#else
long cndaymax(in_century)
int in_century;
#endif /* #ifndef NARGS */
{
	return(((in_century < DATFUNCS_MIN_YEAR) ||
		(in_century > DATFUNCS_MAX_YEAR)) ? 0L : (365L * 100L) +
		(24L + ((long) ((isleapyr((in_century / 100) * 100)) ? 1 : 0))));
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
	long         max_century_day;
	long         base_max_century_day;

	fprintf(stderr, "Test routine for function 'cndaymax()'\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-PRINT")) {
			print_flag = DATFUNCS_TRUE;
			break;
		}
	}

	for (count_1 = ((DATFUNCS_MIN_YEAR / 100) * 100);
		count_1 <= DATFUNCS_MAX_YEAR; count_1 += 100) {
		base_max_century_day  = 365L * 100L;
		base_max_century_day += 24L + ((long) ((isleapyr(count_1)) ? 1 : 0));
		if ((max_century_day = cndaymax(count_1)) != base_max_century_day) {
			printf(
		"Century %04d --- max century day = %5ld --- FAILED (should be %5ld)\n",
				count_1, max_century_day, base_max_century_day);
			failure_count++;
			return_code = DATFUNCS_FAILURE;
		}
		else if (print_flag == DATFUNCS_TRUE)
			printf("Century %04d --- max century day = %5ld\n", count_1,
				max_century_day);
	}

	if (return_code != DATFUNCS_SUCCESS)
		fprintf(stderr, "Test FAILED (%u failures).\n", failure_count);
	else
		fprintf(stderr, "Test SUCCEEDED.\n");

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

