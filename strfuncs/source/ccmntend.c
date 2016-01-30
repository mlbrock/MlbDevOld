/*	***********************************************************************	*/
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Locates the end of a C/C++ language comment.

	Revision History	:	1993-06-25 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
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

   NAME        :	ccmntend

   SYNOPSIS    :	return_ptr = ccmntend(string_ptr, c_plus_plus_flag);

						const char *return_ptr;

						const char *string_ptr;

						int         c_plus_plus_flag;

   DESCRIPTION :	Locates the end of a C language comment. The single-line
						C++ language comment form (''//'') may also optionally be
						handled by this function.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``string_ptr`` points to the beginning of the comment
						for which the end is to be found. This function determines
						the beginning of the comment with the presence of the
						character ''/''. The end of comments is determined as
						follows:

						(..) If on invocation ``string_ptr`` points to the character
						''/'' and the next character is ''*'', then the first
						subsequent instance of the character sequence ''*''
						followed by ''/'' in the string will be used by this
						function as the termination of the comment.

						(..) If on invocation ``string_ptr`` points to the character
						''/'' and the next character is ''/'' and the
						``c_plus_plus_flag`` parameter is non-zero, then first
						subsequent instance of a line-feed (''\n'') in the string
						will be used by this function as the termination of the
						comment.

						(-) If on invocation neither of the above conditions are met
						this function will return a ''NULL'' pointer.

						(.) ``c_plus_plus_flag``, if non-zero, indicates that the
						C++ ''//'' comment style is to be supported 

   RETURNS     :	Returns from this function are as follow:

						(.) If on invocation ``string_ptr`` does not point to a
						valid comment character sequence, this function will return
						a ''NULL'' pointer.

						(.) If on invocation ``string_ptr`` points to a valid
						comment character sequence, this function will return a
						pointer to the character following the termination of the
						comment.

						(.) If the termination of the comment is not found within
						the string, this function will return a pointer to the ASCII
						''0'' at the end of the string.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :  Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	ccmntend
						Miscellaneous Functions:ccmntend
						STRFUNCS:Miscellaneous Functions:ccmntend
						String Functions:See STRFUNCS

   PUBLISH XREF:	ccmntend

   PUBLISH NAME:	ccmntend

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
const char *ccmntend(const char *string_ptr, int c_plus_plus_flag)
#else
const char *ccmntend(string_ptr, c_plus_plus_flag)
const char *string_ptr;
int         c_plus_plus_flag;
#endif /* #ifndef NARGS */
{
	if (*string_ptr != '/')
		string_ptr = NULL;
	else if (*(string_ptr + 1) == '*') {
		string_ptr += 2;
		while (*string_ptr) {
			if ((*string_ptr == '/') && c_plus_plus_flag &&
				(*(string_ptr + 1) == '/')) {
				while (*string_ptr && (*string_ptr != '\n'))
					string_ptr++;
				if (!(*string_ptr))
					goto EXIT_FUNCTION;		/* If no newline, it's OK for C++	*/
			}
			else if ((*string_ptr == '*') && (*(string_ptr + 1) == '/')) {
				string_ptr++;
				break;
			}
			string_ptr++;
		}
		if (!(*string_ptr))
			string_ptr = NULL;
	}
	else if ((*(string_ptr + 1) == '/') && c_plus_plus_flag) {
		while (*string_ptr && (*string_ptr != '\n'))
			string_ptr++;
	}
	else
		string_ptr = NULL;

EXIT_FUNCTION:

	return(string_ptr);
}
/* *********************************************************************** */

