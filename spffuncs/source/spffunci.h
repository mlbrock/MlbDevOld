/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Internal Include File						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Specification Parse
								Facility (SPFFUNCS) Library.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__SPFFUNCI_H__h

#define h__SPFFUNCI_H__h							1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "spffuncs.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	SPF Truth Code Mappings

   NAME        :	SPF Truth Code Mappings

	SYNOPSIS		:	truth_code = SPF_MAP_TRUTH_STR(str_code);

						truth_code = SPF_MAP_TRUTH_GEN(gen_code);

						truth_code = SPF_MAP_TRUTH_DAT(dat_code);

						truth_code = SPF_MAP_TRUTH_TFREAD(tfread_code);

	DESCRIPTION	:	The SPF truth code mapping macros map truth codes from
						various low-level libraries to SPF truth codes.

						(.) ''SPF_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a SPF truth code.

						(.) ''SPF_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a SPF truth code.

						(.) ''SPF_MAP_TRUTH_DAT'' maps a truth code
						from a DATFUNCS truth code to a SPF truth code.

						(.) ''SPF_MAP_TRUTH_TFREAD'' maps a truth code
						from a TFREAD truth code to a SPF truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent SPF truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						SPF return code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	SPF_MAP_TRUTH_STR
						SPF_MAP_TRUTH_GEN
						SPF_MAP_TRUTH_DAT
						SPF_MAP_TRUTH_TFREAD
						Truth Code Mappings:SPF_MAP_TRUTH_STR
						Truth Code Mappings:SPF_MAP_TRUTH_GEN
						Truth Code Mappings:SPF_MAP_TRUTH_DAT
						Truth Code Mappings:SPF_MAP_TRUTH_TFREAD
						Macros and Manifest Constants:SPF_MAP_TRUTH_STR
						Macros and Manifest Constants:SPF_MAP_TRUTH_GEN
						Macros and Manifest Constants:SPF_MAP_TRUTH_DAT
						Macros and Manifest Constants:SPF_MAP_TRUTH_TFREAD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	SPF_MAP_TRUTH_STR
						SPF_MAP_TRUTH_GEN
						SPF_MAP_TRUTH_DAT
						SPF_MAP_TRUTH_TFREAD
						SPF Truth Code Mappings
						SPF Truth Code Mapping
						SPF truth code mappings
						SPF truth code mapping

   PUBLISH NAME:	SPF_MAP_TRUTH_STR
						SPF_MAP_TRUTH_GEN
						SPF_MAP_TRUTH_DAT
						SPF_MAP_TRUTH_TFREAD

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define SPF_MAP_TRUTH_STR(str_code)			\
	(((str_code) == STRFUNCS_TRUE)  ? SPF_TRUE : SPF_FALSE)
#define SPF_MAP_TRUTH_GEN(gen_code)			\
	(((gen_code) == GENFUNCS_TRUE)  ? SPF_TRUE : SPF_FALSE)
#define SPF_MAP_TRUTH_DAT(dat_code)			\
	(((dat_code) == DATFUNCS_TRUE)  ? SPF_TRUE : SPF_FALSE)
#define SPF_MAP_TRUTH_TFREAD(tfread_code)	\
	(((tfread_code) == TFREAD_TRUE) ? SPF_TRUE : SPF_FALSE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	SPF Return Code Mappings

   NAME        :	SPF Return Code Mappings

	SYNOPSIS		:	return_code = SPF_MAP_ERROR_STR(str_code);

						return_code = SPF_MAP_ERROR_GEN(gen_code);

						return_code = SPF_MAP_ERROR_DAT(dat_code);

						return_code = SPF_MAP_ERROR_TFREAD(tfread_code);

	DESCRIPTION	:	The SPF return code mapping macros map return codes from
						various low-level libraries to SPF return codes.

						(.) ''SPF_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a SPF return code.

						(.) ''SPF_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a SPF return code.

						(.) ''SPF_MAP_ERROR_DAT'' maps a return code
						from a DATFUNCS return code to a SPF return code.

						(.) ''SPF_MAP_ERROR_TFREAD'' maps a return code
						from a TFREAD return code to a SPF return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent SPF return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						SPF truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	SPF_MAP_ERROR_STR
						SPF_MAP_ERROR_GEN
						SPF_MAP_ERROR_DAT
						SPF_MAP_ERROR_TFREAD
						Return Code Mappings:SPF_MAP_ERROR_STR
						Return Code Mappings:SPF_MAP_ERROR_GEN
						Return Code Mappings:SPF_MAP_ERROR_DAT
						Return Code Mappings:SPF_MAP_ERROR_TFREAD
						Macros and Manifest Constants:SPF_MAP_ERROR_STR
						Macros and Manifest Constants:SPF_MAP_ERROR_GEN
						Macros and Manifest Constants:SPF_MAP_ERROR_DAT
						Macros and Manifest Constants:SPF_MAP_ERROR_TFREAD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	SPF_MAP_ERROR_STR
						SPF_MAP_ERROR_GEN
						SPF_MAP_ERROR_DAT
						SPF_MAP_ERROR_TFREAD
						SPF Return Code Mappings
						SPF Return Code Mapping
						SPF return code mappings
						SPF return code mapping
						SPF Status Code Mappings
						SPF Status Code Mapping
						SPF status code mappings
						SPF status code mapping
						SPF Error Code Mappings
						SPF Error Code Mapping
						SPF error code mappings
						SPF error code mapping

   PUBLISH NAME:	SPF_MAP_ERROR_STR
						SPF_MAP_ERROR_GEN
						SPF_MAP_ERROR_DAT
						SPF_MAP_ERROR_TFREAD

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define SPF_MAP_ERROR_STR(str_code)													\
	(((str_code) == STRFUNCS_SUCCESS)           ? SPF_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)           ? SPF_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE)  ? SPF_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)    ? SPF_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)    ? SPF_SYSTEM_FAILURE   :	\
	 SPF_FAILURE)
#define SPF_MAP_ERROR_GEN(gen_code)													\
	(((gen_code) == GENFUNCS_SUCCESS)           ? SPF_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)           ? SPF_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE)  ? SPF_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)    ? SPF_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)    ? SPF_SYSTEM_FAILURE   :	\
	 ((gen_code) == GENFUNCS_LOCK_ACQ_FAILURE)  ? SPF_FAILURE          :	\
	 SPF_FAILURE)
#define SPF_MAP_ERROR_DAT(dat_code)													\
	(((dat_code) == DATFUNCS_SUCCESS) ? SPF_SUCCESS : SPF_FAILURE)
#define SPF_MAP_ERROR_TFREAD(tfread_code)											\
	(((tfread_code) == TFREAD_SUCCESS)          ? SPF_SUCCESS          :	\
	 ((tfread_code) == TFREAD_FAILURE)          ? SPF_FAILURE          :	\
	 ((tfread_code) == TFREAD_BAD_ARGS_FAILURE) ? SPF_BAD_ARGS_FAILURE :	\
	 ((tfread_code) == TFREAD_MEMORY_FAILURE)   ? SPF_MEMORY_FAILURE   :	\
	 ((tfread_code) == TFREAD_SYSTEM_FAILURE)   ? SPF_SYSTEM_FAILURE   :	\
	 SPF_FAILURE)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Internal libary function prototypes . . .											*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__SPFFUNCI_H__h */

