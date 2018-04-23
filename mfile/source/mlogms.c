/* *********************************************************************** */
/* *********************************************************************** */
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logs formatted message text to a memory-mapped file.

	Revision History	:	1994-10-31 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <limits.h>
#include <memory.h>
#include <string.h>

#include "mfilei.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static int MFILE_LogMessageFlagMFILE  = MFILE_TRUE;

static int MFILE_LogMessageFlagFILE   = MFILE_TRUE;

static int MFILE_LogMessageFlagSYSLOG = MFILE_TRUE;

static int MFILE_LogMessageFlagGMT    = MFILE_FALSE;

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_LogMessage

   SYNOPSIS    :  MFILE_LogMessage(timeval_ptr, log_priority, mfile_ptr,
							file_ptr, syslog_flag, in_format, ...);

						struct timeval *timeval_ptr;

						int             log_priority;

						MFILE          *mfile_ptr;

						FILE           *file_ptr;

						int             syslog_flag;

						const char     *in_format;

   DESCRIPTION :  This function logs a time-stamped message to the facilities
						specified in the parameter list.

						The logged message has the following format:

<|@|>``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``.``uuuuuu``:``priority``:``Your message here``

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``timeval_ptr`` points to a structure of type
						''timeval'' which contains the time-stamp of the message
						to be logged.

						(-) If ``timeval_ptr`` is a ''NULL'' pointer, the current
						system time will be used to time-stamp the message.

						(-) If GMT/UTC time logging has been set by a call to
						``MFILE_SetLogMessageFlagGMT``, then the time will be
						emitted by this function as GMT time. Otherwise, the
						time will be emitted as local time.

						(.) ``log_priority`` specifies the priority with which the
						message is to be posted. It should be equal to one of the
						following symbolic constants:

						(..) ''LOG_EMERG''

						(..) ''LOG_ALERT''

						(..) ''LOG_CRIT''

						(..) ''LOG_ERR''

						(..) ''LOG_WARNING''

						(..) ''LOG_NOTICE''

						(..) ''LOG_INFO''

						(..) ''LOG_DEBUG''

						(-) If the ``log_priority`` is not one of the above, the
						message will be logged with ''LOG_INFO''.

						(.) ``mfile_ptr`` points to a structure of type ''MFILE''
						which specifies the memory-mapped file to which the message
						is to be logged.

						(-) If ``mfile_ptr`` is a ''NULL'' pointer, or if
						memory-mapped file logging has been turned off by a call
						to ``MFILE_SetLogMessageFlagMFILE``, the message will not
						be logged to a memory-mapped file.

						(.) ``file_ptr`` points to a structure of type ''FILE''
						which specifies the C level-two I/O device to which the
						message is to be logged.

						(-) If ``file_ptr`` is a ''NULL'' pointer, or if ''FILE''
						logging has been turned off by a call to
						``MFILE_SetLogMessageFlagFILE``, the message will not be
						logged to a C level-two I/O device.

						(-) ``Nota Bene``: This parameter is most often set to
						``stderr``

						(.) ``syslog_flag`` specifies whether the message is to
						posted to the Unix system facility ``syslog``. It should
						take on the value of the following manifest constants:

						(..) ''MFILE_TRUE''

						(..) ''MFILE_FALSE''

						(-) Messages are posted to the ``syslog`` facility only on
						those operating systems which possess said facility.

						(-) Note that if ''syslog'' logging has been turned off by
						a call to ``MFILE_SetLogMessageFlagSYSLOG``, the message
						will not be logged to the Unix system ``syslog`` facility.

						(.) ``in_format`` is a ``printf``-style format string
						which specifies how subsequent parameters are to be
						interpreted.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  Because this function uses ``vsprintf`` to perform its
						work, the exact nature of the format specifiers accepted
						and their semantics may differ depending on the capability
						and whimsy of the compiler implementors.

   SEE ALSO    :  MFILE_LogMessageContext

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_LogMessage
						Memory-mapped File Functions:Logging Functions:MFILE_LogMessage
						MFILE Functions:MFILE_LogMessage

	PUBLISH XREF:	MFILE_LogMessage

	PUBLISH NAME:	MFILE_LogMessage

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
void MFILE_LogMessage(struct timeval *timeval_ptr, int log_priority,
	MFILE *mfile_ptr, FILE *file_ptr, int syslog_flag, const char *in_format,
	...)
#else
void MFILE_LogMessage(timeval_ptr, log_priority, mfile_ptr, file_ptr,
	syslog_flag, in_format, va_alist)
struct timeval *timeval_ptr;
int             log_priority;
MFILE          *mfile_ptr;
FILE           *file_ptr;
int             syslog_flag;
const char     *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	unsigned int  char_count;
	char          message_header[SDTIF_FMT_TIME_LEN_TIMEVAL + 256];
	va_list       argument_ptr;
