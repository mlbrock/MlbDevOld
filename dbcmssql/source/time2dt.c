/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a Microsoft SQL Server time type to a
								DATFUNCS 'DTIME' structure date.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <stdio.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_TimeToDTIME(dbc_type, time_ptr, dtime_ptr, error_text)
int         dbc_type;
const void *time_ptr;
DTIME      *dtime_ptr;
char       *error_text;
{
	int return_code = DBC_SUCCESS;

	switch (dbc_type) {
		case SQLDATETIM4	:
			DBC_MSSQL_MSSQL4ToDTIME(((const DBDATETIM4 *) time_ptr), dtime_ptr);
			break;
		case SQLDATETIME	:
			DBC_MSSQL_MSSQL8ToDTIME(((const DBDATETIME *) time_ptr), dtime_ptr);
			break;
		default				:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the DBC-time-to-DTIME conversion function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

