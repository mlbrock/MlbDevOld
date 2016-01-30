/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Internal Null Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Executes a Internal SQL statement.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
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

#include "dbcnulli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_NULL_DoSQLCommand

   SYNOPSIS    :	return_code = DBC_NULL_DoSQLCommand(dbc_control_ptr,
							sql_command, error_text);

						int                return_code;

						DBC_NULL *dbc_control_ptr;

						const char        *sql_command;

						char              *error_text;

   DESCRIPTION :	Sends an SQL statement to a Internal database server.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_NULL'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_NULL_Initialize`` and that a connection to a
						Internal database has been performed by ``DBC_NULL_Open``.

						(.) ``sql_command`` is the SQL statement to be sent to the
						Internal database server.

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

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_NULL_DoSQLCommand
						DBC Internal NULL Functions:DBC_NULL_DoSQLCommand
						DBC Functions:SQL Functions:DBC_NULL_DoSQLCommand

   PUBLISH XREF:	DBC_NULL_DoSQLCommand

   PUBLISH NAME:	DBC_NULL_DoSQLCommand

	ENTRY CLASS	:	DBC Functions:SQL Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_NULL_DoSQLCommand(DBC_NULL *dbc_control_ptr, const char *sql_command,
	char *error_text)
#else
int DBC_NULL_DoSQLCommand(dbc_control_ptr, sql_command, error_text)
DBC_NULL   *dbc_control_ptr;
const char *sql_command;
char       *error_text;
#endif /* #ifndef NARGS */
{
	strcat(strcpy(error_text, DBC_NULL_BASE_ERROR_TEXT),
		"'DBC_NULL_DoSQLCommand()' failed.");

	return(DBC_FAILURE);
}
/* *********************************************************************** */


