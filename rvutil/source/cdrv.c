/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps an 'rv_Error' code to its equivalent string.

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
#define RVUTIL_rv_Error_Count  			((unsigned int) 16)

static const RVUTIL_CODE_STR_MAP
	RVUTIL_rv_Error_List[RVUTIL_rv_Error_Count] = {
	{	RV_OK,								"RV_OK"								},
	{	RV_ERR_INIT_FAILURE,				"RV_ERR_INIT_FAILURE"			},
	{	RV_ERR_INVALID_SESSION,			"RV_ERR_INVALID_SESSION"		},
	{	RV_ERR_BAD_ARG,					"RV_ERR_BAD_ARG"					},
	{	RV_ERR_VERSION_MISMATCH,		"RV_ERR_VERSION_MISMATCH"		},
	{	RV_ERR_SERVICE_NOT_FOUND,		"RV_ERR_SERVICE_NOT_FOUND"		},
	{	RV_ERR_NETWORK_NOT_FOUND,		"RV_ERR_NETWORK_NOT_FOUND"		},
	{	RV_ERR_DAEMON_NOT_FOUND,		"RV_ERR_DAEMON_NOT_FOUND"		},
	{	RV_ERR_NO_MEMORY,					"RV_ERR_NO_MEMORY"				},
	{	RV_ERR_BAD_SUBJECT,				"RV_ERR_BAD_SUBJECT"				},
	{	RV_ERR_DAEMON_NOT_CONNECTED,	"RV_ERR_DAEMON_NOT_CONNECTED"	},
	{	RV_ERR_NONEXISTENT_ID,			"RV_ERR_NONEXISTENT_ID"			},
	{	RV_ERR_HOSTNAME_FAILED,			"RV_ERR_HOSTNAME_FAILED"		},
	{	RV_ERR_HOSTBYNAME_FAILED,		"RV_ERR_HOSTBYNAME_FAILED"		},
	{	RV_ERR_NO_HOSTADDR,				"RV_ERR_NO_HOSTADDR"				},
	{	RV_ERR_NOT_PERMITTED,			"RV_ERR_NOT_PERMITTED"			}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_CodeToString_rv_Error(rv_Error in_code, char *out_text)
{
	return(RVUTIL_CodeToString(RVUTIL_rv_Error_Count,
		RVUTIL_rv_Error_List, ((int) in_code), out_text));
}
/*	***********************************************************************	*/

