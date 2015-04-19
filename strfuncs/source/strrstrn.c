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

	NAME			:	strrstrn

	SYNOPSIS		:	char *strrstrn(search_string, target_string, target_length);

						const char *search_string;

						const char *target_string;

						size_t      target_length;

	DESCRIPTION	:	Locates the last occurrence of the first
						``target_length`` characters in the string
						``target_string`` in the string ``search_string``.

	PARAMETERS	:	``search_string`` is the string in which the search is
						to be performed.

						``target_string`` is the string for which the search is
						to be performed.

						``target_length`` defines the number of characters in
						the string ``target_string`` for which the search is to
						be performed. Regardless of the value of ``target_length``,
						however, the search will be performed for a string no
						longer than the length of ``target_string``.

	RETURNS		:	If found, a pointer to the last occurrence of the string
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

	SEE ALSO		:	strristrn
						strrnstr
						strrnstrn
						strrstr
						STRFUNCS_strstr
						strstrn
						idxrstrn
						STRFUNCS_strrchr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	strrstrn
						String Search Functions/Pointer:strrstrn
						STRFUNCS:String Search Functions/Pointer:strrstrn
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strrstrn

	PUBLISH NAME:	strrstrn

	ENTRY CLASS	:	String Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strrstrn(const char *search_string, const char *target_string,
	size_t target_length)
#else
char *strrstrn(search_string, target_string, target_length)
const char *search_string;
const char *target_string;
size_t      target_length;
#endif /* #ifndef NARGS */
{
	size_t t_length;

	if ((!(*target_string)) || (!target_length))
		return(((char *) search_string));
	else {
		target_length = ((t_length = strlen(target_string)) < target_length) ?
			t_length : target_length;
		return(((char *) STRFUNCS_SHIM_memrmem(strlen(search_string),
			search_string, target_length, target_string)));
	}
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	***********************************************************************	*/
/* BOH

	NAME			:	strristrn

	SYNOPSIS		:	char *strristrn(search_string, target_string, target_length);

						const char *search_string;

						const char *target_string;

						size_t      target_length;

	DESCRIPTION	:	Locates the last occurrence of the first
						``target_length`` characters in the string
						``target_string`` in the string ``search_string``.

						Comparisons necessary to locate ``target_string`` are
						performed in a case-insensitive fashion.

	PARAMETERS	:	``search_string`` is the string in which the search is
						to be performed.

						``target_string`` is the string for which the search is
						to be performed.

						``target_length`` defines the number of characters in
						the string ``target_string`` for which the search is to
						be performed. Regardless of the value of ``target_length``,
						however, the search will be performed for a string no
						longer than the length of ``target_string``.

	RETURNS		:	If found, a pointer to the last occurrence of the string
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

	SEE ALSO		:	stristrn
						strristr
						strrnistr
						strrnistrn
						strrstrn
						STRFUNCS_strstr
						idxristrn
						strrichr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	strristrn
						String Search Functions/Pointer:strristrn
						STRFUNCS:String Search Functions/Pointer:strristrn
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strristrn

	PUBLISH NAME:	strristrn

	ENTRY CLASS	:	String Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strristrn(const char *search_string, const char *target_string,
	size_t target_length)
#else
char *strristrn(search_string, target_string, target_length)
const char *search_string;
const char *target_string;
size_t      target_length;
#endif /* #ifndef NARGS */
{
	size_t t_length;

	if ((!(*target_string)) || (!target_length))
		return(((char *) search_string));
	else {
		target_length = ((t_length = strlen(target_string)) < target_length) ?
			t_length : target_length;
		return(((char *) STRFUNCS_SHIM_memrimem(strlen(search_string),
			search_string, target_length, target_string)));
	}
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	***********************************************************************	*/
/* BOH

	NAME			:	strrnstrn

	SYNOPSIS		:	char *strrnstrn(search_string, target_string, search_length,
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

	RETURNS		:	If found, a pointer to the last occurrence of the string
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

	SEE ALSO		:	strnstrn
						strrnistrn
						strrnstr
						strrstr
						strrstrn
						STRFUNCS_strstr
						idxrnstrn
						strrnchr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	strrnstrn
						String Search Functions/Pointer:strrnstrn
						STRFUNCS:String Search Functions/Pointer:strrnstrn
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strrnstrn

	PUBLISH NAME:	strrnstrn

	ENTRY CLASS	:	String Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strrnstrn(const char *search_string, const char *target_string,
	size_t search_length, size_t target_length)
#else
char *strrnstrn(search_string, target_string, search_length, target_length)
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
		return(((char *) STRFUNCS_SHIM_memrmem(search_length, search_string,
			target_length, target_string)));
	}
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	***********************************************************************	*/
/* BOH

	NAME			:	strrnistrn

	SYNOPSIS		:	char *strrnistrn(search_string, target_string, search_length,
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

	RETURNS		:	If found, a pointer to the last occurrence of the string
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
						strristr
						strristrn
						strrnistr
						strrnstrn
						STRFUNCS_strstr
						idxrnistrn
						strrnichr

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	strrnistrn
						String Search Functions/Pointer:strrnistrn
						STRFUNCS:String Search Functions/Pointer:strrnistrn
						String Functions:See STRFUNCS
 
	PUBLISH XREF:	strrnistrn

	PUBLISH NAME:	strrnistrn

	ENTRY CLASS	:	String Search Functions/Pointer

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *strrnistrn(const char *search_string, const char *target_string,
	size_t search_length, size_t target_length)
#else
char *strrnistrn(search_string, target_string, search_length, target_length)
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
		return(((char *) STRFUNCS_SHIM_memrimem(search_length, search_string,
			target_length, target_string)));
	}
}
/* *********************************************************************** */

