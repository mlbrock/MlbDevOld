/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Co-operative Locking Library File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the DCR co-operative locking library.

	Revision History	:	1994-03-12 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DCRLOCK_H__h

#define h__DCRLOCK_H__h	1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <sys/time.h>

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifdef NO_VOLATILE
# ifndef volatile
#  define volatile
# endif /* #ifndef volatile */
#endif /* #ifndef NO_VOLATILE */

#ifdef NO_VOID
# ifndef void
#  define void char
# endif /* #ifndef void */
#endif /* #ifdef NO_VOID */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_LOCK_UNLOCKED_FLAG			((unsigned long) 0L)
#define DCR_LOCK_LOCKED_FLAG				((unsigned long) 0XFFFFFFFFL)

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	unsigned long lock_count;
	unsigned long lock_flag;
} DCR_LOCK;

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
void DCR_LOCK_Lock(volatile DCR_LOCK *lock_ptr);
void DCR_LOCK_UnLock(volatile DCR_LOCK *lock_ptr);
int  DCR_LOCK_GetLock(volatile DCR_LOCK *in_lock_ptr,
	volatile DCR_LOCK *saved_lock_ptr, unsigned int lock_retry_count,
	unsigned int lock_retry_time_out);
int  DCR_LOCK_CompareLock(volatile DCR_LOCK *lock_ptr_1,
	volatile DCR_LOCK *lock_ptr_2);
#else
void DCR_LOCK_Lock();
void DCR_LOCK_UnLock();
int  DCR_LOCK_GetLock();
int  DCR_LOCK_CompareLock();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

#endif /* #ifndef h__DCRLOCK_H__h */

