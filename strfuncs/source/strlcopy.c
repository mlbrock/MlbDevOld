/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Copies an array of pointers to strings.

	Revision History	:	1991-09-14 --- Creation
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

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strl_copy

   SYNOPSIS    :  return_code = strl_copy(in_string_count, in_string_list,
							out_string_count, out_string_list);

						int             return_code;

						unsigned int    in_string_count;

						char          **in_string_list;

						unsigned int   *out_string_count;

						char         ***out_string_list;

   DESCRIPTION :  Copies the strings in the list ``in_string_list`` to the
						list ``out_string_list``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_string_count`` is the number of strings in the
						source list ``in_string_list``.

						(.) ``in_string_list`` is the list of strings to be copied.

						(.) ``out_string_count`` points to an integer which will
						contain the number of records in the destination list
						``out_string_list`` if this function is successful.

						(.) ``out_string_list`` points to the destination list to
						which strings from ``in_string_list`` are to be copied.
						Memory will be allocated for this list by the function.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  strl_add

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  strl_copy
						String List Functions:strl_copy
						STRFUNCS:String List Functions:strl_copy
						String Functions:See STRFUNCS

   PUBLISH XREF:  strl_copy

   PUBLISH NAME:	strl_copy

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int strl_copy(unsigned int in_string_count, char **in_string_list,
	unsigned int *out_string_count, char ***out_string_list)
#else
int strl_copy(in_string_count, in_string_list, out_string_count,
	out_string_list)
unsigned int    in_string_count;
char          **in_string_list;
unsigned int   *out_string_count;
char         ***out_string_list;
#endif /* #ifndef NARGS */
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int count_1;

	*out_string_count = 0;
	*out_string_list  = NULL;

	for (count_1 = 0; count_1 < in_string_count; count_1++) {
		if ((return_code = memlapp(out_string_count,
			((void ***) out_string_list), ((void *) in_string_list[count_1]),
			strlen(in_string_list[count_1]) + 1)) != STRFUNCS_SUCCESS) {
			meml_remove_all(out_string_count, ((void ***) out_string_list));
			break;
		}
	}

	return(return_code);
}
/*	*********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

COMPAT_FN_DECL(int main, (void));

int main()
{
	int            return_code      = 0;
	unsigned int   difference_count = 0;
	unsigned int   test_count       = 0;
	char         **test_list        = NULL;
	unsigned int   new_count        = 0;
	char         **new_list         = NULL;
	unsigned int   count_1;
	char           buffer[512];

	fprintf(stderr, "Test of function 'strl_copy()'\n");
	fprintf(stderr, "---- -- -------- -------------\n\n");

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
		if ((return_code = strl_copy(test_count, test_list, &new_count,
			&new_list)) != STRFUNCS_SUCCESS)
			fprintf(stderr, "ERROR ON ATTEMPT TO COPY STRING LIST\n\n");
		else if (test_count != new_count) {
			fprintf(stderr,
				"Differences found in list counts (%u versus %u)\n",
				test_count, new_count);
			return_code = -1;
		}
		else {
			for (count_1 = 0; count_1 < test_count; count_1++) {
				if (strcmp(test_list[count_1], new_list[count_1])) {
					if (!difference_count++) {
						fprintf(stderr, "Differences found in lists\n");
						return_code = -1;
					}
					fprintf(stderr, "DIFFERENCE [%05u]: [Index %05u] %s\n",
						difference_count, count_1, test_list[count_1]);
					fprintf(stderr, "                : [Index %05u] %s\n",
						count_1, new_list[count_1]);
				}
			}
			fprintf(stderr, "\nTotal differences: %u\n\n", difference_count);
		}
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

