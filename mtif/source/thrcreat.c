/* *********************************************************************** */
/* *********************************************************************** */
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Creates a thread.

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

#include <limits.h>
#include <stdlib.h>
#include <string.h> 

#include <strfuncs.h>

#include "mtifi.h"

/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int MTIF_THR_CreateFacility, (MTIF_THR_FLAG flags,
	unsigned int stack_size, MTIF_THR_StartFunc start_func, void *start_data,
	MTIF_THR_HANDLE *thr_handle_ptr, char *error_text));
/* *********************************************************************** */

/* *********************************************************************** */
#ifdef _Windows
#include <process.h>
typedef struct {
	MTIF_THR_StartFunc  start_func;
	void               *start_data;
} MTIF_THR_WIN32_DATA;
COMPAT_FN_DECL_STATIC(void *MTIF_THR_Win32Dispatch,
	(MTIF_THR_WIN32_DATA *win32_data));
#endif /* #ifdef _Windows */
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int MTIF_THR_Create(MTIF_THR_FLAG flags, unsigned int stack_size,
	MTIF_THR_StartFunc start_func, void *start_data,
	MTIF_THR_HANDLE *thr_handle_ptr, char *error_text)
#else
int MTIF_THR_Create(flags, stack_size, start_func, start_data,
	thr_handle_ptr, error_text)
MTIF_THR_FLAG       flags;
unsigned int        stack_size;
MTIF_THR_StartFunc  start_func;
void               *start_data;
MTIF_THR_HANDLE    *thr_handle_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code = MTIF_BAD_ARGS_FAILURE;
	MTIF_THR_HANDLE thread_handle;
	char            buffer[STR_VAL2STR_MAX_LEN + 1];
	char            tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if (flags & (~MTIF_THR_FLAG_MASK)) {
		if (error_text != NULL)
			strcat(strcat(strcpy(tmp_error_text,
				"Invalid bits set in the flags parameter ('"),
				val2str_ulong(flags & (~MTIF_THR_FLAG_MASK), 2, "0", buffer)),
				"' binary).");
	}
	else if ((!(flags & MTIF_THR_FLAG_IGNORE_BAD)) &&
		(flags & (~MTIF_THR_FLAG_MASK_FACILITY))) {
		if (error_text != NULL)
			strcat(strcat(strcpy(tmp_error_text,
				"Invalid bits set in the flags parameter ('"),
				val2str_ulong(flags & (~MTIF_THR_FLAG_MASK_FACILITY), 2, "0",
				buffer)),
				"' binary) and the 'MTIF_THR_FLAG_IGNORE_BAD' bit is not set.");
	}
	else if (start_func == NULL) {
		if (error_text != NULL)
			strcpy(tmp_error_text, "Thread start function pointer is 'NULL'.");
	}
	else if ((thr_handle_ptr == NULL) &&
		(!(flags & MTIF_THR_FLAG_DETACHED))) {
		if (error_text != NULL)
			strcat(strcpy(tmp_error_text, "Thread handle pointer is 'NULL', "),
				"but the flags do not specify the detached thread attribute.");
	}
	else {
		thr_handle_ptr = (thr_handle_ptr == NULL) ?
			&thread_handle : thr_handle_ptr;
		return_code =
			MTIF_THR_CreateFacility((flags & MTIF_THR_FLAG_IGNORE_BAD) ?
			(flags & MTIF_THR_FLAG_MASK_FACILITY) : flags, stack_size,
			start_func, start_data, thr_handle_ptr, tmp_error_text);
	}

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform a 'MTIF_THR_Create()' failed: "), tmp_error_text);

	return(return_code);
}
/* *********************************************************************** */

#ifdef _Windows
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_CreateFacility(MTIF_THR_FLAG flags,
	unsigned int stack_size, MTIF_THR_StartFunc start_func, void *start_data,
	MTIF_THR_HANDLE *thr_handle_ptr, char *error_text)
#else
static int MTIF_THR_CreateFacility(flags, stack_size, start_func, start_data,
	thr_handle_ptr, error_text)
