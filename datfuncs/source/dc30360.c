/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the 30/360 day count between two JULIAN dates.

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

	NAME			:	dc30360

	SYNOPSIS		:	julian_day_difference = dc30360(julian_1, julian_2);

						long   julian_day_difference;

						JULIAN julian_1;

						JULIAN julian_2;

	DESCRIPTION	:	Calculates the 30/360 day-count basis difference between
						two JULIAN dates.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``julian_1`` is the first JULIAN for which the
						calculation is to be performed.

						(.) ``julian_2`` is the second JULIAN for which the
						calculation is to be performed.

   RETURNS     :  Returns from this function are as follow:

						The 30/360 day-count basis difference between the two dates.

	NOTES			:	The difference between two JULIAN dates which are equal to
						each other is zero.

	CAVEATS		:	

	SEE ALSO		:	dcactact

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2016 Michael L. Brock

	OUTPUT INDEX:	dc30360
						Date Functions:Day Count Functions:dc30360
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	dc30360

	PUBLISH NAME:	dc30360

	ENTRY CLASS	:	Date Functions:Day Count Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
long dc30360(JULIAN julian_1, JULIAN julian_2)
#else
long dc30360(julian_1, julian_2)
JULIAN julian_1;
JULIAN julian_2;
#endif /* #ifndef NARGS */
{
	long   day_count  = 0L;
	long   sign_value = 1L;
	JULIAN temp_julian;
	JDATE  jdate_1;
	JDATE  jdate_2;

	if (julian_1 != julian_2) {
		if (julian_1 > julian_2) {
			sign_value  = -1;
			temp_julian = julian_1;
			julian_1    = julian_2;
			julian_2    = temp_julian;
		}
		jultodat(julian_1, &jdate_1);
		jultodat(julian_2, &jdate_2);
		jdate_1.day = (jdate_1.day == 31) ? 30 : jdate_1.day;
		jdate_1.day =
			((jdate_1.month == 2) && (jdate_1.day >= 28)) ? 30 :jdate_1.day;
		jdate_2.day =
			((jdate_2.day == 31) && (jdate_1.day == 30)) ? 30 :jdate_2.day;
		day_count  = ((((long) (jdate_2.year - jdate_1.year)) * 360L) +
			           (((long) (jdate_2.month - jdate_1.month)) * 30L) +
			            ((long) (jdate_2.day - jdate_1.day))) * sign_value;
	}

	return(day_count);
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
	int    day_count_type = DAY_COUNT_30_360;
	long   day_count;
	JULIAN temp_julian_1;
	JULIAN temp_julian_2;
	char   buffer_1[100];
	char   buffer_2[100];

	fprintf(stderr, "Test routine for function 'dc30360()'\n\n");

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
			day_count = dc30360(temp_julian_1, temp_julian_2));
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

