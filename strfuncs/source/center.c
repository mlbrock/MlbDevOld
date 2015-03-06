/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Centers a string.

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

#include <memory.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	center

	SYNOPSIS		:	string_ptr = center(in_text, center_length);

						char         *string_ptr;

						char         *in_text;

						unsigned int  center_length;

	DESCRIPTION	:	Creates a string consisting of the input string (the
						``in_text`` parameter) padded with spaces on the left and
						right so as center the input string within the width
						specified by the input parameter ``center_length``. 

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string to be centered.

						(.) ``center_length`` is the number of characters in which
						centering is to be performed.

	RETURNS		:	A pointer to the text resulting from operation of the
						function (that is, ``in_text``).  This may be an empty
						string.

   NOTES       :  Note that the function is biased towards the left.  That
						is, if the number of spaces with which the string is to
						be padded is not an integral multiple of two, the extra
						space is used on the right side of the string.

	CAVEATS		:	If the ``center_length`` parameter is less than the length
						of the ``in_text`` parameter, no centering will be
						performed. Instead, the ``out_text`` parameter will consist
						of the text truncated to fit within the space specified by
						the ``center_length`` parameter.

   SEE ALSO    :  center_basic
						center_basic_mem

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  center
						String Justification Functions:center
						STRFUNCS:String Justification Functions:center
						String Functions:See STRFUNCS

   PUBLISH XREF:  center

   PUBLISH NAME:	center

	ENTRY CLASS	:	String Justification Functions

EOH */
/*	*********************************************************************** */
#ifndef NARGS
char *center(char *in_text, unsigned int center_length)
#else
char *center(in_text, center_length)
char         *in_text;
unsigned int  center_length;
#endif /* #ifndef NARGS */
{
	unsigned int text_length;

	if (!center_length)
		*in_text = '\0';
	else if ((text_length = strlen(trim(in_text))) > center_length)
		in_text[center_length] = '\0';
	else if (text_length < center_length) {
		strpadl(in_text, text_length += ((center_length - text_length) / 2));
		while (text_length < center_length)
			in_text[text_length++] = ' ';
		in_text[center_length] = '\0';
	}

	return(in_text);
}
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	center_basic

	SYNOPSIS		:	string_ptr = center_basic(in_text, out_text, ltrim_flag,
							rtrim_flag, center_char, center_length);

						char         *string_ptr;

						const char   *in_text;

						char         *out_text;

						int           ltrim_flag;

						int           rtrim_flag;

						const char   *center_char;

						unsigned int  center_length;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and pads it
						on the left and right so as center the input string within
						the width specified by the parameter ``center_length``. 

						Leading and/or trailing white-space may optionally be
						removed from the string before the centering is attempted.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the source of the string to be centered.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

						(.) ``ltrim_flag`` indicates whether leading white-space
						is to be removed before the string is centered. If
						``ltrim_flag`` is non-zero, leading white-space will be
						removed. If ``ltrim_flag`` is zero (''0''), leading
						white-space will not be removed.

						(.) ``rtrim_flag`` indicates whether trailing white-space
						is to be removed before the string is centered. If
						``rtrim_flag`` is non-zero, trailing white-space will be
						removed. If ``rtrim_flag`` is zero (''0''), trailing
						white-space will not be removed.

						(.) ``center_char`` points to the character to be used in
						padding the resultant string ``out_text``.

						(-) If ``center_char`` is ''NULL'', the ``space`` character
						(ASCII 32) will be used.

						(.) ``center_length`` is the number of characters in which
						centering is to be performed.

						(-) If the ``center_length`` parameter is zero the string is
						truncated to zero length.

						(-) If the length of the string is greater than the
						``center_length`` parameter, the string is truncated to the
						value of the ``center_length`` parameter.  Thus the returned
						string is always equal in length to the value of the
						``center_length`` parameter.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  Note that the function is biased towards the left.  That
						is, if the number of spaces with which the string is to
						be padded is not an integral multiple of two, the extra
						space is used on the right side of the string.

	CAVEATS		:	If the ``center_length`` parameter is less than the length
						of the ``in_text`` parameter, no centering will be
						performed. Instead, the ``out_text`` parameter will consist
						of the text truncated to fit within the space specified by
						the ``center_length`` parameter.

   SEE ALSO    :  center
						center_basic_mem

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  center_basic
						String Justification Functions:center_basic
						STRFUNCS:String Justification Functions:center_basic
						String Functions:See STRFUNCS

   PUBLISH XREF:  center_basic

   PUBLISH NAME:	center_basic

	ENTRY CLASS	:	String Justification Functions