MTIF_THR_FLAG       flags;
unsigned int        stack_size;
MTIF_THR_StartFunc  start_func;
void               *start_data;
MTIF_THR_HANDLE    *thr_handle_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int                  return_code = MTIF_SUCCESS;
	unsigned int         init_flags;
	MTIF_THR_WIN32_DATA *win32_data;

	if (IsBadCodePtr(((FARPROC) start_func))) {
		strcat(val2str_ptr0_cat(((void *) ((unsigned long) start_func)),
			strcpy(error_text, "The 'start_func' parameter (")), ") is invalid.");
		return_code = MTIF_BAD_ARGS_FAILURE;
	}
	else if ((win32_data = ((MTIF_THR_WIN32_DATA *)
		calloc(1, sizeof(MTIF_THR_WIN32_DATA)))) == NULL) {
		STR_AllocMsgItem(sizeof(MTIF_THR_WIN32_DATA), error_text,
			"Unable to allocate temporary thread storage");
		return_code = MTIF_MEMORY_FAILURE;
	}
	else {
		win32_data->start_func = start_func;
		win32_data->start_data = start_data;
		init_flags             = (flags & MTIF_THR_FLAG_SUSPENDED) ?
			CREATE_SUSPENDED : 0;
#if _MSC_VER >= 1300
		thr_handle_ptr->thread_handle =
			((HANDLE) _beginthreadex(NULL, stack_size,
			((uintptr_t (__stdcall *)(void *)) MTIF_THR_Win32Dispatch),
			win32_data, init_flags,
			((unsigned int *) &thr_handle_ptr->thread_id)));
#else
		thr_handle_ptr->thread_handle =
			((HANDLE) _beginthreadex(NULL, stack_size,
			((unsigned int (__stdcall *)(void *)) MTIF_THR_Win32Dispatch),
			win32_data, init_flags,
			((unsigned int *) &thr_handle_ptr->thread_id)));
#endif /* #if _MSC_VER >= 1300 */
		if (((int) thr_handle_ptr->thread_handle) == 0) {
			MTIF_SUPP_AppendLastErrorString(strcpy(error_text,
				"Unable to create thread: "));
			return_code = MTIF_OP_FAILURE_THR;
		}
		else if (flags & MTIF_THR_FLAG_DETACHED)
			CloseHandle(thr_handle_ptr->thread_handle);
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
static void *MTIF_THR_Win32Dispatch(MTIF_THR_WIN32_DATA *win32_data)
#else
static void *MTIF_THR_Win32Dispatch(win32_data)
MTIF_THR_WIN32_DATA *win32_data;
#endif /* #ifndef NARGS */
{
	MTIF_THR_WIN32_DATA tmp_data;

	tmp_data = *win32_data;

	free(win32_data);

	_endthreadex(((unsigned int) (*tmp_data.start_func)(tmp_data.start_data)));

/* NOTREACHED */
	return(NULL);
}
/* *********************************************************************** */

#elif MTIF_THR_UI_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_CreateFacility(MTIF_THR_FLAG flags,
	unsigned int stack_size, MTIF_THR_StartFunc start_func, void *start_data,
	MTIF_THR_HANDLE *thr_handle_ptr, char *error_text)
#else
static int MTIF_THR_CreateFacility(flags, stack_size, start_func, start_data,
	thr_handle_ptr, error_text)
MTIF_THR_FLAG       flags;
unsigned int        stack_size;
MTIF_THR_StartFunc  start_func;
void               *start_data;
MTIF_THR_HANDLE    *thr_handle_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MTIF_SUCCESS;
	int  error_code;
	long init_flags;

	init_flags =
		((flags & MTIF_THR_FLAG_BOUND)     ? THR_BOUND     : 0)) |
		((flags & MTIF_THR_FLAG_DETACHED)  ? THR_DETACHED  : 0)) |
		((flags & MTIF_THR_FLAG_NEW_LWP)   ? THR_NEW_LWP   : 0)) |
		((flags & MTIF_THR_FLAG_SUSPENDED) ? THR_SUSPENDED : 0)) |
		((flags & MTIF_THR_FLAGS_DAEMON)   ? THR_DAEMON    : 0));

	if ((error_code = thr_create(NULL, stack_size, start_func, start_data,
		flags, &thr_handle_ptr)) {
		MTIF_SUPP_AppendSpecErrorString(error_code,
			strcpy(error_text, "Call to 'thr_create()' failed: "));
		return_code = MTIF_OP_FAILURE_THR;
	}

	return(return_code);
}
/* *********************************************************************** */

#elif MTIF_THR_POSIX_THREADS
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_CreateFacility(MTIF_THR_FLAG flags,
	unsigned int stack_size, MTIF_THR_StartFunc start_func, void *start_data,
	MTIF_THR_HANDLE *thr_handle_ptr, char *error_text)
#else
static int MTIF_THR_CreateFacility(flags, stack_size, start_func, start_data,
	thr_handle_ptr, error_text)
