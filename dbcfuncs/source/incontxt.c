/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Generalized Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes a DBC database context structure to an
								empty state.

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

#include <memory.h>

#include "dbcfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DBC_INIT_DBContext

	SYNOPSIS		:	void DBC_INIT_DBContext(dbc_context_ptr);

						DBC_CONTEXT *dbc_context_ptr;

	DESCRIPTION	:	Initializes the members of a ''DBC_CONTEXT''
						structure to their default values.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` points to the ''DBC_CONTEXT''
						structure to be initialized by this function.

	RETURNS		:	Void.

	SEE ALSO		:	DBC_FREE_DBContext

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	DBC_INIT_DBContext
						Database Functions:Connection Functions:DBC_INIT_DBContext

	PUBLISH XREF:	DBC_INIT_DBContext

	PUBLISH NAME:	DBC_INIT_DBContext

	ENTRY CLASS	:	Database Functions:Connection Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void DBC_INIT_DBContext(DBC_CONTEXT *dbc_context_ptr)
#else
void DBC_INIT_DBContext(dbc_context_ptr)
DBC_CONTEXT *dbc_context_ptr;
#endif /* #ifndef NARGS */
{
	memset(dbc_context_ptr, '\0', sizeof(*dbc_context_ptr));

	dbc_context_ptr->signature       = DBC_SIGNATURE_NONE;
	dbc_context_ptr->user_data_ptr   = NULL;
	dbc_context_ptr->dbc_control_ptr = NULL;

	DBC_INIT_DBCFuncs(&dbc_context_ptr->dbc_funcs);
}
/* *********************************************************************** */

