/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a basic check of an 'RVUTIL_FT_ENV'
								structure.

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

#include <string.h>

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CheckFTEnv(const RVUTIL_FT_ENV *env_ptr, char *error_text)
{
	int  return_code;
	char tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	if ((return_code = RVUTIL_CheckSubjectNameIsFull(env_ptr->group_name,
		tmp_error_text)) != RVUTIL_SUCCESS)
		nstrcat(strcpy(error_text,
			"Invalid Rendezvous fault-tolerance group name: "), tmp_error_text,
			RVUTIL_MAX_ERROR_TEXT - 100);
	else if ((env_ptr->weight < RVUTIL_FT_WEIGHT_MIN) ||
		(env_ptr->weight > RVUTIL_FT_WEIGHT_MAX)) {
		sprintf(error_text,
			"%s ('%lu'): valid range is '%lu' to '%lu', inclusive.",
			"Invalid Rendezvous fault-tolerance weight", env_ptr->weight,
			RVUTIL_FT_WEIGHT_MIN, RVUTIL_FT_WEIGHT_MAX);
		return_code = RVUTIL_BAD_ARGS_FAILURE;
	}
	else if ((env_ptr->active_goal < RVUTIL_FT_ACTIVE_GOAL_MIN) ||
		(env_ptr->active_goal > RVUTIL_FT_ACTIVE_GOAL_MAX)) {
		sprintf(error_text,
			"%s ('%lu'): valid range is '%lu' to '%lu', inclusive.",
			"Invalid Rendezvous fault-tolerance active goal",
			env_ptr->active_goal,
			RVUTIL_FT_ACTIVE_GOAL_MIN, RVUTIL_FT_ACTIVE_GOAL_MAX);
		return_code = RVUTIL_BAD_ARGS_FAILURE;
	}
	else if (!env_ptr->heart_beat_interval) {
		strcpy(error_text,
			"Invalid Rendezvous fault-tolerance heart beat interval ('0').");
		return_code = RVUTIL_BAD_ARGS_FAILURE;
	}
	else if (env_ptr->call_back_function == NULL) {
		strcpy(error_text,
			"Invalid Rendezvous fault-tolerance call-back function ('NULL').");
		return_code = RVUTIL_BAD_ARGS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

