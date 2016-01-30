/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps an 'rvft_Error' code to its equivalent string.

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
#define RVUTIL_rvft_Error_Count  			((unsigned int) 5)

static const RVUTIL_CODE_STR_MAP
	RVUTIL_rvft_Error_List[RVUTIL_rvft_Error_Count] = {
	{	RVFT_OK,							"RVFT_OK"						},
	{	RVFT_ERR_INIT_FAILURE,		"RVFT_ERR_INIT_FAILURE"		},
	{	RVFT_ERR_INVALID_SESSION,	"RVFT_ERR_INVALID_SESSION"	},
	{	RVFT_ERR_BAD_ARG,				"RVFT_ERR_BAD_ARG"			},
	{	RVFT_ERR_RESOURCE,			"RVFT_ERR_RESOURCE"			}
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_CodeToString_rvft_Error(rvft_Error in_code, char *out_text)
{
	return(RVUTIL_CodeToString(RVUTIL_rvft_Error_Count,
		RVUTIL_rvft_Error_List, ((int) in_code), out_text));
}
/*	***********************************************************************	*/

