/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets state associates with an SIIDR.

	Revision History	:	1996-04-11 --- Creation
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

#include <string.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_GetIDRAllocCount(SIIDR *siidr_ptr)
{
	unsigned int return_value = 0;

	if (SIIDR_LockReaderIDR(siidr_ptr, NULL) == SIIDR_SUCCESS) {
		return_value = SIIDR_GetIDRAllocCountRaw(siidr_ptr);
		SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
	}

	return(return_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_GetIDRAllocSize(SIIDR *siidr_ptr)
{
	unsigned int return_value = 0;

	if (SIIDR_LockReaderIDR(siidr_ptr, NULL) == SIIDR_SUCCESS) {
		return_value = SIIDR_GetIDRAllocSizeRaw(siidr_ptr);
		SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
	}

	return(return_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
SIIDR_CompareFunc SIIDR_GetIDRCompareFunc(SIIDR *siidr_ptr)
{
	SIIDR_CompareFunc return_value = NULL;

	if (SIIDR_LockReaderIDR(siidr_ptr, NULL) == SIIDR_SUCCESS) {
		return_value = SIIDR_GetIDRCompareFuncRaw(siidr_ptr);
		SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
	}

	return(return_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *SIIDR_GetIDRName(SIIDR *siidr_ptr, char *idr_name,
	unsigned int max_size)
{
	char *return_value = NULL;

	if ((SIIDR_TouchClear(idr_name, max_size + 1, "'idr_name' parameter",
		NULL) == SIIDR_SUCCESS) &&
		(SIIDR_LockReaderIDR(siidr_ptr, NULL) == SIIDR_SUCCESS)) {
		return_value = SIIDR_GetIDRNameRaw(siidr_ptr, idr_name, max_size);
		SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
	}

	return(return_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_GetIDRRecordCount(SIIDR *siidr_ptr)
{
	unsigned int return_value = 0;

	if (SIIDR_LockReaderIDR(siidr_ptr, NULL) == SIIDR_SUCCESS) {
		return_value = SIIDR_GetIDRRecordCountRaw(siidr_ptr);
		SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
	}

	return(return_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_GetIDRRecordSize(SIIDR *siidr_ptr)
{
	unsigned int return_value = 0;

	if (SIIDR_LockReaderIDR(siidr_ptr, NULL) == SIIDR_SUCCESS) {
		return_value = SIIDR_GetIDRRecordSizeRaw(siidr_ptr);
		SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
	}

	return(return_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
SDTIF_STAT_TVAL *SIIDR_GetIDRStatList(SIIDR *siidr_ptr,
	SDTIF_STAT_TVAL *stat_list)
{
	SDTIF_STAT_TVAL *return_value = NULL;

	if ((SIIDR_TouchClear(stat_list, sizeof(siidr_ptr->stat_list),
		"'stat_list' parameter", NULL) == SIIDR_SUCCESS) &&
		(SIIDR_LockReaderIDR(siidr_ptr, NULL) == SIIDR_SUCCESS)) {
		return_value = SIIDR_GetIDRStatListRaw(siidr_ptr, stat_list);
		SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
	}

	return(return_value);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_GetIDRAllocCountRaw(SIIDR *siidr_ptr)
{
	return(siidr_ptr->allocated_count);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_GetIDRAllocSizeRaw(SIIDR *siidr_ptr)
{
	return(siidr_ptr->allocation_size);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
SIIDR_CompareFunc SIIDR_GetIDRCompareFuncRaw(SIIDR *siidr_ptr)
{
	return(siidr_ptr->compare_func);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *SIIDR_GetIDRNameRaw(SIIDR *siidr_ptr, char *idr_name,
	unsigned int max_size)
{
	return(nstrcpy(idr_name, siidr_ptr->idr_name, max_size));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_GetIDRRecordCountRaw(SIIDR *siidr_ptr)
{
	return(siidr_ptr->record_count);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_GetIDRRecordSizeRaw(SIIDR *siidr_ptr)
{
	return(siidr_ptr->record_size);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
SDTIF_STAT_TVAL *SIIDR_GetIDRStatListRaw(SIIDR *siidr_ptr,
	SDTIF_STAT_TVAL *stat_list)
{
	return(((SDTIF_STAT_TVAL *) memcpy(stat_list, siidr_ptr->stat_list,
		sizeof(siidr_ptr->stat_list))));
}
/*	***********************************************************************	*/

