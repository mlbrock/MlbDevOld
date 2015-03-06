/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Miscellaneous Microsoft SQL Server date type functions.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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
int DBC_MSSQL_IsDate(dbc_type)
int dbc_type;
{
	return(((dbc_type == SQLDATETIM4) || (dbc_type == SQLDATETIME)) ?
		DBC_TRUE : DBC_FALSE);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_MinDate(dbc_type, dtime_ptr, error_text)
int    dbc_type;
DTIME *dtime_ptr;
char  *error_text;
{
	int  return_code = DBC_SUCCESS;
	char dat_error_text[DATFUNCS_MAX_ERROR_TEXT];

	switch (dbc_type) {
		case SQLDATETIM4	:
			if ((return_code = DTIME_YYYYMMDDhhmmsslllToDate(1900, 1, 1, 0, 0, 0,
				0, dtime_ptr, dat_error_text)) != DATFUNCS_SUCCESS) {
				nstrcpy(error_text, dat_error_text, DBC_MAX_ERROR_TEXT - 1);
				return_code = DBC_MAP_ERROR_DAT_TO_DBC(return_code);
			}
			break;
		case SQLDATETIME	:
			if ((return_code = DTIME_YYYYMMDDhhmmsslllToDate(1753, 1, 1, 0, 0, 0,
				0, dtime_ptr, dat_error_text)) != DATFUNCS_SUCCESS) {
				nstrcpy(error_text, dat_error_text, DBC_MAX_ERROR_TEXT - 1);
				return_code = DBC_MAP_ERROR_DAT_TO_DBC(return_code);
			}
			break;
		default				:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the DBC date 'minimum' function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_MaxDate(dbc_type, dtime_ptr, error_text)
int    dbc_type;
DTIME *dtime_ptr;
char  *error_text;
{
	int  return_code = DBC_SUCCESS;
	char dat_error_text[DATFUNCS_MAX_ERROR_TEXT];

	switch (dbc_type) {
		case SQLDATETIM4	:
			if ((return_code = DTIME_YYYYMMDDhhmmsslllToDate(2079, 6, 6, 23,
				59, 59, 999, dtime_ptr, dat_error_text)) != DATFUNCS_SUCCESS) {
				nstrcpy(error_text, dat_error_text, DBC_MAX_ERROR_TEXT - 1);
				return_code = DBC_MAP_ERROR_DAT_TO_DBC(return_code);
			}
			break;
		case SQLDATETIME	:
			if ((return_code = DTIME_YYYYMMDDhhmmsslllToDate(9999, 12, 31, 23,
				59, 59, 999, dtime_ptr, dat_error_text)) != DATFUNCS_SUCCESS) {
				nstrcpy(error_text, dat_error_text, DBC_MAX_ERROR_TEXT - 1);
				return_code = DBC_MAP_ERROR_DAT_TO_DBC(return_code);
			}
			break;
		default				:
			sprintf(error_text, "Invalid DBC type (%d) %s.", dbc_type,
				"was passed to the DBC date 'maximum' function");
			return_code = DBC_BAD_TYPE_FAILURE;
			break;
	}

	return(return_code);
}
/*	***********************************************************************	*/

