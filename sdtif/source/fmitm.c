/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	System Date/Time Interface Facility (SDTIF) Module Source File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats 'struct tm' time measurement values as
								interval values in human-readable format.

	Revision History	:	1985-10-31 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1985 - 2014.
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

	NAME        :  SDTIF_FormatInterval_tm

	SYNOPSIS    :  string_ptr = SDTIF_FormatInterval_tm(in_time, buffer);

						char            *string_ptr;

						const struct tm *in_time;

						char            *buffer;

	DESCRIPTION :  Formats a ''struct tm'' datum as an interval time-value
						string with the following format:

						``dddddddddd`` ``hh``:``mm``:``ss``

						Where:

						(.) ``dddddddddd`` is the number of days.

						(.) ``hh`` is the number of hours.

						(.) ``mm`` is the number of minutes.

						(.) ``ss`` is the number of seconds.

						Note that there is a space (ASCII 32) between the
						``dddddddddd`` and ``hh`` components of the string.

	PARAMETERS  :  The parameters to this function are as follow:

						(.)``in_time`` points to the structure of type ''tm''
						to be formatted as a string.

						(-)if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.)``buffer`` points to the string allocated by the
						invoking function to hold the formatted time string.

	RETURNS     :  A pointer to the formatted time string.

	NOTES       :  This function is designed to minimize running time, not
						executable code size.

	CAVEATS     :  The area to which the ``buffer`` parameter points
						should be at least ''SDTIF_FMTI_TIME_LEN_TM + 1''
						(19 + 1) bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

	SEE ALSO    :  SDTIF_FormatInterval_time_t
						SDTIF_FormatInterval_timeval
						SDTIF_FormatInterval_timespec
						SDTIF_FormatInterval_ulong
						SDTIF_Format_tm

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :  Copyright 1985 - 2014 Michael L. Brock

	OUTPUT INDEX:	SDTIF_FormatInterval_tm
						Date/Time Functions:SDTIF_FormatInterval_tm
						SDTIF:Functions:SDTIF_FormatInterval_tm
						SDTIF:Date/Time Functions:SDTIF_FormatInterval_tm
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_FormatInterval_tm

	PUBLISH NAME:	SDTIF_FormatInterval_tm

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *SDTIF_FormatInterval_tm(const struct tm *in_time, char *buffer)
#else
char *SDTIF_FormatInterval_tm(in_time, buffer)
const struct tm *in_time;
char            *buffer;
#endif /* #ifndef NARGS */
{
	time_t    tmp_time;
	struct tm tm_data;

	if (in_time == NULL)
		SDTIF_FormatInterval_time_t(NULL, buffer);
	else {
		tm_data  = *in_time;
		tmp_time = mktime(&tm_data);
		SDTIF_FormatInterval_time_t(&tmp_time, buffer);
	}

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
	struct tm       tmp_tm;
	unsigned long   tmp_ulong;
	char            buffer[512];

	fprintf(stderr, "Test routine for 'SDTIF_FormatInterval_timespec()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_FormatInterval_timeval()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_FormatInterval_time_t()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_FormatInterval_tm()'\n");
	fprintf(stderr, "Test routine for 'SDTIF_FormatInterval_ulong()'\n");
	fprintf(stderr, "---- ------- --- ---------------------------------\n\n");

	SDTIF_GetTimeNSecs(&tmp_timespec);
	tmp_timeval.tv_sec  = tmp_timespec.tv_sec;
	tmp_timeval.tv_usec = tmp_timespec.tv_nsec / 1000L;

	printf("With the current time:\n");
	printf("---- --- ------- -----\n");

	printf("   Result for 'SDTIF_Format_timespec()'        : %s\n",
		SDTIF_Format_timespec(&tmp_timespec, buffer));
	printf("   Result for 'SDTIF_FormatInterval_timespec()': %s\n",
		SDTIF_FormatInterval_timespec(&tmp_timespec, buffer));
	printf("   TEST COMPARISON ONE                         : ");
	printf("%010lu:%02lu:%02lu:%02lu.%06lu\n",
		tmp_timespec.tv_sec / (60L * 60L * 24L),
		(tmp_timespec.tv_sec % (60L * 60L * 24L)) / (60L * 60L),
		(tmp_timespec.tv_sec % (60L * 60L)) / 60L, tmp_timespec.tv_sec % 60L,
		tmp_timespec.tv_nsec % 1000000000L);
	printf("   TEST COMPARISON TWO                         : %010lu.%010lu\n",
		tmp_timespec.tv_sec, tmp_timespec.tv_nsec);
	printf("\n");

	printf("   Result for 'SDTIF_Format_timeval()'         : %s\n",
		SDTIF_Format_timeval(&tmp_timeval, buffer));
	printf("   Result for 'SDTIF_FormatInterval_timeval()' : %s\n",
		SDTIF_FormatInterval_timeval(&tmp_timeval, buffer));
	printf("   TEST COMPARISON ONE                         : ");
	printf("%010lu:%02lu:%02lu:%02lu.%06lu\n",
		tmp_timeval.tv_sec / (60L * 60L * 24L),
		(tmp_timeval.tv_sec % (60L * 60L * 24L)) / (60L * 60L),
		(tmp_timeval.tv_sec % (60L * 60L)) / 60L, tmp_timeval.tv_sec % 60L,
		tmp_timeval.tv_usec % 1000000L);
	printf("   TEST COMPARISON TWO                         : %010lu.%010lu\n",
		tmp_timeval.tv_sec, tmp_timeval.tv_usec);
	printf("\n");

	printf("   Result for 'SDTIF_Format_time_t()'          : %s\n",
		SDTIF_Format_time_t(&tmp_timeval.tv_sec, buffer));
	printf("   Result for 'SDTIF_FormatInterval_time_t()'  : %s\n",
		SDTIF_FormatInterval_time_t(&tmp_timeval.tv_sec, buffer));
	printf("   TEST COMPARISON ONE                         : ");
	printf("%010lu:%02lu:%02lu:%02lu\n",
		tmp_timeval.tv_sec / (60L * 60L * 24L),
		(tmp_timeval.tv_sec % (60L * 60L * 24L)) / (60L * 60L),
		(tmp_timeval.tv_sec % (60L * 60L)) / 60L, tmp_timeval.tv_sec % 60L);
	printf("   TEST COMPARISON TWO                         : %010lu\n",
		tmp_timeval.tv_sec);
	printf("\n");

	SDTIF_GetTimeLocal(&tmp_timeval.tv_sec, &tmp_tm);
	printf("   Result for 'SDTIF_Format_tm()'              : %s\n",
		SDTIF_Format_tm(&tmp_tm, buffer));
	printf("   Result for 'SDTIF_FormatInterval_tm()'      : %s\n",
		SDTIF_FormatInterval_tm(&tmp_tm, buffer));
	printf("\n");

	tmp_ulong   = (((tmp_tm.tm_year + 1900) % 10000) * 10000L) +
		(((tmp_tm.tm_mon + 1) % 100) * 100L) +
		((unsigned long) (tmp_tm.tm_mday % 100));
	printf("   Result for 'SDTIF_Format_ulong()'           : %s\n",
		SDTIF_Format_ulong(&tmp_ulong, buffer));
	printf("   Result for 'SDTIF_FormatInterval_ulong()'   : %s\n",
		SDTIF_FormatInterval_ulong(&tmp_ulong, buffer));
	printf("\n");

	return(0);
}

#endif /* #ifdef TEST_MAIN */

