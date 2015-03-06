/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Internal Include File	*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Multi-Threading
								Interface Facility (MTIF) library.

	Revision History	:	1994-09-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__MTIFI_H__h

#define h__MTIFI_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Necessary include files . . .															*/
/*	***********************************************************************	*/

#include "mtif.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MTIF Truth Code Mappings

   NAME        :	MTIF Truth Code Mappings

	SYNOPSIS		:	truth_code = MTIF_MAP_TRUTH_STR(str_code);

						truth_code = MTIF_MAP_TRUTH_GEN(gen_code);

	DESCRIPTION	:	The MTIF truth code mapping macros map truth codes from
						various low-level libraries to MTIF truth codes.

						(.) ''MTIF_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a MTIF truth code.

						(.) ''MTIF_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a MTIF truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent MTIF truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						MTIF return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2015 Michael L. Brock

   OUTPUT INDEX:	MTIF_MAP_TRUTH_STR
						MTIF_MAP_TRUTH_GEN
						Truth Code Mappings:MTIF_MAP_TRUTH_STR
						Truth Code Mappings:MTIF_MAP_TRUTH_GEN
						Macros and Manifest Constants:MTIF_MAP_TRUTH_STR
						Macros and Manifest Constants:MTIF_MAP_TRUTH_GEN
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MTIF_MAP_TRUTH_STR
						MTIF_MAP_TRUTH_GEN
						MTIF Truth Code Mappings
						MTIF Truth Code Mapping
						MTIF truth code mappings
						MTIF truth code mapping

   PUBLISH NAME:	MTIF_MAP_TRUTH_STR
						MTIF_MAP_TRUTH_GEN

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define MTIF_MAP_TRUTH(code)							\
	((code)                              ? MTIF_TRUE : MTIF_FALSE)
#define MTIF_MAP_TRUTH_NOT(code)						\
	((MTIF_MAP_TRUTH(code) == MTIF_TRUE) ? MTIF_FALSE : MTIF_TRUE)
	/*	*****************************************************************	*/
#define MTIF_MAP_TRUTH_STR(str_code)				\
	(((str_code) == STRFUNCS_TRUE)       ? MTIF_TRUE : MTIF_FALSE)
