/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Function wrappers for Tib/Rendezvous RV
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
int RVUTIL_rv_Close(rv_Session session, rv_ListenId listen_id,
	rv_Error *rv_code_ptr, char *error_text)
{
	int      return_code;
	rv_Error rv_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rv_code;

	if ((*rv_code_ptr = rv_Close(session, listen_id)) == RV_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rv_Close(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rv_ListenId listen_id", listen_id, 0, error_text);
			chrcat(RVUTIL_FormatString_rv_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rv_Init(rv_Session *session, char *service, char *network,
	char *daemon, rv_Error *rv_code_ptr, char *error_text)
{
	int      return_code;
	rv_Error rv_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rv_code;

	if ((*rv_code_ptr = rv_Init(session, service, network, daemon)) == RV_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rv_Init(");
			RVUTIL_ParamPTR("rv_Session *session", session, 1, error_text);
			RVUTIL_ParamSND("char *service", service, 1, error_text);
			RVUTIL_ParamSND("char *network", network, 1, error_text);
			RVUTIL_ParamSND("char *daemon", daemon, 0, error_text);
			chrcat(RVUTIL_FormatString_rv_Error(NULL, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rv_InitSession(rv_Session *session, rvevm_Context context,
	char *service, char *network, char *daemon, rv_Error *rv_code_ptr,
	char *error_text)
{
	int      return_code;
	rv_Error rv_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rv_code;

	if ((*rv_code_ptr = rv_InitSession(session, context, service, network,
		daemon)) == RV_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rv_InitSession(");
			RVUTIL_ParamPTR("rv_Session *session", session, 1, error_text);
			RVUTIL_ParamPTR("rvevm_Context context", context, 1, error_text);
			RVUTIL_ParamSND("char *service", service, 1, error_text);
			RVUTIL_ParamSND("char *network", network, 1, error_text);
			RVUTIL_ParamSND("char *daemon", daemon, 0, error_text);
			chrcat(RVUTIL_FormatString_rv_Error(NULL, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rv_ListenSubject(rv_Session session, rv_ListenId *listen_id,
	rv_Name subject, rv_Callback callback, rv_Opaque closure,
	rv_Error *rv_code_ptr, char *error_text)
{
	int      return_code;
	rv_Error rv_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rv_code;

	if ((*rv_code_ptr = rv_ListenSubject(session, listen_id, subject,
		callback, closure)) == RV_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rv_ListenSubject(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rv_ListenId *listen_id", listen_id, 1, error_text);
			RVUTIL_ParamSUB("rv_Name subject", subject, 1, error_text);
			RVUTIL_ParamPTR("rv_Callback callback", STR_CAST_FUNC_PTR(callback),
				1, error_text);
			RVUTIL_ParamPTR("rv_Opaque closure", closure, 0, error_text);
			chrcat(RVUTIL_FormatString_rv_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rv_Rpc(rv_Session session, rv_ListenId *listen_id, rv_Name name,
	rvmsg_Type msgType, rvmsg_Size msgSize, rvmsg_Data msg,
	rv_Callback callback, rv_Opaque closure, rv_Error *rv_code_ptr,
	char *error_text)
{
	int      return_code;
	rv_Error rv_code;
  	char     msg_type_name_1[ RVUTIL_MAX_RVMSG_TYPE_NAME + 1];
	char     msg_type_name_2[100 + RVUTIL_MAX_RVMSG_TYPE_NAME + 1];

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rv_code;

	if ((*rv_code_ptr = rv_Rpc(session, listen_id, name, msgType, msgSize,
		msg, callback, closure)) == RV_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			sprintf(msg_type_name_2, "%ld = '%s'", ((long) msgType),
				RVUTIL_GetMsgTypeName(msgType, msg_type_name_1));
			strcpy(error_text, "rv_Rpc(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rv_ListenId *listen_id", listen_id, 1, error_text);
			RVUTIL_ParamSUB("rv_Name name", name, 1, error_text);
			RVUTIL_ParamANY("rvmsg_Type msgType", msg_type_name_2, 1,
				error_text);
			RVUTIL_ParamULD("rvmsg_Size msgSize", ((unsigned long) msgSize),
				1, error_text);
			RVUTIL_ParamPTR("rvmsg_Data msg", msg, 0, error_text);
			RVUTIL_ParamPTR("rv_Callback callback", STR_CAST_FUNC_PTR(callback),
				1, error_text);
			RVUTIL_ParamPTR("rv_Opaque closure", closure, 0, error_text);
			chrcat(RVUTIL_FormatString_rv_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rv_Send(rv_Session session, rv_Name name, rvmsg_Type msgType,
	rvmsg_Size msgSize, rvmsg_Data msg, rv_Error *rv_code_ptr,
	char *error_text)
{
	int      return_code;
	rv_Error rv_code;
  	char     msg_type_name_1[ RVUTIL_MAX_RVMSG_TYPE_NAME + 1];
	char     msg_type_name_2[100 + RVUTIL_MAX_RVMSG_TYPE_NAME + 1];

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rv_code;

	if ((*rv_code_ptr = rv_Send(session, name, msgType, msgSize, msg)) ==
		RV_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			sprintf(msg_type_name_2, "%ld = '%s'", ((long) msgType),
				RVUTIL_GetMsgTypeName(msgType, msg_type_name_1));
			strcpy(error_text, "rv_Send(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamSUB("rv_Name name", name, 1, error_text);
			RVUTIL_ParamANY("rvmsg_Type msgType", msg_type_name_2, 1,
				error_text);
			RVUTIL_ParamULD("rvmsg_Size msgSize", ((unsigned long) msgSize),
				1, error_text);
			RVUTIL_ParamPTR("rvmsg_Data msg", msg, 0, error_text);
			chrcat(RVUTIL_FormatString_rv_Error(NULL, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rv_SendWithReply(rv_Session session, rv_Name name,
	rv_Name replyName, rvmsg_Type msgType, rvmsg_Size msgSize, rvmsg_Data msg,
	rv_Error *rv_code_ptr, char *error_text)
{
	int      return_code;
	rv_Error rv_code;
  	char     msg_type_name_1[ RVUTIL_MAX_RVMSG_TYPE_NAME + 1];
	char     msg_type_name_2[100 + RVUTIL_MAX_RVMSG_TYPE_NAME + 1];

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rv_code;

	if ((*rv_code_ptr = rv_SendWithReply(session, name, replyName, msgType,
		msgSize, msg)) == RV_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			sprintf(msg_type_name_2, "%ld = '%s'", ((long) msgType),
				RVUTIL_GetMsgTypeName(msgType, msg_type_name_1));
			strcpy(error_text, "rv_SendWithReply(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamSUB("rv_Name name", name, 1, error_text);
			RVUTIL_ParamSUB("rv_Name replyName", replyName, 1, error_text);
			RVUTIL_ParamANY("rvmsg_Type msgType", msg_type_name_2, 1,
				error_text);
			RVUTIL_ParamULD("rvmsg_Size msgSize", ((unsigned long) msgSize),
				1, error_text);
			RVUTIL_ParamPTR("rvmsg_Data msg", msg, 0, error_text);
			chrcat(RVUTIL_FormatString_rv_Error(NULL, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rv_Term(rv_Session session, rv_Error *rv_code_ptr,
	char *error_text)
{
	int      return_code;
	rv_Error rv_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rv_code;

	if ((*rv_code_ptr = rv_Term(session)) == RV_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rv_Term(");
			RVUTIL_ParamPTR("rv_Session session", session, 0, error_text);
			chrcat(RVUTIL_FormatString_rv_Error(NULL, *rv_code_ptr,
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

	fprintf(stderr, "Test harness for the RV function wrappers\n");
	fprintf(stderr, "---- ------- --- --- -- -------- --------\n\n");

/*
	RVUTIL_rv_Close(NULL, ((rv_ListenId) 1), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);
*/

	RVUTIL_rv_Init(NULL, "s", "n", "d", NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rv_InitSession(NULL, NULL, "s", "n", "d", NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rv_ListenSubject(NULL, ((rv_ListenId *) 1), "sub.name",
		((rv_Callback) 3), ((rv_Opaque) 4), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rv_Send(NULL, "sub.name", RVMSG_STRING, 0, "The message.", NULL,
		error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

/*
	RVUTIL_rv_Term(NULL, NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);
*/

	return(RVUTIL_SUCCESS);
}

#endif /* #ifdef TEST_MAIN */


