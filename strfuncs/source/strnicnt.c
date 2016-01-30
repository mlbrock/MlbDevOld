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

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <string.h>

#include "strfunci.h"

/*	*********************************************************************** */

/*	*********************************************************************** */
#ifndef NARGS
size_t strnicnt(const char *search_string, const char *target_string,
	size_t search_length)
#else
size_t strnicnt(search_string, target_string, search_length)
const char *search_string;
const char *target_string;
size_t      search_length;
#endif /* #ifndef NARGS */
{
	search_length = (strlen(search_string) < search_length) ?
		strlen(search_string) : search_length;

	return(memicnt(search_length, search_string, strlen(target_string),
		target_string));
}
/* *********************************************************************** */

