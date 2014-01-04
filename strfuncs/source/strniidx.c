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

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <string.h>

#include "strfunci.h"

/*	*********************************************************************** */

/*	*********************************************************************** */
#ifndef NARGS
int   strniidx(const char *search_text, const char *target_text, int count)
#else
int   strniidx(search_text, target_text, count)
const char *search_text;
const char *target_text;
int         count;
#endif /* #ifndef NARGS */
{
	int         text_index = -1;
	const char *temp_ptr   = search_text;
	int         search_text_length;
	int         target_text_length;

	if ((count > 0) && ((search_text_length = strlen(search_text)) != 0) &&
		((target_text_length = strlen(target_text)) != 0)) {
		target_text_length = (target_text_length > count) ?
			count : target_text_length;
		while (search_text_length >= target_text_length) {
			if (strfmacs_toupper(*search_text) ==
				strfmacs_toupper(*target_text)) {
				if (!strnicmp(search_text, target_text, ((unsigned int) count))) {
					text_index = ((int) (search_text - temp_ptr));
					break;
				}
			}
			search_text++;
			search_text_length--;
		}
	}

	return(text_index);
}
/*	*********************************************************************** */

