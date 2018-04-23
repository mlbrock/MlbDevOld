/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MLOG Memory-mapped Logging Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the MLOG recursive mutex locking.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <string.h>

#include <strfuncs.h>

#include "mlogi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_Lock(MLOG *mlog_ptr, char *error_text)
#else
int MLOG_Lock(MLOG *mlog_ptr, char *error_text)
#endif /* #ifndef NARGS */
{
	int  return_code;
	char mtif_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MLOG_Check(mlog_ptr, error_text)) == MLOG_SUCCESS) {
		if ((return_code = MTIF_MTR_Lock(&mlog_ptr->mtr_data,
			mtif_error_text)) != MTIF_SUCCESS) {
			if (error_text != NULL)
				nstrcat(strcpy(error_text, "Attempt to lock MLOG failed: "),
					mtif_error_text, MLOG_MAX_ERROR_TEXT - 100);
			return_code = MLOG_MAP_ERROR_MTIF(return_code);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_TryLock(MLOG *mlog_ptr, char *error_text)
#else
int MLOG_TryLock(MLOG *mlog_ptr, char *error_text)
#endif /* #ifndef NARGS */
{
	int  return_code;
	char mtif_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MLOG_Check(mlog_ptr, error_text)) == MLOG_SUCCESS) {
		if ((return_code = MTIF_MTR_TryLock(&mlog_ptr->mtr_data,
			mtif_error_text)) != MTIF_SUCCESS) {
			if (error_text != NULL)
				nstrcat(strcpy(error_text, "Attempt to try-lock MLOG failed: "),
					mtif_error_text, MLOG_MAX_ERROR_TEXT - 100);
			return_code = MLOG_MAP_ERROR_MTIF(return_code);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MLOG_Unlock(MLOG *mlog_ptr, char *error_text)
#else
int MLOG_Unlock(MLOG *mlog_ptr, char *error_text)
#endif /* #ifndef NARGS */
{
	int  return_code;
	char mtif_error_text[MTIF_MAX_ERROR_TEXT];

	if ((return_code = MLOG_Check(mlog_ptr, error_text)) == MLOG_SUCCESS) {
		if ((return_code = MTIF_MTR_Unlock(&mlog_ptr->mtr_data,
			mtif_error_text)) != MTIF_SUCCESS) {
			if (error_text != NULL)
				nstrcat(strcpy(error_text, "Attempt to unlock MLOG failed: "),
					mtif_error_text, MLOG_MAX_ERROR_TEXT - 100);
			return_code = MLOG_MAP_ERROR_MTIF(return_code);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define TEST_MLOG_FILE_NAME				"TEST_MLOG_Locking.txt"

#define TEST_ITERATION_COUNT				10
#define TEST_THREAD_COUNT					100

COMPAT_FN_DECL(int          main,           (void));
COMPAT_FN_DECL_STATIC(void *TEST_StartFunc, (void *start_data));

int main()
{
	int              return_code  = MLOG_SUCCESS;
	MLOG            *mlog_ptr     = NULL;
	MTIF_THR_FLAG    flags        = MTIF_THR_FLAG_DEFAULT;
	unsigned int     thread_count = TEST_THREAD_COUNT;
	MTIF_THR_HANDLE *thread_list  = NULL;
	unsigned int     count_1;
	char             error_text[MLOG_MAX_ERROR_TEXT];
	char             mtif_error_text[MTIF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for MLOG locking functionality\n");
	fprintf(stderr, "---- ------- --- ---- ------- -------------\n\n");

	if ((return_code = MLOG_OpenBasic(TEST_MLOG_FILE_NAME, NULL,
		"DTMUPL", "locking.c", MLOG_FLAG_MFILE, MLOG_PRIORITY_MASK,
		MLOG_PRIORITY_MASK, MLOG_PRIORITY_MASK, 0, 0, &mlog_ptr, error_text)) !=
		MLOG_SUCCESS)
		goto EXIT_FUNCTION;

	MLOG_DoSepStart(mlog_ptr);

	fprintf(stderr, "Opened test file '%s' (%lu bytes).\n",
		TEST_MLOG_FILE_NAME, MLOG_GET_FILE_LENGTH(mlog_ptr));

	if ((thread_list = ((MTIF_THR_HANDLE *) calloc(thread_count,
		sizeof(MTIF_THR_HANDLE)))) == NULL) {
		STR_AllocMsgList(thread_count, sizeof(MTIF_THR_HANDLE), error_text,
			"Unable to allocate thread handle list");
		return_code = MTIF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	fprintf(stderr, "Created %u %sdetached threads.\n", thread_count,
		(flags & MTIF_THR_FLAG_DETACHED) ? "" : "un-");
	for (count_1 = 0; count_1 < thread_count; count_1++) {
		if ((return_code = MTIF_THR_Create(flags, 0, TEST_StartFunc, mlog_ptr,
			thread_list + count_1, mtif_error_text)) != MTIF_SUCCESS) {
			sprintf(error_text, "%s (index %u) failed: %s",
				"Attempt to create new thread", count_1, mtif_error_text);
			return_code = MLOG_MAP_ERROR_MTIF(return_code);
			goto EXIT_FUNCTION;
		}
	}

	if (!(flags & MTIF_THR_FLAG_DETACHED)) {
		for (count_1 = 0; count_1 < thread_count; count_1++) {
			if ((return_code = MTIF_THR_Join(thread_list + count_1,
				NULL, mtif_error_text)) != MTIF_SUCCESS) {
				sprintf(error_text, "%s %u (index %u) failed: %s",
					"Attempt to join on thread id",
					MTIF_THR_GET_OS_ID(thread_list + count_1),
					count_1, mtif_error_text);
				return_code = MLOG_MAP_ERROR_MTIF(return_code);
				goto EXIT_FUNCTION;
			}
		}
		fprintf(stderr, "All %u threads joined.\n", thread_count);
	}
	else {
		fprintf(stderr, "--- waiting ");
		for (count_1 = 0; count_1 < 3; count_1++) {
			SDTIF_usleep(1000000L);
			fprintf(stderr, ".");
		}
		fprintf(stderr, "\n");
	}

	MLOG_DoSepEnd(mlog_ptr);

EXIT_FUNCTION:

	if (thread_list != NULL)
		free(thread_list);

	MLOG_Close(mlog_ptr, NULL);

	if (return_code != MLOG_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#ifndef NARGS
static void *TEST_StartFunc(void *start_data)
#else
static void *TEST_StartFunc(start_data)
void *start_data;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < TEST_ITERATION_COUNT; count_1++) {
		MLOG_LogInfo(((MLOG *) start_data),
			"Message posted by thread %10lu / iteration %10u of %10u.\n",
			((unsigned long) MTIF_THR_Self()), count_1 + 1, TEST_ITERATION_COUNT);
		/*
			Let another thread have its quantum . . .
		*/
		MTIF_THR_Yield();
	}

	return(start_data);
}

#endif /* #ifdef TEST_MAIN */

