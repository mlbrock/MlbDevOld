/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a binary search on an array.

	Revision History	:	1991-09-07 --- Creation
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

#ifdef DEBUG_FLAG
#include <stdio.h>
#endif /* #ifdef DEBUG_FLAG */

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  STR_ARRAY_bsearch

   SYNOPSIS    :  return_code = STR_ARRAY_bsearch(control_ptr, data_count,
							data_list, key_data, data_length, found_index,
							direction_flag, compare_function);

						int           return_code;

						void         *control_ptr;

						unsigned int  data_count;

						const void   *data_list;

						const void   *key_data;

						size_t        data_length;

						unsigned int *found_index;

						int           direction_flag;

						int          (*compare_function)(void *, const void *,
							const void *, size_t);

   DESCRIPTION :  This function is a binary search routine generalized from
						Knuth (6.2.1) Algorithm B for use with arrays. The algorithm
						assumes that the array has been previously sorted in
						ascending order according to the provided comparison
						function ``compare_function``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparisons
						used to determine the relative equality of ``key_data``
						``vis-a-vis`` the elements in the array ``data_list``. It
						is passed unexamined to the comparison function
						``compare_function``. If unnecessary, it may be a ''NULL''
						pointer.

						(.) ``data_count`` is the number of elements in the array
						``data_list``.

						(.) ``data_list`` is the array in which the search for
						``key_data`` will be performed.

						(.) ``key_data`` points to the data for which the search
						is to occur.

						(.) ``data_length`` is the size each element of the array
						``data_list``.

						(.) ``found_index`` points to an unsigned integer into
						which the index of ``key_data`` in ``data_list`` will be
						placed, if found.

						(-) If ``key_data`` is not found, the unsigned int to
						which ``found_index`` points will be set to the index
						at which ``key_data`` would be inserted if the array is
						to remain ordered.

						(-) Note, however, that ``found_index`` will not be
						de-referenced if it is ''NULL''.

						(.) ``direction_flag`` specifies the anchor point for the
						search. This determines whether the unsigned integer to
						which the ``found_index`` parameter points will be set to
						the first element matching ``key_data``, the last element
						matching ``key_data``, or any arbitrary element matching
						``key_data``.

						(..) ''STRFUNCS_DIRECTION_TOP'' to anchor the returned
						element to the first of the records matching ``key_data``.

						(..) ''STRFUNCS_DIRECTION_BOTTOM'' to anchor the returned
						element to the last of the records matching ``key_data``.

						(..) ''STRFUNCS_DIRECTION_NONE'' specifies that the search
						is not to be anchored --- that any one of the records
						matching ``key_data`` is to be returned.

						(.) ``compare_function`` is a pointer to the function
						which will determine equivalence of ``key_data``
						``vis-a-vis`` the elements in ``data_list``. The function
						to which ``compare_function`` points should accept the
						arguments indicated in the SYNOPSIS and return an integral
						result as follows:

						(..) negative if the first element is less than second.

						(..) positive if the first element is greater than second.

						(..) zero if the elements are equal.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_FAILURE'' if an error occurs.

						(.) ''STRFUNCS_ITEM_FOUND'' if ``key_data`` is found in the
						array ``data_list``. In this case, the unsigned int to
						which the ``found_index`` parameter points will be set to
						the index of that element in the array.

						(.) ''STRFUNCS_ITEM_NOT_FOUND'' if ``key_data`` is not found
						in the array ``data_list``. In this case, the unsigned int
						to which the ``found_index`` parameter points will be set to
						the index of the array into which ``key_data`` should be
						inserted.

   NOTES       :  

   CAVEATS     :  The results of invoking this function with an ``data_list``
						not in sorted order using the same criteria as the function
						``compare_function`` are undefined.

						If there are multiple elements in ``data_list`` which
						compare equal, it is impossible to determine which of
						them will be returned by this function if ``direction_flag``
						is equal to ''STRFUNCS_DIRECTION_NONE''.

   SEE ALSO    :  STR_LIST_bsearch

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2015 Michael L. Brock

   OUTPUT INDEX:  STR_ARRAY_bsearch
						Memory Array Functions:STR_ARRAY_bsearch
						STRFUNCS:Memory Array Functions:STR_ARRAY_bsearch
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_ARRAY_bsearch

   PUBLISH NAME:	STR_ARRAY_bsearch

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int STR_ARRAY_bsearch(void *control_ptr, unsigned int data_count,
	const void *data_list, const void *key_data, size_t data_length,
	unsigned int *found_index, int direction_flag,
	int (*compare_function)(void *, const void *, const void *, size_t))
