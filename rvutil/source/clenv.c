/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes an environment.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
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
void RVUTIL_CloseEnv(RVUTIL_ENV *env_ptr, int expedite_flag)
{
	RVUTIL_EndEnv(env_ptr, expedite_flag);

	if (env_ptr->context != NULL) {
		RVUTIL_rvevm_Destroy(env_ptr->context, NULL, NULL);
		env_ptr->context = NULL;
	}

	RVUTIL_FreeEnv(env_ptr);
}
/*	***********************************************************************	*/

