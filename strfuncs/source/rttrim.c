/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes tabs and spaces from the right side of a
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

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	rttrim

	SYNOPSIS		:	char *rttrim(text);

						char *text;

	DESCRIPTION	:	Removes all trailing blanks from the string to which
						the ``text`` parameter points.  That is, the string is
						trimmed from the right. 

						A blank is defined as either a space (ASCII 32) or
						a tab (ASCII 9).

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``text`` is the string from which spaces and tabs
						on the right are to be removed.

	RETURNS		:	A pointer to the string used as input.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  rtrim
						lttrim
						ttrim

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  rttrim
						String Justification Functions:rttrim
						STRFUNCS:String Justification Functions:rttrim
						String Functions:See STRFUNCS

   PUBLISH XREF:  rttrim

   PUBLISH NAME:	rttrim

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *rttrim(char *text)
#else
char *rttrim(text)
char *text;
#endif /* #ifndef NARGS */
{
	unsigned int  count;
	char         *temp_ptr;

	count = strlen(text);

	if (count) {
		temp_ptr = text + count - 1;
		while (count-- && ((*temp_ptr == ' ') || (*temp_ptr == '\t')))
			*temp_ptr-- = '\0';
	}

	return(text);
}
/* *********************************************************************** */

