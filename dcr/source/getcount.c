/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the number of cache records meeting the
								specified relational operator when compared to a key.

	Revision History	:	1994-07-19 --- Creation.
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

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_BasicGetCount

	SYNOPSIS		:	element_count = DCR_BasicGetCount(cache_ptr,
							index_method, record_align_cmp_ptr, index_align_cmp_ptr,
							compare_type, compare_anchor, record_search_flag,
							entry_count, entry_list, in_record_ptr,
							out_index_element, out_record_element);

						unsigned int   element_count;

						DCR_CACHE     *cache_ptr;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						unsigned int   compare_type;

						int            compare_anchor;

						int            record_search_flag;

						unsigned int   entry_count;

						const void    *entry_list;

						const void    *in_record_ptr;

						unsigned int  *out_index_element;

						unsigned int  *out_record_element;

	DESCRIPTION	:	Determines the number of cache records meeting the specified
						relational operator when compared to a key.

						This function will also optionally return the element
						number of the index entry and/or the record number of the
						first or last record meeting the specified relational
						criterion.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' in which are the records to be searched.

						(.) ``index_method`` is the index access path to be used
						to perform the search.

						(-) Note that unlike the high-level cache ``get`` functions,
						this function does not check the validity of the
						``index_method`` parameter. Passing an invalid
						``index_method`` to this function can therefore result in
						Unix segmentation faults (or equivalents for your
						operating system).

						(.) ``record_align_cmp_ptr`` is a pointer to a structure of
						type ''GEN_ALIGN_CMP'' to be used to manage the comparison
						of record entries. It is of particular use in performing
						partial-key searches.

						(-) If you do not intend to perform a partial-key search,
						this parameter may be passed as ''NULL'', in which case
						the record alignment comparison data built-in to the cache
						for the index ``index_method`` will be used.

						(.) ``index_align_cmp_ptr`` is a pointer to a structure of
						type ''GEN_ALIGN_CMP'' to be used to manage the comparison
						of index entries. It is of particular use in performing
						partial-key searches.

						(-) If you do not intend to perform a partial-key search,
						this parameter may be passed as ''NULL'', in which case
						the index alignment comparison data built-in to the cache
						for the index ``index_method`` will be used.

						(.) ``compare_type`` specifies the relational operator to
						be applied in performing the search.

						(-) The following relational operators should be used:

						(..) ''DCR_COMPARE_TYPE_EQ'' to find records equal
						to the key.

						(..) ''DCR_COMPARE_TYPE_GE'' to find records greater
						than or equal to the key.

						(..) ''DCR_COMPARE_TYPE_GT'' to find records greater
						than the key.

						(..) ''DCR_COMPARE_TYPE_LE'' to find records less
						than or equal to the key.

						(..) ''DCR_COMPARE_TYPE_LT'' to find records less
						than the key.

						(..) ''DCR_COMPARE_TYPE_NE'' to find records not
						equal to the key.

						(-) Note that this function does not complain if it is
						passed an invalid ``compare_type`` parameter. You won't,
						however, find any records.

						(.) ``compare_anchor`` specifies the anchor point for the
						search. This determines whether the unsigned integer to
						which the ``out_index_element`` parameter points will be
						set to the first element meeting the relational criterion
						or the last element meeting the relational criterion.

						(-) The following cache anchor flags should be used:

						(..) ''DCR_FIND_TOP'' to anchor the returned element
						at the top of the records meeting the relational criterion.

						(..) ''DCR_FIND_BOTTOM'' to anchor the returned
						element at the bottom of the records meeting the relational
						criterion.

						(-) Note that if ``compare_anchor`` is not equal to one of
						manifest constants listed above, it will be coerced to the
						value represented by the manifest constant
						''DCR_FIND_TOP''.

						(.) ``record_search_flag`` specifies the record search
						flags which are to be applied to the search.

						(-) The following record search flags should be used:

						(..) ''DCR_RECORD_FLAG_ALL'' to apply the search to
						all records in the cache.

						(..) ''DCR_RECORD_FLAG_KEPT'' to apply the search
						only to records in the cache which have not been deleted.

						(..) ''DCR_RECORD_FLAG_DELETED'' to apply the search
						only to records in the cache which have been deleted.

						(-) Note that because the functionality needed to implement
						fully record deletion is not in place in this version of
						cache library, these flags at present have no effect.

						(.) ``entry_count`` is the number of index entries
						in the array to which the ``entry_list`` parameter points.

						(.) ``entry_list`` points to the list of index entries to
						be used in the search.

						(.) ``in_record_ptr`` points to the record containing the
						key for which the search is to be performed.

						(.) ``out_index_element`` points to an unsigned integer
						into which will be placed the number of the first (or last)
						index element meeting the specified criteria.

						(-) ``out_index_element`` may be ''NULL'', in which case
						no action is taken.

						(.) ``out_record_element`` points to an unsigned integer
						into which will be placed the number of the first (or last)
						record element meeting the specified criteria.

						(-) ``out_record_element`` may be ''NULL'', in which case
						no action is taken.

   RETURNS     :  Returns the number of records having the relationship
						specified by the ``compare_type`` relational operator
						parameter to the ``in_record_ptr`` key parameter.

	NOTES			:	This function supports the relational operation
						``not equal``, but in a fashion different from the
						other relational operators because said operation does not
						result in a continuous block of records in the case where
						records which compare ``equal`` are in the middle of the
						cache. The application can not, therefore, traverse the 
						record list starting at the element indicated by the
						``out_index_element`` and be sure of getting records not
						equal to the key.

						In order to determine which records are ``not equal`` to a
						particular key, the application programmer should invoke
						this function twice: the first time to determine which
						records are ``less than`` the key, and the second time to
						determine which records are ``greater than`` the key. An
						example of this technique can be found in the function
						``DCR_BasicGetList``.

	CAVEATS		:	This function assumes that the parameters passed to it are
						valid. It also assumes that any necessary mapping of
						various cache areas has been performed by the call.
						Application programmers may therefore find it more
						comfortable to call the high-level analogue to this
						function (``DCR_GetCount``).

	SEE ALSO		:	DCR_GetCount
						DCR Cache Compare Types
						DCR Cache Anchor Flags
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

	OUTPUT INDEX:	DCR_BasicGetCount
						DCR Cache Get Functions:DCR_BasicGetCount
						DCR Cache Functions:DCR_BasicGetCount

	PUBLISH XREF:	DCR_BasicGetCount

	PUBLISH NAME:	DCR_BasicGetCount

EOH */
/* *********************************************************************** */
unsigned int DCR_BasicGetCount(cache_ptr, index_method,
	record_align_cmp_ptr, index_align_cmp_ptr, compare_type, compare_anchor,
	record_search_flag, entry_count, entry_list, in_record_ptr,
	out_index_element, out_record_element)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
unsigned int   compare_type;
int            compare_anchor;
int            record_search_flag;
unsigned int   entry_count;
const void    *entry_list;
const void    *in_record_ptr;
unsigned int  *out_index_element;
unsigned int  *out_record_element;
{
	unsigned int element_count = 0;
	unsigned int index_element;
	unsigned int tmp_index;
	unsigned int tmp_count;

	if (entry_count) {
		compare_anchor = ((compare_anchor != DCR_FIND_TOP) &&
			(compare_anchor != DCR_FIND_BOTTOM)) ? DCR_FIND_TOP :
			compare_anchor;
		switch (compare_type) {
			case DCR_COMPARE_TYPE_EQ	:
				if (DCR_Find(cache_ptr, index_method, record_align_cmp_ptr,
					index_align_cmp_ptr, in_record_ptr, entry_count, entry_list,
					DCR_FIND_TOP, &index_element, NULL, NULL, NULL) ==
					DCR_RECORD_FOUND) {
					DCR_Find(cache_ptr, index_method, record_align_cmp_ptr,
						index_align_cmp_ptr, in_record_ptr, entry_count, entry_list,
						DCR_FIND_BOTTOM, &element_count, NULL, NULL, NULL);
						element_count = (element_count - index_element) + 1;
				}
				break;
			case DCR_COMPARE_TYPE_GE	:
				if (DCR_Find(cache_ptr, index_method, record_align_cmp_ptr,
					index_align_cmp_ptr, in_record_ptr, entry_count, entry_list,
					DCR_FIND_TOP, &index_element, NULL, NULL, NULL) ==
					DCR_RECORD_FOUND)
					element_count = entry_count - index_element;
				else if (index_element < entry_count)
					element_count = entry_count - index_element;
				break;
			case DCR_COMPARE_TYPE_GT	:
				if (DCR_Find(cache_ptr, index_method, record_align_cmp_ptr,
					index_align_cmp_ptr, in_record_ptr, entry_count, entry_list,
					DCR_FIND_BOTTOM, &index_element, NULL, NULL, NULL) ==
					DCR_RECORD_FOUND) {
					if (index_element < entry_count) {
						index_element++;
						element_count = entry_count - index_element;
					}
				}
				else if (index_element < entry_count)
					element_count = entry_count - index_element;
				break;
			case DCR_COMPARE_TYPE_LE	:
				if (DCR_Find(cache_ptr, index_method, record_align_cmp_ptr,
					index_align_cmp_ptr, in_record_ptr, entry_count, entry_list,
					DCR_FIND_BOTTOM, &index_element, NULL, NULL, NULL) ==
					DCR_RECORD_FOUND) {
					element_count = index_element + 1;
					index_element = 0;
				}
				else if (index_element) {
					element_count = index_element;
					index_element = 0;
				}
				break;
			case DCR_COMPARE_TYPE_LT	:
				if (DCR_Find(cache_ptr, index_method, record_align_cmp_ptr,
					index_align_cmp_ptr, in_record_ptr, entry_count, entry_list,
					DCR_FIND_TOP, &index_element, NULL, NULL, NULL) ==
					DCR_RECORD_FOUND) {
					if (index_element) {
						element_count = index_element;
						index_element = 0;
					}
				}
				else if (index_element) {
					element_count = index_element;
					index_element = 0;
				}
				break;
			case DCR_COMPARE_TYPE_NE	:
				if ((element_count = DCR_BasicGetCount(cache_ptr,
					index_method, record_align_cmp_ptr, index_align_cmp_ptr,
					DCR_COMPARE_TYPE_GT, compare_anchor, record_search_flag,
					entry_count, entry_list, in_record_ptr, &index_element,
					NULL)) > 0)
					index_element = (compare_anchor == DCR_FIND_TOP) ?
						index_element : ((index_element + element_count) - 1);
				if ((tmp_count = DCR_BasicGetCount(cache_ptr, index_method,
					record_align_cmp_ptr, index_align_cmp_ptr,
					DCR_COMPARE_TYPE_LT, compare_anchor, record_search_flag,
					entry_count, entry_list, in_record_ptr, &tmp_index,
					NULL)) > 0) {
					element_count += tmp_count;
					index_element  = (compare_anchor == DCR_FIND_TOP) ?
						tmp_index : ((tmp_index + tmp_count) - 1);
				}
				break;
			default									:
				break;
		}
		if (element_count) {
			if (out_index_element != NULL)
				*out_index_element = ((compare_anchor == DCR_FIND_TOP) ||
					(compare_type == DCR_COMPARE_TYPE_NE)) ? index_element :
					((index_element + element_count) - 1);
			if (out_record_element != NULL)
				*out_record_element = DCR_IELE_TO_RELE_P(cache_ptr,
					index_method, entry_count, entry_list, index_element);
		}
	}

	return(element_count);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetCount

	SYNOPSIS		:	return_code = DCR_GetCount(cache_ptr, index_method,
							record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
							compare_anchor, record_search_flag, in_record_ptr,
							out_count, out_index_element, out_record_element,
							error_text);

						int            return_code;

						DCR_CACHE     *cache_ptr;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						unsigned int   compare_type;

						int            compare_anchor;

						int            record_search_flag;

						const void    *in_record_ptr;

						unsigned int  *out_count;

						unsigned int  *out_index_element;

						unsigned int  *out_record_element;

						char          *error_text;

	DESCRIPTION	:	Determines the number of cache records meeting the specified
						relational operator when compared to a key.

						This function will also optionally return the element
						number of the index entry and/or the record number of the
						first or last record meeting the specified relational
						criterion.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' in which are the records to be searched.

						(.) ``index_method`` is the index access path to be used
						to perform the search.

						(.) ``record_align_cmp_ptr`` is a pointer to a structure of
						type ''GEN_ALIGN_CMP'' to be used to manage the comparison
						of record entries. It is of particular use in performing
						partial-key searches.

						(-) If you do not intend to perform a partial-key search,
						this parameter may be passed as ''NULL'', in which case
						the record alignment comparison data built-in to the cache
						for the index ``index_method`` will be used.

						(.) ``index_align_cmp_ptr`` is a pointer to a structure of
						type ''GEN_ALIGN_CMP'' to be used to manage the comparison
						of index entries. It is of particular use in performing
						partial-key searches.

						(-) If you do not intend to perform a partial-key search,
						this parameter may be passed as ''NULL'', in which case
						the index alignment comparison data built-in to the cache
						for the index ``index_method`` will be used.

						(.) ``compare_type`` specifies the relational operator to
						be applied in performing the search.

						(-) The following relational operators should be used:

						(..) ''DCR_COMPARE_TYPE_EQ'' to find records equal
						to the key.

						(..) ''DCR_COMPARE_TYPE_GE'' to find records greater
						than or equal to the key.

						(..) ''DCR_COMPARE_TYPE_GT'' to find records greater
						than the key.

						(..) ''DCR_COMPARE_TYPE_LE'' to find records less
						than or equal to the key.

						(..) ''DCR_COMPARE_TYPE_LT'' to find records less
						than the key.

						(..) ''DCR_COMPARE_TYPE_NE'' to find records not
						equal to the key.

						(.) ``compare_anchor`` specifies the anchor point for the
						search. This determines whether the unsigned integer to
						which the ``out_index_element`` parameter points will be
						set to the first element meeting the relational criterion
						or the last element meeting the relational criterion.

						(-) The following cache anchor flags should be used:

						(..) ''DCR_FIND_TOP'' to anchor the returned element
						at the top of the records meeting the relational criterion.

						(..) ''DCR_FIND_BOTTOM'' to anchor the returned
						element at the bottom of the records meeting the relational
						criterion.

						(-) Note that if ``compare_anchor`` is not equal to one of
						manifest constants listed above, it will be coerced to the
						value represented by the manifest constant
						''DCR_FIND_TOP''.

						(.) ``record_search_flag`` specifies the record search
						flags which are to be applied to the search.

						(-) The following record search flags should be used:

						(..) ''DCR_RECORD_FLAG_ALL'' to apply the search to
						all records in the cache.

						(..) ''DCR_RECORD_FLAG_KEPT'' to apply the search
						only to records in the cache which have not been deleted.

						(..) ''DCR_RECORD_FLAG_DELETED'' to apply the search
						only to records in the cache which have been deleted.

						(-) Note that because the functionality needed to implement
						fully record deletion is not in place in this version of
						cache library, these flags at present have no effect. The
						value of this parameter is, however, subject to validation
						by this function.

						(.) ``in_record_ptr`` points to the record containing the
						key for which the search is to be performed.

						(.) ``out_count`` points to an unsigned integer into which
						will be placed the number of records meeting the criteria
						specified.

						(.) ``out_index_element`` points to an unsigned integer
						into which will be placed the number of the first (or last)
						index element meeting the specified criteria.

						(-) ``out_index_element`` may be ''NULL'', in which case
						no action is taken.

						(.) ``out_record_element`` points to an unsigned integer
						into which will be placed the number of the first (or last)
						record element meeting the specified criteria.

						(-) ``out_record_element`` may be ''NULL'', in which case
						no action is taken.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR return codes on error.

	NOTES			:	This function supports the relational operation
						``not equal``, but in a fashion different from the
						other relational operators because said operation does not
						result in a continuous block of records in the case where
						records which compare ``equal`` are in the middle of the
						cache. The application can not, therefore, traverse the 
						record list starting at the element indicated by the
						``out_index_element`` and be sure of getting records not
						equal to the key.

						In order to determine which records are ``not equal`` to a
						particular key, the application programmer should invoke
						this function twice: the first time to determine which
						records are ``less than`` the key, and the second time to
						determine which records are ``greater than`` the key. An
						example of this technique can be found in the function
						``DCR_GetList``.

	CAVEATS		:	

	SEE ALSO		:	DCR_BasicGetCount
						DCR Cache Compare Types
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

	OUTPUT INDEX:	DCR_GetCount
						DCR Cache Get Functions:DCR_GetCount
						DCR Cache Functions:DCR_GetCount

	PUBLISH XREF:	DCR_GetCount

	PUBLISH NAME:	DCR_GetCount

EOH */
/* *********************************************************************** */
int DCR_GetCount(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_type, compare_anchor, record_search_flag,
	in_record_ptr, out_count, out_index_element, out_record_element,
	error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
unsigned int   compare_type;
int            compare_anchor;
int            record_search_flag;
const void    *in_record_ptr;
unsigned int  *out_count;
unsigned int  *out_index_element;
unsigned int  *out_record_element;
char          *error_text;
{
	int          return_code;
	unsigned int index_element;
	unsigned int record_element;

	if ((return_code = DCR_ValidateCompareType(compare_type,
		error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_ValidateRecSearchFlag(record_search_flag,
			error_text)) == DCR_SUCCESS) {
			if ((return_code = DCR_MapDataAndIndex(cache_ptr, NULL, NULL,
				index_method, NULL, NULL, error_text)) == DCR_SUCCESS) {
				if ((*out_count = DCR_BasicGetCount(cache_ptr, index_method,
					record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
					compare_anchor, record_search_flag, cache_ptr->record_count,
					DCR_INDEX_AREA_PTR(cache_ptr, index_method),
					in_record_ptr, &index_element, &record_element)) > 0) {
					if (out_index_element != NULL)
						*out_index_element = index_element;
					if (out_record_element != NULL)
						*out_record_element = record_element;
				}
			}
		}
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

#include <memory.h>
#include <string.h>

#ifndef NARGS
int main(void);
#else
int main();
#endif /* #ifndef NARGS */

#ifndef NARGS
static void DoATest(DCR_CACHE *cache_ptr, int issue_key,
	unsigned int compare_type, unsigned int entry_count,
	const void *entry_list);
#else
static void DoATest();
#endif /* #ifndef NARGS */

#include "datatest.h"						/* For the test meta-data . . .		*/

static int          TestIssueKeyList[] = { 1, 12, 13, 20, 21, 99 };

static unsigned int TestIssueKeyCount  =
	sizeof(TestIssueKeyList) / sizeof(TestIssueKeyList[0]);

int main()
{
	int                return_code;
	unsigned int       count_1;
	unsigned int       count_2;
	DCR_HEADER  *cache_header_ptr = NULL;
	char              *data_list        = NULL;
	void             **index_list       = NULL;
	DCR_CACHE          cache_data;
	char               error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'DCR_BasicGetCount()'\n");
	fprintf(stderr, "---- ------- --- ---------------------------\n\n");

	memset(&cache_data, '\0', sizeof(cache_data));

	if ((return_code = DCR_MakeHeader("TEST_CACHE_NAME",
		"TEST_SERVER,TEST_DB,TEST_OWNER,mlds,mlds", "TEST_SERVER",
		"TEST_DB", "TEST_OWNER", "mlds", "mlds", "TEST_TABLE", 4096, 4096,
		DCR_FALSE, MemberCount, MemberList, 0, NULL,
		IndexSpecCount, IndexSpecList, &cache_header_ptr, error_text)) !=
		DCR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = DCR_AllocCache(&cache_data, cache_header_ptr,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	cache_header_ptr->record_count = DataCount;
	DCR_BindHeader(&cache_data, cache_header_ptr);

	if ((data_list = ((char *) calloc(cache_data.record_count,
		cache_data.total_record_size))) == NULL) {
		sprintf(error_text, "%s (%u elements * %u size = %u total bytes).",
			"Unable to allocate the complete record lists",
			cache_data.record_count, cache_data.total_record_size,
			cache_data.record_count * cache_data.total_record_size);
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	cache_data.data_area_offset = 0L;
	cache_data.mmap_ptr         = data_list;
	cache_data.record_mmap_ptr  = data_list;

	for (count_1 = 0; count_1 < cache_data.record_count; count_1++)
		memcpy(data_list + (count_1 * cache_data.total_record_size),
			DataList + count_1, sizeof(DataList[0]));

	if ((index_list = ((void **) calloc(cache_data.index_count,
		sizeof(void **)))) == NULL) {
		sprintf(error_text, "%s (%u indices * %u size = %u total bytes).",
			"Unable to allocate the array of pointers to index lists",
			cache_data.index_count, sizeof(void *),
			cache_data.index_count * sizeof(void *));
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
		if ((index_list[count_1] = calloc(cache_data.record_count,
			DCR_INDEX_ENTRY_SIZE(&cache_data, count_1))) == NULL) {
			sprintf(error_text,
				"%s %u (%u records * %u size = %u total bytes).",
				"Unable to allocate index list number", count_1,
				cache_data.record_count,
				DCR_INDEX_ENTRY_SIZE(&cache_data, count_1),
				cache_data.record_count *
				DCR_INDEX_ENTRY_SIZE(&cache_data, count_1));
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Because we allocate memory for this test instead of using a	*/
	/*	memory-mapped file, we have to fix-up the index area offsets.	*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
		cache_data.index_list[count_1].index_area_offset       = 0L;
		cache_data.index_data_list[count_1].index_entry_offset = 0L;
		cache_data.index_data_list[count_1].index_entry_list   =
			index_list[count_1];
		cache_data.index_data_list[count_1].mmap_ptr           =
      	index_list[count_1];
	}
	/*	**************************************************************	*/

	DCR_IndexCache(&cache_data);

	printf("=======================================================\n");
	printf("Index Number %u (", 0);
	for (count_1 = 0; count_1 < cache_data.index_list[1].field_count;
		count_1++)
		printf("%s%s", cache_data.field_list[cache_data.
			index_field_list[cache_data.index_list[1].field_index + count_1]].
			db_column_name,
			(count_1 < (cache_data.index_list[1].field_count - 1)) ?
			", " : ")\n");
	printf("-------------------------------------------------------\n");
#ifndef NARGS
	if ((return_code = DCR_EmitData(&cache_data, 1, DCR_FALSE,
		DCR_TRUE, 0, 60, " ", "-", "\f", "", "\n", 0, NULL, NULL, NULL, NULL,
		((void (*)(void *, char *, ...)) fprintf), stdout,	error_text)) !=
		DCR_SUCCESS)
#else
	if ((return_code = DCR_EmitData(&cache_data, 1, DCR_FALSE,
		DCR_TRUE, 0, 60, " ", "-", "\f", "", "\n", 0, NULL, NULL, NULL, NULL,
		fprintf, stdout, error_text)) != DCR_SUCCESS)
#endif /* #ifndef NARGS */
		goto EXIT_FUNCTION;
	printf("=======================================================\n");

	return_code = DCR_CheckIndices(&cache_data, error_text);

	printf("*******************************************************\n");
	printf("*******************************************************\n");
	for (count_1 = 0; count_1 < TestIssueKeyCount; count_1++) {
		for (count_2 = 0; count_2 < DCR_COMPARE_TYPE_COUNT; count_2++)
			DoATest(&cache_data, TestIssueKeyList[count_1], count_2,
				cache_data.record_count,
				cache_data.index_data_list[1].index_entry_list);
		if (count_1 < (TestIssueKeyCount - 1))
			printf("*******************************************************\n");
	}
	printf("*******************************************************\n");
	printf("*******************************************************\n");

EXIT_FUNCTION:

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	if (data_list != NULL)
		free(data_list);

	if (index_list != NULL) {
		for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
			if (index_list[count_1] != NULL)
				free(index_list[count_1]);
		}
		free(index_list);
	}

	return(return_code);
}

static void DoATest(cache_ptr, issue_key, compare_type, entry_count,
	entry_list)
DCR_CACHE    *cache_ptr;
int           issue_key;
unsigned int  compare_type;
unsigned int  entry_count;
const void   *entry_list;
{
	ISSUE_ID     tmp_issue_id;
	char         compare_type_name[DCR_MAX_COMPARE_TYPE_NAME + 1];
	char         buffer[100];

	tmp_issue_id.issue_key = issue_key;

	sprintf(buffer, "Records %s issue key %2d",
		DCR_GetCmpTypeName(compare_type, compare_type_name),
		issue_key);
	printf(">>> %-42.42s: %u\n", buffer, DCR_BasicGetCount(cache_ptr, 1,
		NULL, NULL, compare_type, DCR_FIND_TOP, DCR_RECORD_FLAG_ALL,
		entry_count, entry_list, &tmp_issue_id, NULL, NULL));
}

#endif /* #ifdef TEST_MAIN */

