/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Locates a record within an SIIDR structure.

	Revision History	:	1996-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
const void *SIIDR_FindRecord(SIIDR *siidr_ptr, const void *record_ptr,
	unsigned int *found_index)
{
	const void *return_ptr = NULL;

	if ((SIIDR_CheckIDR(siidr_ptr, NULL) == SIIDR_SUCCESS) &&
		(SIIDR_TouchRecordRead(siidr_ptr, record_ptr, NULL) ==
		SIIDR_SUCCESS) && ((found_index == NULL) ||
		(SIIDR_TouchClear(found_index, sizeof(*found_index),
		"'found_index' parameter", NULL) == SIIDR_SUCCESS))) {
		if (SIIDR_LockReaderIDR(siidr_ptr, NULL) == SIIDR_SUCCESS) {
			return_ptr = SIIDR_FindRecordRaw(siidr_ptr, record_ptr,
				found_index);
			SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
		}
	}

	return(return_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
const void *SIIDR_FindRecordRaw(SIIDR *siidr_ptr,
	const void *record_ptr, unsigned int *found_index)
{
	const void   *return_ptr = NULL;
	unsigned int  tmp_found_index;

	found_index = (found_index == NULL) ? &tmp_found_index : found_index;

	if (STR_LIST_bsearch(siidr_ptr, siidr_ptr->record_count,
		siidr_ptr->record_list, record_ptr, siidr_ptr->record_size,
		found_index, STRFUNCS_DIRECTION_TOP,
		STR_CMP_FUNC_CAST(SIIDR_Compare)) == STRFUNCS_ITEM_FOUND)
		return_ptr = siidr_ptr->record_list[*found_index];

	return(return_ptr);
}
/*	***********************************************************************	*/

