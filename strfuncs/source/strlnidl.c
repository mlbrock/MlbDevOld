/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a case-insensitive binary search on an array
								of pointers to strings to delete a string.

	Revision History	:	1991-10-10 --- Creation
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

   NAME        :  strlni_delete

   SYNOPSIS    :  return_code = strlni_delete(string_count, string_list,
							key_string, string_length, found_index);

						int             return_code;

						unsigned int   *string_count;

						char         ***string_list;

						const char     *key_string;

						size_t          string_length;

						unsigned int   *found_index;

   DESCRIPTION :  Performs a case-insensitive binary search in the array
						``string_list`` for the element ``key_string`` using a
						comparison function equivalent to the C standard library
						function ``strnicmp``.

						If ``key_string`` is found, its corresponding element in
						the array is deleted and its old index in ``string_list``
						is placed into the unsigned int to which ``found_index``
						points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` points to the number of elements in
						the array of pointers ``string_list``.

						(.) ``string_list`` points to the array of pointers in
						which the search for ``key_string`` will be performed.

						(.) ``key_string`` points to the data for which the
						deletion is to occur.

						(.) ``string_length`` is the maximum number of characters
						to be compared by the binary search routine.

						(.) ``found_index`` points to an unsigned integer into
						which the index of ``key_string`` in ``string_list`` will
						be placed, if found.

						(-) Note, however, that ``found_index`` will not be
						de-referenced if it is ''NULL''.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_FAILURE'' if an error occurs.

						(.) ''STRFUNCS_ITEM_FOUND'' if ``key_string`` is found in
						the array ``string_list``. In this case, the element is
						deleted from the array and the unsigned int to which the
						``found_index`` parameter points will be set to its former
						index.

						(.) ''STRFUNCS_ITEM_NOT_FOUND'' if ``key_string`` is not
						found in the array ``string_list``. In this case, the
						unsigned int to which the ``found_index`` parameter
						points will be set to the index of ``key_string`` did
						it reside in the array.

   NOTES       :  If there are multiple elements in ``string_list`` which
						compare equal to ``key_string``, the first of them will be
						deleted by this function.

						It is important to remember that the index returned in
						``found_index`` is no longer valid after a successful
						deletion.

   CAVEATS     :  The results of invoking this function with a ``string_list``
						not in sorted order are undefined.

   SEE ALSO    :  strl_delete
						strln_delete
						strli_delete
						STR_LIST_bsearch
						strl_find
						strl_search
						STR_strcmp

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  strlni_delete
						String List Functions:strlni_delete
						STRFUNCS:String List Functions:strlni_delete
						String Functions:See STRFUNCS

   PUBLISH XREF:  strlni_delete

   PUBLISH NAME:	strlni_delete

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int strlni_delete(unsigned int *string_count, char ***string_list,
	const char *key_string, size_t string_length, unsigned int *found_index)
#else
int strlni_delete(string_count, string_list, key_string, string_length,
	found_index)
unsigned int   *string_count;
char         ***string_list;
const char     *key_string;
size_t          string_length;
unsigned int   *found_index;
#endif /* #ifndef NARGS */
{
#ifndef NARGS
	return(STR_LIST_delete(string_count, ((void ***) string_list),
		((void *) key_string), string_length, found_index,
		((int (*)(void *, const void *, const void *, size_t)) STR_strnicmp)));
#else
	return(STR_LIST_delete(*string_count, ((void **) *string_list),
		((void *) key_string), string_length, found_index, STR_strnicmp));
#endif /* #ifndef NARGS */
}
/* *********************************************************************** */

