/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library Header File										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	This is the include file for the 'DATFUNCS' library.

	Revision History	:	1989-11-08 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DATFUNCS_H__h

#define h__DATFUNCS_H__h	1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <sdtif.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Some basic manifest constants . . .												*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	BASE NAME   :  DATFUNCS Truth Codes

	NAME        :  DATFUNCS Truth Codes

	DESCRIPTION :  Manifest constants used within DATFUNCS to specify the truth
						or falsity of expressions.

						(.) ''DATFUNCS_TRUE''

						(.) ''DATFUNCS_FALSE''

	NOTES       :  The manifest constant ''DATFUNCS_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''DATFUNCS_FALSE'' should be defined as zero (''0'').

	AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:  DATFUNCS_TRUE
						DATFUNCS_FALSE
						DATFUNCS Truth Codes:DATFUNCS_TRUE
						DATFUNCS Truth Codes:DATFUNCS_FALSE
						DATFUNCS Manifest Constants:DATFUNCS_TRUE
						DATFUNCS Manifest Constants:DATFUNCS_FALSE
						DATFUNCS Defines:DATFUNCS_TRUE
						DATFUNCS Defines:DATFUNCS_FALSE
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:  DATFUNCS Truth Codes
						DATFUNCS Truth Code
						DATFUNCS truth codes
						DATFUNCS truth code
						DATFUNCS_TRUE
						DATFUNCS_FALSE

	PUBLISH NAME:	DATFUNCS Truth Codes
						DATFUNCS_TRUE
						DATFUNCS_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DATFUNCS_TRUE							1
#define DATFUNCS_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	BASE NAME   :	DATFUNCS Return Codes

	NAME        :  DATFUNCS Return Codes

	DESCRIPTION :  The DATFUNCS return codes have the following meanings:

						(.) ''DATFUNCS_SUCCESS'' means that the function invoked
						completed without error. ''DATFUNCS_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''DATFUNCS_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other DATFUNCS error codes.

						(.) ''DATFUNCS_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''DATFUNCS_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''DATFUNCS_SYSTEM_FAILURE'' indicates that the function invoked
						encountered a failure of a standard library function or a
						system call.

	AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:  DATFUNCS_SUCCESS
						DATFUNCS_FAILURE
						DATFUNCS_BAD_ARGS_FAILURE
						DATFUNCS_MEMORY_FAILURE
						DATFUNCS_SYSTEM_FAILURE
						DATFUNCS Return Codes:DATFUNCS_SUCCESS
						DATFUNCS Return Codes:DATFUNCS_FAILURE
						DATFUNCS Return Codes:DATFUNCS_BAD_ARGS_FAILURE
						DATFUNCS Return Codes:DATFUNCS_MEMORY_FAILURE
						DATFUNCS Return Codes:DATFUNCS_SYSTEM_FAILURE
						DATFUNCS Manifest Constants:DATFUNCS_SUCCESS
						DATFUNCS Manifest Constants:DATFUNCS_FAILURE
						DATFUNCS Manifest Constants:DATFUNCS_BAD_ARGS_FAILURE
						DATFUNCS Manifest Constants:DATFUNCS_MEMORY_FAILURE
						DATFUNCS Manifest Constants:DATFUNCS_SYSTEM_FAILURE
						DATFUNCS Defines:DATFUNCS_SUCCESS
						DATFUNCS Defines:DATFUNCS_FAILURE
						DATFUNCS Defines:DATFUNCS_BAD_ARGS_FAILURE
						DATFUNCS Defines:DATFUNCS_MEMORY_FAILURE
						DATFUNCS Defines:DATFUNCS_SYSTEM_FAILURE
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:  DATFUNCS_SUCCESS
						DATFUNCS_FAILURE
						DATFUNCS_BAD_ARGS_FAILURE
						DATFUNCS_MEMORY_FAILURE
						DATFUNCS_SYSTEM_FAILURE
						DATFUNCS Return Codes
						DATFUNCS Return Code
						DATFUNCS return codes
						DATFUNCS return code
						DATFUNCS Status Codes
						DATFUNCS Status Code
						DATFUNCS status codes
						DATFUNCS status code
						DATFUNCS Error Codes
						DATFUNCS Error Code
						DATFUNCS error codes
						DATFUNCS error code

	PUBLISH NAME:	DATFUNCS Return Codes
						DATFUNCS return codes
						DATFUNCS_SUCCESS
						DATFUNCS_FAILURE
						DATFUNCS_BAD_ARGS_FAILURE
						DATFUNCS_MEMORY_FAILURE
						DATFUNCS_SYSTEM_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DATFUNCS_SUCCESS						 0
