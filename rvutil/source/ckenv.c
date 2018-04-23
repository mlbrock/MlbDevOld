/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a basic check of an 'RVUTIL_ENV' structure.

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

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_CheckEnv(const RVUTIL_ENV *env_ptr, char *error_text)
{
	int          return_code = RVUTIL_SUCCESS;
	unsigned int count_1;
	char         tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	for (count_1 = 0; count_1 < env_ptr->sub_count; count_1++) {
		if ((return_code =
			RVUTIL_CheckSubjectName(env_ptr->sub_list[count_1].subject_name,
			tmp_error_text)) != RVUTIL_SUCCESS) {
			sprintf(error_text, "Error in subject index %u: %s",
				count_1, tmp_error_text);
			break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

