/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits the data associated with a 'struct servent'
								structure.

	Revision History	:	1993-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
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
	unsigned int   tmp_count;
	char         **tmp_list;
	NPSL_SERVENT   sent_data;
	char          *service;
	char          *protocol;
	char           args_buffer[1023 + 1];
	char           buffer[8191 + 1];
	char           error_text[NPSL_MAX_ERROR_TEXT];

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp("-h", argv[count_1])) ||
			(!stricmp("-help", argv[count_1]))) {
			fprintf(stderr, "USAGE:\n   %s %s [ %s . . . ]\n",
				extract_file_name(argv[0]),
				"<service-name-or-service-number>[=<service-protocol>]",
				"<service-name-or-service-number>[=<service-protocol>]");
			fprintf(stderr, "RESULT:\n   %s %s %s %s %s %s\n",
				"<original-service-name-or-service-number-and-service-protocol>",
				"<struct servent s_name>",
				"<struct servent s_port>",
				"<struct servent s_protocol>",
				"<number of struct servent s_aliases entries>",
				"[ <s_aliases entry> . . . ]");
			goto EXIT_FUNCTION;
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ensure we have at least one command line argument . . .
		*****************************************************************	*/
	if (argc == 1) {
		sprintf(error_text, "%s --- %s %s --- use '-h' for help",
			"Invalid command line", "expected one or more",
			"<service-name-or-service-number>[=<service-protocol>] parameters");
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
		if (strchr(argv[count_1], '=') == NULL) {
			service  = argv[count_1];
			protocol = NULL;
		}
		else if (strlen(argv[count_1]) < sizeof(args_buffer)) {
			protocol = strchr(service = strcpy(args_buffer, argv[count_1]), '=');
			*protocol++ = '\0';
		}
		else {
			fflush(stdout);
			fprintf(stderr, "%s ERROR: %s (%u) %s (%u).\n", argv[count_1],
				"The length of the service specification", strlen(argv[count_1]),
				"exceeds the maximum permissible", sizeof(args_buffer) - 1);
			return_code++;
			continue;
		}
		if (NPSL_GetServByString(service, protocol, &sent_data, buffer,
			sizeof(buffer), error_text) == NPSL_SUCCESS) {
			printf("%s %s %d %s",
				argv[count_1],
				sent_data.s_name,
				((int) ntohs(sent_data.s_port)),
				sent_data.s_proto);
			tmp_count = NPSL_GetServEntAliasesCount(&sent_data) - 1;
			tmp_list  = sent_data.s_aliases;
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


