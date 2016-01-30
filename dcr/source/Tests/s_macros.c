/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Test Module											*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1995-02-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
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

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifdef DCR_INDEX_ENTRY_PTR
#undef DCR_INDEX_ENTRY_PTR
#endif /* #ifdef DCR_INDEX_ENTRY_PTR */

#ifdef DCR_INDEX_ENTRY_REC_OFF
#undef DCR_INDEX_ENTRY_REC_OFF
#endif /* #ifdef DCR_INDEX_ENTRY_REC_OFF */

#ifdef DCR_DATA_IS_MAPPED
#undef DCR_DATA_IS_MAPPED
#endif /* #ifdef DCR_DATA_IS_MAPPED */

#ifdef DCR_INDEX_IS_MAPPED
#undef DCR_INDEX_IS_MAPPED
#endif /* #ifdef DCR_INDEX_IS_MAPPED */

#ifdef DCR_BOTH_ARE_MAPPED
#undef DCR_BOTH_ARE_MAPPED
#endif /* #ifdef DCR_BOTH_ARE_MAPPED */

#ifdef DCR_HEADER_AREA_PTR
#undef DCR_HEADER_AREA_PTR
#endif /* #ifdef DCR_HEADER_AREA_PTR */

#ifdef DCR_DATA_AREA_PTR
#undef DCR_DATA_AREA_PTR
#endif /* #ifdef DCR_DATA_AREA_PTR */

#ifdef DCR_INDEX_AREA_PTR
#undef DCR_INDEX_AREA_PTR
#endif /* #ifdef DCR_INDEX_AREA_PTR */

#ifdef DCR_RELE_TO_RPTR_P
#undef DCR_RELE_TO_RPTR_P
#endif /* #ifdef DCR_RELE_TO_RPTR_P */

#ifdef DCR_RELE_TO_ROFF_P
#undef DCR_RELE_TO_ROFF_P
#endif /* #ifdef DCR_RELE_TO_ROFF_P */

#ifdef DCR_ROFF_TO_RPTR_P
#undef DCR_ROFF_TO_RPTR_P
#endif /* #ifdef DCR_ROFF_TO_RPTR_P */

#ifdef DCR_ROFF_TO_RELE_P
#undef DCR_ROFF_TO_RELE_P
#endif /* #ifdef DCR_ROFF_TO_RELE_P */

#ifdef DCR_IELE_TO_ROFF_P
#undef DCR_IELE_TO_ROFF_P
#endif /* #ifdef DCR_IELE_TO_ROFF_P */

#ifdef DCR_IELE_TO_RELE_P
#undef DCR_IELE_TO_RELE_P
#endif /* #ifdef DCR_IELE_TO_RELE_P */

#ifdef DCR_IELE_TO_RPTR_P
#undef DCR_IELE_TO_RPTR_P
#endif /* #ifdef DCR_IELE_TO_RPTR_P */

#ifdef DCR_IELE_TO_ROFF
#undef DCR_IELE_TO_ROFF
#endif /* #ifdef DCR_IELE_TO_ROFF */

#ifdef DCR_IELE_TO_RELE
#undef DCR_IELE_TO_RELE
#endif /* #ifdef DCR_IELE_TO_RELE */

#ifdef DCR_IELE_TO_RPTR
#undef DCR_IELE_TO_RPTR
#endif /* #ifdef DCR_IELE_TO_RPTR */

#ifdef DCR_RELE_TO_RPTR
#undef DCR_RELE_TO_RPTR
#endif /* #ifdef DCR_RELE_TO_RPTR */

#ifdef DCR_RELE_TO_ROFF
#undef DCR_RELE_TO_ROFF
#endif /* #ifdef DCR_RELE_TO_ROFF */

#ifdef DCR_ROFF_TO_RPTR
#undef DCR_ROFF_TO_RPTR
#endif /* #ifdef DCR_ROFF_TO_RPTR */

#ifdef DCR_ROFF_TO_RELE
#undef DCR_ROFF_TO_RELE
#endif /* #ifdef DCR_ROFF_TO_RELE */

#ifdef DCR_REC_OFF_FROM_IDX_ELE
#undef DCR_REC_OFF_FROM_IDX_ELE
#endif /* #ifdef DCR_REC_OFF_FROM_IDX_ELE */

#ifdef DCR_REC_ELE_FROM_IDX_ELE
#undef DCR_REC_ELE_FROM_IDX_ELE
#endif /* #ifdef DCR_REC_ELE_FROM_IDX_ELE */

#ifdef DCR_REC_PTR_FROM_IDX_ELE
#undef DCR_REC_PTR_FROM_IDX_ELE
#endif /* #ifdef DCR_REC_PTR_FROM_IDX_ELE */

#ifdef DCR_REC_PTR_FROM_REC_ELE
#undef DCR_REC_PTR_FROM_REC_ELE
#endif /* #ifdef DCR_REC_PTR_FROM_REC_ELE */

#ifdef DCR_REC_PTR_FROM_REC_OFF
#undef DCR_REC_PTR_FROM_REC_OFF
#endif /* #ifdef DCR_REC_PTR_FROM_REC_OFF */

#ifdef DCR_REC_ELE_FROM_REC_OFF
#undef DCR_REC_ELE_FROM_REC_OFF
#endif /* #ifdef DCR_REC_ELE_FROM_REC_OFF */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	CODE NOTE: To be removed.																*/
/*	***********************************************************************	*/

/*
	Returns a pointer to the specified index entry within the specified
	index.
*/
     /* 123456789012345678901234567890 */
#define DCR_INDEX_ENTRY_PTR(cache_ptr, idx_method, entry_count,	\
	entry_list, idx_element) (((char *) (entry_list)) +						\
	(((unsigned long) (idx_element)) *												\
	DCR_INDEX_ENTRY_SIZE(cache_ptr, idx_method)))

/*
	Gets the offset of the data record from the specified index entry within
	the specified index.
*/
     /* 123456789012345678901234567890 */
#define DCR_INDEX_ENTRY_REC_OFF(cache_ptr, idx_method, entry_count,	\
	entry_list, idx_element)																\
	*((unsigned long *)																		\
	(DCR_INDEX_ENTRY_PTR(cache_ptr, idx_method, entry_count,				\
	entry_list, idx_element) +	DCR_INDEX_REC_OFF(cache_ptr, idx_method)))

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

	/* Is the cache data area mapped? */
#define DCR_DATA_IS_MAPPED(cache_ptr)								\
	((((cache_ptr)->cache_access_type == DCR_I_AM_WRITER) ||	\
	((cache_ptr)->record_mmap_ptr != NULL)) ? DCR_TRUE : DCR_FALSE)

	/* Is the specified cache index area mapped? */
#define DCR_INDEX_IS_MAPPED(cache_ptr, index_method)				\
	((((cache_ptr)->cache_access_type == DCR_I_AM_WRITER) ||		\
	((cache_ptr)->index_data_list[(index_method)].mmap_ptr != NULL))	\
	? DCR_TRUE : DCR_FALSE)

	/* Is the specified cache index area mapped? */
#define DCR_BOTH_ARE_MAPPED(cache_ptr, index_method)				\
	((((cache_ptr)->cache_access_type == DCR_I_AM_WRITER) ||		\
	(((cache_ptr)->record_mmap_ptr != NULL) &&								\
	((cache_ptr)->index_data_list[(index_method)].mmap_ptr != NULL)))	\
	? DCR_TRUE : DCR_FALSE)

	/* Get a pointer to the cache header. */
#define DCR_HEADER_AREA_PTR(cache_ptr)						\
	((char *) ((cache_ptr)->mmap_ptr))

	/* Get a pointer to the cache data area. */
