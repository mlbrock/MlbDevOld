/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Starts a session for a fault tolerance environment.

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
int RVUTIL_StartSessionFTEnv(RVUTIL_FT_ENV *env_ptr, char *error_text)
{
	int return_code;

	if ((return_code = RVUTIL_CheckFTEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS)
		return_code = RVUTIL_StartSessionEnv(&env_ptr->env, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_StartSessionFTEnvContext(RVUTIL_FT_ENV *env_ptr,
	rvevm_Context context, char *error_text)
{
	int return_code;

	if ((return_code = RVUTIL_CheckFTEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS)
		return_code = RVUTIL_StartSessionEnvContext(&env_ptr->env,
			context, error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_StartSessionFTEnvMakeContext(RVUTIL_FT_ENV *env_ptr,
	char *error_text)
{
	int return_code;

	if ((return_code = RVUTIL_CheckFTEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS)
		return_code = RVUTIL_StartSessionEnvMakeContext(&env_ptr->env,
			error_text);

	return(return_code);
}
/*	***********************************************************************	*/