EOH */
/*	*********************************************************************** */
#ifndef NARGS
char *center_basic(const char *in_text, char *out_text, int ltrim_flag,
	int rtrim_flag, const char *center_char, unsigned int center_length)
#else
char *center_basic(in_text, out_text, ltrim_flag, rtrim_flag, center_char,
	center_length)
const char   *in_text;
char         *out_text;
int           ltrim_flag;
int           rtrim_flag;
const char   *center_char;
unsigned int  center_length;
#endif /* #ifndef NARGS */
{
	unsigned int tmp_length;

	center_basic_mem(strlen(in_text), in_text, &tmp_length, out_text,
		ltrim_flag, rtrim_flag, center_char, center_length);
	*(out_text + tmp_length) = '\0';

	return(out_text);
}
/*	*********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	center_basic_mem

	SYNOPSIS		:	string_ptr = center_basic_mem(in_length, in_text,
							out_length, out_text, ltrim_flag, rtrim_flag,
							center_char, center_length);

						char         *string_ptr;

						unsigned int  in_length;

						const char   *in_text;

						unsigned int *out_length;

						char         *out_text;

						int           ltrim_flag;

						int           rtrim_flag;

						const char   *center_char;

						unsigned int  center_length;

	DESCRIPTION	:	Copies the string ``in_text`` to ``out_text`` and pads it
						on the left and right so as center the input string within
						the width specified by the parameter ``center_length``. 
						 The length of ``in_text`` is specified by the parameter
						``in_length``.

						Leading and/or trailing white-space may optionally be
						removed from the string before the centering is attempted.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_length`` is the length of the string to which
						the ``in_text`` parameter points.

						(.) ``in_text`` is the source of the string to be centered.

						(.) ``out_length`` points to an an ''unsigned int'' into
						which will be placed the length of ``out_text`` upon return
						of this function.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

						(.) ``ltrim_flag`` indicates whether leading white-space
						is to be removed before the string is centered. If
						``ltrim_flag`` is non-zero, leading white-space will be
						removed. If ``ltrim_flag`` is zero (''0''), leading
						white-space will not be removed.

						(.) ``rtrim_flag`` indicates whether trailing white-space
						is to be removed before the string is centered. If
						``rtrim_flag`` is non-zero, trailing white-space will be
						removed. If ``rtrim_flag`` is zero (''0''), trailing
						white-space will not be removed.

						(.) ``center_char`` points to the character to be used in
						padding the resultant string ``out_text``.

						(-) If ``center_char`` is ''NULL'', the ``space`` character
						(ASCII 32) will be used.

						(.) ``center_length`` is the number of characters in which
						centering is to be performed.

						(-) If the ``center_length`` parameter is zero the string is
						truncated to zero length.

						(-) If the length of the string is greater than the
						``center_length`` parameter, the string is truncated to the
						value of the ``center_length`` parameter.  Thus the returned
						string is always equal in length to the value of the
						``center_length`` parameter.

	RETURNS		: 	The ``out_text`` string is returned.

   NOTES       :  Note that the function is biased towards the left.  That
						is, if the number of spaces with which the string is to
						be padded is not an integral multiple of two, the extra
						space is used on the right side of the string.

	CAVEATS		:	If the ``center_length`` parameter is less than the length
						of the ``in_text`` parameter, no centering will be
						performed. Instead, the ``out_text`` parameter will consist
						of the text truncated to fit within the space specified by
						the ``center_length`` parameter.

   SEE ALSO    :  center
						center_basic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  center_basic_mem
						String Justification Functions:center_basic_mem
						STRFUNCS:String Justification Functions:center_basic_mem
						String Functions:See STRFUNCS

   PUBLISH XREF:  center_basic_mem

   PUBLISH NAME:	center_basic_mem

	ENTRY CLASS	:	String Justification Functions

EOH */
/*	*********************************************************************** */
#ifndef NARGS
char *center_basic_mem(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, int ltrim_flag, int rtrim_flag,
	const char *center_char, unsigned int center_length)
#else
char *center_basic_mem(in_length, in_text, out_length, out_text,
	ltrim_flag, rtrim_flag, center_char, center_length)
