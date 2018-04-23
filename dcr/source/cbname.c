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

	Revision History	:	1994-07-29 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
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

static char *DCR_CallBackNameList[DCR_CB_COUNT] = {
	"record insert",
	"record search",
	"record delete",
	"bulk insert",
	"bulk search",
	"index cache",
	"sort cache",
	"resize cache",
	"initial DB load",
	"DB reload",
	"DB update",
	"allocate chunk",
	"record update",
	"check index",
	"check index and records"
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

	CAVEATS		:	The buffer ``call_back_name`` into which the string
						representing the call-back name will be copied by this
						function should be at least the length of the manifest
						constant ''DCR_MAX_CB_NAME'' + ''1''. This will accomodate
						the string used for the case where the ``call_back``
						parameter is invalid.

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1994 - 2018 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
char *DCR_GetCallBackName(call_back, call_back_name)
unsigned long  call_back;
char          *call_back_name;
{
	if (call_back & DCR_CB_REC_INSERT)
		nstrcpy(call_back_name, DCR_CallBackNameList[0],  DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_SEARCH)
		nstrcpy(call_back_name, DCR_CallBackNameList[1],  DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_DELETE)
		nstrcpy(call_back_name, DCR_CallBackNameList[2],  DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_BULK_INSERT)
		nstrcpy(call_back_name, DCR_CallBackNameList[3],  DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_BULK_SEARCH)
		nstrcpy(call_back_name, DCR_CallBackNameList[4],  DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_INDEX_CACHE)
		nstrcpy(call_back_name, DCR_CallBackNameList[5],  DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_SORT_CACHE)
		nstrcpy(call_back_name, DCR_CallBackNameList[6],  DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_RESIZE_CACHE)
		nstrcpy(call_back_name, DCR_CallBackNameList[7],  DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_INITIAL_LOAD)
		nstrcpy(call_back_name, DCR_CallBackNameList[8],  DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_RELOAD)
		nstrcpy(call_back_name, DCR_CallBackNameList[9],  DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_UPDATE)
		nstrcpy(call_back_name, DCR_CallBackNameList[10], DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_ALLOC_CHUNK)
		nstrcpy(call_back_name, DCR_CallBackNameList[11], DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_REC_UPDATE)
		nstrcpy(call_back_name, DCR_CallBackNameList[12], DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_CHECK_INDEX_1)
		nstrcpy(call_back_name, DCR_CallBackNameList[13], DCR_MAX_CB_NAME);
	else if (call_back & DCR_CB_CHECK_INDEX_2)
		nstrcpy(call_back_name, DCR_CallBackNameList[14], DCR_MAX_CB_NAME);
	else
		nstrcpy(call_back_name, "*** INVALID ***", DCR_MAX_CB_NAME);

	return(call_back_name);
}
/* *********************************************************************** */

