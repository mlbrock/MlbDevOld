/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Asserts the type of access an executable has to the
								specified cache.

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

#include <stdio.h>

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

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DCR_AssertAccessType(cache_ptr, cache_access_type, error_text)
const DCR_CACHE *cache_ptr;
unsigned long    cache_access_type;
char            *error_text;
{
	int  return_code = DCR_SUCCESS;
	char buffer_1[DCR_MAX_ACCESS_NAME + 1];
	char buffer_2[DCR_MAX_ACCESS_NAME + 1];

	if (cache_ptr->cache_access_type != cache_access_type) {
		sprintf(error_text, "%s '%s' (0X%08lX) %s --- %s '%s' (0X%08lX).",
			"Assertion check of the cache access type",
			DCR_GetAccessTypeName(cache_access_type, buffer_1),
			cache_access_type, "failed", "the current cache access type is",
			DCR_GetAccessTypeName(cache_ptr->cache_access_type, buffer_2),
			cache_ptr->cache_access_type);
		return_code = DCR_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */
