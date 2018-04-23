/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Fixes the names and values in a configuration by
								removing delimiters.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
int PCFF_FixDelimiters(PCFF_CFG *cfg_ptr, PCFF_PARSE_SPEC *parse_spec_ptr,
	char *error_text)
{
	return(PCFF_FixDelimitersBasic(cfg_ptr, parse_spec_ptr->name_left,
		parse_spec_ptr->name_right, parse_spec_ptr->value_left,
		parse_spec_ptr->value_right, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_FixDelimitersBasic(PCFF_CFG *cfg_ptr, const char *name_left,
	const char *name_right, const char *value_left, const char *value_right,
	char *error_text)
{
	int           return_code = PCFF_SUCCESS;
	unsigned int  count_1;
	unsigned int  count_2;
	unsigned int  name_length;
	unsigned int  value_length;
	PCFF_ITEM    *item_ptr;
	PCFF_SRC     *src_ptr;

	if ((return_code = PCFF_CheckDelimitersBasic(cfg_ptr, name_left,
		name_right, value_left, value_right, error_text)) == PCFF_SUCCESS) {
		name_left    = (name_left  != NULL) ? name_left  : "";
		name_right   = (name_right != NULL) ? name_right : "";
		value_left   = (value_left != NULL) ? value_left : "";
		value_right  = (value_right!= NULL) ? value_right: "";
		name_length  = strlen(name_left);
		value_length = strlen(value_left);
		for (count_1 = 0, item_ptr = cfg_ptr->item_list;
			count_1 < cfg_ptr->item_count; count_1++, item_ptr++) {
			nstrcpy(item_ptr->name, item_ptr->name + 1,
				strlen(item_ptr->name) - 2);
			nstrcpy(item_ptr->value, item_ptr->value + 1,
				strlen(item_ptr->value) - 2);
			for (count_2 = 0, src_ptr = item_ptr->src_list;
				count_2 < item_ptr->src_count; count_2++, src_ptr++)
				nstrcpy(src_ptr->value, src_ptr->value + 1,
					strlen(src_ptr->value) - 2);
		}
	}

	return(return_code);
}
/* *********************************************************************** */


