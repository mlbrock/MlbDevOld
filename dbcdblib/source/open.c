/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase DB-Library Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Opens a connection to a Sybase database for the
								Sybase DB-LIB facility.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
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

#include "dbcdblii.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_Open

   SYNOPSIS    :	return_code = DBC_DBLIB_Open(dbc_control_ptr, app_name,
							server_name, database_name, owner_name, user_name,
							pass_word, error_text);

						int         return_code;

						DBC_DBLIB  *dbc_control_ptr;

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
						''DBC_DBLIB'' structure to be used to open the
						connection with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_DBLIB_Initialize``.

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

   SEE ALSO    :	DBC_DBLIB_Initialize
						DBC_CTLIB_Open

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_Open
						DBC Sybase DB-LIB Functions:DBC_DBLIB_Open
						DBC Functions:Connect Functions:DBC_DBLIB_Open

   PUBLISH XREF:	DBC_DBLIB_Open

   PUBLISH NAME:	DBC_DBLIB_Open

	ENTRY CLASS	:	DBC Functions:Connect Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_DBLIB_Open(DBC_CONTEXT *dbc_context_ptr, const char *conn_type,
	const char *conn_string, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text)
#else
int DBC_DBLIB_Open(dbc_context_ptr, conn_type, conn_string, mlog_ptr, flags,
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
	DBC_DBLIB *dbc_control_ptr      = NULL;
	char               error_buffer[DBC_MAX_ERROR_TEXT];

	if (dbc_context_ptr->dbc_control_ptr != NULL)
		was_initialized_flag = DBC_TRUE;
	else if ((return_code = DBC_DBLIB_Initialize(dbc_context_ptr, mlog_ptr,
		flags, user_data_ptr, error_text)) != DBC_SUCCESS)
		goto EXIT_FUNCTION;

	dbc_control_ptr = ((DBC_DBLIB *) dbc_context_ptr->dbc_control_ptr);

	if ((return_code = (*dbc_control_ptr->dbc_funcs.parse_conn)(conn_type,
		conn_string, &dbc_control_ptr->conn_count, &dbc_control_ptr->conn_list,
		error_text)) != DBC_SUCCESS)
		goto EXIT_FUNCTION;

	if (!(*dbc_control_ptr->conn_list[DBC_DBLIB_SERVER_NAME])) {
		strcpy(error_text, "The server name is empty.");
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = DBC_DBLIB_MSG_DefaultHandler(dbc_control_ptr,
		error_text)) != DBC_SUCCESS)
		goto EXIT_FUNCTION;
	else {
		if ((dbc_control_ptr->server_ptr = dblogin()) == NULL) {
			sprintf(error_text,
				"Attempt to call 'dblogin()' for server '%s' failed: %-.800s",
				dbc_control_ptr->conn_list[DBC_DBLIB_SERVER_NAME],
				DBC_DBLIB_MSG_GetHandlerMessage(error_buffer));
			return_code = DBC_DB_FAILURE;
		}
		else {
			/* CODE NOTE: Set owner here. */
			/*	********************************************************
				********************************************************
				********************************************************
				This worked for negotiating the TDS packet size
				from Sybase 4.9.2 through System 10. In Sybase 11,
				however, it trashes the LOGINREC.
				DBSETLPACKET(dbc_control_ptr->server_ptr, DB__MAX_PACKET_SIZE);
				********************************************************	*/
			if (*dbc_control_ptr->conn_list[DBC_DBLIB_USER_NAME])
				DBSETLUSER(dbc_control_ptr->server_ptr,
					dbc_control_ptr->conn_list[DBC_DBLIB_USER_NAME]);
			if (*dbc_control_ptr->conn_list[DBC_DBLIB_PASS_WORD])
				DBSETLPWD(dbc_control_ptr->server_ptr,
				dbc_control_ptr->conn_list[DBC_DBLIB_PASS_WORD]);
			if ((conn_type != NULL) && *conn_type)
				DBSETLAPP(dbc_control_ptr->server_ptr,
					((char *) conn_type));
			if ((dbc_control_ptr->database_ptr =
				dbopen(dbc_control_ptr->server_ptr,
				dbc_control_ptr->conn_list[DBC_DBLIB_SERVER_NAME])) ==
				NULL) {
				sprintf(error_text,
			"%s %s database '%s' for owner '%s' on server '%s' failed: %-.800s",
					"Attempt to call 'dbopen()' for", conn_type,
					(*dbc_control_ptr->conn_list[DBC_DBLIB_DB_NAME]) ?
					dbc_control_ptr->conn_list[DBC_DBLIB_DB_NAME] : "?",
					(*dbc_control_ptr->conn_list[DBC_DBLIB_OWNER_NAME]) ?
					dbc_control_ptr->conn_list[DBC_DBLIB_OWNER_NAME] : "?",
					dbc_control_ptr->conn_list[DBC_DBLIB_SERVER_NAME],
					DBC_DBLIB_MSG_GetHandlerMessage(error_buffer));
				dbloginfree(dbc_control_ptr->server_ptr);
				dbc_control_ptr->server_ptr = NULL;
				return_code = DBC_DB_FAILURE;
			}
			/*	*****************************************************
				*****************************************************
				The code below is commented-out because Purify
				version 3.0 detects an SBR (actually, eleven of them)
				within the call to 'dbuse()'.
				This logic was always a bit of operational sugar
				because the routines which use it always specify
				the database table on which the act.
				*****************************************************
			else if (*dbc_control_ptr->conn_list[DBC_DBLIB_DB_NAME] &&
				(dbuse(dbc_control_ptr->database_ptr,
				dbc_control_ptr->conn_list[DBC_DBLIB_DB_NAME]) != SUCCEED)) {
				sprintf(error_text,
			"%s %s database '%s' for owner '%s' on server '%s' failed: %-.800s",
					"Attempt to call 'dbuse()' for", db_name,
					(*dbc_control_ptr->conn_list[DBC_DBLIB_DB_NAME]) ?
					dbc_control_ptr->conn_list[DBC_DBLIB_DB_NAME] : "?",
					(*dbc_control_ptr->conn_list[DBC_DBLIB_OWNER_NAME]) ?
					dbc_control_ptr->conn_list[DBC_DBLIB_OWNER_NAME] : "?",
					dbc_control_ptr->conn_list[DBC_DBLIB_SERVER_NAME],
					DBC_DBLIB_MSG_GetHandlerMessage(error_buffer));
				dbclose(dbc_control_ptr->database_ptr);
				dbloginfree(dbc_control_ptr->server_ptr);
				dbc_control_ptr->database_ptr = NULL;
				dbc_control_ptr->server_ptr   = NULL;
				return_code                   = DBC_DB_FAILURE;
			}
				*****************************************************	*/
		}
		DBC_DBLIB_MSG_PopHandler();
	}

EXIT_FUNCTION:

	if ((return_code != DBC_SUCCESS) && (dbc_control_ptr != NULL)) {
		if (was_initialized_flag == DBC_FALSE) {
			DBC_DBLIB_Close(&dbc_control_ptr);
			dbc_context_ptr->dbc_control_ptr = dbc_control_ptr;
		}
		else
			strl_remove_all(&dbc_control_ptr->conn_count,
				&dbc_control_ptr->conn_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

