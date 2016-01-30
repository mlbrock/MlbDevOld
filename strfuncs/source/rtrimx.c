/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes the characters specified from the right side
								of a string.

	Revision History	:	1992-06-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
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

   NAME        :  rtrimx

   SYNOPSIS    :  string_ptr = rtrimx(in_text, trim_string);

						char       *string_ptr;

						char       *in_text;

						const char *trim_string;

	DESCRIPTION	:	Removes all trailing instances of the characters specified
						in ``trim_string`` from the string to which the ``in_text``
						parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string from which characters in
						``trim_string`` on the right are to be removed.

						(.) ``trim_string`` points to an ASCII NUL (''0'')
						terminated string which contains the characters to be
						removed from the right side of ``in_text``.

	RETURNS		: 	A pointer to the string used as input. This is, ``in_text``
						is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  rtrimx_basic
						rtrimx_basic_mem
						rtrim
						ltrimx
						trimx

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:  rtrimx
						String Justification Functions:rtrimx
						STRFUNCS:String Justification Functions:rtrimx
						String Functions:See STRFUNCS

   PUBLISH XREF:  rtrimx

   PUBLISH NAME:	rtrimx

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *rtrimx(char *in_text, const char *trim_string)
#else
char *rtrimx(in_text, trim_string)
char       *in_text;
const char *trim_string;
#endif /* #ifndef NARGS */
{
	unsigned int  count;
	char         *tmp_ptr;


	if (trim_string && *trim_string) {
		count = strlen(in_text);
		if (count) {
			tmp_ptr = in_text + count - 1;
			while (count-- && strchr(trim_string, *tmp_ptr))
				*tmp_ptr-- = '\0';
		}
	}

	return(in_text);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  rtrimx_basic

   SYNOPSIS    :  string_ptr = rtrimx_basic(in_text, out_text, trim_string);

						char       *string_ptr;

						const char *in_text;

						char       *out_text;

						const char *trim_string;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and removes
						all trailing instances of the characters specified in
						``trim_string`` from the string to which the ``in_text``
						parameter points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the source of the string from which
						characters in ``trim_string`` on the right are to be
						removed.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

						(.) ``trim_string`` points to an ASCII NUL (''0'')
						terminated string which contains the characters to be
						removed from the right side of ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  rtrimx
						rtrimx_basic_mem
						rtrim_basic
						ltrimx_basic
						trimx_basic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:  rtrimx_basic
						String Justification Functions:rtrimx_basic
						STRFUNCS:String Justification Functions:rtrimx_basic
						String Functions:See STRFUNCS

   PUBLISH XREF:  rtrimx_basic

   PUBLISH NAME:	rtrimx_basic

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *rtrimx_basic(const char *in_text, char *out_text, const char *trim_string)
#else
char *rtrimx_basic(in_text, out_text, trim_string)
const char   *in_text;
char         *out_text;
const char   *trim_string;
#endif /* #ifndef NARGS */
{
	unsigned int tmp;

	rtrimx_basic_mem(strlen(in_text), in_text, &tmp, out_text,
		strlen(trim_string), trim_string);
	*(out_text + tmp) = '\0';

	return(out_text);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  rtrimx_basic_mem

   SYNOPSIS    :  string_ptr = rtrimx_basic_mem(in_length, in_text,
							out_length, out_text, trim_length, trim_string);

						char         *string_ptr;

						unsigned int  in_length;

						const char   *in_text;

						unsigned int *out_length;

						char         *out_text;

						unsigned int  trim_length;

						const char   *trim_string;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and removes
						all trailing instances of the characters specified in
						``trim_string`` from the string to which the ``in_text``
						parameter points. The length of ``in_text`` is specified by
						the parameter ``in_length``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which
						the ``in_text`` parameter points.

						(.) ``in_text`` is the source of the string from which
						characters in ``trim_string`` on the right are to be
						removed.

						(.) ``out_length`` points to an an ''unsigned int'' into
						which will be placed the length of ``out_text`` upon return
						of this function.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

						(.) ``trim_length`` is the length of the string of
						characters in ``trim_string``.

						(.) ``trim_string`` contains the characters to be removed
						from the right side of ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  rtrimx
						rtrimx_basic
						rtrim_basic_mem
						ltrimx_basic_mem
						trimx_basic_mem

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2016 Michael L. Brock

   OUTPUT INDEX:  rtrimx_basic_mem
						String Justification Functions:rtrimx_basic_mem
						STRFUNCS:String Justification Functions:rtrimx_basic_mem
						String Functions:See STRFUNCS

   PUBLISH XREF:  rtrimx_basic_mem

   PUBLISH NAME:	rtrimx_basic_mem

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *rtrimx_basic_mem(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, unsigned int trim_length,
	const char *trim_string)
#else
char *rtrimx_basic_mem(in_length, in_text, out_length, out_text, trim_length,
	trim_string)
unsigned int  in_length;
const char   *in_text;
unsigned int *out_length;
char         *out_text;
unsigned int  trim_length;
const char   *trim_string;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;

	*out_length = 0;

	tmp_ptr = ((char *) in_text) + in_length - 1;
	while (in_length &&
		(STRFUNCS_SHIM_memmem(trim_length, trim_string, 1, tmp_ptr) != NULL)) {
		in_length--;
		tmp_ptr--;
	}

	tmp_ptr     = out_text;
	*out_length = in_length;
	while (in_length--)
		*tmp_ptr++ = *in_text++;

	return(out_text);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

typedef struct {
	char *trim_string;
	char *in;
	char *out;
} TEST_DATA;

static const TEST_DATA TestList[] = {
	{	"0",
		"123.000000",
		"123."					},
	{	"0.",
		"123.000000",
		"123"						},
	{	" \t\n",
		"1234567890",
		"1234567890"		},
	{	" \t\n",
		" \t\n1234567890",
		" \t\n1234567890",		},
	{	" \t\n",
		"1234567890\n\t ",
		"1234567890",	},
	{	" \t\n",
		" \t\n1234567890\n\t ",
		" \t\n1234567890",	},
	{	"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
		"ABCD1234567890ABCD",
		"ABCD1234567890"	}
};

static const unsigned int TestCount = sizeof(TestList) / sizeof(TestList[0]);

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(char *TEST_rtrimx,
	(char *in_text, const char *trim_string));
COMPAT_FN_DECL_STATIC(int   TEST_DoIt,
	(const TEST_DATA *test_ptr));

int main()
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'rtrimx()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------\n\n");

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
static char *TEST_rtrimx(char *in_text, const char *trim_string)
#else
static char *TEST_rtrimx(in_text, trim_string)
char       *in_text;
const char *trim_string;
#endif /* #ifndef NARGS */
{
	return(rtrimx_basic(in_text, in_text, trim_string));
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

	if (strcmp(rtrimx(strcpy(buffer_1, test_ptr->in), test_ptr->trim_string),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"OLD 'rtrimx()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(TEST_rtrimx(strcpy(buffer_1, test_ptr->in),
		test_ptr->trim_string), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"NEW 'rtrimx()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(rtrimx_basic(strcpy(buffer_1, test_ptr->in), buffer_2,
		test_ptr->trim_string), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'rtrimx_basic()' ERROR (1)", buffer_2, test_ptr->out);
	else if (strcmp(rtrimx_basic(strcpy(buffer_1, test_ptr->in), buffer_1,
		test_ptr->trim_string), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'rtrimx_basic()' ERROR (2)", buffer_2, test_ptr->out);
	else
		return_code = STRFUNCS_SUCCESS;

	return(return_code);

}

#endif /* TEST_MAIN */

