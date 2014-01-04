/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Internal Null Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages cancellation of DBC Internal NULL results.

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

#include "dbcnulli.h"

/* *********************************************************************** */

/*
	ADF NOTE: Need comments here.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_NULL_Cancel(DBC_NULL *dbc_control_ptr, char *error_text)
#else
int DBC_NULL_Cancel(dbc_control_ptr, error_text)
DBC_NULL *dbc_control_ptr;
char     *error_text;
#endif /* #ifndef NARGS */
{
	strcat(strcpy(error_text, DBC_NULL_BASE_ERROR_TEXT),
		"'DBC_NULL_Cancel()' failed.");

	return(DBC_FAILURE);
}
/* *********************************************************************** */

/*
	ADF NOTE: Need comments here.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_NULL_CancelAll(DBC_NULL *dbc_control_ptr, char *error_text)
#else
int DBC_NULL_CancelAll(dbc_control_ptr, error_text)
DBC_NULL *dbc_control_ptr;
char     *error_text;
#endif /* #ifndef NARGS */
{
	strcat(strcpy(error_text, DBC_NULL_BASE_ERROR_TEXT),
		"'DBC_NULL_CancelAll()' failed.");

	return(DBC_FAILURE);
}
/* *********************************************************************** */

/*
	ADF NOTE: Need comments here.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_NULL_CancelQuery(DBC_NULL *dbc_control_ptr, char *error_text)
#else
int DBC_NULL_CancelQuery(dbc_control_ptr, error_text)
DBC_NULL *dbc_control_ptr;
char     *error_text;
#endif /* #ifndef NARGS */
{
	strcat(strcpy(error_text, DBC_NULL_BASE_ERROR_TEXT),
		"'DBC_NULL_CancelQuery()' failed.");

	return(DBC_FAILURE);
}
/* *********************************************************************** */

