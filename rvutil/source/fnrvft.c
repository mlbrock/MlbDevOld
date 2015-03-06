/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Function wrappers for Tib/Rendezvous RVFT
								functions.

	Revision History	:	1996-02-05 --- Creation
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
int RVUTIL_rvft_Join(rv_Session session, rvft_Id *groupId,
	rv_Name group_name, unsigned long weight, unsigned long activeGoal,
	unsigned long heartbeatInterval, unsigned long preparationInterval,
	unsigned long activationInterval, rvft_Callback ftCallbackFn,
	rv_Opaque closureArg, rvft_Error *rv_code_ptr, char *error_text)
{
	int        return_code;
	rvft_Error rvft_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvft_code;

	if ((*rv_code_ptr = rvft_Join(session, groupId, group_name, weight,
		activeGoal, heartbeatInterval, preparationInterval,
		activationInterval, ftCallbackFn, closureArg)) == RVFT_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rvft_Join(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rvft_Id *groupId", groupId, 1, error_text);
			RVUTIL_ParamSUB("rv_Name group_name", group_name, 1, error_text);
			RVUTIL_ParamULD("unsigned long weight", weight, 1, error_text);
			RVUTIL_ParamULD("unsigned long activeGoal", activeGoal, 1,
				error_text);
			RVUTIL_ParamULD("unsigned long heartbeatInterval",
				heartbeatInterval, 1, error_text);
			RVUTIL_ParamULD("unsigned long preparationInterval",
				preparationInterval, 1, error_text);
			RVUTIL_ParamULD("unsigned long activationInterval",
				activationInterval, 1, error_text);
			RVUTIL_ParamPTR("rvft_Callback ftCallbackFn",
				STR_CAST_FUNC_PTR(ftCallbackFn), 1, error_text);
			RVUTIL_ParamPTR("rv_Opaque closureArg", closureArg, 0, error_text);
			chrcat(RVUTIL_FormatString_rvft_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvft_Withdraw(rv_Session session, rvft_Id groupId,
	rvft_Error *rv_code_ptr, char *error_text)
{
	int        return_code;
	rvft_Error rvft_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvft_code;

	if ((*rv_code_ptr = rvft_Withdraw(session, groupId)) == RVFT_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rvft_Withdraw(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rvft_Id groupId", groupId, 0, error_text);
			chrcat(RVUTIL_FormatString_rvft_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

int main(void);

int main()
{
	char error_text[RVUTIL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for the RVFT function wrappers\n");
	fprintf(stderr, "---- ------- --- --- ---- -------- --------\n\n");

	RVUTIL_rvft_Join(NULL, ((rvft_Id *) 1), "Group.Name", 3L, 4L,
		5L, 6L, 7L, ((rvft_Callback) 8), ((rv_Opaque) 9), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rvft_Withdraw(NULL, ((rvft_Id) 1), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	return(RVUTIL_SUCCESS);
}

#endif /* #ifdef TEST_MAIN */


