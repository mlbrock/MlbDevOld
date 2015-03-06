/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MFILE Memory-mapped I/O Library Include File										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Memory-mapped I/O Library
								(MFILE).

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__MFILE_H__h

#define h__MFILE_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#include <stdio.h>
#include <stdlib.h>

#include <sdtif.h>		/* Win32 MWCW needs this included before sys/types.h */

#include <sys/types.h>

#ifndef NO_STDARGS
# include <stdarg.h>
#else
# include <varargs.h>
#endif /* #ifndef NO_STDARGS */

#ifdef _Windows
# define MFILE_MMAP_NON_NATIVE			1
#elif __MSDOS__
# define MFILE_MMAP_NON_NATIVE			1
#else
# include <syslog.h>
#endif /* #ifdef _Windows */

// #include <sdtif.h>

#ifdef __BORLANDC__
# define off_t									long
#endif /* __BORLANDC__ */

#include <strfuncs.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	BASE NAME   :  MFILE Truth Codes

	NAME        :  MFILE Truth Codes

	DESCRIPTION :  Manifest constants used within MFILE to specify the truth
						or falsity of expressions.

						(.) ''MFILE_TRUE''

						(.) ''MFILE_FALSE''

	NOTES       :  The manifest constant ''MFILE_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''MFILE_FALSE'' should be defined as zero (''0'').

	AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:  MFILE_TRUE
						MFILE_FALSE
						MFILE Truth Codes:MFILE_TRUE
						MFILE Truth Codes:MFILE_FALSE
						MFILE Manifest Constants:MFILE_TRUE
						MFILE Manifest Constants:MFILE_FALSE
						MFILE Defines:MFILE_TRUE
						MFILE Defines:MFILE_FALSE
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:  MFILE Truth Codes
						MFILE Truth Code
						MFILE truth codes
						MFILE truth code
						MFILE_TRUE
						MFILE_FALSE

	PUBLISH NAME:	MFILE Truth Codes
						MFILE_TRUE
						MFILE_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MFILE_TRUE							1
#define MFILE_FALSE							0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

	BASE NAME   :	MFILE Return Codes

	NAME        :  MFILE Return Codes

	DESCRIPTION :  The MFILE return codes have the following meanings:

						(.) ''MFILE_SUCCESS'' means that the function invoked
						completed without error. ''MFILE_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''MFILE_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other MFILE error codes.

						(.) ''MFILE_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''MFILE_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''MFILE_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

	AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:  MFILE_SUCCESS
						MFILE_FAILURE
						MFILE_BAD_ARGS_FAILURE
						MFILE_MEMORY_FAILURE
						MFILE_SYSTEM_FAILURE
						MFILE Return Codes:MFILE_SUCCESS
						MFILE Return Codes:MFILE_FAILURE
						MFILE Return Codes:MFILE_BAD_ARGS_FAILURE
						MFILE Return Codes:MFILE_MEMORY_FAILURE
						MFILE Return Codes:MFILE_SYSTEM_FAILURE
						MFILE Manifest Constants:MFILE_SUCCESS
						MFILE Manifest Constants:MFILE_FAILURE
						MFILE Manifest Constants:MFILE_BAD_ARGS_FAILURE
						MFILE Manifest Constants:MFILE_MEMORY_FAILURE
						MFILE Manifest Constants:MFILE_SYSTEM_FAILURE
						MFILE Defines:MFILE_SUCCESS
						MFILE Defines:MFILE_FAILURE
						MFILE Defines:MFILE_BAD_ARGS_FAILURE
						MFILE Defines:MFILE_MEMORY_FAILURE
						MFILE Defines:MFILE_SYSTEM_FAILURE
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:  MFILE_SUCCESS
						MFILE_FAILURE
						MFILE_BAD_ARGS_FAILURE
						MFILE_MEMORY_FAILURE
						MFILE_SYSTEM_FAILURE
						MFILE Return Codes
						MFILE Return Code
						MFILE return codes
						MFILE return code
						MFILE Status Codes
						MFILE Status Code
						MFILE status codes
						MFILE status code
						MFILE Error Codes
						MFILE Error Code
						MFILE error codes
						MFILE error code

	PUBLISH NAME:	MFILE Return Codes
						MFILE return codes
						MFILE_SUCCESS
						MFILE_FAILURE
						MFILE_BAD_ARGS_FAILURE
						MFILE_MEMORY_FAILURE
						MFILE_SYSTEM_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MFILE_SUCCESS						 0
