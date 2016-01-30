/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages cancellation of DBC DB-LIB results.

	Revision History	:	1996-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/*    Include necessary header files . . .                                 */
/* *********************************************************************** */

#include <string.h>

#include "dbcmssql.h"

/* *********************************************************************** */

/*
	ADF NOTE: Need comments here.
*/
/* *********************************************************************** */
int DBC_MSSQL_Cancel(dbc_control_ptr, error_text)
DBC_MSSQL_CONTROL *dbc_control_ptr;
char              *error_text;
{
	int return_code;

	if ((return_code = DBC_MSSQL_MSG_DefaultHandler(dbc_control_ptr,
		error_text)) == DBC_SUCCESS) {
		if (dbcancel(dbc_control_ptr->database_ptr) != SUCCEED)
			strcat(strcpy(error_text, "Call to 'dbcancel()' failed --- "),
				DBC_MSSQL_MSG_GetHandlerMessage(error_text));
		DBC_MSSQL_MSG_PopHandler();
		return_code = DBC_DB_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */

/*
	ADF NOTE: Need comments here.
*/
/* *********************************************************************** */
int DBC_MSSQL_CancelAll(dbc_control_ptr, error_text)
DBC_MSSQL_CONTROL *dbc_control_ptr;
char              *error_text;
{
	int  return_code = DBC_SUCCESS;
	int  tmp_return_code;
	char tmp_error_text[DBC_MAX_ERROR_TEXT];

	return_code = DBC_MSSQL_Cancel(dbc_control_ptr, error_text);

	if (((tmp_return_code = DBC_MSSQL_CancelQuery(dbc_control_ptr,
		tmp_error_text)) != DBC_SUCCESS) && (return_code == DBC_SUCCESS)) {
		return_code = tmp_return_code;
		strcpy(error_text, tmp_error_text);
	}

	return(return_code);
}
/* *********************************************************************** */

/*
	ADF NOTE: Need comments here.
*/
/* *********************************************************************** */
int DBC_MSSQL_CancelQuery(dbc_control_ptr, error_text)
DBC_MSSQL_CONTROL *dbc_control_ptr;
char              *error_text;
{
	int return_code;

	if ((return_code = DBC_MSSQL_MSG_DefaultHandler(dbc_control_ptr,
		error_text)) == DBC_SUCCESS) {
		if (dbcanquery(dbc_control_ptr->database_ptr) != SUCCEED)
			strcat(strcpy(error_text, "Call to 'dbcanquery()' failed --- "),
				DBC_MSSQL_MSG_GetHandlerMessage(error_text));
		DBC_MSSQL_MSG_PopHandler();
	}

	return(return_code);
}
/* *********************************************************************** */

