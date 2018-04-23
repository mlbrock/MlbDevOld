/* *********************************************************************** */
/* *********************************************************************** */
/*	TFREAD Text File Reading Functions Library Internal Include File			*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the TFREAD library.

	Revision History	:	1991-04-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

#ifndef h__TFREADI_H__h

#define h__TFREADI_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "tfread.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	TFREAD Truth Code Mappings

   NAME        :	TFREAD Truth Code Mappings

	SYNOPSIS		:	truth_code = TFREAD_MAP_TRUTH_STR(str_code);

						truth_code = TFREAD_MAP_TRUTH_GEN(gen_code);

						truth_code = TFREAD_MAP_TRUTH_MFILE(mfile_code);

	DESCRIPTION	:	The TFREAD truth code mapping macros map truth codes from
						various low-level libraries to TFREAD truth codes.

						(.) ''TFREAD_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a TFREAD truth code.

						(.) ''TFREAD_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a TFREAD truth code.

						(.) ''TFREAD_MAP_TRUTH_MFILE'' maps a truth code
						from a MFILE truth code to a TFREAD truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent TFREAD truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						TFREAD return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:	TFREAD_MAP_TRUTH_STR
						TFREAD_MAP_TRUTH_GEN
						TFREAD_MAP_TRUTH_MFILE
						Truth Code Mappings:TFREAD_MAP_TRUTH_STR
						Truth Code Mappings:TFREAD_MAP_TRUTH_GEN
						Truth Code Mappings:TFREAD_MAP_TRUTH_MFILE
						Macros and Manifest Constants:TFREAD_MAP_TRUTH_STR
						Macros and Manifest Constants:TFREAD_MAP_TRUTH_GEN
						Macros and Manifest Constants:TFREAD_MAP_TRUTH_MFILE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	TFREAD_MAP_TRUTH_STR
						TFREAD_MAP_TRUTH_GEN
						TFREAD_MAP_TRUTH_MFILE
						TFREAD Truth Code Mappings
						TFREAD Truth Code Mapping
						TFREAD truth code mappings
						TFREAD truth code mapping

   PUBLISH NAME:	TFREAD_MAP_TRUTH_STR
						TFREAD_MAP_TRUTH_GEN
						TFREAD_MAP_TRUTH_MFILE

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define TFREAD_MAP_TRUTH_STR(str_code)						\
	(((str_code) == STRFUNCS_TRUE) ? TFREAD_TRUE : TFREAD_FALSE)
#define TFREAD_MAP_TRUTH_GEN(gen_code)						\
	(((gen_code) == GENFUNCS_TRUE) ? TFREAD_TRUE : TFREAD_FALSE)
#define TFREAD_MAP_TRUTH_MFILE(mfile_code)				\
	(((mfile_code) == MFILE_TRUE) ? TFREAD_TRUE : TFREAD_FALSE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	TFREAD Return Code Mappings

   NAME        :	TFREAD Return Code Mappings

	SYNOPSIS		:	return_code = TFREAD_MAP_ERROR_STR(str_code);

						return_code = TFREAD_MAP_ERROR_GEN(gen_code);

						return_code = TFREAD_MAP_ERROR_MFILE(spf_code);

	DESCRIPTION	:	The TFREAD return code mapping macros map return codes from
						various low-level libraries to TFREAD return codes.

						(.) ''TFREAD_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a TFREAD return code.

						(.) ''TFREAD_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a TFREAD return code.

						(.) ''TFREAD_MAP_ERROR_MFILE'' maps a return code
						from a MFILE return code to a TFREAD return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent TFREAD return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						TFREAD truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:	TFREAD_MAP_ERROR_STR
						TFREAD_MAP_ERROR_GEN
						TFREAD_MAP_ERROR_MFILE
						Return Code Mappings:TFREAD_MAP_ERROR_STR
						Return Code Mappings:TFREAD_MAP_ERROR_GEN
						Return Code Mappings:TFREAD_MAP_ERROR_MFILE
						Macros and Manifest Constants:TFREAD_MAP_ERROR_STR
						Macros and Manifest Constants:TFREAD_MAP_ERROR_GEN
						Macros and Manifest Constants:TFREAD_MAP_ERROR_MFILE
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	TFREAD_MAP_ERROR_STR
						TFREAD_MAP_ERROR_GEN
						TFREAD_MAP_ERROR_MFILE
						TFREAD Return Code Mappings
						TFREAD Return Code Mapping
						TFREAD return code mappings
						TFREAD return code mapping
						TFREAD Status Code Mappings
						TFREAD Status Code Mapping
						TFREAD status code mappings
						TFREAD status code mapping
						TFREAD Error Code Mappings
						TFREAD Error Code Mapping
						TFREAD error code mappings
						TFREAD error code mapping

   PUBLISH NAME:	TFREAD_MAP_ERROR_STR
						TFREAD_MAP_ERROR_GEN
						TFREAD_MAP_ERROR_MFILE

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define TFREAD_MAP_ERROR_STR(str_code)										 			\
	(((str_code) == STRFUNCS_SUCCESS)          ? TFREAD_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? TFREAD_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? TFREAD_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? TFREAD_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? TFREAD_SYSTEM_FAILURE   :	\
	 TFREAD_FAILURE)
#define TFREAD_MAP_ERROR_GEN(gen_code)													\
	(((gen_code) == GENFUNCS_SUCCESS)          ? TFREAD_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? TFREAD_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? TFREAD_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? TFREAD_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? TFREAD_SYSTEM_FAILURE   :	\
	 TFREAD_FAILURE)
#define TFREAD_MAP_ERROR_MFILE(mfile_code)											\
	(((mfile_code) == MFILE_SUCCESS)           ? TFREAD_SUCCESS          :	\
	 ((mfile_code) == MFILE_FAILURE)           ? TFREAD_FAILURE          :	\
	 ((mfile_code) == MFILE_BAD_ARGS_FAILURE)  ? TFREAD_BAD_ARGS_FAILURE :	\
	 ((mfile_code) == MFILE_MEMORY_FAILURE)    ? TFREAD_MEMORY_FAILURE   :	\
	 ((mfile_code) == MFILE_SYSTEM_FAILURE)    ? TFREAD_SYSTEM_FAILURE   :	\
	 TFREAD_FAILURE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	TFREAD Library Version Number

   NAME        :	TFREAD Library Version Number

   DESCRIPTION :	The TFREAD library version number manifest constants
						together define the current version number of the TFREAD
						library as a whole.

						(.) ''TFREAD_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''TFREAD_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''TFREAD_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''TFREAD_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:	TFREAD_VERSION_MAJOR
						TFREAD_VERSION_MINOR
						TFREAD_VERSION_RELEASE
						TFREAD_VERSION_BUILD
						TFREAD Version Numbers:Library Version Number
						Library Version Number:TFREAD_VERSION_MAJOR
						Library Version Number:TFREAD_VERSION_MINOR
						Library Version Number:TFREAD_VERSION_RELEASE
						Library Version Number:TFREAD_VERSION_BUILD
						Macros and Manifest Constants:TFREAD_VERSION_MAJOR
						Macros and Manifest Constants:TFREAD_VERSION_MINOR
						Macros and Manifest Constants:TFREAD_VERSION_RELEASE
						Macros and Manifest Constants:TFREAD_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	TFREAD_VERSION_MAJOR
						TFREAD_VERSION_MINOR
						TFREAD_VERSION_RELEASE
						TFREAD_VERSION_BUILD
						TFREAD Library Version Number
						TFREAD library version number
						TFREAD Library Version
						TFREAD library version
						TFREAD Version Number
						TFREAD version number
						TFREAD Version
						TFREAD version

   PUBLISH NAME:	TFREAD_VERSION_MAJOR
						TFREAD_VERSION_MINOR
						TFREAD_VERSION_RELEASE
						TFREAD_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						TFREAD Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define TFREAD_VERSION_MAJOR				((unsigned char) 2)
#define TFREAD_VERSION_MINOR				((unsigned char) 0)
#define TFREAD_VERSION_RELEASE			((unsigned char) 0)
#define TFREAD_VERSION_BUILD				((unsigned char) 'A')
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define TFREAD_LINE_ALLOC_GRAN			1000
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for internal functions defined within 'tfread.a'.	*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__TFREADI_H__h */

