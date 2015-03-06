/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Sybase DB-Library Support Functions Library Module						*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages cancellation of DBC Sybase DB-LIB results.

	Revision History	:	1996-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
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

#include "dbcdblii.h"

/* *********************************************************************** */

/*
	ADF NOTE: Need comments here.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_DBLIB_Cancel(DBC_DBLIB *dbc_control_ptr, char *error_text)
#else
int DBC_DBLIB_Cancel(dbc_control_ptr, error_text)
DBC_DBLIB *dbc_control_ptr;
char      *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_DBLIB_MSG_DefaultHandler(dbc_control_ptr,
		error_text)) == DBC_SUCCESS) {
		if (dbcancel(dbc_control_ptr->database_ptr) != SUCCEED)
			strcat(strcpy(error_text, "Call to 'dbcancel()' failed --- "),
				DBC_DBLIB_MSG_GetHandlerMessage(error_text));
		DBC_DBLIB_MSG_PopHandler();
		return_code = DBC_DB_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */

/*
	ADF NOTE: Need comments here.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_DBLIB_CancelAll(DBC_DBLIB *dbc_control_ptr, char *error_text)
#else
int DBC_DBLIB_CancelAll(dbc_control_ptr, error_text)
DBC_DBLIB *dbc_control_ptr;
char      *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = DBC_SUCCESS;
	int  tmp_return_code;
	char tmp_error_text[DBC_MAX_ERROR_TEXT];

	return_code = DBC_DBLIB_Cancel(dbc_control_ptr, error_text);

	if (((tmp_return_code = DBC_DBLIB_CancelQuery(dbc_control_ptr,
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
#ifndef NARGS
int DBC_DBLIB_CancelQuery(DBC_DBLIB *dbc_control_ptr, char *error_text)
#else
int DBC_DBLIB_CancelQuery(dbc_control_ptr, error_text)
DBC_DBLIB *dbc_control_ptr;
char      *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_DBLIB_MSG_DefaultHandler(dbc_control_ptr,
		error_text)) == DBC_SUCCESS) {
		if (dbcanquery(dbc_control_ptr->database_ptr) != SUCCEED)
			strcat(strcpy(error_text, "Call to 'dbcanquery()' failed --- "),
				DBC_DBLIB_MSG_GetHandlerMessage(error_text));
		DBC_DBLIB_MSG_PopHandler();
	}

	return(return_code);
}
/* *********************************************************************** */

