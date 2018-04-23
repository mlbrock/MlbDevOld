/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Searchs an array of pointers by key, inserting the
								key if not found.

	Revision History	:	1991-09-26 --- Creation
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

   NAME        :  STR_LIST_search

   SYNOPSIS    :  return_code = STR_LIST_search(data_count, data_list,
							key_data, data_length, found_index, compare_function,
							insert_function);

						int             return_code;

						unsigned int   *data_count;

						void         ***data_list;

						const void     *key_data;

						size_t          data_length;

						unsigned int   *found_index;

						int           (*compare_function)(void *, const void *,
												const void *, size_t);

						int           (*insert_function)(unsigned int *, void ***,
												const void *, size_t, unsigned int);

   DESCRIPTION :  Performs a binary search in the array ``string_list`` for
						the element ``key_string`` using the comparison function
						``compare_function``.

						If ``key_string`` is found, its index in ``string_list``
						is placed into the unsigned int to which ``found_index``
						points.

						If ``key_string`` is not found, this function will attempt
						to add it to the array ``string_list`` in sorted order
						using the insertion function ``insert_function``.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to the number of elements in
						the array of pointers ``string_list``.

						(-) If the function succeeds in inserting ``key_string``
						then that integer will have added to it the number of
						elements inserted (that it, is will be incremented).

						(.) ``string_list`` points to the array of pointers in
						which the search for ``data_key`` will be performed. If
						the function succeeds in inserting an element then the
						memory pointed to by ``string_list`` will be re-allocated
						to hold the new size of the array.

						(.) ``key_string`` points to the data for which the search
						is to occur.

						(.) ``found_index`` points to an unsigned integer into
						which the index of ``key_string`` in ``string_list`` will
						be placed, if found.

						(-) If ``key_string`` is not found, the unsigned int to
						which ``found_index`` points will be set to the index
						at which ``key_string`` will be inserted.

						(-) Note, however, that ``found_index`` will not be
						de-referenced if it is ''NULL''.

						(.) ``compare_function`` is a pointer to the function
						which will determine equivalence of ``key_string``
						``vis-a-vis`` the elements in ``string_list``. The function
						to which ``compare_function`` points should accept the
						arguments indicated in the SYNOPSIS and return an integral
						result as follows:

						(..) negative if the first element is less than second.

						(..) positive if the first element is greater than second.

						(..) zero if the elements are equal.

						(.) ``insert_function`` is a pointer to the function
						which will insert ``key_string`` into the array
						``string_list``. The function to which ``insert_function``
						points should accept the arguments indicated in the SYNOPSIS
						and return one of the two values:

						(..) ''STRFUNCS_FAILURE'' if an error occurs.

						(..) ''STRFUNCS_SUCCESS'' if it successfully inserts
						``key_data``.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_FAILURE'' if an error occurs.

						(.) ''STRFUNCS_ITEM_FOUND'' if ``key_string`` is found in
						the array ``string_list``. In this case, the unsigned int
						to which the ``found_index`` parameter points will be set
						to the index of that element in the array.

						(.) ''STRFUNCS_ITEM_NOT_FOUND'' if ``key_string`` is not
						found in the array ``string_list``. In this case, the
						unsigned int to which the ``found_index`` parameter points
						will be set to the index within ``string_list`` at which
						``key_string`` was inserted by this function.

   NOTES       :  

   CAVEATS     :  The results of invoking this function with an
						``string_list`` not in sorted order using the same criteria
						as the function ``compare_function`` are undefined.

   SEE ALSO    :  STR_LIST_bsearch
						STR_ARRAY_search

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  STR_LIST_search
						Memory List Functions:STR_LIST_search
						STRFUNCS:Memory List Functions:STR_LIST_search
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_LIST_search

   PUBLISH NAME:	STR_LIST_search

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int STR_LIST_search(unsigned int *data_count, void ***data_list,
	const void *key_data, size_t data_length, unsigned int *found_index,
	int (*compare_function)(void *, const void *, const void *, size_t),
	int (*insert_function)(unsigned int *, void ***, const void *, size_t,
		unsigned int))
#else
int STR_LIST_search(data_count, data_list, key_data, data_length, found_index,
	compare_function, insert_function)
unsigned int   *data_count;
void         ***data_list;
const void     *key_data;
size_t          data_length;
unsigned int   *found_index;
int           (*compare_function)();
int           (*insert_function)();
#endif /* #ifndef NARGS */
{
	int          return_code;
	unsigned int tmp_found_index;

	found_index = (found_index != NULL) ? found_index : &tmp_found_index;

	if ((return_code = STR_LIST_bsearch(NULL, *data_count,
		((void **) *data_list), key_data, data_length, found_index,
		STRFUNCS_DIRECTION_TOP, compare_function)) == STRFUNCS_ITEM_NOT_FOUND) {
		if ((*insert_function)(data_count, data_list, key_data, data_length,
			*found_index) == STRFUNCS_FAILURE)
			return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */

