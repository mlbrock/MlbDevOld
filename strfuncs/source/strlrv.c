/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reverses the order of an array of pointers to strings.

	Revision History	:	1991-09-29 --- Creation
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

   NAME        :  strl_reverse

   SYNOPSIS    :  void strl_reverse(string_count, string_list);

						unsigned int   string_count;

						char         **string_list;

   DESCRIPTION :  Reverses the order of an array of pointers to strings.

   PARAMETERS  :  Parameters to this function are as follow:

						``string_count`` is the number of elements in the array
						of pointers ``data_list``.

						``string_list`` is the array of pointers to strings to be
						reversed.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  STR_LIST_reverse

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  strl_reverse
						String List Functions:strl_reverse
						STRFUNCS:String List Functions:strl_reverse
						String Functions:See STRFUNCS

   PUBLISH XREF:  strl_reverse

   PUBLISH NAME:	strl_reverse

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void strl_reverse(unsigned int string_count, char **string_list)
#else
void strl_reverse(string_count, string_list)
unsigned int   string_count;
char         **string_list;
#endif /* #ifndef NARGS */
{
	STR_LIST_reverse(string_count, ((void **) string_list));
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

	fprintf(stderr, "Test of Function 'strl_reverse()'\n");
	fprintf(stderr, "---- -- -------- ----------------\n\n");

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
		strl_sort(test_count, test_list);
		fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
		for (count_1 = 0; count_1 < test_count; count_1++)
			fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
				test_list[count_1], test_list[count_1]);
		strl_reverse(test_count, test_list);
		fprintf(stderr, "[HEAD] ---> [%08p]\n", test_list);
		for (count_1 = 0; count_1 < test_count; count_1++)
			fprintf(stderr, "[%05u][%08p] ---> [%s]\n", count_1,
				test_list[count_1], test_list[count_1]);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

