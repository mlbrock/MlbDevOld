/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Deletes the specified  records from an SIIDR
								structure.

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

#include <stdlib.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_DeleteSpec(SIIDR *siidr_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, char *error_text)
{
	int return_code = SIIDR_SUCCESS;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchCodeOpt(STR_CAST_FUNC_PTR(get_spec_func),
		error_text)) == SIIDR_SUCCESS) &&
		((user_data_ptr == NULL) ||
		((return_code = SIIDR_TouchRead(user_data_ptr, 1,
		"'user_data_ptr' parameter", error_text)) == SIIDR_SUCCESS))) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			SIIDR_DeleteSpecRaw(siidr_ptr, user_data_ptr, get_spec_func);
			SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void SIIDR_DeleteSpecRaw(SIIDR *siidr_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func)
{
	unsigned int count_1;

	if (siidr_ptr->record_count) {
		if (get_spec_func == NULL)
			SIIDR_DeleteAllRaw(siidr_ptr);
		else {
			for (count_1 = siidr_ptr->record_count; count_1; ) {
				count_1--;
				if ((*get_spec_func)(siidr_ptr, user_data_ptr,
					siidr_ptr->record_list[count_1]) == SIIDR_TRUE) {
					free(siidr_ptr->record_list[count_1]);
					siidr_ptr->record_list[count_1] = NULL;
					memmove_delete_voidptr(siidr_ptr->record_count,
						siidr_ptr->record_list, count_1, 1);
					siidr_ptr->record_count--;
				}
			}
		}
	}
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

	fprintf(stderr, "Test harness for function 'SIIDR_DeleteSpec()'\n");
	fprintf(stderr, "                          'SIIDR_DeleteSpecRaw()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------------------\n\n");

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
		fprintf(stderr, "Inserting %u records in the IDR . . .", id_count);
		if ((return_code = SIIDR_TEST_FastInsertIdList(siidr_ptr, 1,
			id_count, 1, SIIDR_FALSE, error_text)) != SIIDR_SUCCESS)
			goto EXIT_FUNCTION;
		else if ((return_code = SIIDR_CheckData(siidr_ptr, error_text)) !=
			SIIDR_SUCCESS)
			goto EXIT_FUNCTION;
		fprintf(stderr, " done\n");
		fprintf(stderr, "Deleting even records from the IDR . . .");
		if ((return_code = SIIDR_DeleteSpec(siidr_ptr, NULL,
			((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityEven), error_text)) !=
			SIIDR_SUCCESS)
			goto EXIT_FUNCTION;
		else if ((return_code = SIIDR_CheckData(siidr_ptr, error_text)) !=
			SIIDR_SUCCESS)
			goto EXIT_FUNCTION;
		fprintf(stderr, " done (%u records remain)\n", siidr_ptr->record_count);
		fprintf(stderr, "Deleting odd records from the IDR . . .");
		if ((return_code = SIIDR_DeleteSpec(siidr_ptr, NULL,
			((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityOdd), error_text)) !=
			SIIDR_SUCCESS)
			goto EXIT_FUNCTION;
		else if ((return_code = SIIDR_CheckData(siidr_ptr, error_text)) !=
			SIIDR_SUCCESS)
			goto EXIT_FUNCTION;
		fprintf(stderr, " done (%u records remain)\n", siidr_ptr->record_count);
	}

EXIT_FUNCTION:

	SIIDR_FreeIDR(siidr_ptr);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

