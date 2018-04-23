/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Ensures a function is called only once during the
								execution of a program.

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

/* *********************************************************************** */
#ifndef NARGS
int MTIF_ONC_Once(MTIF_ONC_HANDLE *once_ptr, MTIF_ONC_OnceFunc once_func,
	void *once_data, char *error_text)
#else
int MTIF_ONC_Once(once_ptr, once_func, once_data, error_text)
MTIF_ONC_HANDLE   *once_ptr;
MTIF_ONC_OnceFunc  once_func;
void              *once_data;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char tmp_error_text_1[MTIF_MAX_ERROR_TEXT];
	char tmp_error_text_2[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MTIF_ONC_Check(once_ptr, tmp_error_text_1)) !=
		MTIF_SUCCESS)
		;
	else if (once_func == NULL) {
		if (error_text != NULL)
			strcpy(tmp_error_text_1, "The 'once_func' parameter is 'NULL'.");
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
#ifdef _Windows
	else if (IsBadCodePtr(((FARPROC) once_func))) {
		if (error_text != NULL)
			strcat(val2str_ptr0_cat(((void *) ((unsigned long) once_func)),
				strcpy(tmp_error_text_1, "The 'once_func' parameter (")),
				") is invalid.");
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
#endif /* #ifdef _Windows */
	else if ((return_code = MTIF_MTX_Lock(&once_ptr->mtx_data,
		tmp_error_text_1)) == MTIF_SUCCESS) {
		if (once_ptr->once_flag == MTIF_FALSE) {
			if ((return_code = (*once_func)(once_data, tmp_error_text_2)) ==
				MTIF_SUCCESS)
				once_ptr->once_flag = MTIF_TRUE;
			else if (error_text != NULL)
				nstrcat(strcat(val2str_ptr0_cat(((void *) ((unsigned long) once_func)),
					strcpy(tmp_error_text_1, "Call to once function at ")),
					" returned an error: "), tmp_error_text_2,
					MTIF_MAX_ERROR_TEXT - 100);
		}
		MTIF_MTX_Unlock(&once_ptr->mtx_data, NULL);
	}

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		nstrcat(strcpy(error_text,
			"Attempt to perform 'MTIF_ONC_Once()' failed: "), tmp_error_text_1,
			MTIF_MAX_ERROR_TEXT - 100);

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <stdio.h>

COMPAT_FN_DECL(int main, (void));
COMPAT_FN_DECL_STATIC(int TEST_OnceFunc, (void *once_data, char *error_text));

static MTIF_ONC_HANDLE TEST_OnceLock_1 = MTIF_ONC_INIT;
static MTIF_ONC_HANDLE TEST_OnceLock_2 = MTIF_ONC_INIT;

int main()
{
	int  return_code;
	char error_text[MTIF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for function 'MTIF_ONC_Once()'\n");
	fprintf(stderr, "---- ------- --- -------- -----------------\n\n");

	if ((return_code = MTIF_ONC_Once(&TEST_OnceLock_1, TEST_OnceFunc,
		&return_code, error_text)) != MTIF_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = MTIF_ONC_Once(&TEST_OnceLock_1, TEST_OnceFunc,
		&return_code, error_text)) != MTIF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = MTIF_ONC_Once(&TEST_OnceLock_2, TEST_OnceFunc,
		NULL, error_text)) == MTIF_SUCCESS) {
		sprintf(error_text, "%s 'TEST_OnceFunc()' (%s).",
			"Failure was expected on call to test function",
			"'once_data' parameter was 'NULL'");
		return_code = MTIF_FAILURE;
		goto EXIT_FUNCTION;
	}
	else {
		printf("********** EXPECTED FAILURE: %s\n", error_text);
		if ((return_code = MTIF_ONC_Once(&TEST_OnceLock_2, TEST_OnceFunc,
			&return_code, error_text)) != MTIF_SUCCESS)
			goto EXIT_FUNCTION;
		else
			return_code = MTIF_ONC_Once(&TEST_OnceLock_2, TEST_OnceFunc,
				&return_code, error_text);
	}

EXIT_FUNCTION:

	if (return_code == MTIF_SUCCESS)
		fprintf(stderr, "\n\n********** ALL TESTS PASSED **********\n\n");
	else
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#ifndef NARGS
static int TEST_OnceFunc(void *once_data, char *error_text)
#else
static int TEST_OnceFunc(once_data, error_text)
void *once_data;
char *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = MTIF_SUCCESS;

	printf("In 'TEST_OnceFunc()': 'once_data' parameter = 0X%08lX\n",
		((unsigned long) once_data));

	if (once_data == NULL) {
		strcpy(error_text,
			"From 'TEST_OnceFunc()': Once data pointer is 'NULL'.");
		return_code = MTIF_BAD_ARGS_FAILURE;
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

