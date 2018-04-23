/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a JULIAN date to three integers which
								represent year, month, and day.

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

	NAME			:	jultoymd

	SYNOPSIS		:	return_code = jultoymd(in_julian, out_year_ptr,
							out_month_ptr, out_day_ptr);

						int     return_code;

						JULIAN  in_julian;

						int    *out_year_ptr;

						int    *out_month_ptr;

						int    *out_day_ptr;

	DESCRIPTION	:	Converts a ''JULIAN'' date to three integers which
						represent the year, month, and day.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_julian`` is the ''JULIAN'' date to be converted
						by this function into its year, month, and day components.

						(.) ``out_year_ptr`` is a pointer to the ''int'' into which
						this function will place the year component of the
						``in_julian`` date parameter.

						(.) ``out_month_ptr`` is a pointer to the ''int'' into which
						this function will place the month component of the
						``in_julian`` date parameter.

						(.) ``out_day_ptr`` is a pointer to the ''int'' into which
						this function will place the day component of the
						``in_julian`` date parameter.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DATFUNCS_SUCCESS'' if no error occurs.

						(.) One of the non-zero DATFUNCS return codes if an error
						occurs.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	ymdtojul
						fixed_ymdtojul

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2018 Michael L. Brock

	OUTPUT INDEX:	jultoymd
						Date Functions:Conversion Functions:jultoymd
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	jultoymd

	PUBLISH NAME:	jultoymd

	ENTRY CLASS	:	Date Functions:Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int jultoymd(JULIAN in_julian, int *out_year_ptr, int *out_month_ptr,
	int *out_day_ptr)
#else
int jultoymd(in_julian, out_year_ptr, out_month_ptr, out_day_ptr)
JULIAN  in_julian;
int    *out_year_ptr;
int    *out_month_ptr;
int    *out_day_ptr;
#endif /* #ifndef NARGS */
{
	int  return_code = DATFUNCS_SUCCESS;
	long century_days;
	int  year_days;
	int  month_days;

	if ((in_julian < DATFUNCS_MIN_JULIAN) ||
		(in_julian > DATFUNCS_MAX_JULIAN)) {
		*out_year_ptr  = 0;
		*out_month_ptr = 0;
		*out_day_ptr   = 0;
		return_code    = DATFUNCS_FAILURE;
	}
	else if (in_julian < ((JULIAN) 0)) {
		*out_year_ptr  = 1899;
		*out_month_ptr = 12;
		*out_day_ptr   = 1;
		in_julian = ((in_julian >= ((JULIAN) 0)) ? in_julian :
			(((JULIAN) 0) - in_julian)) - 1;
		while (in_julian >= (century_days = cndaycnt(*out_year_ptr))) {
			in_julian     -= ((JULIAN) century_days);
			*out_year_ptr -= 100;
		}
		while ((*out_year_ptr > DATFUNCS_MIN_YEAR) &&
			(in_julian >= (year_days = yrdaycnt(*out_year_ptr)))) {
			in_julian -= ((JULIAN) year_days);
			(*out_year_ptr)--;
		}
		while (in_julian >= (month_days = mndaycnt(*out_year_ptr,
			*out_month_ptr))) {
			in_julian -= ((JULIAN) month_days);
			(*out_month_ptr)--;
		}
		*out_day_ptr = (month_days - ((int) in_julian)) +
			(((*out_year_ptr == DATFUNCS_GREGORIAN_YEAR) &&
			(*out_month_ptr == DATFUNCS_GREGORIAN_MONTH) &&
			((month_days - ((int) in_julian)) >=
			DATFUNCS_GREGORIAN_FIRST_DAY)) ? DATFUNCS_GREGORIAN_MISSING : 0);
	}
	else {
		*out_year_ptr  = 1900;
		*out_month_ptr = 1;
		*out_day_ptr   = 1;
		while (in_julian >= (century_days = cndaycnt(*out_year_ptr))) {
			in_julian     -= ((JULIAN) century_days);
			*out_year_ptr += 100;
		}
		while (in_julian >= (year_days = yrdaycnt(*out_year_ptr))) {
			in_julian -= ((JULIAN) year_days);
			(*out_year_ptr)++;
		}
		while (in_julian >= (month_days = mndaycnt(*out_year_ptr,
			*out_month_ptr))) {
			in_julian -= ((JULIAN) month_days);
			(*out_month_ptr)++;
		}
		*out_day_ptr = (!in_julian) ? 1 : (((int) in_julian) + 1);
	}

	return(return_code);
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
	int    year;
	int    month;
	int    day;
	JULIAN tmp_julian;
	JULIAN test_julian;

	fprintf(stderr, "Test routine for function 'jultoymd()'\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		jultoymd(TestList[count_1].julian_date, &year, &month, &day);
		printf("%02u/%02u/%04u (%lu) = %02u/%02u/%04u\n",
			TestList[count_1].jdate_date.month,
			TestList[count_1].jdate_date.day,
			TestList[count_1].jdate_date.year,
			TestList[count_1].julian_date,
			month,
			day,
			year);
	}

	tmp_julian = 32507L;
	while (tmp_julian < 32872L) {
		jultoymd(tmp_julian, &year, &month, &day);
		if (tmp_julian != (test_julian = ymdtojul(year, month, day)))
			fprintf(stderr, "Error on %02u/%02u/%04u (%lu/%lu)\n",
 				month, day, year, tmp_julian, test_julian);
		tmp_julian++;
	}

	return(1);
}
/*	*********************************************************************** */

#endif /* #ifdef TEST_MAIN */

