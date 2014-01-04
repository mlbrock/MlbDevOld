/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Locks a reader/writer lock.

	Revision History	:	1994-09-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2014.
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
COMPAT_FN_DECL_STATIC(int MTIF_RWL_LockReaderFacility,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(int MTIF_RWL_LockWriterFacility,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
/* *********************************************************************** */

/*
	ADF NOTE: Implemented in order to provide an orthogonal interface.
*/
/* *********************************************************************** */
#ifndef NARGS
int MTIF_RWL_Lock(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text)
#else
int MTIF_RWL_Lock(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_RWL_LockWriter(rwl_handle_ptr, error_text));
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_RWL_LockReader(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text)
#else
int MTIF_RWL_LockReader(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MTIF_SUCCESS;
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_RWL_Check(rwl_handle_ptr,
		(error_text != NULL) ? tmp_error_text : NULL)) != MTIF_SUCCESS)
		;
	else if (MTIF_RWL_OWNER_IS_SELF(rwl_handle_ptr) == MTIF_TRUE) {
		if (error_text != NULL)
			chrcat(val2str_ulong_cat(MTIF_THR_Self(), 10, "",
				strcat(strcpy(tmp_error_text,
				"Failed attempt to re-enter a reader/writer lock with "),
				"'MTIF_RWL_LockReader()' on thread identifier ")), '.');
			return_code = MTIF_OP_FAILURE_RWL;
	}
	else
		return_code = MTIF_RWL_LockReaderFacility(rwl_handle_ptr,
			(error_text != NULL) ? tmp_error_text : NULL);

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform 'MTIF_RWL_LockReader()' failed: "),
			tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_RWL_LockWriter(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text)
#else
int MTIF_RWL_LockWriter(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MTIF_SUCCESS;
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_RWL_Check(rwl_handle_ptr,
		(error_text != NULL) ? tmp_error_text : NULL)) != MTIF_SUCCESS)
		;
	else if (MTIF_RWL_OWNER_IS_SELF(rwl_handle_ptr) == MTIF_TRUE) {
		if (error_text != NULL)
			chrcat(val2str_ulong_cat(MTIF_THR_Self(), 10, "",
				strcat(strcpy(tmp_error_text,
				"Failed attempt to re-enter a reader/writer lock with "),
				"'MTIF_RWL_LockWriter()' on thread identifier ")), '.');
			return_code = MTIF_OP_FAILURE_RWL;
	}
	else
		return_code = MTIF_RWL_LockWriterFacility(rwl_handle_ptr,
			(error_text != NULL) ? tmp_error_text : NULL);

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform 'MTIF_RWL_LockWriter()' failed: "),
			tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

