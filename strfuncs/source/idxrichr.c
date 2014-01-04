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

		Copyright Michael L. Brock 1986 - 2014.
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

	NAME			:	idxrichr

	SYNOPSIS		:	int idxrichr(search_string, target_char);

						const char *search_string;

						int         target_char;

	DESCRIPTION	:	Locates the last occurrence of the character
						``target_char`` in the string ``search_string``.

						Comparisons necessary to locate ``target_char`` are
						performed in a case-insensitive fashion.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``search_string`` is the string in which the search is
						to be performed.

						(.) ``target_char`` is the character for which the search is
						to be performed.

	RETURNS		:	If found, the index of the last occurrence of the character
						``target_char`` in the string ``search_string``. Otherwise,
						this function returns ''-1'' --- but refer to the notes in
						the ''Caveats'' section.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strrchr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.5)
						definition of ``strrchr``, the terminating ASCII null
						character in ``search_string`` is considered to be part of
						the string.

	CAVEATS		:	This function returns a signed int and therefore cannot
						accurately represent offsets greater than that defined
						by the manifest constant ''INT_MAX''. You have been
						warned.

	SEE ALSO		:	idxrchr
						idxichr
						strrichr
						idxristr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2014 Michael L. Brock

	OUTPUT INDEX:	idxrichr
						Character Search Functions/Index:idxrichr
						STRFUNCS:Character Search Functions/Index:idxrichr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	idxrichr

	PUBLISH NAME:	idxrichr

	ENTRY CLASS	:	Character Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxrichr(const char *search_string, int target_char)
#else
int idxrichr(search_string, target_char)
const char *search_string;
int         target_char;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = strrichr(search_string, target_char)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	***********************************************************************	*/
/* BOH

	NAME			:	idxrnichr

	SYNOPSIS		:	int idxrnichr(search_string, target_char, search_length);

						const char *search_string;

						int         target_char;

						size_t      search_length;

	DESCRIPTION	:	Locates the last occurrence of the character
						``target_char`` in the string ``search_string`` within the
						first ``search_length`` characters of ``search_string``.

						Comparisons necessary to locate ``target_char`` are
						performed in a case-insensitive fashion.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``search_string`` is the string in which the search is
						to be performed.

						(.) ``target_char`` is the character for which the search is
						to be performed.

						(.) ``search_length`` is the maximum number of characters to
						search within ``search_string``. Regardless of the value
						of ``search_length``, however, no more than the length of
						``search_string`` (plus one for the terminating ASCII null
						character) will be searched.

	RETURNS		:	If found, the index of the last occurrence of the character
						``target_char`` in the string ``search_string``. Otherwise,
						this function returns ''-1'' --- but refer to the notes in
						the ''Caveats'' section.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strrchr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.5)
						definition of ``strrchr``, the terminating ASCII null
						character in ``search_string`` is considered to be part of
						the string.

	CAVEATS		:	This function returns a signed int and therefore cannot
						accurately represent offsets greater than that defined
						by the manifest constant ''INT_MAX''. You have been
						warned.

	SEE ALSO		:	idxrichr
						strrnichr
						strrnistr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2014 Michael L. Brock

	OUTPUT INDEX:	idxrnichr
						Character Search Functions/Index:idxrnichr
						STRFUNCS:Character Search Functions/Index:idxrnichr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	idxrnichr

	PUBLISH NAME:	idxrnichr

	ENTRY CLASS	:	Character Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxrnichr(const char *search_string, int target_char, size_t search_length)
#else
int idxrnichr(search_string, target_char, search_length)
const char *search_string;
int         target_char;
size_t      search_length;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = strrnichr(search_string, target_char,
		search_length)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

