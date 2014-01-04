/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets information about the indices on a specified
								Microsoft SQL Server table.

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
/*	***********************************************************************	*/

#include <stdio.h>
#include <string.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/*	Prototypes for functions private to this module . . .							*/
/* *********************************************************************** */
COMPAT_FN_DECL_STATIC(int DBC_MSSQL_CMP_DB_IDX,
	(const DBC_MSSQL_DB_IDX *ptr_1, const DBC_MSSQL_DB_IDX *ptr_2));
/* *********************************************************************** */

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
COMPAT_EXTERN_DATA_DEF const MDDL   DBC_MSSQL_GetDBIdxMemberList[] = {
	{
		"index_name",
		STR_sizeof(DBC_MSSQL_DB_IDX, index_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_IDX, index_name),
		offsetof(DBC_MSSQL_DB_IDX, index_name),
		STR_sizeof(DBC_MSSQL_DB_IDX, index_name) - 1,
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
		"index_id",
		STR_sizeof(DBC_MSSQL_DB_IDX, index_id),
		STR_sizeof(DBC_MSSQL_DB_IDX, index_id),
		offsetof(DBC_MSSQL_DB_IDX, index_id),
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
		"key_count",
		STR_sizeof(DBC_MSSQL_DB_IDX, key_count),
		STR_sizeof(DBC_MSSQL_DB_IDX, key_count),
		offsetof(DBC_MSSQL_DB_IDX, key_count),
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
		"column_name",
		STR_sizeof(DBC_MSSQL_DB_IDX, column_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_IDX, column_name),
		offsetof(DBC_MSSQL_DB_IDX, column_name),
		STR_sizeof(DBC_MSSQL_DB_IDX, column_name) - 1,
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
		"column_order",
		STR_sizeof(DBC_MSSQL_DB_IDX, column_order),
		STR_sizeof(DBC_MSSQL_DB_IDX, column_order),
		offsetof(DBC_MSSQL_DB_IDX, column_order),
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
		"column_id",
		STR_sizeof(DBC_MSSQL_DB_IDX, column_id),
		STR_sizeof(DBC_MSSQL_DB_IDX, column_id),
		offsetof(DBC_MSSQL_DB_IDX, column_id),
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
		"status",
		STR_sizeof(DBC_MSSQL_DB_IDX, status),
		STR_sizeof(DBC_MSSQL_DB_IDX, status),
		offsetof(DBC_MSSQL_DB_IDX, status),
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
		"segment_number",
		STR_sizeof(DBC_MSSQL_DB_IDX, segment_number),
		STR_sizeof(DBC_MSSQL_DB_IDX, segment_number),
		offsetof(DBC_MSSQL_DB_IDX, segment_number),
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
		"segment_name",
		STR_sizeof(DBC_MSSQL_DB_IDX, segment_name) - 1,
		STR_sizeof(DBC_MSSQL_DB_IDX, segment_name),
		offsetof(DBC_MSSQL_DB_IDX, segment_name),
		STR_sizeof(DBC_MSSQL_DB_IDX, segment_name) - 1,
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
	}
};
COMPAT_EXTERN_DATA_DEF const unsigned int DBC_MSSQL_GetDBIdxMemberCount  =
	sizeof(DBC_MSSQL_GetDBIdxMemberList) /
	sizeof(DBC_MSSQL_GetDBIdxMemberList[0]);
/* *********************************************************************** */

/* *********************************************************************** */
int DBC_MSSQL_GetDBIndex(spec_string, in_table_name, index_count, index_list,
	error_text)
const char      *spec_string;
const char      *in_table_name;
unsigned int    *index_count;
DBC_MSSQL_DB_IDX **index_list;
char            *error_text;
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetIdxs",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code = DBC_MSSQL_GetDBIndexBasic(dbc_context_data.dbc_control_ptr,
			in_table_name, index_count, index_list, error_text);
		DBC_Close(&dbc_context_data);
	}
	else {
		*index_count = 0;
		*index_list  = NULL;
	}

	return(return_code);
}
/* *********************************************************************** */

/* *********************************************************************** */
int DBC_MSSQL_GetDBIndexBasic(dbc_control_ptr, in_table_name, index_count,
	index_list, error_text)
