/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	System Date/Time Interface Facility (SDTIF) Library Include File			*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the SDTIF library.

	Revision History	:	1985-10-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1985 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__SDTIF_H__h

# define h__SDTIF_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#include <limits.h>
#include <time.h>

#ifndef __MSDOS__
# ifndef _Windows
#  include <sys/time.h>
# endif /* #ifndef _Windows */
#endif /* #ifndef __MSDOS__ */

#ifdef _Windows
# ifdef _MSC_VER
#  pragma warning(push)
#  pragma warning(disable:4820)
#  if _MSC_VER >= 1300
#   pragma warning(disable:4255 4668)
#   include <windows.h>
#   pragma warning(default:4255 4668)
#  elif _MSC_VER >= 1200
#   pragma warning(disable:4115)
#   include <windows.h>
#   pragma warning(default:4115)
#  else
#   pragma warning(disable:4115 4201 4214 4514)
#   include <windows.h>
#   pragma warning(default:4115 4201 4214)
# 	endif /* #  if _MSC_VER >= 1200 */
#  pragma warning(pop)
# else
#  include <windows.h>
# endif /* # ifdef _MSC_VER */
#endif /* #ifdef _Windows */

#include <mbcompat.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	BASE NAME   :  SDTIF Truth Codes

	NAME        :  SDTIF Truth Codes

	DESCRIPTION :  Manifest constants used within SDTIF to specify the truth
						or falsity of expressions.

						(.) ''SDTIF_TRUE''

						(.) ''SDTIF_FALSE''

	NOTES       :  The manifest constant ''SDTIF_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''SDTIF_FALSE'' should be defined as zero (''0'').

	AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1985 - 2018 Michael L. Brock

	OUTPUT INDEX:  SDTIF_TRUE
						SDTIF_FALSE
						SDTIF Truth Codes:SDTIF_TRUE
						SDTIF Truth Codes:SDTIF_FALSE
						SDTIF Manifest Constants:SDTIF_TRUE
						SDTIF Manifest Constants:SDTIF_FALSE
						SDTIF Defines:SDTIF_TRUE
						SDTIF Defines:SDTIF_FALSE
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:  SDTIF Truth Codes
						SDTIF Truth Code
						SDTIF truth codes
						SDTIF truth code
						SDTIF_TRUE
						SDTIF_FALSE

	PUBLISH NAME:	SDTIF Truth Codes
						SDTIF_TRUE
						SDTIF_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define SDTIF_TRUE							1
