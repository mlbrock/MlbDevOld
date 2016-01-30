/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Include File							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Automated Documentation Facility.

	Revision History	:	1994-06-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#ifndef h__ADF_H__h

#define h__ADF_H__h	1

#include <strfuncs.h>
#include <sdtif.h>
#include <genfuncs.h>
#include <spffuncs.h>
#include <mfile.h>
#include <mlog.h>

#include <limits.h>
#include <stdio.h>
#include <time.h>

#ifndef _Windows
# include <syslog.h>
# include <sys/param.h>
#endif /* #ifndef _Windows */

/*
	CODE NOTE: To be removed after SunOS & Solaris testing
#include <sys/resource.h>
*/

#ifndef NO_STDARGS
# include <stdarg.h>
#else
# include <varargs.h>
#endif /* #ifndef NO_STDARGS */

#ifdef __SVR4
# include <netdb.h>
#endif /* #ifdef _SVR5 */

#ifdef _Windows
# include <windows.h>
#endif /* #ifdef _Windows */

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* 	The macro 'offsetof' is defined by ANSI C. If it's not available on	*/
/* this system, define it . . .															*/
/* *********************************************************************** */

#ifndef offsetof
# define offsetof(structure_name, member_name) \
	((size_t) &(((structure_name *) 0)->member_name))
#endif /* #ifndef offsetof */

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_PATTERN_SPACE_CHAR			'\001'

#define ADF_DB_SIGNATURE_1					"Automated Documentation Facility (ADF)"
#define ADF_DB_SIGNATURE_2					"--------- ------------- -------- -----"
#define ADF_DB_COPYRIGHT					"Copyright 1992-2003, Michael L. Brock"
#define ADF_DB_END_SIGNATURE				"END_OF_ADF_FILE"

#define ADF_VERSION							"01.00.00"

#define ADF_FILE_INCOMPLETE_FLAG			((unsigned long) 0L)
#define ADF_FILE_COMPLETE_FLAG			((unsigned long) 0X55AA55AAL)

#ifdef __MSDOS__
#define ADF_END_OF_LINE_CHAR				"\r\n"
#else
#define ADF_END_OF_LINE_CHAR				"\n"
#endif /* #ifdef __MSDOS__ */

#define ADF_FILE_PAGE_SIZE					4096

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :  ADF Truth Codes

   NAME        :  ADF Truth Codes

   DESCRIPTION :  Manifest constants used within ADF to specify the truth
						or falsity of expressions.

						(.) ''ADF_TRUE''

						(.) ''ADF_FALSE''

   NOTES       :  The manifest constant ''ADF_TRUE'' should be defined as
						a non-zero value. Conversely, the manifest constant
						''ADF_FALSE'' should be defined as zero (''0'').

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:  ADF_TRUE
						ADF_FALSE
						ADF Truth Codes:ADF_TRUE
						ADF Truth Codes:ADF_FALSE
						ADF Manifest Constants:ADF_TRUE
						ADF Manifest Constants:ADF_FALSE
						ADF Defines:ADF_TRUE
						ADF Defines:ADF_FALSE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  ADF Truth Codes
						ADF Truth Code
						ADF truth codes
						ADF truth code
						ADF_TRUE
						ADF_FALSE

   PUBLISH NAME:	ADF Truth Codes
						ADF_TRUE
						ADF_FALSE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define ADF_TRUE								1
#define ADF_FALSE								0
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   BASE NAME   :	ADF Return Codes

   NAME        :  ADF Return Codes

   DESCRIPTION :  The ADF return codes have the following meanings:

						(.) ''ADF_SUCCESS'' means that the function invoked
						completed without error. ''ADF_SUCCESS'' is guaranteed to
						be equal to zero (''0'').

						(.) ''ADF_FAILURE'' indicates that the function invoked
						encountered a general operation failure. This is the
						'catch-all' error code for those errors which do not fit
						into category of one the other ADF error codes.

						(.) ''ADF_BAD_ARGS_FAILURE'' indicates that the
						arguments passed to a function invoked were invalid.

						(.) ''ADF_MEMORY_FAILURE'' indicates that the memory
						required for operation of the function invoked could not be
						allocated.

						(.) ''ADF_SYSTEM_FAILURE'' indicates that the function
						invoked encountered a failure of a standard library
						function or a system call.

						(.) ''ADF_LOCK_ACQ_FAILURE'' indicates that a lock
						could not be acquired on a resource.

						(.) ''ADF_DB_FAILURE'' indicates that an attempted
						manipulation of an ADF database file was encountered.

						(.) ''ADF_PARSE_FAILURE'' indicates that the ADF parse
						logic failed.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:  ADF_SUCCESS
						ADF_FAILURE
						ADF_BAD_ARGS_FAILURE
						ADF_MEMORY_FAILURE
						ADF_SYSTEM_FAILURE
						ADF_LOCK_ACQ_FAILURE
						ADF_DB_FAILURE
						ADF_PARSE_FAILURE
						ADF Return Codes:ADF_SUCCESS
						ADF Return Codes:ADF_FAILURE
						ADF Return Codes:ADF_BAD_ARGS_FAILURE
						ADF Return Codes:ADF_MEMORY_FAILURE
						ADF Return Codes:ADF_SYSTEM_FAILURE
						ADF Return Codes:ADF_LOCK_ACQ_FAILURE
						ADF Return Codes:ADF_DB_FAILURE
						ADF Return Codes:ADF_PARSE_FAILURE
						ADF Manifest Constants:ADF_SUCCESS
						ADF Manifest Constants:ADF_FAILURE
						ADF Manifest Constants:ADF_BAD_ARGS_FAILURE
						ADF Manifest Constants:ADF_MEMORY_FAILURE
						ADF Manifest Constants:ADF_SYSTEM_FAILURE
						ADF Manifest Constants:ADF_LOCK_ACQ_FAILURE
						ADF Manifest Constants:ADF_DB_FAILURE
						ADF Manifest Constants:ADF_PARSE_FAILURE
						ADF Defines:ADF_SUCCESS
						ADF Defines:ADF_FAILURE
						ADF Defines:ADF_BAD_ARGS_FAILURE
						ADF Defines:ADF_MEMORY_FAILURE
						ADF Defines:ADF_SYSTEM_FAILURE
						ADF Defines:ADF_LOCK_ACQ_FAILURE
						ADF Defines:ADF_DB_FAILURE
						ADF Defines:ADF_PARSE_FAILURE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:  ADF_SUCCESS
						ADF_FAILURE
						ADF_BAD_ARGS_FAILURE
						ADF_MEMORY_FAILURE
						ADF_SYSTEM_FAILURE
						ADF_LOCK_ACQ_FAILURE
						ADF_DB_FAILURE
						ADF_PARSE_FAILURE
						ADF Return Codes
						ADF Return Code
						ADF return codes
						ADF return code
						ADF Status Codes
						ADF Status Code
						ADF status codes
						ADF status code
						ADF Error Codes
						ADF Error Code
						ADF error codes
						ADF error code

   PUBLISH NAME:	ADF Return Codes
						ADF return codes
						ADF_SUCCESS
						ADF_FAILURE
						ADF_BAD_ARGS_FAILURE
						ADF_MEMORY_FAILURE
						ADF_SYSTEM_FAILURE
						ADF_LOCK_ACQ_FAILURE
						ADF_DB_FAILURE
						ADF_PARSE_FAILURE

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define ADF_SUCCESS							   0
#define ADF_FAILURE							  -1
#define ADF_BAD_ARGS_FAILURE				  -2
#define ADF_MEMORY_FAILURE					  -3
#define ADF_SYSTEM_FAILURE					  -4
#define ADF_LOCK_ACQ_FAILURE				  -5
#define ADF_DB_FAILURE						  -6
#define ADF_PARSE_FAILURE					  -7
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :  ADF_MAX_ERROR_TEXT

   DESCRIPTION :  The manifest constant ''ADF_MAX_ERROR_TEXT'' defines
						the minimum amount of storage which should be allocated to
						hold an error message returned by a ADF function.

   CAVEATS     :  ADF error messages can be quite lengthy. Therefore,
						attempting to save space by allocating less than
						''ADF_MAX_ERROR_TEXT'' bytes to error message buffers
						passed to ADF functions can lead to overwriting of the
						heap or the stack.

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:  ADF_MAX_ERROR_TEXT
						ADF Manifest Constants:ADF_MAX_ERROR_TEXT
						ADF Defines:ADF_MAX_ERROR_TEXT
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	ADF_MAX_ERROR_TEXT

   PUBLISH NAME:	ADF_MAX_ERROR_TEXT

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define ADF_MAX_ERROR_TEXT					2048
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	ADF Truth Code Mappings

   NAME        :	ADF Truth Code Mappings

	SYNOPSIS		:	truth_code = ADF_MAP_TRUTH_STR(str_code);

						truth_code = ADF_MAP_TRUTH_GEN(gen_code);

						truth_code = ADF_MAP_TRUTH_DAT(dat_code);

						truth_code = EOS_MAP_TRUTH_MTIF(mtif_code);

						truth_code = ADF_MAP_TRUTH_SPF(spf_code);

						truth_code = ADF_MAP_TRUTH_MFILE(mfile_code);

						truth_code = ADF_MAP_TRUTH_TFREAD(tfread_code);

						truth_code = ADF_MAP_TRUTH_MLOG(mlog_code);

	DESCRIPTION	:	The ADF truth code mapping macros map truth codes from
						various low-level libraries to ADF truth codes.

						(.) ''ADF_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a ADF truth code.

						(.) ''ADF_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a ADF truth code.

						(.) ''ADF_MAP_TRUTH_DAT'' maps a truth code
						from a DATFUNCS truth code to a ADF truth code.

						(.) ''ADF_MAP_TRUTH_MTIF'' maps a truth code
						from a MTIF truth code to a ADF truth code.

						(.) ''ADF_MAP_TRUTH_SPF'' maps a truth code
						from a SPFFUNCS truth code to a ADF truth code.

						(.) ''ADF_MAP_TRUTH_MFILE'' maps a truth code
						from a MFILE truth code to a ADF truth code.

						(.) ''ADF_MAP_TRUTH_TFREAD'' maps a truth code
						from a TFREAD truth code to a ADF truth code.

						(.) ''ADF_MAP_TRUTH_MLOG'' maps a truth code
						from a MLOG truth code to a ADF truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent ADF truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						ADF return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:	ADF_MAP_TRUTH_STR
						ADF_MAP_TRUTH_GEN
						ADF_MAP_TRUTH_DAT
						ADF_MAP_TRUTH_MTIF
						ADF_MAP_TRUTH_SPF
						ADF_MAP_TRUTH_MFILE
						ADF_MAP_TRUTH_TFREAD
						ADF_MAP_TRUTH_MLOG
						Truth Code Mappings:ADF_MAP_TRUTH_STR
						Truth Code Mappings:ADF_MAP_TRUTH_GEN
						Truth Code Mappings:ADF_MAP_TRUTH_DAT
						Truth Code Mappings:ADF_MAP_TRUTH_MTIF
						Truth Code Mappings:ADF_MAP_TRUTH_SPF
						Truth Code Mappings:ADF_MAP_TRUTH_MFILE
						Truth Code Mappings:ADF_MAP_TRUTH_TFREAD
						Truth Code Mappings:ADF_MAP_TRUTH_MLOG
						Macros and Manifest Constants:ADF_MAP_TRUTH_STR
						Macros and Manifest Constants:ADF_MAP_TRUTH_GEN
						Macros and Manifest Constants:ADF_MAP_TRUTH_DAT
						Macros and Manifest Constants:ADF_MAP_TRUTH_MTIF
						Macros and Manifest Constants:ADF_MAP_TRUTH_SPF
						Macros and Manifest Constants:ADF_MAP_TRUTH_MFILE
						Macros and Manifest Constants:ADF_MAP_TRUTH_TFREAD
						Macros and Manifest Constants:ADF_MAP_TRUTH_MLOG
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	ADF_MAP_TRUTH_STR
						ADF_MAP_TRUTH_GEN
						ADF_MAP_TRUTH_DAT
						ADF_MAP_TRUTH_MTIF
						ADF_MAP_TRUTH_SPF
						ADF_MAP_TRUTH_MFILE
						ADF_MAP_TRUTH_TFREAD
						ADF_MAP_TRUTH_MLOG
						ADF_MAP_TRUTH_STR_TO_ADF
						ADF_MAP_TRUTH_GEN_TO_ADF
						ADF_MAP_TRUTH_DAT_TO_ADF
						ADF_MAP_TRUTH_MTIF_TO_ADF
						ADF_MAP_TRUTH_SPF_TO_ADF
						ADF_MAP_TRUTH_MFILE_TO_ADF
						ADF_MAP_TRUTH_TFREAD_TO_ADF
						ADF_MAP_TRUTH_MLOG_TO_ADF
						ADF Truth Code Mappings
						ADF Truth Code Mapping
						ADF truth code mappings
						ADF truth code mapping

   PUBLISH NAME:	ADF_MAP_TRUTH_STR
						ADF_MAP_TRUTH_GEN
						ADF_MAP_TRUTH_DAT
						ADF_MAP_TRUTH_MTIF
						ADF_MAP_TRUTH_SPF
						ADF_MAP_TRUTH_MFILE
						ADF_MAP_TRUTH_TFREAD
						ADF_MAP_TRUTH_MLOG

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define ADF_MAP_TRUTH_STR(str_code)					\
	(((str_code) == STRFUNCS_TRUE)  ? ADF_TRUE : ADF_FALSE)
