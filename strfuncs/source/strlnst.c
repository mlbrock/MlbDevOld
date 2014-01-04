/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sorts an array of pointers to strings.

	Revision History	:	1991-09-20 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
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

   NAME        :  strln_sort

   SYNOPSIS    :  strln_sort(string_count, string_list, string_length);

						unsigned int   string_count;

						char         **string_list;

						size_t         string_length;

   DESCRIPTION :  This function performs a sort of an array of pointers to
						strings using the ACM 271 algorithm popularly known as
						Quicksort.

						Only the first ``string_length`` characters of the strings
						in ``string_list`` are used in the sort comparisons.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` is the number of elements in the array
						of pointers ``string_list``.

						(.) ``string_list`` is the array of pointers to be sorted.

						(.) ``string_length`` is the maximum number of characters
						to be compared by the Quicksort routine.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  strl_sort
						strli_sort
						strlni_sort
						STR_LIST_qsort
						STR_strncmp

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  strln_sort
						String List Functions:strln_sort
						STRFUNCS:String List Functions:strln_sort
						String Functions:See STRFUNCS

   PUBLISH XREF:  strln_sort

   PUBLISH NAME:	strln_sort

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void strln_sort(unsigned int string_count, char **string_list,
	size_t string_length)
#else
void strln_sort(string_count, string_list, string_length)
unsigned int   string_count;
char         **string_list;
size_t         string_length;
#endif /* #ifndef NARGS */
{
#ifndef NARGS
	STR_LIST_qsort(NULL, string_count, ((void **) string_list), string_length,
		((int (*)(void *, const void *, const void *, size_t)) STR_strncmp));
#else
	STR_LIST_qsort(NULL, string_count, ((void **) string_list), string_length,
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

	fprintf(stderr, "Test of function 'strln_sort()'\n");
	fprintf(stderr, "---- -- -------- --------------\n\n");

	fprintf(stderr, "MAXIMUM COMPARISON LENGTH = %u\n", max_length);

	while ((!feof(stdin)) && (!ferror(stdin))) {
		*buffer = '\0';
		while (!(*buffer)) {
			fgets(buffer, sizeof(buffer) - 1, stdin);
			while (strlen(buffer) && (buffer[strlen(buffer) - 1] == '\n'))
				buffer[strlen(buffer) - 1] = '\0';
		}
		if (!stricmp(buffer, "LIST")) {
			fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
			for (count_1 = 0; count_1 < test_count; count_1++)
				fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
					test_list[count_1], test_list[count_1]);
		}
		else if ((!stricmp(buffer, "END")) || (!stricmp(buffer, "QUIT")) ||
			(!stricmp(buffer, "EXIT")))
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
		fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
		for (count_1 = 0; count_1 < test_count; count_1++)
			fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
				test_list[count_1], test_list[count_1]);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

