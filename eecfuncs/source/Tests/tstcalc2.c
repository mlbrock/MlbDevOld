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

	Revision History	:	1996-02-10 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
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

#include "eecfuncs.h"
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

#define TEST_CHARS_PER_NUMBER				16

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(void TEST_CreateFormula,
	(unsigned int formula_length, char *formula_data));
COMPAT_FN_DECL_STATIC(int  TEST_GetResult,
	(EEC_CONTROL *control_ptr, const char *formula_ptr,
	EEC_POSTFIX *postfix_ptr, EEC_DATUM *result_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int  TEST_CheckDifference,
	(const char *description, const char *formula_1, const char *formula_2,
	const EEC_POSTFIX *postfix_1, const EEC_POSTFIX *postfix_2,
	const EEC_DATUM *result_1, const EEC_DATUM *result_2, char *error_text));
COMPAT_FN_DECL_STATIC(void TEST_DescribeDifference,
	(const char *formula_1, const char *formula_2,
	const EEC_POSTFIX *postfix_1, const EEC_POSTFIX *postfix_2));

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
	int             return_code     = EEC_SUCCESS;
	unsigned int    iteration_count = 10000;
	unsigned int    formula_length  = 10;
	char           *formula_1       = NULL;
	char           *formula_2       = NULL;
	unsigned int    percent_done;
	unsigned int    tmp_percent_done;
	unsigned int    count_1;
	EEC_CONTROL     control_data;
	EEC_POSTFIX     postfix_1;
	EEC_POSTFIX     postfix_2;
	EEC_DATUM       result_1;
	EEC_DATUM       result_2;
	char            description[EEC_MAX_ERROR_TEXT];
	char            error_text[EEC_MAX_ERROR_TEXT];

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
			fprintf(stderr, "USAGE: %s [<iteration-count> [<formula-length>]]\n",
				argv[0]);
			goto EXIT_FUNCTION;
		}
	}

	if (argc > 3) {
		sprintf(error_text, "USAGE: %s [<iteration-count> [<formula-length>]]",
			argv[0]);
		return_code = EEC_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (argc > 1) {
		if (atoi(argv[1]) <= 0)
			fprintf(stderr, "Invalid iteration count ('%s') --- ignored.\n",
				argv[1]);
		else
			iteration_count = atoi(argv[1]);
	}

	if (argc > 2) {
		if (atoi(argv[2]) < 1)
			fprintf(stderr, "Invalid formula length ('%s') --- ignored.\n",
				argv[2]);
		else
			formula_length = atoi(argv[2]);
	}

	fprintf(stderr, "Iteration Count: %u\n", iteration_count);
	fprintf(stderr, "Formula Length : %u --- (%u * 2) + 1 = %u\n",
		formula_length, formula_length , (formula_length * 2) + 1);

#ifdef __MSDOS__
	if (((((unsigned long) formula_length) *
		((unsigned long) TEST_CHARS_PER_NUMBER)) + 100L) > 65520L) {
		sprintf(error_text,
			"Requested allocation is too large (%lu) --- max is %lu.\n",
			(formula_length * ((unsigned long) TEST_CHARS_PER_NUMBER)) + 100L,
			65520L);
		return_code = EEC_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
#endif /* #ifdef __MSDOS__ */

	if ((formula_1 = ((char *)
		calloc((formula_length * TEST_CHARS_PER_NUMBER) + 100,
		sizeof(char)))) == NULL) {
		sprintf(error_text, "Unable to allocate memory (%lu).\n",
			(((unsigned long) formula_length) *
			((unsigned long) TEST_CHARS_PER_NUMBER)) + 100L);
		return_code = EEC_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	fprintf(stderr, "Allocated %lu bytes.\n",
		(((unsigned long) formula_length) *
		((unsigned long) TEST_CHARS_PER_NUMBER)) + 100L);

	if ((return_code = EEC_CreateControlBasic(&control_data, EEC_FALSE, NULL,
		(formula_length * 2) + 1, 0, NULL, 0, NULL, NULL, NULL, error_text)) !=
		EEC_SUCCESS)
		goto EXIT_FUNCTION;

	percent_done = 0;
	fprintf(stderr, "Test percent done   : %3u%%", percent_done);
	for (count_1 = 0; count_1 < iteration_count; count_1++) {
		TEST_CreateFormula(formula_length, formula_1);
		if ((return_code = TEST_GetResult(&control_data, formula_1,
			&postfix_1, &result_1, error_text)) != EEC_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = EEC_GetInfixFormula(&postfix_1, EEC_FALSE,
			&formula_2, error_text)) != EEC_SUCCESS)
			goto EXIT_FUNCTION;
		if ((return_code = TEST_GetResult(&control_data, formula_2,
			&postfix_2, &result_2, error_text)) != EEC_SUCCESS)
			goto EXIT_FUNCTION;
		sprintf(description, "Iteration number %u of %u", count_1 + 1,
			iteration_count);
		if ((return_code = TEST_CheckDifference(description, formula_1,
			formula_2, &postfix_1, &postfix_2, &result_1, &result_2,
			error_text)) != EEC_SUCCESS)
			goto EXIT_FUNCTION;
		EEC_FREE_PostFixPtr(&postfix_1);
		EEC_FREE_PostFixPtr(&postfix_2);
		EEC_FREE_DatumPtr(&result_1);
		EEC_FREE_DatumPtr(&result_2);
		if (formula_2 != NULL) {
			free(formula_2);
			formula_2 = NULL;
		}
		if (count_1 && (!(count_1 % 10)) && ((tmp_percent_done =
			((unsigned int) ((((double) (count_1 + 1)) /
			((double) iteration_count)) * 100.0))) != percent_done))
			fprintf(stderr, "\b\b\b\b%3u%%", percent_done = tmp_percent_done);
	}
	fprintf(stderr, "\b\b\b\b%3u%%\n", 100);

EXIT_FUNCTION:

	EEC_FREE_Control(&control_data);

	if (formula_1 != NULL)
		free(formula_1);

	if (formula_2 != NULL)
		free(formula_2);

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
static void TEST_CreateFormula(unsigned int formula_length, char *formula_ptr)
#else
static void TEST_CreateFormula(formula_length, formula_ptr)
unsigned int  formula_length;
char         *formula_ptr;
#endif /* #ifndef NARGS */
{
	int           parend_flag = 0;
	unsigned int  count_1;
	char         *tmp_ptr;

	*formula_ptr = '\0';
	tmp_ptr      = formula_ptr;
	for (count_1 = 0; count_1 < formula_length; count_1++) {
		if (!(parend_flag)) {
			if (count_1 < (formula_length - 1))
				parend_flag = (!(rand() % 10)) ? 1 : 0;
		}
		else
			parend_flag = -1;
		if (parend_flag > 0)
			*tmp_ptr++ = '(';
		sprintf(tmp_ptr, "%u.%u", (rand() % 32767) + 1, rand() % 10000);
		tmp_ptr += strlen(tmp_ptr);
		if (parend_flag < 0) {
			*tmp_ptr++ = ')';
			parend_flag = 0;
		}
		*tmp_ptr++ = "-+%*"[((rand() >> 3) % 4)];
	}
	*tmp_ptr++ = '1';
	*tmp_ptr   = '\0';
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int TEST_GetResult(EEC_CONTROL *control_ptr, const char *formula_ptr,
	EEC_POSTFIX *postfix_ptr, EEC_DATUM *result_ptr, char *error_text)
#else
static int TEST_GetResult(control_ptr, formula_ptr, postfix_ptr, result_ptr,
	error_text)
EEC_CONTROL *control_ptr;
const char  *formula_ptr;
EEC_POSTFIX *postfix_ptr;
EEC_DATUM   *result_ptr;
char        *error_text;
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
		sprintf(error_text, "PARSING ERROR @ %u: %s\n", parse_index,
			tmp_error_text);
	else if ((return_code = EEC_EvalIt(control_ptr, postfix_ptr, result_ptr,
		tmp_error_text)) != EEC_SUCCESS)
		sprintf(error_text, "EVALUATION ERROR: %s\n", tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int  TEST_CheckDifference(const char *description, const char *formula_1,
	const char *formula_2, const EEC_POSTFIX *postfix_1,
	const EEC_POSTFIX *postfix_2, const EEC_DATUM *result_1,
	const EEC_DATUM *result_2, char *error_text)
#else
static int TEST_CheckDifference(description, formula_1, formula_2, postfix_1,
	postfix_2, result_1, result_2, error_text)
const char        *description;
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

	if (result_1->flags != result_2->flags) {
		printf("DIFFERENCE        : %s\n", description);
		printf("FLAGS DIFFERENCE  : (%u versus %u).\n",
			result_1->flags, result_2->flags);
		TEST_DescribeDifference(formula_1, formula_2, postfix_1, postfix_2);
		strcat(strcat(strcpy(error_text, description), " --- "),
			"Formula versus in-fix results differ.");
		return_code = EEC_FAILURE;
	}
	else if (result_1->flags & EEC_EVAL_FLAG_TYPE_STRING) {
		if (result_1->datum.string.length != result_2->datum.string.length) {
			printf("DIFFERENCE        : %s\n", description);
			printf("LENGTH DIFFERENCE : (%u versus %u).\n",
				result_1->datum.string.length, result_2->datum.string.length);
			TEST_DescribeDifference(formula_1, formula_2, postfix_1, postfix_2);
			strcat(strcat(strcpy(error_text, description), " --- "),
				"Formula versus in-fix results differ.");
			return_code = EEC_FAILURE;
		}
		else if (memcmp(result_1->datum.string.data,
			result_2->datum.string.data, result_1->datum.string.length)) {
			printf("DIFFERENCE        : %s\n", description);
			printf("STRING DIFFERENCE :\n");
			printf(">>> ");
			EEC_EMIT_HumanString(result_1->datum.string.length,
				result_1->datum.string.data, EEC_TRUE, 0, NULL, NULL);
			printf("\n");
			printf(">>> ");
			EEC_EMIT_HumanString(result_2->datum.string.length,
				result_2->datum.string.data, EEC_TRUE, 0, NULL, NULL);
			printf("\n");
			TEST_DescribeDifference(formula_1, formula_2, postfix_1, postfix_2);
			strcat(strcat(strcpy(error_text, description), " --- "),
				"Formula versus in-fix results differ.");
			return_code = EEC_FAILURE;
		}
	}
	else if ((result_1->flags & EEC_EVAL_FLAG_TYPE_NUMBER) &&
		(result_1->datum.number != result_2->datum.number)) {
		printf("DIFFERENCE        : %s\n", description);
		printf("NUMERIC DIFFERENCE: (%20.6f versus %20.6f).\n",
			result_1->datum.number, result_2->datum.number);
		TEST_DescribeDifference(formula_1, formula_2, postfix_1, postfix_2);
		strcat(strcat(strcpy(error_text, description), " --- "),
			"Formula versus in-fix results differ.");
		return_code = EEC_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void TEST_DescribeDifference(const char *formula_1,
	const char *formula_2, const EEC_POSTFIX *postfix_1,
	const EEC_POSTFIX *postfix_2)
#else
static void TEST_DescribeDifference(formula_1, formula_2, postfix_1,
	postfix_2)
const char        *formula_1;
const char        *formula_2;
const EEC_POSTFIX *postfix_1;
const EEC_POSTFIX *postfix_2;
#endif /* #ifndef NARGS */
{
	STR_EMIT_CharLine('=', 78, NULL, stdout);
	printf("Formula One:\n------- ----\n");
	printf("[%s]\n", formula_1);
	printf("-------------- ----------------------------------------\n");
	EEC_EMIT_PostFix(postfix_1, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, stdout);

	STR_EMIT_CharLine('=', 78, NULL, stdout);
	printf("Formula Two:\n------- ----\n");
	printf("[%s]\n", formula_2);
	printf("-------------- ----------------------------------------\n");
	EEC_EMIT_PostFix(postfix_2, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, stdout);
}
/*	***********************************************************************	*/

