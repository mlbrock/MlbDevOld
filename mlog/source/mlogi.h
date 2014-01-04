/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Internal Include File						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Memory-mapped Logging
								Facility (MLOG).

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__MLOGI_H__h

#define h__MLOGI_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <mtif.h>
#include <mfile.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Temporary definition to get 'mlog.h' included . . .                     */
/*	***********************************************************************	*/
#define MLOG struct tag_MLOG
struct tag_MLOG;
# include "mlog.h"
#undef MLOG
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MLOG Library Version Number

   NAME        :	MLOG Library Version Number

   DESCRIPTION :	The MLOG library version number manifest constants
						together define the current version number of the MLOG
						library as a whole.

						(.) ''MLOG_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''MLOG_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''MLOG_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''MLOG_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	MLOG_VERSION_MAJOR
						MLOG_VERSION_MINOR
						MLOG_VERSION_RELEASE
						MLOG_VERSION_BUILD
						MLOG Version Numbers:Library Version Number
						Library Version Number:MLOG_VERSION_MAJOR
						Library Version Number:MLOG_VERSION_MINOR
						Library Version Number:MLOG_VERSION_RELEASE
						Library Version Number:MLOG_VERSION_BUILD
						Macros and Manifest Constants:MLOG_VERSION_MAJOR
						Macros and Manifest Constants:MLOG_VERSION_MINOR
						Macros and Manifest Constants:MLOG_VERSION_RELEASE
						Macros and Manifest Constants:MLOG_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MLOG_VERSION_MAJOR
						MLOG_VERSION_MINOR
						MLOG_VERSION_RELEASE
						MLOG_VERSION_BUILD
						MLOG Library Version Number
						MLOG library version number
						MLOG Library Version
						MLOG library version
						MLOG Version Number
						MLOG version number
						MLOG Version
						MLOG version

   PUBLISH NAME:	MLOG_VERSION_MAJOR
						MLOG_VERSION_MINOR
						MLOG_VERSION_RELEASE
						MLOG_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						MLOG Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define MLOG_VERSION_MAJOR					((unsigned char) 1)
#define MLOG_VERSION_MINOR					((unsigned char) 0)
#define MLOG_VERSION_RELEASE				((unsigned char) 0)
#define MLOG_VERSION_BUILD					((unsigned char) 'A')
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MLOG Truth Code Mappings

   NAME        :	MLOG Truth Code Mappings

	SYNOPSIS		:	truth_code = MLOG_MAP_TRUTH_STR(str_code);

						truth_code = MLOG_MAP_TRUTH_GEN(gen_code);

						truth_code = MLOG_MAP_TRUTH_MTIF(mitf_code);

						truth_code = MLOG_MAP_TRUTH_DAT(dat_code);

						truth_code = MLOG_MAP_TRUTH_MRG(mrg_code);

						truth_code = MLOG_MAP_TRUTH_MFILE(mfile_code);

	DESCRIPTION	:	The MLOG truth code mapping macros map truth codes from
						various low-level libraries to MLOG truth codes.

						(.) ''MLOG_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a MLOG truth code.

						(.) ''MLOG_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a MLOG truth code.

						(.) ''MLOG_MAP_TRUTH_MTIF'' maps a truth code
						from a MTIF truth code to a MLOG truth code.

						(.) ''MLOG_MAP_TRUTH_DAT'' maps a truth code
						from a DATFUNCS truth code to a MLOG truth code.

						(.) ''MLOG_MAP_TRUTH_MRG'' maps a truth code
						from a MRG truth code to a MLOG truth code.

						(.) ''MLOG_MAP_TRUTH_MFILE'' maps a truth code
						from a MFILE truth code to a MLOG truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent MLOG truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						MLOG return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	MLOG_MAP_TRUTH_STR
						MLOG_MAP_TRUTH_GEN
						MLOG_MAP_TRUTH_MTIF
						MLOG_MAP_TRUTH_DAT
						MLOG_MAP_TRUTH_MRG
						MLOG_MAP_TRUTH_MFILE
						Truth Code Mappings:MLOG_MAP_TRUTH_STR
						Truth Code Mappings:MLOG_MAP_TRUTH_GEN
						Truth Code Mappings:MLOG_MAP_TRUTH_MTIF
						Truth Code Mappings:MLOG_MAP_TRUTH_DAT
						Truth Code Mappings:MLOG_MAP_TRUTH_MRG
						Truth Code Mappings:MLOG_MAP_TRUTH_MFILE
						Macros and Manifest Constants:MLOG_MAP_TRUTH_STR
						Macros and Manifest Constants:MLOG_MAP_TRUTH_GEN
						Macros and Manifest Constants:MLOG_MAP_TRUTH_MTIF
						Macros and Manifest Constants:MLOG_MAP_TRUTH_DAT
						Macros and Manifest Constants:MLOG_MAP_TRUTH_MRG
						Macros and Manifest Constants:MLOG_MAP_TRUTH_MFILE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MLOG_MAP_TRUTH_STR
						MLOG_MAP_TRUTH_GEN
						MLOG_MAP_TRUTH_MTIF
						MLOG_MAP_TRUTH_DAT
						MLOG_MAP_TRUTH_MRG
						MLOG_MAP_TRUTH_MFILE
						MLOG Truth Code Mappings
						MLOG Truth Code Mapping
						MLOG truth code mappings
						MLOG truth code mapping

   PUBLISH NAME:	MLOG_MAP_TRUTH_STR
						MLOG_MAP_TRUTH_GEN
						MLOG_MAP_TRUTH_MTIF
						MLOG_MAP_TRUTH_DAT
						MLOG_MAP_TRUTH_MRG
						MLOG_MAP_TRUTH_MFILE

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define MLOG_MAP_TRUTH_STR(str_code)		\
	(((str_code) == STRFUNCS_TRUE) ? MLOG_TRUE : MLOG_FALSE)
