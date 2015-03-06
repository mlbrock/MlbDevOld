/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Generalized Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses a DBC database context specification.

	Revision History	:	1993-07-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include "dbcfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DBC_ParseConn

	SYNOPSIS		:	return_code = DBC_ParseConn(dbc_context_ptr, conn_type,
							conn_string, parsed_count, parsed_list, error_text);

						int                  return_code;

						const DBC_CONTEXT   *dbc_context_ptr;

						const char          *conn_type;

						const char          *conn_string;

						unsigned int        *parsed_count;

						char              ***parsed_list;

						char                *error_text;

	DESCRIPTION	:	Parse a DBC database connection string.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` is a pointer to the
						''DBC_CONTEXT'' structure which contains the facility
						to be used.

						(.) ``conn_type`` is a human-readable text which
						describes the purpose of the database connection. It is
						used only within error messages.

						(.) ``conn_string`` describes the nature of the
						connection to formed into a database context by this
						function.

						(-) For example, the connection string used by the Sybase
						DB-LIB and CT-LIB facilities and the Microsoft SQL Server
						facility has the following format:

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

	SEE ALSO		:	DBC_Open
						DBC_Close

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2015 Michael L. Brock

	OUTPUT INDEX:	DBC_ParseConn
						Database Functions:Facility Functions:DBC_ParseConn
						DBC Functions:Connection Functions:DBC_ParseConn

	PUBLISH XREF:	DBC_ParseConn

	PUBLISH NAME:	DBC_ParseConn

	ENTRY CLASS	:	Database Functions:Facility Functions
						DBC Functions:Connection Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_ParseConn(const DBC_CONTEXT *dbc_context_ptr, const char *conn_type,
	const char *conn_string, unsigned int *parsed_count, char ***parsed_list,
	char *error_text)
#else
int DBC_ParseConn(dbc_context_ptr, conn_type, conn_string, parsed_count,
	parsed_list, error_text)
const DBC_CONTEXT   *dbc_context_ptr;
const char          *conn_type;
const char          *conn_string;
unsigned int        *parsed_count;
char              ***parsed_list;
char                *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.parse_conn),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.parse_conn)
			(conn_type, conn_string, parsed_count, parsed_list, error_text);

	return(return_code);
}
/* *********************************************************************** */

