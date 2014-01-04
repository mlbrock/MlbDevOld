/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logs the leading portion of a log file line.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
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
#ifndef NARGS
int MLOG_LogLeaderDebug(MLOG *mlog_ptr)
#else
int MLOG_LogLeaderDebug(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogLeader(mlog_ptr, NULL, MLOG_PRIORITY_DEBUG, NULL));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogLeaderErr(MLOG *mlog_ptr)
#else
int MLOG_LogLeaderErr(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogLeader(mlog_ptr, NULL, MLOG_PRIORITY_ERR, NULL));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogLeaderInfo(MLOG *mlog_ptr)
#else
int MLOG_LogLeaderInfo(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogLeader(mlog_ptr, NULL, MLOG_PRIORITY_INFO, NULL));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogLeaderWarn(MLOG *mlog_ptr)
#else
int MLOG_LogLeaderWarn(mlog_ptr)
MLOG *mlog_ptr;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogLeader(mlog_ptr, NULL, MLOG_PRIORITY_WARNING, NULL));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogLeader(MLOG *mlog_ptr, const struct timeval *in_time,
	MLOG_PRIORITY log_priority, const char *user_string)
#else
int MLOG_LogLeader(mlog_ptr, in_time, log_priority, user_string)
MLOG                 *mlog_ptr;
const struct timeval *in_time;
MLOG_PRIORITY         log_priority;
const char           *user_string;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogLeaderBasic(mlog_ptr, in_time, log_priority, user_string,
		mlog_ptr->flags, mlog_ptr->mfile_mask, mlog_ptr->file_mask,
		mlog_ptr->syslog_mask));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogLeaderBasic(MLOG *mlog_ptr, const struct timeval *in_time,
	MLOG_PRIORITY log_priority, const char *user_string, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask, MLOG_PRIORITY syslog_mask)
#else
int MLOG_LogLeaderBasic(mlog_ptr, in_time, log_priority, user_string, flags,
	mfile_mask, file_mask, syslog_mask)
MLOG                 *mlog_ptr;
const struct timeval *in_time;
MLOG_PRIORITY         log_priority;
const char           *user_string;
MLOG_FLAG             flags;
MLOG_PRIORITY         mfile_mask;
MLOG_PRIORITY         file_mask;
MLOG_PRIORITY         syslog_mask;
#endif /* #ifndef NARGS */
{
	int           return_code   = MLOG_SUCCESS;
	unsigned int  count_1;
	const char   *ptr_list[MLOG_FORMAT_COUNT];
	char          tmp_date[SDTIF_FMT_TIME_LEN_TIMEVAL + 1];
	char          tmp_pid[STR_VAL2STR_MAX_LEN + 1];
	char          tmp_tid[STR_VAL2STR_MAX_LEN + 1];
	char         *tmp_ptr;

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
		val2str(((unsigned long) GEN_GetProcessID()), 0, 10, NULL, tmp_pid);
	ptr_list[MLOG_FORMAT_INDEX_TID]      =
		val2str(((unsigned long) GEN_GetThreadID()), 0, 10, NULL, tmp_tid);
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

	if (MLOG_DO_PRIORITY_MFILE_BASIC(mlog_ptr, flags, log_priority, mfile_mask))
		mprintf(MLOG_GET_MFILE_PTR(mlog_ptr), "%s", mlog_ptr->work_string);

	if (MLOG_DO_PRIORITY_FILE_BASIC(mlog_ptr, flags, log_priority, file_mask))
		fprintf(MLOG_GET_FILE_PTR(mlog_ptr), "%s", mlog_ptr->work_string);

#ifndef MLOG_OS_HAS_NO_SYSLOG
	if (MLOG_DO_PRIORITY_SYSLOG_BASIC(mlog_ptr, flags, log_priority,
		syslog_mask))
		syslog(MLOG_MAP_PRIORITY_TO_OS(log_priority), "%s",
			mlog_ptr->work_string);
#endif /* #ifndef MLOG_OS_HAS_NO_SYSLOG */

	MLOG_CompleteOutput(mlog_ptr);

	return_code = MLOG_Unlock(mlog_ptr, NULL);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define TEST_MLOG_FILE_NAME		"TEST_MLOG_LogLeader.txt"

const char         *TEST_LineList[] = {
	"LINE NUMBER ONE",
	"LINE NUMBER TWO",
	"LINE NUMBER THREE",
	"LINE NUMBER FOUR",
	"LINE NUMBER FIVE"
};

const unsigned int  TEST_LineCount  =
	sizeof(TEST_LineList) / sizeof(TEST_LineList[0]);

int main(void);

int main()
{
	int             return_code = MLOG_SUCCESS;
	MLOG           *mlog_ptr    = NULL;
	unsigned int    count_1;
	struct timeval  tmp_timeval;
	char            error_text[MLOG_MAX_ERROR_TEXT];

	fprintf(stderr, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
		"Test harness for function 'MLOG_LogLeader()'",
		"                          'MLOG_LogLeaderBasic()'",
		"                          'MLOG_LogLine()'",
		"                          'MLOG_LogLineVA()'",
		"                          'MLOG_LogLineDebug()'",
		"                          'MLOG_LogLineDebugVA()'",
		"                          'MLOG_LogLineErr()'",
		"                          'MLOG_LogLineErrVA()'",
		"                          'MLOG_LogLineInfo()'",
		"                          'MLOG_LogLineInfoVA()'",
		"                          'MLOG_LogLineWarn()'",
		"                          'MLOG_LogLineWarnVA()'",
		"                          'MLOG_LogLineBasic()'",
		"                          'MLOG_LogLineBasicVA()'");
	fprintf(stderr,
		"---- ------- --- -------- -----------------------\n\n");

	if ((mlog_ptr = MLOG_FOpenDefault(TEST_MLOG_FILE_NAME)) != NULL) {
		fprintf(stderr, "Opened test file '%s' (%u bytes).\n",
			TEST_MLOG_FILE_NAME, mlog_ptr->initial_alloc);
		if ((return_code = MLOG_Lock(mlog_ptr, error_text)) == MLOG_SUCCESS) {
			SDTIF_GetTimeUSecs(&tmp_timeval);
			for (count_1 = 0; count_1 < TEST_LineCount; count_1++) {
				MLOG_LogLeader(mlog_ptr, &tmp_timeval, MLOG_PRIORITY_INFO, NULL);
				MLOG_LogLineInfo(mlog_ptr, "%s", TEST_LineList[count_1]);
			}
			return_code = MLOG_Unlock(mlog_ptr, error_text);
		}
		MLOG_Close(mlog_ptr, NULL);
	}
	else {
		sprintf(error_text, "Unable to open test file '%s'.\n",
			TEST_MLOG_FILE_NAME);
		return_code = MLOG_FAILURE;
	}

	if (return_code != MLOG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */


