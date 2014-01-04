/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Appends a string element to an array of pointers to
								strings.

	Revision History	:	1991-09-13 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
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

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strln_append

   SYNOPSIS    :  return_code = strln_append(string_count, string_list,
							in_string, string_length);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

						char           *in_string;

						size_t          string_length;

   DESCRIPTION :  Appends an array element to an array of pointers to strings.
						The string copied from ``in_string`` will be truncated to a
						maximum length of ``string_length`` bytes (excluding the
						terminating ASCII NUL byte).

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to integer which contains the
						number of elements in the array to which ``string_list``
						points.

						(-) If the function succeeds in appending the element
						``in_string`` then that integer will be incremented.

						(.) ``string_list`` is a triply-indirect pointer to ``char``
						(``char ***``) which contains the array. If the function
						succeeds in appending the element ``in_string`` then the
						memory pointed to by ``string_list`` will be re-allocated to
						hold the newly-added element.

						(.) ``in_string`` points to the area of memory to be
						appended to the array pointed to by ``string_list``.

						(.) ``string_length`` is the maximum length of ``in_string``
						to be inserted into the array, not including the terminating
						ASCII NUL byte.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  strl_append
						strln_add
						strl_copy
						strln_insert
						strl_remove
						meml_append
						mema_append

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  strln_append
						String List Functions:strln_append
						STRFUNCS:String List Functions:strln_append
						String Functions:See STRFUNCS

   PUBLISH XREF:  strln_append

   PUBLISH NAME:	strln_append

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int strln_append(unsigned int *string_count, char ***string_list,
	const char *in_string, size_t string_length)
#else
int strln_append(string_count, string_list, in_string, string_length)
unsigned int   *string_count;
char         ***string_list;
const char     *in_string;
size_t          string_length;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = memlapp(string_count, ((void ***) string_list),
		((const void *) in_string), string_length + 1)) == STRFUNCS_SUCCESS) {
		if (string_length < strlen(in_string))
			(*string_list)[*string_count - 1][string_length] = '\0';
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strlnapp

   SYNOPSIS    :  return_code =  strlnapp(string_count, string_list,
							in_string, string_length);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

						char           *in_string;

						size_t          string_length;

   DESCRIPTION :  Appends an array element to an array of pointers to strings.
						The string copied from ``in_string`` will be truncated to a
						maximum length of ``string_length`` bytes (excluding the
						terminating ASCII NUL byte).

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to integer which contains the
						number of elements in the array to which ``string_list``
						points.

						(-) If the function succeeds in appending the element
						``in_string`` then that integer will be incremented.

						(.) ``string_list`` is a triply-indirect pointer to ``char``
						(``char ***``) which contains the array. If the function
						succeeds in appending the element ``in_string`` then the
						memory pointed to by ``string_list`` will be re-allocated to
						hold the newly-added element.

						(.) ``in_string`` points to the area of memory to be
						appended to the array pointed to by ``string_list``.

						(.) ``string_length`` is the maximum length of ``in_string``
						to be inserted into the array, not including the terminating
						ASCII NUL byte.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  This function does no more than call the function
						``strln_append``. It is retained for purposes of
						compatibility with legacy code.

   CAVEATS     :  

   SEE ALSO    :  strln_append

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  strlnapp
						String List Functions:strlnapp
						STRFUNCS:String List Functions:strlnapp
						String Functions:See STRFUNCS

   PUBLISH XREF:  strlnapp

   PUBLISH NAME:	strlnapp

	ENTRY CLASS	:	String List Functions

EOH */
/* **************************************************************************	*/
#ifndef NARGS
int strlnapp(unsigned int *string_count, char ***string_list,
	const char *in_string, size_t string_length)
#else
int strlnapp(string_count, string_list, in_string, string_length)
unsigned int   *string_count;
char         ***string_list;
const char     *in_string;
size_t          string_length;
#endif /* #ifndef NARGS */
{
	return(strln_append(string_count, string_list, in_string, string_length));
}
/* *********************************************************************** */

