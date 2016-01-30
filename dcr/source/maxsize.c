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

	Revision History	:	1994-05-03 --- Creation.
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

int DCR_CalculateMaxRecords(header_area_size, total_record_size,
	indirect_index_flag, index_count, index_list, allocation_size,
	max_records_in_cache, error_text)
unsigned long    header_area_size;
unsigned int     total_record_size;
int              indirect_index_flag;
unsigned int     index_count;
DCR_INDEX *index_list;
unsigned int    *allocation_size;
unsigned int    *max_records_in_cache;
char            *error_text;
{
	int           return_code = DCR_SUCCESS;
	unsigned int  count_1;
	unsigned long per_record_size;
	unsigned long tmp_allocation_size;
	unsigned long tmp_allocation_count;
	unsigned long allocation_count;
	unsigned long data_area_size;
	unsigned long index_area_size;
	unsigned long index_size;

	*max_records_in_cache = 0;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Check the parameters for reasonableness . . .						*/
	/*	*****************************************************************	*/
	if (header_area_size != ((unsigned long) STRFUNCS_ADJUST_SIZE(header_area_size,
		DCR_HEADER_PAGE_SIZE))) {
		sprintf(error_text, "%s (%lu) %s (%u).",
			"The header area size", header_area_size,
			"is not an integral multiple of the cache header page size",
			DCR_HEADER_PAGE_SIZE);
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (total_record_size != STRFUNCS_ADJUST_SIZE(total_record_size,
		DCR_ALIGNMENT_SIZE)) {
		sprintf(error_text, "%s (%u) %s (%u).",
			"The total record size", total_record_size,
			"is not an integral multiple of the cache alignment size",
			DCR_ALIGNMENT_SIZE);
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (total_record_size > DCR_MAX_RECORD_SIZE) {
		sprintf(error_text, "%s (%u) is greater than the maximum (%u).",
			"The total record size", total_record_size,
			DCR_MAX_RECORD_SIZE);
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (!index_count) {
		strcpy(error_text, "The number of cache indices is zero (0).");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Calculate the approximate amount of memory needed for each		*/
	/*	cache record.																		*/
	/*	*****************************************************************	*/
	per_record_size = total_record_size;
	for (count_1 = 0; count_1 < index_count; count_1++)
		per_record_size += (indirect_index_flag == DCR_TRUE) ?
			sizeof(unsigned long) : index_list[count_1].index_entry_size;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Calculate the approximate number of records which can fit into	*/
	/*	the largest Unix file and address space --- 2 ^ (31 - 1).			*/
	/*	*****************************************************************	*/
	tmp_allocation_count =
		((unsigned long) LONG_MAX) / ((unsigned long) per_record_size);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Calculate the maximum number of records for the cache . . .		*/
	/*	*****************************************************************	*/
	*allocation_size    = (*allocation_size < DCR_MIN_ALLOC_SIZE) ?
		DCR_MIN_ALLOC_SIZE :
		(*allocation_size > DCR_MAX_ALLOC_SIZE) ?
		DCR_MAX_ALLOC_SIZE : *allocation_size;
	tmp_allocation_size = ((unsigned long) *allocation_size);
	while (1) {
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Calculate the adjusted number of records and the total	*/
		/*	memory needed for the cache data area . . .						*/
		/*	***********************************************************	*/
		allocation_count = tmp_allocation_count;
		allocation_count = (allocation_count <= tmp_allocation_size) ?
			tmp_allocation_size : (allocation_count % tmp_allocation_size) ?
			(((allocation_count / tmp_allocation_size) + 1) *
			tmp_allocation_size) : allocation_count;
		data_area_size   = allocation_count * total_record_size;
		data_area_size   = STRFUNCS_ADJUST_SIZE(data_area_size,
			DCR_HEADER_PAGE_SIZE);
		allocation_count =
			data_area_size / ((unsigned long) total_record_size);
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Calculate the total memory needed for the indices . . .	*/
		/*	***********************************************************	*/
		index_area_size = 0L;
		for (count_1 = 0; count_1 < index_count; count_1++) {
			index_size       = allocation_count * ((unsigned long)
				((indirect_index_flag == DCR_TRUE) ? sizeof(unsigned long) :
				index_list[count_1].index_entry_size));
			index_size       = ((unsigned long) STRFUNCS_ADJUST_SIZE(index_size,
				DCR_HEADER_PAGE_SIZE));
			index_area_size += index_size;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		If the total cache size is less than the maximum Unix		*/
		/*	file size, then we've found the cache maximum record count.	*/
		/*	***********************************************************	*/
		if ((((double) header_area_size) + ((double) data_area_size) +
			((double) index_area_size)) < ((double) LONG_MAX)) {
			*max_records_in_cache = ((unsigned int) allocation_count);
			break;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Otherwise, if we can't reduce the temporary record count	*/
		/*	any further, then we can't fit the records into a cache. An	*/
		/* unlikely circumstance.													*/
		/*	***********************************************************	*/
		else if (tmp_allocation_count <=
			((unsigned long) DCR_MIN_ALLOC_SIZE)) {
			if (*allocation_size > DCR_MIN_ALLOC_SIZE) {
				*allocation_size     -= DCR_MIN_ALLOC_SIZE;
				tmp_allocation_size   = ((unsigned long) *allocation_size);
				tmp_allocation_count  =
					((unsigned long) LONG_MAX) / ((unsigned long) per_record_size);
			}
			else {
				sprintf(error_text, "%s %s.",
					"The specified cache sizing parameters can not be fit into a",
					"cache with the indicated characteristics");
				return_code = DCR_FAILURE;
				break;
			}
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		If the last attempt didn't fit, reduce the number of		*/
		/*	temporary records and try again . . .								*/
		/*	***********************************************************	*/
		else
			tmp_allocation_count -= tmp_allocation_size;
		/*	***********************************************************	*/
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

#include <memory.h>

#ifndef NARGS
int main(void);
#else
int main();
#endif /* #ifndef NARGS */

#ifndef NARGS
static void EmitCalculation(DCR_HEADER *cache_header_ptr);
#else
static void EmitCalculation();
#endif /* #ifndef NARGS */

#include "datatest.h"						/* For the test meta-data . . .		*/

int main()
{
	int               return_code      = DCR_SUCCESS;
	DCR_HEADER *cache_header_ptr = NULL;
	unsigned int      count_1;
	char              error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'DCR_CalculateSizes()'\n");
	fprintf(stderr, "---- ------- --- ----------------------------\n\n");

	if ((return_code = DCR_MakeHeader("TEST_CACHE_NAME",
		"TEST_SERVER,TEST_DB,TEST_OWNER,mlds,mlds", "TEST_SERVER",
		"TEST_DB", "TEST_OWNER", "mlds", "mlds", "TEST_TABLE", 4096, 4096,
		DCR_TRUE, MemberCount, MemberList, 0, NULL,
		IndexSpecCount, IndexSpecList, &cache_header_ptr, error_text)) !=
		DCR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code =
		DCR_CalculateMaxRecords(cache_header_ptr->header_area_size,
		cache_header_ptr->total_record_size,
		cache_header_ptr->indirect_index_flag,
		cache_header_ptr->area_list[DCR_AREA_INDEX].count,
		((DCR_INDEX *) (((char *) cache_header_ptr) + ((unsigned int)
		cache_header_ptr->area_list[DCR_AREA_INDEX].offset))),
		&cache_header_ptr->allocation_size,
		&cache_header_ptr->max_records_in_cache, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	printf("=======================================================\n");
	for (count_1 = 0; count_1 < 4; count_1++) {
		cache_header_ptr->allocated_record_count = (!(count_1 % 2)) ?
			cache_header_ptr->initial_allocation_size :
			cache_header_ptr->max_records_in_cache;
		cache_header_ptr->indirect_index_flag = (count_1 < 2) ? DCR_TRUE :
			DCR_FALSE;
		printf("-------------------------------------------------------\n");
		printf("Test Run %u of 4\n", count_1 + 1);
		printf(">>> With Indirect Index Flag = '%s'\n",
			(cache_header_ptr->indirect_index_flag == DCR_TRUE) ?
			"TRUE" : "FALSE");
		printf(">>> %s Allocation Attempt\n", (!(count_1 % 2)) ? "Minimum" :
			"Maximum");
		printf("-------------------------------------------------------\n");
		if ((return_code =
			DCR_CalculateSizes(cache_header_ptr->header_area_size,
			cache_header_ptr->allocation_size,
			cache_header_ptr->max_records_in_cache,
			cache_header_ptr->total_record_size,
			cache_header_ptr->indirect_index_flag,
			cache_header_ptr->area_list[DCR_AREA_INDEX].count,
			((DCR_INDEX *) (((char *) cache_header_ptr) + ((unsigned int)
			cache_header_ptr->area_list[DCR_AREA_INDEX].offset))),
			&cache_header_ptr->allocated_record_count,
			&cache_header_ptr->data_area_offset,
			&cache_header_ptr->data_area_size,
			&cache_header_ptr->index_area_offset,
			&cache_header_ptr->index_area_size,
			&cache_header_ptr->total_cache_size, error_text)) != DCR_SUCCESS)
			break;
		EmitCalculation(cache_header_ptr);
		printf("=======================================================\n");
	}

EXIT_FUNCTION:

	if (cache_header_ptr != NULL)
		free(cache_header_ptr);

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

static void EmitCalculation(cache_header_ptr)
DCR_HEADER *cache_header_ptr;
{
	unsigned int     count_1;
	DCR_INDEX *index_list;

	printf("Header Size        : %10lu\n",
		cache_header_ptr->header_area_size);
	printf("Allocation Size    : %10u\n",
		 cache_header_ptr->allocation_size);
	printf("Indirect Index Flag: %10.10s\n",
		(cache_header_ptr->indirect_index_flag == DCR_TRUE) ?
		"TRUE" : "FALSE");
	printf("Index Count        : %10u\n",
		 cache_header_ptr->area_list[DCR_AREA_INDEX].count);
	printf("Allocation Count   : %10u\n",
		cache_header_ptr->allocated_record_count);
	printf("Data Area Offset   : %10lu\n",
		cache_header_ptr->data_area_offset);
	printf("Data Area Size     : %10lu\n",
		cache_header_ptr->data_area_size);
	printf("Index Area Offset  : %10lu\n",
		cache_header_ptr->index_area_offset);
	printf("Index Area Size    : %10lu\n",
		cache_header_ptr->index_area_size);
	printf("Cache Size         : %10lu\n",
		cache_header_ptr->total_cache_size);

	index_list = ((DCR_INDEX *) (((char *) cache_header_ptr) +
		((unsigned int)
		cache_header_ptr->area_list[DCR_AREA_INDEX].offset)));
	for (count_1 = 0;
		count_1 < cache_header_ptr->area_list[DCR_AREA_INDEX].count;
		count_1++) {
		printf("-------------------------------------------------------\n");
		printf("Index Offset Detail For Index Number %u\n", count_1);
		printf("----- ------ ------ --- ----- ------ -\n");
		printf("Index Area Entry Size : %10u\n",
			(cache_header_ptr->indirect_index_flag == DCR_TRUE) ?
			sizeof(unsigned long) : index_list[count_1].index_entry_size);
		printf("Index Area Offset     : %10lu\n",
			index_list[count_1].tmp_index_area_offset);
		printf("Index Area Actual Size: %10lu\n",
			index_list[count_1].tmp_actual_index_area_size);
		printf("Index Area Total Size : %10lu\n",
			index_list[count_1].tmp_index_area_size);
	}
}

#endif /* #ifdef TEST_MAIN */

