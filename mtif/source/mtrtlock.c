/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Tries to lock a recursive mutex.

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

#include <errno.h>
#include <string.h>

#include <strfuncs.h>

#include "mtifi.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int MTIF_MTR_TryLockFacility,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTR_TryLock(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text)
#else
int MTIF_MTR_TryLock(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_MTR_Check(mtr_handle_ptr,
		(error_text != NULL) ? tmp_error_text : NULL)) != MTIF_SUCCESS)
		;
	else if (MTIF_MTR_OWNER_IS_SELF(mtr_handle_ptr) == MTIF_TRUE) {
		if (mtr_handle_ptr->lock_count < ULONG_MAX)
			mtr_handle_ptr->lock_count++;
		else {
			if (error_text != NULL)
				strcat(val2str_ulong_cat(MTIF_THR_Self(), 10, "",
					strcat(strcpy(tmp_error_text,
					"Failed attempt to re-enter a recursive mutex with "),
					"'MTIF_MTR_TryLock()' on thread identifier ")),
					": maximum recursive lock count reached.");
			return_code = MTIF_OP_FAILURE_MTR;
		}
	}
	else
		return_code = MTIF_MTR_TryLockFacility(mtr_handle_ptr,
			(error_text != NULL) ? tmp_error_text : NULL);

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform 'MTIF_MTR_TryLock()' failed: "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

/*
	ADF NOTE: Implemented in order to provide an orthogonal interface.
*/
/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTR_TryLockReader(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text)
#else
int MTIF_MTR_TryLockReader(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_TryLock(mtr_handle_ptr, error_text));
}
/* *********************************************************************** */

/*
	ADF NOTE: Implemented in order to provide an orthogonal interface.
*/
/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTR_TryLockWriter(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text)
#else
int MTIF_MTR_TryLockWriter(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTR_TryLock(mtr_handle_ptr, error_text));
}
/* *********************************************************************** */

#ifdef _Windows
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_TryLockFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_TryLockFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	HANDLE tmp_handle;
	char   mtr_name[511 + 1];

	if (mtr_handle_ptr->static_flag == MTIF_TRUE) {
		val2str_ptr0_cat(mtr_handle_ptr,
			strcat(val2str_ulong_cat(MTIF_THR_SelfProcess(), 10, "0",
			strcpy(mtr_name, "MTIF_MTR_WIN32_PRIVATE_NAME_ProcessId=")),
			"___MutexAddress="));
		if ((return_code = MTIF_SUPP_WIN32_CreateMutex(MTIF_TRUE, mtr_name,
			&tmp_handle, error_text)) == MTIF_SUCCESS) {
			if (GetLastError() == ERROR_ALREADY_EXISTS) {
				CloseHandle(tmp_handle);
				while ((mtr_handle_ptr->static_flag == MTIF_TRUE) ||
					(mtr_handle_ptr->mtr_data == ((HANDLE) 0)))
					MTIF_THR_Yield();
				return_code = MTIF_MTR_TryLock(mtr_handle_ptr, error_text);
			}
			else {
				mtr_handle_ptr->mtr_data    = tmp_handle;
				mtr_handle_ptr->static_flag = MTIF_FALSE;
				mtr_handle_ptr->process_id  = MTIF_THR_SelfProcess();
				mtr_handle_ptr->thread_id   = MTIF_THR_Self();
				mtr_handle_ptr->lock_count  = 1L;
				return_code                 = MTIF_SUCCESS;
			}
		}
	}
	else if ((return_code = MTIF_SUPP_WIN32_WaitForSingleObject(
		mtr_handle_ptr->mtr_data, 0, error_text)) == MTIF_SUCCESS) {
		mtr_handle_ptr->process_id = MTIF_THR_SelfProcess();
		mtr_handle_ptr->thread_id  = MTIF_THR_Self();
		mtr_handle_ptr->lock_count = 1L;
		return_code                = MTIF_SUCCESS;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_UI_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_TryLockFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_TryLockFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = mutex_trylock(&mtr_handle_ptr->mtr_data))) {
		mtr_handle_ptr->static_flag = MTIF_FALSE;
		mtr_handle_ptr->process_id  = MTIF_THR_SelfProcess();
		mtr_handle_ptr->thread_id   = MTIF_THR_Self();
		mtr_handle_ptr->lock_count  = 1L;
		return_code                 = MTIF_SUCCESS;
	}
	else if (return_code == EBUSY) {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code, strcpy(error_text,
				"Unable to acquire lock with 'mutex_trylock()': "));
		return_code = MTIF_LOCK_ACQ_FAILURE;
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'mutex_trylock()' failed: "));
		return_code = MTIF_OP_FAILURE_MTR;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_POSIX_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_TryLockFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_TryLockFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = pthread_mutex_trylock(&mtr_handle_ptr->mtr_data))) {
		mtr_handle_ptr->static_flag = MTIF_FALSE;
		mtr_handle_ptr->process_id  = MTIF_THR_SelfProcess();
		mtr_handle_ptr->thread_id   = MTIF_THR_Self();
		mtr_handle_ptr->lock_count  = 1L;
		return_code                 = MTIF_SUCCESS;
	}
	else if (return_code == EBUSY) {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code, strcpy(error_text,
				"Unable to acquire lock with 'pthread_mutex_trylock()': "));
		return_code = MTIF_LOCK_ACQ_FAILURE;
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'pthread_mutex_trylock()' failed: "));
		return_code = MTIF_OP_FAILURE_MTR;
	}

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_TryLockFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_TryLockFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (error_text != NULL)
		strcpy(error_text, "Function 'MTIF_MTR_TryLock()' not supported.");

	return_code = MTIF_OP_FAILURE_MTR;

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifdef _Windows */

