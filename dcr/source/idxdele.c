/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support the removal of index entries from
								indices.

	Revision History	:	1995-08-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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

	NAME			:	DCR_DeleteFromIndex

	SYNOPSIS		:	return_code = DCR_DeleteFromIndex(cache_ptr,
							index_method, index_element, error_text);

						int           return_code;

						DCR_CACHE    *cache_ptr;

						unsigned int  index_method;

						unsigned int  index_element;

						char         *error_text;

	DESCRIPTION	:	Removes the specified index element from the specified
						index access path.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' from which the index element is to be deleted.

						(.) ``index_method`` is the index access path from which
						the index entry at ``index_element`` is to be deleted.

						(.) ``index_element`` is the element of the index entry in
						the index access path ``index_method`` which is to be
						deleted.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR failure codes if an error occurs.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_DeleteFromIndices

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_DeleteFromIndex
						DCR Cache Delete Functions:DCR_DeleteFromIndex
						DCR Cache Functions:DCR_DeleteFromIndex

	PUBLISH XREF:	DCR_DeleteFromIndex

	PUBLISH NAME:	DCR_DeleteFromIndex

EOH */
/* *********************************************************************** */
int DCR_DeleteFromIndex(cache_ptr, index_method, index_element,
	error_text)
DCR_CACHE    *cache_ptr;
unsigned int  index_method;
unsigned int  index_element;
char         *error_text;
{
	int return_code;

	if (((return_code = DCR_AssertAccessType(cache_ptr,
		DCR_I_AM_WRITER, error_text)) == DCR_SUCCESS) &&
		((return_code = DCR_ValidateIndexMethod(cache_ptr, index_method,
		error_text)) == DCR_SUCCESS) &&
		((return_code = DCR_CheckIndexElement(cache_ptr, index_element,
		error_text)) == DCR_SUCCESS)) {
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		If the index element to be deleted from the index is not	*/
		/* last one, move the index elements.									*/
		/*																					*/
		/*		Note that 'bcopy()' is guaranteed to handle over-lapping	*/
		/*	moves correctly on Sun systems (this despite the complaints	*/
		/*	of Purify 3.0).															*/
		/*																					*/
		/*		I'd rather use 'memmove()' function as defined by the		*/
		/*	ISO C Standard 9899:1990 (section 7.11.2.2), but it's not	*/
		/*	available under SunOS 4.1.X . . .									*/
		/*	***********************************************************	*/
		if (index_element < (cache_ptr->record_count - 1))
			bcopy(DCR_IELE_TO_IPTR(cache_ptr, index_method, index_element + 1),
				DCR_IELE_TO_IPTR(cache_ptr, index_method, index_element),
				(cache_ptr->record_count - (index_element + 1)) *
				DCR_INDEX_ENTRY_SIZE(cache_ptr, index_method));
		/*	***********************************************************	*/
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_DeleteFromIndices

	SYNOPSIS		:	return_code = DCR_DeleteFromIndices(cache_ptr,
							index_element_list, error_text);

						int                 return_code;

						DCR_CACHE          *cache_ptr;

						const unsigned int *index_element_list;

						char               *error_text;

	DESCRIPTION	:	Removes the index elements specified by the
						``index_element_list`` from all cache index access paths.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' from which the index element is to be deleted.

						(.) ``index_element_list`` is an array of unsigned
						integers which contain the index elements for index
						elements in each index access path in the cache to
						be deleted.

						(-) The array ``index_element_list`` must have an
						intialized array element for each index in the cache.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR failure codes if an error occurs.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_DeleteFromIndex

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_DeleteFromIndices
						DCR Cache Delete Functions:DCR_DeleteFromIndices
						DCR Cache Functions:DCR_DeleteFromIndices

	PUBLISH XREF:	DCR_DeleteFromIndices

	PUBLISH NAME:	DCR_DeleteFromIndices

EOH */
/* *********************************************************************** */
int DCR_DeleteFromIndices(cache_ptr, index_element_list, error_text)
DCR_CACHE          *cache_ptr;
const unsigned int *index_element_list;
char               *error_text;
{
	int          return_code;
	unsigned int count_1;

	if ((return_code = DCR_AssertAccessType(cache_ptr,
		DCR_I_AM_WRITER, error_text)) == DCR_SUCCESS) {
		for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
			if ((return_code = DCR_CheckIndexElement(cache_ptr,
				index_element_list[count_1], error_text)) != DCR_SUCCESS) {
				return_code = DCR_BAD_ARGS_FAILURE;
				break;
			}
		}
		if (return_code == DCR_SUCCESS) {
			for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
				if ((return_code = DCR_DeleteFromIndex(cache_ptr, count_1,
					index_element_list[count_1], error_text)) != DCR_SUCCESS)
					break;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