#define MLOG_MAP_TRUTH_GEN(gen_code)		\
	(((gen_code) == GENFUNCS_TRUE) ? MLOG_TRUE : MLOG_FALSE)
#define MLOG_MAP_TRUTH_MTIF(mitf_code)		\
	(((mtif_code) == MTIF_TRUE)    ? MLOG_TRUE : MLOG_FALSE)
#define MLOG_MAP_TRUTH_DAT(dat_code)		\
	(((dat_code) == DATFUNCS_TRUE) ? MLOG_TRUE : MLOG_FALSE)
#define MLOG_MAP_TRUTH_MRG(mrg_code)		\
	(((mrg_code) == SPF_TRUE)      ? MLOG_TRUE : MLOG_FALSE)
#define MLOG_MAP_TRUTH_MFILE(mfile_code)	\
	(((mfile_code) == MFILE_TRUE)  ? MLOG_TRUE : MLOG_FALSE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MLOG Return Code Mappings

   NAME        :	MLOG Return Code Mappings

	SYNOPSIS		:	return_code = MLOG_MAP_ERROR_STR(str_code);

						return_code = MLOG_MAP_ERROR_GEN(gen_code);

						return_code = MLOG_MAP_ERROR_MTIF(mtif_code);

						return_code = MLOG_MAP_ERROR_DAT(dat_code);

						return_code = MLOG_MAP_ERROR_MRG(mrg_code);

						return_code = MLOG_MAP_ERROR_MFILE(mrg_code);

	DESCRIPTION	:	The MLOG return code mapping macros map return codes from
						various low-level libraries to MLOG return codes.

						(.) ''MLOG_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a MLOG return code.

						(.) ''MLOG_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a MLOG return code.

						(.) ''MLOG_MAP_ERROR_MTIF'' maps a return code
						from a MTIF return code to a MLOG return code.

						(.) ''MLOG_MAP_ERROR_DAT'' maps a return code
						from a DATFUNCS return code to a MLOG return code.

						(.) ''MLOG_MAP_ERROR_MRG'' maps a return code
						from a MRG return code to a MLOG return code.

						(.) ''MLOG_MAP_ERROR_MFILE'' maps a return code
						from a MFILE return code to a MLOG return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent MLOG return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						MLOG truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	MLOG_MAP_ERROR_STR
						MLOG_MAP_ERROR_GEN
						MLOG_MAP_ERROR_MTIF
						MLOG_MAP_ERROR_DAT
						MLOG_MAP_ERROR_MRG
						MLOG_MAP_ERROR_MFILE
						Return Code Mappings:MLOG_MAP_ERROR_STR
						Return Code Mappings:MLOG_MAP_ERROR_GEN
						Return Code Mappings:MLOG_MAP_ERROR_MTIF
						Return Code Mappings:MLOG_MAP_ERROR_DAT
						Return Code Mappings:MLOG_MAP_ERROR_MRG
						Return Code Mappings:MLOG_MAP_ERROR_MFILE
						Macros and Manifest Constants:MLOG_MAP_ERROR_STR
						Macros and Manifest Constants:MLOG_MAP_ERROR_GEN
						Macros and Manifest Constants:MLOG_MAP_ERROR_MTIF
						Macros and Manifest Constants:MLOG_MAP_ERROR_DAT
						Macros and Manifest Constants:MLOG_MAP_ERROR_MRG
						Macros and Manifest Constants:MLOG_MAP_ERROR_MFILE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MLOG_MAP_ERROR_STR
						MLOG_MAP_ERROR_GEN
						MLOG_MAP_ERROR_MTIF
						MLOG_MAP_ERROR_DAT
						MLOG_MAP_ERROR_MRG
						MLOG_MAP_ERROR_MFILE
						MLOG Return Code Mappings
						MLOG Return Code Mapping
						MLOG return code mappings
						MLOG return code mapping
						MLOG Status Code Mappings
						MLOG Status Code Mapping
						MLOG status code mappings
						MLOG status code mapping
						MLOG Error Code Mappings
						MLOG Error Code Mapping
						MLOG error code mappings
						MLOG error code mapping

   PUBLISH NAME:	MLOG_MAP_ERROR_STR
						MLOG_MAP_ERROR_GEN
						MLOG_MAP_ERROR_MTIF
						MLOG_MAP_ERROR_DAT
						MLOG_MAP_ERROR_MRG
						MLOG_MAP_ERROR_MFILE

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define MLOG_MAP_ERROR_STR(str_code)										 		\
	(((str_code) == STRFUNCS_SUCCESS)          ? MLOG_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? MLOG_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? MLOG_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? MLOG_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? MLOG_SYSTEM_FAILURE   :	\
	 MLOG_FAILURE)
#define MLOG_MAP_ERROR_GEN(gen_code)												\
	(((gen_code) == GENFUNCS_SUCCESS)          ? MLOG_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? MLOG_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? MLOG_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? MLOG_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? MLOG_SYSTEM_FAILURE   :	\
	 ((gen_code) == GENFUNCS_LOCK_ACQ_FAILURE) ? MLOG_LOCK_ACQ_FAILURE :	\
	 MLOG_FAILURE)
#define MLOG_MAP_ERROR_MTIF(mtif_code)												\
	(((mtif_code) == MTIF_SUCCESS)             ? MLOG_SUCCESS          :	\
	 ((mtif_code) == MTIF_FAILURE)             ? MLOG_FAILURE          :	\
	 ((mtif_code) == MTIF_BAD_ARGS_FAILURE)    ? MLOG_BAD_ARGS_FAILURE :	\
	 ((mtif_code) == MTIF_MEMORY_FAILURE)      ? MLOG_MEMORY_FAILURE   :	\
	 ((mtif_code) == MTIF_SYSTEM_FAILURE)      ? MLOG_SYSTEM_FAILURE   :	\
	 ((mtif_code) == MTIF_LOCK_ACQ_FAILURE)    ? MLOG_LOCK_ACQ_FAILURE :	\
	 MLOG_FAILURE)
#define MLOG_MAP_ERROR_DAT(dat_code)												\
	(((dat_code) == DATFUNCS_SUCCESS)          ? MLOG_SUCCESS          :	\
	 ((dat_code) == DATFUNCS_FAILURE)          ? MLOG_FAILURE          :	\
	 ((dat_code) == DATFUNCS_MEMORY_FAILURE)   ? MLOG_MEMORY_FAILURE   :	\
	 MLOG_FAILURE)
#define MLOG_MAP_ERROR_MRG(mrg_code)												\
	(((mrg_code) == MRG_SUCCESS)               ? MLOG_SUCCESS          :	\
	 ((mrg_code) == MRG_FAILURE)               ? MLOG_FAILURE          :	\
	 ((mrg_code) == MRG_BAD_ARGS_FAILURE)      ? MLOG_BAD_ARGS_FAILURE :	\
	 ((mrg_code) == MRG_MEMORY_FAILURE)        ? MLOG_MEMORY_FAILURE   :	\
	 ((mrg_code) == MRG_SYSTEM_FAILURE)        ? MLOG_SYSTEM_FAILURE   :	\
	 MLOG_FAILURE)
#define MLOG_MAP_ERROR_MFILE(mfile_code)											\
	(((mfile_code) == MFILE_SUCCESS)           ? MLOG_SUCCESS          :	\
	 ((mfile_code) == MFILE_FAILURE)           ? MLOG_FAILURE          :	\
	 ((mfile_code) == MFILE_BAD_ARGS_FAILURE)  ? MLOG_BAD_ARGS_FAILURE :	\
	 ((mfile_code) == MFILE_MEMORY_FAILURE)    ? MLOG_MEMORY_FAILURE   :	\
	 ((mfile_code) == MFILE_SYSTEM_FAILURE)    ? MLOG_SYSTEM_FAILURE   :	\
	 MLOG_FAILURE)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_getpagesize					MFILE_getpagesize
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_PRIORITY_NAME_MAX			13

#define MLOG_GET_PRIORITY_NAME(log_priority)								\
	(((log_priority) == MLOG_PRIORITY_EMERG)   ? "EMERGENCY"     :	\
	 ((log_priority) == MLOG_PRIORITY_ALERT)   ? "ALERT"         :	\
	 ((log_priority) == MLOG_PRIORITY_CRIT)    ? "CRITICAL"      :	\
	 ((log_priority) == MLOG_PRIORITY_ERR)     ? "ERROR"         :	\
	 ((log_priority) == MLOG_PRIORITY_WARNING) ? "WARNING"       :	\
	 ((log_priority) == MLOG_PRIORITY_NOTICE)  ? "NOTICE"        :	\
	 ((log_priority) == MLOG_PRIORITY_INFO)    ? "INFORMATIONAL" :	\
	 ((log_priority) == MLOG_PRIORITY_DEBUG)   ? "DEBUGGING"     :	\
	 "UNKNOWN")

#ifdef _Windows
# define MLOG_OS_HAS_NO_SYSLOG			1
#endif /* #ifdef _Windows */

#ifndef MLOG_OS_HAS_NO_SYSLOG
# define MLOG_MAP_PRIORITY_TO_OS(log_priority)						\
	(((log_priority) == MLOG_PRIORITY_EMERG)   ? LOG_EMERG   :	\
	 ((log_priority) == MLOG_PRIORITY_ALERT)   ? LOG_ALERT   :	\
	 ((log_priority) == MLOG_PRIORITY_CRIT)    ? LOG_CRIT    :	\
	 ((log_priority) == MLOG_PRIORITY_ERR)     ? LOG_ERR     :	\
	 ((log_priority) == MLOG_PRIORITY_WARNING) ? LOG_WARNING :	\
	 ((log_priority) == MLOG_PRIORITY_NOTICE)  ? LOG_NOTICE  :	\
	 ((log_priority) == MLOG_PRIORITY_INFO)    ? LOG_INFO    :	\
	 ((log_priority) == MLOG_PRIORITY_DEBUG)   ? LOG_DEBUG   :	\
	 LOG_INFO)
#else
# define MLOG_MAP_PRIORITY_TO_OS(log_priority)	(0)
#endif /* #ifndef MLOG_OS_HAS_NO_SYSLOG */
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_DO_LOG_MFILE_BASIC(mlog_ptr, flags)							\
	MLOG_MAP_TRUTH(MLOG_IS_PTR_I(mlog_ptr) &&									\
	 ((mlog_ptr)->mfile_ptr != NULL)     && ((flags) & MLOG_FLAG_MFILE))
#define MLOG_DO_LOG_FILE_BASIC(mlog_ptr, flags)								\
	MLOG_MAP_TRUTH(MLOG_IS_PTR_I(mlog_ptr) &&									\
	 ((mlog_ptr)->file_ptr != NULL)      && ((flags) & MLOG_FLAG_FILE))
#define MLOG_DO_LOG_SYSLOG_BASIC(mlog_ptr, flags)							\
	MLOG_MAP_TRUTH(MLOG_IS_PTR_I(mlog_ptr) && ((flags) & MLOG_FLAG_SYSLOG))
#define MLOG_DO_LOG_EITHER_FILE_BASIC(mlog_ptr, flags)					\
	MLOG_MAP_TRUTH(MLOG_DO_LOG_MFILE_BASIC(mlog_ptr, flags) |			\
		MLOG_DO_LOG_FILE_BASIC(mlog_ptr, flags))
#define MLOG_DO_LOG_BASIC(mlog_ptr, flags)									\
	MLOG_MAP_TRUTH(MLOG_DO_LOG_EITHER_FILE_BASIC(mlog_ptr, flags) |	\
	MLOG_DO_LOG_SYSLOG_BASIC(mlog_ptr, flags))
	/*	*****************************************************************	*/
#define MLOG_DO_LOG_MFILE(mlog_ptr)				\
	MLOG_DO_LOG_MFILE_BASIC(mlog_ptr, (mlog_ptr)->flags)
#define MLOG_DO_LOG_FILE(mlog_ptr)				\
	MLOG_DO_LOG_FILE_BASIC(mlog_ptr, (mlog_ptr)->flags)
#define MLOG_DO_LOG_SYSLOG(mlog_ptr)			\
	MLOG_DO_LOG_SYSLOG_BASIC(mlog_ptr, (mlog_ptr)->flags)
#define MLOG_DO_LOG_EITHER_FILE(mlog_ptr)		\
	MLOG_DO_LOG_EITHER_FILE_BASIC(mlog_ptr, (mlog_ptr)->flags)
#define MLOG_DO_LOG(mlog_ptr)						\
	MLOG_DO_LOG_BASIC(mlog_ptr, (mlog_ptr)->flags)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_DO_PRIORITY_MFILE_BASIC(mlog_ptr, flags, priority, mfile_mask)	\
	MLOG_MAP_TRUTH(MLOG_DO_LOG_MFILE_BASIC(mlog_ptr, flags)  &&						\
	 ((mfile_mask) & (priority)))
#define MLOG_DO_PRIORITY_FILE_BASIC(mlog_ptr, flags, priority, file_mask)		\
	MLOG_MAP_TRUTH(MLOG_DO_LOG_FILE_BASIC(mlog_ptr, flags)   &&						\
	 ((file_mask) & (priority)))
#define MLOG_DO_PRIORITY_SYSLOG_BASIC(mlog_ptr, flags, priority, syslog_mask)	\
	MLOG_MAP_TRUTH(MLOG_DO_LOG_SYSLOG_BASIC(mlog_ptr, flags) &&						\
	 ((syslog_mask) & (priority)))
#define MLOG_DO_PRIORITY_BASIC(mlog_ptr, flags, priority,							\
	mfile_mask, file_mask, syslog_mask)														\
	MLOG_MAP_TRUTH(																				\
		MLOG_DO_PRIORITY_MFILE_BASIC(mlog_ptr, flags, priority, mfile_mask) |	\
	 MLOG_DO_PRIORITY_FILE_BASIC(mlog_ptr, flags, priority, file_mask)     |	\
	 MLOG_DO_PRIORITY_SYSLOG_BASIC(mlog_ptr, flags, priority, syslog_mask))
	/*	*****************************************************************	*/
