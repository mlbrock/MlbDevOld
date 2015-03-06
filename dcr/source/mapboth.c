/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps both the data area and the index area of a cache.

	Revision History	:	1994-10-28 --- Creation.
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

/*	***********************************************************************	*/
int DCR_MapDataAndIndex(cache_ptr, record_count, record_list,
	index_method, entry_count, entry_list, error_text)
DCR_CACHE     *cache_ptr;
unsigned int  *record_count;
void         **record_list;
unsigned int   index_method;
unsigned int  *entry_count;
void         **entry_list;
char          *error_text;
{
	unsigned int  tmp_record_count;
	void         *tmp_record_list;
	unsigned int  tmp_entry_count;
	void         *tmp_entry_list;

	return(DCR_Refresh(cache_ptr,
		((record_count == NULL) && (record_list == NULL)) ? &tmp_record_count :
		record_count, ((record_count == NULL) && (record_list == NULL)) ?
		&tmp_record_list : record_list, index_method,
		((entry_count == NULL) && (entry_list == NULL)) ? &tmp_entry_count :
		entry_count, ((entry_count == NULL) && (entry_list == NULL)) ?
		&tmp_entry_list : entry_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DCR_MapDataAndIndices(cache_ptr, error_text)
DCR_CACHE *cache_ptr;
char      *error_text;
{
	int           return_code;
	unsigned long old_cache_size;

	do {
		if ((return_code = DCR_MapData(cache_ptr, NULL, NULL,
			error_text)) == DCR_SUCCESS) {
			old_cache_size = cache_ptr->header_ptr->total_cache_size;
			return_code    = DCR_MapAllIndices(cache_ptr, error_text);
		}
	} while ((return_code == DCR_SUCCESS) &&
		(old_cache_size != cache_ptr->header_ptr->total_cache_size));

	return(return_code);
}
/*	***********************************************************************	*/

