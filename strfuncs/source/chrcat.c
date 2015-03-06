/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	Revision History:
		10/27/1986 --- Creation by Michael L. Brock

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

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
char *chrcat(char *to_ptr, int in_char)
#else
char *chrcat(to_ptr, in_char)
char *to_ptr;
int   in_char;
#endif /* #ifndef NARGS */
{
	char *tmp_ptr;

	/* ***************************************************************** */
	/* 	Appends a char followed by a NULL at end of a string				*/
	/* ***************************************************************** */
	*(tmp_ptr = (to_ptr + strlen(to_ptr))) = ((char) in_char);
	*++tmp_ptr = '\0';

	return(to_ptr);
}
/* *********************************************************************** */

