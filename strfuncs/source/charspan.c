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

#include <limits.h>

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
int  charspan(const char *text, int *low, int *high)
#else
int  charspan(text, low, high)
const char *text;
int        *low;
int        *high;
#endif /* #ifndef NARGS */
{
	if (!(*text)) {
		*low  = 0;
		*high = 0;
	}
	else {
		*low  = UCHAR_MAX;
		*high = 0;
		do {
			*low  = (*((unsigned char *) text) < ((unsigned char) *low))  ?
				((int) *((unsigned char *) text)) : *low;
			*high = (*((unsigned char *) text) > ((unsigned char) *high)) ?
				((int) *((unsigned char *) text)) : *high;
			text++;
		} while (*text);
	}

	return(*high - *low);
}
/* *********************************************************************** */

