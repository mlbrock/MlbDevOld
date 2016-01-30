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

	Revision History	:	1994-03-14 --- Creation.
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for functions local to this module . . .			*/
/*	***********************************************************************	*/

#ifndef NARGS
static int DCR_AllocData(DCR_HEADER *cache_header_ptr,
	int cache_area, unsigned int *area_count_ptr, void **area_list_ptr,
	char *error_text);
#else
static int DCR_AllocData();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

int DCR_AllocCache(cache_ptr, cache_header_ptr, error_text)
DCR_CACHE        *cache_ptr;
DCR_HEADER *cache_header_ptr;
char             *error_text;
{
	int            return_code;
	unsigned int   count_1;
	DCR_CACHE      tmp_cache;
	unsigned int   area_count_offset[DCR_AREA_COUNT];
	unsigned int   area_list_offset[DCR_AREA_COUNT];
	void         **tmp_ptr;
	GEN_ALIGN     *align_ptr;

	tmp_cache = *cache_ptr;

	DCR_GetAreaCountOffset(area_count_offset);
	DCR_GetAreaListOffset(area_list_offset);

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < DCR_AREA_COUNT; count_1++) {
		*((unsigned int *) (((char *) &tmp_cache) +
			area_count_offset[count_1]))                                  = 0;
		*((void **) (((char *) &tmp_cache) + area_list_offset[count_1])) = NULL;
	}
	tmp_cache.index_data_list       = NULL;
	tmp_cache.index_location_list   = NULL;
	tmp_cache.index_key_list        = NULL;
	tmp_cache.field_member_list     = NULL;
	tmp_cache.search_record_buffer  = NULL;
	tmp_cache.found_record_buffer   = NULL;
	tmp_cache.embedded_index_buffer = NULL;
	tmp_cache.sql_where_clause      = NULL;
	tmp_cache.sql_group_by_clause   = NULL;
	tmp_cache.sql_order_by_clause   = NULL;
	tmp_cache.saved_header_ptr      = NULL;
	tmp_cache.tmp_saved_header_ptr  = NULL;
	/*	**************************************************************	*/

	for (count_1 = 0; count_1 < DCR_AREA_COUNT; count_1++) {
		tmp_ptr = ((void **) (((char *) &tmp_cache) + area_list_offset[count_1]));
		if ((return_code = DCR_AllocData(cache_header_ptr, ((int) count_1),
			((unsigned int *) (((char *) &tmp_cache) +
			area_count_offset[count_1])),
			tmp_ptr, error_text)) != DCR_SUCCESS)
			goto EXIT_FUNCTION;
	}

	if ((tmp_cache.index_data_list = ((DCR_INDEX_DATA *)
		calloc(tmp_cache.index_count, sizeof(DCR_INDEX_DATA)))) == NULL) {
		sprintf(error_text,
			"%s (%u elements * %u size = %u total bytes required).",
			"Unable to allocate memory for the index data list",
			tmp_cache.index_count, sizeof(DCR_INDEX_DATA),
			tmp_cache.index_count * sizeof(DCR_INDEX_DATA));
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_cache.index_location_list = ((DCR_INDEX_LOCATION *)
		calloc(tmp_cache.index_count, sizeof(DCR_INDEX_LOCATION)))) ==
		NULL) {
		sprintf(error_text,
			"%s (%u elements * %u size = %u total bytes required).",
			"Unable to allocate memory for the index location list",
			tmp_cache.index_count, sizeof(DCR_INDEX_LOCATION),
			tmp_cache.index_count * sizeof(DCR_INDEX_LOCATION));
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_cache.field_member_list = ((GEN_MEMBER *)
		calloc(tmp_cache.field_count, sizeof(GEN_MEMBER)))) ==
		NULL) {
		sprintf(error_text,
			"%s (%u elements * %u size = %u total bytes required).",
			"Unable to allocate memory for the field member list",
			tmp_cache.field_count, sizeof(GEN_MEMBER),
			tmp_cache.field_count * sizeof(GEN_MEMBER));
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_cache.search_record_buffer =
		calloc(cache_header_ptr->total_record_size, sizeof(char))) == NULL) {
		sprintf(error_text, "%s (%u bytes required).",
			"Unable to allocate memory for the search record buffer",
			cache_header_ptr->total_record_size);
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_cache.found_record_buffer =
		calloc(cache_header_ptr->total_record_size, sizeof(char))) == NULL) {
		sprintf(error_text, "%s (%u bytes required).",
			"Unable to allocate memory for the found record buffer",
			cache_header_ptr->total_record_size);
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_cache.embedded_index_buffer =
		calloc(cache_header_ptr->max_entry_length, sizeof(char))) == NULL) {
		sprintf(error_text, "%s (%u bytes required).",
			"Unable to allocate memory for the index entry buffer",
			cache_header_ptr->max_entry_length);
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_cache.saved_header_ptr = ((DCR_HEADER *)
		calloc(cache_header_ptr->header_area_size, sizeof(char)))) == NULL) {
		sprintf(error_text, "%s (%lu bytes required).",
			"Unable to allocate memory for the saved cache header area",
			cache_header_ptr->header_area_size);
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((tmp_cache.tmp_saved_header_ptr = ((DCR_HEADER *)
		calloc(cache_header_ptr->header_area_size, sizeof(char)))) == NULL) {
		sprintf(error_text, "%s (%lu bytes required).",
	"Unable to allocate memory for the temporary saved cache header area",
			cache_header_ptr->header_area_size);
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	DCR_BindInit(&tmp_cache, cache_header_ptr);

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Create the cache field member description list . . .			*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < tmp_cache.field_count; count_1++) {
		GEN_INIT_Member(tmp_cache.field_member_list + count_1);
		nstrcpy(tmp_cache.field_member_list[count_1].name,
			tmp_cache.field_list[count_1].field_name,
			sizeof(tmp_cache.field_member_list[count_1].name) - 1);
		nstrcpy(tmp_cache.field_member_list[count_1].type_spec,
			tmp_cache.field_list[count_1].primitive_type_spec,
			sizeof(tmp_cache.field_member_list[count_1].type_spec) - 1);
		align_ptr                                        =
			tmp_cache.field_align_list +
			tmp_cache.field_list[count_1].primitive_list_index;
		tmp_cache.field_member_list[count_1].data_length =
			tmp_cache.field_list[count_1].data_length -
			(((align_ptr->type == GEN_C_ALIGN_char) ||
			(align_ptr->type == GEN_C_ALIGN_unsigned_char)) ? 1 : 0);
		tmp_cache.field_member_list[count_1].length      =
			tmp_cache.field_list[count_1].data_length;
		tmp_cache.field_member_list[count_1].offset      =
			tmp_cache.field_list[count_1].data_offset;
		tmp_cache.field_member_list[count_1].type_count  =
			tmp_cache.field_list[count_1].primitive_type_count;
		tmp_cache.field_member_list[count_1].dbc_type    =
			tmp_cache.field_list[count_1].db_type;
		tmp_cache.field_member_list[count_1].user_int_1  = 0;
		tmp_cache.field_member_list[count_1].user_int_2  = 0;
		tmp_cache.field_member_list[count_1].user_ptr_1  = NULL;
		tmp_cache.field_member_list[count_1].user_ptr_2  = NULL;
	}
	/*	**************************************************************	*/

	tmp_cache.field_member_count = tmp_cache.field_count;
	*cache_ptr                   = tmp_cache;
	cache_ptr->header_ptr        = cache_header_ptr;

EXIT_FUNCTION:

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Free memory allocated for use by this cache . . .				*/
	/*	**************************************************************	*/
	if (return_code != DCR_SUCCESS)
		DCR_FreeBasicCache(&tmp_cache);
	/*	**************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_AllocData(cache_header_ptr, cache_area, area_count_ptr,
	area_list_ptr, error_text)
DCR_HEADER  *cache_header_ptr;
int                cache_area;
unsigned int      *area_count_ptr;
void             **area_list_ptr;
char              *error_text;
{
	int          return_code = DCR_SUCCESS;
	unsigned int area_item_size;
	char         cache_area_name[DCR_MAX_AREA_NAME + 1];

	if ((*area_count_ptr = DCR_GET_AREA_COUNT(cache_header_ptr,
		cache_area)) > 0) {
		if (!(area_item_size = DCR_GET_AREA_ITEM_SIZE(cache_header_ptr,
			cache_area))) {
			sprintf(error_text,
				"The %s cache area has an element size of zero (0).",
				DCR_GetAreaName(cache_area, cache_area_name));
			return_code = DCR_FAILURE;
		}
		else if ((*area_list_ptr = calloc(*area_count_ptr, area_item_size)) ==
			NULL) {
			sprintf(error_text,
				"%s %s list (%u elements * %u size = %u total bytes required).",
				"Unable to allocate memory for the",
				DCR_GetAreaName(cache_area, cache_area_name),
				*area_count_ptr, 	area_item_size,
				*area_count_ptr * area_item_size);
			return_code = DCR_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

