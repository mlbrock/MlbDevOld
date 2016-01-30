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

	Revision History	:	1994-05-25 --- Creation.
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

#include "dcr.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */

static char *DCR_StatNameList[DCR_STAT_COUNT] = {
	"make header",
	"create cache",
	"load meta-data",
	"record insert",
	"record search",
	"record delete",
	"bulk insert",
	"bulk search",
	"index",
	"sort",
	"resize cache",
	"initial DB load",
	"DB re-load",
	"DB update"
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

	CAVEATS		:	The buffer ``cache_stat_name`` into which the string
						representing the cache stat will be copied by this function
						should be at least the length of the manifest constant
						''DCR_MAX_STAT_NAME'' + ''1''. This will accomodate the
						string used for the case where the ``cache_stat``
						parameter is invalid.

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2016 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
char *DCR_GetStatName(cache_stat, cache_stat_name)
int   cache_stat;
char *cache_stat_name;
{
	return(nstrcpy(cache_stat_name,
		((cache_stat < 0) || (cache_stat >= DCR_STAT_COUNT)) ?
		"*** INVALID ***" : DCR_StatNameList[cache_stat], DCR_MAX_STAT_NAME));
}
/* *********************************************************************** */

