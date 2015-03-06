/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Generalized Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages cancellation of DBC facility results.

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
#ifndef NARGS
int DBC_Cancel(DBC_CONTEXT *dbc_context_ptr, char *error_text)
#else
int DBC_Cancel(dbc_context_ptr, error_text)
DBC_CONTEXT *dbc_context_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.cancel),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.cancel)
			(dbc_context_ptr->dbc_control_ptr, error_text);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int DBC_CancelAll(DBC_CONTEXT *dbc_context_ptr, char *error_text)
#else
int DBC_CancelAll(dbc_context_ptr, error_text)
DBC_CONTEXT *dbc_context_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.cancel_all),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.cancel_all)
			(dbc_context_ptr->dbc_control_ptr, error_text);

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int DBC_CancelQuery(DBC_CONTEXT *dbc_context_ptr, char *error_text)
#else
int DBC_CancelQuery(dbc_context_ptr, error_text)
DBC_CONTEXT *dbc_context_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.cancel_query),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.cancel_query)
			(dbc_context_ptr->dbc_control_ptr, error_text);

	return(return_code);
}
/* *********************************************************************** */

