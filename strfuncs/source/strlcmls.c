/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	STRFUNCS String and Memory Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Generic string pointer list comparison functions.

	Revision History	:	1992-03-19 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
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

   NAME        :  strl_CompareLists

   SYNOPSIS    :  return_code = strl_CompareLists(in_count_1, in_list_1,
							in_count_2, in_list_2, difference_index);

						unsigned int   in_count_1;

						char         **in_list_1;

						unsigned int   in_count_2;

						char         **in_list_2;

						unsigned int  *difference_index;

   DESCRIPTION :  Compares two arrays of pointers to strings to determine
						whether they are equal.

						Arrays are considered not equal if they have a different
						lengths (the ``in_count_1`` and ``in_count_2`` parameters).

						Array elements are considered not equal if the
						comparison function ``STR_strcmp`` returns a non-zero
						value.

						(.) This is a case-sensitive comparison.

						This function compares each element of the two arrays
						up to the minimum of `in_count_1`` and ``in_count_2``.
						If the element of one array is ''NULL'' and the same
						element of the other array is not ''NULL'', the array
						with the non-NULL element will be considered to be
						greater than its correspondent,

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_count_1`` is the number of elements in the
						array of pointers to strings ``in_list_1``.

						(.) ``in_list_1`` is the first array to be compared.

						(.) ``in_count_2`` is the number of elements in the
						array of pointers to strings ``in_list_2``.

						(.) ``in_list_2`` is the second array to be compared.

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

   SEE ALSO    :  strli_CompareLists
						strln_CompareLists
						strlni_CompareLists
						meml_CompareLists
						memli_CompareLists
						meml_CompareListsBasic
						mema_CompareLists
						memai_CompareLists
						mema_CompareListsBasic

   EXAMPLES    :

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  strl_CompareLists
						String List Functions:strl_CompareLists
						STRFUNCS:String List Functions:strl_CompareLists
						String Functions:See STRFUNCS

   PUBLISH XREF:  strl_CompareLists

   PUBLISH NAME:	strl_CompareLists

	ENTRY CLASS	:	String List Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int strl_CompareLists(unsigned int in_count_1, char **in_list_1,
	unsigned int in_count_2, char **in_list_2, unsigned int *difference_index)
#else
int strl_CompareLists(in_count_1, in_list_1, in_count_2, in_list_2,
	difference_index)
unsigned int   in_count_1;
char         **in_list_1;
unsigned int   in_count_2;
char         **in_list_2;
unsigned int  *difference_index;
#endif /* #ifndef NARGS */
{
	return(meml_CompareListsBasic(in_count_1, ((void **) in_list_1),
   	in_count_2, ((void **) in_list_2), STR_CMP_FUNC_CAST(STR_strcmp),
      NULL, 0, difference_index));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  strli_CompareLists

   SYNOPSIS    :  return_code = strli_CompareLists(in_count_1, in_list_1,
							in_count_2, in_list_2, difference_index);

						unsigned int   in_count_1;

						char         **in_list_1;

						unsigned int   in_count_2;

						char         **in_list_2;

						unsigned int  *difference_index;

   DESCRIPTION :  Compares two arrays of pointers to strings to determine
						whether they are equal.

						Arrays are considered not equal if they have a different
						lengths (the ``in_count_1`` and ``in_count_2`` parameters).

						Array elements are considered not equal if the
						comparison function ``STR_stricmp`` returns a non-zero
						value.

						(.) This is a case-insensitive comparison.

						This function compares each element of the two arrays
						up to the minimum of `in_count_1`` and ``in_count_2``.
						If the element of one array is ''NULL'' and the same
						element of the other array is not ''NULL'', the array
						with the non-NULL element will be considered to be
						greater than its correspondent,

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_count_1`` is the number of elements in the
						array of pointers to strings ``in_list_1``.

						(.) ``in_list_1`` is the first array to be compared.

						(.) ``in_count_2`` is the number of elements in the
						array of pointers to strings ``in_list_2``.

						(.) ``in_list_2`` is the second array to be compared.

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
						strln_CompareLists
						strlni_CompareLists
						meml_CompareLists
						memli_CompareLists
						meml_CompareListsBasic
						mema_CompareLists
						memai_CompareLists
						mema_CompareListsBasic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  strli_CompareLists
						String List Functions:strli_CompareLists
						STRFUNCS:String List Functions:strli_CompareLists
						String Functions:See STRFUNCS

   PUBLISH XREF:  strli_CompareLists

   PUBLISH NAME:	strli_CompareLists

	ENTRY CLASS	:	String List Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int strli_CompareLists(unsigned int in_count_1, char **in_list_1,
	unsigned int in_count_2, char **in_list_2, unsigned int *difference_index)
#else
int strli_CompareLists(in_count_1, in_list_1, in_count_2, in_list_2,
	difference_index)
