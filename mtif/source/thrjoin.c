/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Perform a join on a thread.

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

#include <limits.h>
#include <string.h>

#include <strfuncs.h>

#include "mtifi.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int MTIF_THR_JoinFacility,
	(MTIF_THR_HANDLE *thr_handle_ptr, void **status_ptr, char *error_text));
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_Join(MTIF_THR_HANDLE *thr_handle_ptr, void **status_ptr,
	char *error_text)
#else
int MTIF_THR_Join(thr_handle_ptr, status_ptr, error_text)
MTIF_THR_HANDLE  *thr_handle_ptr;
void            **status_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MTIF_SUCCESS;
	char buffer[STR_VAL2STR_MAX_LEN + 1];
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if (thr_handle_ptr == NULL) {
		if (error_text != NULL)
			strcpy(tmp_error_text, "Invalid thread handle ('NULL').");
		return_code = MTIF_OP_FAILURE_THR;
	}
	else if (MTIF_THR_GET_OS_ID(thr_handle_ptr) == MTIF_THR_Self()) {
		if (error_text != NULL)
			strcat(strcat(strcpy(tmp_error_text, "Thread identifier '"),
				val2str_uint(MTIF_THR_Self(), 10, NULL, buffer)),
				"' attempted to perform a 'MTIF_THR_Join()' on itself");
		return_code = MTIF_OP_FAILURE_THR;
	}
	else
		return_code = MTIF_THR_JoinFacility(thr_handle_ptr, status_ptr,
			(error_text != NULL) ? tmp_error_text : NULL);

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform 'MTIF_THR_Join()' failed: "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

#ifdef _Windows
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_JoinFacility(MTIF_THR_HANDLE *thr_handle_ptr,
	void **status_ptr, char *error_text)
#else
static int MTIF_THR_JoinFacility(thr_handle_ptr, status_ptr, error_text)
MTIF_THR_HANDLE  *thr_handle_ptr;
void            **status_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;
	int error_code;


	if ((error_code = WaitForSingleObject(thr_handle_ptr->thread_handle,
		INFINITE)) == WAIT_OBJECT_0) {
		if ((status_ptr != NULL) &&
			(!GetExitCodeThread(thr_handle_ptr->thread_handle,
			((LPDWORD) status_ptr)))) {
			if (error_text != NULL)
				MTIF_SUPP_AppendLastErrorString_Win32(strcpy(error_text,
					"Call to 'GetExitCodeThread()' failed: "));
			return_code = MTIF_OP_FAILURE_THR;
		}
		CloseHandle(thr_handle_ptr->thread_handle);
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendLastErrorString_Win32(
				strcat(val2str_ptr0_cat(thr_handle_ptr->thread_handle,
				strcpy(error_text, "Call to 'WaitForSingleObject(")), 
				", INFINITE)' failed: "));
		return_code = MTIF_OP_FAILURE_THR;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_UI_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_JoinFacility(MTIF_THR_HANDLE *thr_handle_ptr,
	void **status_ptr, char *error_text)
#else
static int MTIF_THR_JoinFacility(thr_handle_ptr, status_ptr, error_text)
MTIF_THR_HANDLE  *thr_handle_ptr;
void            **status_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;
	int error_code;

	if ((error_code = thr_join(*thr_handle_ptr, NULL, status_ptr)) != 0) {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(error_code,
				strcpy(error_text, "Call to 'thr_join()' failed: "));
		return_code = MTIF_OP_FAILURE_THR;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_POSIX_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_JoinFacility(MTIF_THR_HANDLE *thr_handle_ptr,
	void **status_ptr, char *error_text)
#else
static int MTIF_THR_JoinFacility(thr_handle_ptr, status_ptr, error_text)
MTIF_THR_HANDLE  *thr_handle_ptr;
void            **status_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;
	int error_code;

	if ((error_code = pthread_join(*thr_handle_ptr, status_ptr)) != 0) {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(error_code,
				strcpy(error_text, "Call to 'pthread_join()' failed: "));
		return_code = MTIF_OP_FAILURE_THR;
	}

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_JoinFacility(MTIF_THR_HANDLE *thr_handle_ptr,
	void **status_ptr, char *error_text)
#else
static int MTIF_THR_JoinFacility(thr_handle_ptr, status_ptr, error_text)
MTIF_THR_HANDLE  *thr_handle_ptr;
void            **status_ptr;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;

	if (error_text != NULL)
		strcpy(error_text, "Function 'MTIF_THR_Join()' not supported.");

	return_code = MTIF_OP_FAILURE_THR;

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifdef _Windows */

