/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the index elements at which a particular
								cache data record (should) reside(s).

	Revision History	:	1994-08-08 --- Creation.
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

#include "dcr.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_FindRELEInIndices

	SYNOPSIS		:	return_code = DCR_FindRELEInIndices(cache_ptr,
							record_element, index_element_list, error_text);

						int           return_code;

						DCR_CACHE    *cache_ptr;

						unsigned int  record_element;

						unsigned int *index_element_list;

						char         *error_text;

	DESCRIPTION	:	Determines the index elements at which the index entries
						for an existing cache record reside.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' for which the search is to be performed.

						(.) ``record_element`` is the element of the record in the
						cache data area for which the search is to be performed.

						(.) ``index_element_list`` points to an array of unsigned
						integers into which will be placed the index element for
						the record in question for each index access path.

						(-) The area to which ``index_element_list`` points should,
						for any given cache, be allocated to have a minimum size of:

						(--) cache_ptr->index_count * sizeof(unsigned int)

						(-) Alternatively, ``index_element_list`` can be allocated
						statically for any valid cache created by the cache library
						by using the manifest constant ''DCR_MAX_INDEX_COUNT''
						as follows:

						(--) unsigned int index_element_list[DCR_MAX_INDEX_COUNT];

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR failure codes if an error occurs.

	NOTES			:	If this function returns with an error, then one of the
						following are true:

						(.) An invalid ``record_element`` parameter was passed.

						(.) The cache structure to which the ``cache_ptr`` parameter
						points has been trashed.

						(.) One or more of the cache indices are inconsistent with
						the data in the cache.

						The last two of the above alternatives are particularly
						nasty ones and should be investigated immediately.

	CAVEATS		:	

	SEE ALSO		:	DCR_FindRPTRInIndices

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_FindRELEInIndices
						DCR Cache Functions:DCR_FindRELEInIndices

	PUBLISH XREF:	DCR_FindRELEInIndices

	PUBLISH NAME:	DCR_FindRELEInIndices

EOH */
/* *********************************************************************** */
int DCR_FindRELEInIndices(cache_ptr, record_element, index_element_list,
	error_text)
