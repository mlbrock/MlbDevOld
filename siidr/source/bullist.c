/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a bulk insert of a list of pointers into
								an SIIDR structure.

	Revision History	:	1996-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int SIIDR_CheckListPtrRaw, (const SIIDR *siidr_ptr,
	unsigned int record_count, void **record_list, char  *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_BulkInsertList(SIIDR *siidr_ptr, unsigned int in_count,
	void **in_list, char *error_text)
{
	int return_code;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) && in_count &&
		((return_code = SIIDR_CheckListPtrRaw(siidr_ptr, in_count, in_list,
		error_text)) == SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			return_code = SIIDR_BulkInsertListRaw(siidr_ptr, in_count,
				in_list, error_text);
			SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_BulkInsertListRaw(SIIDR *siidr_ptr, unsigned int in_count,
	void **in_list, char *error_text)
{
	int           return_code = SIIDR_SUCCESS;
	unsigned int  bulk_count  = 0;
	SIIDR_BULK   *bulk_list   = NULL;
	unsigned int  count_1;
	char          tmp_error_text[SIIDR_MAX_ERROR_TEXT];

	/*	*****************************************************************
		*****************************************************************
		Make sure that there's some work to do . . .
		*****************************************************************	*/
	if (!in_count)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Create the list of 'SIIDR_BULK' structures and ensure that there
		aren't any internal conflicts using the default comparison
		function . . .
		*****************************************************************	*/
	if ((return_code = SIIDR_InitBulkListRaw(siidr_ptr, in_count, in_list,
		NULL, &bulk_count, &bulk_list, tmp_error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		If the IDR is not empty, ensure that none of the records in the
		list to bulk inserted conflict with any of the already existing
		records using the default comparison function . . .
		*****************************************************************	*/
	if (siidr_ptr->record_count) {
		for (count_1 = 0; count_1 < bulk_count; count_1++) {
			if (SIIDR_FindRecordRaw(siidr_ptr, bulk_list[count_1].bulk_ptr,
				&bulk_list[count_1].record_index) != NULL) {
				if (error_text != NULL)
					sprintf(tmp_error_text, "%s %u %s %u.",
						"Bulk insert record at index", bulk_list[count_1].bulk_index,
						"compares the same as the IDR data record at index",
						bulk_list[count_1].record_index);
				return_code = SIIDR_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ensure that there is sufficient space in the list of IDR record
		pointers . . .
		*****************************************************************	*/
	if (((siidr_ptr->allocated_count - siidr_ptr->record_count) < bulk_count) &&
		((return_code = SIIDR_AllocateIDRRaw(siidr_ptr, bulk_count,
		tmp_error_text)) != SIIDR_SUCCESS))
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		If we got this far, it's time to allocate memory for copies of
		the bulk insert records . . .
		*****************************************************************	*/
	for (count_1 = 0; count_1 < bulk_count; count_1++) {
		if ((bulk_list[count_1].record_ptr = memdup(bulk_list[count_1].bulk_ptr,
			siidr_ptr->record_size)) == NULL) {
			if (error_text != NULL)
				STR_AllocMsgItem(siidr_ptr->record_size, tmp_error_text,
					"%s bulk insert record at index %u",
					"Unable to allocate memory for a copy of the",
					bulk_list[count_1].bulk_index);
			return_code = SIIDR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sort the bulk insert list by the order in which the new bulk
		insert records will occur in the IDR . . .
		*****************************************************************	*/
	STR_ARRAY_qsort(siidr_ptr, bulk_count, bulk_list, sizeof(SIIDR_BULK),
		STR_CMP_FUNC_CAST(SIIDR_CompareBulkByOrder));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Now put the bulk insert records into the IDR.

		There are three possibilities here:

			1)	The IDR is empty.

				In this case we just copy the bulk insert record pointers
				into the IDR.

			2)	The first bulk insert record (and, because the bulk insert
				list is in sorted order, all subsequent bulk insert records)
				is to be inserted at the end of the IDR record list.

				In this case, we append the bulk insert record pointers to
				the list of records already in the IDR.

			3) Otherwise, the bulk insert records are to be interleaved
				with records already in the IDR.

				In this case, we need to put the bulk insert records into
				the IDR in reverse order --- if we didn't, the record
				indices determined using 'SIIDR_FindRecordRaw()' (above)
				would be invalidated by previous insertions.

				Note that it's possible to avoid this problem by adjusting
				the record indices to account for previous insertions. But
				because there is less data to be moved by inserting in
				reverse order, it's actually faster to do it this way . . .
		*****************************************************************	*/
	if (!siidr_ptr->record_count) {
		for (count_1 = 0; count_1 < bulk_count; count_1++)
			siidr_ptr->record_list[count_1] = bulk_list[count_1].record_ptr;
		siidr_ptr->record_count = bulk_count;
	}
	else if (bulk_list[0].record_index >= siidr_ptr->record_count) {
		for (count_1 = 0; count_1 < bulk_count; count_1++)
			siidr_ptr->record_list[siidr_ptr->record_count++] =
				bulk_list[count_1].record_ptr;
		siidr_ptr->record_count += bulk_count;
	}
	else {
		for (count_1 = bulk_count; count_1; ) {
			count_1--;
			if ((return_code = memmove_insert_voidptr(siidr_ptr->record_count,
				siidr_ptr->record_list, bulk_list[count_1].record_index,
				bulk_list[count_1].record_ptr)) != STRFUNCS_SUCCESS) {
				if (error_text != NULL)
					sprintf(error_text, "%s %u %s %u (%s = 0x%p) %s %u %s.",
						"Attempt to bulk insert index", bulk_list[count_1].bulk_index,
						"at IDR record index", bulk_list[count_1].record_index,
						"record pointer", bulk_list[count_1].record_ptr,
						"into a list of", siidr_ptr->record_count,
						"records with 'memmove_insert_voidptr()' failed");
				return_code = SIIDR_MAP_ERROR_STR(return_code);
				break;
			}
			else
				siidr_ptr->record_count++;
		}
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (bulk_list != NULL) {
		if (return_code != SIIDR_SUCCESS) {
			for (count_1 = 0; (count_1 < bulk_count) &&
				(bulk_list[count_1].record_ptr != NULL); count_1++)
				free(bulk_list[count_1].record_ptr);
		}
		free(bulk_list);
	}

	if ((return_code != SIIDR_SUCCESS) && (error_text != NULL))
		sprintf(error_text, "%s %u %-.500s %s: %-.*s",
			"Attempt to bulk insert", in_count, siidr_ptr->idr_name,
			" data records into internal data repository failed",
			SIIDR_MAX_ERROR_TEXT - 600, tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_InitBulkListRaw(SIIDR *siidr_ptr, unsigned int in_count,
	void **in_list, SIIDR_CompareFunc compare_func, unsigned int *bulk_count,
	SIIDR_BULK **bulk_list, char *error_text)
{
	int          return_code = SIIDR_SUCCESS;
	unsigned int count_1;

	*bulk_count  = 0;
	*bulk_list   = NULL;

	compare_func = (compare_func != NULL) ? compare_func :
		siidr_ptr->compare_func;

	/*	*****************************************************************
		*****************************************************************
		Make sure that there's some work to do . . .
		*****************************************************************	*/
	if (!in_count)
		goto EXIT_FUNCTION;
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Allocate memory for the list of 'SIIDR_BULK' structures . . .
		*****************************************************************	*/
	if ((*bulk_list = ((SIIDR_BULK *) calloc(in_count,
		sizeof(SIIDR_BULK)))) == NULL) {
		if (error_text != NULL)
			STR_AllocMsgList(in_count, sizeof(SIIDR_BULK), error_text,
				"Unable to allocate the temporary bulk insert record array");
		return_code = SIIDR_MAP_ERROR_STR(return_code);
		goto EXIT_FUNCTION;
	}
	*bulk_count = in_count;
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Initialize the elements of the list . . .
		*****************************************************************	*/
	for (count_1 = 0; count_1 < *bulk_count; count_1++) {
		(*bulk_list)[count_1].bulk_index    = count_1;
		(*bulk_list)[count_1].bulk_ptr      = in_list[count_1];
		(*bulk_list)[count_1].record_index  = 0;
		(*bulk_list)[count_1].record_ptr    = NULL;
		(*bulk_list)[count_1].compare_index = 0;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sort the list in the order specified by the comparison function.
		*****************************************************************	*/
	SIIDR_SortBulkListRaw(siidr_ptr, *bulk_count, *bulk_list, compare_func);
	for (count_1 = 0; count_1 < *bulk_count; count_1++)
		(*bulk_list)[count_1].compare_index = count_1;
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ensure that there aren't any internal conflicts between bulk list
		records using the specified comparison function . . .
		*****************************************************************	*/
	for (count_1 = 0; count_1 < (*bulk_count - 1); count_1++) {
		if (!(*compare_func)(siidr_ptr, (*bulk_list)[count_1].bulk_ptr,
			(*bulk_list)[count_1 + 1].bulk_ptr, siidr_ptr->record_size)) {
			if (error_text != NULL)
				sprintf(error_text, "%s %u %s %u.",
					"Bulk insert record at index", (*bulk_list)[count_1].bulk_index,
					"compares the same as the bulk insert record at index",
					(*bulk_list)[count_1 + 1].bulk_index);
			return_code = SIIDR_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (return_code != SIIDR_SUCCESS) {
		if (*bulk_list != NULL)
			free(*bulk_list);
		*bulk_count = 0;
		*bulk_list  = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int SIIDR_CheckListPtrRaw(const SIIDR *siidr_ptr,
	unsigned int record_count, void **record_list, char  *error_text)
{
	int          return_code = SIIDR_SUCCESS;
	unsigned int count_1;
	char         tmp_error_text[SIIDR_MAX_ERROR_TEXT];

	if (!siidr_ptr->record_size) {
		if (error_text != NULL)
			strcpy(error_text, "SIIDR structure size is '0'.");
		return_code = SIIDR_FAILURE;
	}
	else if ((!record_count) && (record_list != NULL)) {
		if (error_text != NULL)
			strcat(val2str_ptr_cat(siidr_ptr->record_list,
				strcat(strcpy(error_text,
				"The record count is zero ('0'), "),
				"but the record list is not 'NULL' (")), ").");
		return_code = SIIDR_FAILURE;
	}
	else if (record_count && (record_list == NULL)) {
		if (error_text != NULL)
			sprintf(error_text, "The record count is non-zero ('%u'), %s.",
				record_count, "but the record list is 'NULL'");
		return_code = SIIDR_FAILURE;
	}
	else if (record_count &&
		((return_code = SIIDR_TouchRead(record_list,
		record_count * sizeof(void *), "record pointer list", error_text)) ==
		SIIDR_SUCCESS)) {
		for (count_1 = 0; count_1 < record_count; count_1++) {
			if (record_list[count_1] == NULL) {
				if (error_text != NULL)
					sprintf(error_text, "%s %u is 'NULL'.",
						"Record pointer at index", count_1);
				return_code = SIIDR_FAILURE;
				break;
			}
			else if ((return_code = SIIDR_TouchRecordRead(siidr_ptr,
				record_list[count_1], tmp_error_text)) != SIIDR_SUCCESS) {
				if (error_text != NULL)
					sprintf(error_text, "%s %u is invalid: %s",
						"Record pointer at index", count_1, tmp_error_text);
				return_code = SIIDR_FAILURE;
				break;
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int           return_code = SIIDR_SUCCESS;
	unsigned int  id_count    = SIIDR_TEST_ID_COUNT;
	SIIDR        *siidr_ptr_1 = NULL;
	SIIDR        *siidr_ptr_2 = NULL;
	unsigned int  count_1;
	unsigned int  u_int_1;
	unsigned int  u_int_2;
	void         *tmp_ptr;
	char          error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test harness for function 'SIIDR_BulkInsertList()'\n");
	fprintf(stderr,
		"                          'SIIDR_BulkInsertListRaw()'\n");
	fprintf(stderr,
		"---- ------- --- -------- ---------------------------\n\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "\nHelp request with '%s' noted . . .",
				argv[count_1]);
			fprintf(stderr, "USAGE:\n   %s [-COUNT=<record-count>]\n\n",
				argv[0]);
			goto EXIT_FUNCTION;
		}
		else if (!strnicmp(argv[count_1], "-COUNT=", 7)) {
			if ((id_count = atoi(argv[count_1] + 7)) < 1) {
				sprintf(error_text,
					"Invalid command line parameter ('%-.500s').", argv[count_1]);
				return_code = SIIDR_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
		else {
			sprintf(error_text, "Invalid command line parameter ('%-.500s').",
				argv[count_1]);
			return_code = SIIDR_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	if ((return_code = SIIDR_CreateIDR("order",
		sizeof(SIIDR_TEST_DATA), 0,
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr_1,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if ((return_code = SIIDR_CreateIDR("order",
		sizeof(SIIDR_TEST_DATA), 0,
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr_2,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Inserting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_TEST_FastInsertIdList(siidr_ptr_1, 1,
		id_count, 1, SIIDR_FALSE, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr_1, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

	if (id_count > 1) {
		fprintf(stderr, "Randomizing %u records in the IDR . . .", id_count);
		for (count_1 = 0; count_1 < (id_count * 3); count_1++) {
			while ((u_int_1 = (rand() % id_count)) ==
				(u_int_2 = (rand() % id_count)))
				;
			tmp_ptr                           = siidr_ptr_1->record_list[u_int_1];
			siidr_ptr_1->record_list[u_int_1] = siidr_ptr_1->record_list[u_int_2];
			siidr_ptr_1->record_list[u_int_2] = tmp_ptr;
		}
		fprintf(stderr, " done\n");
	}

	fprintf(stderr, "Bulk inserting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_BulkInsertList(siidr_ptr_2,
		siidr_ptr_1->record_count, siidr_ptr_1->record_list, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr_2, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

	fprintf(stderr, "Re-sorting %u records in IDR number one . . .", id_count);
	if ((return_code = SIIDR_Sort(siidr_ptr_1, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");
	fprintf(stderr, "Deleting even records from IDR number one . . .");
	if ((return_code = SIIDR_DeleteSpec(siidr_ptr_1, NULL,
		((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityEven), error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr_1, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done (%u records remain)\n", siidr_ptr_1->record_count);
	fprintf(stderr, "Deleting odd records from IDR number two . . .");
	if ((return_code = SIIDR_DeleteSpec(siidr_ptr_2, NULL,
		((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityOdd), error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr_2, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done (%u records remain)\n", siidr_ptr_2->record_count);
	fprintf(stderr, "Bulk inserting %u records in IDR number two . . .",
		siidr_ptr_1->record_count);
	if ((return_code = SIIDR_BulkInsertList(siidr_ptr_2,
		siidr_ptr_1->record_count, siidr_ptr_1->record_list, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr_2, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

EXIT_FUNCTION:

	SIIDR_FreeIDR(siidr_ptr_1);
	SIIDR_FreeIDR(siidr_ptr_2);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

