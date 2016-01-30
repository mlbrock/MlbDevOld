/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits the data associated with a 'struct protoent'
								structure.

	Revision History	:	1993-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
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
	int             return_code = NPSL_SUCCESS;
	unsigned int    count_1;
	unsigned int    count_2;
	unsigned int    tmp_count;
	char          **tmp_list;
	NPSL_PROTOENT   pent_data;
	char            buffer[8192];
	char            error_text[NPSL_MAX_ERROR_TEXT];

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp("-h", argv[count_1])) ||
			(!stricmp("-help", argv[count_1]))) {
			fprintf(stderr, "USAGE:\n   %s %s [ %s . . . ]\n",
				extract_file_name(argv[0]),
				"<protocol-name-or-protocol-number>",
				"<protocol-name-or-protocol-number>");
			fprintf(stderr, "RESULT:\n   %s %s %s %s %s\n",
				"<original-protocol-name-or-protocol-number>",
				"<struct protoent p_name>",
				"<struct protoent p_proto>",
				"<number of struct protoent p_aliases entries>",
				"[ <p_aliases entry> . . . ]");
			goto EXIT_FUNCTION;
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ensure we have at least one command line argument . . .
		*****************************************************************	*/
	if (argc == 1) {
		sprintf(error_text, "Invalid command line --- use '-h' for help");
		return_code = NPSL_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Process the command line arguments . . .
		*****************************************************************	*/
	return_code = 0;
	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if (NPSL_GetProtoByString(argv[count_1], &pent_data, buffer,
			sizeof(buffer), error_text) == NPSL_SUCCESS) {
			printf("%s %s %d",
				argv[count_1],
				pent_data.p_name,
				pent_data.p_proto);
			tmp_count = NPSL_GetProtoEntAliasesCount(&pent_data) - 1;
			tmp_list  = pent_data.p_aliases;
			printf(" %u", tmp_count);
			for (count_2 = 0; count_2 < tmp_count; count_2++, tmp_list++)
				printf(" %s", *tmp_list);
			printf("\n");
		}
		else {
			fflush(stdout);
			fprintf(stderr, "%s ERROR: %s\n", argv[count_1], error_text);
			return_code++;
		}
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (return_code != NPSL_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return((return_code == NPSL_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/


