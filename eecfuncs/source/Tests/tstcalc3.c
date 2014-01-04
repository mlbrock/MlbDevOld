/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Expression Evaluation Calculator Library (EECFUNCS) Test Module			*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Post-fix to in-fix test routine.

	Revision History	:	1996-02-22 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <tfread.h>

#include "eecfuncs.h"
#include "evaldefs.h"
#include "parsedat.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned _stklen = ((unsigned int) 32752);
#endif /* #ifdef __MSDOS__ */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(int  TEST_GetResult,
	(EEC_CONTROL *control_ptr, const char *file_name, unsigned int line_number,
	const char *formula_ptr, EEC_POSTFIX *postfix_ptr, EEC_DATUM *result_ptr,
	char *error_text));
COMPAT_FN_DECL_STATIC(int  TEST_CheckDifference,
	(const char *file_name, unsigned int idx_line_1, unsigned int idx_line_2,
	const char *formula_1, const char *formula_2, const EEC_POSTFIX *postfix_1,
	const EEC_POSTFIX *postfix_2, const EEC_DATUM *result_1,
	const EEC_DATUM *result_2, char *error_text));
COMPAT_FN_DECL_STATIC(void TEST_DescribeDifference,
	(const char *formula_1, const char *formula_2, const EEC_POSTFIX *postfix_1,
	const EEC_POSTFIX *postfix_2, const EEC_DATUM *result_1,
	const EEC_DATUM *result_2));
