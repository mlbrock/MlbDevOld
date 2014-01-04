/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
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

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/*	***********************************************************************	*/

#include <limits.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_TVAL_STAT_Init

	SYNOPSIS		:	return_ptr = GEN_TVAL_STAT_Init(stat_ptr);

						GEN_TVAL_STAT *return_ptr;

						GEN_TVAL_STAT *stat_ptr;

	DESCRIPTION	:	Initializes a ''GEN_TVAL_STAT'' structure.

						This function should be called before any of the other
						associated functions are called.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''GEN_TVAL_STAT'' structure
						to be initialized.

   RETURNS     : 	The ``stat_ptr`` parameter is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_TVAL_STAT_Init
						Statistics Gathering Functions:GEN_TVAL_STAT_Init
						GENFUNCS:Functions:GEN_TVAL_STAT_Init
						GENFUNCS:Statistics Gathering Functions:GEN_TVAL_STAT_Init
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_TVAL_STAT_Init

	PUBLISH NAME:	GEN_TVAL_STAT_Init

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
GEN_TVAL_STAT *GEN_TVAL_STAT_Init(GEN_TVAL_STAT *stat_ptr)
#else
GEN_TVAL_STAT *GEN_TVAL_STAT_Init(stat_ptr)
GEN_TVAL_STAT *stat_ptr;
#endif /* #ifndef NARGS */
{
	stat_ptr->maximum_stat_flag      = GENFUNCS_FALSE;
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

	NAME			:	GEN_TVAL_STAT_StartTime

	SYNOPSIS		:	return_ptr = GEN_TVAL_STAT_StartTime(stat_ptr);

						GEN_TVAL_STAT *return_ptr;

						GEN_TVAL_STAT *stat_ptr;

	DESCRIPTION	:	Starts statistics gathering for the specified structure of
						type ''GEN_TVAL_STAT''.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''GEN_TVAL_STAT'' structure
						for which statistics gathering is to be started.

   RETURNS     : 	The ``stat_ptr`` parameter is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_TVAL_STAT_EndTime

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_TVAL_STAT_StartTime
						Statistics Gathering Functions:GEN_TVAL_STAT_StartTime
						GENFUNCS:Functions:GEN_TVAL_STAT_StartTime
						GENFUNCS:Statistics Gathering Functions:GEN_TVAL_STAT_StartTime
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_TVAL_STAT_StartTime

	PUBLISH NAME:	GEN_TVAL_STAT_StartTime

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
GEN_TVAL_STAT *GEN_TVAL_STAT_StartTime(GEN_TVAL_STAT *stat_ptr)
#else
GEN_TVAL_STAT *GEN_TVAL_STAT_StartTime(stat_ptr)
GEN_TVAL_STAT *stat_ptr;
#endif /* #ifndef NARGS */
{
	if (stat_ptr->maximum_stat_flag != GENFUNCS_TRUE)
		GEN_GetTimeUSecs(&stat_ptr->tmp_last_start);

	return(stat_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_TVAL_STAT_EndTime

	SYNOPSIS		:	return_ptr = GEN_TVAL_STAT_EndTime(stat_ptr, item_count);

						GEN_TVAL_STAT *return_ptr;

						GEN_TVAL_STAT *stat_ptr;

						unsigned long  item_count;

	DESCRIPTION	:	Ends statistics gathering for the specified structure of
						type ''GEN_TVAL_STAT''.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''GEN_TVAL_STAT'' structure
						for which statistics gathering is to be ended.

						(.) ``item_count`` is the number of items processed in the
						statistics gathering pass to be ended.

   RETURNS     : 	The ``stat_ptr`` parameter is returned.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	GEN_TVAL_STAT_EndTimeSpecified
						GEN_TVAL_STAT_StartTime

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_TVAL_STAT_EndTime
						Statistics Gathering Functions:GEN_TVAL_STAT_EndTime
						GENFUNCS:Functions:GEN_TVAL_STAT_EndTime
						GENFUNCS:Statistics Gathering Functions:GEN_TVAL_STAT_EndTime
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_TVAL_STAT_EndTime

	PUBLISH NAME:	GEN_TVAL_STAT_EndTime

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
GEN_TVAL_STAT *GEN_TVAL_STAT_EndTime(GEN_TVAL_STAT *stat_ptr,
	unsigned long item_count)
#else
GEN_TVAL_STAT *GEN_TVAL_STAT_EndTime(stat_ptr, item_count)
GEN_TVAL_STAT *stat_ptr;
unsigned long  item_count;
#endif /* #ifndef NARGS */
{
	return(GEN_TVAL_STAT_EndTimeSpecified(stat_ptr, item_count, NULL));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_TVAL_STAT_EndTimeSpecified

	SYNOPSIS		:	return_ptr = GEN_TVAL_STAT_EndTimeSpecified(stat_ptr,
							item_count, last_end);

						GEN_TVAL_STAT *return_ptr;

						GEN_TVAL_STAT        *stat_ptr;

						unsigned long         item_count;

						const struct timeval *last_end;

	DESCRIPTION	:	Ends statistics gathering for the specified structure of
						type ''GEN_TVAL_STAT'' for a given end time.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''GEN_TVAL_STAT'' structure
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
						``GEN_TVAL_STAT_EndTime`` may be called.

	CAVEATS		:	

	SEE ALSO		:	GEN_TVAL_STAT_EndTime
						GEN_TVAL_STAT_StartTime

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_TVAL_STAT_EndTimeSpecified
						Statistics Gathering Functions:GEN_TVAL_STAT_EndTimeSpecified
						GENFUNCS:Functions:GEN_TVAL_STAT_EndTimeSpecified
						GENFUNCS:Statistics Gathering Functions:GEN_TVAL_STAT_EndTimeSpecified
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_TVAL_STAT_EndTimeSpecified

	PUBLISH NAME:	GEN_TVAL_STAT_EndTimeSpecified

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
GEN_TVAL_STAT *GEN_TVAL_STAT_EndTimeSpecified(GEN_TVAL_STAT *stat_ptr,
	unsigned long item_count, const struct timeval *last_end)
#else
GEN_TVAL_STAT *GEN_TVAL_STAT_EndTimeSpecified(stat_ptr, item_count, last_end)
GEN_TVAL_STAT        *stat_ptr;
unsigned long         item_count;
const struct timeval *last_end;
#endif /* #ifndef NARGS */
{
	GEN_TVAL_STAT  tmp_stat;
	double         total_usecs;
	struct timeval total_interval;

	if ((stat_ptr->maximum_stat_flag != GENFUNCS_TRUE) &&
		stat_ptr->tmp_last_start.tv_sec && item_count) {
		tmp_stat            = *stat_ptr;
		tmp_stat.last_start = tmp_stat.tmp_last_start;
		if (last_end != NULL)
			tmp_stat.last_end = *last_end;
		else
			GEN_GetTimeUSecs(&tmp_stat.last_end);
		GEN_GetABSInterval_timeval(&tmp_stat.last_start, &tmp_stat.last_end,
			&tmp_stat.last_interval);
		tmp_stat.last_count = item_count;
		total_usecs         = GEN_GET_TIMEVAL_USECS_DOUBLE(
			GEN_AddInterval_timeval(&tmp_stat.total_interval,
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
			stat_ptr->maximum_stat_flag = GENFUNCS_TRUE;
	}

	return(stat_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_TVAL_STAT_GetLastAverage

	SYNOPSIS		:	return_ptr = GEN_TVAL_STAT_GetLastAverage(stat_ptr,
							average_interval);

						struct timeval      *return_ptr;

						const GEN_TVAL_STAT *stat_ptr;

						struct timeval      *average_interval;

	DESCRIPTION	:	Calculates the average time per item processed for the last
						statistics gathering pass.

   PARAMETERS  :  Parameters to this function are as follows:

						(.) ``stat_ptr`` points to the ''GEN_TVAL_STAT'' structure
						for which the average time is to be calculated.

						(.) ``average_interval`` points to a structure of type
						''struct timeval'' into which this function will place the
						average.

   RETURNS     :  Returns a pointer to the ``average_interval`` parameter.

	NOTES			:	The word ``average`` in this context refers to the mean.

	CAVEATS		:	

	SEE ALSO		:	GEN_TVAL_STAT_GetTotalAverage
						GEN_TVAL_STAT_GetSampleAverage

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_TVAL_STAT_GetLastAverage
						Statistics Gathering Functions:GEN_TVAL_STAT_GetLastAverage
						GENFUNCS:Functions:GEN_TVAL_STAT_GetLastAverage
						GENFUNCS:Statistics Gathering Functions:GEN_TVAL_STAT_GetLastAverage
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_TVAL_STAT_GetLastAverage

	PUBLISH NAME:	GEN_TVAL_STAT_GetLastAverage

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timeval *GEN_TVAL_STAT_GetLastAverage(const GEN_TVAL_STAT *stat_ptr,
	struct timeval *average_interval)
#else
struct timeval *GEN_TVAL_STAT_GetLastAverage(stat_ptr, average_interval)
const GEN_TVAL_STAT *stat_ptr;
struct timeval      *average_interval;
#endif /* #ifndef NARGS */
{
	average_interval->tv_sec  = 0L;
	average_interval->tv_usec = 0L;

	return((stat_ptr->last_count && (stat_ptr->last_interval.tv_sec ||
		stat_ptr->last_interval.tv_usec)) ?
		GEN_GetPerInterval_timeval(&stat_ptr->last_interval,
		stat_ptr->last_count, average_interval) : average_interval);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_TVAL_STAT_GetTotalAverage

	SYNOPSIS		:	return_ptr = GEN_TVAL_STAT_GetTotalAverage(stat_ptr,
							average_interval);

						struct timeval      *return_ptr;

						const GEN_TVAL_STAT *stat_ptr;

						struct timeval      *average_interval;

	DESCRIPTION	:	Calculates the average time per item processed for all
						statistics gathering passes.

						(.) ``stat_ptr`` points to the ''GEN_TVAL_STAT'' structure
						for which the average time is to be calculated.

						(.) ``average_interval`` points to a structure of type
						''struct timeval'' into which this function will place the
						average.

   RETURNS     :  Returns a pointer to the ``average_interval`` parameter.

	NOTES			:	The word ``average`` in this context refers to the mean.

	CAVEATS		:	

	SEE ALSO		:	GEN_TVAL_STAT_GetLastAverage
						GEN_TVAL_STAT_GetSampleAverage

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_TVAL_STAT_GetTotalAverage
						Statistics Gathering Functions:GEN_TVAL_STAT_GetTotalAverage
						GENFUNCS:Functions:GEN_TVAL_STAT_GetTotalAverage
						GENFUNCS:Statistics Gathering Functions:GEN_TVAL_STAT_GetTotalAverage
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_TVAL_STAT_GetTotalAverage

	PUBLISH NAME:	GEN_TVAL_STAT_GetTotalAverage

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timeval *GEN_TVAL_STAT_GetTotalAverage(const GEN_TVAL_STAT *stat_ptr,
	struct timeval *average_interval)
#else
struct timeval *GEN_TVAL_STAT_GetTotalAverage(stat_ptr, average_interval)
const GEN_TVAL_STAT *stat_ptr;
struct timeval      *average_interval;
#endif /* #ifndef NARGS */
{
	average_interval->tv_sec  = 0L;
	average_interval->tv_usec = 0L;

	return((stat_ptr->total_count && (stat_ptr->total_interval.tv_sec ||
		stat_ptr->total_interval.tv_usec)) ?
		GEN_GetPerInterval_timeval(&stat_ptr->total_interval,
		stat_ptr->total_count, average_interval) : average_interval);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	GEN_TVAL_STAT_GetSampleAverage

	SYNOPSIS		:	return_ptr = GEN_TVAL_STAT_GetSampleAverage(stat_ptr,
							average_interval);

						struct timeval      *return_ptr;

						const GEN_TVAL_STAT *stat_ptr;

						struct timeval      *average_interval;

	DESCRIPTION	:	Calculates the average time per pass for all statistics
						gathering passes.

						(.) ``stat_ptr`` points to the ''GEN_TVAL_STAT'' structure
						for which the average time is to be calculated.

						(.) ``average_interval`` points to a structure of type
						''struct timeval'' into which this function will place the
						average.

   RETURNS     :  Returns a pointer to the ``average_interval`` parameter.

	NOTES			:	The word ``average`` in this context refers to the mean.

	CAVEATS		:	

	SEE ALSO		:	GEN_TVAL_STAT_GetLastAverage
						GEN_TVAL_STAT_GetTotalAverage

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	GEN_TVAL_STAT_GetSampleAverage
						Statistics Gathering Functions:GEN_TVAL_STAT_GetSampleAverage
						GENFUNCS:Functions:GEN_TVAL_STAT_GetSampleAverage
						GENFUNCS:Statistics Gathering Functions:GEN_TVAL_STAT_GetSampleAverage
						General Functions:See GENFUNCS

	PUBLISH XREF:	GEN_TVAL_STAT_GetSampleAverage

	PUBLISH NAME:	GEN_TVAL_STAT_GetSampleAverage

	ENTRY CLASS	:	Statistics Gathering Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
struct timeval *GEN_TVAL_STAT_GetSampleAverage(const GEN_TVAL_STAT *stat_ptr,
	struct timeval *average_interval)
#else
struct timeval *GEN_TVAL_STAT_GetSampleAverage(stat_ptr, average_interval)
const GEN_TVAL_STAT *stat_ptr;
struct timeval      *average_interval;
#endif /* #ifndef NARGS */
{
	average_interval->tv_sec  = 0L;
	average_interval->tv_usec = 0L;

	return((stat_ptr->sample_count && (stat_ptr->total_interval.tv_sec ||
		stat_ptr->total_interval.tv_usec)) ?
		GEN_GetPerInterval_timeval(&stat_ptr->total_interval,
		stat_ptr->sample_count, average_interval) : average_interval);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdlib.h>
 
COMPAT_FN_DECL(int main, (void));

int main()
{
	unsigned int   count_1;
	unsigned long  item_count;
	struct timeval average_interval;
   GEN_TVAL_STAT  stat_data;
	char           time_buffer[512];

	fprintf(stderr, "Test routine for 'GEN_TVAL' functions\n");
	fprintf(stderr, "---- ------- --- ---------- ---------\n\n");

	GEN_TVAL_STAT_Init(&stat_data);

	for (count_1 = 0; count_1 < 3; count_1++) {
		fprintf(stderr, "Statistics Test %u : %u seconds, %lu item_count\n",
			count_1 + 1, count_1 + 1,
			item_count = ((unsigned long) ((rand() >> 3) % 100)));
		GEN_TVAL_STAT_StartTime(&stat_data);
		GEN_usleep((count_1 + 1) * 1000000);
		GEN_TVAL_STAT_EndTime(&stat_data, item_count);
		fprintf(stderr, ">>> Last Interval : %s\n",
			GEN_FormatInterval_timeval(&stat_data.last_interval, time_buffer));
		fprintf(stderr, ">>> Total Interval: %s\n",
			GEN_FormatInterval_timeval(&stat_data.total_interval, time_buffer));
		fprintf(stderr, ">>> Last Average  : %s\n",
			GEN_FormatInterval_timeval(GEN_TVAL_STAT_GetLastAverage(&stat_data,
			&average_interval), time_buffer));
		fprintf(stderr, ">>> Total Average : %s\n",
			GEN_FormatInterval_timeval(GEN_TVAL_STAT_GetTotalAverage(&stat_data,
			&average_interval), time_buffer));
		fprintf(stderr, ">>> Sample Average: %s\n",
			GEN_FormatInterval_timeval(GEN_TVAL_STAT_GetSampleAverage(&stat_data,
			&average_interval), time_buffer));
		fprintf(stderr, "------------------- --------------------------\n");
	}

	return(0);
}

#endif /* #ifndef TEST_MAIN */