#define ADF_MAP_TRUTH_GEN(gen_code)					\
	(((gen_code) == GENFUNCS_TRUE)  ? ADF_TRUE : ADF_FALSE)
#define ADF_MAP_TRUTH_DAT(dat_code)					\
	(((dat_code) == DATFUNCS_TRUE)  ? ADF_TRUE : ADF_FALSE)
#define ADF_MAP_TRUTH_MTIF(mtif_code)				\
	(((mtif_code) == MTIF_TRUE)     ? ADF_TRUE : ADF_FALSE)
#define ADF_MAP_TRUTH_SPF(spf_code)					\
	(((spf_code) == SPF_TRUE)       ? ADF_TRUE : ADF_FALSE)
#define ADF_MAP_TRUTH_MFILE(mfile_code)			\
	(((mfile_code) == MFILE_TRUE)   ? ADF_TRUE : ADF_FALSE)
#define ADF_MAP_TRUTH_TFREAD(tfread_code)				\
	(((tfread_code) == TFREAD_TRUE) ? ADF_TRUE : ADF_FALSE)
#define ADF_MAP_TRUTH_MLOG(mlog_code)				\
	(((mlog_code) == MLOG_TRUE)     ? ADF_TRUE : ADF_FALSE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define ADF_MAP_TRUTH_STR_TO_ADF(str_code)		\
	ADF_MAP_TRUTH_STR(str_code)
#define ADF_MAP_TRUTH_GEN_TO_ADF(gen_code)		\
	ADF_MAP_TRUTH_GEN(gen_code)
#define ADF_MAP_TRUTH_DAT_TO_ADF(dat_code)		\
	ADF_MAP_TRUTH_DAT(dat_code)
#define ADF_MAP_TRUTH_MTIF_TO_ADF(mtif_code)		\
	ADF_MAP_TRUTH_MTIF(mtif_code)
#define ADF_MAP_TRUTH_SPF_TO_ADF(spf_code)		\
	ADF_MAP_TRUTH_SPF(spf_code)
#define ADF_MAP_TRUTH_MFILE_TO_ADF(mfile_code)	\
	ADF_MAP_TRUTH_MFILE(mfile_code)
#define ADF_MAP_TRUTH_TFREAD_TO_ADF(tfread_code)\
	ADF_MAP_TRUTH_TFREAD(tfread_code)
#define ADF_MAP_TRUTH_MLOG_TO_ADF(mlog_code)		\
	ADF_MAP_TRUTH_MLOG(mlog_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	ADF Return Code Mappings

   NAME        :	ADF Return Code Mappings

	SYNOPSIS		:	return_code = ADF_MAP_ERROR_STR(str_code);

						return_code = ADF_MAP_ERROR_GEN(gen_code);

						return_code = ADF_MAP_ERROR_DAT(dat_code);

						return_code = ADF_MAP_ERROR_MTIF(mtif_code);

						return_code = ADF_MAP_ERROR_SPF(spf_code);

						return_code = ADF_MAP_ERROR_MFILE(mfile_code);

						return_code = ADF_MAP_ERROR_TFREAD(tfread_code);

						return_code = ADF_MAP_ERROR_MLOG(mlog_code);

	DESCRIPTION	:	The ADF return code mapping macros map return codes from
						various low-level libraries to ADF return codes.

						(.) ''ADF_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a ADF return code.

						(.) ''ADF_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a ADF return code.

						(.) ''ADF_MAP_ERROR_DAT'' maps a return code
						from a DATFUNCS return code to a ADF return code.

						(.) ''ADF_MAP_ERROR_MTIF'' maps a return code
						from a MTIF return code to a ADF return code.

						(.) ''ADF_MAP_ERROR_SPF'' maps a return code
						from a SPFFUNCS return code to a ADF return code.

						(.) ''ADF_MAP_ERROR_MFILE'' maps a return code
						from a MFILE return code to a ADF return code.

						(.) ''ADF_MAP_ERROR_TFREAD'' maps a return code
						from a TFREAD return code to a ADF return code.

						(.) ''ADF_MAP_ERROR_MLOG'' maps a return code
						from a MLOG return code to a ADF return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent ADF return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						ADF truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2016 Michael L. Brock

   OUTPUT INDEX:	ADF_MAP_ERROR_STR
						ADF_MAP_ERROR_GEN
						ADF_MAP_ERROR_DAT
						ADF_MAP_ERROR_MTIF
						ADF_MAP_ERROR_SPF
						ADF_MAP_ERROR_MFILE
						ADF_MAP_ERROR_TFREAD
						ADF_MAP_ERROR_MLOG
						Return Code Mappings:ADF_MAP_ERROR_STR
						Return Code Mappings:ADF_MAP_ERROR_GEN
						Return Code Mappings:ADF_MAP_ERROR_DAT
						Return Code Mappings:ADF_MAP_ERROR_MTIF
						Return Code Mappings:ADF_MAP_ERROR_SPF
						Return Code Mappings:ADF_MAP_ERROR_MFILE
						Return Code Mappings:ADF_MAP_ERROR_TFREAD
						Return Code Mappings:ADF_MAP_ERROR_MLOG
						Macros and Manifest Constants:ADF_MAP_ERROR_STR
						Macros and Manifest Constants:ADF_MAP_ERROR_GEN
						Macros and Manifest Constants:ADF_MAP_ERROR_DAT
						Macros and Manifest Constants:ADF_MAP_ERROR_MTIF
						Macros and Manifest Constants:ADF_MAP_ERROR_SPF
						Macros and Manifest Constants:ADF_MAP_ERROR_MFILE
						Macros and Manifest Constants:ADF_MAP_ERROR_TFREAD
						Macros and Manifest Constants:ADF_MAP_ERROR_MLOG
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	ADF_MAP_ERROR_STR
						ADF_MAP_ERROR_GEN
						ADF_MAP_ERROR_DAT
						ADF_MAP_ERROR_MTIF
						ADF_MAP_ERROR_SPF
						ADF_MAP_ERROR_MFILE
						ADF_MAP_ERROR_TFREAD
						ADF_MAP_ERROR_MLOG
						ADF_MAP_ERROR_STR_TO_ADF
						ADF_MAP_ERROR_GEN_TO_ADF
						ADF_MAP_ERROR_DAT_TO_ADF
						ADF_MAP_ERROR_MTIF_TO_ADF
						ADF_MAP_ERROR_SPF_TO_ADF
						ADF_MAP_ERROR_MFILE_TO_ADF
						ADF_MAP_ERROR_TFREAD_TO_ADF
						ADF_MAP_ERROR_MLOG_TO_ADF
						ADF Return Code Mappings
						ADF Return Code Mapping
						ADF return code mappings
						ADF return code mapping
						ADF Status Code Mappings
						ADF Status Code Mapping
						ADF status code mappings
						ADF status code mapping
						ADF Error Code Mappings
						ADF Error Code Mapping
						ADF error code mappings
						ADF error code mapping

   PUBLISH NAME:	ADF_MAP_ERROR_STR
						ADF_MAP_ERROR_GEN
						ADF_MAP_ERROR_DAT
						ADF_MAP_ERROR_MTIF
						ADF_MAP_ERROR_SPF
						ADF_MAP_ERROR_MFILE
						ADF_MAP_ERROR_TFREAD
						ADF_MAP_ERROR_MLOG

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define ADF_MAP_ERROR_STR(str_code)										 			\
	(((str_code) == STRFUNCS_SUCCESS)          ? ADF_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? ADF_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? ADF_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? ADF_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? ADF_SYSTEM_FAILURE   :	\
	 ADF_FAILURE)
#define ADF_MAP_ERROR_GEN(gen_code)													\
	(((gen_code) == GENFUNCS_SUCCESS)          ? ADF_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? ADF_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? ADF_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? ADF_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? ADF_SYSTEM_FAILURE   :	\
	 ((gen_code) == GENFUNCS_LOCK_ACQ_FAILURE) ? ADF_LOCK_ACQ_FAILURE :	\
	 ADF_FAILURE)
#define ADF_MAP_ERROR_DAT(dat_code)													\
	(((dat_code) == DATFUNCS_SUCCESS)          ? ADF_SUCCESS          :	\
	 ((dat_code) == DATFUNCS_FAILURE)          ? ADF_FAILURE          :	\
	 ((dat_code) == DATFUNCS_MEMORY_FAILURE)   ? ADF_MEMORY_FAILURE   :	\
	 ADF_FAILURE)
#define ADF_MAP_ERROR_MTIF(mtif_code)												\
	(((mtif_code) == MTIF_SUCCESS)             ? ADF_SUCCESS          :	\
	 ((mtif_code) == MTIF_FAILURE)             ? ADF_FAILURE          :	\
	 ((mtif_code) == MTIF_BAD_ARGS_FAILURE)    ? ADF_BAD_ARGS_FAILURE :	\
	 ((mtif_code) == MTIF_MEMORY_FAILURE)      ? ADF_MEMORY_FAILURE   :	\
	 ((mtif_code) == MTIF_SYSTEM_FAILURE)      ? ADF_SYSTEM_FAILURE   :	\
	 ((mtif_code) == MTIF_LOCK_ACQ_FAILURE)    ? ADF_LOCK_ACQ_FAILURE :	\
	 ADF_FAILURE)
#define ADF_MAP_ERROR_SPF(spf_code)													\
	(((spf_code) == SPFFUNCS_SUCCESS)          ? ADF_SUCCESS          :	\
	 ((spf_code) == SPFFUNCS_FAILURE)          ? ADF_FAILURE          :	\
	 ((spf_code) == SPFFUNCS_BAD_ARGS_FAILURE) ? ADF_BAD_ARGS_FAILURE :	\
	 ((spf_code) == SPFFUNCS_MEMORY_FAILURE)   ? ADF_MEMORY_FAILURE   :	\
	 ((spf_code) == SPFFUNCS_SYSTEM_FAILURE)   ? ADF_SYSTEM_FAILURE   :	\
	 ADF_FAILURE)
#define ADF_MAP_ERROR_MFILE(mfile_code)											\
	(((mfile_code) == MFILE_SUCCESS)           ? ADF_SUCCESS          :	\
	 ((mfile_code) == MFILE_FAILURE)           ? ADF_FAILURE          :	\
	 ((mfile_code) == MFILE_BAD_ARGS_FAILURE)  ? ADF_BAD_ARGS_FAILURE :	\
	 ((mfile_code) == MFILE_MEMORY_FAILURE)    ? ADF_MEMORY_FAILURE   :	\
	 ((mfile_code) == MFILE_SYSTEM_FAILURE)    ? ADF_SYSTEM_FAILURE   :	\
	 ADF_FAILURE)
#define ADF_MAP_ERROR_TFREAD(tfread_code)											\
	(((tfread_code) == TFREAD_SUCCESS)          ? ADF_SUCCESS          :	\
	 ((tfread_code) == TFREAD_FAILURE)          ? ADF_FAILURE          :	\
	 ((tfread_code) == TFREAD_BAD_ARGS_FAILURE) ? ADF_BAD_ARGS_FAILURE :	\
	 ((tfread_code) == TFREAD_MEMORY_FAILURE)   ? ADF_MEMORY_FAILURE   :	\
	 ((tfread_code) == TFREAD_SYSTEM_FAILURE)   ? ADF_SYSTEM_FAILURE   :	\
	 ADF_FAILURE)
#define ADF_MAP_ERROR_MLOG(mlog_code)												\
	(((mlog_code) == MLOG_SUCCESS)             ? ADF_SUCCESS          :	\
	 ((mlog_code) == MLOG_FAILURE)             ? ADF_FAILURE          :	\
	 ((mlog_code) == MLOG_BAD_ARGS_FAILURE)    ? ADF_BAD_ARGS_FAILURE :	\
	 ((mlog_code) == MLOG_MEMORY_FAILURE)      ? ADF_MEMORY_FAILURE   :	\
	 ((mlog_code) == MLOG_SYSTEM_FAILURE)      ? ADF_SYSTEM_FAILURE   :	\
	 ADF_FAILURE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define ADF_MAP_ERROR_STR_TO_ADF(str_code)									 	\
	ADF_MAP_ERROR_STR(str_code)
#define ADF_MAP_ERROR_GEN_TO_ADF(gen_code)										\
	ADF_MAP_ERROR_GEN(gen_code)
#define ADF_MAP_ERROR_DAT_TO_ADF(dat_code)										\
	ADF_MAP_ERROR_DAT(dat_code)
#define ADF_MAP_ERROR_MTIF_TO_ADF(mtif_code)										\
	ADF_MAP_ERROR_MTIF(mtif_code)
#define ADF_MAP_ERROR_SPF_TO_ADF(spf_code)										\
	ADF_MAP_ERROR_SPF(spf_code)
#define ADF_MAP_ERROR_MFILE_TO_ADF(mfile_code)									\
	ADF_MAP_ERROR_MFILE(mfile_code)
#define ADF_MAP_ERROR_TFREAD_TO_ADF(tfread_code)								\
	ADF_MAP_ERROR_TFREAD(tfread_code)
#define ADF_MAP_ERROR_MLOG_TO_ADF(mlog_code)										\
	ADF_MAP_ERROR_MLOG(mlog_code)
/*	***********************************************************************	*/



/*	***********************************************************************	*/
#define ADF_ENTRY_DESCRIP_LENGTH			(1024 + 512)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_AREA_NAME_LENGTH				32

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define ADF_PARSE_TYPE_AREA_NAME			SPF_USER_TYPE(1)
#define ADF_PARSE_TYPE_PATTERN			SPF_USER_TYPE(2)
#define ADF_PARSE_TYPE_SECTION			SPF_USER_TYPE(3)
#define ADF_PARSE_TYPE_DOMAIN				SPF_USER_TYPE(4)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_AREA_BASE_NAME					 0
#define ADF_AREA_NAME						 1
#define ADF_AREA_SYNOPSIS					 2
#define ADF_AREA_CODE_SYNTAX				 3
#define ADF_AREA_DESCRIPTION				 4
#define ADF_AREA_DEFINITIONS				 5
#define ADF_AREA_TERMINOLOGY				 6
#define ADF_AREA_OPTIONS					 7
#define ADF_AREA_PARAMETERS				 8
#define ADF_AREA_COMMANDS					 9
#define ADF_AREA_MEMBERS					10
#define ADF_AREA_RETURNS					11
#define ADF_AREA_ERROR_MESSAGES			12
#define ADF_AREA_ENVIRONMENT				13
#define ADF_AREA_FILES						14
#define ADF_AREA_ALGORITHMS				15
#define ADF_AREA_DEBUGGING					16
#define ADF_AREA_DIAGNOSTICS				17
#define ADF_AREA_NOTES						18
#define ADF_AREA_CAVEATS					19
#define ADF_AREA_DEFAULTS					20
#define ADF_AREA_BUGS						21
#define ADF_AREA_LIMITATIONS				22
#define ADF_AREA_COMPATIBILITY			23
#define ADF_AREA_IDIOSYNCRACIES			24
#define ADF_AREA_SEE_ALSO					25
#define ADF_AREA_EXAMPLES					26
#define ADF_AREA_CODE_EXAMPLES			27
#define ADF_AREA_AUTHORS					28
#define ADF_AREA_CONTRIBUTORS				29
#define ADF_AREA_ACKNOWLEDGMENTS			30
#define ADF_AREA_CREDITS					31
#define ADF_AREA_REFERENCES				32
#define ADF_AREA_RESTRICTIONS				33
#define ADF_AREA_DISCLAIMERS				34
#define ADF_AREA_COPYING					35
#define ADF_AREA_COPYRIGHTS				36
#define ADF_AREA_TRADEMARKS				37
#define ADF_AREA_SOURCE_FILE_NAME		38
#define ADF_AREA_SOURCE_FILE_DATE		39
#define ADF_AREA_MAN_SECTION				40
#define ADF_AREA_TAB_SETTING				41
#define ADF_AREA_OUTPUT_INDEX				42
#define ADF_AREA_PUBLISH_XREF				43
#define ADF_AREA_PUBLISH_NAME				44
#define ADF_AREA_SOURCE_FILE_FULL_NAME	45
#define ADF_AREA_ENTRY_CLASS_NAME		46

#define ADF_AREA_COUNT						47

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_CFORMAT_MARKER_CHAR			'\001'

#define ADF_CFORMAT_TYPE_NONE				((unsigned int)   0)
#define ADF_CFORMAT_TYPE_BOLD				((unsigned int)   1)
#define ADF_CFORMAT_TYPE_ITALIC			((unsigned int)   2)
#define ADF_CFORMAT_TYPE_ULINED			((unsigned int)   4)
#define ADF_CFORMAT_TYPE_OLINED			((unsigned int)   8)
#define ADF_CFORMAT_TYPE_STHRU			((unsigned int)  16)
#define ADF_CFORMAT_TYPE_EINDEX			((unsigned int)  32)
#define ADF_CFORMAT_TYPE_SUBSCRIPT		((unsigned int)  64)
#define ADF_CFORMAT_TYPE_SUPERSCRIPT	((unsigned int) 128)
#define ADF_CFORMAT_TYPE_HTEXT			((unsigned int) 256)

#define ADF_CFORMAT_TYPE_ALL				((unsigned int) 0XFFFFU)

#define ADF_CFORMAT_CHAR_NONE				'\0'
#define ADF_CFORMAT_CHAR_BOLD				'B'
#define ADF_CFORMAT_CHAR_ITALIC			'I'
#define ADF_CFORMAT_CHAR_ULINED			'U'
#define ADF_CFORMAT_CHAR_OLINED			'O'
#define ADF_CFORMAT_CHAR_STHRU			'T'
#define ADF_CFORMAT_CHAR_EINDEX			'X'
#define ADF_CFORMAT_CHAR_SUBSCRIPT		'Y'
#define ADF_CFORMAT_CHAR_SUPERSCRIPT	'Z'
#define ADF_CFORMAT_CHAR_HTEXT			'H'

#define ADF_CFORMAT_CHAR_NONE_1			'\0'
#define ADF_CFORMAT_CHAR_BOLD_1			'B'
#define ADF_CFORMAT_CHAR_ITALIC_1		'I'
#define ADF_CFORMAT_CHAR_ULINED_1		'U'
#define ADF_CFORMAT_CHAR_OLINED_1		'O'
#define ADF_CFORMAT_CHAR_STHRU_1			'T'
#define ADF_CFORMAT_CHAR_EINDEX_1		'X'
#define ADF_CFORMAT_CHAR_SUBSCRIPT_1	'Y'
#define ADF_CFORMAT_CHAR_SUPERSCRIPT_1	'Z'
#define ADF_CFORMAT_CHAR_HTEXT_1			'H'

#define ADF_CFORMAT_CHAR_NONE_2			'\0'
#define ADF_CFORMAT_CHAR_BOLD_2			'b'
#define ADF_CFORMAT_CHAR_ITALIC_2		'i'
#define ADF_CFORMAT_CHAR_ULINED_2		'u'
#define ADF_CFORMAT_CHAR_OLINED_2		'o'
#define ADF_CFORMAT_CHAR_STHRU_2			't'
#define ADF_CFORMAT_CHAR_EINDEX_2		'x'
#define ADF_CFORMAT_CHAR_SUBSCRIPT_2	'y'
#define ADF_CFORMAT_CHAR_SUPERSCRIPT_2	'z'
#define ADF_CFORMAT_CHAR_HTEXT_2			'h'

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_PFORMAT_MARKER_CHAR			'\002'

#define ADF_PFORMAT_COUNT					160

#define ADF_PFORMAT_LENGTH					18

#define ADF_PFORMAT_TYPE_NONE				0
#define ADF_PFORMAT_TYPE_BB				1
#define ADF_PFORMAT_TYPE_IN				2
#define ADF_PFORMAT_TYPE_NM				3

#define ADF_PFORMAT_TYPE_COUNT			4

#define ADF_PFORMAT_LEVEL_COUNT			4

#define ADF_PFORMAT_BRACE_TYPE_COUNT	4

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_BASIC_CHAR_MULTIPLIER		3

#define ADF_CFORMAT_MULTIPLIER			100

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_PREP_FILE_MODE_EITHER		0
#define ADF_PREP_FILE_MODE_CREATE		1
#define ADF_PREP_FILE_MODE_UPDATE		2

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_DUP_HANDLER_NONE				0
#define ADF_DUP_HANDLER_FIRST				1
#define ADF_DUP_HANDLER_LAST				2

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define ADF_BOH_SPEC_FILE_TYPE			0
#define ADF_BOH_SPEC_MAN_PAGE				1
#define ADF_BOH_SPEC_TAB_SETTING			2

#define ADF_BOH_SPEC_COUNT					3
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define ADF_DEFAULT_MAN_PAGE				"3"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define ADF_VALID_MAN_PAGE_STRING		"123456789lnop"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define ADF_DEFAULT_TAB_VALUE				3
#define ADF_DEFAULT_TAB_STRING			"3"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_OUTPUT_TYPE_ASCII				0
#define ADF_OUTPUT_TYPE_FRAME				1
#define ADF_OUTPUT_TYPE_HTML				2
#define ADF_OUTPUT_TYPE_MAN				3
#define ADF_OUTPUT_TYPE_PS					4
#define ADF_OUTPUT_TYPE_RTF				5

#define ADF_OUTPUT_TYPE_COUNT				6

#define ADF_OUTPUT_TYPE_NAME_LENGTH		63

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_GENERATE_TYPE_ENTRY			0
#define ADF_GENERATE_TYPE_TOC				1
#define ADF_GENERATE_TYPE_CLASS_TOC		2
#define ADF_GENERATE_TYPE_TOF				3
#define ADF_GENERATE_TYPE_INDEX			4
#define ADF_GENERATE_TYPE_PERM_INDEX	5

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_AREA_NAME_TYPE_INTERNAL		0
#define ADF_AREA_NAME_TYPE_DEF			1

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_AREA_ORDER_TYPE_INTERNAL	0
#define ADF_AREA_ORDER_TYPE_DEF			1
#define ADF_AREA_ORDER_TYPE_SOURCE		2

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_SORT_ENTRY_ENTRY				0
#define ADF_SORT_ENTRY_BASE_NAME			1
#define ADF_SORT_ENTRY_FILE_NAME			2
#define ADF_SORT_ENTRY_CORE_NAME			3
#define ADF_SORT_ENTRY_FILE_TYPE			4
#define ADF_SORT_ENTRY_MAN_PAGE			5

#define ADF_SORT_ENTRY_DICT_ORDER		6

#define ADF_SORT_HTEXT_ENTRY				0
#define ADF_SORT_HTEXT_TEXT				1

#define ADF_SORT_IGNORE_CASE				64

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_CLUDE_TYPE_BASE_NAME			0
#define ADF_CLUDE_TYPE_FILE_NAME			1
#define ADF_CLUDE_TYPE_FILE_TYPE			2
#define ADF_CLUDE_TYPE_MAN_PAGE			3

#define ADF_CLUDE_TYPE_COUNT				4

#define ADF_CLUDE_BASIS_INCLUDE			0
#define ADF_CLUDE_BASIS_EXCLUDE			1

#define ADF_CLUDE_BASIS_COUNT				2

typedef struct {
	unsigned int   clude_count;
	char         **clude_list;
} ADF_CLUDE;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifdef __MSDOS__
# define ADF_fclose							fclose
# define ADF_fflush							fflush
# define ADF_fopen							fopen
# define ADF_fprintf							fprintf
# define ADF_fread							fread
# define ADF_fseek							fseek
# define ADF_ftell							ftell
# define ADF_fwrite							fwrite
#elif _Windows
# define ADF_fclose							fclose
# define ADF_fflush							fflush
# define ADF_fopen							fopen
# define ADF_fprintf							fprintf
# define ADF_fread							fread
# define ADF_fseek							fseek
# define ADF_ftell							ftell
# define ADF_fwrite							fwrite
#else
# define ADF_fclose							mclose
# define ADF_fflush							mflush
# define ADF_fopen							mopen
# define ADF_fprintf							mprintf
# define ADF_fread							mread
# define ADF_fseek							mseek
# define ADF_ftell							mtell
# define ADF_fwrite							mwrite
#endif /* #ifdef __MSDOS__ */

#ifdef __MSDOS__
# include <alloc.h>
# define ADF_BIG_char						char huge
# define ADF_BIG_void						void huge
# define ADF_BIG_calloc						farcalloc
# define ADF_BIG_malloc						farmalloc
# define ADF_BIG_realloc					farrealloc
# define ADF_BIG_free						farfree
#else
# define ADF_BIG_char						char
# define ADF_BIG_void						void
# define ADF_BIG_calloc						calloc
# define ADF_BIG_malloc						malloc
# define ADF_BIG_realloc					realloc
# define ADF_BIG_free						free
#endif /* #ifdef __MSDOS__ */

#define ADF_FILE_PAD_LENGTH				sizeof(double)

#define ADF_FILE_ENTRY_DIR_OFFSET		0
#define ADF_FILE_HYPER_TEXT_OFFSET		1
#define ADF_FILE_ENTRY_DIR_LENGTH		2
#define ADF_FILE_HYPER_TEXT_LENGTH		3
#define ADF_FILE_ENTRY_DIR_COUNT			4
#define ADF_FILE_HYPER_TEXT_COUNT		5

#define ADF_FILE_EOF_COUNT					6

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifdef __MSDOS__
typedef FILE  ADF_FILE;
#elif _Windows
typedef FILE  ADF_FILE;
#else
typedef MFILE ADF_FILE;
#endif /* #ifdef __MSDOS__ */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_MAN_MARGIN_PADDING			3

#define ADF_MAN_CFORMAT_TYPE				(ADF_CFORMAT_TYPE_BOLD |	\
	ADF_CFORMAT_TYPE_ITALIC | ADF_CFORMAT_TYPE_SUBSCRIPT |			\
	ADF_CFORMAT_TYPE_SUPERSCRIPT)

#define ADF_HTML_CFORMAT_TYPE				(ADF_CFORMAT_TYPE_BOLD |	\
	ADF_CFORMAT_TYPE_ITALIC | ADF_CFORMAT_TYPE_ULINED |				\
	ADF_CFORMAT_TYPE_STHRU | ADF_CFORMAT_TYPE_SUBSCRIPT |				\
	ADF_CFORMAT_TYPE_SUPERSCRIPT | ADF_CFORMAT_TYPE_HTEXT)

#define ADF_RTF_CFORMAT_TYPE				(ADF_CFORMAT_TYPE_BOLD |	\
	ADF_CFORMAT_TYPE_ITALIC | ADF_CFORMAT_TYPE_ULINED |				\
	ADF_CFORMAT_TYPE_STHRU | ADF_CFORMAT_TYPE_EINDEX |					\
	ADF_CFORMAT_TYPE_SUBSCRIPT | ADF_CFORMAT_TYPE_SUPERSCRIPT)

