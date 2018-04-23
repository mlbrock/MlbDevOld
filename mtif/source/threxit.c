/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Exit the current thread.

	Revision History	:	1994-09-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*	Necessary include files . . .															*/
/* *********************************************************************** */

#include "mtifi.h"

/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
void MTIF_THR_Exit(void *exit_data)
#else
void MTIF_THR_Exit(exit_data)
void *exit_data;
#endif /* #ifndef NARGS */
{
#ifdef _Windows
	ExitThread(((DWORD) exit_data));
#elif MTIF_THR_UI_THREADS
	thr_exit(exit_data);
#elif MTIF_THR_POSIX_THREADS
	pthread_exit(exit_data);
#else
	exit(((int) exit_data));
#endif /* #ifdef _Windows */
}
/* *********************************************************************** */


