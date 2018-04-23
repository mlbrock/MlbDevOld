/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Miscellaneous Microsoft SQL Server numeric type
								functions.

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

#include <float.h>
#include <limits.h>
#include <stdio.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_IsNumber(dbc_type)
int dbc_type;
{
	return(((dbc_type == SQLINT1) || (dbc_type == SQLINT2) ||
		(dbc_type == SQLINT4) || (dbc_type == SQLFLT4) ||
		(dbc_type == SQLFLT8) || (dbc_type == SQLMONEY4) ||
		(dbc_type == SQLMONEY)) ? DBC_TRUE : DBC_FALSE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_MinNumber(dbc_type, double_ptr, error_text)
int     dbc_type;
double *double_ptr;
char   *error_text;
{
	int return_code = DBC_SUCCESS;

	switch (dbc_type) {
		case SQLINT1	:
			*double_ptr = ((double) 0.0);
			break;
		case SQLINT2	:
			*double_ptr = ((double) SHRT_MIN);
			break;
		case SQLINT4	:
			*double_ptr = ((double) LONG_MIN);
			break;
		case SQLFLT4	:
			*double_ptr = ((double) FLT_MIN);
			break;
		case SQLFLT8	:
			*double_ptr = DBL_MIN;
			break;
		case SQLMONEY4	:
			*double_ptr = ((double) LONG_MIN) / 10000.0;
			break;
		case SQLMONEY	:
			*double_ptr = 922337203685477.5807;
			break;
		default			:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the DBC number 'mininum' function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_MaxNumber(dbc_type, double_ptr, error_text)
int     dbc_type;
double *double_ptr;
char   *error_text;
{
	int return_code = DBC_SUCCESS;

	switch (dbc_type) {
		case SQLINT1	:
			*double_ptr = ((double) UCHAR_MAX);
			break;
		case SQLINT2	:
			*double_ptr = ((double) SHRT_MAX);
			break;
		case SQLINT4	:
			*double_ptr = ((double) LONG_MAX);
			break;
		case SQLFLT4	:
			*double_ptr = ((double) FLT_MAX);
			break;
		case SQLFLT8	:
			*double_ptr = DBL_MAX;
			break;
		case SQLMONEY4	:
			*double_ptr = ((double) LONG_MAX) / 10000.0;
			break;
		case SQLMONEY	:
			*double_ptr = 922337203685477.5808;
			break;
		default			:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the DBC number 'maxinum' function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

