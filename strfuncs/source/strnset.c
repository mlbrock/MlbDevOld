/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sets the specified portion of a string to the
								character specified.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	STRFUNCS_strnset

   SYNOPSIS    :	return_ptr = STRFUNCS_strnset(string, char_value, count);

						char   *return_ptr;

						char   *string;

						int     char_value;

						size_t  count;

   DESCRIPTION :	Sets all characters of the string ``string`` to the
						character ``char_value``.

						If an ASCII NUL terminator byte has not been reached after
						``count`` characters have been processed, the function
						returns.

						This function will set fewer than ``count`` characters in
						``string`` to ``char_value`` in the case where an ASCII
						NUL terminator byte is encountered before ``count``
						characters have been processed. Compare the behavior of
						the related function ``nstrset``.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``string`` is the string in which the characters are
						to be set.

						(.) ``char_value`` is the character to which characters in
						``string`` are to be set.

						(.) ``count`` is the maximum number of characters in
						``string`` to be set to ``char_value``.

   RETURNS     :	Returns the pointer ``string``.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	nstrset
						STRFUNCS_strset

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	STRFUNCS_strnset
						String Set Functions:STRFUNCS_strnset
						STRFUNCS:String Set Functions:STRFUNCS_strnset
						String Functions:See STRFUNCS

	PUBLISH XREF:	STRFUNCS_strnset

	PUBLISH NAME:	STRFUNCS_strnset

	ENTRY CLASS	:	String Set Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *STRFUNCS_strnset(char *string, int char_value, size_t count)
#else
char *STRFUNCS_strnset(string, char_value, count)
char   *string;
int     char_value;
size_t  count;
#endif /* #ifndef NARGS */
{
	register char *temp_ptr;

	for (temp_ptr = string; (count-- > 0) && *temp_ptr; temp_ptr++)
		*temp_ptr = ((char) char_value);

	return(string);
}
/* *********************************************************************** */

