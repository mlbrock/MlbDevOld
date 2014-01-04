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
void DCR_FreeBasicCache(cache_ptr)
DCR_CACHE *cache_ptr;
{
	unsigned int count_1;
	unsigned int area_count_offset[DCR_AREA_COUNT];
	unsigned int area_list_offset[DCR_AREA_COUNT];

	DCR_GetAreaCountOffset(area_count_offset);
	DCR_GetAreaListOffset(area_list_offset);

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Free memory allocated for use by this cache . . .				*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < DCR_AREA_COUNT; count_1++) {
		if (*((void **) (((char *) cache_ptr) + area_list_offset[count_1])) !=
			NULL)
			free(*((void **) (((char *) cache_ptr) + area_list_offset[count_1])));
		*((void **) (((char *) cache_ptr) + area_list_offset[count_1])) = NULL;
	}
	DCR_FreeCacheIndexKeyList(cache_ptr);
	if (cache_ptr->cache_file_name != NULL)
		free(cache_ptr->cache_file_name);
	if (cache_ptr->index_data_list != NULL)
		free(cache_ptr->index_data_list);
	if (cache_ptr->index_location_list != NULL)
		free(cache_ptr->index_location_list);
	if (cache_ptr->field_member_list != NULL)
		free(cache_ptr->field_member_list);
	if (cache_ptr->search_record_buffer != NULL)
		free(cache_ptr->search_record_buffer);
	if (cache_ptr->found_record_buffer != NULL)
		free(cache_ptr->found_record_buffer);
	if (cache_ptr->embedded_index_buffer != NULL)
		free(cache_ptr->embedded_index_buffer);
	if (cache_ptr->sql_where_clause != NULL)
		free(cache_ptr->sql_where_clause);
	if (cache_ptr->sql_group_by_clause != NULL)
		free(cache_ptr->sql_group_by_clause);
	if (cache_ptr->sql_order_by_clause != NULL)
		free(cache_ptr->sql_order_by_clause);
	if (cache_ptr->saved_header_ptr != NULL)
		free(cache_ptr->saved_header_ptr);
	if (cache_ptr->tmp_saved_header_ptr != NULL)
		free(cache_ptr->tmp_saved_header_ptr);
	cache_ptr->cache_file_name       = NULL;
	cache_ptr->index_data_list       = NULL;
	cache_ptr->index_location_list   = NULL;
	cache_ptr->field_member_list     = NULL;
	cache_ptr->search_record_buffer  = NULL;
	cache_ptr->found_record_buffer   = NULL;
	cache_ptr->embedded_index_buffer = NULL;
	cache_ptr->sql_where_clause      = NULL;
	cache_ptr->sql_group_by_clause   = NULL;
	cache_ptr->sql_order_by_clause   = NULL;
	cache_ptr->saved_header_ptr      = NULL;
	cache_ptr->tmp_saved_header_ptr  = NULL;
	/*	**************************************************************	*/
}
/* *********************************************************************** */

