/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Locates the end of a C/C++ language comment.

	Revision History	:	1993-06-22 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <stdio.h>

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	qstrend

   SYNOPSIS    :	return_ptr = qstrend(string_ptr);

						char *return_ptr;

						char *string_ptr;

   DESCRIPTION :	Locates the end of a C/C++ language string quoted with the
						double-quotes (''"'') character.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``string_ptr`` points to the beginning of the quoted
						string for which the end is to be found.

   RETURNS     :	Returns from this function are as follow:

						(.) If on invocation ``string_ptr`` points to the
						double-quotes character ''"'', and a terminating
						double-quotes character is found subsequently in the string,
						this function will return a pointer to the terminating
						double-quotes character.

						(.) If on invocation ``string_ptr`` does not point to the
						double-quotes character ''"'', or if a terminating
						double-quotes character is not found subsequently in the
						string, this function will return a ''NULL'' pointer.

   NOTES       :	The occurrence of the double-quotes character with the
						quoted string (as in the character sequence ''\"'') is
						handled correctly by this function.

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	qstrend
						Miscellaneous Functions:qstrend
						STRFUNCS:Miscellaneous Functions:qstrend
						String Functions:See STRFUNCS

   PUBLISH XREF:	qstrend

   PUBLISH NAME:	qstrend

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *qstrend(char *string_ptr)
#else
char *qstrend(string_ptr)
char *string_ptr;
#endif /* #ifndef NARGS */
{
	if (*string_ptr != '\"')
		string_ptr = NULL;
	else {
		string_ptr++;
		while (*string_ptr) {
			if (*string_ptr == '\"')
				break;
			else if (*string_ptr == '\\') {
				if ((*(string_ptr + 1) == '\"') || (*(string_ptr + 1) == '\\'))
					string_ptr++;
			}
			string_ptr++;
		}
		if (!(*string_ptr))
			string_ptr = NULL;
	}

	return(string_ptr);
}
/* *********************************************************************** */

