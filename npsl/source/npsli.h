/* *********************************************************************** */
/* *********************************************************************** */
/*	Network Programming Support Library (NPSL) Internal Include File			*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Internal Network Programming
								Support Library (NPSL).

	Revision History	:	1993-04-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__NPSLI_H__h

#define h__NPSLI_H__h						1

/* *********************************************************************** */
/* *********************************************************************** */
/*		Include necessary header files . . .											*/
/* *********************************************************************** */

#include "npsl.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	NPSL Truth Code Mappings

   NAME        :	NPSL Truth Code Mappings

	SYNOPSIS		:	truth_code = NPSL_MAP_TRUTH_STR(str_code);

						truth_code = NPSL_MAP_TRUTH_GEN(gen_code);

	DESCRIPTION	:	The NPSL truth code mapping macros map truth codes from
						various low-level libraries to NPSL truth codes.

						(.) ''NPSL_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a NPSL truth code.

						(.) ''NPSL_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a NPSL truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent NPSL truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						NPSL return code mapping macros.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	NPSL_MAP_TRUTH_STR
						NPSL_MAP_TRUTH_GEN
						Truth Code Mappings:NPSL_MAP_TRUTH_STR
						Truth Code Mappings:NPSL_MAP_TRUTH_GEN
						Macros and Manifest Constants:NPSL_MAP_TRUTH_STR
						Macros and Manifest Constants:NPSL_MAP_TRUTH_GEN
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	NPSL_MAP_TRUTH_STR
						NPSL_MAP_TRUTH_GEN
						NPSL Truth Code Mappings
						NPSL Truth Code Mapping
						NPSL truth code mappings
						NPSL truth code mapping

   PUBLISH NAME:	NPSL_MAP_TRUTH_STR
						NPSL_MAP_TRUTH_GEN

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define NPSL_MAP_TRUTH_STR(str_code)					\
	(((str_code) == STRFUNCS_TRUE)  ? NPSL_TRUE : NPSL_FALSE)
#define NPSL_MAP_TRUTH_GEN(gen_code)					\
	(((gen_code) == GENFUNCS_TRUE)  ? NPSL_TRUE : NPSL_FALSE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	NPSL Return Code Mappings

   NAME        :	NPSL Return Code Mappings

	SYNOPSIS		:	return_code = NPSL_MAP_ERROR_STR(str_code);

						return_code = NPSL_MAP_ERROR_GEN(gen_code);

	DESCRIPTION	:	The NPSL return code mapping macros map return codes from
						various low-level libraries to NPSL return codes.

						(.) ''NPSL_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a NPSL return code.

						(.) ''NPSL_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a NPSL return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent NPSL return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						NPSL truth code mapping macros.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	NPSL_MAP_ERROR_STR
						NPSL_MAP_ERROR_GEN
						Return Code Mappings:NPSL_MAP_ERROR_STR
						Return Code Mappings:NPSL_MAP_ERROR_GEN
						Macros and Manifest Constants:NPSL_MAP_ERROR_STR
						Macros and Manifest Constants:NPSL_MAP_ERROR_GEN
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	NPSL_MAP_ERROR_STR
						NPSL_MAP_ERROR_GEN
						NPSL Return Code Mappings
						NPSL Return Code Mapping
						NPSL return code mappings
						NPSL return code mapping
						NPSL Status Code Mappings
						NPSL Status Code Mapping
						NPSL status code mappings
						NPSL status code mapping
						NPSL Error Code Mappings
						NPSL Error Code Mapping
						NPSL error code mappings
						NPSL error code mapping

   PUBLISH NAME:	NPSL_MAP_ERROR_STR
						NPSL_MAP_ERROR_GEN

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define NPSL_MAP_ERROR_STR(str_code)										 			\
	(((str_code) == STRFUNCS_SUCCESS)          ? NPSL_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? NPSL_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? NPSL_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? NPSL_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? NPSL_SYSTEM_FAILURE   :	\
	 NPSL_FAILURE)
#define NPSL_MAP_ERROR_GEN(gen_code)													\
	(((gen_code) == GENFUNCS_SUCCESS)          ? NPSL_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? NPSL_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? NPSL_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? NPSL_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? NPSL_SYSTEM_FAILURE   :	\
	 NPSL_FAILURE)
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#ifdef _Windows
typedef int NPSL_SEND_RECV_LEN_T;
#elif defined(__linux__)
typedef ssize_t NPSL_SEND_RECV_LEN_T;
#else
typedef size_t NPSL_SEND_RECV_LEN_T;
#endif /* #ifdef _Windows */
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* Function prototypes for internal functions defined within 'siidr.a'.		*/
/* *********************************************************************** */

	/*	*****************************************************************
		*****************************************************************
		Error description function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(const GEN_ERROR_SPEC *NPSL_GetErrorPtr,
	(int errno_code));
COMPAT_FN_DECL(const GEN_ERROR_SPEC *NPSL_GetLastErrorPtr,
	(void));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Miscellaneous function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int NPSL_CheckHostEntParams,
	(const NPSL_HOSTENT *host_ent_ptr, const void *host_ent_buffer_ptr,
	unsigned int host_ent_buffer_length, char *error_text));
COMPAT_FN_DECL(int NPSL_CheckProtoEntParams,
	(const NPSL_PROTOENT *proto_ent_ptr, const void *proto_ent_buffer_ptr,
	unsigned int proto_ent_buffer_length, char *error_text));
COMPAT_FN_DECL(int NPSL_CheckServEntParams,
	(const NPSL_SERVENT *serv_ent_ptr, const void *serv_ent_buffer_ptr,
	unsigned int serv_ent_buffer_length, char *error_text));
	/*	*****************************************************************	*/

/* *********************************************************************** */

#endif /* #ifndef h__NPSLI_H__h */

