/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1994-03-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <ctype.h>
#include <stdio.h>

#include "dcr.h"

/*	***********************************************************************	*/

char *DCR_GetVersionCache(cache_version, version_string)
unsigned long  cache_version;
char          *version_string;
{
	sprintf(version_string, "%02u.%02u.%02u%c",
		((unsigned int) ((unsigned char *) &cache_version)[0]) % 99,
		((unsigned int) ((unsigned char *) &cache_version)[1]) % 99,
		((unsigned int) ((unsigned char *) &cache_version)[2]) % 99,
		(isalnum(((unsigned char *) &cache_version)[3])) ?
		((unsigned char *) &cache_version)[3] : '?');

	return(version_string);
}
/*	***********************************************************************	*/

char *DCR_GetVersionLibrary(version_string)
char *version_string;
{
	return(nstrcpy(version_string, DCR_VERSION_LIBRARY,
		DCR_VERSION_NUMBER_LENGTH - 1));
}
/*	***********************************************************************	*/

