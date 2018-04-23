/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase CT-Library Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes an attachment to the Sybase CT-LIB facility.

	Revision History	:	1996-06-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dbcctlii.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_Close

   SYNOPSIS    :	void DBC_CTLIB_Close(dbc_control_ptr);

						DBC_CTLIB **dbc_control_ptr;

   DESCRIPTION :	Closes a ''DBC_CTLIB'' structure database connection
						(if active) and frees the memory associated with the
						structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` points to a pointer to the
						''DBC_CTLIB'' structure to be closed. It is assumed
						by this function that the structure has been properly
						initialized by ``DBC_CTLIB_Initialize``.

						(-) If a connection to a Sybase database has been performed
						by ``DBC_CTLIB_Open`` on the structure, the connection
						will be closed before the structure is freed.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	DBC_DBLIB_Close

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_Close
						DBC Sybase CT-LIB Functions:DBC_CTLIB_Close
						DBC Functions:Close Functions:DBC_CTLIB_Close

   PUBLISH XREF:	DBC_CTLIB_Close

   PUBLISH NAME:	DBC_CTLIB_Close

	ENTRY CLASS	:	DBC Functions:Close Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_CTLIB_Close(DBC_CTLIB **dbc_control_ptr)
#else
void DBC_CTLIB_Close(dbc_control_ptr)
DBC_CTLIB **dbc_control_ptr;
#endif /* #ifndef NARGS */
{
	if (*dbc_control_ptr != NULL) {
		if ((*dbc_control_ptr)->command_ptr != NULL) {
			ct_cancel((*dbc_control_ptr)->connection_ptr, NULL,
				CS_CANCEL_ALL);
			ct_cmd_drop((*dbc_control_ptr)->command_ptr);
		}
		if ((*dbc_control_ptr)->connection_ptr != NULL) {
			ct_close((*dbc_control_ptr)->connection_ptr, CS_FORCE_CLOSE);
			ct_con_drop((*dbc_control_ptr)->connection_ptr);
		}
		if ((*dbc_control_ptr)->context_ptr != NULL) {
			ct_exit((*dbc_control_ptr)->context_ptr, CS_FORCE_EXIT);
			cs_ctx_drop((*dbc_control_ptr)->context_ptr);
		}
		strl_remove_all(&(*dbc_control_ptr)->conn_count,
			&(*dbc_control_ptr)->conn_list);
		free(*dbc_control_ptr);
		*dbc_control_ptr = NULL;
	}
}
/*	***********************************************************************	*/

