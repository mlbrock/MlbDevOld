/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the determination of the maximum 'updatedate'
								column in the cache.

	Revision History	:	1994-12-27 --- Creation.
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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

void DCR_ClearMaxUpdateDate(cache_ptr)
DCR_CACHE *cache_ptr;
{
	cache_ptr->max_update_date_known = DCR_FALSE;
}
/*	***********************************************************************	*/

int DCR_FindMaxUpdateDate(cache_ptr, update_date_field_name,
	update_date_field_index, update_date_field_offset, max_update_date_record,
	max_update_date, error_text)
DCR_CACHE    *cache_ptr;
const char   *update_date_field_name;
unsigned int *update_date_field_index;
unsigned int *update_date_field_offset;
unsigned int *max_update_date_record;
DTIME        *max_update_date;
char         *error_text;
{
	int           return_code = DCR_SUCCESS;
	unsigned int  count_1;
	unsigned int  found_index;
	unsigned int  field_index;
	DCR_FIELD    *field_ptr;
	char         *update_date_ptr;
	DTIME         current_update_date;
	DBC_FUNCS     dbc_funcs;
	char          dbc_error_text[DBC_MAX_ERROR_TEXT];

	update_date_field_name = (update_date_field_name != NULL) ?
		update_date_field_name : DCR_DEFAULT_UPDATE_NAME;

	DBC_AttachFacility(&dbc_funcs);
	if (dbc_funcs.min_date == NULL) {
		strcat(strcpy(error_text, "Unable to locate the DBC database "),
			"'date 'minimum' function.");
		return_code = DCR_FAILURE;
	}
	else if (dbc_funcs.date_to_dtime == NULL) {
		strcat(strcpy(error_text, "Unable to locate the DBC database "),
			"'date-to-DTIME conversion function.");
		return_code = DCR_FAILURE;
	}
	else if (DCR_FIND_COLUMN_NAME(cache_ptr->column_name_count,
		cache_ptr->column_name_list, update_date_field_name, &found_index) !=
		STRFUNCS_ITEM_FOUND) {
		sprintf(error_text,
			"Unable to locate the column '%s' in the column list.",
			update_date_field_name);
		return_code = DCR_FAILURE;
	}
	else {
		field_index = cache_ptr->column_name_list[found_index].field_number;
		field_ptr   = cache_ptr->field_list + field_index;
		if ((*dbc_funcs.min_date)(field_ptr->db_type, max_update_date,
			dbc_error_text) != DBC_SUCCESS) {
			sprintf(error_text, "The column '%s' %s: %-.500s",
				update_date_field_name,
				"does not have the correct type for an 'update-date' column",
				dbc_error_text);
			return_code = DCR_FAILURE;
		}
		else {
			*update_date_field_index  = field_index;
			*update_date_field_offset = field_ptr->data_offset;
			update_date_ptr           = ((char *) cache_ptr->mmap_ptr) +
				((unsigned int) cache_ptr->data_area_offset) +
				*update_date_field_offset;
			for (count_1 = 0; count_1 < cache_ptr->record_count; count_1++,
				update_date_ptr += cache_ptr->total_record_size) {
				if (((*dbc_funcs.date_to_dtime)(field_ptr->db_type,
					update_date_ptr, &current_update_date, dbc_error_text) ==
					DBC_SUCCESS) && (DTIME_Compare(max_update_date,
					&current_update_date) < 0)) {
					*max_update_date        = current_update_date;
					*max_update_date_record = count_1;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_GetMaxUpdateDate(cache_ptr, update_date_field_name, max_update_date,
	error_text)
DCR_CACHE  *cache_ptr;
const char *update_date_field_name;
DTIME      *max_update_date;
char       *error_text;
{
	int return_code;

	update_date_field_name = (update_date_field_name != NULL) ?
		update_date_field_name : DCR_DEFAULT_UPDATE_NAME;

	if ((cache_ptr->max_update_date_known != DCR_TRUE) ||
		(strcmp(cache_ptr->update_date_field_name, update_date_field_name))) {
		if ((return_code = DCR_FindMaxUpdateDate(cache_ptr,
			update_date_field_name, &cache_ptr->update_date_field_index,
			&cache_ptr->update_date_field_offset,
			&cache_ptr->max_update_date_record, &cache_ptr->max_update_date,
			error_text)) == DCR_SUCCESS) {
			nstrcpy(cache_ptr->update_date_field_name, update_date_field_name,
				sizeof(cache_ptr->update_date_field_name) - 1);
			if (cache_ptr->record_count)
				cache_ptr->max_update_date_known = DCR_TRUE;
			if (max_update_date != NULL)
				*max_update_date = cache_ptr->max_update_date;
		}
	}
	else {
		if (max_update_date != NULL)
			*max_update_date = cache_ptr->max_update_date;
		return_code = DCR_SUCCESS;
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_HasUpdateDate(cache_ptr, update_date_field_name)
DCR_CACHE  *cache_ptr;
const char *update_date_field_name;
{
	int          return_code;
	unsigned int update_date_field_index;
	DBC_FUNCS    dbc_funcs;

	update_date_field_name = (update_date_field_name != NULL) ?
		update_date_field_name : DCR_DEFAULT_UPDATE_NAME;

	DBC_AttachFacility(&dbc_funcs);
	if ((dbc_funcs.min_date != NULL) && (dbc_funcs.date_to_dtime != NULL) &&
		(DCR_FIND_COLUMN_NAME(cache_ptr->column_name_count,
		cache_ptr->column_name_list, update_date_field_name,
		&update_date_field_index) == STRFUNCS_ITEM_FOUND) &&
		((*dbc_funcs.is_date)(cache_ptr->field_list[
		cache_ptr->column_name_list[update_date_field_index].field_number].
		db_type) == DBC_TRUE))
		return_code = DCR_TRUE;
	else
		return_code = DCR_FALSE;

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_SetMaxUpdateDate(cache_ptr, max_update_date_record, max_update_date,
	error_text)
DCR_CACHE    *cache_ptr;
unsigned int  max_update_date_record;
const DTIME  *max_update_date;
char         *error_text;
{
	int return_code = DCR_FAILURE;

	if (cache_ptr->max_update_date_known != DCR_TRUE)
		strcpy(error_text,
			"The maximum cache 'update-date' has not been determined.");
	else if (max_update_date_record >= cache_ptr->record_count)
		sprintf(error_text, "%s %s (%u) %s (%u).",
			"The new record index of the cache record having the maximum",
			"update-date", max_update_date_record,
			"is equal to or greater than the number of records in the cache",
			cache_ptr->record_count);
	else {
		cache_ptr->max_update_date_record = max_update_date_record;
		cache_ptr->max_update_date        = *max_update_date;
		return_code                       = DCR_SUCCESS;
	}

	return(return_code);
}
/*	***********************************************************************	*/