#ifndef MFILE_MMAP_NON_NATIVE
	char         *tmp_format;
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

	if (((mfile_ptr != NULL) && (MFILE_LogMessageFlagMFILE == MFILE_TRUE)) ||
		((file_ptr != NULL) && (MFILE_LogMessageFlagFILE == MFILE_TRUE)) ||
		(syslog_flag && (MFILE_LogMessageFlagSYSLOG == MFILE_TRUE))) {
		if (MFILE_LogMessageFlagGMT == MFILE_TRUE)
			SDTIF_Format_timeval_GMT(timeval_ptr, message_header);
		else
			SDTIF_Format_timeval(timeval_ptr, message_header);
		message_header[10] = ':';
		switch (log_priority) {
			case LOG_EMERG		:
				strcat(message_header, ":EMERGENCY    :");
				break;
			case LOG_ALERT		:
				strcat(message_header, ":ALERT        :");
				break;
			case LOG_CRIT		:
				strcat(message_header, ":CRITICAL     :");
				break;
			case LOG_ERR		:
				strcat(message_header, ":ERROR        :");
				break;
			case LOG_WARNING	:
				strcat(message_header, ":WARNING      :");
				break;
			case LOG_NOTICE	:
				strcat(message_header, ":NOTICE       :");
				break;
			case LOG_INFO		:
				strcat(message_header, ":INFORMATIONAL:");
				break;
			case LOG_DEBUG		:
				strcat(message_header, ":DEBUGGING    :");
				break;
			default				:
				log_priority = LOG_INFO;
				strcat(message_header, ":*************:");
				break;
		}
		if ((MFILE_LogMessageFlagMFILE == MFILE_TRUE) &&
			(MFILE_LogEnsureSpace(mfile_ptr) == MFILE_TRUE)) {
			mputs(message_header, mfile_ptr);
#ifndef NO_STDARGS
			va_start(argument_ptr, in_format);
#else
			va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */
#ifndef MFILE_MMAP_NON_NATIVE
			vsprintf(((char *) mfile_ptr->mmap_ptr) +
				mfile_ptr->current_offset, in_format, argument_ptr);
			/* ********************************************************	*/
			/* ********************************************************	*/
			/* 	We take the length of the formatted output string		*/
			/* below because we can't depend upon the return value from	*/
			/* 'vsprintf()' --- pre-ANSI compilers returned a pointer	*/
			/* the buffer rather than the number of characters minus		*/
			/* the terminating ASCII zero.										*/
			/* ********************************************************	*/
			char_count = strlen(((char *) mfile_ptr->mmap_ptr) +
				mfile_ptr->current_offset);
			/* ********************************************************	*/
#else
			char_count = vfprintf(mfile_ptr->file_ptr, in_format, argument_ptr);
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */
			va_end(argument_ptr);
			if (char_count > 0) {
				mfile_ptr->mfile_flags    |= MFILE_FLAG_WRITTEN;
				mfile_ptr->current_offset += char_count;
				mfile_ptr->file_size       =
					(mfile_ptr->current_offset > mfile_ptr->file_size) ?
					mfile_ptr->current_offset : mfile_ptr->file_size;
			}
		}
		if ((file_ptr != NULL) && (MFILE_LogMessageFlagFILE == MFILE_TRUE)) {
			fputs(message_header, file_ptr);
#ifndef NO_STDARGS
			va_start(argument_ptr, in_format);
#else
			va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */
			vfprintf(file_ptr, in_format, argument_ptr);
			va_end(argument_ptr);
		}
#ifndef MFILE_MMAP_NON_NATIVE
		if (syslog_flag && (MFILE_LogMessageFlagSYSLOG == MFILE_TRUE)) {
			if ((tmp_format = ((char *) malloc((strlen(message_header) +
				strlen(in_format) + 1) * sizeof(char)))) != NULL) {
				strcat(strcpy(tmp_format, message_header), in_format);
# ifndef NO_STDARGS
				va_start(argument_ptr, in_format);
# else
				va_start(argument_ptr);
# endif /* #ifndef NO_STDARGS */
				vsyslog(log_priority, tmp_format, argument_ptr);
				va_end(argument_ptr);
				free(tmp_format);
			}
		}
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */
	}
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepStartLog

   SYNOPSIS    :	void MFILE_LogSepStartLog(mfile_ptr, file_ptr);

						MFILE *mfile_ptr;

						FILE  *file_ptr;

   DESCRIPTION :	Emits a log message indicating the beginning of the log
						file to the logging destinations specified by
						``mfile_ptr`` and ``file_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mfile_ptr`` points to a structure of type ''MFILE''
						which specifies the memory-mapped file to which logging
						is to be performed by this function.

						(-) If ``mfile_ptr`` is a ''NULL'' pointer, or if
						memory-mapped file logging has been turned off by a call
						to ``MFILE_SetLogMessageFlagMFILE``, no logging will
						performed to the memory-mapped file.

						(.) ``file_ptr`` points to a structure of type ''FILE''
						which specifies the C level-two I/O device to which logging
						is to be performed.

						(-) If ``file_ptr`` is a ''NULL'' pointer, or if ''FILE''
						logging has been turned off by a call to
						``MFILE_SetLogMessageFlagFILE``, no logging will be
						performed to the C level-two I/O device.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message indicating the ending of the log
						file with the function ``MFILE_LogSepEndLog``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepEndLog
						MFILE_LogSepStartLogContext

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepStartLog
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepStartLog
						MFILE Functions:MFILE_LogSepStartLog

   PUBLISH XREF:	MFILE_LogSepStartLog

   PUBLISH NAME:	MFILE_LogSepStartLog

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepStartLog(MFILE *mfile_ptr, FILE *file_ptr)
#else
void MFILE_LogSepStartLog(mfile_ptr, file_ptr)
MFILE *mfile_ptr;
FILE  *file_ptr;
#endif /* #ifndef NARGS */
{
	MFILE_LOG_CONTEXT log_context;

	MFILE_InitLogContext(&log_context);

	log_context.mfile_ptr  = mfile_ptr;
	log_context.file_ptr   = file_ptr;
	log_context.mfile_flag = MFILE_LogMessageFlagMFILE;
	log_context.file_flag  = MFILE_LogMessageFlagFILE;

	MFILE_LogSepStartLogContext(&log_context);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepEndLog

   SYNOPSIS    :	void MFILE_LogSepEndLog(mfile_ptr, file_ptr);

						MFILE *mfile_ptr;

						FILE  *file_ptr;

   DESCRIPTION :	Emits a log message indicating the ending of the log
						file to the logging destinations specified by
						``mfile_ptr`` and ``file_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mfile_ptr`` points to a structure of type ''MFILE''
						which specifies the memory-mapped file to which logging
						is to be performed by this function.

						(-) If ``mfile_ptr`` is a ''NULL'' pointer, or if
						memory-mapped file logging has been turned off by a call
						to ``MFILE_SetLogMessageFlagMFILE``, no logging will
						performed to the memory-mapped file.

						(.) ``file_ptr`` points to a structure of type ''FILE''
						which specifies the C level-two I/O device to which logging
						is to be performed.

						(-) If ``file_ptr`` is a ''NULL'' pointer, or if ''FILE''
						logging has been turned off by a call to
						``MFILE_SetLogMessageFlagFILE``, no logging will be
						performed to the C level-two I/O device.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message indicating the beginning of the
						log file with the function ``MFILE_LogSepStartLog``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepStartLog
						MFILE_LogSepEndLogContext

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepEndLog
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepEndLog
						MFILE Functions:MFILE_LogSepEndLog

   PUBLISH XREF:	MFILE_LogSepEndLog

   PUBLISH NAME:	MFILE_LogSepEndLog

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepEndLog(MFILE *mfile_ptr, FILE *file_ptr)
#else
void MFILE_LogSepEndLog(mfile_ptr, file_ptr)
MFILE *mfile_ptr;
FILE  *file_ptr;
#endif /* #ifndef NARGS */
{
	MFILE_LOG_CONTEXT log_context;

	MFILE_InitLogContext(&log_context);

	log_context.mfile_ptr  = mfile_ptr;
	log_context.file_ptr   = file_ptr;
	log_context.mfile_flag = MFILE_LogMessageFlagMFILE;
	log_context.file_flag  = MFILE_LogMessageFlagFILE;

	MFILE_LogSepEndLogContext(&log_context);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepHyphenChar

   SYNOPSIS    :	void MFILE_LogSepHyphenChar(mfile_ptr, file_ptr);

						MFILE *mfile_ptr;

						FILE  *file_ptr;

   DESCRIPTION :	Emits a log message containing a string of hyphen characters
						(''-'') to the logging destinations specified by
						``mfile_ptr`` and ``file_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mfile_ptr`` points to a structure of type ''MFILE''
						which specifies the memory-mapped file to which logging
						is to be performed by this function.

						(-) If ``mfile_ptr`` is a ''NULL'' pointer, or if
						memory-mapped file logging has been turned off by a call
						to ``MFILE_SetLogMessageFlagMFILE``, no logging will
						performed to the memory-mapped file.

						(.) ``file_ptr`` points to a structure of type ''FILE''
						which specifies the C level-two I/O device to which logging
						is to be performed.

						(-) If ``file_ptr`` is a ''NULL'' pointer, or if ''FILE''
						logging has been turned off by a call to
						``MFILE_SetLogMessageFlagFILE``, no logging will be
						performed to the C level-two I/O device.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string of an
						arbitrary characters with the function ``MFILE_LogSepChar``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepEqualChar
						MFILE_LogSepChar
						MFILE_LogSepHyphenCharContext

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepHyphenChar
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepHyphenChar
						MFILE Functions:MFILE_LogSepHyphenChar

   PUBLISH XREF:	MFILE_LogSepHyphenChar

   PUBLISH NAME:	MFILE_LogSepHyphenChar

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepHyphenChar(MFILE *mfile_ptr, FILE *file_ptr)
#else
void MFILE_LogSepHyphenChar(mfile_ptr, file_ptr)
MFILE *mfile_ptr;
FILE  *file_ptr;
#endif /* #ifndef NARGS */
{
	MFILE_LogSepChar(mfile_ptr, file_ptr, '-');
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepEqualChar

   SYNOPSIS    :	void MFILE_LogSepEqualChar(mfile_ptr, file_ptr);

						MFILE *mfile_ptr;

						FILE  *file_ptr;

   DESCRIPTION :	Emits a log message containing a string of equal-sign
						characters (''='') to the logging destinations specified by
						``mfile_ptr`` and ``file_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mfile_ptr`` points to a structure of type ''MFILE''
						which specifies the memory-mapped file to which logging
						is to be performed by this function.

						(-) If ``mfile_ptr`` is a ''NULL'' pointer, or if
						memory-mapped file logging has been turned off by a call
						to ``MFILE_SetLogMessageFlagMFILE``, no logging will
						performed to the memory-mapped file.

						(.) ``file_ptr`` points to a structure of type ''FILE''
						which specifies the C level-two I/O device to which logging
						is to be performed.

						(-) If ``file_ptr`` is a ''NULL'' pointer, or if ''FILE''
						logging has been turned off by a call to
						``MFILE_SetLogMessageFlagFILE``, no logging will be
						performed to the C level-two I/O device.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string of an
						arbitrary characters with the function ``MFILE_LogSepChar``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepHyphenChar
						MFILE_LogSepChar
						MFILE_LogSepEqualCharContext

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepEqualChar
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepEqualChar
						MFILE Functions:MFILE_LogSepEqualChar

   PUBLISH XREF:	MFILE_LogSepEqualChar

   PUBLISH NAME:	MFILE_LogSepEqualChar

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepEqualChar(MFILE *mfile_ptr, FILE *file_ptr)
#else
void MFILE_LogSepEqualChar(mfile_ptr, file_ptr)
MFILE *mfile_ptr;
FILE  *file_ptr;
#endif /* #ifndef NARGS */
{
	MFILE_LogSepChar(mfile_ptr, file_ptr, '=');
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepChar

   SYNOPSIS    :	void MFILE_LogSepChar(mfile_ptr, file_ptr, log_char);

						MFILE *mfile_ptr;

						FILE  *file_ptr;

						int    log_char;

   DESCRIPTION :	Emits a log message containing a string of ``log_char``
						characters to the logging destinations specified by
						``mfile_ptr`` and ``file_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mfile_ptr`` points to a structure of type ''MFILE''
						which specifies the memory-mapped file to which logging
						is to be performed by this function.

						(-) If ``mfile_ptr`` is a ''NULL'' pointer, or if
						memory-mapped file logging has been turned off by a call
						to ``MFILE_SetLogMessageFlagMFILE``, no logging will
						performed to the memory-mapped file.

						(.) ``file_ptr`` points to a structure of type ''FILE''
						which specifies the C level-two I/O device to which logging
						is to be performed.

						(-) If ``file_ptr`` is a ''NULL'' pointer, or if ''FILE''
						logging has been turned off by a call to
						``MFILE_SetLogMessageFlagFILE``, no logging will be
						performed to the C level-two I/O device.

						(.) ``log_char`` is the character to be used in logging.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string with the
						function ``MFILE_LogSepString``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepString
						MFILE_LogSepCharContext

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepChar
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepChar
						MFILE Functions:MFILE_LogSepChar

   PUBLISH XREF:	MFILE_LogSepChar

   PUBLISH NAME:	MFILE_LogSepChar

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepChar(MFILE *mfile_ptr, FILE *file_ptr, int log_char)
#else
void MFILE_LogSepChar(mfile_ptr, file_ptr, log_char)
MFILE *mfile_ptr;
FILE  *file_ptr;
int    log_char;
#endif /* #ifndef NARGS */
{
	MFILE_LOG_CONTEXT log_context;

	MFILE_InitLogContext(&log_context);

	log_context.mfile_ptr  = mfile_ptr;
	log_context.file_ptr   = file_ptr;
	log_context.mfile_flag = MFILE_LogMessageFlagMFILE;
	log_context.file_flag  = MFILE_LogMessageFlagFILE;

	MFILE_LogSepCharContext(&log_context, log_char);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepString

   SYNOPSIS    :	void MFILE_LogSepString(mfile_ptr, file_ptr, log_string);

						MFILE      *mfile_ptr;

						FILE       *file_ptr;

						const char *log_string;

   DESCRIPTION :	Emits a log message containing the string of ``log_string``
						to the logging destinations specified by
						``mfile_ptr`` and ``file_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``mfile_ptr`` points to a structure of type ''MFILE''
						which specifies the memory-mapped file to which logging
						is to be performed by this function.

						(-) If ``mfile_ptr`` is a ''NULL'' pointer, or if
						memory-mapped file logging has been turned off by a call
						to ``MFILE_SetLogMessageFlagMFILE``, no logging will
						performed to the memory-mapped file.

						(.) ``file_ptr`` points to a structure of type ''FILE''
						which specifies the C level-two I/O device to which logging
						is to be performed.

						(-) If ``file_ptr`` is a ''NULL'' pointer, or if ''FILE''
						logging has been turned off by a call to
						``MFILE_SetLogMessageFlagFILE``, no logging will be
						performed to the C level-two I/O device.

						(.) ``log_string`` is the string to be used in logging.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string of an
						characters with the function ``MFILE_LogSepChar``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepChar
						MFILE_LogSepStringContext

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepString
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepString
						MFILE Functions:MFILE_LogSepString

   PUBLISH XREF:	MFILE_LogSepString

   PUBLISH NAME:	MFILE_LogSepString

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepString(MFILE *mfile_ptr, FILE *file_ptr,
	const char *log_string)
#else
void MFILE_LogSepString(mfile_ptr, file_ptr, log_string)
MFILE      *mfile_ptr;
FILE       *file_ptr;
const char *log_string;
#endif /* #ifndef NARGS */
{
	MFILE_LOG_CONTEXT log_context;

	MFILE_InitLogContext(&log_context);

	log_context.mfile_ptr  = mfile_ptr;
	log_context.file_ptr   = file_ptr;
	log_context.mfile_flag = MFILE_LogMessageFlagMFILE;
	log_context.file_flag  = MFILE_LogMessageFlagFILE;

	MFILE_LogSepStringContext(&log_context, log_string);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_GetLogMessageFlagFILE

   SYNOPSIS    :  return_flag_value = MFILE_GetLogMessageFlagFILE();

						int return_flag_value;

   DESCRIPTION :  Returns the current log message action flag value for
						C language level-two I/O devices.

   PARAMETERS  :  None.

   RETURNS     :  The current log message action flag value for C language
						level-two I/O devices as one of the following manifest
						constants:

						(.) ''MFILE_TRUE'' if the flag is set. This setting indicates
						that calls to the function ``MFILE_LogMessage`` with a
						non-NULL ``file_ptr`` parameter will result in the log
						text being emitted to the C language level-two I/O device
						specified by that parameter.

						(.) ''MFILE_FALSE'' if the flag is not set. This setting
						indicates that calls to the function ``MFILE_LogMessage``
						will not emit log text to the C language level-two I/O
						device specified by the ``file_ptr`` parameter.

   NOTES       :  The default setting for this flag is ''MFILE_TRUE''.

						You can change the setting of the flag by calling the
						function ``MFILE_SetLogMessageFlagFILE``.

   CAVEATS     :

   SEE ALSO    :  MFILE_SetLogMessageFlagFILE
						MFILE_GetLogMessageFlagMFILE
						MFILE_GetLogMessageFlagSYSLOG
						MFILE_GetLogMessageFlagGMT
						MFILE_LogMessage

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_GetLogMessageFlagFILE
						Memory-mapped File Functions:Logging Functions:MFILE_GetLogMessageFlagFILE
						MFILE Functions:MFILE_GetLogMessageFlagFILE

	PUBLISH XREF:	MFILE_GetLogMessageFlagFILE

	PUBLISH NAME:	MFILE_GetLogMessageFlagFILE

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MFILE_GetLogMessageFlagFILE(void)
#else
int MFILE_GetLogMessageFlagFILE()
#endif /* #ifndef NARGS */
{
	return(MFILE_LogMessageFlagFILE);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_SetLogMessageFlagFILE

   SYNOPSIS    :  return_flag_value =
							MFILE_SetLogMessageFlagFILE(new_flag_value);

						int return_flag_value;

						int new_flag_value;

   DESCRIPTION :  Specifies the log message action flag value to be used for
						C language level-two I/O devices.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``new_flag_value`` specifies the new log message action
						flag to be used for C language level-two I/O devices.

						(-) If ``new_flag_value`` is non-zero, then subsequent calls
						to the function ``MFILE_LogMessage`` with a non-NULL
						``file_ptr`` parameter will result in the log text being
						emitted to the C language level-two I/O device specified by
						that parameter.

						(-) If ``new_flag_value`` is zero, then subsequent calls to
						the function ``MFILE_LogMessage`` will not emit log
						text to the C language level-two I/O device specified by
						the ``file_ptr`` parameter.

   RETURNS     :  The previous log message action flag value for C language
						level-two I/O devices files.

   NOTES       :  The default setting for this flag is ''MFILE_TRUE''.

						You can non-destructively determine the setting of the
						flag by calling the function
						``MFILE_GetLogMessageFlagFILE``.

   CAVEATS     :  

   SEE ALSO    :  MFILE_GetLogMessageFlagFILE
						MFILE_SetLogMessageFlagMFILE
						MFILE_SetLogMessageFlagSYSLOG
						MFILE_SetLogMessageFlagGMT
						MFILE_LogMessage

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_SetLogMessageFlagFILE
						Memory-mapped File Functions:Logging Functions:MFILE_GetLogMessageFlagFILE
						MFILE Functions:MFILE_GetLogMessageFlagFILE

	PUBLISH XREF:	MFILE_SetLogMessageFlagFILE

	PUBLISH NAME:	MFILE_SetLogMessageFlagFILE

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MFILE_SetLogMessageFlagFILE(int new_flag_value)
#else
int MFILE_SetLogMessageFlagFILE(new_flag_value)
int new_flag_value;
#endif /* #ifndef NARGS */
{
	int old_flag_value;

	old_flag_value           = MFILE_LogMessageFlagFILE;
	MFILE_LogMessageFlagFILE = (new_flag_value) ? MFILE_TRUE : MFILE_FALSE;

	return(old_flag_value);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_GetLogMessageFlagMFILE

   SYNOPSIS    :  return_flag_value = MFILE_GetLogMessageFlagMFILE();

						int return_flag_value;

   DESCRIPTION :  Returns the current log message action flag value for
						memory-mapped files.

   PARAMETERS  :  None.

   RETURNS     :  The current log message action flag value for memory-mapped
						files as one of the following manifest constants:

						(.) ''MFILE_TRUE'' if the flag is set. This setting indicates
						that calls to the function ``MFILE_LogMessage`` with a
						non-NULL ``mfile_ptr`` parameter will result in the log
						text being emitted to the memory-mapped file specified by
						that parameter.

						(.) ''MFILE_FALSE'' if the flag is not set. This setting
						indicates that calls to the function ``MFILE_LogMessage``
						will not emit log text to the memory-mapped file specified
						by the ``mfile_ptr`` parameter.

   NOTES       :  The default setting for this flag is ''MFILE_TRUE''.

						You can change the setting of the flag by calling the
						function ``MFILE_SetLogMessageFlagMFILE``.

   CAVEATS     :  

   SEE ALSO    :  MFILE_SetLogMessageFlagMFILE
						MFILE_GetLogMessageFlagFILE
						MFILE_GetLogMessageFlagSYSLOG
						MFILE_GetLogMessageFlagGMT
						MFILE_LogMessage

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_GetLogMessageFlagMFILE
						Memory-mapped File Functions:Logging Functions:MFILE_GetLogMessageFlagFILE
						MFILE Functions:MFILE_GetLogMessageFlagFILE

	PUBLISH XREF:	MFILE_GetLogMessageFlagMFILE

	PUBLISH NAME:	MFILE_GetLogMessageFlagMFILE

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MFILE_GetLogMessageFlagMFILE(void)
#else
int MFILE_GetLogMessageFlagMFILE()
#endif /* #ifndef NARGS */
{
	return(MFILE_LogMessageFlagMFILE);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_SetLogMessageFlagMFILE

   SYNOPSIS    :  return_flag_value =
							MFILE_SetLogMessageFlagMFILE(new_flag_value);

						int return_flag_value;

						int new_flag_value;

   DESCRIPTION :  Specifies the log message action flag value to be used for
						memory-mapped files.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``new_flag_value`` specifies the new log message action
						flag to be used for memory-mapped files.

						(-) If ``new_flag_value`` is non-zero, then subsequent calls
						to the function ``MFILE_LogMessage`` with a non-NULL
						``mfile_ptr`` parameter will result in the log text being
						emitted to the memory-mapped file specified by that
						parameter.

						(-) If ``new_flag_value`` is zero, then subsequent calls to
						the function ``MFILE_LogMessage`` will not emit log
						text to the memory-mapped file specified by the
						``mfile_ptr`` parameter.

   RETURNS     :  The previous log message action flag value for memory-mapped
						files.

   NOTES       :  The default setting for this flag is ''MFILE_TRUE''.

						You can non-destructively determine the setting of the
						flag by calling the function
						``MFILE_GetLogMessageFlagMFILE``.

   CAVEATS     :  

   SEE ALSO    :  MFILE_GetLogMessageFlagMFILE
						MFILE_SetLogMessageFlagFILE
						MFILE_SetLogMessageFlagSYSLOG
						MFILE_SetLogMessageFlagGMT
						MFILE_LogMessage

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_SetLogMessageFlagMFILE
						Memory-mapped File Functions:Logging Functions:MFILE_GetLogMessageFlagFILE
						MFILE Functions:MFILE_GetLogMessageFlagFILE

	PUBLISH XREF:	MFILE_SetLogMessageFlagMFILE

	PUBLISH NAME:	MFILE_SetLogMessageFlagMFILE

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MFILE_SetLogMessageFlagMFILE(int new_flag_value)
#else
int MFILE_SetLogMessageFlagMFILE(new_flag_value)
int new_flag_value;
#endif /* #ifndef NARGS */
{
	int old_flag_value;

	old_flag_value            = MFILE_LogMessageFlagMFILE;
	MFILE_LogMessageFlagMFILE = (new_flag_value) ? MFILE_TRUE : MFILE_FALSE;

	return(old_flag_value);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_GetLogMessageFlagSYSLOG

   SYNOPSIS    :  return_flag_value = MFILE_GetLogMessageFlagSYSLOG();

						int return_flag_value;

   DESCRIPTION :  Returns the current log message action flag value for
						the Unix system ``syslog`` facility.

   PARAMETERS  :  None.

   RETURNS     :  The current log message action flag value for the Unix
						system ``syslog`` facility as one of the following manifest
						constants:

						(.) ''MFILE_TRUE'' if the flag is set. This setting indicates
						that calls to the function ``MFILE_LogMessage`` with a
						non-zero ``syslog_flag`` parameter will result in the log
						text being emitted to the the Unix system ``syslog``
						facility.

						(.) ''MFILE_FALSE'' if the flag is not set. This setting
						indicates that calls to the function ``MFILE_LogMessage``
						will not emit log text to the Unix system ``syslog``
						facility.

   NOTES       :  The default setting for this flag is ''MFILE_TRUE''.

						You can change the setting of the flag by calling the
						function ``MFILE_SetLogMessageFlagSYSLOG``.

   CAVEATS     :  

   SEE ALSO    :  MFILE_SetLogMessageFlagSYSLOG
						MFILE_GetLogMessageFlagFILE
						MFILE_GetLogMessageFlagMFILE
						MFILE_GetLogMessageFlagGMT
						MFILE_LogMessage

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_GetLogMessageFlagSYSLOG
						Memory-mapped File Functions:Logging Functions:MFILE_GetLogMessageFlagFILE
						MFILE Functions:MFILE_GetLogMessageFlagFILE

	PUBLISH XREF:	MFILE_GetLogMessageFlagSYSLOG

	PUBLISH NAME:	MFILE_GetLogMessageFlagSYSLOG

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MFILE_GetLogMessageFlagSYSLOG(void)
#else
int MFILE_GetLogMessageFlagSYSLOG()
#endif /* #ifndef NARGS */
{
	return(MFILE_LogMessageFlagSYSLOG);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_SetLogMessageFlagSYSLOG

   SYNOPSIS    :  return_flag_value =
							MFILE_SetLogMessageFlagSYSLOG(new_flag_value);

						int return_flag_value;

						int new_flag_value;

   DESCRIPTION :  Specifies the log message action flag value to be used for
						the Unix system ``syslog`` facility.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``new_flag_value`` specifies the new log message action
						flag to be used for the Unix system ``syslog`` facility.

						(-) If ``new_flag_value`` is non-zero, then subsequent calls
						to the function ``MFILE_LogMessage`` with a non-zero
						``syslog_flag`` parameter will result in the log text being
						emitted to the Unix system ``syslog`` facility.

						(-) If ``new_flag_value`` is zero, then subsequent calls to
						the function ``MFILE_LogMessage`` will not emit log
						text to the Unix system ``syslog`` facility.

   RETURNS     :  The previous log message action flag value for the Unix
						system ``syslog`` facility.

   NOTES       :  The default setting for this flag is ''MFILE_TRUE''.

						You can non-destructively determine the setting of the
						flag by calling the function
						``MFILE_GetLogMessageFlagSYSLOG``.

   CAVEATS     :  

   SEE ALSO    :  MFILE_GetLogMessageFlagSYSLOG
						MFILE_SetLogMessageFlagFILE
						MFILE_SetLogMessageFlagMFILE
						MFILE_SetLogMessageFlagGMT
						MFILE_LogMessage

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_SetLogMessageFlagSYSLOG
						Memory-mapped File Functions:Logging Functions:MFILE_GetLogMessageFlagFILE
						MFILE Functions:MFILE_GetLogMessageFlagFILEw

	PUBLISH XREF:	MFILE_SetLogMessageFlagSYSLOG

	PUBLISH NAME:	MFILE_SetLogMessageFlagSYSLOG

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MFILE_SetLogMessageFlagSYSLOG(int new_flag_value)
#else
int MFILE_SetLogMessageFlagSYSLOG(new_flag_value)
int new_flag_value;
#endif /* #ifndef NARGS */
{
	int old_flag_value;

	old_flag_value             = MFILE_LogMessageFlagSYSLOG;
	MFILE_LogMessageFlagSYSLOG = (new_flag_value) ? MFILE_TRUE : MFILE_FALSE;

	return(old_flag_value);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_GetLogMessageFlagGMT

   SYNOPSIS    :  return_flag_value = MFILE_GetLogMessageFlagGMT();

						int return_flag_value;

   DESCRIPTION :  Returns the current log message action flag value which
						specifies whether the logging functions emit the log entry
						time in local time or in GMT/UTC time.

   PARAMETERS  :  None.

   RETURNS     :  The current log message action flag value for log entry
						time as one of the following manifest constants:

						(.) ''MFILE_TRUE'' if the flag is set. This setting indicates
						that calls to the function ``MFILE_LogMessage`` will result
						in the log entry time being emitted in GMT/UTC time.

						(.) ''MFILE_FALSE'' if the flag is not set. This setting
						indicates that calls to the function ``MFILE_LogMessage``
						will result in the log entry time being emitted in local
						time.

   NOTES       :  The default setting for this flag is ''MFILE_FALSE''.

						You can change the setting of the flag by calling the
						function ``MFILE_SetLogMessageFlagGMT``.

   CAVEATS     :  

   SEE ALSO    :  MFILE_SetLogMessageFlagGMT
						MFILE_GetLogMessageFlagFILE
						MFILE_GetLogMessageFlagMFILE
						MFILE_GetLogMessageFlagSYSLOG
						MFILE_LogMessage

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_GetLogMessageFlagGMT
						Memory-mapped File Functions:Logging Functions:MFILE_GetLogMessageFlagGMT
						MFILE Functions:MFILE_GetLogMessageFlagGMT

	PUBLISH XREF:	MFILE_GetLogMessageFlagGMT

	PUBLISH NAME:	MFILE_GetLogMessageFlagGMT

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MFILE_GetLogMessageFlagGMT(void)
#else
int MFILE_GetLogMessageFlagGMT()
#endif /* #ifndef NARGS */
{
	return(MFILE_LogMessageFlagGMT);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_SetLogMessageFlagGMT

   SYNOPSIS    :  return_flag_value =
							MFILE_SetLogMessageFlagGMT(new_flag_value);

						int return_flag_value;

						int new_flag_value;

   DESCRIPTION :  Specifies the log message action flag value to indicate
						whether the logging functions emit the log entry time in
						local time or in GMT/UTC time.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``new_flag_value`` specifies the new log message action
						flag which specifies whether the logging functions emit the
						log entry time in local time or in GMT/UTC time.

						(-) If ``new_flag_value`` is non-zero, then subsequent calls
						to the function ``MFILE_LogMessage`` with a non-NULL
						``file_ptr`` parameter will result in the log entry time
						being emitted in GMT/UTC time.

						(-) If ``new_flag_value`` is zero, then subsequent calls to
						the function ``MFILE_LogMessage`` will result in the log
						entry time being emitted in local time.

   RETURNS     :  The previous log message action flag value for the time.

   NOTES       :  The default setting for this flag is ''MFILE_FALSE''.

						You can non-destructively determine the setting of the
						flag by calling the function
						``MFILE_GetLogMessageFlagGMT``.

   CAVEATS     :  

   SEE ALSO    :  MFILE_GetLogMessageFlagGMT
						MFILE_SetLogMessageFlagFILE
						MFILE_SetLogMessageFlagMFILE
						MFILE_SetLogMessageFlagSYSLOG
						MFILE_LogMessage

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_SetLogMessageFlagGMT
						Memory-mapped File Functions:Logging Functions:MFILE_GetLogMessageFlagGMT
						MFILE Functions:MFILE_GetLogMessageFlagGMT

	PUBLISH XREF:	MFILE_SetLogMessageFlagGMT

	PUBLISH NAME:	MFILE_SetLogMessageFlagGMT

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MFILE_SetLogMessageFlagGMT(int new_flag_value)
#else
int MFILE_SetLogMessageFlagGMT(new_flag_value)
int new_flag_value;
#endif /* #ifndef NARGS */
{
	int old_flag_value;

	old_flag_value          = MFILE_LogMessageFlagGMT;
	MFILE_LogMessageFlagGMT = (new_flag_value) ? MFILE_TRUE : MFILE_FALSE;

	return(old_flag_value);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#define TEST_FILE								"MLOGMS.log"

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = 0;
	MFILE        *m_file_ptr  = NULL;
	unsigned int  in_count    = 0;
	char         *fgets_return;
	char          buffer[512];

	fprintf(stderr, "Test routine for 'MFILE_LogMessage()'\n");
	fprintf(stderr, "---- ------- --- --------------------\n\n");

	if ((m_file_ptr = mopen(TEST_FILE, "w")) == NULL) {
		fprintf(stderr, "ERROR: Unable to open output test log file '%s'.\n\n",
			TEST_FILE);
		return_code = -1;
	}
	else {
		while ((!feof(stdin)) && (!ferror(stdin))) {
			*buffer      = '\0';
			fgets_return = buffer;
			while (fgets_return && (!(*buffer))) {
				fgets_return = fgets(buffer, sizeof(buffer) - 1, stdin);
				in_count++;
			}
			if ((!fgets_return) || (!strnicmp(buffer, "END", 3))) {
				fprintf(stderr, "ENDING PROCESS: %s\n", (!fgets_return) ?
					"END-FILE-ENCOUNTERED" : "END IN INPUT ENCOUNTERED");
				break;
			}
			while (*buffer && (buffer[strlen(buffer) - 1] == '\n'))
				buffer[strlen(buffer) - 1] = '\0';
			if (*buffer)
				MFILE_LogMessage(NULL, LOG_INFO, m_file_ptr, stderr, 1, "%s\n",
					buffer);
		}
		mclose(m_file_ptr);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

