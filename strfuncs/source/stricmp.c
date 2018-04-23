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

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include "strfunci.h"

#ifdef __GNUC__
# include <strings.h>
#endif /* #ifdef __GNUC__ */

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
#ifndef NARGS
int STRFUNCS_stricmp(const char *string_1, const char *string_2)
#else
int STRFUNCS_stricmp(string_1, string_2)
const char *string_1;
const char *string_2;
#endif /* #ifndef NARGS */
{
#ifdef __GNUC__
	return(strcasecmp(string_1, string_2));
#else
	register int cmp_value;

	for (; (cmp_value = (strfmacs_toupper(*string_1) -
		strfmacs_toupper(*string_2))) == 0; string_1++, string_2++) {
		if (!(*string_1))
			return(strfmacs_toupper(*string_1) - strfmacs_toupper(*string_2));
	}

	return(cmp_value);
#endif /* #ifdef __GNUC__ */
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	printf("STRFUNCS_stricmp(\"This is a test\", \"This is a test\") = %d\n",
		STRFUNCS_stricmp("This is a test", "This is a test"));

	printf("STRFUNCS_stricmp(\"This is a test\", \"This is not a test\") = %d\n",
		STRFUNCS_stricmp("This is a test", "This is not a test"));

	printf("STRFUNCS_stricmp(\"This is a test\", \"This is a Test\") = %d\n",
		STRFUNCS_stricmp("This is a test", "This is a Test"));

	printf("STRFUNCS_stricmp(\"This is a test*\", \"This is a test\") = %d\n",
		STRFUNCS_stricmp("This is a test*", "This is a test"));

	printf("STRFUNCS_stricmp(\"This is a test\", \"This is a test*\") = %d\n",
		STRFUNCS_stricmp("This is a test", "This is a test*"));

	return(0);
}

#endif /* TEST_MAIN */