#define ADF_FRAME_CFORMAT_TYPE			(ADF_CFORMAT_TYPE_BOLD |	\
	ADF_CFORMAT_TYPE_ITALIC | ADF_CFORMAT_TYPE_ULINED |				\
	ADF_CFORMAT_TYPE_OLINED | ADF_CFORMAT_TYPE_STHRU |					\
	ADF_CFORMAT_TYPE_EINDEX | ADF_CFORMAT_TYPE_SUBSCRIPT |			\
	ADF_CFORMAT_TYPE_SUPERSCRIPT | ADF_CFORMAT_TYPE_HTEXT)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define ADF_HTML_VERSION_1_0				0
#define ADF_HTML_VERSION_2_0				1
#define ADF_HTML_VERSION_PLUS				2
#define ADF_HTML_VERSION_DEFAULT			ADF_HTML_VERSION_1_0

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define ADF_DICT_ORDER_CHAR(in_char)									\
	((char) ((isalpha(in_char)) ? STRFUNCS_toupper(in_char) :	\
	(isdigit(in_char) ? ((char) ((in_char - '0') + 1)) : ((char) '\0'))))
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	unsigned int   pattern_count;
	char         **pattern_list;
	char          *pattern_optimization;
} ADF_PATTERN;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	unsigned int   file_index;
	unsigned int   entry_index;
	unsigned long  entry_offset;
	char          *base_name;
	char          *file_name;
	char          *core_name;
	char          *full_name;
	char          *file_type;
	char          *man_page;
	time_t         file_date;
	time_t         prep_date;
	int            href_flag;
} ADF_ENTRY;

typedef struct {
	unsigned int   file_index;
	unsigned int   entry_index;
	unsigned long  entry_offset;
	time_t         file_date;
	time_t         prep_date;
/*
	CODE NOTE: To be deleted.
	unsigned int   base_name_length;
	unsigned int   file_name_length;
	unsigned int   core_name_length;
	unsigned int   full_name_length;
	unsigned int   file_type_length;
	unsigned int   man_page_length;
*/
	unsigned int   base_name_offset;
	unsigned int   file_name_offset;
	unsigned int   core_name_offset;
	unsigned int   full_name_offset;
	unsigned int   file_type_offset;
	unsigned int   man_page_offset;
} ADF_ENTRY_FILE;

typedef struct {
	unsigned int data_length;
	unsigned int paragraph_count;
	unsigned int name_offset[ADF_AREA_COUNT];
	unsigned int name_length[ADF_AREA_COUNT];
	unsigned int section_offset[ADF_AREA_COUNT];
	unsigned int section_length[ADF_AREA_COUNT];
	unsigned int section_order[ADF_AREA_COUNT];
	unsigned int actual_order[ADF_AREA_COUNT];
} ADF_ENTRY_DATA_FILE;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	unsigned int  file_index;
	unsigned int  entry_index;
	unsigned int  htext_length;
	char         *hyper_text;
	unsigned int  in_entry_index;
} ADF_HTEXT;

