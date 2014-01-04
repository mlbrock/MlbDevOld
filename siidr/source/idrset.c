/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sets state associates with an SIIDR.

	Revision History	:	1996-04-11 --- Creation
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

#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_SetIDRAllocSize(SIIDR *siidr_ptr, unsigned int allocation_size,
	char *error_text)
{
	int return_code;

	if ((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			return_code = SIIDR_SetIDRAllocSizeRaw(siidr_ptr, allocation_size,
				error_text);
			SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_SetIDRCompareFunc(SIIDR *siidr_ptr, SIIDR_CompareFunc compare_func,
	char *error_text)
{
	int return_code;

	if ((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			return_code = SIIDR_SetIDRCompareFuncRaw(siidr_ptr, compare_func,
				error_text);
			SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_SetIDRName(SIIDR *siidr_ptr, const char *idr_name, char *error_text)
{
	int return_code;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchReadString(idr_name, UINT_MAX,
		"'idr_name' parameter", error_text)) == SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			return_code = SIIDR_SetIDRNameRaw(siidr_ptr, idr_name,
				error_text);
			SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_SetIDRRecordSize(SIIDR *siidr_ptr, unsigned int record_size,
	char *error_text)
{
	int return_code;

	if ((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			return_code = SIIDR_SetIDRRecordSizeRaw(siidr_ptr, record_size,
				error_text);
			SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_SetIDRAllocSizeRaw(SIIDR *siidr_ptr, unsigned int allocation_size,
	char *error_text)
{
	int          return_code = SIIDR_SUCCESS;
	unsigned int allocation_count;

	allocation_size = (allocation_size) ? allocation_size :
		SIIDR_DEFAULT_ALLOC_SIZE;

	if (allocation_size != siidr_ptr->allocation_size) {
		if (!siidr_ptr->allocated_count)
			siidr_ptr->allocation_size = allocation_size;
		else if (!(siidr_ptr->allocated_count % allocation_size))
			siidr_ptr->allocation_size = allocation_size;
		else if ((allocation_size > siidr_ptr->allocation_size) &&
			(!(siidr_ptr->allocation_size % allocation_size)))
			siidr_ptr->allocation_size = allocation_size;
		else {
			allocation_count = siidr_ptr->allocated_count +
				(siidr_ptr->allocated_count % allocation_size);
			if ((return_code = SIIDR_AllocateIDRBasicRaw(siidr_ptr,
				allocation_count, allocation_size, error_text)) == SIIDR_SUCCESS)
				siidr_ptr->allocation_size = allocation_size;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_SetIDRCompareFuncRaw(SIIDR *siidr_ptr,
	SIIDR_CompareFunc compare_func, char *error_text)
{
	int           return_code;
	unsigned int  bulk_count  = 0;
	SIIDR_BULK   *bulk_list   = NULL;
	char          tmp_error_text[SIIDR_MAX_ERROR_TEXT];

	if ((return_code = SIIDR_TouchCode(STR_CAST_FUNC_PTR(compare_func),
		tmp_error_text)) != SIIDR_SUCCESS) {
		if (error_text != NULL)
			strcat(strcpy(error_text,
				"Comparison function pointer is invalid: "), tmp_error_text);
	}
	else {
		if (!siidr_ptr->record_count)
			siidr_ptr->compare_func = compare_func;
		else if ((return_code = SIIDR_InitBulkListRaw(siidr_ptr,
			siidr_ptr->record_count, siidr_ptr->record_list, compare_func,
			&bulk_count, &bulk_list, tmp_error_text)) == SIIDR_SUCCESS) {
			free(bulk_list);
			siidr_ptr->compare_func = compare_func;
			SIIDR_SortBasicRaw(siidr_ptr, siidr_ptr->record_count,
				siidr_ptr->record_list, siidr_ptr->compare_func);
		}
		else
			strcat(strcpy(error_text,
				"Unable to modify the comparison function pointer: "),
				tmp_error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_SetIDRNameRaw(SIIDR *siidr_ptr, const char *idr_name,
	char *error_text)
{
	int   return_code;
	char *tmp_idr_name;

	idr_name = ((idr_name != NULL) && *idr_name) ? idr_name : "*** UNKNOWN ***";

	if ((tmp_idr_name = strdup(idr_name)) == NULL) {
		if (error_text != NULL)
			STR_AllocMsgItem(strlen(idr_name) + 1, error_text,
				"Unable to copy SIIDR internal data repository name '%-.500s'",
				idr_name);
		return_code = SIIDR_MEMORY_FAILURE;
	}
	else {
		if (siidr_ptr->idr_name != NULL)
			free(siidr_ptr->idr_name);
		siidr_ptr->idr_name = tmp_idr_name;
		return_code         = SIIDR_SUCCESS;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_SetIDRRecordSizeRaw(SIIDR *siidr_ptr, unsigned int record_size,
	char *error_text)
{
	int            return_code = SIIDR_SUCCESS;
	unsigned int   count_1;
	unsigned int   copy_size;
	unsigned int   tmp_count = 0;
	void         **tmp_list  = NULL;

	if (!record_size) {
		if (error_text != NULL)
			strcpy(error_text, "SIIDR structure size is '0'.");
		return_code = SIIDR_BAD_ARGS_FAILURE;
	}
	else if (record_size != siidr_ptr->record_size) {
		if (!siidr_ptr->record_count)
			siidr_ptr->record_size = record_size;
		else {
			if ((return_code = meml_allocate(&tmp_count, &tmp_list, record_size,
				siidr_ptr->record_count)) == STRFUNCS_SUCCESS) {
				copy_size = (siidr_ptr->record_size > record_size) ? record_size :
					siidr_ptr->record_size;
				for (count_1 = 0; count_1 < siidr_ptr->record_count; count_1++) {
					memcpy(tmp_list[count_1], siidr_ptr->record_list[count_1],
						copy_size);
					free(siidr_ptr->record_list[count_1]);
					siidr_ptr->record_list[count_1] = tmp_list[count_1];
				}
				free(tmp_list);
				siidr_ptr->record_size = record_size;
				return_code            = SIIDR_SUCCESS;
			}
			else {
				if (error_text != NULL)
					STR_AllocMsgPtrList(siidr_ptr->record_count,
						siidr_ptr->record_count * siidr_ptr->record_size,
						error_text, "Unable to allocate list of IDR records");
				return_code = SIIDR_MAP_ERROR_STR(return_code);
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int SIIDR_CopyIDR,
	(SIIDR *in_siidr_ptr, SIIDR **out_siidr_ptr, char *error_text));

#include <stdio.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int           return_code = SIIDR_SUCCESS;
	unsigned int  id_count    = SIIDR_TEST_ID_COUNT;
	SIIDR        *siidr_ptr_1 = NULL;
	SIIDR        *siidr_ptr_2 = NULL;
	unsigned int  count_1;
	char          error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test harness for function 'SIIDR_SetIDRRecordSize()'\n");
	fprintf(stderr,
		"                          'SIIDR_SetIDRRecordSizeRaw()'\n");
	fprintf(stderr,
		"---- ------- --- -------- -----------------------------\n\n");

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

	fprintf(stderr, "Inserting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_TEST_FastInsertIdList(siidr_ptr_1, 1,
		id_count, 1, SIIDR_FALSE, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr_1, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

	fprintf(stderr, "Copying IDR (%u records) . . .", id_count);
	if ((return_code = SIIDR_CopyIDR(siidr_ptr_1, &siidr_ptr_2,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n\n");

	fprintf(stderr, "Changing record size from %u to %u . . .",
		siidr_ptr_1->record_size, siidr_ptr_1->record_size * 2);
	if ((return_code = SIIDR_SetIDRRecordSize(siidr_ptr_2,
		siidr_ptr_1->record_size * 2, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");
	fprintf(stderr, "Checking IDR (%u records) . . .",
		siidr_ptr_2->record_count);
	if ((return_code = SIIDR_CheckData(siidr_ptr_2, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n\n");

	fprintf(stderr, "Changing record size from %u to %u . . .",
		siidr_ptr_2->record_size, siidr_ptr_1->record_size);
	if ((return_code = SIIDR_SetIDRRecordSize(siidr_ptr_2,
		siidr_ptr_1->record_size, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");
	fprintf(stderr, "Checking IDR (%u records) . . .",
		siidr_ptr_2->record_count);
	if ((return_code = SIIDR_CheckData(siidr_ptr_2, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");
	fprintf(stderr, "Comparing %u IDR records . . .",
		siidr_ptr_2->record_count);
	if ((return_code = SIIDR_TEST_CompareIDR(siidr_ptr_1, siidr_ptr_2,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n\n");

EXIT_FUNCTION:

	SIIDR_FreeIDR(siidr_ptr_1);
	SIIDR_FreeIDR(siidr_ptr_2);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

