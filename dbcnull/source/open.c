/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Internal Null Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Opens a connection to a Internal database for the
								Internal NULL facility.

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

   NAME        :	DBC_NULL_Open

   SYNOPSIS    :	return_code = DBC_NULL_Open(dbc_control_ptr, app_name,
							server_name, database_name, owner_name, user_name,
							pass_word, error_text);

						int                return_code;

						DBC_NULL *dbc_control_ptr;

						const char        *app_name;

						const char        *server_name;

						const char        *database_name;

						const char        *owner_name;

						const char        *user_name;

						const char        *pass_word;

						char              *error_text;

   DESCRIPTION :	Logs in and connects to a Internal database server.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_NULL'' structure to be used to open the
						connection with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_NULL_Initialize``.

						(.) ``app_name`` is the name of the application on behalf
						which the connection to the database is to be made. It is
						not required for the correct operation of this function and
						may be passed as ''NULL''.

						(.) ``server_name`` is the name of the Internal database to
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
						to the Internal database.

						(.) ``pass_word`` is the password to be used in conjunction
						with ``user_name`` to login to the Internal database.

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

   SEE ALSO    :	DBC_NULL_Initialize
						DBC_CTLIB_Open

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_NULL_Open
						DBC Internal NULL Functions:DBC_NULL_Open
						DBC Functions:Connect Functions:DBC_NULL_Open

   PUBLISH XREF:	DBC_NULL_Open

   PUBLISH NAME:	DBC_NULL_Open

	ENTRY CLASS	:	DBC Functions:Connect Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_NULL_Open(DBC_CONTEXT *dbc_context_ptr, const char *conn_type,
	const char *conn_string, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text)
#else
int DBC_NULL_Open(dbc_context_ptr, conn_type, conn_string, mlog_ptr, flags,
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
	strcat(strcpy(error_text, DBC_NULL_BASE_ERROR_TEXT),
		"'DBC_NULL_Open()' failed.");

	return(DBC_FAILURE);
}
/*	***********************************************************************	*/

