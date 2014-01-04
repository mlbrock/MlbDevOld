/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Logic to support update of cache data records.

	Revision History	:	1995-08-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
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

	NAME			:	DCR_UpdateRecord

	SYNOPSIS		:	return_code = DCR_UpdateRecord(cache_ptr,
							record_element, new_record_ptr, error_text);

						unsigned int  return_code;

						DCR_CACHE    *cache_ptr;

						unsigned int  record_element;

						const void   *new_record_ptr;

						char         *error_text;

	DESCRIPTION	:	Updates a cache record.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``cache_ptr`` is a pointer to the structure of type
						''DCR_CACHE'' in which the record is to be updated.

						(.) ``record_element`` is the element of the record in the
						cache data area which is to be updated.

						(.) ``new_record_ptr`` points to the record data which is
						to replace the record data at ``record_element`` in the
						cache data area.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur. The string allocated for this purpose should
						be at least ''DCR_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :  Returns from this function are as follow:

						(.) ''DCR_SUCCESS'' if the function completes without error.

						(.) One of the defined DCR failure codes if an error occurs.

	NOTES			:	The logical strategy for updating a record in the cache
						is as follows:

						(+) The columns of the old record (that is, the record at
						``record_element`` in the cache data area) and the new
						record (that is, the record to which the ``new_record_ptr``
						parameter points) are compared. If the fields in the two
						records are identical, no further work is done.

						(+) Otherwise, the elements at which each index entry
						resides in all index access paths is determined for the
						old record.

						(+) The elements at which each index entry will reside
						after the update in all index access paths is determined
						for the new record.

						(+) For each index access path, a determination is made
						as to whether each index access path needs to be updated
						and if so the manner in which to do so.

						(..) If, for a particular index access method, the index
						element of the old record is the same as the index element
						of the new record, then the update has not changed the
						''relative'' position in the index access path for the
						record in question.

						(--) Even if the ''relative'' position within the index
						access path has not changed, the ''absolute'' value
						of the columns which comprise the index for that index
						access path may have changed. If this is so, the data
						which describe embedded indices have to be updated within
						that index access path.

						(..) Otherwise, the index access path will have to have
						the index entry corresponding to the old record deleted
						from the index and an index entry for the new record
						inserted. This is done in a single memory movement operation
						for efficiency.

						(+) The old record data is overlaid with the new record
						data.

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

	OUTPUT INDEX:	DCR_UpdateRecord
						DCR Cache Update Functions:DCR_UpdateRecord
						DCR Cache Functions:DCR_UpdateRecord

	PUBLISH XREF:	DCR_UpdateRecord

	PUBLISH NAME:	DCR_UpdateRecord

EOH */
/* *********************************************************************** */
int DCR_UpdateRecord(cache_ptr, record_element, new_record_ptr,
	error_text)
