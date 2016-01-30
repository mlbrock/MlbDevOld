/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Case-insensitive comparison of strings.

	Revision History	:	1991-10-01 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  STR_strnicmp

   SYNOPSIS    :  return_code = STR_strnicmp(control_ptr, string_ptr_1,
							string_ptr_2, string_length);

						int         return_code;

						void       *control_ptr;

						const char *string_ptr_1;

						const char *string_ptr_2;

						size_t      string_length;

   DESCRIPTION :  Compares the two strings (to which the parameters
						``string_ptr_1`` and ``string_ptr_2`` point) for equality.

						The strings are compared character-by-character until
						one of the three conditions is met:

						(.) a character difference is detected between the two
						strings;

						(.) null-termination (ASCII 0) is detected in either
						string; or,

						(.) ``string_length`` characters have been compared.

						The comparison is performed in a case-insensitive
						manner.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparison
						If unnecessary, it may be a NULL pointer.

						(.) ``string_ptr_1`` points to the first null-terminated
						string to be compared.

						(.) ``string_ptr_2`` points to the second null-terminated
						string to be compared.

						(.) ``string_length`` is the maximum number of characters
						to be compared.

   RETURNS     :  Returns from this function are as follow:

						(.) negative if the first string is less than second.

						(.) positive if the first string is greater than second.

						(.) zero if the strings are equal.

   NOTES       :  The ``control_ptr`` parameter is present only because this
						function is used internally by other STRFUNCS list
						functions. They provide function-call compatibility with
						other, more generic, comparison functions.

   CAVEATS     :  

   SEE ALSO    :  STR_strcmp
						STR_stricmp
						STR_strncmp
						STR_LIST_bsearch
						STR_LIST_qsort

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2016 Michael L. Brock

   OUTPUT INDEX:  STR_strnicmp
						String List Functions:STR_strnicmp
						STRFUNCS:String List Functions:STR_strnicmp
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_strnicmp

   PUBLISH NAME:	STR_strnicmp

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int STR_strnicmp(void *control_ptr, const char *string_ptr_1,
	const char *string_ptr_2, size_t string_length)
#else
int STR_strnicmp(control_ptr, string_ptr_1, string_ptr_2, string_length)
void       *control_ptr;
const char *string_ptr_1;
const char *string_ptr_2;
size_t      string_length;
#endif /* #ifndef NARGS */
{
#ifdef __GNUC__
	((void)(control_ptr));
#endif /* #ifdef __GNUC__ */

	return(STRFUNCS_strnicmp(string_ptr_1, string_ptr_2, string_length));
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */
