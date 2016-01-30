/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase DB-Library Support Functions Library Internal Header File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Sybase DBC Sybase
								DB-LIB support functions library.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCDBLII_H__h

#define h__DBCDBLII_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "dbcdblib.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_FACILITY_NAME

   DESCRIPTION :	The ''DBC_DBLIB_FACILITY_NAME'' manifest constant specifies
						the DBC facility name string for the Sybase DB-LIB facility.

						''DBC_DBLIB_FACILITY_NAME'' is equal to the string value
						''Facility:Sybase DB-LIB''.

   NOTES       :	The DBC facility name can be retrieved by calling the
						``get_id`` function member of the ''DBC_FUNCS'' structure
						attached to your application. This function is implemented
						in the DBC Sybase DB-LIB facility by the function
						``DBC_DBLIB_GetID``.

   CAVEATS     :	The string length of this macro should not exceed the value
						of the manifest constant ''DBC_FACILITY_NAME_LENGTH''. If it
						does, it will be truncated to that length by the function
						``DBC_DBLIB_GetID``.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_FACILITY_NAME
						DBC Macros and Manifest Constants:DBC_DBLIB_FACILITY_NAME
						DBC Sybase DB-LIB Macros and Manifest Constants:DBC_DBLIB_FACILITY_NAME
						Macros and Manifest Constants:DBC_DBLIB_FACILITY_NAME
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_DBLIB_FACILITY_NAME

   PUBLISH NAME:	DBC_DBLIB_FACILITY_NAME

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DBC_DBLIB_FACILITY_NAME			"Facility:Sybase DB-LIB"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	ADF NOTE: Needed here. */
/*	***********************************************************************	*/
#define DBC_DBLIB_VENDOR_NAME				"Sybase"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DBC Sybase DB-LIB Library Version Number

   NAME        :	DBC Sybase DB-LIB Library Version Number

   DESCRIPTION :	The DBC Sybase DB-LIB library version number manifest
						constants together define the current version number of the
						DBC DB-LIB library as a whole.

						(.) ''DBC_DBLIB_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''DBC_DBLIB_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''DBC_DBLIB_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''DBC_DBLIB_VERSION_BUILD'' represents the build
						level component the of library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_VERSION_MAJOR
						DBC_DBLIB_VERSION_MINOR
						DBC_DBLIB_VERSION_RELEASE
						DBC_DBLIB_VERSION_BUILD
						DBC Sybase DB-LIB Version Numbers:Library Version Number
						DBC Sybase DB-LIB Library Version Number:DBC_DBLIB_VERSION_MAJOR
						DBC Sybase DB-LIB Library Version Number:DBC_DBLIB_VERSION_MINOR
						DBC Sybase DB-LIB Library Version Number:DBC_DBLIB_VERSION_RELEASE
						DBC Sybase DB-LIB Library Version Number:DBC_DBLIB_VERSION_BUILD
						DBC Macros and Manifest Constants:DBC_DBLIB_VERSION_MAJOR
						DBC Macros and Manifest Constants:DBC_DBLIB_VERSION_MINOR
						DBC Macros and Manifest Constants:DBC_DBLIB_VERSION_RELEASE
						DBC Macros and Manifest Constants:DBC_DBLIB_VERSION_BUILD
						DBC Sybase DB-LIB Macros and Manifest Constants:DBC_DBLIB_VERSION_MAJOR
						DBC Sybase DB-LIB Macros and Manifest Constants:DBC_DBLIB_VERSION_MINOR
						DBC Sybase DB-LIB Macros and Manifest Constants:DBC_DBLIB_VERSION_RELEASE
						DBC Sybase DB-LIB Macros and Manifest Constants:DBC_DBLIB_VERSION_BUILD
						Macros and Manifest Constants:DBC_DBLIB_VERSION_MAJOR
						Macros and Manifest Constants:DBC_DBLIB_VERSION_MINOR
						Macros and Manifest Constants:DBC_DBLIB_VERSION_RELEASE
						Macros and Manifest Constants:DBC_DBLIB_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_DBLIB_VERSION_MAJOR
						DBC_DBLIB_VERSION_MINOR
						DBC_DBLIB_VERSION_RELEASE
						DBC_DBLIB_VERSION_BUILD
						DBC Sybase DB-LIB Library Version Number
						DBC Sybase DB-LIB library version number
						DBC Sybase DB-LIB Library Version
						DBC Sybase DB-LIB library version
						DBC Sybase DB-LIB Version Number
						DBC Sybase DB-LIB version number
						DBC Sybase DB-LIB Version
						DBC Sybase DB-LIB version

   PUBLISH NAME:	DBC_DBLIB_VERSION_MAJOR
						DBC_DBLIB_VERSION_MINOR
						DBC_DBLIB_VERSION_RELEASE
						DBC_DBLIB_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						DBC Sybase DB-LIB Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define DBC_DBLIB_VERSION_MAJOR			((unsigned char) 1)
#define DBC_DBLIB_VERSION_MINOR			((unsigned char) 0)
#define DBC_DBLIB_VERSION_RELEASE		((unsigned char) 0)
#define DBC_DBLIB_VERSION_BUILD			((unsigned char) 'A')
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCDBLII_H__h */

