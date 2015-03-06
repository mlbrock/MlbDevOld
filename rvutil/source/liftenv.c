/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Begins listening on the subject for a fault
								tolerant environment.

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

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_BeginListenFTEnv(RVUTIL_FT_ENV *env_ptr, void *user_data_ptr,
	char *error_text)
{
	int return_code;

	if ((return_code = RVUTIL_CheckFTEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS)
		return_code = RVUTIL_BeginListenEnv(&env_ptr->env, user_data_ptr,
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <string.h>

COMPAT_FN_DECL(int main, (void));

/*	***********************************************************************	*/
int main()
{
	int                return_code;
	RVUTIL_FT_ENV      ft_env;
	RVUTIL_SIGNAL_SPEC signal_spec;
	rvevm_EventId      periodic_event_id;
	char               error_text[RVUTIL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for 'RVUTIL_BeginListenFTEnv()'\n");
	fprintf(stderr, "---- ------- --- ---------------------------\n\n");

	RVUTIL_InitFTEnv(&ft_env);

	strcpy(ft_env.group_name, "TEST.FTENV.GROUP.NAME");
	ft_env.weight                 = 10L;
	ft_env.active_goal            = 1L;
	ft_env.heart_beat_interval    = 10000L;
	ft_env.preparation_interval   = 0L;
	ft_env.activation_interval    = 15000L;
	ft_env.call_back_function     = RVUTIL_TEST_FTCallback;

	if ((return_code = RVUTIL_AddSub(&ft_env.env, "_RVFT.>",
		RVUTIL_TEST_Callback, NULL, error_text)) != RVUTIL_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = RVUTIL_StartSessionFTEnv(&ft_env, error_text)) ==
		RVUTIL_SUCCESS) {
		fprintf(stderr, "*** %s\n", error_text);
		RVUTIL_GetDefaultSignalSpec(&signal_spec);
		if ((return_code = RVUTIL_StartSignalHandling(&signal_spec, &ft_env.env,
			RVUTIL_TEST_EventCallback, &ft_env, error_text)) == RVUTIL_SUCCESS) {
			if ((return_code =
				RVUTIL_rvevm_AddRepeatingTimer(ft_env.env.session_handle,
				&periodic_event_id, 100L, RVUTIL_TEST_EventCallback, &ft_env.env,
				NULL, error_text)) == RVUTIL_SUCCESS) {
				if ((return_code = RVUTIL_BeginListenFTEnv(&ft_env, &ft_env,
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

EXIT_FUNCTION:

	if (return_code != RVUTIL_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

#endif /* #ifdef TEST_MAIN */

