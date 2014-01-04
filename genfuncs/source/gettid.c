/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines the thread identifier.

	Revision History	:	1994-02-25 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#ifdef __MSDOS__
#elif _Windows
#elif GEN_THR_UI_THREADS
# include <thread.h>
#else
# include <pthread.h>
#endif /* #ifdef __MSDOS__ */

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
unsigned int GEN_GetThreadID(void)
#else
unsigned int GEN_GetThreadID()
#endif /* #ifndef NARGS */
{
#ifdef __MSDOS__
	return(1);
#elif _Windows
	return(((unsigned int) GetCurrentThreadId()));
#elif GEN_THR_UI_THREADS
	return(((unsigned int) thr_self()));
#else
	return(((unsigned int) pthread_self()));
#endif /* #ifdef __MSDOS__ */
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

COMPAT_FN_DECL(int main, (void));

int main()
{
	fprintf(stderr, "Test harness for function 'GEN_GetThreadID()'\n");
	fprintf(stderr, "---- ------- --- -------- -------------------\n\n");

	printf("Thread ID : %u\n", GEN_GetThreadID());

	return(GENFUNCS_SUCCESS);
}

#endif /* #ifdef TEST_MAIN */

