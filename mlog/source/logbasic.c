/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Lowest-level logging functionality.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <limits.h>
#include <string.h>

#include <genfuncs.h>

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogBasic(MLOG *mlog_ptr, const struct timeval *in_time,
	MLOG_PRIORITY log_priority, const char *user_string, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, ...)
#else
int MLOG_LogBasic(mlog_ptr, in_time, log_priority, user_string, flags,
	mfile_mask, file_mask, syslog_mask, in_format, va_list)
MLOG                 *mlog_ptr;
const struct timeval *in_time;
MLOG_PRIORITY         log_priority;
const char           *user_string;
MLOG_FLAG             flags;
MLOG_PRIORITY         mfile_mask;
MLOG_PRIORITY         file_mask;
MLOG_PRIORITY         syslog_mask;
const char           *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	int     return_code;
	va_list arg_list;

#ifndef NO_STDARGS
	va_start(arg_list, in_format);
#else
	va_start(arg_list);
#endif /* #ifndef NO_STDARGS */

	return_code = MLOG_LogBasicVA(mlog_ptr, in_time, log_priority,
		user_string, flags, mfile_mask, file_mask, syslog_mask, in_format,
		arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogBasicVA(MLOG *mlog_ptr, const struct timeval *in_time,
	MLOG_PRIORITY log_priority, const char *user_string, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask, MLOG_PRIORITY syslog_mask,
	const char *in_format, va_list arg_list)
#else
int MLOG_LogBasicVA(mlog_ptr, in_time, log_priority, user_string, flags,
	mfile_mask, file_mask, syslog_mask, in_format, arg_list)
MLOG                 *mlog_ptr;
const struct timeval *in_time;
MLOG_PRIORITY         log_priority;
const char           *user_string;
MLOG_FLAG             flags;
MLOG_PRIORITY         mfile_mask;
MLOG_PRIORITY         file_mask;
MLOG_PRIORITY         syslog_mask;
const char           *in_format;
va_list               arg_list;
#endif /* #ifndef NARGS */
{
	int           return_code   = MLOG_SUCCESS;
	int           has_line_feed = MLOG_FALSE;
	unsigned int  count_1;
	unsigned int  in_format_length;
	const char   *ptr_list[MLOG_FORMAT_COUNT];
	char          tmp_date[SDTIF_FMT_TIME_LEN_TIMEVAL + 1];
	char          tmp_pid[STR_VAL2STR_MAX_LEN + 1];
	char          tmp_tid[STR_VAL2STR_MAX_LEN + 1];
	char         *tmp_ptr;
	char          tmp_format[2048];

	if ((in_format == NULL) || (!(*in_format))) {
		return_code = MLOG_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = MLOG_Lock(mlog_ptr, NULL)) != MLOG_SUCCESS)
		goto EXIT_FUNCTION;

	if (!MLOG_DO_PRIORITY_BASIC(mlog_ptr, flags, log_priority, mfile_mask,
		file_mask, syslog_mask)) {
		MLOG_Unlock(mlog_ptr, NULL);
		goto EXIT_FUNCTION;
	}

	if (mlog_ptr->flags & MLOG_FLAG_TIME_GMT)
		SDTIF_Format_timeval_GMT(in_time, tmp_date);
	else
		SDTIF_Format_timeval(in_time, tmp_date);

	ptr_list[MLOG_FORMAT_INDEX_DATE]     = tmp_date;
	ptr_list[MLOG_FORMAT_INDEX_TIME]     = tmp_date + 11;
	ptr_list[MLOG_FORMAT_INDEX_PRIORITY] =
		MLOG_GET_PRIORITY_NAME(log_priority);
	ptr_list[MLOG_FORMAT_INDEX_PID]      =
		strpadl(val2str(((unsigned long) GEN_GetProcessID()), 0, 10, NULL,
		tmp_pid), 10);
	ptr_list[MLOG_FORMAT_INDEX_TID]      =
		strpadl(val2str(((unsigned long) GEN_GetThreadID()), 0, 10, NULL,
		tmp_tid), 10);
	ptr_list[MLOG_FORMAT_INDEX_USER]     = (user_string != NULL) ? user_string :
		((mlog_ptr->user_string != NULL) ? mlog_ptr->user_string : "");

	tmp_ptr = mlog_ptr->work_string;
	for (count_1 = 0; count_1 < mlog_ptr->format_count; count_1++) {
		chrcat(strpadr(nstrcpy(tmp_ptr,
			ptr_list[mlog_ptr->format_list[count_1].index],
			mlog_ptr->format_list[count_1].length),
			mlog_ptr->format_list[count_1].length), ':');
		tmp_ptr += mlog_ptr->format_list[count_1].length + 1;
	}

	if (in_format[(in_format_length = strlen(in_format)) - 1] == '\n')
		has_line_feed = MLOG_TRUE;

	if (MLOG_DO_PRIORITY_MFILE_BASIC(mlog_ptr, flags, log_priority,
		mfile_mask)) {
		mprintf(MLOG_GET_MFILE_PTR(mlog_ptr), "%s", mlog_ptr->work_string);
		vmprintf(MLOG_GET_MFILE_PTR(mlog_ptr), in_format, arg_list);
		if (has_line_feed != MLOG_TRUE) {
			if (MLOG_GET_CURR_OFFSET(mlog_ptr) &&
				(MLOG_GET_MMAP_PTR(mlog_ptr) != NULL) &&
				(MLOG_GET_OFFSET_PTRC(mlog_ptr)[-1] == '\n'))
				has_line_feed = MLOG_TRUE;
			else if (MLOG_GET_CURR_OFFSET(mlog_ptr) &&
				(mseek(MLOG_GET_MFILE_PTR(mlog_ptr), -1, SEEK_CUR) == 0) &&
				(mgetc(MLOG_GET_MFILE_PTR(mlog_ptr)) == '\n')) {
				mseek(MLOG_GET_MFILE_PTR(mlog_ptr), 0, SEEK_END);
				has_line_feed = MLOG_TRUE;
			}
			else {
				mseek(MLOG_GET_MFILE_PTR(mlog_ptr), 0, SEEK_END);
				mputc('\n', MLOG_GET_MFILE_PTR(mlog_ptr));
				if (in_format_length < (sizeof(tmp_format) - 1)) {
					chrcat(strcpy(tmp_format, in_format), '\n');
					in_format     = tmp_format;
					has_line_feed = MLOG_TRUE;
				}
			}
		}
	}

	if ((has_line_feed != MLOG_TRUE) &&
		(in_format_length < (sizeof(tmp_format) - 1))) {
		chrcat(strcpy(tmp_format, in_format), '\n');
		in_format     = tmp_format;
		has_line_feed = MLOG_TRUE;
	}

	if (MLOG_DO_PRIORITY_FILE_BASIC(mlog_ptr, flags, log_priority, file_mask)) {
		fprintf(MLOG_GET_FILE_PTR(mlog_ptr), "%s", mlog_ptr->work_string);
		vfprintf(MLOG_GET_FILE_PTR(mlog_ptr), in_format, arg_list);
		if (has_line_feed != MLOG_TRUE)
			fputc('\n', MLOG_GET_FILE_PTR(mlog_ptr));
	}

#ifndef MLOG_OS_HAS_NO_SYSLOG
	if (MLOG_DO_PRIORITY_SYSLOG_BASIC(mlog_ptr, flags, log_priority,
		syslog_mask)) {
		syslog(MLOG_MAP_PRIORITY_TO_OS(log_priority), "%s",
			mlog_ptr->work_string);
		vsyslog(MLOG_MAP_PRIORITY_TO_OS(log_priority), in_format, arg_list);
	}
#endif /* #ifndef MLOG_OS_HAS_NO_SYSLOG */

	MLOG_CompleteOutput(mlog_ptr);

	return_code = MLOG_Unlock(mlog_ptr, NULL);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define TEST_MLOG_FILE_NAME		"TEST_MLOG_LogBasic.txt"

int main(void);

int main()
{
	int           return_code = MLOG_SUCCESS;
	MLOG         *mlog_ptr    = NULL;
	unsigned int  count_1;
	char          buffer_list[26][666 + 1];
	char          error_text[MLOG_MAX_ERROR_TEXT];

	fprintf(stderr, "%s\n%s\n",
		"Test harness for function 'MLOG_LogBasic()'",
		"                          'MLOG_LogBasicVA()'");
	fprintf(stderr,
		"---- ------- --- -------- -------------------\n\n");

	if ((mlog_ptr = MLOG_FOpenDefault(TEST_MLOG_FILE_NAME)) != NULL) {
		fprintf(stderr, "Opened test file '%s' (%u bytes).\n",
			TEST_MLOG_FILE_NAME, mlog_ptr->initial_alloc);
		for (count_1 = 0; count_1 < 26; count_1++) {
			memset(buffer_list[count_1], ((int) ('A' + count_1)),
				sizeof(buffer_list[0]));
			buffer_list[count_1][sizeof(buffer_list[0]) - 1] = '\0';
		}
		for (count_1 = 0; count_1 < 26; count_1++) {
			MLOG_LogBasic(mlog_ptr, NULL, MLOG_PRIORITY_INFO, NULL,
				mlog_ptr->flags, mlog_ptr->mfile_mask, mlog_ptr->file_mask,
/*
				mlog_ptr->syslog_mask, "Try number %10u: %s\n",
*/
				mlog_ptr->syslog_mask, "Try number %10u: %s",
				count_1, buffer_list[count_1]);
		}
		return_code = MLOG_Close(mlog_ptr, error_text);
	}
	else {
		sprintf(error_text, "Unable to open test file '%s'.\n",
			TEST_MLOG_FILE_NAME);
		return_code = MLOG_FAILURE;
	}

	if (return_code != MLOG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

fprintf(stderr, "************* REMOVE TEST CODE ********************\n");
	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

