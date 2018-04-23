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

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_CompareEmbedded(cache_ptr, index_entry_1, index_entry_2,
	data_length)
DCR_CACHE  *cache_ptr;
const void *index_entry_1;
const void *index_entry_2;
size_t      data_length;
{
	return(GEN_ALIGN_CompareList(cache_ptr->index_data_list[cache_ptr->
		current_index_method].index_align_cmp_ptr, index_entry_1,
		index_entry_2, cache_ptr->index_list[cache_ptr->current_index_method].
		index_entry_size));
}
/*	***********************************************************************	*/

