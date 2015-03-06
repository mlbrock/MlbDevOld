/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Generic memory area pointer array comparison
								functions.

	Revision History	:	1992-03-19 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "strfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  mema_CompareArrays

   SYNOPSIS    :  return_code = mema_CompareArrays(in_count_1, in_array_1,
							in_count_2, in_array_2, data_length, difference_index);

						unsigned int  in_count_1;

						const void   *in_array_1;

						unsigned int  in_count_2;

						const void   *in_array_2;

						size_t        data_length;

						unsigned int *difference_index;

   DESCRIPTION :  Compares two arrays to determine whether they are equal.

						Arrays are considered not equal if they have a different
						lengths (the ``in_count_1`` and ``in_count_2`` parameters).

						Array elements are considered not equal if the
						comparison function ``MEM_memcmp`` returns a non-zero
						value.

						(.) This is a case-sensitive comparison.

						(.) The maximum length of the memory area comparison is
						``data_length`` characters.

						This function compares each element of the two arrays
						up to the minimum of `in_count_1`` and ``in_count_2``.
						If the element of one array is ''NULL'' and the same
						element of the other array is not ''NULL'', the array
						with the non-NULL element will be considered to be
						greater than its correspondent,

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_count_1`` is the number of elements in the
						array ``in_array_1``.

						(.) ``in_array_1`` is the first array to be compared.

						(.) ``in_count_2`` is the number of elements in the
						array ``in_array_2``.

						(.) ``in_array_2`` is the second array to be compared.

						(.) ``data_length`` is the maximum length of the
						comparisons to be performed on the array elements of
						``in_array_1`` and ``in_array_2``.

						(.) ``difference_index`` is a pointer to an ''unsigned int''
						into which this function will place the index of the first
						difference between the two arrays.

						(-) Note that if the ``difference_index`` parameter is
						''NULL'' it will not be dereferenced by this function.

   RETURNS     :  Returns from this function are as follow:

						(.) negative if the first array compares less than
						the second array.

						(.) positive if the first array compares greater than
						the second array.

						(.) zero if the two arrays are equal both in the number
						of elements in the arrays and the memory to which elements
						in the arrays point.

   NOTES       :  The ``control_ptr`` and ``data_length`` parameters are
						present only because this function is used internally
						by other STRFUNCS list functions. They provide
						function-call compatibility with other, more generic,
						comparison functions.

   CAVEATS     :  

   SEE ALSO    :  strl_CompareArrays
						strli_CompareArrays
						strln_CompareArrays
						strlni_CompareArrays
						memai_CompareArrays
						mema_CompareArraysBasic
						meml_CompareLists

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:  mema_CompareArrays
						String Array Functions:mema_CompareArrays
						STRFUNCS:String Array Functions:mema_CompareArrays
						String Functions:See STRFUNCS

   PUBLISH XREF:  mema_CompareArrays

   PUBLISH NAME:	mema_CompareArrays

	ENTRY CLASS	:	String Array Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int mema_CompareArrays(unsigned int in_count_1, const void *in_array_1,
	unsigned int in_count_2, const void *in_array_2, size_t data_length,
	unsigned int *difference_index)
#else
int mema_CompareArrays(in_count_1, in_array_1, in_count_2, in_array_2,
	data_length, difference_index)
unsigned int  in_count_1;
const void   *in_array_1;
unsigned int  in_count_2;
const void   *in_array_2;
size_t        data_length;
unsigned int *difference_index;
#endif /* #ifndef NARGS */
{
	return(mema_CompareArraysBasic(in_count_1, in_array_1, in_count_2,
		in_array_2, MEM_memcmp, NULL, data_length, difference_index));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  memai_CompareArrays

   SYNOPSIS    :  return_code = memai_CompareArrays(in_count_1, in_array_1,
							in_count_2, in_array_2, data_length, difference_index);

						unsigned int  in_count_1;

						const void   *in_array_1;

						unsigned int  in_count_2;

						const void   *in_array_2;

						size_t        data_length;

						unsigned int *difference_index;

   DESCRIPTION :  Compares two arrays to determine whether they are equal.

						Arrays are considered not equal if they have a different
						lengths (the ``in_count_1`` and ``in_count_2`` parameters).

						Array elements are considered not equal if the
						comparison function ``STR_strnicmp`` returns a non-zero
						value.

						(.) This is a case-insensitive comparison.

						(.) The maximum length of the memory area comparison is
						``data_length`` characters.

						This function compares each element of the two arrays
						up to the minimum of `in_count_1`` and ``in_count_2``.
						If the element of one array is ''NULL'' and the same
						element of the other array is not ''NULL'', the array
						with the non-NULL element will be considered to be
						greater than its correspondent,

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_count_1`` is the number of elements in the
						array ``in_array_1``.

						(.) ``in_array_1`` is the first array to be compared.

						(.) ``in_count_2`` is the number of elements in the
						array ``in_array_2``.

						(.) ``in_array_2`` is the second array to be compared.

						(.) ``data_length`` is the maximum length of the
						comparisons to be performed on the array elements of
						``in_array_1`` and ``in_array_2``.

						(.) ``difference_index`` is a pointer to an ''unsigned int''
						into which this function will place the index of the first
						difference between the two arrays.

						(-) Note that if the ``difference_index`` parameter is
						''NULL'' it will not be dereferenced by this function.

   RETURNS     :  Returns from this function are as follow:

						(.) negative if the first array compares less than
						the second array.

						(.) positive if the first array compares greater than
						the second array.

						(.) zero if the two arrays are equal both in the number
						of elements in the arrays and the memory to which elements
						in the arrays point.

   NOTES       :  The ``control_ptr`` and ``data_length`` parameters are
						present only because this function is used internally
						by other STRFUNCS list functions. They provide
						function-call compatibility with other, more generic,
						comparison functions.

   CAVEATS     :  

   SEE ALSO    :  strl_CompareArrays
						strli_CompareArrays
						strln_CompareArrays
						strlni_CompareArrays
						mema_CompareArrays
						mema_CompareArraysBasic
						memli_CompareLists

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:  memai_CompareArrays
						String Array Functions:memai_CompareArrays
						STRFUNCS:String Array Functions:memai_CompareArrays
						String Functions:See STRFUNCS

   PUBLISH XREF:  memai_CompareArrays

   PUBLISH NAME:	memai_CompareArrays

	ENTRY CLASS	:	String Array Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int memai_CompareArrays(unsigned int in_count_1, const void *in_array_1,
	unsigned int in_count_2, const void *in_array_2, size_t data_length,
	unsigned int *difference_index)
