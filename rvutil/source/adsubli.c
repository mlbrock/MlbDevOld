/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Adds a subject to an environment and begins
								listening to the subject.

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

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_AddSubListen(RVUTIL_ENV *env_ptr, const char *subject_name,
	rv_Callback call_back, rv_Opaque closure, unsigned int *sub_index,
	char *error_text)
{
	int          return_code;
	unsigned int tmp_sub_index;

	sub_index = (sub_index == NULL) ? &tmp_sub_index : sub_index;

	if ((return_code = RVUTIL_AddSub(env_ptr, subject_name, call_back,
		sub_index, error_text)) == RVUTIL_SUCCESS) {
		if ((return_code = RVUTIL_ListenSub(env_ptr, closure, *sub_index,
			error_text)) != RVUTIL_SUCCESS)
			RVUTIL_RemoveSub(env_ptr, *sub_index, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_AddSubListListen(RVUTIL_ENV *env_ptr, unsigned int subject_count,
	char **subject_list, rv_Callback call_back, rv_Opaque closure,
	char *error_text)
{
	int          return_code = RVUTIL_SUCCESS;
	unsigned int count_1;
	unsigned int found_index;
	char         tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	for (count_1 = 0; count_1 < subject_count; count_1++) {
		if ((return_code = RVUTIL_AddSubListen(env_ptr, subject_list[count_1],
			call_back, closure, NULL, tmp_error_text)) != RVUTIL_SUCCESS) {
			sprintf(error_text,
				"Unable to add list of %u subjects to RV environment: %s",
				subject_count, tmp_error_text);
			for ( ; count_1 > 0; count_1--) {
				if (RVUTIL_FindSubByName(env_ptr, subject_list[count_1 - 1],
					&found_index) != NULL)
					RVUTIL_RemoveSub(env_ptr, found_index, tmp_error_text);
			}
			break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

