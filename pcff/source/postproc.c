/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Handles post-processing of a loaded configuration.

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
int PCFF_PostProcess(PCFF_CFG *cfg_ptr, PCFF_PARSE_SPEC *parse_spec_ptr,
	char *error_text)
{
	return(PCFF_PostProcessBasic(cfg_ptr, parse_spec_ptr->flags,
		parse_spec_ptr->name_left, parse_spec_ptr->name_right,
		parse_spec_ptr->value_left, parse_spec_ptr->value_right,
		parse_spec_ptr->required_count, parse_spec_ptr->required_list,
		parse_spec_ptr->optional_count, parse_spec_ptr->optional_list,
		error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_PostProcessBasic(PCFF_CFG *cfg_ptr, PCFF_FLAG flags,
	const char *name_left, const char *name_right, const char *value_left,
	const char *value_right, unsigned int required_count, char **required_list,
	unsigned int optional_count, char **optional_list, char *error_text)
{
	int      return_code;
	PCFF_CFG cfg_data;

	if ((return_code = PCFF_CopyCfg(cfg_ptr, &cfg_data, error_text)) ==
		PCFF_SUCCESS) {
		PCFF_FlattenItems(&cfg_data);
		if ((return_code = PCFF_FixDelimitersBasic(&cfg_data, name_left,
			name_right, value_left, value_right, error_text)) ==
			PCFF_SUCCESS) {
			if (((flags & PCFF_FLAG_UNKNOWN_OK) ||
				((return_code = PCFF_CheckUnknownListBasic(&cfg_data,
				required_count, required_list, optional_count, optional_list,
				error_text)) == PCFF_SUCCESS)) &&
				((flags & PCFF_FLAG_NO_REQUIRE) ||
				((return_code = PCFF_CheckRequiredListBasic(&cfg_data,
				required_count, required_list, error_text)) == PCFF_SUCCESS))) {
				PCFF_FreeCfg(cfg_ptr);
				*cfg_ptr = cfg_data;
				PCFF_InitCfg(&cfg_data);
			}
		}
		PCFF_FreeCfg(&cfg_data);
	}

	return(return_code);
}
/* *********************************************************************** */


