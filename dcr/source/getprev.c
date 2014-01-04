/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Finds the previous record in a cache for a specified
								index method.

	Revision History	:	1994-07-21 --- Creation.
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

	NAME			:	DCR_BasicGetPrevious

	SYNOPSIS		:	return_code = DCR_BasicGetPrevious(cache_ptr,
							index_method, record_search_flag, entry_count,
							entry_list, found_flag, out_index_element,
							out_record_element);

						int           return_code;

						DCR_CACHE    *cache_ptr;

						unsigned int  index_method;

						int           record_search_flag;

						unsigned int  entry_count;

						const void   *entry_list;

						int          *found_flag;

						unsigned int *out_index_element;

						unsigned int *out_record_element;

						char         *error_text;

	DESCRIPTION	:	Gets the previous record in a cache using the specified index
						method.

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

						(.) ``entry_list`` points to the list of index entries
						to be used in the search.

						(.) ``found_flag`` points to an integer into which will
						be placed the value of one of the following two manifest
						constants:

						(..) ''DCR_RECORD_NOT_FOUND'' if no matching record
						is found.

						(..) ''DCR_RECORD_FOUND'' if a matching record is
						found.

						(.) ``out_index_element`` points to an unsigned integer
						into which will be placed the number of the previous index
						element.

						(-) ``out_index_element`` may be ''NULL'', in which case
						no action is taken.

						(.) ``out_record_element`` points to an unsigned integer
						into which will be placed the number of the previous record
						element.

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

	CAVEATS		:	This function assumes that the parameters passed to it are
						valid. It also assumes that any necessary mapping of
						various cache areas has been performed by the call.
						Application programmers may therefore find it more
						comfortable to call the high-level analogue to this
						function (``DCR_GetPrevious``).

	SEE ALSO		:	DCR_GetPrevious
						DCR_BasicGetNext
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DCR_BasicGetPrevious
						DCR Cache Get Functions:DCR_BasicGetPrevious
						DCR Cache Functions:DCR_BasicGetPrevious

	PUBLISH XREF:	DCR_BasicGetPrevious

	PUBLISH NAME:	DCR_BasicGetPrevious

EOH */
/* *********************************************************************** */
int DCR_BasicGetPrevious(cache_ptr, index_method, record_search_flag,
	entry_count, entry_list, found_flag, out_index_element, out_record_element,
	error_text)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
int           record_search_flag;
unsigned int  entry_count;
const void   *entry_list;
int          *found_flag;
unsigned int *out_index_element;
unsigned int *out_record_element;
char         *error_text;
{
	int                       return_code = DCR_SUCCESS;
	DCR_INDEX_LOCATION *locate_ptr;

	*found_flag = DCR_RECORD_NOT_FOUND;
	locate_ptr  = cache_ptr->index_location_list + index_method;

	if (entry_count && locate_ptr->index_element) {
		if ((return_code = DCR_IndexEntryLocate(cache_ptr, index_method,
			entry_count, entry_list, error_text)) == DCR_SUCCESS) {
			if (locate_ptr->index_element < entry_count) {
				locate_ptr->index_element--;
				locate_ptr->index_record_ptr = DCR_IELE_TO_ROFF_P(cache_ptr,
					index_method, entry_count, entry_list,
					locate_ptr->index_element);
				memcpy(cache_ptr->found_record_buffer,
					DCR_ROFF_TO_RPTR(cache_ptr,
					locate_ptr->index_record_ptr), cache_ptr->total_record_size);
				if (out_index_element != NULL)
					*out_index_element = locate_ptr->index_element;
				if (out_record_element != NULL)
					*out_record_element = DCR_ROFF_TO_RELE(cache_ptr,
						locate_ptr->index_record_ptr);
				*found_flag = DCR_RECORD_FOUND;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetPrevious

	SYNOPSIS		:	return_code = DCR_GetPrevious(cache_ptr, index_method,
							record_search_flag, found_flag, out_index_element,
							out_record_element);

						int           return_code;

						DCR_CACHE    *cache_ptr;

						unsigned int  index_method;

						int           record_search_flag;

						int          *found_flag;

						unsigned int *out_index_element;

						unsigned int *out_record_element;

						char         *error_text;

	DESCRIPTION	:	Gets the previous record in a cache using the specified index
						method.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' in which are the records to be searched.

						(.) ``index_method`` is the index access path to be used
						to perform the search.

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

						(.) ``found_flag`` points to an integer into which will
						be placed the value of one of the following two manifest
						constants:

						(..) ''DCR_RECORD_NOT_FOUND'' if no matching record
						is found.

						(..) ''DCR_RECORD_FOUND'' if a matching record is
						found.

						(.) ``out_index_element`` points to an unsigned integer
						into which will be placed the number of the previous index
						element.

						(-) ``out_index_element`` may be ''NULL'', in which case
						no action is taken.

						(.) ``out_record_element`` points to an unsigned integer
						into which will be placed the number of the previous record
						element.

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

	SEE ALSO		:	DCR_BasicGetPrevious
						DCR_GetNext
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	DCR_GetPrevious
						DCR Cache Get Functions:DCR_GetPrevious
						DCR Cache Functions:DCR_GetPrevious

	PUBLISH XREF:	DCR_GetPrevious

	PUBLISH NAME:	DCR_GetPrevious

EOH */
/* *********************************************************************** */
int DCR_GetPrevious(cache_ptr, index_method, record_search_flag, found_flag,
	out_index_element, out_record_element, error_text)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
int           record_search_flag;
int          *found_flag;
unsigned int *out_index_element;
unsigned int *out_record_element;
char         *error_text;
{
	int return_code;

	*found_flag = DCR_RECORD_NOT_FOUND;

	if ((return_code = DCR_ValidateRecSearchFlag(record_search_flag,
		error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_MapDataAndIndex(cache_ptr, NULL, NULL,
			index_method, NULL, NULL, error_text)) == DCR_SUCCESS)
			return_code = DCR_BasicGetPrevious(cache_ptr, index_method,
				record_search_flag, cache_ptr->record_count,
				DCR_INDEX_AREA_PTR(cache_ptr, index_method), found_flag,
				out_index_element, out_record_element, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

