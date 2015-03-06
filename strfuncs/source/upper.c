/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps a string to upper-case.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2015.
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

	NAME			: 	upper

	SYNOPSIS		:	string_ptr = upper(in_text);

						char *string_ptr;

						char *in_text;

	DESCRIPTION	:	Maps each character of in the string to which the
						parameter ``in_text`` points to an upper-case letter.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string to be made upper-case.

	RETURNS		: 	A pointer to the string used as input. This is, ``in_text``
						is returned.

	NOTE(S)		: 	Note the use of the macro ``strfmacs_toupper`` in the 
						determination of whether a particular character
						should be mapped to upper-case.  This is because
						certain stupidly-written macros in 'ctype.h'
						header files (such as the ones on older Sun systems)
						don't first use ``isupper`` before applying the
						addition of 32 in the macro ``toupper``.

   CAVEATS     :  

   SEE ALSO    :  upper_basic
						upper_basic_mem
						lower

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  upper
						Case Conversion Functions:upper
						STRFUNCS:Case Conversion Functions:upper
						String Functions:See STRFUNCS

   PUBLISH XREF:  upper

	PUBLISH NAME:	upper

	ENTRY CLASS	:	Case Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *upper(char *in_text)
#else
char *upper(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	register char *start_ptr = in_text;

	while (*in_text) {
		*in_text = strfmacs_toupper(*in_text);
		in_text++;
	}

	return(start_ptr);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			: 	upper_basic

	SYNOPSIS		:	string_ptr = upper_basic(in_text, out_text);

						char       *string_ptr;

						const char *in_text;

						char       *out_text;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and maps the
						string ``out_text`` to upper-case.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the source of the string to be made
						upper-case.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

	NOTE(S)		: 	Note the use of the macro ``strfmacs_toupper`` in the 
						determination of whether a particular character
						should be mapped to upper-case.  This is because
						certain stupidly-written macros in 'ctype.h'
						header files (such as the ones on older Sun systems)
						don't first use ``isupper`` before applying the
						addition of 32 in the macro ``toupper``.

   CAVEATS     :  

   SEE ALSO    :  upper
						upper_basic_mem
						lower_basic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  upper_basic
						Case Conversion Functions:upper_basic
						STRFUNCS:Case Conversion Functions:upper_basic
						String Functions:See STRFUNCS

   PUBLISH XREF:  upper_basic

	PUBLISH NAME:	upper_basic

	ENTRY CLASS	:	Case Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *upper_basic(const char *in_text, char *out_text)
#else
char *upper_basic(in_text, out_text)
const char *in_text;
char       *out_text;
#endif /* #ifndef NARGS */
{
	return(upper_basic_mem(strlen(in_text) + 1, in_text, out_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			: 	upper_basic_mem

	SYNOPSIS		:	string_ptr = upper_basic_mem(in_length, in_text, out_text);

						char         *string_ptr;

						unsigned int  in_length;

						const char   *in_text;

						char         *out_text;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and maps the
						string ``out_text`` to upper-case. The length of ``in_text``
						is specified by the parameter ``in_length``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which
						the ``in_text`` parameter points.

						(.) ``in_text`` is the source of the string to be made
						upper-case.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

	NOTE(S)		: 	Note the use of the macro ``strfmacs_toupper`` in the 
						determination of whether a particular character
						should be mapped to upper-case.  This is because
						certain stupidly-written macros in 'ctype.h'
						header files (such as the ones on older Sun systems)
						don't first use ``isupper`` before applying the
						addition of 32 in the macro ``toupper``.

   CAVEATS     :  

   SEE ALSO    :  upper
						upper_basic
						lower_basic_mem

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  upper_basic_mem
						Case Conversion Functions:upper_basic_mem
						STRFUNCS:Case Conversion Functions:upper_basic_mem
						String Functions:See STRFUNCS

   PUBLISH XREF:  upper_basic_mem

	PUBLISH NAME:	upper_basic_mem

	ENTRY CLASS	:	Case Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *upper_basic_mem(unsigned int in_length, const char *in_text,
	char *out_text)
#else
char *upper_basic_mem(in_length, in_text, out_text)
unsigned int  in_length;
const char   *in_text;
char         *out_text;
#endif /* #ifndef NARGS */
{
	register char *tmp_ptr = out_text;

	while (in_length--) {
		*tmp_ptr++ = strfmacs_toupper(*in_text);
		in_text++;
	}

	return(out_text);
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
	{	"This is a test.",
		"THIS IS A TEST."						},
	{	"This:Is Another Test.",
		"THIS:IS ANOTHER TEST."				},
	{	"this is kind of a long test.",
		"THIS IS KIND OF A LONG TEST."	}
};

static const unsigned int TestCount = sizeof(TestList) / sizeof(TestList[0]);

COMPAT_FN_DECL(int          main,       (void));
COMPAT_FN_DECL_STATIC(char *TEST_upper, (char *in_text));
COMPAT_FN_DECL_STATIC(int   TEST_DoIt,  (const TEST_DATA *test_ptr));

int main()
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'upper()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------\n\n");

	for (count_1 = 0; count_1 < TestCount; count_1++) {
		if (TEST_DoIt(TestList + count_1) != STRFUNCS_SUCCESS)
			return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}

#ifndef NARGS
static char *TEST_upper(char *in_text)
#else
static char *TEST_upper(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	return(upper_basic(in_text, in_text));
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

	if (strcmp(upper(strcpy(buffer_1, test_ptr->in)), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"OLD 'upper()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(TEST_upper(strcpy(buffer_1, test_ptr->in)),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"NEW 'upper()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(upper_basic(strcpy(buffer_1, test_ptr->in), buffer_2),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'upper_basic()' ERROR (1)", buffer_2, test_ptr->out);
	else if (strcmp(upper_basic(strcpy(buffer_1, test_ptr->in), buffer_1),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'upper_basic()' ERROR (2)", buffer_2, test_ptr->out);
	else
		return_code = STRFUNCS_SUCCESS;

	return(return_code);

}

#endif /* TEST_MAIN */

