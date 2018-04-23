/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase CT-Library Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Opens a connection to a Sybase database for the
								Sybase CT-LIB facility.

	Revision History	:	1996-06-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "dbcctlii.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_Open

   SYNOPSIS    :	return_code = DBC_CTLIB_Open(dbc_control_ptr, app_name,
							server_name, database_name, owner_name, user_name,
							pass_word, error_text);

						int         return_code;

						DBC_CTLIB  *dbc_control_ptr;

						const char *app_name;

						const char *server_name;

						const char *database_name;

						const char *owner_name;

						const char *user_name;

						const char *pass_word;

						char       *error_text;

   DESCRIPTION :	Logs in and connects to a Sybase database server.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_CTLIB'' structure to be used to open the
						connection with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_CTLIB_Initialize``.

						(.) ``app_name`` is the name of the application on behalf
						which the connection to the database is to be made. It is
						not required for the correct operation of this function and
						may be passed as ''NULL''.

						(.) ``server_name`` is the name of the Sybase database to
						which the connection is to be made.

						(.) ``database_name`` is the name of the database to
						which the connection is to be made. It is not required for
						the correct operation of this function and may be passed
						as ''NULL''.

						(.) ``owner_name`` is the name of the owner of the database
						to which the connection is to be made. It is not required
						for the correct operation of this function and may be passed
						as ''NULL''.

						(.) ``user_name`` is the user name to be used to login
						to the Sybase database.

						(.) ``pass_word`` is the password to be used in conjunction
						with ``user_name`` to login to the Sybase database.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''DBC_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	This function returns a DBC return codes manifest constant:

						(.) ''DBC_SUCCESS'' if the function completes without
						error.

						(.) One of the defined non-zero DBC return codes indicative
						of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :  DBC_CTLIB_Initialize
						DBC_DBLIB_Open

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_Open
						DBC Sybase CT-LIB Functions:DBC_CTLIB_Open
						DBC Functions:Connect Functions:DBC_CTLIB_Open

   PUBLISH XREF:	DBC_CTLIB_Open

   PUBLISH NAME:	DBC_CTLIB_Open

	ENTRY CLASS	:	DBC Functions:Connect Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_CTLIB_Open(DBC_CONTEXT *dbc_context_ptr, const char *conn_type,
	const char *conn_string, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text)
#else
int DBC_CTLIB_Open(dbc_context_ptr, conn_type, conn_string, mlog_ptr, flags,
	user_data_ptr, error_text)
