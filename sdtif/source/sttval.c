/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	System Date/Time Interface Facility (SDTIF) Module Source File				*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support generalized operational statistics
								gathering using the 'struct timeval' structure.

	Revision History	:	1995-12-30 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <limits.h>

#include "sdtifi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_Init

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_Init(stat_ptr);

						SDTIF_STAT_TVAL *return_ptr;

						SDTIF_STAT_TVAL *stat_ptr;

	DESCRIPTION	:	Initializes a ''SDTIF_STAT_TVAL'' structure.

						This function should be called before any of the other
						associated functions are called.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						to be initialized.

	RETURNS     : 	The ``stat_ptr`` parameter is returned.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_Init
						Statistics Gathering Functions:SDTIF_STAT_TVAL_Init
						SDTIF:Functions:SDTIF_STAT_TVAL_Init
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_Init
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_Init

	PUBLISH NAME:	SDTIF_STAT_TVAL_Init

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_Init(SDTIF_STAT_TVAL *stat_ptr)
#else
SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_Init(stat_ptr)
SDTIF_STAT_TVAL *stat_ptr;
#endif /* #ifndef NARGS */
{
	stat_ptr->maximum_stat_flag      = SDTIF_FALSE;
	stat_ptr->sample_count           = 0L;
	stat_ptr->last_count             = 0L;
	stat_ptr->last_start.tv_sec      = 0L;
	stat_ptr->last_start.tv_usec     = 0L;
	stat_ptr->last_end.tv_sec        = 0L;
	stat_ptr->last_end.tv_usec       = 0L;
	stat_ptr->last_interval.tv_sec   = 0L;
	stat_ptr->last_interval.tv_usec  = 0L;
	stat_ptr->tmp_last_start.tv_sec  = 0L;
	stat_ptr->tmp_last_start.tv_usec = 0L;
	stat_ptr->total_count            = 0L;
	stat_ptr->total_interval.tv_sec  = 0L;
	stat_ptr->total_interval.tv_usec = 0L;

	return(stat_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_StartTime

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_StartTime(stat_ptr);

						SDTIF_STAT_TVAL *return_ptr;

						SDTIF_STAT_TVAL *stat_ptr;

	DESCRIPTION	:	Starts statistics gathering for the specified structure of
						type ''SDTIF_STAT_TVAL''.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						for which statistics gathering is to be started.

	RETURNS     : 	The ``stat_ptr`` parameter is returned.

	SEE ALSO		:	SDTIF_STAT_TVAL_EndTime

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_StartTime
						Statistics Gathering Functions:SDTIF_STAT_TVAL_StartTime
						SDTIF:Functions:SDTIF_STAT_TVAL_StartTime
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_StartTime
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_StartTime

	PUBLISH NAME:	SDTIF_STAT_TVAL_StartTime

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_StartTime(SDTIF_STAT_TVAL *stat_ptr)
#else
SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_StartTime(stat_ptr)
SDTIF_STAT_TVAL *stat_ptr;
#endif /* #ifndef NARGS */
{
	if (stat_ptr->maximum_stat_flag != SDTIF_TRUE)
		SDTIF_GetTimeUSecs(&stat_ptr->tmp_last_start);

	return(stat_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_EndTime

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_EndTime(stat_ptr, item_count);

						SDTIF_STAT_TVAL    *return_ptr;

						SDTIF_STAT_TVAL    *stat_ptr;

						unsigned long       item_count;

	DESCRIPTION	:	Ends statistics gathering for the specified structure of
						type ''SDTIF_STAT_TVAL''.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						for which statistics gathering is to be ended.

						(.) ``item_count`` is the number of items processed in the
						statistics gathering pass to be ended.

	RETURNS     : 	The ``stat_ptr`` parameter is returned.

	SEE ALSO		:	SDTIF_STAT_TVAL_EndTimeSpecified
						SDTIF_STAT_TVAL_StartTime

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_EndTime
						Statistics Gathering Functions:SDTIF_STAT_TVAL_EndTime
						SDTIF:Functions:SDTIF_STAT_TVAL_EndTime
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_EndTime
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_EndTime

	PUBLISH NAME:	SDTIF_STAT_TVAL_EndTime

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_EndTime(SDTIF_STAT_TVAL *stat_ptr,
	unsigned long item_count)
#else
SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_EndTime(stat_ptr, item_count)
SDTIF_STAT_TVAL *stat_ptr;
unsigned long    item_count;
#endif /* #ifndef NARGS */
{
	return(SDTIF_STAT_TVAL_EndTimeSpecified(stat_ptr, item_count, NULL));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_EndTimeSpecified

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_EndTimeSpecified(stat_ptr,
							item_count, last_end);

						SDTIF_STAT_TVAL      *return_ptr;

						SDTIF_STAT_TVAL      *stat_ptr;

						unsigned long         item_count;

						const struct timeval *last_end;

	DESCRIPTION	:	Ends statistics gathering for the specified structure of
						type ''SDTIF_STAT_TVAL'' for a given end time.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						for which statistics gathering is to be ended.

						(.) ``item_count`` is the number of items processed in the
						statistics gathering pass to be ended.

						(.) ``end_time`` is a pointer to structure of type
						''struct timeval'' in which is stored the end time for
						for the statistics gathering pass to be ended.

						(-) Note that if the ``end_time`` parameter is ''NULL'',
						the function will use the current time.

	RETURNS     : 	The ``stat_ptr`` parameter is returned.

	NOTES			:	If the application programmer wishes the function to
						determine the end time for the statistics gathering pass,
						this function may be called with ``end_time`` equal to
						''NULL''. Alternatively, the related function
						``SDTIF_STAT_TVAL_EndTime`` may be called.

	SEE ALSO		:	SDTIF_STAT_TVAL_EndTime
						SDTIF_STAT_TVAL_StartTime

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_EndTimeSpecified
						Statistics Gathering Functions:SDTIF_STAT_TVAL_EndTimeSpecified
						SDTIF:Functions:SDTIF_STAT_TVAL_EndTimeSpecified
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_EndTimeSpecified
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_EndTimeSpecified

	PUBLISH NAME:	SDTIF_STAT_TVAL_EndTimeSpecified

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_EndTimeSpecified(SDTIF_STAT_TVAL *stat_ptr,
	unsigned long item_count, const struct timeval *last_end)
#else
SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_EndTimeSpecified(stat_ptr, item_count,
	last_end)
SDTIF_STAT_TVAL      *stat_ptr;
unsigned long         item_count;
const struct timeval *last_end;
#endif /* #ifndef NARGS */
{
	SDTIF_STAT_TVAL  tmp_stat;
	double         total_usecs;
	struct timeval total_interval;

	if ((stat_ptr->maximum_stat_flag != SDTIF_TRUE) &&
		stat_ptr->tmp_last_start.tv_sec && item_count) {
		tmp_stat            = *stat_ptr;
		tmp_stat.last_start = tmp_stat.tmp_last_start;
		if (last_end != NULL)
			tmp_stat.last_end = *last_end;
		else
			SDTIF_GetTimeUSecs(&tmp_stat.last_end);
		SDTIF_GetABSInterval_timeval(&tmp_stat.last_start, &tmp_stat.last_end,
			&tmp_stat.last_interval);
		tmp_stat.last_count = item_count;
		total_usecs         = SDTIF_GET_TIMEVAL_USECS_DOUBLE(
			SDTIF_AddInterval_timeval(&tmp_stat.total_interval,
			&tmp_stat.last_interval, &total_interval));
		if ((tmp_stat.sample_count < ULONG_MAX) && (tmp_stat.total_count <
			(tmp_stat.total_count + tmp_stat.last_count)) &&
			((total_usecs / 1000000.0) < ((double) LONG_MAX))) {
			tmp_stat.sample_count++;
			tmp_stat.total_count    += tmp_stat.last_count;
			tmp_stat.total_interval  = total_interval;
			*stat_ptr                = tmp_stat;
		}
		else
			stat_ptr->maximum_stat_flag = SDTIF_TRUE;
	}

	return(stat_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_GetLastAverage

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_GetLastAverage(stat_ptr,
							average_interval);

						struct timeval        *return_ptr;

						const SDTIF_STAT_TVAL *stat_ptr;

						struct timeval        *average_interval;

	DESCRIPTION	:	Calculates the average time per item processed for the last
						statistics gathering pass.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						for which the average time is to be calculated.

						(.) ``average_interval`` points to a structure of type
						''struct timeval'' into which this function will place the
						average.

	RETURNS     :  Returns a pointer to the ``average_interval`` parameter.

	NOTES			:	The word ``average`` in this context refers to the mean.

	SEE ALSO		:	SDTIF_STAT_TVAL_GetTotalAverage
						SDTIF_STAT_TVAL_GetSampleAverage

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_GetLastAverage
						Statistics Gathering Functions:SDTIF_STAT_TVAL_GetLastAverage
						SDTIF:Functions:SDTIF_STAT_TVAL_GetLastAverage
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_GetLastAverage
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_GetLastAverage

	PUBLISH NAME:	SDTIF_STAT_TVAL_GetLastAverage

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timeval *SDTIF_STAT_TVAL_GetLastAverage(const SDTIF_STAT_TVAL *stat_ptr,
	struct timeval *average_interval)
#else
struct timeval *SDTIF_STAT_TVAL_GetLastAverage(stat_ptr, average_interval)
const SDTIF_STAT_TVAL *stat_ptr;
struct timeval        *average_interval;
#endif /* #ifndef NARGS */
{
	average_interval->tv_sec  = 0L;
	average_interval->tv_usec = 0L;

	return((stat_ptr->last_count && (stat_ptr->last_interval.tv_sec ||
		stat_ptr->last_interval.tv_usec)) ?
		SDTIF_GetPerInterval_timeval(&stat_ptr->last_interval,
		stat_ptr->last_count, average_interval) : average_interval);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_GetTotalAverage

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_GetTotalAverage(stat_ptr,
							average_interval);

						struct timeval        *return_ptr;

						const SDTIF_STAT_TVAL *stat_ptr;

						struct timeval        *average_interval;

	DESCRIPTION	:	Calculates the average time per item processed for all
						statistics gathering passes.

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						for which the average time is to be calculated.

						(.) ``average_interval`` points to a structure of type
						''struct timeval'' into which this function will place the
						average.

	RETURNS     :  Returns a pointer to the ``average_interval`` parameter.

	NOTES			:	The word ``average`` in this context refers to the mean.

	SEE ALSO		:	SDTIF_STAT_TVAL_GetLastAverage
						SDTIF_STAT_TVAL_GetSampleAverage

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_GetTotalAverage
						Statistics Gathering Functions:SDTIF_STAT_TVAL_GetTotalAverage
						SDTIF:Functions:SDTIF_STAT_TVAL_GetTotalAverage
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_GetTotalAverage
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_GetTotalAverage

	PUBLISH NAME:	SDTIF_STAT_TVAL_GetTotalAverage

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timeval *SDTIF_STAT_TVAL_GetTotalAverage(const SDTIF_STAT_TVAL *stat_ptr,
	struct timeval *average_interval)
#else
struct timeval *SDTIF_STAT_TVAL_GetTotalAverage(stat_ptr, average_interval)
const SDTIF_STAT_TVAL *stat_ptr;
struct timeval        *average_interval;
#endif /* #ifndef NARGS */
{
	average_interval->tv_sec  = 0L;
	average_interval->tv_usec = 0L;

	return((stat_ptr->total_count && (stat_ptr->total_interval.tv_sec ||
		stat_ptr->total_interval.tv_usec)) ?
		SDTIF_GetPerInterval_timeval(&stat_ptr->total_interval,
		stat_ptr->total_count, average_interval) : average_interval);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_GetSampleAverage

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_GetSampleAverage(stat_ptr,
							average_interval);

						struct timeval        *return_ptr;

						const SDTIF_STAT_TVAL *stat_ptr;

						struct timeval        *average_interval;

	DESCRIPTION	:	Calculates the average time per pass for all statistics
						gathering passes.

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						for which the average time is to be calculated.

						(.) ``average_interval`` points to a structure of type
						''struct timeval'' into which this function will place the
						average.

	RETURNS     :  Returns a pointer to the ``average_interval`` parameter.

	NOTES			:	The word ``average`` in this context refers to the mean.

	SEE ALSO		:	SDTIF_STAT_TVAL_GetLastAverage
						SDTIF_STAT_TVAL_GetTotalAverage

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_GetSampleAverage
						Statistics Gathering Functions:SDTIF_STAT_TVAL_GetSampleAverage
						SDTIF:Functions:SDTIF_STAT_TVAL_GetSampleAverage
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_GetSampleAverage
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_GetSampleAverage

	PUBLISH NAME:	SDTIF_STAT_TVAL_GetSampleAverage

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timeval *SDTIF_STAT_TVAL_GetSampleAverage(
	const SDTIF_STAT_TVAL *stat_ptr, struct timeval *average_interval)
#else
struct timeval *SDTIF_STAT_TVAL_GetSampleAverage(stat_ptr, average_interval)
const SDTIF_STAT_TVAL *stat_ptr;
struct timeval        *average_interval;
#endif /* #ifndef NARGS */
{
	average_interval->tv_sec  = 0L;
	average_interval->tv_usec = 0L;

	return((stat_ptr->sample_count && (stat_ptr->total_interval.tv_sec ||
		stat_ptr->total_interval.tv_usec)) ?
		SDTIF_GetPerInterval_timeval(&stat_ptr->total_interval,
		stat_ptr->sample_count, average_interval) : average_interval);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_FmtLastAverage

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_FmtLastAverage(stat_ptr,
							buffer);

						char                  *return_ptr;

						const SDTIF_STAT_TVAL *stat_ptr;

						char                  *buffer;

	DESCRIPTION	:	Calculates and formats as a string the average time per
						item processed for the last statistics gathering pass.

						The string is formatted with the following format:

						``dddddddddd`` ``hh``:``mm``:``ss``.``uuuuuu``

						Where:

						(.) ``dddddddddd`` is the number of days.

						(.) ``hh`` is the number of hours.

						(.) ``mm`` is the number of minutes.

						(.) ``ss`` is the number of seconds.

						(.) ``uuuuuu`` is the number of microseconds.

						Note that there is a space (ASCII 32) between the
						``dddddddddd`` and ``hh`` components of the string.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						for which the average time is to be calculated.

						(.) ``buffer`` points to the string allocated by the
						invoking function to hold the formatted time string.

	RETURNS     :  A pointer to the formatted time string ``buffer``.

	NOTES			:	The word ``average`` in this context refers to the mean.

	CAVEATS     :  The area to which the ``buffer`` parameter points
						should be at least ''SDTIF_FMTI_TIME_LEN_STAT_TVAL + 1''
						(26 + 1) bytes in size.

	SEE ALSO		:	SDTIF_STAT_TVAL_FmtTotalAverage
						SDTIF_STAT_TVAL_FmtSampleAverage
						SDTIF_STAT_TVAL_GetLastAverage
						SDTIF_STAT_TVAL_FmtLastInterval

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_FmtLastAverage
						Statistics Gathering Functions:SDTIF_STAT_TVAL_FmtLastAverage
						SDTIF:Functions:SDTIF_STAT_TVAL_FmtLastAverage
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_FmtLastAverage
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_FmtLastAverage

	PUBLISH NAME:	SDTIF_STAT_TVAL_FmtLastAverage

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *SDTIF_STAT_TVAL_FmtLastAverage(const SDTIF_STAT_TVAL *stat_ptr,
	char *buffer)
#else
char *SDTIF_STAT_TVAL_FmtLastAverage(stat_ptr, buffer)
const SDTIF_STAT_TVAL *stat_ptr;
char                  *buffer;
#endif /* #ifndef NARGS */
{
	struct timeval average_interval;

	return(SDTIF_FormatInterval_timeval(SDTIF_STAT_TVAL_GetLastAverage(
		stat_ptr, &average_interval), buffer));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_FmtTotalAverage

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_FmtTotalAverage(stat_ptr,
							buffer);

						char                  *return_ptr;

						const SDTIF_STAT_TVAL *stat_ptr;

						char                  *buffer;

	DESCRIPTION	:	Calculates and formats as a string the average time per
						item processed for all statistics gathering passes.

						The string is formatted with the following format:

						``dddddddddd`` ``hh``:``mm``:``ss``.``uuuuuu``

						Where:

						(.) ``dddddddddd`` is the number of days.

						(.) ``hh`` is the number of hours.

						(.) ``mm`` is the number of minutes.

						(.) ``ss`` is the number of seconds.

						(.) ``uuuuuu`` is the number of microseconds.

						Note that there is a space (ASCII 32) between the
						``dddddddddd`` and ``hh`` components of the string.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						for which the average time is to be calculated.

						(.) ``buffer`` points to the string allocated by the
						invoking function to hold the formatted time string.

	RETURNS     :  A pointer to the formatted time string ``buffer``.

	NOTES			:	The word ``average`` in this context refers to the mean.

	CAVEATS     :  The area to which the ``buffer`` parameter points
						should be at least ''SDTIF_FMTI_TIME_LEN_STAT_TVAL + 1''
						(26 + 1) bytes in size.

	SEE ALSO		:	SDTIF_STAT_TVAL_FmtLastAverage
						SDTIF_STAT_TVAL_FmtSampleAverage
						SDTIF_STAT_TVAL_GetTotalAverage
						SDTIF_STAT_TVAL_FmtTotalInterval

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_FmtTotalAverage
						Statistics Gathering Functions:SDTIF_STAT_TVAL_FmtTotalAverage
						SDTIF:Functions:SDTIF_STAT_TVAL_FmtTotalAverage
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_FmtTotalAverage
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_FmtTotalAverage

	PUBLISH NAME:	SDTIF_STAT_TVAL_FmtTotalAverage

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *SDTIF_STAT_TVAL_FmtTotalAverage(const SDTIF_STAT_TVAL *stat_ptr,
	char *buffer)
#else
char *SDTIF_STAT_TVAL_FmtTotalAverage(stat_ptr, buffer)
const SDTIF_STAT_TVAL *stat_ptr;
char                  *buffer;
#endif /* #ifndef NARGS */
{
	struct timeval average_interval;

	return(SDTIF_FormatInterval_timeval(SDTIF_STAT_TVAL_GetTotalAverage(
		stat_ptr, &average_interval), buffer));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_FmtSampleAverage

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_FmtSampleAverage(stat_ptr,
							buffer);

						char                  *return_ptr;

						const SDTIF_STAT_TVAL *stat_ptr;

						char                  *buffer;

						The string is formatted with the following format:

						``dddddddddd`` ``hh``:``mm``:``ss``.``uuuuuu``

						Where:

						(.) ``dddddddddd`` is the number of days.

						(.) ``hh`` is the number of hours.

						(.) ``mm`` is the number of minutes.

						(.) ``ss`` is the number of seconds.

						(.) ``uuuuuu`` is the number of microseconds.

						Note that there is a space (ASCII 32) between the
						``dddddddddd`` and ``hh`` components of the string.

	DESCRIPTION	:	Calculates and formats as a string the average time per
						pass for all statistics gathering passes.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						for which the average time is to be calculated.

						(.) ``buffer`` points to the string allocated by the
						invoking function to hold the formatted time string.

	RETURNS     :  A pointer to the formatted time string ``buffer``.

	NOTES			:	The word ``average`` in this context refers to the mean.

	CAVEATS     :  The area to which the ``buffer`` parameter points
						should be at least ''SDTIF_FMTI_TIME_LEN_STAT_TVAL + 1''
						(26 + 1) bytes in size.

	SEE ALSO		:	SDTIF_STAT_TVAL_FmtLastAverage
						SDTIF_STAT_TVAL_FmtTotalAverage
						SDTIF_STAT_TVAL_GetSampleAverage

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_FmtSampleAverage
						Statistics Gathering Functions:SDTIF_STAT_TVAL_FmtSampleAverage
						SDTIF:Functions:SDTIF_STAT_TVAL_FmtSampleAverage
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_FmtSampleAverage
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_FmtSampleAverage

	PUBLISH NAME:	SDTIF_STAT_TVAL_FmtSampleAverage

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *SDTIF_STAT_TVAL_FmtSampleAverage(const SDTIF_STAT_TVAL *stat_ptr,
	char *buffer)
#else
char *SDTIF_STAT_TVAL_FmtSampleAverage(stat_ptr, buffer)
const SDTIF_STAT_TVAL *stat_ptr;
char                  *buffer;
#endif /* #ifndef NARGS */
{
	struct timeval average_interval;

	return(SDTIF_FormatInterval_timeval(SDTIF_STAT_TVAL_GetSampleAverage(
		stat_ptr, &average_interval), buffer));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_FmtLastInterval

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_FmtLastInterval(stat_ptr,
							buffer);

						char                  *return_ptr;

						const SDTIF_STAT_TVAL *stat_ptr;

						char                  *buffer;

	DESCRIPTION	:	Formats as a string the last time interval for items
						processed in the last statistics gathering pass.

						The string is formatted with the following format:

						``dddddddddd`` ``hh``:``mm``:``ss``.``uuuuuu``

						Where:

						(.) ``dddddddddd`` is the number of days.

						(.) ``hh`` is the number of hours.

						(.) ``mm`` is the number of minutes.

						(.) ``ss`` is the number of seconds.

						(.) ``uuuuuu`` is the number of microseconds.

						Note that there is a space (ASCII 32) between the
						``dddddddddd`` and ``hh`` components of the string.

	PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						for which the time interval is to be formatted.

						(.) ``buffer`` points to the string allocated by the
						invoking function to hold the formatted time string.

	RETURNS     :  A pointer to the formatted time string ``buffer``.

	CAVEATS     :  The area to which the ``buffer`` parameter points
						should be at least ''SDTIF_FMTI_TIME_LEN_STAT_TVAL + 1''
						(26 + 1) bytes in size.

	SEE ALSO		:	SDTIF_STAT_TVAL_FmtLastAverage
						SDTIF_STAT_TVAL_FmtTotalInterval

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_FmtLastInterval
						Statistics Gathering Functions:SDTIF_STAT_TVAL_FmtLastInterval
						SDTIF:Functions:SDTIF_STAT_TVAL_FmtLastInterval
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_FmtLastInterval
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_FmtLastInterval

	PUBLISH NAME:	SDTIF_STAT_TVAL_FmtLastInterval

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *SDTIF_STAT_TVAL_FmtLastInterval(const SDTIF_STAT_TVAL *stat_ptr,
	char *buffer)
#else
char *SDTIF_STAT_TVAL_FmtLastInterval(stat_ptr, buffer)
const SDTIF_STAT_TVAL *stat_ptr;
char                  *buffer;
#endif /* #ifndef NARGS */
{
	return(SDTIF_FormatInterval_timeval(&stat_ptr->last_interval, buffer));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_STAT_TVAL_FmtTotalInterval

	SYNOPSIS		:	return_ptr = SDTIF_STAT_TVAL_FmtTotalInterval(stat_ptr,
							buffer);

						char                  *return_ptr;

						const SDTIF_STAT_TVAL *stat_ptr;

						char                  *buffer;

	DESCRIPTION	:	Formats as a string the total time interval for items
						processed in all statistics gathering passes.

						The string is formatted with the following format:

						``dddddddddd`` ``hh``:``mm``:``ss``.``uuuuuu``

						Where:

						(.) ``dddddddddd`` is the number of days.

						(.) ``hh`` is the number of hours.

						(.) ``mm`` is the number of minutes.

						(.) ``ss`` is the number of seconds.

						(.) ``uuuuuu`` is the number of microseconds.

						Note that there is a space (ASCII 32) between the
						``dddddddddd`` and ``hh`` components of the string.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``stat_ptr`` points to the ''SDTIF_STAT_TVAL'' structure
						for which the total time interval is to be formatted.

						(.) ``buffer`` points to the string allocated by the
						invoking function to hold the formatted time string.

	RETURNS     :  A pointer to the formatted time string ``buffer``.

	CAVEATS     :  The area to which the ``buffer`` parameter points
						should be at least ''SDTIF_FMTI_TIME_LEN_STAT_TVAL + 1''
						(26 + 1) bytes in size.

	SEE ALSO		:	SDTIF_STAT_TVAL_FmtLastInterval
						SDTIF_STAT_TVAL_FmtTotalAverage

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	SDTIF_STAT_TVAL_FmtTotalInterval
						Statistics Gathering Functions:SDTIF_STAT_TVAL_FmtTotalInterval
						SDTIF:Functions:SDTIF_STAT_TVAL_FmtTotalInterval
						SDTIF:Statistics Gathering Functions:SDTIF_STAT_TVAL_FmtTotalInterval
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_STAT_TVAL_FmtTotalInterval

	PUBLISH NAME:	SDTIF_STAT_TVAL_FmtTotalInterval

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *SDTIF_STAT_TVAL_FmtTotalInterval(const SDTIF_STAT_TVAL *stat_ptr,
	char *buffer)
#else
char *SDTIF_STAT_TVAL_FmtTotalInterval(stat_ptr, buffer)
const SDTIF_STAT_TVAL *stat_ptr;
char                  *buffer;
#endif /* #ifndef NARGS */
{
	return(SDTIF_FormatInterval_timeval(&stat_ptr->total_interval, buffer));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>
 
COMPAT_FN_DECL(int main, (void));

int main()
{
	unsigned int    count_1;
	unsigned long   item_count;
	unsigned long   total_item_count;
	struct timeval  average_interval;
	SDTIF_STAT_TVAL stat_data;
	char            time_buffer[512];

	fprintf(stderr, "Test routine for 'SDTIF_STAT_TVAL' functions\n");
	fprintf(stderr, "---- ------- --- ----------------- ---------\n\n");

	SDTIF_STAT_TVAL_Init(&stat_data);

	total_item_count = 0L;

	for (count_1 = 0; count_1 < 3; count_1++) {
		item_count        = ((unsigned long) ((rand() >> 3) % 100));
		total_item_count += item_count;
		fprintf(stderr,
			"%s %u              : %u seconds, %lu item_count, total count = %lu\n",
			"Statistics Test",
			count_1 + 1, count_1 + 1, item_count, total_item_count);
		SDTIF_STAT_TVAL_StartTime(&stat_data);
		SDTIF_sleep(count_1 + 1);
		SDTIF_STAT_TVAL_EndTime(&stat_data, item_count);
		fprintf(stderr, "%s %s\n",
			"--------------------------------", "--------------------------");
		fprintf(stderr, ">>> Last Interval (calculated) : %s\n",
			SDTIF_FormatInterval_timeval(&stat_data.last_interval, time_buffer));
		fprintf(stderr, ">>> Last Interval (formatted)  : %s\n",
			SDTIF_STAT_TVAL_FmtLastInterval(&stat_data, time_buffer));
		fprintf(stderr, ">>> Total Interval (calculated): %s\n",
			SDTIF_FormatInterval_timeval(&stat_data.total_interval, time_buffer));
		fprintf(stderr, ">>> Total Interval (formatted) : %s\n",
			SDTIF_STAT_TVAL_FmtTotalInterval(&stat_data, time_buffer));
		fprintf(stderr, ">>> Last Average (calculated)  : %s\n",
			SDTIF_FormatInterval_timeval(SDTIF_STAT_TVAL_GetLastAverage(&stat_data,
			&average_interval), time_buffer));
		fprintf(stderr, ">>> Last Average (formatted)   : %s\n",
			SDTIF_STAT_TVAL_FmtLastAverage(&stat_data, time_buffer));
		fprintf(stderr, ">>> Total Average (calculated) : %s\n",
			SDTIF_FormatInterval_timeval(SDTIF_STAT_TVAL_GetTotalAverage(&stat_data,
			&average_interval), time_buffer));
		fprintf(stderr, ">>> Total Average (formatted)  : %s\n",
			SDTIF_STAT_TVAL_FmtTotalAverage(&stat_data, time_buffer));
		fprintf(stderr, ">>> Sample Average (calculated): %s\n",
			SDTIF_FormatInterval_timeval(SDTIF_STAT_TVAL_GetSampleAverage(&stat_data,
			&average_interval), time_buffer));
		fprintf(stderr, ">>> Sample Average (formatted) : %s\n",
			SDTIF_STAT_TVAL_FmtSampleAverage(&stat_data, time_buffer));
		fprintf(stderr, "%s %s\n\n",
			"================================", "==========================");
	}

	return(0);
}

#endif /* #ifndef TEST_MAIN */

