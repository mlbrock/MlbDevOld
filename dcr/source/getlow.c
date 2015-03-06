/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Finds the lowest record in a cache for a specified
								index method.

	Revision History	:	1994-07-21 --- Creation.
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

	NAME			:	DCR_BasicGetLowest

	SYNOPSIS		:	void DCR_BasicGetLowest(cache_ptr, index_method,
							record_search_flag, entry_count, entry_list, found_flag,
							out_index_element, out_record_element);

						DCR_CACHE    *cache_ptr;

						unsigned int  index_method;

						int           record_search_flag;

						unsigned int  entry_count;

						const void   *entry_list;

						int          *found_flag;

						unsigned int *out_index_element;

						unsigned int *out_record_element;

	DESCRIPTION	:	Gets the lowest record in a cache using the specified index
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
						into which will be placed the number of the lowest index
						element.

						(-) Because this function accesses the lowest record using
						the specified index method, ``out_index_element`` will
						always be set to zero (''0'').

						(-) ``out_index_element`` may be ''NULL'', in which case
						no action is taken.

						(.) ``out_record_element`` points to an unsigned integer
						into which will be placed the number of the lowest record
						element.

						(-) ``out_record_element`` may be ''NULL'', in which case
						no action is taken.

   RETURNS     :  Void.

	NOTES			:	

	CAVEATS		:	This function assumes that the parameters passed to it are
						valid. It also assumes that any necessary mapping of
						various cache areas has been performed by the call.
						Application programmers may therefore find it more
						comfortable to call the high-level analogue to this
						function (``DCR_GetLowest``).

	SEE ALSO		:	DCR_GetLowest
						DCR_BasicGetHighest
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_BasicGetLowest
						DCR Cache Get Functions:DCR_BasicGetLowest
						DCR Cache Functions:DCR_BasicGetLowest

	PUBLISH XREF:	DCR_BasicGetLowest

	PUBLISH NAME:	DCR_BasicGetLowest

EOH */
/* *********************************************************************** */
void DCR_BasicGetLowest(cache_ptr, index_method, record_search_flag,
	entry_count, entry_list, found_flag, out_index_element, out_record_element)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
int           record_search_flag;
unsigned int  entry_count;
const void   *entry_list;
int          *found_flag;
unsigned int *out_index_element;
unsigned int *out_record_element;
{
	if (!entry_count)
		*found_flag = DCR_RECORD_NOT_FOUND;
	else {
		cache_ptr->index_location_list[index_method].index_element    = 0;
		cache_ptr->index_location_list[index_method].index_record_ptr =
			DCR_IELE_TO_ROFF_P(cache_ptr, index_method, entry_count,
			entry_list, 0);
		memcpy(cache_ptr->found_record_buffer, DCR_ROFF_TO_RPTR(cache_ptr,
			cache_ptr->index_location_list[index_method].index_record_ptr),
			cache_ptr->total_record_size);
		if (out_index_element != NULL)
			*out_index_element =
				cache_ptr->index_location_list[index_method].index_element;
		if (out_record_element != NULL)
			*out_record_element = DCR_ROFF_TO_RELE(cache_ptr,
				cache_ptr->index_location_list[index_method].index_record_ptr);
		*found_flag = DCR_RECORD_FOUND;
	}
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_GetLowest

	SYNOPSIS		:	return_code = DCR_GetLowest(cache_ptr, index_method,
							record_search_flag, found_flag, out_index_element,
							out_record_element);

						int           return_code;

						DCR_CACHE    *cache_ptr;

						unsigned int  index_method;

						int           record_search_flag;

						int          *found_flag;

						unsigned int *out_index_element;

						unsigned int *out_record_element;

						char           *error_text;

	DESCRIPTION	:	Gets the lowest record in a cache using the specified index
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
						into which will be placed the number of the lowest index
						element.

						(-) Because this function accesses the lowest record using
						the specified index method, ``out_index_element`` will
						always be set to zero (''0'').

						(-) ``out_index_element`` may be ''NULL'', in which case
						no action is taken.

						(.) ``out_record_element`` points to an unsigned integer
						into which will be placed the number of the lowest record
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

	SEE ALSO		:	DCR_BasicGetLowest
						DCR_GetHighest
						DCR Cache Record Search Flags

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_GetLowest
						DCR Cache Get Functions:DCR_GetLowest
						DCR Cache Functions:DCR_GetLowest

	PUBLISH XREF:	DCR_GetLowest

	PUBLISH NAME:	DCR_GetLowest

EOH */
/* *********************************************************************** */
int DCR_GetLowest(cache_ptr, index_method, record_search_flag,
	found_flag, out_index_element, out_record_element, error_text)
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
			DCR_BasicGetLowest(cache_ptr, index_method, record_search_flag,
				cache_ptr->record_count, DCR_INDEX_AREA_PTR(cache_ptr,
				index_method), found_flag, out_index_element, out_record_element);
	}

	return(return_code);
}
/*	***********************************************************************	*/