#else
int STR_ARRAY_bsearch(control_ptr, data_count, data_list, key_data,
	data_length, found_index, direction_flag, compare_function)
void         *control_ptr;
unsigned int  data_count;
const void   *data_list;
const void   *key_data;
size_t        data_length;
unsigned int *found_index;
int           direction_flag;
int         (*compare_function)();
#endif /* #ifndef NARGS */
{
	int          return_code = STRFUNCS_ITEM_NOT_FOUND;
	int          compare_value;
	size_t       start_index;
	size_t       current_index;
	size_t       end_index;
	unsigned int tmp_found_index;

	found_index = (found_index != NULL) ? found_index : &tmp_found_index;

#ifdef DEBUG_FLAG
fprintf(stderr, "KEY_AREA: [%08.08X]\n", key_data);
#endif /* #ifdef DEBUG_FLAG */

	if ((!data_count) || (!data_list))
		*found_index = 0;
	else {
		start_index = 0;
		end_index   = data_count - 1;
		while ((current_index =
			(start_index + end_index) / 2) != end_index) {
#ifdef DEBUG_FLAG
fprintf(stderr, "IN LOOP : START = %u, CURRENT = %u, END = %u",
	start_index, current_index, end_index);
#endif /* #ifdef DEBUG_FLAG */
			compare_value = ((*compare_function)(control_ptr, key_data,
				((const void *) (((char *) data_list) +
				(current_index * data_length))), data_length));
#ifdef DEBUG_FLAG
fprintf(stderr, " (%d)\n", compare_value);
#endif /* #ifdef DEBUG_FLAG */
			if (!compare_value) {
				*found_index = current_index;
				return_code  = STRFUNCS_ITEM_FOUND;
				break;
			}
			else if (compare_value > 0)
				start_index = (start_index == current_index) ?
					(current_index + 1) : current_index;
			else
				end_index = current_index;
#ifdef DEBUG_FLAG
fprintf(stderr, ">>> IN LOOP : START = %u, CURRENT = %u, END = %u\n",
	start_index, current_index, end_index);
#endif /* #ifdef DEBUG_FLAG */
		}
		if (return_code != STRFUNCS_ITEM_FOUND) {
			if ((compare_value = ((*compare_function)(control_ptr,
				key_data, ((const void *) (((char *) data_list) +
            (current_index * data_length))), data_length))) == 0)
#ifdef DEBUG_FLAG
{
fprintf(stderr, ">>> USED EXCEPTION ROUTINE (%s)\n", key_data);
#endif /* #ifdef DEBUG_FLAG */
				return_code  = STRFUNCS_ITEM_FOUND;
#ifdef DEBUG_FLAG
}
#endif /* #ifdef DEBUG_FLAG */
			else if (compare_value > 0)
				current_index = data_count;
			*found_index = current_index;
		}
		if (return_code == STRFUNCS_ITEM_FOUND) {
			if (direction_flag > 0) {
				while ((*found_index > 0) && (!(*compare_function)(control_ptr,
				key_data, ((const void *) (((char *) data_list) +
				((*found_index - 1) * data_length))), data_length)))
				(*found_index)--;
			}
			else if (direction_flag < 0) {
				while ((*found_index < (data_count - 1)) &&
				(!(*compare_function)(control_ptr, key_data,
				((const void *) (((char *) data_list) +
				((*found_index + 1) * data_length))), data_length)))
				(*found_index)++;
			}
		}
#ifdef DEBUG_FLAG
fprintf(stderr, "END LOOP: START = %u, CURRENT = %u, END = %u\n",
	start_index, current_index, end_index);
#endif /* #ifdef DEBUG_FLAG */
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COMPAT_FN_DECL(int main, (void));

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
int main()
{
	int           return_code = 0;
	unsigned int  diff_count  = 0;
	unsigned int  line_count  = 0;
	unsigned int  test_count  = 0;
	unsigned int  saved_count = 0;
	char         *test_list   = NULL;
	char         *saved_list  = NULL;
	unsigned int  count_1;
	unsigned int  found_index;
	char         *tmp_ptr_1;
	char         *tmp_ptr_2;
	char          buffer[64];
	char          in_line[64];

	fprintf(stderr, "Test of function 'STR_ARRAY_bsearch()'\n");
	fprintf(stderr, "---- -- -------- ---------------------\n\n");

	while ((!feof(stdin)) && (!ferror(stdin))) {
		*in_line = '\0';
		while (!(*in_line)) {
			fgets(in_line, sizeof(in_line) - 1, stdin);
			while (strlen(in_line) && (in_line[strlen(in_line) - 1] == '\n'))
				in_line[strlen(in_line) - 1] = '\0';
			line_count++;
		}
		memset(buffer, '\0', sizeof(buffer));
		strcpy(buffer, in_line);
		if (!stricmp(in_line, "LIST")) {
			fprintf(stderr, "[HEAD] ---> [%p]\n", test_list);
			for (count_1 = 0; count_1 < test_count; count_1++)
				fprintf(stderr, "[%05u][%p] ---> [%s]\n", count_1,
					test_list + (count_1 * sizeof(in_line)),
					test_list + (count_1 * sizeof(in_line)));
		}
		else if ((!stricmp(in_line, "END")) || (!stricmp(in_line, "QUIT")) ||
			(!stricmp(in_line, "EXIT")))
			break;
		else if ((return_code = STR_ARRAY_bsearch(NULL, test_count, test_list,
			buffer, sizeof(buffer), &found_index, -1,
			((int (*)(void *, const void *, const void *, size_t))
			STR_strcmp))) == STRFUNCS_FAILURE) {
			fprintf(stderr, "\nERROR ON ATTEMPT TO ADD STRING\n\n");
			break;
		}
/*
		else if (return_code == STRFUNCS_ITEM_FOUND)
			fprintf(stderr, "STRING ALREADY IN LIST (INDEX = %u)\n",
				found_index);
*/
		else {
			tmp_ptr_1 = (!test_count)  ? ((char *) calloc(sizeof(buffer), 1)) :
				((char *) realloc(test_list,  (test_count + 1)  * sizeof(buffer)));
			tmp_ptr_2 = (!saved_count) ? ((char *) calloc(sizeof(buffer), 1)) :
				((char *) realloc(saved_list, (saved_count + 1) * sizeof(buffer)));
			if ((tmp_ptr_1 == NULL) || (tmp_ptr_2 == NULL)) {
				fprintf(stderr, "ERROR: Unable to add string to lists.\n\n");
				return_code = -1;
				break;
			}
			test_list  = tmp_ptr_1;
			saved_list = tmp_ptr_2;
			if (found_index < test_count) {
				for (count_1 = test_count; count_1 > found_index; count_1--)
					memcpy(test_list + (count_1 * sizeof(buffer)),
						test_list + ((count_1 - 1) * sizeof(buffer)),
						sizeof(buffer));
			}
			memcpy(test_list  + (found_index       * sizeof(buffer)),
				buffer, sizeof(buffer));
			memcpy(saved_list + (saved_count       * sizeof(buffer)),
				buffer, sizeof(buffer));
			test_count++;
			saved_count++;
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
			STR_ARRAY_qsort(NULL, saved_count, ((void **) saved_list),
				sizeof(buffer),
				((int (*)(void *, const void *, const void *, size_t))
				STR_strcmp));
#else
			STR_ARRAY_qsort(NULL, saved_count, ((void **) saved_list),
				sizeof(buffer), STR_strcmp);
#endif /* #ifndef NARGS */
			fprintf(stderr, "\nChecking . . .");
			if (!memcmp(test_list, saved_list, test_count * sizeof(buffer))) 
				fprintf(stderr, " --- arrays are identical\n\n");
			else {
				fprintf(stderr, " --- ERROR: Arrays are different\n\n");
				for (count_1 = 0; count_1 < test_count; count_1++) {
					if (memcmp(test_list + (count_1 * sizeof(buffer)),
						saved_list + (count_1 * sizeof(buffer)), sizeof(buffer))) {
						fprintf(stderr, "[%05u] LIST 1: %s\n", diff_count,
							test_list + (count_1 * sizeof(buffer)));
						fprintf(stderr, "        LIST 2: %s\n",
							saved_list + (count_1 * sizeof(buffer)));
						diff_count++;
					}
				}
			}
			fprintf(stderr, "\n");
		}
	}

	return(return_code);
}
/* *********************************************************************** */

#endif /* #ifdef TEST_MAIN */

