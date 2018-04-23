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
								century.

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

	NAME			:	cndaycnt

	SYNOPSIS		:	days_in_century = cndaycnt(in_century)

						long days_in_century;

						int in_century;

	DESCRIPTION	:	Determines the number of days in the specified century.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_century`` is the century for which the number of
						days is to be returned.

   RETURNS     :  Returns from this function are as follow:

   					If the ``in_century`` parameter is valid, the number of
						days in the century is returned.

						Otherwise, zero is returned.

	NOTES			:	

	CAVEATS		:	For the century 1700 this function returns a number which
						may be at odds with your expectations.

	SEE ALSO		:	cndaymax
						mndaycnt
						yrdaycnt

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	cndaycnt
						Date Functions:Day Count Functions:cndaycnt
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	cndaycnt

	PUBLISH NAME:	cndaycnt

	ENTRY CLASS	:	Date Functions:Day Count Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
long cndaycnt(int in_century)
#else
long cndaycnt(in_century)
int in_century;
#endif /* #ifndef NARGS */
{
	in_century = (in_century / 100) * 100;

	return(cndaymax(in_century) - ((((in_century / 100) * 100) ==
		((DATFUNCS_GREGORIAN_YEAR / 100) * 100)) ?
		((long) DATFUNCS_GREGORIAN_MISSING) : 0L));
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
	long         days_in_century;
	long         base_days_in_century;

	fprintf(stderr, "Test routine for function 'cndaycnt()'\n\n");

	for (count_1 = 1; count_1 < argc; count_1++) {
		if (!stricmp(argv[count_1], "-PRINT")) {
			print_flag = DATFUNCS_TRUE;
			break;
		}
	}

	for (count_1 = ((DATFUNCS_MIN_YEAR / 100) * 100);
		count_1 <= DATFUNCS_MAX_YEAR; count_1 += 100) {
		base_days_in_century  = 365L * 100L;
		base_days_in_century += 24L + ((long) ((isleapyr(count_1)) ? 1 : 0));
		base_days_in_century -=
			((long) ((count_1 == ((DATFUNCS_GREGORIAN_YEAR / 100) * 100)) ?
			DATFUNCS_GREGORIAN_MISSING : 0));
		if ((days_in_century = cndaycnt(count_1)) != base_days_in_century) {
			printf(
		"Century %04d --- days in century = %5ld --- FAILED (should be %5ld)\n",
				count_1, days_in_century, base_days_in_century);
			failure_count++;
			return_code = DATFUNCS_FAILURE;
		}
		else if (print_flag == DATFUNCS_TRUE)
			printf("Century %04d --- days in century = %5ld\n", count_1,
				days_in_century);
	}

	if (return_code != DATFUNCS_SUCCESS)
		fprintf(stderr, "Test FAILED (%u failures).\n", failure_count);
	else
		fprintf(stderr, "Test SUCCEEDED.\n");

	return(return_code);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

