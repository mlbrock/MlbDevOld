/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes all white-space from a string.

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

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			: 	nospace

	SYNOPSIS		:	char *nospace(text);

						char *text;

	DESCRIPTION	:	Removes all whitespace from the string to which the
						``text`` parameter points.

						Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``text`` is the string from which all whitespace
						is to be removed.

	RETURNS		:	A pointer to the string used as input.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  noblank
						oneblank

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  nospace
						String Justification Functions:nospace
						STRFUNCS:String Justification Functions:nospace
						String Functions:See STRFUNCS

   PUBLISH XREF:  nospace

   PUBLISH NAME:	nospace

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *nospace(char *text)
#else
char *nospace(text)
char *text;
#endif /* #ifndef NARGS */
{
	register char *tmp_ptr_1 = text;
	register char *tmp_ptr_2 = text;
	register int   length;

	length = strlen(text);

	while (*tmp_ptr_1) {
		while (isspace(*tmp_ptr_1)) {
			tmp_ptr_1++;
			length--;
		}
		if (!(*tmp_ptr_1))
			break;
		*text++ = *tmp_ptr_1++;
	}

	tmp_ptr_2[length] = '\0';

	return(tmp_ptr_2);
}
/* *********************************************************************** */

