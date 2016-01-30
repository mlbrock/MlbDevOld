/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Internal Include File							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Tib/Rendezvous Utility
								Library.

	Revision History	:	1996-01-02 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__RVUTILI_H__h

#define h__RVUTILI_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*    Include necessary header files . . .                                 */
/*	***********************************************************************	*/

#include "rvutil.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	RVUTIL Truth Code Mappings

   NAME        :	RVUTIL Truth Code Mappings

	SYNOPSIS		:	truth_code = RVUTIL_MAP_TRUTH_STR(str_code);

						truth_code = RVUTIL_MAP_TRUTH_GEN(gen_code);

						truth_code = RVUTIL_MAP_TRUTH_DAT(dat_code);

						truth_code = RVUTIL_MAP_TRUTH_SPF(spf_code);

						truth_code = RVUTIL_MAP_TRUTH_MFILE(mfile_code);

						truth_code = RVUTIL_MAP_TRUTH_MLOG(mlog_code);

	DESCRIPTION	:	The RVUTIL truth code mapping macros map truth codes from
						various low-level libraries to RVUTIL truth codes.

						(.) ''RVUTIL_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a RVUTIL truth code.

						(.) ''RVUTIL_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a RVUTIL truth code.

						(.) ''RVUTIL_MAP_TRUTH_DAT'' maps a truth code
						from a DATFUNCS truth code to a RVUTIL truth code.

						(.) ''RVUTIL_MAP_TRUTH_SPF'' maps a truth code
						from a SPFFUNCS truth code to a RVUTIL truth code.

						(.) ''RVUTIL_MAP_TRUTH_MFILE'' maps a truth code
						from a MFILE truth code to a RVUTIL truth code.

						(.) ''RVUTIL_MAP_TRUTH_MLOG'' maps a truth code
						from a MLOG truth code to a RVUTIL truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent RVUTIL truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						RVUTIL return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	RVUTIL_MAP_TRUTH_STR
						RVUTIL_MAP_TRUTH_GEN
						RVUTIL_MAP_TRUTH_DAT
						RVUTIL_MAP_TRUTH_SPF
						RVUTIL_MAP_TRUTH_MFILE
						RVUTIL_MAP_TRUTH_MLOG
						Truth Code Mappings:RVUTIL_MAP_TRUTH_STR
						Truth Code Mappings:RVUTIL_MAP_TRUTH_GEN
						Truth Code Mappings:RVUTIL_MAP_TRUTH_DAT
						Truth Code Mappings:RVUTIL_MAP_TRUTH_SPF
						Truth Code Mappings:RVUTIL_MAP_TRUTH_MFILE
						Truth Code Mappings:RVUTIL_MAP_TRUTH_MLOG
						Macros and Manifest Constants:RVUTIL_MAP_TRUTH_STR
						Macros and Manifest Constants:RVUTIL_MAP_TRUTH_GEN
						Macros and Manifest Constants:RVUTIL_MAP_TRUTH_DAT
						Macros and Manifest Constants:RVUTIL_MAP_TRUTH_SPF
						Macros and Manifest Constants:RVUTIL_MAP_TRUTH_MFILE
						Macros and Manifest Constants:RVUTIL_MAP_TRUTH_MLOG
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	RVUTIL_MAP_TRUTH_STR
						RVUTIL_MAP_TRUTH_GEN
						RVUTIL_MAP_TRUTH_DAT
						RVUTIL_MAP_TRUTH_SPF
						RVUTIL_MAP_TRUTH_MFILE
						RVUTIL_MAP_TRUTH_MLOG
						RVUTIL Truth Code Mappings
						RVUTIL Truth Code Mapping
						RVUTIL truth code mappings
						RVUTIL truth code mapping

   PUBLISH NAME:	RVUTIL_MAP_TRUTH_STR
						RVUTIL_MAP_TRUTH_GEN
						RVUTIL_MAP_TRUTH_DAT
						RVUTIL_MAP_TRUTH_SPF
						RVUTIL_MAP_TRUTH_MFILE
						RVUTIL_MAP_TRUTH_MLOG

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define RVUTIL_MAP_TRUTH_STR(str_code)			\
	(((str_code) == STRFUNCS_TRUE) ? RVUTIL_TRUE : RVUTIL_FALSE)
