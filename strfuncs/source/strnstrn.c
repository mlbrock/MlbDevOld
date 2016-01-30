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

	NAME			:	strnstrn

	SYNOPSIS		:	char *strnstrn(search_string, target_string, search_length,
							target_length);

						const char *search_string;

						const char *target_string;

						size_t      search_length;

						size_t      target_length;

	DESCRIPTION	:	Locates the first occurrence of the first
						``target_length`` characters in the string
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

						``target_length`` defines the number of characters in
						the string ``target_string`` for which the search is to
						be performed. Regardless of the value of ``target_length``,
						however, the search will be performed for a string no
						longer than the length of ``target_string``.

	RETURNS		:	If found, a pointer to the first occurrence of the string
						``target_string`` in the string ``search_string``. Otherwise,
						this function returns a ''NULL'' pointer.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strstr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.7)
						definition of ``strstr``, if ``target_string`` is of
						zero-length, a pointer to ``search_string`` is returned.
						In keeping with that thinking, if ``target_length`` is
						equal to zero, a pointer to ``search_string`` is returned.

	CAVEATS		:	

	SEE ALSO		:	strnistrn
						strnstr
						strrnistrn
						STRFUNCS_strstr
						strstrn
						idxnstrn
						strnchr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2016 Michael L. Brock

	OUTPUT INDEX:	strnstrn
						String Search Functions/Pointer:strnstrn
						STRFUNCS:String Search Functions/Pointer:strnstrn
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strnstrn

	PUBLISH NAME:	strnstrn

	ENTRY CLASS	:	String Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strnstrn(const char *search_string, const char *target_string,
	size_t search_length, size_t target_length)
#else
char *strnstrn(search_string, target_string, search_length, target_length)
const char *search_string;
const char *target_string;
size_t      search_length;
size_t      target_length;
#endif /* #ifndef NARGS */
{
	size_t s_length;
	size_t t_length;

	if ((!(*target_string)) || (!target_length))
		return(((char *) search_string));
	else {
		search_length = ((s_length = strlen(search_string)) < search_length) ?
			s_length : search_length;
		target_length = ((t_length = strlen(target_string)) < target_length) ?
			t_length : target_length;
		return(((char *) STRFUNCS_SHIM_memmem(search_length, search_string,
			target_length, target_string)));
	}
}
/* *********************************************************************** */

