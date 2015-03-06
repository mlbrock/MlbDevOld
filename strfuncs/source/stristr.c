/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Find first occurrence of a string in a string,
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

	NAME			:	stristr

	SYNOPSIS		:	char *stristr(search_string, target_string);

						const char *search_string;

						const char *target_string;

	DESCRIPTION	:	Locates the first occurrence of the string
						``target_string`` in the string ``search_string``.

						Comparisons necessary to locate ``target_string`` are
						performed in a case-insensitive fashion.

	PARAMETERS	:	``search_string`` is the string in which the search is
						to be performed.

						``target_string`` is the string for which the search is
						to be performed.

	RETURNS		:	If found, a pointer to the first occurrence of the string
						``target_string`` in the string ``search_string``. Otherwise,
						this function returns a ''NULL'' pointer.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strstr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.7)
						definition of ``strstr``, if ``target_string`` is of
						zero-length, a pointer to ``search_string`` is returned.

	CAVEATS		:	

	SEE ALSO		:	stristrn
						strnistr
						strnistrn
						strristr
						STRFUNCS_strstr
						idxistr
						strichr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	stristr
						String Search Functions/Pointer:stristr
						STRFUNCS:String Search Functions/Pointer:stristr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	stristr

	PUBLISH NAME:	stristr

	ENTRY CLASS	:	String Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *stristr(const char *search_string, const char *target_string)
#else
char *stristr(search_string, target_string)
const char *search_string;
const char *target_string;
#endif /* #ifndef NARGS */
{
	if (!(*target_string))
		return(((char *) search_string));
	else
		return(((char *) memimem(strlen(search_string), search_string,
			strlen(target_string), target_string)));
}
/* *********************************************************************** */