#define MLOG_DO_PRIORITY_MFILE(mlog_ptr, priority)					\
	MLOG_DO_PRIORITY_MFILE_BASIC(mlog_ptr, priority, (mlog_ptr)->mfile_mask)
#define MLOG_DO_PRIORITY_FILE(mlog_ptr, priority)					\
	MLOG_DO_PRIORITY_FILE_BASIC(mlog_ptr, priority, (mlog_ptr)->file_mask)
#define MLOG_DO_PRIORITY_SYSLOG(mlog_ptr, priority)				\
	MLOG_DO_PRIORITY_SYSLOG_BASIC(mlog_ptr, priority, (mlog_ptr)->syslog_mask)
#define MLOG_DO_PRIORITY(mlog_ptr, priority)							\
	MLOG_MAP_TRUTH(MLOG_DO_PRIORITY_MFILE(mlog_ptr, priority) |	\
	 MLOG_DO_PRIORITY_FILE(mlog_ptr, priority)  |					\
	 MLOG_DO_PRIORITY_SYSLOG(mlog_ptr, priority))
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef unsigned long MLOG_SIGNATURE;

#define MLOG_SIGNATURE_NONE				((MLOG_SIGNATURE) 0X00000000UL)
#define MLOG_SIGNATURE_OK 					((MLOG_SIGNATURE) 0XA28C307CUL)

