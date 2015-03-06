/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determine if two thread identifiers are equal.

	Revision History	:	1994-09-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
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
int MTIF_THR_Equal(MTIF_THR_HANDLE *thr_handle_ptr_1,
	MTIF_THR_HANDLE *thr_handle_ptr_2)
#else
int MTIF_THR_Equal(thr_handle_ptr_1, thr_handle_ptr_2)
MTIF_THR_HANDLE *thr_handle_ptr_1;
MTIF_THR_HANDLE *thr_handle_ptr_2;
#endif /* #ifndef NARGS */
{
#ifdef _Windows
	return(((int) ((thr_handle_ptr_1->thread_id ==
		thr_handle_ptr_2->thread_id) ? 1 : 0)));
#elif MTIF_THR_UI_THREADS
	return(((int) ((*thr_handle_ptr_1 == *thr_handle_ptr_2) ? 1 : 0)));
#elif MTIF_THR_POSIX_THREADS
	return(pthread_equal(*thr_handle_ptr_1, *thr_handle_ptr_2));
#else
	return(((int) ((*thr_handle_ptr_1 == *thr_handle_ptr_2) ? 1 : 0)));
#endif /* #ifdef _Windows */
}
/* *********************************************************************** */

