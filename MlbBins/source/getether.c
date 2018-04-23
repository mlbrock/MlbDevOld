/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits the machine Ethernet Media Access Control
								(MAC) address.

	Revision History	:	1994-02-25 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
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
	int           return_code = NPSL_SUCCESS;
	int           upper_flag  = NPSL_FALSE;
	unsigned int  count_1;
	NPSL_ADDR_MAC ethernet_address;
	char          error_text[NPSL_MAX_ERROR_TEXT];

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-help")) ||
			(!stricmp(argv[count_1], "-h"))) {
			fprintf(stderr, "USAGE:\n   %s %s %s\n\n",
				extract_file_name(argv[0]),
				"[ -h | -help ]",
				"[ -upper | -lower ]");
			goto EXIT_FUNCTION;
		}
		else if (!stricmp(argv[count_1], "-upper"))
			upper_flag = NPSL_TRUE;
		else if (!stricmp(argv[count_1], "-lower"))
			upper_flag = NPSL_FALSE;
		else {
			sprintf(error_text, "Invalid command line --- use '-h' for help.");
			return_code = NPSL_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	if ((return_code = NPSL_GetMAC(&ethernet_address, error_text)) ==
		NPSL_SUCCESS)
		printf((upper_flag) ? "%02X-%02X-%02X-%02X-%02X-%02X\n" :
			"%02x-%02x-%02x-%02x-%02x-%02x\n",
			ethernet_address.octet[0],
			ethernet_address.octet[1],
			ethernet_address.octet[2],
			ethernet_address.octet[3],
			ethernet_address.octet[4],
			ethernet_address.octet[5]);

EXIT_FUNCTION:

	if (return_code != NPSL_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return((return_code == NPSL_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/


