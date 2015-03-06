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

#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_CheckHeader(cache_header_ptr, mmap_file_size, error_text)
DCR_HEADER *cache_header_ptr;
unsigned long     mmap_file_size;
char             *error_text;
{
	int  return_code = DCR_SUCCESS;
	char version_1[DCR_VERSION_NUMBER_LENGTH];
	char version_2[DCR_VERSION_NUMBER_LENGTH];

	if (mmap_file_size < sizeof(DCR_HEADER)) {
		sprintf(error_text, "%s (%lu) %s (%u).",
			"The cache memory-mapped file size", mmap_file_size,
			"is less than the size of the basic cache header area",
			sizeof(DCR_HEADER));
		return_code = DCR_FAILURE;
	}
	else if (cache_header_ptr->cache_signature != DCR_SIGNATURE) {
		sprintf(error_text, "Invalid cache signature (0X%08lX), %s (0X%08lX).",
			cache_header_ptr->cache_signature, "expected signature is",
			DCR_SIGNATURE);
		return_code = DCR_FAILURE;
	}
	else if (cache_header_ptr->cache_version != DCR_VERSION_CACHE) {
		sprintf(error_text,
			"Invalid cache version ('%s'), expected version is ('%s').",
			DCR_GetVersionCache(cache_header_ptr->cache_version,
			version_1),
			DCR_GetVersionCache(DCR_VERSION_CACHE, version_2));
		return_code = DCR_FAILURE;
	}
	else if (DCR_IsValidStatus(cache_header_ptr->cache_status) !=
		DCR_TRUE) {
		sprintf(error_text, "Invalid cache status (0X%08lX = %lu).",
			cache_header_ptr->cache_status, cache_header_ptr->cache_status);
		return_code = DCR_FAILURE;
	}
/*
	else if (!cache_header_ptr->allocation_granularity) {
		strcpy(error_text,
			"Invalid cache allocation granularity (the minimum is 1).");
		return_code = DCR_FAILURE;
	}
*/
	else if (!DCR_GET_AREA_COUNT(cache_header_ptr,
		DCR_AREA_FIELD)) {
		strcpy(error_text, "Cache field count is zero (0).");
		return_code = DCR_FAILURE;
	}
	else if (!DCR_GET_AREA_COUNT(cache_header_ptr,
		DCR_AREA_FIELD_ALIGN)) {
		strcpy(error_text, "Cache field align count is zero (0).");
		return_code = DCR_FAILURE;
	}
	else if (!DCR_GET_AREA_COUNT(cache_header_ptr,
		DCR_AREA_INDEX)) {
		strcpy(error_text, "Cache index count is zero (0).");
		return_code = DCR_FAILURE;
	}
	else if (!DCR_GET_AREA_COUNT(cache_header_ptr,
		DCR_AREA_INDEX_ALIGN)) {
		strcpy(error_text, "Cache index align count is zero (0).");
		return_code = DCR_FAILURE;
	}
	else if (!cache_header_ptr->total_record_size) {
		strcpy(error_text, "Total cache record length is zero (0).");
		return_code = DCR_FAILURE;
	}
	else if (!cache_header_ptr->max_entry_length) {
		strcpy(error_text, "Maximum embedded index entry size is zero (0).");
		return_code = DCR_FAILURE;
	}
/*
	else if (cache_header_ptr->total_cache_size != mmap_file_size) {
		sprintf(error_text, "%s (%lu) %s (%lu).",
			"The cache total cache size", cache_header_ptr->total_cache_size,
			"is not equal to the memory-mapped file size", mmap_file_size);
		return_code = DCR_FAILURE;
	}
	else if (cache_header_ptr->total_cache_size !=
		(cache_header_ptr->header_area_size + cache_header_ptr->data_area_size +
		cache_header_ptr->index_area_size)) {
		sprintf(error_text, "%s (%lu) %s (%lu) %s (%lu) %s (%lu) (%s = %lu).",
			"The cache total cache size", cache_header_ptr->total_cache_size,
			"is not equal to the total of the cache header area size",
			cache_header_ptr->header_area_size,
			"plus the cache data area size", cache_header_ptr->data_area_size,
			"plus the index area size", cache_header_ptr->index_area_size,
			"total size of all cache areas", cache_header_ptr->data_area_size +
			cache_header_ptr->data_area_size +
			cache_header_ptr->index_area_size);
		return_code = DCR_FAILURE;
	}
*/

	return(return_code);
}
