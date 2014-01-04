/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Generic comparison of Microsoft SQL Server time types.

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
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_CMP_Time(dbc_type, ptr_1, ptr_2)
int         dbc_type;
const void *ptr_1;
const void *ptr_2;
{
	return(((dbc_type == SQLDATETIM4) ?
		DBC_MSSQL_CMP_DBDATETIME4(((const DBDATETIM4 *) ptr_1),
		((const DBDATETIM4 *) ptr_2)) : (dbc_type == SQLDATETIME) ?
		DBC_MSSQL_CMP_DBDATETIME(((const DBDATETIME *) ptr_1),
		((const DBDATETIME *) ptr_2)) : 0));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_SCMP_Time(control_ptr, ptr_1, ptr_2, data_length)
void       *control_ptr;
const void *ptr_1;
const void *ptr_2;
size_t      data_length;
{
	return(DBC_MSSQL_CMP_Time(((int) data_length), ptr_1, ptr_2));
}
/*	***********************************************************************	*/

