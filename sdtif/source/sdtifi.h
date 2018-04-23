/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	System Date/Time Interface Facility Library Internal Include File			*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the SDTIF library.

	Revision History	:	1985-10-23 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1985 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__SDTIFI_H__h

# define h__SDTIFI_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "sdtif.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	SDTIF Truth Code Mappings

   NAME        :	SDTIF Truth Code Mappings

	SYNOPSIS		:	truth_code = SDTIF_MAP_TRUTH_STR(str_code);

						truth_code = SDTIF_MAP_TRUTH_GEN(gen_code);

	DESCRIPTION	:	The SDTIF truth code mapping macros map truth codes from
						various low-level libraries to SDTIF truth codes.

						(.) ''SDTIF_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a SDTIF truth code.

						(.) ''SDTIF_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a SDTIF truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent SDTIF truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						SDTIF return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1985 - 2018 Michael L. Brock

   OUTPUT INDEX:	SDTIF_MAP_TRUTH_STR
						SDTIF_MAP_TRUTH_GEN
						Truth Code Mappings:SDTIF_MAP_TRUTH_STR
						Truth Code Mappings:SDTIF_MAP_TRUTH_GEN
						Macros and Manifest Constants:SDTIF_MAP_TRUTH_STR
						Macros and Manifest Constants:SDTIF_MAP_TRUTH_GEN
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	SDTIF_MAP_TRUTH_STR
						SDTIF_MAP_TRUTH_GEN
						SDTIF Truth Code Mappings
						SDTIF Truth Code Mapping
						SDTIF truth code mappings
						SDTIF truth code mapping

   PUBLISH NAME:	SDTIF_MAP_TRUTH_STR
						SDTIF_MAP_TRUTH_GEN

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define SDTIF_MAP_TRUTH(code)						\
	((code) ? SDTIF_TRUE : SDTIF_FALSE)
#define SDTIF_MAP_TRUTH_STR(str_code)			\
	(((str_code) == STRFUNCS_TRUE) ? SDTIF_TRUE : SDTIF_FALSE)
#define SDTIF_MAP_TRUTH_GEN(gen_code)			\
	(((gen_code) == GENFUNCS_TRUE) ? SDTIF_TRUE : SDTIF_FALSE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	SDTIF Return Code Mappings

   NAME        :	SDTIF Return Code Mappings

	SYNOPSIS		:	return_code = SDTIF_MAP_ERROR_STR(str_code);

						return_code = SDTIF_MAP_ERROR_GEN(gen_code);

	DESCRIPTION	:	The SDTIF return code mapping macros map return codes from
						various low-level libraries to SDTIF return codes.

						(.) ''SDTIF_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a SDTIF return code.

						(.) ''SDTIF_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a SDTIF return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent SDTIF return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						SDTIF truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1985 - 2018 Michael L. Brock

   OUTPUT INDEX:	SDTIF_MAP_ERROR_STR
						SDTIF_MAP_ERROR_GEN
						Return Code Mappings:SDTIF_MAP_ERROR_STR
						Return Code Mappings:SDTIF_MAP_ERROR_GEN
						Macros and Manifest Constants:SDTIF_MAP_ERROR_STR
						Macros and Manifest Constants:SDTIF_MAP_ERROR_GEN
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	SDTIF_MAP_ERROR_STR
						SDTIF_MAP_ERROR_GEN
						SDTIF Return Code Mappings
						SDTIF Return Code Mapping
						SDTIF return code mappings
						SDTIF return code mapping
						SDTIF Status Code Mappings
						SDTIF Status Code Mapping
						SDTIF status code mappings
						SDTIF status code mapping
						SDTIF Error Code Mappings
						SDTIF Error Code Mapping
						SDTIF error code mappings
						SDTIF error code mapping

   PUBLISH NAME:	SDTIF_MAP_ERROR_STR
						SDTIF_MAP_ERROR_GEN

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define SDTIF_MAP_ERROR_STR(str_code)										 		 \
	(((str_code) == STRFUNCS_SUCCESS)          ? SDTIF_SUCCESS          : \
	 ((str_code) == STRFUNCS_FAILURE)          ? SDTIF_FAILURE          : \
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? SDTIF_BAD_ARGS_FAILURE : \
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? SDTIF_MEMORY_FAILURE   : \
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? SDTIF_SYSTEM_FAILURE   : \
	 SDTIF_FAILURE)
#define SDTIF_MAP_ERROR_GEN(gen_code)										 		 \
	(((gen_code) == GENFUNCS_SUCCESS)          ? SDTIF_SUCCESS          : \
	 ((gen_code) == GENFUNCS_FAILURE)          ? SDTIF_FAILURE          : \
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? SDTIF_BAD_ARGS_FAILURE : \
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? SDTIF_MEMORY_FAILURE   : \
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? SDTIF_SYSTEM_FAILURE   : \
	 SDTIF_FAILURE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	SDTIF Library Version Number

	NAME        :	SDTIF Library Version Number

	DESCRIPTION :	The SDTIF library version number manifest constants
						together define the current version number of the SDTIF
						library as a whole.

						(.) ''SDTIF_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''SDTIF_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''SDTIF_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''SDTIF_VERSION_BUILD'' represents the build
						level component of the library version number.

	SEE ALSO    :	STR_VERSION

	EXAMPLES    :	

	AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1985 - 2018 Michael L. Brock

	OUTPUT INDEX:	SDTIF_VERSION_MAJOR
						SDTIF_VERSION_MINOR
						SDTIF_VERSION_RELEASE
						SDTIF_VERSION_BUILD
						SDTIF Version Numbers:Library Version Number
						Library Version Number:SDTIF_VERSION_MAJOR
						Library Version Number:SDTIF_VERSION_MINOR
						Library Version Number:SDTIF_VERSION_RELEASE
						Library Version Number:SDTIF_VERSION_BUILD
						Macros and Manifest Constants:SDTIF_VERSION_MAJOR
						Macros and Manifest Constants:SDTIF_VERSION_MINOR
						Macros and Manifest Constants:SDTIF_VERSION_RELEASE
						Macros and Manifest Constants:SDTIF_VERSION_BUILD
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:	SDTIF_VERSION_MAJOR
						SDTIF_VERSION_MINOR
						SDTIF_VERSION_RELEASE
						SDTIF_VERSION_BUILD
						SDTIF Library Version Number
						SDTIF library version number
						SDTIF Library Version
						SDTIF library version
						SDTIF Version Number
						SDTIF version number
						SDTIF Version
						SDTIF version

	PUBLISH NAME:	SDTIF_VERSION_MAJOR
						SDTIF_VERSION_MINOR
						SDTIF_VERSION_RELEASE
						SDTIF_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						SDTIF Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define SDTIF_VERSION_MAJOR				((unsigned char) 1)
#define SDTIF_VERSION_MINOR				((unsigned char) 0)
#define SDTIF_VERSION_RELEASE				((unsigned char) 7)
#define SDTIF_VERSION_BUILD				((unsigned char) 'A')
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Function prototypes for internal functions defined within 'sdtif.a'.		*/
/*	***********************************************************************	*/

COMPAT_FN_DECL(unsigned int SDTIF_TEST_DoMacros,
	(time_t *time_t_ptr, struct tm *tm_ptr, struct timeval *timeval_ptr,
	struct timespec *timespec_ptr, unsigned long *ulong_ptr));

/*	***********************************************************************	*/

#endif /* #ifndef h__SDTIFI_H__h */

