/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* STRFUNCS String and Memory Functions Library Internal Include File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Internal include file for the STRFUNCS library.

	Revision History	:	1986-10-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__STRFUNCI_H__h

#define h__STRFUNCI_H__h					1

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Necessary include files . . .														*/
/* *********************************************************************** */

#include "strfuncs.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	STRFUNCS Library Version Number

   NAME        :	STRFUNCS Library Version Number

   DESCRIPTION :	The STRFUNCS library version number manifest constants
						together define the current version number of the STRFUNCS
						library as a whole.

						(.) ''STRFUNCS_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''STRFUNCS_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''STRFUNCS_VERSION_RELEASE'' represents the release
						component of library version number.

						(.) ''STRFUNCS_VERSION_BUILD'' represents the build
						level component of library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:	STRFUNCS_VERSION_MAJOR
						STRFUNCS_VERSION_MINOR
						STRFUNCS_VERSION_RELEASE
						STRFUNCS_VERSION_BUILD
						STRFUNCS Version Numbers:Library Version Number
						Library Version Number:STRFUNCS_VERSION_MAJOR
						Library Version Number:STRFUNCS_VERSION_MINOR
						Library Version Number:STRFUNCS_VERSION_RELEASE
						Library Version Number:STRFUNCS_VERSION_BUILD
						Macros and Manifest Constants:STRFUNCS_VERSION_MAJOR
						Macros and Manifest Constants:STRFUNCS_VERSION_MINOR
						Macros and Manifest Constants:STRFUNCS_VERSION_RELEASE
						Macros and Manifest Constants:STRFUNCS_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	STRFUNCS_VERSION_MAJOR
						STRFUNCS_VERSION_MINOR
						STRFUNCS_VERSION_RELEASE
						STRFUNCS_VERSION_BUILD
						STRFUNCS Library Version Number
						STRFUNCS library version number
						STRFUNCS Library Version
						STRFUNCS library version
						STRFUNCS Version Number
						STRFUNCS version number
						STRFUNCS Version
						STRFUNCS version

   PUBLISH NAME:	STRFUNCS_VERSION_MAJOR
						STRFUNCS_VERSION_MINOR
						STRFUNCS_VERSION_RELEASE
						STRFUNCS_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						STRFUNCS Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define STRFUNCS_VERSION_MAJOR			((unsigned char) 3)
#define STRFUNCS_VERSION_MINOR			((unsigned char) 0)
#define STRFUNCS_VERSION_RELEASE			((unsigned char) 0)
#define STRFUNCS_VERSION_BUILD			((unsigned char) 'A')
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* Function prototypes for internal functions defined within 'strfuncs.a'.	*/
/*	***********************************************************************	*/

COMPAT_FN_DECL(int STR_TEST_DoMacros, (void));

/*	***********************************************************************	*/

#endif /* #ifndef h__STRFUNCI_H__h */

