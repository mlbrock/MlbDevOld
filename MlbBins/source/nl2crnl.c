/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLB Executable Module Source File													*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts NL characters to CR NL sequences.

	Revision History	:	1987-02-09 --- Creation
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
#include <sys\types.h>

#include <strfuncs.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
COMPAT_FN_DECL(int  main, (int, char **));
COMPAT_FN_DECL_STATIC(void read_stream, (FILE *));
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
	int     return_code = 0;
	int     count_1;
	FILE   *file_ptr;
	fpos_t  start_offset = 0L;

	if (argc < 2)
		read_stream(stdin);
	else {
		for (count_1 = 1; count_1 < argc; count_1++) {
			if (!strcmp(argv[count_1], "-"))
				read_stream(stdin);
			else if (!strnicmp(argv[count_1], "-o=", 3))
				start_offset = atol(argv[count_1] + 3);
			else if ((file_ptr = fopen(argv[count_1], "rb")) == NULL) {
				fprintf(stderr, "%s: Unable to open file '%s'.\n",
					extract_file_name(argv[0]), argv[count_1]);
				return_code = -1;
				break;
			}
			else {
				fseek(file_ptr, start_offset, 0);
				read_stream(file_ptr);
				fclose(file_ptr);
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void read_stream(FILE *in_file_ptr)
#else
static void read_stream(in_file_ptr)
FILE *in_file_ptr;
#endif /* #ifndef NARGS */
{
	int in_char;

	while (!feof(in_file_ptr)) {
		if ((!(in_char = fgetc(in_file_ptr))) || (in_char == '\n'))
			fprintf(stdout, "\n");
		else
			fprintf(stdout, "%c", in_char);
	}
}
/*	***********************************************************************	*/

