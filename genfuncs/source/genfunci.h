/* *********************************************************************** */
/* *********************************************************************** */
/*	GENFUNCS General Functions Library Internal Include File						*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the GENFUNCS library.

	Revision History	:	1985-10-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1985 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__GENFUNCI_H__h

#define h__GENFUNCI_H__h					1

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Necessary include files . . .														*/
/* *********************************************************************** */

#include "genfuncs.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	GENFUNCS Truth Code Mappings

   NAME        :	GENFUNCS Truth Code Mappings

	SYNOPSIS		:	truth_code = GEN_MAP_TRUTH_STR(str_code);

						truth_code = GEN_MAP_TRUTH_TFREAD(gen_code);

	DESCRIPTION	:	The GENFUNCS truth code mapping macros map truth codes from
						various low-level libraries to GENFUNCS truth codes.

						(.) ''GEN_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a GENFUNCS truth code.

						(.) ''GEN_MAP_TRUTH_TFREAD'' maps a truth code
						from a TFREAD truth code to a GENFUNCS truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent GENFUNCS truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						GENFUNCS return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1985 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_MAP_TRUTH_STR
						GEN_MAP_TRUTH_TFREAD
						Truth Code Mappings:GEN_MAP_TRUTH_STR
						Truth Code Mappings:GEN_MAP_TRUTH_TFREAD
						Macros and Manifest Constants:GEN_MAP_TRUTH_STR
						Macros and Manifest Constants:GEN_MAP_TRUTH_TFREAD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	GEN_MAP_TRUTH_STR
						GEN_MAP_TRUTH_TFREAD
						GENFUNCS Truth Code Mappings
						GENFUNCS Truth Code Mapping
						GENFUNCS truth code mappings
						GENFUNCS truth code mapping

   PUBLISH NAME:	GEN_MAP_TRUTH_STR
						GEN_MAP_TRUTH_TFREAD

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define GEN_MAP_TRUTH(code)					\
	((code) ? GENFUNCS_TRUE : GENFUNCS_FALSE)
#define GEN_MAP_TRUTH_STR(str_code)			\
	(((str_code) == STRFUNCS_TRUE) ? GENFUNCS_TRUE : GENFUNCS_FALSE)
#define GEN_MAP_TRUTH_TFREAD(tfread_code)	\
	(((tfread_code) == TFREAD_TRUE) ? GENFUNCS_TRUE : GENFUNCS_FALSE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	GENFUNCS Return Code Mappings

   NAME        :	GENFUNCS Return Code Mappings

	SYNOPSIS		:	return_code = GEN_MAP_ERROR_STR(str_code);

						return_code = GEN_MAP_ERROR_TFREAD(gen_code);

	DESCRIPTION	:	The GENFUNCS return code mapping macros map return codes from
						various low-level libraries to GENFUNCS return codes.

						(.) ''GEN_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a GENFUNCS return code.

						(.) ''GEN_MAP_ERROR_TFREAD'' maps a return code
						from a TFREAD return code to a GENFUNCS return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent GENFUNCS return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						GENFUNCS truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1985 - 2015 Michael L. Brock

   OUTPUT INDEX:	GEN_MAP_ERROR_STR
						GEN_MAP_ERROR_TFREAD
						Return Code Mappings:GEN_MAP_ERROR_STR
						Return Code Mappings:GEN_MAP_ERROR_TFREAD
						Macros and Manifest Constants:GEN_MAP_ERROR_STR
						Macros and Manifest Constants:GEN_MAP_ERROR_TFREAD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	GEN_MAP_ERROR_STR
						GEN_MAP_ERROR_TFREAD
						GENFUNCS Return Code Mappings
						GENFUNCS Return Code Mapping
						GENFUNCS return code mappings
						GENFUNCS return code mapping
						GENFUNCS Status Code Mappings
						GENFUNCS Status Code Mapping
						GENFUNCS status code mappings
						GENFUNCS status code mapping
						GENFUNCS Error Code Mappings
						GENFUNCS Error Code Mapping
						GENFUNCS error code mappings
						GENFUNCS error code mapping

   PUBLISH NAME:	GEN_MAP_ERROR_STR
						GEN_MAP_ERROR_TFREAD

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define GEN_MAP_ERROR_STR(str_code)															\
	(((str_code) == STRFUNCS_SUCCESS)           ? GENFUNCS_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)           ? GENFUNCS_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE)  ? GENFUNCS_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)    ? GENFUNCS_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)    ? GENFUNCS_SYSTEM_FAILURE   :	\
	 GENFUNCS_FAILURE)