typedef struct {
	unsigned int  file_index;
	unsigned int  entry_index;
	unsigned int  htext_length;
	unsigned int  htext_offset;
} ADF_HTEXT_FILE;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char *area_name;
	char *area_tag;
	int   required_flag;
	int   pformat_flag;
	int   cformat_flag;
	int   eindex_flag;
	int   htext_flag;
	int   output_flag;
} ADF_AREA;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char         *section_name;
	char         *output_section_name;
	unsigned int  area_index;
	int           required_flag;
	int           wrap_flag;
	int           ltrim_flag;
	int           rtrim_flag;
	int           squeeze_flag;
	int           para_format_flag;
	int           char_format_flag;
	int           eindex_flag;
	int           htext_flag;
	ADF_PATTERN   match_pattern;
} ADF_SECTION;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char          *domain_name;
	char          *domain_description;
	unsigned int   file_type_count;
	char         **file_type_list;
	ADF_PATTERN    boh_pattern;
	ADF_PATTERN    eoh_pattern;
	ADF_PATTERN    bol_pattern;
	ADF_PATTERN    eol_pattern;
	ADF_PATTERN    empty_line_pattern;
	ADF_PATTERN    strip_pattern;
	unsigned int   section_count;
	ADF_SECTION   *section_list;
} ADF_DOMAIN;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	ADF_SECTION   *section_ptr;
	unsigned int   section_index;
	char          *section_name;
	unsigned int   start_position;
	unsigned int   line_number;
	unsigned int   line_count;
	char         **line_list;
	char          *line_data;
} ADF_SOURCE_DATA;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char         *format_string;
	int           char_format_flag;
	int           small_font_flag;
	unsigned int  indent_level;
	int           format_type;
	int           begin_rule_flag;
	int           end_rule_flag;
	int           supported_flag;
} ADF_PFORMAT_DEF;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	int           pformat_flag;
	unsigned int  pformat_index;
	int           char_format_flag;
	int           small_font_flag;
	unsigned int  indent_level;
	int           format_type;
	int           begin_rule_flag;
	int           end_rule_flag;
	unsigned long numeric_value;
	unsigned int  first_count;
	unsigned int  last_count;
} ADF_PFORMAT;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	ADF_PFORMAT  para_format;
	char        *text_ptr;
} ADF_PARA_DATA;

typedef struct {
	unsigned int   area_index;
	unsigned int   section_order;
	unsigned int   actual_order;
	char          *section_name;
	unsigned int   para_count;
	ADF_PARA_DATA *para_list;
} ADF_ENTRY_DATA;

typedef struct {
	int           cformat_type;
	unsigned int  htext_index;
	unsigned int  length;
	char         *ptr;
} ADF_PARA_TEXT;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	time_t        creation_date;
	time_t        update_date;
	char          version_number[16];
	int           area_count;
	unsigned int  sizeof_ADF_ENTRY_FILE;
	unsigned int  sizeof_ADF_HTEXT_FILE;
	unsigned int  sizeof_ADF_ENTRY_DATA_FILE;
	unsigned long completion_flag;
	unsigned long file_length;
	unsigned long entry_data_offset;
	unsigned int  entry_data_length;
	unsigned long entry_list_offset;
	unsigned int  entry_list_length;
	unsigned int  entry_list_count;
	unsigned long htext_data_offset;
	unsigned int  htext_data_length;
	unsigned long htext_list_offset;
	unsigned int  htext_list_length;
	unsigned int  htext_list_count;
} ADF_FILE_HEADER;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char            *file_name;
	char            *href_string;
	int              href_flag;
	ADF_FILE        *file_ptr;
	char            *entry_buffer;
	char            *htext_buffer;
	ADF_FILE_HEADER  header;
	time_t           last_access_time;
} ADF_IN_FILE;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct tag_ADF_INDEX_ITEM {
	unsigned char               item_order;
	char                       *item_name;
	int                         entry_flag;
	unsigned int                index_item_count;
	struct tag_ADF_INDEX_ITEM  *index_item_list;
	const ADF_ENTRY            *entry_ptr;
	unsigned int                htext_index;
} ADF_INDEX_ITEM;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	unsigned char  item_order;
	unsigned int   entry_index;
	unsigned int   ref_count;
	unsigned int  *ref_list;
} ADF_PERM_INDEX;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	unsigned int  count;
	ADF_HTEXT    *list;
} ADF_HTEXT_CHARS;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char *ptr_1;
	char *ptr_2;
} ADF_STRING_PAIR;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char *document_name;
	char *owner_name;
	char *copyright;
	char *cover_name_1;
	char *cover_name_2;
	char *long_name;
	char *short_name;
} ADF_FRAME_DATA;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	unsigned int     author_link_count;
	ADF_STRING_PAIR *author_link_list;
	unsigned int     copyright_link_count;
	ADF_STRING_PAIR *copyright_link_list;
	char             html_heading_level[15 + 1];
} ADF_HTML_DATA;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char *section_name;
	char *owner_name;
} ADF_MAN_DATA;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
typedef struct {
	char             *program_name;
	char             *short_program_name;
	char              host_name[GEN_MAX_HOST_NAME_LEN + 1];
	int               process_id;
	char              current_dir[GEN_MAX_PATH_NAME_LEN + 1];
	struct timeval    start_time;
	struct timeval    end_time;
	struct timeval    overhead_end_time;
	int               help_flag;
	int               version_flag;
	int               shut_down_flag;
	int               signal_received_flag;
	int               queue_signal_flag;
	unsigned int      domain_count;
	ADF_DOMAIN       *domain_list;
	char             *adf_def_file_name;
	char             *prep_adf_file_name;
	ADF_FILE         *prep_adf_file;
	int               prep_adf_file_mode;
	char             *prep_tmp_file_name;
	unsigned int      prep_src_file_length;
	char             *prep_src_file;
	unsigned int      prep_src_core_file_length;
	char             *prep_src_core_file;
	unsigned int      in_file_name_count;
	char            **in_file_name_list;
	unsigned int      htext_ref_file_name_count;
	char            **htext_ref_file_name_list;
	unsigned int      in_file_count;
	ADF_IN_FILE      *in_file_list;
	unsigned int      prep_entry_count;
	ADF_ENTRY        *prep_entry_list;
	unsigned int      prep_htext_count;
	ADF_HTEXT        *prep_htext_list;
	unsigned int      in_entry_count;
	ADF_ENTRY        *in_entry_list;
	unsigned int      in_htext_count;
	ADF_HTEXT        *in_htext_list;
	ADF_HTEXT_CHARS   in_htext_lookup_list[UCHAR_MAX + 1];
	unsigned int      in_entry_order_count;
	ADF_ENTRY       **in_entry_order_list;
	unsigned int      read_entry_buffer_length;
	char             *read_entry_buffer;
	unsigned int      current_para_line_count;
	unsigned int      in_para_line_count;
	ADF_PARA_TEXT    *in_para_line_list;
	unsigned int      in_para_htext_ptr_count;
	ADF_HTEXT       **in_para_htext_ptr_list;
	unsigned int      out_para_buffer_length;
	char             *out_para_buffer;
	unsigned int      wrap_buffer_length;
	char             *wrap_buffer;
	unsigned int      in_entry_para_count;
	ADF_PARA_DATA    *in_entry_para_list;
	char             *default_author;
	char             *default_copyright;
	char             *default_man_page;
	char             *log_dir;
	char             *log_file_name;
	MLOG             *mlog_ptr;
	char             *output_dir;
	char             *output_dir_basic;
	unsigned int      output_file_name_length;
	char             *output_file_name;
	FILE             *output_file_ptr;
	unsigned int      htext_link_name_length;
	char             *htext_link_name;
	int               duplicate_handling_type;
	int               sort_order_type;
	int               output_type;
	int               check_only_flag;
	int               cont_on_error_flag;
	int               ignore_bad_cmnt_flag;
	int               forced_author_flag;
	int               forced_copyright_flag;
	int               forced_man_page_flag;
	int               check_comment_flag;
	int               error_on_no_comment_flag;
	int               no_required_sections_flag;
	int               ignore_bad_xrefs_flag;
	int               remove_bad_xrefs_flag;
	int               keep_bad_xrefs_flag;
	int               list_frame_xrefs_flag;
	int               xref_tree_flag;
	int               hyper_text_flag;
	int               generate_type;
	int               log_flag;
	int               quiet_flag;
	int               output_comment_flag;
	int               output_by_file_flag;
	int               output_to_stdout_flag;
	int               ignore_section_list[ADF_AREA_COUNT];
	int               area_name_type;
	int               area_order_type;
	int               keep_bad_see_also_flag;
	int               html_version;
	unsigned int      entry_include_count;
	unsigned int      entry_exclude_count;
	ADF_CLUDE         entry_clude[ADF_CLUDE_BASIS_COUNT][ADF_CLUDE_TYPE_COUNT];
	unsigned int      htext_include_count;
	unsigned int      htext_exclude_count;
	ADF_CLUDE			htext_clude[ADF_CLUDE_BASIS_COUNT];
	char             *area_name_list[ADF_AREA_COUNT];
	unsigned int      non_ref_index_count;
	char            **non_ref_index_list;
	int               rtf_para_style_list_flag;
	char             *rtf_para_style_list[ADF_PFORMAT_COUNT];
	ADF_FRAME_DATA    frame_data;
	ADF_HTML_DATA     html_data;
	ADF_MAN_DATA      man_data;
} ADF_CONTROL;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Definition parse support function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int ADF_PARSE_Any, (SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, void *parent_ptr, char *error_text));
COMPAT_FN_DECL(int ADF_PARSE_AreaName, (const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	unsigned int *area_name_ptr, char *error_text));
COMPAT_FN_DECL(int ADF_PARSE_Domain, (SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, void *parent_ptr, unsigned int *domain_count,
	ADF_DOMAIN **domain_list, char *error_text));
COMPAT_FN_DECL(int ADF_PARSE_Main, (SPF_CONTEXT *context_ptr, const char *file_name,
	const char *def_string, char *error_text));
COMPAT_FN_DECL(int ADF_PARSE_Pattern, (const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	ADF_PATTERN *pattern_ptr, char *error_text));
COMPAT_FN_DECL(int ADF_PARSE_Section, (SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, void *parent_ptr, unsigned int *section_count,
	ADF_SECTION **section_list, char *error_text));
COMPAT_FN_DECL(int ADF_PARSE_OptPat, (ADF_PATTERN *in_pattern, char *error_text));
	/*	*****************************************************************	*/

COMPAT_FN_DECL(int   ADF_GetOutputTypeFromString, (const char *output_type_string,
	int *output_type, char *error_text));
COMPAT_FN_DECL(char *ADF_GetOutputTypeString, (int output_type, char *output_type_string));