#define SDTIF_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	BASE NAME   :	SDTIF Return Codes

	NAME        :  SDTIF Return Codes

	DESCRIPTION :  The SDTIF return codes have the following meanings:

						(.) ''SDTIF_SUCCESS'' means that the function invoked
						completed without error. ''SDTIF_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''SDTIF_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other SDTIF error codes.

						(.) ''SDTIF_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''SDTIF_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''SDTIF_SYSTEM_FAILURE'' indicates that the function invoked
						encountered a failure of a standard library function or a
						system call.

						(.) ''SDTIF_LOCK_ACQ_FAILURE'' indicates that a lock
						could not be acquired on a resource.

	AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1985 - 2018 Michael L. Brock

	OUTPUT INDEX:  SDTIF_SUCCESS
						SDTIF_FAILURE
						SDTIF_BAD_ARGS_FAILURE
						SDTIF_MEMORY_FAILURE
						SDTIF_SYSTEM_FAILURE
						SDTIF_LOCK_ACQ_FAILURE
						SDTIF Return Codes:SDTIF_SUCCESS
						SDTIF Return Codes:SDTIF_FAILURE
						SDTIF Return Codes:SDTIF_BAD_ARGS_FAILURE
						SDTIF Return Codes:SDTIF_MEMORY_FAILURE
						SDTIF Return Codes:SDTIF_SYSTEM_FAILURE
						SDTIF Return Codes:SDTIF_LOCK_ACQ_FAILURE
						SDTIF Manifest Constants:SDTIF_SUCCESS
						SDTIF Manifest Constants:SDTIF_FAILURE
						SDTIF Manifest Constants:SDTIF_BAD_ARGS_FAILURE
						SDTIF Manifest Constants:SDTIF_MEMORY_FAILURE
						SDTIF Manifest Constants:SDTIF_SYSTEM_FAILURE
						SDTIF Manifest Constants:SDTIF_LOCK_ACQ_FAILURE
						SDTIF Defines:SDTIF_SUCCESS
						SDTIF Defines:SDTIF_FAILURE
						SDTIF Defines:SDTIF_BAD_ARGS_FAILURE
						SDTIF Defines:SDTIF_MEMORY_FAILURE
						SDTIF Defines:SDTIF_SYSTEM_FAILURE
						SDTIF Defines:SDTIF_LOCK_ACQ_FAILURE
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:  SDTIF_SUCCESS
						SDTIF_FAILURE
						SDTIF_BAD_ARGS_FAILURE
						SDTIF_MEMORY_FAILURE
						SDTIF_SYSTEM_FAILURE
						SDTIF_LOCK_ACQ_FAILURE
						SDTIF Return Codes
						SDTIF Return Code
						SDTIF return codes
						SDTIF return code
						SDTIF Status Codes
						SDTIF Status Code
						SDTIF status codes
						SDTIF status code
						SDTIF Error Codes
						SDTIF Error Code
						SDTIF error codes
						SDTIF error code

	PUBLISH NAME:	SDTIF Return Codes
						SDTIF return codes
						SDTIF_SUCCESS
						SDTIF_FAILURE
						SDTIF_BAD_ARGS_FAILURE
						SDTIF_MEMORY_FAILURE
						SDTIF_SYSTEM_FAILURE
						SDTIF_LOCK_ACQ_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define SDTIF_SUCCESS						 0
