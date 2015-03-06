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

	NAME			:	strnichr

	SYNOPSIS		:	char *strnichr(search_string, target_char, search_length);

						const char *search_string;

						int         target_char;

						size_t      search_length;

	DESCRIPTION	:	Locates the first occurrence of the character
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
{@|}	((unsigned int) (strnichr(search_data, '\0', 20) - search_data)));

					will result in the following being printed:

{|@|}offset = 3

	CAVEATS		:	

	SEE ALSO		:	STRFUNCS_strchr
						strichr
						strnchr
						strrnichr
						idxnichr
						strnistr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	strnichr
						Character Search Functions/Pointer:strnichr
						STRFUNCS:Character Search Functions/Pointer:strnichr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strnichr

	PUBLISH NAME:	strnichr

	ENTRY CLASS	:	Character Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strnichr(const char *search_string, int target_char,
	size_t search_length)
#else
char *strnichr(search_string, target_char, search_length)
const char *search_string;
int         target_char;
size_t      search_length;
#endif /* #ifndef NARGS */
{
	char *return_ptr = NULL;

	if (search_length) {
		target_char = strfmacs_toupper(target_char);
		do {
			if (strfmacs_toupper(*search_string) == ((const char) target_char)) {
				return_ptr = ((char *) search_string);
				break;
			}
		} while (--search_length && *search_string++);
	}

	return(return_ptr);
}
/* *********************************************************************** */

