/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Deletes an array of pointers element by key.

	Revision History	:	1991-09-26 --- Creation
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

   NAME        :  STR_LIST_delete

   SYNOPSIS    :  return_code = STR_LIST_delete(data_count, data_list,
							key_data, data_length, found_index, compare_function);

						int             return_code;

						unsigned int   *data_count;

						void         ***data_list;

						const void     *key_data;

						size_t          data_length;

						unsigned int   *found_index;

						int           (*compare_function)(void *, const void *,
												const void *, size_t);


   DESCRIPTION :  Performs a binary search in the array ``string_list`` for
						the element ``key_string`` using the comparison function
						``compare_function``.

						If ``key_string`` is found, its corresponding element in
						the array is deleted and its old index in ``string_list``
						is placed into the unsigned int to which ``found_index``
						points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to the number of elements in
						the array of pointers ``string_list``.

						(-) If the function succeeds in deleting the specified
						element then that integer will have subtracted from it
						the number of elements deleted (that is, it will be
						decremented).

						(.) ``string_list`` points to the array of pointers in
						which the search for ``key_string`` will be performed.

						(-) If the function succeeds in deleting an element then
						the memory pointed to by ``string_list`` will be re-allocated
						to hold the new size of the array.

						(.) ``key_string`` points to the data for which the deletion
						is to occur.

						(.) ``found_index`` points to an unsigned integer into
						which the index of ``key_string`` in ``string_list`` will be
						placed, if found.

						(-) If ``key_string`` is not found, the unsigned int to
						which ``found_index`` points will be set to the index
						at which ``key_string`` would be, assuming the array is
						ordered.

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

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_FAILURE'' if an error occurs.

						(.) ''STRFUNCS_ITEM_FOUND'' if ``key_strinh`` is found in
						the array ``string_list``. In this case, the unsigned int
						to which the ``found_index`` parameter points will be set
						to the index of that element in the array before the element
						is deleted.

						(.) ''STRFUNCS_ITEM_NOT_FOUND'' if ``key_string`` is not
						found in the array ``string_list``. In this case, the
						unsigned int to which the ``found_index`` parameter points
						will be set to the index of ``key_string`` did it reside in
						the array.

   NOTES       :  If there are multiple elements in ``string_list`` which
						compare equal to ``key_string``, the first of them will be
						deleted by this function.

						It is important to remember that the index returned in
						``found_index`` is no longer valid after a successful
						deletion.

   CAVEATS     :  The results of invoking this function with an
						``string_list`` not in sorted order using the same criteria
						as the function ``compare_function`` are undefined.

   SEE ALSO    :  STR_LIST_bsearch
						strl_find
						strl_search
						STR_ARRAY_delete

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  STR_LIST_delete
						Memory List Functions:STR_LIST_delete
						STRFUNCS:Memory List Functions:STR_LIST_delete
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_LIST_delete

   PUBLISH NAME:	STR_LIST_delete

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int STR_LIST_delete(unsigned int *data_count, void ***data_list,
	const void *key_data, size_t data_length, unsigned int *found_index,
	int (*compare_function)(void *, const void *, const void *, size_t))
#else
int STR_LIST_delete(data_count, data_list, key_data, data_length, found_index,
	compare_function)
unsigned int   *data_count;
void         ***data_list;
const void     *key_data;
size_t          data_length;
unsigned int   *found_index;
int           (*compare_function)();
#endif /* #ifndef NARGS */
{
	int          return_code;
	unsigned int tmp_found_index;

	found_index = (found_index != NULL) ? found_index : &tmp_found_index;

	if ((return_code = STR_LIST_bsearch(NULL, *data_count,
		((void **) *data_list), key_data, data_length, found_index,
		STRFUNCS_DIRECTION_TOP, compare_function)) == STRFUNCS_ITEM_FOUND) {
		if (memldel(data_count, data_list, *found_index, 1) == STRFUNCS_FAILURE)
			return_code = STRFUNCS_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */

