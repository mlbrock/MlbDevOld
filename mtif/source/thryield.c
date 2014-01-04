/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Yields the remaining quantum of the calling thread.

	Revision History	:	1994-09-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*	Necessary include files . . .															*/
/* *********************************************************************** */

#include <sdtif.h>

#include "mtifi.h"

/* *********************************************************************** */

/* *********************************************************************** */
void MTIF_THR_Yield()
{
#ifdef _Windows
	Sleep(((DWORD) 0));
#elif MTIF_THR_UI_THREADS
	thr_yield();
#elif MTIF_THR_POSIX_THREADS
	/*	*****************************************************************
		*****************************************************************
		The function 'sched_yield()' will return 'ENOSYS' if the function
		is not supported by the POSIX threads implementation. So we try
		another way . . .
		*****************************************************************	*/
	if (sched_yield() == -1)
		SDTIF_nsleep(0L);
	/*	*****************************************************************	*/
#else
	SDTIF_nsleep(0L);
#endif /* #ifdef _Windows */
}
/* *********************************************************************** */