#define RVUTIL_MAP_TRUTH_GEN(gen_code)			\
	(((gen_code) == GENFUNCS_TRUE) ? RVUTIL_TRUE : RVUTIL_FALSE)
#define RVUTIL_MAP_TRUTH_DAT(dat_code)			\
	(((dat_code) == DATFUNCS_TRUE) ? RVUTIL_TRUE : RVUTIL_FALSE)
#define RVUTIL_MAP_TRUTH_SPF(spf_code)			\
	(((spf_code) == SPF_TRUE) ? RVUTIL_TRUE : RVUTIL_FALSE)
#define RVUTIL_MAP_TRUTH_MFILE(mfile_code)	\
	(((mfile_code) == MFILE_TRUE) ? RVUTIL_TRUE : RVUTIL_FALSE)
#define RVUTIL_MAP_TRUTH_MLOG(mlog_code)		\
	(((mlog_code) == MLOG_TRUE) ? RVUTIL_TRUE : RVUTIL_FALSE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define RVUTIL_MAP_TRUTH_STR_TO_RVUTIL(str_code)		\
	RVUTIL_MAP_TRUTH_STR(str_code)
#define RVUTIL_MAP_TRUTH_GEN_TO_RVUTIL(gen_code)		\
	RVUTIL_MAP_TRUTH_GEN(gen_code)
#define RVUTIL_MAP_TRUTH_DAT_TO_RVUTIL(dat_code)		\
	RVUTIL_MAP_TRUTH_DAT(dat_code)
#define RVUTIL_MAP_TRUTH_SPF_TO_RVUTIL(spf_code)		\
	RVUTIL_MAP_TRUTH_SPF(spf_code)
#define RVUTIL_MAP_TRUTH_MFILE_TO_RVUTIL(mfile_code)	\
	RVUTIL_MAP_TRUTH_MFILE(mfile_code)
#define RVUTIL_MAP_TRUTH_MLOG_TO_RVUTIL(mlog_code)		\
	RVUTIL_MAP_TRUTH_MLOG(mlog_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	RVUTIL Return Code Mappings

   NAME        :	RVUTIL Return Code Mappings

	SYNOPSIS		:	return_code = RVUTIL_MAP_ERROR_STR(str_code);

						return_code = RVUTIL_MAP_ERROR_GEN(gen_code);

						return_code = RVUTIL_MAP_ERROR_DAT(dat_code);

						return_code = RVUTIL_MAP_ERROR_SPF(spf_code);

						return_code = RVUTIL_MAP_ERROR_MFILE(mfile_code);

						return_code = RVUTIL_MAP_ERROR_MLOG(mfile_code);

	DESCRIPTION	:	The RVUTIL return code mapping macros map return codes from
						various low-level libraries to RVUTIL return codes.

						(.) ''RVUTIL_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a RVUTIL return code.

						(.) ''RVUTIL_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a RVUTIL return code.

						(.) ''RVUTIL_MAP_ERROR_DAT'' maps a return code
						from a DATFUNCS return code to a RVUTIL return code.

						(.) ''RVUTIL_MAP_ERROR_SPF'' maps a return code
						from a SPFFUNCS return code to a RVUTIL return code.

						(.) ''RVUTIL_MAP_ERROR_MFILE'' maps a return code
						from a MFILE return code to a RVUTIL return code.

						(.) ''RVUTIL_MAP_ERROR_MLOG'' maps a return code
						from a MLOG return code to a RVUTIL return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent RVUTIL return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						RVUTIL truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	RVUTIL_MAP_ERROR_STR
						RVUTIL_MAP_ERROR_GEN
						RVUTIL_MAP_ERROR_DAT
						RVUTIL_MAP_ERROR_SPF
						RVUTIL_MAP_ERROR_MFILE
						RVUTIL_MAP_ERROR_MLOG
						Return Code Mappings:RVUTIL_MAP_ERROR_STR
						Return Code Mappings:RVUTIL_MAP_ERROR_GEN
						Return Code Mappings:RVUTIL_MAP_ERROR_DAT
						Return Code Mappings:RVUTIL_MAP_ERROR_SPF
						Return Code Mappings:RVUTIL_MAP_ERROR_MFILE
						Return Code Mappings:RVUTIL_MAP_ERROR_MLOG
						Macros and Manifest Constants:RVUTIL_MAP_ERROR_STR
						Macros and Manifest Constants:RVUTIL_MAP_ERROR_GEN
						Macros and Manifest Constants:RVUTIL_MAP_ERROR_DAT
						Macros and Manifest Constants:RVUTIL_MAP_ERROR_SPF
						Macros and Manifest Constants:RVUTIL_MAP_ERROR_MFILE
						Macros and Manifest Constants:RVUTIL_MAP_ERROR_MLOG
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	RVUTIL_MAP_ERROR_STR
						RVUTIL_MAP_ERROR_GEN
						RVUTIL_MAP_ERROR_DAT
						RVUTIL_MAP_ERROR_SPF
						RVUTIL_MAP_ERROR_MFILE
						RVUTIL_MAP_ERROR_MLOG
						RVUTIL Return Code Mappings
						RVUTIL Return Code Mapping
						RVUTIL return code mappings
						RVUTIL return code mapping
						RVUTIL Status Code Mappings
						RVUTIL Status Code Mapping
						RVUTIL status code mappings
						RVUTIL status code mapping
						RVUTIL Error Code Mappings
						RVUTIL Error Code Mapping
						RVUTIL error code mappings
						RVUTIL error code mapping

   PUBLISH NAME:	RVUTIL_MAP_ERROR_STR
						RVUTIL_MAP_ERROR_GEN
						RVUTIL_MAP_ERROR_DAT
						RVUTIL_MAP_ERROR_SPF
						RVUTIL_MAP_ERROR_MFILE
						RVUTIL_MAP_ERROR_MLOG

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define RVUTIL_MAP_ERROR_STR(str_code)								   				\
	(((str_code) == STRFUNCS_SUCCESS)          ? RVUTIL_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? RVUTIL_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? RVUTIL_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? RVUTIL_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? RVUTIL_SYSTEM_FAILURE   :	\
	 RVUTIL_FAILURE)
#define RVUTIL_MAP_ERROR_GEN(gen_code)													\
	(((gen_code) == GENFUNCS_SUCCESS)          ? RVUTIL_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? RVUTIL_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? RVUTIL_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? RVUTIL_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? RVUTIL_SYSTEM_FAILURE   :	\
	 ((gen_code) == GENFUNCS_LOCK_ACQ_FAILURE) ? RVUTIL_LOCK_ACQ_FAILURE :	\
	 RVUTIL_FAILURE)
#define RVUTIL_MAP_ERROR_DAT(dat_code)													\
	(((dat_code) == DATFUNCS_SUCCESS)          ? RVUTIL_SUCCESS          :	\
	 ((dat_code) == DATFUNCS_FAILURE)          ? RVUTIL_FAILURE          :	\
	 ((dat_code) == DATFUNCS_MEMORY_FAILURE)   ? RVUTIL_MEMORY_FAILURE   :	\
	 RVUTIL_FAILURE)
#define RVUTIL_MAP_ERROR_SPF(spf_code)													\
	(((spf_code) == SPFFUNCS_SUCCESS)          ? RVUTIL_SUCCESS          :	\
	 ((spf_code) == SPFFUNCS_FAILURE)          ? RVUTIL_FAILURE          :	\
	 ((spf_code) == SPFFUNCS_BAD_ARGS_FAILURE) ? RVUTIL_BAD_ARGS_FAILURE :	\
	 ((spf_code) == SPFFUNCS_MEMORY_FAILURE)   ? RVUTIL_MEMORY_FAILURE   :	\
	 ((spf_code) == SPFFUNCS_SYSTEM_FAILURE)   ? RVUTIL_SYSTEM_FAILURE   :	\
	 RVUTIL_FAILURE)
#define RVUTIL_MAP_ERROR_MFILE(mfile_code)											\
	(((mfile_code) == MFILE_SUCCESS)          ? RVUTIL_SUCCESS          :	\
	 ((mfile_code) == MFILE_FAILURE)          ? RVUTIL_FAILURE          :	\
	 ((mfile_code) == MFILE_BAD_ARGS_FAILURE) ? RVUTIL_BAD_ARGS_FAILURE :	\
	 ((mfile_code) == MFILE_MEMORY_FAILURE)   ? RVUTIL_MEMORY_FAILURE   :	\
	 ((mfile_code) == MFILE_SYSTEM_FAILURE)   ? RVUTIL_SYSTEM_FAILURE   :	\
	 RVUTIL_FAILURE)
#define RVUTIL_MAP_ERROR_MLOG(mlog_code)												\
	(((mlog_code) == MLOG_SUCCESS)            ? RVUTIL_SUCCESS          :	\
	 ((mlog_code) == MLOG_FAILURE)            ? RVUTIL_FAILURE          :	\
	 ((mlog_code) == MLOG_BAD_ARGS_FAILURE)   ? RVUTIL_BAD_ARGS_FAILURE :	\
	 ((mlog_code) == MLOG_MEMORY_FAILURE)     ? RVUTIL_MEMORY_FAILURE   :	\
	 ((mlog_code) == MLOG_SYSTEM_FAILURE)     ? RVUTIL_SYSTEM_FAILURE   :	\
	 RVUTIL_FAILURE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define RVUTIL_MAP_ERROR_STR_TO_RVUTIL(str_code)								   \
	RVUTIL_MAP_ERROR_STR(str_code)
#define RVUTIL_MAP_ERROR_GEN_TO_RVUTIL(gen_code)									\
	RVUTIL_MAP_ERROR_GEN(gen_code)
#define RVUTIL_MAP_ERROR_DAT_TO_RVUTIL(dat_code)									\
	RVUTIL_MAP_ERROR_DAT(dat_code)
#define RVUTIL_MAP_ERROR_SPF_TO_RVUTIL(spf_code)									\
	RVUTIL_MAP_ERROR_SPF(spf_code)
#define RVUTIL_MAP_ERROR_MFILE_TO_RVUTIL(mfile_code)								\
	RVUTIL_MAP_ERROR_MFILE(mfile_code)
#define RVUTIL_MAP_ERROR_MLOG_TO_RVUTIL(mlog_code)									\
	RVUTIL_MAP_ERROR_MLOG(mlog_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	RVUTIL Library Version Number

   NAME        :	RVUTIL Library Version Number

   DESCRIPTION :	The RVUTIL library version number manifest constants
						together define the current version number of the RVUTIL
						library as a whole.

						(.) ''RVUTIL_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''RVUTIL_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''RVUTIL_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''RVUTIL_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	RVUTIL_VERSION_MAJOR
						RVUTIL_VERSION_MINOR
						RVUTIL_VERSION_RELEASE
						RVUTIL_VERSION_BUILD
						RVUTIL Version Numbers:Library Version Number
						Library Version Number:RVUTIL_VERSION_MAJOR
						Library Version Number:RVUTIL_VERSION_MINOR
						Library Version Number:RVUTIL_VERSION_RELEASE
						Library Version Number:RVUTIL_VERSION_BUILD
						Macros and Manifest Constants:RVUTIL_VERSION_MAJOR
						Macros and Manifest Constants:RVUTIL_VERSION_MINOR
						Macros and Manifest Constants:RVUTIL_VERSION_RELEASE
						Macros and Manifest Constants:RVUTIL_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	RVUTIL_VERSION_MAJOR
						RVUTIL_VERSION_MINOR
						RVUTIL_VERSION_RELEASE
						RVUTIL_VERSION_BUILD
						RVUTIL Library Version Number
						RVUTIL library version number
						RVUTIL Library Version
						RVUTIL library version
						RVUTIL Version Number
						RVUTIL version number
						RVUTIL Version
						RVUTIL version

   PUBLISH NAME:	RVUTIL_VERSION_MAJOR
						RVUTIL_VERSION_MINOR
						RVUTIL_VERSION_RELEASE
						RVUTIL_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						RVUTIL Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define RVUTIL_VERSION_MAJOR					((unsigned char) 1)
#define RVUTIL_VERSION_MINOR					((unsigned char) 0)
#define RVUTIL_VERSION_RELEASE				((unsigned char) 0)
#define RVUTIL_VERSION_BUILD					((unsigned char) 'A')
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Function prototypes for internal functions within 'rvutil.a' . . .		*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Parameter string construction function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(char *RVUTIL_ParamANY, (const char *in_type_name,
	const char *in_string, int more_flag, char *out_string));
COMPAT_FN_DECL(char *RVUTIL_ParamSTR, (const char *in_type_name,
	const char *in_string, unsigned int max_length, int more_flag,
	char *out_string));
COMPAT_FN_DECL(char *RVUTIL_ParamHEX, (const char *in_type_name,
	unsigned long in_ulong, int more_flag, char *out_string));
COMPAT_FN_DECL(char *RVUTIL_ParamULD, (const char *in_type_name,
	unsigned long in_ulong, int more_flag, char *out_string));
COMPAT_FN_DECL(char *RVUTIL_ParamSLD, (const char *in_type_name, long in_slong,
	int more_flag, char *out_string));
COMPAT_FN_DECL(char *RVUTIL_ParamPTR, (const char *in_type_name, void *in_ptr,
	int more_flag, char *out_string));
COMPAT_FN_DECL(char *RVUTIL_ParamSUB, (const char *in_type_name,
	const char *in_subject, int more_flag, char *out_string));
COMPAT_FN_DECL(char *RVUTIL_ParamSND, (const char *in_type_name,
	const char *in_snd, int more_flag, char *out_string));
COMPAT_FN_DECL(char *RVUTIL_ParamFNC, (const char *in_type_name,
	int (*in_ptr)(void), int more_flag, char *out_string));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Support for the test harness . . .													*/
/*	***********************************************************************	*/
COMPAT_FN_DECL(void      RVUTIL_TEST_Callback,
	(rv_Session session, rv_Name name, rv_Name reply_name, rvmsg_Type msg_type,
	rvmsg_Size msg_size, rvmsg_Data msg_data, rv_Opaque closure));
COMPAT_FN_DECL(void      RVUTIL_TEST_EventCallback,
	(rv_Session session, rv_Opaque closure, rvevm_EventType event_type,
	rvevm_EventId event_id));
COMPAT_FN_DECL(void      RVUTIL_TEST_FTCallback,
	(rv_Session session, rv_Name name, rvft_Action action, rvft_Id id,
	rv_Opaque closure));
COMPAT_FN_DECL(rv_Opaque RVUTIL_TEST_Apply,
	(rv_Session session, rv_Name name, rvmsg_Type data_type,
	rvmsg_Size data_size, rvmsg_Data data, rv_Opaque closure));
/*	***********************************************************************	*/

#endif /* #ifndef h__RVUTILI_H__h */