COMPAT_FN_DECL(int ADF_GetOutputFunctions, (int output_type,
	int  (**init_function)(ADF_CONTROL *control_ptr, char *error_text),
	int  (**by_entry_function)(ADF_CONTROL *control_ptr,
		const ADF_ENTRY *entry_ptr, char *error_text),
	int  (**to_stdout_function)(ADF_CONTROL *control_ptr,
		const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text),
	int  (**by_file_function)(ADF_CONTROL *control_ptr,
		unsigned int *entry_index, char *error_text),
	int  (**toc_function)(ADF_CONTROL *control_ptr, char *error_text),
	int  (**class_toc_function)(ADF_CONTROL *control_ptr, char *error_text),
	int  (**tof_function)(ADF_CONTROL *control_ptr, char *error_text),
	int  (**index_function)(ADF_CONTROL *control_ptr, char *error_text),
	int  (**perm_index_function)(ADF_CONTROL *control_ptr, char *error_text),
	void (**output_start_function)(ADF_CONTROL *control_ptr,
		const char *output_name, const time_t *output_date,
		STR_FUNC_TYPE_fprintf output_function, void *output_control),
	void (**output_end_function)(ADF_CONTROL *control_ptr,
		STR_FUNC_TYPE_fprintf output_function, void *output_control),
	void (**output_between_function)(ADF_CONTROL *control_ptr,
		const ADF_ENTRY *entry_ptr, const char *output_name,
		STR_FUNC_TYPE_fprintf output_function, void *output_control),
	char *error_text));

COMPAT_FN_DECL(int ADF_GetAreaList, (ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_ptr, unsigned int *out_count, char ***out_list,
	char *error_text));
COMPAT_FN_DECL(int ADF_GetAreaString, (ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_ptr, char **out_string, char *error_text));

COMPAT_FN_DECL(int ADF_ASCII_OutputByEntry, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, char *error_text));
COMPAT_FN_DECL(int ADF_ASCII_OutputToStdout, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text));
COMPAT_FN_DECL(int ADF_ASCII_OutputByFile, (ADF_CONTROL *control_ptr,
	unsigned int *entry_index, char *error_text));
COMPAT_FN_DECL(int ADF_ASCII_OutputTOC, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int ADF_ASCII_OutputIndex, (ADF_CONTROL *control_ptr, char *error_text));

COMPAT_FN_DECL(int  ADF_FRAME_OutputByEntry, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_FRAME_OutputToStdout, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text));
COMPAT_FN_DECL(int  ADF_FRAME_OutputByFile, (ADF_CONTROL *control_ptr,
	unsigned int *entry_index, char *error_text));
COMPAT_FN_DECL(int  ADF_FRAME_OutputIndex, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_FRAME_OutputTOC, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(void ADF_FRAME_OutputStart, (ADF_CONTROL *control_ptr, const char *output_name,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void ADF_FRAME_OutputEnd, (ADF_CONTROL *control_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));

COMPAT_FN_DECL(int  ADF_HTML_OutputByEntry, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_HTML_OutputToStdout, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text));
COMPAT_FN_DECL(int  ADF_HTML_OutputByFile, (ADF_CONTROL *control_ptr,
	unsigned int *entry_index, char *error_text));
COMPAT_FN_DECL(int  ADF_HTML_OutputIndex, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_HTML_OutputPermIndex, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_HTML_OutputTOC, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_HTML_OutputClassTOC, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_HTML_OutputTOF, (ADF_CONTROL *control_ptr, char *error_text));

COMPAT_FN_DECL(int  ADF_MAN_OutputByEntry, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_MAN_OutputToStdout, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text));
COMPAT_FN_DECL(int  ADF_MAN_OutputByFile, (ADF_CONTROL *control_ptr,
	unsigned int *entry_index, char *error_text));
COMPAT_FN_DECL(int  ADF_MAN_OutputIndex, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_MAN_OutputTOC, (ADF_CONTROL *control_ptr, char *error_text));

COMPAT_FN_DECL(int ADF_PS_OutputByEntry, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, char *error_text));
COMPAT_FN_DECL(int ADF_PS_OutputToStdout, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text));
COMPAT_FN_DECL(int ADF_PS_OutputByFile, (ADF_CONTROL *control_ptr,
	unsigned int *entry_index, char *error_text));
COMPAT_FN_DECL(int ADF_PS_OutputIndex, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int ADF_PS_OutputTOC, (ADF_CONTROL *control_ptr, char *error_text));

COMPAT_FN_DECL(int  ADF_RTF_OutputInit, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_RTF_OutputByEntry, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_RTF_OutputToStdout, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text));
COMPAT_FN_DECL(int  ADF_RTF_OutputByFile, (ADF_CONTROL *control_ptr,
	unsigned int *entry_index, char *error_text));
