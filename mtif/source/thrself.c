/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the identifier of the current thread.

	Revision History	:	1994-09-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*	Necessary include files . . .															*/
/* *********************************************************************** */

#include <genfuncs.h>

#include "mtifi.h"

/* *********************************************************************** */

/* *********************************************************************** */
MTIF_THR_ID MTIF_THR_Self()
{
#ifdef _Windows
	return(((MTIF_THR_ID) GEN_GetThreadID()));
#elif MTIF_THR_UI_THREADS
	return(((MTIF_THR_ID) thr_self()));
#elif MTIF_THR_POSIX_THREADS
	return(((MTIF_THR_ID) pthread_self()));
#else
	return(((MTIF_THR_ID) GEN_GetThreadID()));
#endif /* #ifdef _Windows */
}
/* *********************************************************************** */

