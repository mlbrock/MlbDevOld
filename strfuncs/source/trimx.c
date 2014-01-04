/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes the characters specified from the left and
								right sides of a string.

	Revision History	:	1992-06-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
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

   NAME        :  trimx

   SYNOPSIS    :  string_ptr = trimx(in_text, trim_string);

						char       *string_ptr;

						char       *in_text;

						const char *trim_string;

	DESCRIPTION	:	Removes leading and trailing instances of the characters
						specified in ``trim_string`` from the string to which the
						``in_text`` parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string from which leading and
						trailing characters in ``trim_string`` are to be removed.

						(.) ``trim_string`` points to an ASCII NUL (''0'')
						terminated string which contains the characters to be
						removed from the leading and trailing edges of ``in_text``.

	RETURNS		: 	A pointer to the string used as input. This is, ``in_text``
						is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  trimx_basic
						trimx_basic_mem
						trim
						ltrimx
						rtrimx

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:  trimx
						String Justification Functions:trimx
						STRFUNCS:String Justification Functions:trimx
						String Functions:See STRFUNCS

   PUBLISH XREF:  trimx

   PUBLISH NAME:	trimx

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *trimx(char *in_text, const char *trim_string)
#else
char *trimx(in_text, trim_string)
char       *in_text;
const char *trim_string;
#endif /* #ifndef NARGS */
{
	return(ltrimx(rtrimx(in_text, trim_string), trim_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  trimx_basic

   SYNOPSIS    :  string_ptr = trimx_basic(in_text, out_text, trim_string);

						char       *string_ptr;

						const char *in_text;

						char       *out_text;

						const char *trim_string;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and removes
						leading and trailing instances of the characters specified
						in ``trim_string`` from the string to which the ``in_text``
						parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the source of the string from which
						leading and trailing characters in ``trim_string`` are to
						be removed.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

						(.) ``trim_string`` points to an ASCII NUL (''0'')
						terminated string which contains the characters to be
						removed from the leading and trailing edges of ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  trimx
						trimx_basic_mem
						trim_basic
						ltrimx_basic
						rtrimx_basic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:  trimx_basic
						String Justification Functions:trimx_basic
						STRFUNCS:String Justification Functions:trimx_basic
						String Functions:See STRFUNCS

   PUBLISH XREF:  trimx_basic

   PUBLISH NAME:	trimx_basic

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *trimx_basic(const char *in_text, char *out_text, const char *trim_string)
#else
char *trimx_basic(in_text, out_text, trim_string)
const char *in_text;
char       *out_text;
const char *trim_string;
#endif /* #ifndef NARGS */
{
	return(ltrimx_basic(rtrimx_basic(in_text, out_text, trim_string), out_text,
		trim_string));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  trimx_basic_mem

   SYNOPSIS    :  string_ptr = trimx_basic_mem(in_length, in_text,
							out_length, out_text, trim_length, trim_string);

						char         *string_ptr;

						unsigned int  in_length;

						const char   *in_text;

						unsigned int *out_length;

						char         *out_text;

						unsigned int  trim_length;

						const char   *trim_string;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and removes
						leading and trailing instances of the characters specified
						in ``trim_string`` from the string to which the ``in_text``
						parameter points. The length of ``in_text`` is specified by
						the parameter ``in_length``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which
						the ``in_text`` parameter points.

						(.) ``in_text`` is the source of the string from which
						leading and trailing characters in ``trim_string`` are to
						be removed.

						(.) ``out_length`` points to an an ''unsigned int'' into
						which will be placed the length of ``out_text`` upon return
						of this function.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

						(.) ``trim_length`` is the length of the string of
						characters in ``trim_string``.

						(.) ``trim_string`` contains the characters to be removed
						from the leading and trailing edges of ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  trimx
						trimx_basic
						trim_basic_mem
						ltrimx_basic_mem
						rtrimx_basic_mem

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2014 Michael L. Brock

   OUTPUT INDEX:  trimx_basic_mem
						String Justification Functions:trimx_basic_mem
						STRFUNCS:String Justification Functions:trimx_basic_mem
						String Functions:See STRFUNCS

   PUBLISH XREF:  trimx_basic_mem

   PUBLISH NAME:	trimx_basic_mem

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *trimx_basic_mem(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, unsigned int trim_length,
	const char *trim_string)
#else
char *trimx_basic_mem(in_length, in_text, out_length, out_text, trim_length,
	trim_string)
unsigned int  in_length;
const char   *in_text;
unsigned int *out_length;
char         *out_text;
unsigned int  trim_length;
const char   *trim_string;
#endif /* #ifndef NARGS */
{
	return(ltrimx_basic_mem(*out_length, rtrimx_basic_mem(in_length, in_text,
		out_length, out_text, trim_length, trim_string), out_length, out_text,
		trim_length, trim_string));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

typedef struct {
	char *trim_string;
	char *in;
	char *out;
} TEST_DATA;

static const TEST_DATA TestList[] = {
	{	" \t\n",
		"1234567890",
		"1234567890"		},
	{	" \t\n",
		" \t\n1234567890",
		"1234567890",		},
	{	" \t\n",
		"1234567890\n\t ",
		"1234567890",	},
	{	" \t\n",
		" \t\n1234567890\n\t ",
		"1234567890",	},
	{	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
		"ABCD1234567890ABCD",
		"1234567890"	}
};

static const unsigned int TestCount = sizeof(TestList) / sizeof(TestList[0]);

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(char *TEST_trimx,
	(char *in_text, const char *trim_string));
COMPAT_FN_DECL_STATIC(int   TEST_DoIt,
	(const TEST_DATA *test_ptr));

int main()
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'trimx()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------\n\n");

	for (count_1 = 0; count_1 < TestCount; count_1++) {
		if (TEST_DoIt(TestList + count_1) != STRFUNCS_SUCCESS)
			return_code = STRFUNCS_FAILURE;
	}

	if (return_code != STRFUNCS_FAILURE)
		fprintf(stderr, "\n\nALL REGRESSION TESTS PASSED.\n\n");
	else
		fprintf(stderr, "\n\nONE OR MORE REGRESSION TESTS FAILED.\n\n");

	return(return_code);
}

#ifndef NARGS
static char *TEST_trimx(char *in_text, const char *trim_string)
#else
static char *TEST_trimx(in_text, trim_string)
char       *in_text;
const char *trim_string;
#endif /* #ifndef NARGS */
{
	return(trimx_basic(in_text, in_text, trim_string));
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

	if (strcmp(trimx(strcpy(buffer_1, test_ptr->in), test_ptr->trim_string),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"OLD 'trimx()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(TEST_trimx(strcpy(buffer_1, test_ptr->in),
		test_ptr->trim_string), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"NEW 'trimx()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(trimx_basic(strcpy(buffer_1, test_ptr->in), buffer_2,
		test_ptr->trim_string), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'trimx_basic()' ERROR (1)", buffer_2, test_ptr->out);
	else if (strcmp(trimx_basic(strcpy(buffer_1, test_ptr->in), buffer_1,
		test_ptr->trim_string), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'trimx_basic()' ERROR (2)", buffer_2, test_ptr->out);
	else
		return_code = STRFUNCS_SUCCESS;

	return(return_code);

}

#endif /* TEST_MAIN */

