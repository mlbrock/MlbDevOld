/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets a list of cache records meeting the specified
								relational operator when compared to a key.

	Revision History	:	1994-07-19 --- Creation.
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

#include <memory.h>

#include "dcr.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_BasicGetList

	SYNOPSIS		:	return_code = DCR_BasicGetList(cache_ptr,
							index_method, record_align_cmp_ptr, index_align_cmp_ptr,
							compare_type, record_search_flag, entry_count,
							entry_list, record_list_type, in_record_ptr,
							max_record_count, out_count, out_list, error_text);

						int             return_code;

						unsigned int    index_method;

						GEN_ALIGN_CMP  *record_align_cmp_ptr;

						GEN_ALIGN_CMP  *index_align_cmp_ptr;

						unsigned int    compare_type;

						int             record_search_flag;

						unsigned int    entry_count;

						const void     *entry_list;

						int             record_list_type;

						const void     *in_record_ptr;

						unsigned int    max_record_count;

						unsigned int   *out_count;

						void          **out_list;

						char           *error_text;

	DESCRIPTION	:	Gets a list of cache records meeting the specified
						relational operator when compared to a key.

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
						the cache library, these flags at present have no effect.

						(.) ``entry_count`` is the number of index entries
						in the array to which the ``entry_list`` parameter points.

						(.) ``entry_list`` points to the list of index entries
						to be used in the search.

						(.) ``record_list_type`` specifies the type of record list
						to be returned by this function.

						(-) The following record list flags should be used:

						(..) ''DCR_GET_LIST_TYPE_RECORD'' to get a list of
						records as defined.

						(..) ''DCR_GET_LIST_TYPE_FULL'' to get a list of
						records which includes the flags and locking structure
						for each record.

						(..) ''DCR_GET_LIST_TYPE_ELE'' to get a list of
						elements of each of the records within the cache. To use
						such a list in the invoking function cast it to a pointer
						to ``unsigned int``.

						(..) ''DCR_GET_LIST_TYPE_OFF'' to get a list of
						offsets to each of the records within the cache. To use
						such a list in the invoking function cast it to a pointer
						to ``unsigned long``.

						(--) The offsets are from the beginning of the cache.

						(..) ''DCR_GET_LIST_TYPE_PTR'' to get a list of
						pointers to each of the records within the cache. To use
						such a list in the invoking function cast it to
						``void **``. If the data portion of the cache records
						represent a structure, cast it to ``structure **''.

						(--) The pointers are relative to the ``mmap()``ed pointer
						to the beginning of the cache. If the cache is re-mapped,
						the pointers will probably be invalidated.

						(-) Note that if the ``record_list_type`` parameter is not
						equal to one of the manifest constants specified above,
						no work will be performed by this function.

						(.) ``in_record_ptr`` points to the record containing the
						key for which the search is to be performed.

						(.) ``max_record_count`` is the maximum number of records
						to be returned by this function. If ``max_record_count`` is
						zero, all records meeting the criteria specified will be
						returned.

						(.) ``out_count`` points to an unsigned integer into which
						will be placed the number of records meeting the criteria
						specified.

						(.) ``out_list`` points to a pointer to ``void``. This
						function will allocate memory to store the list of any
						records meeting the criteria specified in that pointer.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) ''DCR_MEMORY_FAILURE'' if memory could not be allocated
						for the record list.

	NOTES			:	

	CAVEATS		:	This function assumes that the parameters passed to it are
						valid. It also assumes that any necessary mapping of
						various cache areas has been performed by the call.
						Application programmers may therefore find it more
						comfortable to call one of the high-level analogues to this
						function (``DCR_GetList``, ``DCR_GetListFull``,
						``DCR_GetListElement`` or ``DCR_GetListOffset``).

	SEE ALSO		:	DCR_GetList
						DCR Cache Compare Types
						DCR Cache Record Search Flags
						DCR Cache Record List Types

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_BasicGetList
						DCR Cache Get Functions:DCR_BasicGetList
						DCR Cache Functions:DCR_BasicGetList

	PUBLISH XREF:	DCR_BasicGetList

	PUBLISH NAME:	DCR_BasicGetList

EOH */
/* *********************************************************************** */
int DCR_BasicGetList(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_type, record_search_flag, entry_count,
	entry_list, record_list_type, in_record_ptr, max_record_count, out_count,
	out_list, error_text)
