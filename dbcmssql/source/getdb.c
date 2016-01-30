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
#include <string.h>

#include "dbcmssql.h"

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
int DBC_MSSQL_GetDB(spec_string, database_count, database_list, error_text)
const char    *spec_string;
unsigned int  *database_count;
DBC_MSSQL_DB   **database_list;
char          *error_text;
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetDBs",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code = DBC_MSSQL_GetDBBasic(dbc_context_data.dbc_control_ptr,
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

	COPYRIGHT	:	Copyright 1995 - 2016 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DBC_MSSQL_GetDBBasic(dbc_control_ptr, database_count, database_list,
	error_text)
void          *dbc_control_ptr;
unsigned int  *database_count;
DBC_MSSQL_DB   **database_list;
char          *error_text;
{
	int            return_code       = DBC_SUCCESS;
	unsigned int   db_database_count = 0;
	DBC_MSSQL_DB_DB *db_database_list  = NULL;
	unsigned int   count_1;

	*database_count = 0;
	*database_list  = NULL;

	if ((return_code = DBC_MSSQL_GetDBDBBasic(dbc_control_ptr,
		&db_database_count, &db_database_list, error_text)) == DBC_SUCCESS) {
		if ((*database_list = ((DBC_MSSQL_DB *) calloc(db_database_count,
			sizeof(DBC_MSSQL_DB)))) == NULL) {
			STR_AllocMsgList(db_database_count, sizeof(DBC_MSSQL_DB),
				error_text, "Unable to allocate memory for the database list");
			return_code = DBC_MEMORY_FAILURE;
		}
		else {
			*database_count = db_database_count;
			for (count_1 = 0; count_1 < db_database_count; count_1++) {
				nstrcpy((*database_list)[count_1].name,
					db_database_list[count_1].name,
					sizeof((*database_list)[count_1].name) - 1);
				(*database_list)[count_1].id                  =
					db_database_list[count_1].dbid;
				(*database_list)[count_1].user_id             =
					db_database_list[count_1].suid;
/*
	The 'mode' column is not in 'master.dbo.sysdatabases' in System 10.
				(*database_list)[count_1].mode                =
					db_database_list[count_1].mode;
*/
				(*database_list)[count_1].status              =
					db_database_list[count_1].status;
				(*database_list)[count_1].version             =
					db_database_list[count_1].version;
				(*database_list)[count_1].log_ptr         =
					db_database_list[count_1].logptr;
				(*database_list)[count_1].creation_date                =
					db_database_list[count_1].crdate;
				(*database_list)[count_1].dumptr_date   =
					db_database_list[count_1].dumptrdate;
				(*database_list)[count_1].select_into_flag             =
					(db_database_list[count_1].status & 0X0004) ?
					DBC_TRUE : DBC_FALSE;
				(*database_list)[count_1].truncate_on_chkpoint_flag    =
					(db_database_list[count_1].status & 0X0008) ?
					DBC_TRUE : DBC_FALSE;
				(*database_list)[count_1].no_chkpoint_on_recovery_flag =
					(db_database_list[count_1].status & 0X0010) ?
					DBC_TRUE : DBC_FALSE;
				(*database_list)[count_1].crashed_while_loading_flag   =
					(db_database_list[count_1].status & 0X0020) ?
					DBC_TRUE : DBC_FALSE;
				(*database_list)[count_1].suspect_flag                 =
					(db_database_list[count_1].status & 0X0100) ?
					DBC_TRUE : DBC_FALSE;
				(*database_list)[count_1].read_only_flag               =
					(db_database_list[count_1].status & 0X0400) ?
					DBC_TRUE : DBC_FALSE;
				(*database_list)[count_1].owner_only_flag              =
					(db_database_list[count_1].status & 0X0800) ?
					DBC_TRUE : DBC_FALSE;
				(*database_list)[count_1].single_user_flag             =
					(db_database_list[count_1].status & 0X1000) ?
					DBC_TRUE : DBC_FALSE;
				(*database_list)[count_1].name_changed_flag            =
					(db_database_list[count_1].status & 0X4000) ?
					DBC_TRUE : DBC_FALSE;
			}
		}
		if (db_database_list != NULL)
			free(db_database_list);
	}

	return(return_code);
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
	int           return_code  = DBC_SUCCESS;
	unsigned int  database_count = 0;
	DBC_MSSQL_DB   *database_list  = NULL;
	unsigned int  count_1;
	char          error_text[DBC_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DBC_MSSQL_GetDB()'\n");
	fprintf(stderr, "---- ------- --- -----------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	for (count_1 = 1; count_1 < argc; count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H")))
			GEN_DoSimpleUsage(DBC_SUCCESS, argv[0],
				"Help request with '-HELP' noted . . .", UsageString);
	}

	if (argc != 2)
		GEN_DoSimpleUsage(DBC_BAD_ARGS_FAILURE, argv[0],
			"Invalid command line encountered . . .", UsageString);

	DBC_AttachFacility(NULL);

	fprintf(stderr, "Getting database list --- ");
	if ((return_code = DBC_MSSQL_GetDB(argv[1], &database_count,
		&database_list, error_text)) == DBC_SUCCESS) {
		fprintf(stderr, "%u databases found.\n", database_count);
		DBC_MSSQL_EMIT_DBListIdx(database_count, database_list, NULL, NULL);
		mema_remove_all(&database_count, ((void **) &database_list));
	}

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

