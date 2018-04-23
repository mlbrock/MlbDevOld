/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Executes a Microsoft SQL Server SQL statement.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
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

   NAME        :	DBC_MSSQL_DoSQLCommand

   SYNOPSIS    :	return_code = DBC_MSSQL_DoSQLCommand(dbc_control_ptr,
							sql_command, error_text);

						int                return_code;

						DBC_MSSQL_CONTROL *dbc_control_ptr;

						const char        *sql_command;

						char              *error_text;

   DESCRIPTION :	Sends an SQL statement to a Microsoft SQL Server database server.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_MSSQL_CONTROL'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_MSSQL_Initialize`` and that a connection to a
						Microsoft SQL Server database has been performed by ``DBC_MSSQL_Connect``.

						(.) ``sql_command`` is the SQL statement to be sent to the
						Microsoft SQL Server database server.

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

   SEE ALSO    :	DBC_CTLIB_DoSQLCommand

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_DoSQLCommand
						DBC DB-LIB Functions:DBC_MSSQL_DoSQLCommand
						DBC Functions:SQL Functions:DBC_MSSQL_DoSQLCommand

   PUBLISH XREF:	DBC_MSSQL_DoSQLCommand

   PUBLISH NAME:	DBC_MSSQL_DoSQLCommand

	ENTRY CLASS	:	DBC Functions:SQL Functions

EOH */
/*	***********************************************************************	*/
int DBC_MSSQL_DoSQLCommand(dbc_control_ptr, sql_command, error_text)
DBC_MSSQL_CONTROL *dbc_control_ptr;
const char        *sql_command;
char              *error_text;
{
	int  return_code;
	char error_buffer[DBC_MAX_ERROR_TEXT];

	if ((sql_command == NULL) || (!(*sql_command))) {
		strcpy(error_text, "SQL command buffer is blank.");
		return_code = DBC_BAD_ARGS_FAILURE;
	}
	else if ((return_code = DBC_MSSQL_MSG_DefaultHandler(dbc_control_ptr,
		error_text)) == DBC_SUCCESS) {
		if (dbc_control_ptr->flags & DBC_FLAG_DEBUG_SQL)
			MLOG_LogInfo(dbc_control_ptr->mlog_ptr,
				"SQL COMMAND TO SERVER:[%s]\n", sql_command);
		if (dbcmd(dbc_control_ptr->database_ptr, ((char *) sql_command)) !=
			SUCCEED) {
			strcat(strcpy(error_text, "Call to 'dbcmd()' failed --- "),
				DBC_MSSQL_MSG_GetHandlerMessage(error_buffer));
			return_code = DBC_DB_FAILURE;
		}
		else if (dbsqlexec(dbc_control_ptr->database_ptr) != SUCCEED) {
			strcat(strcpy(error_text, "Call to 'dbsqlexec()' failed --- "),
				DBC_MSSQL_MSG_GetHandlerMessage(error_buffer));
			dbcancel(dbc_control_ptr->database_ptr);
			return_code = DBC_DB_FAILURE;
		}
		DBC_MSSQL_MSG_PopHandler();
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <genfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#define TEST_LOG_FILE_NAME					"DBC_MSSQL_DoSQL.LOG"

#define PROMPT_TEXT							"ENTER SQL COMMAND>"

int main(argc, argv)
int    argc;
char **argv;
{
	int                return_code       = DBC_SUCCESS;
	DBC_MSSQL_CONTROL *dbc_control_ptr   = NULL;
	MLOG              *mlog_ptr          = NULL;
	const char        *connection_string = "SPS_PROD,,,mlds,mlds";
	DBC_CONTEXT        dbc_context;
	int                db_results_flag;
	char               buffer[8192];
	char               error_text[DBC_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'DBC_MSSQL_DoSQLCommand()'\n");
	fprintf(stderr, "---- ------- --- --------------------------\n\n");

	if (argc > 1)
		connection_string = argv[1];

	if (dbinit() != SUCCEED) {
		strcpy(error_text, "Call to 'dbinit()' failed.");
		return_code = DBC_DB_FAILURE;
	}
	else if ((mlog_ptr = MLOG_FOpenDefault(TEST_LOG_FILE_NAME)) == NULL) {
		sprintf(error_text,
			"Unable to 'MLOG_FOpenDefault()' the log file '%s' for writing: ",
			TEST_LOG_FILE_NAME);
		GEN_AppendLastErrorString(0, DBC_MAX_ERROR_TEXT, error_text);
		return_code = DBC_SYSTEM_FAILURE;
	}
	else {
		if ((return_code = DBC_Open(&dbc_context, DBC_MSSQL_AttachFacility,
			"Test App", connection_string, mlog_ptr, DBC_FLAG_ALL, NULL,
			error_text)) == DBC_SUCCESS) {
			dbc_control_ptr = ((DBC_MSSQL_CONTROL *) dbc_context.dbc_control_ptr);
			while ((!feof(stdin)) && (!ferror(stdin))) {
				printf("%s", PROMPT_TEXT);
				fgets(buffer, sizeof(buffer) - 1, stdin);
				while (*buffer && (buffer[strlen(buffer) - 1] == '\n'))
					buffer[strlen(buffer) - 1] = '\0';
				if (!(*trim(oneblank(buffer))))
					continue;
				else if ((!stricmp(buffer, "QUIT")) ||
					(!stricmp(buffer, "EXIT")))
					break;
				else if ((return_code = DBC_MSSQL_DoSQLCommand(dbc_control_ptr,
					buffer, error_text)) != DBC_SUCCESS)
					fprintf(stderr, "\nERROR ON SQL COMMAND: %s\n\n",
						error_text);
				else {
					while (((db_results_flag =
						dbresults(dbc_control_ptr->database_ptr)) !=
						FAIL) && (db_results_flag != NO_MORE_RESULTS)) {
						if (DBCMDROW(dbc_control_ptr->database_ptr) == SUCCEED) {
							dbprhead(dbc_control_ptr->database_ptr);
							dbprrow(dbc_control_ptr->database_ptr);
						}
					}
					fprintf(stderr, "COMMAND DONE\n");
				}
			}
			DBC_Close(&dbc_context);
		}
		MLOG_Close(mlog_ptr, NULL);
	}

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

