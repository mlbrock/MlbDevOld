/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Generalized Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes a 'DBC_GETROWS' structure to an empty
								state.

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

#include <memory.h>

#include "dbcfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DBC_INIT_DBCGetRows

	SYNOPSIS		:	void DBC_INIT_DBCGetRows(dbc_getrows_ptr);

						DBC_GETROWS *dbc_getrows_ptr;

	DESCRIPTION	:	Initializes the members of a ''DBC_GETROWS'' structure to
						their default values.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_getrows_ptr`` points to the ''DBC_GETROWS''
						structure to be initialized by this function.

	RETURNS		:	Void.

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2018 Michael L. Brock

	OUTPUT INDEX:	DBC_INIT_DBCGetRows
						Database Functions:Connection Functions:DBC_INIT_DBCGetRows

	PUBLISH XREF:	DBC_INIT_DBCGetRows

	PUBLISH NAME:	DBC_INIT_DBCGetRows

	ENTRY CLASS	:	Database Functions:Connection Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void DBC_INIT_DBCGetRows(DBC_GETROWS *dbc_getrows_ptr)
#else
void DBC_INIT_DBCGetRows(dbc_getrows_ptr)
DBC_GETROWS *dbc_getrows_ptr;
#endif /* #ifndef NARGS */
{
	memset(dbc_getrows_ptr, '\0', sizeof(*dbc_getrows_ptr));

	dbc_getrows_ptr->member_count      = 0;
	dbc_getrows_ptr->member_list       = NULL;
	dbc_getrows_ptr->sql_command       = NULL;
	dbc_getrows_ptr->table_name        = NULL;
	dbc_getrows_ptr->out_row_size      = 0;
	dbc_getrows_ptr->data_row_size     = 0;
	dbc_getrows_ptr->data_row_offset   = 0;
	dbc_getrows_ptr->max_row_count     = 0;
	dbc_getrows_ptr->alloc_granularity = 0;
	dbc_getrows_ptr->alloc_control_ptr = NULL;
	dbc_getrows_ptr->user_data_ptr     = NULL;
	dbc_getrows_ptr->per_row           = NULL;
	dbc_getrows_ptr->alloc             = NULL;
	dbc_getrows_ptr->realloc           = NULL;
	dbc_getrows_ptr->free              = NULL;
	dbc_getrows_ptr->per_row_free      = NULL;
}
/* *********************************************************************** */

