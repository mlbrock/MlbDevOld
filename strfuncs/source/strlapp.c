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

		Copyright Michael L. Brock 1991 - 2018.
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

   NAME        :  strl_append

   SYNOPSIS    :  return_code = strl_append(string_count, string_list,
							in_string);

						int              return_code;

						unsigned int    *string_count;

						char          ***string_list;

						const char      *in_string;

   DESCRIPTION :  Appends an array element to an array of pointers to strings.

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

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  strln_append
						strl_add
						strl_copy
						strl_insert
						strl_remove
						meml_append
						mema_append

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  strl_append
						String List Functions:strl_append
						STRFUNCS:String List Functions:strl_append
						String Functions:See STRFUNCS

   PUBLISH XREF:  strl_append

   PUBLISH NAME:	strl_append

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int strl_append(unsigned int *string_count, char ***string_list,
	const char *in_string)
#else
int strl_append(string_count, string_list, in_string)
unsigned int    *string_count;
char          ***string_list;
const char      *in_string;
#endif /* #ifndef NARGS */
{
	return(memlapp(string_count, ((void ***) string_list),
		((const void *) in_string), strlen(in_string) + 1));
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strlapp

   SYNOPSIS    :  strl_app(string_count, string_list, in_string);

						int              return_code;

						unsigned int    *string_count;

						char          ***string_list;

						const char      *in_string;

   DESCRIPTION :  Appends an array element to an array of pointers to strings.

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

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  This function does no more than call the function
						``strl_append``. It is retained for purposes of
						compatibility with legacy code.

   CAVEATS     :  

   SEE ALSO    :  strl_append

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  strlapp
						String List Functions:strlapp
						STRFUNCS:String List Functions:strlapp
						String Functions:See STRFUNCS

   PUBLISH XREF:  strlapp

   PUBLISH NAME:	strlapp

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int strlapp(unsigned int *string_count, char ***string_list,
	const char *in_string)
#else
int strlapp(string_count, string_list, in_string)
unsigned int    *string_count;
char          ***string_list;
const char      *in_string;
#endif /* #ifndef NARGS */
{
	return(strl_append(string_count, string_list, in_string));
}
/* *********************************************************************** */

