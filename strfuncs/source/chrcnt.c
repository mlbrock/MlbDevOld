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

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <string.h>

#include "strfunci.h"

/*	*********************************************************************** */

/*
	ADF NOTE:	This function was written using 'strchr()' to find the next
					character of interest in the belief that said function is
					likely to be implemented with high efficiency on most target
					platforms.
*/
/*	*********************************************************************** */
#ifndef NARGS
size_t chrcnt(const char *search_string, int target_char)
#else
size_t chrcnt(search_string, target_char)
const char *search_string;
int         target_char;
#endif /* #ifndef NARGS */
{
	unsigned int  count = 0;
	const char   *tmp_ptr;

	while ((tmp_ptr = strchr(search_string, target_char)) != NULL) {
		count++;
		search_string = tmp_ptr + 1;
	}

	return(count);
}
/* *********************************************************************** */