#define MFILE_FAILURE						-1
#define MFILE_BAD_ARGS_FAILURE			-2
#define MFILE_MEMORY_FAILURE				-3
#define MFILE_SYSTEM_FAILURE				-4
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME        :  MFILE_MAX_ERROR_TEXT

	DESCRIPTION :  The manifest constant ''MFILE_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a MFILE function.

	CAVEATS     :  MFILE error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''MFILE_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to MFILE functions can lead to overwriting of the
						heap or the stack.

	AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:  MFILE_MAX_ERROR_TEXT
						MFILE Manifest Constants:MFILE_MAX_ERROR_TEXT
						MFILE Defines:MFILE_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:	MFILE_MAX_ERROR_TEXT

	PUBLISH NAME:	MFILE_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define MFILE_MAX_ERROR_TEXT				1024
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Define some necessary manifest constants . . .								*/
/*	***********************************************************************	*/

#define MFILE_MODE_READ		  				1
#define MFILE_MODE_WRITE	  				2

#define MFILE_FLAG_READ		 				32
#define MFILE_FLAG_WRITTEN	 				64
#define MFILE_FLAG_IN_USE					128

#define MFILE_PRINTF_BUFFER_SIZE_MIN   ((unsigned long) 65536L)
#define MFILE_PRINTF_BUFFER_SIZE       (MFILE_PRINTF_BUFFER_SIZE_MIN * 16L)

#define MFILE_DEFAULT_FS_BLOCK_SIZE		512

/*	***********************************************************************	*/

/*
	Provides compatibility between the external and internal versions of the
	MFILE include files. Must be '#undef'ed at the end of this include file.
*/
/*	***********************************************************************	*/
#ifndef h__MFILEI_H__h
typedef void *MFILE;
#endif /* #ifndef h__MFILEI_H__h */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME        :	MFILE_LOG_CONTEXT

	DESCRIPTION :	The ''MFILE_LOG_CONTEXT'' structure contains the data
						needed to support logging to the context-driven MFILE
						logging functions.

						The ''MFILE_LOG_CONTEXT'' structure is declared as follows:

{|@|}typedef struct {
	int    mfile_flag;
	int    file_flag;
	int    syslog_flag;
	int    gmt_flag;
	MFILE *mfile_ptr;
	FILE  *file_ptr;
} MFILE_LOG_CONTEXT;

	MEMBERS		:	The members of this structure are as follow:

						(.) The ``mfile_flag`` member is an ''int'' which should be
						set to ''MFILE_TRUE'' if the context logging functions are
						to log messages to the memory-mapped file specified by the
						``mfile_ptr`` member.

						(.) The ``file_flag`` member is an ''int'' which should be
						set to ''MFILE_TRUE'' if the context logging functions are
						to log messages to the C level-two I/O file specified by the
						``file_ptr`` member.

						(.) The ``syslog_flag`` member is an ''int'' which should be
						set to ''MFILE_TRUE'' if the context logging functions are
						to log messages to the operating system ``syslog()``
						facility (where available).

						(.) The ``gmt_flag`` is an ''int'' which should be set to
						''MFILE_FALSE'' if logged messages are to use the local
						time, and ''MFILE_TRUE'' if logged messages are to use the
						UTC/GMT time.

						(.) The ``mfile_ptr`` member points to a structure of
						type ''MFILE'' which specifies the memory-mapped file to
						which messages are to be logged.

						(-) If ``mfile_ptr`` is a ''NULL'' pointer, or if the
						``mfile_flag`` member is ''0'', messages will not
						be logged to a memory-mapped file.

						(.) The ``file_ptr`` member points to a structure of type
						''FILE'' which specifies the C level-two I/O device to which
						messages are to be logged.

						(-) If ``file_ptr`` is a ''NULL'' pointer, or if the
						``file_flag`` member is ''0'', messages will not be
						logged to a C level-two I/O device.

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	MFILE_LOG_CONTEXT
						Structures and Data Types:MFILE_LOG_CONTEXT

	PUBLISH XREF:	MFILE_LOG_CONTEXT

	PUBLISH NAME:	MFILE_LOG_CONTEXT

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	int    mfile_flag;
	int    file_flag;
	int    syslog_flag;
	int    gmt_flag;
	MFILE *mfile_ptr;
	FILE  *file_ptr;
} MFILE_LOG_CONTEXT;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifdef MFILE_MMAP_NON_NATIVE
#define LOG_EMERG								0
#define LOG_ALERT								1
#define LOG_CRIT								2
#define LOG_ERR								3
#define LOG_WARNING							4
#define LOG_NOTICE							5
#define LOG_INFO								6
#define LOG_DEBUG								7
#endif /* #ifdef MFILE_MMAP_NON_NATIVE */
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MFILE_getpagesize					GEN_GetAllocGranularity()
/*	***********************************************************************	*/