DCR_CACHE    *cache_ptr;
unsigned int  record_element;
const void   *new_record_ptr;
char         *error_text;
{
	int            return_code = DCR_SUCCESS;
	unsigned int   count_1;
	unsigned int   old_index_element_list[DCR_MAX_INDEX_COUNT];
	unsigned int   new_index_element_list[DCR_MAX_INDEX_COUNT];
	unsigned long  old_cache_status;
	void          *to_ptr;
	void          *from_ptr;
	void          *new_ptr;
	unsigned int   move_count;

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Note start time of the record update attempt . . .					*/
	/*	*****************************************************************	*/
#ifdef DCR_STAT_REC_UPDATE
	if (cache_ptr->cache_access_type == DCR_I_AM_WRITER)
		DCR_StatStartTime(cache_ptr->header_ptr->stat_list +
			DCR_STAT_REC_UPDATE);
#endif /* #ifdef DCR_STAT_REC_UPDATE */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the application programmer requested a call-back, do it.		*/
	/*	*****************************************************************	*/
	if ((cache_ptr->call_back_mask & DCR_CB_REC_UPDATE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_REC_UPDATE,
			DCR_FALSE, 0, 0, 1, ((void *) new_record_ptr), NULL, return_code,
			error_text);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Only writers get to update records in the cache . . .				*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_AssertAccessType(cache_ptr,
		DCR_I_AM_WRITER, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		The element number of the record to be updated must be valid.	*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_CheckRecordElement(cache_ptr, record_element,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the new record data is the same as the old record data, we	*/
	/*	don't have any work to do . . .												*/
	/*	*****************************************************************	*/
	if (!DCR_CompareRecords(cache_ptr, new_record_ptr,
		DCR_RELE_TO_RPTR(cache_ptr, record_element)))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We need to know where the index entries for the old record		*/
	/*	are in each of the indices . . .												*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_FindRELEInIndices(cache_ptr, record_element,
		old_index_element_list, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We need to determine where the index entries for the new			*/
	/* record data should be placed into each of the indices.				*/
	/*	*****************************************************************	*/
	if ((return_code = DCR_FindRPTRInIndices(cache_ptr, &record_element,
		new_record_ptr, new_index_element_list, error_text)) != DCR_SUCCESS)
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
			DCR_CB_REC_UPDATE, DCR_FALSE, 0, 1, ((void *) new_record_ptr),
			return_code, error_text);
	cache_ptr->header_ptr->cache_lock_status.lock_flag |=
		DCR_STATUS_CRITICAL;
	cache_ptr->header_ptr->cache_status                 =
		cache_ptr->header_ptr->cache_lock_status.lock_flag;
	/*	*****************************************************************	*/

	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		cache_ptr->current_index_method = count_1;
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		If the old index element of the record and the new index	*/
		/*	element of the record are equal, no index entries need be	*/
		/*	moved.																		*/
		/*																					*/
		/*		We may, however, need to update the embedded index (if	*/
		/*	present) as the columns which constitute the index may have	*/
		/*	changed in the new record . . .										*/
		/*	***********************************************************	*/
		if (new_index_element_list[count_1] ==
			old_index_element_list[count_1]) {
			if (DCR_INDEX_IS_INDIRECT(cache_ptr) != DCR_TRUE) {
				if (DCR_CompareEmbedded(cache_ptr, new_record_ptr,
					DCR_RELE_TO_RPTR(cache_ptr, record_element),
					DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1)))
					DCR_CopyEmbedded(cache_ptr, count_1,
						DCR_RELE_TO_ROFF(cache_ptr, record_element),
						new_record_ptr, DCR_IELE_TO_IPTR(cache_ptr, count_1,
						new_index_element_list[count_1]));
			}
			continue;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		If the old index element of the record is greater than	*/
		/*	the new index element of the record, open an entry at the	*/
		/*	new index element of the index array by moving the elements	*/
		/*	between the two elements forwards in the array.					*/
		/*																					*/
		/*		Note that this will overwrite the index entry at the old	*/
		/*	index element.																*/
		/*	***********************************************************	*/
		if (old_index_element_list[count_1] > new_index_element_list[count_1]) {
			from_ptr   = DCR_IELE_TO_IPTR(cache_ptr, count_1,
				new_index_element_list[count_1]);
			to_ptr     = DCR_IELE_TO_IPTR(cache_ptr, count_1,
				new_index_element_list[count_1] + 1);
			new_ptr    = from_ptr;
			move_count = (old_index_element_list[count_1] -
				new_index_element_list[count_1]) *
				DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1);
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		If the old index element of the record is less than the	*/
		/*	new index element of the record, open an entry at the new	*/
		/*	index element of the index array by moving the elements		*/
		/*	between the two elements backwards in the array.				*/
		/*																					*/
		/*		Note that this will overwrite the index entry at the old	*/
		/*	index element.																*/
		/*																					*/
		/*		Because the new index element is determined relative to	*/
		/*	the index array WITH the old index entry present, the actual*/
		/*	element at which the new index entry will be placed by the	*/
		/*	function is one less than value of the new index element.	*/
		/*	There is a special case: if the new index element is one		*/
		/*	greater than the old index element, 'move_count' will be		*/
		/*	set to zero and no movement of index entries will be done.	*/
		/*	***********************************************************	*/
		else {
			from_ptr   = DCR_IELE_TO_IPTR(cache_ptr, count_1,
				old_index_element_list[count_1] + 1);
			to_ptr     = DCR_IELE_TO_IPTR(cache_ptr, count_1,
				old_index_element_list[count_1]);
			new_ptr    = DCR_IELE_TO_IPTR(cache_ptr, count_1,
				new_index_element_list[count_1] - 1);
			move_count = (new_index_element_list[count_1] -
				(old_index_element_list[count_1] + 1)) *
				DCR_INDEX_ENTRY_SIZE(cache_ptr, count_1);
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Move the index entries . . .										*/
		/*																					*/
		/*		Note that 'bcopy()' is guaranteed to handle over-lapping	*/
		/*	moves correctly on Sun systems (this despite the complaints	*/
		/*	of Purify 3.0).															*/
		/*																					*/
		/*		I'd rather use 'memmove()' function as defined by the		*/
		/*	ISO C Standard 9899:1990 (section 7.11.2.2), but it's not	*/
		/*	available under SunOS 4.1.X . . .									*/
		/*	***********************************************************	*/
		if (move_count)
			bcopy(from_ptr, to_ptr, move_count);
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Update the index entry if it is an embedded index.			*/
		/*	***********************************************************	*/
		if (DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE)
			*((unsigned long *) new_ptr) =
				DCR_RELE_TO_ROFF(cache_ptr, record_element);
		else
			DCR_CopyEmbedded(cache_ptr, count_1,
				DCR_RELE_TO_ROFF(cache_ptr, record_element),
				new_record_ptr, new_ptr);
		/*	***********************************************************	*/
	}

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now copy the new record data to the cache data area.				*/
	/*	*****************************************************************	*/
	memcpy(DCR_RELE_TO_RPTR(cache_ptr, record_element), new_record_ptr,
		cache_ptr->actual_data_record_size);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		End of the critical section.												*/
	/*	*****************************************************************	*/
	cache_ptr->header_ptr->cache_lock_status.lock_count++;
	cache_ptr->header_ptr->cache_lock_status.lock_flag = old_cache_status;
	cache_ptr->header_ptr->cache_status                = old_cache_status;
	if (cache_ptr->critical_call_back_function != NULL)
		(*cache_ptr->critical_call_back_function)(cache_ptr,
			DCR_CB_REC_UPDATE, DCR_TRUE, 0, 1, ((void *) new_record_ptr),
			return_code, error_text);
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Note end time of the record update attempt . . .					*/
	/*	*****************************************************************	*/
#ifdef DCR_STAT_REC_UPDATE
	if (cache_ptr->cache_access_type == DCR_I_AM_WRITER)
		DCR_StatEndTime(cache_ptr->header_ptr->stat_list +
			DCR_STAT_REC_UPDATE,
			((unsigned long) ((return_code == DCR_SUCCESS) ? 1L : 0L)));
#endif /* #ifdef DCR_STAT_REC_UPDATE */
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If the application programmer requested a call-back, do it.		*/
	/*	*****************************************************************	*/
	if ((cache_ptr->call_back_mask & DCR_CB_REC_UPDATE) &&
		(cache_ptr->call_back_function != NULL))
		(*cache_ptr->call_back_function)(cache_ptr, DCR_CB_REC_UPDATE,
		DCR_TRUE, 0, 0, 1, ((void *) new_record_ptr),
#ifdef DCR_STAT_REC_UPDATE
		((DCR_HEADER *) cache_ptr->header_ptr)->stat_list +
		DCR_STAT_REC_UPDATE, return_code, error_text);
#endif /* #ifdef DCR_STAT_REC_UPDATE */
		NULL, return_code, error_text);
	/*	*****************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <../spsscf/spsscf.h>

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static const unsigned long  Test_CallBackMask  = 0L;

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
	DCR_CONTROL   cache_control_data;
	DCR_CACHE          *cache_ptr;
	MFILE              *mfile_ptr_1;
	MFILE              *mfile_ptr_2;
	unsigned int        cache_index;
	char                error_text[DCR_MAX_ERROR_TEXT];
	unsigned int        changed_count = 0;

	fprintf(stderr,
		"Test routine for function 'DCR_CACHEUpdateRecord()'\n");
	fprintf(stderr,
		"---- ------- --- -------- -------------------------\n\n");

	memset(&cache_control_data, '\0', sizeof(cache_control_data));

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "Help request with '%s' noted . . .\n\n",
				argv[count_1]);
			fprintf(stderr, "USAGE:\n   %s %s %s\n\n", argv[0],
				"<input-cache-file-name>", "<test-cache-file-name>");
			goto EXIT_FUNCTION;
		}
	}

	if (argc != 3) {
		sprintf(error_text, "%s --- use '-HELP' for help.",
			"Expected command-line parameters");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stdout, "%s\n",
"==========================================================================");

	fprintf(stderr, "%s '%s' %s to 'xref_code' + -1,000,000.\n",
		"Will update all records in the cache file", argv[2],
		"where the 'xref_code' column modulus '40' equals '0'");
	fprintf(stderr, "%s '%s' %s to 'xref_code' + -  100,000.\n",
		"Will update all records in the cache file", argv[2],
		"where the 'xref_code' column modulus '30' equals '0'");
	fprintf(stderr, "%s '%s' %s to 'xref_code' +  1,000,000.\n",
		"Will update all records in the cache file", argv[2],
		"where the 'xref_code' column modulus '20' equals '0'");
	fprintf(stderr, "%s '%s' %s to 'xref_code' +    100,000.\n",
		"Will update all records in the cache file", argv[2],
		"where the 'xref_code' column modulus '10' equals '0'");

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

	if ((mfile_ptr_2 = mopen(argv[2], "w")) == NULL) {
		sprintf(error_text, "Unable to 'mopen()' test cache '%s' for writing: ",
			argv[2]);
		DCR_GEN_AppendLastErrorString(error_text);
		mclose(mfile_ptr_1);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "'mopen()' of test cache '%s' for writing succeeded.\n",
		argv[2]);

	if (mtruncate_safe(mfile_ptr_2, cache_ptr->total_cache_size)) {
		sprintf(error_text,
			"Unable to 'mtruncate_safe()' test cache '%s' to %u bytes: ",
			argv[2], cache_ptr->total_cache_size);
		DCR_GEN_AppendLastErrorString(error_text);
		mclose(mfile_ptr_1);
		munlink(mfile_ptr_2);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "Truncation of test cache '%s' to %u bytes succeeded.\n",
		argv[2], cache_ptr->total_cache_size);

	madvise(((void *) mfile_ptr_1->mmap_ptr), mfile_ptr_1->mmap_size,
		MADV_SEQUENTIAL);
	madvise(((void *) mfile_ptr_2->mmap_ptr), mfile_ptr_2->mmap_size,
		MADV_SEQUENTIAL);

	bcopy(((void *) mfile_ptr_1->mmap_ptr), ((void *) mfile_ptr_2->mmap_ptr),
		cache_ptr->total_cache_size);

	fprintf(stderr, "Copied input cache '%s' to test cache '%s'\n", argv[1],
		argv[2]);

	DCR_CloseOneCache(cache_ptr);
	mclose(mfile_ptr_1);
	mclose(mfile_ptr_2);

	if ((return_code = DCR_OpenWrite(&cache_control_data, argv[2],
		&cache_ptr, &cache_index, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Opened test cache '%s' for writing.\n", argv[2]);

	DCR_SetUserCallBack(cache_ptr, &Test_CallBackMask, NULL);

	fprintf(stdout, "%s\n",
"==========================================================================");

	memset(cache_ptr->header_ptr->stat_list, '\0',
		sizeof(cache_ptr->header_ptr->stat_list));

	fprintf(stderr, "Updating records . . . ");
	for (count_1 = 0; count_1 < cache_ptr->record_count; count_1++) {
		memcpy(&Test_RecordData, DCR_RELE_TO_RPTR(cache_ptr, count_1),
			cache_ptr->actual_data_record_size);
		if (!(Test_RecordData.xref_code % 10)) {
			Test_RecordData.xref_code += (Test_RecordData.xref_code % 40) ?
				((int) -1000000L) : (Test_RecordData.xref_code % 30) ?
				((int) -100000L) : (Test_RecordData.xref_code % 20) ?
				((int) 1000000L) : ((int) 100000L);
			if ((return_code = DCR_UpdateRecord(cache_ptr, count_1,
				&Test_RecordData, error_text)) != DCR_SUCCESS)
				goto EXIT_FUNCTION;
			changed_count++;
		}
	}
	fprintf(stderr, "done\n");

	fprintf(stderr, "Records in Cache: %10u\n", cache_ptr->record_count);
	fprintf(stderr, "Records Updated : %10u\n", changed_count);

	fprintf(stdout, "%s\n",
"==========================================================================");

#ifdef DCR_STAT_REC_UPDATE
# ifndef NARGS
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Record Update Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		DCR_STAT_REC_UPDATE, ((void (*)(void *, char *, ...)) fprintf),
		stdout);
# else
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	fprintf(stdout, "Record Update Statistics\n");
	fprintf(stdout, "%s\n",
"--------------------------------------------------------------------------");
	DCR_EmitOneStat(cache_ptr->header_ptr->stat_list +
		DCR_STAT_REC_UPDATE, fprintf, stdout);
# endif /* #ifndef NARGS */
#endif /* #ifdef DCR_STAT_REC_UPDATE */

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

#endif /* #ifdef TEST_MAIN */

