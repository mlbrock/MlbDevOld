/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Deletes the records specified by a relational
								operator.

	Revision History	:	1996-04-12 --- Creation
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

#include <stdlib.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_DeleteMatch(SIIDR *siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, char *error_text)
{
	int return_code;

	if (((return_code = SIIDR_ClearErrorOpt(error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckIDR(siidr_ptr, error_text)) ==
		SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchRecordRead(siidr_ptr, in_record_ptr,
		error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_CheckRelOp(rel_op, error_text)) ==
		SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchCodeOpt(STR_CAST_FUNC_PTR(compare_func),
		error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchCodeOpt(STR_CAST_FUNC_PTR(get_spec_func),
		error_text)) == SIIDR_SUCCESS) &&
		((user_data_ptr == NULL) ||
		((return_code = SIIDR_TouchRead(user_data_ptr, 1,
		"'user_data_ptr' parameter", error_text)) == SIIDR_SUCCESS))) {
		if ((return_code = SIIDR_LockWriterIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			SIIDR_DeleteMatchRaw(siidr_ptr, in_record_ptr, rel_op,
				compare_func, user_data_ptr, get_spec_func);
			SIIDR_UnLockWriterIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
void SIIDR_DeleteMatchRaw(SIIDR *siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func)
{
	unsigned int      count_1;
	unsigned int      count_2;
	unsigned int      this_index;
	unsigned int      block_count;
	SIIDR_MATCH_BLOCK block_list[2];

	if (siidr_ptr->record_count) {
		if ((compare_func == NULL) ||
			(compare_func == siidr_ptr->compare_func)) {
			block_count = SIIDR_SetMatchBlockListRaw(siidr_ptr, in_record_ptr,
				rel_op, block_list);
			if (get_spec_func == NULL) {
				for (count_1 = block_count; count_1; ) {
					count_1--;
					for (count_2 = 0; count_2 < block_list[count_1].count;
						count_2++) {
						this_index = block_list[count_1].first + count_2;
						free(siidr_ptr->record_list[this_index]);
						siidr_ptr->record_list[this_index] = NULL;
					}
					memmove_delete_voidptr(siidr_ptr->record_count,
						siidr_ptr->record_list, block_list[count_1].first,
						block_list[count_1].count);
					siidr_ptr->record_count -= block_list[count_1].count;
				}
			}
			else {
				for (count_1 = block_count; count_1; ) {
					count_1--;
					for (count_2 = block_list[count_1].count; count_2; ) {
						this_index = block_list[count_1].first + --count_2;
						if ((*get_spec_func)(siidr_ptr, user_data_ptr,
							siidr_ptr->record_list[this_index])) {
							free(siidr_ptr->record_list[this_index]);
							memmove_delete_voidptr(siidr_ptr->record_count,
								siidr_ptr->record_list, this_index, 1);
							siidr_ptr->record_count--;
						}
					}
				}
			}
		}
		else {
			for (count_1 = siidr_ptr->record_count; count_1; ) {
				count_1--;
				if (SIIDR_TestMatchRaw(siidr_ptr, in_record_ptr,
					siidr_ptr->record_list[count_1], rel_op, compare_func,
					user_data_ptr, get_spec_func)) {
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

#include <strfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int              return_code = SIIDR_SUCCESS;
	unsigned int     id_count    = SIIDR_TEST_ID_COUNT;
	SIIDR           *siidr_ptr   = NULL;
	unsigned int     tmp_count;
	unsigned int     count_1;
	unsigned int     found_count;
	unsigned int     bucket;
	SIIDR_TEST_DATA  test_record;
	char             error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test harness for function 'SIIDR_DeleteMatch()'\n");
	fprintf(stderr,
		"                          'SIIDR_DeleteMatchRaw()'\n");
	fprintf(stderr,
		"---- ------- --- -------- ------------------------\n\n");

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

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Test Number One: Without 'SIIDR_GetSpecFunc'\n");
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	if ((return_code = SIIDR_CreateIDR("order",
		sizeof(SIIDR_TEST_DATA), 0,
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Inserting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_TEST_FastInsertIdList(siidr_ptr, 1, id_count, 1,
		SIIDR_FALSE, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n\n");

	tmp_count             = siidr_ptr->record_count;
	bucket                = ((SIIDR_TEST_DATA **) siidr_ptr->record_list)
		[(rand() % id_count)]->record_id;
	test_record.record_id = bucket;
	found_count           = SIIDR_MatchCount(siidr_ptr, &test_record,
		SIIDR_REL_OP_EQ, ((SIIDR_CompareFunc) SIIDR_TEST_CompareBucket100),
		NULL, NULL);
	fprintf(stderr, "Match count for 100 bucket %u/%u = %u\n",
		bucket / 100, bucket, found_count);
	fprintf(stderr, "Deleting matching records . .  .");
	if ((return_code = SIIDR_DeleteMatch(siidr_ptr, &test_record,
		SIIDR_REL_OP_EQ, ((SIIDR_CompareFunc) SIIDR_TEST_CompareBucket100), NULL,
		NULL, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	tmp_count -= siidr_ptr->record_count;
	fprintf(stderr, " done (%u records remain)\n", siidr_ptr->record_count);

	if (tmp_count != found_count) {
		sprintf(error_text,
			"!!!100 bucket for delete %u count (%u) not equal to match count (%u).",
			bucket / 100, tmp_count, found_count);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}

	SIIDR_FreeIDR(siidr_ptr);

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Test Number Two: With 'SIIDR_GetSpecFunc'\n");
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	if ((return_code = SIIDR_CreateIDR("order",
		sizeof(SIIDR_TEST_DATA), 0,
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	fprintf(stderr, "Inserting %u records in the IDR . . .", id_count);
	if ((return_code = SIIDR_TEST_FastInsertIdList(siidr_ptr, 1, id_count, 1,
		SIIDR_FALSE, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, " done\n\n");

	tmp_count   = siidr_ptr->record_count;
	test_record = *((SIIDR_TEST_DATA **) siidr_ptr->record_list)
		[(rand() % id_count)];
	found_count = SIIDR_MatchCount(siidr_ptr, &test_record, SIIDR_REL_OP_EQ,
		NULL, NULL, ((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityEven));
	fprintf(stderr, "Match count for 100 bucket %u/%u = %u\n",
		bucket / 100, bucket, found_count);
	fprintf(stderr, "Deleting matching records . .  .");
	if ((return_code = SIIDR_DeleteMatch(siidr_ptr, &test_record,
		SIIDR_REL_OP_EQ, NULL, NULL,
		((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityEven), error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = SIIDR_CheckData(siidr_ptr, error_text)) !=
		SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	tmp_count -= siidr_ptr->record_count;
	fprintf(stderr, " done (%u records remain)\n", siidr_ptr->record_count);

	if (tmp_count != found_count) {
		sprintf(error_text,
			"!!!100 bucket for delete %u count (%u) not equal to match count (%u).",
			bucket / 100, tmp_count, found_count);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}

	SIIDR_FreeIDR(siidr_ptr);

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("\n");

EXIT_FUNCTION:

	SIIDR_FreeIDR(siidr_ptr);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

