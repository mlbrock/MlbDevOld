/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies an SIIDR.

	Revision History	:	1996-04-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
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
int SIIDR_CopyIDR(SIIDR *in_siidr_ptr, SIIDR **out_siidr_ptr, char *error_text)
{
	return(SIIDR_CopyIDRBasic(in_siidr_ptr, NULL, SIIDR_REL_OP_NONE, NULL,
		NULL, NULL, out_siidr_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_CopyIDRBasic(SIIDR *in_siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, SIIDR **out_siidr_ptr, char *error_text)
{
	int return_code;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(in_siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchRecordReadOpt(in_siidr_ptr, in_record_ptr,
		error_text)) == SIIDR_SUCCESS) &&
		((rel_op == SIIDR_REL_OP_NONE) ||
		((return_code = SIIDR_CheckRelOp(rel_op, error_text)) ==
		SIIDR_SUCCESS)) &&
		((return_code = SIIDR_TouchCodeOpt(STR_CAST_FUNC_PTR(compare_func),
		error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchCodeOpt(STR_CAST_FUNC_PTR(get_spec_func),
		error_text)) == SIIDR_SUCCESS) &&
		((user_data_ptr == NULL) ||
		((return_code = SIIDR_TouchRead(user_data_ptr, 1,
		"'user_data_ptr' parameter", error_text)) == SIIDR_SUCCESS)) &&
		((return_code = SIIDR_TouchWrite(out_siidr_ptr, sizeof(*out_siidr_ptr),
		"'out_siidr_ptr' parameter", error_text)) == SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockReaderIDR(in_siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			return_code = SIIDR_CopyIDRRaw(in_siidr_ptr, in_record_ptr, rel_op,
				compare_func, user_data_ptr, get_spec_func, out_siidr_ptr,
				error_text);
			SIIDR_UnLockReaderIDR(in_siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_CopyIDRRaw(SIIDR *in_siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, SIIDR **out_siidr_ptr, char *error_text)
{
	int            return_code;
	unsigned int   tmp_count;
	void         **tmp_list;
	char           tmp_error_text[SIIDR_MAX_ERROR_TEXT];

	if ((in_record_ptr == NULL) && (rel_op != SIIDR_REL_OP_NONE)) {
		sprintf(tmp_error_text, "%s is not 'NONE' (%d).",
			"The record comparison pointer is 'NULL', but the relational operator",
			((int) rel_op));
		return_code = SIIDR_FAILURE;
	}
	else if ((in_record_ptr != NULL) && (rel_op == SIIDR_REL_OP_NONE)) {
		sprintf(tmp_error_text, "%s (0x%p), %s (%d).",
			"The record comparison pointer is not 'NULL',", in_record_ptr,
			"but the relational operator is NONE", ((int) rel_op));
		return_code = SIIDR_FAILURE;
	}
	else if (((return_code = SIIDR_CreateIDR(in_siidr_ptr->idr_name,
		in_siidr_ptr->record_size, in_siidr_ptr->allocation_size,
		in_siidr_ptr->compare_func, out_siidr_ptr, tmp_error_text)) ==
		SIIDR_SUCCESS) && in_siidr_ptr->record_count) {
		if (rel_op != SIIDR_REL_OP_NONE) {
			if (((return_code = SIIDR_MatchListPtrRaw(*out_siidr_ptr,
				in_record_ptr, rel_op, compare_func, user_data_ptr, get_spec_func,
				&tmp_count, &tmp_list, error_text)) == SIIDR_SUCCESS) &&
				tmp_count) {
				return_code = SIIDR_BulkInsertListRaw(*out_siidr_ptr, tmp_count,
					tmp_list, tmp_error_text);
				free(tmp_list);
			}
		}
		else if (get_spec_func != NULL) {
			if (((return_code = SIIDR_GetListPtrRaw(in_siidr_ptr, user_data_ptr,
				get_spec_func, &tmp_count, &tmp_list, error_text)) ==
				SIIDR_SUCCESS) && tmp_count) {
				return_code = SIIDR_BulkInsertListRaw(*out_siidr_ptr, tmp_count,
					tmp_list, tmp_error_text);
				free(tmp_list);
			}
		}
		else
			return_code = SIIDR_BulkInsertListRaw(*out_siidr_ptr,
				in_siidr_ptr->record_count, in_siidr_ptr->record_list,
				tmp_error_text);
	}

	if (return_code != SIIDR_SUCCESS) {
		SIIDR_FreeIDR(*out_siidr_ptr);
		*out_siidr_ptr = NULL;
		if (error_text != NULL)
			strcat(strcpy(error_text, "Attempt to copy IDR failed: "),
				tmp_error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

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
		"Test harness for function 'SIIDR_CopyIDR()'\n");
	fprintf(stderr,
		"                          'SIIDR_CopyIDRBasic()'\n");
	fprintf(stderr,
		"                          'SIIDR_CopyIDRRaw()'\n");
	fprintf(stderr,
		"---- ------- --- -------- ----------------------\n\n");

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
	fprintf(stderr, " done\n");

	fprintf(stderr, "Checking new IDR (%u records) . . .",
		siidr_ptr_2->record_count);
	if ((return_code = SIIDR_CheckData(siidr_ptr_2, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n\n");


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

