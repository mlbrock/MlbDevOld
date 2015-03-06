/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Find first occurrence of a character in a string,
								ignoring case.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <string.h>

#include "strfunci.h"

/*	*********************************************************************** */

/*	*********************************************************************** */
/*	***********************************************************************	*/
/* BOH

	NAME			:	strichr

	SYNOPSIS		:	char *strichr(search_string, target_char);

						const char *search_string;

						int         target_char;

	DESCRIPTION	:	Locates the first occurrence of the character
						``target_char`` in the string ``search_string``.

						Comparisons necessary to locate ``target_char`` are
						performed in a case-insensitive fashion.

	PARAMETERS	:	``search_string`` is the string in which the search is
						to be performed.

						``target_char`` is the character for which the search is
						to be performed.

	RETURNS		:	If found, a pointer to the first occurrence of the character
						``target_char`` in the string ``search_string``. Otherwise,
						this function returns a ''NULL'' pointer.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strchr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.2)
						definition of ``strchr``, the terminating ASCII null
						character in ``search_string`` is considered to be part of
						the string. Therefore the code:

{|@}// Initialize to "ABC\0".
{@}char *search_data = "ABC";
{@}// Print the result.
{@}printf("offset = %u\n",
{@|}	((unsigned int) (strichr(search_data, '\0') - search_data)));

					will result in the following being printed:

{|@|}offset = 3

	CAVEATS		:	

	SEE ALSO		:	STRFUNCS_strchr
						strnichr
						strrichr
						idxichr
						stristr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	strichr
						Character Search Functions/Pointer:strichr
						STRFUNCS:Character Search Functions/Pointer:strichr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strichr

	PUBLISH NAME:	strichr

	ENTRY CLASS	:	Character Search Functions/Pointer

EOH */
/*	*********************************************************************** */
#ifndef NARGS
char *strichr(const char *search_string, int target_char)
#else
char *strichr(search_string, target_char)
const char *search_string;
int         target_char;
#endif /* #ifndef NARGS */
{
	target_char = strfmacs_toupper(target_char);

	for (; strfmacs_toupper(*search_string) != ((const char) target_char);
		search_string++) {
		if (!(*search_string))
			return(NULL);
	}

	return(((char *) search_string));
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

typedef struct {
	int         target_char;
	const char *target_ptr;
} TEST_ITEM;

const char TestString[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

TEST_ITEM TestList[] = {
	{	'A',	TestString			},
	{	'B',	TestString + 1		},
	{	'Z',	TestString + 25	},
	{	'a',	TestString			},
	{	'@',	NULL					},
	{	'\0',	TestString + 62	}
};

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = 0;
	unsigned int  count_1;
	char         *return_ptr;

	fprintf(stderr, "Test routine for function 'strichr()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		printf("Test Number %u:\n", count_1);
		if (isprint(TestList[count_1].target_char))
			printf(">>> Searching for '%c' in the string '%s\\0'.\n",
				TestList[count_1].target_char, TestString);
		else
			printf(">>> Searching for ASCII %u in the string '%s\\0'.\n",
				TestList[count_1].target_char, TestString);
		if ((return_ptr = strichr(TestString, TestList[count_1].target_char)) !=
			TestList[count_1].target_ptr) {
			printf(">>> ERROR:");
			return_code++;
		}
		else
			printf(">>> SUCCESS:");
		printf("Expected %p%s, returned %p%s.\n",
			TestList[count_1].target_ptr,
			(TestList[count_1].target_ptr == NULL) ? " (NULL)" : "",
			return_ptr, (return_ptr == NULL) ? " (NULL)" : "");
	}

	printf("\n***** %u errors encountered in regression test\n", return_code);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