#define SDTIF_FAILURE						-1
#define SDTIF_BAD_ARGS_FAILURE			-2
#define SDTIF_MEMORY_FAILURE				-3
#define SDTIF_SYSTEM_FAILURE				-4
#define SDTIF_LOCK_ACQ_FAILURE			-5
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME        :  SDTIF_MAX_ERROR_TEXT

	DESCRIPTION :  The manifest constant ''SDTIF_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a SDTIF function.

	CAVEATS     :  SDTIF error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''SDTIF_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to SDTIF functions can lead to overwriting of the
						heap or the stack.

	AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1985 - 2018 Michael L. Brock

	OUTPUT INDEX:  SDTIF_MAX_ERROR_TEXT
						SDTIF Manifest Constants:SDTIF_MAX_ERROR_TEXT
						SDTIF Defines:SDTIF_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:	SDTIF_MAX_ERROR_TEXT

	PUBLISH NAME:	SDTIF_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define SDTIF_MAX_ERROR_TEXT				1024
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define SDTIF_MAP_TRUTH(code)         	((code)  ? SDTIF_TRUE : SDTIF_FALSE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		An approximation of 'gettimeofday()' for MS-DOS and Windows . . .		*/
/*	***********************************************************************	*/
#ifdef __MSDOS__
# ifndef SDTIF_struct_timeval
#  define SDTIF_struct_timeval
	struct timeval { long tv_sec; long tv_usec; };
# endif /* # ifndef SDTIF_struct_timeval */
# ifndef SDTIF_struct_timespec
#  define SDTIF_struct_timespec
	struct timespec { time_t tv_sec; long tv_nsec; };
# endif /* # ifndef SDTIF_struct_timespec */
# ifndef SDTIF_struct_timezone
#  define SDTIF_struct_timezone
	struct timezone { char data; };
# endif /* # ifndef SDTIF_struct_timezone */
# ifndef gettimeofday
#  define gettimeofday(timeval_ptr, time_zone_ptr)	\
		SDTIF_gettimeofday(timeval_ptr, time_zone_ptr)
# endif /* #ifndef gettimeofday */
#elif _Windows
# ifndef SDTIF_struct_timespec
#  define SDTIF_struct_timespec
#  pragma warning(push)
#  pragma warning(disable:4820)
	struct timespec { time_t tv_sec; long tv_nsec; };
#  pragma warning(pop)
# endif /* # ifndef SDTIF_struct_timespec */
# ifndef SDTIF_struct_timezone
#  define SDTIF_struct_timezone
	struct timezone { char data; };
# endif /* # ifndef SDTIF_struct_timezone */
# ifndef gettimeofday
#  define gettimeofday(timeval_ptr, time_zone_ptr)	\
		SDTIF_gettimeofday(timeval_ptr, time_zone_ptr)
# endif /* #ifndef gettimeofday */
#else
#endif /* #ifndef __MSDOS__ */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#if _Windows
typedef union {
	FILETIME         struct_data;
	unsigned __int64 scalar_data;
} SDTIF_WIN32_FILETIME_64;
# define SDTIF_WIN32_FILETIME_EPOCH_BIAS	116444736000000000i64
#endif /* #if _Windows */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	NAME			:	SDTIF_TVAL

	DESCRIPTION	:	The ''SDTIF_TVAL'' structure is designed to support
						application operational statistics gathering.

						The ''SDTIF_TVAL'' structure is declared as follows:

{|@|}typedef struct {
	int            maximum_stat_flag;
	unsigned long  sample_count;
	unsigned long  last_count;
	struct timeval last_start;
	struct timeval last_end;
	struct timeval last_interval;
	struct timeval tmp_last_start;
	unsigned long  total_count;
	struct timeval total_interval;
} SDTIF_TVAL;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``maximum_stat_flag`` is an ''int'' which indicates
						whether the ''SDTIF_TVAL'' has stored the maximum
						number of statistics gathering passes, in which case
						it will be set to the value of the manifest constant
						''SDTIF_TRUE''. Otherwise, it will be set equal to the
						manifest constant ''SDTIF_FALSE''.

						(-) ``maximum_stat_flag`` will be set to ''SDTIF_TRUE''
						by the logic in the function ``SDTIF_TVAL_EndTimeSpecified``
						upon detection of any of the following conditions:

						(..) The ``sample_count`` member is equal to its maximum
						value of ''ULONG_MAX''.

						(..) An attempt to add the ``last_count`` member to the
						``total_count`` member results in a value greater than
						''ULONG_MAX''.

						(..) An attempt to add the ``last_interval`` member to the
						``total_interval`` member results in a number of seconds
						greater than ''ULONG_MAX''.

						(.) ``sample_count`` is an ''unsigned long'' in which is
						stored the number of statistics samples represented by
						the ''SDTIF_TVAL'' structure.

						(.) ``last_count`` is an ''unsigned long'' in which is
						stored the number of items processed in the last statistics
						gathering pass.

						(.) ``last_start`` is a ''struct timeval'' in which is
						stored the start time of the last statistics gathering pass.

						(.) ``last_end`` is a ''struct timeval'' in which is stored
						the end time of the last statistics gathering pass.

						(.) ``last_interval`` is a ''struct timeval'' in which is
						stored the total time taken by the last statistics gathering
						pass. That is, ``last_interval`` is equal to ``end_time``
						minus ``start_time``.

						(.) ``tmp_last_start`` is a ''struct timeval'' in which the
						start time of the current (last) statistics gathering pass
						is stored temporarily until the end of the statistics
						gathering pass.

						(.) ``total_count`` is an ''unsigned long'' in which is
						stored the total number of items processed in all
						statistics gathering passes.

						(.) ``total_interval`` is a ''struct timeval'' in which is
						stored the total time taken by all statistics gathering
						passes.

	NOTES			:	It is planned to implement (eventually) a structure
						equivalent to this one which uses the Posix ''struct
						timespec''.

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	SDTIF_TVAL
						Statistics Gathering Structures:SDTIF_TVAL
						SDTIF:Structures:SDTIF_TVAL
						SDTIF:Statistics Gathering Structures:SDTIF_TVAL
						System Date/Time Interface Facility Functions:See SDTIF

	PUBLISH XREF:	SDTIF_TVAL

	PUBLISH NAME:	SDTIF_TVAL

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	int            maximum_stat_flag;
	unsigned long  sample_count;
	unsigned long  last_count;
	struct timeval last_start;
	struct timeval last_end;
	struct timeval last_interval;
	struct timeval tmp_last_start;
	unsigned long  total_count;
	struct timeval total_interval;
} SDTIF_STAT_TVAL;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
				ULONG		:	yyyy-mm-dd							=	10 + 1
				TIME_T	:	yyyy-mm-dd hh:mm:ss				=	19 + 1
				TM			:	yyyy-mm-dd hh:mm:ss				=	19 + 1
				TIMEB		:	yyyy-mm-dd hh:mm:ss.mmm			=	23 + 1
				TIMEVAL	:	yyyy-mm-dd hh:mm:ss.uuuuuu		=	26 + 1
				TIMESPEC	:	yyyy-mm-dd hh:mm:ss.nnnnnnnnn	=	29 + 1
