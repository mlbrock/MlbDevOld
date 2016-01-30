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
int SIIDR_Insert(SIIDR *siidr_ptr, const void *record_ptr,
	char *error_text)
{
	int return_code = SIIDR_SUCCESS;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchRecordRead(siidr_ptr, record_ptr,
		error_text)) == SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			if ((return_code = SIIDR_InsertRaw(siidr_ptr, record_ptr,
				error_text)) == SIIDR_SUCCESS)
				return_code = SIIDR_UnLockWriterIDR(siidr_ptr, error_text);
			else
				SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_InsertRaw(SIIDR *siidr_ptr, const void *record_ptr,
	char *error_text)
{
	int              return_code = SIIDR_SUCCESS;
	unsigned int     found_index;
	SDTIF_STAT_TVAL  stat_data;
	void            *tmp_ptr;
	char             tmp_error_text[SIIDR_MAX_ERROR_TEXT];

	stat_data = siidr_ptr->stat_list[SIIDR_STAT_INSERT];
	SDTIF_STAT_TVAL_StartTime(&stat_data);

	if (SIIDR_FindRecordRaw(siidr_ptr, record_ptr, &found_index) != NULL) {
		if (error_text != NULL)
			chrcat(val2str_uint_cat(found_index, 10, 0,
				strcat(strcpy(tmp_error_text, "Data record key is already in "),
				"internal data repository at element number ")), '.');
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
				siidr_ptr->record_list, found_index, tmp_ptr)) !=
				STRFUNCS_SUCCESS) {
				if (error_text != NULL)
					sprintf(error_text, "%s %u (%s = 0x%p) %s %u %s.",
						"Attempt to insert at IDR record index", found_index,
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
		nstrcat(strcat(nstrcat(strcpy(error_text,
			"Attempt to insert "), siidr_ptr->idr_name, 500),
			" data record into internal data repository failed: "),
			tmp_error_text, SIIDR_MAX_ERROR_TEXT - 600);

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
	SIIDR        *siidr_ptr   = NULL;
	unsigned int  count_1;
	char          error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'SIIDR_Insert()'\n");
	fprintf(stderr, "                          'SIIDR_InsertRaw()'\n");
	fprintf(stderr, "---- ------- --- -------- -------------------\n\n");

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
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr,
		error_text)) == SIIDR_SUCCESS) {
		if ((return_code = SIIDR_TEST_InsertIdList(siidr_ptr, 1, id_count, 1,
			SIIDR_FALSE, error_text)) == SIIDR_SUCCESS) {
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			printf("Sequential order insertion test\n");
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			SIIDR_TEST_ShowStats(siidr_ptr);
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			return_code = SIIDR_CheckData(siidr_ptr, error_text);
		}
		SIIDR_FreeIDR(siidr_ptr);
	}

	if (return_code != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = SIIDR_CreateIDR("order",
		sizeof(SIIDR_TEST_DATA), 0,
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr,
		error_text)) == SIIDR_SUCCESS) {
		if ((return_code = SIIDR_TEST_InsertIdList(siidr_ptr, 1, id_count, 1,
			SIIDR_TRUE, error_text)) == SIIDR_SUCCESS) {
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			printf("Random order insertion test\n");
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			SIIDR_TEST_ShowStats(siidr_ptr);
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			return_code = SIIDR_CheckData(siidr_ptr, error_text);
		}
		SIIDR_FreeIDR(siidr_ptr);
	}

EXIT_FUNCTION:

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

