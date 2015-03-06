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

#include "dcr.h"

/*	***********************************************************************	*/

void DCR_Sort(cache_ptr, index_method, entry_count, entry_list)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
unsigned int  entry_count;
void         *entry_list;
{
	if (DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE)
		DCR_SortIndirect(cache_ptr, index_method, entry_count,
			entry_list);
	else
		DCR_SortEmbedded(cache_ptr, index_method, entry_count,
			entry_list);
}
/*	***********************************************************************	*/

