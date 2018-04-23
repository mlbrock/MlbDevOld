/* *********************************************************************** */
/* *********************************************************************** */
/*	System Date/Time Interface Facility (SDTIF) Module Source File				*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Ensures compilation of macros.

	Revision History	:	2001-03-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include "sdtifi.h"

/* *********************************************************************** */

/* *********************************************************************** */
static const time_t          SDTIF_TEST_time_t   = SDTIF_TIME_T_ZERO;
static const struct tm       SDTIF_TEST_tm       = SDTIF_TM_ZERO;
static const struct timeval  SDTIF_TEST_timeval  = SDTIF_TIMEVAL_ZERO;
static const struct timespec SDTIF_TEST_timespec = SDTIF_TIMESPEC_ZERO;
static const unsigned long   SDTIF_TEST_ulong    = ((unsigned long) 1);
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
unsigned int SDTIF_TEST_DoMacros(time_t *time_t_ptr, struct tm *tm_ptr,
	struct timeval *timeval_ptr, struct timespec *timespec_ptr,
	unsigned long *ulong_ptr)
#else
unsigned int SDTIF_TEST_DoMacros(time_t_ptr, tm_ptr, timeval_ptr, timespec_ptr,
	ulong_ptr)
time_t          *time_t_ptr;
struct tm       *tm_ptr;
struct timeval  *timeval_ptr;
struct timespec *timespec_ptr;
unsigned long   *ulong_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int count = 0;

	if (SDTIF_COMPARE_TIME_T(&SDTIF_TEST_time_t, time_t_ptr))
		count++;
	else if (SDTIF_COMPARE_TM(&SDTIF_TEST_tm, tm_ptr))
		count++;
	else if (SDTIF_COMPARE_TIMEVAL(&SDTIF_TEST_timeval, timeval_ptr))
		count++;
	else if (SDTIF_GET_TIMEVAL_USECS_DOUBLE(timeval_ptr))
		count++;
	else if (SDTIF_GET_TIMEVAL_USECS(timeval_ptr))
		count++;
	else if (SDTIF_SET_TIMEVAL(timeval_ptr, 1L, 2L))
		count++;
	else if (SDTIF_SET_TIMEVAL_ZERO(timeval_ptr))
		count++;
	else if (SDTIF_TIMEVAL_IS_ZERO(timeval_ptr))
		count++;
	else if (SDTIF_TIMEVAL_IS_NONZERO(timeval_ptr))
		count++;
	else if (SDTIF_COMPARE_TIMESPEC(&SDTIF_TEST_timespec, timespec_ptr))
		count++;
	else if (SDTIF_GET_TIMESPEC_NSECS_DOUBLE(timespec_ptr))
		count++;
	else if (SDTIF_GET_TIMESPEC_NSECS(timespec_ptr))
		count++;
	else if (SDTIF_SET_TIMESPEC(timespec_ptr, 1L, 2L))
		count++;
	else if (SDTIF_SET_TIMESPEC_ZERO(timespec_ptr))
		count++;
	else if (SDTIF_TIMESPEC_IS_ZERO(timespec_ptr))
		count++;
	else if (SDTIF_TIMESPEC_IS_NONZERO(timespec_ptr))
		count++;
	else if (SDTIF_COMPARE_ULONG(&SDTIF_TEST_ulong, ulong_ptr))
		count++;

	return(count);
}
/* *********************************************************************** */

