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
#include <stdlib.h>
#include <string.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const MDDL   DBC_MSSQL_GetDBColMemberList[] = {
	{
		"type",
		STR_sizeof(DBC_MSSQL_DB_COL, type),
		STR_sizeof(DBC_MSSQL_DB_COL, type),
		offsetof(DBC_MSSQL_DB_COL, type),
		1,
		"C",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLINT1,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	},
	{
		"table_type",
		STR_sizeof(DBC_MSSQL_DB_COL, table_type),
		STR_sizeof(DBC_MSSQL_DB_COL, table_type),
		offsetof(DBC_MSSQL_DB_COL, table_type),
		1,
		"C",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLINT1,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	},
	{
		"user_type",
		STR_sizeof(DBC_MSSQL_DB_COL, user_type),
		STR_sizeof(DBC_MSSQL_DB_COL, user_type),
		offsetof(DBC_MSSQL_DB_COL, user_type),
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
		"name",
		STR_sizeof(DBC_MSSQL_DB_COL, name) - 1,
		STR_sizeof(DBC_MSSQL_DB_COL, name),
		offsetof(DBC_MSSQL_DB_COL, name),
		STR_sizeof(DBC_MSSQL_DB_COL, name) - 1,
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
		"length",
		STR_sizeof(DBC_MSSQL_DB_COL, length),
		STR_sizeof(DBC_MSSQL_DB_COL, length),
		offsetof(DBC_MSSQL_DB_COL, length),
		1,
		"C",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLINT1,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	},
	{
		"type_name",
		STR_sizeof(DBC_MSSQL_DB_COL, type_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_COL, type_name),
		offsetof(DBC_MSSQL_DB_COL, type_name),
		STR_sizeof(DBC_MSSQL_DB_COL, type_name) - 1,
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
		"offset",
		STR_sizeof(DBC_MSSQL_DB_COL, offset),
		STR_sizeof(DBC_MSSQL_DB_COL, offset),
		offsetof(DBC_MSSQL_DB_COL, offset),
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
		"default_name",
		STR_sizeof(DBC_MSSQL_DB_COL, default_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_COL, default_name),
		offsetof(DBC_MSSQL_DB_COL, default_name),
		STR_sizeof(DBC_MSSQL_DB_COL, default_name) - 1,
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
		"rule_name",
		STR_sizeof(DBC_MSSQL_DB_COL, rule_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_COL, rule_name),
		offsetof(DBC_MSSQL_DB_COL, rule_name),
		STR_sizeof(DBC_MSSQL_DB_COL, rule_name) - 1,
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
		"status",
		STR_sizeof(DBC_MSSQL_DB_COL, status),
		STR_sizeof(DBC_MSSQL_DB_COL, status),
		offsetof(DBC_MSSQL_DB_COL, status),
		1,
		"C",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SQLINT1,
		DBC_MSSQL_SetDisplayLength,
		DBC_MSSQL_DumpField,
		0,
		0,
		NULL,
		NULL
	}
	/*
		NOTE: Member 'basic_type' should not be loaded from the DBMS.
	*/
};
COMPAT_EXTERN_DATA_DEF const unsigned int DBC_MSSQL_GetDBColMemberCount  =
	sizeof(DBC_MSSQL_GetDBColMemberList) /
	sizeof(DBC_MSSQL_GetDBColMemberList[0]);
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

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DBC_MSSQL_GetDBColumn(spec_string, in_table_name, column_count, column_list,
	error_text)
