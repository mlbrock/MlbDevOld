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
								local or GMT/UTC values in human-readable format.

	Revision History	:	1991-10-31 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2015.
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

   NAME        :  GEN_Format_time_t

   SYNOPSIS    :  string_ptr = GEN_Format_time_t(in_time, buffer);

						char         *string_ptr;

						const time_t *in_time;

						char         *buffer;

   DESCRIPTION :  Formats a ''time_t'' datum as an local time-value string
						with the following format:

						``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``

   PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the structure of type ''time_t''
						to be formatted as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 20 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_Format_time_t_GMT
						GEN_Format_tm
						GEN_Format_timeval
						GEN_Format_timespec
						GEN_FormatInterval_time_t

   EXAMPLES    :  

   AUTHOR      : 	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_Format_time_t
						Date/Time Functions:GEN_Format_time_t
						GENFUNCS:Functions:GEN_Format_time_t
						GENFUNCS:Date/Time Functions:GEN_Format_time_t
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_Format_time_t

   PUBLISH NAME:	GEN_Format_time_t

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_Format_time_t(const time_t *in_time, char *buffer)
#else
char *GEN_Format_time_t(in_time, buffer)
const time_t *in_time;
char         *buffer;
#endif /* #ifndef NARGS */
{
	time_t    tmp_in_time;
	struct tm tm_data;

	tmp_in_time = (in_time == NULL) ? time(NULL) : *in_time;

	GEN_GetTimeLocal(&tmp_in_time, &tm_data);

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
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_Format_time_t_GMT

   SYNOPSIS    :  string_ptr = GEN_Format_time_t_GMT(in_time, buffer);

						char         *string_ptr;

						const time_t *in_time;

						char         *buffer;

   DESCRIPTION :  Formats a ''time_t'' datum as an GMT/UTC time-value string
						with the following format:

						``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``

   PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the structure of type ''time_t''
						to be formatted as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 20 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_Format_time_t
						GEN_Format_tm_GMT
						GEN_Format_timeval_GMT
						GEN_Format_timespec_GMT
						GEN_FormatInterval_time_t

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_Format_time_t_GMT
						Date/Time Functions:GEN_Format_time_t_GMT
						GENFUNCS:Functions:GEN_Format_time_t_GMT
						GENFUNCS:Date/Time Functions:GEN_Format_time_t_GMT
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_Format_time_t_GMT

   PUBLISH NAME:	GEN_Format_time_t_GMT

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_Format_time_t_GMT(const time_t *in_time, char *buffer)
#else
char *GEN_Format_time_t_GMT(in_time, buffer)
const time_t *in_time;
char         *buffer;
#endif /* #ifndef NARGS */
{
	time_t    tmp_in_time;
	struct tm tm_data;

	tmp_in_time      = (in_time == NULL) ? time(NULL) : *in_time;

	GEN_GetTimeGMT(&tmp_in_time, &tm_data);

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
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_Format_tm

   SYNOPSIS    :  string_ptr = GEN_Format_tm(in_time, buffer);

						char            *string_ptr;

						const struct tm *in_time;

						char            *buffer;

   DESCRIPTION :  Formats a ''struct tm'' datum as an local time-value
						string with the following format:

						``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``

   PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the structure of type ''tm''
						to be formatted as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 20 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_Format_tm_GMT
						GEN_Format_time_t
						GEN_Format_timeval
						GEN_Format_timespec

   EXAMPLES    :  

   AUTHOR      : 	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_Format_tm
						Date/Time Functions:GEN_Format_tm
						GENFUNCS:Functions:GEN_Format_tm
						GENFUNCS:Date/Time Functions:GEN_Format_tm
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_Format_tm

   PUBLISH NAME:	GEN_Format_tm

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_Format_tm(const struct tm *in_time, char *buffer)
#else
char *GEN_Format_tm(in_time, buffer)
const struct tm *in_time;
char            *buffer;
#endif /* #ifndef NARGS */
{
	struct tm tm_data;
	time_t    tmp_time;

	if (in_time != NULL)
		tm_data = *in_time;
	else {
		tmp_time = time(NULL);
		GEN_GetTimeLocal(&tmp_time, &tm_data);
	}

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
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_Format_tm_GMT

   SYNOPSIS    :  string_ptr = GEN_Format_tm_GMT(in_time, buffer);

						char            *string_ptr;

						const struct tm *in_time;

						char            *buffer;

   DESCRIPTION :  Formats a ''struct tm'' datum as an GMT/UTC time-value
						string with the following format:

						``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``

   PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the structure of type ''tm''
						to be formatted as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 20 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_Format_tm
						GEN_Format_time_t_GMT
						GEN_Format_timeval_GMT
						GEN_Format_timespec_GMT

   EXAMPLES    :  

   AUTHOR      : 	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_Format_tm_GMT
						Date/Time Functions:GEN_Format_tm_GMT
						GENFUNCS:Functions:GEN_Format_tm_GMT
						GENFUNCS:Date/Time Functions:GEN_Format_tm_GMT
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_Format_tm_GMT

   PUBLISH NAME:	GEN_Format_tm_GMT

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_Format_tm_GMT(const struct tm *in_time, char *buffer)
#else
char *GEN_Format_tm_GMT(in_time, buffer)
const struct tm *in_time;
char            *buffer;
#endif /* #ifndef NARGS */
{
	struct tm tm_data;
	time_t    tmp_time;

	if (in_time != NULL)
		tm_data = *in_time;
	else {
		tmp_time = time(NULL);
		GEN_GetTimeGMT(&tmp_time, &tm_data);
	}

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
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_Format_timeval

   SYNOPSIS    :  string_ptr = GEN_Format_timeval(in_time, buffer);

						char                 *string_ptr;

						const struct timeval *in_time;

						char                 *buffer;

   DESCRIPTION :  Formats a ''struct timeval'' datum as an local time-value
						string with the following format:

						``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``.``uuuuuu``

						where ``uuuuuu`` represents microseconds.

   PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the structure of type ''timeval''
						to be formatted as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 27 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_Format_timeval_GMT
						GEN_Format_time_t
						GEN_Format_tm
						GEN_Format_timespec
						GEN_FormatInterval_timeval

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_Format_timeval
						Date/Time Functions:GEN_Format_timeval
						GENFUNCS:Functions:GEN_Format_timeval
						GENFUNCS:Date/Time Functions:GEN_Format_timeval
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_Format_timeval

   PUBLISH NAME:	GEN_Format_timeval

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_Format_timeval(const struct timeval *in_time, char *buffer)
#else
char *GEN_Format_timeval(in_time, buffer)
const struct timeval *in_time;
char                 *buffer;
#endif /* #ifndef NARGS */
{
	struct tm      tm_data;
	struct timeval tmp_in_time;

	if (in_time != NULL) {
		tmp_in_time         = *in_time;
		tmp_in_time.tv_usec = (tmp_in_time.tv_usec >= 0L) ? tmp_in_time.tv_usec :
			(0L - tmp_in_time.tv_usec);
	}
	else
		GEN_GetTimeUSecs(&tmp_in_time);

	GEN_GetTimeLocal(&tmp_in_time.tv_sec, &tm_data);

	tm_data.tm_year      = (tm_data.tm_year + 1900) % 10000;
	tm_data.tm_mon       = (tm_data.tm_mon + 1) % 100;
	tm_data.tm_mday     %= 100;
	tm_data.tm_hour     %= 100;
	tm_data.tm_min      %= 100;
	tm_data.tm_sec      %= 100;
	tmp_in_time.tv_usec %= 1000000L;

	buffer[0]            = ((char) ('0' + (tm_data.tm_year / 1000)));
	buffer[1]            = ((char) ('0' + ((tm_data.tm_year % 1000) / 100)));
	buffer[2]            = ((char) ('0' + ((tm_data.tm_year % 100) / 10)));
	buffer[3]            = ((char) ('0' + (tm_data.tm_year % 10)));
	buffer[4]            = '-';
	buffer[5]            = ((char) ('0' + (tm_data.tm_mon / 10)));
	buffer[6]            = ((char) ('0' + (tm_data.tm_mon % 10)));
	buffer[7]            = '-';
	buffer[8]            = ((char) ('0' + (tm_data.tm_mday / 10)));
	buffer[9]            = ((char) ('0' + (tm_data.tm_mday % 10)));
	buffer[10]           = ' ';
	buffer[11]           = ((char) ('0' + (tm_data.tm_hour / 10)));
	buffer[12]           = ((char) ('0' + (tm_data.tm_hour % 10)));
	buffer[13]           = ':';
	buffer[14]           = ((char) ('0' + (tm_data.tm_min / 10)));
	buffer[15]           = ((char) ('0' + (tm_data.tm_min % 10)));
	buffer[16]           = ':';
	buffer[17]           = ((char) ('0' + (tm_data.tm_sec / 10)));
	buffer[18]           = ((char) ('0' + (tm_data.tm_sec % 10)));
	buffer[19]           = '.';
	buffer[20]           =
		((char) ('0' + ((char) (tmp_in_time.tv_usec / 100000L))));
	buffer[21]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_usec % 100000L) / 10000L))));
	buffer[22]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_usec % 10000L) / 1000L))));
	buffer[23]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_usec % 1000L) / 100L))));
	buffer[24]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_usec % 100L) / 10L))));
	buffer[25]           =
		((char) ('0' + ((char) (tmp_in_time.tv_usec % 10L))));
	buffer[26]           = '\0';

	return(buffer);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_Format_timeval_GMT

   SYNOPSIS    :  string_ptr = GEN_Format_timeval_GMT(in_time, buffer);

						char                 *string_ptr;

						const struct timeval *in_time;

						char                 *buffer;

   DESCRIPTION :  Formats a ''struct timeval'' datum as an GMT/UTC time-value
						string with the following format:

						``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``.``uuuuuu``

						where ``uuuuuu`` represents microseconds.

	PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the structure of type ''timeval''
						to be formatted as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 27 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_Format_timeval
						GEN_Format_time_t_GMT
						GEN_Format_tm_GMT
						GEN_Format_timespec_GMT
						GEN_FormatInterval_timeval

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_Format_timeval_GMT
						Date/Time Functions:GEN_Format_timeval_GMT
						GENFUNCS:Functions:GEN_Format_timeval_GMT
						GENFUNCS:Date/Time Functions:GEN_Format_timeval_GMT
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_Format_timeval_GMT

	PUBLISH NAME:	GEN_Format_timeval_GMT

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_Format_timeval_GMT(const struct timeval *in_time, char *buffer)
#else
char *GEN_Format_timeval_GMT(in_time, buffer)
const struct timeval *in_time;
char                 *buffer;
#endif /* #ifndef NARGS */
{
	struct tm      tm_data;
	struct timeval tmp_in_time;

	if (in_time != NULL) {
		tmp_in_time         = *in_time;
		tmp_in_time.tv_usec = (tmp_in_time.tv_usec >= 0L) ? tmp_in_time.tv_usec :
			(0L - tmp_in_time.tv_usec);
	}
	else
		GEN_GetTimeUSecs(&tmp_in_time);

	GEN_GetTimeGMT(&tmp_in_time.tv_sec, &tm_data);

	tm_data.tm_year      = (tm_data.tm_year + 1900) % 10000;
	tm_data.tm_mon       = (tm_data.tm_mon + 1) % 100;
	tm_data.tm_mday     %= 100;
	tm_data.tm_hour     %= 100;
	tm_data.tm_min      %= 100;
	tm_data.tm_sec      %= 100;
	tmp_in_time.tv_usec %= 1000000L;

	buffer[0]            = ((char) ('0' + (tm_data.tm_year / 1000)));
	buffer[1]            = ((char) ('0' + ((tm_data.tm_year % 1000) / 100)));
	buffer[2]            = ((char) ('0' + ((tm_data.tm_year % 100) / 10)));
	buffer[3]            = ((char) ('0' + (tm_data.tm_year % 10)));
	buffer[4]            = '-';
	buffer[5]            = ((char) ('0' + (tm_data.tm_mon / 10)));
	buffer[6]            = ((char) ('0' + (tm_data.tm_mon % 10)));
	buffer[7]            = '-';
	buffer[8]            = ((char) ('0' + (tm_data.tm_mday / 10)));
	buffer[9]            = ((char) ('0' + (tm_data.tm_mday % 10)));
	buffer[10]           = ' ';
	buffer[11]           = ((char) ('0' + (tm_data.tm_hour / 10)));
	buffer[12]           = ((char) ('0' + (tm_data.tm_hour % 10)));
	buffer[13]           = ':';
	buffer[14]           = ((char) ('0' + (tm_data.tm_min / 10)));
	buffer[15]           = ((char) ('0' + (tm_data.tm_min % 10)));
	buffer[16]           = ':';
	buffer[17]           = ((char) ('0' + (tm_data.tm_sec / 10)));
	buffer[18]           = ((char) ('0' + (tm_data.tm_sec % 10)));
	buffer[19]           = '.';
	buffer[20]           =
		((char) ('0' + ((char) (tmp_in_time.tv_usec / 100000L))));
	buffer[21]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_usec % 100000L) / 10000L))));
	buffer[22]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_usec % 10000L) / 1000L))));
	buffer[23]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_usec % 1000L) / 100L))));
	buffer[24]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_usec % 100L) / 10L))));
	buffer[25]           =
		((char) ('0' + ((char) (tmp_in_time.tv_usec % 10L))));
	buffer[26]           = '\0';

	return(buffer);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_Format_timespec

   SYNOPSIS    :  string_ptr = GEN_Format_timespec(in_time, buffer);

						char                  *string_ptr;

						const struct timespec *in_time;

						char                  *buffer;

   DESCRIPTION :  Formats a ''struct timespec'' datum as an local time-value
						string with the following format:

						``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``.``nnnnnnnnn``

						where ``nnnnnnnnn`` represents nanoseconds.

   PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the structure of type ''timespec''
						to be formatted as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 30 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_Format_timespec_GMT
						GEN_Format_time_t
						GEN_Format_tm
						GEN_Format_timeval
						GEN_FormatInterval_timespec

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_Format_timespec
						Date/Time Functions:GEN_Format_timespec
						GENFUNCS:Functions:GEN_Format_timespec
						GENFUNCS:Date/Time Functions:GEN_Format_timespec
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_Format_timespec

   PUBLISH NAME:	GEN_Format_timespec

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_Format_timespec(const struct timespec *in_time, char *buffer)
#else
char *GEN_Format_timespec(in_time, buffer)
const struct timespec *in_time;
char                  *buffer;
#endif /* #ifndef NARGS */
{
	struct tm       tm_data;
	struct timespec tmp_in_time;

	if (in_time != NULL) {
		tmp_in_time         = *in_time;
		tmp_in_time.tv_nsec = (tmp_in_time.tv_nsec >= 0L) ? tmp_in_time.tv_nsec :
			(0L - tmp_in_time.tv_nsec);
	}
	else
		GEN_GetTimeNSecs(&tmp_in_time);

	GEN_GetTimeLocal(&tmp_in_time.tv_sec, &tm_data);

	tm_data.tm_year      = (tm_data.tm_year + 1900) % 10000;
	tm_data.tm_mon       = (tm_data.tm_mon + 1) % 100;
	tm_data.tm_mday     %= 100;
	tm_data.tm_hour     %= 100;
	tm_data.tm_min      %= 100;
	tm_data.tm_sec      %= 100;
	tmp_in_time.tv_nsec %= 1000000000L;

	buffer[0]            = ((char) ('0' + (tm_data.tm_year / 1000)));
	buffer[1]            = ((char) ('0' + ((tm_data.tm_year % 1000) / 100)));
	buffer[2]            = ((char) ('0' + ((tm_data.tm_year % 100) / 10)));
	buffer[3]            = ((char) ('0' + (tm_data.tm_year % 10)));
	buffer[4]            = '-';
	buffer[5]            = ((char) ('0' + (tm_data.tm_mon / 10)));
	buffer[6]            = ((char) ('0' + (tm_data.tm_mon % 10)));
	buffer[7]            = '-';
	buffer[8]            = ((char) ('0' + (tm_data.tm_mday / 10)));
	buffer[9]            = ((char) ('0' + (tm_data.tm_mday % 10)));
	buffer[10]           = ' ';
	buffer[11]           = ((char) ('0' + (tm_data.tm_hour / 10)));
	buffer[12]           = ((char) ('0' + (tm_data.tm_hour % 10)));
	buffer[13]           = ':';
	buffer[14]           = ((char) ('0' + (tm_data.tm_min / 10)));
	buffer[15]           = ((char) ('0' + (tm_data.tm_min % 10)));
	buffer[16]           = ':';
	buffer[17]           = ((char) ('0' + (tm_data.tm_sec / 10)));
	buffer[18]           = ((char) ('0' + (tm_data.tm_sec % 10)));
	buffer[19]           = '.';
	buffer[20]           =
		((char) ('0' + ((char) (tmp_in_time.tv_nsec /  100000000L))));
	buffer[21]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 100000000L) / 10000000L))));
	buffer[22]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 10000000L) / 1000000L))));
	buffer[23]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 1000000L) / 100000L))));
	buffer[24]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 100000L) / 10000L))));
	buffer[25]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 10000L) / 1000L))));
	buffer[26]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 1000L) / 100L))));
	buffer[27]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 100L) / 10L))));
	buffer[28]           =
		((char) ('0' + ((char) (tmp_in_time.tv_nsec %  10L))));
	buffer[29]           = '\0';

	return(buffer);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_Format_timespec_GMT

   SYNOPSIS    :  string_ptr = GEN_Format_timespec_GMT(in_time, buffer);

						char                  *string_ptr;

						const struct timespec *in_time;

						char                  *buffer;

   DESCRIPTION :  Formats a ''struct timespec'' datum as an GMT/UTC time-value
						string with the following format:

						``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``.``nnnnnnnnn``

						where ``nnnnnnnnn`` represents nanoseconds.

	PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the structure of type ''timespec''
						to be formatted as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 30 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_Format_timespec
						GEN_Format_time_t_GMT
						GEN_Format_tm_GMT
						GEN_Format_timeval_GMT
						GEN_FormatInterval_timespec

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_Format_timespec_GMT
						Date/Time Functions:GEN_Format_timespec_GMT
						GENFUNCS:Functions:GEN_Format_timespec_GMT
						GENFUNCS:Date/Time Functions:GEN_Format_timespec_GMT
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_Format_timespec_GMT

	PUBLISH NAME:	GEN_Format_timespec_GMT

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_Format_timespec_GMT(const struct timespec *in_time, char *buffer)
#else
char *GEN_Format_timespec_GMT(in_time, buffer)
const struct timespec *in_time;
char                  *buffer;
#endif /* #ifndef NARGS */
{
	struct tm       tm_data;
	struct timespec tmp_in_time;

	if (in_time != NULL) {
		tmp_in_time         = *in_time;
		tmp_in_time.tv_nsec = (tmp_in_time.tv_nsec >= 0L) ? tmp_in_time.tv_nsec :
			(0L - tmp_in_time.tv_nsec);
	}
	else
		GEN_GetTimeNSecs(&tmp_in_time);

	GEN_GetTimeGMT(&tmp_in_time.tv_sec, &tm_data);

	tm_data.tm_year      = (tm_data.tm_year + 1900) % 10000;
	tm_data.tm_mon       = (tm_data.tm_mon + 1) % 100;
	tm_data.tm_mday     %= 100;
	tm_data.tm_hour     %= 100;
	tm_data.tm_min      %= 100;
	tm_data.tm_sec      %= 100;
	tmp_in_time.tv_nsec %= 1000000000L;

	buffer[0]            = ((char) ('0' + (tm_data.tm_year / 1000)));
	buffer[1]            = ((char) ('0' + ((tm_data.tm_year % 1000) / 100)));
	buffer[2]            = ((char) ('0' + ((tm_data.tm_year % 100) / 10)));
	buffer[3]            = ((char) ('0' + (tm_data.tm_year % 10)));
	buffer[4]            = '-';
	buffer[5]            = ((char) ('0' + (tm_data.tm_mon / 10)));
	buffer[6]            = ((char) ('0' + (tm_data.tm_mon % 10)));
	buffer[7]            = '-';
	buffer[8]            = ((char) ('0' + (tm_data.tm_mday / 10)));
	buffer[9]            = ((char) ('0' + (tm_data.tm_mday % 10)));
	buffer[10]           = ' ';
	buffer[11]           = ((char) ('0' + (tm_data.tm_hour / 10)));
	buffer[12]           = ((char) ('0' + (tm_data.tm_hour % 10)));
	buffer[13]           = ':';
	buffer[14]           = ((char) ('0' + (tm_data.tm_min / 10)));
	buffer[15]           = ((char) ('0' + (tm_data.tm_min % 10)));
	buffer[16]           = ':';
	buffer[17]           = ((char) ('0' + (tm_data.tm_sec / 10)));
	buffer[18]           = ((char) ('0' + (tm_data.tm_sec % 10)));
	buffer[19]           = '.';
	buffer[20]           =
		((char) ('0' + ((char) (tmp_in_time.tv_nsec /  100000000L))));
	buffer[21]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 100000000L) / 10000000L))));
	buffer[22]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 10000000L) / 1000000L))));
	buffer[23]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 1000000L) / 100000L))));
	buffer[24]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 100000L) / 10000L))));
	buffer[25]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 10000L) / 1000L))));
	buffer[26]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 1000L) / 100L))));
	buffer[27]           =
		((char) ('0' + ((char) ((tmp_in_time.tv_nsec % 100L) / 10L))));
	buffer[28]           =
		((char) ('0' + ((char) (tmp_in_time.tv_nsec %  10L))));
	buffer[29]           = '\0';

	return(buffer);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_Format_ulong_time

   SYNOPSIS    :  string_ptr = GEN_Format_ulong_time(in_time, buffer);

						char                *string_ptr;

						const unsigned long *in_time;

						char                *buffer;

   DESCRIPTION :  Formats an ``unsigned long`` datum which represents a date
						as a series of decimal digits as:

						[``yy``]``yymmdd``

						as an local time-value string with the following format:

						``yyyy``-``mm``-``dd``

   PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the unsigned long to be formatted
						as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

	CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 11 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_Format_ulong_time_GMT
						GEN_Format_tm
						GEN_Format_timeval
						GEN_Format_time_t

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_Format_ulong_time
						Date/Time Functions:GEN_Format_ulong_time
						GENFUNCS:Functions:GEN_Format_ulong_time
						GENFUNCS:Date/Time Functions:GEN_Format_ulong_time
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_Format_ulong_time

   PUBLISH NAME:	GEN_Format_ulong_time

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_Format_ulong_time(const unsigned long *in_time, char *buffer)
#else
char *GEN_Format_ulong_time(in_time, buffer)
const unsigned long *in_time;
char                *buffer;
#endif /* #ifndef NARGS */
{
	unsigned long tmp_time;
	time_t        tmp_time_t;
	struct tm     tm_data;

	if (in_time != NULL) {
		tmp_time  = *in_time % 100000000L;
		tmp_time += (tmp_time <= 500101L) ? 20000000L : 0L;
		tmp_time += (tmp_time <= 991231L) ? 19000000L : 0L;
	}
	else {
		tmp_time_t = time(NULL);
		GEN_GetTimeLocal(&tmp_time_t, &tm_data);
		tmp_time   = (((tm_data.tm_year + 1900) % 10000) * 10000L) +
			(((tm_data.tm_mon + 1) % 100) * 100L) +
			((unsigned long) (tm_data.tm_mday % 100));
	}

	buffer[0]  = ((char) ('0' + ((tmp_time / 10000L) / 1000L)));
	buffer[1]  = ((char) ('0' + (((tmp_time / 10000L) % 1000L) / 100L)));
	buffer[2]  = ((char) ('0' + (((tmp_time / 10000L) % 100L) / 10L)));
	buffer[3]  = ((char) ('0' + ((tmp_time / 10000L) % 10L)));
	buffer[4]  = '-';
	buffer[5]  = ((char) ('0' + (((tmp_time % 10000L) / 100L) / 10L)));
	buffer[6]  = ((char) ('0' + (((tmp_time % 10000L) / 100L) % 10L)));
	buffer[7]  = '-';
	buffer[8]  = ((char) ('0' + ((tmp_time % 100L) / 10L)));
	buffer[9]  = ((char) ('0' + ((tmp_time % 100L) % 10L)));
	buffer[10] = '\0';

	return(buffer);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  GEN_Format_ulong_time_GMT

   SYNOPSIS    :  string_ptr = GEN_Format_ulong_time_GMT(in_time, buffer);

						char                *string_ptr;

						const unsigned long *in_time;

						char                *buffer;

   DESCRIPTION :  Formats an ``unsigned long`` datum which represents a date
						as a series of decimal digits as:

						[``yy``]``yymmdd``

						as an GMT/UTC time-value string with the following format:

						``yyyy``-``mm``-``dd``

   PARAMETERS  :  The parameters to this function are as follow:

						(.) ``in_time`` points to the unsigned long to be formatted
						as a string.

						(-) if ``in_time`` is a NULL pointer, the current time will
						be used.

						(.) ``out_string`` points to the string allocated by the
						invoking function to hold the formatted time string.

   RETURNS     :  A pointer to the formatted time string.

   NOTES       :  This function is designed to minimize running time, not
						executable code size.

   CAVEATS     :  The area to which the ``out_string`` parameter points
						should be at least 11 bytes in size.

						This function assumes that the ASCII character set is in
						use by the run-time environment. Use of this function with
						other character sets is not supported.

   SEE ALSO    :  GEN_Format_ulong_time
						GEN_Format_tm_GMT
						GEN_Format_timeval_GMT
						GEN_Format_time_t_GMT

   EXAMPLES    :  

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_Format_ulong_time_GMT
						Date/Time Functions:GEN_Format_ulong_time_GMT
						GENFUNCS:Functions:GEN_Format_ulong_time_GMT
						GENFUNCS:Date/Time Functions:GEN_Format_ulong_time_GMT
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_Format_ulong_time_GMT

   PUBLISH NAME:	GEN_Format_ulong_time_GMT

	ENTRY CLASS	:	Date/Time Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *GEN_Format_ulong_time_GMT(const unsigned long *in_time, char *buffer)
#else
char *GEN_Format_ulong_time_GMT(in_time, buffer)
const unsigned long *in_time;
char                *buffer;
#endif /* #ifndef NARGS */
{
	unsigned long tmp_time;
	time_t        tmp_time_t;
	struct tm     tm_data;

	if (in_time != NULL) {
		tmp_time  = *in_time % 100000000L;
		tmp_time += (tmp_time <= 500101L) ? 20000000L : 0L;
		tmp_time += (tmp_time <= 991231L) ? 19000000L : 0L;
	}
	else {
		tmp_time_t = time(NULL);
		GEN_GetTimeGMT(&tmp_time_t, &tm_data);
		tmp_time   = (((tm_data.tm_year + 1900) % 10000) * 10000L) +
			(((tm_data.tm_mon + 1) % 100) * 100L) +
			((unsigned long) (tm_data.tm_mday % 100));
	}

	buffer[0]  = ((char) ('0' + ((tmp_time / 10000L) / 1000L)));
	buffer[1]  = ((char) ('0' + (((tmp_time / 10000L) % 1000L) / 100L)));
	buffer[2]  = ((char) ('0' + (((tmp_time / 10000L) % 100L) / 10L)));
	buffer[3]  = ((char) ('0' + ((tmp_time / 10000L) % 10L)));
	buffer[4]  = '-';
	buffer[5]  = ((char) ('0' + (((tmp_time % 10000L) / 100L) / 10L)));
	buffer[6]  = ((char) ('0' + (((tmp_time % 10000L) / 100L) % 10L)));
	buffer[7]  = '-';
	buffer[8]  = ((char) ('0' + ((tmp_time % 100L) / 10L)));
	buffer[9]  = ((char) ('0' + ((tmp_time % 100L) % 10L)));
	buffer[10] = '\0';

	return(buffer);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#ifdef __MSDOS__
#include <dos.h>
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (void));

int main()
{
	struct timeval this_time;
	struct tm      tmp_tm_1;
	struct tm      tmp_tm_2;
	unsigned long  tmp_ulong_1;
	unsigned long  tmp_ulong_2;
	char           buffer[512];

	fprintf(stderr, "Test routine for 'GEN_Format_timeval()'\n");
	fprintf(stderr, "                 'GEN_Format_tm()'\n");
	fprintf(stderr, "                 'GEN_Format_time_t()'\n");
	fprintf(stderr, "                 'GEN_Format_ulong_time()'\n");
	fprintf(stderr, "                 -------------------------\n\n");

	GEN_GetTimeUSecs(&this_time);

	GEN_GetTimeLocal(&this_time.tv_sec, &tmp_tm_1);
	tmp_ulong_1 = (((tmp_tm_1.tm_year + 1900) % 10000) * 10000L) +
		(((tmp_tm_1.tm_mon + 1) % 100) * 100L) +
		((unsigned long) (tmp_tm_1.tm_mday % 100));
	GEN_GetTimeGMT(&this_time.tv_sec, &tmp_tm_2);
	tmp_ulong_2 = (((tmp_tm_1.tm_year + 1900) % 10000) * 10000L) +
		(((tmp_tm_1.tm_mon + 1) % 100) * 100L) +
		((unsigned long) (tmp_tm_1.tm_mday % 100));

	printf("With the current time:\n");
	printf("---- --- ------- -----\n");
	printf("   Result for 'GEN_Format_timeval()'       : %s\n",
		GEN_Format_timeval(&this_time, buffer));
	printf("   Result for 'GEN_Format_timeval_GMT()'   : %s\n",
		GEN_Format_timeval_GMT(&this_time, buffer));
	printf("   Result for 'GEN_Format_tm()'            : %s\n",
		GEN_Format_tm(&tmp_tm_1, buffer));
	printf("   Result for 'GEN_Format_tm_GMT()'        : %s\n",
		GEN_Format_tm_GMT(&tmp_tm_2, buffer));
	printf("   Result for 'GEN_Format_time_t()'        : %s\n",
		GEN_Format_time_t(&this_time.tv_sec, buffer));
	printf("   Result for 'GEN_Format_time_t_GMT()'    : %s\n",
		GEN_Format_time_t_GMT(&this_time.tv_sec, buffer));
	printf("   Result for 'GEN_Format_ulong_time()'    : %s\n",
		GEN_Format_ulong_time(&tmp_ulong_1, buffer));
	printf("   Result for 'GEN_Format_ulong_time_GMT()': %s\n",
		GEN_Format_ulong_time_GMT(&tmp_ulong_2, buffer));

	printf("Sleeping . . .\n");
	GEN_usleep(2 * 1000000);
	printf("\n");

	printf("With a NULL pointer:\n");
	printf("---- - ---- --------\n");
	printf("   Result for 'GEN_Format_timeval()'       : %s\n",
		GEN_Format_timeval(NULL, buffer));
	printf("   Result for 'GEN_Format_timeval_GMT()'   : %s\n",
		GEN_Format_timeval_GMT(NULL, buffer));
	printf("   Result for 'GEN_Format_tm()'            : %s\n",
		GEN_Format_tm(NULL, buffer));
	printf("   Result for 'GEN_Format_tm_GMT()'        : %s\n",
		GEN_Format_tm_GMT(NULL, buffer));
	printf("   Result for 'GEN_Format_time_t()'        : %s\n",
		GEN_Format_time_t(NULL, buffer));
	printf("   Result for 'GEN_Format_time_t_GMT()'    : %s\n",
		GEN_Format_time_t_GMT(NULL, buffer));
	printf("   Result for 'GEN_Format_ulong_time()'    : %s\n",
		GEN_Format_ulong_time(NULL, buffer));
	printf("   Result for 'GEN_Format_ulong_time_GMT()': %s\n",
		GEN_Format_ulong_time_GMT(NULL, buffer));

	return(0);
}

#endif /* #ifdef TEST_MAIN */

