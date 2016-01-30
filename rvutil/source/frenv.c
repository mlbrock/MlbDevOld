/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees an environment.

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

#include <stdlib.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_FreeEnv(RVUTIL_ENV *env_ptr)
{
	if (env_ptr->sub_list != NULL)
		free(env_ptr->sub_list);

	RVUTIL_InitEnv(env_ptr);
}
/*	***********************************************************************	*/