#define GEN_MAP_ERROR_TFREAD(tfread_code)													\
	(((tfread_code) == TFREAD_SUCCESS)          ? GENFUNCS_SUCCESS          :	\
	 ((tfread_code) == TFREAD_FAILURE)          ? GENFUNCS_FAILURE          :	\
	 ((tfread_code) == TFREAD_BAD_ARGS_FAILURE) ? GENFUNCS_BAD_ARGS_FAILURE :	\
	 ((tfread_code) == TFREAD_MEMORY_FAILURE)   ? GENFUNCS_MEMORY_FAILURE   :	\
	 ((tfread_code) == TFREAD_SYSTEM_FAILURE)   ? GENFUNCS_SYSTEM_FAILURE   :	\
	 GENFUNCS_FAILURE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	GENFUNCS Library Version Number

   NAME        :	GENFUNCS Library Version Number

   DESCRIPTION :	The GENFUNCS library version number manifest constants
						together define the current version number of the GENFUNCS
						library as a whole.

						(.) ''GENFUNCS_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''GENFUNCS_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''GENFUNCS_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''GENFUNCS_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1985 - 2015 Michael L. Brock

   OUTPUT INDEX:	GENFUNCS_VERSION_MAJOR
						GENFUNCS_VERSION_MINOR
						GENFUNCS_VERSION_RELEASE
						GENFUNCS_VERSION_BUILD
						GENFUNCS Version Numbers:Library Version Number
						Library Version Number:GENFUNCS_VERSION_MAJOR
						Library Version Number:GENFUNCS_VERSION_MINOR
						Library Version Number:GENFUNCS_VERSION_RELEASE
						Library Version Number:GENFUNCS_VERSION_BUILD
						Macros and Manifest Constants:GENFUNCS_VERSION_MAJOR
						Macros and Manifest Constants:GENFUNCS_VERSION_MINOR
						Macros and Manifest Constants:GENFUNCS_VERSION_RELEASE
						Macros and Manifest Constants:GENFUNCS_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	GENFUNCS_VERSION_MAJOR
						GENFUNCS_VERSION_MINOR
						GENFUNCS_VERSION_RELEASE
						GENFUNCS_VERSION_BUILD
						GENFUNCS Library Version Number
						GENFUNCS library version number
						GENFUNCS Library Version
						GENFUNCS library version
						GENFUNCS Version Number
						GENFUNCS version number
						GENFUNCS Version
						GENFUNCS version

   PUBLISH NAME:	GENFUNCS_VERSION_MAJOR
						GENFUNCS_VERSION_MINOR
						GENFUNCS_VERSION_RELEASE
						GENFUNCS_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						GENFUNCS Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define GENFUNCS_VERSION_MAJOR			((unsigned char) 3)
#define GENFUNCS_VERSION_MINOR			((unsigned char) 0)
#define GENFUNCS_VERSION_RELEASE			((unsigned char) 0)
#define GENFUNCS_VERSION_BUILD			((unsigned char) 'A')
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/*		Declares global variables which are defined in 'genalign.c'.			*/
/* *********************************************************************** */
COMPAT_EXTERN_DATA_DECL const unsigned int   GEN_ALIGN_TypeCount;
COMPAT_EXTERN_DATA_DECL const GEN_ALIGN_SPEC GEN_ALIGN_TypeList[];
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* Function prototypes for internal functions within 'genfuncs.a' . . .		*/
/* *********************************************************************** */

/* *********************************************************************** */

#endif /* #ifndef h__GENFUNCI_H__h */