#define MLOG_IS_SIG(ptr)					\
	MLOG_MAP_TRUTH((ptr)->signature == MLOG_SIGNATURE_OK)
/*
	CODE NOTE: Not used at present.
#define MLOG_IS_VALID_PTR(ptr)			\
	MLOG_MAP_TRUTH_GEN(GEN_VPTR_IsValidArea(((void *) (ptr)), sizeof(MLOG),	\
	GEN_VPTR_ACCESS_READ_WRITE, NULL))
*/
#define MLOG_IS_VALID_PTR(ptr)			MLOG_MAP_TRUTH((ptr) != NULL)

#define MLOG_IS_PTR_I(ptr)					\
	MLOG_MAP_TRUTH(MLOG_IS_VALID_PTR(ptr) && MLOG_IS_SIG(ptr))
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_MTR_INIT_FLAGS				MTIF_MTR_FLAG_IGNORE_BAD
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_FORMAT_CHAR_DATE				'D'
#define MLOG_FORMAT_CHAR_TIME_0			'0'
#define MLOG_FORMAT_CHAR_TIME_1			'1'
#define MLOG_FORMAT_CHAR_TIME_2			'2'
#define MLOG_FORMAT_CHAR_TIME_3			'3'
#define MLOG_FORMAT_CHAR_TIME_4			'4'
#define MLOG_FORMAT_CHAR_TIME_5			'5'
#define MLOG_FORMAT_CHAR_TIME_6			'6'
#define MLOG_FORMAT_CHAR_TIME				'T'
#define MLOG_FORMAT_CHAR_PRIORITY		'M'
#define MLOG_FORMAT_CHAR_PID				'P'
#define MLOG_FORMAT_CHAR_TID				'L'
#define MLOG_FORMAT_CHAR_USER				'U'
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_FORMAT_VALID_STRING			"D0123456TMPLU"
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_FORMAT_INDEX_DATE			0
#define MLOG_FORMAT_INDEX_TIME			1
#define MLOG_FORMAT_INDEX_PRIORITY		2
#define MLOG_FORMAT_INDEX_PID				4
#define MLOG_FORMAT_INDEX_TID				5
#define MLOG_FORMAT_INDEX_USER			6