#define DATFUNCS_FAILURE						-1
#define DATFUNCS_BAD_ARGS_FAILURE			-2
#define DATFUNCS_MEMORY_FAILURE				-3
#define DATFUNCS_SYSTEM_FAILURE				-4
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME        :  DATFUNCS_MAX_ERROR_TEXT

	DESCRIPTION :  The manifest constant ''DATFUNCS_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a DATFUNCS function.

	CAVEATS     :  DATFUNCS error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''DATFUNCS_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to DATFUNCS functions can lead to overwriting of the
						heap or the stack.

	AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1989 - 2015 Michael L. Brock

	OUTPUT INDEX:  DATFUNCS_MAX_ERROR_TEXT
						DATFUNCS Manifest Constants:DATFUNCS_MAX_ERROR_TEXT
						DATFUNCS Defines:DATFUNCS_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:	DATFUNCS_MAX_ERROR_TEXT

	PUBLISH NAME:	DATFUNCS_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DATFUNCS_MAX_ERROR_TEXT			1024
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DATFUNCS_MIN_YEAR					100
#define DATFUNCS_MAX_YEAR					9999
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DATFUNCS_MIN_JULIAN				((JULIAN) -657438L)
#define DATFUNCS_MAX_JULIAN				((JULIAN) 2958463L)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DATFUNCS_EPOCH_YEAR				1900
#define DATFUNCS_EPOCH_MONTH				1
#define DATFUNCS_EPOCH_DAY					1
#define DATFUNCS_EPOCH_DAY_OF_WEEK		1
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DATFUNCS_UNIX_EPOCH_YEAR			1970
#define DATFUNCS_UNIX_EPOCH_MONTH		1
#define DATFUNCS_UNIX_EPOCH_DAY			1
#define DATFUNCS_UNIX_EPOCH_JULIAN		((JULIAN) 25567L)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DATFUNCS_GREGORIAN_YEAR			1752
#define DATFUNCS_GREGORIAN_MONTH			9
#define DATFUNCS_GREGORIAN_MISSING		11
#define DATFUNCS_GREGORIAN_FIRST_DAY	3
#define DATFUNCS_GREGORIAN_LAST_DAY		\
	((DATFUNCS_GREGORIAN_FIRST_DAY + DATFUNCS_GREGORIAN_MISSING) - 1)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DATFUNCS_DEFAULT_JULIAN_FORMAT	"YYYY-MM-DD"
#define DATFUNCS_DEFAULT_DTIME_FORMAT	"YYYY-MM-DD HH:NN:SS.LLL"
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		These manifest constants define the date count types . . .				*/
/*	***********************************************************************	*/
#define DAY_COUNT_ACTUAL_ACTUAL		0
#define DAY_COUNT_30_360				1
#define DAY_COUNT_ACTUAL_360			2
#define DAY_COUNT_ACTUAL_365			365
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		These manifest constants define the formats used in the function		*/
/*	'jultostr()'.																				*/
/*	***********************************************************************	*/

#define DATE_SPEC_DEFAULT						0X0000

#define DATE_SPEC_SETTING						0XFFFF

#define DATE_SPEC_ORDER_MM_DD_YY				0X0000	/* 0000000000000000 */
#define DATE_SPEC_ORDER_DD_MM_YY				0X0001	/* 0000000000000001 */
#define DATE_SPEC_ORDER_YY_MM_DD				0X0002	/* 0000000000000010 */

#define DATE_SPEC_YEAR_4_DIGIT				0X0000	/* 0000000000000000 */
#define DATE_SPEC_YEAR_2_DIGIT				0X0004	/* 0000000000000100 */

#define DATE_SPEC_MONTH_ZERO_FILLED			0X0000	/* 0000000000000000 */
#define DATE_SPEC_MONTH_BLANK_FILLED		0X0008	/* 0000000000001000 */
#define DATE_SPEC_MONTH_SHORT_NAME			0X0010	/* 0000000000010000 */
#define DATE_SPEC_MONTH_LONG_NAME			0X0018	/* 0000000000011000 */

