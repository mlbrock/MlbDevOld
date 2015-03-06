/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps an 'rvft_Action' to its string equivalent.

	Revision History	:	1996-01-20 --- Creation
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

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_GetActionNameRVFT(rvft_Action action, char *action_name)
{
	return(nstrcpy(action_name,
		(action == RVFT_PREPARE_TO_ACTIVATE) ? "RVFT_PREPARE_TO_ACTIVATE" :
		(action == RVFT_ACTIVATE)            ? "RVFT_ACTIVATE"            :
		(action == RVFT_DEACTIVATE)          ? "RVFT_DEACTIVATE"          :
		"*** Invalid 'rvft_Action' ***", RVUTIL_MAX_RVFT_ACT_NAME));
}
/*	***********************************************************************	*/

