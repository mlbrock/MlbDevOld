/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Internal Include File						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Keyword Matching
								Library.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__KMLFUNCI_H__h

#define h__KMLFUNCI_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "kmlfuncs.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	KMLFUNCS Truth Code Mappings

	NAME        :	KMLFUNCS Truth Code Mappings

	SYNOPSIS		:	truth_code = KML_MAP_TRUTH_STR(strfuncs_code);

						truth_code = KML_MAP_TRUTH_GEN(genfuncs_code);

						truth_code = KML_MAP_TRUTH_SPF(spf_code);

						truth_code = KML_MAP_TRUTH_TFREAD(tfread_code);

	DESCRIPTION	:	The KMLFUNCS truth code mapping macros map truth codes from
						various low-level libraries to KMLFUNCS truth codes.

						(.) ''KML_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a KMLFUNCS truth code.

						(.) ''KML_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a KMLFUNCS truth code.

						(.) ''KML_MAP_TRUTH_SPF'' maps a truth code
						from a SPFFUNCS truth code to a KMLFUNCS truth code.

						(.) ''KML_MAP_TRUTH_TFREAD'' maps a truth code
						from a TFREAD truth code to a KMLFUNCS truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent KMLFUNCS truth
						code.

	NOTES       :	To map return codes from the libraries, use the related
						KMLFUNCS return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_MAP_TRUTH_STR
						KML_MAP_TRUTH_GEN
						KML_MAP_TRUTH_SPF
						KML_MAP_TRUTH_TFREAD
						Truth Code Mappings:KML_MAP_TRUTH_STR
						Truth Code Mappings:KML_MAP_TRUTH_GEN
						Truth Code Mappings:KML_MAP_TRUTH_SPF
						Truth Code Mappings:KML_MAP_TRUTH_TFREAD
						Macros and Manifest Constants:KML_MAP_TRUTH_STR
						Macros and Manifest Constants:KML_MAP_TRUTH_GEN
						Macros and Manifest Constants:KML_MAP_TRUTH_SPF
						Macros and Manifest Constants:KML_MAP_TRUTH_TFREAD
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:	KML_MAP_TRUTH_STR
						KML_MAP_TRUTH_GEN
						KML_MAP_TRUTH_SPF
						KML_MAP_TRUTH_TFREAD
						KMLFUNCS Truth Code Mappings
						KMLFUNCS Truth Code Mapping
						KMLFUNCS truth code mappings
						KMLFUNCS truth code mapping

   PUBLISH NAME:	KML_MAP_TRUTH_STR
						KML_MAP_TRUTH_GEN
						KML_MAP_TRUTH_SPF
						KML_MAP_TRUTH_TFREAD

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define KML_MAP_TRUTH_STR(str_code)			\
	(((str_code) == STRFUNCS_TRUE)  ? KML_TRUE : KML_FALSE)
#define KML_MAP_TRUTH_GEN(gen_code)			\
	(((gen_code) == GENFUNCS_TRUE)  ? KML_TRUE : KML_FALSE)
#define KML_MAP_TRUTH_SPF(spf_code)			\
	(((spf_code) == SPF_TRUE)       ? KML_TRUE : KML_FALSE)
#define KML_MAP_TRUTH_TFREAD(tfread_code)	\
	(((tfread_code) == TFREAD_TRUE) ? KML_TRUE : KML_FALSE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	KMLFUNCS Return Code Mappings

	NAME        :	KMLFUNCS Return Code Mappings

	SYNOPSIS		:	return_code = KML_MAP_ERROR_STR(strfuncs_code);

						return_code = KML_MAP_ERROR_GEN(genfuncs_code);

						return_code = KML_MAP_ERROR_SPF(spf_code);

						return_code = KML_MAP_ERROR_TFREAD(tfread_code);

	DESCRIPTION	:	The KMLFUNCS return code mapping macros map return codes from
						various low-level libraries to KMLFUNCS return codes.

						(.) ''KML_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a KMLFUNCS return code.

						(.) ''KML_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a KMLFUNCS return code.

						(.) ''KML_MAP_ERROR_SPF'' maps a return code
						from a SPFFUNCS return code to a KMLFUNCS return code.

						(.) ''KML_MAP_ERROR_TFREAD'' maps a return code
						from a TFREAD return code to a KMLFUNCS return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent KMLFUNCS return
						code.

	NOTES       :	To map truth codes from the libraries, use the related
						KMLFUNCS truth code mapping macros.

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :	Copyright 1998 - 2015 Michael L. Brock

	OUTPUT INDEX:	KML_MAP_ERROR_STR
						KML_MAP_ERROR_GEN
						KML_MAP_ERROR_SPF
						KML_MAP_ERROR_TFREAD
						Return Code Mappings:KML_MAP_ERROR_STR
						Return Code Mappings:KML_MAP_ERROR_GEN
						Return Code Mappings:KML_MAP_ERROR_SPF
						Return Code Mappings:KML_MAP_ERROR_TFREAD
						Macros and Manifest Constants:KML_MAP_ERROR_STR
						Macros and Manifest Constants:KML_MAP_ERROR_GEN
						Macros and Manifest Constants:KML_MAP_ERROR_SPF
						Macros and Manifest Constants:KML_MAP_ERROR_TFREAD
						Defines:See Macros and Manifest Constants

	PUBLISH XREF:	KML_MAP_ERROR_STR
						KML_MAP_ERROR_GEN
						KML_MAP_ERROR_SPF
						KML_MAP_ERROR_TFREAD
						KMLFUNCS Return Code Mappings
						KMLFUNCS Return Code Mapping
						KMLFUNCS return code mappings
						KMLFUNCS return code mapping
						KMLFUNCS Status Code Mappings
						KMLFUNCS Status Code Mapping
						KMLFUNCS status code mappings
						KMLFUNCS status code mapping
						KMLFUNCS Error Code Mappings
						KMLFUNCS Error Code Mapping
						KMLFUNCS error code mappings
						KMLFUNCS error code mapping

   PUBLISH NAME:	KML_MAP_ERROR_STR
						KML_MAP_ERROR_GEN
						KML_MAP_ERROR_SPF
						KML_MAP_ERROR_TFREAD

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define KML_MAP_ERROR_STR(str_code)													\
	(((str_code) == STRFUNCS_SUCCESS)           ? KML_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)           ? KML_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE)  ? KML_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)    ? KML_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)    ? KML_SYSTEM_FAILURE   :	\
	 KML_FAILURE)
#define KML_MAP_ERROR_GEN(gen_code)													\
	(((gen_code) == GENFUNCS_SUCCESS)           ? KML_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)           ? KML_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE)  ? KML_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)    ? KML_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)    ? KML_SYSTEM_FAILURE   :	\
	 ((gen_code) == GENFUNCS_LOCK_ACQ_FAILURE)  ? KML_FAILURE          :	\
	 KML_FAILURE)
#define KML_MAP_ERROR_SPF(spf_code)													\
	(((spf_code) == SPF_SUCCESS)                ? KML_SUCCESS          :	\
	 ((spf_code) == SPF_FAILURE)                ? KML_FAILURE          :	\
	 ((spf_code) == SPF_BAD_ARGS_FAILURE)       ? KML_BAD_ARGS_FAILURE :	\
	 ((spf_code) == SPF_MEMORY_FAILURE)         ? KML_MEMORY_FAILURE   :	\
	 ((spf_code) == SPF_SYSTEM_FAILURE)         ? KML_SYSTEM_FAILURE   :	\
	 KML_FAILURE)
#define KML_MAP_ERROR_TFREAD(tfread_code)											\
	(((tfread_code) == TFREAD_SUCCESS)          ? KML_SUCCESS          :	\
	 ((tfread_code) == TFREAD_FAILURE)          ? KML_FAILURE          :	\
	 ((tfread_code) == TFREAD_BAD_ARGS_FAILURE) ? KML_BAD_ARGS_FAILURE :	\
	 ((tfread_code) == TFREAD_MEMORY_FAILURE)   ? KML_MEMORY_FAILURE   :	\
	 ((tfread_code) == TFREAD_SYSTEM_FAILURE)   ? KML_SYSTEM_FAILURE   :	\
	 KML_FAILURE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Internal function prototypes . . .													*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__KMLFUNCI_H__h */

