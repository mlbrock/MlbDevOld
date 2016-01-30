/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Internal Header File			*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the generic Sybase support
								functions library.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCSYBI_H__h

#define h__DBCSYBI_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "dbcsyb.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DBC Sybase Library Version Number

   NAME        :	DBC Sybase Library Version Number

   DESCRIPTION :	The DBC Sybase library version number manifest constants
						together define the current version number of the DBC Sybase
						library as a whole.

						(.) ''DBC_SYB_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''DBC_SYB_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''DBC_SYB_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''DBC_SYB_VERSION_BUILD'' represents the build
						level component the of library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_SYB_VERSION_MAJOR
						DBC_SYB_VERSION_MINOR
						DBC_SYB_VERSION_RELEASE
						DBC_SYB_VERSION_BUILD
						DBC Sybase Version Numbers:Library Version Number
						DBC Sybase Library Version Number:DBC_SYB_VERSION_MAJOR
						DBC Sybase Library Version Number:DBC_SYB_VERSION_MINOR
						DBC Sybase Library Version Number:DBC_SYB_VERSION_RELEASE
						DBC Sybase Library Version Number:DBC_SYB_VERSION_BUILD
						DBC Macros and Manifest Constants:DBC_SYB_VERSION_MAJOR
						DBC Macros and Manifest Constants:DBC_SYB_VERSION_MINOR
						DBC Macros and Manifest Constants:DBC_SYB_VERSION_RELEASE
						DBC Macros and Manifest Constants:DBC_SYB_VERSION_BUILD
						DBC Sybase Macros and Manifest Constants:DBC_SYB_VERSION_MAJOR
						DBC Sybase Macros and Manifest Constants:DBC_SYB_VERSION_MINOR
						DBC Sybase Macros and Manifest Constants:DBC_SYB_VERSION_RELEASE
						DBC Sybase Macros and Manifest Constants:DBC_SYB_VERSION_BUILD
						Macros and Manifest Constants:DBC_SYB_VERSION_MAJOR
						Macros and Manifest Constants:DBC_SYB_VERSION_MINOR
						Macros and Manifest Constants:DBC_SYB_VERSION_RELEASE
						Macros and Manifest Constants:DBC_SYB_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_SYB_VERSION_MAJOR
						DBC_SYB_VERSION_MINOR
						DBC_SYB_VERSION_RELEASE
						DBC_SYB_VERSION_BUILD
						DBC Sybase Library Version Number
						DBC Sybase library version number
						DBC Sybase Library Version
						DBC Sybase library version
						DBC Sybase Version Number
						DBC Sybase version number
						DBC Sybase Version
						DBC Sybase version

   PUBLISH NAME:	DBC_SYB_VERSION_MAJOR
						DBC_SYB_VERSION_MINOR
						DBC_SYB_VERSION_RELEASE
						DBC_SYB_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						DBC Sybase Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define DBC_SYB_VERSION_MAJOR			((unsigned char) 1)
#define DBC_SYB_VERSION_MINOR			((unsigned char) 0)
#define DBC_SYB_VERSION_RELEASE		((unsigned char) 0)
#define DBC_SYB_VERSION_BUILD			((unsigned char) 'A')
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCSYBI_H__h */

