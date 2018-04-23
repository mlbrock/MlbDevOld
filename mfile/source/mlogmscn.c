/* *********************************************************************** */
/* *********************************************************************** */
/*	MFILE Memory-mapped I/O Library Source Code Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logs formatted message text to a memory-mapped file
								using an 'MFILE_LOG_CONTEXT' structure.

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

#include <genfuncs.h>

#include "mfilei.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_LogMessageContext

   SYNOPSIS    :  MFILE_LogMessageContext(log_context_ptr, timeval_ptr,
							log_priority, syslog_flag, in_format, ...);

						MFILE_LOG_CONTEXT *log_context_ptr;

						struct timeval    *timeval_ptr;

						int                log_priority;

						int                syslog_flag;

						const char        *in_format;

   DESCRIPTION :  This function logs a time-stamped message to the facilities
						specified in the parameter list, as modified by the
						settings in the ``log_context_ptr`` parameter.

						The logged message has the following format:

<|@|>``yyyy``-``mm``-``dd`` ``hh``:``mm``:``ss``.``uuuuuu``:``priority``:``Your message here``

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``log_context_ptr`` points to a structure of type
						''MFILE_LOG_CONTEXT'' which describes the particulars of
						how the log entry is to be emitted by this function.

						(-) If ``log_context_ptr`` is ''NULL'' the function will not
						perform any logging.

						(..) The ``mfile_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''MFILE'' which specifies the
						memory-mapped file to which the message is to be logged.

						(--) If ``mfile_ptr`` is a ''NULL'' pointer, or if the
						``mfile_flag`` member is ''0'', the message will not
						be logged to a memory-mapped file.

						(..) The ``file_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''FILE'' which specifies the C
						level-two I/O device to which the message is to be logged.

						(--) If ``file_ptr`` is a ''NULL'' pointer, or if the
						``file_flag`` member is ''0'', the message will not be
						logged to a C level-two I/O device.

						(.) ``timeval_ptr`` points to a structure of type
						''timeval'' which contains the time-stamp of the message
						to be logged.

						(-) If ``timeval_ptr`` is a ''NULL'' pointer, the current
						system time will be used to time-stamp the message.

						(-) If the ``gmt_flag`` member of ``log_context_ptr`` is
						non-zero, then the time will be emitted by this function as
						GMT time. Otherwise, the time will be emitted as local time.

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
						message will be posted with ''LOG_INFO''.

						(.) ``syslog_flag`` specifies whether the message is to
						posted to the Unix system facility ``syslog``. It should
						take on the value of the following manifest constants:

						(..) ''MFILE_TRUE''

						(..) ''MFILE_FALSE''

						(-) Messages are posted to the ``syslog`` facility only on
						those operating systems which possess said facility.

						(-) Note that if the ``syslog_flag`` member of
						``log_context_ptr`` is ''0'', the message will not be
						logged to the Unix system ``syslog`` facility.

						(.) ``in_format`` is a ``printf``-style format string
						which specifies how subsequent parameters are to be
						interpreted.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  Because this function uses ``vsprintf`` to perform its
						work, the exact nature of the format specifiers accepted
						and their semantics may differ depending on the capability
						and whimsy of the compiler implementors.

   SEE ALSO    :  MFILE_LogMessage

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_LogMessageContext
						Memory-mapped File Functions:Logging Functions:MFILE_LogMessageContext
						MFILE Functions:MFILE_LogMessageContext

	PUBLISH XREF:	MFILE_LogMessageContext

	PUBLISH NAME:	MFILE_LogMessageContext

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
void MFILE_LogMessageContext(MFILE_LOG_CONTEXT *log_context_ptr,
	struct timeval *timeval_ptr, int log_priority,
	int syslog_flag, const char *in_format, ...)
#else
void MFILE_LogMessageContext(log_context_ptr, timeval_ptr, log_priority,
	syslog_flag, in_format, va_alist)
MFILE_LOG_CONTEXT *log_context_ptr;
struct timeval    *timeval_ptr;
int                log_priority;
int                syslog_flag;
const char        *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	unsigned int  char_count;
	char          message_header[SDTIF_FMT_TIME_LEN_TIMEVAL + 256];
	va_list       argument_ptr;
	MFILE        *mfile_ptr;
	FILE         *file_ptr;
#ifndef MFILE_MMAP_NON_NATIVE
	char         *tmp_format;
#endif /* #ifndef MFILE_MMAP_NON_NATIVE */

	if (log_context_ptr == NULL)
		return;

	mfile_ptr = log_context_ptr->mfile_ptr;
	file_ptr  = log_context_ptr->file_ptr;

	if (((mfile_ptr != NULL) && (log_context_ptr->mfile_flag == MFILE_TRUE)) ||
		((file_ptr != NULL) && (log_context_ptr->file_flag == MFILE_TRUE)) ||
		(syslog_flag && (log_context_ptr->syslog_flag == MFILE_TRUE))) {
		if (log_context_ptr->gmt_flag)
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
		if ((log_context_ptr->mfile_flag == MFILE_TRUE) &&
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
		if ((file_ptr != NULL) && (log_context_ptr->file_flag == MFILE_TRUE)) {
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
		if (syslog_flag && (log_context_ptr->syslog_flag == MFILE_TRUE)) {
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

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_InitLogContext

   SYNOPSIS    :  void MFILE_InitLogContext(log_context_ptr);

						MFILE_LOG_CONTEXT *log_context_ptr;

   DESCRIPTION :  Initializes the members of a ''MFILE_LOG_CONTEXT'' structure
						to their default values.

						The structure is initialized as follows:

{|@|}log_context_ptr->mfile_flag  = MFILE_TRUE;
log_context_ptr->file_flag   = MFILE_TRUE;
log_context_ptr->syslog_flag = MFILE_TRUE;
log_context_ptr->gmt_flag    = MFILE_FALSE;
log_context_ptr->mfile_ptr   = NULL;
log_context_ptr->file_ptr    = NULL;

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``log_context_ptr`` points to the ''MFILE_LOG_CONTEXT''
						to be initialized by this function.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_InitLogContext
						Memory-mapped File Functions:Logging Functions:MFILE_InitLogContext
						MFILE Functions:MFILE_InitLogContext

	PUBLISH XREF:	MFILE_InitLogContext

	PUBLISH NAME:	MFILE_InitLogContext

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void MFILE_InitLogContext(MFILE_LOG_CONTEXT *log_context_ptr)
#else
void MFILE_InitLogContext(log_context_ptr)
MFILE_LOG_CONTEXT *log_context_ptr;
#endif /* #ifndef NARGS */
{
	log_context_ptr->mfile_flag  = MFILE_TRUE;
	log_context_ptr->file_flag   = MFILE_TRUE;
	log_context_ptr->syslog_flag = MFILE_TRUE;
	log_context_ptr->gmt_flag    = MFILE_FALSE;
	log_context_ptr->mfile_ptr   = NULL;
	log_context_ptr->file_ptr    = NULL;
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  MFILE_LogEnsureSpace

   SYNOPSIS    :  truth_code = MFILE_LogEnsureSpace(mfile_ptr);

						int    truth_code;

						MFILE *mfile_ptr;

   DESCRIPTION :  Attempts to ensure that there is sufficient unused space
						in a memory-mapped log file for an additional log message
						line. The minimum amount of unused space is defined by the
						value of the manifest constant ''MFILE_PRINTF_BUFFER_SIZE''.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``mfile_ptr`` points to the ''MFILE'' structure which
						represents the log file.

   RETURNS     :  Returns from this function are as follow:

						(.) ''MFILE_TRUE'' if there was sufficient space in the
						log file at the time of the call or if the function was
						able to expand the size of the log file.

						(.) ''MFILE_FALSE'' if sufficient space in the log file
						could not be procured by the function.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  mprintf_ensure_space

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	MFILE_LogEnsureSpace
						Memory-mapped File Functions:Logging Functions:MFILE_LogEnsureSpace
						MFILE Functions:MFILE_LogEnsureSpace

	PUBLISH XREF:	MFILE_LogEnsureSpace

	PUBLISH NAME:	MFILE_LogEnsureSpace

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int MFILE_LogEnsureSpace(MFILE *mfile_ptr)
#else
int MFILE_LogEnsureSpace(mfile_ptr)
MFILE *mfile_ptr;
#endif /* #ifndef NARGS */
{
	int           log_has_space_flag = MFILE_FALSE;
	unsigned long buffer_size;
	unsigned long new_size;

	if ((mfile_ptr != NULL) && (!MFILE_ValidateMFILEPtr(mfile_ptr)) &&
 		(mfile_ptr->mfile_flags & MFILE_MODE_WRITE)) {
		buffer_size = (mfile_ptr->buffer_size > MFILE_PRINTF_BUFFER_SIZE) ?
			mfile_ptr->buffer_size : MFILE_PRINTF_BUFFER_SIZE;
		if ((new_size = (mfile_ptr->mmap_size - mfile_ptr->current_offset)) <
			MFILE_PRINTF_BUFFER_SIZE_MIN) {
			new_size = mfile_ptr->mmap_size + buffer_size;
			if (!mtruncate_safe(mfile_ptr, new_size)) {
				mfile_ptr->file_size = mfile_ptr->current_offset;
				log_has_space_flag   = MFILE_TRUE;
			}
		}
		else
			log_has_space_flag = MFILE_TRUE;
	}

	return(log_has_space_flag);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepStartLogContext

   SYNOPSIS    :	void MFILE_LogSepStartLogContext(log_context_ptr);

						MFILE_LOG_CONTEXT *log_context_ptr;

   DESCRIPTION :	Emits a log message indicating the beginning of the log
						file to the logging destinations specified by
						``log_context_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``log_context_ptr`` points to a structure of type
						''MFILE_LOG_CONTEXT'' which describes the particulars of
						how logging by this function is to be performed.

						(-) If ``log_context_ptr`` is ''NULL'' the function will not
						perform any logging.

						(..) The ``mfile_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''MFILE'' which specifies the
						memory-mapped file to which logging is to be performed.

						(--) If ``mfile_ptr`` is a ''NULL'' pointer, or if the
						``mfile_flag`` member is ''0'', no logging will performed
						to the memory-mapped file.

						(..) The ``file_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''FILE'' which specifies the C
						level-two I/O device to which logging is to be performed.

						(--) If ``file_ptr`` is a ''NULL'' pointer, or if the
						``file_flag`` member is ''0'', no logging will be performed
						to the C level-two I/O device.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message indicating the ending of the log
						file with the function ``MFILE_LogSepEndLogContext``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepEndLogContext
						MFILE_LogSepStartLog

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepStartLogContext
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepStartLogContext
						MFILE Functions:MFILE_LogSepStartLogContext

   PUBLISH XREF:	MFILE_LogSepStartLogContext

   PUBLISH NAME:	MFILE_LogSepStartLogContext

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepStartLogContext(MFILE_LOG_CONTEXT *log_context_ptr)
#else
void MFILE_LogSepStartLogContext(log_context_ptr)
MFILE_LOG_CONTEXT *log_context_ptr;
#endif /* #ifndef NARGS */
{
	MFILE_LOG_CONTEXT log_context;

	if (log_context_ptr != NULL) {
		log_context           = *log_context_ptr;
		log_context.mfile_ptr =
			((log_context.mfile_ptr == NULL) || (!log_context.mfile_flag)) ?
			NULL : log_context.mfile_ptr;
		log_context.file_ptr  =
			((log_context.file_ptr == NULL) || (!log_context.file_flag))   ?
			NULL : log_context.file_ptr;
		MFILE_LogSepEqualCharContext(&log_context);
		MFILE_LogSepEqualCharContext(&log_context);
		if ((log_context.mfile_ptr != NULL) &&
			(MFILE_LogEnsureSpace(log_context.mfile_ptr) == MFILE_TRUE))
			mprintf(log_context.mfile_ptr, "%s %s %s %s\n",
			"                                        ",
			"******************************", "START OF LOG FILE",
			"*****************************");
		if (log_context.file_ptr != NULL)
			fprintf(log_context.file_ptr, "%s %s %s %s\n",
				"                                        ",
				"******************************", "START OF LOG FILE",
				"*****************************");
		MFILE_LogSepEqualCharContext(&log_context);
	}
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepEndLogContext

   SYNOPSIS    :	void MFILE_LogSepEndLogContext(log_context_ptr);

						MFILE_LOG_CONTEXT *log_context_ptr;

   DESCRIPTION :	Emits a log message indicating the ending of the log
						file to the logging destinations specified by
						``log_context_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``log_context_ptr`` points to a structure of type
						''MFILE_LOG_CONTEXT'' which describes the particulars of
						how logging by this function is to be performed.

						(-) If ``log_context_ptr`` is ''NULL'' the function will not
						perform any logging.

						(..) The ``mfile_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''MFILE'' which specifies the
						memory-mapped file to which logging is to be performed.

						(--) If ``mfile_ptr`` is a ''NULL'' pointer, or if the
						``mfile_flag`` member is ''0'', no logging will performed
						to a memory-mapped file.

						(..) The ``file_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''FILE'' which specifies the C
						level-two I/O device to which logging is to be performed.

						(--) If ``file_ptr`` is a ''NULL'' pointer, or if the
						``file_flag`` member is ''0'', no logging will be performed
						to a C level-two I/O device.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message indicating the beginning of the
						log file with the function ``MFILE_LogSepStartLogContext``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepStartLogContext
						MFILE_LogSepEndLog

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepEndLogContext
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepEndLogContext
						MFILE Functions:MFILE_LogSepEndLogContext

   PUBLISH XREF:	MFILE_LogSepEndLogContext

   PUBLISH NAME:	MFILE_LogSepEndLogContext

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepEndLogContext(MFILE_LOG_CONTEXT *log_context_ptr)
#else
void MFILE_LogSepEndLogContext(log_context_ptr)
MFILE_LOG_CONTEXT *log_context_ptr;
#endif /* #ifndef NARGS */
{
	MFILE_LOG_CONTEXT log_context;

	if (log_context_ptr != NULL) {
		log_context           = *log_context_ptr;
		log_context.mfile_ptr =
			((log_context.mfile_ptr == NULL) || (!log_context.mfile_flag)) ?
			NULL : log_context.mfile_ptr;
		log_context.file_ptr  =
			((log_context.file_ptr == NULL) || (!log_context.file_flag))   ?
			NULL : log_context.file_ptr;
		MFILE_LogSepEqualCharContext(&log_context);
		MFILE_LogSepEqualCharContext(&log_context);
		if ((log_context.mfile_ptr != NULL) &&
			(MFILE_LogEnsureSpace(log_context.mfile_ptr) == MFILE_TRUE))
			mprintf(log_context.mfile_ptr, "%s %s %s %s\n",
				"                                        ",
				"*******************************", "END OF LOG FILE",
				"******************************");
		if (log_context.file_ptr != NULL)
			fprintf(stderr, "%s %s %s %s\n",
				"                                        ",
				"*******************************", "END OF LOG FILE",
				"******************************");
		MFILE_LogSepEqualCharContext(&log_context);
	}
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepHyphenCharContext

   SYNOPSIS    :	void MFILE_LogSepHyphenCharContext(log_context_ptr);

						MFILE_LOG_CONTEXT *log_context_ptr;

   DESCRIPTION :	Emits a log message containing a string of hyphen characters
						(''-'') to the logging destinations specified by
						``log_context_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``log_context_ptr`` points to a structure of type
						''MFILE_LOG_CONTEXT'' which describes the particulars of
						how logging by this function is to be performed.

						(-) If ``log_context_ptr`` is ''NULL'' the function will not
						perform any logging.

						(..) The ``mfile_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''MFILE'' which specifies the
						memory-mapped file to which logging is to be performed.

						(--) If ``mfile_ptr`` is a ''NULL'' pointer, or if the
						``mfile_flag`` member is ''0'', no logging will performed
						to a memory-mapped file.

						(..) The ``file_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''FILE'' which specifies the C
						level-two I/O device to which logging is to be performed.

						(--) If ``file_ptr`` is a ''NULL'' pointer, or if the
						``file_flag`` member is ''0'', no logging will be performed
						to a C level-two I/O device.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string of an
						arbitrary characters with the function
						``MFILE_LogSepCharContext``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepEqualCharContext
						MFILE_LogSepCharContext
						MFILE_LogSepHyphenChar

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepHyphenCharContext
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepHyphenCharContext
						MFILE Functions:MFILE_LogSepHyphenCharContext

   PUBLISH XREF:	MFILE_LogSepHyphenCharContext

   PUBLISH NAME:	MFILE_LogSepHyphenCharContext

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepHyphenCharContext(MFILE_LOG_CONTEXT *log_context_ptr)
#else
void MFILE_LogSepHyphenCharContext(log_context_ptr)
MFILE_LOG_CONTEXT *log_context_ptr;
#endif /* #ifndef NARGS */
{
	MFILE_LogSepCharContext(log_context_ptr, '-');
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepEqualCharContext

   SYNOPSIS    :	void MFILE_LogSepEqualCharContext(log_context_ptr);

						MFILE_LOG_CONTEXT *log_context_ptr;

   DESCRIPTION :	Emits a log message containing a string of equal-sign
						characters (''='') to the logging destinations specified by
						``log_context_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``log_context_ptr`` points to a structure of type
						''MFILE_LOG_CONTEXT'' which describes the particulars of
						how logging by this function is to be performed.

						(-) If ``log_context_ptr`` is ''NULL'' the function will not
						perform any logging.

						(..) The ``mfile_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''MFILE'' which specifies the
						memory-mapped file to which logging is to be performed.

						(--) If ``mfile_ptr`` is a ''NULL'' pointer, or if the
						``mfile_flag`` member is ''0'', no logging will performed
						to a memory-mapped file.

						(..) The ``file_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''FILE'' which specifies the C
						level-two I/O device to which logging is to be performed.

						(--) If ``file_ptr`` is a ''NULL'' pointer, or if the
						``file_flag`` member is ''0'', no logging will be performed
						to a C level-two I/O device.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string of an
						arbitrary characters with the function
						``MFILE_LogSepCharContext``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepHyphenCharContext
						MFILE_LogSepCharContext
						MFILE_LogSepEqualChar

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepEqualCharContext
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepEqualCharContext
						MFILE Functions:MFILE_LogSepEqualCharContext

   PUBLISH XREF:	MFILE_LogSepEqualCharContext

   PUBLISH NAME:	MFILE_LogSepEqualCharContext

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepEqualCharContext(MFILE_LOG_CONTEXT *log_context_ptr)
#else
void MFILE_LogSepEqualCharContext(log_context_ptr)
MFILE_LOG_CONTEXT *log_context_ptr;
#endif /* #ifndef NARGS */
{
	MFILE_LogSepCharContext(log_context_ptr, '=');
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepCharContext

   SYNOPSIS    :	void MFILE_LogSepCharContext(log_context_ptr, log_char);

						MFILE_LOG_CONTEXT *log_context_ptr;

						int                log_char;

   DESCRIPTION :	Emits a log message containing a string of ``log_char``
						characters to the logging destinations specified by
						``log_context_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``log_context_ptr`` points to a structure of type
						''MFILE_LOG_CONTEXT'' which describes the particulars of
						how logging by this function is to be performed.

						(-) If ``log_context_ptr`` is ''NULL'' the function will not
						perform any logging.

						(..) The ``mfile_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''MFILE'' which specifies the
						memory-mapped file to which logging is to be performed.

						(--) If ``mfile_ptr`` is a ''NULL'' pointer, or if the
						``mfile_flag`` member is ''0'', no logging will performed
						to a memory-mapped file.

						(..) The ``file_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''FILE'' which specifies the C
						level-two I/O device to which logging is to be performed.

						(--) If ``file_ptr`` is a ''NULL'' pointer, or if the
						``file_flag`` member is ''0'', no logging will be performed
						to a C level-two I/O device.

						(.) ``log_char`` is the character to be used in logging.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string with the
						function ``MFILE_LogSepStringContext``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepStringContext
						MFILE_LogSepChar

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepCharContext
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepCharContext
						MFILE Functions:MFILE_LogSepCharContext

   PUBLISH XREF:	MFILE_LogSepCharContext

   PUBLISH NAME:	MFILE_LogSepCharContext

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepCharContext(MFILE_LOG_CONTEXT *log_context_ptr, int log_char)
#else
void MFILE_LogSepCharContext(log_context_ptr, log_char)
MFILE_LOG_CONTEXT *log_context_ptr;
int                log_char;
#endif /* #ifndef NARGS */
{
/*
1994-01-01:12:34:56.123456:INFORMATIONAL:<log-message-text> . . .
012345678901234567890123456789012345678901234567890
          1         2         3         4         5
*/
	char buffer[10 + 1 + 15 + 1 + 13 + 1 + 78 + 1];

	if (log_context_ptr != NULL) {
		memset(buffer, log_char, sizeof(buffer) - 1);
		buffer[10]                 = ' ';
		buffer[26]                 = ' ';
		buffer[40]                 = ' ';
		buffer[sizeof(buffer) - 1] = '\0';
		MFILE_LogSepStringContext(log_context_ptr, buffer);
	}
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_LogSepStringContext

   SYNOPSIS    :	void MFILE_LogSepStringContext(log_context_ptr, log_string);

						MFILE_LOG_CONTEXT *log_context_ptr;

						const char        *log_string;

   DESCRIPTION :	Emits a log message containing the string of ``log_string``
						to the logging destinations specified by
						``log_context_ptr``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``log_context_ptr`` points to a structure of type
						''MFILE_LOG_CONTEXT'' which describes the particulars of
						how logging by this function is to be performed.

						(-) If ``log_context_ptr`` is ''NULL'' the function will not
						perform any logging.

						(..) The ``mfile_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''MFILE'' which specifies the
						memory-mapped file to which logging is to be performed.

						(--) If ``mfile_ptr`` is a ''NULL'' pointer, or if the
						``mfile_flag`` member is ''0'', no logging will performed
						to a memory-mapped file.

						(..) The ``file_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''FILE'' which specifies the C
						level-two I/O device to which logging is to be performed.

						(--) If ``file_ptr`` is a ''NULL'' pointer, or if the
						``file_flag`` member is ''0'', no logging will be performed
						to a C level-two I/O device.

						(.) ``log_string`` is the string to be used in logging.

   RETURNS     :	Void.

   NOTES       :	You can emit a log message containing a string of an
						characters with the function ``MFILE_LogSepCharContext``.

   CAVEATS     :	

   SEE ALSO    :	MFILE_LogSepCharContext
						MFILE_LogSepString

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_LogSepStringContext
						Memory-mapped File Functions:Logging Functions:MFILE_LogSepStringContext
						MFILE Functions:MFILE_LogSepStringContext

   PUBLISH XREF:	MFILE_LogSepStringContext

   PUBLISH NAME:	MFILE_LogSepStringContext

	ENTRY CLASS	:	Memory-mapped File Functions:Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_LogSepStringContext(MFILE_LOG_CONTEXT *log_context_ptr,
	const char *log_string)
#else
void MFILE_LogSepStringContext(log_context_ptr, log_string)
MFILE_LOG_CONTEXT *log_context_ptr;
const char        *log_string;
#endif /* #ifndef NARGS */
{
	MFILE_LOG_CONTEXT log_context;

	if (log_context_ptr != NULL) {
		log_context           = *log_context_ptr;
		log_context.mfile_ptr =
			((log_context.mfile_ptr == NULL) || (!log_context.mfile_flag)) ?
			NULL : log_context.mfile_ptr;
		log_context.file_ptr  =
			((log_context.file_ptr == NULL) || (!log_context.file_flag))   ?
			NULL : log_context.file_ptr;
		if ((log_context.mfile_ptr != NULL) &&
			(MFILE_LogEnsureSpace(log_context.mfile_ptr) == MFILE_TRUE))
			mprintf(log_context.mfile_ptr, "%s\n", log_string);
		if (log_context.file_ptr != NULL)
			fprintf(log_context.file_ptr, "%s\n", log_string);
	}
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_ShowExecTime

   SYNOPSIS    :	void MFILE_ShowExecTime(start_time, end_time,
							overhead_end_time, log_context_ptr);

						const struct timeval *start_time;

						const struct timeval *end_time;

						const struct timeval *overhead_end_time;

						MFILE_LOG_CONTEXT    *log_context_ptr;

   DESCRIPTION :	Logs information about the running time of a executable to
						a log file.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``start_time`` is a pointer to a ``struct timeval``
						which contains the starting time of the executable.

						(.) ``end_time`` is a pointer to a ``struct timeval``
						which contains the ending time of the executable.

						(-) If ``end_time`` is ''NULL'', the current time will
						be used.

						(.) ``overhead_end_time`` is a pointer to a ``struct
						timeval`` which contains the time at which the executable
						finished its overhead processing.

						(-) If ``overhead_end_time`` is ''NULL'', overhead
						processing time will be reported as zero.

						(.) ``log_context_ptr`` points to a structure of type
						''MFILE_LOG_CONTEXT'' which describes the particulars of
						how logging by this function is to be performed.

						(-) If ``log_context_ptr`` is ''NULL'' the function will not
						perform any logging.

						(..) The ``mfile_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''MFILE'' which specifies the
						memory-mapped file to which logging is to be performed.

						(--) If ``mfile_ptr`` is a ''NULL'' pointer, or if the
						``mfile_flag`` member is ''0'', no logging will performed
						to the memory-mapped file.

						(..) The ``file_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''FILE'' which specifies the C
						level-two I/O device to which logging is to be performed.

						(--) If ``file_ptr`` is a ''NULL'' pointer, or if the
						``file_flag`` member is ''0'', no logging will be performed
						to the C level-two I/O device.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	MFILE_ShowExecRUsage

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_ShowExecTime
						Memory-mapped File Functions:Logging Functions:MFILE_ShowExecTime
						MFILE Functions:MFILE_ShowExecTime

   PUBLISH XREF:	MFILE_ShowExecTime

   PUBLISH NAME:	MFILE_ShowExecTime

	ENTRY CLASS	:	Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_ShowExecTime(const struct timeval *start_time,
	const struct timeval *end_time, const struct timeval *overhead_end_time,
	MFILE_LOG_CONTEXT *log_context_ptr)
#else
void MFILE_ShowExecTime(start_time, end_time, overhead_end_time,
	log_context_ptr)
const struct timeval *start_time;
const struct timeval *end_time;
const struct timeval *overhead_end_time;
MFILE_LOG_CONTEXT    *log_context_ptr;
#endif /* #ifndef NARGS */
{
	struct timeval tmp_end_time;
	struct timeval overhead_interval;
	struct timeval total_interval;
	char           tmp_buffer_1[512];
	char           tmp_buffer_2[512];
	char           tmp_interval[256];

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*	Default the end time to now . . .										*/
	/*	**************************************************************	*/
	if (end_time == NULL) {
		SDTIF_GetTimeUSecs(&tmp_end_time);
		end_time = ((const struct timeval *) &tmp_end_time);
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Calculate the basic total executable time . . .					*/
	/*	**************************************************************	*/
	SDTIF_GetABSInterval_timeval(start_time, end_time, &total_interval);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Calculate the executable overhead time . . .						*/
	/*	**************************************************************	*/
	if ((overhead_end_time != NULL) &&
		(overhead_end_time->tv_sec || overhead_end_time->tv_usec))
		SDTIF_GetABSInterval_timeval(start_time, overhead_end_time,
			&overhead_interval);
	else {
		overhead_interval.tv_sec  = 0L;
		overhead_interval.tv_usec = 0L;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Set-up some buffers for logging . . .								*/
	/*	**************************************************************	*/
	sprintf(tmp_buffer_1, "%s %s %s",
		"========== ===============", "=============",
		"========================================================");
	sprintf(tmp_buffer_2, "%s %s %s",
		"---------- ---------------", "-------------",
		"--------------------------------------------------------");
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Show timing statistics . . .											*/
	/*	**************************************************************	*/
	MFILE_LogSepStringContext(log_context_ptr, tmp_buffer_1);
	MFILE_LogMessageContext(log_context_ptr, NULL, LOG_INFO,
		MFILE_FALSE, "%-28.28s: %s\n", "Start Time",
		SDTIF_Format_timeval(start_time, tmp_interval));
	MFILE_LogMessageContext(log_context_ptr, NULL, LOG_INFO,
		MFILE_FALSE, "%-28.28s: %s\n", "End Time",
		SDTIF_Format_timeval(end_time, tmp_interval));
	MFILE_LogSepStringContext(log_context_ptr, tmp_buffer_2);
	MFILE_LogMessageContext(log_context_ptr, NULL, LOG_INFO,
		MFILE_FALSE, "%-28.28s: %s\n", "Overhead Time",
		SDTIF_FormatInterval_timeval(&overhead_interval, tmp_interval));
	MFILE_LogMessageContext(log_context_ptr, NULL, LOG_INFO,
		MFILE_FALSE, "%-28.28s: %s\n", "Total Time",
		SDTIF_FormatInterval_timeval(&total_interval, tmp_interval));
	MFILE_LogSepStringContext(log_context_ptr, tmp_buffer_2);
	/*	**************************************************************	*/
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	MFILE_ShowExecRUsage

   SYNOPSIS    :	void MFILE_ShowExecRUsage(log_context_ptr);

						MFILE_LOG_CONTEXT *log_context_ptr;

   DESCRIPTION :	Logs information about the operating system resource usage
						metrics of an executable to a log file.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``log_context_ptr`` points to a structure of type
						''MFILE_LOG_CONTEXT'' which describes the particulars of
						how logging by this function is to be performed.

						(-) If ``log_context_ptr`` is ''NULL'' the function will not
						perform any logging.

						(..) The ``mfile_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''MFILE'' which specifies the
						memory-mapped file to which logging is to be performed.

						(--) If ``mfile_ptr`` is a ''NULL'' pointer, or if the
						``mfile_flag`` member is ''0'', no logging will performed
						to the memory-mapped file.

						(..) The ``file_ptr`` member of ``log_context_ptr`` points
						to a structure of type ''FILE'' which specifies the C
						level-two I/O device to which logging is to be performed.

						(--) If ``file_ptr`` is a ''NULL'' pointer, or if the
						``file_flag`` member is ''0'', no logging will be performed
						to the C level-two I/O device.

   RETURNS     :	Void.

   NOTES       :	This function uses ``GEN_FormatRUsageList`` to determine
						and format the usage metrics.

   CAVEATS     :	

   SEE ALSO    :	MFILE_ShowExecTime

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2018 Michael L. Brock

   OUTPUT INDEX:	MFILE_ShowExecRUsage
						Memory-mapped File Functions:Logging Functions:MFILE_ShowExecRUsage
						MFILE Functions:MFILE_ShowExecRUsage

   PUBLISH XREF:	MFILE_ShowExecRUsage

   PUBLISH NAME:	MFILE_ShowExecRUsage

	ENTRY CLASS	:	Logging Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MFILE_ShowExecRUsage(MFILE_LOG_CONTEXT *log_context_ptr)
#else
void MFILE_ShowExecRUsage(log_context_ptr)
MFILE_LOG_CONTEXT *log_context_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int   rusage_count = 0;
	char         **rusage_list  = NULL;
	unsigned int   count_1;
	char           tmp_buffer[512];
	char           error_text[GENFUNCS_MAX_ERROR_TEXT];

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Try to get the formatted process usage information . . .		*/
	/*	**************************************************************	*/
	if ((log_context_ptr == NULL) || ((GEN_FormatRUsageList(NULL, 28,
		GEN_RUSAGE_NULL_FORMAT_NULL, &rusage_count, &rusage_list,
		error_text)) != GENFUNCS_SUCCESS))
		return;
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Set-up buffer for logging . . .										*/
	/*	**************************************************************	*/
	sprintf(tmp_buffer, "%s %s %s",
		"========== ===============", "=============",
		"========================================================");
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Show the process resource usage . . .								*/
	/*	**************************************************************	*/
	MFILE_LogSepStringContext(log_context_ptr, tmp_buffer);
	for (count_1 = 0; count_1 < rusage_count; count_1++)
		MFILE_LogMessageContext(log_context_ptr, NULL, LOG_INFO,
			MFILE_FALSE, "%s\n", rusage_list[count_1]);
	MFILE_LogSepStringContext(log_context_ptr, tmp_buffer);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Free the formatted process usage information . . .				*/
	/*	**************************************************************	*/
	strl_remove_all(&rusage_count, &rusage_list);
	/*	**************************************************************	*/
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define TEST_FILE								"MLOGMSCN.log"

COMPAT_FN_DECL(int main, (void));

int main()
{
	int                return_code = 0;
	unsigned int       in_count    = 0;
	MFILE_LOG_CONTEXT  log_context;
	char              *fgets_return;
	char               buffer[512];

	fprintf(stderr, "Test routine for 'MFILE_LogMessageContext()'\n");
	fprintf(stderr, "---- ------- --- ---------------------------\n\n");

	MFILE_InitLogContext(&log_context);

	if ((log_context.mfile_ptr = mopen(TEST_FILE, "w")) == NULL) {
		fprintf(stderr, "ERROR: Unable to open output test log file '%s'.\n\n",
			TEST_FILE);
		return_code = -1;
	}
	else {
		log_context.file_ptr = stderr;
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
				MFILE_LogMessageContext(&log_context, NULL, LOG_INFO, MFILE_FALSE,
					"%s\n", buffer);
		}
		mclose(log_context.mfile_ptr);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

