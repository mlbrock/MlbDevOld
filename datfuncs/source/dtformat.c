/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats a DTIME structure as a human-readable string.

	Revision History	:	1994-01-24 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <string.h>
 
#include <strfuncs.h>

#include "datfunci.h"

/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* NOTE:BOH

	NAME			:	DTIME_FormatDate

	SYNOPSIS		:	formatted_date_string = DTIME_FormatDate(in_date,
							format_string, out_string);

						char  *formatted_date_string;

						const DTIME *in_date;

						const char  *format_string;

						char        *out_string;

	DESCRIPTION	:	

   PARAMETERS  :  Parameters to this function are as follow:

   RETURNS     :  Returns from this function are as follow:

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

	OUTPUT INDEX:	DTIME_FormatDate
						Date Functions:Formatting Functions:DTIME_FormatDate
						DATFUNCS Functions:See Date Functions

	PUBLISH XREF:	DTIME_FormatDate

	PUBLISH NAME:	DTIME_FormatDate

	ENTRY CLASS	:	Date Functions:Formatting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *DTIME_FormatDate(const DTIME *in_date, const char *format_string,
	char *out_string)
#else
char *DTIME_FormatDate(in_date, format_string, out_string)
const DTIME *in_date;
const char  *format_string;
char        *out_string;
#endif /* #ifndef NARGS */
{
   int    tmp_value = 0;
	int    tmp_year;
	int    tmp_month;
	int    tmp_day;
	char  *tmp_ptr;
	DTIME  tmp_dtime;

	in_date       = (in_date == NULL) ? DTIME_NowUTC(&tmp_dtime) : in_date;
	format_string = ((format_string == NULL) || (!(*format_string))) ?
		DATFUNCS_DEFAULT_DTIME_FORMAT : format_string;
	tmp_ptr       = out_string;
	*tmp_ptr      = '\0';

	jultoymd(in_date->julian_date, &tmp_year, &tmp_month, &tmp_day);

	while (*format_string) {
		if (*format_string == '\\') {
			format_string++;
			if (*format_string)
				*tmp_ptr++ = *format_string++;
		}
		else if (!strncmp(format_string, "CCCC", 4)) {
			tmp_value      = tmp_year / 100;
			*tmp_ptr++     = ((char) ('0' + (tmp_value / 1000)));
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 1000) / 100)));
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 4;
		}
		else if (*format_string == 'C') {
			if ((tmp_value  = getcentury(in_date->julian_date)) > 99)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 1000) / 100)));
			if ((tmp_value  = getcentury(in_date->julian_date)) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if (!strncmp(format_string, "YYYY", 4)) {
			tmp_value      = tmp_year;
			*tmp_ptr++     = ((char) ('0' + (tmp_year / 1000)));
			*tmp_ptr++     = ((char) ('0' + ((tmp_year % 1000) / 100)));
			*tmp_ptr++     = ((char) ('0' + ((tmp_year % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_year % 10)));
			format_string += 4;
		}
		else if (!strncmp(format_string, "YYY", 3)) {
			tmp_value      = tmp_year;
			*tmp_ptr++     = ((char) ('0' + ((tmp_year % 1000) / 100)));
			*tmp_ptr++     = ((char) ('0' + ((tmp_year % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_year % 10)));
			format_string += 3;
		}
		else if (!strncmp(format_string, "YY", 2)) {
			tmp_value      = tmp_year;
			*tmp_ptr++     = ((char) ('0' + ((tmp_year % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_year % 10)));
			format_string += 2;
		}
		else if (*format_string == 'Y') {
			tmp_value  = tmp_year;
			*tmp_ptr++ = ((char) ('0' + (tmp_year % 10)));
			format_string++;
		}
		else if ((!strncmp(format_string, "MMMM", 4)) ||
			(!strncmp(format_string, "Mmmm", 4)) ||
			(!strncmp(format_string, "mmmm", 4))) {
			getmname(tmp_value = tmp_month, tmp_ptr, 1);
			if (!strncmp(format_string, "MMMM", 4))
				upper(tmp_ptr);
			else if (!strncmp(format_string, "mmmm", 4))
				lower(tmp_ptr);
			format_string += 4;
			tmp_ptr       += strlen(tmp_ptr);
		}
		else if ((!strncmp(format_string, "MMM", 3)) ||
			(!strncmp(format_string, "Mmm", 3)) ||
			(!strncmp(format_string, "mmm", 3))) {
			getmname(tmp_value = tmp_month, tmp_ptr, 0);
			if (!strncmp(format_string, "MMM", 3))
				upper(tmp_ptr);
			else if (!strncmp(format_string, "mmm", 3))
				lower(tmp_ptr);
			format_string += 3;
			tmp_ptr       += strlen(tmp_ptr);
		}
		else if (!strncmp(format_string, "MM", 2)) {
			tmp_value      = tmp_month;
			*tmp_ptr++     = ((char) ('0' + ((tmp_month % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_month % 10)));
			format_string += 2;
		}
		else if (*format_string == 'M') {
			if ((tmp_value = tmp_month) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if ((!strncmp(format_string, "DDDD", 4)) ||
			(!strncmp(format_string, "Dddd", 4)) ||
			(!strncmp(format_string, "dddd", 4))) {
			tmp_value = getdow(in_date->julian_date);
			downame(tmp_value, tmp_ptr);
			if (!strncmp(format_string, "DDDD", 4))
				upper(tmp_ptr);
			else if (!strncmp(format_string, "dddd", 4))
				lower(tmp_ptr);
			format_string += 4;
			tmp_ptr       += strlen(tmp_ptr);
		}
		else if ((!strncmp(format_string, "DDD", 3)) ||
			(!strncmp(format_string, "Ddd", 3)) ||
			(!strncmp(format_string, "ddd", 3))) {
			tmp_value = getdow(in_date->julian_date);
			downame(tmp_value, tmp_ptr);
			*(tmp_ptr + 3) = '\0';
			if (!strncmp(format_string, "DDD", 3))
				upper(tmp_ptr);
			else if (!strncmp(format_string, "ddd", 3))
				lower(tmp_ptr);
			format_string += 3;
			tmp_ptr       += strlen(tmp_ptr);
		}
		else if (!strncmp(format_string, "DD", 2)) {
			tmp_value      = tmp_day;
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 2;
		}
		else if (*format_string == 'D') {
			if ((tmp_value = tmp_day) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if (!strncmp(format_string, "HH", 2)) {
			tmp_value      = gethour(in_date->milliseconds);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 2;
		}
		else if (*format_string == 'H') {
			if ((tmp_value = gethour(in_date->milliseconds)) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if (!strncmp(format_string, "hh", 2)) {
			tmp_value      = gethour12(in_date->milliseconds);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 2;
		}
		else if (*format_string == 'h') {
			if ((tmp_value = gethour12(in_date->milliseconds)) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if (!strncmp(format_string, "NN", 2)) {
			tmp_value      = getminute(in_date->milliseconds);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 2;
		}
		else if (*format_string == 'N') {
			if ((tmp_value = getminute(in_date->milliseconds)) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if (!strncmp(format_string, "SS", 2)) {
			tmp_value      = getsecond(in_date->milliseconds);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 2;
		}
		else if (*format_string == 'S') {
			if ((tmp_value = getsecond(in_date->milliseconds)) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if (!strncmp(format_string, "LLL", 3)) {
			tmp_value      = getmillisecond(in_date->milliseconds);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 1000) / 100)));
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 3;
		}
		else if (!strncmp(format_string, "L00", 3)) {
			tmp_value      = gethundredthsecond(in_date->milliseconds);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 3;
		}
		else if (!strncmp(format_string, "L0", 2)) {
			tmp_value      = gettenthsecond(in_date->milliseconds);
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 2;
		}
		else if (*format_string == 'L') {
			if ((tmp_value = getmillisecond(in_date->milliseconds)) > 99)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 1000) / 100)));
			if ((tmp_value = getmillisecond(in_date->milliseconds)) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if (*format_string == 'W') {
			*tmp_ptr++ = ((char) ('0' + (getdow(in_date->julian_date) + 1)));
			format_string++;
		}
		else if (!strncmp(format_string, "ww", 2)) {
			tmp_value      = getweek(in_date->julian_date);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 2;
		}
		else if (*format_string == 'w') {
			if ((tmp_value = getweek(in_date->julian_date)) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if (*format_string == 'Q') {
			*tmp_ptr++ = ((char) ('0' + ((tmp_value = getqtr(in_date->julian_date)) % 10)));
			format_string++;
		}
		else if ((!strncmp(format_string, "OO", 2)) ||
			(!strncmp(format_string, "Oo", 2)) ||
			(!strncmp(format_string, "oo", 2))) {
			ordinal(((unsigned int) tmp_value), tmp_ptr);
			if (!strncmp(format_string, "OO", 2))
				upper(tmp_ptr);
			else if (!strncmp(format_string, "Oo", 2))
				initcaps(tmp_ptr);
			else if (!strncmp(format_string, "oo", 2))
				lower(tmp_ptr);
			tmp_ptr       += strlen(tmp_ptr);
			format_string += 2;
		}
		else
			*tmp_ptr++ = *format_string++;
	}

	*tmp_ptr = '\0';

	return(out_string);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int    count_1;
	DTIME  test_dtime;
   char   date_buffer[1024];

	fprintf(stderr, "Test routine for 'DTIME_FormatDate()'\n");
	fprintf(stderr, "---- ------- --- --------------------\n\n");
	fprintf(stderr, "*** Using test date 1994-01-01 13:17:21.456 ***\n\n");

	test_dtime.julian_date  = ymdtojul(1994, 1, 1);
	test_dtime.milliseconds = ((unsigned long) ((13L * (60L * 60L * 1000L)) +
		(17L * 60L * 1000L) + (21L * 1000L) + 456L));

	if (argc == 1)
		printf("Using default format [%s]: %s\n", DATFUNCS_DEFAULT_DTIME_FORMAT,
			DTIME_FormatDate(&test_dtime, NULL, date_buffer));
	else {
		for (count_1 = 1; count_1 < argc; count_1++)
			printf("Using format [%s]: %s\n", argv[count_1],
				DTIME_FormatDate(&test_dtime, argv[count_1], date_buffer));
	}

	printf("\n");

	return(0);
}

#endif /* #ifdef TEST_MAIN */

