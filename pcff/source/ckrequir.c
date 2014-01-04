/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Checks a configuration for the existence of
								a required names.

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

#include <stdio.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
int PCFF_CheckRequiredList(PCFF_CFG *cfg_ptr, PCFF_PARSE_SPEC *parse_spec_ptr,
	char *error_text)
{
	return(PCFF_CheckRequiredListBasic(cfg_ptr, parse_spec_ptr->required_count,
		parse_spec_ptr->required_list, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_CheckRequiredListBasic(PCFF_CFG *cfg_ptr,
	unsigned int required_count, char **required_list, char *error_text)
{
	int          return_code = PCFF_SUCCESS;
	unsigned int count_1;

	for (count_1 = 0; count_1 < required_count; count_1++) {
		if ((return_code = PCFF_CheckRequired(cfg_ptr,
			required_list[count_1], error_text)) != PCFF_SUCCESS)
			break;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
int PCFF_CheckRequired(PCFF_CFG *cfg_ptr, const char *name, char *error_text)
{
	int return_code = PCFF_SUCCESS;

	if (PCFF_FindItem(cfg_ptr, name, NULL) == NULL) {
		sprintf(error_text, "%s '%-.500s' %s.",
			"Required configuration file parameter", name,
			"not found in loaded configuration files");
		return_code = PCFF_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */


