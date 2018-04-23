/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Validates an index method for a cache.

	Revision History	:	1994-03-12 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
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

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DCR_ValidateIndexMethod(cache_ptr, index_method, error_text)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
char         *error_text;
{
	int return_code = DCR_SUCCESS;

	if (index_method >= cache_ptr->index_count) {
		if (error_text != NULL)
			sprintf(error_text, "%s '%s' (%u) --- %s %u, inclusive.",
				"Invalid cache index method specified for the cache named",
				cache_ptr->header_ptr->cache_name, index_method,
				"valid cache index methods range from 0 to",
				cache_ptr->index_count - 1);
		return_code = DCR_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */

