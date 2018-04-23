/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Loads configurations from memory lists.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "pcffi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
int PCFF_LoadFromList(PCFF_CFG *cfg_ptr, PCFF_FLAG flags,
	const char *source_name, unsigned int in_line_count, char **in_line_list,
	char *error_text)
{
	PCFF_InitCfg(cfg_ptr);

	return(PCFF_AppendFromList(cfg_ptr, flags, source_name, in_line_count,
		in_line_list, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_AppendFromList(PCFF_CFG *cfg_ptr, PCFF_FLAG flags,
	const char *source_name, unsigned int in_line_count, char **in_line_list,
	char *error_text)
{
	unsigned int   include_stack_count = 0;
	char         **include_stack_list  = NULL;

	return(PCFF_ProcessFromList(cfg_ptr, flags, source_name, in_line_count,
		in_line_list, &include_stack_count, &include_stack_list, error_text));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

#include <strfuncs.h>

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int  main, (int argc, char **argv));

int main(int argc, char **argv)
{
	int               return_code = PCFF_SUCCESS;
	unsigned int      count_1;
	PCFF_CFG          cfg_data;
	PCFF_PARSE_SPEC   parse_spec;
	unsigned int      line_count;
	char            **line_list;
	char              error_text[PCFF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for 'PCFF_LoadFromList()'\n");
	fprintf(stderr, "                 'PCFF_AppendFromList()'\n");
	fprintf(stderr, "---- ------- --- -----------------------\n\n");

	PCFF_InitCfg(&cfg_data);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp("-H", argv[count_1])) ||
			(!stricmp("-HELP", argv[count_1]))) {
			fprintf(stderr, "\n\nUSAGE:\n   %s [<config-file-name> . . . ]\n\n",
				argv[0]);
			goto EXIT_FUNCTION;
		}
	}

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Configuration File: %s\n", "<<<INTERNAL LIST>>>");
	PCFF_TEST_GetTestData(&line_count, &line_list, &parse_spec);
	if ((return_code = PCFF_LoadFromList(&cfg_data, PCFF_FLAG_NONE,
		"<<<INTERNAL LIST>>>", line_count, line_list, error_text)) ==
		PCFF_SUCCESS) {
		if ((return_code = PCFF_PostProcess(&cfg_data, &parse_spec,
			error_text)) != PCFF_SUCCESS)
			goto EXIT_FUNCTION;
		STR_EMIT_CharLine('-', 78, NULL, NULL);
		PCFF_TEST_ShowCfg(&cfg_data, NULL, NULL);
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		PCFF_FreeCfg(&cfg_data);
	}
	else
		goto EXIT_FUNCTION;

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		printf("Configuration File: %s\n", argv[count_1]);
		if ((return_code = PCFF_LoadFromFile(&cfg_data, PCFF_FLAG_NONE,
			argv[count_1], error_text)) != PCFF_SUCCESS)
			break;
		STR_EMIT_CharLine('-', 78, NULL, NULL);
		PCFF_TEST_ShowCfg(&cfg_data, NULL, NULL);
		STR_EMIT_CharLine('=', 78, NULL, NULL);
		PCFF_FreeCfg(&cfg_data);
	}

EXIT_FUNCTION:

	PCFF_FreeCfg(&cfg_data);

	if (return_code != PCFF_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

