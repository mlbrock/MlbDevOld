/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps an 'rvevm_Returns' code to its equivalent string.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define RVUTIL_rvevm_Error_Count  			((unsigned int) 12)

static const RVUTIL_CODE_STR_MAP
	RVUTIL_rvevm_Error_List[RVUTIL_rvevm_Error_Count] = {
	{	RVEVM_OK,						"RVEVM_OK"						},
	{	RVEVM_ERR_INIT,				"RVEVM_ERR_INIT"				},
	{	RVEVM_ERR_BAD_ID,				"RVEVM_ERR_BAD_ID"			},
	{	RVEVM_ERR_BAD_SOURCE,		"RVEVM_ERR_BAD_SOURCE"		},
	{	RVEVM_ERR_BAD_CONDITION,	"RVEVM_ERR_BAD_CONDITION"	},
	{	RVEVM_ERR_BAD_PROC,			"RVEVM_ERR_BAD_PROC"			},
	{	RVEVM_ERR_BAD_SIG,			"RVEVM_ERR_BAD_SIG"			},
	{	RVEVM_ERR_BAD_INTERVAL,		"RVEVM_ERR_BAD_INTERVAL"	},
	{	RVEVM_ERR_RESOURCE_LIMIT,	"RVEVM_ERR_RESOURCE_LIMIT"	},
	{	RVEVM_ERR_OS_ERROR,			"RVEVM_ERR_OS_ERROR"			},
	{	RVEVM_ERR_NO_EVENTS,			"RVEVM_ERR_NO_EVENTS"		},
	{	RVEVM_ERR_SYNC_SESSION,		"RVEVM_ERR_SYNC_SESSION"	}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_CodeToString_rvevm_Error(rvevm_Returns in_code, char *out_text)
{
	return(RVUTIL_CodeToString(RVUTIL_rvevm_Error_Count,
		RVUTIL_rvevm_Error_List, ((int) in_code), out_text));
}
/*	***********************************************************************	*/