#define DATE_SPEC_DAY_ZERO_FILLED			0X0000	/* 0000000000000000 */
#define DATE_SPEC_DAY_BLANK_FILLED			0X0020	/* 0000000000100000 */

#define DATE_SPEC_SEPARATOR_SLASH			0X0000	/* 0000000000000000 */
#define DATE_SPEC_SEPARATOR_PERIOD			0X0040	/* 0000000001000000 */
#define DATE_SPEC_SEPARATOR_DASH				0X0080	/* 0000000010000000 */
#define DATE_SPEC_SEPARATOR_BLANK			0X00C0	/* 0000000011000000 */

#define DATE_SPEC_DOW_NONE						0X0000	/* 0000000000000000 */
#define DATE_SPEC_DOW_SHORT_NAME				0X0100	/* 0000000100000000 */
#define DATE_SPEC_DOW_LONG_NAME				0X0200	/* 0000001000000000 */

#define DATE_SPEC_ORDINAL_NONE				0X0000	/* 0000000000000000 */
#define DATE_SPEC_ORDINAL_ON					0X0400	/* 0000010000000000 */

#define DATE_SPEC_CASE_INITCAPS				0X0000	/* 0000000000000000 */
#define DATE_SPEC_CASE_LOWER					0X0800	/* 0000100000000000 */
#define DATE_SPEC_CASE_UPPER					0X1000	/* 0001000000000000 */

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Some ancilliary manifest constants . . .										*/
/*	***********************************************************************	*/

#define MONTHS_IN_YEAR			12

#define DAYS_IN_WEEK				 7

#define MAX_MONTH_NAME_LENGTH	20
#define MAX_DAY_NAME_LENGTH	10

#define JDATE_NAME_TYPE_SHORT	 0
#define JDATE_NAME_TYPE_LONG	 1

#define SIZE_OF_INGRES_DATE	25
#define INGRES_DATE_SEPARATOR	"-"

	/* 123456789012345678901234 */
	/* MMM DD YYYY hh:mm:ss.zzz */
#define SIZE_OF_SYBASE_DATE	24
#define SYBASE_DATE_SEPARATOR " "

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Types used in the library . . .													*/
/*	***********************************************************************	*/

typedef long JULIAN;

typedef struct {
	int year;
	int month;
	int day;
} JDATE;

typedef struct {
	long          julian_date;
	unsigned long milliseconds;
} DTIME;

typedef int DATFUNCS_LOCALE;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions in the library 'datfuncs.a' . . .	*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for version functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void  DATFUNCS_GetVersionNumber, (unsigned int *major,
	unsigned int *minor, unsigned int *release, unsigned int *build));
