/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps the data area of a cache.

	Revision History	:	1994-08-14 --- Creation.
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

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_MapData(cache_ptr, record_count, record_list, error_text)
DCR_CACHE     *cache_ptr;
unsigned int  *record_count;
void         **record_list;
char          *error_text;
{
	unsigned int  tmp_record_count;
	void         *tmp_record_list;

	return(DCR_Refresh(cache_ptr,
		((record_count == NULL) && (record_list == NULL)) ? &tmp_record_count :
		record_count, ((record_count == NULL) && (record_list == NULL)) ?
		&tmp_record_list : record_list, 0, NULL, NULL, error_text));
}
/*	***********************************************************************	*/

void DCR_UnMapData(cache_ptr)
DCR_CACHE *cache_ptr;
{
	if ((cache_ptr->cache_access_type != DCR_I_AM_WRITER) &&
		cache_ptr->record_mmap_size && (cache_ptr->record_mmap_ptr != NULL))
		munmap(cache_ptr->record_mmap_ptr, ((int) cache_ptr->record_mmap_size));

	cache_ptr->record_mmap_size = 0;
	cache_ptr->record_mmap_ptr  = NULL;
}
/*	***********************************************************************	*/

