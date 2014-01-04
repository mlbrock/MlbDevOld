/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Validates a compare type.

	Revision History	:	1994-07-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
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

#include "dcr.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2014 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DCR_ValidateCompareType(compare_type, error_text)
unsigned int  compare_type;
char         *error_text;
{
	int return_code = DCR_SUCCESS;

	if (compare_type >= DCR_COMPARE_TYPE_COUNT) {
		sprintf(error_text, "%s (%u) --- %s %u, inclusive.",
			"Invalid cache compare type specified", compare_type,
			"valid cache compare types range from 0 to",
			DCR_COMPARE_TYPE_COUNT - 1);
		return_code = DCR_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */

