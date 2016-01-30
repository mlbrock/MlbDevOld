/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a 'JDATE' structure to a 'JULIAN'.

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

	NAME			:	dattojul

	SYNOPSIS		:	out_julian = dattojul(in_date);

						JULIAN       out_julian;

						const JDATE *in_date;

	DESCRIPTION	:	Converts a structure of type ''JDATE'' to a ''JULIAN''.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_date`` is a pointer to the structure of type
						''JDATE'' to be converted to a ''JULIAN''.

   RETURNS     :  The ''JULIAN'' date.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	jultodat

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	dattojul
						Date Functions:Conversion Functions:dattojul
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	dattojul

	PUBLISH NAME:	dattojul

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
JULIAN dattojul(const JDATE *in_date)
#else
JULIAN dattojul(in_date)
const JDATE *in_date;
#endif /* #ifndef NARGS */
{
	return(ymdtojul(in_date->year, in_date->month, in_date->day));
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <memory.h>
#include <stdio.h>

JDATE TestDateList[][2] = {
	{ { 1900, 1, 1 }, { 1900, 3, 1 } },
	{ { 1988, 1, 1 }, { 1988, 3, 1 } },
	{ { 1988, 1, 1 }, { 1989, 1, 1 } },
	{ { 1989, 1, 1 }, { 1989, 3, 1 } },
	{ { 1989, 1, 1 }, { 1989,12,31 } },
	{ { 1989, 1, 1 }, { 1990, 1, 1 } },
	{ { 1986,11,15 }, { 2016,11,15 } }
};

COMPAT_FN_DECL(int main, (void));

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
int main()
{
	int    count_1;
	int    count_2;
	JULIAN j_list[2];
	JDATE  temp_date;

	fprintf(stderr, "Test routine for function 'dattojul()'\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestDateList) /
		sizeof(TestDateList[0])); count_1++) {
		printf("Days between ");
		for (count_2 = 0; count_2 < 2; count_2++) {
			printf("%02u/%02u/%04u (%05lu[",
				TestDateList[count_1][count_2].month,
				TestDateList[count_1][count_2].day,
				TestDateList[count_1][count_2].year,
				j_list[count_2] = dattojul(&(TestDateList[count_1][count_2])));
			jultodat(j_list[count_2], &temp_date);
			printf("%s])", (!memcmp((char *) &(TestDateList[count_1][count_2]),
				(char *) &temp_date, sizeof(temp_date))) ? "Y" : "N");
			printf("%s", (!count_2) ? " and " : " : ");
		}
		printf("%10ld\n", j_list[1] - j_list[0]);
	}

	for (count_1 = 0; count_1 < (sizeof(TestDateList) /
		sizeof(TestDateList[0])); count_1++) {
		for (count_2 = 0; count_2 < 2; count_2++) {
			printf("Using 'dattojul()' : ");
			printf("%02u/%02u/%04u (%05lu)\n",
				TestDateList[count_1][count_2].month,
				TestDateList[count_1][count_2].day,
				TestDateList[count_1][count_2].year,
				j_list[count_2] = dattojul(&(TestDateList[count_1][count_2])));
			jultodat(j_list[count_2], &temp_date);
			printf("      'jultodat()' : ");
			printf("%02u/%02u/%04u (%05lu)\n\n",
				temp_date.month,
				temp_date.day,
				temp_date.year,
				j_list[count_2]);
		}
	}


	return(1);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

