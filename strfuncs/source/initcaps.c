/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Capitalizes the first letter of words in a string.

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

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			: 	initcaps

	SYNOPSIS		:	string_ptr = initcaps(in_text);

						char *string_ptr;

						char *in_text;

	DESCRIPTION	:	Maps the string in the ``in_text`` parameter to mixed-case,
						with the initial character of each word made upper-case.

						A word is defined as beginning at the start of the string
						or immediately preceded by a non-alphabetic character.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string for which initial characters
						are to be capitalized.

	RETURNS		: 	A pointer to the string used as input. This is, ``in_text``
						is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  initcaps_basic
						initcaps_basic_mem
						lower
						upper

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  initcaps
						Case Conversion Functions:initcaps
						STRFUNCS:Case Conversion Functions:initcaps
						String Functions:See STRFUNCS

   PUBLISH XREF:  initcaps

   PUBLISH NAME:	initcaps

	ENTRY CLASS	:	Case Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *initcaps(char *in_text)
#else
char *initcaps(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	int   state_flag = 0;
	char *tmp_ptr;

	tmp_ptr = lower(in_text);

	while (*tmp_ptr) {
		if (isalpha(*tmp_ptr)) {
			if (!state_flag) {
				*tmp_ptr   = strfmacs_toupper(*tmp_ptr);
				state_flag = 1;
			}
		}
		else
			state_flag = 0;
		tmp_ptr++;
	}

	return(in_text);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			: 	initcaps_basic

	SYNOPSIS		:	string_ptr = initcaps_basic(in_text, out_text);

						char       *string_ptr;

						const char *in_text;

						char       *out_text;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and maps the
						string ``out_text`` to mixed-case, with the initial
						character of each word made upper-case and other characters
						made lower-case.

						A word is defined as beginning at the start of the string
						or immediately preceded by a non-alphabetic character.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the source of the string for which
						initial characters are to be capitalized.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  initcaps
						initcaps_basic_mem
						lower_basic
						upper_basic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  initcaps_basic
						Case Conversion Functions:initcaps_basic
						STRFUNCS:Case Conversion Functions:initcaps_basic
						String Functions:See STRFUNCS

   PUBLISH XREF:  initcaps_basic

   PUBLISH NAME:	initcaps_basic

	ENTRY CLASS	:	Case Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *initcaps_basic(const char *in_text, char *out_text)
#else
char *initcaps_basic(in_text, out_text)
const char *in_text;
char       *out_text;
#endif /* #ifndef NARGS */
{
	return(initcaps_basic_mem(strlen(in_text) + 1, in_text, out_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*	BOH

	NAME			: 	initcaps_basic_mem

	SYNOPSIS		:	string_ptr = initcaps_basic_mem(in_length, in_text,
							out_text);

						char         *string_ptr;

						unsigned int  in_length;

						const char   *in_text;

						char         *out_text;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and maps the
						string ``out_text`` to mixed-case, with the initial
						character of each word made upper-case and other characters
						made lower-case. The length of ``in_text`` is specified by
						the parameter ``in_length``.

						A word is defined as beginning at the start of the string
						or immediately preceded by a non-alphabetic character.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which
						the ``in_text`` parameter points.

						(.) ``in_text`` is the source of the string for which
						initial characters are to be capitalized.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  initcaps
						initcaps_basic
						lower_basic_mem
						upper_basic_mem

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  initcaps_basic_mem
						Case Conversion Functions:initcaps_basic_mem
						STRFUNCS:Case Conversion Functions:initcaps_basic_mem
						String Functions:See STRFUNCS

   PUBLISH XREF:  initcaps_basic_mem

   PUBLISH NAME:	initcaps_basic_mem

	ENTRY CLASS	:	Case Conversion Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *initcaps_basic_mem(unsigned int in_length, const char *in_text,
	char *out_text)
#else
char *initcaps_basic_mem(in_length, in_text, out_text)
unsigned int  in_length;
const char   *in_text;
char         *out_text;
#endif /* #ifndef NARGS */
{
	int   state_flag = 0;
	char *tmp_ptr;

	if (in_length) {
		tmp_ptr = lower_basic_mem(in_length, in_text, out_text);
		while (in_length--) {
			if (isalpha(*tmp_ptr)) {
				if (!state_flag) {
					*tmp_ptr   = strfmacs_toupper(*tmp_ptr);
					state_flag = 1;
				}
			}
			else
				state_flag = 0;
			tmp_ptr++;
		}
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
		"This Is A Test."						},
	{	"This:Is Another Test.",
		"This:Is Another Test."				},
	{	"this is kind of a long test.",
		"This Is Kind Of A Long Test."	}
};

static const unsigned int TestCount = sizeof(TestList) / sizeof(TestList[0]);

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(char *TEST_initcaps,
	(char *in_text));
COMPAT_FN_DECL_STATIC(int   TEST_DoIt,
	(const TEST_DATA *test_ptr));

int main()
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'initcaps()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------\n\n");

	for (count_1 = 0; count_1 < TestCount; count_1++) {
		if (TEST_DoIt(TestList + count_1) != STRFUNCS_SUCCESS)
			return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}

#ifndef NARGS
static char *TEST_initcaps(char *in_text)
#else
static char *TEST_initcaps(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	return(initcaps_basic(in_text, in_text));
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

	if (strcmp(initcaps(strcpy(buffer_1, test_ptr->in)), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"OLD 'initcaps()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(TEST_initcaps(strcpy(buffer_1, test_ptr->in)),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"NEW 'initcaps()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(initcaps_basic(strcpy(buffer_1, test_ptr->in), buffer_2),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'initcaps_basic()' ERROR (1)", buffer_2, test_ptr->out);
	else if (strcmp(initcaps_basic(strcpy(buffer_1, test_ptr->in), buffer_1),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'initcaps_basic()' ERROR (2)", buffer_2, test_ptr->out);
	else
		return_code = STRFUNCS_SUCCESS;

	return(return_code);

}

#endif /* TEST_MAIN */

