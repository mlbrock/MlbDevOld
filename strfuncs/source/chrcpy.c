/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	Revision History:
		10/27/1986 --- Creation by Michael L. Brock

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

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
char *chrcpy(char *to_ptr, int in_char)
#else
char *chrcpy(to_ptr, in_char)
char *to_ptr;
int   in_char;
#endif /* #ifndef NARGS */
{
	/* ***************************************************************** */
	/* 	Makes a string by putting a char followed by a NULL in a string*/
	/* ***************************************************************** */

	*to_ptr       = ((char) in_char);	/* Put the char in the string		*/

	*(to_ptr + 1) = '\0';					/* Now, add the NULL byte			*/

	return(to_ptr);
}
/* *********************************************************************** */

