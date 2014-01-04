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

		Copyright Michael L. Brock 1994 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "dcr.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	The buffer ``cache_access_type_name`` into which the
						string representing the cache access type will be
						copied by this function should be at least the length of
						the manifest constant ''DCR_MAX_ACCESS_NAME'' + ''1''.
						This will accomodate the string used for the case where
						the ``cache_access_type`` parameter is invalid.

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
char *DCR_GetAccessTypeName(cache_access_type, cache_access_type_name)
unsigned long  cache_access_type;
char          *cache_access_type_name;
{
	return(nstrcpy(cache_access_type_name,
		(cache_access_type == DCR_I_AM_WRITER) ? "WRITE" :
		(cache_access_type == DCR_I_AM_READER) ? "READ" :
		"*** INVALID ***", DCR_MAX_ACCESS_NAME));
}
/* *********************************************************************** */

