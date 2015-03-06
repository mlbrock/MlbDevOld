/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Echos command line arguments to stdout.

	Revision History	:	2002-10-09 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2002 - 2015.
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

#include <strfuncs.h>

/*	***********************************************************************	*/

#define ECHOARGS_FILE_NAME					"echoargs.txt"

COMPAT_FN_DECL_STATIC(void EmitArgs, (int argc, char **argv, FILE *file_ptr));

/*	***********************************************************************	*/
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int   return_code = EXIT_SUCCESS;
	FILE *file_ptr;

	EmitArgs(argc, argv, stdout);

	if ((file_ptr = fopen(ECHOARGS_FILE_NAME, "w")) != NULL) {
		EmitArgs(argc, argv, file_ptr);
		fclose(file_ptr);
	}
	else {
		fprintf(stderr, "\n\nERROR: Unable to open \'%s\' for writing.\n\n",
			ECHOARGS_FILE_NAME);
		return_code = EXIT_FAILURE;
	}

	return(EXIT_SUCCESS);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void EmitArgs(int argc, char **argv, FILE *file_ptr)
#else
int main(argc, argv, file_ptr)
int    argc;
char **argv;
FILE  *file_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if (str_space(argv[count_1], 1) == NULL)
			fprintf(file_ptr, "%s%s", (count_1 > 1) ? " " : "", argv[count_1]);
		else
			fprintf(file_ptr, "%s\"%s\"", (count_1 > 1) ? " " : "", argv[count_1]);
	}

	fprintf(file_ptr, "\n");
}
/*	***********************************************************************	*/
