/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Adds an array of pointers to strings to the end of
								another array of pointers to strings.

	Revision History	:	1991-09-13 --- Creation
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

#include <string.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  strln_add

   SYNOPSIS    :  return_code = strln_add(from_string_count,
							from_string_list, to_string_count, to_string_list,
							string_length);

						int             return_code;

						unsigned int    from_string_count;

						char          **from_string_list;

						unsigned int   *to_string_count;

						char         ***to_string_list;

						size_t          string_length;

   DESCRIPTION :  Adds the strings in the list ``from_string_list`` to the
						list ``to_string_list``. Strings copied from
						``from_string_list`` will be truncated to a maximum length
						of ``string_length`` bytes (excluding the terminating ASCII
						NUL byte).

   PARAMETERS  :  Parameters to this function are as follow:

						(.) ``from_string_count`` is the number of strings in the
						source list ``from_string_list``.

						(.) ``from_string_list`` is the list of strings to be
						added.

						(.) ``to_string_count`` points to the number of strings
						already in the destination list ``to_string_list``.

						(.) ``to_string_list`` points to the destination list to
						which strings from ``from_string_list`` are to be added.

						(.) ``string_length`` is the maximum length which will be
						copied of any string from ``from_string_list`` to
						``to_string_list``.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  

   CAVEATS     :  

   SEE ALSO    :  strl_add
						strln_append
						strl_copy
						strln_insert
						strl_remove
						meml_add
						mema_add

   EXAMPLES    :  

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:  strln_add
						String List Functions:strln_add
						STRFUNCS:String List Functions:strln_add
						String Functions:See STRFUNCS

   PUBLISH XREF:  strln_add

   PUBLISH NAME:	strln_add

	ENTRY CLASS	:	String List Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int strln_add(unsigned int from_string_count, char **from_string_list,
	unsigned int *to_string_count, char ***to_string_list, size_t string_length)
#else
int strln_add(from_string_count, from_string_list, to_string_count,
	to_string_list, string_length)
unsigned int    from_string_count;
char          **from_string_list;
unsigned int   *to_string_count;
char         ***to_string_list;
size_t          string_length;
#endif /* #ifndef NARGS */
{
	int          return_code = STRFUNCS_SUCCESS;
	unsigned int old_to_count;
	unsigned int count_1;

	if (string_length <= 0)
		return_code = STRFUNCS_FAILURE;
	else {
		old_to_count = *to_string_count;
		for (count_1 = 0; count_1 < from_string_count; count_1++) {
			if ((return_code = strln_append(to_string_count, to_string_list,
				from_string_list[count_1], string_length)) != STRFUNCS_SUCCESS) {
				if (count_1)
					strl_remove(to_string_count, to_string_list,	old_to_count,
						count_1);
				break;
			}
		}
	}

	return(return_code);
}
/* *********************************************************************** */