/*
	CODE NOTE:	To be removed when code in 'eosomdqf' library is changed.
*/
/*	***********************************************************************	*/
#define MFILE_GET_file_size(mfile_ptr)			\
	MFILE_GetFileSize(mfile_ptr)
#define MFILE_GET_current_offset(mfile_ptr)	\
	MFILE_GetOffset(mfile_ptr)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for the MFILE functions . . .							*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for version functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void  MFILE_GetVersionNumber, (unsigned int *major,
	unsigned int *minor, unsigned int *release, unsigned int *build));
COMPAT_FN_DECL(char *MFILE_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MFILE core function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int    mclose, (MFILE *mfile_ptr));
COMPAT_FN_DECL(int    mcloseall, (void));
COMPAT_FN_DECL(int    mclose_no_unmap, (MFILE *mfile_ptr));
COMPAT_FN_DECL(int    mclose_to_offset, (MFILE *mfile_ptr));
COMPAT_FN_DECL(int    mflush, (MFILE *mfile_ptr));
COMPAT_FN_DECL(int    mflush_async, (MFILE *mfile_ptr, int async_flag));
COMPAT_FN_DECL(int    mflushall, (void));
COMPAT_FN_DECL(int    mgetc, (MFILE *mfile_ptr));
COMPAT_FN_DECL(char  *mgets, (char *buffer_ptr, int buffer_max,
	MFILE *mfile_ptr));
COMPAT_FN_DECL(MFILE *mopen, (const char *file_name, const char *file_mode));
#ifdef __GNUC__
COMPAT_FN_DECL(int    mprintf, (MFILE *mfile_ptr, const char *format_ptr, ...)
	__attribute__ ((format (printf, 2, 3))));
#else
# ifndef NO_STDARGS
COMPAT_FN_DECL(int    mprintf, (MFILE *mfile_ptr, const char *in_format, ...));
# else
COMPAT_FN_DECL(int    mprintf, (MFILE *mfile_ptr, const char *in_format,
	va_alist));
# endif /* # ifndef NO_STDARGS */
#endif /* #ifdef __GNUC__ */
COMPAT_FN_DECL(int    mprintf_ensure_space, (MFILE *mfile_ptr));
COMPAT_FN_DECL(int    mputc, (int put_char, MFILE *mfile_ptr));
COMPAT_FN_DECL(int    mputs, (const char *put_string, MFILE *mfile_ptr));
COMPAT_FN_DECL(int    mread, (void *data_ptr, unsigned int element_size,
	unsigned int element_count, MFILE *mfile_ptr));
COMPAT_FN_DECL(int    mremap, (MFILE *mfile_ptr));
COMPAT_FN_DECL(int    mremap_basic_1, (MFILE *mfile_ptr, unsigned long offset,
	unsigned long length));
COMPAT_FN_DECL(int    mremap_basic_2, (int file_handle,
	unsigned long *mmap_size, volatile void **mmap_ptr,
	unsigned long *current_offset, int mmap_prot, int mmap_flags,
	unsigned long offset, unsigned long length, int *fatal_error_flag));
COMPAT_FN_DECL(void   mrewind, (MFILE *mfile_ptr));
COMPAT_FN_DECL(int    mseek, (MFILE *mfile_ptr, long offset,
	int position_type));
COMPAT_FN_DECL(void   msetbuf, (MFILE *mfile_ptr, unsigned int buffer_size));
COMPAT_FN_DECL(int    msetflag, (MFILE *mfile_ptr, int mmap_prot,
	int mmap_flags));
COMPAT_FN_DECL(long   mtell, (MFILE *mfile_ptr));
COMPAT_FN_DECL(MFILE *mtmpfile, (const char *dir_name,
	const char *file_prefix));
COMPAT_FN_DECL(int    mtruncate, (MFILE *mfile_ptr, unsigned long length));
COMPAT_FN_DECL(int    mtruncate_safe, (MFILE *mfile_ptr,
	unsigned long length));
