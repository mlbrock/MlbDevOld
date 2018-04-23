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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static int DCR_AllocCacheLists(DCR_CONTROL *cache_control_ptr,
	unsigned int allocation_size, char *error_text);
#else
static int DCR_AllocCacheLists();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

int DCR_AllocCacheControl(cache_control_ptr, allocation_granularity,
	error_text)
DCR_CONTROL *cache_control_ptr;
unsigned int       allocation_granularity;
char              *error_text;
{
	allocation_granularity                   =
		(!allocation_granularity) ? 100 : allocation_granularity;

	cache_control_ptr->high_water_mark       = 0;
	cache_control_ptr->allocated_cache_count = 0;
	cache_control_ptr->active_cache_count    = 0;
	cache_control_ptr->cache_list            = NULL;
	cache_control_ptr->usage_list            = NULL;

	return(DCR_AllocCacheLists(cache_control_ptr, allocation_granularity,
		error_text));
}
/*	***********************************************************************	*/

int DCR_AddACache(cache_control_ptr, cache_file_name, in_cache_ptr,
	out_cache_ptr, out_cache_index, error_text)
DCR_CONTROL  *cache_control_ptr;
const char         *cache_file_name;
DCR_CACHE          *in_cache_ptr;
DCR_CACHE         **out_cache_ptr;
unsigned int       *out_cache_index;
char               *error_text;
{
	int          return_code            = DCR_SUCCESS;
	int          cache_entry_found_flag = DCR_FALSE;
	unsigned int count_1;

	*out_cache_ptr   = NULL;
	*out_cache_index = 0;

	if ((cache_file_name == NULL) || (!(*cache_file_name))) {
		strcpy(error_text, "The cache file name is blank.");
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if (cache_control_ptr->active_cache_count <
		cache_control_ptr->allocated_cache_count) {
		for (count_1 = 0; count_1 < cache_control_ptr->allocated_cache_count;
			count_1++) {
			if (cache_control_ptr->cache_list[count_1] == NULL) {
				*out_cache_index       = count_1;
				cache_entry_found_flag = DCR_TRUE;
				break;
			}
		}
		if (cache_entry_found_flag != DCR_TRUE) {
			sprintf(error_text, "%s: %s (%u) %s (%u) %s.",
				"Invalid cache control structure detected",
				"the active cache count", cache_control_ptr->active_cache_count,
				"is less than the allocated cache count",
				cache_control_ptr->allocated_cache_count,
				"but an empty cache slot could not be located");
			return_code = DCR_FAILURE;
		}
	}
	else if (cache_control_ptr->active_cache_count >
		cache_control_ptr->allocated_cache_count) {
		sprintf(error_text, "%s: %s (%u) %s (%u).",
			"Invalid cache control structure detected",
			"the active cache count", cache_control_ptr->active_cache_count,
			"is greater than the allocated cache count",
			cache_control_ptr->allocated_cache_count);
		return_code = DCR_FAILURE;
	}
	else if (cache_control_ptr->allocated_cache_count %
		cache_control_ptr->allocation_granularity) {
		sprintf(error_text, "%s: %s (%u) %s (%u).",
			"Invalid cache control structure detected",
			"the allocated cache count",
			cache_control_ptr->allocated_cache_count,
			"is not an integral multiple of the allocation granularity",
			cache_control_ptr->allocation_granularity);
		return_code = DCR_FAILURE;
	}
	else if ((return_code = DCR_AllocCacheLists(cache_control_ptr,
		((cache_control_ptr->allocated_cache_count + 1) /
		cache_control_ptr->allocation_granularity) *
		cache_control_ptr->allocation_granularity, error_text)) == DCR_SUCCESS)
		*out_cache_index = cache_control_ptr->active_cache_count + 1;

	if (return_code == DCR_SUCCESS) {
		if ((in_cache_ptr->cache_file_name = strdup(cache_file_name)) == NULL) {
   		sprintf(error_text, "%s '%-.500s' failed (%u bytes required).",
				"Attempt to allocate memory for a copy of the cache file name",
				cache_file_name, strlen(cache_file_name) + 1);
			return_code = DCR_MEMORY_FAILURE;
		}
		else if ((*out_cache_ptr = ((DCR_CACHE *) calloc(1,
			sizeof(DCR_CACHE)))) == NULL) {
			free(in_cache_ptr->cache_file_name);
			in_cache_ptr->cache_file_name = NULL;
			sprintf(error_text, "%s (%u bytes required).",
				"Unable to allocate memory to store the cache data",
				sizeof(DCR_CACHE));
			return_code = DCR_MEMORY_FAILURE;
		}
		else {
			**out_cache_ptr                                 = *in_cache_ptr;
			(*out_cache_ptr)->cache_index                   = *out_cache_index;
			(*out_cache_ptr)->control_ptr                   = cache_control_ptr;
			cache_control_ptr->cache_list[*out_cache_index] = *out_cache_ptr;
			cache_control_ptr->active_cache_count++;
		}
	}

	if (return_code != DCR_SUCCESS) {
		*out_cache_ptr   = NULL;
		*out_cache_index = 0;
	}

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_AllocCacheLists(cache_control_ptr, allocation_size,
	error_text)
DCR_CONTROL *cache_control_ptr;
unsigned int       allocation_size;
char              *error_text;
{
	int               return_code = DCR_SUCCESS;
	DCR_CACHE       **tmp_cache_list;
	DCR_USAGE  *tmp_usage_list;

	if ((tmp_cache_list = ((DCR_CACHE **) calloc(allocation_size,
		sizeof(DCR_CACHE *)))) == NULL) {
		sprintf(error_text, "%s (%u elements * %u size = %u total bytes).",
			"Unable to allocate memory for the list of pointers to caches",
			allocation_size, sizeof(DCR_CACHE *),
			allocation_size * sizeof(DCR_CACHE *));
		return_code = DCR_MEMORY_FAILURE;
	}
	else if ((tmp_usage_list = ((DCR_USAGE *)
		calloc(allocation_size, sizeof(DCR_USAGE)))) == NULL) {
		sprintf(error_text, "%s (%u elements * %u size = %u total bytes).",
			"Unable to allocate memory for the list cache usage items",
			allocation_size, sizeof(DCR_USAGE),
			allocation_size * sizeof(DCR_USAGE));
		free(tmp_cache_list);
		return_code = DCR_MEMORY_FAILURE;
	}
	else {
		if (cache_control_ptr->cache_list != NULL) {
			memcpy(tmp_cache_list, cache_control_ptr->cache_list,
				cache_control_ptr->allocated_cache_count *
				sizeof(DCR_CACHE *));
			memcpy(tmp_usage_list, cache_control_ptr->usage_list,
				cache_control_ptr->allocated_cache_count *
				sizeof(DCR_USAGE));
			free(cache_control_ptr->cache_list);
			free(cache_control_ptr->usage_list);
		}
		cache_control_ptr->cache_list            = tmp_cache_list;
		cache_control_ptr->usage_list            = tmp_usage_list;
		cache_control_ptr->allocated_cache_count = allocation_size;
	}

	return(return_code);
}
/*	***********************************************************************	*/

