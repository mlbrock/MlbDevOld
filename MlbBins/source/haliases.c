/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits a list of host names with aliases.

	Revision History	:	1993-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
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

#include <npsl.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int main, (int argc, char **argv));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int            return_code = NPSL_SUCCESS;
	unsigned int   count_1;
	unsigned int   count_2;
	unsigned int   host_count  = 0;
	char         **host_list   = NULL;
	char           error_text[NPSL_MAX_ERROR_TEXT];

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp("-h", argv[count_1])) ||
			(!stricmp("-help", argv[count_1]))) {
			fprintf(stderr, "USAGE:\n   %s %s [ %s . . . ]\n",
				extract_file_name(argv[0]),
				"<host-name> | <IP-address>",
				"<host-name> | <IP-address>");
			goto EXIT_FUNCTION;
		}
	}

	if (argc == 1) {
		sprintf(error_text, "Invalid command line --- use '-h' for help");
		return_code = NPSL_FAILURE;
		goto EXIT_FUNCTION;
	}

	return_code = 0;

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if (NPSL_ExpandHostNameList(1, argv + count_1, &host_count, &host_list,
			error_text) == NPSL_SUCCESS) {
			printf("%s", argv[count_1]);
			for (count_2 = 0; count_2 < host_count; count_2++)
				printf(" %s", host_list[count_2]);
			printf("\n");
			strl_remove_all(&host_count, &host_list);
		}
		else {
			fflush(stdout);
			fprintf(stderr, "%s ERROR: %s\n", argv[count_1], error_text);
			return_code++;
		}
	}

EXIT_FUNCTION:

	if (return_code != NPSL_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return((return_code == NPSL_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/


