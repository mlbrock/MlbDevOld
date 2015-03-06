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

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#ifndef NARGS
int STRFUNCS_memicmp(const void *area_1, const void *area_2, size_t count)
#else
int STRFUNCS_memicmp(area_1, area_2, count)
const void *area_1;
const void *area_2;
size_t      count;
#endif /* #ifndef NARGS */
{
	size_t count_1;
	int    cmp_value = 0;

	for (count_1 = 0; count_1 < count; count_1++) {
		if ((cmp_value = (strfmacs_toupper(((char *) area_1)[count_1]) -
			strfmacs_toupper(((char *) area_2)[count_1]))) != 0)
			break;
	}

	return(cmp_value);
}
/* *********************************************************************** */