COMPAT_FN_DECL_STATIC(void TEST_DescribeOneDifference,
	(int instance, const char *formula, const EEC_POSTFIX *postfix,
	const EEC_DATUM *result));

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int             return_code   = EEC_SUCCESS;
	unsigned int    line_count_1  = 0;
	char          **line_list_1   = NULL;
	unsigned int    line_count_2  = 0;
	char          **line_list_2   = NULL;
	unsigned int   *idx_list      = NULL;
	unsigned int    percent_done;
	unsigned int    tmp_percent_done;
	unsigned int    count_1;
	unsigned int    count_2;
	EEC_CONTROL     control_data;
	EEC_POSTFIX     postfix_1;
	EEC_POSTFIX     postfix_2;
	EEC_DATUM       result_1;
	EEC_DATUM       result_2;
	char            error_text[EEC_MAX_ERROR_TEXT];
	char            tfread_error_text[TFREAD_MAX_ERROR_TEXT];

	fprintf(stderr, "Stress test routine for the EECFUNCS library\n");
	fprintf(stderr, "------ ---- ------- --- --- -------- -------\n");

	EEC_INIT_EEC_CONTROL(&control_data);
	EEC_INIT_EEC_POSTFIX(&postfix_1);
	EEC_INIT_EEC_POSTFIX(&postfix_2);
	EEC_INIT_EEC_DATUM(&result_1);
	EEC_INIT_EEC_DATUM(&result_2);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "USAGE: %s [<file-name> [<file-name>]]\n", argv[0]);
			goto EXIT_FUNCTION;
		}
	}

	if (argc < 2) {
		sprintf(error_text, "USAGE: %s [<file-name> [<file-name>]]\n", argv[0]);
		return_code = EEC_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = EEC_CreateControl(&control_data, error_text)) !=
		EEC_SUCCESS)
		goto EXIT_FUNCTION;

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		fprintf(stderr, "File: %-12s", argv[count_1]);
		if ((return_code = TFREAD_ReadLines(argv[count_1], &line_count_1,
			&line_list_1, tfread_error_text)) != TFREAD_SUCCESS) {
			nstrcpy(error_text, tfread_error_text, EEC_MAX_ERROR_TEXT - 1);
			return_code = EEC_FAILURE;
			break;
		}
		return_code = EEC_SUCCESS;
		if (!line_count_1) {
			fprintf(stderr, " --- no lines in file --- ignored");
			continue;
		}
		fprintf(stderr, " --- %8u read", line_count_1);
		if ((line_list_2 = ((char **) calloc(line_count_1,
			sizeof(char *)))) == NULL) {
			STR_AllocMsgList(line_count_1, sizeof(char *), error_text,
				"Unable to allocate list of pointers to lines");
			return_code = EEC_MEMORY_FAILURE;
			break;
		}
		if ((idx_list = ((unsigned int *) calloc(line_count_1,
			sizeof(unsigned int)))) == NULL) {
			STR_AllocMsgList(line_count_1, sizeof(unsigned int), error_text,
				"Unable to allocate list of line indices");
			return_code = EEC_MEMORY_FAILURE;
			break;
		}
		for (count_2 = 0; count_2 < line_count_1; count_2++) {
			if ((*trim(line_list_1[count_2]) != '#') && *line_list_1[count_2]) {
				line_list_2[line_count_2] = line_list_1[count_2];
				idx_list[line_count_2++]  = count_2 + 1;
			}
		}
		if (!line_count_2) {
			fprintf(stderr, " --- no active lines in file --- ignored");
			continue;
		}
		if (line_count_2 % 2) {
			sprintf(error_text, "%s '%-.500s' (%u) %s.",
				"The number of non-empty, non-comment lines in file",
				argv[count_1], line_count_2,
				"is not an integral multiple of two (2)");
			return_code = EEC_FAILURE;
			goto EXIT_FUNCTION;
		}
		else {
			percent_done = 0;
			fprintf(stderr, " --- %8u active --- percent done: %3u%%",
				line_count_2, percent_done);
			for (count_2 = 0; count_2 < (line_count_2 - 1); count_2 += 2) {
				if ((return_code = TEST_GetResult(&control_data, argv[count_1],
					count_2 + 1, line_list_2[count_2], &postfix_1, &result_1,
					error_text)) != EEC_SUCCESS)
					goto EXIT_FUNCTION;
				if ((return_code = TEST_GetResult(&control_data, argv[count_1],
					count_2 + 2, line_list_2[count_2 + 1], &postfix_2, &result_2,
					error_text)) != EEC_SUCCESS)
					goto EXIT_FUNCTION;
				if ((return_code = TEST_CheckDifference(argv[count_1],
					idx_list[count_2], idx_list[count_2 + 1], line_list_2[count_2],
					line_list_2[count_2 + 1], &postfix_1, &postfix_2, &result_1,
					&result_2, error_text)) != EEC_SUCCESS)
					goto EXIT_FUNCTION;
				EEC_FREE_PostFixPtr(&postfix_1);
				EEC_FREE_PostFixPtr(&postfix_2);
				EEC_FREE_DatumPtr(&result_1);
				EEC_FREE_DatumPtr(&result_2);
				if (count_2 && (!(count_2 % 10)) && ((tmp_percent_done =
					((unsigned int) ((((double) (count_2 + 1)) /
					((double) line_count_2)) * 100.0))) != percent_done))
					fprintf(stderr, "\b\b\b\b%3u%%",
						percent_done = tmp_percent_done);
			}
			fprintf(stderr, "\b\b\b\b%3u%%", 100);
		}
		strl_remove_all(&line_count_1, &line_list_1);
		free(line_list_2);
		free(idx_list);
		line_count_2 = 0;
		line_list_2  = NULL;
		idx_list     = NULL;
		fprintf(stderr, "\n");
	}


EXIT_FUNCTION:

	EEC_FREE_Control(&control_data);

	strl_remove_all(&line_count_1, &line_list_1);

	if (line_list_2 != NULL)
		free(line_list_2);

	if (idx_list != NULL)
		free(idx_list);

	EEC_FREE_PostFixPtr(&postfix_1);
	EEC_FREE_PostFixPtr(&postfix_2);

	EEC_FREE_DatumPtr(&result_1);
	EEC_FREE_DatumPtr(&result_2);

	if (return_code != EEC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int TEST_GetResult(EEC_CONTROL *control_ptr, const char *file_name,
	unsigned int line_number, const char *formula_ptr, EEC_POSTFIX *postfix_ptr,
	EEC_DATUM *result_ptr, char *error_text)
#else
static int TEST_GetResult(control_ptr, file_name, line_number, formula_ptr,
	postfix_ptr, result_ptr, error_text)
EEC_CONTROL  *control_ptr;
const char   *file_name;
unsigned int  line_number;
const char   *formula_ptr;
EEC_POSTFIX  *postfix_ptr;
EEC_DATUM    *result_ptr;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code;
	unsigned int parse_index;
	char         tmp_error_text[EEC_MAX_ERROR_TEXT];

	EEC_INIT_EEC_DATUM(result_ptr);

	EEC_INIT_EEC_POSTFIX(postfix_ptr);

	if ((return_code = EEC_ParseIt(control_ptr, strlen(formula_ptr),
		formula_ptr, NULL, postfix_ptr, &parse_index, tmp_error_text)) !=
		EEC_SUCCESS)
		sprintf(error_text,
			"PARSING ERROR (file='%-.500s'/line=%u/char=%u): %s\n",
			file_name, line_number, parse_index, tmp_error_text);
	else if ((return_code = EEC_EvalIt(control_ptr, postfix_ptr, result_ptr,
		tmp_error_text)) != EEC_SUCCESS)
		sprintf(error_text,
			"EVALUATION ERROR (file='%-.500s'/line=%u)     : %s\n",
			file_name, line_number, tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int TEST_CheckDifference(const char *file_name, unsigned int idx_line_1,
	unsigned int idx_line_2, const char *formula_1, const char *formula_2,
	const EEC_POSTFIX *postfix_1, const EEC_POSTFIX *postfix_2,
	const EEC_DATUM *result_1, const EEC_DATUM *result_2, char *error_text)
#else
static int TEST_CheckDifference(file_name, idx_line_1, idx_line_2,
	formula_1, formula_2, postfix_1, postfix_2, result_1, result_2, error_text)
const char        *file_name;
unsigned int       idx_line_1;
unsigned int       idx_line_2;
const char        *formula_1;
const char        *formula_2;
const EEC_POSTFIX *postfix_1;
const EEC_POSTFIX *postfix_2;
const EEC_DATUM   *result_1;
const EEC_DATUM   *result_2;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = EEC_SUCCESS;

	if (EEC_EVAL_DATUM_IS_SFLAG(result_1) &&
		EEC_EVAL_DATUM_IS_SFLAG(result_2)) {
		if ((result_1->flags & EEC_EVAL_FLAG_FLAGS_SPECIAL) !=
			(result_2->flags & EEC_EVAL_FLAG_FLAGS_SPECIAL)) {
			printf("DIFFERENCE        : File '%s', line number %u and %u.\n",
				file_name, idx_line_1, idx_line_2);
			printf("FLAGS DIFFERENCE  : (%u versus %u).\n",
				result_1->flags, result_2->flags);
			TEST_DescribeDifference(formula_1, formula_2, postfix_1, postfix_2,
				result_1, result_2);
			return_code = EEC_FAILURE;
		}
	}
	else if (result_1->flags != result_2->flags) {
		printf("DIFFERENCE        : File '%s', line number %u and %u.\n",
			file_name, idx_line_1, idx_line_2);
		printf("FLAGS DIFFERENCE  : (%u versus %u).\n",
			result_1->flags, result_2->flags);
		TEST_DescribeDifference(formula_1, formula_2, postfix_1, postfix_2,
			result_1, result_2);
		return_code = EEC_FAILURE;
	}
	else if (result_1->flags & EEC_EVAL_FLAG_TYPE_STRING) {
		if (result_1->datum.string.length != result_2->datum.string.length) {
			printf("DIFFERENCE        : File '%s', line number %u and %u.\n",
				file_name, idx_line_1, idx_line_2);
			printf("LENGTH DIFFERENCE : (%u versus %u).\n",
				result_1->datum.string.length, result_2->datum.string.length);
			TEST_DescribeDifference(formula_1, formula_2, postfix_1, postfix_2,
				result_1, result_2);
			return_code = EEC_FAILURE;
		}
		else if (memcmp(result_1->datum.string.data,
			result_2->datum.string.data, result_1->datum.string.length)) {
			printf("DIFFERENCE        : File '%s', line number %u and %u.\n",
				file_name, idx_line_1, idx_line_2);
			printf("STRING DIFFERENCE :\n");
			printf(">>> ");
			EEC_EMIT_HumanString(result_1->datum.string.length,
				result_1->datum.string.data, EEC_TRUE, 0, NULL, NULL);
			printf("\n");
			printf(">>> ");
			EEC_EMIT_HumanString(result_2->datum.string.length,
				result_2->datum.string.data, EEC_TRUE, 0, NULL, NULL);
			printf("\n");
			TEST_DescribeDifference(formula_1, formula_2, postfix_1, postfix_2,
				result_1, result_2);
			return_code = EEC_FAILURE;
		}
	}
	else if ((result_1->flags & EEC_EVAL_FLAG_TYPE_NUMBER) &&
		(result_1->datum.number != result_2->datum.number)) {
		printf("DIFFERENCE        : File '%s', line number %u and %u.\n",
			file_name, idx_line_1, idx_line_2);
		printf("NUMERIC DIFFERENCE: (%20.6f versus %20.6f).\n",
			result_1->datum.number, result_2->datum.number);
		TEST_DescribeDifference(formula_1, formula_2, postfix_1, postfix_2,
			result_1, result_2);
		return_code = EEC_FAILURE;
	}

	if (return_code != EEC_SUCCESS)
		sprintf(error_text, "File '%s', line number %u and %u --- %s.",
			file_name, idx_line_1, idx_line_2,
			"formula versus in-fix results differ");

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void TEST_DescribeDifference(const char *formula_1,
	const char *formula_2, const EEC_POSTFIX *postfix_1,
	const EEC_POSTFIX *postfix_2, const EEC_DATUM *result_1,
	const EEC_DATUM *result_2)
#else
static void TEST_DescribeDifference(formula_1, formula_2, postfix_1,
	postfix_2, result_1, result_2)
const char        *formula_1;
const char        *formula_2;
const EEC_POSTFIX *postfix_1;
const EEC_POSTFIX *postfix_2;
const EEC_DATUM   *result_1;
const EEC_DATUM   *result_2;
#endif /* #ifndef NARGS */
{
	TEST_DescribeOneDifference(1, formula_1, postfix_1, result_1);
	TEST_DescribeOneDifference(2, formula_2, postfix_2, result_2);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void TEST_DescribeOneDifference(int instance, const char *formula,
	const EEC_POSTFIX *postfix, const EEC_DATUM *result)
#else
static void TEST_DescribeOneDifference(instance, formula, postfix, result)
int                instance;
const char        *formula;
const EEC_POSTFIX *postfix;
const EEC_DATUM   *result;
#endif /* #ifndef NARGS */
{
	STR_EMIT_CharLine('=', 78, NULL, stdout);
	printf("Formula %3.3s:\n------- ----\n", (instance == 1) ? "One" : "Two");
	printf("[%s]\n", formula);
	printf("-------------- ----------------------------------------\n");
	EEC_EMIT_PostFix(postfix, NULL, NULL);
	STR_EMIT_CharLine('-', 78, NULL, stdout);
	if (EEC_EVAL_DATUM_IS_SFLAG(result))
		printf("RESULT FLAGS    : %u\n",
			result->flags & EEC_EVAL_FLAG_FLAGS_SPECIAL);
	else if (EEC_EVAL_DATUM_IS_NUMBER(result))
		printf("RESULT NUMBER   : %20.6f\n", EEC_EVAL_DATUM_GET_NUMBER(result));
	else {
		printf("RESULT STRING   : ");
		EEC_EMIT_HumanString(EEC_EVAL_DATUM_GET_STR_LEN(result),
			EEC_EVAL_DATUM_GET_STR_PTR(result), EEC_TRUE, 0, NULL, NULL);
		printf("\n");
	}
	STR_EMIT_CharLine('=', 78, NULL, stdout);
}
/*	***********************************************************************	*/

