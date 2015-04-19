/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Find first occurrence of a string in a string.

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

	NAME			:	strnstr

	SYNOPSIS		:	char *strnstr(search_string, target_string, search_length);

						const char *search_string;

						const char *target_string;

						size_t      search_length;

	DESCRIPTION	:	Locates the first occurrence of the string
						``target_string`` in the string ``search_string``.

						Only the first ``search_length`` characters of
						``search_string`` are searched.

	PARAMETERS	:	``search_string`` is the string in which the search is
						to be performed.

						``target_string`` is the string for which the search is
						to be performed.

						``search_length`` is the maximum number of characters to
						search within ``search_string``. Regardless of the value
						of ``search_length``, however, no more than the length of
						``search_string`` will be searched.

	RETURNS		:	If found, a pointer to the first occurrence of the string
						``target_string`` in the string ``search_string``. Otherwise,
						this function returns a ''NULL'' pointer.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strstr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.7)
						definition of ``strstr``, if ``target_string`` is of
						zero-length, a pointer to ``search_string`` is returned.

	CAVEATS		:	

	SEE ALSO		:	strnistr
						strrnstr
						strnstrn
						STRFUNCS_strstr
						strstrn
						idxnstr
						strnchr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	strnstr
						String Search Functions/Pointer:strnstr
						STRFUNCS:String Search Functions/Pointer:strnstr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strnstr

	PUBLISH NAME:	strnstr

	ENTRY CLASS	:	String Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strnstr(const char *search_string, const char *target_string,
	size_t search_length)
#else
char *strnstr(search_string, target_string, search_length)
const char *search_string;
const char *target_string;
size_t      search_length;
#endif /* #ifndef NARGS */
{
	size_t s_length;

	if (!(*target_string))
		return(((char *) search_string));
	else {
		search_length = ((s_length = strlen(search_string)) < search_length) ?
			s_length : search_length;
		return(((char *) STRFUNCS_SHIM_memmem(search_length, search_string,
			strlen(target_string), target_string)));
	}
}
/* *********************************************************************** */

