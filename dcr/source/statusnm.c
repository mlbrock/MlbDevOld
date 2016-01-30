/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1994-03-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

static char *DCR_StatusNameList[DCR_STATUS_COUNT] = {
	"ready",
	"building",
	"indexing",
	"adding",
	"re-sizing"
};

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	The buffer ``cache_status_name`` into which the
						string representing the cache access type will be
						copied by this function should be at least the length of
						the manifest constant ''DCR_MAX_STATUS_NAME'' + ''1''.
						This will accomodate the string used for the case where
						the ``cache_status`` parameter is invalid.

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
char *DCR_GetStatusName(cache_status, cache_status_name)
unsigned long  cache_status;
char          *cache_status_name;
{
	if ((cache_status & DCR_STATUS_MASK) >=
		((unsigned long) DCR_STATUS_COUNT))
		nstrcpy(cache_status_name, "*** INVALID ***", DCR_MAX_STATUS_NAME);
	else {
		nstrcpy(cache_status_name,
			DCR_StatusNameList[((unsigned int)
			(cache_status & DCR_STATUS_MASK))], DCR_MAX_STATUS_NAME);
		if (cache_status & DCR_STATUS_CRITICAL)
			strcat(strcat(strcat(cache_status_name, " ("), "critical"), ")");
	}

	return(cache_status_name);
}
/* *********************************************************************** */