MTIF_THR_FLAG       flags;
unsigned int        stack_size;
MTIF_THR_StartFunc  start_func;
void               *start_data;
MTIF_THR_HANDLE    *thr_handle_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code = MTIF_SUCCESS;
	int             error_code  = 0;
	pthread_attr_t *attr_ptr    = NULL;
	pthread_attr_t  attr_data;

	if (stack_size ||
		((flags != MTIF_THR_FLAG_NONE) &&
		(flags != MTIF_THR_FLAG_IGNORE_BAD))) {
		return_code = MTIF_OP_FAILURE_THR;
		if ((error_code = pthread_attr_init(&attr_data)) != 0)
			strcpy(error_text, "Call to 'pthread_attr_init()' failed: ");
		else {
			attr_ptr = &attr_data;
			if ((flags & MTIF_THR_FLAG_BOUND) &&
				((error_code = pthread_attr_setscope(attr_ptr,
				PTHREAD_SCOPE_SYSTEM)) != 0))
				strcat(strcpy(error_text, "Call to 'pthread_attr_setscope()' "),
					"for 'PTHREAD_SCOPE_SYSTEM' failed: ");
			else if ((flags & MTIF_THR_FLAG_DETACHED) &&
				((error_code = pthread_attr_setdetachstate(attr_ptr,
				PTHREAD_CREATE_DETACHED)) != 0))
				strcat(strcpy(error_text,
					"Call to 'pthread_attr_setdetachstate()' "),
					"with 'PTHREAD_CREATE_DETACHED' failed: ");
			else if (stack_size &&
				((error_code = pthread_attr_setstacksize(attr_ptr, stack_size)) !=
				0))
				strcat(val2str_uint_cat(stack_size, 10, NULL, strcpy(error_text,
					"Call to 'pthread_attr_setstacksize()' with stack size of ")),
					" failed: ");
			else
				return_code = MTIF_SUCCESS;
		}
	}

	if (return_code == MTIF_SUCCESS) {
		if ((error_code = pthread_create(thr_handle_ptr, attr_ptr,
			start_func, start_data)) != 0) {
			strcpy(error_text, "Call to 'pthread_create()' failed: ");
			return_code = MTIF_OP_FAILURE_THR;
		}
	}

	if (return_code != MTIF_SUCCESS)
		MTIF_SUPP_AppendSpecErrorString(error_code, error_text);

	if (attr_ptr != NULL)
		pthread_attr_destroy(&attr_data);

	return(return_code);
}
/* *********************************************************************** */

#else
/* *********************************************************************** */
#ifndef NARGS
static int MTIF_THR_CreateFacility(MTIF_THR_FLAG flags,
	unsigned int stack_size, MTIF_THR_StartFunc start_func, void *start_data,
	MTIF_THR_HANDLE *thr_handle_ptr, char *error_text)
#else
static int MTIF_THR_CreateFacility(flags, stack_size, start_func, start_data,
	thr_handle_ptr, error_text)
MTIF_THR_FLAG       flags;
unsigned int        stack_size;
MTIF_THR_StartFunc  start_func;
void               *start_data;
MTIF_THR_HANDLE    *thr_handle_ptr;
char               *error_text;
#endif /* #ifndef NARGS */
{
	strcpy(error_text, "Function 'MTIF_THR_Create()' not supported.");

	return(MTIF_OP_FAILURE_THR);
}
/* *********************************************************************** */

#endif /* #ifdef _Windows */

#ifdef TEST_MAIN

#include <stdio.h>

#include <sdtif.h>

#define TEST_ITERATION_COUNT				10
#define TEST_THREAD_COUNT					100

static int  MTIF_TEST_ErrorCode;
static char MTIF_TEST_ErrorText[MTIF_MAX_ERROR_TEXT];

COMPAT_FN_DECL(int          main, (int argc, char **argv));
COMPAT_FN_DECL_STATIC(int   TEST_DoIterations, (unsigned int iteration_count,
	unsigned int thread_count, MTIF_THR_HANDLE *thread_list,
	MTIF_THR_FLAG flags, char *error_text));
