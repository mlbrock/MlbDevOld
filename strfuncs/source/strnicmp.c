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

#ifdef __GNUC__
# include <strings.h>
#endif /* #ifdef __GNUC__ */

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#ifndef NARGS
int STRFUNCS_strnicmp(const char *string_1, const char *string_2, size_t count)
#else
int STRFUNCS_strnicmp(string_1, string_2, count)
const char *string_1;
const char *string_2;
size_t      count;
#endif /* #ifndef NARGS */
{
#ifdef __GNUC__
	return(strncasecmp(string_1, string_2, count));
#else
	register int cmp_value;

	for (; (count && *string_1 && *string_2); count--, string_1++, string_2++){
		if ((cmp_value = (strfmacs_toupper(*string_1) -
			strfmacs_toupper(*string_2))) != 0)
		return(cmp_value);
	}

	if (count) {
		if (*string_1)
			return(1);
		if (*string_2)
			return(-1);
	}

	return(0);
#endif /* #ifdef __GNUC__ */
}
/* *********************************************************************** */

