/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Generalized Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees a DBC database context structure.

	Revision History	:	1993-07-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
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

#include "dbcfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DBC_FREE_DBContext

	SYNOPSIS		:	void DBC_FREE_DBContext(dbc_context_ptr);

						DBC_CONTEXT *dbc_context_ptr;

	DESCRIPTION	:	Frees ancilliary memory associated with a structure of
						type ''DBC_CONTEXT''.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` points to the ''DBC_CONTEXT''
						structure to be freed by this function.

	RETURNS		:	Void.

	SEE ALSO		:	DBC_INIT_DBContext

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

	OUTPUT INDEX:	DBC_FREE_DBContext
						Database Functions:Connection Functions:DBC_FREE_DBContext

	PUBLISH XREF:	DBC_FREE_DBContext

	PUBLISH NAME:	DBC_FREE_DBContext

	ENTRY CLASS	:	Database Functions:Connection Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void DBC_FREE_DBContext(DBC_CONTEXT *dbc_context_ptr)
#else
void DBC_FREE_DBContext(dbc_context_ptr)
DBC_CONTEXT *dbc_context_ptr;
#endif /* #ifndef NARGS */
{
	if ((dbc_context_ptr->dbc_funcs.close != NULL) &&
		(dbc_context_ptr->dbc_control_ptr != NULL))
		(*dbc_context_ptr->dbc_funcs.close)(&dbc_context_ptr->dbc_control_ptr);

	DBC_INIT_DBContext(dbc_context_ptr);
}
/* *********************************************************************** */

