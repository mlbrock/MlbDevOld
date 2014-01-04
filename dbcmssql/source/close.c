/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes an attachment to the Microsoft SQL Server
								DB-LIB facility.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_Close

   SYNOPSIS    :	void DBC_MSSQL_Close(dbc_control_ptr);

						DBC_MSSQL_CONTROL **dbc_control_ptr;

   DESCRIPTION :	Closes a ''DBC_MSSQL_CONTROL'' structure database connection
						(if active) and frees the memory associated with the
						structure.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` points to a pointer to the
						''DBC_MSSQL_CONTROL'' structure to be closed. It is assumed
						by this function that the structure has been properly
						initialized by ``DBC_MSSQL_Initialize``.

						(-) If a connection to a Microsoft SQL Server database has been performed
						by ``DBC_MSSQL_Connect`` on the structure, the connection
						will be closed before the structure is freed.

   RETURNS     :	Void.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	DBC_CTLIB_Close

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_Close
						DBC DB-LIB Functions:DBC_MSSQL_Close
						DBC Functions:Close Functions:DBC_MSSQL_Close

   PUBLISH XREF:	DBC_MSSQL_Close

   PUBLISH NAME:	DBC_MSSQL_Close

	ENTRY CLASS	:	DBC Functions:Close Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_Close(dbc_control_ptr)
DBC_MSSQL_CONTROL **dbc_control_ptr;
{
	if (*dbc_control_ptr != NULL) {
		if ((*dbc_control_ptr)->server_ptr != NULL)
			dbfreelogin((*dbc_control_ptr)->server_ptr);
		if ((*dbc_control_ptr)->database_ptr != NULL)
			dbclose((*dbc_control_ptr)->database_ptr);
		strl_remove_all(&(*dbc_control_ptr)->conn_count,
			&(*dbc_control_ptr)->conn_list);
		free(*dbc_control_ptr);
		*dbc_control_ptr = NULL;
	}
}
/*	***********************************************************************	*/

