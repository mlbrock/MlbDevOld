/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits the data associated with a 'struct hostent'
								structure.

	Revision History	:	1993-04-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
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
	NPSL_HOSTENT   hent_data;
	char           buffer[8192];
	char           inet_buffer[NPSL_MAX_IPV4_ADDR_STR + 1];
	char           error_text[NPSL_MAX_ERROR_TEXT];

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp("-h", argv[count_1])) ||
			(!stricmp("-help", argv[count_1]))) {
			fprintf(stderr, "USAGE:\n   %s %s [ %s . . . ]\n",
				extract_file_name(argv[0]),
				"<host-name-or-IP-address>",
				"<host-name-or-IP-address>");
			fprintf(stderr, "RESULT:\n   %s %s %s %s %s %s %s %s\n",
				"<original-host-name-or-IP-address>",
				"<struct hostent h_name>",
				"<struct hostent h_addrtype>",
				"<struct hostent h_length>",
				"<number of struct hostent h_aliases entries>",
				"[ <h_aliases entry> . . . ]",
				"<number of struct hostent h_addr_list entries>",
				"[ <h_addr_list entry> . . . ]");
			goto EXIT_FUNCTION;
		}
	}

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
		if (NPSL_GetHostByString(argv[count_1], &hent_data, buffer,
			sizeof(buffer), error_text) == NPSL_SUCCESS) {
			printf("%s %s %d %d",
				argv[count_1],
				hent_data.h_name,
				hent_data.h_addrtype,
				hent_data.h_length);
			tmp_count = NPSL_GetHostEntAliasesCount(&hent_data) - 1;
			tmp_list  = hent_data.h_aliases;
			printf(" %u", tmp_count);
			for (count_2 = 0; count_2 < tmp_count; count_2++, tmp_list++)
				printf(" %s", *tmp_list);
			tmp_count = NPSL_GetHostEntAddressCount(&hent_data) - 1;
			tmp_list  = hent_data.h_addr_list;
			printf(" %u", tmp_count);
			for (count_2 = 0; count_2 < tmp_count; count_2++, tmp_list++)
				printf(" %s", NPSL_AddrToINet(*tmp_list, inet_buffer));
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