unsigned int   in_count_1;
char         **in_list_1;
unsigned int   in_count_2;
char         **in_list_2;
unsigned int  *difference_index;
#endif /* #ifndef NARGS */
{
	return(meml_CompareListsBasic(in_count_1, ((void **) in_list_1),
   	in_count_2, ((void **) in_list_2), STR_CMP_FUNC_CAST(STR_stricmp),
      NULL, 0, difference_index));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  strln_CompareLists

   SYNOPSIS    :  return_code = strln_CompareLists(in_count_1, in_list_1,
							in_count_2, in_list_2, string_length, difference_index);

						unsigned int   in_count_1;

						char         **in_list_1;

						unsigned int   in_count_2;

						char         **in_list_2;

						size_t         string_length;

						unsigned int  *difference_index;

   DESCRIPTION :  Compares two arrays of pointers to strings to determine
						whether they are equal.

						Arrays are considered not equal if they have a different
						lengths (the ``in_count_1`` and ``in_count_2`` parameters).

						Array elements are considered not equal if the
						comparison function ``STR_strncmp`` returns a non-zero
						value.

						(.) This is a case-sensitive comparison.

						(.) The maximum length of the string comparison is
						``string_length`` characters.

						This function compares each element of the two arrays
						up to the minimum of `in_count_1`` and ``in_count_2``.
						If the element of one array is ''NULL'' and the same
						element of the other array is not ''NULL'', the array
						with the non-NULL element will be considered to be
						greater than its correspondent,

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_count_1`` is the number of elements in the
						array of pointers to strings ``in_list_1``.

						(.) ``in_list_1`` is the first array to be compared.

						(.) ``in_count_2`` is the number of elements in the
						array of pointers to strings ``in_list_2``.

						(.) ``in_list_2`` is the second array to be compared.

						(.) ``string_length`` is the maximum length of the
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

   SEE ALSO    :  strli_CompareLists
						strl_CompareLists
						strlni_CompareLists
						meml_CompareLists
						memli_CompareLists
						meml_CompareListsBasic
						mema_CompareLists
						memai_CompareLists
						mema_CompareListsBasic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  strln_CompareLists
						String List Functions:strln_CompareLists
						STRFUNCS:String List Functions:strln_CompareLists
						String Functions:See STRFUNCS

   PUBLISH XREF:  strln_CompareLists

   PUBLISH NAME:	strln_CompareLists

	ENTRY CLASS	:	String List Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int strln_CompareLists(unsigned int in_count_1, char **in_list_1,
	unsigned int in_count_2, char **in_list_2, size_t string_length,
	unsigned int *difference_index)
#else
int strln_CompareLists(in_count_1, in_list_1, in_count_2, in_list_2,
	string_length, difference_index)
unsigned int   in_count_1;
char         **in_list_1;
unsigned int   in_count_2;
char         **in_list_2;
size_t         string_length;
unsigned int  *difference_index;
#endif /* #ifndef NARGS */
{
	return(meml_CompareListsBasic(in_count_1, ((void **) in_list_1),
   	in_count_2, ((void **) in_list_2), STR_CMP_FUNC_CAST(STR_strncmp),
      NULL, string_length, difference_index));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* BOH

   NAME        :  strlni_CompareLists

   SYNOPSIS    :  return_code = strlni_CompareLists(in_count_1, in_list_1,
							in_count_2, in_list_2, string_length, difference_index);

						unsigned int   in_count_1;

						char         **in_list_1;

						unsigned int   in_count_2;

						char         **in_list_2;

						size_t         string_length;

						unsigned int  *difference_index;

   DESCRIPTION :  Compares two arrays of pointers to strings to determine
						whether they are equal.

						Arrays are considered not equal if they have a different
						lengths (the ``in_count_1`` and ``in_count_2`` parameters).

						Array elements are considered not equal if the
						comparison function ``STR_strnicmp`` returns a non-zero
						value.

						(.) This is a case-insensitive comparison.

						(.) The maximum length of the string comparison is
						``string_length`` characters.

						This function compares each element of the two arrays
						up to the minimum of `in_count_1`` and ``in_count_2``.
						If the element of one array is ''NULL'' and the same
						element of the other array is not ''NULL'', the array
						with the non-NULL element will be considered to be
						greater than its correspondent,

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``in_count_1`` is the number of elements in the
						array of pointers to strings ``in_list_1``.

						(.) ``in_list_1`` is the first array to be compared.

						(.) ``in_count_2`` is the number of elements in the
						array of pointers to strings ``in_list_2``.

						(.) ``in_list_2`` is the second array to be compared.

						(.) ``string_length`` is the maximum length of the
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

   SEE ALSO    :  strli_CompareLists
						strl_CompareLists
						strln_CompareLists
						meml_CompareLists
						memli_CompareLists
						meml_CompareListsBasic

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2018 Michael L. Brock

   OUTPUT INDEX:  strlni_CompareLists
						String List Functions:strlni_CompareLists
						STRFUNCS:String List Functions:strlni_CompareLists
						String Functions:See STRFUNCS

   PUBLISH XREF:  strlni_CompareLists

   PUBLISH NAME:	strlni_CompareLists

	ENTRY CLASS	:	String List Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int strlni_CompareLists(unsigned int in_count_1, char **in_list_1,
	unsigned int in_count_2, char **in_list_2, size_t string_length,
	unsigned int *difference_index)
#else
int strlni_CompareLists(in_count_1, in_list_1, in_count_2, in_list_2,
	string_length, difference_index)
unsigned int   in_count_1;
char         **in_list_1;
unsigned int   in_count_2;
char         **in_list_2;
size_t         string_length;
unsigned int  *difference_index;
#endif /* #ifndef NARGS */
{
	return(meml_CompareListsBasic(in_count_1, ((void **) in_list_1),
   	in_count_2, ((void **) in_list_2), STR_CMP_FUNC_CAST(STR_strnicmp),
      NULL, string_length, difference_index));
}
/*	***********************************************************************	*/