*/
/*	***********************************************************************	*/
#define SDTIF_FMT_TIME_LEN_ULONG			10
#define SDTIF_FMT_TIME_LEN_TIME_T		19
#define SDTIF_FMT_TIME_LEN_TM				19
#define SDTIF_FMT_TIME_LEN_TIMEB			23
#define SDTIF_FMT_TIME_LEN_TIMEVAL		26
#define SDTIF_FMT_TIME_LEN_TIMESPEC		29
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
				ULONG		:	dddddddddd							=	10 + 1
				TIME_T	:	dddddddddd hh:mm:ss				=	19 + 1
				TM			:	dddddddddd hh:mm:ss				=	19 + 1
				TIMEB		:	dddddddddd hh:mm:ss.mmm			=	23 + 1
				TIMEVAL	:	dddddddddd hh:mm:ss.uuuuuu		=	26 + 1
				TIMESPEC	:	dddddddddd hh:mm:ss.nnnnnnnnn	=	29 + 1
*/
/*	***********************************************************************	*/
#define SDTIF_FMTI_TIME_LEN_ULONG		10
#define SDTIF_FMTI_TIME_LEN_TIME_T		19
#define SDTIF_FMTI_TIME_LEN_TM			19
#define SDTIF_FMTI_TIME_LEN_TIMEB		23
#define SDTIF_FMTI_TIME_LEN_TIMEVAL		26
#define SDTIF_FMTI_TIME_LEN_TIMESPEC	29
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define SDTIF_FMT_TIME_LEN_STAT_TVAL	SDTIF_FMT_TIME_LEN_TIMEVAL
#define SDTIF_FMTI_TIME_LEN_STAT_TVAL	SDTIF_FMTI_TIME_LEN_TIMEVAL
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define SDTIF_DATE_YYYY_MM_DD_LEN		10

#define SDTIF_TIME_HH_MM_SS_LEN			8

#define SDTIF_TIME_FRACTIONAL6_LEN		(SDTIF_TIME_HH_MM_SS_LEN + 1 + 6)
#define SDTIF_TIME_FRACTIONAL9_LEN		(SDTIF_TIME_HH_MM_SS_LEN + 1 + 9)
#define SDTIF_TIME_TIMEVAL_LEN			(SDTIF_TIME_HH_MM_SS_LEN + 1 + 6)
#define SDTIF_TIME_TIMESPEC_LEN			(SDTIF_TIME_HH_MM_SS_LEN + 1 + 9)

#define SDTIF_DATE_TIME_TIMEVAL_LEN		\
	(SDTIF_DATE_YYYY_MM_DD_LEN + 1 + SDTIF_TIME_TIMEVAL_LEN)
#define SDTIF_DATE_TIME_TIMESPEC_LEN	\
	(SDTIF_DATE_YYYY_MM_DD_LEN + 1 + SDTIF_TIME_TIMESPEC_LEN)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Time structure manipulation macros . . .											*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Macros used to manipulate structures of type 'time_t' . . .
		*****************************************************************	*/
#define SDTIF_TIME_T_ZERO					((time_t)       0L)
#define SDTIF_TIME_T_MIN					((time_t) LONG_MIN)
#define SDTIF_TIME_T_MAX					((time_t) LONG_MAX)

