/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Generic memory area pointer list comparison
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

   NAME        :  meml_CompareLists

   SYNOPSIS    :  return_code = meml_CompareLists(in_count_1, in_list_1,
							in_count_2, in_list_2, data_length, difference_index);

						unsigned int   in_count_1;

						void         **in_list_1;

						unsigned int   in_count_2;

						void         **in_list_2;

						size_t         data_length;

						unsigned int  *difference_index;

   DESCRIPTION :  Compares two arrays of pointers to memory areas to determine
						whether they are equal.

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
						array of pointers to memory areas ``in_list_1``.

						(.) ``in_list_1`` is the first array to be compared.

						(.) ``in_count_2`` is the number of elements in the
						array of pointers to memory areas ``in_list_2``.

						(.) ``in_list_2`` is the second array to be compared.

						(.) ``data_length`` is the maximum length of the
						comparisons to be performed on the array elements of
						``in_list_1`` and ``in_list_2``.

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

   SEE ALSO    :  strl_CompareLists
						strli_CompareLists
						strln_CompareLists
						strlni_CompareLists
						memli_CompareLists
						meml_CompareListsBasic
						mema_CompareLists
						memai_CompareLists
						mema_CompareListsBasic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:  meml_CompareLists
						String List Functions:meml_CompareLists
						STRFUNCS:String List Functions:meml_CompareLists
						String Functions:See STRFUNCS

   PUBLISH XREF:  meml_CompareLists

   PUBLISH NAME:	meml_CompareLists

	ENTRY CLASS	:	String List Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int meml_CompareLists(unsigned int in_count_1, void **in_list_1,
	unsigned int in_count_2, void **in_list_2, size_t data_length,
	unsigned int *difference_index)
#else
int meml_CompareLists(in_count_1, in_list_1, in_count_2, in_list_2,
	data_length, difference_index)
unsigned int   in_count_1;
void         **in_list_1;
unsigned int   in_count_2;
void         **in_list_2;
size_t         data_length;
unsigned int  *difference_index;
#endif /* #ifndef NARGS */
{
	return(meml_CompareListsBasic(in_count_1, in_list_1, in_count_2,
		in_list_2, MEM_memcmp, NULL, data_length, difference_index));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  memli_CompareLists

   SYNOPSIS    :  return_code = memli_CompareLists(in_count_1, in_list_1,
							in_count_2, in_list_2, data_length, difference_index);

						unsigned int   in_count_1;

						void         **in_list_1;

						unsigned int   in_count_2;

						void         **in_list_2;

						size_t         data_length;

						unsigned int  *difference_index;

   DESCRIPTION :  Compares two arrays of pointers to memory areas to determine
						whether they are equal.

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
						array of pointers to memory areas ``in_list_1``.

						(.) ``in_list_1`` is the first array to be compared.

						(.) ``in_count_2`` is the number of elements in the
						array of pointers to memory areas ``in_list_2``.

						(.) ``in_list_2`` is the second array to be compared.

						(.) ``data_length`` is the maximum length of the
						comparisons to be performed on the array elements of
						``in_list_1`` and ``in_list_2``.

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

   SEE ALSO    :  strl_CompareLists
						strli_CompareLists
						strln_CompareLists
						strlni_CompareLists
						meml_CompareLists
						meml_CompareListsBasic
						mema_CompareLists
						memai_CompareLists
						mema_CompareListsBasic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:  memli_CompareLists
						String List Functions:memli_CompareLists
						STRFUNCS:String List Functions:memli_CompareLists
						String Functions:See STRFUNCS

   PUBLISH XREF:  memli_CompareLists

   PUBLISH NAME:	memli_CompareLists

	ENTRY CLASS	:	String List Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int memli_CompareLists(unsigned int in_count_1, void **in_list_1,
	unsigned int in_count_2, void **in_list_2, size_t data_length,
	unsigned int *difference_index)
#else
int memli_CompareLists(in_count_1, in_list_1, in_count_2, in_list_2,
	data_length, difference_index)
unsigned int   in_count_1;
void         **in_list_1;
unsigned int   in_count_2;
void         **in_list_2;
size_t         data_length;
unsigned int  *difference_index;
#endif /* #ifndef NARGS */
{
	return(meml_CompareListsBasic(in_count_1, in_list_1, in_count_2,
		in_list_2, MEM_memicmp, NULL, data_length, difference_index));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  meml_CompareListsBasic

   SYNOPSIS    :  return_code = meml_CompareListsBasic(in_count_1, in_list_1,
							in_count_2, in_list_2, STR_CMP_FUNC_TYPE compare_func,
							control_ptr, data_length, difference_index);

						unsigned int        in_count_1;

						void              **in_list_1;

						unsigned int        in_count_2;

						void              **in_list_2;

						STR_CMP_FUNC_TYPE   compare_func;

						void               *control_ptr;

						size_t              data_length;

						unsigned int       *difference_index;

   DESCRIPTION :  Compares two arrays of pointers to memory areas to determine
						whether they are equal.

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
						array of pointers to memory areas ``in_list_1``.

						(.) ``in_list_1`` is the first array to be compared.

						(.) ``in_count_2`` is the number of elements in the
						array of pointers to memory areas ``in_list_2``.

						(.) ``in_list_2`` is the second array to be compared.

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
						``in_list_1`` and ``in_list_2``.

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

   SEE ALSO    :  strl_CompareLists
						strli_CompareLists
						strln_CompareLists
						strlni_CompareLists
						meml_CompareLists
						memli_CompareLists
						mema_CompareLists
						memai_CompareLists
						mema_CompareListsBasic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

   OUTPUT INDEX:  meml_CompareListsBasic
						String List Functions:meml_CompareListsBasic
						STRFUNCS:String List Functions:meml_CompareListsBasic
						String Functions:See STRFUNCS

   PUBLISH XREF:  meml_CompareListsBasic

   PUBLISH NAME:	meml_CompareListsBasic

	ENTRY CLASS	:	String List Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int meml_CompareListsBasic(unsigned int in_count_1, void **in_list_1,
	unsigned int in_count_2, void **in_list_2, STR_CMP_FUNC_TYPE compare_func,
	void *control_ptr, size_t data_length, unsigned int *difference_index)
#else
int meml_CompareListsBasic(in_count_1, in_list_1, in_count_2, in_list_2,
	compare_func, control_ptr, data_length, difference_index)
unsigned int        in_count_1;
void              **in_list_1;
unsigned int        in_count_2;
void              **in_list_2;
STR_CMP_FUNC_TYPE   compare_func;
void               *control_ptr;
size_t              data_length;
unsigned int       *difference_index;
#endif /* #ifndef NARGS */
{
	int          cmp                  = 0;
	unsigned int tmp_difference_index = 0;

	if (difference_index != NULL)
		*difference_index = 0;

	while (in_count_1 && in_count_2) {
		in_count_1--;
		in_count_2--;
		if ((*in_list_1 == NULL) && (*in_list_2 == NULL))
			break;
		else if ((*in_list_1 != NULL) && (*in_list_2 == NULL)) {
			cmp = 1;
			break;
		}
		else if ((*in_list_1 == NULL) && (*in_list_2 != NULL)) {
			cmp = -1;
			break;
		}
		else if ((cmp = (*compare_func)(control_ptr, *in_list_1,
			*in_list_2, data_length)) != 0)
			break;
		in_list_1++;
		in_list_2++;
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