#define MLOG_FORMAT_COUNT					7
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct {
	unsigned int index;
	unsigned int offset;
	unsigned int length;
} MLOG_FORMAT;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
typedef struct tag_MLOG {
	MLOG_SIGNATURE   signature;
	int              mtr_data_init_flag;
	MTIF_MTR_HANDLE  mtr_data;
	MLOG_FLAG        flags;
	MLOG_PRIORITY    mfile_mask;
	MLOG_PRIORITY    file_mask;
	MLOG_PRIORITY    syslog_mask;
	unsigned int     initial_alloc;
	unsigned int     added_alloc;
	char            *log_format;
	char            *user_string;
	unsigned int     format_count;
	MLOG_FORMAT     *format_list;
	unsigned int     used_length;
	unsigned int     work_length;
	char            *work_string;
	unsigned int     sep_length;
	MFILE           *mfile_ptr;
	FILE            *file_ptr;
	int              may_log_flag;		/* CODE NOTE: Not yet implemented.	*/
	int              pdebug_flag;
} MLOG;
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MLOG_GET_MFILE_PTR(ptr)			((ptr)->mfile_ptr)
#define MLOG_GET_FILE_PTR(ptr)			((ptr)->file_ptr)
#define MLOG_GET_FILE_NAME_I(ptr)		\
	MFILE_GetFileName(MLOG_GET_MFILE_PTR(ptr))
