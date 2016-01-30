/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	System Date/Time Interface Facility (SDTIF) Module Source File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets a variety of time measurement values.

	Revision History	:	1985-10-31 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1985 - 2016.
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
/*	Support for operating systems other than Unix . . .							*/
/*	***********************************************************************	*/
#ifdef __MSDOS__
# include <sys/timeb.h>
#endif /* #ifdef __MSDOS__ */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
struct tm *SDTIF_GetTimeLocal(const time_t *in_time, struct tm *time_buffer)
#else
struct tm *SDTIF_GetTimeLocal(in_time, time_buffer)
const time_t *in_time;
struct tm    *time_buffer;
#endif /* #ifndef NARGS */
{
	time_t tmp_in_time;

	tmp_in_time = (in_time == NULL)             ? time(NULL)    : *in_time;
	tmp_in_time = (tmp_in_time < ((time_t) 0L)) ? ((time_t) 0L) : tmp_in_time;

#ifdef _Windows
	*time_buffer = *localtime(&tmp_in_time);
#else
# if defined(__EXTENSIONS__) || defined(_REENTRANT) || defined(_POSIX_C_SOURCE)
	localtime_r(&tmp_in_time, time_buffer);
# else
	*time_buffer = *localtime(&tmp_in_time);
# endif /* #if defined(__EXTENSIONS__ || _REENTRANT || _POSIX_C_SOURCE) */
#endif /* #ifdef _Windows */

	return(time_buffer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
struct tm *SDTIF_GetTimeGMT(const time_t *in_time, struct tm *time_buffer)
#else
struct tm *SDTIF_GetTimeGMT(in_time, time_buffer)
const time_t *in_time;
struct tm    *time_buffer;
#endif /* #ifndef NARGS */
{
	time_t tmp_in_time;

	tmp_in_time = (in_time == NULL)             ? time(NULL)    : *in_time;
	tmp_in_time = (tmp_in_time < ((time_t) 0L)) ? ((time_t) 0L) : tmp_in_time;

#ifdef _Windows
	*time_buffer = *gmtime(&tmp_in_time);
#else
# if defined(__EXTENSIONS__) || defined(_REENTRANT) || defined(_POSIX_C_SOURCE)
	gmtime_r(&tmp_in_time, time_buffer);
# else
	*time_buffer = *gmtime(&tmp_in_time);
# endif /* #if defined(__EXTENSIONS__ || _REENTRANT || _POSIX_C_SOURCE) */
#endif /* #ifdef _Windows */

	return(time_buffer);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
struct tm *SDTIF_GetTime_tm(struct tm *out_time)
#else
struct tm *SDTIF_GetTime_tm(out_time)
struct tm *out_time;
#endif /* #ifndef NARGS */
{
	return(SDTIF_GetTimeLocal(NULL, out_time));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
struct tm *SDTIF_GetTime_tm_GMT(struct tm *out_time)
#else
struct tm *SDTIF_GetTime_tm_GMT(out_time)
struct tm *out_time;
#endif /* #ifndef NARGS */
{
	return(SDTIF_GetTimeGMT(NULL, out_time));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
unsigned long SDTIF_GetTime_ulong(void)
#else
unsigned long SDTIF_GetTime_ulong()
#endif /* #ifndef NARGS */
{
	struct tm tm_data;

	SDTIF_GetTimeLocal(NULL, &tm_data);

	return(((unsigned long) (((tm_data.tm_year + 1900) % 10000) * 10000L)) +
		((unsigned long) (((tm_data.tm_mon + 1) % 100) * 100L)) +
		((unsigned long) (tm_data.tm_mday % 100)));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
unsigned long SDTIF_GetTime_ulong_GMT(void)
#else
unsigned long SDTIF_GetTime_ulong_GMT()
#endif /* #ifndef NARGS */
{
	struct tm tm_data;

	SDTIF_GetTimeGMT(NULL, &tm_data);

	return(((unsigned long) (((tm_data.tm_year + 1900) % 10000) * 10000L)) +
		((unsigned long) (((tm_data.tm_mon + 1) % 100) * 100L)) +
		((unsigned long) (tm_data.tm_mday % 100)));
}
/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
#ifndef NARGS
int SDTIF_gettimeofday(struct timeval *time_ptr, struct timezone *timezone_ptr)
#else
int SDTIF_gettimeofday(time_ptr, timezone_ptr)
struct timeval  *time_ptr;
struct timezone *timezone_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = 0;

#ifdef __MSDOS__
	SDTIF_GetTimeUSecs(time_ptr);
#elif _Windows
	SDTIF_GetTimeUSecs(time_ptr);
#else
	return_code = gettimeofday(time_ptr, timezone_ptr);
#endif /* #ifdef __MSDOS__ */

	return(return_code);
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

#ifdef __MWERKS__
# pragma ANSI_strict off
#endif /* #ifdef __MWERKS__ */
/*	***********************************************************************	*/
#ifndef NARGS
struct timeval *SDTIF_GetTimeUSecs(struct timeval *time_ptr)
#else
struct timeval *SDTIF_GetTimeUSecs(time_ptr)
struct timeval *time_ptr;
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	struct timeb struct_timeb;

	ftime(&struct_timeb);
	time_ptr->tv_sec  = struct_timeb.time;
	time_ptr->tv_usec = ((long) struct_timeb.millitm) * 1000L;
#elif _Windows
	SDTIF_WIN32_FILETIME_64 sys_time;

	GetSystemTimeAsFileTime(&sys_time.struct_data);

	time_ptr->tv_sec  = ((long) ((sys_time.scalar_data -
		SDTIF_WIN32_FILETIME_EPOCH_BIAS) / 10000000i64));
	time_ptr->tv_usec = ((long) ((sys_time.scalar_data / 10i64) % 1000000i64));
#elif _POSIX_TIMERS
	struct timespec tmp_timespec;

	clock_gettime(CLOCK_REALTIME, &tmp_timespec);

	time_ptr->tv_sec  = tmp_timespec.tv_sec;
	time_ptr->tv_usec = tmp_timespec.tv_nsec / 1000L;
#else
	gettimeofday(time_ptr, NULL);
#endif /* #ifdef __MSDOS__ */

	return(time_ptr);
}
/*	***********************************************************************	*/
#ifdef __MWERKS__
# pragma ANSI_strict reset
#endif /* #ifdef __MWERKS__ */

#ifdef __MWERKS__
# pragma ANSI_strict off
#endif /* #ifdef __MWERKS__ */
/*	***********************************************************************	*/
#ifndef NARGS
struct timespec *SDTIF_GetTimeNSecs(struct timespec *time_ptr)
#else
struct timespec *SDTIF_GetTimeNSecs(time_ptr)
struct timespec *time_ptr;
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	struct timeb struct_timeb;

	ftime(&struct_timeb);
	time_ptr->tv_sec  = struct_timeb.time;
	time_ptr->tv_nsec = ((long) struct_timeb.millitm) * 1000000L;
#elif _Windows
	SDTIF_WIN32_FILETIME_64 sys_time;

	GetSystemTimeAsFileTime(&sys_time.struct_data);

	time_ptr->tv_sec  = ((long) ((sys_time.scalar_data -
		SDTIF_WIN32_FILETIME_EPOCH_BIAS) / 10000000i64));
	time_ptr->tv_nsec = ((long) ((sys_time.scalar_data * 100i64) %
		1000000000i64));
#elif _POSIX_TIMERS
	clock_gettime(CLOCK_REALTIME, time_ptr);
#else
	struct timeval tmp_timeval;

	SDTIF_GetTimeUSecs(&tmp_timeval);

	time_ptr->tv_sec  = tmp_timeval.tv_sec;
	time_ptr->tv_nsec = tmp_timeval.tv_usec * 1000L;
#endif /* #ifdef __MSDOS__ */

	return(time_ptr);
}
/*	***********************************************************************	*/
#ifdef __MWERKS__
# pragma ANSI_strict reset
#endif /* #ifdef __MWERKS__ */

#ifdef TEST_MAIN

#include <stdio.h>

#include <strfuncs.h>

#ifdef __MSDOS__
#include <dos.h>
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (void));

int main()
{
	struct timespec tmp_timespec;
	struct timeval  tmp_timeval;
	struct tm       tmp_tm_1;
	struct tm       tmp_tm_2;
	char            buffer_1[512];
	char            buffer_2[512];

#if _Windows
	unsigned int            count_1;
	SDTIF_WIN32_FILETIME_64 sys_time;
	SDTIF_WIN32_FILETIME_64 old_sys_time;
#endif /* #if _Windows */

	fprintf(stderr, "Test routine for 'SDTIF_GetTimeLocal()'\n");
	fprintf(stderr, "                 'SDTIF_GetTimeGMT()'\n");
	fprintf(stderr, "                 'SDTIF_GetTimeUSecs()'\n");
	fprintf(stderr, "                 'SDTIF_GetTimeNSecs()'\n");
	fprintf(stderr, "                 --------------------\n\n");

	SDTIF_GetTimeNSecs(&tmp_timespec);

	tmp_timeval.tv_sec  = tmp_timespec.tv_sec;
	tmp_timeval.tv_usec = (tmp_timespec.tv_nsec / 1000L) % 1000000L;

	SDTIF_GetTimeLocal(&tmp_timeval.tv_sec, &tmp_tm_1);
	SDTIF_GetTimeGMT(&tmp_timeval.tv_sec, &tmp_tm_2);
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("With the current time:\n");
	printf("---- --- ------- -----\n");
	printf("Result for 'SDTIF_Format_tm()'            : %s\n",
		SDTIF_Format_tm(&tmp_tm_1, buffer_1));
	printf("Result for 'SDTIF_Format_tm_GMT()'        : %s\n",
		SDTIF_Format_tm_GMT(&tmp_tm_2, buffer_2));
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("\n");

	SDTIF_Format_timeval_GMT(&tmp_timeval, buffer_1);
	SDTIF_Format_timespec_GMT(&tmp_timespec, buffer_2);

	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("With the current time:\n");
	printf("---- --- ------- -----\n");
	printf("Result for 'SDTIF_Format_timeval_GMT()'   : %s\n", buffer_1);
	printf("Result for 'SDTIF_Format_timespec_GMT()'  : %s\n", buffer_2);
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("\n");

#ifdef _Windows
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("Windows Date/Time Granularity Information:\n");
	printf("------- --------- ----------- ------------\n");
	for (count_1 = 0; count_1 < 4; count_1++) {
		printf("[%04u]:SDTIF_WIN32_FILETIME_EPOCH_BIAS: %I64u\n", count_1,
			SDTIF_WIN32_FILETIME_EPOCH_BIAS);
		GetSystemTimeAsFileTime(&sys_time.struct_data);
		printf("[%04u]:FILETIME Scalar Equivalent     : %I64u\n", count_1,
			sys_time.scalar_data);
		printf("[%04u]:FILETIME.dwLowDateTime         : %lu\n", count_1,
			sys_time.struct_data.dwLowDateTime);
		printf("[%04u]:FILETIME.dwHighDateTime        : %lu\n", count_1,
			sys_time.struct_data.dwHighDateTime);
		tmp_timespec.tv_sec  = ((long) ((sys_time.scalar_data -
			SDTIF_WIN32_FILETIME_EPOCH_BIAS) / 10000000i64));
		tmp_timespec.tv_nsec = ((long) ((sys_time.scalar_data * 100i64) %
			1000000000i64));
		printf("[%04u]:Old TIMESPEC Calculation       : %s\n", count_1,
			SDTIF_Format_timespec(&tmp_timespec, buffer_1));
		tmp_timeval.tv_sec  = ((long) ((sys_time.scalar_data -
			SDTIF_WIN32_FILETIME_EPOCH_BIAS) / 10000000i64));
		tmp_timeval.tv_usec = ((long) ((sys_time.scalar_data / 10i64) %
			1000000i64));
		printf("[%04u]:Old TIMEVAL Calculation        : %s\n", count_1,
			SDTIF_Format_timeval(&tmp_timeval, buffer_1));
		if (count_1 && memcmp(&sys_time, &old_sys_time, sizeof(sys_time))) {
			printf("[DIFF]:FILETIME Scalar Equivalent     : %12.8f\n",
				((double) ((signed __int64) sys_time.scalar_data)) -
				((double) ((signed __int64) old_sys_time.scalar_data)));
			printf("[DIFF]:FILETIME.dwLowDateTime         : %12.8f\n",
				((double) sys_time.struct_data.dwLowDateTime) -
				((double) old_sys_time.struct_data.dwLowDateTime));
			printf("[DIFF]:FILETIME.dwHighDateTime        : %12.8f\n",
				((double) sys_time.struct_data.dwHighDateTime) -
				((double) old_sys_time.struct_data.dwHighDateTime));
		}
		old_sys_time = sys_time;
		STR_EMIT_CharLine('-', 77, NULL, NULL);
	}
/*
	tmp_timespec.tv_sec  = ((long) ((sys_time.scalar_data -
		SDTIF_WIN32_FILETIME_EPOCH_BIAS) / 10000000i64));
	tmp_timespec.tv_nsec = ((long) ((sys_time.scalar_data * 100i64) %
		1000000000i64));
	STR_EMIT_CharLine('=', 77, NULL, NULL);
*/
#endif /* #if _Windows */

	return(0);
}

#endif /* #ifndef TEST_MAIN */

