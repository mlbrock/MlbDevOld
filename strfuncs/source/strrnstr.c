/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Find last occurrence of a string in a string.

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

	NAME			:	strrnstr

	SYNOPSIS		:	char *strrnstr(search_string, target_string, search_length);

						const char *search_string;

						const char *target_string;

						size_t      search_length;

	DESCRIPTION	:	Locates the last occurrence of the string
						``target_string`` in the string ``search_string``.

						Only the first ``search_length`` characters of
						``search_string`` are searched.

						Comparisons necessary to locate ``target_string`` are
						performed in a case-insensitive fashion.

	PARAMETERS	:	``search_string`` is the string in which the search is
						to be performed.

						``target_string`` is the string for which the search is
						to be performed.

	RETURNS		:	If found, a pointer to the last occurrence of the string
						``target_string`` in the string ``search_string``. Otherwise,
						this function returns a ''NULL'' pointer.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strstr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.7)
						definition of ``strstr``, if ``target_string`` is of
						zero-length, a pointer to ``search_string`` is returned.

	CAVEATS		:	

	SEE ALSO		:	strnstr
						strrnistrn
						strrnstrn
						strrstr
						strrstrn
						STRFUNCS_strstr
						idxrnstr
						strrnchr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2018 Michael L. Brock

	OUTPUT INDEX:	strrnstr
						String Search Functions/Pointer:strrnstr
						STRFUNCS:String Search Functions/Pointer:strrnstr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strrnstr

	PUBLISH NAME:	strrnstr

	ENTRY CLASS	:	String Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strrnstr(const char *search_string, const char *target_string,
	size_t search_length)
#else
char *strrnstr(search_string, target_string, search_length)
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
		return(((char *) STRFUNCS_SHIM_memrmem(search_length, search_string,
			strlen(target_string), target_string)));
	}
}
/* *********************************************************************** */

