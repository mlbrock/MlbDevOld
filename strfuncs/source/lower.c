/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps a string to lower-case.

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

	NAME			:	lower

	SYNOPSIS		:	string_ptr = lower(in_text);

						char *string_ptr;

						char *in_text;

	DESCRIPTION	:	Maps each character of in the string to which the
						parameter ``in_text`` points to a lower-case letter.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string to be made lower-case.

	RETURNS		: 	A pointer to the string used as input. This is, ``in_text``
						is returned.

	NOTE(S)		:	Note the use of the macro ``strfmacs_tolower`` in the 
						determination of whether a particular character
						should be mapped to lower-case.  This is because
						certain stupidly-written macros in 'ctype.h'
						header files (such as the ones on older Sun systems)
						don't first use ``islower`` before applying the
						addition of 32 in the macro ``tolower``.

   CAVEATS     :  

   SEE ALSO    :  lower_basic
						lower_basic_mem
						upper

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:  lower
						Case Conversion Functions:lower
						STRFUNCS:Case Conversion Functions:lower
						String Functions:See STRFUNCS

   PUBLISH XREF:  lower

	PUBLISH NAME:	lower

	ENTRY CLASS	:	Case Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *lower(char *in_text)
#else
char *lower(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	char *start_ptr = in_text;

	while (*in_text) {
		*in_text = strfmacs_tolower(*in_text);
		in_text++;
	}

	return(start_ptr);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	lower_basic

	SYNOPSIS		:	string_ptr = lower_basic(in_text, out_text);

						char       *string_ptr;

						const char *in_text;

						char       *out_text;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and maps the
						string ``out_text`` to lower-case.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the source of the string to be made
						lower-case.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

	NOTE(S)		:	Note the use of the macro ``strfmacs_tolower`` in the 
						determination of whether a particular character
						should be mapped to lower-case.  This is because
						certain stupidly-written macros in 'ctype.h'
						header files (such as the ones on older Sun systems)
						don't first use ``islower`` before applying the
						addition of 32 in the macro ``tolower``.

   CAVEATS     :  

   SEE ALSO    :  lower
						lower_basic_mem
						upper_basic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:  lower_basic
						Case Conversion Functions:lower_basic
						STRFUNCS:Case Conversion Functions:lower_basic
						String Functions:See STRFUNCS

   PUBLISH XREF:  lower_basic

	PUBLISH NAME:	lower_basic

	ENTRY CLASS	:	Case Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *lower_basic(const char *in_text, char *out_text)
#else
char *lower_basic(in_text, out_text)
const char *in_text;
char       *out_text;
#endif /* #ifndef NARGS */
{
	return(lower_basic_mem(strlen(in_text) + 1, in_text, out_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	lower_basic_mem

	SYNOPSIS		:	string_ptr = lower_basic_mem(in_length, in_text, out_text);

						char         *string_ptr;

						unsigned int  in_length;

						const char   *in_text;

						char         *out_text;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and maps the
						string ``out_text`` to lower-case. The length of ``in_text``
						is specified by the parameter ``in_length``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which
						the ``in_text`` parameter points.

						(.) ``in_text`` is the source of the string to be made
						lower-case.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

	NOTE(S)		:	Note the use of the macro ``strfmacs_tolower`` in the 
						determination of whether a particular character
						should be mapped to lower-case.  This is because
						certain stupidly-written macros in 'ctype.h'
						header files (such as the ones on older Sun systems)
						don't first use ``islower`` before applying the
						addition of 32 in the macro ``tolower``.

   CAVEATS     :  

   SEE ALSO    :  lower
						lower_basic
						lower_basic_mem

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:  lower_basic_mem
						Case Conversion Functions:lower_basic_mem
						STRFUNCS:Case Conversion Functions:lower_basic_mem
						String Functions:See STRFUNCS

   PUBLISH XREF:  lower_basic_mem

	PUBLISH NAME:	lower_basic_mem

	ENTRY CLASS	:	Case Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *lower_basic_mem(unsigned int in_length, const char *in_text,
	char *out_text)
#else
char *lower_basic_mem(in_length, in_text, out_text)
unsigned int  in_length;
const char   *in_text;
char         *out_text;
#endif /* #ifndef NARGS */
{
	register char *tmp_ptr = out_text;

	while (in_length--) {
		*tmp_ptr++ = strfmacs_tolower(*in_text);
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
		"this is a test."						},
	{	"This:Is Another Test.",
		"this:is another test."				},
	{	"this is kind of a long test.",
		"this is kind of a long test."	}
};

static const unsigned int TestCount = sizeof(TestList) / sizeof(TestList[0]);

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(char *TEST_lower,
	(char *in_text));
COMPAT_FN_DECL_STATIC(int   TEST_DoIt,
	(const TEST_DATA *test_ptr));

int main()
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'lower()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------\n\n");

	for (count_1 = 0; count_1 < TestCount; count_1++) {
		if (TEST_DoIt(TestList + count_1) != STRFUNCS_SUCCESS)
			return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}

#ifndef NARGS
static char *TEST_lower(char *in_text)
#else
static char *TEST_lower(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	return(lower_basic(in_text, in_text));
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

	if (strcmp(lower(strcpy(buffer_1, test_ptr->in)), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"OLD 'lower()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(TEST_lower(strcpy(buffer_1, test_ptr->in)),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"NEW 'lower()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(lower_basic(strcpy(buffer_1, test_ptr->in), buffer_2),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'lower_basic()' ERROR (1)", buffer_2, test_ptr->out);
	else if (strcmp(lower_basic(strcpy(buffer_1, test_ptr->in), buffer_1),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'lower_basic()' ERROR (2)", buffer_2, test_ptr->out);
	else
		return_code = STRFUNCS_SUCCESS;

	return(return_code);

}

#endif /* TEST_MAIN */

