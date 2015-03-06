/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps an 'rvmsg_Error' code to its equivalent string.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
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
#define RVUTIL_rvmsg_Error_Count  			((unsigned int) 9)

static const RVUTIL_CODE_STR_MAP
	RVUTIL_rvmsg_Error_List[RVUTIL_rvmsg_Error_Count] = {
	{	RVMSG_OK,							"RVMSG_OK"							},
	{	RVMSG_ERR_NOT_INITIALIZED,		"RVMSG_ERR_NOT_INITIALIZED"	},
	{	RVMSG_ERR_INVALID_SESSION,		"RVMSG_ERR_INVALID_SESSION"	},
	{	RVMSG_ERR_BAD_ARG,				"RVMSG_ERR_BAD_ARG"				},
	{	RVMSG_ERR_VERSION_MISMATCH,	"RVMSG_ERR_VERSION_MISMATCH"	},
	{	RVMSG_ERR_OUT_OF_SPACE,			"RVMSG_ERR_OUT_OF_SPACE"		},
	{	RVMSG_ERR_BAD_NAME,				"RVMSG_ERR_BAD_NAME"				},
	{	RVMSG_ERR_BAD_DATA,				"RVMSG_ERR_BAD_DATA"				},
	{	RVMSG_ERR_NOT_FOUND,				"RVMSG_ERR_NOT_FOUND"			}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_CodeToString_rvmsg_Error(rvmsg_Error in_code, char *out_text)
{
	return(RVUTIL_CodeToString(RVUTIL_rvmsg_Error_Count,
		RVUTIL_rvmsg_Error_List, ((int) in_code), out_text));
}
/*	***********************************************************************	*/

