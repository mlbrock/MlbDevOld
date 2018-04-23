/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Generalized Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Opens a DBC database context.

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

#include <stdlib.h>
#include <string.h>

#include "dbcfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DBC_Open

	SYNOPSIS		:	return_code = DBC_Open(dbc_context_ptr,
							conn_type, conn_string, db_debug_flag,
							sql_debug_flag, user_data_ptr, error_text);

						int          return_code;

						DBC_CONTEXT *dbc_context_ptr;

						const char  *conn_type;

						const char  *conn_string;

						MLOG        *mlog_ptr;

						DBC_FLAGS    flags;

						void        *user_data_ptr;

						char        *error_text;

	DESCRIPTION	:	Opens a DBC database context.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` points to the ''DBC_CONTEXT''
						structure which this function is to initialize.

						(.) ``conn_type`` is a human-readable text which
						describes the purpose of the database connection to be made
						by this function. It is used only within error messages.

						(.) ``conn_string`` describes the nature of the
						connection to be made by this function. It has the
						following format:

						<|-|>``server-name``,''[''``database-name``'']'',''[''``owner-name``'']'',``user-name``''['',``password``'']''

						(.) ``mlog_ptr`` points to the ''MLOG''
						structure to be used for logging of database messages and
						SQL statements.

						(.) ``flags`` contains indicators as to the type of
						debugging to be performed.

						(.) ``user_data_ptr`` is a pointer to ''void'' which the
						application programmer may use in order to attach
						application-specific knowledge to the ''DBC_CONTEXT''
						structure to which ``dbc_context_ptr`` points.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''DBC_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	Returns from this function are as follow:

						(.) ''DBC_SUCCESS'' if the function initializes a
						connection to the database without error.

						(.) Otherwise, the function will return one of the non-zero
						DBC return codes indicating an error.

	NOTES			:	Use the related function ``DBC_Close`` to
						close the connection to the database when you have no
						further need of it.

	SEE ALSO		:	DBC_Close

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

	OUTPUT INDEX:	DBC_Open
						Database Functions:Connection Functions:DBC_Open

	PUBLISH XREF:	DBC_Open

	PUBLISH NAME:	DBC_Open

	ENTRY CLASS	:	Database Functions:Connection Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_Open(DBC_CONTEXT *dbc_context_ptr,
	void (*attach_func)(DBC_FUNCS *funcs_ptr), const char *conn_type,
	const char *conn_string, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text)
#else
int DBC_Open(dbc_context_ptr, attach_func, conn_type, conn_string, mlog_ptr,
	flags, user_data_ptr, error_text)
DBC_CONTEXT  *dbc_context_ptr;
void        (*attach_func)(DBC_FUNCS *funcs_ptr);
const char   *conn_type;
const char   *conn_string;
MLOG         *mlog_ptr;
DBC_FLAG      flags;
void         *user_data_ptr;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	DBC_INIT_DBContext(dbc_context_ptr);

	attach_func = (attach_func != NULL) ? attach_func :
		DBC_AttachFacility;

	(*attach_func)(&dbc_context_ptr->dbc_funcs);

	if (dbc_context_ptr->dbc_funcs.open == NULL) {
		strcat(strcpy(error_text, "Unable to locate the DBC database "),
			"open function.");
		return_code = DBC_FAILURE;
	}
	else {
		dbc_context_ptr->signature = DBC_SIGNATURE_OK;
		if ((return_code = (*dbc_context_ptr->dbc_funcs.open)(dbc_context_ptr,
			conn_type, conn_string, mlog_ptr, flags, user_data_ptr,
			error_text)) != DBC_SUCCESS)
			DBC_FREE_DBContext(dbc_context_ptr);
	}

	return(return_code);
}
/* *********************************************************************** */