DBC_CONTEXT *dbc_context_ptr;
const char  *conn_type;
const char  *conn_string;
MLOG        *mlog_ptr;
DBC_FLAG     flags;
void        *user_data_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code          = DBC_SUCCESS;
	int                was_initialized_flag = DBC_FALSE;
	DBC_CTLIB *dbc_control_ptr      = NULL;
	int                connected_flag       = DBC_FALSE;
	CS_RETCODE         ct_code;
	char               error_buffer[DBC_MAX_ERROR_TEXT];

	if (dbc_context_ptr->dbc_control_ptr != NULL)
		was_initialized_flag = DBC_TRUE;
	else if ((return_code = DBC_CTLIB_Initialize(dbc_context_ptr, mlog_ptr,
		flags, user_data_ptr, error_text)) != DBC_SUCCESS)
		goto EXIT_FUNCTION;

	dbc_control_ptr = ((DBC_CTLIB *) dbc_context_ptr->dbc_control_ptr);

	if ((return_code = (*dbc_control_ptr->dbc_funcs.parse_conn)(conn_type,
		conn_string, &dbc_control_ptr->conn_count, &dbc_control_ptr->conn_list,
		error_text)) != DBC_SUCCESS)
		goto EXIT_FUNCTION;

	if (!(*dbc_control_ptr->conn_list[DBC_CTLIB_SERVER_NAME])) {
		strcpy(error_text, "The server name is empty.");
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}

	cs_ctx_alloc(CS_VERSION_100, &dbc_control_ptr->context_ptr);

	if ((ct_code = ct_init(dbc_control_ptr->context_ptr, CS_VERSION_100)) !=
		CS_SUCCEED) {
		strcpy(error_text, "Call to 'ct_init()' failed.");
		return_code = (ct_code == CS_MEM_ERROR) ? DBC_MEMORY_FAILURE :
			DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((ct_code = ct_callback(dbc_control_ptr->context_ptr, NULL,
		CS_SET, CS_SERVERMSG_CB, ((CS_VOID *) DBC_CTLIB_ServerMsgCB))) !=
		CS_SUCCEED) {
		sprintf(error_text, "%s 'ct_callback()' failed with code %d.",
			"Attempt to set new 'CS_SERVERMSG' call-back with",
			((int) ct_code));
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((ct_code = ct_callback(dbc_control_ptr->context_ptr, NULL,
		CS_SET, CS_CLIENTMSG_CB, ((CS_VOID *) DBC_CTLIB_ClientMsgCB))) !=
		CS_SUCCEED) {
		sprintf(error_text, "%s 'ct_callback()' failed with code %d.",
			"Attempt to set new 'CS_CLIENTMSG' call-back with",
			((int) ct_code));
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((ct_code = ct_con_alloc(dbc_control_ptr->context_ptr,
		&dbc_control_ptr->connection_ptr)) != CS_SUCCEED) {
		sprintf(error_text,
			"Call to 'ct_con_alloc()' failed with code %d.", ((int) ct_code));
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}

	/*	*** Set user data ptr *** */
	if (ct_con_props(dbc_control_ptr->connection_ptr, CS_SET, CS_USERDATA,
		&dbc_control_ptr, sizeof(dbc_control_ptr), NULL) != CS_SUCCEED) {
		strcpy(error_text, "Call to 'ct_con_props()' failed.");
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((conn_type != NULL) && *conn_type &&
		(ct_con_props(dbc_control_ptr->connection_ptr, CS_SET, CS_APPNAME,
		((CS_VOID *) conn_type), CS_NULLTERM, NULL) != CS_SUCCEED)) {
		sprintf(error_text,
			"Call to 'ct_con_props()' failed: %-.*s", DBC_MAX_ERROR_TEXT - 100,
			DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_buffer));
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (ct_con_props(dbc_control_ptr->connection_ptr, CS_SET, CS_USERNAME,
		((CS_VOID *) dbc_control_ptr->conn_list[DBC_CTLIB_USER_NAME]),
		CS_NULLTERM, NULL) != CS_SUCCEED) {
		sprintf(error_text,
			"Call to 'ct_con_props()' failed: %-.*s", DBC_MAX_ERROR_TEXT - 100,
			DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_buffer));
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (ct_con_props(dbc_control_ptr->connection_ptr, CS_SET, CS_PASSWORD,
		((CS_VOID *) dbc_control_ptr->conn_list[DBC_CTLIB_PASS_WORD]),
		CS_NULLTERM, NULL) != CS_SUCCEED) {
		sprintf(error_text,
			"Call to 'ct_con_props()' failed: %-.*s", DBC_MAX_ERROR_TEXT - 100,
			DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_buffer));
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (ct_connect(dbc_control_ptr->connection_ptr,
		((CS_CHAR *) dbc_control_ptr->conn_list[DBC_CTLIB_SERVER_NAME]),
		CS_NULLTERM) != CS_SUCCEED) {
		sprintf(error_text,
			"Call to 'ct_connect()' for server '%s' failed: %-.*s",
			dbc_control_ptr->conn_list[DBC_CTLIB_SERVER_NAME],
			DBC_MAX_ERROR_TEXT - 100,
			DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_buffer));
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}

	connected_flag = DBC_TRUE;

	if (ct_cmd_alloc(dbc_control_ptr->connection_ptr,
		&dbc_control_ptr->command_ptr) != CS_SUCCEED) {
		sprintf(error_text,
			"Call to 'ct_cmd_alloc()' failed: %-.*s", DBC_MAX_ERROR_TEXT - 100,
			DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_buffer));
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}

EXIT_FUNCTION:

	if ((return_code != DBC_SUCCESS) && (dbc_control_ptr != NULL)) {
		if (dbc_control_ptr->command_ptr != NULL) {
			ct_cancel(dbc_control_ptr->connection_ptr, NULL, CS_CANCEL_ALL);
			ct_cmd_drop(dbc_control_ptr->command_ptr);
		}
		if (dbc_control_ptr->connection_ptr != NULL) {
			if (connected_flag == DBC_TRUE)
				ct_close(dbc_control_ptr->connection_ptr, CS_FORCE_CLOSE);
			ct_con_drop(dbc_control_ptr->connection_ptr);
		}
		if (dbc_control_ptr->context_ptr != NULL) {
			ct_exit(dbc_control_ptr->context_ptr, CS_FORCE_EXIT);
			cs_ctx_drop(dbc_control_ptr->context_ptr);
		}
		dbc_control_ptr->context_ptr    = NULL;
		dbc_control_ptr->connection_ptr = NULL;
		dbc_control_ptr->command_ptr    = NULL;
		if (was_initialized_flag == DBC_FALSE) {
			DBC_CTLIB_Close(&dbc_control_ptr);
			dbc_context_ptr->dbc_control_ptr = dbc_control_ptr;
		}
		else
			strl_remove_all(&dbc_control_ptr->conn_count,
				&dbc_control_ptr->conn_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

