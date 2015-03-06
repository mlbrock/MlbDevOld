/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Begins listening on the subject for an environment.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_BeginListenEnv(RVUTIL_ENV *env_ptr, void *user_data_ptr,
	char *error_text)
{
	int          return_code;
	unsigned int done_count;
	unsigned int count_1;
	char         snd_text[RVUTIL_MAX_ERROR_TEXT];

	if ((return_code = RVUTIL_CheckEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS) {
		RVUTIL_SNDToStr(env_ptr, snd_text);
		if (!env_ptr->sub_count) {
			strcpy(error_text, "No subject names specified in the environment.");
			return_code = RVUTIL_BAD_ARGS_FAILURE;
		}
		else if (env_ptr->session_handle == NULL) {
			sprintf(error_text,
				"Unable to begin listening to subject names: %s %s.",
				"no session has been started on", snd_text);
			return_code = RVUTIL_BAD_ARGS_FAILURE;
		}
		else {
			done_count = 0;
			for (count_1 = 0; count_1 < env_ptr->sub_count; count_1++) {
				if ((env_ptr->sub_list[count_1].listen_id == NULL) &&
					((return_code = RVUTIL_ListenSub(env_ptr, user_data_ptr,
					count_1, error_text)) != RVUTIL_SUCCESS))
					break;
				done_count++;
			}
			if (return_code == RVUTIL_SUCCESS)
				sprintf(error_text,
					"All %u outstanding subscriptions on session %s.",
					done_count, snd_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#define TEST_SUBJECT_NAME_COUNT	100

#define TEST_SUBJECT_NAME_FMT		"TEST.ENV.SUBJECT.%u"

COMPAT_FN_DECL(int main, (void));

/*	***********************************************************************	*/
int main()
{
	int                return_code;
	unsigned int       count_1;
	RVUTIL_ENV         env;
	RVUTIL_SIGNAL_SPEC signal_spec;
	rvevm_EventId      periodic_event_id;
	char               subject_name[RVUTIL_MAX_SUB_NAME_LEN + 1];
	char               error_text[RVUTIL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for 'RVUTIL_BeginListenEnv()'\n");
	fprintf(stderr, "---- ------- --- -------------------------\n\n");

	RVUTIL_InitEnv(&env);

	for (count_1 = 0; count_1 < TEST_SUBJECT_NAME_COUNT; count_1++) {
		sprintf(subject_name, TEST_SUBJECT_NAME_FMT, count_1);
		if ((return_code = RVUTIL_AddSub(&env, subject_name, RVUTIL_TEST_Callback,
			NULL, error_text)) != RVUTIL_SUCCESS)
			goto EXIT_FUNCTION;
	}

	if ((return_code = RVUTIL_AddSub(&env, "_RV.>", RVUTIL_TEST_Callback,
		NULL, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = RVUTIL_StartSessionEnv(&env, error_text)) ==
		RVUTIL_SUCCESS) {
		fprintf(stderr, "*** %s\n", error_text);
		RVUTIL_GetDefaultSignalSpec(&signal_spec);
		if ((return_code = RVUTIL_StartSignalHandling(&signal_spec, &env,
			RVUTIL_TEST_EventCallback, &env, error_text)) == RVUTIL_SUCCESS) {
			if ((return_code = RVUTIL_rvevm_AddRepeatingTimer(env.session_handle,
				&periodic_event_id, 100L, RVUTIL_TEST_EventCallback, &env, NULL,
				error_text)) == RVUTIL_SUCCESS) {
				if ((return_code = RVUTIL_BeginListenEnv(&env, &env, error_text)) ==
					RVUTIL_SUCCESS) {
					fprintf(stderr, "*** %s\n", error_text);
					fprintf(stderr, "*** ENTERING 'rv_MainLoop()' ***\n");
					rv_MainLoop(env.session_handle);
					fprintf(stderr, "*** RETURNED FROM 'rv_MainLoop()' ***\n");
				}
			}
		}
	}

EXIT_FUNCTION:

	RVUTIL_CloseEnv(&env, RVUTIL_FALSE);

	if (return_code != RVUTIL_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

#endif /* #ifdef TEST_MAIN */