COMPAT_FN_DECL_STATIC(void *TEST_StartFunc, (void *start_data));
COMPAT_FN_DECL_STATIC(void *TEST_JoinTestStartFunc, (void *start_data));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int              return_code     = MTIF_SUCCESS;
	int              detached_flag   = MTIF_TRUE;
	int              undetached_flag = MTIF_TRUE;
	unsigned int     iteration_count = TEST_ITERATION_COUNT;
	unsigned int     thread_count    = TEST_THREAD_COUNT;
	MTIF_THR_FLAG    flags           = MTIF_THR_FLAG_DEFAULT;
	MTIF_THR_HANDLE *thread_list     = NULL;
	MTIF_THR_HANDLE  join_test_thread;
	unsigned int     count_1;
	char             error_text[MTIF_MAX_ERROR_TEXT];
	char             tmp_error_text[MTIF_MAX_ERROR_TEXT];

MTIF_THR_FLAG thr_defaults = MTIF_THR_FLAG_DEFAULT;
MTIF_THR_FLAG thr_facility = MTIF_THR_FLAG_MASK_FACILITY;

	fprintf(stderr, "Test harness routine for 'MTIF_THR_Create()'\n");
	fprintf(stderr, "                         'MTIF_THR_Join()'\n");
	fprintf(stderr, "---- ------- ------- --- -------------------\n\n");

