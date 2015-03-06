/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sets all characters of a string to the specified
								character.

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

   NAME        :	STRFUNCS_strset

   SYNOPSIS    :	return_ptr = STRFUNCS_strset(string, char_value);

						char *return_ptr;

						char *string;

						int   char_value;

	DESCRIPTION :	Sets all characters of the string ``string`` to the
						character ``char_value``.

						This function stops when it encounters an ASCII NUL
						terminator byte.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``string`` is the string in which the characters are
						to be set.

						(.) ``char_value`` is the character to which characters in
						``string`` are to be set.

   RETURNS     :	Returns the pointer ``string``.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	nstrset
						STRFUNCS_strnset

	EXAMPLES    :	

	AUTHOR      :	Michael L. Brock

	COPYRIGHT   :	Copyright 1986 - 2015 Michael L. Brock

	OUTPUT INDEX:	STRFUNCS_strset
						String Set Functions:STRFUNCS_strset
						STRFUNCS:String Set Functions:STRFUNCS_strset
						String Functions:See STRFUNCS

	PUBLISH XREF:	STRFUNCS_strset

	PUBLISH NAME:	STRFUNCS_strset

	ENTRY CLASS	:	String Set Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *STRFUNCS_strset(char *string, int char_value)
#else
char *STRFUNCS_strset(string, char_value)
char *string;
int   char_value;
#endif /* #ifndef NARGS */
{
	register char *temp_ptr;

	for (temp_ptr = string; *temp_ptr; temp_ptr++)
		*temp_ptr = ((char) char_value);

	return(string);
}
/* *********************************************************************** */

