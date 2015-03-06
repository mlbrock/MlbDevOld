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

	NAME			:	idxistrn

	SYNOPSIS		:	int idxistrn(search_string, target_string, target_length);

						const char *search_string;

						const char *target_string;

						size_t      target_length;

	DESCRIPTION	:	Locates the first occurrence of the first
						``target_length`` characters in the string
						``target_string`` in the string ``search_string``.

						Comparisons necessary to locate ``target_string`` are
						performed in a case-insensitive fashion.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``search_string`` is the string in which the search is
						to be performed.

						(.) ``target_string`` is the string for which the search is
						to be performed.

						``target_length`` defines the number of characters in
						the string ``target_string`` for which the search is to
						be performed. Regardless of the value of ``target_length``,
						however, the search will be performed for a string no
						longer than the length of ``target_string``.

	RETURNS		:	If found, the index of the first occurrence of the string
						``target_string`` in the string ``search_string``. Otherwise,
						this function returns ''-1'' --- but refer to the notes in
						the ''Caveats'' section.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strstr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.7)
						definition of ``strstr``, if ``target_string`` is of
						zero-length, a pointer to ``search_string`` is returned.
						In keeping with that thinking, if ``target_length`` is
						equal to zero, a pointer to ``search_string`` is returned.

	CAVEATS		:	This function returns a signed int and therefore cannot
						accurately represent offsets greater than that defined
						by the manifest constant ''INT_MAX''. You have been
						warned.

	SEE ALSO		:	STRFUNCS_strstr
						idxstrn
						idxnistrn
						idxnistr
						idxichr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	idxistrn
						String Search Functions/Index:idxistrn
						STRFUNCS:String Search Functions/Index:idxistrn
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	idxistrn

	PUBLISH NAME:	idxistrn

	ENTRY CLASS	:	String Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxistrn(const char *search_string, const char *target_string,
	size_t target_length)
#else
int idxistrn(search_string, target_string, target_length)
const char *search_string;
const char *target_string;
size_t      target_length;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = stristrn(search_string, target_string,
		target_length)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	***********************************************************************	*/
/* BOH

	NAME			:	idxnistrn

	SYNOPSIS		:	int idxnistrn(search_string, target_string, search_length,
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

						(.) ``target_length`` defines the number of characters in
						the string ``target_string`` for which the search is to
						be performed. Regardless of the value of ``target_length``,
						however, the search will be performed for a string no
						longer than the length of ``target_string``.

	RETURNS		:	If found, the index of the first occurrence of the string
						``target_string`` in the string ``search_string``. Otherwise,
						this function returns ''-1'' --- but refer to the notes in
						the ''Caveats'' section.

	NOTES			:	This function is a permutation of the functionality
						embodied in the standard C library function ``strstr``.
						Per the ISO C Standard 9899:1990 (section 7.11.5.7)
						definition of ``strstr``, if ``target_string`` is of
						zero-length, a pointer to ``search_string`` is returned.
						In keeping with that thinking, if ``target_length`` is
						equal to zero, a pointer to ``search_string`` is returned.

	CAVEATS		:	This function returns a signed int and therefore cannot
						accurately represent offsets greater than that defined
						by the manifest constant ''INT_MAX''. You have been
						warned.

	SEE ALSO		:	STRFUNCS_strstr
						strnistrn
						idxnstrn
						idxnistr
						idxistrn
						idxnichr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	idxnistrn
						String Search Functions/Index:idxnistrn
						STRFUNCS:String Search Functions/Index:idxnistrn
						String Functions:See STRFUNCS

	PUBLISH XREF:	idxnistrn

	PUBLISH NAME:	idxnistrn

	ENTRY CLASS	:	String Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxnistrn(const char *search_string, const char *target_string,
	size_t search_length, size_t target_length)
#else
int idxnistrn(search_string, target_string, search_length, target_length)
const char *search_string;
const char *target_string;
size_t      search_length;
size_t      target_length;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = strnistrn(search_string, target_string,
		search_length, target_length)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

