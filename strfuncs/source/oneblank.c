/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Replaces multiple instances of white-space with a
								single space.

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

#include <ctype.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			: 	oneblank

	SYNOPSIS		:	char *oneblank(text);

						char *text;

	DESCRIPTION	:	Removes multiple consecutive whitespace characters from the
						string to which the ``text`` parameter points, replacing
						them with a single space (ASCII 32).

						Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``text`` is the string in which multiple whitespace
						characters are to be reduced to a single space.

	RETURNS		:	A pointer to the string used as input.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  nospace
						noblank

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  oneblank
						String Justification Functions:oneblank
						STRFUNCS:String Justification Functions:oneblank
						String Functions:See STRFUNCS

   PUBLISH XREF:  oneblank

   PUBLISH NAME:	oneblank

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *oneblank(char *text)
#else
char *oneblank(text)
char *text;
#endif /* #ifndef NARGS */
{
	char         *temp_ptr_1 = text;
	char         *temp_ptr_2 = text;
	unsigned int  length;

	length = strlen(text);

	while (*temp_ptr_1) {
		if (isspace(*temp_ptr_1)) {
			*text++ = ' ';
			temp_ptr_1++;
			while (isspace(*temp_ptr_1)) {
				temp_ptr_1++;
				length--;
			}
		}
		else
			*text++ = *temp_ptr_1++;
	}

	temp_ptr_2[length] = '\0';

	return(temp_ptr_2);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

/* *********************************************************************** */
int main()
{
	char *test_ptr_1, *test_ptr_2;

	printf("This is a test of the 'oneblank()' function call\n");
	printf("---- -- - ---- -- --- ------------ -------- ----\n\n");

	test_ptr_1 = "This is a test";
	test_ptr_2 = "This is a test";
	printf("Test Number 1: [%s]\n               [%s]\n\n",
		test_ptr_1, oneblank(test_ptr_2));

	test_ptr_1 = "This is a  test";
	test_ptr_2 = "This is a  test";
	printf("Test Number 2: [%s]\n               [%s]\n\n",
		test_ptr_1, oneblank(test_ptr_2));

	test_ptr_1 = "This is a   test";
	test_ptr_2 = "This is a   test";
	printf("Test Number 3: [%s]\n               [%s]\n\n",
		test_ptr_1, oneblank(test_ptr_2));

	test_ptr_1 = "This is a test ";
	test_ptr_2 = "This is a test ";
	printf("Test Number 4: [%s]\n               [%s]\n\n",
		test_ptr_1, oneblank(test_ptr_2));

	test_ptr_1 = "This is a test  ";
	test_ptr_2 = "This is a test  ";
	printf("Test Number 5: [%s]\n               [%s]\n\n",
		test_ptr_1, oneblank(test_ptr_2));

	test_ptr_1 = "This is a    test   ";
	test_ptr_2 = "This is a    test   ";
	printf("Test Number 6: [%s]\n               [%s]\n\n",
		test_ptr_1, oneblank(test_ptr_2));

	test_ptr_1 = "  This is a   test   ";
	test_ptr_2 = "  This is a   test   ";
	printf("Test Number 7: [%s]\n               [%s]\n",
		test_ptr_1, oneblank(test_ptr_2));

	return(0);
}
/* *********************************************************************** */

#endif /* TEST_MAIN */

