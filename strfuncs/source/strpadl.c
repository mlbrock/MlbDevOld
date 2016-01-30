/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Pads the left side of a string with spaces.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2016.
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
#include <stdlib.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME:			 	strpadl

	SYNOPSIS:		string_ptr = strpadl(in_text, pad_length);

						char         *string_ptr;

						char         *in_text;

						unsigned int  pad_length;

	DESCRIPTION:	Pads on the left with spaces the string to which the
						``in_text`` parameter points in an area the length of the
						``pad_length`` parameter.

						Leading white-space is removed from the string before the
						padding is attempted.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string to be left-padded.

						(.) ``pad_length`` is the length within which ``in_text``
						is to be left-padded.

						(-) If the ``pad_length`` parameter is zero the string is
						truncated to zero length.

						(-) If the length of the string is greater than the
						``pad_length`` parameter, the string is truncated to the
						value of the ``pad_length`` parameter.  Thus the returned
						string is always equal in length to the value of the
						``pad_length`` parameter.

	RETURNS		: 	A pointer to the string used as input. This is, ``in_text``
						is returned.

	NOTE(S):			Trailing spaces and tabs are considered to be a part
						of the string and are not affected by this function
						(except in those cases where truncation of the string
						is necessary).

   CAVEATS     :  

   SEE ALSO    :  strpadl_basic
						strpadl_basic_mem
						strpadr
						ltrim
						rtrim
						trim
						ljust
						rjust

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2016 Michael L. Brock

   OUTPUT INDEX:  strpadl
						String Justification Functions:strpadl
						STRFUNCS:String Justification Functions:strpadl
						String Functions:See STRFUNCS

   PUBLISH XREF:  strpadl

   PUBLISH NAME:	strpadl

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *strpadl(char *in_text, unsigned int pad_length)
#else
char *strpadl(in_text, pad_length)
char         *in_text;
unsigned int  pad_length;
#endif /* #ifndef NARGS */
{
	int          count_1;
	unsigned int padding;
	unsigned int string_length;

	if (!pad_length)
		*in_text = '\0';
	else {
		string_length = strlen(ltrim(in_text));
		if (string_length >= pad_length)
			in_text[pad_length] = '\0';
		else {
			padding = pad_length - string_length;
			for (count_1 = (string_length - 1); count_1 >= 0; count_1--)
				*(in_text + count_1 + padding) = *(in_text + count_1);
			memset(in_text, ' ', padding);
			*(in_text + string_length + padding) = '\0';
		}
	}

	return(in_text);
}			
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME:			 	strpadl_basic

	SYNOPSIS:		string_ptr = strpadl_basic(in_text, out_text, ltrim_flag,
							rtrim_flag, pad_char, pad_length);

						char         *string_ptr;

						const char   *in_text;

						char         *out_text;

						int           ltrim_flag;

						int           rtrim_flag;

						const char   *pad_char;

						unsigned int  pad_length;

	DESCRIPTION:	Copies the string ``in_text`` to ``out_text`` and pads it
						on the left with the specified character in an area the
						length of the ``pad_length`` parameter.

						Leading and/or trailing white-space may optionally be
						removed from the string before the padding is attempted.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the source of the string from which
						white-space on the left is to be removed.

						(.) ``out_text`` is the string into which the altered
						copy of the string is to be placed.

						(-) ``out_text`` may be the same as ``in_text``.

						(.) ``ltrim_flag`` indicates whether leading white-space
						is to be removed before the string is padded. If
						``ltrim_flag`` is non-zero, leading white-space will be
						removed. If ``ltrim_flag`` is zero (''0''), leading
						white-space will not be removed.

						(.) ``rtrim_flag`` indicates whether trailing white-space
						is to be removed before the string is padded. If
						``rtrim_flag`` is non-zero, trailing white-space will be
						removed. If ``rtrim_flag`` is zero (''0''), trailing
						white-space will not be removed.

						(.) ``pad_char`` points to the character to be used in
						padding the resultant string ``out_text``.

						(-) If ``pad_char`` is ''NULL'', the ``space`` character
						(ASCII 32) will be used.

						(.) ``pad_length`` is the length within which ``in_text``
						is to be left-padded.

						(-) If the ``pad_length`` parameter is zero the string is
						truncated to zero length.

						(-) If the length of the string is greater than the
						``pad_length`` parameter, the string is truncated to the
						value of the ``pad_length`` parameter.  Thus the returned
						string is always equal in length to the value of the
						``pad_length`` parameter.

	RETURNS		: 	The ``out_text`` string is returned.

	NOTE(S)		:	

   CAVEATS     :  

   SEE ALSO    :  strpadl
						strpadl_basic_mem
						strpadr_basic
						ltrim_basic
						rtrim_basic
						trim_basic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2016 Michael L. Brock

   OUTPUT INDEX:  strpadl_basic
						String Justification Functions:strpadl_basic
						STRFUNCS:String Justification Functions:strpadl_basic
						String Functions:See STRFUNCS

   PUBLISH XREF:  strpadl_basic

   PUBLISH NAME:	strpadl_basic

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *strpadl_basic(const char *in_text, char *out_text, int ltrim_flag,
	int rtrim_flag, const char *pad_char, unsigned int pad_length)