#define SDTIF_COMPARE_TIME_T(time_ptr_1, time_ptr_2)							\
	((int) (*(time_ptr_1) > *(time_ptr_2)) ?  1 :								\
			((*(time_ptr_1) < *(time_ptr_2)) ? -1 : 0))
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Macros used to manipulate structures of type 'tm' . . .
		*****************************************************************	*/
#ifdef __linux__
# define SDTIF_TM_ZERO				{	 0,  0,  0,  0,  0,   0, 0,   0,  0, 0, 0	}
# define SDTIF_TM_MIN				{	 0,  0,  0,  1,  0,   0, 0,   0,  0, 0, 0	}
# define SDTIF_TM_MAX				{	59, 59, 23, 31, 11, 138, 0, 365, -1, 0, 0	}
#else
# define SDTIF_TM_ZERO				{	 0,  0,  0,  0,  0,   0, 0,   0,  0	}
# define SDTIF_TM_MIN				{	 0,  0,  0,  1,  0,   0, 0,   0,  0	}
# define SDTIF_TM_MAX				{	59, 59, 23, 31, 11, 138, 0, 365, -1	}
#endif /* #ifdef __linux__ */

#define SDTIF_COMPARE_TM(time_ptr_1, time_ptr_2)								\
	((int) ((time_ptr_1)->tm_year > (time_ptr_2)->tm_year) ?  1 :			\
			(((time_ptr_1)->tm_year < (time_ptr_2)->tm_year) ? -1 :			\
			(((time_ptr_1)->tm_mon  > (time_ptr_2)->tm_mon)  ?  1 :			\
			(((time_ptr_1)->tm_mon  < (time_ptr_2)->tm_mon)  ? -1 :			\
			(((time_ptr_1)->tm_mday > (time_ptr_2)->tm_mday) ?  1 :			\
			(((time_ptr_1)->tm_mday < (time_ptr_2)->tm_mday) ? -1 :			\
			(((time_ptr_1)->tm_hour > (time_ptr_2)->tm_hour) ?  1 :			\
			(((time_ptr_1)->tm_hour < (time_ptr_2)->tm_hour) ? -1 :			\
			(((time_ptr_1)->tm_min  > (time_ptr_2)->tm_min)  ?  1 :			\
			(((time_ptr_1)->tm_min  < (time_ptr_2)->tm_min)  ? -1 :			\
			(((time_ptr_1)->tm_sec  > (time_ptr_2)->tm_sec)  ?  1 :			\
			(((time_ptr_1)->tm_sec  < (time_ptr_2)->tm_sec)  ? -1 : 0))))))))))))
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Macros used to manipulate structures of type 'timeval' . . .
		*****************************************************************	*/
#define SDTIF_TIMEVAL_ZERO				{        0L,	      0L	}
#define SDTIF_TIMEVAL_MIN				{  LONG_MIN,	      0L	}
#define SDTIF_TIMEVAL_MAX				{  LONG_MAX,	LONG_MAX	}

#define SDTIF_COMPARE_TIMEVAL(time_ptr_1, time_ptr_2)							\
	((int) ((time_ptr_1)->tv_sec  > (time_ptr_2)->tv_sec)  ?  1 : 			\
			(((time_ptr_1)->tv_sec  < (time_ptr_2)->tv_sec)  ? -1 : 			\
			(((time_ptr_1)->tv_usec > (time_ptr_2)->tv_usec) ?  1 : 			\
			(((time_ptr_1)->tv_usec < (time_ptr_2)->tv_usec) ? -1 : 0))))
#define SDTIF_GET_TIMEVAL_USECS_DOUBLE(time_ptr)	\
	((((double) (time_ptr)->tv_sec) * 1000000.0) +	\
	((double) ((time_ptr)->tv_usec % 1000000L)))
#define SDTIF_GET_TIMEVAL_USECS(time_ptr)				\
	((unsigned long) SDTIF_GET_TIMEVAL_USECS_DOUBLE(time_ptr))
#define SDTIF_SET_TIMEVAL(timeval_ptr, sec, usec)		\
	(((timeval_ptr) != NULL) ?									\
		((timeval_ptr)->tv_sec  = (sec),						\
		 (timeval_ptr)->tv_usec = (usec),					\
		 (timeval_ptr))     :									\
		(NULL))
#define SDTIF_SET_TIMEVAL_ZERO(timeval_ptr)				\
	SDTIF_SET_TIMEVAL((timeval_ptr), 0L, 0L)
#define SDTIF_TIMEVAL_IS_ZERO(timeval_ptr)				\
	SDTIF_MAP_TRUTH((((timeval_ptr)->tv_sec  == 0L) &&	\
						  ((timeval_ptr)->tv_usec == 0L)))
#define SDTIF_TIMEVAL_IS_NONZERO(timeval_ptr)			\
	SDTIF_MAP_TRUTH((((timeval_ptr)->tv_sec  != 0L) ||	\
						  ((timeval_ptr)->tv_usec != 0L)))
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Macros used to manipulate structures of type 'timespec' . . .
		*****************************************************************	*/
#define SDTIF_TIMESPEC_ZERO				{  ((time_t)       0L),	      0L	}
#define SDTIF_TIMESPEC_MIN					{  ((time_t) LONG_MIN),	      0L	}
#define SDTIF_TIMESPEC_MAX					{  ((time_t) LONG_MAX),	LONG_MAX	}

#define SDTIF_COMPARE_TIMESPEC(time_ptr_1, time_ptr_2)						\
	((int) ((time_ptr_1)->tv_sec  > (time_ptr_2)->tv_sec)  ?  1 :			\
			(((time_ptr_1)->tv_sec  < (time_ptr_2)->tv_sec)  ? -1 :			\
			(((time_ptr_1)->tv_nsec > (time_ptr_2)->tv_nsec) ?  1 :			\
			(((time_ptr_1)->tv_nsec < (time_ptr_2)->tv_nsec) ? -1 : 0))))
#define SDTIF_GET_TIMESPEC_NSECS_DOUBLE(time_ptr)		\
	((((double) (time_ptr)->tv_sec) * 1000000000.0) +	\
	((double) ((time_ptr)->tv_nsec % 1000000000L)))
#define SDTIF_GET_TIMESPEC_NSECS(time_ptr)				\
	((unsigned long) SDTIF_GET_TIMESPEC_NSECS_DOUBLE(time_ptr))
#define SDTIF_SET_TIMESPEC(timespec_ptr, sec, nsec)	\
	(((timespec_ptr) != NULL) ?								\
		((timespec_ptr)->tv_sec  = (sec),					\
		 (timespec_ptr)->tv_nsec = (nsec),					\
		 (timespec_ptr))     :									\
		(NULL))
#define SDTIF_SET_TIMESPEC_ZERO(timespec_ptr)			\
	SDTIF_SET_TIMESPEC((timespec_ptr), 0L, 0L)
#define SDTIF_TIMESPEC_IS_ZERO(timespec_ptr)				\
	SDTIF_MAP_TRUTH((((timespec_ptr)->tv_sec  == 0L) &&\
						  ((timespec_ptr)->tv_nsec == 0L)))
#define SDTIF_TIMESPEC_IS_NONZERO(timespec_ptr)			\
	SDTIF_MAP_TRUTH((((timespec_ptr)->tv_sec  != 0L) ||\
						  ((timespec_ptr)->tv_nsec != 0L)))
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Macros used to manipulate structures of type 'unsigned long' . . .
		*****************************************************************	*/
#define SDTIF_ULONG_ZERO					((unsigned long)       0L)
#define SDTIF_ULONG_MIN						((unsigned long) LONG_MIN)
#define SDTIF_ULONG_MAX						((unsigned long) LONG_MAX)

#define SDTIF_COMPARE_ULONG(time_ptr_1, time_ptr_2)							\
	((int) (*(time_ptr_1) > *(time_ptr_2)) ?  1 :								\
			((*(time_ptr_1) < *(time_ptr_2)) ? -1 : 0))
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Function prototypes for functions defined within 'sdtif.a' . . .			*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for version functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void  SDTIF_GetVersionNumber, (unsigned int *major,
	unsigned int *minor, unsigned int *release, unsigned int *build));