DCR_CACHE      *cache_ptr;
unsigned int    index_method;
GEN_ALIGN_CMP  *record_align_cmp_ptr;
GEN_ALIGN_CMP  *index_align_cmp_ptr;
unsigned int    compare_type;
int             record_search_flag;
unsigned int    entry_count;
const void     *entry_list;
int             record_list_type;
const void     *in_record_ptr;
unsigned int    max_record_count;
unsigned int   *out_count;
void          **out_list;
char           *error_text;
{
	int           return_code  = DCR_SUCCESS;
	unsigned int  record_count = 0;
	unsigned int  count_1;
	unsigned int  record_length;
   unsigned int  index_element;
	int           do_GT_flag;
	unsigned int  tmp_count;
	void         *tmp_list;
	void         *tmp_ptr;

	*out_count = 0;
	*out_list  = NULL;

	if ((entry_count) &&
		((record_list_type == DCR_GET_LIST_TYPE_RECORD) ||
		(record_list_type == DCR_GET_LIST_TYPE_FULL)    ||
		(record_list_type == DCR_GET_LIST_TYPE_ELE)     ||
		(record_list_type == DCR_GET_LIST_TYPE_OFF)  ||
		(record_list_type == DCR_GET_LIST_TYPE_PTR))) {
		record_length = (record_list_type == DCR_GET_LIST_TYPE_FULL) ?
			cache_ptr->total_record_size       :
			(record_list_type == DCR_GET_LIST_TYPE_RECORD) ?
			cache_ptr->actual_data_record_size :
			(record_list_type == DCR_GET_LIST_TYPE_ELE)    ?
			sizeof(unsigned int)               :
			(record_list_type == DCR_GET_LIST_TYPE_OFF) ?
			sizeof(unsigned long)              : sizeof(void *);
		if (compare_type != DCR_COMPARE_TYPE_NE) {
			if ((record_count = DCR_BasicGetCount(cache_ptr, index_method,
				record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
				DCR_FIND_TOP, record_search_flag, entry_count, entry_list,
				in_record_ptr, &index_element, NULL)) > 0) {
				record_count =
					(max_record_count && (record_count > max_record_count)) ?
					max_record_count : record_count;
				if ((*out_list = calloc(record_count, record_length)) == NULL) {
					sprintf(error_text,
						"%s (%u records * %u size = %u total bytes).",
						"Unable to allocate memory for a list of cache records",
						record_count, record_length, record_count * record_length);
					return_code = DCR_MEMORY_FAILURE;
				}
				else if (record_list_type == DCR_GET_LIST_TYPE_ELE) {
					*out_count = record_count;
					for (count_1 = 0; count_1 < record_count; count_1++)
						((unsigned int *) *out_list)[count_1] =
							DCR_IELE_TO_RELE_P(cache_ptr, index_method,
							entry_count, entry_list, index_element + count_1);
				}
				else if (record_list_type == DCR_GET_LIST_TYPE_OFF) {
					*out_count = record_count;
					for (count_1 = 0; count_1 < record_count; count_1++)
						((unsigned long *) *out_list)[count_1] =
							DCR_IELE_TO_ROFF_P(cache_ptr, index_method,
							entry_count, entry_list, index_element + count_1);
				}
				else if (record_list_type == DCR_GET_LIST_TYPE_PTR) {
					*out_count = record_count;
					for (count_1 = 0; count_1 < record_count; count_1++)
						(*((void ***) out_list))[count_1] =
							DCR_IELE_TO_RPTR_P(cache_ptr, index_method,
							entry_count, entry_list, index_element + count_1,
							cache_ptr->record_mmap_ptr);
				}
				else {
					*out_count = record_count;
					for (count_1 = 0; count_1 < record_count; count_1++) {
						memcpy(((char *) *out_list) + (count_1 * record_length),
							DCR_IELE_TO_RPTR_P(cache_ptr, index_method,
							entry_count, entry_list, index_element + count_1,
							cache_ptr->record_mmap_ptr), record_length);
					}
				}
			}
		}
		else if ((return_code = DCR_BasicGetList(cache_ptr, index_method,
			record_align_cmp_ptr, index_align_cmp_ptr, DCR_COMPARE_TYPE_LT,
			record_search_flag, entry_count, entry_list, record_list_type,
			in_record_ptr, max_record_count, out_count, out_list, error_text)) ==
			DCR_SUCCESS) {
			do_GT_flag        = ((!max_record_count) ||
				(max_record_count - record_count)) ? DCR_TRUE : DCR_FALSE;
			max_record_count -= (!max_record_count) ? 0 : record_count;
			if ((do_GT_flag == DCR_TRUE) &&
				((return_code = DCR_BasicGetList(cache_ptr, index_method,
				record_align_cmp_ptr, index_align_cmp_ptr,
				DCR_COMPARE_TYPE_GT, record_search_flag, entry_count,
				entry_list, record_list_type, in_record_ptr, max_record_count,
				&tmp_count, &tmp_list, error_text)) == DCR_SUCCESS) &&
				tmp_count) {
				if (!(*out_count)) {
					*out_count = tmp_count;
					*out_list  = tmp_list;
					tmp_count  = 0;
					tmp_list   = NULL;
				}
				else if ((tmp_ptr = realloc(*out_list, (*out_count + tmp_count) *
					record_length)) == NULL) {
					sprintf(error_text,
						"%s (%u records * %u size = %u total bytes).",
						"Unable to allocate memory for a list of cache records",
						(*out_count + tmp_count), record_length,
						(*out_count + tmp_count) * record_length);
					return_code = DCR_MEMORY_FAILURE;
				}
				else {
					memcpy(((char *) tmp_ptr) + (*out_count * record_length),
						tmp_list, tmp_count * record_length);
					*out_count += tmp_count;
					*out_list   = tmp_ptr;
				}
			}
			if (tmp_list != NULL)
				free(tmp_list);
			if ((return_code != DCR_SUCCESS) && (*out_list != NULL)) {
				free(*out_list);
				*out_count = 0;
				*out_list  = NULL;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetList

	SYNOPSIS		:	return_code = DCR_GetList(cache_ptr, index_method,
							record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
							record_search_flag, in_record_ptr, max_record_count,
							out_count, out_list, error_text);

						int             return_code;

						unsigned int    index_method;

						GEN_ALIGN_CMP  *record_align_cmp_ptr;

						GEN_ALIGN_CMP  *index_align_cmp_ptr;

						unsigned int    compare_type;

						int             record_search_flag;

						const void     *in_record_ptr;

						unsigned int    max_record_count;

						unsigned int   *out_count;

						void          **out_list;

						char           *error_text;

	DESCRIPTION	:	Gets a list of the data portion of cache records meeting
						the specified relational operator when compared to a key.

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

						(.) ``max_record_count`` is the maximum number of records
						to be returned by this function. If ``max_record_count`` is
						zero, all records meeting the criteria specified will be
						returned.

						(.) ``out_count`` points to an unsigned integer into which
						will be placed the number of records meeting the criteria
						specified.

						(.) ``out_list`` points to a pointer to ``void``. This
						function will allocate memory to store the list of any
						records meeting the criteria specified in that pointer.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR return codes on error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_BasicGetList
						DCR_GetListFull
						DCR_GetListElement
						DCR_GetListOffset
						DCR_GetListPointer
						DCR Cache Compare Types
						DCR Cache Record Search Flags
						DCR Cache Record List Types

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_GetList
						DCR Cache Get Functions:DCR_GetList
						DCR Cache Functions:DCR_GetList

	PUBLISH XREF:	DCR_GetList

	PUBLISH NAME:	DCR_GetList

EOH */
/* *********************************************************************** */
int DCR_GetList(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_type, record_search_flag, in_record_ptr,
	max_record_count, out_count, out_list, error_text)
DCR_CACHE      *cache_ptr;
unsigned int    index_method;
GEN_ALIGN_CMP  *record_align_cmp_ptr;
GEN_ALIGN_CMP  *index_align_cmp_ptr;
unsigned int    compare_type;
int             record_search_flag;
const void     *in_record_ptr;
unsigned int    max_record_count;
unsigned int   *out_count;
void          **out_list;
char           *error_text;
{
	int return_code;

	*out_count = 0;
	*out_list  = NULL;

	if ((return_code = DCR_ValidateCompareType(compare_type,
		error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_ValidateRecSearchFlag(record_search_flag,
			error_text)) == DCR_SUCCESS) {
			if ((return_code = DCR_MapDataAndIndex(cache_ptr, NULL, NULL,
				index_method, NULL, NULL, error_text)) == DCR_SUCCESS)
				return_code = DCR_BasicGetList(cache_ptr, index_method,
					record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
					record_search_flag, cache_ptr->record_count,
					DCR_INDEX_AREA_PTR(cache_ptr, index_method),
					DCR_GET_LIST_TYPE_RECORD, in_record_ptr,
					max_record_count, out_count, out_list, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetListFull

	SYNOPSIS		:	return_code = DCR_GetListFull(cache_ptr, index_method,
							record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
							record_search_flag, in_record_ptr, max_record_count,
							out_count, out_list, error_text);

						int             return_code;

						unsigned int    index_method;

						GEN_ALIGN_CMP  *record_align_cmp_ptr;

						GEN_ALIGN_CMP  *index_align_cmp_ptr;

						unsigned int    compare_type;

						int             record_search_flag;

						const void     *in_record_ptr;

						unsigned int    max_record_count;

						unsigned int   *out_count;

						void          **out_list;

						char           *error_text;

	DESCRIPTION	:	Gets a list of the complete cache records meeting the
						specified relational operator when compared to a key.

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

						(.) ``max_record_count`` is the maximum number of records
						to be returned by this function. If ``max_record_count`` is
						zero, all records meeting the criteria specified will be
						returned.

						(.) ``out_count`` points to an unsigned integer into which
						will be placed the number of records meeting the criteria
						specified.

						(.) ``out_list`` points to a pointer to ``void``. This
						function will allocate memory to store the list of any
						records meeting the criteria specified in that pointer.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR return codes on error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_BasicGetList
						DCR_GetList
						DCR_GetListElement
						DCR_GetListOffset
						DCR_GetListPointer
						DCR Cache Compare Types
						DCR Cache Record Search Flags
						DCR Cache Record List Types

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_GetListFull
						DCR Cache Get Functions:DCR_GetListFull
						DCR Cache Functions:DCR_GetListFull

	PUBLISH XREF:	DCR_GetListFull

	PUBLISH NAME:	DCR_GetListFull

EOH */
/* *********************************************************************** */
int DCR_GetListFull(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_type, record_search_flag, in_record_ptr,
	max_record_count, out_count, out_list, error_text)
DCR_CACHE      *cache_ptr;
unsigned int    index_method;
GEN_ALIGN_CMP  *record_align_cmp_ptr;
GEN_ALIGN_CMP  *index_align_cmp_ptr;
unsigned int    compare_type;
int             record_search_flag;
const void     *in_record_ptr;
unsigned int    max_record_count;
unsigned int   *out_count;
void          **out_list;
char           *error_text;
{
	int return_code;

	*out_count = 0;
	*out_list  = NULL;

	if ((return_code = DCR_ValidateCompareType(compare_type,
		error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_ValidateRecSearchFlag(record_search_flag,
			error_text)) == DCR_SUCCESS) {
			if ((return_code = DCR_MapDataAndIndex(cache_ptr, NULL, NULL,
				index_method, NULL, NULL, error_text)) == DCR_SUCCESS)
				return_code = DCR_BasicGetList(cache_ptr, index_method,
					record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
					record_search_flag, cache_ptr->record_count,
					DCR_INDEX_AREA_PTR(cache_ptr, index_method),
					DCR_GET_LIST_TYPE_FULL, in_record_ptr, max_record_count,
					out_count, out_list, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetListElement

	SYNOPSIS		:	return_code = DCR_GetListElement(cache_ptr,
							index_method, record_align_cmp_ptr, index_align_cmp_ptr,
							compare_type, record_search_flag, in_record_ptr,
							max_record_count, out_count, out_list, error_text);

						int             return_code;

						unsigned int    index_method;

						GEN_ALIGN_CMP  *record_align_cmp_ptr;

						GEN_ALIGN_CMP  *index_align_cmp_ptr;

						unsigned int    compare_type;

						int             record_search_flag;

						const void     *in_record_ptr;

						unsigned int    max_record_count;

						unsigned int   *out_count;

						unsigned int  **out_list;

						char           *error_text;

	DESCRIPTION	:	Gets a list of the record elements of cache records meeting
						the specified relational operator when compared to a key.

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

						(.) ``max_record_count`` is the maximum number of records
						to be returned by this function. If ``max_record_count`` is
						zero, all records meeting the criteria specified will be
						returned.

						(.) ``out_count`` points to an unsigned integer into which
						will be placed the number of records meeting the criteria
						specified.

						(.) ``out_list`` points to a pointer to ``unsigned int``.
						This function will allocate memory to store the list of
						record elements of any records meeting the criteria
						specified in that pointer.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR return codes on error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_BasicGetList
						DCR_GetList
						DCR_GetListFull
						DCR_GetListOffset
						DCR_GetListPointer
						DCR Cache Compare Types
						DCR Cache Record Search Flags
						DCR Cache Record List Types

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_GetListElement
						DCR Cache Get Functions:DCR_GetListElement
						DCR Cache Functions:DCR_GetListElement

	PUBLISH XREF:	DCR_GetListElement

	PUBLISH NAME:	DCR_GetListElement

EOH */
/* *********************************************************************** */
int DCR_GetListElement(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_type, record_search_flag, in_record_ptr,
	max_record_count, out_count, out_list, error_text)
DCR_CACHE      *cache_ptr;
unsigned int    index_method;
GEN_ALIGN_CMP  *record_align_cmp_ptr;
GEN_ALIGN_CMP  *index_align_cmp_ptr;
unsigned int    compare_type;
int             record_search_flag;
const void     *in_record_ptr;
unsigned int    max_record_count;
unsigned int   *out_count;
unsigned int  **out_list;
char           *error_text;
{
	int return_code;

	*out_count = 0;
	*out_list  = NULL;

	if ((return_code = DCR_ValidateCompareType(compare_type,
		error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_ValidateRecSearchFlag(record_search_flag,
			error_text)) == DCR_SUCCESS) {
			if ((return_code = DCR_MapDataAndIndex(cache_ptr, NULL, NULL,
				index_method, NULL, NULL, error_text)) == DCR_SUCCESS)
				return_code = DCR_BasicGetList(cache_ptr, index_method,
					record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
					record_search_flag, cache_ptr->record_count,
					DCR_INDEX_AREA_PTR(cache_ptr, index_method),
					DCR_GET_LIST_TYPE_ELE, in_record_ptr,
					max_record_count, out_count, ((void **) out_list), error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetListOffset

	SYNOPSIS		:	return_code = DCR_GetListOffset(cache_ptr,
							index_method, record_align_cmp_ptr, index_align_cmp_ptr,
							compare_type, record_search_flag, in_record_ptr,
							max_record_count, out_count, out_list, error_text);

						int             return_code;

						unsigned int    index_method;

						GEN_ALIGN_CMP  *record_align_cmp_ptr;

						GEN_ALIGN_CMP  *index_align_cmp_ptr;

						unsigned int    compare_type;

						int             record_search_flag;

						const void     *in_record_ptr;

						unsigned int    max_record_count;

						unsigned int   *out_count;

						unsigned long **out_list;

						char           *error_text;

	DESCRIPTION	:	Gets a list of the offsets of cache records meeting the
						specified relational operator when compared to a key.

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

						(.) ``max_record_count`` is the maximum number of records
						to be returned by this function. If ``max_record_count`` is
						zero, all records meeting the criteria specified will be
						returned.

						(.) ``out_count`` points to an unsigned integer into which
						will be placed the number of records meeting the criteria
						specified.

						(.) ``out_list`` points to a pointer to ``unsigned long``.
						This function will allocate memory to store the list of
						offsets of any records meeting the criteria specified in
						that pointer.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR return codes on error.

	NOTES			:	The offsets returned in the array ``out_list`` are relative
						to the data area of the cache. This value can be found in
						the ``data_area_offset`` member of the structure
						''DCR_CACHE''.

	CAVEATS		:	

	SEE ALSO		:	DCR_BasicGetList
						DCR_GetList
						DCR_GetListFull
						DCR_GetListElement
						DCR_GetListPointer
						DCR Cache Compare Types
						DCR Cache Record Search Flags
						DCR Cache Record List Types

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_GetListOffset
						DCR Cache Get Functions:DCR_GetListOffset
						DCR Cache Functions:DCR_GetListOffset

	PUBLISH XREF:	DCR_GetListOffset

	PUBLISH NAME:	DCR_GetListOffset

EOH */
/* *********************************************************************** */
int DCR_GetListOffset(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_type, record_search_flag, in_record_ptr,
	max_record_count, out_count, out_list, error_text)
DCR_CACHE      *cache_ptr;
unsigned int    index_method;
GEN_ALIGN_CMP  *record_align_cmp_ptr;
GEN_ALIGN_CMP  *index_align_cmp_ptr;
unsigned int    compare_type;
int             record_search_flag;
const void     *in_record_ptr;
unsigned int    max_record_count;
unsigned int   *out_count;
unsigned long **out_list;
char           *error_text;
{
	int return_code;

	*out_count = 0;
	*out_list  = NULL;

	if ((return_code = DCR_ValidateCompareType(compare_type,
		error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_ValidateRecSearchFlag(record_search_flag,
			error_text)) == DCR_SUCCESS) {
			if ((return_code = DCR_MapDataAndIndex(cache_ptr, NULL, NULL,
				index_method, NULL, NULL, error_text)) == DCR_SUCCESS)
				return_code = DCR_BasicGetList(cache_ptr, index_method,
					record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
					record_search_flag, cache_ptr->record_count,
					DCR_INDEX_AREA_PTR(cache_ptr, index_method),
					DCR_GET_LIST_TYPE_OFF, in_record_ptr,
					max_record_count, out_count, ((void **) out_list), error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetListPointer

	SYNOPSIS		:	return_code = DCR_GetListPointer(cache_ptr,
							index_method, record_align_cmp_ptr, index_align_cmp_ptr,
							compare_type, record_search_flag, in_record_ptr,
							max_record_count, out_count, out_list, error_text);

						int              return_code;

						unsigned int     index_method;

						GEN_ALIGN_CMP   *record_align_cmp_ptr;

						GEN_ALIGN_CMP   *index_align_cmp_ptr;

						unsigned int     compare_type;

						int              record_search_flag;

						const void      *in_record_ptr;

						unsigned int     max_record_count;

						unsigned int    *out_count;

						void          ***out_list;

						char            *error_text;

	DESCRIPTION	:	Gets a list of the offsets of cache records meeting the
						specified relational operator when compared to a key.

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

						(.) ``max_record_count`` is the maximum number of records
						to be returned by this function. If ``max_record_count`` is
						zero, all records meeting the criteria specified will be
						returned.

						(.) ``out_count`` points to an unsigned integer into which
						will be placed the number of records meeting the criteria
						specified.

						(.) ``out_list`` points to a pointer to ``void *``.
						This function will allocate memory to store the list of
						pointers to any records meeting the criteria specified in
						that pointer.

						(-) The pointers are relative to the ``mmap()``ed pointer
						to the beginning of the cache. If the cache is re-mapped,
						the pointers will probably be invalidated.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR return codes on error.

	NOTES			:	The offsets returned in the array ``out_list`` are relative
						to the data area of the cache. This value can be found in
						the ``data_area_offset`` member of the structure
						''DCR_CACHE''.

	CAVEATS		:	

	SEE ALSO		:	DCR_BasicGetList
						DCR_GetList
						DCR_GetListFull
						DCR_GetListElement
						DCR_GetListOffset
						DCR Cache Compare Types
						DCR Cache Record Search Flags
						DCR Cache Record List Types

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_GetListPointer
						DCR Cache Get Functions:DCR_GetListPointer
						DCR Cache Functions:DCR_GetListPointer

	PUBLISH XREF:	DCR_GetListPointer

	PUBLISH NAME:	DCR_GetListPointer

EOH */
/* *********************************************************************** */
int DCR_GetListPointer(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_type, record_search_flag, in_record_ptr,
	max_record_count, out_count, out_list, error_text)
DCR_CACHE       *cache_ptr;
unsigned int     index_method;
GEN_ALIGN_CMP   *record_align_cmp_ptr;
GEN_ALIGN_CMP   *index_align_cmp_ptr;
unsigned int     compare_type;
int              record_search_flag;
const void      *in_record_ptr;
unsigned int     max_record_count;
unsigned int    *out_count;
void          ***out_list;
char            *error_text;
{
	int return_code;

	*out_count = 0;
	*out_list  = NULL;

	if ((return_code = DCR_ValidateCompareType(compare_type,
		error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_ValidateRecSearchFlag(record_search_flag,
			error_text)) == DCR_SUCCESS) {
			if ((return_code = DCR_MapDataAndIndex(cache_ptr, NULL, NULL,
				index_method, NULL, NULL, error_text)) == DCR_SUCCESS)
				return_code = DCR_BasicGetList(cache_ptr, index_method,
					record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
					record_search_flag, cache_ptr->record_count,
					DCR_INDEX_AREA_PTR(cache_ptr, index_method),
					DCR_GET_LIST_TYPE_PTR, in_record_ptr, max_record_count,
					out_count, ((void **) out_list), error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

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
static int DoATest_1(DCR_CACHE *cache_ptr, int issue_key,
	unsigned int compare_type, unsigned int entry_count,
	const void *entry_list, char *error_text);
static int DoATest_2(DCR_CACHE *cache_ptr, int issue_key,
	unsigned int compare_type, unsigned int entry_count,
	const void *entry_list, char *error_text);
#else
static int DoATest_1();
static int DoATest_2();
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

	fprintf(stderr, "Test routine for 'DCR_BasicGetList()'\n");
	fprintf(stderr, "---- ------- --- --------------------------\n\n");

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
		for (count_2 = 0; count_2 < DCR_COMPARE_TYPE_COUNT; count_2++) {
			if ((return_code = DoATest_1(&cache_data, TestIssueKeyList[count_1],
				count_2, cache_data.record_count,
				cache_data.index_data_list[1].index_entry_list, error_text)) !=
				DCR_SUCCESS)
				goto EXIT_FUNCTION;
			if ((return_code = DoATest_2(&cache_data, TestIssueKeyList[count_1],
				count_2, cache_data.record_count,
				cache_data.index_data_list[1].index_entry_list, error_text)) !=
				DCR_SUCCESS)
				goto EXIT_FUNCTION;
		}
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

static int DoATest_1(cache_ptr, issue_key, compare_type, entry_count,
	entry_list, error_text)
DCR_CACHE    *cache_ptr;
int           issue_key;
unsigned int  compare_type;
unsigned int  entry_count;
const void   *entry_list;
char         *error_text;
{
	int           return_code;
	unsigned int  count_1;
	unsigned int  record_count;
	ISSUE_ID     *record_list;
	ISSUE_ID      tmp_issue_id;
	char          compare_type_name[DCR_MAX_COMPARE_TYPE_NAME + 1];
	char          buffer[100];

	tmp_issue_id.issue_key = issue_key;

	if ((return_code = DCR_BasicGetList(cache_ptr, 1, NULL, NULL,
		compare_type, DCR_RECORD_FLAG_ALL, entry_count, entry_list,
		DCR_GET_LIST_TYPE_RECORD, &tmp_issue_id, 0, &record_count,
		((void **) &record_list), error_text)) == DCR_SUCCESS) {
		sprintf(buffer, "Records %s issue key %2d",
			DCR_GetCmpTypeName(compare_type, compare_type_name),
			issue_key);
		printf(">>> %-42.42s: %u\n", buffer, record_count);
		for (count_1 = 0; count_1 < record_count; count_1++) {
			printf(">>> >>> ");
			PrintTestDataRow(record_list + count_1);
		}
		if (record_list != NULL)
			free(record_list);
		printf("===========================================================\n");
	}

	return(return_code);
}

static int DoATest_2(cache_ptr, issue_key, compare_type, entry_count,
	entry_list, error_text)
DCR_CACHE    *cache_ptr;
int           issue_key;
unsigned int  compare_type;
unsigned int  entry_count;
const void   *entry_list;
char         *error_text;
{
	int             return_code;
	unsigned int    count_1;
	unsigned int    record_count  = 0;
	ISSUE_ID       *record_list   = NULL;
	unsigned int    full_count    = 0;
	void           *full_list     = NULL;
	unsigned int    element_count = 0;
	unsigned int   *element_list  = NULL;
	unsigned int    offset_count  = 0;
	unsigned long  *offset_list   = NULL;
	unsigned int    pointer_count = 0;
   void          **pointer_list  = NULL;
	ISSUE_ID        tmp_issue_id;
	char            compare_type_name[DCR_MAX_COMPARE_TYPE_NAME + 1];
	char            buffer[100];
	char            tmp_error_text[DCR_MAX_ERROR_TEXT];

	tmp_issue_id.issue_key = issue_key;

	if ((return_code = DCR_BasicGetList(cache_ptr, 1, NULL, NULL,
		compare_type, DCR_RECORD_FLAG_ALL, entry_count, entry_list,
		DCR_GET_LIST_TYPE_RECORD, &tmp_issue_id, 0, &record_count,
		((void **) &record_list), tmp_error_text)) != DCR_SUCCESS)
		strcat(strcpy(error_text, "Error on RECORD list attempt: "),
			tmp_error_text);
	else if ((return_code = DCR_BasicGetList(cache_ptr, 1, NULL, NULL,
		compare_type, DCR_RECORD_FLAG_ALL, entry_count, entry_list,
		DCR_GET_LIST_TYPE_FULL, &tmp_issue_id, 0, &full_count,
		((void **) &full_list), tmp_error_text)) != DCR_SUCCESS)
		strcat(strcpy(error_text, "Error on FULL list attempt: "),
			tmp_error_text);
	else if ((return_code = DCR_BasicGetList(cache_ptr, 1, NULL, NULL,
		compare_type, DCR_RECORD_FLAG_ALL, entry_count, entry_list,
		DCR_GET_LIST_TYPE_ELE, &tmp_issue_id, 0, &element_count,
		((void **) &element_list), tmp_error_text)) != DCR_SUCCESS)
		strcat(strcpy(error_text, "Error on ELEMENT list attempt: "),
			tmp_error_text);
	else if ((return_code = DCR_BasicGetList(cache_ptr, 1, NULL, NULL,
		compare_type, DCR_RECORD_FLAG_ALL, entry_count, entry_list,
		DCR_GET_LIST_TYPE_OFF, &tmp_issue_id, 0, &offset_count,
		((void **) &offset_list), tmp_error_text)) != DCR_SUCCESS)
		strcat(strcpy(error_text, "Error on OFFSET list attempt: "),
			tmp_error_text);
	else if ((return_code = DCR_BasicGetList(cache_ptr, 1, NULL, NULL,
		compare_type, DCR_RECORD_FLAG_ALL, entry_count, entry_list,
		DCR_GET_LIST_TYPE_PTR, &tmp_issue_id, 0, &pointer_count,
		((void **) &pointer_list), tmp_error_text)) != DCR_SUCCESS)
		strcat(strcpy(error_text, "Error on PTR list attempt: "),
			tmp_error_text);
	else if (record_count != full_count) {
		sprintf(error_text, "RECORD count (%u) not equal to FULL count (%u).",
			record_count, full_count);
		return_code = DCR_FAILURE;
	}
	else if (full_count != element_count) {
		sprintf(error_text, "FULL count (%u) not equal to ELEMENT count (%u).",
			full_count, element_count);
		return_code = DCR_FAILURE;
	}
	else if (element_count != offset_count) {
		sprintf(error_text, "ELEMENT count (%u) not equal to OFFSET count (%u).",
			element_count, offset_count);
		return_code = DCR_FAILURE;
	}
	else if (offset_count != pointer_count) {
		sprintf(error_text, "OFFSET count (%u) not equal to PTR count (%u).",
			offset_count, pointer_count);
		return_code = DCR_FAILURE;
	}
	else {
		for (count_1 = 0; count_1 < record_count; count_1++) {
			if (memcmp(record_list + count_1, ((char *) full_list) +
				(cache_ptr->total_record_size * count_1),
				sizeof(record_list[0]))) {
				fprintf(stderr,
					"RECORD/FULL Difference (index %u).\n", count_1);
				strcpy(error_text, "List record differences encountered.");
				return_code = DCR_FAILURE;
			}
		}
		for (count_1 = 0; count_1 < record_count; count_1++) {
			if (memcmp(record_list + count_1, DCR_RELE_TO_RPTR(cache_ptr,
				element_list[count_1]), sizeof(record_list[0]))) {
				fprintf(stderr,
					"RECORD/ELEMENT Difference (index %u).\n", count_1);
				strcpy(error_text, "List record differences encountered.");
				return_code = DCR_FAILURE;
			}
		}
		for (count_1 = 0; count_1 < record_count; count_1++) {
			if (memcmp(record_list + count_1, ((char *) cache_ptr->mmap_ptr) +
				((unsigned int) offset_list[count_1]), sizeof(record_list[0]))) {
				fprintf(stderr,
					"RECORD/OFFSET Difference (index %u).\n", count_1);
				strcpy(error_text, "List record differences encountered.");
				return_code = DCR_FAILURE;
			}
		}
		for (count_1 = 0; count_1 < record_count; count_1++) {
			if (memcmp(record_list + count_1, pointer_list[count_1],
				sizeof(record_list[0]))) {
				fprintf(stderr,
					"RECORD/PTR Difference (index %u).\n", count_1);
				strcpy(error_text, "List record differences encountered.");
				return_code = DCR_FAILURE;
			}
		}
	}

	if (record_list != NULL)
		free(record_list);

	if (full_list != NULL)
		free(full_list);

	if (element_list != NULL)
		free(element_list);

	if (offset_list != NULL)
		free(offset_list);

	if (pointer_list != NULL)
		free(pointer_list);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

