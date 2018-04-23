/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts tabs to spaces.

	Revision History	:	1987-02-11 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1987 - 2018.
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
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifdef __MSDOS__
extern unsigned int _stklen = 16384;
#endif /* __MSDOS__ */
/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int main, (int, char **));
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
	int           return_code = -1;
	FILE         *file_ptr    = NULL;
	unsigned int  count_1;
	char          buffer_1[4096];
	char          buffer_2[4096];

	if (argc == 1)
		fprintf(stderr, "File name expected on command-line.\n");
	else {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			if ((file_ptr = fopen(argv[count_1], "r")) == NULL)
				fprintf(stderr, "Unable to open file name '%s'.\n",
					argv[count_1]);
			else {
				return_code = 0;
				while (!feof(file_ptr)) {
					*buffer_1 = '\0';
					fgets(buffer_1, sizeof(buffer_1) - 1, file_ptr);
					printf("%s", tabtospc(strcpy(buffer_2, buffer_1), 3));
				}
			}
			fclose(file_ptr);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

