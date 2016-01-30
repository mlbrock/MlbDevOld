/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts JULIAN date to an unsigned long.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "datfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	jultolon

	SYNOPSIS		:	ulong_date = jultolon(in_julian);

						unsigned long ulong_date;

						JULIAN        in_julian;

	DESCRIPTION	:	Converts ''JULIAN'' date to an ''unsigned long''.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date to be converted
						by this function into its ''unsigned long'' equivalent.

   RETURNS     :  Returns the ''unsigned long'' equivalent of the
						``in_julian`` parameter.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	lontojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	jultolon
						Date Functions:Conversion Functions:jultolon
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jultolon

	PUBLISH NAME:	jultolon

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
unsigned long jultolon(JULIAN in_julian)
#else
unsigned long jultolon(in_julian)
JULIAN in_julian;
#endif /* #ifndef NARGS */
{
	int tmp_year;
	int tmp_month;
	int tmp_day;

	jultoymd(in_julian, &tmp_year, &tmp_month, &tmp_day);

	return((((unsigned long) tmp_year) * 10000L) +
		(((unsigned long) tmp_month) * 100L) + ((unsigned long) tmp_day));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

typedef struct {
	JULIAN julian_date;
	JDATE  jdate_date;
} JULTOLON_TEST_STRUCT;

JULTOLON_TEST_STRUCT TestList[] = {
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
	int           count_1;
	JDATE         temp_date;
	JULIAN        temp_julian;
	JULIAN        test_julian;
	unsigned long temp_ulong;

	fprintf(stderr, "Test routine for function 'jultolon()'\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		temp_ulong = jultolon(TestList[count_1].julian_date);
		lontodat(temp_ulong, &temp_date);
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
		temp_ulong = jultolon(temp_julian);
		lontodat(temp_ulong, &temp_date);
		if (temp_julian != (test_julian = lontojul(temp_ulong)))
			fprintf(stderr, "Error on %02u/%02u/%04u (%lu/%lu)\n",
 				temp_date.month, temp_date.day, temp_date.year,
				temp_julian, test_julian);
		temp_julian++;
	}

	return(1);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

