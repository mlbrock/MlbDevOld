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
int charicnt(int look_for_char, const char *search_string)
#else
int charicnt(look_for_char, search_string)
int         look_for_char;
const char *search_string;
#endif /* #ifndef NARGS */
{
	int  counter = 0;
	char look_for_upper;

	look_for_upper = strfmacs_toupper(look_for_char);

	while (*search_string) {
		counter += (strfmacs_toupper(*search_string) == look_for_upper) ? 1 : 0;
		search_string++;
	}

	return(counter);
}
/* *********************************************************************** */

