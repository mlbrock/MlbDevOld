/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Deletes a record specified by its index order from
								an SIIDR structure.

	Revision History	:	1996-04-12 --- Creation
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
int SIIDR_Delete(SIIDR *siidr_ptr, const void *record_ptr,
	char *error_text)
{
	int return_code = SIIDR_SUCCESS;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchRecordRead(siidr_ptr,
		record_ptr, error_text)) == SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			if ((return_code = SIIDR_DeleteRaw(siidr_ptr, record_ptr,
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
int SIIDR_DeleteRaw(SIIDR *siidr_ptr, const void *record_ptr,
	char *error_text)
{
	int              return_code = SIIDR_SUCCESS;
	unsigned int     found_index;
	const void      *tmp_ptr;
	SDTIF_STAT_TVAL  stat_data;
	char             tmp_error_text[SIIDR_MAX_ERROR_TEXT];

	stat_data = siidr_ptr->stat_list[SIIDR_STAT_DELETE];
	SDTIF_STAT_TVAL_StartTime(&stat_data);

	if ((tmp_ptr = SIIDR_FindRecordRaw(siidr_ptr, record_ptr,
		&found_index)) == NULL) {
		if (error_text != NULL)
			strcpy(tmp_error_text,
				"Specified data record key is not in internal data repository.");
		return_code = SIIDR_FAILURE;
	}
	else if ((return_code = memmove_delete_voidptr(siidr_ptr->record_count,
		siidr_ptr->record_list, found_index, 1)) != STRFUNCS_SUCCESS) {
		if (error_text != NULL)
			sprintf(tmp_error_text, "%s %u (%s = 0x%p) %s %u %s.",
				"Attempt to delete IDR record index", found_index,
				"record pointer", tmp_ptr, "from a list of",
				siidr_ptr->record_count,
				"records with 'memmove_delete_voidptr()' failed");
		return_code = SIIDR_MAP_ERROR_STR(return_code);
	}
	else {
		free(((void *) tmp_ptr));
		siidr_ptr->record_list[--siidr_ptr->record_count] = NULL;
		siidr_ptr->stat_list[SIIDR_STAT_DELETE]           =
			*SDTIF_STAT_TVAL_EndTime(&stat_data, 1L);
	}

	if ((return_code != SIIDR_SUCCESS) && (error_text != NULL))
		nstrcat(strcat(nstrcat(strcpy(error_text,
			"Attempt to delete "), siidr_ptr->idr_name, 500),
			" data record from internal data repository failed: "),
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

	fprintf(stderr, "Test harness for function 'SIIDR_Delete()'\n");
	fprintf(stderr, "                          'SIIDR_DeleteRaw()'\n");
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
		if ((return_code = SIIDR_TEST_DeleteIdList(siidr_ptr, 1, id_count, 1,
			SIIDR_FALSE, error_text)) == SIIDR_SUCCESS) {
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			printf("Sequential order deletion test (reversed)\n");
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
		if ((return_code = SIIDR_TEST_DeleteIdList(siidr_ptr, 1, id_count, 1,
			SIIDR_TRUE, error_text)) == SIIDR_SUCCESS) {
			STR_EMIT_CharLine('=', 78, NULL, NULL);
			printf("Random order deletion test\n");
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

