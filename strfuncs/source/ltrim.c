/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes white-space from the left side of a string.

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

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ltrim

	SYNOPSIS		:	string_ptr = ltrim(in_text);

						char *string_ptr;

						char *in_text;

	DESCRIPTION	:	Removes all leading whitespace from the string to which
						the ``in_text`` parameter points.  That is, the string is
						trimmed from the left. 

						Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string from which whitespace on the
						left is to be removed.

	RETURNS		: 	A pointer to the string used as input. This is, ``in_text``
						is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  ltrim_basic
						ltrim_basic_mem
						ltrimx
						rtrim
						trim

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:  ltrim
						String Justification Functions:ltrim
						STRFUNCS:String Justification Functions:ltrim
						String Functions:See STRFUNCS

   PUBLISH XREF:  ltrim

   PUBLISH NAME:	ltrim

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ltrim(char *in_text)
#else
char *ltrim(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	char *temp_ptr_1 = in_text;
	char *temp_ptr_2 = in_text;

	if (isspace(*((unsigned char *) temp_ptr_1++))) {
		while (isspace(*((unsigned char *) temp_ptr_1)))
			++temp_ptr_1;
		do {
			*temp_ptr_2++ = *temp_ptr_1;
		} while (*temp_ptr_1++);
	}

	return(in_text);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ltrim_basic

	SYNOPSIS		:	string_ptr = ltrim_basic(in_text, out_text);

						char       *string_ptr;

						const char *in_text;

						char       *out_text;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and removes
						all leading whitespace from ``out_text``.

						Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the source of the string from which
						white-space on the left is to be removed.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  ltrim
						ltrim_basic_mem
						ltrimx_basic
						rtrim_basic
						trim_basic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:  ltrim_basic
						String Justification Functions:ltrim_basic
						STRFUNCS:String Justification Functions:ltrim_basic
						String Functions:See STRFUNCS

   PUBLISH XREF:  ltrim_basic

   PUBLISH NAME:	ltrim_basic

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ltrim_basic(const char *in_text, char *out_text)
#else
char *ltrim_basic(in_text, out_text)
const char *in_text;
char       *out_text;
#endif /* #ifndef NARGS */
{
	unsigned int tmp;

	return(ltrim_basic_mem(strlen(in_text) + 1, in_text, &tmp, out_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ltrim_basic_mem

	SYNOPSIS		:	string_ptr = ltrim_basic_mem(in_length, in_text, out_length,
							out_text);

						char         *string_ptr;

						unsigned int  in_length;

						const char   *in_text;

						unsigned int *out_length;

						char         *out_text;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and removes
						all leading whitespace from ``out_text``. The length of
						``in_text`` is specified by the parameter ``in_length``.

						Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which
						the ``in_text`` parameter points.

						(.) ``in_text`` is the source of the string from which
						white-space on the left is to be removed.

						(.) ``out_length`` points to an an ''unsigned int'' into
						which will be placed the length of ``out_text`` upon return
						of this function.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  ltrim
						ltrim_basic
						ltrimx_basic_mem
						rtrim_basic_mem
						trim_basic_mem

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:  ltrim_basic_mem
						String Justification Functions:ltrim_basic_mem
						STRFUNCS:String Justification Functions:ltrim_basic_mem
						String Functions:See STRFUNCS

   PUBLISH XREF:  ltrim_basic_mem

   PUBLISH NAME:	ltrim_basic_mem

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ltrim_basic_mem(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text)
#else
char *ltrim_basic_mem(in_length, in_text, out_length, out_text)
unsigned int  in_length;
const char   *in_text;
unsigned int *out_length;
char         *out_text;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;

	*out_length = 0;

	while (in_length && isspace(*((unsigned char *) in_text))) {
		in_length--;
		in_text++;
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
	char *in;
	char *out;
} TEST_DATA;

static const TEST_DATA TestList[] = {
	{  "      ",
		""		},
	{  " \t\n\f\v\r ",
		""		},
	{	"1234567890",
		"1234567890"	},
	{	" \t\n1234567890",
		"1234567890",	},
	{	"1234567890 \t\n",
		"1234567890 \t\n",	},
	{	" \t\n1234567890\n\t ",
		"1234567890\n\t ",	}
};

static const unsigned int TestCount = sizeof(TestList) / sizeof(TestList[0]);

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(char *TEST_ltrim,
	(char *in_text));
COMPAT_FN_DECL_STATIC(int   TEST_DoIt,
	(const TEST_DATA *test_ptr));

int main()
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'ltrim()'\n");
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
static char *TEST_ltrim(char *in_text)
#else
static char *TEST_ltrim(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	return(ltrim_basic(in_text, in_text));
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

	if (strcmp(ltrim(strcpy(buffer_1, test_ptr->in)), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"OLD 'ltrim()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(TEST_ltrim(strcpy(buffer_1, test_ptr->in)),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"NEW 'ltrim()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(ltrim_basic(strcpy(buffer_1, test_ptr->in), buffer_2),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'ltrim_basic()' ERROR (1)", buffer_2, test_ptr->out);
	else if (strcmp(ltrim_basic(strcpy(buffer_1, test_ptr->in), buffer_1),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'ltrim_basic()' ERROR (2)", buffer_2, test_ptr->out);
	else
		return_code = STRFUNCS_SUCCESS;

	return(return_code);

}

#endif /* TEST_MAIN */

