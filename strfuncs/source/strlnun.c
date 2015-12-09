/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Makes an array of pointers to strings unique.

	Revision History	:	1991-10-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2015.
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

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strln_uniq

   SYNOPSIS    :  strln_uniq(string_count, string_list, string_length);

						unsigned int   *string_count;

						char         ***string_list;

						size_t          string_length;

   DESCRIPTION :  This function makes unique an array of strings.

						No more than ``string_length`` characters are considered
						in determining the equivalence of strings in the array.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to the number of elements in
						the array of pointers ``string_list``.

						(.) ``string_list`` points to the array of pointers to be
						made unique.

						(.) ``string_length`` is the maximum number of characters
						to be compared in determining equivalence of two strings.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  The results of invoking this function with a
						``string_list`` not in sorted order are undefined.

   SEE ALSO    :  strl_uniq
						strli_uniq
						strlni_uniq
						STR_LIST_uniq
						STR_strncmp

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  strln_uniq
						String List Functions:strln_uniq
						STRFUNCS:String List Functions:strln_uniq
						String Functions:See STRFUNCS

   PUBLISH XREF:  strln_uniq

   PUBLISH NAME:	strln_uniq

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void strln_uniq(unsigned int *string_count, char ***string_list,
	size_t string_length)
#else
void strln_uniq(string_count, string_list, string_length)
unsigned int   *string_count;
char         ***string_list;
size_t          string_length;
#endif /* #ifndef NARGS */
{
#ifndef NARGS
	STR_LIST_uniq(NULL, string_count, ((void ***) string_list), string_length,
		((int (*)(void *, const void *, const void *, size_t)) STR_strncmp));
#else
	STR_LIST_uniq(NULL, string_count, ((void ***) string_list), string_length,
		STR_strncmp);
#endif /* #ifndef NARGS */
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int            return_code = 0;
	unsigned int   test_count  = 0;
	size_t         max_length  = 5;
	char         **test_list   = NULL;
	unsigned int   count_1;
	char           buffer[512];

	fprintf(stderr, "Test of function 'strln_uniq()'\n");
	fprintf(stderr, "---- -- -------- --------------\n\n");

	fprintf(stderr, "MAXIMUM COMPARISON LENGTH = %u\n", max_length);

	while ((!feof(stdin)) && (!ferror(stdin))) {
		*buffer = '\0';
		while (!(*buffer)) {
			fgets(buffer, sizeof(buffer) - 1, stdin);
			while (strlen(buffer) && (buffer[strlen(buffer) - 1] == '\n'))
				buffer[strlen(buffer) - 1] = '\0';
		}
		if (!STRFUNCS_stricmp(buffer, "LIST")) {
			fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
			for (count_1 = 0; count_1 < test_count; count_1++)
				fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
					test_list[count_1], test_list[count_1]);
		}
		else if ((!STRFUNCS_stricmp(buffer, "END")) ||
			(!STRFUNCS_stricmp(buffer, "QUIT")) ||
			(!STRFUNCS_stricmp(buffer, "EXIT")))
			break;
		else if ((return_code = strlapp(&test_count, &test_list, buffer)) ==
			STRFUNCS_FAILURE) {
			fprintf(stderr, "\nERROR ON ATTEMPT TO APPEND STRING\n\n");
			break;
		}
		return_code = 0;
	}

	if (!return_code) {
		strln_sort(test_count, test_list, max_length);
		strln_uniq(&test_count, &test_list, max_length);
		fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
		for (count_1 = 0; count_1 < test_count; count_1++)
			fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
				test_list[count_1], test_list[count_1]);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

