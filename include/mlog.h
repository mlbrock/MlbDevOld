/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Include File									*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Memory-mapped Logging Facility
								(MLOG).

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__MLOG_H__h

#define h__MLOG_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <stdio.h>

#ifndef NO_STDARGS
# include <stdarg.h>
#else
# include <varargs.h>
#endif /* #ifndef NO_STDARGS */

#include <sdtif.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  MLOG Truth Codes

   NAME        :  MLOG Truth Codes

	DESCRIPTION :  Manifest constants used within MLOG to specify the truth
						or falsity of expressions.

						(.) ''MLOG_TRUE''

						(.) ''MLOG_FALSE''

   NOTES       :  The manifest constant ''MLOG_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''MLOG_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:  MLOG_TRUE
						MLOG_FALSE
						MLOG Truth Codes:MLOG_TRUE
						MLOG Truth Codes:MLOG_FALSE
						MLOG Manifest Constants:MLOG_TRUE
						MLOG Manifest Constants:MLOG_FALSE
						MLOG Defines:MLOG_TRUE
						MLOG Defines:MLOG_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  MLOG Truth Codes
						MLOG Truth Code
						MLOG truth codes
						MLOG truth code
						MLOG_TRUE
						MLOG_FALSE

   PUBLISH NAME:	MLOG Truth Codes
						MLOG_TRUE
						MLOG_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MLOG_TRUE								1
#define MLOG_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	MLOG Return Codes

   NAME        :  MLOG Return Codes

   DESCRIPTION :  The MLOG return codes have the following meanings:

						(.) ''MLOG_SUCCESS'' means that the function invoked
						completed without error. ''MLOG_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''MLOG_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other MLOG error codes.

						(.) ''MLOG_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''MLOG_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''MLOG_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

						(.) ''MLOG_LOCK_ACQ_FAILURE'' indicates that a lock
						could not be acquired on the MLOG mutex.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:  MLOG_SUCCESS
						MLOG_FAILURE
						MLOG_BAD_ARGS_FAILURE
						MLOG_MEMORY_FAILURE
						MLOG_SYSTEM_FAILURE
						MLOG_LOCK_ACQ_FAILURE
						MLOG Return Codes:MLOG_SUCCESS
						MLOG Return Codes:MLOG_FAILURE
						MLOG Return Codes:MLOG_BAD_ARGS_FAILURE
						MLOG Return Codes:MLOG_MEMORY_FAILURE
						MLOG Return Codes:MLOG_SYSTEM_FAILURE
						MLOG Return Codes:MLOG_LOCK_ACQ_FAILURE
						MLOG Manifest Constants:MLOG_SUCCESS
						MLOG Manifest Constants:MLOG_FAILURE
						MLOG Manifest Constants:MLOG_BAD_ARGS_FAILURE
						MLOG Manifest Constants:MLOG_MEMORY_FAILURE
						MLOG Manifest Constants:MLOG_SYSTEM_FAILURE
						MLOG Manifest Constants:MLOG_LOCK_ACQ_FAILURE
						MLOG Defines:MLOG_SUCCESS
						MLOG Defines:MLOG_FAILURE
						MLOG Defines:MLOG_BAD_ARGS_FAILURE
						MLOG Defines:MLOG_MEMORY_FAILURE
						MLOG Defines:MLOG_SYSTEM_FAILURE
						MLOG Defines:MLOG_LOCK_ACQ_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  MLOG_SUCCESS
						MLOG_FAILURE
						MLOG_BAD_ARGS_FAILURE
						MLOG_MEMORY_FAILURE
						MLOG_SYSTEM_FAILURE
						MLOG_LOCK_ACQ_FAILURE
						MLOG Return Codes
						MLOG Return Code
						MLOG return codes
						MLOG return code
						MLOG Status Codes
						MLOG Status Code
						MLOG status codes
						MLOG status code
						MLOG Error Codes
						MLOG Error Code
						MLOG error codes
						MLOG error code

   PUBLISH NAME:	MLOG Return Codes
						MLOG return codes
						MLOG_SUCCESS
						MLOG_FAILURE
						MLOG_BAD_ARGS_FAILURE
						MLOG_MEMORY_FAILURE
						MLOG_SYSTEM_FAILURE
						MLOG_LOCK_ACQ_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MLOG_SUCCESS								 0