#define DCR_DATA_AREA_PTR(cache_ptr)						\
	(((char *) (cache_ptr)->record_mmap_ptr) +					\
	((unsigned int) (cache_ptr)->data_area_offset))

	/* Get a pointer to a cache index area. */
#define DCR_INDEX_AREA_PTR(cache_ptr, index_method)	\
	((char *) ((cache_ptr)->index_data_list[(index_method)].mmap_ptr))

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Primitive data access macros . . .												*/
/*	***********************************************************************	*/

	/* Given a record element, what is the record pointer? */
#define DCR_RELE_TO_RPTR_P(cache_ptr, record_mmap_ptr,					\
	record_element)																			\
	((void *) (((char *) (record_mmap_ptr)) +											\
	DCR_RELE_TO_ROFF_P(cache_ptr, record_element)))

	/* Given a record element, what is the record offset? */
#define DCR_RELE_TO_ROFF_P(cache_ptr, record_element)						\
	(((unsigned int) (cache_ptr)->data_area_offset) +								\
	((record_element) * (cache_ptr)->total_record_size))

	/* Given a record offset, what is the record pointer? */
#define DCR_ROFF_TO_RPTR_P(cache_ptr, record_mmap_ptr,					\
	record_offset)																				\
	((void *) (((char *) (record_mmap_ptr)) +											\
	((unsigned int) (record_offset))))

	/* Given a record offset, what is the record element? */
#define DCR_ROFF_TO_RELE_P(cache_ptr, record_offset) 						\
	(((record_offset) - (cache_ptr)->data_area_offset) /							\
	(cache_ptr)->total_record_size)

	/*	Given an element of an index, get the pointer to the index element. */
#define DCR_IELE_TO_IPTR_P(cache_ptr, index_method, entry_count,		\
	entry_list, index_element) (((char *) (entry_list)) +							\
	(((unsigned int) (index_element)) *													\
	DCR_INDEX_ENTRY_SIZE(cache_ptr, index_method)))

	/* Given an element of an index, what is the record offset? */
#define DCR_IELE_TO_ROFF_P(cache_ptr, index_method, entry_count,		\
	entry_list, index_element)																\
	*((unsigned int *) (DCR_IELE_TO_IPTR_P(cache_ptr, index_method,	\
	record_count, entry_list, index_element) +										\
	DCR_INDEX_REC_OFF(cache_ptr, index_method)))

	/* Given an element of an index, what is the record element? */
#define DCR_IELE_TO_RELE_P(cache_ptr, index_method, entry_count,		\
	entry_list, index_element)																\
	(DCR_ROFF_TO_RELE_P(cache_ptr, DCR_IELE_TO_ROFF_P(cache_ptr,\
	index_method, entry_count, entry_list, index_element)))

	/* Given an element of an index, what is the record pointer? */
#define DCR_IELE_TO_RPTR_P(cache_ptr, index_method, entry_count,		\
	entry_list, index_element,	record_mmap_ptr)											\
	DCR_RELE_TO_RPTR_P(cache_ptr, record_mmap_ptr,								\
	DCR_IELE_TO_RELE_P(cache_ptr, index_method, entry_count,				\
	entry_list, index_element))

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Application-level data access macros . . .									*/
/*	***********************************************************************	*/

	/* Given a record element, what is the record pointer? */
#define DCR_RELE_TO_RPTR(cache_ptr, record_element)						\
	DCR_RELE_TO_RPTR_P(cache_ptr, (cache_ptr)->record_mmap_ptr,			\
	record_element)

	/* Given a record element, what is the record offset? */
#define DCR_RELE_TO_ROFF(cache_ptr, record_element)						\
	DCR_RELE_TO_ROFF_P(cache_ptr, record_element)

	/* Given a record offset, what is the record pointer? */
