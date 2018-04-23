/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Destroys a recursive mutex.

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
COMPAT_FN_DECL_STATIC(int MTIF_MTR_DestroyFacility,
	(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text));
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTR_Destroy(MTIF_MTR_HANDLE *mtr_handle_ptr, char *error_text)
#else
int MTIF_MTR_Destroy(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = MTIF_SUCCESS;
	unsigned long lock_count;
	char          tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_MTR_Lock(mtr_handle_ptr,
		(error_text != NULL) ? tmp_error_text : NULL)) == MTIF_SUCCESS) {
		if ((lock_count = mtr_handle_ptr->lock_count) != 1L) {
			MTIF_MTR_Unlock(mtr_handle_ptr, NULL);
			if (error_text != NULL)
				strcat(val2str_ulong_cat(lock_count, 10, "",
					strcpy(tmp_error_text, "Invalid recursive mutex lock count (")),
					").");
			return_code = MTIF_OP_FAILURE_MTR;
		}
		else if (MTIF_MTR_IS_STATIC(mtr_handle_ptr) == MTIF_TRUE) {
			MTIF_MTR_Unlock(mtr_handle_ptr, NULL);
			if (error_text != NULL)
				strcpy(tmp_error_text,
					"Static recursive mutexes may not be destroyed.");
			return_code = MTIF_OP_FAILURE_MTR;
		}
		else {
			mtr_handle_ptr->signature = 0L;
			MTIF_MTR_UnlockBasic(mtr_handle_ptr, NULL);
			if ((return_code = MTIF_MTR_DestroyFacility(mtr_handle_ptr,
				(error_text != NULL) ? tmp_error_text : NULL)) == MTIF_SUCCESS)
				memset(mtr_handle_ptr, '\0', sizeof(*mtr_handle_ptr));
		}
	}

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform 'MTIF_MTR_Destroy()' failed: "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTR_DestroyStaticAlso(MTIF_MTR_HANDLE *mtr_handle_ptr,
	int destroy_if_static_flag, char *error_text)
#else
int MTIF_MTR_DestroyStaticAlso(mtr_handle_ptr, destroy_if_static_flag,
	error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
int              destroy_if_static_flag;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = MTIF_SUCCESS;
	unsigned long lock_count;
	char          tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_MTR_Lock(mtr_handle_ptr,
		(error_text != NULL) ? tmp_error_text : NULL)) == MTIF_SUCCESS) {
		if ((lock_count = mtr_handle_ptr->lock_count) != 1L) {
			MTIF_MTR_Unlock(mtr_handle_ptr, NULL);
			if (error_text != NULL)
				strcat(val2str_ulong_cat(lock_count, 10, "",
					strcpy(tmp_error_text, "Invalid recursive mutex lock count (")),
					").");
			return_code = MTIF_OP_FAILURE_MTR;
		}
		else if ((MTIF_MTR_IS_STATIC(mtr_handle_ptr) == MTIF_TRUE) &&
			(!destroy_if_static_flag))
			MTIF_MTR_Unlock(mtr_handle_ptr, NULL);
		else if ((MTIF_MTR_IS_STATIC(mtr_handle_ptr) == MTIF_TRUE) &&
			destroy_if_static_flag &&
			(MTIF_MTR_CAN_DESTROY(mtr_handle_ptr) != MTIF_TRUE)) {
			MTIF_MTR_Unlock(mtr_handle_ptr, NULL);
			if (error_text != NULL)
				strcpy(tmp_error_text,
					"Static recursive mutexes may not be destroyed.");
			return_code = MTIF_OP_FAILURE_MTR;
		}
		else {
			mtr_handle_ptr->signature = 0L;
			MTIF_MTR_UnlockBasic(mtr_handle_ptr, NULL);
			if ((return_code = MTIF_MTR_DestroyFacility(mtr_handle_ptr,
				(error_text != NULL) ? tmp_error_text : NULL)) == MTIF_SUCCESS)
				memset(mtr_handle_ptr, '\0', sizeof(*mtr_handle_ptr));
		}
	}

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform 'MTIF_MTR_Destroy()' failed: "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

#ifdef _Windows
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_DestroyFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_DestroyFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MTIF_SUPP_WIN32_CloseHandle(&mtr_handle_ptr->mtr_data,
		error_text)) == MTIF_SUCCESS) {
		if (mtr_handle_ptr->mtr_name != NULL)
			free(mtr_handle_ptr->mtr_name);
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_UI_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_DestroyFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_DestroyFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = mutex_destroy(&mtr_handle_ptr->mtr_data)))
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'mutex_destroy()' failed: "));
		return_code = MTIF_OP_FAILURE_MTR;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_POSIX_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_DestroyFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_DestroyFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = pthread_mutex_destroy(&mtr_handle_ptr->mtr_data)))
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'pthread_mutex_destroy()' failed: "));
		return_code = MTIF_OP_FAILURE_MTR;
	}

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTR_DestroyFacility(MTIF_MTR_HANDLE *mtr_handle_ptr,
	char *error_text)
#else
static int MTIF_MTR_DestroyFacility(mtr_handle_ptr, error_text)
MTIF_MTR_HANDLE *mtr_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;

	if (error_text != NULL)
		strcpy(error_text, "Function 'MTIF_MTR_Destroy()' not supported.");

	return_code = MTIF_OP_FAILURE_MTR;

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifdef _Windows */


