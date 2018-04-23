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

	Revision History	:	1994-07-17 --- Creation.
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

#include <memory.h>

#include "dcr.h"

/*	***********************************************************************	*/

void *DCR_GetUserDataPtr(cache_ptr, user_data_ptr_index)
DCR_CACHE    *cache_ptr;
unsigned int  user_data_ptr_index;
{
	return((user_data_ptr_index < DCR_USER_DATA_PTR_COUNT) ?
		cache_ptr->user_data_ptr_list[user_data_ptr_index] : NULL);
}
/*	***********************************************************************	*/

void **DCR_GetUserDataPtrList(cache_ptr, user_data_ptr_list)
DCR_CACHE  *cache_ptr;
void      **user_data_ptr_list;
{
	if (user_data_ptr_list != NULL)
		memcpy(*user_data_ptr_list, cache_ptr->user_data_ptr_list,
			sizeof(cache_ptr->user_data_ptr_list));

	return(cache_ptr->user_data_ptr_list);
}
/*	***********************************************************************	*/

void *DCR_SetUserDataPtr(cache_ptr, user_data_ptr_index, user_data_ptr)
DCR_CACHE    *cache_ptr;
unsigned int  user_data_ptr_index;
const void   *user_data_ptr;
{
	void *tmp_user_data_ptr = NULL;

	if (user_data_ptr_index < DCR_USER_DATA_PTR_COUNT) {
		tmp_user_data_ptr                                  =
			cache_ptr->user_data_ptr_list[user_data_ptr_index];
		cache_ptr->user_data_ptr_list[user_data_ptr_index] =
			((void *) user_data_ptr);
	}

	return(tmp_user_data_ptr);
}
/*	***********************************************************************	*/