unsigned int  in_length;
const char   *in_text;
unsigned int *out_length;
char         *out_text;
int           ltrim_flag;
int           rtrim_flag;
const char   *center_char;
unsigned int  center_length;
#endif /* #ifndef NARGS */
{
	unsigned int tmp_length;

	center_char = (center_char == NULL) ? " " : center_char;

	if (!center_length)
		*out_length = 0;
	else {
		if (ltrim_flag || rtrim_flag) {
			if (ltrim_flag && rtrim_flag)
				trim_basic_mem(in_length, in_text, out_length, out_text);
			else if (ltrim_flag)
				ltrim_basic_mem(in_length, in_text, out_length, out_text);
			else
				rtrim_basic_mem(in_length, in_text, out_length, out_text);
			*out_length = (*out_length <= center_length) ? *out_length :
				center_length;
		}
		else if ((out_text != in_text) && in_length)
			memcpy(out_text, in_text, *out_length =
				((in_length <= center_length) ? in_length : center_length));
		else
			*out_length = (in_length <= center_length) ? in_length :
				center_length;
		if (*out_length < center_length) {
			tmp_length = *out_length + ((center_length - *out_length) / 2);
			strpadl_basic_mem(*out_length, out_text, out_length, out_text,
				ltrim_flag, rtrim_flag, center_char, tmp_length);
			while (*out_length < center_length)
				out_text[(*out_length)++] = *center_char;
		}
	}

	return(out_text);
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

typedef struct {
	unsigned int  pad;
	char         *in;
	char         *out;
} TEST_DATA;

static const TEST_DATA TestList[] = {
	{	20,
		"1234567890",
		"     1234567890     "	},
	{	5,
		"1234567890",
		"12345"						},
	{	0,
		"1234567890",
		""								},
	{	20,
		" \t\n1234567890",
		"     1234567890     "	},
	{	5,
		" \t\n1234567890",
		"12345"						},
	{	0,
		" \t\n1234567890",
		"",							},
	{	20,
		"1234567890 \t\n",
		"     1234567890     "	},
	{	5,
		"1234567890 \t\n",
		"12345"						},
	{	0,
		"1234567890 \t\n",
		""								},
	{	20,
		" \t\n1234567890\n\t ",
		"     1234567890     "	},
	{	5,
		" \t\n1234567890\n\t ",
		"12345"						},
	{	0,
		" \t\n1234567890\n\t ",
		""								}
};

static const unsigned int TestCount = sizeof(TestList) / sizeof(TestList[0]);

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(char *TEST_center,
	(char *in_text, unsigned int pad_length));
COMPAT_FN_DECL_STATIC(int   TEST_DoIt,
	(const TEST_DATA *test_ptr));

int main()
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'center()'\n");
	fprintf(stderr, "---- ------- --- -------- ----------\n\n");

	for (count_1 = 0; count_1 < TestCount; count_1++) {
		if (TEST_DoIt(TestList + count_1) != STRFUNCS_SUCCESS)
			return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}

#ifndef NARGS
static char *TEST_center(char *in_text, unsigned int pad_length)
#else
static char *TEST_center(in_text, pad_length)
char         *in_text;
unsigned int  pad_length;
#endif /* #ifndef NARGS */
{
	return(center_basic(in_text, ((char *) in_text), STRFUNCS_TRUE,
		STRFUNCS_TRUE, " ", pad_length));
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

	if (strcmp(center(strcpy(buffer_1, test_ptr->in), test_ptr->pad),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"OLD 'center()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(TEST_center(strcpy(buffer_1, test_ptr->in),
		test_ptr->pad), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"NEW 'center()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(center_basic(strcpy(buffer_1, test_ptr->in), buffer_2,
		STRFUNCS_TRUE, STRFUNCS_TRUE, " ", test_ptr->pad), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'center_basic()' ERROR (1)", buffer_2, test_ptr->out);
	else if (strcmp(center_basic(strcpy(buffer_1, test_ptr->in), buffer_1,
		STRFUNCS_TRUE, STRFUNCS_TRUE, " ", test_ptr->pad), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'center_basic()' ERROR (2)", buffer_2, test_ptr->out);
	else
		return_code = STRFUNCS_SUCCESS;

	return(return_code);

}

#endif /* TEST_MAIN */

