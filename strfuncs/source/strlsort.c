/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sorts an array of pointers.

	Revision History	:	1991-09-20 --- Creation
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

   NAME        :  STR_LIST_qsort

   SYNOPSIS    :  STR_LIST_qsort(control_ptr, data_count, data_list,
							data_length, compare_function);

						void          *control_ptr;

						unsigned int   data_count;

						void         **data_list;

						size_t         data_length;

						int          (*compare_function)(void *, const void *,
							const void *, size_t);

   DESCRIPTION :  This function sorts an array of pointers using the ACM
						271 algorithm popularly known as Quicksort.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparisons
						used to determine sort order. It is passed unexamined
						to the comparison function ``compare_function``. If
						unnecessary, it may be a ''NULL'' pointer.

						(.) ``data_count`` is the number of elements in the array
						of pointers ``data_list``.

						(.) ``data_list`` is the array of pointers to be sorted.

						(.) ``data_length`` is the size the areas to which each
						element of the array ``data_list`` points. It is passed
						unexamined to the comparison function ``compare_function``.
						If unnecessary, it may be zero (0).

						(.) ``compare_function`` is a pointer to the function which
						will determine sort order. The function to which
						``compare_function`` points should accept the arguments
						indicated in the SYNOPSIS and return an integral result
						as follows:

						(..) negative if the first element is less than second.

						(..) positive if the first element is greater than second.

						(..) zero if the elements are equal.

   RETURNS     :  Void.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  STR_LIST_qsort
						Memory List Functions:STR_LIST_qsort
						STRFUNCS:Memory List Functions:STR_LIST_qsort
						String Functions:See STRFUNCS

   PUBLISH XREF:  STR_LIST_qsort

   PUBLISH NAME:	STR_LIST_qsort

	ENTRY CLASS	:	Memory List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void STR_LIST_qsort(void *control_ptr, unsigned int data_count,
	void **data_list, size_t data_length,
	int (*compare_function)(void *, const void *, const void *, size_t))
#else
void STR_LIST_qsort(control_ptr, data_count, data_list, data_length,
	compare_function)
void          *control_ptr;
unsigned int   data_count;
void         **data_list;
size_t         data_length;
int          (*compare_function)();
#endif /* #ifndef NARGS */
{
	unsigned int   count_1;
	unsigned int   count_2;
	void         **ptr_1;
	void         **ptr_2;
	void          *temp_ptr;

	if (data_count <= 1L)
		return;

	ptr_1 = data_list + 1;

	if (data_count == 2) {
		if (((*compare_function)(control_ptr, *data_list, *ptr_1,
			data_length)) > 0) {
			temp_ptr   = *data_list;
			*data_list = *ptr_1;
			*ptr_1     = temp_ptr;
		}
		return;
	}

	temp_ptr                        = *data_list;
	*data_list                      = *(data_list + (data_count / 2));
	*(data_list + (data_count / 2)) = temp_ptr;

	for (ptr_2 = data_list, count_2 = 0, count_1 = 1; count_1 < data_count;
		count_1++) {
		if (((*compare_function)(control_ptr, *ptr_1, *data_list,
			data_length)) < 0) {
			count_2++;
			ptr_2++;
			if (ptr_1 != ptr_2) {
				temp_ptr = *ptr_1;
				*ptr_1   = *ptr_2;
				*ptr_2   = temp_ptr;
			}
		}
		ptr_1++;
	}

	if (ptr_2 != data_list) {
		temp_ptr   = *data_list;
		*data_list = *ptr_2;
		*ptr_2     = temp_ptr;
	}

	STR_LIST_qsort(control_ptr, count_2, data_list, data_length,
		compare_function);

	STR_LIST_qsort(control_ptr, data_count - count_2 - 1, ptr_2 + 1,
		data_length, compare_function);
}
/*	*********************************************************************** */

