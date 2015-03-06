/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Multi-Threading Interface Facility (MTIF) Library Source File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes a reader/writer lock.

	Revision History	:	1994-09-01 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Necessary include files . . .															*/
/*	***********************************************************************	*/

#include <limits.h>
#include <stdlib.h>
#include <string.h> 

#include <strfuncs.h>

#include "mtifi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int MTIF_RWL_InitFacility, (MTIF_RWL_FLAG flags,
	const char *rwl_name, MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MTIF_RWL_Init(MTIF_RWL_FLAG flags, const char *rwl_name,
	MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text)
#else
int MTIF_RWL_Init(flags, rwl_name,  rwl_handle_ptr, error_text)
MTIF_RWL_FLAG    flags;
const char      *rwl_name;
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MTIF_BAD_ARGS_FAILURE;
	char buffer[STR_VAL2STR_MAX_LEN + 1];
	char tmp_error_text[MTIF_MAX_ERROR_TEXT];

	if (rwl_handle_ptr == NULL) {
		if (error_text != NULL)
			strcpy(tmp_error_text, "Reader/writer lock handle pointer is 'NULL'.");
	}
	else {
		memset(rwl_handle_ptr, '\0', sizeof(*rwl_handle_ptr));
		if (flags & (~MTIF_RWL_FLAG_MASK)) {
			if (error_text != NULL)
				strcat(strcat(strcpy(tmp_error_text,
					"Invalid bits set in the flags parameter ('"),
					val2str_ulong(flags & (~MTIF_RWL_FLAG_MASK), 2, "0", buffer)),
					"' binary).");
		}
		else if ((!(flags & MTIF_RWL_FLAG_IGNORE_BAD)) &&
			(flags & (~MTIF_RWL_FLAG_MASK_FACILITY))) {
			if (error_text != NULL)
				strcat(strcat(strcpy(tmp_error_text,
					"Invalid bits set in the flags parameter ('"),
					val2str_ulong(flags & (~MTIF_RWL_FLAG_MASK_FACILITY),
					2, "0", buffer)),
					"' binary) and the 'MTIF_RWL_FLAG_IGNORE_BAD' bit is not set.");
		}
		else if (rwl_name != NULL) {
			if (error_text != NULL)
				strcpy(error_text,
					"MTIF does not yet support reader/writer lock names.");
		}
		else
			return_code =
				MTIF_RWL_InitFacility((flags & MTIF_RWL_FLAG_IGNORE_BAD) ?
				(flags & MTIF_RWL_FLAG_MASK_FACILITY) : flags, rwl_name,
				rwl_handle_ptr, (error_text != NULL) ? tmp_error_text : NULL);
	}

	if ((return_code != MTIF_SUCCESS) && (error_text != NULL))
		strcat(strcpy(error_text,
			"Attempt to perform 'MTIF_RWL_Init()' failed: "), tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef _Windows
/*	***********************************************************************	*/
#ifndef NARGS
static int MTIF_RWL_InitFacility(MTIF_RWL_FLAG flags, const char *rwl_name,
	MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text)
#else
static int MTIF_RWL_InitFacility(flags, rwl_name, rwl_handle_ptr, error_text)
MTIF_RWL_FLAG    flags;
const char      *rwl_name;
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	rwl_name = NULL;

	if ((return_code = MTIF_SUPP_WIN32_CreateMutex(MTIF_FALSE, NULL,
		&rwl_handle_ptr->rwl_data, error_text)) == MTIF_SUCCESS) {
		rwl_handle_ptr->init_flags = flags;
		rwl_handle_ptr->signature  = MTIF_RWL_SIGNATURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

#elif MTIF_THR_UI_THREADS
/*	***********************************************************************	*/
#ifndef NARGS
static int MTIF_RWL_InitFacility(MTIF_RWL_FLAG flags, const char *rwl_name,
	MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text)
#else
static int MTIF_RWL_InitFacility(flags, rwl_name, rwl_handle_ptr, error_text)
MTIF_RWL_FLAG    flags;
const char      *rwl_name;
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = MTIF_SUCCESS;
	int  error_code;
	long init_flags;

	init_flags = (flags & MTIF_RWL_FLAG_SHARED) ? USYNC_PROCESS : USYNC_THREAD;

	rwl_name   = NULL;

	if (!(error_code = rwlock_init(&rwl_handle_ptr->rwl_data, init_flags,
		NULL)) {
		rwl_handle_ptr->init_flags = flags;
		rwl_handle_ptr->signature  = MTIF_RWL_SIGNATURE;
	}
	else {
		if (error_text != NULL)
			MTIF_SUPP_AppendSpecErrorString(error_code,
				strcpy(error_text, "Call to 'rwlock_init()' failed: "));
		return_code = MTIF_OP_FAILURE_RWL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

#elif MTIF_THR_POSIX_THREADS
/*	***********************************************************************	*/
#ifndef NARGS
static int MTIF_RWL_InitFacility(MTIF_RWL_FLAG flags, const char *rwl_name,
	MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text)
#else
static int MTIF_RWL_InitFacility(flags, rwl_name, rwl_handle_ptr, error_text)
MTIF_RWL_FLAG    flags;
const char      *rwl_name;
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int                  return_code = MTIF_SUCCESS;
	pthread_mutexattr_t *attr_ptr    = NULL;
	int                  error_code  = 0;
	pthread_mutexattr_t  attr_data;

	rwl_name = NULL;

	if (flags & MTIF_RWL_FLAG_SHARED) {
		if ((error_code = pthread_mutexattr_init(&attr_data)) != 0) {
			if (error_text != NULL)
				strcpy(error_text, "Call to 'pthread_mutexattr_init()' failed: ");
			return_code = MTIF_OP_FAILURE_RWL;
		}
		else {
			attr_ptr = &attr_data;
			if ((error_code = pthread_mutexattr_setpshared(attr_ptr,
				PTHREAD_PROCESS_SHARED)) != 0) {
				strcat(strcpy(error_text,
					"Call to 'pthread_mutexattr_init()' "),
					"for 'PTHREAD_PROCESS_SHARED' failed: ");
				return_code = MTIF_OP_FAILURE_RWL;
			}
		}
	}

	if ((return_code == MTIF_SUCCESS) &&
		(!(error_code = pthread_mutex_init(&rwl_handle_ptr->rwl_data,
		attr_ptr)))) {
		rwl_handle_ptr->init_flags = flags;
		rwl_handle_ptr->signature  = MTIF_RWL_SIGNATURE;
	}
	else {
		if (error_text != NULL)
			strcpy(error_text, "Call to 'pthread_mutex_init()' failed: ");
		return_code = MTIF_OP_FAILURE_RWL;
	}

	if (return_code != MTIF_SUCCESS)
		MTIF_SUPP_AppendSpecErrorString(error_code, error_text);

	if (attr_ptr != NULL)
		pthread_mutexattr_destroy(&attr_data);

	return(return_code);
}
/*	***********************************************************************	*/

#else
/*	***********************************************************************	*/
#ifndef NARGS
static int MTIF_RWL_InitFacility(MTIF_RWL_FLAG flags, const char *rwl_name,
	MTIF_RWL_HANDLE *rwl_handle_ptr, char *error_text)
#else
static int MTIF_RWL_InitFacility(flags, rwl_name, rwl_handle_ptr, error_text)
MTIF_RWL_FLAG    flags;
const char      *rwl_name;
MTIF_RWL_HANDLE *rwl_handle_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	rwl_name   = NULL;

	if (error_text != NULL)
		strcpy(error_text, "Function 'MTIF_RWL_Init()' not supported.");

	return(MTIF_OP_FAILURE_RWL);
}
/*	***********************************************************************	*/
#endif /* #ifdef _Windows */

#ifdef TEST_MAIN

#include <stdio.h>

#include <sdtif.h>

#define TEST_ITERATION_COUNT				10
#define TEST_THREAD_COUNT					100

typedef struct {
	unsigned int     thread_index;
	unsigned long    sleep_usecs;
	MTIF_RWL_HANDLE *rwl_ptr;
} TEST_DATA;

COMPAT_FN_DECL(       int   main, (int argc, char **argv));
COMPAT_FN_DECL_STATIC(int   TEST_DoIterations, (unsigned int iteration_count,
	unsigned int thread_count, MTIF_THR_HANDLE *thread_list,
	TEST_DATA *data_list, MTIF_THR_FLAG flags, unsigned long sleep_modulus,
	MTIF_RWL_HANDLE *rwl_ptr, char *error_text));
COMPAT_FN_DECL_STATIC(void *TEST_StartFunc, (TEST_DATA *start_data));
COMPAT_FN_DECL_STATIC(void  TEST_ShowData, (const TEST_DATA *start_data));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int              return_code     = MTIF_SUCCESS;
	unsigned int     iteration_count = TEST_ITERATION_COUNT;
	unsigned int     thread_count    = TEST_THREAD_COUNT;
	unsigned long    sleep_modulus   = 10L;
	MTIF_THR_HANDLE *thread_list     = NULL;
	TEST_DATA       *data_list       = NULL;
	MTIF_THR_FLAG    flags           = MTIF_THR_FLAG_DEFAULT;
	MTIF_RWL_HANDLE  rwl_static      = MTIF_RWL_STATIC_INIT;
	MTIF_RWL_HANDLE  rwl_dynamic;
	unsigned int     count_1;
	char             error_text[MTIF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness routine for 'MTIF_RWL_Init()'\n");
	fprintf(stderr, "                         'MTIF_RWL_LockReader()'\n");
	fprintf(stderr, "                         'MTIF_RWL_LockWriter()'\n");
	fprintf(stderr, "                         'MTIF_RWL_Unlock()'\n");
	fprintf(stderr, "                         'MTIF_RWL_Destroy()'\n");
	fprintf(stderr, "---- ------- ------- --- --------------------\n\n");

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

	sleep_modulus = (thread_count < 100) ? ((unsigned long) thread_count) :
		10L;

	printf("================ ==========\n");
	printf("Iteration Count: %10u\n",  iteration_count);
	printf("Thread Count   : %10u\n",  thread_count);
	printf("Sleep Modulus  : %10lu\n", sleep_modulus);
	printf("================ ==========\n\n");

	if ((thread_list = ((MTIF_THR_HANDLE *) calloc(thread_count,
		sizeof(MTIF_THR_HANDLE)))) == NULL) {
		STR_AllocMsgList(thread_count, sizeof(MTIF_THR_HANDLE), error_text,
			"Unable to allocate thread handle list");
		return_code = MTIF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((data_list = ((TEST_DATA *) calloc(thread_count,
		sizeof(TEST_DATA)))) == NULL) {
		STR_AllocMsgList(thread_count, sizeof(TEST_DATA), error_text,
			"Unable to allocate the per-thread test data list");
		return_code = MTIF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = MTIF_RWL_Init(MTIF_RWL_FLAG_DEFAULT,
		NULL, &rwl_dynamic, error_text)) != MTIF_SUCCESS)
		goto EXIT_FUNCTION;

	/*	*****************************************************************
		*****************************************************************
		Dynamic process reader/writer lock tests . . .
		*****************************************************************	*/
	flags &= (~MTIF_THR_FLAG_DETACHED);
	if ((return_code = TEST_DoIterations(iteration_count, thread_count,
		thread_list, data_list, flags, sleep_modulus, &rwl_dynamic,
		error_text)) != MTIF_SUCCESS) {
		MTIF_RWL_Destroy(&rwl_dynamic, NULL);
		goto EXIT_FUNCTION;
	}
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Recusive reader/writer lock test\n");
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	if (MTIF_RWL_LockReader(&rwl_dynamic, error_text) == MTIF_SUCCESS) {
		printf("***** First lock succceeded.\n");
		if (MTIF_RWL_TryLockReader(&rwl_dynamic, error_text) != MTIF_SUCCESS) {
			printf("***** Second lock failed: %s\n", error_text);
			printf("***** EXPECTED BEHAVIOR FOR NON-RECURSIVE R/W LOCK\n");
		}
		else {
			printf("***** Second lock succeeded.\n");
			printf("***** NOT EXPECTED BEHAVIOR FOR NON-RECURSIVE R/W LOCK\n");
			MTIF_RWL_Unlock(&rwl_dynamic, error_text);
		}
		MTIF_RWL_Unlock(&rwl_dynamic, error_text);
	}
	else
		printf("***** First lock failed: %s\n", error_text);
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	return_code = MTIF_RWL_Destroy(&rwl_dynamic, error_text);
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Static process reader/writer lock tests . . .
		*****************************************************************	*/
	flags &= (~MTIF_THR_FLAG_DETACHED);
	if ((return_code = TEST_DoIterations(iteration_count, thread_count,
		thread_list, data_list, flags, sleep_modulus, &rwl_static,
		error_text)) != MTIF_SUCCESS)
		goto EXIT_FUNCTION;

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	printf("Recusive reader/writer lock test\n");
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	if (MTIF_RWL_LockReader(&rwl_static, error_text) == MTIF_SUCCESS) {
		printf("***** First lock succceeded.\n");
		if (MTIF_RWL_TryLockReader(&rwl_static, error_text) != MTIF_SUCCESS) {
			printf("***** Second lock failed: %s\n", error_text);
			printf("***** EXPECTED BEHAVIOR FOR NON-RECURSIVE R/W LOCK\n");
		}
		else {
			printf("***** Second lock succeeded.\n");
			printf("***** NOT EXPECTED BEHAVIOR FOR NON-RECURSIVE R/W LOCK\n");
			MTIF_RWL_Unlock(&rwl_static, error_text);
		}
		MTIF_RWL_Unlock(&rwl_static, error_text);
	}
	else
		printf("***** First lock failed: %s\n", error_text);
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	/*	*****************************************************************	*/

EXIT_FUNCTION:

	if (thread_list != NULL)
		free(thread_list);

	if (data_list != NULL)
		free(data_list);

	if (return_code != MTIF_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#ifndef NARGS
static int TEST_DoIterations(unsigned int iteration_count,
	unsigned int thread_count, MTIF_THR_HANDLE *thread_list,
	TEST_DATA *data_list, MTIF_THR_FLAG flags, unsigned long sleep_modulus,
	MTIF_RWL_HANDLE *rwl_ptr, char *error_text)
#else
static int TEST_DoIterations(iteration_count, thread_count, thread_list,
	data_list, flags, sleep_modulus, rwl_ptr, error_text)
unsigned int     iteration_count;
unsigned int     thread_count;
MTIF_THR_HANDLE *thread_list;
TEST_DATA       *data_list;
MTIF_THR_FLAG    flags;
unsigned long    sleep_modulus;
MTIF_RWL_HANDLE *rwl_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = MTIF_SUCCESS;
	unsigned int count_1;
	unsigned int count_2;
	char         tmp_error_text[MTIF_MAX_ERROR_TEXT];

	flags &= (~MTIF_THR_FLAG_DETACHED);

	for (count_1 = 0; count_1 < iteration_count; count_1++) {
		fprintf(stderr, "Iteration %5u:\n", count_1 + 1);
		for (count_2 = 0; count_2 < thread_count; count_2++) {
			data_list[count_2].thread_index = count_2;
			data_list[count_2].sleep_usecs  =
				((rand() % sleep_modulus) + 1L) * 1000000L;
			data_list[count_2].rwl_ptr    = rwl_ptr;
			if ((return_code = MTIF_THR_Create(flags, 0,
				((MTIF_THR_StartFunc) TEST_StartFunc), data_list + count_2,
				thread_list + count_2, tmp_error_text)) != MTIF_SUCCESS) {
				sprintf(error_text, "%s (index %u) failed: %s",
					"Attempt to create new thread", count_2, tmp_error_text);
fprintf(stderr, "********** Created only %u of %u threads: %s\n",
	count_2, thread_count, error_text);
thread_count = count_2;
break;
				goto EXIT_FUNCTION;
			}
		}
		for (count_2 = 0; count_2 < thread_count; count_2++) {
			if ((return_code = MTIF_THR_Join(thread_list + count_2,
				NULL, tmp_error_text)) != MTIF_SUCCESS) {
TEST_ShowData(data_list + count_2);
				sprintf(error_text, "%s %lu (index %u) failed: %s",
					"Attempt to join on thread id",
					((unsigned long) MTIF_THR_GET_OS_ID(thread_list + count_2)),
					count_2, tmp_error_text);
				goto EXIT_FUNCTION;
			}
		}
		fprintf(stderr, "********** All %u threads have been joined.\n",
			thread_count);
	}

EXIT_FUNCTION:

	return(return_code);
}

#ifndef NARGS
static void *TEST_StartFunc(TEST_DATA *start_data)
#else
static void *TEST_StartFunc(start_data)
TEST_DATA *start_data;
#endif /* #ifndef NARGS */
{
	int  return_code;
	char error_text[MTIF_MAX_ERROR_TEXT];

	SDTIF_usleep(start_data->sleep_usecs);

	if ((return_code = MTIF_RWL_LockReader(start_data->rwl_ptr, error_text)) !=
		MTIF_SUCCESS)
		fprintf(stderr,
			"ERROR ON 'MTIF_RWL_LockReader()' FOR THREAD INDEX %u, ID %lu: %s\n",
			start_data->thread_index, ((unsigned long) MTIF_THR_Self()),
			error_text);
	else {
		fprintf(stderr,
	"Thread index %5u (id = %5lu) releasing %sstatic reader/writer mutex.\n",
			start_data->thread_index, ((unsigned long) MTIF_THR_Self()),
			(MTIF_RWL_IS_STATIC(start_data->rwl_ptr)) ? "" : "non-");
		if ((return_code = MTIF_RWL_Unlock(start_data->rwl_ptr, error_text)) !=
			MTIF_SUCCESS)
			fprintf(stderr,
				"ERROR ON 'MTIF_RWL_Unlock()' FOR THREAD INDEX %u, ID %lu: %s\n",
				start_data->thread_index, ((unsigned long) MTIF_THR_Self()),
				error_text);
	}

	if (return_code != MTIF_SUCCESS) {
		TEST_ShowData(start_data);
		exit(-1);
	}

	return(start_data);
}

#ifndef NARGS
static void  TEST_ShowData(const TEST_DATA *start_data)
#else
static void TEST_ShowData(start_data)
const TEST_DATA *start_data;
#endif /* #ifndef NARGS */
{
	char buffer[STR_VAL2STR_MAX_LEN + 1];

	fprintf(stderr, "********** signature   =  0x%08lX = 0b%s\n",
		start_data->rwl_ptr->signature,
		val2str_ulong(start_data->rwl_ptr->signature, 2, "0", buffer));
	fprintf(stderr, "********** init_flags  =  0x%08lX = 0b%s\n",
		start_data->rwl_ptr->init_flags,
		val2str_ulong(start_data->rwl_ptr->init_flags, 2, "0", buffer));
	fprintf(stderr, "********** static_flag = %11d\n",
		start_data->rwl_ptr->static_flag);
	fprintf(stderr, "********** process_id  = %11lu\n",
		start_data->rwl_ptr->process_id);
	fprintf(stderr, "********** thread_id   = %11lu\n",
		((unsigned long) start_data->rwl_ptr->thread_id));
#ifdef _Windows
	fprintf(stderr, "********** rwl_data    = %11lu\n",
		((unsigned long) start_data->rwl_ptr->rwl_data));
	fprintf(stderr, "********** rwl_name    =  %s\n",
		(start_data->rwl_ptr->rwl_name == NULL) ? "*** NONE ***" :
		start_data->rwl_ptr->rwl_name);
#else
	fprintf(stderr, "********** rwl_data    = %11lu\n",
		((unsigned long) &start_data->rwl_ptr->rwl_data));
#endif /* #ifdef _Windows */
}

#endif /* #ifdef TEST_MAIN */

