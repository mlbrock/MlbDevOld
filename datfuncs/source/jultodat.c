/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a JULIAN date to a 'JDATE' structure.

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

	NAME			:	jultodat

	SYNOPSIS		:	return_code = jultodat(in_julian, in_date);

						int     return_code;

						JULIAN  in_julian;

						JDATE  *in_date;

	DESCRIPTION	:	Converts a ''JULIAN'' date to a ''JDATE'' structure.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date to be converted
						by this function into a ''JDATE'' structure.

						(.) ``in_date`` is a pointer to the ''JDATE'' structure
						into which this function will place the date value
						equivalent of the ``in_julian`` parameter.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero DATFUNCS return codes if an error
						occurs.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	dattojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	jultodat
						Date Functions:Conversion Functions:jultodat
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jultodat

	PUBLISH NAME:	jultodat

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int jultodat(JULIAN in_julian, JDATE *in_date)
#else
int jultodat(in_julian, in_date)
JULIAN  in_julian;
JDATE  *in_date;
#endif /* #ifndef NARGS */
{
	return(jultoymd(in_julian, &in_date->year, &in_date->month,
		&in_date->day));
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

typedef struct {
	JULIAN julian_date;
	JDATE  jdate_date;
} JULTODAT_TEST_STRUCT;

JULTODAT_TEST_STRUCT TestList[] = {
	{	31729, { 1986, 11, 15 } },
	{  32507, { 1989, 01, 01 } },
	{	32871, { 1989, 12, 31 } },
	{	32872, { 1990, 01, 01 } },
	{	42687, { 2016, 11, 15 } },
};

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
int main()
{
	int    count_1;
	JDATE  temp_date;
	JULIAN temp_julian;
	JULIAN test_julian;

	fprintf(stderr, "Test routine for function 'jultodat()'\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		jultodat(TestList[count_1].julian_date, &temp_date);
		printf("%02u/%02u/%04u (%lu) = %02u/%02u/%04u\n",
			TestList[count_1].jdate_date.month,
			TestList[count_1].jdate_date.day,
			TestList[count_1].jdate_date.year,
			TestList[count_1].julian_date,
			temp_date.month,
			temp_date.day,
			temp_date.year);
	}

	temp_julian = 32507L;
	while (temp_julian < 32872L) {
		jultodat(temp_julian, &temp_date);
		if (temp_julian != (test_julian = dattojul(&temp_date)))
			fprintf(stderr, "Error on %02u/%02u/%04u (%lu/%lu)\n",
 				temp_date.month, temp_date.day, temp_date.year,
				temp_julian, test_julian);
		temp_julian++;
	}

	return(1);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

