/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Single Index Internal Data Repository Library Source Module					*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets a list of pointers to copies of the records in
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

#include <stdlib.h>

#include <strfuncs.h>

#include "siidri.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_MatchList(SIIDR *siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *out_count, void ***out_list,
	char *error_text)
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
		"'user_data_ptr' parameter", error_text)) == SIIDR_SUCCESS)) &&
		((return_code = SIIDR_TouchWrite(out_count, sizeof(*out_count),
		"'out_count' parameter", error_text)) == SIIDR_SUCCESS) &&
		((return_code = SIIDR_TouchWrite(out_list, sizeof(*out_list),
		"'out_list' parameter", error_text)) == SIIDR_SUCCESS)) {
		if ((return_code = SIIDR_LockReaderIDR(siidr_ptr, error_text)) ==
			SIIDR_SUCCESS) {
			return_code = SIIDR_MatchListRaw(siidr_ptr, in_record_ptr, rel_op,
				compare_func, user_data_ptr, get_spec_func, out_count, out_list,
				error_text);
			SIIDR_UnLockReaderIDR(siidr_ptr, NULL);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_MatchListRaw(SIIDR *siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *out_count, void ***out_list,
	char *error_text)
{
	int            return_code;
	unsigned int   tmp_count;
	void         **tmp_list;

	*out_count = 0;
	*out_list  = NULL;

	if (((return_code = SIIDR_MatchListPtrRaw(siidr_ptr, in_record_ptr, rel_op,
		compare_func, user_data_ptr, get_spec_func, &tmp_count, &tmp_list,
		error_text)) == SIIDR_SUCCESS) && tmp_count) {
		if ((return_code = meml_copy(tmp_count, tmp_list, siidr_ptr->record_size,
			out_count, out_list)) != STRFUNCS_SUCCESS) {
			if (error_text != NULL)
				STR_AllocMsgPtrList(tmp_count, tmp_count * siidr_ptr->record_size,
					error_text,
					"Unable to allocate list of pointers to IDR records");
			return_code = SIIDR_MAP_ERROR_STR(return_code);
		}
		free(tmp_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int SIIDR_MatchListPtrRaw(SIIDR *siidr_ptr, const void *in_record_ptr,
	SIIDR_REL_OP rel_op, SIIDR_CompareFunc compare_func, void *user_data_ptr,
	SIIDR_GetSpecFunc get_spec_func, unsigned int *out_count, void ***out_list,
	char *error_text)
{
	int                return_code = SIIDR_SUCCESS;
	unsigned int       count_1;
	unsigned int       count_2;
	void              *tmp_ptr;
	unsigned int       block_count;
	SIIDR_MATCH_BLOCK  block_list[2];

	*out_count = 0;
	*out_list  = NULL;

	if (siidr_ptr->record_count) {
		if ((*out_list = ((void **) calloc(siidr_ptr->record_count,
			sizeof(void *)))) != NULL) {
			if ((compare_func == NULL) ||
				(compare_func == siidr_ptr->compare_func)) {
				block_count = SIIDR_SetMatchBlockListRaw(siidr_ptr, in_record_ptr,
					rel_op, block_list);
				if (get_spec_func == NULL) {
					for (count_1 = 0; count_1 < block_count; count_1++) {
						for (count_2 = 0; count_2 < block_list[count_1].count;
							count_2++)
							(*out_list)[(*out_count)++] =
								siidr_ptr->record_list
									[block_list[count_1].first + count_2];
					}
				}
				else {
					for (count_1 = 0; count_1 < block_count; count_1++) {
						for (count_2 = 0; count_2 < block_list[count_1].count;
							count_2++) {
                     if ((*get_spec_func)(siidr_ptr, user_data_ptr,
								tmp_ptr = siidr_ptr->record_list
								[block_list[count_1].first + count_2]))
								(*out_list)[(*out_count)++] = tmp_ptr;
						}
					}
				}
			}
			else {
				for (count_1 = 0; count_1 < siidr_ptr->record_count; count_1++) {
					if (SIIDR_TestMatchRaw(siidr_ptr, in_record_ptr,
						siidr_ptr->record_list[count_1], rel_op, compare_func,
						user_data_ptr, get_spec_func))
						(*out_list)[(*out_count)++] = siidr_ptr->record_list[count_1];
				}
			}
			if (*out_count < siidr_ptr->record_count) {
				if (!(*out_count)) {
					free(*out_list);
					*out_count = 0;
					*out_list  = NULL;
				}
				else
					*out_list = ((void **) realloc(*out_list,
						*out_count * sizeof(void *)));
			}
		}
		else {
			if (error_text != NULL)
				STR_AllocMsgList(siidr_ptr->record_count, sizeof(void *),
					error_text,
					"Unable to allocate list of pointers to IDR records");
			return_code = SIIDR_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

#include <strfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int               return_code = SIIDR_SUCCESS;
	unsigned int      id_count    = SIIDR_TEST_ID_COUNT;
	SIIDR            *siidr_ptr   = NULL;
	unsigned int      tmp_count   = 0;
	void            **tmp_list    = NULL;
	unsigned int      count_1;
	unsigned int      found_count;
	unsigned int      bucket;
	SIIDR_TEST_DATA   test_record;
	SDTIF_STAT_TVAL   tval_stat;
	char              buffer[SDTIF_FMTI_TIME_LEN_TIMEVAL + 1];
	char              error_text[SIIDR_MAX_ERROR_TEXT];

	fprintf(stderr,
		"Test harness for function 'SIIDR_MatchList()'\n");
	fprintf(stderr,
		"                          'SIIDR_MatchListRaw()'\n");
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
		((SIIDR_CompareFunc) SIIDR_TEST_Compare), &siidr_ptr,
		error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;

	SIIDR_TEST_SetRecord(siidr_ptr->record_count + 1, &test_record);
	if ((return_code = SIIDR_MatchList(siidr_ptr, &test_record,
		SIIDR_REL_OP_NE, NULL, NULL, NULL,
		&tmp_count, &tmp_list, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (tmp_count) {
		sprintf(error_text, "!!!Records found %u in empty IDR!!!",
			tmp_count);
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
	if ((return_code = SIIDR_MatchList(siidr_ptr, &test_record,
		SIIDR_REL_OP_NE, NULL, NULL, NULL,
		&tmp_count, &tmp_list, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	printf("*** Default comparison function   : %s\n",
		SDTIF_STAT_TVAL_FmtLastAverage(SDTIF_STAT_TVAL_EndTime(&tval_stat, 1L),
		buffer));
	found_count = tmp_count;
	if (found_count != siidr_ptr->record_count) {
		sprintf(error_text, "%s (%u) %s (%u).",
			"The count returned by 'SIIDR_MatchList()'", found_count,
			"is not the same as the number of records in the IDR",
			siidr_ptr->record_count);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	meml_remove_all(&tmp_count, &tmp_list);
	SDTIF_STAT_TVAL_Init(&tval_stat);
	SDTIF_STAT_TVAL_StartTime(&tval_stat);
	if ((return_code = SIIDR_MatchList(siidr_ptr, &test_record,
		SIIDR_REL_OP_NE, ((SIIDR_CompareFunc) SIIDR_TEST_CompareEquivalent),
		NULL, NULL, &tmp_count, &tmp_list, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	printf("*** Equivalent comparison function: %s\n",
		SDTIF_STAT_TVAL_FmtLastAverage(SDTIF_STAT_TVAL_EndTime(&tval_stat, 1L),
		buffer));
	if (found_count != tmp_count) {
		sprintf(error_text, "%s %s (%u) %s (%u).",
			"The count returned by 'SIIDR_MatchList()'",
			"using the default comparison function", found_count,
			"is not the same as that using an equivalent comparison function",
			tmp_count);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	STR_EMIT_CharLine('=', 77, NULL, NULL);

	printf("********** Records in list: %10u\n", tmp_count);
	for (count_1 = 0; count_1 < tmp_count; count_1++) {
		if (memcmp(tmp_list[count_1], siidr_ptr->record_list[count_1],
			siidr_ptr->record_size)) {
			printf("IDR/list mis-match at index %u:\n", count_1);
			printf(">>> IDR : ");
			SIIDR_TEST_EmitRecord(count_1,
				((const SIIDR_TEST_DATA *) siidr_ptr->record_list[count_1]));
			printf(">>> LIST: ");
			SIIDR_TEST_EmitRecord(count_1,
				((const SIIDR_TEST_DATA *) tmp_list[count_1]));
			sprintf(error_text, "List records not matched at index %u",
				count_1);
			return_code = SIIDR_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	meml_remove_all(&tmp_count, &tmp_list);

	bucket = ((SIIDR_TEST_DATA **) siidr_ptr->record_list)
		[(rand() % id_count)]->record_id;
	test_record.record_id = bucket;
	if ((return_code = SIIDR_MatchList(siidr_ptr, &test_record,
		SIIDR_REL_OP_EQ, ((SIIDR_CompareFunc) SIIDR_TEST_CompareBucket100),
		NULL, NULL, &tmp_count, &tmp_list, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (tmp_count != (found_count = SIIDR_MatchCount(siidr_ptr, &test_record,
		SIIDR_REL_OP_EQ, ((SIIDR_CompareFunc) SIIDR_TEST_CompareBucket100),
		NULL, NULL))) {
		sprintf(error_text,
			"!!!100 bucket for %u count (%u) not equal to IDR count (%u).",
			bucket / 100, tmp_count, found_count);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	printf("********** Records with 100 bucket of %u in IDR: %10u\n",
		bucket / 100, tmp_count);
	for (count_1 = 0; count_1 < tmp_count; count_1++) {
		if ((((SIIDR_TEST_DATA **) tmp_list)[count_1]->record_id / 100) !=
			bucket / 100) {
			printf("IDR/list 100 bucket %u/%u mis-match at index %u:\n",
				bucket / 100, bucket, count_1);
			printf(">>> IDR : ");
			SIIDR_TEST_EmitRecord(count_1,
				((const SIIDR_TEST_DATA *) siidr_ptr->record_list[count_1]));
			printf(">>> LIST: ");
			SIIDR_TEST_EmitRecord(count_1,
				((const SIIDR_TEST_DATA *) tmp_list[count_1]));
			sprintf(error_text, "List records not matched at index %u",
				count_1);
			return_code = SIIDR_FAILURE;
			goto EXIT_FUNCTION;
		}
	}
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	meml_remove_all(&tmp_count, &tmp_list);

	if ((return_code = SIIDR_MatchList(siidr_ptr, &test_record,
		SIIDR_REL_OP_EQ, ((SIIDR_CompareFunc) SIIDR_TEST_CompareAlwaysEqual),
		NULL, ((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityOdd),
		&tmp_count, &tmp_list, error_text)) != SIIDR_SUCCESS)
		goto EXIT_FUNCTION;
	if (tmp_count != (found_count = SIIDR_MatchCount(siidr_ptr, &test_record,
		SIIDR_REL_OP_EQ, ((SIIDR_CompareFunc) SIIDR_TEST_CompareAlwaysEqual),
		NULL, ((SIIDR_GetSpecFunc) SIIDR_TEST_GetSpecQuantityOdd)))) {
		sprintf(error_text, "!!!Odd list count (%u) not equal to IDR count (%u).",
			tmp_count, found_count);
		return_code = SIIDR_FAILURE;
		goto EXIT_FUNCTION;
	}
	printf("********** Records with odd quantity in IDR: %10u\n",
		tmp_count);
	STR_EMIT_CharLine('=', 77, NULL, NULL);
	meml_remove_all(&tmp_count, &tmp_list);

EXIT_FUNCTION:

	meml_remove_all(&tmp_count, &tmp_list);

	if (siidr_ptr != NULL)
		SIIDR_FreeIDR(siidr_ptr);

	if (return_code != SIIDR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

