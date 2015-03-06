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

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogTextDebug(MLOG *mlog_ptr, const char *in_format, ...)
#else
int MLOG_LogTextDebug(mlog_ptr, in_format, va_list)
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

	return_code = MLOG_LogTextDebugVA(mlog_ptr, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogTextDebugVA(MLOG *mlog_ptr, const char *in_format, va_list arg_list)
#else
int MLOG_LogTextDebugVA(mlog_ptr, in_format, arg_list)
MLOG       *mlog_ptr;
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogTextVA(mlog_ptr, MLOG_PRIORITY_DEBUG, in_format, arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogTextErr(MLOG *mlog_ptr, const char *in_format, ...)
#else
int MLOG_LogTextErr(mlog_ptr, in_format, va_list)
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

	return_code = MLOG_LogTextErrVA(mlog_ptr, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogTextErrVA(MLOG *mlog_ptr, const char *in_format, va_list arg_list)
#else
int MLOG_LogTextErrVA(mlog_ptr, in_format, arg_list)
MLOG       *mlog_ptr;
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogTextVA(mlog_ptr, MLOG_PRIORITY_ERR, in_format, arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogTextInfo(MLOG *mlog_ptr, const char *in_format, ...)
#else
int MLOG_LogTextInfo(mlog_ptr, in_format, va_list)
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

	return_code = MLOG_LogTextInfoVA(mlog_ptr, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogTextInfoVA(MLOG *mlog_ptr, const char *in_format, va_list arg_list)
#else
int MLOG_LogTextInfoVA(mlog_ptr, in_format, arg_list)
MLOG       *mlog_ptr;
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogTextVA(mlog_ptr, MLOG_PRIORITY_INFO, in_format, arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogTextWarn(MLOG *mlog_ptr, const char *in_format, ...)
#else
int MLOG_LogTextWarn(mlog_ptr, in_format, va_list)
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

	return_code = MLOG_LogTextWarnVA(mlog_ptr, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogTextWarnVA(MLOG *mlog_ptr, const char *in_format, va_list arg_list)
#else
int MLOG_LogTextWarnVA(mlog_ptr, in_format, arg_list)
MLOG       *mlog_ptr;
const char *in_format;
va_list     arg_list;
#endif /* #ifndef NARGS */
{
	return(MLOG_LogTextVA(mlog_ptr, MLOG_PRIORITY_WARNING, in_format,
		arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogText(MLOG *mlog_ptr, MLOG_PRIORITY log_priority,
	const char *in_format, ...)
#else
int MLOG_LogText(mlog_ptr, log_priority, in_format, va_list)
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

	return_code = MLOG_LogTextVA(mlog_ptr, log_priority, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogTextVA(MLOG *mlog_ptr, MLOG_PRIORITY log_priority,
	const char *in_format, va_list arg_list)
#else
int MLOG_LogTextVA(mlog_ptr, log_priority, in_format, arg_list)
MLOG          *mlog_ptr;
MLOG_PRIORITY  log_priority;
const char    *in_format;
va_list        arg_list;
#endif /* #ifndef NARGS */
{
	return((!MLOG_DO_LOG(mlog_ptr)) ? MLOG_FAILURE :
		MLOG_LogTextBasicVA(mlog_ptr, log_priority, mlog_ptr->flags,
		mlog_ptr->mfile_mask, mlog_ptr->file_mask, mlog_ptr->syslog_mask,
		in_format, arg_list));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*VARARGS2*/
#ifndef NO_STDARGS
int MLOG_LogTextBasic(MLOG *mlog_ptr, MLOG_PRIORITY log_priority,
	MLOG_FLAG flags, MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, ...)
#else
int MLOG_LogTextBasic(mlog_ptr, log_priority, flags, mfile_mask, file_mask,
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

	return_code = MLOG_LogTextBasicVA(mlog_ptr, log_priority, flags, mfile_mask,
		file_mask, syslog_mask, in_format, arg_list);

	va_end(arg_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_LogTextBasicVA(MLOG *mlog_ptr, MLOG_PRIORITY log_priority,
	MLOG_FLAG flags, MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, va_list arg_list)
#else
int MLOG_LogTextBasicVA(mlog_ptr, log_priority, flags, mfile_mask, file_mask,
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
	int return_code = MLOG_SUCCESS;

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

	if (MLOG_DO_PRIORITY_MFILE_BASIC(mlog_ptr, flags, log_priority,
		mfile_mask))
		vmprintf(MLOG_GET_MFILE_PTR(mlog_ptr), in_format, arg_list);

	if (MLOG_DO_PRIORITY_FILE_BASIC(mlog_ptr, flags, log_priority, file_mask))
		vfprintf(MLOG_GET_FILE_PTR(mlog_ptr), in_format, arg_list);

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


