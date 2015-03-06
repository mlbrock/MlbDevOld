/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes the characters specified from the left side
								of a string.

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

	NAME			:	noblank

	SYNOPSIS		:	char *noblank(text);

						char *text;

	DESCRIPTION	:	Removes all whitespace from the string to which the
						``text`` parameter points.

						Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``text`` is the string from which all whitespace is
						to be removed.

	RETURNS		:	A pointer to the string used as input.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  nospace
						oneblank

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2015 Michael L. Brock

   OUTPUT INDEX:  noblank
						String Justification Functions:noblank
						STRFUNCS:String Justification Functions:noblank
						String Functions:See STRFUNCS

   PUBLISH XREF:  noblank

   PUBLISH NAME:	noblank

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *noblank(char *text)
#else
char *noblank(text)
char *text;
#endif /* #ifndef NARGS */
{
	return(nospace(text));
}
/* *********************************************************************** */