COMPAT_FN_DECL(char *SDTIF_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Thread-safe time conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(struct tm       *SDTIF_GetTimeLocal,
	(const time_t *in_time, struct tm *time_buffer));
COMPAT_FN_DECL(struct tm       *SDTIF_GetTimeGMT,
	(const time_t *in_time, struct tm *time_buffer));
COMPAT_FN_DECL(struct tm       *SDTIF_GetTime_tm,
	(struct tm *out_time));
COMPAT_FN_DECL(struct tm       *SDTIF_GetTime_tm_GMT,
	(struct tm *out_time));
COMPAT_FN_DECL(unsigned long    SDTIF_GetTime_ulong,
	(void));
COMPAT_FN_DECL(unsigned long    SDTIF_GetTime_ulong_GMT,
	(void));
COMPAT_FN_DECL(int              SDTIF_gettimeofday,
	(struct timeval *time_ptr, struct timezone *timezone_ptr));
COMPAT_FN_DECL(struct timeval  *SDTIF_GetTimeUSecs,
	(struct timeval *time_ptr));
COMPAT_FN_DECL(struct timespec *SDTIF_GetTimeNSecs,
	(struct timespec *time_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Time interval function prototypes for 'struct timeval' . . .
		*****************************************************************	*/
COMPAT_FN_DECL(struct timeval *SDTIF_GetInterval_timeval,
	(const struct timeval *start_ptr, const struct timeval *end_ptr,
	struct timeval *out_interval_ptr));
COMPAT_FN_DECL(struct timeval *SDTIF_GetABSInterval_timeval,
	(const struct timeval *start_ptr, const struct timeval *end_ptr,
	struct timeval *out_interval_ptr));
COMPAT_FN_DECL(struct timeval *SDTIF_GetPerInterval_timeval,
	(const struct timeval *in_interval_ptr, unsigned long item_count,
	struct timeval *out_interval_ptr));
COMPAT_FN_DECL(struct timeval *SDTIF_AddInterval_timeval,
	(const struct timeval *time_ptr_1, const struct timeval *time_ptr_2,
	struct timeval *out_interval_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Time interval function prototypes for 'struct timespec' . . .
		*****************************************************************	*/
COMPAT_FN_DECL(struct timespec *SDTIF_GetInterval_timespec,
	(const struct timespec *start_ptr, const struct timespec *end_ptr,
	struct timespec *out_interval_ptr));
COMPAT_FN_DECL(struct timespec *SDTIF_GetABSInterval_timespec,
	(const struct timespec *start_ptr, const struct timespec *end_ptr,
	struct timespec *out_interval_ptr));
COMPAT_FN_DECL(struct timespec *SDTIF_GetPerInterval_timespec,
	(const struct timespec *in_interval_ptr, unsigned long item_count,
	struct timespec *out_interval_ptr));
COMPAT_FN_DECL(struct timespec *SDTIF_AddInterval_timespec,
	(const struct timespec *time_ptr_1, const struct timespec *time_ptr_2,
	struct timespec *out_interval_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Time formatting function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(char *SDTIF_Format_time_t,
	(const time_t *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_Format_time_t_GMT,
	(const time_t *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_Format_tm,
	(const struct tm *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_Format_tm_GMT,
	(const struct tm *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_Format_timeval,
	(const struct timeval *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_Format_timeval_GMT,
	(const struct timeval *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_Format_timespec,
	(const struct timespec *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_Format_timespec_GMT,
	(const struct timespec *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_Format_ulong,
	(const unsigned long *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_Format_ulong_GMT,
	(const unsigned long *in_time, char *buffer));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Interval formatting function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(char *SDTIF_FormatInterval_time_t,
	(const time_t *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_FormatInterval_tm,
	(const struct tm *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_FormatInterval_timeval,
	(const struct timeval *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_FormatInterval_timespec,
	(const struct timespec *in_time, char *buffer));
COMPAT_FN_DECL(char *SDTIF_FormatInterval_ulong,
	(const unsigned long *in_time, char *buffer));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Time comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SDTIF_Compare_time_t,
	(const time_t *time_ptr_1, const time_t *time_ptr_2));
COMPAT_FN_DECL(int SDTIF_Compare_tm,
	(const struct tm *time_ptr_1, const struct tm *time_ptr_2));
COMPAT_FN_DECL(int SDTIF_Compare_timeval,
	(const struct timeval *time_ptr_1, const struct timeval *time_ptr_2));
COMPAT_FN_DECL(int SDTIF_Compare_timespec,
	(const struct timespec *time_ptr_1, const struct timespec *time_ptr_2));
COMPAT_FN_DECL(int SDTIF_Compare_ulong,
	(const unsigned long *time_ptr_1, const unsigned long *time_ptr_2));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Time comparison function prototypes for STRFUNCS . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int SDTIF_SCompare_time_t, (void *control_ptr,
	const time_t *time_ptr_1, const time_t *time_ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int SDTIF_SCompare_tm, (void *control_ptr,
	const struct tm *time_ptr_1, const struct tm *time_ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int SDTIF_SCompare_timeval, (void *control_ptr,
	const struct timeval *time_ptr_1, const struct timeval *time_ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int SDTIF_SCompare_timespec, (void *control_ptr,
	const struct timespec *time_ptr_1, const struct timespec *time_ptr_2,
	size_t data_length));
COMPAT_FN_DECL(int SDTIF_SCompare_ulong, (void *control_ptr,
	const unsigned long *time_ptr_1, const unsigned long *time_ptr_2,
	size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sleep function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void SDTIF_sleep, (unsigned int seconds));
COMPAT_FN_DECL(void SDTIF_msleep, (unsigned long milliseconds));
COMPAT_FN_DECL(void SDTIF_usleep, (unsigned long microseconds));
COMPAT_FN_DECL(void SDTIF_nsleep, (unsigned long nanoseconds));
COMPAT_FN_DECL(int  SDTIF_nanosleep, (const struct timespec *request_ptr,
	struct timespec *remaining_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		SDTIF timeval-based statisitics gathering functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_Init,
	(SDTIF_STAT_TVAL *stat_ptr));
COMPAT_FN_DECL(SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_StartTime,
	(SDTIF_STAT_TVAL *stat_ptr));
COMPAT_FN_DECL(SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_EndTime,
	(SDTIF_STAT_TVAL *stat_ptr, unsigned long item_count));
COMPAT_FN_DECL(SDTIF_STAT_TVAL *SDTIF_STAT_TVAL_EndTimeSpecified,
	(SDTIF_STAT_TVAL *stat_ptr, unsigned long item_count,
	const struct timeval *last_end));
COMPAT_FN_DECL(struct timeval  *SDTIF_STAT_TVAL_GetLastAverage,
	(const SDTIF_STAT_TVAL *stat_ptr, struct timeval *average_interval));
COMPAT_FN_DECL(struct timeval  *SDTIF_STAT_TVAL_GetTotalAverage,
	(const SDTIF_STAT_TVAL *stat_ptr, struct timeval *average_interval));
COMPAT_FN_DECL(struct timeval  *SDTIF_STAT_TVAL_GetSampleAverage,
	(const SDTIF_STAT_TVAL *stat_ptr, struct timeval *average_interval));
COMPAT_FN_DECL(char            *SDTIF_STAT_TVAL_FmtLastAverage,
	(const SDTIF_STAT_TVAL *stat_ptr, char *buffer));
COMPAT_FN_DECL(char            *SDTIF_STAT_TVAL_FmtTotalAverage,
	(const SDTIF_STAT_TVAL *stat_ptr, char *buffer));
COMPAT_FN_DECL(char            *SDTIF_STAT_TVAL_FmtSampleAverage,
	(const SDTIF_STAT_TVAL *stat_ptr, char *buffer));
COMPAT_FN_DECL(char            *SDTIF_STAT_TVAL_FmtLastInterval,
	(const SDTIF_STAT_TVAL *stat_ptr, char *buffer));
COMPAT_FN_DECL(char            *SDTIF_STAT_TVAL_FmtTotalInterval,
	(const SDTIF_STAT_TVAL *stat_ptr, char *buffer));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__SDTIF_H__h */

