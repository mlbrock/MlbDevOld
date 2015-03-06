/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Searchs an array by key, inserting the key if not
								found.

	Revision History	:	1991-09-08 --- Creation
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

   NAME        :  STR_ARRAY_search

   SYNOPSIS    :  return_code = STR_ARRAY_search(data_count, data_list,
							key_data, data_length, found_index, compare_function,
							insert_function);

						int            return_code;

						unsigned int  *data_count;

						void         **data_list;

						const void    *key_data;

						size_t         data_length;

						unsigned int  *found_index;

						int          (*compare_function)(void *, const void *,
											const void *, size_t);

						int          (*insert_function)(unsigned int *, void **,
											const void *, size_t, unsigned int);

   DESCRIPTION :  Performs a binary search in the array ``data_list`` for
						the element ``key_data`` using the comparison function
						``compare_function``.

						If ``key_data`` is found, its index in ``data_list``
						is placed into the unsigned int to which ``found_index``
						points.

						If ``key_data`` is not found, this function will attempt
						to add it to the array ``data_list`` in sorted order using
						the insertion function ``insert_function``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to an ``unsigned int`` which
						contains the number of elements in the array to which
						``data_list`` points.

						(-) If the function succeeds in inserting ``key_data``
						then that integer will have added to it the number of
						elements inserted (that it, is will be incremented).

						(.) ``data_list`` points to a pointer to ``void`` which
						contains the array. If the function succeeds in inserting
						an element then the memory pointed to by ``data_list`` will
						be re-allocated to hold the new size of the array.

						(.) ``key_data`` points to the data for which the search
						is to occur.

						(.) ``data_length`` is the length of the array elements in
						``data_list``.

						(.) ``found_index`` points to an unsigned integer into
						which the index of ``key_data`` in ``data_list`` will be
						placed, if found.

						(-) If ``key_data`` is not found, the unsigned int to
						which ``found_index`` points will be set to the index
						at which ``key_data`` will be inserted.

						(-) Note, however, that ``found_index`` will not be
						de-referenced if it is ''NULL''.

						(.) ``compare_function`` is a pointer to the function
						which will determine equivalence of ``key_data``
						``vis-a-vis`` the elements in ``data_list``. The function
						to which ``compare_function`` points should accept the
						arguments indicated in the SYNOPSIS and return an integral
						result as follows:

						(..) negative if the first element is less than second.

						(..) positive if the first element is greater than second.

						(..) zero if the elements are equal.

						(.) ``insert_function`` is a pointer to the function
						which will insert ``key_data`` into the array ``data_list``.
						The function to which ``insert_function`` points should
						accept the arguments indicated in the SYNOPSIS and return
						one of the two values:

						(..) ''STRFUNCS_FAILURE'' if an error occurs.

						(..) ''STRFUNCS_SUCCESS'' if it successfully inserts
						``key_data``.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_FAILURE'' if an error occurs.

						(.) ''STRFUNCS_ITEM_FOUND'' if ``key_data`` is found in the
						array ``data_list``. In this case, the unsigned int to
						which the ``found_index`` parameter points will be set to
						the index of that element in the array.

						(.) ''STRFUNCS_ITEM_NOT_FOUND'' if ``key_data`` is not found
						in the array ``data_list``. In this case, the unsigned int
						to which the ``found_index`` parameter points will be set to
						the index within ``data_list`` at which ``key_data`` was
						inserted by this function.

   NOTES       :  

   CAVEATS     :  The results of invoking this function with an ``data_list``
						not in sorted order using the same criteria as the function
						``compare_function`` are undefined.

   SEE ALSO    :  STR_ARRAY_bsearch
						STR_LIST_search

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  STR_ARRAY_search
						Memory Array Functions:STR_ARRAY_search
						STRFUNCS:Memory Array Functions:STR_ARRAY_search
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_ARRAY_search

   PUBLISH NAME:	STR_ARRAY_search

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int STR_ARRAY_search(unsigned int *data_count, void **data_list,
	const void *key_data, size_t data_length, unsigned int *found_index,
	int (*compare_function)(void *, const void *, const void *, size_t),
	int (*insert_function)(unsigned int *, void **, const void *, size_t,
		unsigned int))
