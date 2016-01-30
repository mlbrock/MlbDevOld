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

#include <memory.h>
#include <string.h>

#include "strfunci.h"

/*	*********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
#ifndef NARGS
void *memmem(const void *search_area, size_t search_length,
	const void *target_area, size_t target_length)
#else
void *memmem(search_area, search_length, target_area, target_length)
const void *search_area;
size_t      search_length;
const void *target_area;
size_t      target_length;
#endif /* #ifndef NARGS */
{
	unsigned char *search_ptr;

	if ((search_length > 0) && (target_length > 0)) {
		search_ptr = ((unsigned char *) search_area);
		while (search_length >= target_length) {
			if ((*search_ptr == *((unsigned char *) target_area)) &&
				((target_length == 1) ||
				(!memcmp(search_ptr, target_area, target_length))))
				return((void *) search_ptr);
			search_ptr++;
			search_length--;
		}
	}

	return(NULL);
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
#ifndef NARGS
void *STRFUNCS_SHIM_memmem(size_t search_length, const void *search_area,
	size_t target_length, const void *target_area)
#else
void *STRFUNCS_SHIM_memmem(search_length, search_area, target_length,
	target_area)
size_t      search_length;
const void *search_area;
size_t      target_length;
const void *target_area;
#endif /* #ifndef NARGS */
{
	return(memmem(search_area, search_length, target_area, target_length));
}
/*	*********************************************************************** */

