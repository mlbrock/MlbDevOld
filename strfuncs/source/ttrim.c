/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes tabs and spaces from the left and right sides
								of a string.

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

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	ttrim

	SYNOPSIS		:	char *ttrim(text);

						char *text;

	DESCRIPTION	:	Removes all leading and trailing blanks from the
						string to which the ``text`` parameter points.

						A blank is defined as either a space (ASCII 32) or
						a tab (ASCII 9).

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``text`` is the string to be trimmed.

	RETURNS		: 	A pointer to the string used as input.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  trim
						lttrim
						rttrim

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2016 Michael L. Brock

   OUTPUT INDEX:  ttrim
						String Justification Functions:ttrim
						STRFUNCS:String Justification Functions:ttrim
						String Functions:See STRFUNCS

   PUBLISH XREF:  ttrim

   PUBLISH NAME:	ttrim

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ttrim(char *text)
#else
char *ttrim(text)
char *text;
#endif /* #ifndef NARGS */
{
	return(lttrim(rttrim(text)));
}
/* *********************************************************************** */