#else
char *strpadl_basic(in_text, out_text, ltrim_flag, rtrim_flag, pad_char,
	pad_length)
const char   *in_text;
char         *out_text;
int           ltrim_flag;
int           rtrim_flag;
const char   *pad_char;
unsigned int  pad_length;
#endif /* #ifndef NARGS */
{
	unsigned int tmp_length;

	strpadl_basic_mem(strlen(in_text), in_text, &tmp_length, out_text,
		ltrim_flag, rtrim_flag, pad_char, pad_length);
	*(out_text + tmp_length) = '\0';

	return(out_text);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME:			 	strpadl_basic_mem

	SYNOPSIS:		string_ptr = strpadl_basic_mem(in_length, in_text,
							out_length, out_text, ltrim_flag, rtrim_flag, pad_char,
							pad_length);

						char         *string_ptr;

						unsigned int  in_length;
 
						const char   *in_text;

						unsigned int *out_length;

 						char         *out_text;

						int           ltrim_flag;

						int           rtrim_flag;

						const char   *pad_char;

						unsigned int  pad_length;

	DESCRIPTION:	Copies the string ``in_text`` to ``out_text`` and pads it
						on the left with the specified character in an area the
						length of the ``pad_length`` parameter. The length of
						``in_text`` is specified by the parameter ``in_length``.

						Leading and/or trailing white-space may optionally be
						removed from the string before the padding is attempted.

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

						(.) ``ltrim_flag`` indicates whether leading white-space
						is to be removed before the string is padded. If
						``ltrim_flag`` is non-zero, leading white-space will be
						removed. If ``ltrim_flag`` is zero (''0''), leading
						white-space will not be removed.

						(.) ``rtrim_flag`` indicates whether trailing white-space
						is to be removed before the string is padded. If
						``rtrim_flag`` is non-zero, trailing white-space will be
						removed. If ``rtrim_flag`` is zero (''0''), trailing
						white-space will not be removed.

						(.) ``pad_char`` points to the character to be used in
						padding the resultant string ``out_text``.

						(-) If ``pad_char`` is ''NULL'', the ``space`` character
						(ASCII 32) will be used.

						(.) ``pad_length`` is the length within which ``in_text``
						is to be left-padded.

						(-) If the ``pad_length`` parameter is zero the string is
						truncated to zero length.

						(-) If the length of the string is greater than the
						``pad_length`` parameter, the string is truncated to the
						value of the ``pad_length`` parameter.  Thus the returned
						string is always equal in length to the value of the
						``pad_length`` parameter.

	RETURNS		: 	The ``out_text`` string is returned.

	NOTE(S)		:	

   CAVEATS     :  

   SEE ALSO    :  strpadl
						strpadl_basic
						strpadr_basic_mem
						ltrim_basic_mem
						rtrim_basic_mem
						trim_basic_mem

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2016 Michael L. Brock

   OUTPUT INDEX:  strpadl_basic_mem
						String Justification Functions:strpadl_basic_mem
						STRFUNCS:String Justification Functions:strpadl_basic_mem
						String Functions:See STRFUNCS

   PUBLISH XREF:  strpadl_basic_mem

   PUBLISH NAME:	strpadl_basic_mem

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *strpadl_basic_mem(unsigned int in_length, const char *in_text,
	unsigned int *out_length, char *out_text, int ltrim_flag, int rtrim_flag,
	const char *pad_char, unsigned int pad_length)
#else
char *strpadl_basic_mem(in_length, in_text, out_length, out_text, ltrim_flag,
	rtrim_flag, pad_char, pad_length)
unsigned int  in_length;
const char   *in_text;
unsigned int *out_length;
char         *out_text;
int           ltrim_flag;
int           rtrim_flag;
const char   *pad_char;
unsigned int  pad_length;
#endif /* #ifndef NARGS */
{
   unsigned int count_1;
	unsigned int tmp_length;

	pad_char = (pad_char == NULL) ? " " : pad_char;

	if (!pad_length)
		*out_length = 0;
	else {
		if (ltrim_flag || rtrim_flag) {
			if (ltrim_flag && rtrim_flag)
				trim_basic_mem(in_length, in_text, out_length, out_text);
			else if (ltrim_flag)
				ltrim_basic_mem(in_length, in_text, out_length, out_text);
			else
				rtrim_basic_mem(in_length, in_text, out_length, out_text);
			*out_length = (*out_length <= pad_length) ? *out_length : pad_length;
		}
		else if ((out_text != in_text) && in_length)
			memcpy(out_text, in_text, *out_length =
				((in_length <= pad_length) ? in_length : pad_length));
		else
			*out_length = (in_length <= pad_length) ? in_length : pad_length;
		if (*out_length < pad_length) {
			tmp_length = pad_length - *out_length;
			for (count_1 = *out_length; count_1; ) {
				count_1--;
				*(out_text + tmp_length + count_1) = *(out_text + count_1);
			}
			for (count_1 = 0; count_1 < tmp_length; count_1++)
				*(out_text + count_1) = *pad_char;
			*out_length = pad_length;
		}
	}

	return(out_text);
}
/* *********************************************************************** */

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
		"          1234567890"	},
	{	5,
		"1234567890",
		"12345"						},
	{	0,
		"1234567890",
		""								},
	{	20,
		" \t\n1234567890",
		"          1234567890"	},
	{	5,
		" \t\n1234567890",
		"12345"						},
	{	0,
		" \t\n1234567890",
		"",							},
	{	20,
		"1234567890 \t\n",
		"       1234567890 \t\n"	},
	{	5,
		"1234567890 \t\n",
		"12345"						},
	{	0,
		"1234567890 \t\n",
		""								},
	{	20,
		" \t\n1234567890\n\t ",
		"       1234567890\n\t "	},
	{	5,
		" \t\n1234567890\n\t ",
		"12345"						},
	{	0,
		" \t\n1234567890\n\t ",
		""								}
};