COMPAT_FN_DECL(char *DATFUNCS_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for the basic library functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(long           cndaycnt,
	(int));
COMPAT_FN_DECL(long           cndaymax,
	(int));
COMPAT_FN_DECL(JULIAN         dattojul,
	(const JDATE *));
COMPAT_FN_DECL(long           dc30360,
	(JULIAN, JULIAN));
COMPAT_FN_DECL(long           dcactact,
	(JULIAN, JULIAN));
COMPAT_FN_DECL(char          *downame,
	(int, char *));
COMPAT_FN_DECL(int            dayofmon,
	(JULIAN));
COMPAT_FN_DECL(JULIAN         dttojul,
	(const DTIME *in_dtime_ptr));
COMPAT_FN_DECL(JULIAN         fixed_lontojul,
	(unsigned long, int, int));
COMPAT_FN_DECL(int            fixed_ulongok,
	(unsigned long, int, int));
COMPAT_FN_DECL(int            fixed_yearok,
	(int, int, int));
COMPAT_FN_DECL(int            fixed_ymdok,
	(int, int, int, int, int));
COMPAT_FN_DECL(JULIAN         fixed_ymdtojul,
	(int, int, int, int, int));
COMPAT_FN_DECL(unsigned long  fixulong,
	(unsigned long, int, int));
COMPAT_FN_DECL(int            fixyear,
	(int, int, int));
COMPAT_FN_DECL(JULIAN         get0101,
	(JULIAN));
COMPAT_FN_DECL(JULIAN         get1231,
	(JULIAN));
COMPAT_FN_DECL(int            getcentury,
	(JULIAN));
COMPAT_FN_DECL(int            getday,
	(JULIAN));
COMPAT_FN_DECL(int            getdow,
	(JULIAN));
COMPAT_FN_DECL(int            gethour,
	(unsigned long));
COMPAT_FN_DECL(int            gethour12,
	(unsigned long));
COMPAT_FN_DECL(int            gethour24,
	(unsigned long));
COMPAT_FN_DECL(int            gethundredthsecond,
	(unsigned long));
COMPAT_FN_DECL(int            getjspec,
	(void));
COMPAT_FN_DECL(int            getmillisecond,
	(unsigned long));
COMPAT_FN_DECL(int            getminute,
	(unsigned long));
COMPAT_FN_DECL(char          *getmname,
	(int, char *, int));
COMPAT_FN_DECL(int            getmnumb,
	(int));
COMPAT_FN_DECL(int            getmonth,
	(JULIAN));
COMPAT_FN_DECL(int            getqtr,
	(JULIAN));
COMPAT_FN_DECL(int            getsecond,
	(unsigned long));
COMPAT_FN_DECL(int            gettenthsecond,
	(unsigned long));
COMPAT_FN_DECL(int            getweek,
	(JULIAN));
COMPAT_FN_DECL(int            getyear,
	(JULIAN));
COMPAT_FN_DECL(int            hourok,
	(int));
COMPAT_FN_DECL(JULIAN         ingtojul,
	(char *));
COMPAT_FN_DECL(int            isleapyr,
	(int));
COMPAT_FN_DECL(int            jdateok,
	(const JDATE *));
COMPAT_FN_DECL(int            julianok,
	(JULIAN));
COMPAT_FN_DECL(int            jultodat,
	(JULIAN, JDATE *));
COMPAT_FN_DECL(DTIME         *jultodt,
	(JULIAN in_julian, DTIME *out_dtime_ptr));
COMPAT_FN_DECL(char          *jultofmt,
	(JULIAN, const char *, char *));
COMPAT_FN_DECL(char          *jultoing,
	(JULIAN, char *));
COMPAT_FN_DECL(unsigned long  jultolon,
	(JULIAN));
COMPAT_FN_DECL(char          *jultostr,
	(JULIAN, char *));
COMPAT_FN_DECL(char          *jultosyb,
	(JULIAN, char *));
COMPAT_FN_DECL(int            jultoymd,
	(JULIAN in_julian, int *out_year_ptr, int *out_month_ptr,
	int *out_day_ptr));
COMPAT_FN_DECL(JDATE         *lontodat,
	(unsigned long, JDATE *));
COMPAT_FN_DECL(JULIAN         lontojul,
	(unsigned long));
COMPAT_FN_DECL(int            millisecondok,
	(int));
COMPAT_FN_DECL(int            minuteok,
	(int));
COMPAT_FN_DECL(int            mndaycnt,
	(int, int));
COMPAT_FN_DECL(int            mndaymax,
	(int, int));
COMPAT_FN_DECL(JULIAN         mnend,
	(int, int));
COMPAT_FN_DECL(JULIAN         mnstart,
	(int, int));
COMPAT_FN_DECL(int            monthok,
	(int));
COMPAT_FN_DECL(JULIAN         nowtojul,
	(void));
COMPAT_FN_DECL(JULIAN         nowtojul_local,
	(void));
COMPAT_FN_DECL(JULIAN         qtrend,
	(int, int));
COMPAT_FN_DECL(JULIAN         qtrstart,
	(int, int));
COMPAT_FN_DECL(int            secondok,
	(int));
COMPAT_FN_DECL(int            setjspec,
	(int));
COMPAT_FN_DECL(unsigned long  ulongnow,
	(void));
COMPAT_FN_DECL(unsigned long  ulongnow_local,
	(void));
COMPAT_FN_DECL(int            ulongok,
	(unsigned long));
COMPAT_FN_DECL(JULIAN         wkend,
	(int, int));
COMPAT_FN_DECL(JULIAN         wkstart,
	(int, int));
COMPAT_FN_DECL(int            yearok,
	(int));
COMPAT_FN_DECL(int            ymdok,
	(int, int, int));
COMPAT_FN_DECL(JULIAN         ymdtojul,
	(int in_year, int in_month, int in_day));
COMPAT_FN_DECL(int            yrdaycnt,
	(int));
COMPAT_FN_DECL(int            yrdaymax,
	(int));
COMPAT_FN_DECL(JULIAN         yrend,
	(int));
COMPAT_FN_DECL(JULIAN         yrstart,
	(int));

COMPAT_FN_DECL(JULIAN jul_GMTToLocal,
	(JULIAN in_julian));
COMPAT_FN_DECL(JULIAN jul_AdjustHours,
	(JULIAN in_julian, long adj_hours));
COMPAT_FN_DECL(JULIAN jul_AdjustMinutes,
	(JULIAN in_julian, long adj_minutes));
COMPAT_FN_DECL(JULIAN jul_AdjustSeconds,
	(JULIAN in_julian, long adj_seconds));
COMPAT_FN_DECL(JULIAN jul_AdjustMilliseconds,
	(JULIAN in_julian, long adj_milliseconds));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for the advanced library functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int    DTIME_Ok,
	(const DTIME *dtime_ptr));
