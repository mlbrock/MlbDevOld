/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes leading zeroes from a string.

	Revision History	:	1993-07-07 --- Creation
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

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	zerotrim

	SYNOPSIS		:	string_ptr = zerotrim(text);

						char *string_ptr;

						char *text;

	DESCRIPTION	:	Removes from the string to which the ``text`` parameter
						points all leading and trailing whitespace, and all leading
						zeroes (''0'').

						If, however, removing a zero character would result in a
						blank string, that zero is not removed.

   PARAMETERS  :  Parameters to this function are as follow:

   					(.) ``text`` is the string on which the function is to
						operate.

	RETURNS		:	A pointer to the string used as input.

   NOTES       :  Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   CAVEATS     :  

   SEE ALSO    :  zerotrim_basic
						zerotrim_basic_mem
						trim

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

	OUTPUT INDEX:	zerotrim
						String Justification Functions:zerotrim
						STRFUNCS:String Justification Functions:zerotrim
						String Functions:See STRFUNCS

	PUBLISH XREF:	zerotrim

	PUBLISH NAME:	zerotrim

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *zerotrim(char *text)
#else
char *zerotrim(text)
char *text;
#endif /* #ifndef NARGS */
{
	char *temp_ptr_1 = trim(text);

	while (*temp_ptr_1 && ((*temp_ptr_1 == '0') || isspace(*temp_ptr_1)) &&
		(*(temp_ptr_1 + 1) != '\0'))
		*temp_ptr_1++ = ' ';

	return(trim(text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	zerotrim_basic

	SYNOPSIS		:	string_ptr = zerotrim_basic(in_text, out_text,
							keep_last_zero_flag);

						char       *string_ptr;

						const char *in_text;

						char       *out_text;

						int         keep_last_zero_flag;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and removes
						all leading and trailing whitespace and leading zeroes
						(''0'') from ``out_text``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the source of the string from which
						leading and trailing white-space and leading zeroes are to
						be removed.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

						(.) ``keep_last_zero_flag`` indicates whether operation of
						this function which results in the string containing a
						single ''0'' is to remove that last ''0''.

						(..) If ``keep_last_zero_flag`` is equal to ''0'', the
						last zero will be removed from the string.

						(..) If ``keep_last_zero_flag`` is non-zero, the last zero
						will not be removed from the string.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   CAVEATS     :  

   SEE ALSO    :  zerotrim
						zerotrim_basic_mem
						trim_basic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

	OUTPUT INDEX:	zerotrim_basic
						String Justification Functions:zerotrim_basic
						STRFUNCS:String Justification Functions:zerotrim_basic
						String Functions:See STRFUNCS

	PUBLISH XREF:	zerotrim_basic

	PUBLISH NAME:	zerotrim_basic

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *zerotrim_basic(const char *in_text, char *out_text,
	int keep_last_zero_flag)
#else
char *zerotrim_basic(in_text, out_text, keep_last_zero_flag)
const char *in_text;
char       *out_text;
int         keep_last_zero_flag;
#endif /* #ifndef NARGS */
{
	unsigned int tmp_length;

	zerotrim_basic_mem(strlen(in_text), in_text, &tmp_length, out_text,
		keep_last_zero_flag);
	*(out_text + tmp_length) = '\0';

	return(out_text);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	zerotrim_basic_mem

	SYNOPSIS		:	string_ptr = zerotrim_basic_mem(in_length, in_text,
							out_length, out_text, keep_last_zero_flag);

						char         *string_ptr;

						unsigned int  in_length;

						const char   *in_text;

						unsigned int *out_length;

						char         *out_text;

						int         keep_last_zero_flag;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and removes
						all leading and trailing whitespace and leading zeroes
						(''0'') from ``out_text``. The length of ``in_text`` is
						specified by the parameter ``in_length``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which
						the ``in_text`` parameter points.

						(.) ``in_text`` is the source of the string from which
						leading and trailing white-space and leading zeroes are to
						be removed.

						(.) ``out_length`` points to an an ''unsigned int'' into
						which will be placed the length of ``out_text`` upon return
						of this function.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

						(.) ``keep_last_zero_flag`` indicates whether operation of
						this function which results in the string containing a
						single ''0'' is to remove that last ''0''.

						(..) If ``keep_last_zero_flag`` is equal to ''0'', the
						last zero will be removed from the string.

						(..) If ``keep_last_zero_flag`` is non-zero, the last zero
						will not be removed from the string.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   CAVEATS     :  

   SEE ALSO    :  zerotrim
						zerotrim_basic
						trim_basic_mem

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

	OUTPUT INDEX:	zerotrim_basic_mem
						String Justification Functions:zerotrim_basic_mem
						STRFUNCS:String Justification Functions:zerotrim_basic_mem
						String Functions:See STRFUNCS

	PUBLISH XREF:	zerotrim_basic_mem

	PUBLISH NAME:	zerotrim_basic_mem

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *zerotrim_basic_mem(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, int keep_last_zero_flag)
#else
char *zerotrim_basic_mem(in_length, in_text, out_length, out_text,
	keep_last_zero_flag)
unsigned int  in_length;
const char   *in_text;
unsigned int *out_length;
char         *out_text;
int           keep_last_zero_flag;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;

	tmp_ptr   = trim_basic_mem(in_length, in_text, out_length, out_text);
	in_length = *out_length;

	while (in_length && (isspace(*tmp_ptr) || (*tmp_ptr == '0'))) {
		if (keep_last_zero_flag && (*tmp_ptr == '0') && (in_length == 1))
			break;
		*tmp_ptr++ = ' ';
		in_length--;
	}

	return(trim_basic_mem(*out_length, out_text, out_length, out_text));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

typedef struct {
	char *in;
	char *out;
} TEST_DATA;

static const TEST_DATA TestList[] = {
	{	"1234567890",				"1234567890"	},
	{	"01234567890",				"1234567890",	},
	{	"0 0 0 1234567890",		"1234567890",	},
	{	" 0 0 0 1234567890",		"1234567890",	},
	{	"00000000000000000",		"0"				},
	{	"0000000000000000 0",	"0"				},
	{	"0000000000000000 00",	"0"				},
	{	" 1234567890",				"1234567890",	}
};

static const unsigned int TestCount = sizeof(TestList) / sizeof(TestList[0]);

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(char *TEST_zerotrim,
	(char *in_text));
COMPAT_FN_DECL_STATIC(int   TEST_DoIt,
	(const TEST_DATA *test_ptr));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;
	char         buffer[512];

	fprintf(stderr, "Test routine for function 'zerotrim()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------\n\n");

	while (argc) {
		if ((!STRFUNCS_stricmp("-HELP", argv[argc - 1])) ||
			(!STRFUNCS_stricmp("-H", argv[argc - 1]))) {
			fprintf(stderr, "USAGE:\n   cat <test-file> | %s\n\n", argv[0]);
			goto EXIT_FUNCTION;
		}
		argc--;
	}

	fprintf(stderr, "Performing regression test . . .\n");
	for (count_1 = 0; count_1 < TestCount; count_1++) {
		if (TEST_DoIt(TestList + count_1) != STRFUNCS_SUCCESS)
			return_code = STRFUNCS_FAILURE;
	}

	while ((!feof(stdin)) && (!ferror(stdin))) {
		if (fgets(buffer, sizeof(buffer) - 1, stdin) == NULL)
			break;
		while (*buffer && ((buffer[strlen(buffer) - 1] == '\r') ||
			(buffer[strlen(buffer) - 1] == '\n')))
			buffer[strlen(buffer) - 1] = '\0';
		if ((!STRFUNCS_stricmp(buffer, "QUIT")) ||
			 (!STRFUNCS_stricmp(buffer, "EXIT")))
			break;
		printf("RESULT: [%s]\n", zerotrim(buffer));
	}

EXIT_FUNCTION:

	return(return_code);
}

#ifndef NARGS
static char *TEST_zerotrim(char *in_text)
#else
static char *TEST_zerotrim(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	return(zerotrim_basic(in_text, in_text, 1));
}

#ifndef NARGS
static int TEST_DoIt(const TEST_DATA *test_ptr)
#else
static int TEST_DoIt(test_ptr)
const TEST_DATA *test_ptr;
#endif /* #ifndef NARGS */
{
	int  return_code = STRFUNCS_FAILURE;
	char buffer_1[511 + 1];
	char buffer_2[511 + 1];

	if (strcmp(zerotrim(strcpy(buffer_1, test_ptr->in)), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"OLD 'zerotrim()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(TEST_zerotrim(strcpy(buffer_1, test_ptr->in)),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"NEW 'zerotrim()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(zerotrim_basic(strcpy(buffer_1, test_ptr->in),
		buffer_2, 1), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'zerotrim_basic()' ERROR (1)", buffer_2, test_ptr->out);
	else if (strcmp(zerotrim_basic(strcpy(buffer_1, test_ptr->in),
		buffer_1, 1), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'zerotrim_basic()' ERROR (2)", buffer_2, test_ptr->out);
	else
		return_code = STRFUNCS_SUCCESS;

	return(return_code);

}

#endif /* #ifdef TEST_MAIN */

