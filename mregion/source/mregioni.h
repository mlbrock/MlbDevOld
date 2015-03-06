/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Interface Library Internal Include File				*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Memory-mapped Region
								Interface Library (MREGION).

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__MREGIONI_H__h

#define h__MREGIONI_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "mregion.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	MREGION Library Version Number

   NAME        :	MREGION Library Version Number

   DESCRIPTION :	The MREGION library version number manifest constants
						together define the current version number of the MREGION
						library as a whole.

						(.) ''MRG_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''MRG_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''MRG_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''MRG_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:	MRG_VERSION_MAJOR
						MRG_VERSION_MINOR
						MRG_VERSION_RELEASE
						MRG_VERSION_BUILD
						MREGION Version Numbers:Library Version Number
						Library Version Number:MRG_VERSION_MAJOR
						Library Version Number:MRG_VERSION_MINOR
						Library Version Number:MRG_VERSION_RELEASE
						Library Version Number:MRG_VERSION_BUILD
						Macros and Manifest Constants:MRG_VERSION_MAJOR
						Macros and Manifest Constants:MRG_VERSION_MINOR
						Macros and Manifest Constants:MRG_VERSION_RELEASE
						Macros and Manifest Constants:MRG_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	MRG_VERSION_MAJOR
						MRG_VERSION_MINOR
						MRG_VERSION_RELEASE
						MRG_VERSION_BUILD
						MREGION Library Version Number
						MREGION library version number
						MREGION Library Version
						MREGION library version
						MREGION Version Number
						MREGION version number
						MREGION Version
						MREGION version

   PUBLISH NAME:	MRG_VERSION_MAJOR
						MRG_VERSION_MINOR
						MRG_VERSION_RELEASE
						MRG_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						MREGION Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define MRG_VERSION_MAJOR					((unsigned char) 1)
#define MRG_VERSION_MINOR					((unsigned char) 0)
#define MRG_VERSION_RELEASE				((unsigned char) 0)
#define MRG_VERSION_BUILD					((unsigned char) 'A')
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MRG_MAP_TRUTH(code)				((code) ? MRG_TRUE : MRG_FALSE)
#define MRG_MAP_TRUTH_STR(str_code)		\
	(((str_code) == STRFUNCS_TRUE) ? MRG_TRUE : MRG_FALSE)
#define MRG_MAP_TRUTH_GEN(gen_code)		\
	(((gen_code) == GENFUNCS_TRUE) ? MRG_TRUE : MRG_FALSE)
#define MRG_MAP_TRUTH_MMI(mmi_code)		\
	(((mmi_code) == MMI_TRUE) ? MRG_TRUE : MRG_FALSE)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MRG_MAP_ERROR_STR(str_code)		\
	(((str_code) == STRFUNCS_SUCCESS) ? MRG_SUCCESS : MRG_FAILURE)
#define MRG_MAP_ERROR_GEN(gen_code)		\
	(((gen_code) == GENFUNCS_SUCCESS) ? MRG_SUCCESS : MRG_FAILURE)
#define MRG_MAP_ERROR_MMI(mmi_code)		\
	(((mmi_code) == MMI_SUCCESS)      ? MRG_SUCCESS : MRG_FAILURE)
/*	***********************************************************************	*/

/*
	ADF NOTE: No ADF.
*/
/*	***********************************************************************	*/
#define MRG_SIGNATURE_NONE					((MRG_SIGNATURE) 0X00000000UL)
#define MRG_SIGNATURE_REG					((MRG_SIGNATURE) 0X12345678UL)
#define MRG_SIGNATURE_FIL					((MRG_SIGNATURE) 0X87654321UL)
#define MRG_SIGNATURE_CTL	  				((MRG_SIGNATURE) 0X18273645UL)

#define MRG_IS_REG_SIG(ptr)				\
	MRG_MAP_TRUTH((ptr)->signature == MRG_SIGNATURE_REG)
#define MRG_IS_FIL_SIG(ptr)				\
	MRG_MAP_TRUTH((ptr)->signature == MRG_SIGNATURE_FIL)
#define MRG_IS_CTL_SIG(ptr)				\
	MRG_MAP_TRUTH((ptr)->signature == MRG_SIGNATURE_CTL)
/*
	CODE NOTE: Not used at present.
#define MRG_IS_REG_VALID_PTR(ptr)		\
	MRG_MAP_TRUTH_GEN(GEN_VPTR_IsValidArea(((void *) (ptr)), sizeof(MRG_REG),	\
	GEN_VPTR_ACCESS_READ_WRITE, NULL))
#define MRG_IS_FIL_VALID_PTR(ptr)		\
	MRG_MAP_TRUTH_GEN(GEN_VPTR_IsValidArea(((void *) (ptr)), sizeof(MRG_FIL),	\
	GEN_VPTR_ACCESS_READ_WRITE, NULL))
#define MRG_IS_CTL_VALID_PTR(ptr)		\
	MRG_MAP_TRUTH_GEN(GEN_VPTR_IsValidArea(((void *) (ptr)), sizeof(MRG_CTL),	\
	GEN_VPTR_ACCESS_READ_WRITE, NULL))
*/
#define MRG_IS_REG_VALID_PTR(ptr)		MRG_MAP_TRUTH((ptr) != NULL)
#define MRG_IS_FIL_VALID_PTR(ptr)		MRG_MAP_TRUTH((ptr) != NULL)
#define MRG_IS_CTL_VALID_PTR(ptr)		MRG_MAP_TRUTH((ptr) != NULL)

#define MRG_IS_REG_PTR(ptr)						\
	MRG_MAP_TRUTH(MRG_IS_REG_VALID_PTR(ptr) && MRG_IS_REG_SIG(ptr))
#define MRG_IS_FIL_PTR(ptr)						\
	MRG_MAP_TRUTH(MRG_IS_FIL_VALID_PTR(ptr) && MRG_IS_FIL_SIG(ptr))
#define MRG_IS_CTL_PTR(ptr)						\
	MRG_MAP_TRUTH(MRG_IS_CTL_VALID_PTR(ptr) && MRG_IS_CTL_SIG(ptr))
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for the internal MREGION functions . . .				*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__MREGIONI_H__h */

