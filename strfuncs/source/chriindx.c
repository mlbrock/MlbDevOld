/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	Revision History:
		10/27/1986 --- Creation by Michael L. Brock

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

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
int chriindx(int look_for_char, const char *search_string)
#else
int chriindx(look_for_char, search_string)
int         look_for_char;
const char *search_string;
#endif /* #ifndef NARGS */
{
	register int  counter = 0;
	register char look_for_upper;

	look_for_upper = strfmacs_toupper(look_for_char);

	while (*search_string) {
		if (strfmacs_toupper(*search_string) == look_for_upper)
			return(counter);
		counter++;
		search_string++;
	}

	return(-1);
}
/* *********************************************************************** */

