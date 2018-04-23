/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
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

#include <stdio.h>
#include <string.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const MDDL   DBC_MSSQL_GetDBDBMemberList[] = {
	{
		"name",
		STR_sizeof(DBC_MSSQL_DB_DB, name) - 1,
		STR_sizeof(DBC_MSSQL_DB_DB, name),
		offsetof(DBC_MSSQL_DB_DB, name),
		STR_sizeof(DBC_MSSQL_DB_DB, name) - 1,
		"c",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLCHAR,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	},
	{
		"dbid",
		STR_sizeof(DBC_MSSQL_DB_DB, dbid),
		STR_sizeof(DBC_MSSQL_DB_DB, dbid),
		offsetof(DBC_MSSQL_DB_DB, dbid),
		1,
		"s",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLINT2,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	},
	{
		"suid",
		STR_sizeof(DBC_MSSQL_DB_DB, suid),
		STR_sizeof(DBC_MSSQL_DB_DB, suid),
		offsetof(DBC_MSSQL_DB_DB, suid),
		1,
		"s",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLINT2,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	},
/*
	The 'mode' column is not in 'master.dbo.sysdatabases' in System 10.
	{
		"mode",
		STR_sizeof(DBC_MSSQL_DB_DB, mode),
		STR_sizeof(DBC_MSSQL_DB_DB, mode),
		offsetof(DBC_MSSQL_DB_DB, mode),
		1,
		"s",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLINT2,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	},
*/
	{
		"status",
		STR_sizeof(DBC_MSSQL_DB_DB, status),
		STR_sizeof(DBC_MSSQL_DB_DB, status),
		offsetof(DBC_MSSQL_DB_DB, status),
		1,
		"s",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLINT2,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	},
	{
		"version",
		STR_sizeof(DBC_MSSQL_DB_DB, version),
		STR_sizeof(DBC_MSSQL_DB_DB, version),
		offsetof(DBC_MSSQL_DB_DB, version),
		1,
		"s",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLINT2,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	},
	{
		"logptr",
		STR_sizeof(DBC_MSSQL_DB_DB, logptr),
		STR_sizeof(DBC_MSSQL_DB_DB, logptr),
		offsetof(DBC_MSSQL_DB_DB, logptr),
		1,
		"l",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLINT4,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	},
	{
		"crdate",
		STR_sizeof(DBC_MSSQL_DB_DB, crdate),
		STR_sizeof(DBC_MSSQL_DB_DB, crdate),
		offsetof(DBC_MSSQL_DB_DB, crdate),
		1,
		"l,l",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLDATETIME,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	},
	{
		"dumptrdate",
		STR_sizeof(DBC_MSSQL_DB_DB, dumptrdate),
		STR_sizeof(DBC_MSSQL_DB_DB, dumptrdate),
		offsetof(DBC_MSSQL_DB_DB, dumptrdate),
		1,
		"l,l",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLDATETIME,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	}
};
COMPAT_EXTERN_DATA_DEF const unsigned int DBC_MSSQL_GetDBDBMemberCount  =
	sizeof(DBC_MSSQL_GetDBDBMemberList) /
	sizeof(DBC_MSSQL_GetDBDBMemberList[0]);
/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DBC_MSSQL_GetDBDB(spec_string, database_count, database_list, error_text)
const char     *spec_string;
unsigned int   *database_count;
DBC_MSSQL_DB_DB **database_list;
char           *error_text;
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetDBDBs",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code = DBC_MSSQL_GetDBDBBasic(dbc_context_data.dbc_control_ptr,
			database_count, database_list, error_text);
		DBC_Close(&dbc_context_data);
	}
	else {
		*database_count = 0;
		*database_list  = NULL;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* BOH

	NAME			:	

	SYNOPSIS		:	

	DESCRIPTION	:	

	PARAMETERS	:	

	RETURNS		:	

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DBC_MSSQL_GetDBDBBasic(dbc_control_ptr, database_count, database_list,
	error_text)
void           *dbc_control_ptr;
unsigned int   *database_count;
DBC_MSSQL_DB_DB **database_list;
char           *error_text;
{
	DBC_FUNCS dbc_funcs;
	char      sql_command[4096];

	*database_count = 0;
	*database_list  = NULL;

	DBC_AttachFacility(&dbc_funcs);

	strcat(strcat(strcat(strcat(strcpy(sql_command, "SELECT "),
/*
	The 'mode' column is not in 'master.dbo.sysdatabases' in System 10.
		"name, dbid, suid, mode, status, version, logptr, crdate, dumptrdate "),
*/
		"name, dbid, suid, status, version, logptr, crdate, dumptrdate "),
		"FROM "), "master.dbo.sysdatabases "), "ORDER BY name");

	return((*dbc_funcs.get_rows)(dbc_control_ptr, DBC_MSSQL_GetDBDBMemberCount,
		DBC_MSSQL_GetDBDBMemberList, sql_command, NULL, database_count,
		((void **) database_list), sizeof(**database_list),
		sizeof(**database_list), 0, 0, 1000, error_text));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <memory.h>

#include <genfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

static const char *UsageString = "<connection-spec>";

int main(argc, argv)
int    argc;
char **argv;
{
	int            return_code  = DBC_SUCCESS;
	unsigned int   database_count = 0;
	DBC_MSSQL_DB_DB *database_list  = NULL;
	unsigned int   count_1;
	char           error_text[DBC_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DBC_MSSQL_GetDBDB()'\n");
	fprintf(stderr, "---- ------- --- -------------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H")))
			GEN_DoSimpleUsage(DBC_SUCCESS, argv[0],
				"Help request with '-HELP' noted . . .", UsageString);
	}

	if (argc != 2)
		GEN_DoSimpleUsage(DBC_FAILURE, argv[0],
			"Invalid command line encountered . . .", UsageString);

	DBC_AttachFacility(NULL);

	fprintf(stderr, "Getting database list --- ");
	if ((return_code = DBC_MSSQL_GetDBDB(argv[1], &database_count,
		&database_list, error_text)) == DBC_SUCCESS) {
		fprintf(stderr, "%u databases found.\n", database_count);
		DBC_MSSQL_EMIT_DBDBListIdx(database_count, database_list, NULL, NULL);
		mema_remove_all(&database_count, ((void **) &database_list));
	}

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

