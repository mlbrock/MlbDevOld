/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes tabs and spaces from the left side of a
								string.

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

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			: 	lttrim

	SYNOPSIS		:	char *lttrim(text);

						char *text;

	DESCRIPTION	:	Removes all leading blanks from the string to which
						the ``text`` parameter points.  That is, the string is
						trimmed from the left.

						A blank is defined as either a space (ASCII 32) or
						a tab (ASCII 9).

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``text`` is the string from which spaces and tabs on
						the left are to be removed.

	RETURNS		:	A pointer to the string used as input.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  ltrim
						rttrim
						ttrim

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  lttrim
						String Justification Functions:lttrim
						STRFUNCS:String Justification Functions:lttrim
						String Functions:See STRFUNCS

   PUBLISH XREF:  lttrim

   PUBLISH NAME:	lttrim

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *lttrim(char *text)
#else
char *lttrim(text)
char *text;
#endif /* #ifndef NARGS */
{
	char *temp_ptr_1 = text;
	char *temp_ptr_2 = text;

	while (*temp_ptr_1) {
		if ((*temp_ptr_1 != ' ') && (*temp_ptr_1 != '\t')) {
			while (*temp_ptr_1)
				*text++ = *temp_ptr_1++;
			*text = '\0';
			return(temp_ptr_2);
		}
		temp_ptr_1++;
	}

	return(temp_ptr_2);
}
/* *********************************************************************** */

