/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logs the text portion of a log file line.

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

#include <string.h>

#include <strfuncs.h>

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogLineDebug(MLOG *mlog_ptr, const char *in_format, ...)
#else
int MLOG_LogLineDebug(mlog_ptr, in_format, va_list)
MLOG       *mlog_ptr;
const char *in_format;
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

	return_code = MLOG_LogLineDebugVA(mlog_ptr, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogLineDebugVA(MLOG *mlog_ptr, const char *in_format, va_list arg_list)
#else
int MLOG_LogLineDebugVA(mlog_ptr, in_format, arg_list)
MLOG       *mlog_ptr;
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogLineVA(mlog_ptr, MLOG_PRIORITY_DEBUG, in_format, arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogLineErr(MLOG *mlog_ptr, const char *in_format, ...)
#else
int MLOG_LogLineErr(mlog_ptr, in_format, va_list)
MLOG       *mlog_ptr;
const char *in_format;
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

	return_code = MLOG_LogLineErrVA(mlog_ptr, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogLineErrVA(MLOG *mlog_ptr, const char *in_format, va_list arg_list)
#else
int MLOG_LogLineErrVA(mlog_ptr, in_format, arg_list)
MLOG       *mlog_ptr;
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogLineVA(mlog_ptr, MLOG_PRIORITY_ERR, in_format, arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogLineInfo(MLOG *mlog_ptr, const char *in_format, ...)
#else
int MLOG_LogLineInfo(mlog_ptr, in_format, va_list)
MLOG       *mlog_ptr;
const char *in_format;
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

	return_code = MLOG_LogLineInfoVA(mlog_ptr, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogLineInfoVA(MLOG *mlog_ptr, const char *in_format, va_list arg_list)
#else
int MLOG_LogLineInfoVA(mlog_ptr, in_format, arg_list)
MLOG       *mlog_ptr;
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogLineVA(mlog_ptr, MLOG_PRIORITY_INFO, in_format, arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogLineWarn(MLOG *mlog_ptr, const char *in_format, ...)
#else
int MLOG_LogLineWarn(mlog_ptr, in_format, va_list)
MLOG       *mlog_ptr;
const char *in_format;
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

	return_code = MLOG_LogLineWarnVA(mlog_ptr, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogLineWarnVA(MLOG *mlog_ptr, const char *in_format, va_list arg_list)
#else
int MLOG_LogLineWarnVA(mlog_ptr, in_format, arg_list)
MLOG       *mlog_ptr;
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogLineVA(mlog_ptr, MLOG_PRIORITY_WARNING, in_format,
		arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogLine(MLOG *mlog_ptr, MLOG_PRIORITY log_priority,
	const char *in_format, ...)
#else
int MLOG_LogLine(mlog_ptr, log_priority, in_format, va_list)
MLOG          *mlog_ptr;
MLOG_PRIORITY  log_priority;
const char    *in_format;
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

	return_code = MLOG_LogLineVA(mlog_ptr, log_priority, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogLineVA(MLOG *mlog_ptr, MLOG_PRIORITY log_priority,
	const char *in_format, va_list arg_list)
#else
int MLOG_LogLineVA(mlog_ptr, log_priority, in_format, arg_list)
MLOG          *mlog_ptr;
MLOG_PRIORITY  log_priority;
const char    *in_format;
va_list        arg_list;
#endif /* #ifndef NARGS */
{
	return((!MLOG_DO_LOG(mlog_ptr)) ? MLOG_FAILURE :
		MLOG_LogLineBasicVA(mlog_ptr, log_priority, mlog_ptr->flags,
		mlog_ptr->mfile_mask, mlog_ptr->file_mask, mlog_ptr->syslog_mask,
		in_format, arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogLineBasic(MLOG *mlog_ptr, MLOG_PRIORITY log_priority,
	MLOG_FLAG flags, MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, ...)
#else
int MLOG_LogLineBasic(mlog_ptr, log_priority, flags, mfile_mask, file_mask,
	syslog_mask, in_format, va_list)
MLOG          *mlog_ptr;
MLOG_PRIORITY  log_priority;
MLOG_FLAG      flags;
MLOG_PRIORITY  mfile_mask;
MLOG_PRIORITY  file_mask;
MLOG_PRIORITY  syslog_mask;
const char    *in_format;
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

	return_code = MLOG_LogLineBasicVA(mlog_ptr, log_priority, flags, mfile_mask,
		file_mask, syslog_mask, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogLineBasicVA(MLOG *mlog_ptr, MLOG_PRIORITY log_priority,
	MLOG_FLAG flags, MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, va_list arg_list)
#else
int MLOG_LogLineBasicVA(mlog_ptr, log_priority, flags, mfile_mask, file_mask,
	syslog_mask, in_format, arg_list)
MLOG          *mlog_ptr;
MLOG_PRIORITY  log_priority;
MLOG_FLAG      flags;
MLOG_PRIORITY  mfile_mask;
MLOG_PRIORITY  file_mask;
MLOG_PRIORITY  syslog_mask;
const char    *in_format;
va_list        arg_list;
#endif /* #ifndef NARGS */
{
	int          return_code   = MLOG_SUCCESS;
	int          has_line_feed = MLOG_FALSE;
	unsigned int in_format_length;
	char         tmp_format[2048];

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

	if (in_format[(in_format_length = strlen(in_format)) - 1] == '\n')
		has_line_feed = MLOG_TRUE;

	if (MLOG_DO_PRIORITY_MFILE_BASIC(mlog_ptr, flags, log_priority,
		mfile_mask)) {
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
		vfprintf(MLOG_GET_FILE_PTR(mlog_ptr), in_format, arg_list);
		if (has_line_feed != MLOG_TRUE)
			fputc('\n', MLOG_GET_FILE_PTR(mlog_ptr));
	}

#ifndef MLOG_OS_HAS_NO_SYSLOG
	if (MLOG_DO_PRIORITY_SYSLOG_BASIC(mlog_ptr, flags, log_priority,
		syslog_mask))
		vsyslog(MLOG_MAP_PRIORITY_TO_OS(log_priority), in_format, arg_list);
#endif /* #ifndef MLOG_OS_HAS_NO_SYSLOG */

	MLOG_CompleteOutput(mlog_ptr);

	return_code = MLOG_Unlock(mlog_ptr, NULL);

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/


