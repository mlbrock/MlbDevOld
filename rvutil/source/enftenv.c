/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Ends a fault-tolerant environment session.

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
void RVUTIL_EndFTEnv(RVUTIL_FT_ENV *env_ptr, int expedite_flag)
{
	if (env_ptr->env.session_handle != NULL) {
		if (env_ptr->group_id != NULL) {
			RVUTIL_rvft_Withdraw(env_ptr->env.session_handle, env_ptr->group_id,
				NULL, NULL);
			env_ptr->group_id = NULL;
		}
	}

	RVUTIL_EndEnv(&env_ptr->env, expedite_flag);
}
/*	***********************************************************************	*/

