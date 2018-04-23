/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a binary search on an array of pointers to
								strings.

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

   NAME        :  strln_find

   SYNOPSIS    :  return_code = strln_find(string_count, string_list,
							key_string, string_length, found_index);

						int            return_code;

						unsigned int   string_count;

						char         **string_list;

						const char    *key_string;

						size_t         string_length;

						unsigned int  *found_index;

   DESCRIPTION :  Performs a binary search in the array ``string_list`` for
						the element ``key_string`` using a comparison function
						equivalent to the C standard library function ``strncmp``.

						If ``key_string`` is found, its index in ``string_list``
						is placed into the ``unsigned int`` to which ``found_index``
						points.

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``string_count`` is the number of elements in the array
						of pointers ``string_list``.

						(.) ``string_list`` is the array of pointers in which the
						search for ``data_key`` will be performed.

						(.) ``key_string`` points to the data for which the search
						is to occur.

						(.) ``string_length`` is the maximum number of characters
						to be compared by the binary search routine.

						(.) ``found_index`` points to an unsigned integer into
						which the index of ``key_string`` in ``string_list`` will
						be placed, if found.

						(-) Note, however, that ``found_index`` will not be
						de-referenced if it is ''NULL''.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_FAILURE'' if an error occurs.

						(.) ''STRFUNCS_ITEM_FOUND'' if ``string_key`` is found in
						the array ``string_list``. In this case, the unsigned int
						to which the ``found_index`` parameter points will be set
						to the index of that element in the array.

						(.) ''STRFUNCS_ITEM_NOT_FOUND'' if ``key_string`` is not
						found in the array ``string_list``. In this case, the
						unsigned int to which the ``found_index`` parameter
						points will be set to the index of the array into which
						``key_string`` should be inserted.

   NOTES       :  If there are multiple elements in ``data_list`` which
						compare equal to ``key_data``, the first of them will be
						located by this function.

   CAVEATS     :  The results of invoking this function with an ``data_list``
						not in sorted order are undefined.

   SEE ALSO    :  strl_find
						strli_find
						strlni_find
						STR_LIST_bsearch
						strl_search
						strl_delete
						STR_strcmp

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  strln_find
						String List Functions:strln_find
						STRFUNCS:String List Functions:strln_find
						String Functions:See STRFUNCS

   PUBLISH XREF:  strln_find

   PUBLISH NAME:	strln_find

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int strln_find(unsigned int string_count, char **string_list,
	const char *key_string, size_t string_length, unsigned int *found_index)
#else
int strln_find(string_count, string_list, key_string, string_length,
	found_index)
unsigned int   string_count;
char         **string_list;
const char    *key_string;
size_t         string_length;
unsigned int  *found_index;
#endif /* #ifndef NARGS */
{
#ifndef NARGS
	return(STR_LIST_find(string_count, ((void **) string_list),
		key_string, string_length, found_index,
		((int (*)(void *, const void *, const void *, size_t)) STR_strncmp)));
#else
	return(STR_LIST_find(string_count, ((void **) string_list),
		key_string, string_length, found_index, STR_strncmp));
#endif /* #ifndef NARGS */
}
/* *********************************************************************** */

