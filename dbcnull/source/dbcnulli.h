/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Internal Null Support Functions Library Internal Header File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the null DBC support
								functions library.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCNULLI_H__h

#define h__DBCNULLI_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "dbcnull.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_NULL_FACILITY_NAME

   DESCRIPTION :	The ''DBC_NULL_FACILITY_NAME'' manifest constant specifies
						the DBC facility name string for the Internal NULL facility.

						''DBC_NULL_FACILITY_NAME'' is equal to the string value
						''Facility:Internal NULL''.

   NOTES       :	The DBC facility name can be retrieved by calling the
						``get_id`` function member of the ''DBC_FUNCS'' structure
						attached to your application. This function is implemented
						in the DBC Internal NULL facility by the function
						``DBC_NULL_GetID``.

   CAVEATS     :	The string length of this macro should not exceed the value
						of the manifest constant ''DBC_FACILITY_NAME_LENGTH''. If it
						does, it will be truncated to that length by the function
						``DBC_NULL_GetID``.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_NULL_FACILITY_NAME
						DBC Macros and Manifest Constants:DBC_NULL_FACILITY_NAME
						DBC Internal NULL Macros and Manifest Constants:DBC_NULL_FACILITY_NAME
						Macros and Manifest Constants:DBC_NULL_FACILITY_NAME
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_NULL_FACILITY_NAME

   PUBLISH NAME:	DBC_NULL_FACILITY_NAME

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DBC_NULL_FACILITY_NAME			"Facility:NULL"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	ADF NOTE: Needed here. */
/*	***********************************************************************	*/
#define DBC_NULL_VENDOR_NAME				"Michael L. Brock"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DBC Internal NULL Library Version Number

   NAME        :	DBC Internal NULL Library Version Number

   DESCRIPTION :	The DBC Internal NULL library version number manifest
						constants together define the current version number of the
						DBC NULL library as a whole.

						(.) ''DBC_NULL_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''DBC_NULL_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''DBC_NULL_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''DBC_NULL_VERSION_BUILD'' represents the build
						level component the of library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_NULL_VERSION_MAJOR
						DBC_NULL_VERSION_MINOR
						DBC_NULL_VERSION_RELEASE
						DBC_NULL_VERSION_BUILD
						DBC Internal NULL Version Numbers:Library Version Number
						DBC Internal NULL Library Version Number:DBC_NULL_VERSION_MAJOR
						DBC Internal NULL Library Version Number:DBC_NULL_VERSION_MINOR
						DBC Internal NULL Library Version Number:DBC_NULL_VERSION_RELEASE
						DBC Internal NULL Library Version Number:DBC_NULL_VERSION_BUILD
						DBC Macros and Manifest Constants:DBC_NULL_VERSION_MAJOR
						DBC Macros and Manifest Constants:DBC_NULL_VERSION_MINOR
						DBC Macros and Manifest Constants:DBC_NULL_VERSION_RELEASE
						DBC Macros and Manifest Constants:DBC_NULL_VERSION_BUILD
						DBC Internal NULL Macros and Manifest Constants:DBC_NULL_VERSION_MAJOR
						DBC Internal NULL Macros and Manifest Constants:DBC_NULL_VERSION_MINOR
						DBC Internal NULL Macros and Manifest Constants:DBC_NULL_VERSION_RELEASE
						DBC Internal NULL Macros and Manifest Constants:DBC_NULL_VERSION_BUILD
						Macros and Manifest Constants:DBC_NULL_VERSION_MAJOR
						Macros and Manifest Constants:DBC_NULL_VERSION_MINOR
						Macros and Manifest Constants:DBC_NULL_VERSION_RELEASE
						Macros and Manifest Constants:DBC_NULL_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_NULL_VERSION_MAJOR
						DBC_NULL_VERSION_MINOR
						DBC_NULL_VERSION_RELEASE
						DBC_NULL_VERSION_BUILD
						DBC Internal NULL Library Version Number
						DBC Internal NULL library version number
						DBC Internal NULL Library Version
						DBC Internal NULL library version
						DBC Internal NULL Version Number
						DBC Internal NULL version number
						DBC Internal NULL Version
						DBC Internal NULL version

   PUBLISH NAME:	DBC_NULL_VERSION_MAJOR
						DBC_NULL_VERSION_MINOR
						DBC_NULL_VERSION_RELEASE
						DBC_NULL_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						DBC Internal NULL Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define DBC_NULL_VERSION_MAJOR			((unsigned char) 1)
#define DBC_NULL_VERSION_MINOR			((unsigned char) 0)
#define DBC_NULL_VERSION_RELEASE			((unsigned char) 0)
#define DBC_NULL_VERSION_BUILD			((unsigned char) 'A')
/*	***********************************************************************	*/

#define DBC_NULL_BASE_ERROR_TEXT			\
	"Function not supported in the internal NULL DBC library: "

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Private and internal NULL facility function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_NULL_MapTypeToMDDL,
	(DBC_BASIC_TYPE dbc_basic_type, MDDL *mddl_ptr, char *error_text));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCNULLI_H__h */

