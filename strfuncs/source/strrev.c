/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reverses an ASCII-NUL terminated string.

	Revision History	:	1986-07-10 --- Creation
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
#ifndef NARGS
char *STR_strrev(char *in_string)
#else
char *STR_strrev(in_string)
char *in_string;
#endif /* #ifndef NARGS */
{
	char *old_in_string = in_string;
	char *current_ptr   = in_string;
	char  this_char;

	while (*in_string++)
		;

	in_string -= 2;

	while (current_ptr < in_string) {
		this_char      = *current_ptr;
		*current_ptr++ = *in_string;
		*in_string--   = this_char;
	}

	return(old_in_string);
}
/*	***********************************************************************	*/


