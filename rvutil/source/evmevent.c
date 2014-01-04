/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps an 'rvevm_EventType' to its string equivalent.

	Revision History	:	1996-01-20 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
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
char *RVUTIL_GetEventNameRVEVM(rvevm_EventType event_type, char *event_name)
{
	return(nstrcpy(event_name,
		(event_type == RVEVM_IO_EVENT)     ? "RVEVM_IO_EVENT"     :
		(event_type == RVEVM_TIMER_EVENT)  ? "RVEVM_TIMER_EVENT"  :
		(event_type == RVEVM_SIGNAL_EVENT) ? "RVEVM_SIGNAL_EVENT" :
		"*** Invalid 'rvevm_EventType' ***", RVUTIL_MAX_RVEVM_EVNT_NAME));
}
/*	***********************************************************************	*/

