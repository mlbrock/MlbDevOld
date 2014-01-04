/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Generalized Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes a DBC facility handle.

	Revision History	:	1993-07-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
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
#ifndef NARGS
int DBC_Initialize(DBC_CONTEXT *dbc_context_ptr,
	void (*attach_func)(DBC_FUNCS *funcs_ptr), MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text)
#else
int DBC_Initialize(dbc_context_ptr, attach_func, mlog_ptr, flags,
	user_data_ptr, error_text)
DBC_CONTEXT  *dbc_context_ptr;
void        (*attach_func)(DBC_FUNCS *funcs_ptr);
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

	if (dbc_context_ptr->dbc_funcs.init == NULL) {
		strcat(strcpy(error_text, "Unable to locate the DBC database "),
			"init function.");
		return_code = DBC_FAILURE;
	}
	else {
		dbc_context_ptr->signature = DBC_SIGNATURE_OK;
		if ((return_code = (*dbc_context_ptr->dbc_funcs.init)(dbc_context_ptr,
			mlog_ptr, flags, user_data_ptr, error_text)) != DBC_SUCCESS)
			DBC_FREE_DBContext(dbc_context_ptr);
	}

	return(return_code);
}
/* *********************************************************************** */

