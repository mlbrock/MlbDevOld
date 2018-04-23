/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Retrieves information about the columns which
								comprise a specified table.

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

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_DefaultDatabaseName(in_name, default_database_name,
	default_owner_name, out_database_name, out_owner_name, error_text)
const char *in_name;
const char *default_database_name;
const char *default_owner_name;
char       *out_database_name;
char       *out_owner_name;
char       *error_text;
{
	int return_code;

	if ((return_code = DBC_MSSQL_BreakDatabaseName(in_name, out_database_name,
		out_owner_name, error_text)) == DBC_SUCCESS) {
		if ((out_database_name == '\0') && (default_database_name != NULL))
			nstrcpy(out_database_name, default_database_name,
				DBC_MSSQL_MAX_DB_NAME_LEN);
		if ((out_owner_name == '\0') && (default_owner_name != NULL))
			nstrcpy(out_owner_name, default_owner_name,
				DBC_MSSQL_MAX_OWN_NAME_LEN);
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
int DBC_MSSQL_DefaultTableName(in_name, default_database_name,
	default_owner_name, out_database_name, out_owner_name, out_table_name,
	error_text)
const char *in_name;
const char *default_database_name;
const char *default_owner_name;
char       *out_database_name;
char       *out_owner_name;
char       *out_table_name;
char       *error_text;
{
	int return_code;

	if ((return_code = DBC_MSSQL_BreakTableName(in_name, out_database_name,
		out_owner_name, out_table_name, error_text)) == DBC_SUCCESS) {
		if ((out_database_name == '\0') && (default_database_name != NULL))
			nstrcpy(out_database_name, default_database_name,
				DBC_MSSQL_MAX_DB_NAME_LEN);
		if ((out_owner_name == '\0') && (default_owner_name != NULL))
			nstrcpy(out_owner_name, default_owner_name,
				DBC_MSSQL_MAX_OWN_NAME_LEN);
	}

	return(return_code);
}
/*	***********************************************************************	*/