void            *dbc_control_ptr;
const char      *in_table_name;
unsigned int    *index_count;
DBC_MSSQL_DB_IDX **index_list;
char            *error_text;
{
	int             return_code;
	unsigned int    tmp_index_count = 0;
	DBC_MSSQL_DB_IDX *tmp_index_list  = NULL;
	unsigned int    count_1;
	DBC_FUNCS       dbc_funcs;
	char            database_name[DBC_MSSQL_MAX_DB_NAME_LEN + 1];
	char            owner_name[DBC_MSSQL_MAX_OWN_NAME_LEN + 1];
	char            table_name[DBC_MSSQL_MAX_TBL_NAME_LEN + 1];
	char            sql_command[4096];
	char            tmp_error_text[DBC_MAX_ERROR_TEXT];

	*index_count = 0;
	*index_list  = NULL;

	DBC_AttachFacility(&dbc_funcs);

	if (((return_code = DBC_MSSQL_BreakTableName(in_table_name, database_name,
		owner_name, table_name, tmp_error_text)) == DBC_SUCCESS) &&
		(!(*table_name))) {
		sprintf(tmp_error_text,
			"The table name component is empty in specification '%s'.",
			in_table_name);
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else {
		if (!(*owner_name))
			strcpy(owner_name, "dbo");
		for (count_1 = 0; count_1 < DBC_MSSQL_MAX_IDX_COLS; count_1++) {
			strcpy(sql_command,
				"SELECT D.name,\n");
			strcat(sql_command,
				"\t\t D.indid,\n");
			strcat(sql_command,
				"\t\t D.keycnt,\n");
			strcat(sql_command,
				"\t\t B.name,\n");
			sprintf(sql_command + strlen(sql_command),
				"\t\t %u,\n", count_1 + 1);
			strcat(sql_command,
				"\t\t B.colid,\n");
			strcat(sql_command,
				"\t\t D.status,\n");
			strcat(sql_command,
				"\t\t E.segment,\n");
			strcat(sql_command,
				"\t\t E.name\n");
			sprintf(sql_command + strlen(sql_command),
				"FROM  %s.%s.sysobjects A,\n", database_name, owner_name);
			sprintf(sql_command + strlen(sql_command),
				"\t\t%s.%s.syscolumns   B,\n", database_name, owner_name);
			sprintf(sql_command + strlen(sql_command),
				"\t\t%s.%s.sysusers     C,\n", database_name, owner_name);
			sprintf(sql_command + strlen(sql_command),
				"\t\t%s.%s.sysindexes   D,\n", database_name, owner_name);
			sprintf(sql_command + strlen(sql_command),
				"\t\t%s.%s.syssegments  E\n", database_name, owner_name);
			sprintf(sql_command + strlen(sql_command),
				"WHERE\t(C.name = \"%s\")        AND\n", owner_name);
			strcat(sql_command,
				"\t\t(A.uid = C.uid)         AND\n");
			sprintf(sql_command + strlen(sql_command),
				"\t\t(A.name = \"%s\")      AND\n", table_name);
			strcat(sql_command,
				"\t\t(B.id = A.id)           AND\n");
			strcat(sql_command,
				"\t\t(D.id = A.id)           AND\n");
			strcat(sql_command,
				"\t\t(D.indid > 0)           AND\n");
			strcat(sql_command,
				"\t\t(D.indid < 255)         AND\n");
			strcat(sql_command,
				"\t\t(E.segment = D.segment) AND\n");
			sprintf(sql_command + strlen(sql_command),
				"\t\t(index_col(\"%s.%s.%s\", D.indid, %u) = B.name)\n",
				database_name, owner_name, table_name, count_1 + 1);
			if ((return_code = (*dbc_funcs.get_rows)(dbc_control_ptr,
				DBC_MSSQL_GetDBIdxMemberCount, DBC_MSSQL_GetDBIdxMemberList,
				sql_command, table_name, &tmp_index_count,
				((void **) &tmp_index_list), sizeof(*tmp_index_list),
				sizeof(*tmp_index_list), 0, 0, 1000, tmp_error_text)) !=
				DBC_SUCCESS)
				break;
			if (!tmp_index_count)
				break;
			if (mema_add(tmp_index_count, tmp_index_list, sizeof(**index_list),
				index_count, ((void **) index_list)) != STRFUNCS_SUCCESS) {
				STR_AllocMsgList(*index_count + tmp_index_count,
					sizeof(**index_list), tmp_error_text,
					"Unable to add to the table index list");
				return_code = DBC_MEMORY_FAILURE;
				break;
			}
			free(tmp_index_list);
			tmp_index_list = NULL;
		}
#ifndef NARGS
		qsort(*index_list, *index_count, sizeof(**index_list),
			((int (*)(const void *, const void *)) DBC_MSSQL_CMP_DB_IDX));
#else
		qsort(*index_list, *index_count, sizeof(**index_list),
			DBC_MSSQL_CMP_DB_IDX);
#endif /* #ifndef NARGS */
	}

EXIT_FUNCTION:

	if (tmp_index_list != NULL)
		tmp_index_list = NULL;

	if (return_code != DBC_SUCCESS) {
		sprintf(error_text, "%s '%s.%s.%s' failed: %s",
			"Attempt to get a index definition for the table",
			database_name, owner_name, table_name, tmp_error_text);
		if (*index_list != NULL)
			free(*index_list);
		*index_count = 0;
		*index_list  = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
static int DBC_MSSQL_CMP_DB_IDX(ptr_1, ptr_2)
const DBC_MSSQL_DB_IDX *ptr_1;
const DBC_MSSQL_DB_IDX *ptr_2;
{
	int cmp;

	if (!(cmp = ((ptr_1->index_id > ptr_2->index_id) ? 1 :
		(ptr_1->index_id < ptr_2->index_id) ? -1 : 0)))
		cmp = (ptr_1->column_order > ptr_2->column_order) ? 1 :
			(ptr_1->column_order < ptr_2->column_order) ? -1 : 0;

	return(cmp);
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
	int             return_code = DBC_SUCCESS;
	unsigned int    index_count = 0;
	DBC_MSSQL_DB_IDX *index_list  = NULL;
	unsigned int    count_1;
	char            error_text[DBC_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DBC_MSSQL_GetDBIndex()'\n");
	fprintf(stderr, "---- ------- --- ----------------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H")))
			GEN_DoSimpleUsage(DBC_SUCCESS, argv[0],
				"Help request with '-HELP' noted . . .", UsageString);
	}

	if (argc < 3)
		GEN_DoSimpleUsage(DBC_BAD_ARGS_FAILURE, argv[0],
			"Invalid command line encountered . . .", UsageString);

	DBC_AttachFacility(NULL);

	for (count_1 = 2; count_1 < argc; count_1++) {
		fprintf(stderr, "Table Name  : %s --- ", argv[count_1]);
		if ((return_code = DBC_MSSQL_GetDBIndex(argv[1], argv[count_1],
			&index_count, &index_list, error_text)) != DBC_SUCCESS)
			break;
		fprintf(stderr, "%u indices in table\n", index_count);
		DBC_MSSQL_EMIT_DBIndexListIdx(index_count, index_list, NULL, NULL);
		mema_remove_all(&index_count, ((void **) &index_list));
	}

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

