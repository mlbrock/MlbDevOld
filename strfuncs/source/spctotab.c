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

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <stdio.h>

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
char *spctotab(char *in_string, unsigned int tab_setting)
#else
char *spctotab(in_string, tab_setting)
char         *in_string;
unsigned int  tab_setting;
#endif /* #ifndef NARGS */
{
	unsigned int  count_1;
	unsigned int  found_flag;
	char         *tmp_ptr_1   = in_string;
	char         *tmp_ptr_2;
	char         *tmp_ptr_3;

	if (!tab_setting)
		return(NULL);

	while ((*tmp_ptr_1 == ' ') || (*tmp_ptr_1 == '\t')) {
		if (*tmp_ptr_1 == ' ') {
			if (tab_setting == 1)
				*tmp_ptr_1 = '\t';
			else {
				found_flag = 1;
				for (count_1 = 1; count_1 < tab_setting; count_1++) {
					if (*(tmp_ptr_1 + count_1) != ' ') {
						found_flag = 0;
						break;
					}
				}
				if (found_flag) {
					*tmp_ptr_1 = '\t';
					tmp_ptr_2  = tmp_ptr_1 + 1;
					tmp_ptr_3  = tmp_ptr_2 + (tab_setting - 1);
					while (*(tmp_ptr_2 - 1))
						*tmp_ptr_2++ = *tmp_ptr_3++;
				}
			}
		}
		tmp_ptr_1++;
	}

	return(in_string);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <string.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

/*	***********************************************************************	*/
/*	***********************************************************************	*/
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

	fprintf(stderr, "Test one of STRFUNCS library function 'spctotab()'\n\n");
	fprintf(stderr, "---- --- -- -------- ------- -------- ------------\n");

	if (argc == 1)
		fprintf(stderr, "File name expeted on command-line.\n");
	else if ((file_ptr = fopen(argv[1], "r")) == NULL)
		fprintf(stderr, "Unable to open file name '%s'.\n", argv[1]);
	else {
		return_code = 0;
		while (!feof(file_ptr)) {
			*buffer_1 = '\0';
			fgets(buffer_1, sizeof(buffer_1) - 1, file_ptr);
			printf("%s", spctotab(strcpy(buffer_2, buffer_1), 3));
		}
		fclose(file_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

#endif /* #ifdef TEST_MAIN */

