/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Left-justifies a string.

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

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			: 	ljust

	SYNOPSIS		:	string_ptr = ljust(in_text);

						char *string_ptr;

						char *in_text;

	DESCRIPTION	:	Left-justifies (with spaces on the right) the string
						to which the ``in_text`` parameter points.

						Leading and trailing whitespace is first removed from the
						string before the justification is attempted.

						Whitespace is defined as any character for which the
						standard library macro ``isspace`` returns true.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string for which left-justification
						is to be performed.

	RETURNS		: 	A pointer to the string used as input. This is, ``in_text``
						is returned.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  rjust
						trim
						strpadr

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2016 Michael L. Brock

   OUTPUT INDEX:  ljust
						String Justification Functions:ljust
						STRFUNCS:String Justification Functions:ljust
						String Functions:See STRFUNCS

   PUBLISH XREF:  ljust

   PUBLISH NAME:	ljust

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *ljust(char *in_text)
#else
char *ljust(in_text)
char *in_text;
#endif /* #ifndef NARGS */
{
	unsigned int text_length;

	text_length = strlen(in_text);

	return(strpadr(trim(in_text), text_length));
}
/* *********************************************************************** */

