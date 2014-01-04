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

	NAME			:	idxrstrn

	SYNOPSIS		:	int idxrstrn(search_string, target_string, target_length);

						const char *search_string;

						const char *target_string;

						size_t      target_length;

	DESCRIPTION	:	Locates the last occurrence of the first
						``target_length`` characters in the string
						``target_string`` in the string ``search_string``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``search_string`` is the string in which the search is
						to be performed.

						(.) ``target_string`` is the string for which the search is
						to be performed.

						(.) ``target_length`` defines the number of characters in
						the string ``target_string`` for which the search is to
						be performed. Regardless of the value of ``target_length``,
						however, the search will be performed for a string no
						longer than the length of ``target_string``.

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
						idxrnstr
						idxrnstrn
						idxristrn
						strrstrn
						idxrchr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2014 Michael L. Brock

	OUTPUT INDEX:	idxrstrn
						String Search Functions/Index:idxrstrn
						STRFUNCS:String Search Functions/Index:idxrstrn
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	idxrstrn

	PUBLISH NAME:	idxrstrn

	ENTRY CLASS	:	String Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxrstrn(const char *search_string, const char *target_string,
	size_t target_length)
#else
int idxrstrn(search_string, target_string, target_length)
const char *search_string;
const char *target_string;
size_t      target_length;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = strrstrn(search_string, target_string,
		target_length)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	***********************************************************************	*/
/* BOH

	NAME			:	idxristrn

	SYNOPSIS		:	int idxristrn(search_string, target_string, target_length);

						const char *search_string;

						const char *target_string;

						size_t      target_length;

	DESCRIPTION	:	Locates the last occurrence of the first
						``target_length`` characters in the string
						``target_string`` in the string ``search_string``.

						Comparisons necessary to locate ``target_string`` are
						performed in a case-insensitive fashion.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``search_string`` is the string in which the search is
						to be performed.

						(.) ``target_string`` is the string for which the search is
						to be performed.

						(.) ``target_length`` defines the number of characters in
						the string ``target_string`` for which the search is to
						be performed. Regardless of the value of ``target_length``,
						however, the search will be performed for a string no
						longer than the length of ``target_string``.

	RETURNS		:	If found, the index of the last occurrence of the string
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

	SEE ALSO		:	idxistrn
						idxristr
						strristrn
						idxrichr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2014 Michael L. Brock

	OUTPUT INDEX:	idxristrn
						String Search Functions/Index:idxristrn
						STRFUNCS:String Search Functions/Index:idxristrn
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	idxristrn

	PUBLISH NAME:	idxristrn

	ENTRY CLASS	:	String Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxristrn(const char *search_string, const char *target_string,
	size_t target_length)
#else
int idxristrn(search_string, target_string, target_length)
const char *search_string;
const char *target_string;
size_t      target_length;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = strristrn(search_string, target_string,
		target_length)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	***********************************************************************	*/
/* BOH

	NAME			:	idxrnstrn

	SYNOPSIS		:	int idxrnstrn(search_string, target_string, search_length,
							target_length);

						const char *search_string;

						const char *target_string;

						size_t      search_length;

						size_t      target_length;

	DESCRIPTION	:	Locates the last occurrence of the first
						``target_length`` characters in the string
						``target_string`` in the string ``search_string``.

						Only the first ``search_length`` characters of
						``search_string`` are searched.

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

	RETURNS		:	If found, the index of the last occurrence of the string
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

	SEE ALSO		:	idxnstrn
						idxrnistrn
						idxrstr
						strrnstrn
						idxrnchr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2014 Michael L. Brock

	OUTPUT INDEX:	idxrnstrn
						String Search Functions/Index:idxrnstrn
						STRFUNCS:String Search Functions/Index:idxrnstrn
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	idxrnstrn

	PUBLISH NAME:	idxrnstrn

	ENTRY CLASS	:	String Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxrnstrn(const char *search_string, const char *target_string,
	size_t search_length, size_t target_length)
#else
int idxrnstrn(search_string, target_string, search_length, target_length)
const char *search_string;
const char *target_string;
size_t      search_length;
size_t      target_length;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = strrnstrn(search_string, target_string,
		search_length, target_length)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	***********************************************************************	*/
/* BOH

	NAME			:	idxrnistrn

	SYNOPSIS		:	int idxrnistrn(search_string, target_string, search_length,
							target_length);

						const char *search_string;

						const char *target_string;

						size_t      search_length;

						size_t      target_length;

	DESCRIPTION	:	Locates the last occurrence of the first
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

	RETURNS		:	If found, the index of the last occurrence of the string
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

	SEE ALSO		:	idxrnstrn
						idxristr
						strrnistrn
						idxrnichr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2014 Michael L. Brock

	OUTPUT INDEX:	idxrnistrn
						String Search Functions/Index:idxrnistrn
						STRFUNCS:String Search Functions/Index:idxrnistrn
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	idxrnistrn

	PUBLISH NAME:	idxrnistrn

	ENTRY CLASS	:	String Search Functions/Index

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int idxrnistrn(const char *search_string, const char *target_string,
	size_t search_length, size_t target_length)
#else
int idxrnistrn(search_string, target_string, search_length, target_length)
const char *search_string;
const char *target_string;
size_t      search_length;
size_t      target_length;
#endif /* #ifndef NARGS */
{
	int   found_index = -1;
	char *found_ptr;

	if ((found_ptr = strrnistrn(search_string, target_string,
		search_length, target_length)) != NULL)
		found_index = ((int) (found_ptr - ((char *) search_string)));

	return(found_index);
}
/* *********************************************************************** */

