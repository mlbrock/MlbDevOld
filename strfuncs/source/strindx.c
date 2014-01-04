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

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <memory.h>
#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#ifndef NARGS
int strindx(const char *search_string, const char *look_for_string)
#else
int strindx(search_string, look_for_string)
const char *search_string;
const char *look_for_string;
#endif /* #ifndef NARGS */
{
	register char       *found_ptr;
	register const char *search_ptr = search_string;

	while ((found_ptr = strchr(search_ptr, *look_for_string)) != NULL) {
		if (!memcmp(found_ptr, look_for_string, strlen(look_for_string)))
			return(((int) (found_ptr - ((char *) search_string))));
		search_ptr = found_ptr + 1;
	}

	return(-1);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));

/* *********************************************************************** */
int main()
{
	printf("         01234567890123456789012345678901234567890123456789\n");
	printf("strindx(\"%s\", \"%s\") = %d\n",
		"This is a test of the function strindx()", "indx",
		strindx("This is a test of the function strindx()", "indx"));

	printf("         01234567890123456789012345678901234567890123456789\n");
	printf("strindx(\"%s\", \"%s\") = %d\n",
		"This is a another test of the function strindx()", "indx",
		strindx("This is a another test of the function strindx()", "indx"));

	printf("         01234567890123456789012345678901234567890123456789\n");
	printf("strindx(\"%s\", \"%s\") = %d\n",
		"This, too, is a test of the function strindx()", "indx",
		 strindx("This, too, is a test of the function strindx()", "indx"));

	return(0);
}
/* *********************************************************************** */

#endif /* TEST_MAIN */