COMPAT_FN_DECL(int    mtruncate_basic_1, (MFILE *mfile_ptr,
	unsigned long length, int safe_flag));
COMPAT_FN_DECL(int    mtruncate_basic_2, (int file_handle,
	unsigned long *file_size, unsigned long *mmap_size,
	volatile void **mmap_ptr, unsigned long *current_offset, int mmap_prot,
	int mmap_flags, unsigned long length, int safe_flag,
	int *fatal_error_flag));
COMPAT_FN_DECL(int    munlink, (MFILE *mfile_ptr));
COMPAT_FN_DECL(int    mwrite, (const void *data_ptr,
	unsigned int element_size, unsigned int element_count, MFILE *mfile_ptr));
COMPAT_FN_DECL(int    vmprintf, (MFILE *mfile_ptr, const char *in_format,
	va_list arg_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MFILE locking function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MFILE_Lock,    (MFILE *mfile_ptr, char *error_text));
COMPAT_FN_DECL(int MFILE_TryLock, (MFILE *mfile_ptr, char *error_text));
COMPAT_FN_DECL(int MFILE_Unlock,  (MFILE *mfile_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Get the MFILE structure state function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(const char    *MFILE_GetFileName,       (MFILE *mfile_ptr));
COMPAT_FN_DECL(volatile void *MFILE_GetMMapPtr,        (MFILE *mfile_ptr));
COMPAT_FN_DECL(int            MFILE_GetFileHandle,     (MFILE *mfile_ptr));
COMPAT_FN_DECL(FILE          *MFILE_GetFileDescriptor, (MFILE *mfile_ptr));
COMPAT_FN_DECL(unsigned long  MFILE_GetFileSize,       (MFILE *mfile_ptr));
COMPAT_FN_DECL(unsigned long  MFILE_GetMMapSize,       (MFILE *mfile_ptr));
COMPAT_FN_DECL(unsigned long  MFILE_GetOffset,         (MFILE *mfile_ptr));
COMPAT_FN_DECL(unsigned long  MFILE_GetBufferSize,     (MFILE *mfile_ptr));
COMPAT_FN_DECL(int            MFILE_GetMFileFlags,     (MFILE *mfile_ptr));
COMPAT_FN_DECL(int            MFILE_GetMMapProt,       (MFILE *mfile_ptr));
COMPAT_FN_DECL(int            MFILE_GetMMapFlags,      (MFILE *mfile_ptr));
COMPAT_FN_DECL(int            MFILE_GetMMapMode,       (MFILE *mfile_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MFILE logging function prototypes . . .
		*****************************************************************	*/
# ifdef __GNUC__
COMPAT_FN_DECL(void MFILE_LogMessage, (struct timeval *timeval_ptr,
	int log_priority, MFILE *mfile_ptr, FILE *file_ptr, int syslog_flag,
	const char *format_ptr, ...) __attribute__ ((format (printf, 6, 7))));
COMPAT_FN_DECL(void MFILE_LogMessageContext,
	(MFILE_LOG_CONTEXT *log_context_ptr, struct timeval *timeval_ptr,
	int log_priority, int syslog_flag, const char *format_ptr, ...)
	__attribute__ ((format (printf, 5, 6))));
# else
#  ifndef NO_STDARGS
COMPAT_FN_DECL(void MFILE_LogMessage, (struct timeval *timeval_ptr,
	int log_priority, MFILE *mfile_ptr, FILE *file_ptr, int syslog_flag,
	const char *in_format, ...));
COMPAT_FN_DECL(void MFILE_LogMessageContext,
	(MFILE_LOG_CONTEXT *log_context_ptr, struct timeval *timeval_ptr,
	int log_priority, int syslog_flag, const char *format_ptr, ...));
#  else
COMPAT_FN_DECL(void MFILE_LogMessage, (struct timeval *timeval_ptr,
	int log_priority, MFILE *mfile_ptr, FILE *file_ptr, int syslog_flag,
	const char *in_format, va_alist));
COMPAT_FN_DECL(void MFILE_LogMessageContext,
	(MFILE_LOG_CONTEXT *log_context_ptr, struct timeval *timeval_ptr,
	int log_priority, int syslog_flag, const char *format_ptr, va_alist));
#  endif /* #ifndef NO_STDARGS */
# endif /* #ifdef __GNUC__ */
COMPAT_FN_DECL(void MFILE_InitLogContext,
	(MFILE_LOG_CONTEXT *log_context_ptr));
COMPAT_FN_DECL(int  MFILE_LogEnsureSpace, (MFILE *mfile_ptr));
COMPAT_FN_DECL(void MFILE_LogSepStartLogContext,
	(MFILE_LOG_CONTEXT *log_context_ptr));
COMPAT_FN_DECL(void MFILE_LogSepStartLog, (MFILE *mfile_ptr, FILE *file_ptr));
COMPAT_FN_DECL(void MFILE_LogSepEndLogContext,
	(MFILE_LOG_CONTEXT *log_context_ptr));
COMPAT_FN_DECL(void MFILE_LogSepEndLog, (MFILE *mfile_ptr, FILE *file_ptr));
COMPAT_FN_DECL(void MFILE_LogSepHyphenCharContext,
	(MFILE_LOG_CONTEXT *log_context_ptr));
COMPAT_FN_DECL(void MFILE_LogSepHyphenChar, (MFILE *mfile_ptr,
	FILE *file_ptr));
COMPAT_FN_DECL(void MFILE_LogSepEqualCharContext,
	(MFILE_LOG_CONTEXT *log_context_ptr));
COMPAT_FN_DECL(void MFILE_LogSepEqualChar, (MFILE *mfile_ptr, FILE *file_ptr));
COMPAT_FN_DECL(void MFILE_LogSepCharContext,
	(MFILE_LOG_CONTEXT *log_context_ptr,
	int log_char));
COMPAT_FN_DECL(void MFILE_LogSepChar, (MFILE *mfile_ptr, FILE *file_ptr,
	int log_char));
COMPAT_FN_DECL(void MFILE_LogSepStringContext,
	(MFILE_LOG_CONTEXT *log_context_ptr, const char *log_string));
COMPAT_FN_DECL(void MFILE_LogSepString, (MFILE *mfile_ptr, FILE *file_ptr,
	const char *log_string));
COMPAT_FN_DECL(int  MFILE_GetLogMessageFlagFILE, (void));
COMPAT_FN_DECL(int  MFILE_GetLogMessageFlagMFILE, (void));
COMPAT_FN_DECL(int  MFILE_GetLogMessageFlagSYSLOG, (void));
COMPAT_FN_DECL(int  MFILE_GetLogMessageFlagGMT, (void));
COMPAT_FN_DECL(int  MFILE_SetLogMessageFlagFILE, (int new_flag_value));
COMPAT_FN_DECL(int  MFILE_SetLogMessageFlagMFILE, (int new_flag_value));
COMPAT_FN_DECL(int  MFILE_SetLogMessageFlagSYSLOG, (int new_flag_value));
COMPAT_FN_DECL(int  MFILE_SetLogMessageFlagGMT, (int new_flag_value));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Executable logging support function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void MFILE_ShowExecTime, (const struct timeval *start_time,
	const struct timeval *end_time, const struct timeval *overhead_end_time,
	MFILE_LOG_CONTEXT *log_context_ptr));
COMPAT_FN_DECL(void MFILE_ShowExecRUsage,
	(MFILE_LOG_CONTEXT *log_context_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Miscellaneous support function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int  MFILE_EnsureSpace, (MFILE *mfile_ptr,
	unsigned int in_buffer_size, unsigned int in_min_size, char *error_text));
COMPAT_FN_DECL(void MFILE_EMIT_SetDefaults,
	(STR_FUNC_TYPE_fprintf *output_function, void **output_control));
COMPAT_FN_DECL(void MFILE_EMIT_SetDefaultsVA,
	(STR_FUNC_TYPE_vfprintf *output_function, void **output_control));
COMPAT_FN_DECL(STR_CFILE_FUNCS *MFILE_EMIT_SetDefaultsCFILE_FUNCS,
	(STR_CFILE_FUNCS *cfile_funcs_ptr));
COMPAT_FN_DECL(STR_CFILE_FUNCS *MFILE_EMIT_GetDefaultsCFILE_FUNCS,
	(STR_CFILE_FUNCS *cfile_funcs_ptr));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

/*
	Provides compatibility between the external and internal versions of the
	MFILE include files.
*/
/*	***********************************************************************	*/
#ifdef h__MFILEI_H__h
# undef MFILE
#endif /* #ifdef h__MFILEI_H__h */
/*	***********************************************************************	*/

#endif /* #ifndef h__MFILE_H__h */

