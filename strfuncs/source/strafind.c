/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Finds an array element by key.

	Revision History	:	1991-09-08 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2016.
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

   NAME        :  STR_ARRAY_find

   SYNOPSIS    :  return_code = STR_ARRAY_find(data_count, data_list,
							key_data, data_length, found_index, compare_function);

						int            return_code;

						unsigned int   data_count;

						const void    *data_list;

						const void    *key_data;

						size_t         data_length;

						unsigned int  *found_index;

						int          (*compare_function)(void *, const void *,
											const void *, size_t);

   DESCRIPTION :  Performs a binary search in the array ``data_list`` for
						the element ``key_data`` using the comparison function
						``compare_function``.

						If ``key_data`` is found, its index in ``data_list``
						is placed into the unsigned int to which ``found_index``
						points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``data_count`` points to an ``unsigned int`` which
						contains the number of elements in the array to which
						``data_list`` points.

						(.) ``data_list`` points to a pointer to ``void`` which
						contains the array to be searched.

						(.) ``key_data`` points to the data for which the search
						is to occur.

						(.) ``data_length`` is the length of the array elements in
						``data_list``.

						(.) ``found_index`` points to an unsigned integer into
						which the index of ``key_data`` in ``data_list`` will be
						placed, if found.

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

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_FAILURE'' if an error occurs.

						(.) ''STRFUNCS_ITEM_FOUND'' if ``key_data`` is found in the
						array ``data_list``. In this case, the unsigned int to
						which the ``found_index`` parameter points will be set to
						the index of that element in the array.

						(.) ''STRFUNCS_ITEM_NOT_FOUND'' if ``key_data`` is not found
						in the array ``data_list``.

   NOTES       :  If there are multiple elements in ``data_list`` which
						compare equal to ``key_data``, the first of them will be
						located by this function.

   CAVEATS     :  The results of invoking this function with an ``data_list``
						not in sorted order using the same criteria as the function
						``compare_function`` are undefined.

   SEE ALSO    :  STR_ARRAY_bsearch
						STR_LIST_find

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2016 Michael L. Brock

   OUTPUT INDEX:  STR_ARRAY_find
						Memory Array Functions:STR_ARRAY_find
						STRFUNCS:Memory Array Functions:STR_ARRAY_find
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_ARRAY_find

   PUBLISH NAME:	STR_ARRAY_find

	ENTRY CLASS	:	Memory Array Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int STR_ARRAY_find(unsigned int data_count, const void *data_list,
	const void *key_data, size_t data_length, unsigned int *found_index,
	int (*compare_function)(void *, const void *, const void *, size_t))
#else
int STR_ARRAY_find(data_count, data_list, key_data, data_length, found_index,
	compare_function)
unsigned int   data_count;
const void    *data_list;
const void    *key_data;
size_t         data_length;
unsigned int  *found_index;
int          (*compare_function)();
#endif /* #ifndef NARGS */
{
	return(STR_ARRAY_bsearch(NULL, data_count, data_list, key_data,
		data_length, found_index, STRFUNCS_DIRECTION_TOP, compare_function));
}
/* *********************************************************************** */

