/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the configuration items loaded which are
								neither required nor optional.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "pcffi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
int PCFF_GetUnknownList(const PCFF_CFG *in_cfg_ptr,
	PCFF_PARSE_SPEC *parse_spec_ptr, PCFF_CFG *out_cfg_ptr, char *error_text)
{
	return(PCFF_GetUnknownListBasic(in_cfg_ptr, parse_spec_ptr->required_count,
		parse_spec_ptr->required_list, parse_spec_ptr->optional_count,
		parse_spec_ptr->optional_list, out_cfg_ptr, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_GetUnknownListBasic(const PCFF_CFG *in_cfg_ptr,
	unsigned int required_count, char **required_list,
	unsigned int optional_count, char **optional_list, PCFF_CFG *out_cfg_ptr,
	char *error_text)
{
	int          return_code = PCFF_SUCCESS;
	unsigned int count_1;
	unsigned int found_index;
	PCFF_CFG     cfg_data;

	if ((return_code = PCFF_CopyCfg(in_cfg_ptr, &cfg_data,
		error_text)) == PCFF_SUCCESS) {
		PCFF_SortCfgByName(&cfg_data);
		for (count_1 = 0; count_1 < required_count; count_1++) {
			if (PCFF_FindItem(&cfg_data, required_list[count_1],
				&found_index) != NULL) {
				if ((return_code = PCFF_DeleteItem(&cfg_data, found_index,
					error_text)) != PCFF_SUCCESS)
					break;
			}
		}
		if (return_code == PCFF_SUCCESS) {
			for (count_1 = 0; count_1 < optional_count; count_1++) {
				if (PCFF_FindItem(&cfg_data, optional_list[count_1],
					&found_index) != NULL) {
					if ((return_code = PCFF_DeleteItem(&cfg_data, found_index,
						error_text)) != PCFF_SUCCESS)
						break;
				}
			}
		}
		if (return_code == PCFF_SUCCESS) {
			if (in_cfg_ptr == out_cfg_ptr)
				PCFF_FreeCfg(out_cfg_ptr);
			*out_cfg_ptr = cfg_data;
		}
		else
			PCFF_FreeCfg(&cfg_data);
	}

	return(return_code);
}
/* *********************************************************************** */


