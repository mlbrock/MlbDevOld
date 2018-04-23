/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the actual/actual day count between two JULIAN
								dates.

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

	NAME			:	dcactact

	SYNOPSIS		:	julian_day_difference = dcactact(julian_1, julian_2)

						long   julian_day_difference;

						JULIAN julian_1;

						JULIAN julian_2;

	DESCRIPTION	:	Calculates the actual/actual day-count basis difference
						between two JULIAN dates.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``julian_1`` is the first JULIAN for which the
						calculation is to be performed.

						(.) ``julian_2`` is the second JULIAN for which the
						calculation is to be performed.

   RETURNS     :  Returns from this function are as follow:

						The actual/actual day-count basis difference between the
						two dates.

	NOTES			:	This function is present in the library only for the
						purpose of maintaining orthagonality. Because JULIAN
						dates are the actual number of days from the library
						epoch, this routine is equivalent to subtracting one
						JULIAN from another.

						The difference between two JULIAN dates which are equal to
						each other is zero.

	CAVEATS		:	

	SEE ALSO		:	dc30360

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	dcactact
						Date Functions:Day Count Functions:dcactact
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	dcactact

	PUBLISH NAME:	dcactact

	ENTRY CLASS	:	Date Functions:Day Count Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
long dcactact(JULIAN julian_1, JULIAN julian_2)
#else
long dcactact(julian_1, julian_2)
JULIAN julian_1;
JULIAN julian_2;
#endif /* #ifndef NARGS */
{
	return(julian_2 - julian_1);
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

char *DayCountName[] = {
	"Actual/Actual",
	"30/360",
	"Actual/360",
	"Actual/365"
};

typedef struct {
	JDATE date_value[2];
	long  day_count[2];
} DAY_COUNT_TEST_DATA;

DAY_COUNT_TEST_DATA TestList[] = {
	{ { { 1985,  1, 31 }, { 1986,  3, 16 } }, { 409, 406 } },
	{ { { 1986,  1,  1 }, { 1986,  2,  1 } }, {  31,  30 } },
	{ { { 1986,  2,  1 }, { 1986,  3,  1 } }, {  28,  30 } },
	{ { { 1988,  2,  1 }, { 1988,  3,  1 } }, {  29,  30 } },
	{ { { 1986,  1,  1 }, { 1987,  1,  1 } }, { 365, 360 } },
	{ { { 1986,  1, 15 }, { 1986,  2,  1 } }, {  17,  16 } },
	{ { { 1986,  2, 15 }, { 1986,  4,  1 } }, {  45,  46 } },
	{ { { 1986,  3, 31 }, { 1986,  4, 30 } }, {  30,  30 } },
	{ { { 1986,  3, 31 }, { 1986, 12, 31 } }, { 275, 270 } },
	{ { { 1986,  3, 15 }, { 1986,  6, 15 } }, {  92,  90 } },
	{ { { 1986, 11,  1 }, { 1987,  3,  1 } }, { 120, 120 } },
	{ { { 1986, 12, 31 }, { 1987,  2,  1 } }, {  32,  31 } },
	{ { { 1986,  7, 15 }, { 1986,  9, 15 } }, {  62,  60 } },
	{ { { 1986,  8, 21 }, { 1987,  4, 11 } }, { 233, 230 } },
	{ { { 1986,  3, 31 }, { 1986,  4,  1 } }, {   1,   1 } },
	{ { { 1986, 12, 15 }, { 1986, 12, 31 } }, {  16,  16 } },
	{ { { 1986, 12, 15 }, { 1986, 12, 30 } }, {  15,  15 } }
};

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
int main()
{
	int    count_1;
	int    day_count_type = DAY_COUNT_ACTUAL_ACTUAL;
	long   day_count;
	JULIAN temp_julian_1;
	JULIAN temp_julian_2;
	char   buffer_1[100];
	char   buffer_2[100];

	fprintf(stderr, "Test routine for function 'dcactact()'\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		temp_julian_1 = ymdtojul(TestList[count_1].date_value[0].year,
			TestList[count_1].date_value[0].month,
			TestList[count_1].date_value[0].day);
		temp_julian_2 = ymdtojul(TestList[count_1].date_value[1].year,
			TestList[count_1].date_value[1].month,
			TestList[count_1].date_value[1].day);
		jultostr(temp_julian_1, buffer_1);
		jultostr(temp_julian_2, buffer_2);
		printf("%02u Day count %s for %s - %s: %10ld ---> ", count_1,
		  	DayCountName[day_count_type], buffer_1, buffer_2,
			day_count = dcactact(temp_julian_1, temp_julian_2));
		if (day_count == TestList[count_1].day_count[day_count_type])
			printf("\tOK\n");
		else
			printf("\tWRONG --- %lu expected\n",
				TestList[count_1].day_count[day_count_type]);
	}

	return(1);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

