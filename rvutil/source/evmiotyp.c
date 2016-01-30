/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Maps an 'rvevm_IoEventType' to its string equivalent.

	Revision History	:	1996-01-20 --- Creation
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

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
char *RVUTIL_GetIOEventTypeRVEVM(rvevm_IoEventType io_event_type,
	char *io_event_name)
{
	return(nstrcpy(io_event_name,
		(io_event_type == RVEVM_READ)      ? "RVEVM_READ"      :
		(io_event_type == RVEVM_WRITE)     ? "RVEVM_WRITE"     :
		(io_event_type == RVEVM_EXCEPTION) ? "RVEVM_EXCEPTION" :
		"*** Invalid 'rvevm_IoEventType' ***", RVUTIL_MAX_RVEVM_IO_EVNT_NAME));
}
/*	***********************************************************************	*/

