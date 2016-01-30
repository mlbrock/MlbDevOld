/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts a 'double' to a Microsoft SQL Server numeric
								type.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
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
int DBC_MSSQL_DoubleToNumber(dbc_type, double_value, number_ptr, error_text)
int     dbc_type;
double  double_value;
void   *number_ptr;
char   *error_text;
{
	int return_code = DBC_SUCCESS;

	switch (dbc_type) {
		case SQLINT1	:
			*((unsigned char *) number_ptr) = ((unsigned char) double_value);
			break;
		case SQLINT2	:
			*((short *) number_ptr) = ((short) double_value);
			break;
		case SQLINT4	:
			*((long *) number_ptr) = ((long) double_value);
			break;
		case SQLFLT4	:
			*((float *) number_ptr) = ((float) double_value);
			break;
		case SQLFLT8	:
			*((double *) number_ptr) = double_value;
			break;
		case SQLMONEY4	:
			DBC_MSSQL_DoubleToDBMONEY4(double_value, ((DBMONEY4 *) number_ptr));
			break;
		case SQLMONEY	:
			DBC_MSSQL_DoubleToDBMONEY(double_value, ((DBMONEY *) number_ptr));
			break;
		default			:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the double-to-DBC-number conversion function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

