/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the first or last cache record meeting the
								specified relational operator when compared to a key.

	Revision History	:	1994-07-20 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
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

	NAME			:	DCR_GetRelation

	SYNOPSIS		:	return_code = DCR_GetRelation(cache_ptr,
							index_method, record_align_cmp_ptr, index_align_cmp_ptr,
							compare_type, compare_anchor, record_search_flag,
							in_record_ptr, found_flag, out_index_element,
							out_record_element, error_text);

						int            return_code;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						unsigned int   compare_type;

						int            compare_anchor;

						int            record_search_flag;

						const void    *in_record_ptr;

						int           *found_flag;

						unsigned int  *out_index_element;

						unsigned long *out_record_element;

						char          *error_text;

	DESCRIPTION	:	Gets a the cache record meeting the criterion specified
						by a relational operator when compared to a key.

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

						(.) ``found_flag`` points to an integer into which will
						be placed the value of one of the following two manifest
						constants:

						(..) ''DCR_RECORD_NOT_FOUND'' if no matching record
						is found.

						(..) ''DCR_RECORD_FOUND'' if a matching record is
						found.

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

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_BasicGetCount
						DCR_GetEQ
						DCR_GetGE
						DCR_GetGT
						DCR_GetLE
						DCR_GetLT
						DCR_GetNE
						DCR Cache Compare Types
						DCR Cache Anchor Flags
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DCR_GetRelation
						DCR Cache Get Functions:DCR_GetRelation
						DCR Cache Functions:DCR_GetRelation

	PUBLISH XREF:	DCR_GetRelation

	PUBLISH NAME:	DCR_GetRelation