COMPAT_FN_DECL(void ADF_RTF_OutputStart, (ADF_CONTROL *control_ptr, const char *output_name,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void ADF_RTF_OutputEnd, (ADF_CONTROL *control_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));

COMPAT_FN_DECL(int ADF_DoSource, (ADF_CONTROL *control_ptr, unsigned int domain_count,
	const ADF_DOMAIN *domain_list, const char *file_name, char *error_text));

COMPAT_FN_DECL(int   ADF_ValidateManPage, (const char *man_page, char *error_text));
COMPAT_FN_DECL(char *ADF_GetDefaultManSection, (const char *man_page, char *man_section));

COMPAT_FN_DECL(void ADF_InitDataFRAME, (ADF_FRAME_DATA *frame_data_ptr));
COMPAT_FN_DECL(void ADF_FreeDataFRAME, (ADF_FRAME_DATA *frame_data_ptr));
COMPAT_FN_DECL(void ADF_InitDataHTML, (ADF_HTML_DATA *html_data_ptr));
COMPAT_FN_DECL(void ADF_FreeDataHTML, (ADF_HTML_DATA *html_data_ptr));
COMPAT_FN_DECL(void ADF_InitDataMAN, (ADF_MAN_DATA *man_data_ptr));
COMPAT_FN_DECL(void ADF_FreeDataMAN, (ADF_MAN_DATA *man_data_ptr));

COMPAT_FN_DECL(int  ADF_StringPairParse, (const char *string_pair_name,
	const char *string_pair_data, unsigned int *string_pair_count,
	ADF_STRING_PAIR **string_pair_list, char *error_text));
COMPAT_FN_DECL(int  ADF_StrPairAlloc, (const char *string_ptr_1, const char *string_ptr_2,
	ADF_STRING_PAIR *string_pair_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_StrPairListAlloc, (const char *string_ptr_1, const char *string_ptr_2,
	unsigned int *string_pair_count, ADF_STRING_PAIR **string_pair_list,
	char *error_text));
COMPAT_FN_DECL(void ADF_StrPairFree, (ADF_STRING_PAIR *string_pair_ptr));
COMPAT_FN_DECL(void ADF_StrPairListFree, (unsigned int *string_pair_count,
	ADF_STRING_PAIR **string_pair_list));
COMPAT_FN_DECL(void ADF_StrPairInit, (ADF_STRING_PAIR *string_pair_ptr));
COMPAT_FN_DECL(int  ADF_SEARCH_StrPairList, (const char *string_ptr_1, const char *string_ptr_2,
	unsigned int *string_pair_count, ADF_STRING_PAIR **string_pair_list,
	char *error_text));

COMPAT_FN_DECL(int ADF_FixParagraph, (ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_PARA_DATA *para_ptr, unsigned int cformat_flags, char *error_text));
COMPAT_FN_DECL(int ADF_FixParagraphWrap, (ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_PARA_DATA *para_ptr, unsigned int cformat_flags,
	unsigned int output_width, unsigned int tab_setting,
	unsigned int left_padding, char *error_text));

COMPAT_FN_DECL(int  ADF_GetEntry, (ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_list, char *error_text));

COMPAT_FN_DECL(int  ADF_CMP_EntryDataList, (const ADF_ENTRY_DATA *entry_data_list_1,
	const ADF_ENTRY_DATA *entry_data_list_2, unsigned int *diff_area_index,
	unsigned int *diff_para_index));
COMPAT_FN_DECL(int  ADF_CMP_EntryData, (const ADF_ENTRY_DATA *entry_data_ptr_1,
	const ADF_ENTRY_DATA *entry_data_ptr_2, unsigned int *diff_para_index));

COMPAT_FN_DECL(int  ADF_COPY_EntryDataList, (const ADF_ENTRY_DATA *in_entry_data_list,
	ADF_ENTRY_DATA *out_entry_data_list, char *error_text));
COMPAT_FN_DECL(int  ADF_COPY_EntryData, (const ADF_ENTRY_DATA *in_entry_data_ptr,
	ADF_ENTRY_DATA *out_entry_data_ptr, char *error_text));

COMPAT_FN_DECL(void ADF_FREE_AreaDataList, (ADF_ENTRY_DATA *entry_data_list));
COMPAT_FN_DECL(void ADF_FREE_AreaData, (ADF_ENTRY_DATA *entry_data_ptr));

COMPAT_FN_DECL(void ADF_INIT_AreaDataList, (ADF_ENTRY_DATA *entry_data_list));
COMPAT_FN_DECL(void ADF_INIT_AreaData, (ADF_ENTRY_DATA *entry_data_ptr));

COMPAT_FN_DECL(int  ADF_COPY_ParaDataList, (unsigned int in_para_count,
	const ADF_PARA_DATA *in_para_list, unsigned int *out_para_count,
	ADF_PARA_DATA **out_para_list, char *error_text));
COMPAT_FN_DECL(int  ADF_COPY_ParaData, (const ADF_PARA_DATA *in_para_ptr,
	ADF_PARA_DATA *out_para_ptr, char *error_text));

COMPAT_FN_DECL(void ADF_FREE_ParaDataList, (unsigned int *para_count,
	ADF_PARA_DATA **para_list));
COMPAT_FN_DECL(void ADF_FREE_ParaData, (ADF_PARA_DATA *para_ptr));

COMPAT_FN_DECL(void ADF_INIT_ParaDataList, (unsigned int para_count, ADF_PARA_DATA *para_list));
COMPAT_FN_DECL(void ADF_INIT_ParaData, (ADF_PARA_DATA *para_ptr));

COMPAT_FN_DECL(int  ADF_ApplyCludesEntry, (ADF_CONTROL *control_ptr, const char *base_name,
	const char *file_name, const char *file_type, const char *man_page));
COMPAT_FN_DECL(int  ADF_ApplyCludesHText, (ADF_CONTROL *control_ptr, const char *hyper_text));
COMPAT_FN_DECL(void ADF_FREE_CludeItem, (ADF_CLUDE *clude_ptr));
COMPAT_FN_DECL(void ADF_INIT_CludeItem, (ADF_CLUDE *clude_ptr));

COMPAT_FN_DECL(int  ADF_LoadInFileList, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_LoadHTextRefFileList, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_OpenADFFileIn, (ADF_CONTROL *control_ptr, const char *file_name,
	char *error_text));
COMPAT_FN_DECL(int  ADF_OpenADFFileHTextRef, (ADF_CONTROL *control_ptr, const char *file_name,
	const char *href_string, char *error_text));
COMPAT_FN_DECL(int  ADF_OpenADFFile, (ADF_CONTROL *control_ptr, const char *file_name,
	const char *href_string, ADF_IN_FILE *in_file_ptr, char *error_text));
COMPAT_FN_DECL(void ADF_CloseADFFileIn, (ADF_CONTROL *control_ptr));

COMPAT_FN_DECL(int  ADF_OpenADFFilePrep, (ADF_CONTROL *control_ptr, const char *file_name,
	char *error_text));
COMPAT_FN_DECL(void ADF_CloseADFFilePrep, (ADF_CONTROL *control_ptr));
COMPAT_FN_DECL(int  ADF_WriteADFHumanHeader, (ADF_FILE *prep_adf_file_ptr,
	const ADF_FILE_HEADER *header_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_AddToPrepList, (ADF_CONTROL *control_ptr, const char *base_name,
	const char *file_name, const char *core_name, const char *full_name,
	const char *file_type, const char *man_page, const time_t *file_date,
	const time_t *prep_date, const ADF_DOMAIN *domain_ptr,
	const ADF_SOURCE_DATA *area_list, unsigned int publish_xref_count,
	char **publish_xref_list, char *error_text));
COMPAT_FN_DECL(int  ADF_WriteTrailer, (ADF_CONTROL *control_ptr, unsigned int entry_count,
	const ADF_ENTRY *entry_list, unsigned int htext_count,
	const ADF_HTEXT *htext_list, char *error_text));

COMPAT_FN_DECL(void ADF_RemoveExistingEntry, (ADF_CONTROL *control_ptr,
	unsigned int entry_index));
COMPAT_FN_DECL(void ADF_RemoveHText, (const ADF_ENTRY *entry_ptr, unsigned int *htext_count,
	ADF_HTEXT **htext_list));

COMPAT_FN_DECL(char            *ADF_DescribeEntry, (const ADF_ENTRY *entry_ptr, char *buffer));
COMPAT_FN_DECL(char            *ADF_DescribeInEntry, (const ADF_ENTRY *entry_ptr,
	const ADF_IN_FILE *in_file_ptr, char *buffer));
COMPAT_FN_DECL(const ADF_ENTRY *ADF_FIND_LookUpEntryByEntry, (unsigned int entry_count,
	const ADF_ENTRY *entry_list, unsigned int file_index,
	unsigned int entry_index, unsigned int *found_index));
COMPAT_FN_DECL(int              ADF_FIND_FindEntryByEntry, (unsigned int entry_count,
	const ADF_ENTRY *entry_list, unsigned int file_index,
	unsigned int entry_index, unsigned int *found_index));
COMPAT_FN_DECL(int              ADF_FIND_FindEntryByBaseName, (unsigned int entry_count,
	const ADF_ENTRY *entry_list, const char *base_name,
	unsigned int *found_index));
COMPAT_FN_DECL(int              ADF_FIND_FindHTextByText, (unsigned int htext_count,
	const ADF_HTEXT *htext_list, const char *hyper_text,
	unsigned int *found_index));
COMPAT_FN_DECL(int              ADF_AllocateEntryItem, (ADF_ENTRY *entry_ptr,
	const char *base_name, const char *file_name, const char *core_name,
	const char *full_name, const char *file_type, const char *man_page,
	char *error_text));
COMPAT_FN_DECL(int              ADF_AllocateHTextItem, (ADF_HTEXT *htext_ptr,
	const char *hyper_text, char *error_text));
COMPAT_FN_DECL(void             ADF_FreeEntryListPrep, (ADF_CONTROL *control_ptr));
COMPAT_FN_DECL(void             ADF_FreeHTextListPrep, (ADF_CONTROL *control_ptr));
COMPAT_FN_DECL(void             ADF_FreeEntryListIn, (ADF_CONTROL *control_ptr));
COMPAT_FN_DECL(void             ADF_FreeHTextListIn, (ADF_CONTROL *control_ptr));
COMPAT_FN_DECL(void             ADF_FreeEntryItem, (ADF_ENTRY *entry_ptr));
COMPAT_FN_DECL(void             ADF_FreeHTextItem, (ADF_HTEXT *htext_ptr));
COMPAT_FN_DECL(void             ADF_SORT_EntryList, (int sort_type, unsigned int entry_count,
	ADF_ENTRY *entry_list));
COMPAT_FN_DECL(void             ADF_SORT_HTextList, (int sort_type, unsigned int htext_count,
	ADF_HTEXT *htext_list));
COMPAT_FN_DECL(int              ADF_FinalizeEntries, (ADF_CONTROL *control_ptr,
	char *error_text));
COMPAT_FN_DECL(int              ADF_ReadEntry, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA_FILE *entry_data_ptr,
	ADF_SOURCE_DATA *area_list, char *error_text));
COMPAT_FN_DECL(int              ADF_WriteEntry, (ADF_CONTROL *control_ptr,
	ADF_ENTRY *entry_ptr, const ADF_SOURCE_DATA *area_list, char *error_text));
COMPAT_FN_DECL(void             ADF_SORT_EntrySections, (int sort_type,
	ADF_ENTRY_DATA *entry_data_list));

COMPAT_FN_DECL(void ADF_FreeInFileList, (ADF_CONTROL *control_ptr));
COMPAT_FN_DECL(void ADF_FREE_InFileItem, (ADF_IN_FILE *in_file_ptr));
COMPAT_FN_DECL(void ADF_INIT_InFilePtr, (ADF_IN_FILE *in_file_ptr));
COMPAT_FN_DECL(int  ADF_PadFile, (ADF_FILE *adf_file_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_PadFileBasic, (ADF_FILE *adf_file_ptr, unsigned long pad_modulus,
	char *error_text));
COMPAT_FN_DECL(int  ADF_FRead, (void *buffer, unsigned int size, unsigned int count,
	ADF_FILE *adf_file_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_FWrite, (const void *buffer, unsigned int size, unsigned int count,
	ADF_FILE *adf_file_ptr, char *error_text));

COMPAT_FN_DECL(const ADF_PFORMAT_DEF *ADF_MatchParaFormat, (const char *in_string,
	char *para_format_ptr, unsigned int *para_format_index,
	unsigned int *pattern_end_index));
COMPAT_FN_DECL(const ADF_PFORMAT_DEF *ADF_GetParaFormat, (unsigned int para_format_index));
COMPAT_FN_DECL(char                  *ADF_MakeFormatString, (unsigned int pformat_index,
	char *pformat_string));

COMPAT_FN_DECL(int ADF_MatchPattern, (const char *in_string, const char *pattern_string,
	unsigned int *pattern_end_index));
COMPAT_FN_DECL(int ADF_MatchPatternList, (const char *in_string, unsigned int pattern_count,
	char **pattern_list, unsigned int *pattern_end_index));
COMPAT_FN_DECL(int ADF_MatchPatternPtr, (const char *in_string, const ADF_PATTERN *pattern_ptr,
	unsigned int *pattern_end_index));

COMPAT_FN_DECL(int  ADF_BuildIndexItemList, (ADF_CONTROL *control_ptr,
	unsigned int *index_item_count, ADF_INDEX_ITEM **index_item_list,
	char *error_text));
COMPAT_FN_DECL(int  ADF_BuildClassTOCItemList, (ADF_CONTROL *control_ptr,
	unsigned int *index_item_count, ADF_INDEX_ITEM **index_item_list,
	char *error_text));
COMPAT_FN_DECL(int  ADF_BuildPermIndex, (ADF_CONTROL *control_ptr,
	unsigned int *index_item_count, ADF_PERM_INDEX **index_item_list,
	char *error_text));
COMPAT_FN_DECL(void ADF_FreeIndexItemList, (unsigned int *index_item_count,
	ADF_INDEX_ITEM **index_item_list));
COMPAT_FN_DECL(void ADF_FreeIndexItem, (ADF_INDEX_ITEM *index_item_ptr));
COMPAT_FN_DECL(void ADF_FreePermIndexList, (unsigned int *index_item_count,
	ADF_PERM_INDEX **index_item_list));
COMPAT_FN_DECL(void ADF_FreePermIndex, (ADF_PERM_INDEX *index_item_ptr));

COMPAT_FN_DECL(void ADF_INIT_Control, (ADF_CONTROL *control_ptr));
COMPAT_FN_DECL(void ADF_INIT_Domain, (ADF_DOMAIN *ptr));
COMPAT_FN_DECL(void ADF_INIT_DomainList, (unsigned int in_coun
	, ADF_DOMAIN *in_list));
COMPAT_FN_DECL(void ADF_INIT_Pattern, (ADF_PATTERN *ptr));
COMPAT_FN_DECL(void ADF_INIT_Section, (ADF_SECTION *ptr));
COMPAT_FN_DECL(void ADF_INIT_SectionList, (unsigned int in_count,
	ADF_SECTION *in_list));

COMPAT_FN_DECL(int ADF_COPY_Domain, (const ADF_DOMAIN *in_ptr, ADF_DOMAIN *out_ptr,
	char *error_text));
COMPAT_FN_DECL(int ADF_COPY_DomainList, (unsigned int in_count, const ADF_DOMAIN *in_list,
	unsigned int *out_count, ADF_DOMAIN **out_list, char *error_text));
COMPAT_FN_DECL(int ADF_COPY_Pattern, (const ADF_PATTERN *in_ptr, ADF_PATTERN *out_ptr,
	char *error_text));
COMPAT_FN_DECL(int ADF_COPY_Section, (const ADF_SECTION *in_ptr, ADF_SECTION *out_ptr,
	char *error_text));
COMPAT_FN_DECL(int ADF_COPY_SectionList, (unsigned int in_count,
	const ADF_SECTION *in_list, unsigned int *out_count,
	ADF_SECTION **out_list, char *error_text));

COMPAT_FN_DECL(void ADF_FREE_Control, (ADF_CONTROL *control_ptr));
COMPAT_FN_DECL(void ADF_FREE_Domain, (ADF_DOMAIN *ptr));
COMPAT_FN_DECL(void ADF_FREE_DomainList, (unsigned int *in_count,
	ADF_DOMAIN **in_list));
COMPAT_FN_DECL(void ADF_FREE_Pattern, (ADF_PATTERN *ptr));
COMPAT_FN_DECL(void ADF_FREE_Section, (ADF_SECTION *ptr));
COMPAT_FN_DECL(void ADF_FREE_SectionList, (unsigned int *in_count,
	ADF_SECTION **in_list));

COMPAT_FN_DECL(int  ADF_CopyDefaultDefSpec, (unsigned int *domain_count,
	ADF_DOMAIN **domain_list, char *error_text));
COMPAT_FN_DECL(void ADF_GetDefaultDefSpec, (unsigned int *domain_count,
	ADF_DOMAIN **domain_list));

COMPAT_FN_DECL(int ADF_EMIT_DefCDomainList, (unsigned int domain_count,
	const ADF_DOMAIN *domain_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));

COMPAT_FN_DECL(void ADF_EMIT_Def, (unsigned int domain_count, const ADF_DOMAIN *domain_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void ADF_EMIT_DomainDef, (const ADF_DOMAIN *domain_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void ADF_EMIT_PatternList, (const ADF_PATTERN *pattern_ptr,
	const char *pattern_name, int trailing_comma_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void ADF_EMIT_PatternString, (const char *pattern_string,
	const char *pattern_name, int trailing_comma_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void ADF_EMIT_SectionDef, (const ADF_SECTION *section_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));

COMPAT_FN_DECL(int ADF_ReadSourceFile, (const char *file_name, unsigned int *line_count,
	char ***line_list, ADF_BIG_char **buffer_ptr, char *error_text));
COMPAT_FN_DECL(int ADF_ReadDefinitionFile, (ADF_CONTROL *control_ptr, const char *file_name,
	char *error_text));
COMPAT_FN_DECL(int ADF_ReadFileBuffer, (const char *file_name, unsigned int *buffer_length,
	char **buffer_ptr, char *error_text));

COMPAT_FN_DECL(char *ADF_AreaToParseArea, (char *area_name));
COMPAT_FN_DECL(char *ADF_GetAreaName, (unsigned int area_index, char *area_name));
COMPAT_FN_DECL(char *ADF_GetParseAreaName, (unsigned int area_index, char *area_name));
COMPAT_FN_DECL(char *ADF_GetOutputAreaName, (int area_name_type, unsigned int area_index,
	char **area_name_list, const char *section_name,
	unsigned int max_area_name_length, char *area_name));

COMPAT_FN_DECL(char *ADF_GetSpecifedErrorString, (int, char *));
COMPAT_FN_DECL(char *ADF_GetLastErrorString, (char *));

COMPAT_FN_DECL(const ADF_AREA   *ADF_FIND_AreaByName, (const char *area_name,
	unsigned int *found_index));
COMPAT_FN_DECL(const ADF_DOMAIN *ADF_FIND_Domain, (unsigned int domain_count,
	const ADF_DOMAIN *domain_list, const char *file_type,
	unsigned int *found_index));

COMPAT_FN_DECL(int ADF_GetParams, (void *control_ptr, unsigned int argc, char **argv,
	int *help_flag, int *version_flag, int (*parse_function)(void *,
	unsigned int, char **, int, unsigned int, char *), char *error_text));

COMPAT_FN_DECL(void ADF_DoSimpleUsage, (int exit_code, const char *program_name,
	const char *exit_message, const char *usage_string));
COMPAT_FN_DECL(void ADF_DoUsage, (int exit_code, const char *program_name,
	const char *exit_message, char **usage_string_list));
COMPAT_FN_DECL(void ADF_DoFormatUsage, (int exit_code, const char *program_name,
	const char *exit_message, char **usage_string_list));

#ifndef NO_STDARGS
COMPAT_FN_DECL(void ADF_LogMessage, (struct timeval *timeval_ptr, int log_priority,
	ADF_FILE *adf_file_ptr, FILE *file_ptr, int syslog_flag,
	const char *in_format, ...));
#else
COMPAT_FN_DECL(void ADF_LogMessage, (struct timeval *timeval_ptr, int log_priority,
	ADF_FILE *adf_file_ptr, FILE *file_ptr, int syslog_flag,
	const char *in_format, va_alist));
#endif /* # ifndef NO_STDARGS */
COMPAT_FN_DECL(int  ADF_LogEnsureSpace, (ADF_FILE *adf_file_ptr));
COMPAT_FN_DECL(void ADF_LogSeparatorStartLog, (ADF_FILE *adf_file_ptr, FILE *file_ptr));
COMPAT_FN_DECL(void ADF_LogSeparatorEndLog, (ADF_FILE *adf_file_ptr, FILE *file_ptr));
COMPAT_FN_DECL(void ADF_LogSeparatorHyphenChar, (ADF_FILE *adf_file_ptr, FILE *file_ptr));
COMPAT_FN_DECL(void ADF_LogSeparatorEqualChar, (ADF_FILE *adf_file_ptr, FILE *file_ptr));
COMPAT_FN_DECL(void ADF_LogSeparatorChar, (ADF_FILE *adf_file_ptr, FILE *file_ptr,
	int log_char));
COMPAT_FN_DECL(void ADF_LogSeparatorString, (ADF_FILE *adf_file_ptr, FILE *file_ptr,
	const char *log_string));
COMPAT_FN_DECL(int  ADF_GetLogMessageFlagFILE, (void));
COMPAT_FN_DECL(int  ADF_GetLogMessageFlagADF_FILE, (void));
COMPAT_FN_DECL(int  ADF_GetLogMessageFlagSYSLOG, (void));
COMPAT_FN_DECL(int  ADF_SetLogMessageFlagFILE, (int new_flag_value));
COMPAT_FN_DECL(int  ADF_SetLogMessageFlagADF_FILE, (int new_flag_value));
COMPAT_FN_DECL(int  ADF_SetLogMessageFlagSYSLOG, (int new_flag_value));

COMPAT_FN_DECL(int   ADF_OUT_AllocFileString, (ADF_CONTROL *control_ptr,
	unsigned int alloc_length, char *error_text));
COMPAT_FN_DECL(int   ADF_OUT_AllocHTextString, (ADF_CONTROL *control_ptr,
	unsigned int link_length, char *error_text));
COMPAT_FN_DECL(int   ADF_OUT_AllocString, (unsigned int alloc_length, const char *alloc_text,
	unsigned int *string_length, char **string_ptr, char *error_text));
COMPAT_FN_DECL(char *ADF_OUT_CleanName, (char *in_name));
COMPAT_FN_DECL(int   ADF_OUT_OpenOutputFile, (ADF_CONTROL *control_ptr, char *error_text));
COMPAT_FN_DECL(void  ADF_OUT_LogOutputFile, (ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const char *output_file_name));

COMPAT_FN_DECL(int ADF_PARG_ADFDefFile, (const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, char **adf_def_file_name, int *error_code,
	char *error_text));
COMPAT_FN_DECL(int ADF_PARG_IgnoreBadCmntFlag, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *ignore_bad_cmt_flag,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_PARG_PrepADFFile, (const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, char **prep_adf_file_name, int *error_code,
	char *error_text));
COMPAT_FN_DECL(int ADF_PARG_PrepADFFileMode, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *prep_adf_file_mode,
	int *error_code, char *error_text));

COMPAT_FN_DECL(int ADF_PUSE_ADFDefFile, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_PUSE_IgnoreBadCmntFlag, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_PUSE_PrepADFFile, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count, char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_PUSE_PrepADFFileMode, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));

COMPAT_FN_DECL(int ADF_OARG_AreaName, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, char **area_name_list,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_AreaNameType, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *area_name_type,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_AreaOrderType, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *area_order_type,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_ExternalHTextRef, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, char **external_ref,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_GenerateType, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *generate_type,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_HyperTextFlag, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *hyper_text_flag,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_KeepBadSeeAlso, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	int *keep_bad_see_also_flag, int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_OutputByFileFlag, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	int *output_by_file_flag, int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_OutputCommentFlag, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	int *output_comment_flag, int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_OutputDir, (const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, char **output_dir, char **output_dir_basic,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_OutputToStdoutFlag, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	int *output_to_stdout_flag, int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_OutputType, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *output_type,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_ParseOutParam, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_CONTROL *control_ptr, int *error_code, char *error_text));

COMPAT_FN_DECL(int ADF_OUSE_AreaName, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_AreaNameType, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_AreaOrderType, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_ExternalHTextRef, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_GenerateType, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_HyperTextFlag, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_KeepBadSeeAlso, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_OutputByFileFlag, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_OutputCommentFlag, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_OutputDir, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_OutputToStdoutFlag, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_OutputType, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_ParseOutParam, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));

COMPAT_FN_DECL(int ADF_OARG_FRAME_ParseOutParam, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_FRAME_DATA *html_data_ptr, int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_HTML_ParseOutParam, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_HTML_DATA *html_data_ptr, int *error_code, char *error_text));
COMPAT_FN_DECL(int ADF_OARG_MAN_ParseOutParam, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr,
	ADF_MAN_DATA *man_data_ptr, int *error_code, char *error_text));

COMPAT_FN_DECL(int ADF_OUSE_FRAME_ParseOutParam, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_HTML_ParseOutParam, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_OUSE_MAN_ParseOutParam, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));

COMPAT_FN_DECL(int  ADF_BARG_CheckOnlyFlag, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *check_only_flag,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  ADF_BARG_CludeEntry, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, ADF_CONTROL *control_ptr,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  ADF_BARG_CludeHText, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, ADF_CONTROL *control_ptr,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  ADF_BARG_ContOnErrorFlag, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *cont_on_error_flag,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  ADF_BARG_DuplicateType, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *dup_handling_type,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  ADF_BARG_IgnoreSection, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *ignore_section_list,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  ADF_BARG_LogDir, (const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, char **log_dir, int *error_code, char *error_text));
COMPAT_FN_DECL(int  ADF_BARG_LogFlag, (const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *log_flag, int *error_code, char *error_text));
COMPAT_FN_DECL(int  ADF_BARG_QuietFlag, (const char *in_arg_ptr, unsigned int *in_arg_length,
	char **in_data_ptr, int *quiet_flag, int *error_code, char *error_text));
COMPAT_FN_DECL(int  ADF_BARG_SortOrderType, (const char *in_arg_ptr,
	unsigned int *in_arg_length, char **in_data_ptr, int *sort_order_type,
	int *error_code, char *error_text));
COMPAT_FN_DECL(int  ADF_BARG_BasicParamAlloc, (const char *in_arg_ptr, unsigned int arg_length,
	const char *data_ptr, char **alloc_ptr, char *error_text));
COMPAT_FN_DECL(int  ADF_BARG_BasicPathExpand, (const char *in_arg_ptr, unsigned int arg_length,
	const char *data_ptr, char **alloc_ptr, char *error_text));
COMPAT_FN_DECL(void ADF_BARG_BadComponentMsg, (const char *in_arg_ptr, unsigned int arg_length,
	const char *data_ptr, const char *expected_string, char *error_text));

COMPAT_FN_DECL(int ADF_BUSE_CheckOnlyFlag, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_CludeEntry, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_CludeHText, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_ContOnErrorFlag, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_DuplicateType, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_Help, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_IgnoreSection, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_LogDir, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_LogFlag, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_QuietFlag, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_SortOrderType, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_Version, (const char *base_arg_ptr, int optional_flag,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_AppendParamText, (unsigned int *usage_count, char ***usage_list,
	char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_AppendLine, (const char *in_line, unsigned int *usage_count,
	char ***usage_list, char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_AppendNL, (unsigned int *usage_count, char ***usage_list,
	char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_AppendNULL, (unsigned int *usage_count, char ***usage_list,
	char *error_text));
COMPAT_FN_DECL(int ADF_BUSE_BasicConstruct, (const char *base_arg_ptr, const char *arg_ptr,
	int optional_flag, char **arg_usage_list,
	char **extra_usage_list, unsigned int *usage_count,
	char ***usage_list, char *error_text));

/*	***********************************************************************	*/

#endif /* #ifndef h__ADF_H__h */

