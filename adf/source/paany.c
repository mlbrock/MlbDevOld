/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1997-04-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1997 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PARSE_Any(SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, void *parent_ptr, char *error_text)
#else
int ADF_PARSE_Any(context_ptr, spec_ptr, parse_ptr, parent_ptr, error_text)
SPF_CONTEXT     *context_ptr;
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
void            *parent_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code;
	ADF_CONTROL *adf_control_ptr;

	adf_control_ptr = ((ADF_CONTROL *) context_ptr->user_data_ptr);

	switch (spec_ptr->type) {
		case ADF_PARSE_TYPE_AREA_NAME		:
			return_code = ADF_PARSE_AreaName(spec_ptr, parse_ptr,
				((unsigned int *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case ADF_PARSE_TYPE_PATTERN		:
			return_code = ADF_PARSE_Pattern(spec_ptr, parse_ptr,
				((ADF_PATTERN *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				error_text);
			break;
		case ADF_PARSE_TYPE_SECTION		:
			return_code = ADF_PARSE_Section(context_ptr, spec_ptr, parse_ptr,
				parent_ptr,
				((unsigned int *) (((char *) parent_ptr) + spec_ptr->offset_1)),
				((ADF_SECTION **) (((char *) parent_ptr) + spec_ptr->offset_2)),
				error_text);
			break;
		case ADF_PARSE_TYPE_DOMAIN			:
			return_code = ADF_PARSE_Domain(context_ptr, spec_ptr, parse_ptr,
				parent_ptr, &adf_control_ptr->domain_count,
				&adf_control_ptr->domain_list, error_text);
			break;
		default									:
			return_code = SPF_PARSE_Basic(context_ptr, spec_ptr, parse_ptr,
				parent_ptr, error_text);
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

