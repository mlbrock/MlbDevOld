/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Find first occurrence of a character in a string.

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

	NAME			:	idxchr

	SYNOPSIS		:	int idxchr(search_string, target_char);

						const char *search_string;

						int         target_char;

	DESCRIPTION	:	Locates the first occurrence of the character
						``target_char`` in the string ``search_string``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``search_string`` is the string in which the search is
						to be performed.

						(.) ``target_char`` is the character for which the search is
						to be performed.

	RETURNS		:	If found, the index of the first occurrence of the character
						``target_char`` in the string ``search_string``. Otherwise,
						this function returns ''-1'' --- but refer to the notes in
						the ''Caveats'' section.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strchr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.2)
						definition of ``strchr``, the terminating ASCII null
						character in ``search_string`` is considered to be part of
						the string.

	CAVEATS		:	This function returns a signed int and therefore cannot
						accurately represent offsets greater than that defined
						by the manifest constant ''INT_MAX''. You have been
						warned.

	SEE ALSO		:	idxichr
						STRFUNCS_strchr
						idxstr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2016 Michael L. Brock

	OUTPUT INDEX:	idxchr
						Character Search Functions/Index:idxchr
						STRFUNCS:Character Search Functions/Index:idxchr
						String Functions:See STRFUNCS


 
	PUBLISH XREF:	idxchr

	PUBLISH NAME:	idxchr

	ENTRY CLASS	:	Character Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxchr(const char *search_string, int target_char)
#else
int idxchr(search_string, target_char)
const char *search_string;
int         target_char;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = strchr(search_string, target_char)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

