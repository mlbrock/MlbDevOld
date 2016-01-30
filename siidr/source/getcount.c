/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets count of records in an SIIDR structure.

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

#include <string.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_GetCount(SIIDR *siidr_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func)
{
	unsigned int found_count = 0;
	char         error_text[SIIDR_MAX_ERROR_TEXT];

	SIIDR_GetCountBasic(siidr_ptr, user_data_ptr, get_spec_func,
		&found_count, error_text);

	return(found_count);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_GetCountBasic(SIIDR *siidr_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *found_count,
	char *error_text)
{
	int          return_code;
	unsigned int tmp_found_count;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchCodeOpt(STR_CAST_FUNC_PTR(get_spec_func),
		error_text)) == SIIDR_SUCCESS) &&
		((user_data_ptr == NULL) ||
		((return_code = SIIDR_TouchRead(user_data_ptr, 1,
		"'user_data_ptr' parameter", error_text)) == SIIDR_SUCCESS)) &&
		((found_count == NULL) || ((return_code = SIIDR_TouchClear(found_count,
		sizeof(*found_count), "'found_count' parameter", error_text)) ==
		SIIDR_SUCCESS))) {
		if ((return_code = SIIDR_LockReaderIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			found_count  = (found_count != NULL) ? found_count : &tmp_found_count;
			*found_count = SIIDR_GetCountRaw(siidr_ptr, user_data_ptr,
				get_spec_func);
			return_code  = SIIDR_UnLockReaderIDR(siidr_ptr, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_GetCountRaw(SIIDR *siidr_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func)
{
	unsigned int found_count = 0;
	unsigned int found_index = 0;

	if (siidr_ptr->record_count) {
		if (get_spec_func == NULL)
			found_count = siidr_ptr->record_count;
		else {
			while (found_index < siidr_ptr->record_count) {
				if ((*get_spec_func)(siidr_ptr, user_data_ptr,
					siidr_ptr->record_list[found_index]) == SIIDR_TRUE)
					found_count++;
				found_index++;
			}
		}
	}

	return(found_count);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

#include <strfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int           return_code = SIIDR_SUCCESS;
	unsigned int  id_count    = SIIDR_TEST_ID_COUNT;
	SIIDR        *siidr_ptr   = NULL;
	unsigned int  count_1;
	unsigned int  found_count;
	unsigned int  tmp_quantity;
	char          error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test harness for function 'SIIDR_GetCount()'\n");
	fprintf(stderr,
		"                          'SIIDR_GetCountRaw()'\n");
	fprintf(stderr,
		"                          'SIIDR_GetCountBasic()'\n");
	fprintf(stderr,
		"---- ------- --- -------- -----------------------\n\n");

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
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = SIIDR_GetCountBasic(siidr_ptr, NULL, NULL,
		&found_count, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (found_count) {
		sprintf(error_text, "!!!Records found %u in empty IDR!!!",
			found_count);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "Inserting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_TEST_FastInsertIdList(siidr_ptr, 1, id_count, 1,
		SIIDR_FALSE, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

	STR_EMIT_CharLine('=', 77, NULL, NULL);
	if ((return_code = SIIDR_GetCountBasic(siidr_ptr, NULL, NULL,
		&found_count, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (!found_count) {
		sprintf(error_text, "!!!Count = 0 in non-empty IDR!!!");
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	printf("********** Records in IDR: %10u\n", found_count);
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	if ((return_code = SIIDR_GetCountBasic(siidr_ptr, NULL,
		((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityOdd),
		&found_count, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	printf("********** Records with odd quantity in IDR: %10u\n",
		found_count);
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	tmp_quantity = (rand() % id_count);
	if ((return_code = SIIDR_GetCountBasic(siidr_ptr, &tmp_quantity,
		((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantity), &found_count,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	printf("********** Records with quantity = %u in IDR: %10u\n",
		tmp_quantity, found_count);
	STR_EMIT_CharLine('=', 77, NULL, NULL);

EXIT_FUNCTION:

	if (siidr_ptr != NULL)
		SIIDR_FreeIDR(siidr_ptr);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