EOH */
/* *********************************************************************** */
int DCR_GetRelation(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_type, compare_anchor, record_search_flag,
	in_record_ptr, found_flag, out_index_element, out_record_element,
	error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
unsigned int   compare_type;
int            compare_anchor;
int            record_search_flag;
const void    *in_record_ptr;
int           *found_flag;
unsigned int  *out_index_element;
unsigned int  *out_record_element;
char          *error_text;
{
	int          return_code;
	unsigned int index_element;
	unsigned int record_element;

	*found_flag = DCR_RECORD_NOT_FOUND;

	if ((return_code = DCR_ValidateCompareType(compare_type,
		error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_ValidateRecSearchFlag(record_search_flag,
			error_text)) == DCR_SUCCESS) {
			if ((return_code = DCR_MapDataAndIndex(cache_ptr, NULL, NULL,
				index_method, NULL, NULL, error_text)) == DCR_SUCCESS) {
				if (DCR_BasicGetCount(cache_ptr, index_method,
					record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
					compare_anchor, record_search_flag, cache_ptr->record_count,
					DCR_INDEX_AREA_PTR(cache_ptr, index_method),
					in_record_ptr, &index_element, &record_element)) {
					cache_ptr->index_location_list[index_method].index_element    =
						index_element;
					cache_ptr->index_location_list[index_method].index_record_ptr =
						((unsigned long) record_element) *
						((unsigned long) cache_ptr->total_record_size);
					memcpy(cache_ptr->found_record_buffer,
						DCR_RELE_TO_RPTR(cache_ptr, record_element),
						cache_ptr->total_record_size);
					if (out_index_element != NULL)
						*out_index_element = index_element;
					if (out_record_element != NULL)
						*out_record_element = record_element;
					*found_flag = DCR_RECORD_FOUND;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetEQ

	SYNOPSIS		:	return_code = DCR_GetEQ(cache_ptr, index_method,
							record_align_cmp_ptr, index_align_cmp_ptr,
							compare_anchor, record_search_flag, in_record_ptr,
							found_flag, out_index_element, out_record_element,
							error_text);

						int            return_code;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						int            compare_anchor;

						int            record_search_flag;

						const void    *in_record_ptr;

						int           *found_flag;

						unsigned int  *out_index_element;

						unsigned long *out_record_element;

						char          *error_text;

	DESCRIPTION	:	Gets the first or last cache record equal to the
						specified key.

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

						(.) ``found_flag`` points to an integer into which will
						be placed the value of one of the following two manifest
						constants:

						(..) ''DCR_RECORD_NOT_FOUND'' if no matching record
						is found.

						(..) ''DCR_RECORD_FOUND'' if a matching record is
						found.

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

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_GetRelation
						DCR_GetGE
						DCR_GetGT
						DCR_GetLE
						DCR_GetLT
						DCR_GetNE
						DCR Cache Compare Types
						DCR Cache Anchor Flags
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DCR_GetEQ
						DCR Cache Get Functions:DCR_GetEQ
						DCR Cache Functions:DCR_GetEQ

	PUBLISH XREF:	DCR_GetEQ

	PUBLISH NAME:	DCR_GetEQ

EOH */
/* *********************************************************************** */
int DCR_GetEQ(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_anchor, record_search_flag, in_record_ptr,
	found_flag, out_index_element, out_record_element, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
int            compare_anchor;
int            record_search_flag;
const void    *in_record_ptr;
int           *found_flag;
unsigned int  *out_index_element;
unsigned int  *out_record_element;
char          *error_text;
{
	return(DCR_GetRelation(cache_ptr, index_method, record_align_cmp_ptr,
		index_align_cmp_ptr, DCR_COMPARE_TYPE_EQ, compare_anchor,
		record_search_flag, in_record_ptr, found_flag, out_index_element,
		out_record_element, error_text));
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetGE

	SYNOPSIS		:	return_code = DCR_GetGE(cache_ptr, index_method,
							record_align_cmp_ptr, index_align_cmp_ptr,
							compare_anchor, record_search_flag, in_record_ptr,
							found_flag, out_index_element, out_record_element,
							error_text);

						int            return_code;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						int            compare_anchor;

						int            record_search_flag;

						const void    *in_record_ptr;

						int           *found_flag;

						unsigned int  *out_index_element;

						unsigned long *out_record_element;

						char          *error_text;

	DESCRIPTION	:	Gets the first or last cache record greater that or equal
						to the specified key.

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

						(.) ``found_flag`` points to an integer into which will
						be placed the value of one of the following two manifest
						constants:

						(..) ''DCR_RECORD_NOT_FOUND'' if no matching record
						is found.

						(..) ''DCR_RECORD_FOUND'' if a matching record is
						found.

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

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_GetRelation
						DCR_GetEQ
						DCR_GetGT
						DCR_GetLE
						DCR_GetLT
						DCR_GetNE
						DCR Cache Compare Types
						DCR Cache Anchor Flags
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DCR_GetGE
						DCR Cache Get Functions:DCR_GetGE
						DCR Cache Functions:DCR_GetGE

	PUBLISH XREF:	DCR_GetGE

	PUBLISH NAME:	DCR_GetGE

EOH */
/* *********************************************************************** */
int DCR_GetGE(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_anchor, record_search_flag, in_record_ptr,
	found_flag, out_index_element, out_record_element, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
int            compare_anchor;
int            record_search_flag;
const void    *in_record_ptr;
int           *found_flag;
unsigned int  *out_index_element;
unsigned int  *out_record_element;
char          *error_text;
{
	return(DCR_GetRelation(cache_ptr, index_method, record_align_cmp_ptr,
		index_align_cmp_ptr, DCR_COMPARE_TYPE_GE, compare_anchor,
		record_search_flag, in_record_ptr, found_flag, out_index_element,
		out_record_element, error_text));
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetGT

	SYNOPSIS		:	return_code = DCR_GetGT(cache_ptr, index_method,
							record_align_cmp_ptr, index_align_cmp_ptr,
							compare_anchor, record_search_flag, in_record_ptr,
							found_flag, out_index_element, out_record_element,
							error_text);

						int            return_code;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						int            compare_anchor;

						int            record_search_flag;

						const void    *in_record_ptr;

						int           *found_flag;

						unsigned int  *out_index_element;

						unsigned long *out_record_element;

						char          *error_text;

	DESCRIPTION	:	Gets the first or last cache record greater than the
						specified key.

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

						(.) ``found_flag`` points to an integer into which will
						be placed the value of one of the following two manifest
						constants:

						(..) ''DCR_RECORD_NOT_FOUND'' if no matching record
						is found.

						(..) ''DCR_RECORD_FOUND'' if a matching record is
						found.

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

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_GetRelation
						DCR_GetEQ
						DCR_GetGE
						DCR_GetLE
						DCR_GetLT
						DCR_GetNE
						DCR Cache Compare Types
						DCR Cache Anchor Flags
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DCR_GetGT
						DCR Cache Get Functions:DCR_GetGT
						DCR Cache Functions:DCR_GetGT

	PUBLISH XREF:	DCR_GetGT

	PUBLISH NAME:	DCR_GetGT

EOH */
/* *********************************************************************** */
int DCR_GetGT(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_anchor, record_search_flag, in_record_ptr,
	found_flag, out_index_element, out_record_element, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
int            compare_anchor;
int            record_search_flag;
const void    *in_record_ptr;
int           *found_flag;
unsigned int  *out_index_element;
unsigned int  *out_record_element;
char          *error_text;
{
	return(DCR_GetRelation(cache_ptr, index_method, record_align_cmp_ptr,
		index_align_cmp_ptr, DCR_COMPARE_TYPE_GT, compare_anchor,
		record_search_flag, in_record_ptr, found_flag, out_index_element,
		out_record_element, error_text));
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetLE

	SYNOPSIS		:	return_code = DCR_GetLE(cache_ptr, index_method,
							record_align_cmp_ptr, index_align_cmp_ptr,
							compare_anchor, record_search_flag, in_record_ptr,
							found_flag, out_index_element, out_record_element,
							error_text);

						int            return_code;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						int            compare_anchor;

						int            record_search_flag;

						const void    *in_record_ptr;

						int           *found_flag;

						unsigned int  *out_index_element;

						unsigned long *out_record_element;

						char          *error_text;

	DESCRIPTION	:	Gets the first or last cache record less than or equal to
						the specified key.

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

						(.) ``found_flag`` points to an integer into which will
						be placed the value of one of the following two manifest
						constants:

						(..) ''DCR_RECORD_NOT_FOUND'' if no matching record
						is found.

						(..) ''DCR_RECORD_FOUND'' if a matching record is
						found.

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

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_GetRelation
						DCR_GetEQ
						DCR_GetGE
						DCR_GetGT
						DCR_GetLT
						DCR_GetNE
						DCR Cache Compare Types
						DCR Cache Anchor Flags
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DCR_GetLE
						DCR Cache Get Functions:DCR_GetLE
						DCR Cache Functions:DCR_GetLE

	PUBLISH XREF:	DCR_GetLE

	PUBLISH NAME:	DCR_GetLE

EOH */
/* *********************************************************************** */
int DCR_GetLE(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_anchor, record_search_flag, in_record_ptr,
	found_flag, out_index_element, out_record_element, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
int            compare_anchor;
int            record_search_flag;
const void    *in_record_ptr;
int           *found_flag;
unsigned int  *out_index_element;
unsigned int  *out_record_element;
char          *error_text;
{
	return(DCR_GetRelation(cache_ptr, index_method, record_align_cmp_ptr,
		index_align_cmp_ptr, DCR_COMPARE_TYPE_LE, compare_anchor,
		record_search_flag, in_record_ptr, found_flag, out_index_element,
		out_record_element, error_text));
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetLT

	SYNOPSIS		:	return_code = DCR_GetLT(cache_ptr, index_method,
							record_align_cmp_ptr, index_align_cmp_ptr,
							compare_anchor, record_search_flag, in_record_ptr,
							found_flag, out_index_element, out_record_element,
							error_text);

						int            return_code;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						int            compare_anchor;

						int            record_search_flag;

						const void    *in_record_ptr;

						int           *found_flag;

						unsigned int  *out_index_element;

						unsigned long *out_record_element;

						char          *error_text;

	DESCRIPTION	:	Gets the first or last cache record less than the
						specified key.

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

						(.) ``found_flag`` points to an integer into which will
						be placed the value of one of the following two manifest
						constants:

						(..) ''DCR_RECORD_NOT_FOUND'' if no matching record
						is found.

						(..) ''DCR_RECORD_FOUND'' if a matching record is
						found.

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

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_GetRelation
						DCR_GetEQ
						DCR_GetGE
						DCR_GetGT
						DCR_GetLE
						DCR_GetNE
						DCR Cache Compare Types
						DCR Cache Anchor Flags
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DCR_GetLT
						DCR Cache Get Functions:DCR_GetLT
						DCR Cache Functions:DCR_GetLT

	PUBLISH XREF:	DCR_GetLT

	PUBLISH NAME:	DCR_GetLT

EOH */
/* *********************************************************************** */
int DCR_GetLT(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_anchor, record_search_flag, in_record_ptr,
	found_flag, out_index_element, out_record_element, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
int            compare_anchor;
int            record_search_flag;
const void    *in_record_ptr;
int           *found_flag;
unsigned int  *out_index_element;
unsigned int  *out_record_element;
char          *error_text;
{
	return(DCR_GetRelation(cache_ptr, index_method, record_align_cmp_ptr,
		index_align_cmp_ptr, DCR_COMPARE_TYPE_LT, compare_anchor,
		record_search_flag, in_record_ptr, found_flag, out_index_element,
		out_record_element, error_text));
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetNE

	SYNOPSIS		:	return_code = DCR_GetNE(cache_ptr, index_method,
							record_align_cmp_ptr, index_align_cmp_ptr,
							compare_anchor, record_search_flag, in_record_ptr,
							found_flag, out_index_element, out_record_element,
							error_text);

						int            return_code;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						int            compare_anchor;

						int            record_search_flag;

						const void    *in_record_ptr;

						int           *found_flag;

						unsigned int  *out_index_element;

						unsigned long *out_record_element;

						char          *error_text;

	DESCRIPTION	:	Gets the first or last cache record not equal to the
						specified key.

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

						(.) ``found_flag`` points to an integer into which will
						be placed the value of one of the following two manifest
						constants:

						(..) ''DCR_RECORD_NOT_FOUND'' if no matching record
						is found.

						(..) ''DCR_RECORD_FOUND'' if a matching record is
						found.

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

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_GetRelation
						DCR_GetEQ
						DCR_GetGE
						DCR_GetGT
						DCR_GetLE
						DCR_GetLT
						DCR Cache Compare Types
						DCR Cache Anchor Flags
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DCR_GetNE
						DCR Cache Get Functions:DCR_GetNE
						DCR Cache Functions:DCR_GetNE

	PUBLISH XREF:	DCR_GetNE

	PUBLISH NAME:	DCR_GetNE

EOH */
/* *********************************************************************** */
int DCR_GetNE(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_anchor, record_search_flag, in_record_ptr,
	found_flag, out_index_element, out_record_element, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
int            compare_anchor;
int            record_search_flag;
const void    *in_record_ptr;
int           *found_flag;
unsigned int  *out_index_element;
unsigned int  *out_record_element;
char          *error_text;
{
	return(DCR_GetRelation(cache_ptr, index_method, record_align_cmp_ptr,
		index_align_cmp_ptr, DCR_COMPARE_TYPE_NE, compare_anchor,
		record_search_flag, in_record_ptr, found_flag, out_index_element,
		out_record_element, error_text));
}
/*	***********************************************************************	*/

