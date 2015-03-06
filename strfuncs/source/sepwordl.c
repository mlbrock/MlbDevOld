/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Transforms a string into an array of pointers into
								strings using a white-space characters to specify
								the set of separation characters.

	Revision History	:	1992-06-27 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* 	Include necessary header files . . .											*/
/* *********************************************************************** */

#include <stdio.h>

#include "strfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

   NAME        :  sepwordl

   SYNOPSIS    :  return_code = sepwordl(in_string, string_count,
							string_list);

						unsigned int    return_code;

						const char     *in_string;

						unsigned int   *string_count;

						char         ***string_list;

   DESCRIPTION :  Transforms a string into an array of pointers to strings.
						The transformation is effected by examining the string for
						the presence of separation characters. Strings composed of
						characters not in the set of separation characters will
						become elements in the array of pointers to strings created
						by this function.

						Separation characters are specified as being white-space
						characters (as defined by the C standard library macro
						``isspace``).

						Multiple instances of the separation characters are
						swallowed by this function.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``in_string`` is the string to be transformed into an
						array of pointers to strings.

						(.) ``string_count`` points to an integer which will
						contain the number of records in the destination list
						``string_list`` if this function is successful.

						(.) ``string_list`` points to the list to which string
						segments from ``in_string`` are to be copied. Memory will
						be allocated for this list by this function.

   RETURNS     :  Returns from this function are as follow:

						(.) ''STRFUNCS_SUCCESS'' if no error occurred.

						(.) One of the non-zero STRFUNCS return codes if an error
						occurred.

   NOTES       :  To separate a string by an arbitrary set of characters,
						use the function ``sepwordx`` instead.

   CAVEATS     :  

   SEE ALSO    :  sepwordc
						sepwordc_keep
						sepwords
						sepwordx
						sepwordx_keep
						

	EXAMPLES    :

   AUTHOR      :  Michael L. Brock

   COPYRIGHT   :  Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	sepwordl
						String Splitting Functions:sepwordl
						STRFUNCS:String Splitting Functions:sepwordl
						String Functions:See STRFUNCS

	PUBLISH XREF:	sepwordl

	PUBLISH NAME:	sepwordl

	ENTRY CLASS	:	String Splitting Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int sepwordl(const char *in_string, unsigned int *string_count,
	char ***string_list)
#else
int sepwordl(in_string, string_count, string_list)
const char     *in_string;
unsigned int   *string_count;
char         ***string_list;
#endif /* #ifndef NARGS */
{
	int   return_code = STRFUNCS_SUCCESS;
	char *tmp_ptr_1;

	*string_count = 0;
	*string_list  = NULL;

	while (*in_string) {
		if (!isspace(*in_string)) {
			tmp_ptr_1 = ((char*) in_string);
			while (*tmp_ptr_1 && (!isspace(*tmp_ptr_1)))
				tmp_ptr_1++;
			if ((return_code = strln_append(string_count, string_list, in_string,
				((unsigned int) (tmp_ptr_1 - ((char *) in_string))))) != 0)
				break;
			if (!(*(in_string = tmp_ptr_1)))
				break;
		}
		in_string++;
	}

	if (return_code)
		strldel(string_count, string_list, 0, *string_count);

	return(return_code);
}
/* *********************************************************************** */

