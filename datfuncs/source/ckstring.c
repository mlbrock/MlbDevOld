/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DATFUNCS Date Functions Library														*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks to see if strings are valid dates/times.

	Revision History	:	1989-11-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1989 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "datfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DATFUNCS_CheckCanonicalTimeVal(const char *in_string, char *error_text)
#else
int DATFUNCS_CheckCanonicalTimeVal(in_string, error_text)
const char *in_string;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = DATFUNCS_FAILURE;
	char tmp_timeval[SDTIF_FMT_TIME_LEN_TIMEVAL + 1];
	char tmp_error_text[DATFUNCS_MAX_ERROR_TEXT];

	if (strlen(in_string) != SDTIF_FMT_TIME_LEN_TIMEVAL)
		sprintf(tmp_error_text,
			"Expected length of a 'struct timeval' string is %d.",
			SDTIF_FMT_TIME_LEN_TIMEVAL);
	else {
		strcpy(tmp_timeval, in_string);
		tmp_timeval[SDTIF_DATE_YYYY_MM_DD_LEN] = '\0';
		if (((return_code = DATFUNCS_CheckCanonicalDate(tmp_timeval,
			tmp_error_text)) == DATFUNCS_SUCCESS) == ((return_code =
			DATFUNCS_CheckCanonicalTimeFrac6(in_string +
			SDTIF_DATE_YYYY_MM_DD_LEN + 1, tmp_error_text)) == DATFUNCS_SUCCESS) &&
			(in_string[SDTIF_DATE_YYYY_MM_DD_LEN] == ' '))
			return_code = DATFUNCS_SUCCESS;
	}

	if ((return_code != DATFUNCS_SUCCESS) && (error_text != NULL))
		sprintf(error_text, "%s ('%-.500s') %s: %s",
			"Invalid 'struct timeval' string ", in_string,
			"expected format is 'yyyy-mm-dd hh:mm:ss.uuuuuu'", tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DATFUNCS_CheckCanonicalTimeSpec(const char *in_string, char *error_text)
#else
int DATFUNCS_CheckCanonicalTimeSpec(in_string, error_text)
const char *in_string;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = DATFUNCS_FAILURE;
	char tmp_timeval[SDTIF_FMT_TIME_LEN_TIMESPEC + 1];
	char tmp_error_text[DATFUNCS_MAX_ERROR_TEXT];

	if (strlen(in_string) != SDTIF_FMT_TIME_LEN_TIMESPEC)
		sprintf(tmp_error_text,
			"Expected length of a 'struct timespec' string is %d.",
			SDTIF_FMT_TIME_LEN_TIMESPEC);
	else {
		strcpy(tmp_timeval, in_string);
		tmp_timeval[SDTIF_DATE_YYYY_MM_DD_LEN] = '\0';
		if (((return_code = DATFUNCS_CheckCanonicalDate(tmp_timeval,
			tmp_error_text)) == DATFUNCS_SUCCESS) == ((return_code =
			DATFUNCS_CheckCanonicalTimeFrac9(in_string +
			SDTIF_DATE_YYYY_MM_DD_LEN + 1, tmp_error_text)) == DATFUNCS_SUCCESS) &&
			(in_string[SDTIF_DATE_YYYY_MM_DD_LEN] == ' '))
			return_code = DATFUNCS_SUCCESS;
	}

	if ((return_code != DATFUNCS_SUCCESS) && (error_text != NULL))
		sprintf(error_text, "%s ('%-.500s') %s: %s",
			"Invalid 'struct timespec' string ", in_string,
			"expected format is 'yyyy-mm-dd hh:mm:ss.nnnnnnnnn'", tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DATFUNCS_CheckCanonicalDate(const char *in_string, char *error_text)
#else
int DATFUNCS_CheckCanonicalDate(in_string, error_text)
const char *in_string;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DATFUNCS_FAILURE;

	if ((strlen(in_string) != SDTIF_DATE_YYYY_MM_DD_LEN) ||
		(idx_digit(in_string, 0) != 4) || (idx_digit(in_string + 5, 0) != 2) ||
		(idx_digit(in_string + 8, 0) != -1) ||
		(in_string[4] != '-') || (in_string[7] != '-')) {
		if (error_text != NULL)
			sprintf(error_text,
		"Invalid message date format ('%-.500s') --- expected 'yyyy-mm-dd'.",
				in_string);
	}
	else if (ymdok(atoi(in_string), atoi(in_string + 5),
		atoi(in_string + 8)) != DATFUNCS_TRUE) {
		if (error_text != NULL)
			sprintf(error_text,
				"Invalid message date ('%s') --- %s field is invalid.",
				in_string, (yearok(atoi(in_string)) != DATFUNCS_TRUE) ?
				"year" : (monthok(atoi(in_string + 5)) != DATFUNCS_TRUE) ?
				"month" : "day-of-month");
	}
	else
		return_code = DATFUNCS_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DATFUNCS_CheckCanonicalTime(const char *in_string, char *error_text)
#else
int DATFUNCS_CheckCanonicalTime(in_string, error_text)
const char *in_string;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DATFUNCS_FAILURE;

	if ((strlen(in_string) != SDTIF_TIME_HH_MM_SS_LEN) ||
		(idx_digit(in_string, 0) != 2) || (idx_digit(in_string + 3, 0) != 2) ||
		(idx_digit(in_string + 6, 0) != -1) ||
		(in_string[2] != ':') || (in_string[5] != ':')) {
		if (error_text != NULL)
			sprintf(error_text,
				"Invalid message time format ('%-.500s') --- expected '%s'.",
				in_string, "hh:mm:ss");
	}
	else if ((hourok(atoi(in_string)) != DATFUNCS_TRUE) ||
		(minuteok(atoi(in_string + 3)) != DATFUNCS_TRUE) ||
		(secondok(atoi(in_string + 6)) != DATFUNCS_TRUE)) {
		if (error_text != NULL)
			sprintf(error_text,
				"Invalid message time ('%s') --- %s field is invalid.",
				in_string, (hourok(atoi(in_string)) != DATFUNCS_TRUE) ?
				"hour" : (minuteok(atoi(in_string + 3)) != DATFUNCS_TRUE) ?
				"minute" : "second");
	}
	else
		return_code = DATFUNCS_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DATFUNCS_CheckCanonicalTimeFrac6(const char *in_string, char *error_text)
#else
int DATFUNCS_CheckCanonicalTimeFrac6(in_string, error_text)
const char *in_string;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DATFUNCS_FAILURE;

	if ((strlen(in_string) != SDTIF_TIME_TIMEVAL_LEN) ||
		(idx_digit(in_string, 0) != 2) || (idx_digit(in_string + 3, 0) != 2) ||
		(idx_digit(in_string + 6, 0) != 2) ||
		(idx_digit(in_string + 9, 0) != -1) ||
		(in_string[2] != ':') || (in_string[5] != ':') || (in_string[8] != '.')) {
		if (error_text != NULL)
			sprintf(error_text,
				"Invalid message time format ('%-.500s') --- expected '%s'.",
				in_string, "hh:mm:ss.uuuuuu");
	}
	else if ((hourok(atoi(in_string)) != DATFUNCS_TRUE) ||
		(minuteok(atoi(in_string + 3)) != DATFUNCS_TRUE) ||
		(secondok(atoi(in_string + 6)) != DATFUNCS_TRUE) ||
		(atoi(in_string + 9) > 999999)) {
		if (error_text != NULL)
			sprintf(error_text,
				"Invalid message time ('%s') --- %s field is invalid.",
				in_string, (hourok(atoi(in_string)) != DATFUNCS_TRUE) ?
				"hour" : (minuteok(atoi(in_string + 3)) != DATFUNCS_TRUE) ?
				"minute" : (secondok(atoi(in_string + 6)) != DATFUNCS_TRUE) ?
				"second" : "microsecond");
	}
	else
		return_code = DATFUNCS_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DATFUNCS_CheckCanonicalTimeFrac9(const char *in_string, char *error_text)
#else
int DATFUNCS_CheckCanonicalTimeFrac9(in_string, error_text)
const char *in_string;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DATFUNCS_FAILURE;

	if ((strlen(in_string) != SDTIF_TIME_TIMESPEC_LEN) ||
		(idx_digit(in_string, 0) != 2) || (idx_digit(in_string + 3, 0) != 2) ||
		(idx_digit(in_string + 6, 0) != 2) ||
		(idx_digit(in_string + 9, 0) != -1) ||
		(in_string[2] != ':') || (in_string[5] != ':') || (in_string[8] != '.')) {
		if (error_text != NULL)
			sprintf(error_text,
				"Invalid message time format ('%-.500s') --- expected '%s'.",
				in_string, "hh:mm:ss.nnnnnnnnn");
	}
	else if ((hourok(atoi(in_string)) != DATFUNCS_TRUE) ||
		(minuteok(atoi(in_string + 3)) != DATFUNCS_TRUE) ||
		(secondok(atoi(in_string + 6)) != DATFUNCS_TRUE) ||
		(atoi(in_string + 9) > 999999999)) {
		if (error_text != NULL)
			sprintf(error_text,
				"Invalid message time ('%s') --- %s field is invalid.",
				in_string, (hourok(atoi(in_string)) != DATFUNCS_TRUE) ?
				"hour" : (minuteok(atoi(in_string + 3)) != DATFUNCS_TRUE) ?
				"minute" : (secondok(atoi(in_string + 6)) != DATFUNCS_TRUE) ?
				"second" : "nanosecond");
	}
	else
		return_code = DATFUNCS_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/


