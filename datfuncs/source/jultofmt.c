/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

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

#include <string.h>

#include <strfuncs.h>

#include "datfunci.h"

/*	*********************************************************************** */

/*	*********************************************************************** */
#ifndef NARGS
char *jultofmt(JULIAN in_julian, const char *format_string, char *out_string)
#else
char *jultofmt(in_julian, format_string, out_string)
JULIAN      in_julian;
const char *format_string;
char       *out_string;
#endif /* #ifndef NARGS */
{
   int   tmp_value = 0;
	char *tmp_ptr;

	format_string = ((format_string == NULL) || (!(*format_string))) ?
		DATFUNCS_DEFAULT_JULIAN_FORMAT : format_string;
	tmp_ptr       = out_string;
	*tmp_ptr      = '\0';

	while (*format_string) {
		if (*format_string == '\\') {
			format_string++;
			if (*format_string)
				*tmp_ptr++ = *format_string++;
		}
		else if (!strncmp(format_string, "CCCC", 4)) {
			tmp_value      = getyear(in_julian) / 100;
			*tmp_ptr++     = ((char) ('0' + (tmp_value / 1000)));
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 1000) / 100)));
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 4;
		}
		else if (*format_string == 'C') {
			if ((tmp_value  = getcentury(in_julian)) > 99)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 1000) / 100)));
			if ((tmp_value  = getcentury(in_julian)) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if (!strncmp(format_string, "YYYY", 4)) {
			tmp_value      = getyear(in_julian);
			*tmp_ptr++     = ((char) ('0' + (tmp_value / 1000)));
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 1000) / 100)));
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 4;
		}
		else if (!strncmp(format_string, "YYY", 3)) {
			tmp_value      = getyear(in_julian);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 1000) / 100)));
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 3;
		}
		else if (!strncmp(format_string, "YY", 2)) {
			tmp_value      = getyear(in_julian);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 2;
		}
		else if (*format_string == 'Y') {
			tmp_value  = getyear(in_julian);
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if ((!strncmp(format_string, "MMMM", 4)) ||
			(!strncmp(format_string, "Mmmm", 4)) ||
			(!strncmp(format_string, "mmmm", 4))) {
			tmp_value = getmonth(in_julian);
			getmname(tmp_value, tmp_ptr, 1);
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
			tmp_value = getmonth(in_julian);
			getmname(tmp_value, tmp_ptr, 0);
			if (!strncmp(format_string, "MMM", 3))
				upper(tmp_ptr);
			else if (!strncmp(format_string, "mmm", 3))
				lower(tmp_ptr);
			format_string += 3;
			tmp_ptr       += strlen(tmp_ptr);
		}
		else if (!strncmp(format_string, "MM", 2)) {
			tmp_value      = getmonth(in_julian);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 2;
		}
		else if (*format_string == 'M') {
			if ((tmp_value = getmonth(in_julian)) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if ((!strncmp(format_string, "DDDD", 4)) ||
			(!strncmp(format_string, "Dddd", 4)) ||
			(!strncmp(format_string, "dddd", 4))) {
			tmp_value = getdow(in_julian);
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
			tmp_value = getdow(in_julian);
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
			tmp_value      = getday(in_julian);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 2;
		}
		else if (*format_string == 'D') {
			if ((tmp_value = getday(in_julian)) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if (*format_string == 'W') {
			*tmp_ptr++ = ((char) ('0' + (getdow(in_julian) + 1)));
			format_string++;
		}
		else if (!strncmp(format_string, "ww", 2)) {
			tmp_value      = getweek(in_julian);
			*tmp_ptr++     = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++     = ((char) ('0' + (tmp_value % 10)));
			format_string += 2;
		}
		else if (*format_string == 'w') {
			if ((tmp_value = getweek(in_julian)) > 9)
				*tmp_ptr++ = ((char) ('0' + ((tmp_value % 100) / 10)));
			*tmp_ptr++ = ((char) ('0' + (tmp_value % 10)));
			format_string++;
		}
		else if (*format_string == 'Q') {
			*tmp_ptr++ = ((char) ('0' + ((tmp_value = getqtr(in_julian)) % 10)));
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
/*	*********************************************************************** */

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
	JULIAN test_julian;
   char   date_buffer[1024];

	fprintf(stderr, "Test routine for 'jultofmt()'\n");
	fprintf(stderr, "---- ------- --- ------------\n");
	fprintf(stderr, "*** Using test date 1994-01-01 ***\n\n");

	test_julian = ymdtojul(1994, 1, 1);

	if (argc == 1)
		printf("Using default format [%s]: %s\n", DATFUNCS_DEFAULT_JULIAN_FORMAT,
			jultofmt(test_julian, NULL, date_buffer));
	else {
		for (count_1 = 1; count_1 < argc; count_1++)
			printf("Using format [%s]: %s\n", argv[count_1],
				jultofmt(test_julian, argv[count_1], date_buffer));
	}

	printf("\n");

	return(0);
}

#endif /* #ifdef TEST_MAIN */

