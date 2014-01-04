/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Makes an array of pointers unique.

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

   NAME        :  STR_LIST_uniq

   SYNOPSIS    :  STR_LIST_uniq(control_ptr, data_count, data_list,
							data_length, compare_function);

						void           *control_ptr;

						unsigned int   *data_count;

						void         ***data_list;

						size_t          data_length;

						int           (*compare_function)(void *, const void *,
							const void *, size_t);

   DESCRIPTION :  Makes an array of pointers unique.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparisons
						used to determine equivalence. It is passed unexamined
						to the comparison function ``compare_function``. If
						unnecessary, it may be a ''NULL'' pointer.

						(.) ``data_count`` points to the number of elements in the
						array of pointers ``data_list``.

						(.) ``data_list`` points to the array of pointers to be made
						unique.

						(.) ``data_length`` is the size the areas to which each
						element of the array ``data_list`` points. It is passed
						unexamined to the comparison function ``compare_function``.
						If unnecessary, it may be zero (0).

						(.) ``compare_function`` is a pointer to the function which
						will determine equivalence. The function to which
						``compare_function`` points should accept the arguments
						indicated in the SYNOPSIS and return an integral result
						as follows:

						(..) negative if the first element is less than second.

						(..) positive if the first element is greater than second.

						(..) zero if the elements are equal.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  The results of invoking this function with an ``data_list``
						not in sorted order using the same criteria as the function
						``compare_function`` are undefined.

						If there are multiple elements in ``data_list`` which
						compare equal, it is impossible to determine which of
						them will be removed by this function.

   SEE ALSO    :  STR_ARRAY_uniq

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2014 Michael L. Brock

   OUTPUT INDEX:  STR_LIST_uniq
						Memory List Functions:STR_LIST_uniq
						STRFUNCS:Memory List Functions:STR_LIST_uniq
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_LIST_uniq

   PUBLISH NAME:	STR_LIST_uniq

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void STR_LIST_uniq(void *control_ptr, unsigned int *data_count,
	void ***data_list, size_t data_length,
	int (*compare_function)(void *, const void *, const void *, size_t))
#else
void STR_LIST_uniq(control_ptr, data_count, data_list, data_length,
	compare_function)
void           *control_ptr;
unsigned int   *data_count;
void         ***data_list;
size_t          data_length;
int           (*compare_function)();
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	if (*data_count > 1) {
		for (count_1 = 0; *data_count && (count_1 < (*data_count - 1));
			count_1++) {
			while (((count_1 + 1) < *data_count) &&
				(!(*compare_function)(control_ptr, (*data_list)[count_1],
				(*data_list)[count_1 + 1], data_length)))
				memldel(data_count, data_list, count_1 + 1, 1);
		}
	}
}
/*	*********************************************************************** */

