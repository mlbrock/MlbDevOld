/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Formats a variety of time measurement values as
								interval values in human-readable format.

	Revision History	:	1991-10-31 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "genfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_FormatInterval_time_t

   SYNOPSIS    :  string_ptr = GEN_FormatInterval_time_t(in_time, buffer);

						char         *string_ptr;

						const time_t *in_time;

						char         *buffer;

   DESCRIPTION :  Formats a ''time_t'' datum as an interval time-value string
						with the following format:

						``dddddddddd`` ``hh``:``mm``:``ss``

   PARAMETERS  :  The parameters to this function are as follow:

						(.)``in_time`` points to the structure of type ''time_t''
						to be formatted as a string.

						(-)if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.)``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 20 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_FormatInterval_timeval
						GEN_FormatInterval_timespec
						GEN_Format_time_t

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_FormatInterval_time_t
						Date/Time Functions:GEN_FormatInterval_time_t
						GENFUNCS:Functions:GEN_FormatInterval_time_t
						GENFUNCS:Date/Time Functions:GEN_FormatInterval_time_t
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_FormatInterval_time_t

   PUBLISH NAME:	GEN_FormatInterval_time_t

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_FormatInterval_time_t(const time_t *in_time, char *buffer)
#else
char *GEN_FormatInterval_time_t(in_time, buffer)
const time_t *in_time;
char         *buffer;
#endif /* #ifndef NARGS */
{
	time_t        tmp_in_time;
	unsigned long all_seconds;
	unsigned long days;
	unsigned long hours;
	unsigned long minutes;
	unsigned long seconds;

	tmp_in_time = (in_time == NULL) ? time(NULL) : *in_time;
	all_seconds = ((unsigned long) tmp_in_time);
	days        = all_seconds / (60L * 60L * 24L);
	hours       = (all_seconds % (60L * 60L * 24L)) / (60L * 60L);
	minutes     = (all_seconds % (60L * 60L)) / 60L;
	seconds     = all_seconds % 60L;

	buffer[0]   = ((char) ('0' + ((char) (days / 1000000000L))));
	buffer[1]   = ((char) ('0' + ((char) ((days % 1000000000L) / 100000000L))));
	buffer[2]   = ((char) ('0' + ((char) ((days %  100000000L) / 10000000L))));
	buffer[3]   = ((char) ('0' + ((char) ((days %   10000000L) / 1000000L))));
	buffer[4]   = ((char) ('0' + ((char) ((days %    1000000L) / 100000L))));
	buffer[5]   = ((char) ('0' + ((char) ((days %     100000L) / 10000L))));
	buffer[6]   = ((char) ('0' + ((char) ((days %      10000L) / 1000L))));
	buffer[7]   = ((char) ('0' + ((char) ((days %       1000L) / 100L))));
	buffer[8]   = ((char) ('0' + ((char) ((days %        100L) / 10L))));
	buffer[9]   = ((char) ('0' + ((char)  (days % 10L))));
	buffer[10]  = ' ';
	buffer[11]  = ((char) ('0' + ((char) (hours / 10L))));
	buffer[12]  = ((char) ('0' + ((char) (hours % 10L))));
	buffer[13]  = ':';
	buffer[14]  = ((char) ('0' + ((char) (minutes / 10L))));
	buffer[15]  = ((char) ('0' + ((char) (minutes % 10L))));
	buffer[16]  = ':';
	buffer[17]  = ((char) ('0' + ((char) (seconds / 10L))));
	buffer[18]  = ((char) ('0' + ((char) (seconds % 10L))));
	buffer[19]  = '\0';

	return(buffer);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_FormatInterval_timeval

   SYNOPSIS    :  string_ptr = GEN_FormatInterval_timeval(in_time, buffer);

						char                 *string_ptr;

						const struct timeval *in_time;

						char                 *buffer;

   DESCRIPTION :  Formats a ''struct timeval'' datum as an interval time-value
						string with the following format:

						``dddddddddd`` ``hh``:``mm``:``ss``.``uuuuuu``

						where ``uuuuuu`` represents microseconds.

   PARAMETERS  :  The parameters to this function are as follow:

						(.)``in_time`` points to the structure of type ''timeval''
						to be formatted as a string.

						(-)if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.)``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 27 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_FormatInterval_time_t
						GEN_FormatInterval_timespec
						GEN_Format_timeval

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_FormatInterval_timeval
						Date/Time Functions:GEN_FormatInterval_timeval
						GENFUNCS:Functions:GEN_FormatInterval_timeval
						GENFUNCS:Date/Time Functions:GEN_FormatInterval_timeval
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_FormatInterval_timeval

   PUBLISH NAME:	GEN_FormatInterval_timeval

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_FormatInterval_timeval(const struct timeval *in_time, char *buffer)
#else
char *GEN_FormatInterval_timeval(in_time, buffer)
const struct timeval *in_time;
char                 *buffer;
#endif /* #ifndef NARGS */
{
	struct timeval tmp_in_time;
	unsigned long  all_seconds;
	unsigned long  all_useconds;
	unsigned long  days;
	unsigned long  hours;
	unsigned long  minutes;
	unsigned long  seconds;

	if (in_time != NULL) {
		tmp_in_time         = *in_time;
		tmp_in_time.tv_usec = (tmp_in_time.tv_usec >= 0L) ? tmp_in_time.tv_usec :
			(0L - tmp_in_time.tv_usec);
	}
	else
		GEN_GetTimeUSecs(&tmp_in_time);

	all_seconds  = ((unsigned long) tmp_in_time.tv_sec);
	all_useconds = ((unsigned long) (tmp_in_time.tv_usec % 1000000L));
	days         = all_seconds / (60L * 60L * 24L);
	hours        = (all_seconds % (60L * 60L * 24L)) / (60L * 60L);
	minutes      = (all_seconds % (60L * 60L)) / 60L;
	seconds      = all_seconds % 60L;

	buffer[0]    = ((char) ('0' + ((char)  (days / 1000000000L))));
	buffer[1]    = ((char) ('0' + ((char) ((days % 1000000000L) / 100000000L))));
	buffer[2]    = ((char) ('0' + ((char) ((days %  100000000L) / 10000000L))));
	buffer[3]    = ((char) ('0' + ((char) ((days %   10000000L) / 1000000L))));
	buffer[4]    = ((char) ('0' + ((char) ((days %    1000000L) / 100000L))));
	buffer[5]    = ((char) ('0' + ((char) ((days %     100000L) / 10000L))));
	buffer[6]    = ((char) ('0' + ((char) ((days %      10000L) / 1000L))));
	buffer[7]    = ((char) ('0' + ((char) ((days %       1000L) / 100L))));
	buffer[8]    = ((char) ('0' + ((char) ((days %        100L) / 10L))));
	buffer[9]    = ((char) ('0' + ((char)  (days %         10L))));
	buffer[10]   = ' ';
	buffer[11]   = ((char) ('0' + ((char) (hours / 10L))));
	buffer[12]   = ((char) ('0' + ((char) (hours % 10L))));
	buffer[13]   = ':';
	buffer[14]   = ((char) ('0' + ((char) (minutes / 10L))));
	buffer[15]   = ((char) ('0' + ((char) (minutes % 10L))));
	buffer[16]   = ':';
	buffer[17]   = ((char) ('0' + ((char) (seconds / 10L))));
	buffer[18]   = ((char) ('0' + ((char) (seconds % 10L))));
	buffer[19]   = '.';
	buffer[20]   = ((char) ('0' + ((char) (all_useconds / 100000L))));
	buffer[21]   = ((char) ('0' + ((char) ((all_useconds % 100000L) / 10000))));
	buffer[22]   = ((char) ('0' + ((char) ((all_useconds % 10000L) / 1000L))));
	buffer[23]   = ((char) ('0' + ((char) ((all_useconds % 1000L) / 100L))));
	buffer[24]   = ((char) ('0' + ((char) ((all_useconds % 100L) / 10L))));
	buffer[25]   = ((char) ('0' + ((char) (all_useconds % 10L))));
	buffer[26]   = '\0';

	return(buffer);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_FormatInterval_timespec

   SYNOPSIS    :  string_ptr = GEN_FormatInterval_timespec(in_time, buffer);

						char                  *string_ptr;

						const struct timespec *in_time;

						char                  *buffer;

   DESCRIPTION :  Formats a ''struct timespec'' datum as an interval time-value
						string with the following format:

						``dddddddddd`` ``hh``:``mm``:``ss``.``nnnnnnnnn``

						where ``nnnnnnnnn`` represents nanoseconds.

   PARAMETERS  :  The parameters to this function are as follow:

						(.)``in_time`` points to the structure of type ''timespec''
						to be formatted as a string.

						(-)if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.)``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 30 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_FormatInterval_time_t
						GEN_Format_timeval

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:	GEN_FormatInterval_timespec
						Date/Time Functions:GEN_FormatInterval_timespec
						GENFUNCS:Functions:GEN_FormatInterval_timespec
						GENFUNCS:Date/Time Functions:GEN_FormatInterval_timespec
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_FormatInterval_timespec

   PUBLISH NAME:	GEN_FormatInterval_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_FormatInterval_timespec(const struct timespec *in_time, char *buffer)
#else
char *GEN_FormatInterval_timespec(in_time, buffer)
const struct timespec *in_time;
char                  *buffer;
#endif /* #ifndef NARGS */
{
	struct timespec tmp_in_time;
	unsigned long   all_seconds;
	unsigned long   all_nseconds;
	unsigned long   days;
	unsigned long   hours;
	unsigned long   minutes;
	unsigned long   seconds;

	if (in_time != NULL) {
		tmp_in_time         = *in_time;
		tmp_in_time.tv_nsec = (tmp_in_time.tv_nsec >= 0L) ? tmp_in_time.tv_nsec :
			(0L - tmp_in_time.tv_nsec);
	}
	else
		GEN_GetTimeNSecs(&tmp_in_time);

	all_seconds  = ((unsigned long) tmp_in_time.tv_sec);
	all_nseconds = ((unsigned long) (tmp_in_time.tv_nsec % 1000000000L));
	days         = all_seconds / (60L * 60L * 24L);
	hours        = (all_seconds % (60L * 60L * 24L)) / (60L * 60L);
	minutes      = (all_seconds % (60L * 60L)) / 60L;
	seconds      = all_seconds % 60L;

	buffer[0]    = ((char) ('0' + ((char)  (days / 1000000000L))));
	buffer[1]    = ((char) ('0' + ((char) ((days % 1000000000L) / 100000000L))));
	buffer[2]    = ((char) ('0' + ((char) ((days %  100000000L) / 10000000L))));
	buffer[3]    = ((char) ('0' + ((char) ((days %   10000000L) / 1000000L))));
	buffer[4]    = ((char) ('0' + ((char) ((days %    1000000L) / 100000L))));
	buffer[5]    = ((char) ('0' + ((char) ((days %     100000L) / 10000L))));
	buffer[6]    = ((char) ('0' + ((char) ((days %      10000L) / 1000L))));
	buffer[7]    = ((char) ('0' + ((char) ((days %       1000L) / 100L))));
	buffer[8]    = ((char) ('0' + ((char) ((days %        100L) / 10L))));
	buffer[9]    = ((char) ('0' + ((char)  (days %         10L))));
	buffer[10]   = ' ';
	buffer[11]   = ((char) ('0' + ((char) (hours / 10L))));
	buffer[12]   = ((char) ('0' + ((char) (hours % 10L))));
	buffer[13]   = ':';
	buffer[14]   = ((char) ('0' + ((char) (minutes / 10L))));
	buffer[15]   = ((char) ('0' + ((char) (minutes % 10L))));
	buffer[16]   = ':';
	buffer[17]   = ((char) ('0' + ((char) (seconds / 10L))));
	buffer[18]   = ((char) ('0' + ((char) (seconds % 10L))));
	buffer[19]   = '.';

	buffer[20]           =
		((char) ('0' + ((char) (all_nseconds /  100000000L))));
	buffer[21]           =
		((char) ('0' + ((char) ((all_nseconds % 100000000L) / 10000000L))));
	buffer[22]           =
		((char) ('0' + ((char) ((all_nseconds % 10000000L) / 1000000L))));
	buffer[23]           =
		((char) ('0' + ((char) ((all_nseconds % 1000000L) / 100000L))));
	buffer[24]           =
		((char) ('0' + ((char) ((all_nseconds % 100000L) / 10000L))));
	buffer[25]           =
		((char) ('0' + ((char) ((all_nseconds % 10000L) / 1000L))));
	buffer[26]           =
		((char) ('0' + ((char) ((all_nseconds % 1000L) / 100L))));
	buffer[27]           =
		((char) ('0' + ((char) ((all_nseconds % 100L) / 10L))));
	buffer[28]           =
		((char) ('0' + ((char) (all_nseconds %  10L))));
	buffer[29]           = '\0';

	return(buffer);
}
/* *********************************************************************** */

#ifdef TEST_MAIN
 
COMPAT_FN_DECL(int main, (void));

int main()
{
	struct timeval this_time;
	char           buffer[512];

	fprintf(stderr, "Test routine for 'GEN_FormatInterval_timeval()'\n");
	fprintf(stderr, "                 'GEN_FormatInterval_time_t()'\n");
	fprintf(stderr, "---- ------- --- ------------------------------\n\n");

	GEN_GetTimeUSecs(&this_time);

	printf("With the current time:\n");
	printf("---- --- ------- -----\n");
	printf("   Result for 'GEN_Format_timeval()'        : %s\n",
		GEN_Format_timeval(&this_time, buffer));
	printf("   Result for 'GEN_FormatInterval_timeval()': %s\n",
		GEN_FormatInterval_timeval(&this_time, buffer));
	printf("   TEST COMPARISON ONE                      : ");
	printf("%010lu:%02lu:%02lu:%02lu.%06lu\n",
		this_time.tv_sec / (60L * 60L * 24L),
		(this_time.tv_sec % (60L * 60L * 24L)) / (60L * 60L),
		(this_time.tv_sec % (60L * 60L)) / 60L, this_time.tv_sec % 60L,
		this_time.tv_usec % 1000000L);
	printf("   TEST COMPARISON TWO                      : %010lu.%010lu\n",
		this_time.tv_sec, this_time.tv_usec);
	printf("\n");

	printf("   Result for 'GEN_Format_time_t()'         : %s\n",
		GEN_Format_time_t(&this_time.tv_sec, buffer));
	printf("   Result for 'GEN_FormatInterval_time_t()' : %s\n",
		GEN_FormatInterval_time_t(&this_time.tv_sec, buffer));
	printf("   TEST COMPARISON ONE                      : ");
	printf("%010lu:%02lu:%02lu:%02lu\n",
		this_time.tv_sec / (60L * 60L * 24L),
		(this_time.tv_sec % (60L * 60L * 24L)) / (60L * 60L),
		(this_time.tv_sec % (60L * 60L)) / 60L, this_time.tv_sec % 60L);
	printf("   TEST COMPARISON TWO                      : %010lu\n",
		this_time.tv_sec);
	printf("\n");

	return(0);
}

#endif /* #ifdef TEST_MAIN */

