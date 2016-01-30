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

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
int striindx(const char *look_for_string, const char *search_string)
#else
int striindx(look_for_string, search_string)
const char *look_for_string;
const char *search_string;
#endif /* #ifndef NARGS */
{
	register unsigned int count_1;
	register unsigned int look_for_length;
	register unsigned int search_length;

	if (*look_for_string && *search_string) {
		look_for_length = strlen(look_for_string);
		search_length   = strlen(search_string);
		for (count_1 = 0; (count_1 < search_length) &&
			((search_length + count_1) >= look_for_length); count_1++) {
			if ((strfmacs_toupper(*look_for_string) ==
				strfmacs_toupper(*(search_string + count_1))) &&
				(!STRFUNCS_strnicmp(look_for_string, search_string, look_for_length)))
				return(((int) count_1));
		}
	}

	return(-1);
}
/* *********************************************************************** */

