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

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#ifndef NARGS
char *strndup(const char *in_string, size_t count)
#else
char *strndup(in_string, count)
const char *in_string;
size_t      count;
#endif /* #ifndef NARGS */
{
	unsigned int  memory_size;
	unsigned int  copy_size;
	const char   *tmp_string;
	char         *copied_string;

	tmp_string  = (!in_string) ? "" : in_string;
	memory_size = ((count < 1) ? 0 : count) + 1;
	copy_size   = (count <= strlen(tmp_string)) ? count : strlen(tmp_string);

	if ((copied_string = (char *) calloc(memory_size, sizeof(char))) != NULL)
		memcpy(copied_string, tmp_string, copy_size * sizeof(char));

	return(copied_string);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = 0;
	unsigned int  count_1;
	char         *test_string = "This is a test of the strndup() function";
	char         *copied_string;

	printf("TEST_MAIN for function strndup()\n");
	printf("--------- --- -------- --------\n\n");

	printf("Test in progress (length = 00000)");
	for (count_1 = 0; count_1 < strlen(test_string); count_1++) {
		if (strncmp(test_string, copied_string = strndup(test_string, count_1),
			count_1)) {
			fprintf(stderr, "\nError in 'strndup()' for size %u (%s).\n",
				count_1, test_string);
			return_code = -1;
			goto EXIT_FUNCTION;
		}
		free(copied_string);
		printf("\b\b\b\b\b\b%05u)", count_1);
	}

	printf("\n");

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