#define DCR_ROFF_TO_RPTR(cache_ptr, record_offset)							\
	DCR_ROFF_TO_RPTR_P(cache_ptr, (cache_ptr)->record_mmap_ptr,			\
	record_offset)

	/* Given a record offset, what is the record element? */
#define DCR_ROFF_TO_RELE(cache_ptr, record_offset) 						\
	DCR_ROFF_TO_RELE_P(cache_ptr, record_offset)

	/*	Given an element of an index, get the pointer to the index element. */
#define DCR_IELE_TO_IPTR(cache_ptr, index_method, index_element)		\
	DCR_IELE_TO_IPTR_P(cache_ptr, index_method,								\
	(cache_ptr)->record_count,																\
	(cache_ptr)->index_data_list[(index_method)].mmap_ptr, index_element)	\

	/* Given an element of an index, what is the record offset? */
#define DCR_IELE_TO_ROFF(cache_ptr, index_method, index_element)		\
	DCR_IELE_TO_ROFF_P(cache_ptr, index_method,								\
	(cache_ptr)->record_count,																\
	(cache_ptr)->index_data_list[(index_method)].mmap_ptr, index_element)	\

	/* Given an element of an index, what is the record element? */
#define DCR_IELE_TO_RELE(cache_ptr, index_method, index_element)		\
	DCR_IELE_TO_RELE_P(cache_ptr, index_method,								\
	(cache_ptr)->record_count,																\
	(cache_ptr)->index_data_list[(index_method)].mmap_ptr, index_element)	\

	/* Given an element of an index, what is the record pointer? */
#define DCR_IELE_TO_RPTR(cache_ptr, index_method, index_element)		\
	DCR_IELE_TO_RPTR_P(cache_ptr, index_method,								\
	(cache_ptr)->record_count,																\
	(cache_ptr)->index_data_list[(index_method)].mmap_ptr, index_element,	\
	(cache_ptr)->record_mmap_ptr)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Old-style application-level data access macros . . .						*/
/*	***********************************************************************	*/

	/* Given an element of an index, what is the record offset? */
#define DCR_REC_OFF_FROM_IDX_ELE(cache_ptr, index_method,				\
	index_element)																				\
	DCR_IELE_TO_ROFF(cache_ptr, index_method, index_element)

	/* Given an element of an index, what is the record element? */
#define DCR_REC_ELE_FROM_IDX_ELE(cache_ptr, index_method,				\
	index_element)																				\
	DCR_IELE_TO_RELE(cache_ptr, index_method, index_element)

	/* Given an element of an index, what is the record pointer? */
#define DCR_REC_PTR_FROM_IDX_ELE(cache_ptr, index_method, 				\
	index_element)																				\
	DCR_IELE_TO_RPTR(cache_ptr, index_method, index_element)

	/* Given a record element, what is the record pointer? */
#define DCR_REC_PTR_FROM_REC_ELE(cache_ptr, record_element)				\
	DCR_RELE_TO_RPTR(cache_ptr, record_element)

	/* Given a record offset, what is the record pointer? */
#define DCR_REC_PTR_FROM_REC_OFF(cache_ptr, record_offset)				\
	DCR_ROFF_TO_RPTR(cache_ptr, record_offset)

	/* Given a record offset, what is the record element? */
#define DCR_REC_ELE_FROM_REC_OFF(cache_ptr, record_offset) 				\
	DCR_ROFF_TO_RELE(cache_ptr, record_offset)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
