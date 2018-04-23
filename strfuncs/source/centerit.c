/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Centers a string.

	Revision History	:	1986-10-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2018.
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
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	centerit

	SYNOPSIS		:	text = centerit(in_text, width, out_text);

						char         *text;

						const char   *in_text;

						unsigned int  width;

						char         *out_text;

	DESCRIPTION	:	Creates a string consisting of the input string (the
						``in_text`` parameter) padded with spaces on the left and
						right so as center the input string within the width
						specified by the input parameter ``width``.  The resulting
						string is placed in the area pointed to by ``out_string``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_text`` is the string to be centered.

						(.) ``width`` is the number of characters in which
						centering is to be performed.

						(.) ``out_text`` is the area into which the centered string
						is to be placed.

	RETURNS		:	A pointer to the text resulting from operation of the
						function (that is, ``out_text``).  This may be a null
						string.

   NOTES       :  Note that the function is biased towards the right.  That
						is, if the number of spaces with which the string is to
						be padded is not even, the extra space is used on the left
						side of the string.

	CAVEATS		:	If the ``width`` parameter is less than the length of the
						``in_text`` parameter, no centering will be performed.
						Instead, the ``out_text`` parameter will consist of the
						text 	truncated to fit within the space specified by the
						``width`` parameter.

   SEE ALSO    :  center

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1986 - 2018 Michael L. Brock

   OUTPUT INDEX:  centerit
						String Justification Functions:centerit
						STRFUNCS:String Justification Functions:centerit
						String Functions:See STRFUNCS

   PUBLISH XREF:  centerit

   PUBLISH NAME:	centerit

	ENTRY CLASS	:	String Justification Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *centerit(const char *in_text, unsigned int width, char *out_text)
#else
char *centerit(in_text, width, out_text)
const char   *in_text;
unsigned int  width;
char         *out_text;
#endif /* #ifndef NARGS */
{
	int lpad, rpad;

	*out_text = '\0';							/* Set output string to NULL string	*/

	if (width) {								/* Is it OK to do the centering?		*/

													/* 'rpad' spaces on the right . . .	*/
		rpad = ((width - strlen(in_text)) > 0) ?
			(width - strlen(in_text)) / 2 : 0;

													/*    and 'lpad' spaces on the left	*/
		lpad = ((width - (strlen(in_text) + rpad)) > 0) ?
			width - (strlen(in_text) + rpad) : 0;

													/* Center it								*/
		if (lpad)
			sprintf(out_text, "%*s", lpad, " ");
		sprintf(out_text + lpad, "%.*s", ((int) width), in_text);
		if (rpad)
			sprintf(out_text + lpad + strlen(in_text) , "%*s", rpad, " ");

	/* The above kludge is necessary because the Lattice library function
		'sprintf' insists upon treating the string width parameter as the
		value one (1) when it is actually zero (0).  Under a compiler without
		this bug in the library, the below coding is sufficient:

		sprintf(out_text, "%*s%.*s%*s", lpad, " ", width, in_text, rpad, " ");
	*/
	}

	return(out_text);
}
/* *********************************************************************** */

