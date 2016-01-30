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

	Revision History	:	1994-05-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
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

void DCR_IndexCache(cache_ptr)
DCR_CACHE *cache_ptr;
{
	unsigned int count_1;

	if (cache_ptr->record_count) {
		for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
			if (DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE)
				DCR_IndexIndirect(cache_ptr, count_1,
					cache_ptr->index_data_list[count_1].index_entry_list);
			else
				DCR_IndexEmbedded(cache_ptr, count_1,
					cache_ptr->index_data_list[count_1].index_entry_list);
		}
	}
}
/*	***********************************************************************	*/