static const unsigned int TestCount = sizeof(TestList) / sizeof(TestList[0]);

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(char *TEST_strpadl,
	(char *in_text, unsigned int pad_length));
COMPAT_FN_DECL_STATIC(int   TEST_DoIt,
	(const TEST_DATA *test_ptr));

int main()
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	fprintf(stderr, "Test routine for function 'strpadl()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------\n\n");

	for (count_1 = 0; count_1 < TestCount; count_1++) {
		if (TEST_DoIt(TestList + count_1) != STRFUNCS_SUCCESS)
			return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}

#ifndef NARGS
static char *TEST_strpadl(char *in_text, unsigned int pad_length)
#else
static char *TEST_strpadl(in_text, pad_length)
char         *in_text;
unsigned int  pad_length;
#endif /* #ifndef NARGS */
{
	return(strpadl_basic(in_text, ((char *) in_text), STRFUNCS_TRUE,
		STRFUNCS_FALSE, " ", pad_length));
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

	if (strcmp(strpadl(strcpy(buffer_1, test_ptr->in), test_ptr->pad),
		test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"OLD 'strpadl()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(TEST_strpadl(strcpy(buffer_1, test_ptr->in),
		test_ptr->pad), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"NEW 'strpadl()' ERROR", buffer_1, test_ptr->out);
	else if (strcmp(strpadl_basic(strcpy(buffer_1, test_ptr->in), buffer_2,
		STRFUNCS_TRUE, STRFUNCS_FALSE, " ", test_ptr->pad), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'strpadl_basic()' ERROR (1)", buffer_2, test_ptr->out);
	else if (strcmp(strpadl_basic(strcpy(buffer_1, test_ptr->in), buffer_1,
		STRFUNCS_TRUE, STRFUNCS_FALSE, " ", test_ptr->pad), test_ptr->out))
		printf("%-26.26s:\n>>>[%s]\n>>>[%s]\n",
			"'strpadl_basic()' ERROR (2)", buffer_2, test_ptr->out);
	else
		return_code = STRFUNCS_SUCCESS;

	return(return_code);

}

#endif /* TEST_MAIN */

