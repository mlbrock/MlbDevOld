/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Function wrappers for Tib/Rendezvous RVMSG
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
int RVUTIL_rvmsg_Append(rv_Session session, rvmsg_Msg msg,
	rvmsg_Size msgLimit, rv_Name name, rvmsg_Type dataType, rvmsg_Size dataSize,
	rvmsg_Data data, rvmsg_Error *rv_code_ptr, char *error_text)
{
	int         return_code;
	rvmsg_Error rvmsg_code;
	char        msg_type_name_1[ RVUTIL_MAX_RVMSG_TYPE_NAME + 1];
	char        msg_type_name_2[100 + RVUTIL_MAX_RVMSG_TYPE_NAME + 1];

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvmsg_code;

	if ((*rv_code_ptr = rvmsg_Append(session, msg, msgLimit, name, dataType,
		dataSize, data)) == RVMSG_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			sprintf(msg_type_name_2, "%ld = '%s'", ((long) dataType),
				RVUTIL_GetMsgTypeName(dataType, msg_type_name_1));
			strcpy(error_text, "rvmsg_Append(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rvmsg_Msg msg", msg, 1, error_text);
			RVUTIL_ParamULD("rvmsg_Size msgLimit", ((unsigned long) msgLimit), 1,
				error_text);
			RVUTIL_ParamSUB("rv_Name name", name, 1, error_text);
			RVUTIL_ParamANY("rvmsg_Type dataType", msg_type_name_2, 1,
				error_text);
			RVUTIL_ParamULD("rvmsg_Size dataSize", ((unsigned long) dataSize), 1,
				error_text);
			RVUTIL_ParamPTR("rvmsg_Data data", data, 0, error_text);
			chrcat(RVUTIL_FormatString_rvmsg_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvmsg_Init(rv_Session session, rvmsg_Msg msg,
	rvmsg_Size msgLimit, rvmsg_Error *rv_code_ptr, char *error_text)
{
	int         return_code;
	rvmsg_Error rvmsg_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvmsg_code;

	if ((*rv_code_ptr = rvmsg_Init(session, msg, msgLimit)) == RVMSG_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rvmsg_Init(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rvmsg_Msg msg", msg, 1, error_text);
			RVUTIL_ParamULD("rvmsg_Size msgLimit", ((unsigned long) msgLimit), 0,
				error_text);
			chrcat(RVUTIL_FormatString_rvmsg_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvmsg_Length(rv_Session session, rvmsg_Msg msg,
	rvmsg_Size *length, rvmsg_Error *rv_code_ptr, char *error_text)
{
	int         return_code;
	rvmsg_Error rvmsg_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvmsg_code;

	if ((*rv_code_ptr = rvmsg_Length(session, msg, length)) == RVMSG_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rvmsg_Length(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rvmsg_Msg msg", msg, 1, error_text);
			RVUTIL_ParamPTR("rvmsg_Size *length", length, 0, error_text);
			chrcat(RVUTIL_FormatString_rvmsg_Error(session, *rv_code_ptr,
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
	rvmsg_Size msg_length;
	char       error_text[RVUTIL_MAX_ERROR_TEXT];

	fprintf(stderr, "Test harness for the RVMSG function wrappers\n");
	fprintf(stderr, "---- ------- --- --- ----- -------- --------\n\n");

	RVUTIL_rvmsg_Append(NULL, ((rvmsg_Msg) 1), ((rvmsg_Size) 2), ((rv_Name) 3),
		((rvmsg_Type) 4), ((rvmsg_Size) 5), ((rvmsg_Data) 6), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rvmsg_Init(NULL, ((rvmsg_Msg) 1), ((rvmsg_Size) 2), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rvmsg_Length(NULL, ((rvmsg_Msg) 1), ((rvmsg_Size *) &msg_length),
		NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	return(RVUTIL_SUCCESS);
}

#endif /* #ifdef TEST_MAIN */


