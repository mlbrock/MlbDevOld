/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Begins listening to a subject.

	Revision History	:	1996-02-18 --- Creation
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
int RVUTIL_ListenSub(RVUTIL_ENV *env_ptr, rv_Opaque closure,
	unsigned int sub_index, char *error_text)
{
	int         return_code;
	char        snd_text[RVUTIL_MAX_ERROR_TEXT];
	RVUTIL_SUB *sub_ptr;

	if ((return_code = RVUTIL_CheckEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS) {
		RVUTIL_SNDToStr(env_ptr, snd_text);
		sub_ptr = env_ptr->sub_list + sub_index;
		if (sub_index >= env_ptr->sub_count) {
			sprintf(error_text, "Invalid subject index (%u).",
				sub_index);
			return_code = RVUTIL_FAILURE;
		}
		else if (env_ptr->sub_list[sub_index].listen_id != NULL) {
			sprintf(error_text, "Already listening to subject '%s'.",
				sub_ptr->subject_name);
			return_code = RVUTIL_FAILURE;
		}
		else if (env_ptr->session_handle == NULL) {
			sprintf(error_text,
				"Unable to begin listening to subject '%s': %s %s.",
				sub_ptr->subject_name, "no session has been started on",
				snd_text);
			return_code = RVUTIL_FAILURE;
		}
		else
			return_code = RVUTIL_rv_ListenSubject(env_ptr->session_handle,
				&sub_ptr->listen_id, sub_ptr->subject_name,
				sub_ptr->call_back_function, closure, NULL, error_text);

	}

	return(return_code);
}
/*	***********************************************************************	*/

