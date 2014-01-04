/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a binary search on an array of pointers to
								strings to insert a string.

	Revision History	:	1991-10-10 --- Creation
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

   NAME        :  strln_search

   SYNOPSIS    :  return_code = strln_search(string_count, string_list,
							key_string, string_length, found_index);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

						const char     *key_string;

						size_t          string_length;

						unsigned int   *found_index;

   DESCRIPTION :  Performs a binary search in the array ``string_list`` for
						the element ``key_string`` using a comparison function
						equivalent to the C standard library function ``strncmp``.

						If ``key_string`` is found, its index in ``string_list``
						is placed into the unsigned int to which ``found_index``
						points.

						If ``key_string`` is not found, this function will attempt
						to add it to the array ``string_list`` in sorted order.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to the number of elements in
						the array of pointers ``string_list``.

						(.) ``string_list`` points to the array of pointers in
						which the search for ``data_key`` will be performed.

						(.) ``key_string`` points to the data for which the search
						is to occur.

						(.) ``string_length`` is the maximum number of characters
						to be compared by the binary search routine.

						(.) ``found_index`` points to an unsigned integer into
						which the index of ``key_string`` in ``string_list`` will
						be placed, if found.

						(-) Note, however, that ``found_index`` will not be
						de-referenced if it is ''NULL''.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_FAILURE'' if an error occurs.

						(.) ''STRFUNCS_ITEM_FOUND'' if ``key_string`` is found in
						the array ``string_list``. In this case, the unsigned int
						to which the ``found_index`` parameter points will be set
						to the index of that element in the array.

						(.) ''STRFUNCS_ITEM_NOT_FOUND'' if ``key_string`` is not
						found in the array ``string_list``. In this case,
						``key_string`` will be inserted into ``string_list`` in
						sorted order and the unsigned int to which the
						``found_index`` parameter points will be set to the
						index of the inserted element of the array.

   NOTES       :  

   CAVEATS     :  The results of invoking this function with a
						``string_list`` not in sorted order are undefined.

						If there are multiple elements in ``string_list`` which
						compare equal, the first will be returned by this function.

   SEE ALSO    :  strl_search
						strli_search
						strlni_search

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  strln_search
						String List Functions:strln_search
						STRFUNCS:String List Functions:strln_search
						String Functions:See STRFUNCS

   PUBLISH XREF:  strln_search

   PUBLISH NAME:	strln_search

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int strln_search(unsigned int *string_count, char ***string_list,
	const char *key_string, size_t string_length, unsigned int *found_index)
#else
int strln_search(string_count, string_list, key_string, string_length,
	found_index)
unsigned int   *string_count;
char         ***string_list;
const char     *key_string;
size_t          string_length;
unsigned int   *found_index;
#endif /* #ifndef NARGS */
{
#ifndef NARGS
	return(STR_LIST_search(string_count, ((void ***) string_list),
		((void *) key_string), string_length, found_index,
		((int (*)(void *, const void *, const void *, size_t)) STR_strncmp),
		((int (*)(unsigned int *, void ***, const void *, size_t,
		unsigned int)) strln_insert)));
#else
	return(STR_LIST_search(string_count, ((void ***) string_list),
		((void *) key_string), string_length, found_index, STR_strncmp,
		strln_insert));
#endif /* #ifndef NARGS */
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>
#include <string.h>

COMPAT_FN_DECL(int main, (void));

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
int main()
{
	int            return_code = 0;
	unsigned int   line_count  = 0;
	unsigned int   test_count  = 0;
	unsigned int   saved_count = 0;
	size_t         max_length  = 5;
	char         **test_list   = NULL;
	char         **saved_list  = NULL;
	unsigned int   count_1;
	unsigned int   found_index;
	char           buffer[512];

	fprintf(stderr, "Test of function 'strln_search()'\n");
	fprintf(stderr, "---- -- -------- ----------------\n\n");

	fprintf(stderr, "MAXIMUM COMPARISON LENGTH = %u\n", max_length);

	while ((!feof(stdin)) && (!ferror(stdin))) {
		*buffer = '\0';
		while (!(*buffer)) {
			fgets(buffer, sizeof(buffer) - 1, stdin);
			while (strlen(buffer) && (buffer[strlen(buffer) - 1] == '\n'))
				buffer[strlen(buffer) - 1] = '\0';
			line_count++;
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
		else if ((return_code = strln_search(&test_count, &test_list,
			buffer, max_length, &found_index)) == STRFUNCS_FAILURE) {
			fprintf(stderr, "\nERROR ON ATTEMPT TO ADD STRING\n\n");
			break;
		}
		else if (return_code == STRFUNCS_ITEM_FOUND)
			fprintf(stderr, "STRING ALREADY IN LIST (INDEX = %u)\n",
				found_index);
		else if ((return_code = strlapp(&saved_count, &saved_list,
			buffer)) == STRFUNCS_FAILURE) {
			fprintf(stderr, "UNABLE TO SAVE BACK-UP COPY OF STRING\n");
			break;
		}
		fprintf(stderr, "%05u / %05u ----------------------------------\n",
			line_count, test_count);
		return_code = 0;
	}

	fprintf(stderr, "%05u / %05u ==================================\n",
		line_count, test_count);

	if (!return_code) {
		if (test_count != saved_count) {
			fprintf(stderr, "%s (%u) %s (%u).\n",
				"The number of strings added to the list", test_count,
				"is not equal to the number of saved string copies", saved_count);
			return_code = -1;
		}
		else {
			fprintf(stderr, "Sorting . . .");
			strln_sort(saved_count, saved_list, max_length);
			fprintf(stderr, "\nChecking . . .");
			for (count_1 = 0; count_1 < saved_count; count_1++) {
				if ((return_code = strln_find(test_count, test_list,
					saved_list[count_1], max_length, &found_index)) ==
					STRFUNCS_FAILURE) {
					fprintf(stderr,
						"\nERROR ON ATTEMPT TO FIND STRING %u (%s).\n",
						count_1, saved_list[count_1]);
					break;
				}
				else if (return_code == STRFUNCS_ITEM_NOT_FOUND) {
					fprintf(stderr, "\nUNABLE TO FIND STRING %s.\n",
						saved_list[count_1]);
					break;
				}
				else if (found_index != count_1) {
					fprintf(stderr,
						"\n%s (SORTED SAVED ITEM %u, FOUND ITEM %u).\n",
						"FIND ATTEMPT YIELDED UNEXPECTED RESULT:", count_1,
						found_index);
					return_code = -1;
					break;
				}
				return_code = 0;
			}
			fprintf(stderr, "\n");
		}
	}

	return(return_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

