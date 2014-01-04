/* *********************************************************************** */
/* *********************************************************************** */
/*	STRFUNCS String and Memory Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Finds the shortest element in a list of strings.

	Revision History	:	1986-07-10 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1986 - 2014.
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

/*	***********************************************************************	*/
unsigned int STR_LIST_GetElementMaxLength(unsigned int string_count,
	char **string_list, unsigned int *max_index)
{
	unsigned int max_length = 0;
	unsigned int tmp_index;
	unsigned int count_1;
	unsigned int this_length;

	max_index  = (max_index != NULL) ? max_index : &tmp_index;
	*max_index = 0;

	for (count_1 = 0; count_1 < string_count; count_1++, string_list++) {
		this_length = (*string_list != NULL) ? strlen(*string_list) : 0;
		if (max_length < this_length) {
			max_length = this_length;
			*max_index = count_1;
		}
	}

	return(max_length);
}
/*	***********************************************************************	*/

