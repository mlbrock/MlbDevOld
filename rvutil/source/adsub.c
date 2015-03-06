/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Adds a subject to an environment.

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

#include <string.h>

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_AddSub(RVUTIL_ENV *env_ptr, const char *subject_name,
	rv_Callback call_back, unsigned int *sub_index, char *error_text)
{
	int          return_code;
	unsigned int tmp_sub_index;
	RVUTIL_SUB   tmp_sub;

	if ((return_code = RVUTIL_CheckEnv(env_ptr, error_text)) ==
		RVUTIL_SUCCESS) {
		if (call_back == NULL) {
			strcpy(error_text, "Invalid parameter: 'call_back' is 'NULL'.");
			return_code = RVUTIL_BAD_ARGS_FAILURE;
		}
		else if ((return_code = RVUTIL_CheckSubjectName(subject_name,
			error_text)) == RVUTIL_SUCCESS) {
			sub_index = (sub_index == NULL) ? &tmp_sub_index : sub_index;
			if (RVUTIL_FindSubByName(env_ptr, subject_name, sub_index) != NULL) {
				sprintf(error_text,
					"%s '%s' is already in environment subject list (index = %u).",
					"Subject name", subject_name, *sub_index);
				return_code = RVUTIL_FAILURE;
			}
			else {
				RVUTIL_InitSub(&tmp_sub);
				tmp_sub.call_back_function = call_back;
				strcpy(tmp_sub.subject_name, subject_name);
				if (mema_insert(&env_ptr->sub_count,
					((void **) &env_ptr->sub_list), &tmp_sub, sizeof(RVUTIL_SUB),
					*sub_index) != STRFUNCS_SUCCESS) {
					STR_AllocMsgList(env_ptr->sub_count + 1, sizeof(RVUTIL_SUB),
						error_text,
						"Unable to %sallocate the environment subject list",
						(env_ptr->sub_count) ? "re-" : "");
					return_code = RVUTIL_MEMORY_FAILURE;
				}
			}
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_AddSubList(RVUTIL_ENV *env_ptr, unsigned int subject_count,
	char **subject_list, rv_Callback call_back, char *error_text)
{
	int          return_code = RVUTIL_SUCCESS;
	unsigned int count_1;
	unsigned int found_index;
	char         tmp_error_text[RVUTIL_MAX_ERROR_TEXT];

	for (count_1 = 0; count_1 < subject_count; count_1++) {
		if ((return_code = RVUTIL_AddSub(env_ptr, subject_list[count_1],
			call_back, NULL, tmp_error_text)) != RVUTIL_SUCCESS) {
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

