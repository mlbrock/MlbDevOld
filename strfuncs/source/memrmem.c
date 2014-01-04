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

#include <memory.h>
#include <string.h>

#include "strfunci.h"

/*	*********************************************************************** */

/*	*********************************************************************** */
#ifndef NARGS
void *memrmem(size_t search_length, const void *search_area,
	size_t target_length, const void *target_area)
#else
void *memrmem(search_length, search_area, target_length, target_area)
size_t      search_length;
const void *search_area;
size_t      target_length;
const void *target_area;
#endif /* #ifndef NARGS */
{
	unsigned char *search_ptr;

	if ((search_length > 0) && (target_length > 0) &&
		(search_length >= target_length)) {
		search_ptr = ((unsigned char *) search_area) +
			(search_length - target_length);
		do {
			if ((*search_ptr == *((unsigned char *) target_area)) &&
				((target_length == 1) ||
				(!memcmp(search_ptr + 1, ((unsigned char *) target_area) + 1,
				target_length - 1))))
				return((void *) search_ptr);
		} while (search_ptr-- > ((unsigned char *) search_area));
	}

	return(NULL);
}
/* *********************************************************************** */

