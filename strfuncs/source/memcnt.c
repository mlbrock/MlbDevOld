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

/*	*********************************************************************** */
/*	*********************************************************************** */
/* 	Necessary include files . . .														*/
/*	*********************************************************************** */

#include <memory.h>
#include <string.h>

#include "strfunci.h"

/*	*********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
#ifndef NARGS
size_t memcnt(size_t search_length, const void *search_area,
	size_t target_length, const void *target_area)
#else
size_t memcnt(search_length, search_area, target_length, target_area)
size_t      search_length;
const void *search_area;
size_t      target_length;
const void *target_area;
#endif /* #ifndef NARGS */
{
	register size_t count         = 0;
	register size_t search_offset = 0;

	if ((search_length > 0) && (target_length > 0)) {
		while (search_length >= target_length) {
			if (((char *) search_area)[search_offset] ==
				*((char *) target_area)) {
				if (!memcmp(((char *) search_area) + search_offset, target_area,
					target_length)) {
					count++;
					search_offset += target_length;
					search_length -= target_length;
					continue;
				}
			}
			search_offset++;
			search_length--;
		}
	}

	return(count);
}
/* *********************************************************************** */

