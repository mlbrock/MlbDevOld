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

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
#ifndef NARGS
void *memrimem(const void *search_area, size_t search_length,
	const void *target_area, size_t target_length)
#else
void *memrimem(search_area, search_length, target_area, target_length)
const void *search_area;
size_t      search_length;
const void *target_area;
size_t      target_length;
#endif /* #ifndef NARGS */
{
	unsigned char *search_ptr;

	if ((search_length > 0) && (target_length > 0) &&
		(search_length >= target_length)) {
		search_ptr = ((unsigned char *) search_area) +
			(search_length - target_length);
		do {
			if ((strfmacs_toupper(*search_ptr) ==
				strfmacs_toupper(*((unsigned char *) target_area))) &&
				((target_length == 1) ||
				(!STRFUNCS_memicmp(search_ptr + 1,
				((unsigned char *) target_area) + 1, target_length - 1))))
				return((void *) search_ptr);
		} while (search_ptr-- > ((unsigned char *) search_area));
	}

	return(NULL);
}
/* *********************************************************************** */

/*	*********************************************************************** */
/*	*********************************************************************** */
/*	*********************************************************************** */
#ifndef NARGS
void *STRFUNCS_SHIM_memrimem(size_t search_length, const void *search_area,
	size_t target_length, const void *target_area)
#else
void *STRFUNCS_SHIM_memrimem(search_length, search_area, target_length,
	target_area)
size_t      search_length;
const void *search_area;
size_t      target_length;
const void *target_area;
#endif /* #ifndef NARGS */
{
	return(memrimem(search_area, search_length, target_area, target_length));
}
/*	*********************************************************************** */

