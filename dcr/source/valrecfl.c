/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Validates a record type flag.

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
int DCR_ValidateRecSearchFlag(record_search_flag, error_text)
int   record_search_flag;
char *error_text;
{
	int return_code = DCR_SUCCESS;

	if ((record_search_flag != DCR_RECORD_FLAG_ALL) &&
		(record_search_flag != DCR_RECORD_FLAG_KEPT) &&
		(record_search_flag != DCR_RECORD_FLAG_DELETED)) {
		sprintf(error_text,
			"%s (%u) --- %s '%s' (%d), '%s' (%d), and '%s' (%d).",
			"Invalid cache record search flag specified", record_search_flag,
			"valid cache record search flags are the manifest constants",
			"DCR_RECORD_FLAG_ALL", DCR_RECORD_FLAG_ALL,
			"DCR_RECORD_FLAG_KEPT", DCR_RECORD_FLAG_KEPT,
			"DCR_RECORD_FLAG_DELETED", DCR_RECORD_FLAG_DELETED);
		return_code = DCR_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */

