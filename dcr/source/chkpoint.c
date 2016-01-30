/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the synchronization of memory-resident cache
								data to its disk image.

	Revision History	:	1994-12-28 --- Creation.
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

int DCR_CheckPointBasic(cache_ptr, check_point_offset,
	check_point_length, synchronous_flag, error_text)
const DCR_CACHE *cache_ptr;
unsigned long    check_point_offset;
unsigned long    check_point_length;
int              synchronous_flag;
char            *error_text;
{
	int  return_code;
	char tmp_error_text[DCR_MAX_ERROR_TEXT];

	if ((return_code = DCR_AssertAccessType(cache_ptr,
		DCR_I_AM_WRITER, tmp_error_text)) == DCR_SUCCESS) {
		if (check_point_offset % ((unsigned long) GEN_GetPageSize())) {
			sprintf(tmp_error_text, "The check-point offset (%lu) %s (%u).",
				check_point_offset,
				"is not an integral multiple of the system page-size",
				GEN_GetPageSize());
			return_code = DCR_FAILURE;
		}
		else if (check_point_offset > cache_ptr->header_ptr->total_cache_size) {
			sprintf(tmp_error_text, "The check-point offset (%lu) %s (%lu).",
				check_point_offset, "is greater than the total cache size",
				cache_ptr->header_ptr->total_cache_size);
			return_code = DCR_FAILURE;
		}
		else if ((check_point_offset + check_point_length) >
			cache_ptr->header_ptr->total_cache_size) {
			sprintf(tmp_error_text, "%s (%lu + %lu = %lu) %s (%lu).",
				"The check-point offset plus the check-point length",
				check_point_offset, check_point_length, check_point_offset +
				check_point_length, "is greater than the total cache size",
				cache_ptr->header_ptr->total_cache_size);
			return_code = DCR_FAILURE;
		}
		else if (msync(((char *) cache_ptr->mmap_ptr) + check_point_offset,
			((int) check_point_length), (synchronous_flag == DCR_TRUE) ? 0 :
			MS_ASYNC)) {
			GEN_GetLastErrorString(0, DCR_MAX_ERROR_TEXT, tmp_error_text);
			return_code = DCR_SYSTEM_FAILURE;
		}
	}

	if (return_code != DCR_SUCCESS) {
		sprintf(error_text,
			"%s %s %lu (0X%08lX) %s %lu (0X%08lX) in %ssynchronous mode failed: ",
			"Attempt to check-point the cache (using 'msync()') beginning at",
			"offset", check_point_offset, check_point_offset, "for length",
			check_point_length, check_point_length,
			(synchronous_flag == DCR_TRUE) ? "" : "a");
		nstrcat(error_text, tmp_error_text,
			DCR_MAX_ERROR_TEXT - (strlen(error_text) + 1));
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_CheckPoint(cache_ptr, synchronous_flag, error_text)
const DCR_CACHE *cache_ptr;
int              synchronous_flag;
char            *error_text;
{
	return(DCR_CheckPointBasic(cache_ptr, 0L,
		cache_ptr->header_ptr->total_cache_size, synchronous_flag, error_text));
}
/*	***********************************************************************	*/

int DCR_CheckPointHeader(cache_ptr, synchronous_flag, error_text)
const DCR_CACHE *cache_ptr;
int              synchronous_flag;
char            *error_text;
{
	return(DCR_CheckPointBasic(cache_ptr, 0L,
		cache_ptr->header_area_size, synchronous_flag, error_text));
}
/*	***********************************************************************	*/

int DCR_CheckPointData(cache_ptr, synchronous_flag, error_text)
const DCR_CACHE *cache_ptr;
int              synchronous_flag;
char            *error_text;
{
	return(DCR_CheckPointBasic(cache_ptr, cache_ptr->data_area_offset,
		cache_ptr->data_area_size, synchronous_flag, error_text));
}
/*	***********************************************************************	*/
int DCR_CheckPointIndices(cache_ptr, synchronous_flag, error_text)
const DCR_CACHE *cache_ptr;
int              synchronous_flag;
char            *error_text;
{
	return(DCR_CheckPointBasic(cache_ptr, cache_ptr->index_area_offset,
		cache_ptr->index_area_size, synchronous_flag, error_text));
}
/*	***********************************************************************	*/

int DCR_CheckPointRecord(cache_ptr, record_element, synchronous_flag,
	error_text)
const DCR_CACHE *cache_ptr;
unsigned int     record_element;
int              synchronous_flag;
char            *error_text;
{
	int return_code;

	if ((return_code = DCR_CheckRecordElement(cache_ptr, record_element,
		error_text)) == DCR_SUCCESS)
		return_code = DCR_CheckPointBasic(cache_ptr,
			cache_ptr->data_area_offset + ((unsigned long) (record_element *
			cache_ptr->total_record_size)), cache_ptr->total_record_size,
			synchronous_flag, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

