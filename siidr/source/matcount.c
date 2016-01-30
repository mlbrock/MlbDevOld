/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets count of records in an SIIDR structure using
								a specified matching comparison function and a
								relational operator.

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

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_MatchCount(SIIDR *siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func)
{
	unsigned int found_count = 0;
	char         error_text[SIIDR_MAX_ERROR_TEXT];

	SIIDR_MatchCountBasic(siidr_ptr, in_record_ptr, rel_op, compare_func,
		user_data_ptr, get_spec_func, &found_count, error_text);

	return(found_count);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_MatchCountBasic(SIIDR *siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *found_count,
	char *error_text)
{
	int          return_code;
	unsigned int tmp_found_count;

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
		"'user_data_ptr' parameter", error_text)) == SIIDR_SUCCESS)) &&
		((found_count == NULL) || ((return_code = SIIDR_TouchClear(found_count,
		sizeof(*found_count), "'found_count' parameter", error_text)) ==
		SIIDR_SUCCESS))) {
		if ((return_code = SIIDR_LockReaderIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			found_count  = (found_count != NULL) ? found_count : &tmp_found_count;
			*found_count = SIIDR_MatchCountRaw(siidr_ptr, in_record_ptr, rel_op,
				compare_func, user_data_ptr, get_spec_func);
			return_code  = SIIDR_UnLockReaderIDR(siidr_ptr, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
unsigned int SIIDR_MatchCountRaw(SIIDR *siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func)
{
	unsigned int      found_count = 0;
	unsigned int      count_1;
	unsigned int      count_2;
	unsigned int      block_count;
	SIIDR_MATCH_BLOCK block_list[2];

	if (siidr_ptr->record_count) {
		if ((compare_func == NULL) ||
			(compare_func == siidr_ptr->compare_func)) {
			block_count = SIIDR_SetMatchBlockListRaw(siidr_ptr, in_record_ptr,
				rel_op, block_list);
			if (get_spec_func == NULL)
				found_count = block_list[0].count +
					((block_count == 2) ? block_list[1].count : 0);
			else {
				for (count_1 = 0; count_1 < block_count; count_1++) {
					for (count_2 = 0; count_2 < block_list[count_1].count;
						count_2++)
						found_count += (*get_spec_func)(siidr_ptr, user_data_ptr,
							siidr_ptr->record_list
							[block_list[count_1].first + count_2]) ? 1 : 0;
				}
			}
		}
		else {
			for (count_1 = 0; count_1 < siidr_ptr->record_count; count_1++)
				found_count += (SIIDR_TestMatchRaw(siidr_ptr, in_record_ptr,
					siidr_ptr->record_list[count_1], rel_op, compare_func,
					user_data_ptr, get_spec_func)) ? 1 : 0;
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
	int              return_code = SIIDR_SUCCESS;
	unsigned int     id_count    = SIIDR_TEST_ID_COUNT;
	SIIDR           *siidr_ptr   = NULL;
	unsigned int     count_1;
	unsigned int     found_count_1;
	unsigned int     found_count_2;
	unsigned int     bucket;
	unsigned int     tmp_quantity;
	SIIDR_TEST_DATA  test_record;
	SDTIF_STAT_TVAL  tval_stat;
	char             buffer[SDTIF_FMTI_TIME_LEN_TIMEVAL + 1];
	char             error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test harness for function 'SIIDR_MatchCount()'\n");
	fprintf(stderr,
		"                          'SIIDR_MatchCountRaw()'\n");
	fprintf(stderr,
		"                          'SIIDR_MatchCountBasic()'\n");
	fprintf(stderr,
		"---- ------- --- -------- -------------------------\n\n");

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

	SIIDR_TEST_SetRecord(siidr_ptr->record_count + 1, &test_record);
	if ((return_code = SIIDR_MatchCountBasic(siidr_ptr, &test_record,
		SIIDR_REL_OP_NE, NULL, NULL, NULL,
		&found_count_1, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (found_count_1) {
		sprintf(error_text, "!!!Records found %u in empty IDR!!!",
			found_count_1);
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
	printf("Search for records not equal to a key not in the IDR\n");
	printf("----------------------------------------------------\n");
	SDTIF_STAT_TVAL_Init(&tval_stat);
	SDTIF_STAT_TVAL_StartTime(&tval_stat);
	SIIDR_TEST_SetRecord(siidr_ptr->record_count + 1, &test_record);
	if ((return_code = SIIDR_MatchCountBasic(siidr_ptr, &test_record,
		SIIDR_REL_OP_NE, NULL, NULL, NULL,
		&found_count_1, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	printf("*** Default comparison function   : %s\n",
		SDTIF_STAT_TVAL_FmtLastAverage(SDTIF_STAT_TVAL_EndTime(&tval_stat, 1L),
		buffer));
	if (found_count_1 != siidr_ptr->record_count) {
		sprintf(error_text, "%s (%u) %s (%u).",
			"The count returned by 'SIIDR_MatchCountBasic()'", found_count_1,
			"is not the same as the number of records in the IDR",
			siidr_ptr->record_count);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	SDTIF_STAT_TVAL_Init(&tval_stat);
	SDTIF_STAT_TVAL_StartTime(&tval_stat);
	if ((return_code = SIIDR_MatchCountBasic(siidr_ptr, &test_record,
		SIIDR_REL_OP_NE, ((SIIDR_CompareFunc) SIIDR_TEST_CompareEquivalent),
		NULL, NULL, &found_count_2, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	printf("*** Equivalent comparison function: %s\n",
		SDTIF_STAT_TVAL_FmtLastAverage(SDTIF_STAT_TVAL_EndTime(&tval_stat, 1L),
		buffer));
	if (found_count_1 != found_count_2) {
		sprintf(error_text, "%s %s (%u) %s (%u).",
			"The count returned by 'SIIDR_MatchCountBasic()'",
			"using the default comparison function", found_count_1,
			"is not the same as that using an equivalent comparison function",
			found_count_2);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	bucket = ((SIIDR_TEST_DATA **) siidr_ptr->record_list)
		[(rand() % id_count)]->record_id;
	test_record.record_id = bucket;
	if ((return_code = SIIDR_MatchCountBasic(siidr_ptr, &test_record,
		SIIDR_REL_OP_EQ, ((SIIDR_CompareFunc) SIIDR_TEST_CompareBucket100),
		NULL, NULL, &found_count_1, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	printf("********** Records with 100 bucket of %u in IDR: %10u\n",
		bucket / 100, found_count_1);
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	bucket = ((SIIDR_TEST_DATA **) siidr_ptr->record_list)
		[(rand() % id_count)]->record_id;
	test_record.record_id = bucket;
	if ((return_code = SIIDR_MatchCountBasic(siidr_ptr, &test_record,
		SIIDR_REL_OP_EQ, ((SIIDR_CompareFunc) SIIDR_TEST_CompareBucket1000),
		NULL, NULL, &found_count_1, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	printf("********** Records with 1000 bucket of %u in IDR: %10u\n",
		bucket / 1000, found_count_1);
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	if ((return_code = SIIDR_MatchCountBasic(siidr_ptr, &test_record,
		SIIDR_REL_OP_EQ, ((SIIDR_CompareFunc) SIIDR_TEST_CompareAlwaysEqual),
		NULL, ((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityOdd),
		&found_count_1, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	printf("********** Records with odd quantity in IDR: %10u\n",
		found_count_1);
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	tmp_quantity = ((SIIDR_TEST_DATA **) siidr_ptr->record_list)
		[(rand() % id_count)]->quantity;
	if ((return_code = SIIDR_MatchCountBasic(siidr_ptr, &test_record,
		SIIDR_REL_OP_EQ, ((SIIDR_CompareFunc) SIIDR_TEST_CompareAlwaysEqual),
		&tmp_quantity, ((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantity),
		&found_count_1, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	printf("********** Records with quantity = %u in IDR: %10u\n",
		tmp_quantity, found_count_1);
	STR_EMIT_CharLine('=', 77, NULL, NULL);

EXIT_FUNCTION:

	if (siidr_ptr != NULL)
		SIIDR_FreeIDR(siidr_ptr);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

