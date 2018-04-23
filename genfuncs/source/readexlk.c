/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	GENFUNCS General Functions Library Source Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the logic for reader-exclusion locking.

	Revision History	:	1991-03-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "genfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_LOCK_READEX_LockInit

   SYNOPSIS    :	void GEN_LOCK_READEX_LockInit(lock_ptr);

						volatile GEN_LOCK_READEX *lock_ptr;

   DESCRIPTION :	Initializes a ''GEN_LOCK_READEX'' datum to its unlocked
						state, with a count of ''0''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``lock_ptr`` points to the ''GEN_LOCK_READEX'' datum
						to be initialized.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_LOCK_READEX_LockInit
						Reader-Exclusion Locking Functions:GEN_LOCK_READEX_LockInit
						GENFUNCS:Functions:GEN_LOCK_READEX_LockInit
						GENFUNCS:Reader-Exclusion Locking Functions:GEN_LOCK_READEX_LockInit
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_LOCK_READEX_LockInit

   PUBLISH NAME:	GEN_LOCK_READEX_LockInit

	ENTRY CLASS	:	Reader-Exclusion Locking Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_LOCK_READEX_LockInit(volatile GEN_LOCK_READEX *lock_ptr)
#else
void GEN_LOCK_READEX_LockInit(lock_ptr)
volatile GEN_LOCK_READEX *lock_ptr;
#endif /* #ifndef NARGS */
{
	*lock_ptr = GEN_LOCK_READEX_FLAG_INIT;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_LOCK_READEX_StartLock

   SYNOPSIS    :	void GEN_LOCK_READEX_StartLock(lock_ptr);

						volatile GEN_LOCK_READEX *lock_ptr;

   DESCRIPTION :	Starts a reader-exclusion lock on a resource.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``lock_ptr`` points to the ''GEN_LOCK_READEX'' datum
						to be locked.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_LOCK_READEX_EndLock
						GEN_LOCK_READEX_IncrementLock

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_LOCK_READEX_StartLock
						Reader-Exclusion Locking Functions:GEN_LOCK_READEX_StartLock
						GENFUNCS:Functions:GEN_LOCK_READEX_StartLock
						GENFUNCS:Reader-Exclusion Locking Functions:GEN_LOCK_READEX_StartLock
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_LOCK_READEX_StartLock

   PUBLISH NAME:	GEN_LOCK_READEX_StartLock

	ENTRY CLASS	:	Reader-Exclusion Locking Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_LOCK_READEX_StartLock(volatile GEN_LOCK_READEX *lock_ptr)
#else
void GEN_LOCK_READEX_StartLock(lock_ptr)
volatile GEN_LOCK_READEX *lock_ptr;
#endif /* #ifndef NARGS */
{
	*lock_ptr |= GEN_LOCK_READEX_FLAG_MASK;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_LOCK_READEX_EndLock

   SYNOPSIS    :	void GEN_LOCK_READEX_EndLock(lock_ptr);

						volatile GEN_LOCK_READEX *lock_ptr;

   DESCRIPTION :	Ends a reader-exclusion lock on a resource.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``lock_ptr`` points to the ''GEN_LOCK_READEX'' datum
						to be unlocked.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_LOCK_READEX_StartLock
						GEN_LOCK_READEX_IncrementLock

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_LOCK_READEX_EndLock
						Reader-Exclusion Locking Functions:GEN_LOCK_READEX_EndLock
						GENFUNCS:Functions:GEN_LOCK_READEX_EndLock
						GENFUNCS:Reader-Exclusion Locking Functions:GEN_LOCK_READEX_EndLock
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_LOCK_READEX_EndLock

   PUBLISH NAME:	GEN_LOCK_READEX_EndLock

	ENTRY CLASS	:	Reader-Exclusion Locking Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_LOCK_READEX_EndLock(volatile GEN_LOCK_READEX *lock_ptr)
#else
void GEN_LOCK_READEX_EndLock(lock_ptr)
volatile GEN_LOCK_READEX *lock_ptr;
#endif /* #ifndef NARGS */
{
	*lock_ptr = (*lock_ptr + 1) & GEN_LOCK_READEX_COUNT_MASK;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_LOCK_READEX_IncrementLock

   SYNOPSIS    :	void GEN_LOCK_READEX_IncrementLock(lock_ptr);

						volatile GEN_LOCK_READEX *lock_ptr;

   DESCRIPTION :	Increments a reader-exclusion lock.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``lock_ptr`` points to the ''GEN_LOCK_READEX'' datum
						to be incremented.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_LOCK_READEX_StartLock
						GEN_LOCK_READEX_EndLock

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_LOCK_READEX_IncrementLock
						Reader-Exclusion Locking Functions:GEN_LOCK_READEX_IncrementLock
						GENFUNCS:Functions:GEN_LOCK_READEX_IncrementLock
						GENFUNCS:Reader-Exclusion Locking Functions:GEN_LOCK_READEX_IncrementLock
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_LOCK_READEX_IncrementLock

   PUBLISH NAME:	GEN_LOCK_READEX_IncrementLock

	ENTRY CLASS	:	Reader-Exclusion Locking Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void GEN_LOCK_READEX_IncrementLock(volatile GEN_LOCK_READEX *lock_ptr)
#else
void GEN_LOCK_READEX_IncrementLock(lock_ptr)
volatile GEN_LOCK_READEX *lock_ptr;
#endif /* #ifndef NARGS */
{
	*lock_ptr |= (*lock_ptr + 1) % GEN_LOCK_READEX_COUNT_MASK;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_LOCK_READEX_TestLock

   SYNOPSIS    :	truth_flag = GEN_LOCK_READEX_TestLock(lock_ptr);

						const volatile GEN_LOCK_READEX *lock_ptr;

   DESCRIPTION :	Tests a reader-exclusion lock to determine the lock is
						active.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``lock_ptr`` points to the ''GEN_LOCK_READEX'' datum
						to be tested.

   RETURNS     :	Returns one of the GENFUNCS truth codes:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the parameter
						was matched.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_LOCK_READEX_WaitLock
						GEN_LOCK_READEX_CheckLock

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_LOCK_READEX_TestLock
						Reader-Exclusion Locking Functions:GEN_LOCK_READEX_TestLock
						GENFUNCS:Functions:GEN_LOCK_READEX_TestLock
						GENFUNCS:Reader-Exclusion Locking Functions:GEN_LOCK_READEX_TestLock
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_LOCK_READEX_TestLock

   PUBLISH NAME:	GEN_LOCK_READEX_TestLock

	ENTRY CLASS	:	Reader-Exclusion Locking Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_LOCK_READEX_TestLock(const volatile GEN_LOCK_READEX *lock_ptr)
#else
int GEN_LOCK_READEX_TestLock(lock_ptr)
const volatile GEN_LOCK_READEX *lock_ptr;
#endif /* #ifndef NARGS */
{
	return((*lock_ptr & GEN_LOCK_READEX_FLAG_MASK) ? GENFUNCS_TRUE :
		GENFUNCS_FALSE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_LOCK_READEX_WaitLock

   SYNOPSIS    :	return_code = GEN_LOCK_READEX_WaitLock(in_lock_ptr,
							cycle_count, cycle_time_out, out_lock_ptr);

						int                             return_code;

						const volatile GEN_LOCK_READEX *in_lock_ptr;

						unsigned int                    cycle_count;

						unsigned long                   cycle_time_out;

						GEN_LOCK_READEX                *out_lock_ptr;

   DESCRIPTION :	Performs a spin-wait on a reader-exclusion lock until the
						lock is released by the writer or the ``cycle_count``
						cycles have been spun.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``in_lock_ptr`` points to the ''GEN_LOCK_READEX''
						upon which this function is to wait.

						(.) ``cycle_count`` is the number of cycles to spin.

						(.) ``cycle_time_out`` is the time-out in micrseconds
						between spin cycles.

						(.) ``out_lock_ptr`` points to a ''GEN_LOCK_READEX'' datum
						into which this function will place a copy of the
						``in_lock_ptr`` datum if the lock is available.

   RETURNS     :	Returns one of the GENFUNCS truth codes:

						(.) The manifest constant ''GENFUNCS_SUCCESS'' if the
						lock is free.

						(.) Otherwise, the manifest constant
						''GENFUNCS_LOCK_ACQ_FAILURE'' is returned if the lock was
						not released within the specified cycle time.

   NOTES       :	This function will spin on the lock at least once, even if
						the ``cycle_count`` parameter is ''0''.

   CAVEATS     :	

   SEE ALSO    :	GEN_LOCK_READEX_TestLock
						GEN_LOCK_READEX_CheckLock

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_LOCK_READEX_WaitLock
						Reader-Exclusion Locking Functions:GEN_LOCK_READEX_WaitLock
						GENFUNCS:Functions:GEN_LOCK_READEX_WaitLock
						GENFUNCS:Reader-Exclusion Locking Functions:GEN_LOCK_READEX_WaitLock
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_LOCK_READEX_WaitLock

   PUBLISH NAME:	GEN_LOCK_READEX_WaitLock

	ENTRY CLASS	:	Reader-Exclusion Locking Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_LOCK_READEX_WaitLock(const volatile GEN_LOCK_READEX *in_lock_ptr,
	unsigned int cycle_count, unsigned long cycle_time_out,
	GEN_LOCK_READEX *out_lock_ptr)
#else
int GEN_LOCK_READEX_WaitLock(in_lock_ptr, cycle_count, cycle_time_out,
	out_lock_ptr)
const volatile GEN_LOCK_READEX *in_lock_ptr;
unsigned int                    cycle_count;
unsigned long                   cycle_time_out;
GEN_LOCK_READEX                *out_lock_ptr;
#endif /* #ifndef NARGS */
{
	int return_code = GENFUNCS_LOCK_ACQ_FAILURE;

	cycle_count = (cycle_count) ? cycle_count : 1;

	while (1) {
		if (!(*in_lock_ptr & GEN_LOCK_READEX_FLAG_MASK)) {
			*out_lock_ptr = *in_lock_ptr;
			return_code   = GENFUNCS_SUCCESS;
			break;
		}
		if (!--cycle_count)
			break;
		if (cycle_time_out)
			GEN_usleep(cycle_time_out);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	GEN_LOCK_READEX_CheckLock

   SYNOPSIS    :	truth_flag = GEN_LOCK_READEX_CheckLock(lock_ptr_1,
							lock_ptr_2);

						int                             truth_flag;

						const volatile GEN_LOCK_READEX *lock_ptr_1;

						const GEN_LOCK_READEX          *lock_ptr_2;

   DESCRIPTION :	Determines whether two ''GEN_LOCK_READEX'' data are
						identical.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``lock_ptr_1`` points to the first lock to be compared.

						(.) ``lock_ptr_2`` points to the second lock to be compared.

   RETURNS     :	Returns one of the GENFUNCS truth codes:

						(.) The manifest constant ''GENFUNCS_TRUE'' if the locks
						are identical.

						(.) Otherwise, the manifest constant ''GENFUNCS_FALSE'' is
						returned.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	GEN_LOCK_READEX_TestLock
						GEN_LOCK_READEX_WaitLock

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

   COPYRIGHT   :	Copyright 1991 - 2018 Michael L. Brock

   OUTPUT INDEX:	GEN_LOCK_READEX_CheckLock
						Reader-Exclusion Locking Functions:GEN_LOCK_READEX_CheckLock
						GENFUNCS:Functions:GEN_LOCK_READEX_CheckLock
						GENFUNCS:Reader-Exclusion Locking Functions:GEN_LOCK_READEX_CheckLock
						General Functions:See GENFUNCS

   PUBLISH XREF:	GEN_LOCK_READEX_CheckLock

   PUBLISH NAME:	GEN_LOCK_READEX_CheckLock

	ENTRY CLASS	:	Reader-Exclusion Locking Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int GEN_LOCK_READEX_CheckLock(const volatile GEN_LOCK_READEX *lock_ptr_1,
	const GEN_LOCK_READEX *lock_ptr_2)
#else
int GEN_LOCK_READEX_CheckLock(lock_ptr_1, lock_ptr_2)
const volatile GEN_LOCK_READEX *lock_ptr_1;
const GEN_LOCK_READEX          *lock_ptr_2;
#endif /* #ifndef NARGS */
{
	return((*lock_ptr_1 != *lock_ptr_2) ? GENFUNCS_FALSE : GENFUNCS_TRUE);
}
/*	***********************************************************************	*/

