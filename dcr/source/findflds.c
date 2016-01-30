/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to manage the update of databases from caches.

	Revision History	:	1995-01-31 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
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

int DCR_FindFieldByColumn(cache_ptr, db_column_name, out_field_index,
	out_field_ptr, error_text)
const DCR_CACHE *cache_ptr;
const char      *db_column_name;
unsigned int    *out_field_index;
DCR_FIELD *out_field_ptr;
char            *error_text;
{
	int          return_code = DCR_SUCCESS;
	unsigned int found_index;

	if (DCR_FIND_COLUMN_NAME(cache_ptr->column_name_count,
		cache_ptr->column_name_list, db_column_name, &found_index) !=
		STRFUNCS_ITEM_FOUND) {
		sprintf(error_text,
			"Unable to locate the column '%s' in the column list.",
			db_column_name);
		return_code = DCR_FAILURE;
	}
	else {
		if (out_field_index != NULL)
			*out_field_index = found_index;
		if (out_field_ptr != NULL)
			*out_field_ptr = cache_ptr->field_list[cache_ptr->
				column_name_list[found_index].field_number];
	}

	return(return_code);
}
/* *********************************************************************** */

int DCR_FindFieldByName(cache_ptr, field_name, out_field_index,
	out_field_ptr, error_text)
const DCR_CACHE *cache_ptr;
const char      *field_name;
unsigned int    *out_field_index;
DCR_FIELD *out_field_ptr;
char            *error_text;
{
	int          return_code = DCR_SUCCESS;
	unsigned int found_index;

	if (DCR_FIND_FIELD_NAME(cache_ptr->field_name_count,
		cache_ptr->field_name_list, field_name, &found_index) !=
		STRFUNCS_ITEM_FOUND) {
		sprintf(error_text,
			"Unable to locate the field '%s' in the field list.", field_name);
		return_code = DCR_FAILURE;
	}
	else {
		if (out_field_index != NULL)
			*out_field_index = found_index;
		if (out_field_ptr != NULL)
			*out_field_ptr = cache_ptr->field_list[cache_ptr->
				field_name_list[found_index].field_number];
	}

	return(return_code);
}
/* *********************************************************************** */

