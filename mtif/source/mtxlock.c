/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Locks a basic mutex.

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
COMPAT_FN_DECL_STATIC(int MTIF_MTX_LockFacility,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTX_Lock(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text)
#else
int MTIF_MTX_Lock(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_MTX_Check(mtx_handle_ptr,
		(error_text != NULL) ? tmp_error_text : NULL)) != MTIF_SUCCESS)
		;
	else if (MTIF_MTX_OWNER_IS_SELF(mtx_handle_ptr) == MTIF_TRUE) {
		if (error_text != NULL)
			chrcat(val2str_ulong_cat(MTIF_THR_Self(), 10, "",
				strcat(strcpy(tmp_error_text,
				"Failed attempt to re-enter a basic mutex with "),
				"'MTIF_MTX_Lock()' on thread identifier ")), '.');
		return_code = MTIF_OP_FAILURE_MTX;
	}
	else
		return_code = MTIF_MTX_LockFacility(mtx_handle_ptr,
			(error_text != NULL) ? tmp_error_text : NULL);

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform 'MTIF_MTX_Lock()' failed: "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

/*
	ADF NOTE: Implemented in order to provide an orthogonal interface.
*/
/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTX_LockReader(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text)
#else
int MTIF_MTX_LockReader(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTX_Lock(mtx_handle_ptr, error_text));
}
/* *********************************************************************** */

/*
	ADF NOTE: Implemented in order to provide an orthogonal interface.
*/
/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTX_LockWriter(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text)
#else
int MTIF_MTX_LockWriter(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_MTX_Lock(mtx_handle_ptr, error_text));
}
/* *********************************************************************** */

#ifdef _Windows
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTX_LockFacility(MTIF_MTX_HANDLE *mtx_handle_ptr,
	char *error_text)
#else
static int MTIF_MTX_LockFacility(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	HANDLE tmp_handle;
	char   mtx_name[511 + 1];

	if (mtx_handle_ptr->static_flag == MTIF_TRUE) {
		val2str_ptr0_cat(mtx_handle_ptr,
			strcat(val2str_ulong_cat(MTIF_THR_SelfProcess(), 10, "0",
			strcpy(mtx_name, "MTIF_MTX_WIN32_PRIVATE_NAME_ProcessId=")),
			"___MutexAddress="));
		if ((return_code = MTIF_SUPP_WIN32_CreateMutex(MTIF_TRUE, mtx_name,
			&tmp_handle, error_text)) == MTIF_SUCCESS) {
			if (GetLastError() == ERROR_ALREADY_EXISTS) {
				CloseHandle(tmp_handle);
				while ((mtx_handle_ptr->static_flag == MTIF_TRUE) ||
					(mtx_handle_ptr->mtx_data == ((HANDLE) 0)))
					MTIF_THR_Yield();
				return_code = MTIF_MTX_Lock(mtx_handle_ptr, error_text);
			}
			else {
				mtx_handle_ptr->mtx_data    = tmp_handle;
				mtx_handle_ptr->static_flag = MTIF_FALSE;
				mtx_handle_ptr->process_id  = MTIF_THR_SelfProcess();
				mtx_handle_ptr->thread_id   = MTIF_THR_Self();
				return_code                 = MTIF_SUCCESS;
			}
		}
	}
	else if ((return_code = MTIF_SUPP_WIN32_WaitForSingleObject(
		mtx_handle_ptr->mtx_data, INFINITE, error_text)) == MTIF_SUCCESS) {
		mtx_handle_ptr->process_id = MTIF_THR_SelfProcess();
		mtx_handle_ptr->thread_id  = MTIF_THR_Self();
		return_code                = MTIF_SUCCESS;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_UI_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTX_LockFacility(MTIF_MTX_HANDLE *mtx_handle_ptr,
	char *error_text)
#else
static int MTIF_MTX_LockFacility(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = mutex_lock(&mtx_handle_ptr->mtx_data))) {
		mtx_handle_ptr->static_flag = MTIF_FALSE;
		mtx_handle_ptr->process_id  = MTIF_THR_SelfProcess();
		mtx_handle_ptr->thread_id   = MTIF_THR_Self();
		return_code                 = MTIF_SUCCESS;
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'mutex_lock()' failed: "));
		return_code = MTIF_OP_FAILURE_MTX;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_POSIX_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTX_LockFacility(MTIF_MTX_HANDLE *mtx_handle_ptr,
	char *error_text)
#else
static int MTIF_MTX_LockFacility(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = pthread_mutex_lock(&mtx_handle_ptr->mtx_data))) {
		mtx_handle_ptr->static_flag = MTIF_FALSE;
		mtx_handle_ptr->process_id  = MTIF_THR_SelfProcess();
		mtx_handle_ptr->thread_id   = MTIF_THR_Self();
		return_code                 = MTIF_SUCCESS;
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'pthread_mutex_lock()' failed: "));
		return_code = MTIF_OP_FAILURE_MTX;
	}

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTX_LockFacility(MTIF_MTX_HANDLE *mtx_handle_ptr,
	char *error_text)
#else
static int MTIF_MTX_LockFacility(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (error_text != NULL)
		strcpy(error_text, "Function 'MTIF_MTX_Lock()' not supported.");

	return_code = MTIF_OP_FAILURE_MTX;

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifdef _Windows */

