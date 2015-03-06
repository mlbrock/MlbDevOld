/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Opens a connection to a Microsoft SQL Server database
								for the DB-LIB facility.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_Connect

   SYNOPSIS    :	return_code = DBC_MSSQL_Connect(dbc_control_ptr, app_name,
							server_name, database_name, owner_name, user_name,
							pass_word, error_text);

						int                return_code;

						DBC_MSSQL_CONTROL *dbc_control_ptr;

						const char        *app_name;

						const char        *server_name;

						const char        *database_name;

						const char        *owner_name;

						const char        *user_name;

						const char        *pass_word;

						char              *error_text;

   DESCRIPTION :	Logs in and connects to a Microsoft SQL Server database server.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_MSSQL_CONTROL'' structure to be used to open the
						connection with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_MSSQL_Initialize``.

						(.) ``app_name`` is the name of the application on behalf
						which the connection to the database is to be made. It is
						not required for the correct operation of this function and
						may be passed as ''NULL''.

						(.) ``server_name`` is the name of the Microsoft SQL Server database to
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
						to the Microsoft SQL Server database.

						(.) ``pass_word`` is the password to be used in conjunction
						with ``user_name`` to login to the Microsoft SQL Server database.

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

   SEE ALSO    :	DBC_CTLIB_Connect

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_Connect
						DBC DB-LIB Functions:DBC_MSSQL_Connect
						DBC Functions:Connect Functions:DBC_MSSQL_Connect

   PUBLISH XREF:	DBC_MSSQL_Connect

   PUBLISH NAME:	DBC_MSSQL_Connect

	ENTRY CLASS	:	DBC Functions:Connect Functions

EOH */
/*	***********************************************************************	*/
int DBC_MSSQL_Connect(dbc_control_ptr, app_name, server_name, database_name,
	owner_name, user_name, pass_word, error_text)
DBC_MSSQL_CONTROL *dbc_control_ptr;
const char        *app_name;
const char        *server_name;
const char        *database_name;
const char        *owner_name;
const char        *user_name;
const char        *pass_word;
char              *error_text;
{
	int  return_code = DBC_SUCCESS;
	char error_buffer[DBC_MAX_ERROR_TEXT];

	database_name = (database_name == NULL) ? "" : database_name;
	owner_name    = (owner_name == NULL)    ? "" : owner_name;
	user_name     = (user_name == NULL)     ? "" : user_name;
	pass_word     = (pass_word == NULL)     ? "" : pass_word;

	dbc_control_ptr->server_ptr   = NULL;
	dbc_control_ptr->database_ptr = NULL;

	if ((server_name == NULL) || (!(*server_name))) {
		strcpy(error_text, "The server name is empty.");
		return_code = DBC_FAILURE;
	}
	else if ((return_code = DBC_MSSQL_MSG_DefaultHandler(dbc_control_ptr,
		error_text)) == DBC_SUCCESS) {
		if ((dbc_control_ptr->server_ptr = dblogin()) == NULL) {
			sprintf(error_text,
				"Attempt to call 'dblogin()' for server '%s' failed: %-.800s",
				server_name, DBC_MSSQL_MSG_GetHandlerMessage(error_buffer));
			return_code = DBC_DB_FAILURE;
		}
		else {
			/* CODE NOTE: Set owner */
/*
	This worked for negotiating the TDS packet size from Microsoft SQL Server 4.9.2
	through System 10. In Microsoft SQL Server 11, however, it trashes the LOGINREC.
			DBSETLPACKET(dbc_control_ptr->server_ptr, DB__MAX_PACKET_SIZE);
*/
			if (*user_name)
				DBSETLUSER(dbc_control_ptr->server_ptr, ((char *) user_name));
			if (*pass_word)
				DBSETLPWD(dbc_control_ptr->server_ptr, ((char *) pass_word));
			if ((app_name != NULL) && *app_name)
				DBSETLAPP(dbc_control_ptr->server_ptr, ((char *) app_name));
			if ((dbc_control_ptr->database_ptr =
				dbopen(dbc_control_ptr->server_ptr, ((char *) server_name))) ==
				NULL) {
				sprintf(error_text,
			"%s %s database '%s' for owner '%s' on server '%s' failed: %-.800s",
					"Attempt to call 'dbopen()' for", app_name,
					(*database_name) ? database_name : "?",
					(*owner_name) ? owner_name : "?", server_name,
					DBC_MSSQL_MSG_GetHandlerMessage(error_buffer));
				dbfreelogin(dbc_control_ptr->server_ptr);
				dbc_control_ptr->server_ptr = NULL;
				return_code = DBC_DB_FAILURE;
			}
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		The code below is commented-out because Purify		*/
			/*	version 3.0 detects an SBR (actually, eleven of them)	*/
			/*	within the call to 'dbuse()'.									*/
			/*																			*/
			/*		This logic was always a bit of operational sugar	*/
			/*	because the routines which use it always specify		*/
			/* the database table on which the act.						*/
			/*	*****************************************************	*/
/*
			else if ((*database_name) && (dbuse(dbc_control_ptr->database_ptr,
				((char *) database_name)) != SUCCEED)) {
				sprintf(error_text,
			"%s %s database '%s' for owner '%s' on server '%s' failed: %-.800s",
					"Attempt to call 'dbuse()' for", db_name,
					(*database_name) ? database_name : "?",
					(*owner_name) ? owner_name : "?", server_name,
					DBC_MSSQL_MSG_GetHandlerMessage(error_buffer));
				dbclose(dbc_control_ptr->database_ptr);
				dbfreelogin(dbc_control_ptr->server_ptr);
				dbc_control_ptr->database_ptr = NULL;
				dbc_control_ptr->server_ptr   = NULL;
				return_code                   = DBC_DB_FAILURE;
			}
*/
			/*	*****************************************************	*/
		}
		DBC_MSSQL_MSG_PopHandler();
	}

	return(return_code);
}
/*	***********************************************************************	*/

