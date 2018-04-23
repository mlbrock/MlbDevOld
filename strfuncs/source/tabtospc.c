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
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <stdio.h>
#include <string.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
char *tabtospc(char *in_string, unsigned int tab_setting)
#else
char *tabtospc(in_string, tab_setting)
char         *in_string;
unsigned int  tab_setting;
#endif /* #ifndef NARGS */
{
	unsigned int  space_count;
	unsigned int  current_col = 0;
	char         *tmp_ptr_1   = in_string;
	char         *tmp_ptr_2;
	char         *tmp_ptr_3;

	while (*tmp_ptr_1) {
		if (*tmp_ptr_1 == '\t') {
			if (!tab_setting) {
				tmp_ptr_2 = tmp_ptr_1;
				while (*tmp_ptr_2) {
					*tmp_ptr_2 = *(tmp_ptr_2 + 1);
					tmp_ptr_2++;
				}
			}
			else {
				space_count  = tab_setting - (current_col % tab_setting);
				current_col += space_count;
				tmp_ptr_2    = tmp_ptr_1 + strlen(tmp_ptr_1);
				tmp_ptr_3    = tmp_ptr_2 + (space_count - 1);
				while (tmp_ptr_2 > tmp_ptr_1)
					*tmp_ptr_3-- = *tmp_ptr_2--;
				while (space_count--)
					*tmp_ptr_1++ = ' ';
			}
		}
		else {
			current_col++;
			tmp_ptr_1++;
		}
	}

	return(in_string);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (int argc, char **argv));

/*	***********************************************************************	*/
#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int   return_code = -1;
	char  buffer_1[2048];
	char  buffer_2[4096];
	FILE *file_ptr    = NULL;

	fprintf(stderr, "Test one of STRFUNCS library function 'tabtospc()'\n");
	fprintf(stderr, "---- --- -- -------- ------- -------- ------------\n\n");

	if (argc == 1)
		fprintf(stderr, "File name expeted on command-line.\n");
	else if ((file_ptr = fopen(argv[1], "r")) == NULL)
		fprintf(stderr, "Unable to open file name '%s'.\n", argv[1]);
	else {
		return_code = 0;
		while (!feof(file_ptr)) {
			*buffer_1 = '\0';
			fgets(buffer_1, sizeof(buffer_1) - 1, file_ptr);
			printf("%s", tabtospc(strcpy(buffer_2, buffer_1), 3));
		}
		fclose(file_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

#endif /* #ifdef TEST_MAIN */

