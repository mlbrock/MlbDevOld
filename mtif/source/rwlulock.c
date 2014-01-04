/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Unlocks a reader/writer lock.

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
COMPAT_FN_DECL_STATIC(int MTIF_RWL_UnlockFacility,
	(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_RWL_Unlock(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text)
#else
int MTIF_RWL_Unlock(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MTIF_SUCCESS;
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_RWL_Check(rwl_handle_ptr,
		(error_text != NULL) ? tmp_error_text : NULL)) == MTIF_SUCCESS)
		return_code = MTIF_RWL_UnlockBasic(rwl_handle_ptr,
			(error_text != NULL) ? tmp_error_text : NULL);

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform 'MTIF_RWL_Unlock()' failed: "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

/*
	ADF NOTE:	Aside from ``MTIF_RWL_Unlock``, this function is used only by
					internal functions to unlock disabled reader/writer locks at
					the time of their destruction. See ``MTIF_RWL_Destroy``.
*/
/* *********************************************************************** */
#ifndef NARGS
int MTIF_RWL_UnlockBasic(MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text)
#else
int MTIF_RWL_UnlockBasic(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;

	if (MTIF_RWL_OWNER_IS_SELF(rwl_handle_ptr) != MTIF_TRUE) {
		if (error_text != NULL)
			chrcat(val2str_ulong_cat(MTIF_THR_Self(), 10, "",
				strcat(strcpy(error_text,
				"Failed attempt to unlock a reader/writer lock with "),
				"'MTIF_RWL_Unlock' on thread identifier ")), '.');
			return_code = MTIF_OP_FAILURE_RWL;
	}
	else {
		rwl_handle_ptr->process_id = 0L;
		rwl_handle_ptr->thread_id  = 0;
		return_code = MTIF_RWL_UnlockFacility(rwl_handle_ptr, error_text);
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef _Windows
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_UnlockFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_UnlockFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	return(MTIF_SUPP_WIN32_ReleaseMutex(rwl_handle_ptr->rwl_data, error_text));
}
/* *********************************************************************** */

#elif MTIF_THR_UI_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_UnlockFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_UnlockFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;

	if (!(return_code = rw_unlock(&rwl_handle_ptr->rwl_data)))
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'rw_unlock()' failed: "));
		return_code = MTIF_OP_FAILURE_RWL;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_POSIX_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_UnlockFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_UnlockFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;

	if (!(return_code = pthread_mutex_unlock(&rwl_handle_ptr->rwl_data)))
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'pthread_mutex_unlock()' failed: "));
		return_code = MTIF_OP_FAILURE_RWL;
	}

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_RWL_UnlockFacility(MTIF_RWL_HANDLE *rwl_handle_ptr,
	char *error_text)
#else
static int MTIF_RWL_UnlockFacility(rwl_handle_ptr, error_text)
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;

	if (error_text != NULL)
		strcpy(error_text, "Function 'MTIF_RWL_Unlock()' not supported.");

	return_code = MTIF_OP_FAILURE_RWL;

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifdef _Windows */