int main(argc, argv)
int    argc;
char **argv;
{
	int                return_code = DCR_SUCCESS;
	unsigned int       count_1;
   unsigned int       count_2;
	DCR_CONTROL  cache_control_data;
	DCR_CACHE         *cache_ptr;
	unsigned int       cache_index;
	void              *record_mmap_ptr;
	unsigned int       record_element;
	unsigned int       record_offset;
	unsigned int       entry_count;
	void              *entry_list;
	unsigned int       index_method;
	unsigned int       index_element;
	char               error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for the DCR macros\n");
	fprintf(stderr, "---- ------- --- --- --- ------\n\n");

	memset(&cache_control_data, '\0', sizeof(cache_control_data));

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "Help request with '%s' noted . . .\n\n",
				argv[count_1]);
			fprintf(stderr, "USAGE:\n   %s %s\n\n", argv[0], "<cache-name>");
			goto EXIT_FUNCTION;
		}
	}

	if (argc != 2) {
		sprintf(error_text, "%s (%s) --- use '-HELP' for help.",
			"Expected a command-line parameter", "the cache file name");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((return_code = DCR_AllocCacheControl(&cache_control_data,
		100, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Allocated the cache control structure.\n");

	if ((return_code = DCR_OpenRead(&cache_control_data, argv[1],
		50, 10000, 0, 0, &cache_ptr, &cache_index, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Opened cache '%s' (%u records).\n", argv[1],
		cache_ptr->record_count);

	if ((return_code = DCR_MapDataAndIndices(cache_ptr, error_text)) !=
		DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Mapped data area and %u indices for cache.\n",
		cache_ptr->index_count);

	printf("%s %s %s %s\n",
		"*********************************", "**********", "*", "**********");
	printf("%-32.32s: %10lu / 0X%08lX\n", "Cache Size",
		cache_ptr->total_cache_size,
		cache_ptr->total_cache_size);
	printf("%-32.32s: %10lu / 0X%08lX\n", "Header Area Size",
		cache_ptr->header_area_size,
		cache_ptr->header_area_size);
	printf("%-32.32s: %10lu / 0X%08lX\n", "Data Area Offset",
		cache_ptr->data_area_offset,
		cache_ptr->data_area_offset);
	printf("%-32.32s: %10lu / 0X%08lX\n", "Data Area Size",
		cache_ptr->data_area_size,
		cache_ptr->data_area_size);
	printf("%-32.32s: %10lu / 0X%08lX\n", "Complete Index Area Offset",
		cache_ptr->index_area_offset,
		cache_ptr->index_area_offset);
	printf("%-32.32s: %10lu / 0X%08lX\n", "Complete Index Area Size",
		cache_ptr->index_area_size,
		cache_ptr->index_area_size);
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		printf("%s %s %s %s\n",
			"---------------------------------", "----------", "-",
			"----------");
		sprintf(error_text, "Index %u Area Offset", count_1);
		printf("%-32.32s: %10lu / 0X%08lX\n", error_text,
			cache_ptr->index_data_list[count_1].index_entry_offset,
			cache_ptr->index_data_list[count_1].index_entry_offset);
		sprintf(error_text, "Index %u Area Size", count_1);
		printf("%-32.32s: %10lu / 0X%08lX\n", error_text,
			cache_ptr->index_data_list[count_1].index_entry_size,
			cache_ptr->index_data_list[count_1].index_entry_size);
		sprintf(error_text, "Index %u Area Pointer", count_1);
		printf("%-32.32s: %10lu / 0X%08lX\n", error_text,
			((unsigned long) DCR_INDEX_AREA_PTR(cache_ptr, count_1)),
			((unsigned long) DCR_INDEX_AREA_PTR(cache_ptr, count_1)));
		sprintf(error_text, "Index %u Entry Size", count_1);
		printf("%-32.32s: %10lu / 0X%08lX\n", error_text,
			DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1),
			DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1));
	}
	printf("%s %s %s %s\n",
		"---------------------------------", "----------", "-", "----------");
	printf("%-32.32s: %10lu / 0X%08lX\n", "Total Record Size",
		cache_ptr->total_record_size,
		cache_ptr->total_record_size);
	printf("%s %s %s %s\n",
		"*********************************", "**********", "*", "**********");
	printf("\n");

	printf("%s %s %s %s\n",
		"=================================", "==========", "=", "==========");

	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		for (count_2 = 0; count_2 < cache_ptr->record_count; count_2++) {
			index_method    = count_1;
			index_element   = count_2;
			entry_count     = cache_ptr->record_count;
			entry_list      =
				cache_ptr->index_data_list[index_method].mmap_ptr;
			record_mmap_ptr = ((void *) cache_ptr->mmap_ptr);
			record_element  = (DCR_INDEX_ENTRY_REC_OFF(cache_ptr,
				index_method, entry_count,	entry_list, index_element) -
				cache_ptr->data_area_offset) /
				cache_ptr->total_record_size;
			record_offset   = cache_ptr->data_area_offset +
				(cache_ptr->total_record_size * record_element);
			printf("%-32.32s: %10lu / 0X%08lX\n", "index_method",
				((unsigned long) index_method),
				((unsigned long) index_method));
			printf("%-32.32s: %10lu / 0X%08lX\n", "index_element",
				((unsigned long) index_element),
				((unsigned long) index_element));
			printf("%-32.32s: %10lu / 0X%08lX\n", "record_element",
				((unsigned long) record_element),
				((unsigned long) record_element));
			printf("%-32.32s: %10lu / 0X%08lX\n", "record_offset",
				((unsigned long) record_offset),
				((unsigned long) record_offset));
			printf("%-32.32s: %10lu / 0X%08lX\n", "entry_count",
				((unsigned long) entry_count),
				((unsigned long) entry_count));
			printf("%-32.32s: %10lu / 0X%08lX\n", "entry_list",
				((unsigned long) entry_list),
				((unsigned long) entry_list));
			printf("%-32.32s: %10lu / 0X%08lX\n", "record_mmap_ptr",
				((unsigned long) record_mmap_ptr),
				((unsigned long) record_mmap_ptr));
			printf("%s %s %s %s\n",
				"---------------------------------", "----------", "-",
				"----------");
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_RELE_TO_RPTR_P",
				((unsigned long) DCR_RELE_TO_RPTR_P(cache_ptr,
				record_mmap_ptr, record_element)),
				((unsigned long) DCR_RELE_TO_RPTR_P(cache_ptr,
				record_mmap_ptr, record_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_ROFF_TO_RPTR_P",
				((unsigned long) DCR_ROFF_TO_RPTR_P(cache_ptr,
				record_mmap_ptr, record_offset)),
				((unsigned long) DCR_ROFF_TO_RPTR_P(cache_ptr,
				record_mmap_ptr, record_offset)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_ROFF_TO_RELE_P",
				((unsigned long) DCR_ROFF_TO_RELE_P(cache_ptr,
				record_offset)),
				((unsigned long) DCR_ROFF_TO_RELE_P(cache_ptr,
				record_offset)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_IELE_TO_IPTR_P",
				((unsigned long) DCR_IELE_TO_IPTR_P(cache_ptr,
				index_method, entry_count, entry_list, index_element)),
				((unsigned long) DCR_IELE_TO_IPTR_P(cache_ptr,
				index_method, entry_count, entry_list, index_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_IELE_TO_ROFF_P",
				((unsigned long) DCR_IELE_TO_ROFF_P(cache_ptr,
				index_method, entry_count, entry_list, index_element)),
				((unsigned long) DCR_IELE_TO_ROFF_P(cache_ptr,
				index_method, entry_count, entry_list, index_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_IELE_TO_RELE_P",
				((unsigned long) DCR_IELE_TO_RELE_P(cache_ptr,
				index_method, entry_count, entry_list, index_element)),
				((unsigned long) DCR_IELE_TO_RELE_P(cache_ptr,
				index_method, entry_count, entry_list, index_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_IELE_TO_RPTR_P",
				((unsigned long) DCR_IELE_TO_RPTR_P(cache_ptr,
				index_method, entry_count, entry_list, index_element,
				record_mmap_ptr)),
				((unsigned long) DCR_IELE_TO_RPTR_P(cache_ptr,
				index_method, entry_count, entry_list, index_element,
				record_mmap_ptr)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_RELE_TO_RPTR",
				((unsigned long) DCR_RELE_TO_RPTR(cache_ptr,
				record_element)),
				((unsigned long) DCR_RELE_TO_RPTR(cache_ptr,
				record_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_ROFF_TO_RPTR",
				((unsigned long) DCR_ROFF_TO_RPTR(cache_ptr,
				record_offset)),
				((unsigned long) DCR_ROFF_TO_RPTR(cache_ptr,
				record_offset)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_ROFF_TO_RELE",
				((unsigned long) DCR_ROFF_TO_RELE(cache_ptr,
				record_offset)),
				((unsigned long) DCR_ROFF_TO_RELE(cache_ptr,
				record_offset)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_IELE_TO_IPTR",
				((unsigned long) DCR_IELE_TO_IPTR(cache_ptr,
				index_method, index_element)),
				((unsigned long) DCR_IELE_TO_IPTR(cache_ptr,
				index_method, index_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_IELE_TO_ROFF",
				((unsigned long) DCR_IELE_TO_ROFF(cache_ptr,
				index_method, index_element)),
				((unsigned long) DCR_IELE_TO_ROFF(cache_ptr,
				index_method, index_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_IELE_TO_RELE",
				((unsigned long) DCR_IELE_TO_RELE(cache_ptr,
				index_method, index_element)),
				((unsigned long) DCR_IELE_TO_RELE(cache_ptr,
				index_method, index_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_IELE_TO_RPTR",
				((unsigned long) DCR_IELE_TO_RPTR(cache_ptr,
				index_method, index_element)),
				((unsigned long) DCR_IELE_TO_RPTR(cache_ptr,
				index_method, index_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_REC_OFF_FROM_IDX_ELE",
				((unsigned long) DCR_REC_OFF_FROM_IDX_ELE(cache_ptr,
				index_method, index_element)),
				((unsigned long) DCR_REC_OFF_FROM_IDX_ELE(cache_ptr,
				index_method, index_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_REC_ELE_FROM_IDX_ELE",
				((unsigned long) DCR_REC_ELE_FROM_IDX_ELE(cache_ptr,
				index_method, index_element)),
				((unsigned long) DCR_REC_ELE_FROM_IDX_ELE(cache_ptr,
				index_method, index_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_REC_PTR_FROM_IDX_ELE",
				((unsigned long) DCR_REC_PTR_FROM_IDX_ELE(cache_ptr,
				index_method, index_element)),
				((unsigned long) DCR_REC_PTR_FROM_IDX_ELE(cache_ptr,
				index_method, index_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_REC_PTR_FROM_REC_ELE",
				((unsigned long) DCR_REC_PTR_FROM_REC_ELE(cache_ptr,
				record_element)),
				((unsigned long) DCR_REC_PTR_FROM_REC_ELE(cache_ptr,
				record_element)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_REC_PTR_FROM_REC_OFF",
				((unsigned long) DCR_REC_PTR_FROM_REC_OFF(cache_ptr,
				record_offset)),
				((unsigned long) DCR_REC_PTR_FROM_REC_OFF(cache_ptr,
				record_offset)));
			printf("%-32.32s: %10lu / 0X%08lX\n",
				"DCR_REC_ELE_FROM_REC_OFF",
				((unsigned long) DCR_REC_ELE_FROM_REC_OFF(cache_ptr,
				record_offset)),
				((unsigned long) DCR_REC_ELE_FROM_REC_OFF(cache_ptr,
				record_offset)));
			printf("%s %s %s %s\n",
				"=================================", "==========", "=",
				"==========");
		}
	}

	printf("%s %s %s %s\n",
		"*********************************", "**********", "*", "**********");

EXIT_FUNCTION:

	DCR_CloseAllCaches(&cache_control_data);

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

