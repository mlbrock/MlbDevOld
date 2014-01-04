/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Starts a session for an environment.

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

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_StartSessionEnv(RVUTIL_ENV *env_ptr, char *error_text)
{
	int  return_code;
	char snd_text[RVUTIL_MAX_ERROR_TEXT];
	char tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	if ((return_code = RVUTIL_CheckEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS) {
		RVUTIL_SNDToStr(env_ptr, snd_text);
		if (env_ptr->session_handle != NULL) {
			sprintf(error_text, "Session is already started on %s (%s = 0x%lx).",
				snd_text, "session handle",
				((unsigned long) env_ptr->session_handle));
			return_code = RVUTIL_BAD_ARGS_FAILURE;
		}
		else if ((return_code = RVUTIL_rv_Init(&env_ptr->session_handle,
			(!env_ptr->service[0]) ? NULL : env_ptr->service,
			(!env_ptr->network[0]) ? NULL : env_ptr->network,
			(!env_ptr->daemon[0])  ? NULL : env_ptr->daemon, NULL,
			tmp_error_text)) == RVUTIL_SUCCESS)
			sprintf(error_text, "Initialized a session for %s (%s = 0x%lx).",
				snd_text, "session handle",
				((unsigned long) env_ptr->session_handle));
		else
			sprintf(error_text, "%s %s: %s",
				"Unable to initialize a session for", snd_text, tmp_error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_StartSessionEnvContext(RVUTIL_ENV *env_ptr, rvevm_Context context,
	char *error_text)
{
	int  return_code;
	char snd_text[RVUTIL_MAX_ERROR_TEXT];
	char tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	if (context == NULL)
		return_code = RVUTIL_StartSessionEnv(env_ptr, error_text);
	else if ((return_code = RVUTIL_CheckEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS) {
		RVUTIL_SNDToStr(env_ptr, snd_text);
		if (env_ptr->session_handle != NULL) {
			sprintf(error_text, "%s %s (%s = 0x%lx, %s = 0x%lx).",
				"Session is already started on", snd_text,
				"context handle", ((unsigned long) context),
				"session handle", ((unsigned long) env_ptr->session_handle));
			return_code = RVUTIL_BAD_ARGS_FAILURE;
		}
		else if ((return_code = RVUTIL_rv_InitSession(&env_ptr->session_handle,
			context,
			(!env_ptr->service[0]) ? NULL : env_ptr->service,
			(!env_ptr->network[0]) ? NULL : env_ptr->network,
			(!env_ptr->daemon[0])  ? NULL : env_ptr->daemon, NULL,
			tmp_error_text)) != RVUTIL_SUCCESS)
			sprintf(error_text, "%s %s (%s = 0x%lx, %s = 0x%lx): %s",
				"Unable to initialize a session for", snd_text,
				"context handle", ((unsigned long) context),
				"session handle", ((unsigned long) env_ptr->session_handle),
				tmp_error_text);
		else
			sprintf(error_text, "%s %s (%s = 0x%lx, %s = 0x%lx).",
				"Initialized a session for", snd_text,
				"context handle", ((unsigned long) context),
				"session handle", ((unsigned long) env_ptr->session_handle));
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_StartSessionEnvMakeContext(RVUTIL_ENV *env_ptr, char *error_text)
{
	int  return_code;
	char snd_text[RVUTIL_MAX_ERROR_TEXT];
	char tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	if ((return_code = RVUTIL_CheckEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS) {
		RVUTIL_SNDToStr(env_ptr, snd_text);
		if (env_ptr->context != NULL) {
			sprintf(error_text, "%s %s (%s = 0x%lx, %s = 0x%lx).",
				"Context already created on", snd_text,
				"context handle", ((unsigned long) env_ptr->context),
				"session handle", ((unsigned long) env_ptr->session_handle));
			return_code = RVUTIL_BAD_ARGS_FAILURE;
		}
		else if (env_ptr->session_handle != NULL) {
			sprintf(error_text, "%s %s (%s = 0x%lx, %s = 0x%lx).",
				"Session is already started on", snd_text,
				"context handle", ((unsigned long) env_ptr->context),
				"session handle", ((unsigned long) env_ptr->session_handle));
			return_code = RVUTIL_BAD_ARGS_FAILURE;
		}
		else if ((return_code = RVUTIL_rvevm_Make(&env_ptr->context, NULL,
			tmp_error_text)) != RVUTIL_SUCCESS)
			sprintf(error_text, "%s %s --- couldn't create a context: %s",
				"Unable to initialize a session for", snd_text, tmp_error_text);
		else if ((return_code = RVUTIL_StartSessionEnvContext(env_ptr,
			env_ptr->context, error_text)) != RVUTIL_SUCCESS) {
			RVUTIL_rvevm_Destroy(env_ptr->context, NULL, NULL);
			env_ptr->context = NULL;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

