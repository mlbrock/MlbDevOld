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

	NAME			:	strrstr

	SYNOPSIS		:	char *strrstr(search_string, target_string);

						const char *search_string;

						const char *target_string;

	DESCRIPTION	:	Locates the last occurrence of the string
						``target_string`` in the string ``search_string``.

	PARAMETERS	:	``search_string`` is the string in which the search is
						to be performed.

						``target_string`` is the string for which the search is
						to be performed.

	RETURNS		:	If found, a pointer to the last occurrence of the string
						``target_string`` in the string ``search_string``. Otherwise,
						this function returns a ''NULL'' pointer.

	NOTES			:	Per the ISO C Standard 9899:1990 (section 7.11.5.7)
						definition of ``strstr``, if ``target_string`` is of
						zero-length, a pointer to ``search_string`` is returned.

	CAVEATS		:	

	SEE ALSO		:	strristr
						strrnstr
						strrnstrn
						strrstrn
						STRFUNCS_strstr
						idxrstr
						STRFUNCS_strrchr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2018 Michael L. Brock

	OUTPUT INDEX:	strrstr
						String Search Functions/Pointer:strrstr
						STRFUNCS:String Search Functions/Pointer:strrstr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strrstr

	PUBLISH NAME:	strrstr

	ENTRY CLASS	:	String Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strrstr(const char *search_string, const char *target_string)
#else
char *strrstr(search_string, target_string)
const char *search_string;
const char *target_string;
#endif /* #ifndef NARGS */
{
	if (!(*target_string))
		return(((char *) search_string));
	else
		return(((char *) STRFUNCS_SHIM_memrmem(strlen(search_string),
			search_string, strlen(target_string), target_string)));
}
/* *********************************************************************** */

