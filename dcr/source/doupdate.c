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

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_DoCacheUpdate(cache_ptr, insert_method, update_date_field_name,
	max_load_rows, db_load_granularity, error_text)
DCR_CACHE    *cache_ptr;
int           insert_method;
const char   *update_date_field_name;
unsigned int  max_load_rows;
unsigned int  db_load_granularity;
char         *error_text;
{
	int          return_code;
	unsigned int old_record_count;
	int          update_flag;
	DTIME        old_max_update_date;

	DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_DB_UPDATE);
	if ((cache_ptr->call_back_mask & DCR_CB_UPDATE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_UPDATE,
		DCR_FALSE, 0, 0, 0, NULL, NULL, DCR_SUCCESS, error_text);

	old_record_count = cache_ptr->record_count;

	if ((return_code = DCR_GetMaxUpdateDate(cache_ptr,
		update_date_field_name, NULL, error_text)) == DCR_SUCCESS) {
		old_max_update_date = cache_ptr->max_update_date;
		update_flag         = (cache_ptr->record_count) ? DCR_TRUE : DCR_FALSE;
		if ((return_code = DCR_DoCacheReload(cache_ptr, insert_method,
			DCR_FALSE, update_flag, (update_flag == DCR_TRUE) ?
			cache_ptr->update_date_field_name : NULL, (update_flag == DCR_TRUE) ?
			&cache_ptr->max_update_date : NULL, max_load_rows,
			db_load_granularity, error_text)) == DCR_SUCCESS)
			cache_ptr->old_max_update_date = old_max_update_date;
	}

	DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
		DCR_STAT_DB_UPDATE,
		((unsigned long) (cache_ptr->record_count - old_record_count)));
	if ((cache_ptr->call_back_mask & DCR_CB_UPDATE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_UPDATE,
		DCR_TRUE, 0, 0, cache_ptr->record_count - old_record_count, NULL,
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_DB_UPDATE, return_code, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

