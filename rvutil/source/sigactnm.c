/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Given a signal action type, returns its equivalent
								name as a string.

	Revision History	:	1996-01-23 --- Creation
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

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Data private to this module . . .												*/
/*	***********************************************************************	*/
static const char *RVUTIL_SignalActionNameList[RVUTIL_SIGNAL_ACTION_COUNT] = {
	"IGNORE",
	"EXIT",
	"EXIT_FAST",
	"USER"
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_GetSignalActionName(int action, char *action_name)
{
	return(nstrcpy(action_name,
		((action < 0) || (action >= RVUTIL_SIGNAL_ACTION_COUNT)) ?
		"***INVALID***" : RVUTIL_SignalActionNameList[action],
		RVUTIL_SIGNAL_ACTION_NAME_MAX));
}
/*	***********************************************************************	*/

