/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sets a logging format.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/


/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <string.h>

#include <strfuncs.h>

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SetLogFormat(MLOG *mlog_ptr, const char *in_log_format,
	const char *in_user_string, char *error_text)
#else
int MLOG_SetLogFormat(mlog_ptr, in_log_format, in_user_string, error_text)
MLOG       *mlog_ptr;
const char *in_log_format;
const char *in_user_string;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int return_code  = MLOG_SUCCESS;

	if ((return_code = MLOG_Lock(mlog_ptr, error_text)) != MLOG_SUCCESS) {
		return_code = MLOG_SetLogFormatBasic(mlog_ptr, in_log_format,
			in_user_string, error_text);
		return_code = MLOG_Check(mlog_ptr, error_text);
		MLOG_Unlock(mlog_ptr, NULL);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*
	ADF NOTE: Because this function is used by ``MLOG_OpenBasic`` before
	the ''MLOG'' structure is completely initialized, it does not lock the
	structure. This function is therefore visible only in the internal MLOG
	API.
*/
/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_SetLogFormatBasic(MLOG *mlog_ptr, const char *in_log_format,
	const char *in_user_string, char *error_text)
#else
int MLOG_SetLogFormatBasic(mlog_ptr, in_log_format, in_user_string, error_text)
MLOG       *mlog_ptr;
const char *in_log_format;
const char *in_user_string;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code  = MLOG_SUCCESS;
	unsigned int  format_count = 0;
	MLOG_FORMAT  *format_list  = NULL;
	unsigned int  used_length  = 0;
	unsigned int  work_length  = 0;
	char         *work_string  = NULL;
	char         *user_string  = NULL;
	char         *log_format   = NULL;
	unsigned int  count_1;

	if ((return_code = MLOG_Check(mlog_ptr, error_text)) != MLOG_SUCCESS)
		goto EXIT_FUNCTION;

	in_log_format  =
		((in_log_format != NULL) && *in_log_format) ? in_log_format : "D6M";
	in_user_string =
		((in_user_string != NULL) && *in_user_string) ? in_user_string : NULL;

	if ((log_format = strdup(in_log_format)) == NULL) {
		STR_AllocMsgItem(strlen(in_log_format) + 1, error_text,
			"Unable to copy the log format string");
		return_code = MLOG_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((in_user_string != NULL) &&
		((user_string = strdup(in_user_string)) == NULL)) {
		STR_AllocMsgItem(strlen(in_user_string) + 1, error_text,
			"Unable to copy the user string");
		return_code = MLOG_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	format_count = strlen(log_format);
	if ((format_list = ((MLOG_FORMAT *) calloc(format_count,
		sizeof(MLOG_FORMAT)))) == NULL) {
		STR_AllocMsgList(format_count, sizeof(MLOG_FORMAT), error_text,
			"Unable to allocate the array of log format specifications");
		return_code = MLOG_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < format_count; count_1++) {
		switch (toupper(log_format[count_1])) {
			case MLOG_FORMAT_CHAR_DATE		:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_DATE;
				format_list[count_1].length = 10;
				break;
			case MLOG_FORMAT_CHAR_TIME_0	:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_TIME;
				format_list[count_1].length = 8;
				break;
			case MLOG_FORMAT_CHAR_TIME_1	:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_TIME;
				format_list[count_1].length = 10;
				break;
			case MLOG_FORMAT_CHAR_TIME_2	:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_TIME;
				format_list[count_1].length = 11;
				break;
			case MLOG_FORMAT_CHAR_TIME_3	:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_TIME;
				format_list[count_1].length = 12;
				break;
			case MLOG_FORMAT_CHAR_TIME_4	:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_TIME;
				format_list[count_1].length = 13;
				break;
			case MLOG_FORMAT_CHAR_TIME_5	:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_TIME;
				format_list[count_1].length = 14;
				break;
			case MLOG_FORMAT_CHAR_TIME_6	:
			case MLOG_FORMAT_CHAR_TIME		:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_TIME;
				format_list[count_1].length = 15;
				break;
			case MLOG_FORMAT_CHAR_PID		:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_PID;
				format_list[count_1].length = 10;
				break;
			case MLOG_FORMAT_CHAR_TID		:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_TID;
				format_list[count_1].length = 10;
				break;
			case MLOG_FORMAT_CHAR_PRIORITY	:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_PRIORITY;
				format_list[count_1].length = MLOG_PRIORITY_NAME_MAX;
				break;
			case MLOG_FORMAT_CHAR_USER		:
				format_list[count_1].index  = MLOG_FORMAT_INDEX_USER;
				format_list[count_1].length =
					(user_string != NULL) ? strlen(user_string) : 32;
				break;
			default								:
				if (error_text != NULL)
					sprintf(error_text, "%s (ASCII %uD = '%c').",
						"Invalid log format character",
						((unsigned int) log_format[count_1]),
						(isprint(log_format[count_1])) ? log_format[count_1] : '?');
				return_code = MLOG_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
		}
		format_list[count_1].offset  = used_length;
		used_length                 += format_list[count_1].length + 1;
	}

	work_length =
		STRFUNCS_ADJUST_SIZE(used_length + mlog_ptr->sep_length, 1024) + 1024;

	if ((work_string = ((char *) calloc(work_length, sizeof(char)))) == NULL) {
		STR_AllocMsgItem(work_length, error_text,
			"Unable to allocate the log format working buffer");
		return_code = MLOG_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (mlog_ptr->log_format != NULL)
		free(mlog_ptr->log_format);

	if (mlog_ptr->user_string != NULL)
		free(mlog_ptr->user_string);

	if (mlog_ptr->format_list != NULL)
		free(mlog_ptr->format_list);

	if (mlog_ptr->work_string != NULL)
		free(mlog_ptr->work_string);

	mlog_ptr->log_format   = log_format;
	mlog_ptr->user_string  = user_string;
	mlog_ptr->format_count = format_count;
	mlog_ptr->format_list  = format_list;
	mlog_ptr->used_length  = used_length;
	mlog_ptr->work_length  = work_length;
	mlog_ptr->work_string  = work_string;

EXIT_FUNCTION:

	if (return_code != MLOG_SUCCESS) {
		if (log_format != NULL)
			free(log_format);
		if (user_string != NULL)
			free(user_string);
		if (format_list != NULL)
			free(format_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

