/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps the specified index area of a cache.

	Revision History	:	1994-05-18 --- Creation.
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

int DCR_MapAllIndices(cache_ptr, error_text)
DCR_CACHE *cache_ptr;
char      *error_text;
{
	int           return_code;
	unsigned int  count_1;
	unsigned long old_cache_size;

	do {
		old_cache_size = cache_ptr->header_ptr->total_cache_size;
		for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
			if ((return_code = DCR_MapIndex(cache_ptr, count_1, NULL, NULL,
				error_text)) != DCR_SUCCESS)
				break;
			if (old_cache_size != cache_ptr->header_ptr->total_cache_size)
				break;
		}
	} while ((return_code == DCR_SUCCESS) &&
		(old_cache_size != cache_ptr->header_ptr->total_cache_size));

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_MapIndex(cache_ptr, index_method, entry_count, entry_list,
	error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
unsigned int  *entry_count;
void         **entry_list;
char          *error_text;
{
	unsigned int  tmp_entry_count;
	void         *tmp_entry_list;

	return(DCR_Refresh(cache_ptr, NULL, NULL, index_method,
		((entry_count == NULL) && (entry_list == NULL)) ? &tmp_entry_count :
		entry_count, ((entry_count == NULL) && (entry_list == NULL)) ?
		&tmp_entry_list : entry_list, error_text));
}
/*	***********************************************************************	*/

void DCR_UnMapAllIndices(cache_ptr)
DCR_CACHE *cache_ptr;
{
	unsigned int count_1;
	char         tmp_error_text[DCR_MAX_ERROR_TEXT];

	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++)
		DCR_UnMapIndex(cache_ptr, count_1, tmp_error_text);
}
/*	***********************************************************************	*/

int DCR_UnMapIndex(cache_ptr, index_method, error_text)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
char         *error_text;
{
	int                   return_code;
	DCR_INDEX_DATA *index_ptr;

	if ((return_code = DCR_ValidateIndexMethod(cache_ptr, index_method,
		error_text)) == DCR_SUCCESS) {
		index_ptr = cache_ptr->index_data_list + index_method;
		if (cache_ptr->cache_access_type == DCR_I_AM_WRITER) {
			index_ptr->mmap_size = 0;
			index_ptr->mmap_ptr  = NULL;
		}
		else {
			if (index_ptr->mmap_size && (index_ptr->mmap_ptr != NULL))
				munmap(index_ptr->mmap_ptr, ((int) index_ptr->mmap_size));
			index_ptr->mmap_size = 0;
			index_ptr->mmap_ptr  = NULL;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

