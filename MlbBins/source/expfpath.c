/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits file and directory names expanded to their
								fully-qualified equivalents.

	Revision History	:	1996-01-02 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .															*/
/*	***********************************************************************	*/

#include <stdio.h>

#include <genfuncs.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int main, (int argc, char **argv));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int           return_code = GENFUNCS_SUCCESS;
	char         *path_name;
	unsigned int  count_1;
	char          error_text[GENFUNCS_MAX_ERROR_TEXT];

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp("-h", argv[count_1])) ||
			(!stricmp("-help", argv[count_1]))) {
			fprintf(stderr,
				"USAGE:\n   %s <file-name> [ <file-name> . . . ]\n",
				extract_file_name(argv[0]));
			goto EXIT_FUNCTION;
		}
	}

	if (argc == 1) {
		sprintf(error_text, "Invalid command line --- use '-h' for help");
		return_code = GENFUNCS_FAILURE;
	}

	return_code = 0;

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if (GEN_ExpandToFullPathName(argv[count_1], &path_name, error_text) ==
			GENFUNCS_SUCCESS) {
			printf("%s\n", path_name);
			free(path_name);
		}
		else {
			fflush(stdout);
			fprintf(stderr, "ERROR: %s\n", error_text);
			return_code++;
		}
	}

EXIT_FUNCTION:

	if (return_code != GENFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return((return_code == GENFUNCS_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/


