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

	NAME			:	idxrstr

	SYNOPSIS		:	int idxrstr(search_string, target_string);

						const char *search_string;

						const char *target_string;

	DESCRIPTION	:	Locates the last occurrence of the string
						``target_string`` in the string ``search_string``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``search_string`` is the string in which the search is
						to be performed.

						(.) ``target_string`` is the string for which the search is
						to be performed.

	RETURNS		:	If found, the index of the last occurence of the string
						``target_string`` in the string ``search_string``. Otherwise,
						this function returns ''-1'' --- but refer to the notes in
						the ''Caveats'' section.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strstr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.7)
						definition of ``strstr``, if ``target_string`` is of
						zero-length, a pointer to ``search_string`` is returned.

	CAVEATS		:	This function returns a signed int and therefore cannot
						accurately represent offsets greater than that defined
						by the manifest constant ''INT_MAX''. You have been
						warned.

	SEE ALSO		:	idxstr
						strrstr
						idxrchr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	idxrstr
						String Search Functions/Index:idxrstr
						STRFUNCS:String Search Functions/Index:idxrstr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	idxrstr

	PUBLISH NAME:	idxrstr

	ENTRY CLASS	:	String Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxrstr(const char *search_string, const char *target_string)
#else
int idxrstr(search_string, target_string)
const char *search_string;
const char *target_string;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = strrstr(search_string, target_string)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