#define MLOG_FAILURE								-1
#define MLOG_BAD_ARGS_FAILURE					-2
#define MLOG_MEMORY_FAILURE					-3
#define MLOG_SYSTEM_FAILURE					-4
#define MLOG_LOCK_ACQ_FAILURE					-5
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  MLOG_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''MLOG_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a MLOG function.

   CAVEATS     :  MLOG error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''MLOG_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to MLOG functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:  MLOG_MAX_ERROR_TEXT
						MLOG Manifest Constants:MLOG_MAX_ERROR_TEXT
						MLOG Defines:MLOG_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MLOG_MAX_ERROR_TEXT

   PUBLISH NAME:	MLOG_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MLOG_MAX_ERROR_TEXT				1024
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_MAP_TRUTH(code)					\
	((code) ? MLOG_TRUE : MLOG_FALSE)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long MLOG_FLAG;
typedef unsigned long MLOG_PRIORITY;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_FLAG_NONE	 					((MLOG_FLAG) 0X0000)
#define MLOG_FLAG_MFILE 					((MLOG_FLAG) 0X0001)
#define MLOG_FLAG_APPEND					((MLOG_FLAG) 0X0002)
#define MLOG_FLAG_FILE						((MLOG_FLAG) 0X0004)
#define MLOG_FLAG_SYSLOG					((MLOG_FLAG) 0X0008)
#define MLOG_FLAG_SYNC						((MLOG_FLAG) 0X0010)
#define MLOG_FLAG_SYNC_ASYNC				((MLOG_FLAG) 0X0020)
#define MLOG_FLAG_TIME_GMT					((MLOG_FLAG) 0X0040)
#define MLOG_FLAG_FILE_FLUSH				((MLOG_FLAG) 0X0080)
#define MLOG_FLAG_FILE_CLOSE				((MLOG_FLAG) 0X0100)

#define MLOG_FLAG_MASK		\
	(MLOG_FLAG_MFILE      |	\
	 MLOG_FLAG_APPEND     |	\
	 MLOG_FLAG_FILE       |	\
	 MLOG_FLAG_SYSLOG     |	\
	 MLOG_FLAG_SYNC       |	\
	 MLOG_FLAG_SYNC_ASYNC |	\
	 MLOG_FLAG_TIME_GMT)

#define MLOG_FLAGS_FOR_MFILE	\
	(MLOG_FLAG_MFILE      |		\
	 MLOG_FLAG_APPEND     |		\
	 MLOG_FLAG_SYNC       |		\
	 MLOG_FLAG_SYNC_ASYNC)
#define MLOG_FLAGS_FOR_FILE	\
	(MLOG_FLAG_FILE       |		\
	 MLOG_FLAG_FILE_FLUSH |		\
	 MLOG_FLAG_FILE_CLOSE)
#define MLOG_FLAGS_FOR_SYSLOG	\
	(MLOG_FLAG_SYSLOG)

#define MLOG_HAS_FLAGS_FOR_MFILE(flags)	\
	MLOG_MAP_TRUTH((flags) & MLOG_FLAGS_FOR_MFILE)
#define MLOG_HAS_FLAGS_FOR_FILE(flags)		\
	MLOG_MAP_TRUTH((flags) & MLOG_FLAGS_FOR_FILE)
#define MLOG_HAS_FLAGS_FOR_SYSLOG(flags)	\
	MLOG_MAP_TRUTH((flags) & MLOG_FLAGS_FOR_SYSLOG)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_FLAG_DEFAULT					\
	(MLOG_FLAG_MFILE | MLOG_FLAG_FILE | MLOG_FLAG_SYSLOG)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_PRIORITY_NONE					((MLOG_PRIORITY) 0X0000)
#define MLOG_PRIORITY_EMERG				((MLOG_PRIORITY) 0X0001)
#define MLOG_PRIORITY_ALERT				((MLOG_PRIORITY) 0X0002)
#define MLOG_PRIORITY_CRIT					((MLOG_PRIORITY) 0X0004)
#define MLOG_PRIORITY_ERR					((MLOG_PRIORITY) 0X0008)
#define MLOG_PRIORITY_WARNING				((MLOG_PRIORITY) 0X0010)
#define MLOG_PRIORITY_NOTICE				((MLOG_PRIORITY) 0X0020)
#define MLOG_PRIORITY_INFO					((MLOG_PRIORITY) 0X0040)
#define MLOG_PRIORITY_DEBUG				((MLOG_PRIORITY) 0X0080)