#define MLOG_GET_FILE_HANDLE(ptr)		\
	MFILE_GetFileDescriptor(MLOG_GET_MFILE_PTR(ptr))
#define MLOG_GET_FILE_LENGTH(ptr)		\
	MFILE_GetFileSize(MLOG_GET_MFILE_PTR(ptr))
#define MLOG_GET_BASE_ADDR(ptr)			(NULL)
#define MLOG_GET_MMAP_PTR(ptr)			\
	((void *) MFILE_GetMMapPtr(MLOG_GET_MFILE_PTR(ptr)))
#define MLOG_GET_MMAP_LENGTH(ptr)		\
	MFILE_GetMMapSize(MLOG_GET_MFILE_PTR(ptr))
#define MLOG_GET_MMAP_OFFSET(ptr)		(0)
#define MLOG_GET_MMAP_FLAGS(ptr)			\
	MFILE_GetMMapFlags(MLOG_GET_MFILE_PTR(ptr))
#define MLOG_GET_PROT_FLAGS(ptr)			\
	MFILE_GetMMapProt(MLOG_GET_MFILE_PTR(ptr))
#define MLOG_GET_OS_MMAP_HANDLE(ptr)	(NULL)
#define MLOG_GET_CURR_OFFSET(ptr)		\
	MFILE_GetOffset(MLOG_GET_MFILE_PTR(ptr))
