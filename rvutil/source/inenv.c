/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes an environment.

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

#include <memory.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_InitEnv(RVUTIL_ENV *env_ptr)
{
	memset(env_ptr, '\0', sizeof(*env_ptr));

	env_ptr->service[0]     = '\0';
	env_ptr->network[0]     = '\0';
	env_ptr->daemon[0]      = '\0';
	env_ptr->user_data_ptr  = NULL;
	env_ptr->context        = NULL;
	env_ptr->session_handle = NULL;
	env_ptr->sub_count      = 0;
	env_ptr->sub_list       = NULL;
}
/*	***********************************************************************	*/

