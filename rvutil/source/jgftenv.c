/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Joins a group for a fault tolerant environment.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
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

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_JoinGroupFTEnv(RVUTIL_FT_ENV *env_ptr, void *user_data_ptr,
	char *error_text)
{
	int        return_code;
	rvft_Error rvft_error_code;
	char       snd_text[RVUTIL_MAX_ERROR_TEXT];

	if ((return_code = RVUTIL_CheckFTEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS) {
		RVUTIL_SNDToStr(&env_ptr->env, snd_text);
		if (env_ptr->group_id != NULL) {
			sprintf(error_text, "%s '%s' on %s (%s = 0x%lx, %s = 0x%lx).",
				"Already joined fault tolerant group", env_ptr->group_name,
				snd_text, "group id", ((unsigned long) env_ptr->group_id),
				"session handle", ((unsigned long) env_ptr->env.session_handle));
			return_code = RVUTIL_BAD_ARGS_FAILURE;
		}
		else if (env_ptr->env.session_handle == NULL) {
			sprintf(error_text, "%s '%s': %s %s.",
				"Unable to join fault tolerant group",
				env_ptr->group_name,
				"no session has been started on", snd_text);
			return_code = RVUTIL_BAD_ARGS_FAILURE;
		}
		else if ((rvft_error_code = rvft_Join(env_ptr->env.session_handle,
			&env_ptr->group_id, env_ptr->group_name,
			env_ptr->weight,
			env_ptr->active_goal,
			env_ptr->heart_beat_interval,
			env_ptr->preparation_interval,
			env_ptr->activation_interval,
			env_ptr->call_back_function, user_data_ptr)) == RVFT_OK)
			sprintf(error_text, "%s '%s' on %s (%s = 0x%lx, %s = 0x%lx).",
				"Joined fault tolerant group", env_ptr->group_name,
				snd_text, "group id", ((unsigned long) env_ptr->group_id),
				"session handle", ((unsigned long) env_ptr->env.session_handle));
		else {
			sprintf(error_text, "%s '%s' on %s failed: ",
				"Attempt to join Rendezvous fault-tolerance group",
				env_ptr->group_name, snd_text);
			sprintf(error_text + strlen(error_text),
		"%s(0x%lx, 0x%lx, \"%s\", %lu, %lu, %lu, %lu, %lu, 0x%lx, 0x%lx) = ",
				"rvft_Join", ((unsigned long) env_ptr->env.session_handle),
				((unsigned long) &env_ptr->group_id),
				env_ptr->group_name,
				env_ptr->weight,
				env_ptr->active_goal,
				env_ptr->heart_beat_interval,
				env_ptr->preparation_interval,
				env_ptr->activation_interval,
				((unsigned long) env_ptr->call_back_function),
				((unsigned long) user_data_ptr));
			chrcat(RVUTIL_FormatString_rvft_Error(env_ptr->env.session_handle,
				rvft_error_code, error_text + strlen(error_text)), '.');
			return_code = RVUTIL_RENDEZVOUS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_WithdrawFromGroupFTEnv(RVUTIL_FT_ENV *env_ptr, char *error_text)
{
	int        return_code;
	rvft_Error rvft_error_code;
	char       snd_text[RVUTIL_MAX_ERROR_TEXT];

	if ((return_code = RVUTIL_CheckFTEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS) {
		RVUTIL_SNDToStr(&env_ptr->env, snd_text);
		if (env_ptr->group_id == NULL) {
			sprintf(error_text, "%s '%s' on %s (%s = 0x%lx, %s = 0x%lx): %s.",
				"Unable to withdraw from fault tolerant group", env_ptr->group_name,
				snd_text, "group id", ((unsigned long) env_ptr->group_id),
				"session handle", ((unsigned long) env_ptr->env.session_handle),
				"not a member");
			return_code = RVUTIL_BAD_ARGS_FAILURE;
		}
		else if (env_ptr->env.session_handle == NULL) {
			sprintf(error_text, "%s '%s': %s %s.",
				"Unable to withdraw from fault tolerant group",
				env_ptr->group_name,
				"no session has been started on", snd_text);
			return_code = RVUTIL_BAD_ARGS_FAILURE;
		}
		else if ((rvft_error_code = rvft_Withdraw(env_ptr->env.session_handle,
			env_ptr->group_id)) == RVFT_OK) {
			sprintf(error_text, "%s '%s' on %s (%s = 0x%lx, %s = 0x%lx).",
				"Withdrew from fault tolerant group", env_ptr->group_name,
				snd_text, "group id", ((unsigned long) env_ptr->group_id),
				"session handle", ((unsigned long) env_ptr->env.session_handle));
			env_ptr->group_id = NULL;
		}
		else {
			sprintf(error_text, "%s '%s' on %s failed: ",
				"Attempt to withdraw from Rendezvous fault-tolerance group",
				env_ptr->group_name, snd_text);
			sprintf(error_text + strlen(error_text), "%s(0x%lx, 0x%lx) = ",
				"rvft_Withdraw", ((unsigned long) env_ptr->env.session_handle),
				((unsigned long) env_ptr->group_id));
			chrcat(RVUTIL_FormatString_rvft_Error(env_ptr->env.session_handle,
				rvft_error_code, error_text + strlen(error_text)), '.');
			return_code = RVUTIL_RENDEZVOUS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_WithdrawAndReJoinGroupFTEnv(RVUTIL_FT_ENV *env_ptr,
	void *user_data_ptr, char *error_text)
{
	int  return_code;
	char snd_text[RVUTIL_MAX_ERROR_TEXT];

	if ((return_code = RVUTIL_WithdrawFromGroupFTEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS) {
		if ((return_code = RVUTIL_JoinGroupFTEnv(env_ptr, user_data_ptr,
			error_text)) == RVUTIL_SUCCESS) {
			RVUTIL_SNDToStr(&env_ptr->env, snd_text);
			sprintf(error_text, "%s '%s' on %s (%s = 0x%lx, %s = 0x%lx).",
				"Withdrew from and re-joined fault tolerant group",
				env_ptr->group_name, snd_text, "group id",
				((unsigned long) env_ptr->group_id), "session handle",
				((unsigned long) env_ptr->env.session_handle));
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

static unsigned int  TEST_CountDown = 30;

static rvevm_EventId TEST_EventId   = NULL;

COMPAT_FN_DECL(int main, (void));

COMPAT_FN_DECL_STATIC(void RVUTIL_TEST_JGEventCallback,
	(rv_Session session, rv_Opaque closure, rvevm_EventType event_type,
	rvevm_EventId event_id));

/*	***********************************************************************	*/
int main()
{
	int                return_code;
	RVUTIL_FT_ENV      ft_env;
	RVUTIL_SIGNAL_SPEC signal_spec;
	char               error_text[RVUTIL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for 'RVUTIL_JoinGroupFTEnv()'\n");
	fprintf(stderr, "Test harness for 'RVUTIL_WithdrawFromGroupFTEnv()'\n");
	fprintf(stderr, "Test harness for 'RVUTIL_WithdrawAndReJoinGroupFTEnv()'\n");
	fprintf(stderr, "---- ------- --- --------------------------------------\n\n");

	RVUTIL_InitFTEnv(&ft_env);
	strcpy(ft_env.group_name, "TEST.FTENV.GROUP.NAME");
	ft_env.weight                 = 10L;
	ft_env.active_goal            = 1L;
	ft_env.heart_beat_interval    = 1000L;
	ft_env.preparation_interval   = 0L;
	ft_env.activation_interval    = 10000L;
	ft_env.call_back_function     = RVUTIL_TEST_FTCallback;

	if ((return_code = RVUTIL_StartSessionFTEnv(&ft_env, error_text)) ==
		RVUTIL_SUCCESS) {
		fprintf(stderr, "*** %s\n", error_text);
		RVUTIL_GetDefaultSignalSpec(&signal_spec);
		if ((return_code = RVUTIL_StartSignalHandling(&signal_spec,
			&ft_env.env, RVUTIL_TEST_JGEventCallback, &ft_env.env, error_text)) ==
			RVUTIL_SUCCESS) {
			if ((return_code =
				RVUTIL_rvevm_AddRepeatingTimer(ft_env.env.session_handle,
				&TEST_EventId, 1000L, RVUTIL_TEST_JGEventCallback, &ft_env, NULL,
				error_text)) == RVUTIL_SUCCESS) {
				if ((return_code = RVUTIL_JoinGroupFTEnv(&ft_env, &ft_env,
					error_text)) == RVUTIL_SUCCESS) {
					fprintf(stderr, "*** %s\n", error_text);
					fprintf(stderr, "*** ENTERING 'rv_MainLoop()' ***\n");
					rv_MainLoop(ft_env.env.session_handle);
					fprintf(stderr, "*** RETURNED FROM 'rv_MainLoop()' ***\n");
				}
			}
		}
		RVUTIL_CloseFTEnv(&ft_env, RVUTIL_FALSE);
	}

	if (return_code != RVUTIL_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static void RVUTIL_TEST_JGEventCallback(rv_Session session, rv_Opaque closure,
	rvevm_EventType event_type, rvevm_EventId event_id)
{
	int  return_code;
	char error_text[RVUTIL_MAX_ERROR_TEXT];

	if (event_type == RVEVM_SIGNAL_EVENT) {
		fprintf(stderr,
			"Callback [Event]          : session = 0x%p, type = '%d', id = %lu\n",
			session, event_type, ((unsigned long) event_id));
		fprintf(stderr, "********** Going down on signal . . .\n\n");
		RVUTIL_EndFTEnv(((RVUTIL_FT_ENV *) closure), RVUTIL_FALSE);
	}
	else if (event_type == RVEVM_TIMER_EVENT) {
		if (TEST_CountDown > 1)
			fprintf(stderr, "Count-down: %u seconds to go.\n", --TEST_CountDown);
		else if (TEST_CountDown == 1) {
			TEST_CountDown = 30;
			fprintf(stderr,
				"Attempting to withdraw and re-join fault tolarant group.\n");
			return_code =
				RVUTIL_WithdrawAndReJoinGroupFTEnv(((RVUTIL_FT_ENV *) closure),
				closure, error_text);
			fprintf(stderr, "%-7.7s: %s\n",
				(return_code == RVUTIL_SUCCESS) ? "SUCCESS" : "FAILURE",
				error_text);
		}
	}
}
/*	***********************************************************************	*/

#endif /* #ifdef TEST_MAIN */

