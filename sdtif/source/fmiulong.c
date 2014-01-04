/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	System Date/Time Interface Facility (SDTIF) Module Source File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats 'unsigned long' time measurement values as
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

#include <memory.h>

#include <strfuncs.h>

#include "sdtifi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME        :  SDTIF_FormatInterval_ulong

	SYNOPSIS    :  string_ptr = SDTIF_FormatInterval_ulong(in_time, buffer);

						char                *string_ptr;

						const unsigned long *in_time;

						char                *buffer;

	DESCRIPTION :  Formats a ''unsigned long'' datum as an interval time-value
						string with the following format:

						``dddddddddd``

						Where ``dddddddddd`` is the number of days.

	PARAMETERS  :  The parameters to this function are as follow:

						(.)``in_time`` points to the ''unsigned long''
						to be formatted as a string.

						(-)if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.)``buffer`` points to the string allocated by the
						invoking function to hold the formatted time string.

	RETURNS     :  A pointer to the formatted time string.

	NOTES       :  This function is designed to minimize running time, not
						executable code size.

	CAVEATS     :  The area to which the ``buffer`` parameter points
						should be at least ''SDTIF_FMTI_TIME_LEN_ULONG + 1''
						(10 + 1) bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

	SEE ALSO    :  SDTIF_FormatInterval_time_t
						SDTIF_FormatInterval_tm
						SDTIF_FormatInterval_timeval
						SDTIF_FormatInterval_timespec
						SDTIF_Format_ulong

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :  Copyright 1985 - 2014 Michael L. Brock

	OUTPUT INDEX:	SDTIF_FormatInterval_ulong
						Date/Time Functions:SDTIF_FormatInterval_ulong
						SDTIF:Functions:SDTIF_FormatInterval_ulong
						SDTIF:Date/Time Functions:SDTIF_FormatInterval_ulong
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_FormatInterval_ulong

	PUBLISH NAME:	SDTIF_FormatInterval_ulong

	ENTRY CLASS	:	Date/Time Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *SDTIF_FormatInterval_ulong(const unsigned long *in_time, char *buffer)
#else
char *SDTIF_FormatInterval_ulong(in_time, buffer)
const unsigned long *in_time;
char                *buffer;
#endif /* #ifndef NARGS */
{
	struct tm tm_data;
	char      tmp_buffer[SDTIF_FMTI_TIME_LEN_TM + 1];

	if (in_time == NULL)
		SDTIF_FormatInterval_tm(NULL, tmp_buffer);
	else {
		memset(&tm_data, '\0', sizeof(tm_data));
		tm_data.tm_year  = ((int) ((*in_time % 100000000L) / 10000L));
		tm_data.tm_mon   = ((int) ((*in_time % 10000L) / 100L));
		tm_data.tm_mday  = ((int) (*in_time % 100L));
		tm_data.tm_hour  = 0;
		tm_data.tm_min   = 0;
		tm_data.tm_sec   = 0;
		tm_data.tm_wday  = 0;
		tm_data.tm_yday  = 0;
		tm_data.tm_isdst = 0;
		SDTIF_FormatInterval_tm(&tm_data, tmp_buffer);
	}

	return(nstrcpy(buffer, tmp_buffer, SDTIF_FMT_TIME_LEN_ULONG));
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

