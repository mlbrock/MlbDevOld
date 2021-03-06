/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Makes an array of pointers to strings unique using
								case-insensitive comparisons.

	Revision History	:	1991-10-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2018.
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

   NAME        :  strli_uniq

   SYNOPSIS    :  strli_uniq(string_count, string_list);

						unsigned int   *string_count;

						char         ***string_list;

   DESCRIPTION :  This function makes unique an array of strings by use of
						a case-insensitive comparison routine.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to the number of elements in
						the array of pointers ``string_list``.

						(.) ``string_list`` points to the array of pointers to
						be made unique.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  The results of invoking this function with a ``string_list``
						not in sorted order are undefined.

   SEE ALSO    :  strl_uniq
						strln_uniq
						strlni_uniq
						STR_LIST_uniq
						STR_stricmp

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  strli_uniq
						String List Functions:strli_uniq
						STRFUNCS:String List Functions:strli_uniq
						String Functions:See STRFUNCS

   PUBLISH XREF:  strli_uniq

   PUBLISH NAME:	strli_uniq

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void strli_uniq(unsigned int *string_count, char ***string_list)
#else
void strli_uniq(string_count, string_list)
unsigned int   *string_count;
char         ***string_list;
#endif /* #ifndef NARGS */
{
#ifndef NARGS
	STR_LIST_uniq(NULL, string_count, ((void ***) string_list), 0,
		((int (*)(void *, const void *, const void *, size_t)) STR_stricmp));
#else
	STR_LIST_uniq(NULL, string_count, ((void ***) string_list), 0,
		STR_stricmp);
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
	char         **test_list   = NULL;
	unsigned int   count_1;
	char           buffer[512];

	fprintf(stderr, "Test of function 'strli_uniq()'\n");
	fprintf(stderr, "---- -- -------- --------------\n\n");

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
		strli_sort(test_count, test_list);
		strli_uniq(&test_count, &test_list);
		fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
		for (count_1 = 0; count_1 < test_count; count_1++)
			fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
				test_list[count_1], test_list[count_1]);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

