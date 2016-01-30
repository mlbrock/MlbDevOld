/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Inserts a record into an SIIDR structure.

	Revision History	:	1996-04-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
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
int SIIDR_InsertAt(SIIDR *siidr_ptr, unsigned int data_element,
	const void *record_ptr, char *error_text)
{
	int return_code = SIIDR_SUCCESS;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) && ((return_code = SIIDR_TouchRecordRead(siidr_ptr,
		record_ptr, error_text)) == SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			if ((return_code = SIIDR_InsertAtRaw(siidr_ptr, data_element,
				record_ptr, error_text)) == SIIDR_SUCCESS)
				return_code = SIIDR_UnLockWriterIDR(siidr_ptr, error_text);
			else
				SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_InsertAtRaw(SIIDR *siidr_ptr, unsigned int data_element,
	const void *record_ptr, char *error_text)
{
	int              return_code = SIIDR_SUCCESS;
	unsigned int     found_index;
	SDTIF_STAT_TVAL  stat_data;
	void            *tmp_ptr;
	char             tmp_error_text[SIIDR_MAX_ERROR_TEXT];

	stat_data = siidr_ptr->stat_list[SIIDR_STAT_INSERT];
	SDTIF_STAT_TVAL_StartTime(&stat_data);

	if (data_element > siidr_ptr->record_count) {
		if (error_text != NULL)
			sprintf(tmp_error_text, "%s %u --- %s %u.",
				"The number of records in the SIIDR is", siidr_ptr->record_count,
				"therefore the highest index element is", siidr_ptr->record_count);
		return_code = SIIDR_FAILURE;
	}
	else if (SIIDR_FindRecordRaw(siidr_ptr, record_ptr, &found_index) !=
		NULL) {
		if (error_text != NULL)
			chrcat(val2str_uint_cat(found_index, 10, 0,
				strcat(strcpy(tmp_error_text, "Data record key is already in "),
				"internal data repository at element number ")), '.');
		return_code = SIIDR_FAILURE;
	}
	else if (data_element &&
		((*siidr_ptr->compare_func)(siidr_ptr, record_ptr,
		siidr_ptr->record_list[data_element - 1],
		siidr_ptr->record_size) < 0)) {
		if (error_text != NULL)
			strcat(val2str_uint_cat(data_element - 1, 10, 0,
				strcpy(tmp_error_text, "The data record key at element ")),
				" is greater than the data record specified for insertion.");
		return_code = SIIDR_FAILURE;
	}
	else if (siidr_ptr->record_count &&
		(data_element < (siidr_ptr->record_count - 1)) &&
		((*siidr_ptr->compare_func)(siidr_ptr, record_ptr,
		siidr_ptr->record_list[data_element + 1],
		siidr_ptr->record_size) > 0)) {
		if (error_text != NULL)
			strcat(val2str_uint_cat(data_element + 1, 10, 0,
				strcpy(tmp_error_text, "The data record key at element ")),
				" is less than the data record specified for insertion.");
		return_code = SIIDR_FAILURE;
	}
	else if ((tmp_ptr = memdup(record_ptr, siidr_ptr->record_size)) ==
		NULL) {
		if (error_text != NULL)
			STR_AllocMsgItem(siidr_ptr->record_size, tmp_error_text,
				"%s %-.500s data record in the internal data repository",
				"Unable to allocate memory for a copied", siidr_ptr->idr_name);
		return_code = SIIDR_MEMORY_FAILURE;
	}
	else {
		if ((siidr_ptr->record_count < siidr_ptr->allocated_count) ||
			((return_code = SIIDR_AllocateIDRRaw(siidr_ptr, 1, error_text)) ==
			SIIDR_SUCCESS)) {

			if ((return_code = memmove_insert_voidptr(siidr_ptr->record_count,
				siidr_ptr->record_list, data_element, tmp_ptr)) !=
				STRFUNCS_SUCCESS) {
				if (error_text != NULL)
					sprintf(error_text, "%s %u (%s = 0x%p) %s %u %s.",
						"Attempt to insert at IDR record index", data_element,
						"record pointer", tmp_ptr, "into a list of",
						siidr_ptr->record_count,
						"records with 'memmove_insert_voidptr()' failed");
				return_code = SIIDR_MAP_ERROR_STR(return_code);
			}
			else {
				siidr_ptr->record_count++;
				siidr_ptr->stat_list[SIIDR_STAT_INSERT] =
					*SDTIF_STAT_TVAL_EndTime(&stat_data, 1L);
			}
		}
		if ((return_code = SIIDR_MAP_ERROR_STR(return_code)) != SIIDR_SUCCESS)
			free(tmp_ptr);
	}

	if ((return_code != SIIDR_SUCCESS) && (error_text != NULL))
		sprintf(error_text, "%s %-.500s %s %u %s: %-.*s",
			"Attempt to insert", siidr_ptr->idr_name,
			"data record element number", data_element,
			"into the internal data repository failed",
			SIIDR_MAX_ERROR_TEXT - 600, tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int              return_code = SIIDR_SUCCESS;
	unsigned int     id_count    = SIIDR_TEST_ID_COUNT;
	unsigned int    *id_list     = NULL;
	SIIDR           *siidr_ptr   = NULL;
	unsigned int     count_1;
	unsigned int     insert_index;
	SIIDR_TEST_DATA  tmp_record;
	char             error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'SIIDR_InsertAt()'\n");
	fprintf(stderr, "                          'SIIDR_InsertAtRaw()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------------------\n\n");

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

	if ((return_code = SIIDR_TEST_CreateIdList(0, id_count, 2,
		SIIDR_FALSE, &id_list, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = SIIDR_CreateIDR("order",
		sizeof(SIIDR_TEST_DATA), 0,
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr,
		error_text)) == SIIDR_SUCCESS) {
		if ((return_code = SIIDR_TEST_InsertIdList(siidr_ptr, 1, id_count, 2,
			SIIDR_FALSE, error_text)) == SIIDR_SUCCESS) {
			for (count_1 = 0; count_1 < id_count; count_1++) {
				SIIDR_TEST_SetRecord(id_list[count_1], &tmp_record);
				if ((return_code = SIIDR_InsertAt(siidr_ptr, id_list[count_1],
					&tmp_record, error_text)) != SIIDR_SUCCESS)
					goto EXIT_FUNCTION;
			}
		}
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		printf("Sequential order insertion test\n");
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		SIIDR_TEST_ShowStats(siidr_ptr);
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		return_code = SIIDR_CheckData(siidr_ptr, error_text);
		SIIDR_FreeIDR(siidr_ptr);
	}

	if (return_code != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	free(id_list);
	id_list = NULL;
	if ((return_code = SIIDR_TEST_CreateIdList(0, id_count, 2,
		SIIDR_TRUE, &id_list, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = SIIDR_CreateIDR("order",
		sizeof(SIIDR_TEST_DATA), 0,
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr,
		error_text)) == SIIDR_SUCCESS) {
		if ((return_code = SIIDR_TEST_InsertIdList(siidr_ptr, 1, id_count, 2,
			SIIDR_FALSE, error_text)) == SIIDR_SUCCESS) {
			for (count_1 = 0; count_1 < id_count; count_1++) {
				SIIDR_TEST_SetRecord(id_list[count_1], &tmp_record);
				SIIDR_FindRecordRaw(siidr_ptr, &tmp_record, &insert_index);
				if ((return_code = SIIDR_InsertAt(siidr_ptr, insert_index,
					&tmp_record, error_text)) != SIIDR_SUCCESS)
					goto EXIT_FUNCTION;
			}
		}
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		printf("Random order insertion test\n");
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		SIIDR_TEST_ShowStats(siidr_ptr);
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		return_code = SIIDR_CheckData(siidr_ptr, error_text);
		SIIDR_FreeIDR(siidr_ptr);
	}

EXIT_FUNCTION:

	SIIDR_FreeIDR(siidr_ptr);

	if (id_list != NULL)
		free(id_list);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

