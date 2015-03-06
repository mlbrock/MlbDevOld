/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Removes a subject from an environment.

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

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_RemoveSub(RVUTIL_ENV *env_ptr, unsigned int sub_index,
	char *error_text)
{
	int return_code;

	if ((return_code = RVUTIL_CloseSub(env_ptr, sub_index, error_text)) ==
		RVUTIL_SUCCESS) {
		mema_remove(&env_ptr->sub_count, ((void **) &env_ptr->sub_list),
			sizeof(RVUTIL_SUB), sub_index, 1);
	}

	return(return_code);
}
/*	***********************************************************************	*/