#else
int STR_ARRAY_search(data_count, data_list, key_data, data_length,
	found_index, compare_function, insert_function)
unsigned int  *data_count;
void         **data_list;
const void    *key_data;
size_t         data_length;
unsigned int  *found_index;
int          (*compare_function)();
int          (*insert_function)();
#endif /* #ifndef NARGS */
{
	int          return_code;
	unsigned int tmp_found_index;

	found_index = (found_index != NULL) ? found_index : &tmp_found_index;

	if ((return_code = STR_ARRAY_bsearch(NULL, *data_count, *data_list,
		key_data, data_length, found_index, STRFUNCS_DIRECTION_TOP,
		compare_function)) == STRFUNCS_ITEM_NOT_FOUND) {
		if ((*insert_function)(data_count, data_list, key_data, data_length,
			*found_index) == STRFUNCS_FAILURE)
			return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
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
	int           return_code = 0;
	unsigned int  count_1;
	unsigned int  line_count  = 0;
	unsigned int  test_count  = 0;
	unsigned int  saved_count = 0;
	unsigned int  found_index;
	char         *test_list   = NULL;
	char         *saved_list  = NULL;
	char          buffer[512];

	fprintf(stderr, "Test of function 'STR_ARRAY_search()'\n");
	fprintf(stderr, "---- -- -------- --------------------\n\n");

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
					test_list + (count_1 * sizeof(buffer)),
					test_list + (count_1 * sizeof(buffer)));
		}
		else if ((!stricmp(buffer, "END")) || (!stricmp(buffer, "QUIT")) ||
			(!stricmp(buffer, "EXIT")))
			break;
		else if ((return_code = STR_ARRAY_search(&test_count, ((void **) &test_list),
			((const void *) buffer), sizeof(buffer), &found_index,
			((int (*)(void *, const void *, const void *, size_t)) STR_strcmp),
			mema_insert)) == STRFUNCS_FAILURE) {
			fprintf(stderr, "\nERROR ON ATTEMPT TO ADD STRING\n\n");
			break;
		}
		else if (return_code == STRFUNCS_ITEM_FOUND)
			fprintf(stderr, "STRING ALREADY IN LIST (INDEX = %u)\n",
				found_index);
		else if ((return_code = mema_append(&saved_count,
			((void **) &saved_list), buffer, sizeof(buffer))) ==
			STRFUNCS_FAILURE) {
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
#ifndef NARGS
			STR_ARRAY_qsort(NULL, saved_count, saved_list, sizeof(buffer),
				((int (*)(void *, const void *, const void *, size_t))
				STR_strcmp));
#else
			STR_ARRAY_qsort(NULL, saved_count, saved_list, sizeof(buffer),
				STR_strcmp);
#endif /* #ifndef NARGS */
			fprintf(stderr, "\nChecking . . .");
			for (count_1 = 0; count_1 < saved_count; count_1++) {
#ifndef NARGS
				if ((return_code = STR_ARRAY_find(test_count, test_list,
					saved_list + (count_1 * sizeof(buffer)), sizeof(buffer),
					&found_index,
					((int (*)(void *, const void *, const void *, size_t))
					STR_strcmp))) == STRFUNCS_FAILURE) {
#else
				if ((return_code = STR_ARRAY_find(test_count, test_list,
					saved_list + (count_1 * sizeof(buffer)), sizeof(buffer),
					&found_index, STR_strcmp)) == STRFUNCS_FAILURE) {
#endif /* #ifndef NARGS */
					fprintf(stderr,
						"\nERROR ON ATTEMPT TO FIND STRING %u (%s).\n",
						count_1, saved_list + (count_1 * sizeof(buffer)));
					break;
				}
				else if (return_code == STRFUNCS_ITEM_NOT_FOUND) {
					fprintf(stderr, "\nUNABLE TO FIND STRING %s.\n",
						saved_list + (count_1 * sizeof(buffer)));
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

