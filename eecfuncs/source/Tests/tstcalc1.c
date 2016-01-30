/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Expression Evaluation Calculator Library (EECFUNCS) Test Module			*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Elapsed time test routine.

	Revision History	:	1996-02-04 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
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

#include <sdtif.h>

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

COMPAT_FN_DECL(int main, (int argc, char **argv));

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
	int              return_code     = EEC_SUCCESS;
	unsigned int     iteration_count = 10000;
	unsigned int     formula_length  = 10;
	char            *formula_data    = NULL;
	char            *formula_ptr;
	unsigned int     percent_done;
	unsigned int     tmp_percent_done;
	unsigned int     count_1;
	unsigned int     parse_index;
	EEC_CONTROL      control_data;
	EEC_POSTFIX      postfix_data;
	EEC_DATUM        result;
	SDTIF_STAT_TVAL  parse_stat_1;
	SDTIF_STAT_TVAL  parse_stat_2;
	SDTIF_STAT_TVAL  parse_stat_3;
	SDTIF_STAT_TVAL  evals_stat_1;
	SDTIF_STAT_TVAL  evals_stat_2;
	SDTIF_STAT_TVAL  evals_stat_3;
	unsigned int     normal_pfix_length;
	unsigned int     optimized_pfix_length;
   char             time_buffer[100];
	char             tmp_error_text[EEC_MAX_ERROR_TEXT];
	char             error_text[EEC_MAX_ERROR_TEXT];

	fprintf(stderr, "Stress test routine for the EECFUNCS library\n");
	fprintf(stderr, "------ ---- ------- --- --- -------- -------\n");

	EEC_INIT_EEC_CONTROL(&control_data);
	EEC_INIT_EEC_POSTFIX(&postfix_data);
	EEC_INIT_EEC_DATUM(&result);

	SDTIF_STAT_TVAL_Init(&parse_stat_1);
	SDTIF_STAT_TVAL_Init(&parse_stat_2);
	SDTIF_STAT_TVAL_Init(&parse_stat_3);
	SDTIF_STAT_TVAL_Init(&evals_stat_1);
	SDTIF_STAT_TVAL_Init(&evals_stat_2);
	SDTIF_STAT_TVAL_Init(&evals_stat_3);

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
	if (((formula_length * 6L) + 100L) > 65520L) {
		sprintf(error_text,
			"Requested allocation is too large (%lu) --- max is %lu.\n",
			(formula_length * 6L) + 100L, 65520L);
		return_code = EEC_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
#endif /* #ifdef __MSDOS__ */

	if ((formula_data = ((char *) calloc((formula_length * 6) + 100,
		sizeof(char)))) == NULL) {
		sprintf(error_text, "Unable to allocate memory (%lu).\n",
			(((unsigned long) formula_length) * 6L) + 100L);
		return_code = EEC_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	fprintf(stderr, "Allocated %lu bytes.\n", (formula_length * 6L) + 100L);

	fprintf(stderr, "Creating string ");
	*formula_data = '\0';
	formula_ptr   = formula_data;
	for (count_1 = 0; count_1 < formula_length; count_1++) {
		sprintf(formula_ptr, "%u", (rand() % 32767) + 1);
		formula_ptr    += strlen(formula_ptr);
		*formula_ptr++  = "---+++%\\/***"[((rand() >> 3) % 12)];
		if (!(count_1 % 10000))
			fprintf(stderr, ".");
	}
	*formula_ptr = '1';
	fprintf(stderr, " allocated %u bytes, used %u bytes\n\n",
		((formula_length * 6) + 100) * sizeof(char),
		strlen(formula_data) + 1);

	if ((return_code = EEC_CreateControlBasic(&control_data, EEC_FALSE, NULL,
		(formula_length * 2) + 1, 0, NULL, 0, NULL, NULL, NULL, error_text)) !=
		EEC_SUCCESS)
		goto EXIT_FUNCTION;

	SDTIF_STAT_TVAL_StartTime(&parse_stat_1);
	if ((return_code = EEC_ParseIt(&control_data, strlen(formula_data),
		formula_data, NULL, &postfix_data, &parse_index, tmp_error_text)) !=
		EEC_SUCCESS) {
		sprintf(error_text, "PARSING ERROR @ %u: %s\n", parse_index,
			tmp_error_text);
		goto EXIT_FUNCTION;
	}
	SDTIF_STAT_TVAL_EndTime(&parse_stat_1, 1L);
	EEC_FREE_PostFixPtr(&postfix_data);

	percent_done = 0;
	fprintf(stderr, "Normal parse test           : %3u%%", percent_done);
	for (count_1 = 0; count_1 < iteration_count; count_1++) {
		SDTIF_STAT_TVAL_StartTime(&parse_stat_2);
		if ((return_code = EEC_ParseIt(&control_data, strlen(formula_data),
			formula_data, NULL, &postfix_data, &parse_index, tmp_error_text)) !=
			EEC_SUCCESS) {
			sprintf(error_text, "PARSING ERROR @ %u: %s\n", parse_index,
				tmp_error_text);
			goto EXIT_FUNCTION;
		}
		SDTIF_STAT_TVAL_EndTime(&parse_stat_2, 1L);
		if (count_1 < (iteration_count - 1))
			EEC_FREE_PostFixPtr(&postfix_data);
		if (count_1 && (!(count_1 % 100)) && ((tmp_percent_done =
			((unsigned int) ((((double) (count_1 + 1)) /
			((double) iteration_count)) * 100.0))) != percent_done))
			fprintf(stderr, "\b\b\b\b%3u%%", percent_done = tmp_percent_done);
	}
	fprintf(stderr, "\b\b\b\b%3u%%\n", 100);

	SDTIF_STAT_TVAL_StartTime(&evals_stat_1);
	if ((return_code = EEC_EvalIt(&control_data, &postfix_data, &result,
		tmp_error_text)) != EEC_SUCCESS) {
		sprintf(error_text, "EVALUATION ERROR: %s\n", tmp_error_text);
		goto EXIT_FUNCTION;
	}
	SDTIF_STAT_TVAL_EndTime(&evals_stat_1, 1L);
	EEC_FREE_DatumPtr(&result);

	percent_done = 0;
	fprintf(stderr, "Normal evaluation test      : %3u%%", percent_done);
	for (count_1 = 0; count_1 < iteration_count; count_1++) {
		SDTIF_STAT_TVAL_StartTime(&evals_stat_2);
		if ((return_code = EEC_EvalIt(&control_data, &postfix_data, &result,
			tmp_error_text)) != EEC_SUCCESS) {
			sprintf(error_text, "EVALUATION ERROR: %s\n", tmp_error_text);
			goto EXIT_FUNCTION;
		}
		SDTIF_STAT_TVAL_EndTime(&evals_stat_2, 1L);
		EEC_FREE_DatumPtr(&result);
		if (count_1 && (!(count_1 % 100)) && ((tmp_percent_done =
			((unsigned int) ((((double) (count_1 + 1)) /
			((double) iteration_count)) * 100.0))) != percent_done))
			fprintf(stderr, "\b\b\b\b%3u%%", percent_done = tmp_percent_done);
	}
	fprintf(stderr, "\b\b\b\b%3u%%\n", 100);

	normal_pfix_length = postfix_data.length;
	EEC_FREE_PostFixPtr(&postfix_data);

	control_data.optimize_flag = EEC_TRUE;

	percent_done = 0;
	fprintf(stderr, "Optimzed parse test         : %3u%%", percent_done);
	for (count_1 = 0; count_1 < iteration_count; count_1++) {
		SDTIF_STAT_TVAL_StartTime(&parse_stat_3);
		if ((return_code = EEC_ParseIt(&control_data, strlen(formula_data),
			formula_data, NULL, &postfix_data, &parse_index, tmp_error_text)) !=
			EEC_SUCCESS) {
			sprintf(error_text, "PARSING ERROR @ %u: %s\n", parse_index,
				tmp_error_text);
			goto EXIT_FUNCTION;
		}
		SDTIF_STAT_TVAL_EndTime(&parse_stat_3, 1L);
		if (count_1 < (iteration_count - 1))
			EEC_FREE_PostFixPtr(&postfix_data);
		if (count_1 && (!(count_1 % 100)) && ((tmp_percent_done =
			((unsigned int) ((((double) (count_1 + 1)) /
			((double) iteration_count)) * 100.0))) != percent_done))
			fprintf(stderr, "\b\b\b\b%3u%%", percent_done = tmp_percent_done);
	}
	fprintf(stderr, "\b\b\b\b%3u%%\n", 100);

	percent_done = 0;
	fprintf(stderr, "Optimized parse test        : %3u%%", percent_done);
	for (count_1 = 0; count_1 < iteration_count; count_1++) {
		SDTIF_STAT_TVAL_StartTime(&evals_stat_3);
		if ((return_code = EEC_EvalIt(&control_data, &postfix_data, &result,
			tmp_error_text)) != EEC_SUCCESS) {
			sprintf(error_text, "EVALUATION ERROR: %s\n", tmp_error_text);
			goto EXIT_FUNCTION;
		}
		SDTIF_STAT_TVAL_EndTime(&evals_stat_3, 1L);
		EEC_FREE_DatumPtr(&result);
		if (count_1 && (!(count_1 % 100)) && ((tmp_percent_done =
			((unsigned int) ((((double) (count_1 + 1)) /
			((double) iteration_count)) * 100.0))) != percent_done))
			fprintf(stderr, "\b\b\b\b%3u%%", percent_done = tmp_percent_done);
	}
	fprintf(stderr, "\b\b\b\b%3u%%\n", 100);

	optimized_pfix_length = postfix_data.length;
	EEC_FREE_PostFixPtr(&postfix_data);

	fprintf(stderr, "\n");

	printf("ITERATION COUNT             : %u\n", iteration_count);
	printf("FORMULA LENGTH              : %u\n", formula_length);
	printf("FIRST PASS PARSE SECONDS    : %s / ",
		SDTIF_STAT_TVAL_FmtTotalInterval(&parse_stat_1, time_buffer));
	printf("%s\n",
		SDTIF_STAT_TVAL_FmtTotalAverage(&parse_stat_1, time_buffer) + 11);
	printf("FIRST EVALUATE SECONDS      : %s / ",
		SDTIF_STAT_TVAL_FmtTotalInterval(&evals_stat_1, time_buffer));
	printf("%s\n",
		SDTIF_STAT_TVAL_FmtTotalAverage(&evals_stat_1, time_buffer) + 11);
	printf("NORMAL PARSE SECONDS        : %s / ",
		SDTIF_STAT_TVAL_FmtTotalInterval(&parse_stat_2, time_buffer));
	printf("%s\n",
		SDTIF_STAT_TVAL_FmtTotalAverage(&parse_stat_2,  time_buffer) + 11);
	printf("NORMAL EVALUATE SECONDS     : %s / ",
		SDTIF_STAT_TVAL_FmtTotalInterval(&evals_stat_2, time_buffer));
	printf("%s\n",
		SDTIF_STAT_TVAL_FmtTotalAverage(&evals_stat_2, time_buffer) + 11);
	printf("OPTIMIZED PARSE SECONDS     : %s / ",
		SDTIF_STAT_TVAL_FmtTotalInterval(&parse_stat_3, time_buffer));
	printf("%s\n",
		SDTIF_STAT_TVAL_FmtTotalAverage(&parse_stat_3, time_buffer) + 11);
	printf("OPTIMIZED EVALUATE SECONDS  : %s / ",
		SDTIF_STAT_TVAL_FmtTotalInterval(&evals_stat_3, time_buffer));
	printf("%s\n",
		SDTIF_STAT_TVAL_FmtTotalAverage(&evals_stat_3, time_buffer) + 11);
	printf("NORMAL POSTFIX LENGTH       : %10u\n", normal_pfix_length);
	printf("OPTIMIZED POSTFIX LENGTH    : %10u\n", optimized_pfix_length);

EXIT_FUNCTION:

	EEC_FREE_Control(&control_data);

	if (formula_data != NULL)
		free(formula_data);

	EEC_FREE_PostFixPtr(&postfix_data);

	if (return_code != EEC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

