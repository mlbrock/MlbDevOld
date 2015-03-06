/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Loads configurations from files.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2015.
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
int PCFF_LoadFromFile(PCFF_CFG *cfg_ptr, PCFF_FLAG flags, const char *in_file,
	char *error_text)
{
	PCFF_InitCfg(cfg_ptr);

	return(PCFF_AppendFromFile(cfg_ptr, flags, in_file, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_AppendFromFile(PCFF_CFG *cfg_ptr, PCFF_FLAG flags,
	const char *in_file, char *error_text)
{
	unsigned int   include_stack_count = 0;
	char         **include_stack_list  = NULL;

	return(PCFF_ProcessFromFile(cfg_ptr, flags, in_file, &include_stack_count,
		&include_stack_list, error_text));
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
	int          return_code = PCFF_SUCCESS;
	unsigned int count_1;
	PCFF_CFG     cfg_data;
	char         error_text[PCFF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for 'PCFF_LoadFromFile()'\n");
	fprintf(stderr, "                 'PCFF_AppendFromFile()'\n");
	fprintf(stderr, "---- ------- --- -----------------------\n\n");

	PCFF_InitCfg(&cfg_data);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp("-H", argv[count_1])) ||
			(!stricmp("-HELP", argv[count_1]))) {
			fprintf(stderr,
		"\n\nUSAGE:\n   %s <config-file-name> [<config-file-name> . . . ]\n\n",
				argv[0]);
			goto EXIT_FUNCTION;
		}
	}

	if (argc < 2) {
		sprintf(error_text,
			"No configuration file on command line --- use '-h' for help.");
		return_code = PCFF_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}

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

