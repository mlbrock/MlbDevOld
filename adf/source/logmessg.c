/* *********************************************************************** */
/* *********************************************************************** */
/*	Automated Documentation Facility (ADF) Program Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logging support for ADF executables.

	Revision History	:	1995-07-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "adf.h"

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#ifndef _Windows
# include <syslog.h>
#endif /* #ifndef _Windows */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static int ADF_LogMessageFlagADF_FILE  = ADF_TRUE;

static int ADF_LogMessageFlagFILE      = ADF_TRUE;

static int ADF_LogMessageFlagSYSLOG    = ADF_TRUE;

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  ADF_LogMessage

   SYNOPSIS    :  ADF_LogMessage(timeval_ptr, log_priority, adf_file_ptr,
							file_ptr, syslog_flag, in_format, ...);

						struct timeval *timeval_ptr;

						int             log_priority;

						ADF_FILE       *adf_file_ptr;

						FILE           *file_ptr;

						int             syslog_flag;

						const char     *in_format;

   DESCRIPTION :  This function logs a time-stamped message to the facilities
						specified in the parameter list.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``timeval_ptr`` points to a structure of type
						''timeval'' which contains the time-stamp of the message
						to be logged. If it is a ''NULL'' pointer, the current
						system time will be used to time-stamp the message.

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

						(.) ``adf_file_ptr`` points to a structure of type
						''ADF_FILE'' which specifies the file to which the message
						is to be posted. If it is a ''NULL'' pointer, the message
						will not be posted to a file. Also, if the ``adf_file_ptr``
						parameter is equal to the ``file_ptr`` parameter, the
						message will not be posted to a file.

						(.) ``file_ptr`` points to a structure of type ''FILE''
						which specifies the C level-two I/O device to which the
						message is to be posted. If it is a ''NULL'' pointer, the
						message will not be posted to a C level-two I/O device.

						(-) This parameter is most often set to ``stderr``

						(.) ``syslog_flag`` specifies whether the message is to
						posted to the Unix system facility ``syslog``. It should
						take on the value of the following manifest constants:

						(..) ''ADF_TRUE''

						(..) ''ADF_FALSE''

						(-) Messages are posted to the ``syslog`` facility only on
						those operating systems which possess said facility.

						(.) ``in_format`` is a ``printf``-style format string
						which specifies how subsequent parameters are to be
						interpreted.

   RETURNS     :  Void.

   CAVEATS     :  Because this function uses ``vsprintf`` to perform its
						work, the exact nature of the format specifiers accepted
						and their semantics may differ depending on the capability
						and whimsy of the compiler implementors.

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	ADF_LogMessage
						ADF General Functions:ADF_LogMessage

	PUBLISH XREF:	ADF_LogMessage

	PUBLISH NAME:	ADF_LogMessage

EOH */
/* *********************************************************************** */
/*VARARGS2*/
#ifndef NO_STDARGS
void ADF_LogMessage(struct timeval *timeval_ptr, int log_priority,
	ADF_FILE *adf_file_ptr, FILE *file_ptr, int syslog_flag,
	const char *in_format, ...)
#else
void ADF_LogMessage(timeval_ptr, log_priority, adf_file_ptr, file_ptr,
	syslog_flag, in_format, va_alist)
struct timeval *timeval_ptr;
int             log_priority;
ADF_FILE       *adf_file_ptr;
FILE           *file_ptr;
int             syslog_flag;
const char     *in_format;
va_dcl
#endif /* #ifndef NO_STDARGS */
{
	char           message_header[256];
	va_list        argument_ptr;
#ifndef __MSDOS__
# ifndef _Windows
	unsigned int   char_count;
	char          *tmp_format;
	MFILE         *mfile_ptr;
# endif /* # ifndef _Windows */
#endif /* #ifndef __MSDOS__ */

	adf_file_ptr = (((FILE *) adf_file_ptr) == file_ptr) ? NULL : adf_file_ptr;

	if (((adf_file_ptr != NULL) && (ADF_LogMessageFlagADF_FILE == ADF_TRUE)) ||
		((file_ptr != NULL) && (ADF_LogMessageFlagFILE == ADF_TRUE)) ||
		(syslog_flag && (ADF_LogMessageFlagSYSLOG == ADF_TRUE))) {
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
#ifdef __MSDOS__
		if ((ADF_LogMessageFlagADF_FILE == ADF_TRUE) &&
			(adf_file_ptr != NULL)) {
			fputs(message_header, adf_file_ptr);
# ifndef NO_STDARGS
			va_start(argument_ptr, in_format);
# else
			va_start(argument_ptr);
# endif /* # ifndef NO_STDARGS */
			vfprintf(adf_file_ptr, in_format, argument_ptr);
			va_end(argument_ptr);
		}
#elif _Windows
		if ((ADF_LogMessageFlagADF_FILE == ADF_TRUE) &&
			(adf_file_ptr != NULL)) {
			fputs(message_header, adf_file_ptr);
# ifndef NO_STDARGS
			va_start(argument_ptr, in_format);
# else
			va_start(argument_ptr);
# endif /* # ifndef NO_STDARGS */
			vfprintf(adf_file_ptr, in_format, argument_ptr);
			va_end(argument_ptr);
		}
#else
		if ((ADF_LogMessageFlagADF_FILE == ADF_TRUE) &&
			(adf_file_ptr != NULL) &&
			(ADF_LogEnsureSpace(adf_file_ptr) == ADF_TRUE)) {
			mfile_ptr = ((MFILE *) adf_file_ptr);
			mputs(message_header, mfile_ptr);
# ifndef NO_STDARGS
			va_start(argument_ptr, in_format);
# else
			va_start(argument_ptr);
# endif /* # ifndef NO_STDARGS */
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
			va_end(argument_ptr);
			if (char_count > 0) {
				mfile_ptr->mfile_flags    |= MFILE_FLAG_WRITTEN;
				mfile_ptr->current_offset += char_count;
				mfile_ptr->file_size       =
					(mfile_ptr->current_offset > mfile_ptr->file_size) ?
					mfile_ptr->current_offset : mfile_ptr->file_size;
			}
		}
#endif /* #ifdef __MSDOS__ */
		if ((file_ptr != NULL) && (ADF_LogMessageFlagFILE == ADF_TRUE)) {
			fputs(message_header, file_ptr);
#ifndef NO_STDARGS
			va_start(argument_ptr, in_format);
#else
			va_start(argument_ptr);
#endif /* #ifndef NO_STDARGS */
			vfprintf(file_ptr, in_format, argument_ptr);
			va_end(argument_ptr);
		}
#ifndef __MSDOS__
# ifndef _Windows
		if (syslog_flag && (ADF_LogMessageFlagSYSLOG == ADF_TRUE)) {
			if ((tmp_format = ((char *) malloc((strlen(message_header) +
				strlen(in_format) + 1) * sizeof(char)))) != NULL) {
				strcat(strcpy(tmp_format, message_header), in_format);
#  ifndef NO_STDARGS
				va_start(argument_ptr, in_format);
#  else
				va_start(argument_ptr);
#  endif /* #  ifndef NO_STDARGS */
				vsyslog(log_priority, tmp_format, argument_ptr);
				va_end(argument_ptr);
				free(tmp_format);
			}
		}
# endif /* # ifndef _Windows */
#endif /* #ifndef __MSDOS__ */
	}
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int ADF_LogEnsureSpace(ADF_FILE *adf_file_ptr)
#else
int ADF_LogEnsureSpace(adf_file_ptr)
ADF_FILE *adf_file_ptr;
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	return(ADF_TRUE);
#elif _Windows
	return(ADF_TRUE);
#else
	int            log_has_space_flag = ADF_FALSE;
	unsigned long  buffer_size;
	unsigned long  new_size;
	MFILE         *mfile_ptr;

	mfile_ptr = ((MFILE *) adf_file_ptr);

	if ((mfile_ptr != NULL) && (!MFILE_ValidateMFILEPtr(mfile_ptr)) &&
		(mfile_ptr->mfile_flags & MFILE_MODE_WRITE)) {
		buffer_size = (mfile_ptr->buffer_size > MFILE_PRINTF_BUFFER_SIZE) ?
			mfile_ptr->buffer_size : MFILE_PRINTF_BUFFER_SIZE;
		if ((new_size = (mfile_ptr->mmap_size - mfile_ptr->current_offset)) <
			MFILE_PRINTF_BUFFER_SIZE_MIN) {
			new_size = mfile_ptr->mmap_size + buffer_size;
			if (!mtruncate_safe(mfile_ptr, new_size)) {
				mfile_ptr->file_size = mfile_ptr->current_offset;
				log_has_space_flag   = ADF_TRUE;
			}
		}
		else
			log_has_space_flag = ADF_TRUE;
	}

	return(log_has_space_flag);
#endif /* #ifdef __MSDOS__ */
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
void ADF_LogSeparatorStartLog(ADF_FILE *adf_file_ptr, FILE *file_ptr)
#else
void ADF_LogSeparatorStartLog(adf_file_ptr, file_ptr)
ADF_FILE *adf_file_ptr;
FILE     *file_ptr;
#endif /* #ifndef NARGS */
{
	adf_file_ptr = (((FILE *) adf_file_ptr) == file_ptr) ? NULL : adf_file_ptr;

	if (((adf_file_ptr != NULL) && (ADF_LogMessageFlagADF_FILE == ADF_TRUE)) ||
		((file_ptr != NULL) && (ADF_LogMessageFlagFILE == ADF_TRUE))) {
		ADF_LogSeparatorEqualChar(adf_file_ptr, file_ptr);
		ADF_LogSeparatorEqualChar(adf_file_ptr, file_ptr);
		if ((adf_file_ptr != NULL) &&
			(ADF_LogMessageFlagADF_FILE == ADF_TRUE) &&
			(ADF_LogEnsureSpace(adf_file_ptr) == ADF_TRUE))
			ADF_fprintf(adf_file_ptr, "%s %s %s %s\n",
			"                                        ",
			"******************************", "START OF LOG FILE",
			"*****************************");
		if ((file_ptr != NULL) && (ADF_LogMessageFlagFILE == ADF_TRUE))
			fprintf(file_ptr, "%s %s %s %s\n",
				"                                        ",
				"******************************", "START OF LOG FILE",
				"*****************************");
		ADF_LogSeparatorEqualChar(adf_file_ptr, file_ptr);
	}
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
void ADF_LogSeparatorEndLog(ADF_FILE *adf_file_ptr, FILE *file_ptr)
#else
void ADF_LogSeparatorEndLog(adf_file_ptr, file_ptr)
ADF_FILE *adf_file_ptr;
FILE     *file_ptr;
#endif /* #ifndef NARGS */
{
	adf_file_ptr = (((FILE *) adf_file_ptr) == file_ptr) ? NULL : adf_file_ptr;

	if (((adf_file_ptr != NULL) && (ADF_LogMessageFlagADF_FILE == ADF_TRUE)) ||
		((file_ptr != NULL) && (ADF_LogMessageFlagFILE == ADF_TRUE))) {
		ADF_LogSeparatorEqualChar(adf_file_ptr, file_ptr);
		ADF_LogSeparatorEqualChar(adf_file_ptr, file_ptr);
		if ((adf_file_ptr != NULL) &&
			(ADF_LogMessageFlagADF_FILE == ADF_TRUE) &&
			(ADF_LogEnsureSpace(adf_file_ptr) == ADF_TRUE))
			ADF_fprintf(adf_file_ptr, "%s %s %s %s\n",
				"                                        ",
				"*******************************", "END OF LOG FILE",
				"******************************");
		if ((file_ptr != NULL) && (ADF_LogMessageFlagFILE == ADF_TRUE))
			fprintf(stderr, "%s %s %s %s\n",
				"                                        ",
				"*******************************", "END OF LOG FILE",
				"******************************");
		ADF_LogSeparatorEqualChar(adf_file_ptr, file_ptr);
	}
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
void ADF_LogSeparatorHyphenChar(ADF_FILE *adf_file_ptr, FILE *file_ptr)
#else
void ADF_LogSeparatorHyphenChar(adf_file_ptr, file_ptr)
ADF_FILE *adf_file_ptr;
FILE     *file_ptr;
#endif /* #ifndef NARGS */
{
	adf_file_ptr = (((FILE *) adf_file_ptr) == file_ptr) ? NULL : adf_file_ptr;

	if (((adf_file_ptr != NULL) && (ADF_LogMessageFlagADF_FILE == ADF_TRUE)) ||
		((file_ptr != NULL) && (ADF_LogMessageFlagFILE == ADF_TRUE)))
		ADF_LogSeparatorChar(adf_file_ptr, file_ptr, '-');
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
void ADF_LogSeparatorEqualChar(ADF_FILE *adf_file_ptr, FILE *file_ptr)
#else
void ADF_LogSeparatorEqualChar(adf_file_ptr, file_ptr)
ADF_FILE *adf_file_ptr;
FILE     *file_ptr;
#endif /* #ifndef NARGS */
{
	adf_file_ptr = (((FILE *) adf_file_ptr) == file_ptr) ? NULL : adf_file_ptr;

	if (((adf_file_ptr != NULL) && (ADF_LogMessageFlagADF_FILE == ADF_TRUE)) ||
		((file_ptr != NULL) && (ADF_LogMessageFlagFILE == ADF_TRUE)))
		ADF_LogSeparatorChar(adf_file_ptr, file_ptr, '=');
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
void ADF_LogSeparatorChar(ADF_FILE *adf_file_ptr, FILE *file_ptr, int log_char)
#else
void ADF_LogSeparatorChar(adf_file_ptr, file_ptr, log_char)
ADF_FILE *adf_file_ptr;
FILE     *file_ptr;
int       log_char;
#endif /* #ifndef NARGS */
{
/*
1995-01-01:12:34:56.123456:INFORMATIONAL:<log-message-text> . . .
012345678901234567890123456789012345678901234567890
          1         2         3         4         5
*/
	char buffer[10 + 1 + 15 + 1 + 13 + 1 + 78 + 1];

	adf_file_ptr = (((FILE *) adf_file_ptr) == file_ptr) ? NULL : adf_file_ptr;

	if (((adf_file_ptr != NULL) && (ADF_LogMessageFlagADF_FILE == ADF_TRUE)) ||
		((file_ptr != NULL) && (ADF_LogMessageFlagFILE == ADF_TRUE))) {
		memset(buffer, log_char, sizeof(buffer) - 1);
		buffer[10]                 = ' ';
		buffer[26]                 = ' ';
		buffer[40]                 = ' ';
		buffer[sizeof(buffer) - 1] = '\0';
		ADF_LogSeparatorString(adf_file_ptr, file_ptr, buffer);
	}
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
void ADF_LogSeparatorString(ADF_FILE *adf_file_ptr, FILE *file_ptr,
	const char *log_string)
#else
void ADF_LogSeparatorString(adf_file_ptr, file_ptr, log_string)
ADF_FILE   *adf_file_ptr;
FILE       *file_ptr;
const char *log_string;
#endif /* #ifndef NARGS */
{
	adf_file_ptr = (((FILE *) adf_file_ptr) == file_ptr) ? NULL : adf_file_ptr;

	if (((adf_file_ptr != NULL) && (ADF_LogMessageFlagADF_FILE == ADF_TRUE)) ||
		((file_ptr != NULL) && (ADF_LogMessageFlagFILE == ADF_TRUE))) {
		if ((adf_file_ptr != NULL) &&
			(ADF_LogMessageFlagADF_FILE == ADF_TRUE) &&
			(ADF_LogEnsureSpace(adf_file_ptr) == ADF_TRUE))
			ADF_fprintf(adf_file_ptr, "%s\n", log_string);
		if ((file_ptr != NULL) && (ADF_LogMessageFlagFILE == ADF_TRUE))
			fprintf(file_ptr, "%s\n", log_string);
	}
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  ADF_GetLogMessageFlagFILE

   SYNOPSIS    :  return_flag_value = ADF_GetLogMessageFlagFILE();

						int return_flag_value;

   DESCRIPTION :  Returns the current log message action flag value for
						C language level-two I/O devices.

   PARAMETERS  :  None.

   RETURNS     :  The current log message action flag value for C language
						level-two I/O devices as one of the following manifest
						constants:

						(.) ''ADF_TRUE'' if the flag is set. This setting indicates
						that calls to the function ``ADF_LogMessage`` with a
						non-NULL ``file_ptr`` parameter will result in the log
						text being emitted to the C language level-two I/O device
						specified by that parameter.

						(.) ''ADF_FALSE'' if the flag is not set. This setting
						indicates that calls to the function ``ADF_LogMessage``
						will not emit log text to the C language level-two I/O
						device specified by the ``file_ptr`` parameter.

   NOTES       :  The default setting for this flag is ''ADF_TRUE''.

						You can change the setting of the flag by calling the
						function ``ADF_SetLogMessageFlagFILE``.

   SEE ALSO    :  ADF_SetLogMessageFlagFILE
						ADF_GetLogMessageFlagADF_FILE
						ADF_GetLogMessageFlagSYSLOG
						ADF_LogMessage

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	ADF_GetLogMessageFlagFILE
						ADF General Functions:ADF_GetLogMessageFlagFILE

	PUBLISH XREF:	ADF_GetLogMessageFlagFILE

	PUBLISH NAME:	ADF_GetLogMessageFlagFILE

EOH */
/* *********************************************************************** */
int ADF_GetLogMessageFlagFILE()
{
	return(ADF_LogMessageFlagFILE);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  ADF_SetLogMessageFlagFILE

   SYNOPSIS    :  return_flag_value =
							ADF_SetLogMessageFlagFILE(new_flag_value);

						int return_flag_value;

						int new_flag_value;

   DESCRIPTION :  Specifies the log message action flag value to be used for
						C language level-two I/O devices.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``new_flag_value`` specifies the new log message action
						flag to be used for C language level-two I/O devices.

						(-) If ``new_flag_value`` is non-zero, then subsequent calls
						to the function ``ADF_LogMessage`` with a non-NULL
						``file_ptr`` parameter will result in the log text being
						emitted to the C language level-two I/O device specified by
						that parameter.

						(-) If ``new_flag_value`` is zero, then subsequent calls to
						the function ``ADF_LogMessage`` will not emit log text to
						the C language level-two I/O device specified by the
						``file_ptr`` parameter.

   RETURNS     :  The previous log message action flag value for C language
						level-two I/O devices files.

   NOTES       :  The default setting for this flag is ''ADF_TRUE''.

						You can non-destructively determine the setting of the
						flag by calling the function
						``ADF_GetLogMessageFlagFILE``.

   SEE ALSO    :  ADF_GetLogMessageFlagFILE
						ADF_SetLogMessageFlagADF_FILE
						ADF_SetLogMessageFlagSYSLOG
						ADF_LogMessage

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	ADF_SetLogMessageFlagFILE
						ADF General Functions:ADF_SetLogMessageFlagFILE

	PUBLISH XREF:	ADF_SetLogMessageFlagFILE

	PUBLISH NAME:	ADF_SetLogMessageFlagFILE

EOH */
/* *********************************************************************** */
#ifndef NARGS
int ADF_SetLogMessageFlagFILE(int new_flag_value)
#else
int ADF_SetLogMessageFlagFILE(new_flag_value)
int new_flag_value;
#endif /* #ifndef NARGS */
{
	int old_flag_value;

	old_flag_value         = ADF_LogMessageFlagFILE;
	ADF_LogMessageFlagFILE = (new_flag_value) ? ADF_TRUE : ADF_FALSE;

	return(old_flag_value);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  ADF_GetLogMessageFlagADF_FILE

   SYNOPSIS    :  return_flag_value = ADF_GetLogMessageFlagADF_FILE();

						int return_flag_value;

   DESCRIPTION :  Returns the current log message action flag value for
						memory-mapped files.

   PARAMETERS  :  None.

   RETURNS     :  The current log message action flag value for memory-mapped
						files as one of the following manifest constants:

						(.) ''ADF_TRUE'' if the flag is set. This setting indicates
						that calls to the function ``ADF_LogMessage`` with a
						non-NULL ``adf_file_ptr`` parameter will result in the log
						text being emitted to the file specified by that parameter.

						(.) ''ADF_FALSE'' if the flag is not set. This setting
						indicates that calls to the function ``ADF_LogMessage``
						will not emit log text to the specified by the
						``adf_file_ptr`` parameter.

   NOTES       :  The default setting for this flag is ''ADF_TRUE''.

						You can change the setting of the flag by calling the
						function ``ADF_SetLogMessageFlagADF_FILE``.

   SEE ALSO    :  ADF_SetLogMessageFlagADF_FILE
						ADF_GetLogMessageFlagFILE
						ADF_GetLogMessageFlagSYSLOG
						ADF_LogMessage

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	ADF_GetLogMessageFlagADF_FILE
						ADF General Functions:ADF_GetLogMessageFlagADF_FILE

	PUBLISH XREF:	ADF_GetLogMessageFlagADF_FILE

	PUBLISH NAME:	ADF_GetLogMessageFlagADF_FILE

EOH */
/* *********************************************************************** */
int ADF_GetLogMessageFlagADF_FILE()
{
	return(ADF_LogMessageFlagADF_FILE);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  ADF_SetLogMessageFlagADF_FILE

   SYNOPSIS    :  return_flag_value =
							ADF_SetLogMessageFlagADF_FILE(new_flag_value);

						int return_flag_value;

						int new_flag_value;

   DESCRIPTION :  Specifies the log message action flag value to be used for
						memory-mapped files.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``new_flag_value`` specifies the new log message action
						flag to be used for memory-mapped files.

						(-) If ``new_flag_value`` is non-zero, then subsequent calls
						to the function ``ADF_LogMessage`` with a non-NULL
						``adf_file_ptr`` parameter will result in the log text being
						emitted to the file specified by that parameter.

						(-) If ``new_flag_value`` is zero, then subsequent calls to
						the function ``ADF_LogMessage`` will not emit log text to
						the file specified by the ``adf_file_ptr`` parameter.

   RETURNS     :  The previous log message action flag value for memory-mapped
						files.

   NOTES       :  The default setting for this flag is ''ADF_TRUE''.

						You can non-destructively determine the setting of the
						flag by calling the function
						``ADF_GetLogMessageFlagADF_FILE``.

   SEE ALSO    :  ADF_GetLogMessageFlagADF_FILE
						ADF_SetLogMessageFlagFILE
						ADF_SetLogMessageFlagSYSLOG
						ADF_LogMessage

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	ADF_SetLogMessageFlagADF_FILE
						ADF General Functions:ADF_SetLogMessageFlagADF_FILE

	PUBLISH XREF:	ADF_SetLogMessageFlagADF_FILE

	PUBLISH NAME:	ADF_SetLogMessageFlagADF_FILE

EOH */
/* *********************************************************************** */
#ifndef NARGS
int ADF_SetLogMessageFlagADF_FILE(int new_flag_value)
#else
int ADF_SetLogMessageFlagADF_FILE(new_flag_value)
int new_flag_value;
#endif /* #ifndef NARGS */
{
	int old_flag_value;

	old_flag_value             = ADF_LogMessageFlagADF_FILE;
	ADF_LogMessageFlagADF_FILE = (new_flag_value) ? ADF_TRUE : ADF_FALSE;

	return(old_flag_value);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  ADF_GetLogMessageFlagSYSLOG

   SYNOPSIS    :  return_flag_value = ADF_GetLogMessageFlagSYSLOG();

						int return_flag_value;

   DESCRIPTION :  Returns the current log message action flag value for
						the Unix system ``syslog`` facility.

   PARAMETERS  :  None.

   RETURNS     :  The current log message action flag value for the Unix
						system ``syslog`` facility as one of the following manifest
						constants:

						(.) ''ADF_TRUE'' if the flag is set. This setting indicates
						that calls to the functions ``ADF_LogMessageFILE`` and
						``ADF_LogMessageADF_FILE`` with a non-zero ``syslog_flag``
						parameter will result in the log text being emitted to
						the Unix system ``syslog`` facility (if the program is
						running on a Unix system).

						(.) ''ADF_FALSE'' if the flag is not set. This setting
						indicates that calls to the functions ``ADF_LogMessageFILE``
						and ``ADF_LogMessageADF_FILE``  will not emit log text to
						the Unix system ``syslog`` facility.

   NOTES       :  The default setting for this flag is ''ADF_TRUE''.

						You can change the setting of the flag by calling the
						function ``ADF_SetLogMessageFlagSYSLOG``.

   SEE ALSO    :  ADF_SetLogMessageFlagSYSLOG
						ADF_GetLogMessageFlagFILE
						ADF_GetLogMessageFlagADF_FILE
						ADF_LogMessage

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	ADF_GetLogMessageFlagSYSLOG
						ADF General Functions:ADF_GetLogMessageFlagSYSLOG

	PUBLISH XREF:	ADF_GetLogMessageFlagSYSLOG

	PUBLISH NAME:	ADF_GetLogMessageFlagSYSLOG

EOH */
/* *********************************************************************** */
int ADF_GetLogMessageFlagSYSLOG()
{
	return(ADF_LogMessageFlagSYSLOG);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  ADF_SetLogMessageFlagSYSLOG

   SYNOPSIS    :  return_flag_value =
							ADF_SetLogMessageFlagSYSLOG(new_flag_value);

						int return_flag_value;

						int new_flag_value;

   DESCRIPTION :  Specifies the log message action flag value to be used for
						the Unix system ``syslog`` facility.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``new_flag_value`` specifies the new log message action
						flag to be used for the Unix system ``syslog`` facility.

						(-) If ``new_flag_value`` is non-zero, then subsequent calls
						to the functions ``ADF_LogMessageFILE`` and
						``ADF_LogMessageADF_FILE``  with a non-zero ``syslog_flag``
						parameter will result in the log text being emitted to the
						Unix system ``syslog`` facility.

						(-) If ``new_flag_value`` is zero, then subsequent calls to
						the functions ``ADF_LogMessageFILE`` and
						``ADF_LogMessageADF_FILE``  will not emit log text to the
						Unix system ``syslog`` facility.

   RETURNS     :  The previous log message action flag value for the Unix
						system ``syslog`` facility.

   NOTES       :  The default setting for this flag is ''ADF_TRUE''.

						You can non-destructively determine the setting of the
						flag by calling the function
						``ADF_GetLogMessageFlagSYSLOG``.

   SEE ALSO    :  ADF_GetLogMessageFlagSYSLOG
						ADF_SetLogMessageFlagFILE
						ADF_SetLogMessageFlagADF_FILE
						ADF_LogMessage

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	ADF_SetLogMessageFlagSYSLOG
						ADF General Functions:ADF_SetLogMessageFlagSYSLOG

	PUBLISH XREF:	ADF_SetLogMessageFlagSYSLOG

	PUBLISH NAME:	ADF_SetLogMessageFlagSYSLOG

EOH */
/* *********************************************************************** */
#ifndef NARGS
int ADF_SetLogMessageFlagSYSLOG(int new_flag_value)
#else
int ADF_SetLogMessageFlagSYSLOG(new_flag_value)
int new_flag_value;
#endif /* #ifndef NARGS */
{
	int old_flag_value;

	old_flag_value           = ADF_LogMessageFlagSYSLOG;
	ADF_LogMessageFlagSYSLOG = (new_flag_value) ? ADF_TRUE : ADF_FALSE;

	return(old_flag_value);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = 0;
	ADF_FILE     *file_ptr    = NULL;
	unsigned int  in_count    = 0;
	char         *fgets_return;
	char          buffer[512];

	fprintf(stderr, "Test routine for 'ADF_LogMessage()'\n");
	fprintf(stderr, "---- ------- --- ------------------\n\n");

	if (!(file_ptr = ADF_fopen("ERASE.ME", "w"))) {
		fprintf(stderr, "ERROR: Unable to open output file 'ERASE.ME'.\n\n");
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
				ADF_LogMessage(NULL, LOG_INFO, file_ptr, stderr, 1, "%s\n",
					buffer);
		}
		ADF_fclose(file_ptr);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

