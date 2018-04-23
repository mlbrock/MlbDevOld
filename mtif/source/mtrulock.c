/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Unlocks a recursive mutex.

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

#include <string.h>

#include <strfuncs.h>

#include "mtifi.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int MTIF_MTR_UnlockFacility,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTR_Unlock(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text)
#else
int MTIF_MTR_Unlock(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MTIF_SUCCESS;
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_MTR_Check(mtr_handle_ptr,
		(error_text != NULL) ? tmp_error_text : NULL)) == MTIF_SUCCESS)
		return_code = MTIF_MTR_UnlockBasic(mtr_handle_ptr,
			(error_text != NULL) ? tmp_error_text : NULL);

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform 'MTIF_MTR_Unlock()' failed: "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

/*
	ADF NOTE:	Aside from ``MTIF_MTR_Unlock``, this function is used only by
					internal functions to unlock disabled recursive mutexes at
					the time of their destruction. See ``MTIF_MTR_Destroy``.
*/
/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTR_UnlockBasic(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text)
#else
int MTIF_MTR_UnlockBasic(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;

	if (MTIF_MTR_OWNER_IS_SELF(mtr_handle_ptr) != MTIF_TRUE) {
		if (error_text != NULL)
			chrcat(val2str_ulong_cat(MTIF_THR_Self(), 10, "",
				strcat(strcpy(error_text,
				"Failed attempt to unlock a recursive mutex with "),
				"'MTIF_MTR_UnlockBasic' on thread identifier ")), '.');
			return_code = MTIF_OP_FAILURE_MTR;
	}
	else if (mtr_handle_ptr->lock_count > 1L)
		mtr_handle_ptr->lock_count--;
	else {
		mtr_handle_ptr->process_id = 0L;
		mtr_handle_ptr->thread_id  = 0;
		mtr_handle_ptr->lock_count = 0L;
		return_code = MTIF_MTR_UnlockFacility(mtr_handle_ptr, error_text);
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef _Windows
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_UnlockFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_UnlockFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_SUPP_WIN32_ReleaseMutex(mtr_handle_ptr->mtr_data, error_text));
}
/* *********************************************************************** */

#elif MTIF_THR_UI_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_UnlockFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_UnlockFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = mutex_unlock(&mtr_handle_ptr->mtr_data)))
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'mutex_unlock()' failed: "));
		return_code = MTIF_OP_FAILURE_MTR;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_POSIX_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_UnlockFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_UnlockFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = pthread_mutex_unlock(&mtr_handle_ptr->mtr_data)))
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'pthread_mutex_unlock()' failed: "));
		return_code = MTIF_OP_FAILURE_MTR;
	}

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_UnlockFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_UnlockFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;

	if (error_text != NULL)
		strcpy(error_text, "Function 'MTIF_MTR_Unlock()' not supported.");

	return_code = MTIF_OP_FAILURE_MTR;

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifdef _Windows */

