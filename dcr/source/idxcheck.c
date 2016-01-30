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

	Revision History	:	1994-05-07 --- Creation.
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
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static int DCR_CheckElementList(DCR_CACHE *cache_ptr,
	unsigned int index_method, unsigned int entry_count,
	const void *entry_list, const unsigned int *element_list, char *error_text);
#else
static int DCR_CheckElementList();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DCR_CheckIndices(cache_ptr, error_text)
DCR_CACHE    *cache_ptr;
char         *error_text;
{
	int           return_code = DCR_SUCCESS;
	unsigned int  count_1;
	unsigned int  entry_count;
	void         *entry_list;

	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		if ((return_code = DCR_MapDataAndIndex(cache_ptr, NULL, NULL,
			count_1, &entry_count, &entry_list, error_text)) != DCR_SUCCESS)
			break;
		if (cache_ptr->header_ptr->indirect_index_flag == DCR_TRUE) {
			return_code = DCR_CheckIndirect(cache_ptr, count_1,
				entry_count, entry_list, error_text);
		}
		else
			return_code = DCR_CheckEmbedded(cache_ptr, count_1,
				entry_count, entry_list, error_text);
		if (return_code != DCR_SUCCESS)
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DCR_CheckIndicesElements(cache_ptr, error_text)
DCR_CACHE *cache_ptr;
char      *error_text;
{
	int           return_code = DCR_SUCCESS;
	unsigned int  count_1;
	unsigned int *element_list;
	unsigned int  entry_count;
	void         *entry_list;

	if (cache_ptr->record_count) {
		if ((element_list = ((unsigned int *) malloc(cache_ptr->record_count *
			sizeof(unsigned int)))) == NULL) {
			sprintf(error_text, "%s (%u elements * %u size = %u total bytes).",
				"Unable to allocate memory for the index element check array",
				cache_ptr->record_count, sizeof(unsigned int),
				cache_ptr->record_count * sizeof(unsigned int));
			return_code = DCR_MEMORY_FAILURE;
		}
		else {
			for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
				if ((return_code = DCR_MapDataAndIndex(cache_ptr, NULL, NULL,
					count_1, &entry_count, &entry_list, error_text)) != DCR_SUCCESS)
					break;
				if (cache_ptr->header_ptr->indirect_index_flag == DCR_TRUE) {
					return_code = DCR_CheckIndirectElements(cache_ptr,
						count_1, entry_count, entry_list, element_list, error_text);
				}
				else
					return_code = DCR_CheckEmbeddedElements(cache_ptr,
						count_1, entry_count, entry_list, element_list, error_text);
				if ((return_code != DCR_SUCCESS) || ((return_code =
					DCR_CheckElementList(cache_ptr, count_1, entry_count,
					entry_list, element_list, error_text)) != DCR_SUCCESS))
					break;
			}
			free(element_list);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int DCR_CheckElementList(cache_ptr, index_method, entry_count,
	entry_list, element_list, error_text)
DCR_CACHE          *cache_ptr;
unsigned int        index_method;
unsigned int        entry_count;
const void         *entry_list;
const unsigned int *element_list;
char               *error_text;
{
	int          return_code = DCR_SUCCESS;
	unsigned int count_1;

	for (count_1 = 0; count_1 < entry_count; count_1++) {
		if (element_list[count_1] == UINT_MAX) {
			sprintf(error_text, "%s %u: %s %u %s %u.",
				"Error in index number", index_method,
				"There is no index entry for data record element", count_1,
				"at record offset", DCR_RELE_TO_ROFF(cache_ptr, count_1));
			return_code = DCR_FAILURE;
			break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

