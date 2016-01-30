/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes non-printable characters from a string.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2016.
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

   NAME        :	nocontrl

   SYNOPSIS    :	return_ptr = nocontrl(text);

						char *return_ptr;

						char *text;

   DESCRIPTION :	Removes non-printable characters from a string.

   PARAMETERS  :	Parameters to this function are as follow:

   					(.) ``text`` is the string on which the function is to
						operate.

	RETURNS		:	A pointer to the string used as input.

   NOTES       :  Control characters are defined as any character for which
						the standard library macro ``isprint`` returns zero.

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1986 - 2016 Michael L. Brock

   OUTPUT INDEX:	nocontrl
						Miscellaneous Functions:nocontrl
						STRFUNCS:Miscellaneous Functions:nocontrl
						String Functions:See STRFUNCS

   PUBLISH XREF:	nocontrl

   PUBLISH NAME:	nocontrl

	ENTRY CLASS	:	Miscellaneous Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
char *nocontrl(char *text)
#else
char *nocontrl(text)
char *text;
#endif /* #ifndef NARGS */
{
	register char *temp_ptr_1 = text;
	register char *temp_ptr_2 = text;

	while (*temp_ptr_1) {
		if (isprint(*temp_ptr_1))
			*temp_ptr_2++ = *temp_ptr_1++;
		else
			temp_ptr_1++;
	}

	*temp_ptr_2 = '\0';

	return(text);
}
/* *********************************************************************** */

