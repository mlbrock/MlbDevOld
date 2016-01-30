/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Re-maps a cache.

	Revision History	:	1994-10-03 --- Creation.
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

#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

unsigned int DCR_GetIndexStringLen(cache_ptr, index_method)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
{
	unsigned int count_1;
	unsigned int index_string_length = 0;

	if (DCR_ValidateIndexMethod(cache_ptr, index_method, NULL) ==
		DCR_SUCCESS) {
		for (count_1 = 0;
			count_1 < cache_ptr->index_list[index_method].field_count;
			count_1++)
			index_string_length +=
				strlen(cache_ptr->field_list[cache_ptr->index_field_list[
				cache_ptr->index_list[index_method].field_index + count_1]].
				db_column_name) + 1;
	}

	return(index_string_length);
}
/*	***********************************************************************	*/

unsigned int DCR_GetMaxIndexStringLen(cache_ptr, index_method)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
{
	unsigned int count_1;
	unsigned int index_string_length     = 0;
	unsigned int tmp_index_string_length = 0;

	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++)
		index_string_length = ((tmp_index_string_length =
			DCR_GetIndexStringLen(cache_ptr, index_method)) > 
			index_string_length) ? tmp_index_string_length : index_string_length;

	return(index_string_length);
}
/*	***********************************************************************	*/

char *DCR_GetIndexString(cache_ptr, index_method, index_string)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
char         *index_string;
{
	unsigned int count_1;

	*index_string = '\0';

	if (DCR_ValidateIndexMethod(cache_ptr, index_method, NULL) ==
		DCR_SUCCESS) {
		for (count_1 = 0;
			count_1 < cache_ptr->index_list[index_method].field_count;
			count_1++)
			strcat(strcat(index_string,
				cache_ptr->field_list[cache_ptr->index_field_list[
				cache_ptr->index_list[index_method].field_index + count_1]].
				db_column_name), (count_1 <
				(cache_ptr->index_list[index_method].field_count - 1)) ?
				"," : "");
	}

	return(index_string);
}
/*	***********************************************************************	*/