fprintf(stderr, "***** DEFAULTS: 0x%08lX\n", thr_defaults);
fprintf(stderr, "***** FACILITY: 0x%08lX\n", thr_facility);
#if _POSIX_THREADS
fprintf(stderr, "***** POSIX   : TRUE\n");
#else
fprintf(stderr, "***** POSIX   : FALSE\n");
#endif /* #if _POSIX_THREADS */
fprintf(stderr, "==================================================\n");

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H"))) {
			fprintf(stderr, "\n\nUSAGE:\n   %s [%s=%u [%s=%u]]\n\n",
				argv[0],
				"<iteration-count>", TEST_ITERATION_COUNT,
				"<thread-count>", TEST_THREAD_COUNT);
			goto EXIT_FUNCTION;
		}
	}

	if (argc > 1) {
		if (atoi(argv[1]) < 1) {
			sprintf(error_text, "%s ('%-.500s') --- %s.",
				"Invalid <iteration-count> command-line parameter", argv[1],
				"use '-HELP' to get usage");
			return_code = MTIF_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		iteration_count = atoi(argv[1]);
	}

	if (argc > 2) {
		if (atoi(argv[2]) < 1) {
			sprintf(error_text, "%s ('%-.500s') --- %s.",
				"Invalid <thread-count> command-line parameter", argv[2],
				"use '-HELP' to get usage");
			return_code = MTIF_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		thread_count = atoi(argv[2]);
	}

	MTIF_TEST_ErrorCode    = MTIF_SUCCESS;
	MTIF_TEST_ErrorText[0] = '\0';
	printf("Starting thread for self-join test ");
	fflush(stdout);
	if ((return_code = MTIF_THR_Create(MTIF_THR_FLAG_NONE, 0,
		TEST_JoinTestStartFunc, &join_test_thread, &join_test_thread,
		tmp_error_text)) != MTIF_SUCCESS) {
		sprintf(error_text, "%s failed: %s",
			"Attempt to create new thread for self-join test", tmp_error_text);
		goto EXIT_FUNCTION;
	}
	else if ((return_code = MTIF_THR_Join(&join_test_thread, NULL,
		tmp_error_text)) != MTIF_SUCCESS) {
		sprintf(error_text, "%s failed: %s",
			"Attempt to get status from self-join test thread", tmp_error_text);
		goto EXIT_FUNCTION;
	}
	else if (MTIF_TEST_ErrorCode == MTIF_SUCCESS) {
		sprintf(error_text, "Self-join attempt succeeded.");
		printf("Self-join attempt succeeded.");
		printf("***** NOT EXPECTED BEHAVIOR *****\n\n");
		return_code = MTIF_OP_FAILURE_THR;
		goto EXIT_FUNCTION;
	}
	else {
		printf("Self-join attempt failed with %d: %s\n",
			MTIF_TEST_ErrorCode, MTIF_TEST_ErrorText);
		printf("***** EXPECTED BEHAVIOR *****\n\n");
	}
		
	printf("================ ==========\n");
	printf("Iteration Count: %10u\n",  iteration_count);
	printf("Thread Count   : %10u\n",  thread_count);
	printf("================ ==========\n\n");

	if ((thread_list = ((MTIF_THR_HANDLE *) calloc(thread_count,
		sizeof(MTIF_THR_HANDLE)))) == NULL) {
		STR_AllocMsgList(thread_count, sizeof(MTIF_THR_HANDLE), error_text,
			"Unable to allocate thread handle list");
		return_code = MTIF_MEMORY_FAILURE;
	}
	else {
		flags |= MTIF_THR_FLAG_DETACHED;
		if (detached_flag == MTIF_TRUE) {
			if ((return_code = TEST_DoIterations(iteration_count, thread_count,
				thread_list, flags, error_text)) != MTIF_SUCCESS)
				goto EXIT_FUNCTION;
		}
		flags &= ~MTIF_THR_FLAG_DETACHED;
		if (undetached_flag == MTIF_TRUE)
			return_code = TEST_DoIterations(iteration_count, thread_count,
				thread_list, flags, error_text);
	}

EXIT_FUNCTION:

	if (thread_list != NULL)
		free(thread_list);

	if (return_code != MTIF_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#ifndef NARGS
static int TEST_DoIterations(unsigned int iteration_count,
	unsigned int thread_count, MTIF_THR_HANDLE *thread_list, MTIF_THR_FLAG flags,
	char *error_text)
#else
static int TEST_DoIterations(iteration_count, thread_count, thread_list,
	flags, error_text)
unsigned int     iteration_count;
unsigned int     thread_count;
MTIF_THR_HANDLE *thread_list;
MTIF_THR_FLAG    flags;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = MTIF_SUCCESS;
	unsigned int count_1;
	unsigned int count_2;
	char         tmp_error_text[MTIF_MAX_ERROR_TEXT];

	for (count_1 = 0; count_1 < iteration_count; count_1++) {
		fprintf(stderr, "Iteration %5u: ", count_1 + 1);
		for (count_2 = 0; count_2 < thread_count; count_2++) {
			if ((return_code = MTIF_THR_Create(flags, 0, TEST_StartFunc, NULL,
				thread_list + count_2, tmp_error_text)) !=
				MTIF_SUCCESS) {
				sprintf(error_text, "%s (index %u) failed: %s",
					"Attempt to create new thread", count_2, tmp_error_text);
/*
	CODE NOTE: To be removed.
fprintf(stderr, "********** Created only %u of %u threads: %s\n",
	count_2, thread_count, error_text);
thread_count = count_2;
break;
*/
				goto EXIT_FUNCTION;
			}
/*
	CODE NOTE: To be removed.
			else if (thread_list[count_2].thread_handle == 0) {
				sprintf(error_text, "%s (index %u) failed: %s",
					"Attempt to create new thread", count_2, "*** NULL HANDLE ***");
				return_code = MTIF_FAILURE;
				goto EXIT_FUNCTION;
			}
*/
		}
		fprintf(stderr, "created %5u %sdetached threads ", thread_count,
			(flags & MTIF_THR_FLAG_DETACHED) ? "" : "un-");
		if (!(flags & MTIF_THR_FLAG_DETACHED)) {
			for (count_2 = 0; count_2 < thread_count; count_2++) {
				if ((return_code = MTIF_THR_Join(thread_list + count_2,
					NULL, tmp_error_text)) != MTIF_SUCCESS) {
					sprintf(error_text, "%s %lu (index %u) failed: %s",
						"Attempt to join on thread id",
						((unsigned long) MTIF_THR_GET_OS_ID(thread_list + count_2)),
						count_2, tmp_error_text);
					goto EXIT_FUNCTION;
				}
			}
			fprintf(stderr, "--- joined.\n");
		}
		else {
			fprintf(stderr, "--- waiting ");
			for (count_2 = 0; count_2 < 3; count_2++) {
				SDTIF_usleep(1000000L);
				fprintf(stderr, ".");
			}
			fprintf(stderr, "\n");
		}
	}

EXIT_FUNCTION:

	return(return_code);
}

#ifndef NARGS
void *TEST_StartFunc(void *start_data)
#else
static void *TEST_StartFunc(start_data)
void *start_data;
#endif /* #ifndef NARGS */
{
	return(start_data);
}

#ifndef NARGS
void *TEST_JoinTestStartFunc(void *start_data)
#else
static void *TEST_JoinTestStartFunc(start_data)
void *start_data;
#endif /* #ifndef NARGS */
{
	printf("--- started thread %lu.\n", ((unsigned long) MTIF_THR_Self()));
	printf(">>> Attempting self-join ");
	fflush(stdout);

	MTIF_TEST_ErrorCode = MTIF_THR_Join(((MTIF_THR_HANDLE *) start_data),
		NULL, MTIF_TEST_ErrorText);

	return(start_data);
}

#endif /* #ifdef TEST_MAIN */

