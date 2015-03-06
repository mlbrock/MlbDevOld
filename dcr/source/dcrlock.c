/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the DCR co-operative locking
								library.

	Revision History	:	1994-03-12 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dcr.h"

/*	***********************************************************************	*/

void DCR_LOCK_Lock(lock_ptr)
volatile DCR_LOCK *lock_ptr;
{
}
/*	***********************************************************************	*/

void DCR_LOCK_UnLock(lock_ptr)
volatile DCR_LOCK *lock_ptr;
{
}
/*	***********************************************************************	*/

int DCR_LOCK_GetLock(in_lock_ptr, saved_lock_ptr, lock_retry_count,
	lock_retry_time_out)
volatile DCR_LOCK *in_lock_ptr;
volatile DCR_LOCK *saved_lock_ptr;
unsigned int       lock_retry_count;
unsigned int       lock_retry_time_out;
{
	return(DCR_SUCCESS);
}
/*	***********************************************************************	*/

int DCR_LOCK_CompareLock(lock_ptr_1, lock_ptr_2)
volatile DCR_LOCK *lock_ptr_1;
volatile DCR_LOCK *lock_ptr_2;
{
	return(0);
}
/*	***********************************************************************	*/

