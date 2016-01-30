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

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_CalculateSizes(header_area_size, allocation_size,
	max_records_in_cache, total_record_size, indirect_index_flag, index_count,
	index_list, allocation_count, data_area_offset, data_area_size,
	index_area_offset, index_area_size, cache_size, error_text)
unsigned long    header_area_size;
unsigned int     allocation_size;
unsigned int     max_records_in_cache;
unsigned int     total_record_size;
int              indirect_index_flag;
unsigned int     index_count;
DCR_INDEX *index_list;
unsigned int    *allocation_count;
unsigned long   *data_area_offset;
unsigned long   *data_area_size;
unsigned long   *index_area_offset;
unsigned long   *index_area_size;
unsigned long   *cache_size;
char            *error_text;
{
	int           return_code = DCR_SUCCESS;
   unsigned int  count_1;
	unsigned long tmp_index_size;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Can't allocate more the pre-calculated maximum record count.	*/
	/*	*****************************************************************	*/
	if (*allocation_count > max_records_in_cache) {
		sprintf(error_text, "%s (%u) exceeds the maximum for the cache (%u).",
			"The specified allocation count",
			*allocation_count, max_records_in_cache);
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Determine the number of records for which we are to allocate	*/
	/* the cache. We'll adjust upward to meet the specified allocation	*/
	/* size specified at the time of cache creation . . .						*/
	/*																							*/
	/*		Note that code commented-out immediately below is not used		*/
	/*	because Purify spuriously marks the last two bytes of the word		*/
	/*	as 'YY' (uninitialized) when the value of the unsigned int to		*/
	/*	which the 'allocation_count' parameter points is greater than		*/
	/*	(but not an integral multiple of) 'allocation_size' and the GCC	*/
	/*	compiler version 2.2.2 is used.												*/
	/*	*****************************************************************	*/
/*
	*allocation_count  = (*allocation_count <= allocation_size) ?
		allocation_size : ((*allocation_count % allocation_size) ?
		(((*allocation_count / allocation_size) + 1) * allocation_size) :
		*allocation_count);
*/
	*allocation_count  = (*allocation_count <= allocation_size) ?
		allocation_size : ((*allocation_count % allocation_size) ?
		(*allocation_count + (allocation_size -
		(*allocation_count % allocation_size))) : *allocation_count);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		The cache data area begins immediately after the cache header	*/
	/*	(but aligned on a cache page).												*/
	/*	*****************************************************************	*/
	*data_area_offset  = STRFUNCS_ADJUST_SIZE(header_area_size,
		DCR_HEADER_PAGE_SIZE);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		The size of the cache data area is the number of records to be	*/
	/*	allocated times the total record size. This may be adjusted			*/
	/* upward to to meet cache page alignment requirements . . .			*/
	/*	*****************************************************************	*/
	*data_area_size    = ((unsigned long) *allocation_count) *
		((unsigned long) total_record_size);
	*data_area_size    = STRFUNCS_ADJUST_SIZE(*data_area_size,
		DCR_HEADER_PAGE_SIZE);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If we had to adjust the data area size upward, the number of	*/
	/*	allocated records may have increased. We adjust that here . . .	*/
	/*	*****************************************************************	*/
	*allocation_count  = ((unsigned int)
		(*data_area_size / ((unsigned long) total_record_size)));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		The index area begins immediately after the cache data area.	*/
	/*	*****************************************************************	*/
	*index_area_offset = header_area_size + *data_area_size;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Calculate the offsets and sizes for each of the indices . . .	*/
	/*	*****************************************************************	*/
	*index_area_size = 0L;
	for (count_1 = 0; count_1 < index_count; count_1++) {
		index_list[count_1].tmp_index_area_offset       = (!count_1) ?
			*index_area_offset : (index_list[count_1 - 1].tmp_index_area_offset +
			index_list[count_1 - 1].tmp_index_area_size);
		tmp_index_size                                  =
			((unsigned long) *allocation_count) *
			((unsigned long) ((indirect_index_flag == DCR_TRUE) ?
			sizeof(unsigned long) : index_list[count_1].index_entry_size));
		index_list[count_1].tmp_actual_index_area_size  = tmp_index_size;
		tmp_index_size                                  =
			STRFUNCS_ADJUST_SIZE(tmp_index_size, DCR_HEADER_PAGE_SIZE);
		index_list[count_1].tmp_index_area_size         = tmp_index_size;
		*index_area_size                               += tmp_index_size;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		The total cache size . . .													*/
	/*	*****************************************************************	*/
	*cache_size = header_area_size + *data_area_size + *index_area_size;
	/*	*****************************************************************	*/

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
		IndexSpecCount, IndexSpecList, &cache_header_ptr, error_text)) ==
		DCR_SUCCESS) {
		printf("=======================================================\n");
		for (count_1 = 0; count_1 < 2; count_1++) {
			cache_header_ptr->indirect_index_flag = (!count_1) ? DCR_TRUE :
				DCR_FALSE;
			printf("-------------------------------------------------------\n");
			printf("Test Run With Indirect Index Flag = '%s'\n",
				(cache_header_ptr->indirect_index_flag == DCR_TRUE) ?
				"TRUE" : "FALSE");
			printf("-------------------------------------------------------\n");
			if ((return_code =
				DCR_CalculateSizes(cache_header_ptr->header_area_size,
				cache_header_ptr->allocation_size,
				cache_header_ptr->max_records_in_cache,
				cache_header_ptr->total_record_size,
				cache_header_ptr->indirect_index_flag,
				cache_header_ptr->area_list[DCR_AREA_INDEX].count,
				((DCR_INDEX *) (((char *) cache_header_ptr) +
				((unsigned int)
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
		free(cache_header_ptr);
	}

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