const char      *spec_string;
const char      *in_table_name;
unsigned int    *column_count;
DBC_MSSQL_DB_COL **column_list;
char            *error_text;
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetDBCols",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code = DBC_MSSQL_GetDBColumnBasic(dbc_context_data.dbc_control_ptr,
			in_table_name, column_count, column_list, error_text);
		DBC_Close(&dbc_context_data);
	}
	else {
		*column_count = 0;
		*column_list  = NULL;
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

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DBC_MSSQL_GetDBColumnBasic(dbc_control_ptr, in_table_name, column_count,
	column_list, error_text)
void            *dbc_control_ptr;
const char      *in_table_name;
unsigned int    *column_count;
DBC_MSSQL_DB_COL **column_list;
char            *error_text;
{
	int          return_code = DBC_SUCCESS;
	unsigned int count_1;
	DBC_FUNCS    dbc_funcs;
	char         database_name[DBC_MSSQL_MAX_DB_NAME_LEN + 1];
	char         owner_name[DBC_MSSQL_MAX_OWN_NAME_LEN + 1];
	char         table_name[DBC_MSSQL_MAX_TBL_NAME_LEN + 1];
	char         sql_command[4096];

	*column_count = 0;
	*column_list  = NULL;

	DBC_AttachFacility(&dbc_funcs);

	if (((return_code = DBC_MSSQL_BreakTableName(in_table_name, database_name,
		owner_name, table_name, error_text)) == DBC_SUCCESS) &&
		(!(*table_name))) {
		sprintf(error_text,
			"The table name component is empty in specification '%s'.",
			in_table_name);
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (!(*owner_name))
		strcpy(owner_name, "dbo");

	strcat(strcat(strcpy(sql_command,
		"SELECT D.type, B.type, B.usertype, B.name, B.length, D.name, "),
		"B.offset, object_name(B.cdefault), object_name(B.domain), "),
		"B.status ");
	sprintf(sql_command + strlen(sql_command),
		"FROM %s.dbo.%s A, %s.dbo.%s B, %s.dbo.%s C, %s.dbo.%s D ",
		database_name, "sysobjects", database_name, "syscolumns",
		database_name, "sysusers",   database_name, "systypes");
	sprintf(sql_command + strlen(sql_command),
		"WHERE (C.name = \"%s\") AND (A.uid = C.uid) AND ", owner_name);
	sprintf(sql_command + strlen(sql_command),
		"(A.name = \"%s\") AND ", table_name);
	sprintf(sql_command + strlen(sql_command),
		"((A.type = \"U\") OR (A.type = \"S\")) AND ");
	sprintf(sql_command + strlen(sql_command),
		"(B.id = A.id) AND (D.usertype = B.usertype) ORDER BY colid");

	if ((return_code = (*dbc_funcs.get_rows)(dbc_control_ptr,
		DBC_MSSQL_GetDBColMemberCount, DBC_MSSQL_GetDBColMemberList, sql_command,
		table_name, column_count, ((void **) column_list),
		sizeof(**column_list), sizeof(**column_list), 0, 0, 1000,
		error_text)) == DBC_SUCCESS) {
		if (!(*column_count)) {
			sprintf(error_text, "%s ('%s.%s.%s') failed --- %s.",
				"Attempt to get a column definition for the table",
				database_name, owner_name, table_name,
				"no columns for that table were located");
			return_code = DBC_FAILURE;
		}
		else {
			for (count_1 = 0; count_1 < *column_count; count_1++)
				(*column_list)[count_1].basic_type =
					((*column_list)[count_1].type == SQLVARCHAR)   ?
					SQLCHAR     :
					((*column_list)[count_1].type == SQLVARBINARY) ?
					SQLBINARY   :
					((*column_list)[count_1].type == SQLDATETIMN)  ?
					SQLDATETIME :
					((*column_list)[count_1].type == SQLMONEYN)    ?
					SQLMONEY    :
					((*column_list)[count_1].type == SQLFLTN)      ?
					SQLFLT8     :
					(((*column_list)[count_1].type == SQLINTN) &&
					 ((*column_list)[count_1].length == 1))        ?
					SQLINT1     :
					(((*column_list)[count_1].type == SQLINTN) &&
					 ((*column_list)[count_1].length == 2))        ?
					SQLINT2     :
					(((*column_list)[count_1].type == SQLINTN) &&
					 ((*column_list)[count_1].length == 4))        ?
					SQLINT4     : (*column_list)[count_1].type;
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <memory.h>

#include <genfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

static const char *UsageString =
	"<connection-spec> <table-name> [<table-name> . . .]";

int main(argc, argv)
int    argc;
char **argv;
{
	int             return_code  = DBC_SUCCESS;
	unsigned int    column_count = 0;
	DBC_MSSQL_DB_COL *column_list  = NULL;
	unsigned int    count_1;
	char            error_text[DBC_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DBC_MSSQL_GetDBColumn()'\n");
	fprintf(stderr, "---- ------- --- -----------------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H")))
			GEN_DoSimpleUsage(DBC_SUCCESS, argv[0],
				"Help request with '-HELP' noted . . .", UsageString);
	}

	if (argc < 3)
		GEN_DoSimpleUsage(DBC_FAILURE, argv[0],
			"Invalid command line encountered . . .", UsageString);

	DBC_AttachFacility(NULL);

	for (count_1 = 2; count_1 < argc; count_1++) {
		fprintf(stderr, "Table Name  : %s --- ", argv[count_1]);
		if ((return_code = DBC_MSSQL_GetDBColumn(argv[1], argv[count_1],
			&column_count, &column_list, error_text)) != DBC_SUCCESS)
			break;
		fprintf(stderr, "%u columns in table.\n", column_count);
		DBC_MSSQL_EMIT_DBColumnListIdx(column_count, column_list, NULL, NULL);
		mema_remove_all(&column_count, ((void **) &column_list));
	}

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

