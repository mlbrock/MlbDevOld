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

	Revision History	:	1994-05-15 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
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

static char *DCR_AreaNameList[DCR_AREA_COUNT] = {
	"cache field",
	"cache field name",
	"cache column name",
	"cache field align",
	"cache index",
	"cache index name",
	"cache index field",
	"cache index align"
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

	CAVEATS		:	The buffer ``cache_area_name`` into which the string
						representing the cache area will be copied by this function
						should be at least the length of the manifest constant
						''DCR_MAX_AREA_NAME'' + ''1''. This will accomodate the
						string used for the case where the ``cache_area``
						parameter is invalid.

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
char *DCR_GetAreaName(cache_area, cache_area_name)
int   cache_area;
char *cache_area_name;
{
	return(nstrcpy(cache_area_name,
		((cache_area < 0) || (cache_area >= DCR_AREA_COUNT)) ?
		"*** INVALID ***" : DCR_AreaNameList[cache_area], DCR_MAX_AREA_NAME));
}
/* *********************************************************************** */

