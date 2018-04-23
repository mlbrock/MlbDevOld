/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Executes an SQL statement.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dbcfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DoSQL

   SYNOPSIS    :	return_code = DBC_DoSQL(dbc_context_ptr, sql_command,
							error_text);

						int          return_code;

						DBC_CONTEXT *dbc_context_ptr;

						const char  *sql_command;

						char        *error_text;

   DESCRIPTION :	Sends an SQL statement to a facility database server.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` is a pointer to the
						''DBC_CONTEXT'' structure to be used to manage
						communication with the database.

						(.) ``sql_command`` is the SQL statement to be sent to the
						database server.

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

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DoSQL
						Database Functions:Facility Functions:DBC_DoSQL

   PUBLISH XREF:	DBC_DoSQL

   PUBLISH NAME:	DBC_DoSQL

	ENTRY CLASS	:	Database Functions:Facility Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_DoSQL(DBC_CONTEXT *dbc_context_ptr, const char *sql_command,
	char *error_text)
#else
int DBC_DoSQL(dbc_context_ptr, sql_command, error_text)
DBC_CONTEXT *dbc_context_ptr;
const char  *sql_command;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.do_sql), error_text)) ==
		DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.do_sql)
			(dbc_context_ptr->dbc_control_ptr, sql_command, error_text);

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <genfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#define TEST_LOG_FILE_NAME					"DBC_DoSQL.LOG"

#define PROMPT_TEXT							"ENTER SQL COMMAND>"

#include "dbcdblib.h"

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int                return_code       = DBC_SUCCESS;
	MLOG              *mlog_ptr          = NULL;
	const char        *connection_string = "SPS_PROD,,,mlds,mlds";
	DBC_CONTEXT        dbc_context;
	int                db_results_flag;
	char               buffer[8192];
	char               error_text[DBC_MAX_ERROR_TEXT];

DBC_DBLIB *dbc_control_ptr;

	fprintf(stderr, "Test routine for 'DBC_DoSQL()'\n");
	fprintf(stderr, "---- ------- --- -------------\n\n");

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
		if ((return_code = DBC_Open(&dbc_context, DBC_AttachFacility,
			"Test App", connection_string, mlog_ptr, DBC_FLAG_ALL, NULL,
			error_text)) == DBC_SUCCESS) {
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
				else if ((return_code = DBC_DoSQL(&dbc_context,
					buffer, error_text)) != DBC_SUCCESS)
					fprintf(stderr, "\nERROR ON SQL COMMAND: %s\n\n",
						error_text);
				else {
dbc_control_ptr = ((DBC_DBLIB *) dbc_context.dbc_control_ptr);
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

