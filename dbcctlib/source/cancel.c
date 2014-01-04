/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Sybase CT-Library Support Functions Library Module						*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages cancellation of DBC Sybase CT-LIB results.

	Revision History	:	1996-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
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

#include "dbcctlii.h"

/* *********************************************************************** */

/*
	ADF NOTE: Need comments here.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_CTLIB_Cancel(DBC_CTLIB *dbc_control_ptr, char *error_text)
#else
int DBC_CTLIB_Cancel(dbc_control_ptr, error_text)
DBC_CTLIB *dbc_control_ptr;
char      *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_SUCCESS;

	DBC_CTLIB_MSG_ClearMsg(dbc_control_ptr);

	if (ct_cancel(dbc_control_ptr->connection_ptr, NULL, CS_CANCEL_ALL) !=
		CS_SUCCEED) {
		sprintf(error_text, "Call to 'ct_cancel(%s)' failed --- %-500s",
			"CS_CANCEL_ALL",
			DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_text));
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
int DBC_CTLIB_CancelAll(DBC_CTLIB *dbc_control_ptr, char *error_text)
#else
int DBC_CTLIB_CancelAll(dbc_control_ptr, error_text)
DBC_CTLIB *dbc_control_ptr;
char      *error_text;
#endif /* #ifndef NARGS */
{
	int        return_code = DBC_SUCCESS;
	int        tmp_return_code;
	CS_RETCODE cs_return_code;
	CS_INT     result_type;
	char       tmp_error_text[DBC_MAX_ERROR_TEXT];

	DBC_CTLIB_MSG_ClearMsg(dbc_control_ptr);

	while ((cs_return_code = ct_results(dbc_control_ptr->command_ptr,
		&result_type)) == CS_SUCCEED) {
		if (((tmp_return_code = DBC_CTLIB_CancelQuery(dbc_control_ptr,
			tmp_error_text)) != DBC_SUCCESS) && (return_code == DBC_SUCCESS)) {
			return_code = tmp_return_code;
			strcpy(error_text, tmp_error_text);
		}
	}

	if ((cs_return_code == CS_FAIL) &&
		((tmp_return_code = DBC_CTLIB_Cancel(dbc_control_ptr,
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
int DBC_CTLIB_CancelQuery(DBC_CTLIB *dbc_control_ptr, char *error_text)
#else
int DBC_CTLIB_CancelQuery(dbc_control_ptr, error_text)
DBC_CTLIB *dbc_control_ptr;
char      *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_SUCCESS;

	DBC_CTLIB_MSG_ClearMsg(dbc_control_ptr);

	if (ct_cancel(NULL, dbc_control_ptr->command_ptr, CS_CANCEL_CURRENT) !=
		CS_SUCCEED) {
		sprintf(error_text, "Call to 'ct_cancel(%s)' failed --- %-500s",
			"CS_CANCEL_CURRENT",
			DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_text));
		return_code = DBC_DB_FAILURE;
	}

	return(return_code);
}
/* *********************************************************************** */

