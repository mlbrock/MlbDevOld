/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	Revision History:
		10/27/1986 --- Creation by Michael L. Brock

		Copyright Michael L. Brock 1986 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Necessary include files . . .														*/
/* *********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#ifndef NARGS
char *STRFUNCS_strdup(const char *in_string)
#else
char *STRFUNCS_strdup(in_string)
const char *in_string;
#endif /* #ifndef NARGS */
{
	char *copied_string;

	if ((copied_string = (char *) malloc((((!in_string) ? 0 :
		strlen(in_string)) + 1) * sizeof(char))) != NULL)
		strcpy(copied_string, (!in_string) ? "" : ((char *) in_string));

	return(copied_string);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

COMPAT_FN_DECL(int main, (void));

char *TestList[] = {
	"This is a test of the strwrap() function",
	" --- the last line ends exactly on the",
	" boundary specified for wrapping.",
	"This is a test, which requires that non-",
	"space character wrapping be performed.  ",
	"(The first line is on the boundary).",
	"This test checks multiple break chars---",
	"(The first line is on the boundary).",
	"This test checks multiple break chars----",
	"(The first line is on the boundary).",
	""
};

int main()
{
	int   return_code = 0;
	int   count_1;
	int   count_2;
	char *copied_string;

	printf("TEST_MAIN for function STRFUNCS_strdup()\n");
	printf("--------- --- -------- -----------------\n\n");

	printf("Test in progress [00000]");
	for (count_1 = 0; count_1 < 10000; count_1++) {
		for (count_2 = 0; count_2 < (sizeof(TestList) / sizeof(TestList[0]));
			count_2++) {
			if ((copied_string = STRFUNCS_strdup(TestList[count_2])) == NULL) {
				fprintf(stderr, "\nFailure of 'STRFUNCS_strdup()' at %u,%u,%s\n",
					count_1, count_2, TestList[count_2]);
				return_code = -1;
				goto EXIT_FUNCTION;
			}
			free(copied_string);
		}
		printf("\b\b\b\b\b\b%05u]", count_1 + 1);
	}

	printf("\n");

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

