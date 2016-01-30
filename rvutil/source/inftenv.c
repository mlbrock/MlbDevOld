/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes a fault tolerant environment.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_InitFTEnv(RVUTIL_FT_ENV *env_ptr)
{
	memset(env_ptr, '\0', sizeof(*env_ptr));

	RVUTIL_InitEnv(&env_ptr->env);

	env_ptr->group_name[0]        = '\0';
   env_ptr->weight               = 0L;
   env_ptr->active_goal          = 0L;
   env_ptr->heart_beat_interval  = 0L;
   env_ptr->preparation_interval = 0L;
   env_ptr->activation_interval  = 0L;
	env_ptr->group_id             = NULL;
   env_ptr->call_back_function   = NULL;
}
/*	***********************************************************************	*/

