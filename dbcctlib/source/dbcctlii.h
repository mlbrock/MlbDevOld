/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase CT-Library Support Functions Library Internal Header File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the Sybase DBC Sybase
								CT-LIB support functions library.

	Revision History	:	1996-06-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCCTLII_H__h

#define h__DBCCTLII_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "dbcctlib.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_FACILITY_NAME

   DESCRIPTION :	The ''DBC_CTLIB_FACILITY_NAME'' manifest constant specifies
						the DBC facility name string for the Sybase CT-LIB facility.

						''DBC_CTLIB_FACILITY_NAME'' is equal to the string value
						''Facility:Sybase CT-LIB''.

   NOTES       :	The DBC facility name can be retrieved by calling the
						``get_id`` function member of the ''DBC_FUNCS'' structure
						attached to your application. This function is implemented
						in the DBC Sybase CT-LIB facility by the function
						``DBC_CTLIB_GetID``.

   CAVEATS     :	The string length of this macro should not exceed the value
						of the manifest constant ''DBC_FACILITY_NAME_LENGTH''. If it
						does, it will be truncated to that length by the function
						``DBC_CTLIB_GetID``.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_FACILITY_NAME
						DBC Macros and Manifest Constants:DBC_CTLIB_FACILITY_NAME
						DBC Sybase CT-LIB Macros and Manifest Constants:DBC_CTLIB_FACILITY_NAME
						Macros and Manifest Constants:DBC_CTLIB_FACILITY_NAME
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_CTLIB_FACILITY_NAME

   PUBLISH NAME:	DBC_CTLIB_FACILITY_NAME

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DBC_CTLIB_FACILITY_NAME			"Facility:Sybase CT-LIB"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	ADF NOTE: Needed here. */
/*	***********************************************************************	*/
#define DBC_CTLIB_VENDOR_NAME				"Sybase"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DBC Sybase CT-LIB Library Version Number

   NAME        :	DBC Sybase CT-LIB Library Version Number

   DESCRIPTION :	The DBC Sybase CT-LIB library version number manifest
						constants together define the current version number of
						the DBC Sybase CT-LIB library as a whole.

						(.) ''DBC_CTLIB_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''DBC_CTLIB_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''DBC_CTLIB_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''DBC_CTLIB_VERSION_BUILD'' represents the build
						level component of the library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_VERSION_MAJOR
						DBC_CTLIB_VERSION_MINOR
						DBC_CTLIB_VERSION_RELEASE
						DBC_CTLIB_VERSION_BUILD
						DBC Sybase CT-LIB Version Numbers:Library Version Number
						DBC Sybase CT-LIB Library Version Number:DBC_CTLIB_VERSION_MAJOR
						DBC Sybase CT-LIB Library Version Number:DBC_CTLIB_VERSION_MINOR
						DBC Sybase CT-LIB Library Version Number:DBC_CTLIB_VERSION_RELEASE
						DBC Sybase CT-LIB Library Version Number:DBC_CTLIB_VERSION_BUILD
						DBC Macros and Manifest Constants:DBC_CTLIB_VERSION_MAJOR
						DBC Macros and Manifest Constants:DBC_CTLIB_VERSION_MINOR
						DBC Macros and Manifest Constants:DBC_CTLIB_VERSION_RELEASE
						DBC Macros and Manifest Constants:DBC_CTLIB_VERSION_BUILD
						DBC Sybase CT-LIB Macros and Manifest Constants:DBC_CTLIB_VERSION_MAJOR
						DBC Sybase CT-LIB Macros and Manifest Constants:DBC_CTLIB_VERSION_MINOR
						DBC Sybase CT-LIB Macros and Manifest Constants:DBC_CTLIB_VERSION_RELEASE
						DBC Sybase CT-LIB Macros and Manifest Constants:DBC_CTLIB_VERSION_BUILD
						Macros and Manifest Constants:DBC_CTLIB_VERSION_MAJOR
						Macros and Manifest Constants:DBC_CTLIB_VERSION_MINOR
						Macros and Manifest Constants:DBC_CTLIB_VERSION_RELEASE
						Macros and Manifest Constants:DBC_CTLIB_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_CTLIB_VERSION_MAJOR
						DBC_CTLIB_VERSION_MINOR
						DBC_CTLIB_VERSION_RELEASE
						DBC_CTLIB_VERSION_BUILD
						DBC Sybase CT-LIB Library Version Number
						DBC Sybase CT-LIB library version number
						DBC Sybase CT-LIB Library Version
						DBC Sybase CT-LIB library version
						DBC Sybase CT-LIB Version Number
						DBC Sybase CT-LIB version number
						DBC Sybase CT-LIB Version
						DBC Sybase CT-LIB version

   PUBLISH NAME:	DBC_CTLIB_VERSION_MAJOR
						DBC_CTLIB_VERSION_MINOR
						DBC_CTLIB_VERSION_RELEASE
						DBC_CTLIB_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						DBC Sybase CT-LIB Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define DBC_CTLIB_VERSION_MAJOR			((unsigned char) 1)
#define DBC_CTLIB_VERSION_MINOR			((unsigned char) 0)
#define DBC_CTLIB_VERSION_RELEASE		((unsigned char) 0)
#define DBC_CTLIB_VERSION_BUILD			((unsigned char) 'A')
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCCTLII_H__h */

