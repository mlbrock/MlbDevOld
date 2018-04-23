/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes all caches associated with the specified
								cache control structure.

	Revision History	:	1994-03-16 --- Creation.
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

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

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
void DCR_CloseAllCaches(cache_control_ptr)
DCR_CONTROL *cache_control_ptr;
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < cache_control_ptr->allocated_cache_count;
		count_1++) {
		if (cache_control_ptr->cache_list[count_1] != NULL)
			DCR_CloseOneCache(cache_control_ptr->cache_list[count_1]);
	}

	if (cache_control_ptr->cache_list != NULL)
		free(cache_control_ptr->cache_list);
	if (cache_control_ptr->usage_list != NULL)
		free(cache_control_ptr->usage_list);

	memset(cache_control_ptr, '\0', sizeof(*cache_control_ptr));
}
/* *********************************************************************** */

