/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase CT-Library Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Executes a Sybase CT-LIB SQL statement.

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

   NAME        :	DBC_CTLIB_DoSQLCommand

   SYNOPSIS    :	return_code = DBC_CTLIB_DoSQLCommand(dbc_control_ptr,
							sql_command, error_text);

						int        return_code;

						DBC_CTLIB  *dbc_control_ptr;

						const char *sql_command;

						char       *error_text;

   DESCRIPTION :	Sends an SQL statement to a Sybase database server.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_CTLIB'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_CTLIB_Initialize`` and that a connection to a
						Sybase database has been performed by ``DBC_CTLIB_Open``.

						(.) ``sql_command`` is the SQL statement to be sent to the
						Sybase database server.

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

   SEE ALSO    :	DBC_DBLIB_DoSQLCommand

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_DoSQLCommand
						DBC Sybase CT-LIB Functions:DBC_CTLIB_DoSQLCommand
						DBC Functions:SQL Functions:DBC_CTLIB_DoSQLCommand

   PUBLISH XREF:	DBC_CTLIB_DoSQLCommand

   PUBLISH NAME:	DBC_CTLIB_DoSQLCommand

	ENTRY CLASS	:	DBC Functions:SQL Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_CTLIB_DoSQLCommand(DBC_CTLIB *dbc_control_ptr, const char *sql_command,
	char *error_text)
#else
int DBC_CTLIB_DoSQLCommand(dbc_control_ptr, sql_command, error_text)
DBC_CTLIB  *dbc_control_ptr;
const char *sql_command;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = DBC_SUCCESS;
	char error_buffer[DBC_MAX_ERROR_TEXT];

	if ((sql_command == NULL) || (!(*sql_command))) {
		strcpy(error_text, "SQL command buffer is blank.");
		return_code = DBC_BAD_ARGS_FAILURE;
	}
	else {
		DBC_CTLIB_MSG_ClearMsg(dbc_control_ptr);
		if (dbc_control_ptr->flags & DBC_FLAG_DEBUG_SQL)
			MLOG_LogInfo(dbc_control_ptr->mlog_ptr,
				"SQL COMMAND TO SERVER:[%s]\n", sql_command);
		if (ct_command(dbc_control_ptr->command_ptr, CS_LANG_CMD,
			((char *) sql_command), CS_NULLTERM, CS_UNUSED) != CS_SUCCEED) {
			strcat(strcpy(error_text, "Call to 'ct_command()' failed --- "),
				DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_buffer));
			return_code = DBC_DB_FAILURE;
		}
		else if (ct_send(dbc_control_ptr->command_ptr) != CS_SUCCEED) {
			strcat(strcpy(error_text, "Call to 'ct_send()' failed --- "),
				DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_buffer));
			ct_cancel(NULL, dbc_control_ptr->command_ptr, CS_CANCEL_CURRENT);
			return_code = DBC_DB_FAILURE;
		}
	}

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <genfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#define TEST_LOG_FILE_NAME					"DBC_CTLIB_DoSQL.LOG"

#define PROMPT_TEXT							"ENTER SQL COMMAND>"

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int                return_code     = DBC_SUCCESS;
	DBC_CTLIB *dbc_control_ptr = NULL;
	MLOG              *mlog_ptr        = NULL;
	const char        *connection_string = "SPS_PROD,,,mlds,mlds";
	DBC_CONTEXT        dbc_context;
	char               buffer[8192];
	char               error_text[DBC_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'DBC_CTLIB_DoSQLCommand()'\n");
	fprintf(stderr, "---- ------- --- --------------------------\n\n");

	if (argc > 1)
		connection_string = argv[1];

	if ((mlog_ptr = MLOG_FOpenDefault(TEST_LOG_FILE_NAME)) == NULL) {
		sprintf(error_text,
			"Unable to 'MLOG_FOpenDefault()' the log file '%s' for writing: ",
			TEST_LOG_FILE_NAME);
		GEN_AppendLastErrorString(0, DBC_MAX_ERROR_TEXT, error_text);
		return_code = DBC_SYSTEM_FAILURE;
	}
	else {
		if ((return_code = DBC_Open(&dbc_context, DBC_CTLIB_AttachFacility,
			"Test App", connection_string, mlog_ptr, DBC_FLAG_ALL, NULL,
			error_text)) == DBC_SUCCESS) {
			dbc_control_ptr = ((DBC_CTLIB *) dbc_context.dbc_control_ptr);
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
				else if ((return_code = DBC_CTLIB_DoSQLCommand(dbc_control_ptr,
					buffer, error_text)) != DBC_SUCCESS)
					fprintf(stderr, "\nERROR ON SQL COMMAND: %s\n\n",
						error_text);
				else {
					ct_cancel(dbc_control_ptr->connection_ptr, NULL,
						CS_CANCEL_ALL);
					fprintf(stderr, "COMMAND DONE\n");
				}
			}
			DBC_Close(&dbc_context);
		}
		MLOG_Close(mlog_ptr, NULL);
	}

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "ERROR: %s\n\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

