/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	System Date/Time Interface Facility (SDTIF) Module Source File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats 'time_t' time measurement values as
								local or GMT/UTC values in human-readable format.

	Revision History	:	1985-10-31 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1985 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "sdtifi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME        :  SDTIF_Format_time_t

	SYNOPSIS    :  string_ptr = SDTIF_Format_time_t(in_time, buffer);

						char         *string_ptr;

						const time_t *in_time;

						char         *buffer;

	DESCRIPTION :  Formats a ''time_t'' datum as an local time-value string
						with the following format:

						``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``

						Where:

						(.) ``yyyy`` represents the year.

						(.) ``mm`` represents the month.

						(.) ``dd`` represents the day of the month.

						(.) ``hh`` represents the hour.

						(.) ``mm`` represents the minute.

						(.) ``ss`` represents the second.

						Note that there is a space (ASCII 32) between the
						``dd`` and ``hh`` components of the string.

	PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the structure of type ''time_t''
						to be formatted as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``buffer`` points to the string allocated by the
						invoking function to hold the formatted time string.

	RETURNS     :  A pointer to the formatted time string.

	NOTES       :  This function is designed to minimize running time, not
						executable code size.

	CAVEATS     :  The area to which the ``buffer`` parameter points
						should be at least ''SDTIF_FMT_TIME_LEN_TIME_T + 1''
						(19 + 1) bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

	SEE ALSO    :  SDTIF_Format_time_t_GMT
						SDTIF_Format_tm
						SDTIF_Format_timeval
						SDTIF_Format_timespec
						SDTIF_FormatInterval_time_t

	AUTHOR      : 	Michael L. Brock

	COPYRIGHT   :  Copyright 1985 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_Format_time_t
						Date/Time Functions:SDTIF_Format_time_t
						SDTIF:Functions:SDTIF_Format_time_t
						SDTIF:Date/Time Functions:SDTIF_Format_time_t
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_Format_time_t

	PUBLISH NAME:	SDTIF_Format_time_t

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *SDTIF_Format_time_t(const time_t *in_time, char *buffer)
#else
char *SDTIF_Format_time_t(in_time, buffer)
const time_t *in_time;
char         *buffer;
#endif /* #ifndef NARGS */
{
	time_t    tmp_in_time;
	struct tm tm_data;

	tmp_in_time = (in_time == NULL) ? time(NULL) : *in_time;

	SDTIF_GetTimeLocal(&tmp_in_time, &tm_data);

	tm_data.tm_year  = (tm_data.tm_year + 1900) % 10000;
	tm_data.tm_mon   = (tm_data.tm_mon + 1) % 100;
	tm_data.tm_mday %= 100;
	tm_data.tm_hour %= 100;
	tm_data.tm_min  %= 100;
	tm_data.tm_sec  %= 100;

	buffer[0]        = ((char) ('0' + (tm_data.tm_year / 1000)));
	buffer[1]        = ((char) ('0' + ((tm_data.tm_year % 1000) / 100)));
	buffer[2]        = ((char) ('0' + ((tm_data.tm_year % 100) / 10)));
	buffer[3]        = ((char) ('0' + (tm_data.tm_year % 10)));
	buffer[4]        = '-';
	buffer[5]        = ((char) ('0' + (tm_data.tm_mon / 10)));
	buffer[6]        = ((char) ('0' + (tm_data.tm_mon % 10)));
	buffer[7]        = '-';
	buffer[8]        = ((char) ('0' + (tm_data.tm_mday / 10)));
	buffer[9]        = ((char) ('0' + (tm_data.tm_mday % 10)));
	buffer[10]       = ' ';
	buffer[11]       = ((char) ('0' + (tm_data.tm_hour / 10)));
	buffer[12]       = ((char) ('0' + (tm_data.tm_hour % 10)));
	buffer[13]       = ':';
	buffer[14]       = ((char) ('0' + (tm_data.tm_min / 10)));
	buffer[15]       = ((char) ('0' + (tm_data.tm_min % 10)));
	buffer[16]       = ':';
	buffer[17]       = ((char) ('0' + (tm_data.tm_sec / 10)));
	buffer[18]       = ((char) ('0' + (tm_data.tm_sec % 10)));
	buffer[19]       = '\0';

	return(buffer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME        :  SDTIF_Format_time_t_GMT

	SYNOPSIS    :  string_ptr = SDTIF_Format_time_t_GMT(in_time, buffer);

						char         *string_ptr;

						const time_t *in_time;

						char         *buffer;

	DESCRIPTION :  Formats a ''time_t'' datum as an GMT/UTC time-value string
						with the following format:

						``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``

						Where:

						(.) ``yyyy`` represents the year.

						(.) ``mm`` represents the month.

						(.) ``dd`` represents the day of the month.

						(.) ``hh`` represents the hour.

						(.) ``mm`` represents the minute.

						(.) ``ss`` represents the second.

						Note that there is a space (ASCII 32) between the
						``dd`` and ``hh`` components of the string.

	PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the structure of type ''time_t''
						to be formatted as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``buffer`` points to the string allocated by the
						invoking function to hold the formatted time string.

	RETURNS     :  A pointer to the formatted time string.

	NOTES       :  This function is designed to minimize running time, not
						executable code size.

	CAVEATS     :  The area to which the ``buffer`` parameter points
						should be at least ''SDTIF_FMT_TIME_LEN_TIME_T + 1''
						(19 + 1) bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

	SEE ALSO    :  SDTIF_Format_time_t
						SDTIF_Format_tm_GMT
						SDTIF_Format_timeval_GMT
						SDTIF_Format_timespec_GMT
						SDTIF_FormatInterval_time_t

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :  Copyright 1985 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_Format_time_t_GMT
						Date/Time Functions:SDTIF_Format_time_t_GMT
						SDTIF:Functions:SDTIF_Format_time_t_GMT
						SDTIF:Date/Time Functions:SDTIF_Format_time_t_GMT
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_Format_time_t_GMT

	PUBLISH NAME:	SDTIF_Format_time_t_GMT

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *SDTIF_Format_time_t_GMT(const time_t *in_time, char *buffer)
#else
char *SDTIF_Format_time_t_GMT(in_time, buffer)
const time_t *in_time;
char         *buffer;
#endif /* #ifndef NARGS */
{
	time_t    tmp_in_time;
	struct tm tm_data;

	tmp_in_time      = (in_time == NULL) ? time(NULL) : *in_time;

	SDTIF_GetTimeGMT(&tmp_in_time, &tm_data);

	tm_data.tm_year  = (tm_data.tm_year + 1900) % 10000;
	tm_data.tm_mon   = (tm_data.tm_mon + 1) % 100;
	tm_data.tm_mday %= 100;
	tm_data.tm_hour %= 100;
	tm_data.tm_min  %= 100;
	tm_data.tm_sec  %= 100;

	buffer[0]        = ((char) ('0' + (tm_data.tm_year / 1000)));
	buffer[1]        = ((char) ('0' + ((tm_data.tm_year % 1000) / 100)));
	buffer[2]        = ((char) ('0' + ((tm_data.tm_year % 100) / 10)));
	buffer[3]        = ((char) ('0' + (tm_data.tm_year % 10)));
	buffer[4]        = '-';
	buffer[5]        = ((char) ('0' + (tm_data.tm_mon / 10)));
	buffer[6]        = ((char) ('0' + (tm_data.tm_mon % 10)));
	buffer[7]        = '-';
	buffer[8]        = ((char) ('0' + (tm_data.tm_mday / 10)));
	buffer[9]        = ((char) ('0' + (tm_data.tm_mday % 10)));
	buffer[10]       = ' ';
	buffer[11]       = ((char) ('0' + (tm_data.tm_hour / 10)));
	buffer[12]       = ((char) ('0' + (tm_data.tm_hour % 10)));
	buffer[13]       = ':';
	buffer[14]       = ((char) ('0' + (tm_data.tm_min / 10)));
	buffer[15]       = ((char) ('0' + (tm_data.tm_min % 10)));
	buffer[16]       = ':';
	buffer[17]       = ((char) ('0' + (tm_data.tm_sec / 10)));
	buffer[18]       = ((char) ('0' + (tm_data.tm_sec % 10)));
	buffer[19]       = '\0';

	return(buffer);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	struct timeval  tmp_timeval;
	struct timespec tmp_timespec;
	struct tm       tmp_tm_1;
	struct tm       tmp_tm_2;
	unsigned long   tmp_ulong_1;
	unsigned long   tmp_ulong_2;
	char            buffer[512];

	fprintf(stderr, "Test routine for 'SDTIF_Format_timespec()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_Format_timespec_GMT()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_Format_timeval()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_Format_timeval_GMT()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_Format_tm()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_Format_tm_GMT()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_Format_time_t()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_Format_time_t_GMT()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_Format_ulong()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_Format_ulong_GMT()'\n");
	fprintf(stderr, "---- ------- --- ---------------------------\n\n");

	SDTIF_GetTimeNSecs(&tmp_timespec);
	tmp_timeval.tv_sec  = tmp_timespec.tv_sec;
	tmp_timeval.tv_usec = tmp_timespec.tv_nsec / 1000L;

	SDTIF_GetTimeLocal(&tmp_timeval.tv_sec, &tmp_tm_1);
	tmp_ulong_1 = (((tmp_tm_1.tm_year + 1900) % 10000) * 10000L) +
		(((tmp_tm_1.tm_mon + 1) % 100) * 100L) +
		((unsigned long) (tmp_tm_1.tm_mday % 100));
	SDTIF_GetTimeGMT(&tmp_timeval.tv_sec, &tmp_tm_2);
	tmp_ulong_2 = (((tmp_tm_1.tm_year + 1900) % 10000) * 10000L) +
		(((tmp_tm_1.tm_mon + 1) % 100) * 100L) +
		((unsigned long) (tmp_tm_1.tm_mday % 100));

	printf("With the current time:\n");
	printf("---- --- ------- -----\n");
	printf("   Result for 'SDTIF_Format_timespec()'      : %s\n",
		SDTIF_Format_timespec(&tmp_timespec, buffer));
	printf("   Result for 'SDTIF_Format_timespec_GMT()'  : %s\n",
		SDTIF_Format_timespec_GMT(&tmp_timespec, buffer));
	printf("   Result for 'SDTIF_Format_timeval()'       : %s\n",
		SDTIF_Format_timeval(&tmp_timeval, buffer));
	printf("   Result for 'SDTIF_Format_timeval_GMT()'   : %s\n",
		SDTIF_Format_timeval_GMT(&tmp_timeval, buffer));
	printf("   Result for 'SDTIF_Format_tm()'            : %s\n",
		SDTIF_Format_tm(&tmp_tm_1, buffer));
	printf("   Result for 'SDTIF_Format_tm_GMT()'        : %s\n",
		SDTIF_Format_tm_GMT(&tmp_tm_2, buffer));
	printf("   Result for 'SDTIF_Format_time_t()'        : %s\n",
		SDTIF_Format_time_t(&tmp_timeval.tv_sec, buffer));
	printf("   Result for 'SDTIF_Format_time_t_GMT()'    : %s\n",
		SDTIF_Format_time_t_GMT(&tmp_timeval.tv_sec, buffer));
	printf("   Result for 'SDTIF_Format_ulong()'         : %s\n",
		SDTIF_Format_ulong(&tmp_ulong_1, buffer));
	printf("   Result for 'SDTIF_Format_ulong_GMT()'     : %s\n",
		SDTIF_Format_ulong_GMT(&tmp_ulong_2, buffer));

	printf("Sleeping for three seconds");
	SDTIF_sleep(1);
	printf(" .");
	fflush(stdout);
	SDTIF_sleep(1);
	printf(" .");
	fflush(stdout);
	SDTIF_sleep(1);
	printf(" .");
	fflush(stdout);
	printf("\n");

	printf("With a NULL pointer:\n");
	printf("---- - ---- --------\n");
	printf("   Result for 'SDTIF_Format_timespec()'      : %s\n",
		SDTIF_Format_timespec(NULL, buffer));
	printf("   Result for 'SDTIF_Format_timespec_GMT()'  : %s\n",
		SDTIF_Format_timespec_GMT(NULL, buffer));
	printf("   Result for 'SDTIF_Format_timeval()'       : %s\n",
		SDTIF_Format_timeval(NULL, buffer));
	printf("   Result for 'SDTIF_Format_timeval_GMT()'   : %s\n",
		SDTIF_Format_timeval_GMT(NULL, buffer));
	printf("   Result for 'SDTIF_Format_tm()'            : %s\n",
		SDTIF_Format_tm(NULL, buffer));
	printf("   Result for 'SDTIF_Format_tm_GMT()'        : %s\n",
		SDTIF_Format_tm_GMT(NULL, buffer));
	printf("   Result for 'SDTIF_Format_time_t()'        : %s\n",
		SDTIF_Format_time_t(NULL, buffer));
	printf("   Result for 'SDTIF_Format_time_t_GMT()'    : %s\n",
		SDTIF_Format_time_t_GMT(NULL, buffer));
	printf("   Result for 'SDTIF_Format_ulong()'         : %s\n",
		SDTIF_Format_ulong(NULL, buffer));
	printf("   Result for 'SDTIF_Format_ulong_GMT()'     : %s\n",
		SDTIF_Format_ulong_GMT(NULL, buffer));

	return(0);
}

#endif /* #ifdef TEST_MAIN */

