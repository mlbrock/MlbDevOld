/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Generic Sybase Support Functions Library Module							*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses a DBC database context specification.

	Revision History	:	1993-07-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <strfuncs.h>

#include "dbcsybi.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DBC_SYB_ParseConn

	SYNOPSIS		:	return_code = DBC_SYB_ParseConn(conn_type,
							conn_string, dbc_context_ptr, error_text);

						int          return_code;

						const char  *conn_type;

						const char  *conn_string;

						DBC_CONTEXT *dbc_context_ptr;

						char        *error_text;

	DESCRIPTION	:	Parse a parameter string in order to initialize a
						''DBC_CONTEXT'' structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``conn_type`` is a human-readable text which
						describes the purpose of the database connection. It is
						used only within error messages.

						(.) ``conn_string`` describes the nature of the
						connection to formed into a database context by this
						function. It has the following format:

						<|-|>``server-name``,''[''``database-name``'']'',''[''``owner-name``'']'',``user-name``''['',``password``'']''

						(.) ``parsed_count`` points to the unsigned int into which
						this function will place the number of ``conn_string``
						components parsed into the array ``parsed_list``.

						(.) ``parsed_list`` points to a pointer to char which is
						the array of char pointers which contain the components
						parsed from the ``conn_string`` parameter.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''DBC_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''DBC_SUCCESS'' if the function initializes the
						database context without error.

						(.) Otherwise, the function will return one of the non-zero
						DBC return codes indicating an error.

	NOTES			:	Use the related function ``DBC_OPEN_DBContext`` to
						open a connection to the database after this function
						has built the ''DBC_CONTEXT'' structure.

	CAVEATS		:	

	SEE ALSO		:	DBC_Open
						DBC_Close

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

	OUTPUT INDEX:	DBC_SYB_ParseConn
						DBC Sybase Functions:DBC_SYB_ParseConn
						DBC Functions:Connection Functions:DBC_SYB_ParseConn

	PUBLISH XREF:	DBC_SYB_ParseConn

	PUBLISH NAME:	DBC_SYB_ParseConn

	ENTRY CLASS	:	DBC Functions:Connection Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_ParseConn(const char *conn_type, const char *conn_string,
	unsigned int *parsed_count, char ***parsed_list, char *error_text)
#else
int DBC_SYB_ParseConn(conn_type, conn_string, parsed_count, parsed_list,
	error_text)
const char     *conn_type;
const char     *conn_string;
unsigned int   *parsed_count;
char         ***parsed_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code  = DBC_SUCCESS;
	unsigned int   tmp_count    = 0;
	char         **tmp_list     = NULL;
	char          *arg_data_ptr = NULL;
	unsigned int   count_1;

	*parsed_count = 0;
	*parsed_list  = NULL;

	if ((arg_data_ptr = strdup(conn_string)) == NULL) {
		STR_AllocMsgItem(strlen(conn_string) + 1, error_text,
			"%s database specification '%-.500s'",
			"Unable to allocate memory for a temporary copy of the",
			conn_string);
		return_code = DBC_MEMORY_FAILURE;
	}
	else {
		if (sepwordx_keep(trim(noblank(arg_data_ptr)), ",", &tmp_count,
			&tmp_list) != STRFUNCS_SUCCESS) {
			sprintf(error_text,
				"%s ('%s,%s') for the %s database specification.",
				"Unable to allocate memory for the database access data",
				"<db-server-name>,[<db-name>],[<db-owner-name>]",
				"<db-user-name>[,[<db-password>]]", conn_type);
			return_code = DBC_MEMORY_FAILURE;
		}
		else if ((tmp_count < 4) || (tmp_count > 5)) {
			sprintf(error_text,
				"%s %s %s encountered ('%.200s') --- '%s,%s' expected.",
				"Invalid", conn_type, "database specification parameter",
				conn_string,
				"<db-server-name>,[<db-name>],[<db-owner-name>]",
				"<db-user-name>[,[<db-password>]]");
			return_code = DBC_BAD_ARGS_FAILURE;
		}
		else if (!tmp_list[0][0]) {
			strcpy(error_text,
				"The server name component of the DB specification is empty.");
			return_code = DBC_BAD_ARGS_FAILURE;
		}
		else if (!tmp_list[3][0]) {
			strcpy(error_text,
				"The user name component of the DB specification is empty.");
			return_code = DBC_BAD_ARGS_FAILURE;
		}
		else {
			for (count_1 = 0; count_1 < tmp_count; count_1++) {
				if (strlen(tmp_list[count_1]) > DBC_SYB_MAX_ANY_NAME_LEN) {
					sprintf(error_text, "%s %s '%-.500s' (%u) %s (%u).",
						"The length of connection string",
						(count_1 == 0) ? "server name" :
						(count_1 == 1) ? "database name" :
						(count_1 == 2) ? "owner name"    :
						(count_1 == 3) ? "user name"     : "password",
						tmp_list[count_1], strlen(tmp_list[count_1]),
						"exceeds the maximum permissible length",
						DBC_SYB_MAX_ANY_NAME_LEN);
					return_code = DBC_FAILURE;
					break;
				}
			}
			if ((return_code == DBC_SUCCESS) && (tmp_count < 5) &&
				(strl_append(&tmp_count, &tmp_list, "") != STRFUNCS_SUCCESS)) {
				strcpy(error_text, "Unable to allocate an empty password.");
				return_code = DBC_MEMORY_FAILURE;
			}
			if (return_code == DBC_SUCCESS) {
				*parsed_count = tmp_count;
				*parsed_list  = tmp_list;
				tmp_count     = 0;
				tmp_list      = NULL;
			}
		}
		free(arg_data_ptr);
		strl_remove_all(&tmp_count, &tmp_list);
	}

	return(return_code);
}
/* *********************************************************************** */

