/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	Revision History:
		10/27/1986 --- Creation by Michael L. Brock

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
/* *********************************************************************** */
#ifndef NARGS
char *strmask(char *text, int mask_char)
#else
char *strmask(text, mask_char)
char *text;
int   mask_char;
#endif /* #ifndef NARGS */
{
	register char *tmp_ptr = text;

	while (*tmp_ptr) {
		if (*tmp_ptr == '\"') {
			while (*tmp_ptr) {
				tmp_ptr++;
				if (*tmp_ptr == '\"')
					break;
				else if ((*tmp_ptr == '\\') && (*(tmp_ptr + 1) == '\"'))
					*tmp_ptr++ = ((char) mask_char);
				*tmp_ptr = ((char) mask_char);
			}
			if (!(*tmp_ptr))
				break;
		}
		tmp_ptr++;
	}

	return(text);
}
/* *********************************************************************** */