#ifdef _Windows
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_LockReaderFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_LockReaderFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	HANDLE tmp_handle;
	char   rwl_name[511 + 1];

	if (rwl_handle_ptr->static_flag == MTIF_TRUE) {
		val2str_ptr0_cat(rwl_handle_ptr,
			strcat(val2str_ulong_cat(MTIF_THR_SelfProcess(), 10, "0",
			strcpy(rwl_name, "MTIF_RWL_WIN32_PRIVATE_NAME_ProcessId=")),
			"___MutexAddress="));
		if ((return_code = MTIF_SUPP_WIN32_CreateMutex(MTIF_TRUE, rwl_name,
			&tmp_handle, error_text)) == MTIF_SUCCESS) {
			if (GetLastError() == ERROR_ALREADY_EXISTS) {
				CloseHandle(tmp_handle);
				while ((rwl_handle_ptr->static_flag == MTIF_TRUE) ||
					(rwl_handle_ptr->rwl_data == ((HANDLE) 0)))
					MTIF_THR_Yield();
				return_code = MTIF_RWL_LockReader(rwl_handle_ptr, error_text);
			}
			else {
				rwl_handle_ptr->rwl_data    = tmp_handle;
				rwl_handle_ptr->static_flag = MTIF_FALSE;
				rwl_handle_ptr->process_id  = MTIF_THR_SelfProcess();
				rwl_handle_ptr->thread_id   = MTIF_THR_Self();
				return_code                 = MTIF_SUCCESS;
			}
		}
	}
	else if ((return_code = MTIF_SUPP_WIN32_WaitForSingleObject(
		rwl_handle_ptr->rwl_data, INFINITE, error_text)) == MTIF_SUCCESS) {
		rwl_handle_ptr->process_id = MTIF_THR_SelfProcess();
		rwl_handle_ptr->thread_id  = MTIF_THR_Self();
		return_code                = MTIF_SUCCESS;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_LockWriterFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_LockWriterFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int    return_code;
	HANDLE tmp_handle;
	char   rwl_name[511 + 1];

	if (rwl_handle_ptr->static_flag == MTIF_TRUE) {
		val2str_ptr0_cat(rwl_handle_ptr,
			strcat(val2str_ulong_cat(MTIF_THR_SelfProcess(), 10, "0",
			strcpy(rwl_name, "MTIF_RWL_WIN32_PRIVATE_NAME_ProcessId=")),
			"___MutexAddress="));
		if ((return_code = MTIF_SUPP_WIN32_CreateMutex(MTIF_TRUE, rwl_name,
			&tmp_handle, error_text)) == MTIF_SUCCESS) {
			if (GetLastError() == ERROR_ALREADY_EXISTS) {
				CloseHandle(tmp_handle);
				while ((rwl_handle_ptr->static_flag == MTIF_TRUE) ||
					(rwl_handle_ptr->rwl_data == ((HANDLE) 0)))
					MTIF_THR_Yield();
				return_code = MTIF_RWL_LockWriter(rwl_handle_ptr, error_text);
			}
			else {
				rwl_handle_ptr->rwl_data    = tmp_handle;
				rwl_handle_ptr->static_flag = MTIF_FALSE;
				rwl_handle_ptr->process_id  = MTIF_THR_SelfProcess();
				rwl_handle_ptr->thread_id   = MTIF_THR_Self();
				return_code                 = MTIF_SUCCESS;
			}
		}
	}
	else if ((return_code = MTIF_SUPP_WIN32_WaitForSingleObject(
		rwl_handle_ptr->rwl_data, INFINITE, error_text)) == MTIF_SUCCESS) {
		rwl_handle_ptr->process_id = MTIF_THR_SelfProcess();
		rwl_handle_ptr->thread_id  = MTIF_THR_Self();
		return_code                = MTIF_SUCCESS;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_UI_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_LockReaderFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_LockReaderFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = rw_rdlock(&rwl_handle_ptr->rwl_data))) {
		rwl_handle_ptr->process_id = MTIF_THR_SelfProcess();
		rwl_handle_ptr->thread_id  = MTIF_THR_Self();
		return_code                = MTIF_SUCCESS;
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'rw_rdlock()' failed: "));
		return_code = MTIF_OP_FAILURE_RWL;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_LockWriterFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_LockWriterFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = rw_wrlock(&rwl_handle_ptr->rwl_data))) {
		rwl_handle_ptr->process_id = MTIF_THR_SelfProcess();
		rwl_handle_ptr->thread_id  = MTIF_THR_Self();
		return_code                = MTIF_SUCCESS;
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'rw_wrlock()' failed: "));
		return_code = MTIF_OP_FAILURE_RWL;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_POSIX_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_LockReaderFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_LockReaderFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = pthread_mutex_lock(&rwl_handle_ptr->rwl_data))) {
		rwl_handle_ptr->process_id = MTIF_THR_SelfProcess();
		rwl_handle_ptr->thread_id  = MTIF_THR_Self();
		return_code                = MTIF_SUCCESS;
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'pthread_mutex_lock()' failed: "));
		return_code = MTIF_OP_FAILURE_RWL;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_LockWriterFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_LockWriterFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = pthread_mutex_lock(&rwl_handle_ptr->rwl_data))) {
		rwl_handle_ptr->process_id = MTIF_THR_SelfProcess();
		rwl_handle_ptr->thread_id  = MTIF_THR_Self();
		return_code                = MTIF_SUCCESS;
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'pthread_mutex_lock()' failed: "));
		return_code = MTIF_OP_FAILURE_RWL;
	}

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_LockReaderFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_LockReaderFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (error_text != NULL)
		strcpy(error_text,
			"Function 'MTIF_RWL_LockReader()' not supported.");

	return_code = MTIF_OP_FAILURE_RWL;

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_LockWriterFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_LockWriterFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (error_text != NULL)
		strcpy(error_text,
			"Function 'MTIF_RWL_LockWriter()' not supported.");

	return_code = MTIF_OP_FAILURE_RWL;

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifdef _Windows */

