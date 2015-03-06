/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the longest of string values among the
								items in a configuration.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2015.
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
unsigned int PCFF_GetLongestName(const PCFF_CFG *cfg_ptr)
{
	unsigned int max_len = 0;
	unsigned int tmp_len;
	unsigned int count_1;

	for (count_1 = 0; count_1 < cfg_ptr->item_count; count_1++)
		max_len =
			(max_len >= (tmp_len = strlen(cfg_ptr->item_list[count_1].name))) ?
			max_len : tmp_len;

	return(max_len);
}
/* *********************************************************************** */

/* *********************************************************************** */
unsigned int PCFF_GetLongestValue(const PCFF_CFG *cfg_ptr)
{
	unsigned int max_len = 0;
	unsigned int tmp_len;
	unsigned int count_1;

	for (count_1 = 0; count_1 < cfg_ptr->item_count; count_1++)
		max_len =
			(max_len >= (tmp_len = strlen(cfg_ptr->item_list[count_1].value))) ?
			max_len : tmp_len;

	return(max_len);
}
/* *********************************************************************** */

/* *********************************************************************** */
unsigned int PCFF_GetLongestLineNumber(const PCFF_CFG *cfg_ptr)
{
	unsigned int max_len = 0;
	unsigned int tmp_len;
	unsigned int count_1;
	char         buffer[STR_VAL2STR_MAX_LEN + 1];
	

	for (count_1 = 0; count_1 < cfg_ptr->item_count; count_1++)
		max_len = (max_len >=
			(tmp_len = cfg_ptr->item_list[count_1].src_list->line_number)) ?
			max_len : tmp_len;

	return(strlen(val2str(((unsigned long) max_len), 0, 10, NULL, buffer)));
}
/* *********************************************************************** */

/* *********************************************************************** */
unsigned int PCFF_GetLongestFileName(const PCFF_CFG *cfg_ptr)
{
	unsigned int max_len = 0;
	unsigned int tmp_len;
	unsigned int count_1;
	unsigned int count_2;

	for (count_1 = 0; count_1 < cfg_ptr->item_count; count_1++) {
		for (count_2 = 0; count_2 < cfg_ptr->item_list[count_1].src_count;
			count_2++)
			max_len = (max_len >= (tmp_len =
				strlen(cfg_ptr->item_list[count_1].src_list[count_2].file_name))) ?
				max_len : tmp_len;
	}

	return(max_len);
}
/* *********************************************************************** */

/* *********************************************************************** */
unsigned int PCFF_GetLongestMemberName(const PCFF_PARAM_SPEC *param_spec_ptr)
{
	unsigned int max_len = 0;
	unsigned int tmp_len;
	unsigned int count_1;

	for (count_1 = 0; count_1 < param_spec_ptr->param_count; count_1++) {
		max_len = (max_len >= (tmp_len =
			strlen(param_spec_ptr->param_list[count_1].member_name))) ?
			max_len : tmp_len;
	}

	return(max_len);
}
/* *********************************************************************** */