#define MLOG_PRIORITY_MASK		\
	(MLOG_PRIORITY_EMERG   |	\
	 MLOG_PRIORITY_ALERT   |	\
	 MLOG_PRIORITY_CRIT    |	\
	 MLOG_PRIORITY_ERR     |	\
	 MLOG_PRIORITY_WARNING |	\
	 MLOG_PRIORITY_NOTICE  |	\
	 MLOG_PRIORITY_INFO    |	\
	 MLOG_PRIORITY_DEBUG)

#define MLOG_PRIORITY_DEFAULT_MFILE		MLOG_PRIORITY_MASK
#define MLOG_PRIORITY_DEFAULT_FILE		MLOG_PRIORITY_MASK
#define MLOG_PRIORITY_DEFAULT_SYSLOG	\
	(MLOG_PRIORITY_EMERG |					\
	 MLOG_PRIORITY_ALERT |					\
	 MLOG_PRIORITY_CRIT  |					\
	 MLOG_PRIORITY_ERR   |					\
	 MLOG_PRIORITY_WARNING)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_PRIORITY_DEFAULT_MFILE		MLOG_PRIORITY_MASK
#define MLOG_PRIORITY_DEFAULT_FILE		MLOG_PRIORITY_MASK
#define MLOG_PRIORITY_DEFAULT_SYSLOG	\
	(MLOG_PRIORITY_EMERG | MLOG_PRIORITY_ALERT | MLOG_PRIORITY_CRIT | \
	MLOG_PRIORITY_ERR | MLOG_PRIORITY_WARNING)
/*	***********************************************************************	*/

/*
	CODE NOTE:	To be removed when code in 'eosomrv' library is changed.
*/
/*	***********************************************************************	*/
#define MLOG_IS_PTR(ptr)               \
	MLOG_MAP_TRUTH(MLOG_Check(ptr, NULL) == MLOG_SUCCESS)
#define MLOG_GET_FILE_NAME(ptr)			MLOG_GetFileName(ptr)
#define MLOG_GET_FLAGS(ptr)            MLOG_GetFlags(ptr)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#ifndef h__MLOGI_H__h
typedef void *MLOG;
#endif /* #ifndef h__MLOGI_H__h */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for the MLOG functions . . .							*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MLOG core function prototypes . . .
		*****************************************************************	*/
