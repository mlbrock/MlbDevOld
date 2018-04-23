/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support deletion of cache data records.

	Revision History	:	1994-07-30 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
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

	NAME			:	DCR_DeleteRecordByElement

	SYNOPSIS		:	return_code = DCR_DeleteRecordByElement(cache_ptr,
							record_element, error_text);

						int           return_code;

						DCR_CACHE    *cache_ptr;

						unsigned int  record_element;

						char         *error_text;

	DESCRIPTION	:	Removes the record specified by its record element number
						from the cache.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' from which the specified record is to be
						deleted.

						(.) ``record_element`` is the element of the record in the
						cache data area which is to be deleted.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR failure codes if an error occurs.

	NOTES			:	The logical strategy for deleting a record from the cache
						is as follows:

						(+) The index entries for the record to be deleted are
						removed from each index access path.

						(+) If the record element to be deleted is not the last
						record in the cache data area, the last record in the
						cache data area is copied into the position of the deleted
						record and its index entries are updated to reflect its
						new offset within the cache.

						(+) The cache record count is decremented.

	CAVEATS		:	

	SEE ALSO		:	DCR_DeleteRecordByOffset

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	DCR_DeleteRecordByElement
						DCR Cache Delete Functions:DCR_DeleteRecordByElement
						DCR Cache Functions:DCR_DeleteRecordByElement

	PUBLISH XREF:	DCR_DeleteRecordByElement

	PUBLISH NAME:	DCR_DeleteRecordByElement

