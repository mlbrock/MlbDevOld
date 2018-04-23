/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Function wrappers for Tib/Rendezvous RVEVM
								functions.

	Revision History	:	1996-02-05 --- Creation
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

#include <limits.h>
#include <string.h>

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Function prototypes for functions private to this module . . .				*/
/*	***********************************************************************	*/
typedef COMPAT_FN_TYPE(rvevm_Returns (*RVUTIL_rvevm_RemoveEventFunc),
	(rv_Session session, rvevm_EventId event_id));
#define RVUTIL_rvevm_RemoveEventFunc_CAST(fptr)	\
	COMPAT_FN_CAST(rvevm_Returns,						\
		(rv_Session CAST_session, rvevm_EventId CAST_event_id), (fptr))
COMPAT_FN_DECL_STATIC(int RVUTIL_rvevm_RemoveBasic,
	(const char *func_name, RVUTIL_rvevm_RemoveEventFunc func_ptr,
	rv_Session session, rvevm_EventId event_id, rvevm_Returns *rv_code_ptr,
	char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvevm_AddIo(rv_Session session, rvevm_EventId *event_id_ptr,
	int socket_number, rvevm_IoEventType io_event_type,
	rvevm_EventCallback proc, rv_Opaque closure, rvevm_Returns *rv_code_ptr,
	char *error_text)
{
	int           return_code;
	rvevm_Returns rvevm_code;
	char          rvevm_io_type_name[RVUTIL_MAX_RVEVM_IO_EVNT_NAME + 1];
	char          buffer[RVUTIL_MAX_RVEVM_IO_EVNT_NAME + 100];

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvevm_code;

	if ((*rv_code_ptr = rvevm_AddIo(session, event_id_ptr, socket_number,
		io_event_type, proc, closure)) == RVEVM_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			sprintf(buffer, "%d = '%s'", io_event_type,
				RVUTIL_GetIOEventTypeRVEVM(io_event_type, rvevm_io_type_name));
			strcpy(error_text, "rvevm_AddIo(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rvevm_EventId *event_id_ptr", event_id_ptr, 1,
				error_text);
			RVUTIL_ParamSLD("int socket_number", ((long) socket_number), 1,
				error_text);
			RVUTIL_ParamANY("rvevm_IoEventType io_event_type", buffer, 1,
				error_text);
			RVUTIL_ParamPTR("rvevm_EventCallback proc", STR_CAST_FUNC_PTR(proc),
				1, error_text);
			RVUTIL_ParamPTR("rv_Opaque closure", closure, 0, error_text);
			chrcat(RVUTIL_FormatString_rvevm_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvevm_AddRepeatingTimer(rv_Session session,
	rvevm_EventId *event_id_ptr, unsigned long interval,
	rvevm_EventCallback proc, rv_Opaque closure, rvevm_Returns *rv_code_ptr,
	char *error_text)
{
	int           return_code;
	rvevm_Returns rvevm_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvevm_code;

	if ((*rv_code_ptr = rvevm_AddRepeatingTimer(session, event_id_ptr,
		interval, proc, closure)) == RVEVM_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rvevm_AddRepeatingTimer(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rvevm_EventId *event_id_ptr", event_id_ptr, 1,
				error_text);
			RVUTIL_ParamULD("unsigned long interval", interval, 1, error_text);
			RVUTIL_ParamPTR("rvevm_EventCallback proc", STR_CAST_FUNC_PTR(proc),
				1, error_text);
			RVUTIL_ParamPTR("rv_Opaque closure", closure, 0, error_text);
			chrcat(RVUTIL_FormatString_rvevm_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvevm_AddSignal(rv_Session session, rvevm_EventId *event_id_ptr,
	int signal_number, rvevm_EventCallback proc, rv_Opaque closure,
	rvevm_Returns *rv_code_ptr, char *error_text)
{
	int           return_code;
	rvevm_Returns rvevm_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvevm_code;

	if ((*rv_code_ptr = rvevm_AddSignal(session, event_id_ptr, signal_number,
		proc, closure)) == RVEVM_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rvevm_AddSignal(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rvevm_EventId *event_id_ptr", event_id_ptr, 1,
				error_text);
			RVUTIL_ParamSLD("int signal_number", signal_number, 1, error_text);
			RVUTIL_ParamPTR("rvevm_EventCallback proc", STR_CAST_FUNC_PTR(proc),
				1, error_text);
			RVUTIL_ParamPTR("rv_Opaque closure", closure, 0, error_text);
			chrcat(RVUTIL_FormatString_rvevm_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvevm_AddTimer(rv_Session session, rvevm_EventId *event_id_ptr,
	unsigned long interval, rvevm_EventCallback proc, rv_Opaque closure,
	rvevm_Returns *rv_code_ptr, char *error_text)
{
	int           return_code;
	rvevm_Returns rvevm_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvevm_code;

	if ((*rv_code_ptr = rvevm_AddTimer(session, event_id_ptr, interval, proc,
		closure)) == RVEVM_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rvevm_AddTimer(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rvevm_EventId *event_id_ptr", event_id_ptr, 1,
				error_text);
			RVUTIL_ParamULD("unsigned long interval", interval, 1, error_text);
			RVUTIL_ParamPTR("rvevm_EventCallback proc", STR_CAST_FUNC_PTR(proc),
				1, error_text);
			RVUTIL_ParamPTR("rv_Opaque closure", closure, 0, error_text);
			chrcat(RVUTIL_FormatString_rvevm_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvevm_Destroy(rvevm_Context context, rvevm_Returns *rv_code_ptr,
	char *error_text)
{
	int           return_code;
	rvevm_Returns rvevm_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvevm_code;

	if (context != NULL) {
		rvevm_Destroy(context);
		*rv_code_ptr = RVEVM_OK;
		return_code  = RVUTIL_SUCCESS;
	}
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rvevm_Destroy(");
			RVUTIL_ParamPTR("rvevm_Context context", context, 0, error_text);
			strcat(error_text, "The 'rvevm_Context' is 'NULL'.");
		}
		*rv_code_ptr = RVEVM_ERR_OS_ERROR;
		return_code  = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvevm_Make(rvevm_Context *context, rvevm_Returns *rv_code_ptr,
	char *error_text)
{
	int           return_code;
	rvevm_Returns rvevm_code;
	char          text_buffer[RVUTIL_MAX_CODE_STR_TEXT + 1];
	char          number_buffer[STR_VAL2STR_MAX_LEN + 1];


	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvevm_code;

	if ((*rv_code_ptr = rvevm_Make(context)) == RVEVM_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rvevm_Make(");
			RVUTIL_ParamPTR("rvevm_Context *context", context, 0, error_text);
			strcat(strcat(strcat(strcat(error_text,
				val2str(((unsigned long) ((*rv_code_ptr < 0) ?
				(0 - *rv_code_ptr) : *rv_code_ptr)), ((int) *rv_code_ptr), 10,
				NULL, number_buffer)),
				" = '"),
				RVUTIL_CodeToString_rvevm_Error(*rv_code_ptr, text_buffer)),
				"'.");
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvevm_RemoveIo(rv_Session session, rvevm_EventId event_id,
	rvevm_Returns *rv_code_ptr, char *error_text)
{
	return(RVUTIL_rvevm_RemoveBasic("rvevm_RemoveIo",
		RVUTIL_rvevm_RemoveEventFunc_CAST(rvevm_RemoveIo), session,
		event_id, rv_code_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvevm_RemoveSignal(rv_Session session, rvevm_EventId event_id,
	rvevm_Returns *rv_code_ptr, char *error_text)
{
	return(RVUTIL_rvevm_RemoveBasic("rvevm_RemoveSignal",
		RVUTIL_rvevm_RemoveEventFunc_CAST(rvevm_RemoveSignal), session,
		event_id, rv_code_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvevm_RemoveTimer(rv_Session session, rvevm_EventId event_id,
	rvevm_Returns *rv_code_ptr, char *error_text)
{
	return(RVUTIL_rvevm_RemoveBasic("rvevm_RemoveTimer",
		RVUTIL_rvevm_RemoveEventFunc_CAST(rvevm_RemoveTimer), session,
		event_id, rv_code_ptr, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int RVUTIL_rvevm_ResetTimer(rv_Session session, rvevm_EventId event_id,
	unsigned long interval, rvevm_Returns *rv_code_ptr, char *error_text)
{
	int           return_code;
	rvevm_Returns rvevm_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvevm_code;

	if ((*rv_code_ptr = rvevm_ResetTimer(session, event_id, interval)) ==
		RVEVM_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			strcpy(error_text, "rvevm_ResetTimer(");
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rvevm_EventId event_id", event_id, 1, error_text);
			RVUTIL_ParamULD("unsigned long interval", interval, 0, error_text);
			chrcat(RVUTIL_FormatString_rvevm_Error(session, *rv_code_ptr,
				error_text + strlen(error_text)), '.');
		}
		return_code = RVUTIL_RENDEZVOUS_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int RVUTIL_rvevm_RemoveBasic(const char *func_name,
	RVUTIL_rvevm_RemoveEventFunc func_ptr, rv_Session session,
	rvevm_EventId event_id, rvevm_Returns *rv_code_ptr, char *error_text)
{
	int           return_code;
	rvevm_Returns rvevm_code;

	rv_code_ptr = (rv_code_ptr != NULL) ? rv_code_ptr : &rvevm_code;

	if ((*rv_code_ptr = (*func_ptr)(session, event_id)) == RVEVM_OK)
		return_code = RVUTIL_SUCCESS;
	else {
		if (error_text != NULL) {
			chrcat(strcpy(error_text, func_name), '(');
			RVUTIL_ParamPTR("rv_Session session", session, 1, error_text);
			RVUTIL_ParamPTR("rvevm_EventId event_id", event_id, 0, error_text);
			chrcat(RVUTIL_FormatString_rvevm_Error(session, *rv_code_ptr,
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

	fprintf(stderr, "Test harness for the RVEVM function wrappers\n");
	fprintf(stderr, "---- ------- --- --- ----- -------- --------\n\n");

	RVUTIL_rvevm_AddIo(NULL, ((rvevm_EventId *) 1), 2, RVEVM_WRITE,
		((rvevm_EventCallback) 3), ((rv_Opaque) 4), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rvevm_AddRepeatingTimer(NULL, ((rvevm_EventId *) 1),
		2L, ((rvevm_EventCallback) 3), ((rv_Opaque) 4), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rvevm_AddSignal(NULL, ((rvevm_EventId *) 1),
		2, ((rvevm_EventCallback) 3), ((rv_Opaque) 4), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rvevm_AddTimer(NULL, ((rvevm_EventId *) 1),
		2L, ((rvevm_EventCallback) 3), ((rv_Opaque) 4), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rvevm_Destroy(NULL, NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

/*
	RVUTIL_rvevm_Make(tmp_context, NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);
*/

	RVUTIL_rvevm_RemoveIo(NULL, ((rvevm_EventId) 1), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rvevm_RemoveSignal(NULL, ((rvevm_EventId) 1), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	RVUTIL_rvevm_RemoveTimer(NULL, ((rvevm_EventId) 1), NULL, error_text);
	printf("%s\n", error_text);
	STR_EMIT_CharLine('-', 78, NULL, NULL);

	return(RVUTIL_SUCCESS);
}

#endif /* #ifdef TEST_MAIN */