#ifdef __GNUC__
COMPAT_FN_DECL(int MLOG_LogDebug,
	(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogErr,
	(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogInfo,
	(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogWarn,
		(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogPDebug,
		(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogIf,
		(MLOG *mlog_ptr, int if_value, const char *in_format, ...)
	__attribute__ ((format (printf, 3, 4))));
COMPAT_FN_DECL(int MLOG_LogBasic,
	(MLOG *mlog_ptr, const struct timeval *in_time, MLOG_PRIORITY log_priority,
	const char *user_string, MLOG_FLAG flags, MLOG_PRIORITY mfile_mask,
	MLOG_PRIORITY file_mask, MLOG_PRIORITY syslog_mask, const char *in_format,
	...) __attribute__ ((format (printf, 9, 10))));
#else
COMPAT_FN_DECL(int MLOG_LogDebug,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogErr,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogInfo,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogWarn,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogPDebug,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogIf,
	(MLOG *mlog_ptr, int if_value, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogBasic,
	(MLOG *mlog_ptr, const struct timeval *in_time, MLOG_PRIORITY log_priority,
	const char *user_string, MLOG_FLAG flags, MLOG_PRIORITY mfile_mask,
	MLOG_PRIORITY file_mask, MLOG_PRIORITY syslog_mask, const char *in_format,
	...));
#endif /* #ifdef __GNUC__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MLOG variable-argument core function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MLOG_LogDebugVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogErrVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogInfoVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogWarnVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogPDebugVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogIfVA,
	(MLOG *mlog_ptr, int if_value, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogBasicVA,
	(MLOG *mlog_ptr, const struct timeval *in_time, MLOG_PRIORITY log_priority,
	const char *user_string, MLOG_FLAG flags, MLOG_PRIORITY mfile_mask,
	MLOG_PRIORITY file_mask, MLOG_PRIORITY syslog_mask, const char *in_format,
	va_list arg_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MLOG core functions with specified time prototypes . . .
		*****************************************************************	*/
#ifdef __GNUC__
COMPAT_FN_DECL(int MLOG_LogDebugTime,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format, ...)
	__attribute__ ((format (printf, 3, 4))));
COMPAT_FN_DECL(int MLOG_LogErrTime,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format, ...)
	__attribute__ ((format (printf, 3, 4))));
COMPAT_FN_DECL(int MLOG_LogInfoTime,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format, ...)
	__attribute__ ((format (printf, 3, 4))));
COMPAT_FN_DECL(int MLOG_LogWarnTime,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format, ...)
	__attribute__ ((format (printf, 3, 4))));
COMPAT_FN_DECL(int MLOG_LogPDebugTime,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format, ...)
	__attribute__ ((format (printf, 3, 4))));
COMPAT_FN_DECL(int MLOG_LogIfTime,
	(MLOG *mlog_ptr, int if_value, const struct timeval *in_time,
	const char *in_format, ...)
	__attribute__ ((format (printf, 4, 5))));
#else
COMPAT_FN_DECL(int MLOG_LogDebugTime,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogErrTime,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogInfoTime,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogWarnTime,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogPDebugTime,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogIfTime,
	(MLOG *mlog_ptr, int if_value, const struct timeval *in_time,
	const char *in_format, ...));
#endif /* #ifdef __GNUC__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MLOG variable-argument core functions with specified time prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MLOG_LogDebugTimeVA,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format,
	va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogErrTimeVA,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format,
	va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogInfoTimeVA,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format,
	va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogWarnTimeVA,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format,
	va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogPDebugTimeVA,
	(MLOG *mlog_ptr, const struct timeval *in_time, const char *in_format,
	va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogIfTimeVA,
	(MLOG *mlog_ptr, int if_value, const struct timeval *in_time,
	const char *in_format, va_list arg_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for the leader logging functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MLOG_LogLeaderDebug,
	(MLOG *mlog_ptr));
COMPAT_FN_DECL(int MLOG_LogLeaderErr,
	(MLOG *mlog_ptr));
COMPAT_FN_DECL(int MLOG_LogLeaderInfo,
	(MLOG *mlog_ptr));
COMPAT_FN_DECL(int MLOG_LogLeaderWarn,
	(MLOG *mlog_ptr));
COMPAT_FN_DECL(int MLOG_LogLeader,
	(MLOG *mlog_ptr, const struct timeval *in_time, MLOG_PRIORITY log_priority,
	const char *user_string));
COMPAT_FN_DECL(int MLOG_LogLeaderBasic,
	(MLOG *mlog_ptr, const struct timeval *in_time, MLOG_PRIORITY log_priority,
	const char *user_string, MLOG_FLAG flags, MLOG_PRIORITY mfile_mask,
	MLOG_PRIORITY file_mask, MLOG_PRIORITY syslog_mask));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for the text logging functions . . .
		*****************************************************************	*/
#ifdef __GNUC__
COMPAT_FN_DECL(int MLOG_LogTextDebug,
	(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogTextErr,
	(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogTextInfo,
	(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogTextWarn,
	(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogText,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, const char *in_format, ...)
	__attribute__ ((format (printf, 3, 4))));
COMPAT_FN_DECL(int MLOG_LogTextBasic,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, ...)
	__attribute__ ((format (printf, 7, 8))));
#else
COMPAT_FN_DECL(int MLOG_LogTextDebug,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogTextErr,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogTextInfo,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogTextWarn,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogText,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogTextBasic,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, ...));
#endif /* #ifdef __GNUC__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for the variable-argument text logging functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MLOG_LogTextDebugVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogTextErrVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogTextInfoVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogTextWarnVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogTextVA,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, const char *in_format,
	va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogTextBasicVA,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, va_list arg_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for the line logging functions . . .
		*****************************************************************	*/
#ifdef __GNUC__
COMPAT_FN_DECL(int MLOG_LogLineDebug,
	(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogLineErr,
	(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogLineInfo,
	(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogLineWarn,
	(MLOG *mlog_ptr, const char *in_format, ...)
	__attribute__ ((format (printf, 2, 3))));
COMPAT_FN_DECL(int MLOG_LogLine,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, const char *in_format, ...)
	__attribute__ ((format (printf, 3, 4))));
COMPAT_FN_DECL(int MLOG_LogLineBasic,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, ...)
	__attribute__ ((format (printf, 7, 8))));
#else
COMPAT_FN_DECL(int MLOG_LogLineDebug,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogLineErr,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogLineInfo,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogLineWarn,
	(MLOG *mlog_ptr, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogLine,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, const char *in_format, ...));
COMPAT_FN_DECL(int MLOG_LogLineBasic,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, ...));
#endif /* #ifdef __GNUC__ */
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for the variable-argument line logging functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MLOG_LogLineDebugVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogLineErrVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogLineInfoVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogLineWarnVA,
	(MLOG *mlog_ptr, const char *in_format, va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogLineVA,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, const char *in_format,
	va_list arg_list));
COMPAT_FN_DECL(int MLOG_LogLineBasicVA,
	(MLOG *mlog_ptr, MLOG_PRIORITY log_priority, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, const char *in_format, va_list arg_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for open and close functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(MLOG *MLOG_FOpenDefault, (const char *file_name));
COMPAT_FN_DECL(MLOG *MLOG_FOpenDefaultAppend, (const char *file_name));
COMPAT_FN_DECL(int MLOG_OpenLog, (const char *file_name,
	const char *log_format, const char *user_string, MLOG_FLAG flags,
	MLOG **mlog_ptr, char *error_text));
COMPAT_FN_DECL(MLOG *MLOG_FOpenDefaultTid, (const char *file_name));
COMPAT_FN_DECL(MLOG *MLOG_FOpenDefaultTidAppend, (const char *file_name));
COMPAT_FN_DECL(int MLOG_OpenBasic, (const char *file_name, FILE *file_ptr,
	const char *log_format, const char *user_string, MLOG_FLAG flags,
	MLOG_PRIORITY mfile_mask, MLOG_PRIORITY file_mask,
	MLOG_PRIORITY syslog_mask, unsigned int initial_alloc,
	unsigned int added_alloc, MLOG **mlog_ptr, char *error_text));
COMPAT_FN_DECL(int MLOG_Close, (MLOG *mlog_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for the synchronization functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MLOG_Sync,
	(MLOG *mlog_ptr, char *error_text));
COMPAT_FN_DECL(int MLOG_SyncMFILE,
	(MLOG *mlog_ptr, char *error_text));
COMPAT_FN_DECL(int MLOG_SyncMFILEBasic,
	(MLOG *mlog_ptr, int async_flag, char *error_text));
COMPAT_FN_DECL(int MLOG_SyncFILE,
	(MLOG *mlog_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for check functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MLOG_Check,               (const MLOG *mlog_ptr,
	char *error_text));
COMPAT_FN_DECL(int MLOG_CheckFlags,          (MLOG_FLAG flags,
	char *error_text));
COMPAT_FN_DECL(int MLOG_CheckPriority,       (MLOG_PRIORITY priority_mask,
	char *error_text));
COMPAT_FN_DECL(int MLOG_CheckPriorityMFile,  (MLOG_PRIORITY mfile_mask,
	char *error_text));
COMPAT_FN_DECL(int MLOG_CheckPriorityFile,   (MLOG_PRIORITY file_mask,
	char *error_text));
COMPAT_FN_DECL(int MLOG_CheckPrioritySyslog, (MLOG_PRIORITY syslog_mask,
	char *error_text));
COMPAT_FN_DECL(int MLOG_CheckLogFormat,      (const char *log_format,
	char *error_text));
COMPAT_FN_DECL(int MLOG_CheckUserString,     (const char *log_format,
	const char *user_string, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for MLOG structure locking functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MLOG_Lock,    (MLOG *mlog_ptr, char *error_text));
COMPAT_FN_DECL(int MLOG_TryLock, (MLOG *mlog_ptr, char *error_text));
COMPAT_FN_DECL(int MLOG_Unlock,  (MLOG *mlog_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for get functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int            MLOG_GetMayLog,         (MLOG *mlog_ptr));
COMPAT_FN_DECL(int            MLOG_GetPDebug,         (MLOG *mlog_ptr));
COMPAT_FN_DECL(MLOG_FLAG      MLOG_GetFlags,          (MLOG *mlog_ptr));
COMPAT_FN_DECL(int            MLOG_GetFlagMFile,      (MLOG *mlog_ptr));
COMPAT_FN_DECL(int            MLOG_GetFlagFile,       (MLOG *mlog_ptr));
COMPAT_FN_DECL(int            MLOG_GetFlagSyslog,     (MLOG *mlog_ptr));
COMPAT_FN_DECL(MLOG_PRIORITY  MLOG_GetPriorityMFile,  (MLOG *mlog_ptr));
COMPAT_FN_DECL(MLOG_PRIORITY  MLOG_GetPriorityFile,   (MLOG *mlog_ptr));
COMPAT_FN_DECL(MLOG_PRIORITY  MLOG_GetPrioritySyslog, (MLOG *mlog_ptr));
COMPAT_FN_DECL(char          *MLOG_GetFileName,       (MLOG *mlog_ptr));
COMPAT_FN_DECL(char          *MLOG_GetLogFormat,      (MLOG *mlog_ptr));
COMPAT_FN_DECL(char          *MLOG_GetUserString,     (MLOG *mlog_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for set functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MLOG_SetMayLog,         (MLOG *mlog_ptr, int may_log_flag));
COMPAT_FN_DECL(int MLOG_SetPDebug,         (MLOG *mlog_ptr, int pdebug_flag));
COMPAT_FN_DECL(int MLOG_SetFlags,          (MLOG *mlog_ptr,
	MLOG_FLAG flags, char *error_text));
COMPAT_FN_DECL(int MLOG_SetFlagMFile,      (MLOG *mlog_ptr,
	int flag, char *error_text));
COMPAT_FN_DECL(int MLOG_SetFlagFile,       (MLOG *mlog_ptr,
	int flag, char *error_text));
COMPAT_FN_DECL(int MLOG_SetFlagSyslog,     (MLOG *mlog_ptr,
	int flag, char *error_text));
COMPAT_FN_DECL(int MLOG_SetPriorityMFile,  (MLOG *mlog_ptr,
	MLOG_PRIORITY mfile_mask, char *error_text));
COMPAT_FN_DECL(int MLOG_SetPriorityFile,   (MLOG *mlog_ptr,
	MLOG_PRIORITY file_mask, char *error_text));
COMPAT_FN_DECL(int MLOG_SetPrioritySyslog, (MLOG *mlog_ptr,
	MLOG_PRIORITY syslog_mask, char *error_text));
COMPAT_FN_DECL(int MLOG_SetLogFormat,      (MLOG *mlog_ptr,
	const char *in_log_format, const char *in_user_string, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for miscellaneous logging functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void MLOG_DoSepStart,      (MLOG *mlog_ptr));
COMPAT_FN_DECL(void MLOG_DoSepEnd,        (MLOG *mlog_ptr));
COMPAT_FN_DECL(void MLOG_DoSepHyphen,     (MLOG *mlog_ptr));
COMPAT_FN_DECL(void MLOG_DoSepEqual,      (MLOG *mlog_ptr));
COMPAT_FN_DECL(void MLOG_DoSepStar,       (MLOG *mlog_ptr));
COMPAT_FN_DECL(void MLOG_DoSepChar,       (MLOG *mlog_ptr, int log_char));
COMPAT_FN_DECL(void MLOG_DoSepCharBasic,	(MLOG *mlog_ptr,
	unsigned int sep_length, int log_char));
COMPAT_FN_DECL(void MLOG_DoSepString,     (MLOG *mlog_ptr,
	const char *log_string));
COMPAT_FN_DECL(void MLOG_DoExecTime,      (MLOG *mlog_ptr,
	const struct timeval *start_time, const struct timeval *end_time,
	const struct timeval *overhead_end_time));
COMPAT_FN_DECL(void MLOG_DoRUsage,        (MLOG *mlog_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for miscellaneous supporting functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void MLOG_CompleteOutput, (MLOG *mlog_ptr));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__MLOG_H__h */

