/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps an 'rvcm_Error' code to its equivalent string.

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
#define RVUTIL_rvcm_Error_Count  			((unsigned int) 20)

static const RVUTIL_CODE_STR_MAP
	RVUTIL_rvcm_Error_List[RVUTIL_rvcm_Error_Count] = {
	{	RVCM_OK,									"RVCM_OK"									},
	{	RVCM_ERR_INIT_FAILURE,				"RVCM_ERR_INIT_FAILURE"					},
	{	RVCM_ERR_INVALID_SESSION,			"RVCM_ERR_INVALID_SESSION"				},
	{	RVCM_ERR_BAD_ARG,						"RVCM_ERR_BAD_ARG"						},
	{	RVCM_ERR_BAD_SESSION_NAME,			"RVCM_ERR_BAD_SESSION_NAME"			},
	{	RVCM_ERR_NO_MEMORY,					"RVCM_ERR_NO_MEMORY"						},
	{	RVCM_ERR_BAD_SUBJECT,				"RVCM_ERR_BAD_SUBJECT"					},
	{	RVCM_ERR_ID_CONFIRM_CONFLICT,		"RVCM_ERR_ID_CONFIRM_CONFLICT"		},
	{	RVCM_ERR_NONEXISTENT_ID,			"RVCM_ERR_NONEXISTENT_ID"				},
	{	RVCM_ERR_DUPLICATE_SUBJECT,		"RVCM_ERR_DUPLICATE_SUBJECT"			},
	{	RVCM_ERR_NONEXISTENT_PUBLISHER,	"RVCM_ERR_NONEXISTENT_PUBLISHER"		},
	{	RVCM_ERR_DISALLOWED_LISTENER,		"RVCM_ERR_DISALLOWED_LISTENER"		},
	{	RVCM_ERR_SESSION_NOT_ENABLED,		"RVCM_ERR_SESSION_NOT_ENABLED"		},
	{	RVCM_ERR_SESSION_ALREADY_ENABLED,"RVCM_ERR_SESSION_ALREADY_ENABLED"	},
	{	RVCM_ERR_LEDGER_NAME_CONFLICT,	"RVCM_ERR_LEDGER_NAME_CONFLICT"		},
	{	RVCM_ERR_PARAMETER_CONFLICT,		"RVCM_ERR_PARAMETER_CONFLICT"			},
	{	RVCM_ERR_FILE_IO_ERROR,				"RVCM_ERR_FILE_IO_ERROR"				},
	{	RVCM_ERR_FILE_NO_PERMISSION,		"RVCM_ERR_FILE_NO_PERMISSION"			},
	{	RVCM_ERR_FILE_NOT_LEDGER_OWNER,	"RVCM_ERR_FILE_NOT_LEDGER_OWNER"		},
	{	RVCM_ERR_CORRUPT_LEDGER_FILE,		"RVCM_ERR_CORRUPT_LEDGER_FILE"		}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_CodeToString_rvcm_Error(rvcm_Error in_code, char *out_text)
{
	return(RVUTIL_CodeToString(RVUTIL_rvcm_Error_Count,
		RVUTIL_rvcm_Error_List, ((int) in_code), out_text));
}
/*	***********************************************************************	*/