#define MLOG_GET_ACTUAL_OFFSET(ptr)		\
	MFILE_GetOffset(MLOG_GET_MFILE_PTR(ptr))
#define MLOG_GET_MMAP_PTRC(ptr)			((char *) MLOG_GET_MMAP_PTR(ptr))
#define MLOG_GET_OFFSET_PTRC(ptr)		\
	(MLOG_GET_MMAP_PTRC(ptr) + MLOG_GET_CURR_OFFSET(ptr))
#define MLOG_GET_OFFSET_PTR(ptr)			\
	((void *) MLOG_GET_OFFSET_PTRC(ptr))
#define MLOG_GET_FLAGS_I(ptr)				((ptr)->flags)
#define MLOG_GET_MASK_MFILE(ptr)			((ptr)->mfile_mask)
#define MLOG_GET_MASK_FILE(ptr)			((ptr)->file_mask)
#define MLOG_GET_MASK_SYSLOG(ptr)		((ptr)->syslog_mask)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for the internal MLOG functions . . .				*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototypes for data management functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void MLOG_Free, (MLOG *mlog_ptr));
COMPAT_FN_DECL(void MLOG_Init, (MLOG *mlog_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Function prototype for the internal log format function . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MLOG_SetLogFormatBasic, (MLOG *mlog_ptr,
	const char *in_log_format, const char *in_user_string, char *error_text));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__MLOGI_H__h */

