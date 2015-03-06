/* *********************************************************************** */
/* *********************************************************************** */
/*	DBC Generalized Support Functions Library Module								*/
/* *********************************************************************** */
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes a DBC database functions structure to an
								empty state.

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

#include <memory.h>

#include "dbcfunci.h"

/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	DBC_INIT_DBCFuncs

	SYNOPSIS		:	void DBC_INIT_DBCFuncs(funcs_ptr);

						DBC_FUNCS *funcs_ptr;

	DESCRIPTION	:	Initializes the members of a ''DBC_FUNCS'' structure to
						their default values.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``funcs_ptr`` points to the ''DBC_FUNCS''
						structure to be initialized by this function.

	RETURNS		:	Void.

	AUTHOR		:	Michael L. Brock

   COPYRIGHT   :	Copyright 1993 - 2015 Michael L. Brock

	OUTPUT INDEX:	DBC_INIT_DBCFuncs
						Database Functions:Connection Functions:DBC_INIT_DBCFuncs

	PUBLISH XREF:	DBC_INIT_DBCFuncs

	PUBLISH NAME:	DBC_INIT_DBCFuncs

	ENTRY CLASS	:	Database Functions:Connection Functions

EOH */
/* *********************************************************************** */
#ifndef NARGS
void DBC_INIT_DBCFuncs(DBC_FUNCS *funcs_ptr)
#else
void DBC_INIT_DBCFuncs(funcs_ptr)
DBC_FUNCS *funcs_ptr;
#endif /* #ifndef NARGS */
{
	memset(funcs_ptr, '\0', sizeof(*funcs_ptr));

	funcs_ptr->bind               = NULL;
	funcs_ptr->cancel             = NULL;
	funcs_ptr->cancel_query       = NULL;
	funcs_ptr->close              = NULL;
	funcs_ptr->do_sql             = NULL;
	funcs_ptr->get_id             = NULL;
	funcs_ptr->get_rows           = NULL;
	funcs_ptr->get_rows_basic     = NULL;
	funcs_ptr->get_vendor_name    = NULL;
	funcs_ptr->get_version        = NULL;
	funcs_ptr->get_version_string = NULL;
	funcs_ptr->init               = NULL;
	funcs_ptr->parse_conn         = NULL;
	funcs_ptr->table_to_members   = NULL;
	funcs_ptr->set_display_length = NULL;
	funcs_ptr->dump_field         = NULL;
	funcs_ptr->double_to_number   = NULL;
	funcs_ptr->number_to_double   = NULL;
	funcs_ptr->dtime_to_date      = NULL;
	funcs_ptr->date_to_dtime      = NULL;
	funcs_ptr->dtime_to_time      = NULL;
	funcs_ptr->time_to_dtime      = NULL;
	funcs_ptr->is_number          = NULL;
	funcs_ptr->min_number         = NULL;
	funcs_ptr->max_number         = NULL;
	funcs_ptr->cmp_number         = NULL;
	funcs_ptr->scmp_number        = NULL;
	funcs_ptr->is_date            = NULL;
	funcs_ptr->min_date           = NULL;
	funcs_ptr->max_date           = NULL;
	funcs_ptr->cmp_date           = NULL;
	funcs_ptr->scmp_date          = NULL;
	funcs_ptr->is_time            = NULL;
	funcs_ptr->min_time           = NULL;
	funcs_ptr->max_time           = NULL;
	funcs_ptr->cmp_time           = NULL;
	funcs_ptr->scmp_time          = NULL;
}
/* *********************************************************************** */

