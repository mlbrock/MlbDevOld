/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts ASCII control characters to spaces.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

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

#include "strfunci.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ctltospc

	SYNOPSIS		:	return_ptr = ctltospc(in_string);

						char *return_ptr;

						char *in_string;

	DESCRIPTION	:	Changes control characters to spaces (ASCII 32).

   PARAMETERS  :  Parameters to this function are as follow:

   					(.) ``in_string`` is the string on which the function is to
						operate.

	RETURNS		:	A pointer to the string used as input.

   NOTES       :  Control characters are defined as any character for which
						the standard library macro ``iscntrl`` returns non-zero.

	CAVEATS		:

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2018 Michael L. Brock
 
	OUTPUT INDEX:	ctltospc
						Miscellaneous Functions:ctltospc
						STRFUNCS:Miscellaneous Functions:ctltospc
						String Functions:See STRFUNCS

	PUBLISH XREF:	ctltospc

	PUBLISH NAME:	ctltospc

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ctltospc(char *in_string)
#else
char *ctltospc(in_string)
char *in_string;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr = in_string;

	if (in_string != NULL) {
		while (*tmp_ptr) {
			*tmp_ptr = ((char) ((iscntrl(*tmp_ptr)) ? ' ' : *tmp_ptr));
			tmp_ptr++;
		}
	}

	return(in_string);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>

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
	FILE *file_ptr    = NULL;
	char  buffer[2048];

	fprintf(stderr, "Test one of STRFUNCS library function 'ctltospc()'\n");
	fprintf(stderr, "---- --- -- -------- ------- -------- ------------\n\n");

	if (argc == 1)
		fprintf(stderr, "File name expeted on command-line.\n");
	else if ((file_ptr = fopen(argv[1], "r")) == NULL)
		fprintf(stderr, "Unable to open file name '%s'.\n", argv[1]);
	else {
		return_code = 0;
		while (!feof(file_ptr)) {
			*buffer = '\0';
			fgets(buffer, sizeof(buffer) - 1, file_ptr);
			printf("%s", ctltospc(buffer));
		}
		fclose(file_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

#endif /* #ifdef TEST_MAIN */