#define MTIF_MAP_TRUTH_GEN(gen_code)				\
	(((gen_code) == GENFUNCS_TRUE)       ? MTIF_TRUE : MTIF_FALSE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define MTIF_MAP_TRUTH_STR_TO_MTIF(str_code)		\
	MTIF_MAP_TRUTH_STR(str_code)
#define MTIF_MAP_TRUTH_GEN_TO_MTIF(gen_code)		\
	MTIF_MAP_TRUTH_GEN(gen_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MTIF Return Code Mappings

   NAME        :	MTIF Return Code Mappings

	SYNOPSIS		:	return_code = MTIF_MAP_ERROR_STR(str_code);

						return_code = MTIF_MAP_ERROR_GEN(gen_code);

	DESCRIPTION	:	The MTIF return code mapping macros map return codes from
						various low-level libraries to MTIF return codes.

						(.) ''MTIF_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a MTIF return code.

						(.) ''MTIF_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a MTIF return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent MTIF return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						MTIF truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1994 - 2015 Michael L. Brock

   OUTPUT INDEX:	MTIF_MAP_ERROR_STR
						MTIF_MAP_ERROR_GEN
						Return Code Mappings:MTIF_MAP_ERROR_STR
						Return Code Mappings:MTIF_MAP_ERROR_GEN
						Macros and Manifest Constants:MTIF_MAP_ERROR_STR
						Macros and Manifest Constants:MTIF_MAP_ERROR_GEN
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MTIF_MAP_ERROR_STR
						MTIF_MAP_ERROR_GEN
						MTIF Return Code Mappings
						MTIF Return Code Mapping
						MTIF return code mappings
						MTIF return code mapping
						MTIF Status Code Mappings
						MTIF Status Code Mapping
						MTIF status code mappings
						MTIF status code mapping
						MTIF Error Code Mappings
						MTIF Error Code Mapping
						MTIF error code mappings
						MTIF error code mapping

   PUBLISH NAME:	MTIF_MAP_ERROR_STR
						MTIF_MAP_ERROR_GEN

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define MTIF_MAP_ERROR_STR(str_code)										 			\
	(((str_code) == STRFUNCS_SUCCESS)          ? MTIF_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? MTIF_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? MTIF_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? MTIF_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? MTIF_SYSTEM_FAILURE   :	\
	 MTIF_FAILURE)
#define MTIF_MAP_ERROR_GEN(gen_code)													\
	(((gen_code) == GENFUNCS_SUCCESS)          ? MTIF_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? MTIF_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? MTIF_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? MTIF_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? MTIF_SYSTEM_FAILURE   :	\
	 ((gen_code) == GENFUNCS_LOCK_ACQ_FAILURE) ? MTIF_LOCK_ACQ_FAILURE :	\
	 MTIF_FAILURE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define MTIF_MAP_ERROR_STR_TO_MTIF(str_code)									 	\
	MTIF_MAP_ERROR_STR(str_code)
#define MTIF_MAP_ERROR_GEN_TO_MTIF(gen_code)										\
	MTIF_MAP_ERROR_GEN(gen_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MTIF Library Version Number

   NAME        :	MTIF Library Version Number

   DESCRIPTION :	The MTIF library version number manifest constants
						together define the current version number of the MTIF
						library as a whole.

						(.) ''MTIF_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''MTIF_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''MTIF_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''MTIF_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

   OUTPUT INDEX:	MTIF_VERSION_MAJOR
						MTIF_VERSION_MINOR
						MTIF_VERSION_RELEASE
						MTIF_VERSION_BUILD
						MTIF Version Numbers:Library Version Number
						Library Version Number:MTIF_VERSION_MAJOR
						Library Version Number:MTIF_VERSION_MINOR
						Library Version Number:MTIF_VERSION_RELEASE
						Library Version Number:MTIF_VERSION_BUILD
						Macros and Manifest Constants:MTIF_VERSION_MAJOR
						Macros and Manifest Constants:MTIF_VERSION_MINOR
						Macros and Manifest Constants:MTIF_VERSION_RELEASE
						Macros and Manifest Constants:MTIF_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MTIF_VERSION_MAJOR
						MTIF_VERSION_MINOR
						MTIF_VERSION_RELEASE
						MTIF_VERSION_BUILD
						MTIF Library Version Number
						MTIF library version number
						MTIF Library Version
						MTIF library version
						MTIF Version Number
						MTIF version number
						MTIF Version
						MTIF version

   PUBLISH NAME:	MTIF_VERSION_MAJOR
						MTIF_VERSION_MINOR
						MTIF_VERSION_RELEASE
						MTIF_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						MTIF Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define MTIF_VERSION_MAJOR					((unsigned char) 1)
#define MTIF_VERSION_MINOR					((unsigned char) 0)
#define MTIF_VERSION_RELEASE				((unsigned char) 0)
#define MTIF_VERSION_BUILD					((unsigned char) 'A')
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_ANY_IS_PTR(any_handle_ptr, any_signature)	\
	MTIF_MAP_TRUTH((((any_handle_ptr) != NULL) &&	\
						((any_handle_ptr)->signature == (any_signature))))
#define MTIF_MTR_IS_PTR(mtr_handle_ptr)				\
	MTIF_ANY_IS_PTR((mtr_handle_ptr), MTIF_MTR_SIGNATURE)
#define MTIF_MTX_IS_PTR(mtx_handle_ptr)				\
	MTIF_ANY_IS_PTR((mtx_handle_ptr), MTIF_MTX_SIGNATURE)
#define MTIF_RWL_IS_PTR(rwl_handle_ptr)				\
	MTIF_ANY_IS_PTR((rwl_handle_ptr), MTIF_RWL_SIGNATURE)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_MTX_IS_STATIC_UNINIT(mtx_handle_ptr)	\
	MTIF_MAP_TRUTH((mtx_handle_ptr)->static_flag)
#define MTIF_MTR_IS_STATIC_UNINIT(mtr_handle_ptr)	\
	MTIF_MAP_TRUTH((mtr_handle_ptr)->static_flag)
#define MTIF_RWL_IS_STATIC_UNINIT(rwl_handle_ptr)	\
	MTIF_MAP_TRUTH((rwl_handle_ptr)->static_flag)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_MTX_IS_STATIC(mtx_handle_ptr)	\
	MTIF_MAP_TRUTH((mtx_handle_ptr)->init_flags & MTIF_MTX_FLAG_STATIC)
#define MTIF_MTR_IS_STATIC(mtr_handle_ptr)	\
	MTIF_MAP_TRUTH((mtr_handle_ptr)->init_flags & MTIF_MTR_FLAG_STATIC)
#define MTIF_RWL_IS_STATIC(rwl_handle_ptr)	\
	MTIF_MAP_TRUTH((rwl_handle_ptr)->init_flags & MTIF_RWL_FLAG_STATIC)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_MTX_OWNER_IS_SELF(mtx_handle_ptr)							\
	((((mtx_handle_ptr)->process_id == MTIF_THR_SelfProcess()) &&	\
	 ((mtx_handle_ptr)->thread_id == MTIF_THR_Self())) ? MTIF_TRUE : MTIF_FALSE)
#define MTIF_MTR_OWNER_IS_SELF(mtr_handle_ptr)							\
	((((mtr_handle_ptr)->process_id == MTIF_THR_SelfProcess()) &&	\
	 ((mtr_handle_ptr)->thread_id == MTIF_THR_Self())) ? MTIF_TRUE : MTIF_FALSE)
#define MTIF_RWL_OWNER_IS_SELF(rwl_handle_ptr)							\
	((((rwl_handle_ptr)->process_id == MTIF_THR_SelfProcess()) &&	\
	 ((rwl_handle_ptr)->thread_id == MTIF_THR_Self())) ? MTIF_TRUE : MTIF_FALSE)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
# define MTIF_MTX_CAN_DESTROY_STATIC	MTIF_TRUE
# define MTIF_MTR_CAN_DESTROY_STATIC	MTIF_TRUE
# define MTIF_RWL_CAN_DESTROY_STATIC	MTIF_TRUE
#elif MTIF_THR_UI_THREADS
# define MTIF_MTX_CAN_DESTROY_STATIC	MTIF_FALSE
# define MTIF_MTR_CAN_DESTROY_STATIC	MTIF_FALSE
# define MTIF_RWL_CAN_DESTROY_STATIC	MTIF_FALSE
#elif MTIF_THR_POSIX_THREADS
# define MTIF_MTX_CAN_DESTROY_STATIC	MTIF_FALSE
# define MTIF_MTR_CAN_DESTROY_STATIC	MTIF_FALSE
# define MTIF_RWL_CAN_DESTROY_STATIC	MTIF_FALSE
#else
# define MTIF_MTX_CAN_DESTROY_STATIC	MTIF_TRUE
# define MTIF_MTR_CAN_DESTROY_STATIC	MTIF_TRUE
# define MTIF_RWL_CAN_DESTROY_STATIC	MTIF_TRUE
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_MTX_CAN_DESTROY(mtx_handle_ptr)         	\
	MTIF_MAP_TRUTH(MTIF_MTX_IS_PTR(mtx_handle_ptr) &&	\
	((!MTIF_MTX_IS_STATIC(mtx_handle_ptr)) || MTIF_MTX_CAN_DESTROY_STATIC))
#define MTIF_MTR_CAN_DESTROY(mtr_handle_ptr)         	\
	MTIF_MAP_TRUTH(MTIF_MTR_IS_PTR(mtr_handle_ptr) &&	\
	((!MTIF_MTR_IS_STATIC(mtr_handle_ptr)) || MTIF_MTR_CAN_DESTROY_STATIC))
#define MTIF_RWL_CAN_DESTROY(rwl_handle_ptr)         	\
	MTIF_MAP_TRUTH(MTIF_RWL_IS_PTR(rwl_handle_ptr) &&	\
	((!MTIF_RWL_IS_STATIC(rwl_handle_ptr)) || MTIF_RWL_CAN_DESTROY_STATIC))
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define MTIF_THR_ID_TEXT_LENGTH			(31 + STR_VAL2STR_MAX_LEN)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Internal functions provided in library 'mtif.{a|lib}' . . .					*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Internal basic unlock function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int MTIF_MTX_UnlockBasic,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_MTR_UnlockBasic,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_RWL_UnlockBasic,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Internal supporting function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int   MTIF_SUPP_Check,
	(const void *handle_ptr, const char *handle_name, unsigned int handle_size,
	unsigned int signature_offset, MTIF_SIGNATURE signature, char *error_text));
COMPAT_FN_DECL(char *MTIF_THR_GetThreadText,
	(const MTIF_THR_HANDLE *thr_handle_ptr, char *out_text));
COMPAT_FN_DECL(char *MTIF_SUPP_AppendSpecErrorString,
	(int errno_code, char *error_text));
COMPAT_FN_DECL(char *MTIF_SUPP_AppendLastErrorString, (char *error_text));
COMPAT_FN_DECL(char *MTIF_SUPP_GetSpecErrorString,
	(int errno_code, char *error_text));
COMPAT_FN_DECL(char *MTIF_SUPP_GetLastErrorString, (char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Internal function prototypes for Win32 platforms . . .
		*****************************************************************	*/
#ifdef _Windows
COMPAT_FN_DECL(char *MTIF_SUPP_AppendSpecErrorString_Win32,
	(int win32_code, char *error_text));
COMPAT_FN_DECL(char *MTIF_SUPP_AppendLastErrorString_Win32, (char *error_text));
COMPAT_FN_DECL(char *MTIF_SUPP_GetSpecErrorString_Win32,
	(int win32_code, char *error_text));
COMPAT_FN_DECL(char *MTIF_SUPP_GetLastErrorString_Win32, (char *error_text));
COMPAT_FN_DECL(int MTIF_SUPP_WIN32_CheckHandlePtr,
	(const HANDLE *handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_SUPP_WIN32_CheckHandlePtrAndValue,
	(const HANDLE *handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_SUPP_WIN32_CheckHandleValue,
	(HANDLE in_handle, char *error_text));
COMPAT_FN_DECL(int MTIF_SUPP_WIN32_CloseHandle,
	(HANDLE *handle_ptr, char *error_text));
COMPAT_FN_DECL(int MTIF_SUPP_WIN32_CreateMutex,
	(int init_owner_flag, const char *mtr_name, HANDLE *handle_ptr,
	char *error_text));
COMPAT_FN_DECL(int MTIF_SUPP_WIN32_ReleaseMutex,
	(HANDLE in_handle, char *error_text));
COMPAT_FN_DECL(int MTIF_SUPP_WIN32_WaitForSingleObject,
	(HANDLE in_handle, DWORD time_out, char *error_text));
#endif /* #ifdef _Windows */
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__MTIFI_H__h */

