/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Internal Null Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes an attachment to the Internal NULL facility.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dbcnulli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_NULL_Close

   SYNOPSIS    :	void DBC_NULL_Close(dbc_control_ptr);

						DBC_NULL **dbc_control_ptr;

   DESCRIPTION :	Closes a ''DBC_NULL'' structure database connection
						(if active) and frees the memory associated with the
						structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` points to a pointer to the
						''DBC_NULL'' structure to be closed. It is assumed
						by this function that the structure has been properly
						initialized by ``DBC_NULL_Initialize``.

						(-) If a connection to a Internal database has been performed
						by ``DBC_NULL_Open`` on the structure, the connection
						will be closed before the structure is freed.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	DBC_CTLIB_Close

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_NULL_Close
						DBC Internal NULL Functions:DBC_NULL_Close
						DBC Functions:Close Functions:DBC_NULL_Close

   PUBLISH XREF:	DBC_NULL_Close

   PUBLISH NAME:	DBC_NULL_Close

	ENTRY CLASS	:	DBC Functions:Close Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_NULL_Close(DBC_NULL **dbc_control_ptr)
#else
void DBC_NULL_Close(dbc_control_ptr)
DBC_NULL **dbc_control_ptr;
#endif /* #ifndef NARGS */
{
	if (*dbc_control_ptr != NULL) {
		strl_remove_all(&(*dbc_control_ptr)->conn_count,
			&(*dbc_control_ptr)->conn_list);
		free(*dbc_control_ptr);
		*dbc_control_ptr = NULL;
	}
}
/*	***********************************************************************	*/

