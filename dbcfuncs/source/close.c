/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Generalized Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes a DBC database context.

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

#include "dbcfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DBC_Close

	SYNOPSIS		:	void DBC_Close(dbc_context_ptr);

						DBC_CONTEXT *dbc_context_ptr;

	DESCRIPTION	:	Closes a DBC database context.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` points to the ''DBC_CONTEXT''
						structure (opened by a call to ``DBC_OPEN_DBContext``)
						for which this function is to close the database
						connection.

	RETURNS		:	Void.

	SEE ALSO		:	DBC_Open
						DBC_FREE_DBContext

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

	OUTPUT INDEX:	DBC_Close
						Database Functions:Connection Functions:DBC_Close

	PUBLISH XREF:	DBC_Close

	PUBLISH NAME:	DBC_Close

	ENTRY CLASS	:	Database Functions:Connection Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void DBC_Close(DBC_CONTEXT *dbc_context_ptr)
#else
void DBC_Close(dbc_context_ptr)
DBC_CONTEXT *dbc_context_ptr;
#endif /* #ifndef NARGS */
{
	if ((dbc_context_ptr->dbc_funcs.close != NULL) &&
		(dbc_context_ptr->dbc_control_ptr != NULL))
		(*dbc_context_ptr->dbc_funcs.close)(&dbc_context_ptr->dbc_control_ptr);

	DBC_FREE_DBContext(dbc_context_ptr);
}
/* *********************************************************************** */

