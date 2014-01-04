/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Right-justifies a string.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2014.
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

	NAME			: 	rjust

	SYNOPSIS		:	string_ptr = rjust(in_text);

						char *string_ptr;

						char *in_text;

	DESCRIPTION	:	Right-justifies (with spaces on the left) the string
						to which the ``in_text`` parameter points.

						Leading and trailing white-space is first removed from the
						string before the justification is attempted.

						Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string for which right-justification
						is to be performed.

	RETURNS		: 	A pointer to the string used as input. This is, ``in_text``
						is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  ljust
						strpadl
						trim

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2014 Michael L. Brock

   OUTPUT INDEX:  rjust
						String Justification Functions:rjust
						STRFUNCS:String Justification Functions:rjust
						String Functions:See STRFUNCS

   PUBLISH XREF:  rjust

   PUBLISH NAME:	rjust

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *rjust(char *in_text)
#else
char *rjust(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	unsigned int text_length;

	text_length = strlen(in_text);

	return(strpadl(trim(in_text), text_length));
}
/* *********************************************************************** */

