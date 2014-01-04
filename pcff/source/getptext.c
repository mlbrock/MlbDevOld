/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Get descriptive text for a 'PCFF_PARAM' structure.

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
#include <string.h>

#include <strfuncs.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *PCFF_GetParamText(const PCFF_PARAM *param_ptr, char *param_text)
{
	return(chrcat(strcat(strcat(strcat(strcpy(param_text, "parameter name '"),
		param_ptr->param_name), "', member name '"), param_ptr->member_name),
		'\''));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *PCFF_GetParamTextIndex(const PCFF_PARAM *param_ptr,
	unsigned int param_index, char *param_text)
{
	sprintf(param_text, "parameter index %u, ", param_index);

	return(PCFF_GetParamText(param_ptr, param_text + strlen(param_text)));
}
/*	***********************************************************************	*/


