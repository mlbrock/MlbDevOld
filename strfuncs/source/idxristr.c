/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Find last occurrence of a string in a string,
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

	NAME			:	idxristr

	SYNOPSIS		:	int idxristr(search_string, target_string);

						const char *search_string;

						const char *target_string;

	DESCRIPTION	:	Locates the last occurrence of the string
						``target_string`` in the string ``search_string``.

						Comparisons necessary to locate ``target_string`` are
						performed in a case-insensitive fashion.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``search_string`` is the string in which the search is
						to be performed.

						(.) ``target_string`` is the string for which the search is
						to be performed.

	RETURNS		:	If found, the index of the last occurrence of the string
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

	SEE ALSO		:	idxrstr
						strristr
						idxrichr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2014 Michael L. Brock

	OUTPUT INDEX:	idxristr
						String Search Functions/Index:idxristr
						STRFUNCS:String Search Functions/Index:idxristr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	idxristr

	PUBLISH NAME:	idxristr

	ENTRY CLASS	:	String Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxristr(const char *search_string, const char *target_string)
#else
int idxristr(search_string, target_string)
const char *search_string;
const char *target_string;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = strristr(search_string, target_string)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	***********************************************************************	*/
/* BOH

	NAME			:	idxrnistr

	SYNOPSIS		:	int idxrnistr(search_string, target_string, search_length);

						const char *search_string;

						const char *target_string;

						size_t      search_length;

	DESCRIPTION	:	Locates the last occurrence of the string
						``target_string`` in the string ``search_string``.

						Only the first ``search_length`` characters of
						``search_string`` are searched.

						Comparisons necessary to locate ``target_string`` are
						performed in a case-insensitive fashion.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``search_string`` is the string in which the search is
						to be performed.

						(.) ``target_string`` is the string for which the search is
						to be performed.

						(.) ``search_length`` is the maximum number of characters to
						search within ``search_string``. Regardless of the value
						of ``search_length``, however, no more than the length of
						``search_string`` will be searched.

	RETURNS		:	If found, the index of the last occurrence of the string
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

	SEE ALSO		:	idxrnstr
						idxristr
						strrnistr
						idxrnichr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2014 Michael L. Brock

	OUTPUT INDEX:	idxrnistr
						String Search Functions/Index:idxrnistr
						STRFUNCS:String Search Functions/Index:idxrnistr
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	idxrnistr

	PUBLISH NAME:	idxrnistr

	ENTRY CLASS	:	String Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxrnistr(const char *search_string, const char *target_string,
	size_t search_length)
#else
int idxrnistr(search_string, target_string, search_length)
const char *search_string;
const char *target_string;
size_t      search_length;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = strrnistr(search_string, target_string,
		search_length)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

