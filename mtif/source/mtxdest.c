/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Destroys a basic mutex.

	Revision History	:	1994-09-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
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
COMPAT_FN_DECL_STATIC(int MTIF_MTX_DestroyFacility,
	(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text));
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_MTX_Destroy(MTIF_MTX_HANDLE *mtx_handle_ptr, char *error_text)
#else
int MTIF_MTX_Destroy(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MTIF_SUCCESS;
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_MTX_Lock(mtx_handle_ptr,
		(error_text != NULL) ? tmp_error_text : NULL)) == MTIF_SUCCESS) {
		if (MTIF_MTX_IS_STATIC(mtx_handle_ptr) == MTIF_TRUE) {
			MTIF_MTX_Unlock(mtx_handle_ptr, NULL);
			if (error_text != NULL)
				strcpy(tmp_error_text,
					"Static basic mutexes may not be destroyed.");
			return_code = MTIF_OP_FAILURE_MTX;
		}
		else {
			mtx_handle_ptr->signature = 0L;
			MTIF_MTX_UnlockBasic(mtx_handle_ptr, NULL);
			if ((return_code = MTIF_MTX_DestroyFacility(mtx_handle_ptr,
				(error_text != NULL) ? tmp_error_text : NULL)) == MTIF_SUCCESS)
				memset(mtx_handle_ptr, '\0', sizeof(*mtx_handle_ptr));
		}
	}

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform 'MTIF_MTX_Destroy()' failed: "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

#ifdef _Windows
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTX_DestroyFacility(MTIF_MTX_HANDLE *mtx_handle_ptr,
	char *error_text)
#else
static int MTIF_MTX_DestroyFacility(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MTIF_SUPP_WIN32_CloseHandle(&mtx_handle_ptr->mtx_data,
		error_text)) == MTIF_SUCCESS) {
		if (mtx_handle_ptr->mtx_name != NULL)
			free(mtx_handle_ptr->mtx_name);
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_UI_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTX_DestroyFacility(MTIF_MTX_HANDLE *mtx_handle_ptr,
	char *error_text)
#else
static int MTIF_MTX_DestroyFacility(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = mutex_destroy(&mtx_handle_ptr->mtx_data)))
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'mutex_destroy()' failed: "));
		return_code = MTIF_OP_FAILURE_MTX;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_POSIX_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTX_DestroyFacility(MTIF_MTX_HANDLE *mtx_handle_ptr,
	char *error_text)
#else
static int MTIF_MTX_DestroyFacility(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if (!(return_code = pthread_mutex_destroy(&mtx_handle_ptr->mtx_data)))
		return_code = MTIF_SUCCESS;
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(return_code,
				strcpy(error_text, "Call to 'pthread_mutex_destroy()' failed: "));
		return_code = MTIF_OP_FAILURE_MTX;
	}

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_MTX_DestroyFacility(MTIF_MTX_HANDLE *mtx_handle_ptr,
	char *error_text)
#else
static int MTIF_MTX_DestroyFacility(mtx_handle_ptr, error_text)
MTIF_MTX_HANDLE *mtx_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;

	if (error_text != NULL)
		strcpy(error_text, "Function 'MTIF_MTX_Destroy()' not supported.");

	return_code = MTIF_OP_FAILURE_MTX;

	return(return_code);
}
/* *********************************************************************** */
#endif /* #ifdef _Windows */

