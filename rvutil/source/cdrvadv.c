/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps an 'rvadv_Error' code to its equivalent string.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
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
#define RVUTIL_rvadv_Error_Count  			((unsigned int) 9)

static const RVUTIL_CODE_STR_MAP
	RVUTIL_rvadv_Error_List[RVUTIL_rvadv_Error_Count] = {
	{	RVADV_OK,							"RVADV_OK"							},
	{	RVADV_ERR_NOT_INITIALIZED,		"RVADV_ERR_NOT_INITIALIZED"	},
	{	RVADV_ERR_INVALID_SESSION,		"RVADV_ERR_INVALID_SESSION"	},
	{	RVADV_ERR_BAD_ARG,				"RVADV_ERR_BAD_ARG"				},
	{	RVADV_ERR_VERSION_MISMATCH,	"RVADV_ERR_VERSION_MISMATCH"	},
	{	RVADV_ERR_OUT_OF_SPACE,			"RVADV_ERR_OUT_OF_SPACE"		},
	{	RVADV_ERR_BAD_NAME,				"RVADV_ERR_BAD_NAME"				},
	{	RVADV_ERR_BAD_DATA,				"RVADV_ERR_BAD_DATA"				},
	{	RVADV_ERR_NOT_FOUND,				"RVADV_ERR_NOT_FOUND"			}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_CodeToString_rvadv_Error(rvadv_Error in_code, char *out_text)
{
	return(RVUTIL_CodeToString(RVUTIL_rvadv_Error_Count,
		RVUTIL_rvadv_Error_List, ((int) in_code), out_text));
}
/*	***********************************************************************	*/

