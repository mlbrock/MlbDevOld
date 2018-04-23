/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Attempts to find the specified specification item.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include <strfuncs.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_FIND_Spec(const SPF_SPEC *spec_ptr, unsigned int parse_count,
	const SPF_PARSE *parse_list, unsigned int *found_index)
#else
int SPF_FIND_Spec(spec_ptr, parse_count, parse_list, found_index)
const SPF_SPEC  *spec_ptr;
unsigned int     parse_count;
const SPF_PARSE *parse_list;
unsigned int    *found_index;
#endif /* #ifndef NARGS */
{
	int          return_code;
	unsigned int count_1 = 0;

	if ((return_code = SPF_FIND_SpecName(spec_ptr->name, parse_count,
		parse_list, found_index)) != STRFUNCS_ITEM_FOUND) {
		while ((count_1 < SPF_MAX_SPEC_ALIASES) &&
			spec_ptr->aliases[count_1][0] &&
			(return_code != STRFUNCS_ITEM_FOUND))
			return_code = SPF_FIND_SpecName(spec_ptr->aliases[count_1++],
				parse_count, parse_list, found_index);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_FIND_SpecName(const char *spec_name, unsigned int parse_count,
	const SPF_PARSE *parse_list, unsigned int *found_index)
#else
int SPF_FIND_SpecName(spec_name, parse_count, parse_list, found_index)
const char      *spec_name;
unsigned int     parse_count;
const SPF_PARSE *parse_list;
unsigned int    *found_index;
#endif /* #ifndef NARGS */
{
	int          return_code = STRFUNCS_ITEM_NOT_FOUND;
	unsigned int count_1;
	unsigned int data_length;

	data_length = strlen(spec_name);

	for (count_1 = 0; count_1 < parse_count; count_1++) {
		if ((data_length < parse_list[count_1].length)                  &&
			(!memicmp(spec_name, parse_list[count_1].text, data_length)) &&
			(parse_list[count_1].text[data_length] == '(')) {
			if (found_index != NULL)
				*found_index = count_1;
			return_code = STRFUNCS_ITEM_FOUND;
			break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

