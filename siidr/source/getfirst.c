/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the first record in an SIIDR structure.

	Revision History	:	1996-04-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
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
int SIIDR_GetFirst(SIIDR *siidr_ptr, unsigned int *out_index,
	void *out_record_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func)
{
	int  found_flag = SIIDR_FALSE;
	char error_text[SIIDR_MAX_ERROR_TEXT];

	SIIDR_GetFirstBasic(siidr_ptr, out_index, out_record_ptr, user_data_ptr,
		get_spec_func, &found_flag, error_text);

	return(found_flag);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_GetFirstBasic(SIIDR *siidr_ptr, unsigned int *out_index,
	void *out_record_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, int *found_flag, char *error_text)
{
	int return_code;
	int tmp_found_flag;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) &&
		((out_index == NULL) || ((return_code = SIIDR_TouchClear(out_index,
		sizeof(*out_index), "'out_index' parameter", error_text)) ==
		SIIDR_SUCCESS)) &&
		((return_code = SIIDR_TouchRecordClearOpt(siidr_ptr, out_record_ptr,
		error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchCodeOpt(STR_CAST_FUNC_PTR(get_spec_func),
		error_text)) == SIIDR_SUCCESS) &&
		((user_data_ptr == NULL) ||
		((return_code = SIIDR_TouchRead(user_data_ptr, 1,
		"'user_data_ptr' parameter", error_text)) == SIIDR_SUCCESS)) &&
		((found_flag == NULL) || ((return_code = SIIDR_TouchClear(found_flag,
		sizeof(*found_flag), "'found_flag' parameter", error_text)) ==
		SIIDR_SUCCESS))) {
		if ((return_code = SIIDR_LockReaderIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			found_flag  = (found_flag != NULL) ? found_flag : &tmp_found_flag;
			*found_flag = SIIDR_GetFirstRaw(siidr_ptr, out_index,
				out_record_ptr, user_data_ptr, get_spec_func);
			return_code = SIIDR_UnLockReaderIDR(siidr_ptr, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_GetFirstRaw(SIIDR *siidr_ptr, unsigned int *out_index,
	void *out_record_ptr, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func)
{
	int          found_flag = SIIDR_FALSE;
	unsigned int found_index;

	if (siidr_ptr->record_count) {
		found_index = 0;
		if (get_spec_func == NULL)
			found_flag = SIIDR_TRUE;
		else {
			while (found_index < siidr_ptr->record_count) {
				if ((found_flag = (*get_spec_func)(siidr_ptr, user_data_ptr,
					siidr_ptr->record_list[found_index])) == SIIDR_TRUE)
					break;
				found_index++;
			}
		}
		if (found_flag == SIIDR_TRUE) {
			if (out_index != NULL)
				*out_index = found_index;
			if (out_record_ptr != NULL)
				memcpy(out_record_ptr, siidr_ptr->record_list[found_index],
					siidr_ptr->record_size);
		}
	}

	return(found_flag);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

#include <strfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int              return_code = SIIDR_SUCCESS;
	unsigned int     id_count    = SIIDR_TEST_ID_COUNT;
	SIIDR           *siidr_ptr   = NULL;
	unsigned int     count_1;
	unsigned int     out_index;
	SIIDR_TEST_DATA  out_record;
	int              found_flag;
	unsigned int     tmp_quantity;
	char             error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test harness for function 'SIIDR_GetFirst()'\n");
	fprintf(stderr,
		"                          'SIIDR_GetFirstRaw()'\n");
	fprintf(stderr,
		"                          'SIIDR_GetFirstBasic()'\n");
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

	if ((return_code = SIIDR_GetFirstBasic(siidr_ptr, &out_index,
		&out_record, NULL, NULL, &found_flag, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (found_flag != SIIDR_FALSE) {
		sprintf(error_text, "!!!Record found in empty IDR!!!");
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "Inserting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_TEST_FastInsertIdList(siidr_ptr, 1, id_count, 1,
		SIIDR_FALSE, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n");

	STR_EMIT_CharLine('=', 77, NULL, NULL);
	if ((return_code = SIIDR_GetFirstBasic(siidr_ptr, &out_index,
		&out_record, NULL, NULL, &found_flag, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (found_flag != SIIDR_TRUE) {
		sprintf(error_text, "!!!First record not found in non-empty IDR!!!");
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	printf("********** First record in IDR:\n");
	SIIDR_TEST_EmitRecord(out_index, &out_record);
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	if ((return_code = SIIDR_GetFirstBasic(siidr_ptr, &out_index,
		&out_record, NULL, 
		((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityOdd),
		&found_flag, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (found_flag != SIIDR_TRUE) {
		sprintf(error_text,
			"!!!First record with odd quantity not found in non-empty IDR!!!");
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	printf("********** First record with odd quantity in IDR:\n");
	SIIDR_TEST_EmitRecord(out_index, &out_record);
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	tmp_quantity = (rand() % id_count);
	if ((return_code = SIIDR_GetFirstBasic(siidr_ptr, &out_index,
		&out_record, &tmp_quantity,
		((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantity), &found_flag,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (found_flag != SIIDR_TRUE) {
		sprintf(error_text,
			"!!!First record with quantity = %u not found in non-empty IDR!!!",
			tmp_quantity);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	printf("********** First record with quantity = %u in IDR:\n",
		tmp_quantity);
	SIIDR_TEST_EmitRecord(out_index, &out_record);
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	return_code = SIIDR_CheckData(siidr_ptr, error_text);

EXIT_FUNCTION:

	if (siidr_ptr != NULL)
		SIIDR_FreeIDR(siidr_ptr);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