#else
int memai_CompareArrays(in_count_1, in_array_1, in_count_2, in_array_2,
	data_length, difference_index)
unsigned int  in_count_1;
const void   *in_array_1;
unsigned int  in_count_2;
const void   *in_array_2;
size_t        data_length;
unsigned int *difference_index;
#endif /* #ifndef NARGS */
{
	return(mema_CompareArraysBasic(in_count_1, in_array_1, in_count_2,
		in_array_2, MEM_memicmp, NULL, data_length, difference_index));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  mema_CompareArraysBasic

   SYNOPSIS    :  return_code = mema_CompareArraysBasic(in_count_1, in_array_1,
							in_count_2, in_array_2, STR_CMP_FUNC_TYPE compare_func,
							control_ptr, data_length, difference_index);

						unsigned int       in_count_1;

						const void        *in_array_1;

						unsigned int       in_count_2;

						const void        *in_array_2;

						STR_CMP_FUNC_TYPE  compare_func;

						void              *control_ptr;

						size_t             data_length;

						unsigned int      *difference_index;

   DESCRIPTION :  Compares two arrays to determine whether they are equal.

						Arrays are considered not equal if they have a different
						lengths (the ``in_count_1`` and ``in_count_2`` parameters).

						Array elements are considered not equal if the
						comparison function ``MEM_memcmp`` returns a non-zero
						value.

						(.) This is a case-sensitive comparison.

						(.) The maximum length of the memory area comparison is
						``data_length`` characters.

						This function compares each element of the two arrays
						up to the minimum of `in_count_1`` and ``in_count_2``.
						If the element of one array is ''NULL'' and the same
						element of the other array is not ''NULL'', the array
						with the non-NULL element will be considered to be
						greater than its correspondent,

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_count_1`` is the number of elements in the
						array ``in_array_1``.

						(.) ``in_array_1`` is the first array to be compared.

						(.) ``in_count_2`` is the number of elements in the
						array ``in_array_2``.

						(.) ``in_array_2`` is the second array to be compared.

						(.) ``compare_function`` is a pointer to the function which
						will determine element ordering. The function to which
						``compare_function`` points should be prototyped as:

						(-) int (*compare_function)(void *, const void *, const void *, size_t);

						(-) Return values from ``compare_func`` should be determined
						as follows:

						(..) negative if the first element is less than second.

						(..) positive if the first element is greater than second.

						(..) zero if the elements are equal.

						(.) ``control_ptr`` points to a arbitrary user-defined
						structure which may be used to modify the comparisons
						used to determine element ordering. It is passed unexamined
						to the comparison function ``compare_function``. If
						unnecessary, it may be a ''NULL'' pointer.

						(.) ``data_length`` is the maximum length of the
						comparisons to be performed on the array elements of
						``in_array_1`` and ``in_array_2``.

						(.) ``difference_index`` is a pointer to an ''unsigned int''
						into which this function will place the index of the first
						difference between the two arrays.

						(-) Note that if the ``difference_index`` parameter is
						''NULL'' it will not be dereferenced by this function.

   RETURNS     :  Returns from this function are as follow:

						(.) negative if the first array compares less than
						the second array.

						(.) positive if the first array compares greater than
						the second array.

						(.) zero if the two arrays are equal both in the number
						of elements in the arrays and the memory to which elements
						in the arrays point.

   NOTES       :  The ``control_ptr`` and ``data_length`` parameters are
						present only because this function is used internally
						by other STRFUNCS list functions. They provide
						function-call compatibility with other, more generic,
						comparison functions.

   CAVEATS     :  

   SEE ALSO    :  strl_CompareArrays
						strli_CompareArrays
						strln_CompareArrays
						strlni_CompareArrays
						mema_CompareArrays
						memai_CompareArrays
						meml_CompareListsBasic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:  mema_CompareArraysBasic
						String Array Functions:mema_CompareArraysBasic
						STRFUNCS:String Array Functions:mema_CompareArraysBasic
						String Functions:See STRFUNCS

   PUBLISH XREF:  mema_CompareArraysBasic

   PUBLISH NAME:	mema_CompareArraysBasic

	ENTRY CLASS	:	String Array Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int mema_CompareArraysBasic(unsigned int in_count_1, const void *in_array_1,
	unsigned int in_count_2, const void *in_array_2,
	STR_CMP_FUNC_TYPE compare_func, void *control_ptr, size_t data_length,
	unsigned int *difference_index)
#else
int mema_CompareArraysBasic(in_count_1, in_array_1, in_count_2, in_array_2,
	compare_func, control_ptr, data_length, difference_index)
unsigned int       in_count_1;
const void        *in_array_1;
unsigned int       in_count_2;
const void        *in_array_2;
STR_CMP_FUNC_TYPE  compare_func;
void              *control_ptr;
size_t             data_length;
unsigned int      *difference_index;
#endif /* #ifndef NARGS */
{
	int          cmp                  = 0;
	unsigned int tmp_difference_index = 0;

	if (difference_index != NULL)
		*difference_index = 0;

	while (in_count_1 && in_count_2) {
		in_count_1--;
		in_count_2--;
		if ((cmp = (*compare_func)(control_ptr, in_array_1,
			in_array_2, data_length)) != 0)
			break;
		in_array_1 = ((const void *) (((char *) in_array_1) + data_length));
		in_array_2 = ((const void *) (((char *) in_array_2) + data_length));
		tmp_difference_index++;
	}
	if (!cmp) {
		if (in_count_1 > in_count_2)
			cmp = 1;
		else if (in_count_1 < in_count_2)
			cmp = -1;
	}

	if (cmp && (difference_index != NULL))
		*difference_index = tmp_difference_index;

	return(cmp);
}
/*	***********************************************************************	*/

