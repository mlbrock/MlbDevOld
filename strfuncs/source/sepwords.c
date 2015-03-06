/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Separates a string by converting multiple
								non-alphabetic characters to a line-feed character.

	Revision History	:	1992-06-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
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

   NAME        :  sepwords

   SYNOPSIS    :  return_ptr = sepwords(text);

						char *return_ptr;

						char *text;

   DESCRIPTION :  Separates alphanumeric sequences in a string with the
						ASCII line-feed character.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``text`` is the string to be operated upon by this
						function.

   RETURNS     :  Returns a pointer to ``text``.

   NOTES       :  Leading and trailing non-alphanumeric characters are
						removed by this function.

   CAVEATS     :  

   SEE ALSO    :  sepwordc
						sepwordc_keep
						sepwordl
						sepwordx
						sepwordx_keep

	EXAMPLES    :

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	sepwords
						String Splitting Functions:sepwords
						STRFUNCS:String Splitting Functions:sepwords
						String Functions:See STRFUNCS

	PUBLISH XREF:	sepwords

	PUBLISH NAME:	sepwords

	ENTRY CLASS	:	String Splitting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
char *sepwords(char *text)
#else
char *sepwords(text)
char *text;
#endif /* #ifndef NARGS */
{
	register char *temp_ptr = text;

	while (*temp_ptr) {
		if (*temp_ptr && (!isalnum(*temp_ptr)))
			*temp_ptr = ' ';
		temp_ptr++;
	}
	trim(oneblank(nocontrl(text)));

	temp_ptr = text;
	while (*temp_ptr) {
		if (*temp_ptr == ' ')
			*temp_ptr = '\n';
		temp_ptr++;
	}

	return(text);
}
/* *********************************************************************** */

