/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Escapes characters in a string.

	Revision History	:	1993-07-10 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	strescap

	SYNOPSIS		:	return_ptr = strescap(in_string, escape_char_list,
							escape_string);

						char *return_ptr;

						char *in_string;

						char *escape_char_list;

						char *escape_string;

	DESCRIPTION	:	Escapes specified characters within a string.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_string`` points to the string for which characters
						are to be escaped.

						(.) ``escape_char_list`` points to a string of characters
						which are to be escaped by this function.

						(.) ``escape_string`` points to the string to be used to
						escape characters.

						(-) If ``escape_string`` is ''NULL'' or points to a
						zero-length string, characters will be escaped by doubling
						their occurrence in ``in_string``.

	RETURNS		:	A pointer to ``in_string``.

	NOTES			:	

	CAVEATS		:	As this function lengthens ``in_string`` in place by
						inserting the escape sequence, the memory allocated for
						``in_string`` must be sufficient to support this. The
						following formula guarantees safety for an arbitrary
						string:

						(-) strlen(in_string) *
						(strlen(escape_string) + ((!strlen(escape_string)) ? 1 : 0))

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2015 Michael L. Brock
 
	OUTPUT INDEX:	strescap
						Miscellaneous Functions:strescap
						STRFUNCS:Miscellaneous Functions:strescap
						String Functions:See STRFUNCS

	PUBLISH XREF:	strescap

	PUBLISH NAME:	strescap

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *strescap(char *in_string, const char *escape_char_list,
	const char *escape_string)
#else
char *strescap(in_string, escape_char_list, escape_string)
char       *in_string;
const char *escape_char_list;
const char *escape_string;
#endif /* #ifndef NARGS */
{
	char    escape_buffer;
	size_t  escape_string_length;
	char   *tmp_ptr;

	if ((in_string != NULL) && *in_string && (escape_char_list != NULL) &&
		*escape_char_list) {
		tmp_ptr              = in_string;
		escape_string        = (escape_string == NULL) ? "" : escape_string;
		escape_string_length = (*escape_string) ? strlen(escape_string) : 1;
		while (*tmp_ptr) {
			if (strchr(escape_char_list, *tmp_ptr) != NULL) {
				if (!(*escape_string)) {
					escape_buffer = *tmp_ptr;
					strninst(tmp_ptr, &escape_buffer, 0, 1);
				}
				else
					strinst(tmp_ptr, escape_string, 0);
				tmp_ptr += escape_string_length;
			}
			tmp_ptr++;
		}
	}

	return(in_string);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	char *escape_string;
	char  buffer[512];

	fprintf(stderr, "Test routine for function 'strescap()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------\n\n");

	fprintf(stderr, "USAGE: cat <test-file> | %s [<escape-string>]\n\n",
		argv[0]);

	escape_string = (argc > 1) ? argv[1] : NULL;

	while ((!feof(stdin)) && (!ferror(stdin))) {
		if (fgets(buffer, sizeof(buffer) - 1, stdin) == NULL)
			break;
		while (*buffer && ((buffer[strlen(buffer) - 1] == '\r') ||
			(buffer[strlen(buffer) - 1] == '\n')))
			buffer[strlen(buffer) - 1] = '\0';
		if ((!STRFUNCS_stricmp(buffer, "QUIT")) ||
			 (!STRFUNCS_stricmp(buffer, "EXIT")))
			break;
		printf("RESULT: [%s]\n", strescap(buffer, "'\"\\", escape_string));
	}

	return(0);
}

#endif /* #ifdef TEST_MAIN */

