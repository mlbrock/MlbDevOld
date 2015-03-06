/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes a subject.

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
int RVUTIL_CloseSub(RVUTIL_ENV *env_ptr, unsigned int sub_index,
	char *error_text)
{
	int         return_code;
	RVUTIL_SUB *sub_ptr;

	if ((return_code = RVUTIL_CheckEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS) {
		sub_ptr = env_ptr->sub_list + sub_index;
		if (sub_index >= env_ptr->sub_count) {
			sprintf(error_text, "Invalid subject index (%u).",
				sub_index);
			return_code = RVUTIL_FAILURE;
		}
		else if ((env_ptr->session_handle != NULL) &&
			(env_ptr->sub_list[sub_index].listen_id != NULL)) {
			RVUTIL_rv_Close(env_ptr->session_handle,
				env_ptr->sub_list[sub_index].listen_id, NULL, NULL);
			env_ptr->sub_list[sub_index].listen_id = NULL;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

