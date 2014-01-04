/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Cracks a Tib/Rendezvous subject name into its
								constituent elements.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdlib.h>

#include <pcff.h>

#include "rvutil.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int main(int argc, char **argv)
{
	int               return_code = RVUTIL_SUCCESS;
	unsigned int      count_1;
	unsigned int      count_2;
	RVUTIL_SNAME_WORK work_name;
	char              error_text[RVUTIL_MAX_ERROR_TEXT];

	/*	*****************************************************************
		*****************************************************************
		First, scan the command line parameters for a help request . . .
		*****************************************************************	*/
	if (PCFF_CMLPARAM_LocateHelp(argc, argv, NULL)) {
		fprintf(stderr, "USAGE:\n   %s [ %s . . . ]\n\n",
			extract_file_name(argv[0]),
			"<RV-subject-name>",
			"<RV-subject-name>");
		fprintf(stderr, "RESULT:\n   %s: %s %s %s\n",
			"<RV-subject-name>",
			"<number-of-elements>",
			"<element-1>",
			"<element-2> . . . <element-n>");
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Ensure we have at least one command line argument . . .
		*****************************************************************	*/
	if (argc == 1) {
		sprintf(error_text, "Invalid command line --- use '-h' for help");
		return_code = RVUTIL_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Process the command line arguments . . .
		*****************************************************************	*/
	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		printf("%s:", argv[count_1]);
		if (RVUTIL_CrackSubjectWork(argv[count_1], &work_name,
			error_text) == RVUTIL_SUCCESS) {
			printf("%11u", work_name.element_count);
			for (count_2 = 0; count_2 < work_name.element_count; count_2++)
				printf(" %s", work_name.element_list[count_2]);
		}
		else
			printf("ERROR: %s", error_text);
		printf("\n");
	}
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (return_code != RVUTIL_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return((return_code == RVUTIL_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE);
}
/*	***********************************************************************	*/