EOH */
/* *********************************************************************** */
int DCR_DeleteRecordByElement(cache_ptr, record_element, error_text)
DCR_CACHE    *cache_ptr;
unsigned int  record_element;
char         *error_text;
{
	int           return_code = DCR_SUCCESS;
	unsigned int  count_1;
	unsigned int  tmp_index_element;
	unsigned int  index_element_list_1[DCR_MAX_INDEX_COUNT];
	unsigned int  index_element_list_2[DCR_MAX_INDEX_COUNT];
	unsigned long old_cache_status;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Note start time of the record deletion attempt . . .				*/
	/*	*****************************************************************	*/
	if (cache_ptr->cache_access_type == DCR_I_AM_WRITER)
		DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
			DCR_STAT_DELETE);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the application programmer requested a call-back, do it.		*/
	/*	*****************************************************************	*/
	if ((cache_ptr->call_back_mask & DCR_CB_DELETE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_DELETE,
			DCR_FALSE, 0, 0, 1, NULL, NULL, return_code, error_text);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Only writers get to delete records from the cache . . .			*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_AssertAccessType(cache_ptr,
		DCR_I_AM_WRITER, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		The element number of the record to be deleted must be valid.	*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_CheckRecordElement(cache_ptr, record_element,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We need to know where the index entries for the record to be	*/
	/*	deleted are in each of the indices . . .									*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_FindRELEInIndices(cache_ptr, record_element,
		index_element_list_1, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the record to be deleted is not the last record in the		*/
	/*	cache data area, we will swap it with the record which is to be	*/
	/*	deleted.																				*/
	/*																							*/
	/*		In order to do this, we'll need to update the offsets for the	*/
	/*	record to be swapped in the index entry for each index. We need,	*/
	/*	therefore, to get the index element for the entry representing		*/
	/*	that record in each of the indices . . .									*/
	/*	*****************************************************************	*/
	if ((record_element < (cache_ptr->record_count - 1)) &&
		((return_code = DCR_FindRELEInIndices(cache_ptr,
		cache_ptr->record_count - 1, index_element_list_2, error_text)) !=
		DCR_SUCCESS))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Set-up flags --- we're entering a critical section.				*/
	/*	*****************************************************************	*/
	old_cache_status                                   =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	cache_ptr->header_ptr->cache_lock_status.lock_flag =
		(cache_ptr->header_ptr->cache_lock_status.lock_flag &
		DCR_STATUS_CRITICAL) | DCR_STATUS_ADDING;
	cache_ptr->header_ptr->cache_status                =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	if (cache_ptr->critical_call_back_function != NULL)
		(*cache_ptr->critical_call_back_function)(cache_ptr,
			DCR_CB_DELETE, DCR_FALSE, 0, 1, NULL, return_code, error_text);
	cache_ptr->header_ptr->cache_lock_status.lock_flag |=
		DCR_STATUS_CRITICAL;
	cache_ptr->header_ptr->cache_status                 =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	/*	*****************************************************************	*/

	if ((return_code = DCR_DeleteFromIndices(cache_ptr,
		index_element_list_1, error_text)) == DCR_SUCCESS) {
		if (record_element < (cache_ptr->record_count - 1)) {
			for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
				/*	***********************************************	*/
				/*	***********************************************	*/
				/*		If the index element of the entry of the		*/
				/*	record to be swapped is greater than the index	*/
				/*	entry of the deleted record for the current		*/
				/*	index method, subtract one (because the index	*/
				/*	entry for the deleted record has been removed	*/
				/*	from the array of index elements).					*/
				/*	***********************************************	*/
				tmp_index_element = index_element_list_2[count_1] -
					((index_element_list_2[count_1] >
					index_element_list_1[count_1]) ? 1 : 0);
				/*	***********************************************	*/
				/*	***********************************************	*/
				/*		Update the offset portion of the index entry	*/
				/*	to reflect the new offset of the swapped record.*/
				/*	***********************************************	*/
				*((unsigned long *) (DCR_IELE_TO_IPTR(cache_ptr, count_1,
					tmp_index_element) + DCR_INDEX_REC_OFF(cache_ptr,
					count_1))) = DCR_RELE_TO_ROFF(cache_ptr, record_element);
				/*	***********************************************	*/
			}
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		Now actually copy the swapped record to its new		*/
			/*	location in the data area.										*/
			/*	*****************************************************	*/
			memcpy(DCR_RELE_TO_RPTR(cache_ptr, record_element),
				DCR_RELE_TO_RPTR(cache_ptr, cache_ptr->record_count - 1),
				cache_ptr->actual_data_record_size);
			/*	*****************************************************	*/
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Record deleted!														*/
		/*	***********************************************************	*/
		cache_ptr->record_count = --cache_ptr->header_ptr->record_count;
		/*	***********************************************************	*/
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		End of the critical section.												*/
	/*	*****************************************************************	*/
	cache_ptr->header_ptr->cache_lock_status.lock_count++;
	cache_ptr->header_ptr->cache_lock_status.lock_flag = old_cache_status;
	cache_ptr->header_ptr->cache_status                = old_cache_status;
	if (cache_ptr->critical_call_back_function != NULL)
		(*cache_ptr->critical_call_back_function)(cache_ptr,
			DCR_CB_DELETE, DCR_TRUE, 0, 1, NULL, return_code,
			error_text);
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Note end time of the record deletion attempt . . .					*/
	/*	*****************************************************************	*/
	if (cache_ptr->cache_access_type == DCR_I_AM_WRITER)
		DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
			DCR_STAT_DELETE,
			((unsigned long) ((return_code == DCR_SUCCESS) ? 1L : 0L)));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the application programmer requested a call-back, do it.		*/
	/*	*****************************************************************	*/
	if ((cache_ptr->call_back_mask & DCR_CB_DELETE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_DELETE,
		DCR_TRUE, 0, 0, 1, NULL,
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_DELETE, return_code, error_text);
	/*	*****************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_DeleteRecordByOffset

	SYNOPSIS		:	return_code = DCR_DeleteRecordByOffset(cache_ptr,
							record_offset, error_text);

						int            return_code;

						DCR_CACHE     *cache_ptr;

						unsigned long  record_offset;

						char          *error_text;

	DESCRIPTION	:	Removes the record specified by its record offset from the
						cache.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' from which the specified record is to be
						deleted.

						(.) ``record_offset`` is the offset of the record in the
						cache which is to be deleted.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR failure codes if an error occurs.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_DeleteRecordByElement

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	DCR_DeleteRecordByOffset
						DCR Cache Delete Functions:DCR_DeleteRecordByOffset
						DCR Cache Functions:DCR_DeleteRecordByOffset

	PUBLISH XREF:	DCR_DeleteRecordByOffset

	PUBLISH NAME:	DCR_DeleteRecordByOffset

EOH */
/* *********************************************************************** */
int DCR_DeleteRecordByOffset(cache_ptr, record_offset, error_text)
DCR_CACHE     *cache_ptr;
unsigned long  record_offset;
char          *error_text;
{
	return(DCR_DeleteRecordByElement(cache_ptr,
		DCR_ROFF_TO_RELE(cache_ptr, record_offset), error_text));
}
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DCR_DeleteRecordByKey

	SYNOPSIS		:	return_code = DCR_DeleteRecordByKey(cache_ptr,
							index_method, record_align_cmp_ptr, index_align_cmp_ptr,
							compare_type, in_record_ptr, max_record_count,
							deleted_count, error_text);

						int            return_code;

						DCR_CACHE     *cache_ptr;

						unsigned int   index_method;

						GEN_ALIGN_CMP *record_align_cmp_ptr;

						GEN_ALIGN_CMP *index_align_cmp_ptr;

						unsigned int   compare_type;

						const void    *in_record_ptr;

						unsigned int   max_record_count;

						unsigned int  *deleted_count;

						char          *error_text;

	DESCRIPTION	:	Removes all records meeting the specified relational
						operator when compared to a key from the cache.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' from which the specified records are to be
						deleted.

						(.) ``index_method`` is the index access path to be used
						to perform the search for records to be deleted.

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

						(.) ``in_record_ptr`` points to the record containing the
						key for which the search is to be performed.

						(.) ``max_record_count`` is the maximum number of records
						to be deleted by this function. If ``max_record_count`` is
						zero, all records meeting the criteria specified will be
						deleted.

						(.) ``deleted_count`` points to an unsigned integer into
						which will be placed the number of records deleted by this
						function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR failure codes if an error occurs.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	DCR_DeleteRecordByElement

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	DCR_DeleteRecordByKey
						DCR Cache Delete Functions:DCR_DeleteRecordByKey
						DCR Cache Functions:DCR_DeleteRecordByKey

	PUBLISH XREF:	DCR_DeleteRecordByKey

	PUBLISH NAME:	DCR_DeleteRecordByKey

EOH */
/* *********************************************************************** */
int DCR_DeleteRecordByKey(cache_ptr, index_method, record_align_cmp_ptr,
	index_align_cmp_ptr, compare_type, in_record_ptr, max_record_count,
	deleted_count, error_text)
DCR_CACHE     *cache_ptr;
unsigned int   index_method;
GEN_ALIGN_CMP *record_align_cmp_ptr;
GEN_ALIGN_CMP *index_align_cmp_ptr;
unsigned int   compare_type;
const void    *in_record_ptr;
unsigned int   max_record_count;
unsigned int  *deleted_count;
char          *error_text;
{
	int          return_code;
	unsigned int record_count;
	unsigned int index_element;
	unsigned int tmp_deleted_count;

	*deleted_count = 0;

	if (((return_code = DCR_AssertAccessType(cache_ptr,
		DCR_I_AM_WRITER, error_text)) == DCR_SUCCESS) &&
		((return_code = DCR_ValidateCompareType(compare_type,
		error_text)) == DCR_SUCCESS) &&
		((return_code = DCR_ValidateIndexMethod(cache_ptr, index_method,
		error_text)) == DCR_SUCCESS)) {
		/* *********************************************************** */
		/* *********************************************************** */
		/*		If the desired comparison type is not 'not-equal', find	*/
		/*	the index element of the first record meeting the specified	*/
		/*	criteria and, for the number of records found, delete the	*/
		/*	record at the indicated record element.							*/
		/*																					*/
		/*		Because we don't change the 'index_element' within the	*/
		/*	loop, it might look as if we are deleting the same record	*/
		/*	over and over again. However, after a successful call to		*/
		/*	'DCR_DeleteRecordByElement()', the record at the		*/
		/*	position indicated by 'index_element' has been removed from	*/
		/*	the index.																	*/
		/* *********************************************************** */
		if (compare_type != DCR_COMPARE_TYPE_NE) {
			if ((record_count = DCR_BasicGetCount(cache_ptr, index_method,
				record_align_cmp_ptr, index_align_cmp_ptr, compare_type,
				DCR_FIND_TOP, DCR_RECORD_FLAG_KEPT,
				cache_ptr->record_count, cache_ptr->index_data_list[index_method].
				mmap_ptr, in_record_ptr, &index_element, NULL)) > 0) {
				for ( ; record_count; record_count-- ) {
					if ((return_code = DCR_DeleteRecordByElement(cache_ptr,
						DCR_IELE_TO_RELE(cache_ptr, index_method,
						index_element), error_text)) != DCR_SUCCESS)
						break;
					(*deleted_count)++;
					if (max_record_count && (max_record_count == *deleted_count))
						break;
				}
			}
		}
		/* *********************************************************** */
		/* *********************************************************** */
		/*		If the desired comparison type is 'not-equal', we invoke	*/
		/*	this function twice --- the first time to delete records		*/
		/*	which are less than the key, and the second time to delete	*/
		/*	records which are greater than the key.							*/
		/*																					*/
		/*		Note that the unsigned integer to which 'deleted_count'	*/
		/*	points is the cumulative count of the two invocations.		*/
		/* *********************************************************** */
		else {
			if ((return_code = DCR_DeleteRecordByKey(cache_ptr,
				index_method, record_align_cmp_ptr, index_align_cmp_ptr,
				DCR_COMPARE_TYPE_LT, in_record_ptr, max_record_count,
				deleted_count, error_text)) == DCR_SUCCESS) {
				return_code = DCR_DeleteRecordByKey(cache_ptr, index_method,
					record_align_cmp_ptr, index_align_cmp_ptr,
					DCR_COMPARE_TYPE_GT, in_record_ptr, max_record_count,
					&tmp_deleted_count, error_text);
				*deleted_count += tmp_deleted_count;
			}
		}
		/* *********************************************************** */
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <string.h>

#include <../spsscf/spsscf.h>

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static const unsigned long  Test_CallBackMask  = 0L;

static const unsigned int   Test_IndexMethod   = 0;

static const unsigned int   Test_CompareType   = DCR_COMPARE_TYPE_GE;

static const char          *Test_RecordName    = "SPS_SCF_XREF";

static SPS_SCF_XREF         Test_RecordData;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

#ifndef NARGS
static void Test_EmitRecord(const SPS_SCF_XREF *record_ptr);
#else
static void Test_EmitRecord();
#endif /* #ifndef NARGS */


/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
int main(argc, argv)
int    argc;
char **argv;
{
	int                 return_code = DCR_SUCCESS;
	unsigned int        count_1;
	unsigned int        count_2;
	DCR_CONTROL   cache_control_data;
	DCR_CACHE          *cache_ptr;
	DCR_CACHE          *cmp_cache_ptr;
	MFILE              *mfile_ptr_1;
	MFILE              *mfile_ptr_2;
	unsigned int        cache_index;
	char                error_text[DCR_MAX_ERROR_TEXT];
	unsigned int        deleted_count;
	int                 found_flag;
	unsigned int        found_count;
	unsigned int        index_element;

	fprintf(stderr,
		"Test routine for function 'DCR_DeleteRecordByKey()'\n");
	fprintf(stderr,
		"---- ------- --- -------- -------------------------------\n\n");

	memset(&cache_control_data, '\0', sizeof(cache_control_data));

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "Help request with '%s' noted . . .\n\n",
				argv[count_1]);
			fprintf(stderr, "USAGE:\n   %s %s %s %s\n\n", argv[0],
				"<input-cache-file-name>", "<comparison-cache-file-name>",
				"<test-cache-file-name>");
			goto EXIT_FUNCTION;
		}
	}

	if (argc != 4) {
		sprintf(error_text, "%s --- use '-HELP' for help.",
			"Expected command-line parameters");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}


	strcpy(Test_RecordData.category, "M");
	fprintf(stderr, "%s '%s' %s.\n",
		"Will delete all records in the cache file", argv[3],
		"where the 'category' column is greater than or equal to 'M'");

	fprintf(stdout, "%s\n",
"==========================================================================");

	if ((return_code = DCR_AllocCacheControl(&cache_control_data,
		100, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Allocated the cache control structure.\n");

	if ((return_code = DCR_OpenRead(&cache_control_data, argv[1],
		0, 0L, 0, 0L, &cache_ptr, &cache_index, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Opened input cache '%s' for reading.\n", argv[1]);

	if (cache_ptr->actual_data_record_size != sizeof(Test_RecordData)) {
		sprintf(error_text, "%s '%s' (%u) %s '%s' structure (%u).",
			"The length of the actual data record in the input cache file",
			argv[1], cache_ptr->actual_data_record_size,
			"is not equal to the size of the", Test_RecordName,
			sizeof(Test_RecordData));
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((mfile_ptr_1 = mopen(cache_ptr->cache_file_name, "r")) == NULL) {
		sprintf(error_text,
			"Unable to 'mopen()' input cache '%s' for reading: ", argv[1]);
		DCR_GEN_AppendLastErrorString(error_text);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "'mopen()' of input cache '%s' for reading succeeded.\n",
		argv[1]);

	if ((return_code = DCR_OpenRead(&cache_control_data, argv[2],
		0, 0L, 0, 0L, &cmp_cache_ptr, &cache_index, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Opened comparison cache '%s' for reading.\n", argv[2]);

	if (cmp_cache_ptr->actual_data_record_size != sizeof(Test_RecordData)) {
		sprintf(error_text, "%s '%s' (%u) %s '%s' structure (%u).",
			"The length of the actual data record in the comparison cache file",
			argv[2], cmp_cache_ptr->actual_data_record_size,
			"is not equal to the size of the", Test_RecordName,
			sizeof(Test_RecordData));
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (cache_ptr->index_count != cmp_cache_ptr->index_count) {
		sprintf(error_text, "%s '%s' (%u) %s '%s' (%u).",
			"The number of indices in the input cache file", argv[1],
			cache_ptr->index_count,
			"The number of indices in the comparison cache file", argv[2],
			cmp_cache_ptr->index_count);
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (cache_ptr->field_count != cmp_cache_ptr->field_count) {
		sprintf(error_text, "%s '%s' (%u) %s '%s' (%u).",
			"The number of fields in the input cache file", argv[1],
			cache_ptr->field_count,
			"The number of fields in the comparison cache file", argv[2],
			cmp_cache_ptr->field_count);
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (cache_ptr->field_align_count != cmp_cache_ptr->field_align_count) {
		sprintf(error_text, "%s '%s' (%u) %s '%s' (%u).",
			"The number of field aligns in the input cache file", argv[1],
			cache_ptr->field_align_count,
			"The number of field aligns in the comparison cache file", argv[2],
			cmp_cache_ptr->field_align_count);
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((mfile_ptr_2 = mopen(argv[3], "w")) == NULL) {
		sprintf(error_text, "Unable to 'mopen()' test cache '%s' for writing: ",
			argv[3]);
		DCR_GEN_AppendLastErrorString(error_text);
		mclose(mfile_ptr_1);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "'mopen()' of test cache '%s' for writing succeeded.\n",
		argv[3]);

	if (mtruncate_safe(mfile_ptr_2, cache_ptr->total_cache_size)) {
		sprintf(error_text,
			"Unable to 'mtruncate_safe()' test cache '%s' to %u bytes: ",
			argv[3], cache_ptr->total_cache_size);
		DCR_GEN_AppendLastErrorString(error_text);
		mclose(mfile_ptr_1);
		munlink(mfile_ptr_2);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "Truncation of test cache '%s' to %u bytes succeeded.\n",
		argv[3], cache_ptr->total_cache_size);

	madvise(((void *) mfile_ptr_1->mmap_ptr), mfile_ptr_1->mmap_size,
		MADV_SEQUENTIAL);
	madvise(((void *) mfile_ptr_2->mmap_ptr), mfile_ptr_2->mmap_size,
		MADV_SEQUENTIAL);

	bcopy(((void *) mfile_ptr_1->mmap_ptr), ((void *) mfile_ptr_2->mmap_ptr),
		cache_ptr->total_cache_size);

	fprintf(stderr, "Copied input cache '%s' to test cache '%s'\n", argv[1],
		argv[3]);

	DCR_CloseOneCache(cache_ptr);
	mclose(mfile_ptr_1);
	mclose(mfile_ptr_2);

	if ((return_code = DCR_OpenWrite(&cache_control_data, argv[3],
		&cache_ptr, &cache_index, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Opened test cache '%s' for writing.\n", argv[3]);

	DCR_SetUserCallBack(cache_ptr, &Test_CallBackMask, NULL);

	fprintf(stdout, "%s\n",
"==========================================================================");

	memset(cache_ptr->header_ptr->stat_list, '\0',
		sizeof(cache_ptr->header_ptr->stat_list));

	fprintf(stderr, "Old Records in Cache: %10u\n", cache_ptr->record_count);

	if ((return_code = DCR_DeleteRecordByKey(cache_ptr,
		Test_IndexMethod, NULL, NULL, Test_CompareType, &Test_RecordData, 0,
		&deleted_count, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Records Deleted     : %10u\n", deleted_count);
	fprintf(stderr, "--------------------  ----------\n");
	fprintf(stderr, "New Records in Cache: %10u\n", cache_ptr->record_count);

	fprintf(stdout, "%s\n",
"==========================================================================");

#ifndef NARGS
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Record Delete Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		DCR_STAT_DELETE, ((void (*)(void *, char *, ...)) fprintf),
		stdout);
#else
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Record Delete Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		DCR_STAT_DELETE, fprintf, stdout);
#endif /* #ifndef NARGS */

	fprintf(stdout, "%s\n",
"==========================================================================");

	fprintf(stdout, "%s\n",
"==========================================================================");

	if ((return_code = DCR_MapData(cmp_cache_ptr, NULL, NULL,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	if (cache_ptr->record_count != cmp_cache_ptr->record_count) {
		sprintf(error_text, "%s '%s' (%u) %s '%s' (%u).",
			"The number of records in the test cache file", argv[3],
			cache_ptr->record_count,
			"The number of records in the comparison cache file", argv[2],
			cmp_cache_ptr->record_count);
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");

	fprintf(stderr, "%s '%s' %s '%s' . . . [",
		"Comparing the records in input cache file", cache_ptr->cache_file_name,
		"to the records in the comparison cache file",
		cmp_cache_ptr->cache_file_name);
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		if (DCR_MapIndex(cmp_cache_ptr, count_1, NULL, NULL,
			error_text) != DCR_SUCCESS) {
			return_code = DCR_FAILURE;
			goto EXIT_FUNCTION;
		}
		for (count_2 = 0; count_2 < cache_ptr->record_count; count_2++) {
			found_flag = DCR_FALSE;
			if (DCR_GetCount(cmp_cache_ptr, count_1, NULL, NULL,
				DCR_COMPARE_TYPE_EQ, DCR_FIND_TOP,
				DCR_RECORD_FLAG_ALL, DCR_IELE_TO_RPTR(cache_ptr,
				count_1, count_2), &found_count, &index_element, NULL,
				error_text) != DCR_SUCCESS) {
				return_code = DCR_FAILURE;
				goto EXIT_FUNCTION;
			}
			for ( ; found_count; found_count--, index_element++) {
				if (!DCR_CompareRecords(cache_ptr,
					DCR_IELE_TO_RPTR(cache_ptr, count_1, count_2),
					DCR_IELE_TO_RPTR(cmp_cache_ptr, count_1,
					index_element))) {
					found_flag = DCR_TRUE;
					break;
				}
			}
			if (found_flag != DCR_TRUE) {
				sprintf(error_text, "%s %u %s %u %s '%s' %s '%s'.",
					"The data record for index number", count_1,
					"at index element number", count_2, "in test cache file",
					argv[3], "was not found in comparison cache file", argv[2]);
				fprintf(stderr, "\nRECORD ERROR: %s\n", error_text);
				Test_EmitRecord(DCR_IELE_TO_RPTR(cache_ptr, count_1,
					count_2));
				return_code = DCR_FAILURE;
			}
		}
		DCR_UnMapIndex(cmp_cache_ptr, count_1, error_text);
		fprintf(stderr, ".");
	}
	fprintf(stderr, "]\n");

	if (return_code != DCR_SUCCESS) {
		strcpy(error_text, "Errors occurred in matching records.");
		goto EXIT_FUNCTION;
	}
		
	fprintf(stdout, "%s\n",
"==========================================================================");

	fprintf(stderr, "Checking indices in cache file '%s' . . .",
		cache_ptr->cache_file_name);
	if (DCR_CheckIndicesElements(cache_ptr, error_text) == DCR_SUCCESS)
		fprintf(stderr, " OK\n");
	else
		fprintf(stderr, " ERROR: %s\n", error_text);

EXIT_FUNCTION:

	DCR_CloseAllCaches(&cache_control_data);

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void Test_EmitRecord(record_ptr)
const SPS_SCF_XREF *record_ptr;
{
	fprintf(stderr, ">>> [%10u|%-32.32s|%-32.32s|%-128.128s]\n",
		record_ptr->xref_code,
		record_ptr->category,
		record_ptr->value_type,
		record_ptr->value);
}
/*	***********************************************************************	*/

#endif /* #ifdef TEST_MAIN */