COMPAT_FN_DECL(DTIME *DTIME_NowGMT,
	(DTIME *));
COMPAT_FN_DECL(DTIME *DTIME_NowUTC,
	(DTIME *));
COMPAT_FN_DECL(DTIME *DTIME_NowLocal,
	(DTIME *in_dtime_ptr));
COMPAT_FN_DECL(long   DTIME_GetGMTToLocalSeconds,
	(const DTIME *in_dtime_ptr));
COMPAT_FN_DECL(DTIME *DTIME_GMTToLocal,
	(DTIME *in_dtime_ptr));
COMPAT_FN_DECL(DTIME *DTIME_LocalToGMT,
	(DTIME *in_dtime_ptr));
COMPAT_FN_DECL(DTIME *DTIME_AdjustHours,
	(DTIME *in_dtime_ptr, long adj_hours));
COMPAT_FN_DECL(DTIME *DTIME_AdjustMinutes,
	(DTIME *in_dtime_ptr, long adj_minutes));
COMPAT_FN_DECL(DTIME *DTIME_AdjustSeconds,
	(DTIME *in_dtime_ptr, long adj_seconds));
COMPAT_FN_DECL(DTIME *DTIME_AdjustMilliseconds,
	(DTIME *in_dtime_ptr, long adj_milliseconds));
COMPAT_FN_DECL(DTIME *DTIME_GetAdjustedMilliseconds,
	(const DTIME *in_dtime_ptr,
	long adj_milliseconds, DTIME *out_dtime_ptr));
COMPAT_FN_DECL(char  *DTIME_FormatDate,
	(const DTIME *in_date, const char *format_string,
	char *out_string));

COMPAT_FN_DECL(int DTIME_YYYYMMDDhhmmsslllToDate,
	(int in_year, int in_month, int in_day,
	int in_hour, int in_minute, int in_second, int in_millisecond,
	DTIME *dtime_ptr, char *error_text));

COMPAT_FN_DECL(DTIME *DTIME_timevalToDate,
	(const struct timeval *, DTIME *));
 
COMPAT_FN_DECL(int DTIME_Compare,
	(const DTIME *date_ptr_1, const DTIME *date_ptr_2));
COMPAT_FN_DECL(int DTIME_STR_Compare,
	(void *control_ptr, const DTIME *date_ptr_1,
	const DTIME *date_ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		String checking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DATFUNCS_CheckCanonicalTimeVal,
	(const char *in_string, char *error_text));
COMPAT_FN_DECL(int DATFUNCS_CheckCanonicalTimeSpec,
	(const char *in_string, char *error_text));
COMPAT_FN_DECL(int DATFUNCS_CheckCanonicalDate,
	(const char *in_string, char *error_text));
COMPAT_FN_DECL(int DATFUNCS_CheckCanonicalTime,
	(const char *in_string, char *error_text));
COMPAT_FN_DECL(int DATFUNCS_CheckCanonicalTimeFrac6,
	(const char *in_string, char *error_text));
COMPAT_FN_DECL(int DATFUNCS_CheckCanonicalTimeFrac9,
	(const char *in_string, char *error_text));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DATFUNCS_H__h */

