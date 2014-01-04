/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes the specified cache.

	Revision History	:	1994-03-16 --- Creation.
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

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
void DCR_CloseOneCache(cache_ptr)
DCR_CACHE *cache_ptr;
{
	unsigned int       count_1;
	unsigned int       tmp_cache_index;
	DCR_CONTROL *tmp_cache_control_ptr;

	DCR_CloseBasicCache(cache_ptr);
	DCR_FreeBasicCache(cache_ptr);

	tmp_cache_index       = cache_ptr->cache_index;
	tmp_cache_control_ptr = cache_ptr->control_ptr;
	free(tmp_cache_control_ptr->cache_list[tmp_cache_index]);
	tmp_cache_control_ptr->cache_list[tmp_cache_index] = NULL;
	for (count_1 = tmp_cache_index;
		count_1 < (tmp_cache_control_ptr->active_cache_count - 1); count_1++)
		tmp_cache_control_ptr->usage_list[count_1] =
			tmp_cache_control_ptr->usage_list[count_1 + 1];
	tmp_cache_control_ptr->active_cache_count--;
}
/* *********************************************************************** */

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

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
void DCR_CloseBasicCache(cache_ptr)
DCR_CACHE *cache_ptr;
{
	if (cache_ptr->cache_access_type == DCR_I_AM_WRITER) {
		if ((cache_ptr->file_handle > -1) && (cache_ptr->mmap_ptr != NULL)) {
			cache_ptr->header_ptr->cache_writer_pid           = 0;
			cache_ptr->header_ptr->cache_writer_ip_address[0] = 0;
			cache_ptr->header_ptr->cache_writer_ip_address[1] = 0;
			cache_ptr->header_ptr->cache_writer_ip_address[2] = 0;
			cache_ptr->header_ptr->cache_writer_ip_address[3] = 0;
			msync(((void *) cache_ptr->mmap_ptr), ((long) cache_ptr->mmap_size),
				MS_ASYNC);
		}
	}

	DCR_UnMapData(cache_ptr);
	DCR_UnMapAllIndices(cache_ptr);

	if ((cache_ptr->file_handle > -1) && (cache_ptr->mmap_ptr != NULL))
		DCR_CloseRaw(&cache_ptr->file_handle, &cache_ptr->mmap_ptr,
			&cache_ptr->mmap_size);

	cache_ptr->file_handle = -1;
	cache_ptr->mmap_ptr    = NULL;
	cache_ptr->mmap_size   = 0L;
}
/* *********************************************************************** */

