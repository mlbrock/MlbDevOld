/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses an expression.

	Revision History	:	1996-02-05 --- Creation.
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

#include <stdlib.h>
#include <string.h>

#include <pcff.h>

#include "eecfuncs.h"

/*	***********************************************************************	*/

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

/*	***********************************************************************	*/
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code     = EEC_SUCCESS;
	int          parse_tree_flag = EEC_FALSE;
	unsigned int count_1;
	unsigned int parse_index;
	EEC_CONTROL  control_data;
	EEC_POSTFIX  postfix_data;
	EEC_DATUM    result;
	char         error_text[EEC_MAX_ERROR_TEXT];

	EEC_INIT_EEC_CONTROL(&control_data);

	/*	*****************************************************************
		*****************************************************************
		First, scan the command line parameters for a help request . . .
		*****************************************************************	*/
	if (PCFF_CMLPARAM_LocateHelp(argc, argv, NULL)) {
		fprintf(stderr, "USAGE:\n   %s %s %s %s %s\n\n",
			extract_file_name(argv[0]),
			"[ -h | -help ]"
			"[ -parse_tree ]",
			"[ <expression-text> [ <expression-text> . . . ] ]");
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	return_code = EEC_CreateControl(&control_data, error_text);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if (PCFF_CMLPARAM_FindVA(argv[count_1], NULL, "-parse_tree", "-parsetree",
			"-parse", "-tree", NULL))
			parse_tree_flag = EEC_TRUE;
		else if ((return_code = EEC_ParseIt(&control_data, strlen(argv[count_1]),
			argv[count_1], NULL, &postfix_data, &parse_index, error_text)) ==
			EEC_SUCCESS) {
			if (parse_tree_flag == EEC_TRUE)
				EEC_EMIT_PostFix(&postfix_data, NULL, NULL);
			if ((return_code = EEC_EvalIt(&control_data, &postfix_data, &result,
				error_text)) == EEC_SUCCESS) {
				if (result.flags & EEC_EVAL_FLAG_TYPE_NULL)
					printf("Flag  : NULL\n");
				else if (result.flags & EEC_EVAL_FLAG_TYPE_NA)
					printf("Flag  : NA\n");
				else if (result.flags & EEC_EVAL_FLAG_TYPE_ERR)
					printf("Flag  : ERR\n");
				else if (result.flags & EEC_EVAL_FLAG_TYPE_NUMBER)
					printf("Number: %20.6f\n", result.datum.number);
				else {
					printf("String: ");
					EEC_EMIT_HumanString(result.datum.string.length,
						result.datum.string.data, EEC_TRUE, 0, NULL, NULL);
					printf("\n");
				}
				EEC_FREE_DatumPtr(&result);
			}
			else
				fprintf(stderr, "EERROR: %s\n", error_text);
			EEC_FREE_PostFixPtr(&postfix_data);
		}
		else {
			fprintf(stderr, "PERROR: %s\n", error_text);
			goto EXIT_FUNCTION;
		}
	}

EXIT_FUNCTION:

	EEC_FREE_Control(&control_data);

	if (return_code != EEC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return((return_code == EEC_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/

