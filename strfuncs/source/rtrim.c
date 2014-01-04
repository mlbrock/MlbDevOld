/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes white-space from the right side of a string.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2014.
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

	NAME			: 	rtrim

	SYNOPSIS		:	string_ptr = rtrim(in_text);

						char *string_ptr;

						char *in_text;

	DESCRIPTION	:	Removes all trailing whitespace from the string to which
						the ``in_text`` parameter points.  That is, the string is
						trimmed from the right. 

						Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string from which whitespace on the
						right is to be removed.

	RETURNS		: 	A pointer to the string used as input. This is, ``in_text``
						is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  rtrim_basic
						rtrim_basic_mem
						rtrimx
						ltrim
						trim

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2014 Michael L. Brock

   OUTPUT INDEX:  rtrim
						String Justification Functions:rtrim
						STRFUNCS:String Justification Functions:rtrim
						String Functions:See STRFUNCS

   PUBLISH XREF:  rtrim

   PUBLISH NAME:	rtrim

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *rtrim(char *in_text)
#else
char *rtrim(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	unsigned int  count;
	char         *temp_ptr;

	count = strlen(in_text);

	if (count) {
		temp_ptr = in_text + count - 1;
		while (count-- && isspace(*((unsigned char *) temp_ptr)))
			*temp_ptr-- = 0;
	}

	return(in_text);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			: 	rtrim_basic

	SYNOPSIS		:	string_ptr = rtrim_basic(in_text, out_text);

						char       *string_ptr;

						const char *in_text;

						char       *out_text;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and removes
						all trailing whitespace from ``out_text``.

						Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the source of the string from which
						white-space on the right is to be removed.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  rtrim
						rtrim_basic_mem
						rtrimx_basic
						ltrim_basic
						trim_basic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2014 Michael L. Brock

   OUTPUT INDEX:  rtrim_basic
						String Justification Functions:rtrim_basic
						STRFUNCS:String Justification Functions:rtrim_basic
						String Functions:See STRFUNCS

   PUBLISH XREF:  rtrim_basic

   PUBLISH NAME:	rtrim_basic

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *rtrim_basic(const char *in_text, char *out_text)
#else
char *rtrim_basic(in_text, out_text)
const char   *in_text;
char         *out_text;
#endif /* #ifndef NARGS */
{
	unsigned int tmp;

	rtrim_basic_mem(strlen(in_text), in_text, &tmp, out_text);
	*(out_text + tmp) = '\0';

	return(out_text);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			: 	rtrim_basic_mem

	SYNOPSIS		:	string_ptr = rtrim_basic_mem(in_length, in_text, out_length,
							out_text);

						char         *string_ptr;

						unsigned int  in_length;

						const char   *in_text;

						unsigned int *out_length;

						char         *out_text;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and removes
						all trailing whitespace from ``out_text``. The length of
						``in_text`` is specified by the parameter ``in_length``.

						Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which
						the ``in_text`` parameter points.

						(.) ``in_text`` is the source of the string from which
						white-space on the right is to be removed.

						(.) ``out_length`` points to an an ''unsigned int'' into
						which will be placed the length of ``out_text`` upon return
						of this function.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  rtrim
						rtrim_basic
						rtrimx_basic_mem
						ltrim_basic_mem
						trim_basic_mem

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2014 Michael L. Brock

   OUTPUT INDEX:  rtrim_basic_mem
						String Justification Functions:rtrim_basic_mem
						STRFUNCS:String Justification Functions:rtrim_basic_mem
						String Functions:See STRFUNCS

   PUBLISH XREF:  rtrim_basic_mem

   PUBLISH NAME:	rtrim_basic_mem

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *rtrim_basic_mem(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text)
#else
char *rtrim_basic_mem(in_length, in_text, out_length, out_text)
unsigned int  in_length;
const char   *in_text;
unsigned int *out_length;
char         *out_text;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;

	*out_length = 0;

	tmp_ptr = ((char *) in_text) + in_length - 1;
	while (in_length && isspace(*((unsigned char *) tmp_ptr))) {
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
	char *in;
	char *out;
} TEST_DATA;

static const TEST_DATA TestList[] = {
	{	"1234567890",
		"1234567890"	},
	{	" \t\n1234567890",
		" \t\n1234567890",	},
	{	"1234567890 \t\n",
		"1234567890",	},
	{	" \t\n1234567890\n\t ",
		" \t\n1234567890",	}
};

static const unsigned int TestCount = sizeof(TestList) / sizeof(TestList[0]);

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(char *TEST_rtrim,
	(char *in_text));
COMPAT_FN_DECL_STATIC(int   TEST_DoIt,
	(const TEST_DATA *test_ptr));

int main()
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'rtrim()'\n");
	fprintf(stderr, "---- ------- --- -------- ---------\n\n");

	for (count_1 = 0; count_1 < TestCount; count_1++) {
		if (TEST_DoIt(TestList + count_1) != STRFUNCS_SUCCESS)
			return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}

#ifndef NARGS
static char *TEST_rtrim(char *in_text)
#else
static char *TEST_rtrim(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	return(rtrim_basic(in_text, in_text));
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

	if (strcmp(rtrim(strcpy(buffer_1, test_ptr->in)), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"OLD 'rtrim()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(TEST_rtrim(strcpy(buffer_1, test_ptr->in)),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"NEW 'rtrim()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(rtrim_basic(strcpy(buffer_1, test_ptr->in), buffer_2),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'rtrim_basic()' ERROR (1)", buffer_2, test_ptr->out);
	else if (strcmp(rtrim_basic(strcpy(buffer_1, test_ptr->in), buffer_1),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'rtrim_basic()' ERROR (2)", buffer_2, test_ptr->out);
	else
		return_code = STRFUNCS_SUCCESS;

	return(return_code);

}

#endif /* TEST_MAIN */

