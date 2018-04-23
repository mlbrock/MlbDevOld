/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Find last occurrence of a character in a string,
								ignoring case.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2018.
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

	NAME			:	strrichr

	SYNOPSIS		:	char *strrichr(search_string, target_char);

						const char *search_string;

						int         target_char;

	DESCRIPTION	:	Locates the last occurrence of the character
						``target_char`` in the string ``search_string``.

						Comparisons necessary to locate ``target_char`` are
						performed in a case-insensitive fashion.

	PARAMETERS	:	``search_string`` is the string in which the search is
						to be performed.

						``target_char`` is the character for which the search is
						to be performed.

	RETURNS		:	If found, a pointer to the last occurrence of the character
						``target_char`` in the string ``search_string``. Otherwise,
						this function returns a ''NULL'' pointer.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strrchr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.5)
						definition of ``strrchr``, the terminating ASCII null
						character in ``search_string`` is considered to be part
						of the string. Therefore the code:

{|@}// Initialize to "ABC\0".
{@}char *search_data = "ABC";
{@}// Print the result.
{@}printf("offset = %u\n",
{@|}	((unsigned int) (strrichr(search_data, '\0') - search_data)));

					will result in the following being printed:

{|@|}offset = 3

	CAVEATS		:	

	SEE ALSO		:	STRFUNCS_strchr
						strichr
						STRFUNCS_strrchr
						strrnichr
						idxrichr
						strristr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2018 Michael L. Brock

	OUTPUT INDEX:	strrichr
						Character Search Functions/Pointer:strrichr
						STRFUNCS:Character Search Functions/Pointer:strrichr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strrichr

	PUBLISH NAME:	strrichr

	ENTRY CLASS	:	Character Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strrichr(const char *search_string, int target_char)
#else
char *strrichr(search_string, target_char)
const char *search_string;
int         target_char;
#endif /* #ifndef NARGS */
{
	char *return_ptr = NULL;

	target_char = strfmacs_toupper(target_char);

	do {
		if (strfmacs_toupper(*search_string) == ((const char) target_char))
			return_ptr = ((char *) search_string);
	} while (*search_string++);

	return(return_ptr);
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	***********************************************************************	*/
/* BOH

	NAME			:	strrnichr

	SYNOPSIS		:	char *strrnichr(search_string, target_char, search_length);

						const char *search_string;

						int         target_char;

						size_t      search_length;

	DESCRIPTION	:	Locates the last occurrence of the character
						``target_char`` in the string ``search_string`` within the
						first ``search_length`` characters of ``search_string``.

						Comparisons necessary to locate ``target_char`` are
						performed in a case-insensitive fashion.

	PARAMETERS	:	``search_string`` is the string in which the search is
						to be performed.

						``target_char`` is the character for which the search is
						to be performed.

						``search_length`` is the maximum number of characters to
						search within ``search_string``. Regardless of the value
						of ``search_length``, however, no more than the length of
						``search_string`` (plus one for the terminating ASCII null
						character) will be searched.

	RETURNS		:	If found, a pointer to the last occurrence of the character
						``target_char`` in the string ``search_string``. Otherwise,
						this function returns a ''NULL'' pointer.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strrchr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.5)
						definition of ``strrchr``, the terminating ASCII null
						character in ``search_string`` is considered to be part
						of the string. Therefore the code:

{|@}// Initialize to "ABC\0".
{@}char *search_data = "ABC";
{@}// Print the result.
{@}printf("offset = %u\n",
{@|}	((unsigned int) (strrnichr(search_data, '\0', 20) - search_data)));

						will print:

{|@|}offset = 3

	CAVEATS		:

	SEE ALSO		:	STRFUNCS_strchr
						strnichr
						STRFUNCS_strrchr
						strrnchr
						idxrnichr
						strrnistr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2018 Michael L. Brock

	OUTPUT INDEX:	strrnichr
						Character Search Functions/Pointer:strrnichr
						STRFUNCS:Character Search Functions/Pointer:strrnichr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strrnichr

	PUBLISH NAME:	strrnichr

	ENTRY CLASS	:	Character Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strrnichr(const char *search_string, int target_char,
	size_t search_length)
#else
char *strrnichr(search_string, target_char, search_length)
const char *search_string;
int         target_char;
size_t      search_length;
#endif /* #ifndef NARGS */
{
	char *return_ptr = NULL;

	if (search_length) {
		target_char = strfmacs_toupper(target_char);
		do {
			if (strfmacs_toupper(*search_string) == ((const char) target_char))
				return_ptr = ((char *) search_string);
		} while (--search_length && *search_string++);
	}

	return(return_ptr);
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
	{	'A',	TestString + 26	},
	{	'B',	TestString + 27	},
	{	'Z',	TestString + 51	},
	{	'a',	TestString + 26	},
	{	'@',	NULL					},
	{	'\0',	TestString + 62	}
};

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = 0;
	unsigned int  count_1;
	char         *return_ptr;

	fprintf(stderr, "Test routine for function 'strrichr()'\n");
	fprintf(stderr, "---- ------- --- -------- ------------\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		printf("Test Number %u:\n", count_1);
		if (isprint(TestList[count_1].target_char))
			printf(">>> Searching for '%c' in the string '%s\\0'.\n",
				TestList[count_1].target_char, TestString);
		else
			printf(">>> Searching for ASCII %u in the string '%s\\0'.\n",
				TestList[count_1].target_char, TestString);
		if ((return_ptr = strrichr(TestString, TestList[count_1].target_char)) !=
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

