/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Type Alignment (DTA) Functions Library Internal Include File			*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Data Type Alignment
								(DTA) library.

	Revision History	:	1992-02-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DTAI_H__h

# define h__DTAI_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dta.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DTA Truth Code Mappings

   NAME        :	DTA Truth Code Mappings

	SYNOPSIS		:	truth_code = DTA_MAP_TRUTH_STR(str_code);

						truth_code = DTA_MAP_TRUTH_GEN(gen_code);

	DESCRIPTION	:	The DTA truth code mapping macros map truth codes from
						various low-level libraries to DTA truth codes.

						(.) ''DTA_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a DTA truth code.

						(.) ''DTA_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a DTA truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent DTA truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						DTA return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	DTA_MAP_TRUTH_STR
						DTA_MAP_TRUTH_GEN
						Truth Code Mappings:DTA_MAP_TRUTH_STR
						Truth Code Mappings:DTA_MAP_TRUTH_GEN
						Macros and Manifest Constants:DTA_MAP_TRUTH_STR
						Macros and Manifest Constants:DTA_MAP_TRUTH_GEN
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DTA_MAP_TRUTH_STR
						DTA_MAP_TRUTH_GEN
						DTA_MAP_TRUTH_STR_TO_DTA
						DTA_MAP_TRUTH_GEN_TO_DTA
						DTA Truth Code Mappings
						DTA Truth Code Mapping
						DTA truth code mappings
						DTA truth code mapping

   PUBLISH NAME:	DTA_MAP_TRUTH_STR
						DTA_MAP_TRUTH_GEN

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define DTA_MAP_TRUTH_STR(str_code)				\
	(((str_code) == STRFUNCS_TRUE) ? DTA_TRUE : DTA_FALSE)
#define DTA_MAP_TRUTH_GEN(gen_code)				\
	(((gen_code) == GENFUNCS_TRUE) ? DTA_TRUE : DTA_FALSE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define DTA_MAP_TRUTH_STR_TO_DTA(str_code)	\
	DTA_MAP_TRUTH_STR(str_code)
#define DTA_MAP_TRUTH_GEN_TO_DTA(gen_code)	\
	DTA_MAP_TRUTH_GEN(gen_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DTA Return Code Mappings

   NAME        :	DTA Return Code Mappings

	SYNOPSIS		:	return_code = DTA_MAP_ERROR_STR(str_code);

						return_code = DTA_MAP_ERROR_GEN(gen_code);

	DESCRIPTION	:	The DTA return code mapping macros map return codes from
						various low-level libraries to DTA return codes.

						(.) ''DTA_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a DTA return code.

						(.) ''DTA_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a DTA return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent DTA return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						DTA truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	DTA_MAP_ERROR_STR
						DTA_MAP_ERROR_GEN
						Return Code Mappings:DTA_MAP_ERROR_STR
						Return Code Mappings:DTA_MAP_ERROR_GEN
						Macros and Manifest Constants:DTA_MAP_ERROR_STR
						Macros and Manifest Constants:DTA_MAP_ERROR_GEN
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DTA_MAP_ERROR_STR
						DTA_MAP_ERROR_GEN
						DTA_MAP_ERROR_STR_TO_DTA
						DTA_MAP_ERROR_GEN_TO_DTA
						DTA Return Code Mappings
						DTA Return Code Mapping
						DTA return code mappings
						DTA return code mapping
						DTA Status Code Mappings
						DTA Status Code Mapping
						DTA status code mappings
						DTA status code mapping
						DTA Error Code Mappings
						DTA Error Code Mapping
						DTA error code mappings
						DTA error code mapping

   PUBLISH NAME:	DTA_MAP_ERROR_STR
						DTA_MAP_ERROR_GEN

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define DTA_MAP_ERROR_STR(str_code)									 				\
	(((str_code) == STRFUNCS_SUCCESS)          ? DTA_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? DTA_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? DTA_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? DTA_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? DTA_SYSTEM_FAILURE   :	\
	 DTA_FAILURE)
#define DTA_MAP_ERROR_GEN(gen_code)									 				\
	(((gen_code) == GENFUNCS_SUCCESS)          ? DTA_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? DTA_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? DTA_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? DTA_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? DTA_SYSTEM_FAILURE   :	\
	 DTA_FAILURE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define DTA_MAP_ERROR_STR_TO_DTA(str_code)									 	\
	DTA_MAP_ERROR_STR(str_code)
#define DTA_MAP_ERROR_GEN_TO_DTA(gen_code)									 	\
	DTA_MAP_ERROR_GEN(gen_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DTA Library Version Number

   NAME        :	DTA Library Version Number

   DESCRIPTION :	The DTA library version number manifest constants
						together define the current version number of the DTA
						library as a whole.

						(.) ''DTA_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''DTA_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''DTA_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''DTA_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:	DTA_VERSION_MAJOR
						DTA_VERSION_MINOR
						DTA_VERSION_RELEASE
						DTA_VERSION_BUILD
						DTA Version Numbers:Library Version Number
						Library Version Number:DTA_VERSION_MAJOR
						Library Version Number:DTA_VERSION_MINOR
						Library Version Number:DTA_VERSION_RELEASE
						Library Version Number:DTA_VERSION_BUILD
						Macros and Manifest Constants:DTA_VERSION_MAJOR
						Macros and Manifest Constants:DTA_VERSION_MINOR
						Macros and Manifest Constants:DTA_VERSION_RELEASE
						Macros and Manifest Constants:DTA_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DTA_VERSION_MAJOR
						DTA_VERSION_MINOR
						DTA_VERSION_RELEASE
						DTA_VERSION_BUILD
						DTA Library Version Number
						DTA library version number
						DTA Library Version
						DTA library version
						DTA Version Number
						DTA version number
						DTA Version
						DTA version

   PUBLISH NAME:	DTA_VERSION_MAJOR
						DTA_VERSION_MINOR
						DTA_VERSION_RELEASE
						DTA_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						DTA Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define DTA_VERSION_MAJOR					((unsigned char) 3)
#define DTA_VERSION_MINOR					((unsigned char) 0)
#define DTA_VERSION_RELEASE				((unsigned char) 0)
#define DTA_VERSION_BUILD					((unsigned char) 'A')
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Function prototypes for internal functions defined within 'dta.a' . . .	*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DTAI_H__h */

