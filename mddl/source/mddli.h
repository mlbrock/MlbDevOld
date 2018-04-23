/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Member Data Definition Library (MDDL) Internal Include File					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the MDDL library.

	Revision History	:	1993-12-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__MDDLI_H__h

# define h__MDDLI_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <mddl.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MDDL Truth Code Mappings

   NAME        :	MDDL Truth Code Mappings

	SYNOPSIS		:	truth_code = MDDL_MAP_TRUTH_STR(str_code);

						truth_code = MDDL_MAP_TRUTH_GEN(gen_code);

						truth_code = MDDL_MAP_TRUTH_DTA(dat_code);

	DESCRIPTION	:	The MDDL truth code mapping macros map truth codes from
						various low-level libraries to MDDL truth codes.

						(.) ''MDDL_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a MDDL truth code.

						(.) ''MDDL_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a MDDL truth code.

						(.) ''MDDL_MAP_TRUTH_DTA'' maps a truth code
						from a DTAFUNCS truth code to a MDDL truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent MDDL truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						MDDL return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	MDDL_MAP_TRUTH_STR
						MDDL_MAP_TRUTH_GEN
						MDDL_MAP_TRUTH_DTA
						Truth Code Mappings:MDDL_MAP_TRUTH_STR
						Truth Code Mappings:MDDL_MAP_TRUTH_GEN
						Truth Code Mappings:MDDL_MAP_TRUTH_DTA
						Macros and Manifest Constants:MDDL_MAP_TRUTH_STR
						Macros and Manifest Constants:MDDL_MAP_TRUTH_GEN
						Macros and Manifest Constants:MDDL_MAP_TRUTH_DTA
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MDDL_MAP_TRUTH_STR
						MDDL_MAP_TRUTH_GEN
						MDDL_MAP_TRUTH_DTA
						MDDL_MAP_TRUTH_STR_TO_MDDL
						MDDL_MAP_TRUTH_GEN_TO_MDDL
						MDDL_MAP_TRUTH_DTA_TO_MDDL
						MDDL Truth Code Mappings
						MDDL Truth Code Mapping
						MDDL truth code mappings
						MDDL truth code mapping

   PUBLISH NAME:	MDDL_MAP_TRUTH_STR
						MDDL_MAP_TRUTH_GEN
						MDDL_MAP_TRUTH_DTA

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define MDDL_MAP_TRUTH_STR(str_code)				\
	(((str_code) == STRFUNCS_TRUE) ? MDDL_TRUE : MDDL_FALSE)
#define MDDL_MAP_TRUTH_GEN(gen_code)				\
	(((gen_code) == GENFUNCS_TRUE) ? MDDL_TRUE : MDDL_FALSE)
#define MDDL_MAP_TRUTH_DTA(dta_code)				\
	(((dta_code) == DTA_TRUE) ? MDDL_TRUE : MDDL_FALSE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define MDDL_MAP_TRUTH_STR_TO_MDDL(str_code)	\
	MDDL_MAP_TRUTH_STR(str_code)
#define MDDL_MAP_TRUTH_GEN_TO_MDDL(gen_code)	\
	MDDL_MAP_TRUTH_GEN(gen_code)
#define MDDL_MAP_TRUTH_DTA_TO_MDDL(gen_code)	\
	MDDL_MAP_TRUTH_DTA(dta_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MDDL Return Code Mappings

   NAME        :	MDDL Return Code Mappings

	SYNOPSIS		:	return_code = MDDL_MAP_ERROR_STR(str_code);

						return_code = MDDL_MAP_ERROR_GEN(gen_code);

						return_code = MDDL_MAP_ERROR_DTA(dat_code);

	DESCRIPTION	:	The MDDL return code mapping macros map return codes from
						various low-level libraries to MDDL return codes.

						(.) ''MDDL_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a MDDL return code.

						(.) ''MDDL_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a MDDL return code.

						(.) ''MDDL_MAP_ERROR_DTA'' maps a return code
						from a DTAFUNCS return code to a MDDL return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent MDDL return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						MDDL truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	MDDL_MAP_ERROR_STR
						MDDL_MAP_ERROR_GEN
						MDDL_MAP_ERROR_DTA
						Return Code Mappings:MDDL_MAP_ERROR_STR
						Return Code Mappings:MDDL_MAP_ERROR_GEN
						Return Code Mappings:MDDL_MAP_ERROR_DTA
						Macros and Manifest Constants:MDDL_MAP_ERROR_STR
						Macros and Manifest Constants:MDDL_MAP_ERROR_GEN
						Macros and Manifest Constants:MDDL_MAP_ERROR_DTA
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MDDL_MAP_ERROR_STR
						MDDL_MAP_ERROR_GEN
						MDDL_MAP_ERROR_DTA
						MDDL_MAP_ERROR_STR_TO_MDDL
						MDDL_MAP_ERROR_GEN_TO_MDDL
						MDDL_MAP_ERROR_DTA_TO_MDDL
						MDDL Return Code Mappings
						MDDL Return Code Mapping
						MDDL return code mappings
						MDDL return code mapping
						MDDL Status Code Mappings
						MDDL Status Code Mapping
						MDDL status code mappings
						MDDL status code mapping
						MDDL Error Code Mappings
						MDDL Error Code Mapping
						MDDL error code mappings
						MDDL error code mapping

   PUBLISH NAME:	MDDL_MAP_ERROR_STR
						MDDL_MAP_ERROR_GEN
						MDDL_MAP_ERROR_DTA

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define MDDL_MAP_ERROR_STR(str_code)								 				\
	(((str_code) == STRFUNCS_SUCCESS)          ? MDDL_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? MDDL_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? MDDL_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? MDDL_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? MDDL_SYSTEM_FAILURE   :	\
	 MDDL_FAILURE)
#define MDDL_MAP_ERROR_GEN(gen_code)								 				\
	(((gen_code) == GENFUNCS_SUCCESS)          ? MDDL_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? MDDL_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? MDDL_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? MDDL_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? MDDL_SYSTEM_FAILURE   :	\
	 MDDL_FAILURE)
#define MDDL_MAP_ERROR_DTA(dta_code)								 				\
	(((dta_code) == DTA_SUCCESS)               ? MDDL_SUCCESS          :	\
	 ((dta_code) == DTA_FAILURE)               ? MDDL_FAILURE          :	\
	 ((dta_code) == DTA_BAD_ARGS_FAILURE)      ? MDDL_BAD_ARGS_FAILURE :	\
	 ((dta_code) == DTA_MEMORY_FAILURE)        ? MDDL_MEMORY_FAILURE   :	\
	 ((dta_code) == DTA_SYSTEM_FAILURE)        ? MDDL_SYSTEM_FAILURE   :	\
	 MDDL_FAILURE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define MDDL_MAP_ERROR_STR_TO_MDDL(str_code)									 	\
	MDDL_MAP_ERROR_STR(str_code)
#define MDDL_MAP_ERROR_GEN_TO_MDDL(gen_code)									 	\
	MDDL_MAP_ERROR_GEN(gen_code)
#define MDDL_MAP_ERROR_DTA_TO_MDDL(dta_code)									 	\
	MDDL_MAP_ERROR_DTA(dta_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MDDL Library Version Number

   NAME        :	MDDL Library Version Number

   DESCRIPTION :	The MDDL library version number manifest constants
						together define the current version number of the MDDL
						library as a whole.

						(.) ''MDDL_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''MDDL_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''MDDL_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''MDDL_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	MDDL_VERSION_MAJOR
						MDDL_VERSION_MINOR
						MDDL_VERSION_RELEASE
						MDDL_VERSION_BUILD
						MDDL Version Numbers:Library Version Number
						Library Version Number:MDDL_VERSION_MAJOR
						Library Version Number:MDDL_VERSION_MINOR
						Library Version Number:MDDL_VERSION_RELEASE
						Library Version Number:MDDL_VERSION_BUILD
						Macros and Manifest Constants:MDDL_VERSION_MAJOR
						Macros and Manifest Constants:MDDL_VERSION_MINOR
						Macros and Manifest Constants:MDDL_VERSION_RELEASE
						Macros and Manifest Constants:MDDL_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MDDL_VERSION_MAJOR
						MDDL_VERSION_MINOR
						MDDL_VERSION_RELEASE
						MDDL_VERSION_BUILD
						MDDL Library Version Number
						MDDL library version number
						MDDL Library Version
						MDDL library version
						MDDL Version Number
						MDDL version number
						MDDL Version
						MDDL version

   PUBLISH NAME:	MDDL_VERSION_MAJOR
						MDDL_VERSION_MINOR
						MDDL_VERSION_RELEASE
						MDDL_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						MDDL Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define MDDL_VERSION_MAJOR					((unsigned char) 3)
#define MDDL_VERSION_MINOR					((unsigned char) 0)
#define MDDL_VERSION_RELEASE				((unsigned char) 0)
#define MDDL_VERSION_BUILD					((unsigned char) 'A')
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Internal function prototypes for functions defined within 'mddl.a'.		*/
/*	***********************************************************************	*/

/* *********************************************************************** */

#endif /* #ifndef h__MDDLI_H__h */

