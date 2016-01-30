/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Find last occurrence of a character in a string.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2016.
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

	NAME			:	STRFUNCS_strrchr

	SYNOPSIS		:	char *STRFUNCS_strrchr(search_string, target_char);

						const char *search_string;

						int         target_char;

	DESCRIPTION	:	Locates the last occurrence of the character
						``target_char`` in the string ``search_string``.

	PARAMETERS	:	``search_string`` is the string in which the search is
						to be performed.

						``target_char`` is the character for which the search is
						to be performed.

	RETURNS		:	If found, a pointer to the last occurrence of the character
						``target_char`` in the string ``search_string``. Otherwise,
						this function returns a ''NULL'' pointer.

	NOTES			:	Per the ISO C Standard 9899:1990 (section 7.11.5.5)
						definition of ``strrchr()``, the terminating ASCII null
						character in ``search_string`` is considered to be part
						of the string. Therefore the code:

{|@}// Initialize to "ABC\0".
{@}char *search_data = "ABC";
{@}// Print the result.
{@}printf("offset = %u\n",
{@|}	((unsigned int) (STRFUNCS_strrchr(search_data, '\0') - search_data)));

					will result in the following being printed:

{|@|}offset = 3

	CAVEATS		:	

	SEE ALSO		:	STRFUNCS_strchr
						strrichr
						strrnchr
						idxrchr
						strrstr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2016 Michael L. Brock

	OUTPUT INDEX:	STRFUNCS_strrchr
						Character Search Functions/Pointer:STRFUNCS_strrchr
						STRFUNCS:Character Search Functions/Pointer:STRFUNCS_strrchr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	STRFUNCS_strrchr

	PUBLISH NAME:	STRFUNCS_strrchr

	ENTRY CLASS	:	Character Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *STRFUNCS_strrchr(const char *search_string, int target_char)
#else
char *STRFUNCS_strrchr(search_string, target_char)
const char *search_string;
int         target_char;
#endif /* #ifndef NARGS */
{
	char *return_ptr = NULL;

	do {
		if (*search_string == ((const char) target_char))
			return_ptr = ((char *) search_string);
	} while (*search_string++);

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
	"ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

TEST_ITEM TestList[] = {
	{	'A',	TestString + 26	},
	{	'B',	TestString + 27	},
	{	'Z',	TestString + 51	},
	{	'a',	NULL					},
	{	'@',	NULL					},
	{	'\0',	TestString + 62	}
};

COMPAT_FN_DECL(int main, (void));

int main()
{
	int           return_code = 0;
	unsigned int  count_1;
	char         *return_ptr;

	fprintf(stderr, "Test routine for function 'STRFUNCS_strrchr()'\n");
	fprintf(stderr, "---- ------- --- -------- --------------------\n\n");

	for (count_1 = 0; count_1 < (sizeof(TestList) / sizeof(TestList[0]));
		count_1++) {
		printf("Test Number %u:\n", count_1);
		if (isprint(TestList[count_1].target_char))
			printf(">>> Searching for '%c' in the string '%s\\0'.\n",
				TestList[count_1].target_char, TestString);
		else
			printf(">>> Searching for ASCII %u in the string '%s\\0'.\n",
				TestList[count_1].target_char, TestString);
		if ((return_ptr = STRFUNCS_strrchr(TestString,
      	TestList[count_1].target_char)) != TestList[count_1].target_ptr) {
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

