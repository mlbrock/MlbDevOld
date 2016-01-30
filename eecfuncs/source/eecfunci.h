/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Expression Evaluation Calculator Library (EECFUNCS) Internal Include		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the EECFUNCS library.

	Revision History	:	1991-11-03 --- Creation.
									Michael L. Brock
								1993-04-04 --- Version 4 changes.
									Michael L. Brock
								1996-01-28 --- Version 5 changes.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__EECFUNCI_H__h

#define h__EECFUNCI_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "eecfuncs.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	EEC Truth Code Mappings

   NAME        :	EEC Truth Code Mappings

	SYNOPSIS		:	truth_code = EEC_MAP_TRUTH_STR(str_code);

						truth_code = EEC_MAP_TRUTH_GEN(gen_code);

						truth_code = EEC_MAP_TRUTH_DAT(dat_code);

						truth_code = EEC_MAP_TRUTH_TFREAD(tfread_code);

	DESCRIPTION	:	The EEC truth code mapping macros map truth codes from
						various low-level libraries to EEC truth codes.

						(.) ''EEC_MAP_TRUTH_STR'' maps a truth code
						from a STRFUNCS truth code to a EEC truth code.

						(.) ''EEC_MAP_TRUTH_GEN'' maps a truth code
						from a GENFUNCS truth code to a EEC truth code.

						(.) ''EEC_MAP_TRUTH_DAT'' maps a truth code
						from a DATFUNCS truth code to a EEC truth code.

						(.) ''EEC_MAP_TRUTH_TFREAD'' maps a truth code
						from a TFREAD truth code to a EEC truth code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						truth code to be mapped to its equivalent EEC truth
						code.

   NOTES       :	To map return codes from the libraries, use the related
						EEC return code mapping macros.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1991 - 2016 Michael L. Brock

   OUTPUT INDEX:	EEC_MAP_TRUTH_STR
						EEC_MAP_TRUTH_GEN
						EEC_MAP_TRUTH_DAT
						EEC_MAP_TRUTH_TFREAD
						Truth Code Mappings:EEC_MAP_TRUTH_STR
						Truth Code Mappings:EEC_MAP_TRUTH_GEN
						Truth Code Mappings:EEC_MAP_TRUTH_DAT
						Truth Code Mappings:EEC_MAP_TRUTH_TFREAD
						Macros and Manifest Constants:EEC_MAP_TRUTH_STR
						Macros and Manifest Constants:EEC_MAP_TRUTH_GEN
						Macros and Manifest Constants:EEC_MAP_TRUTH_DAT
						Macros and Manifest Constants:EEC_MAP_TRUTH_TFREAD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	EEC_MAP_TRUTH_STR
						EEC_MAP_TRUTH_GEN
						EEC_MAP_TRUTH_DAT
						EEC_MAP_TRUTH_TFREAD
						EEC Truth Code Mappings
						EEC Truth Code Mapping
						EEC truth code mappings
						EEC truth code mapping

   PUBLISH NAME:	EEC_MAP_TRUTH_STR
						EEC_MAP_TRUTH_GEN
						EEC_MAP_TRUTH_DAT
						EEC_MAP_TRUTH_TFREAD

	ENTRY CLASS	:	Macros and Manifest Constants:Truth Code Mappings

EOH */
/*	***********************************************************************	*/
#define EEC_MAP_TRUTH(code)			\
	(((code) ? EEC_TRUE : EEC_FALSE)
#define EEC_MAP_TRUTH_STR(str_code)	\
	(((str_code) == STRFUNCS_TRUE) ? EEC_TRUE : EEC_FALSE)
#define EEC_MAP_TRUTH_GEN(gen_code)	\
	(((gen_code) == GENFUNCS_TRUE)  ? EEC_TRUE : EEC_FALSE)
#define EEC_MAP_TRUTH_DAT(dat_code)	\
	(((dat_code) == DATFUNCS_TRUE)  ? EEC_TRUE : EEC_FALSE)
#define EEC_MAP_TRUTH_TFREAD(tfread_code)				\
	(((tfread_code) == TFREAD_TRUE) ? EEC_TRUE : EEC_FALSE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define EEC_MAP_TRUTH_STR_TO_EEC(str_code)	\
	EEC_MAP_TRUTH_STR(str_code)
#define EEC_MAP_TRUTH_GEN_TO_EEC(gen_code)	\
	EEC_MAP_TRUTH_GEN(gen_code)
#define EEC_MAP_TRUTH_DAT_TO_EEC(dat_code)	\
	EEC_MAP_TRUTH_DAT(dat_code)
#define EEC_MAP_TRUTH_TFREAD_TO_EEC(tfread_code)\
	EEC_MAP_TRUTH_TFREAD(tfread_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	EEC Return Code Mappings

   NAME        :	EEC Return Code Mappings

	SYNOPSIS		:	return_code = EEC_MAP_ERROR_STR(str_code);

						return_code = EEC_MAP_ERROR_GEN(gen_code);

						return_code = EEC_MAP_ERROR_DAT(dat_code);

						return_code = EEC_MAP_ERROR_TFREAD(tfread_code);

	DESCRIPTION	:	The EEC return code mapping macros map return codes from
						various low-level libraries to EEC return codes.

						(.) ''EEC_MAP_ERROR_STR'' maps a return code
						from a STRFUNCS return code to a EEC return code.

						(.) ''EEC_MAP_ERROR_GEN'' maps a return code
						from a GENFUNCS return code to a EEC return code.

						(.) ''EEC_MAP_ERROR_DAT'' maps a return code
						from a DATFUNCS return code to a EEC return code.

						(.) ''EEC_MAP_ERROR_TFREAD'' maps a return code
						from a TFREAD return code to a EEC return code.

	PARAMETERS	:	The single parameter to these macros is the value of the
						return code to be mapped to its equivalent EEC return
						code.

   NOTES       :	To map truth codes from the libraries, use the related
						EEC truth code mapping macros.

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1991 - 2016 Michael L. Brock

   OUTPUT INDEX:	EEC_MAP_ERROR_STR
						EEC_MAP_ERROR_GEN
						EEC_MAP_ERROR_DAT
						EEC_MAP_ERROR_TFREAD
						Return Code Mappings:EEC_MAP_ERROR_STR
						Return Code Mappings:EEC_MAP_ERROR_GEN
						Return Code Mappings:EEC_MAP_ERROR_DAT
						Return Code Mappings:EEC_MAP_ERROR_TFREAD
						Macros and Manifest Constants:EEC_MAP_ERROR_STR
						Macros and Manifest Constants:EEC_MAP_ERROR_GEN
						Macros and Manifest Constants:EEC_MAP_ERROR_DAT
						Macros and Manifest Constants:EEC_MAP_ERROR_TFREAD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	EEC_MAP_ERROR_STR
						EEC_MAP_ERROR_GEN
						EEC_MAP_ERROR_DAT
						EEC_MAP_ERROR_TFREAD
						EEC Return Code Mappings
						EEC Return Code Mapping
						EEC return code mappings
						EEC return code mapping
						EEC Status Code Mappings
						EEC Status Code Mapping
						EEC status code mappings
						EEC status code mapping
						EEC Error Code Mappings
						EEC Error Code Mapping
						EEC error code mappings
						EEC error code mapping

   PUBLISH NAME:	EEC_MAP_ERROR_STR
						EEC_MAP_ERROR_GEN
						EEC_MAP_ERROR_DAT
						EEC_MAP_ERROR_TFREAD

	ENTRY CLASS	:	Macros and Manifest Constants:Return Code Mappings

EOH */
/*	***********************************************************************	*/
#define EEC_MAP_ERROR_STR(str_code)													\
	(((str_code) == STRFUNCS_SUCCESS)          ? EEC_SUCCESS          :	\
	 ((str_code) == STRFUNCS_FAILURE)          ? EEC_FAILURE          :	\
	 ((str_code) == STRFUNCS_BAD_ARGS_FAILURE) ? EEC_BAD_ARGS_FAILURE :	\
	 ((str_code) == STRFUNCS_MEMORY_FAILURE)   ? EEC_MEMORY_FAILURE   :	\
	 ((str_code) == STRFUNCS_SYSTEM_FAILURE)   ? EEC_SYSTEM_FAILURE   :	\
	 EEC_FAILURE)
#define EEC_MAP_ERROR_GEN(gen_code)													\
	(((gen_code) == GENFUNCS_SUCCESS)          ? EEC_SUCCESS          :	\
	 ((gen_code) == GENFUNCS_FAILURE)          ? EEC_FAILURE          :	\
	 ((gen_code) == GENFUNCS_BAD_ARGS_FAILURE) ? EEC_BAD_ARGS_FAILURE :	\
	 ((gen_code) == GENFUNCS_MEMORY_FAILURE)   ? EEC_MEMORY_FAILURE   :	\
	 ((gen_code) == GENFUNCS_SYSTEM_FAILURE)   ? EEC_SYSTEM_FAILURE   :	\
	 ((gen_code) == GENFUNCS_LOCK_ACQ_FAILURE) ? EEC_FAILURE          :	\
	 EEC_FAILURE)
#define EEC_MAP_ERROR_DAT(dat_code)													\
	(((dat_code) == DATFUNCS_SUCCESS)          ? EEC_SUCCESS				:	\
	 ((dat_code) == DATFUNCS_FAILURE)          ? EEC_FAILURE          :	\
	 ((dat_code) == DATFUNCS_MEMORY_FAILURE)   ? EEC_MEMORY_FAILURE   :	\
	 EEC_FAILURE)
#define EEC_MAP_ERROR_TFREAD(tfread_code)											\
	(((tfread_code) == TFREAD_SUCCESS)          ? EEC_SUCCESS          :	\
	 ((tfread_code) == TFREAD_FAILURE)          ? EEC_FAILURE          :	\
	 ((tfread_code) == TFREAD_BAD_ARGS_FAILURE) ? EEC_BAD_ARGS_FAILURE :	\
	 ((tfread_code) == TFREAD_MEMORY_FAILURE)   ? EEC_MEMORY_FAILURE   :	\
	 ((tfread_code) == TFREAD_SYSTEM_FAILURE)   ? EEC_SYSTEM_FAILURE   :	\
	 EEC_FAILURE)
	/*	*****************************************************************
		*****************************************************************
		For compatibility . . .
		*****************************************************************	*/
#define EEC_MAP_ERROR_STR_TO_EEC(str_code)										\
	EEC_MAP_ERROR_STR(str_code)
#define EEC_MAP_ERROR_GEN_TO_EEC(gen_code)										\
	EEC_MAP_ERROR_GEN(gen_code)
#define EEC_MAP_ERROR_DAT_TO_EEC(dat_code)										\
	EEC_MAP_ERROR_DAT(dat_code)
#define EEC_MAP_ERROR_TFREAD_TO_EEC(tfread_code)								\
	EEC_MAP_ERROR_TFREAD(tfread_code)
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Internal functions provided in library 'eecfuncs.{a|lib}' . . .			*/
/*	***********************************************************************	*/

COMPAT_FN_DECL(unsigned int EEC_TEST_DoMacros, (void));

/*	***********************************************************************	*/

#endif /* #ifndef h__EECFUNCI_H__h */

