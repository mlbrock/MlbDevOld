/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Ends an environment session.

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

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_EndEnv(RVUTIL_ENV *env_ptr, int expedite_flag)
{
	unsigned int count_1;
	char         error_text[RVUTIL_MAX_ERROR_TEXT];

	if (env_ptr->session_handle != NULL) {
		if (expedite_flag != RVUTIL_TRUE) {
			for (count_1 = 0; count_1 < env_ptr->sub_count; count_1++) {
				if (env_ptr->sub_list[count_1].listen_id != NULL)
					RVUTIL_CloseSub(env_ptr, count_1, error_text);
			}
		}
		RVUTIL_rv_Term(env_ptr->session_handle, NULL, NULL);
		env_ptr->session_handle = NULL;
	}
}
/*	***********************************************************************	*/

