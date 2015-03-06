/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a configuration for unknown names.

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

#include <stdio.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
int PCFF_CheckUnknownList(const PCFF_CFG *cfg_ptr,
	PCFF_PARSE_SPEC *parse_spec_ptr, char *error_text)
{
	return(PCFF_CheckUnknownListBasic(cfg_ptr, parse_spec_ptr->required_count,
		parse_spec_ptr->required_list, parse_spec_ptr->optional_count,
		parse_spec_ptr->optional_list, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_CheckUnknownListBasic(const PCFF_CFG *cfg_ptr,
	unsigned int required_count, char **required_list,
	unsigned int optional_count, char **optional_list, char *error_text)
{
	int      return_code = PCFF_SUCCESS;
	PCFF_CFG cfg_data;

	if ((return_code = PCFF_GetUnknownListBasic(cfg_ptr, required_count,
		required_list, optional_count, optional_list, &cfg_data, error_text)) ==
		PCFF_SUCCESS) {
		if (cfg_data.item_count) {
			PCFF_SortCfgByOrder(&cfg_data);
			sprintf(error_text,
				"There %s %u %s %s %s %s %s: %s '%-.250s' %s '%-.250s'.",
				(cfg_data.item_count == 1) ? "is" : "are", cfg_data.item_count,
				(cfg_data.item_count == 1) ? "item" : "items", "in the loaded",
				"configuration files which",
				(cfg_data.item_count == 1) ? "is" : "are",
				"neither required nor optional",
				"The first loaded has the name", cfg_data.item_list->name,
				"and the value", cfg_data.item_list->value);
			return_code = PCFF_FAILURE;
		}
		PCFF_FreeCfg(&cfg_data);
	}

	return(return_code);
}
/* *********************************************************************** */


