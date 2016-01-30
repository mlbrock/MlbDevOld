/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Source Module								*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets a variety of time measurement values.

	Revision History	:	1991-10-31 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <sdtif.h>

#include "genfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
#ifndef NARGS
struct tm *GEN_GetTimeLocal(const time_t *in_time, struct tm *time_buffer)
#else
struct tm *GEN_GetTimeLocal(in_time, time_buffer)
const time_t *in_time;
struct tm    *time_buffer;
#endif /* #ifndef NARGS */
{
	return(SDTIF_GetTimeLocal(in_time, time_buffer));
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
struct tm *GEN_GetTimeGMT(const time_t *in_time, struct tm *time_buffer)
#else
struct tm *GEN_GetTimeGMT(in_time, time_buffer)
const time_t *in_time;
struct tm    *time_buffer;
#endif /* #ifndef NARGS */
{
	return(SDTIF_GetTimeGMT(in_time, time_buffer));
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int GEN_gettimeofday(struct timeval *time_ptr, struct timezone *timezone_ptr)
#else
int GEN_gettimeofday(time_ptr, timezone_ptr)
struct timeval  *time_ptr;
struct timezone *timezone_ptr;
#endif /* #ifndef NARGS */
{
	return(SDTIF_gettimeofday(time_ptr, timezone_ptr));
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
struct timeval *GEN_GetTimeUSecs(struct timeval *time_ptr)
#else
struct timeval *GEN_GetTimeUSecs(time_ptr)
struct timeval *time_ptr;
#endif /* #ifndef NARGS */
{
	return(SDTIF_GetTimeUSecs(time_ptr));
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
struct timespec *GEN_GetTimeNSecs(struct timespec *time_ptr)
#else
struct timespec *GEN_GetTimeNSecs(time_ptr)
struct timespec *time_ptr;
#endif /* #ifndef NARGS */
{
	return(SDTIF_GetTimeNSecs(time_ptr));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

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

	fprintf(stderr, "Test routine for 'GEN_GetTimeLocal()'\n");
	fprintf(stderr, "                 'GEN_GetTimeGMT()'\n");
	fprintf(stderr, "                 'GEN_GetTimeUSecs()'\n");
	fprintf(stderr, "                 'GEN_GetTimeNSecs()'\n");
	fprintf(stderr, "                 --------------------\n\n");

	GEN_GetTimeNSecs(&tmp_timespec);

	tmp_timeval.tv_sec  = tmp_timespec.tv_sec;
	tmp_timeval.tv_usec = (tmp_timespec.tv_nsec / 1000L) % 1000000L;

	GEN_GetTimeLocal(&tmp_timeval.tv_sec, &tmp_tm_1);
	GEN_GetTimeGMT(&tmp_timeval.tv_sec, &tmp_tm_2);
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("With the current time:\n");
	printf("---- --- ------- -----\n");
	printf("Result for 'GEN_Format_tm()'            : %s\n",
		GEN_Format_tm(&tmp_tm_1, buffer_1));
	printf("Result for 'GEN_Format_tm_GMT()'        : %s\n",
		GEN_Format_tm_GMT(&tmp_tm_2, buffer_2));
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("\n");

	GEN_Format_timeval_GMT(&tmp_timeval, buffer_1);
	GEN_Format_timespec_GMT(&tmp_timespec, buffer_2);

	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("With the current time:\n");
	printf("---- --- ------- -----\n");
	printf("Result for 'GEN_Format_timeval_GMT()'   : %s\n", buffer_1);
	printf("Result for 'GEN_Format_timespec_GMT()'  : %s\n", buffer_2);
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	printf("\n");

	return(0);
}

#endif /* #ifndef TEST_MAIN */

