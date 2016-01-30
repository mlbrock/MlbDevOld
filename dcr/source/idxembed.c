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

#include <memory.h>

#include "dcr.h"

/*	***********************************************************************	*/

void DCR_CopyEmbedded(cache_ptr, index_method, record_offset,
	record_ptr, index_ptr)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
unsigned long  record_offset;
const char    *record_ptr;
char          *index_ptr;
{
	unsigned int count_1;

	for (count_1 = 0;
		count_1 < cache_ptr->index_list[index_method].record_align_count;
		count_1++)
		memcpy(index_ptr +
			cache_ptr->index_data_list[index_method].index_align_cmp_data.
			align_list[count_1].offset,
			record_ptr +
			cache_ptr->index_data_list[index_method].record_align_cmp_data.
			align_list[count_1].offset,
			cache_ptr->index_data_list[index_method].index_align_cmp_data.
			align_list[count_1].length);

	*((unsigned long *) (index_ptr + cache_ptr->index_list[index_method].
		index_pointer_offset)) = record_offset;
}
/*	***********************************************************************	*/