DCR_CACHE    *cache_ptr;
unsigned int  record_element;
unsigned int *index_element_list;
char         *error_text;
{
	int          return_code;
	int          found_flag;
	unsigned int count_1;
	unsigned int record_count;
	unsigned int index_element;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		The element number of the record to be located must be valid.	*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_CheckRecordElement(cache_ptr, record_element,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		For each index, determine the number of records which match		*/
	/*	the record at the specified cache data area element. One of the	*/
	/*	the records so found should have an record element equal to that	*/
	/*	passed as a parameter to this function.									*/
	/*																							*/
	/*		If such a record is not found by the logic below, then the		*/
	/*	index in question is out-of-sync with the records in the cache		*/
	/*	data area . . . a bad situation.												*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		found_flag = DCR_FALSE;
		if ((return_code = DCR_GetCount(cache_ptr, count_1, NULL, NULL,
			DCR_COMPARE_TYPE_EQ, DCR_FIND_TOP,
			DCR_RECORD_FLAG_ALL, DCR_RELE_TO_RPTR(cache_ptr,
			record_element), &record_count, &index_element, NULL, error_text)) !=
			DCR_SUCCESS)
			break;
		else {
			for ( ; record_count; record_count--, index_element++) {
				if (DCR_IELE_TO_RELE(cache_ptr, count_1, index_element) ==
					record_element) {
					found_flag = DCR_TRUE;
					break;
				}
			}
			if (found_flag != DCR_TRUE) {
				sprintf(error_text, "%s '%u' in index method number %u.",
					"Unable to locate an index entry for record element",
					record_element, count_1);
				return_code = DCR_FAILURE;
				break;
			}
			index_element_list[count_1] = index_element;
		}
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_FindRPTRInIndices

	SYNOPSIS		:	return_code = DCR_FindRPTRInIndices(cache_ptr,
							record_element, record_ptr, index_element_list,
							error_text);

						int           return_code;

						DCR_CACHE    *cache_ptr;

						unsigned int *record_element;

						const void   *record_ptr;

						unsigned int *index_element_list;

						char         *error_text;

	DESCRIPTION	:	Determines the index elements at which the index entries
						for an exisiting or proposed cache record reside.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' for which the search is to be performed.

						(.) ``record_element`` either points to the unsigned
						integer which contains the element of the record in the
						cache data area for which the search is to be performed
						(for an existing record) or is ''NULL'' (for a proposed
						record).

						(-) If ``record_element`` is not ''NULL'', this function
						will attempt to locate the index element matching the
						record ``record_ptr`` at the specified record element. If
						such an index element can not be located, the function
						will use the index element at the end of any matching
						index elements.

						(-) If ``record_element`` is ''NULL'', this function will
						use the index element at the end of any matching index
						elements.

						(.) ``record_ptr`` points to the record for which the
						search is to be performed.

						(.) ``index_element_list`` points to an array of unsigned
						integers into which will be placed the index element for
						the record in question for each index access path.

						(-) The area to which ``index_element_list`` points should,
						for any given cache, be allocated to have a minimum size of:

						(--) cache_ptr->index_count * sizeof(unsigned int)

						(-) Alternatively, ``index_element_list`` can be allocated
						statically for any valid cache created by the cache library
						by using the manifest constant ''DCR_MAX_INDEX_COUNT''
						as follows:

						(--) unsigned int index_element_list[DCR_MAX_INDEX_COUNT];

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR failure codes if an error occurs.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_FindRELEInIndices

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	DCR_FindRPTRInIndices
						DCR Cache Functions:DCR_FindRPTRInIndices

	PUBLISH XREF:	DCR_FindRPTRInIndices

	PUBLISH NAME:	DCR_FindRPTRInIndices

EOH */
/* *********************************************************************** */
int DCR_FindRPTRInIndices(cache_ptr, record_element, record_ptr,
	index_element_list, error_text)
DCR_CACHE    *cache_ptr;
unsigned int *record_element;
const void   *record_ptr;
unsigned int *index_element_list;
char         *error_text;
{
	int          return_code = DCR_FAILURE;
	unsigned int count_1;
	unsigned int record_count;
	unsigned int index_element;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		The element number of the record to be located must be valid.	*/
	/*	*****************************************************************	*/
	if ((record_element != NULL) &&
		((return_code = DCR_CheckRecordElement(cache_ptr, *record_element,
		error_text)) != DCR_SUCCESS))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now we try to find the approriate location for the record in	*/
	/*	each of the indices using the following procedure:						*/
	/*																							*/
	/*			1)	We try to locate any records matching the key for the		*/
	/*				index	in question.													*/
	/*																							*/
	/*			1)	If records were found and the record element specified	*/
	/*				is non-NULL, we look for the record element among the		*/
	/*				matching records.														*/
	/*																							*/
	/*			2)	If the record element is found among the matching			*/
	/*				records, that index element will be used. Otherwise,		*/
	/*				index element will be incremented by the 'for' loop		*/
	/*				to the index element just beyond the index elements of	*/
	/*				the matching elements.												*/
	/*																							*/
	/*			3)	If records were found and the record element specified	*/
	/*				is NULL, the index element used will be the index			*/
	/*				element just beyond the index elements of the matching	*/
	/*				elements.																*/
	/*																							*/
	/*			4)	If no records were found matching the key for the index	*/
	/*				in question, we use the function 'DCR_Find()' to	*/
	/*				determine where the record would be inserted.				*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		if ((return_code = DCR_GetCount(cache_ptr, count_1, NULL, NULL,
			DCR_COMPARE_TYPE_EQ, DCR_FIND_TOP,
			DCR_RECORD_FLAG_ALL, record_ptr, &record_count, &index_element,
			NULL, error_text)) != DCR_SUCCESS)
			break;
		if (record_count) {
			if (record_element != NULL) {
				for ( ; record_count; record_count--, index_element++) {
					if (DCR_IELE_TO_RELE(cache_ptr, count_1,
						index_element) == *record_element)
						break;
				}
				index_element_list[count_1] = index_element;
			}
			else
				index_element_list[count_1] = index_element + record_count;
		}
		else {
			if (DCR_Find(cache_ptr, count_1, NULL, NULL, record_ptr,
				cache_ptr->record_count, cache_ptr->index_data_list[count_1].
				index_entry_list, DCR_FIND_BOTTOM, &index_element, NULL,
				NULL, NULL) == DCR_RECORD_FOUND)
				index_element++;
			index_element_list[count_1] = index_element;
		}
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

