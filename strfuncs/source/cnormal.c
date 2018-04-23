/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Normalizes C/C++ source code.

	Revision History	:	1993-07-10 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	cnormal

	SYNOPSIS		:	return_ptr = cnormal(in_string);

						char *return_ptr;

						char *in_string;

	DESCRIPTION	:	Normalizes a string containing C or C++ code to a canonical
						format by doing the following:

						(.) removing all comments;

						(.) mapping all control characters and multiple
						white-space characters to a single space; and,

						(.) removing any leading and trailing white-space.

						Text within quotes is not modified by this function.

   PARAMETERS  :  Parameters to this function are as follow:

   					(.) ``in_string`` is the string on which the function is to
						operate.

	RETURNS		:	A pointer to the string used as input.

   NOTES       :  White-space is defined as any character for which the
						standard library macro ``isspace`` returns non-zero.

						The C++ comment style (''//'') is supported by this
						function.

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

	OUTPUT INDEX:	cnormal
						Miscellaneous Functions:cnormal
						STRFUNCS:Miscellaneous Functions:cnormal
						String Functions:See STRFUNCS

	PUBLISH XREF:	cnormal

	PUBLISH NAME:	cnormal

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *cnormal(char *in_string)
#else
char *cnormal(in_string)
char *in_string;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr = in_string;

	while (*tmp_ptr) {
		if ((!isascii(*tmp_ptr)) || iscntrl(*tmp_ptr))
			*tmp_ptr++ = ' ';
		else if ((*tmp_ptr == '/') && (*(tmp_ptr + 1) == '*')) {
			*tmp_ptr++ = ' '; *tmp_ptr++ = ' ';
			while (*tmp_ptr) {
				if ((*tmp_ptr == '*') && (*(tmp_ptr + 1) == '/')) {
					*tmp_ptr++ = ' '; *tmp_ptr++ = ' ';
					break;
				}
				*tmp_ptr++ = ' ';
			}
		}
		else if ((*tmp_ptr == '/') && (*(tmp_ptr + 1) == '/')) {
			while (*tmp_ptr) {
				if (*tmp_ptr == '\n') {
					*tmp_ptr++ = ' ';
					break;
				}
				*tmp_ptr++ = ' ';
			}
		}
		else if (*tmp_ptr == '\'') {
			tmp_ptr++;
			while (*tmp_ptr) {
				if (*tmp_ptr == '\'') {
					tmp_ptr++;
					break;
				}
				else if ((*tmp_ptr == '\\') && *(tmp_ptr + 1))
					tmp_ptr++;
				tmp_ptr++;
			}
		}
		else if (*tmp_ptr == '\"') {
			tmp_ptr++;
			while (*tmp_ptr) {
				if (*tmp_ptr == '\"') {
					tmp_ptr++;
					break;
            }
				else if ((*tmp_ptr == '\\') && *(tmp_ptr + 1))
					tmp_ptr++;
				tmp_ptr++;
			}
		}
		else
			tmp_ptr++;
	}

	return(trim(oneblank(in_string)));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code = 0;
	FILE        *file_ptr    = NULL;
	char        *file_buffer = NULL;
	int          count_1;
	struct stat  stat_data;

	fprintf(stderr, "Test routine for function 'cnormal()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------\n\n");

	fprintf(stderr, "USAGE: %s <file-name> [<file-name>]\n\n", argv[0]);

	if (argc == 1) {
		fprintf(stderr, "No files specified.\n\n");
		return_code = 1;
	}

	for (count_1 = 1; count_1 < argc; count_1++) {
		fprintf(stderr, "FILE '%s' --- ", argv[count_1]);
		if (stat(argv[count_1], &stat_data)) {
			fprintf(stderr, "Unable to 'stat()' file '%s'.\n",
				argv[count_1]);
			return_code = 1;
			break;
		}
		if ((file_ptr = fopen(argv[count_1], "r")) == NULL) {
			fprintf(stderr, "Unable to open file '%s' for reading.\n",
				argv[count_1]);
			return_code = 1;
			break;
		}
		if ((file_buffer = ((char *) calloc(((size_t) stat_data.st_size) + 1,
			sizeof(char)))) == NULL) {
			fclose(file_ptr);
			fprintf(stderr, "%s '%s' (%lu bytes required).",
				"Unable to allocate memory to store a copy of the file",
				 argv[count_1], stat_data.st_size + 1);
			return_code = 1;
			break;
		}
		fread(file_buffer, ((size_t) stat_data.st_size), 1, file_ptr);
		printf("%s\n", cnormal(file_buffer));
		printf("---------------------------------------------------\n");
		free(file_buffer);
		fclose(file_ptr);
		fprintf(stderr, "DONE\n");
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

