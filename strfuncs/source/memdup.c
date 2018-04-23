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
void *memdup(const void *in_area, size_t count)
#else
void *memdup(in_area, count)
const void *in_area;
size_t      count;
#endif /* #ifndef NARGS */
{
	void *tmp_area;
	void *copied_area = NULL;

	if (count > 0) {
		tmp_area = (!in_area) ? ((void *) "") : ((void *) in_area);
		if ((copied_area = malloc(count * sizeof(char))) != NULL)
			memcpy(copied_area, tmp_area, count * sizeof(char));
	}

	return(copied_area);
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
	char         *test_area = "This is a test of the memdup() function";
	char         *copied_area;

	printf("TEST_MAIN for function memdup()\n");
	printf("--------- --- -------- --------\n\n");

	printf("Test in progress (length = 00000)");
	for (count_1 = 1; count_1 < strlen(test_area); count_1++) {
		if (memcmp(test_area,
			copied_area = ((char *) memdup(test_area, count_1)), count_1)) {
			fprintf(stderr, "\nError in 'memdup()' for size %u (%s).\n",
				count_1, test_area);
			return_code = -1;
			goto EXIT_FUNCTION;
		}
		free(copied_area);
		printf("\b\b\b\b\b\b%05u)", count_1);
	}

	printf("\n");

EXIT_FUNCTION:

	return(return_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

