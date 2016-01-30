/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Retrieves information about the columns which
								comprise a specified table.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
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

#include "dbcsybi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* Prototypes for functions private to this module . . .							*/
/* *********************************************************************** */
COMPAT_FN_DECL_STATIC(int DBC_SYB_LoadTableNames, (void *dbc_control_ptr,
	const char *in_database_name, int user_only_flag, unsigned int *name_count,
	DBC_SYB_NAME **name_list, char *error_text));
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

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetTableName(const char *spec_string, const char *in_database_name,
	unsigned int *name_count, DBC_SYB_NAME **name_list, char *error_text)
#else
int DBC_SYB_GetTableName(spec_string, in_database_name, name_count, name_list,
	error_text)
const char    *spec_string;
const char    *in_database_name;
unsigned int  *name_count;
DBC_SYB_NAME **name_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetTableNames",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code = DBC_SYB_GetTableNameBasic(dbc_context_data.dbc_control_ptr,
			in_database_name, name_count, name_list, error_text);
		DBC_Close(&dbc_context_data);
	}
	else {
		*name_count = 0;
		*name_list  = NULL;
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

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetTableNameBasic(void *dbc_control_ptr,
	const char *in_database_name, unsigned int *name_count,
	DBC_SYB_NAME **name_list, char *error_text)
#else
int DBC_SYB_GetTableNameBasic(dbc_control_ptr, in_database_name, name_count,
	name_list, error_text)
void          *dbc_control_ptr;
const char    *in_database_name;
unsigned int  *name_count;
DBC_SYB_NAME **name_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_LoadTableNames(dbc_control_ptr, in_database_name, DBC_FALSE,
		name_count, name_list, error_text));
}
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

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetUserTableName(const char *spec_string,
	const char *in_database_name, unsigned int *name_count,
	DBC_SYB_NAME **name_list, char *error_text)
#else
int DBC_SYB_GetUserTableName(spec_string, in_database_name, name_count,
	name_list, error_text)
const char    *spec_string;
const char    *in_database_name;
unsigned int  *name_count;
DBC_SYB_NAME **name_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetUserTableNames",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code =
			DBC_SYB_GetUserTableNameBasic(dbc_context_data.dbc_control_ptr,
			in_database_name, name_count, name_list, error_text);
		DBC_Close(&dbc_context_data);
	}
	else {
		*name_count = 0;
		*name_list  = NULL;
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

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetUserTableNameBasic(void *dbc_control_ptr,
	const char *in_database_name, unsigned int *name_count,
	DBC_SYB_NAME **name_list, char *error_text)
#else
int DBC_SYB_GetUserTableNameBasic(dbc_control_ptr, in_database_name,
	name_count, name_list, error_text)
void          *dbc_control_ptr;
const char    *in_database_name;
unsigned int  *name_count;
DBC_SYB_NAME **name_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_LoadTableNames(dbc_control_ptr, in_database_name, DBC_TRUE,
		name_count, name_list, error_text));
}
/*	***********************************************************************	*/

/* *********************************************************************** */
#ifndef NARGS
static int DBC_SYB_LoadTableNames(void *dbc_control_ptr,
	const char *in_database_name, int user_only_flag, unsigned int *name_count,
	DBC_SYB_NAME **name_list, char *error_text)
#else
static int DBC_SYB_LoadTableNames(dbc_control_ptr, in_database_name,
	user_only_flag, name_count, name_list, error_text)
void          *dbc_control_ptr;
const char    *in_database_name;
int            user_only_flag;
unsigned int  *name_count;
DBC_SYB_NAME **name_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int  return_code = DBC_SUCCESS;
	char database_name[DBC_SYB_MAX_DB_NAME_LEN + 1];
	char owner_name[DBC_SYB_MAX_OWN_NAME_LEN + 1];
	char sql_command[1024];

	*name_count = 0;
	*name_list  = NULL;

	if ((return_code = DBC_SYB_BreakDatabaseName(in_database_name,
		database_name, owner_name, error_text)) == DBC_SUCCESS) {
		if (!(*database_name)) {
			sprintf(error_text,
				"The database name component is empty in specification '%s'.",
				in_database_name);
			return_code = DBC_FAILURE;
		}
		else {
			sprintf(sql_command,
				"SELECT name FROM %s.dbo.sysobjects WHERE %s",
				database_name, (user_only_flag) ? "(type = \"U\")" :
				"((type = \"U\") OR (type = \"S\"))");
			if (*owner_name)
				sprintf(sql_command + strlen(sql_command),
		" AND uid IN (SELECT uid FROM %s.dbo.sysusers WHERE (name = \"%s\"))",
					database_name, owner_name);
			strcat(sql_command, " ORDER BY name");
			return_code = DBC_SYB_GetNameListBasic(dbc_control_ptr, sql_command,
				name_count, name_list, 0, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <genfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

static const char *UsageString =
	"<connection-spec> <database-name> [<database-name> . . .]";

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = DBC_SUCCESS;
	unsigned int  name_count  = 0;
	DBC_SYB_NAME *name_list   = NULL;
	unsigned int  count_1;
	unsigned int  count_2;
	char          error_text[DBC_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DBC_SYB_GetTableName()'\n");
	fprintf(stderr, "---- ------- --- ------------------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H")))
			GEN_DoSimpleUsage(DBC_SUCCESS, argv[0],
				"Help request with '-HELP' noted . . .", UsageString);
	}

	if (argc < 3)
		GEN_DoSimpleUsage(DBC_BAD_ARGS_FAILURE, argv[0],
			"Invalid command line encountered . . .", UsageString);

	DBC_AttachFacility(NULL);

	for (count_1 = 2; count_1 < ((unsigned int) argc); count_1++) {
		fprintf(stderr, "Getting table list for database '%s' --- ",
			argv[count_1]);
		if ((return_code = DBC_SYB_GetTableName(argv[1], argv[count_1],
			&name_count, &name_list, error_text)) != DBC_SUCCESS)
			goto EXIT_FUNCTION;
		fprintf(stderr, "%u tables found.\n", name_count);
		for (count_2 = 0; count_2 < name_count; count_2++)
			printf("[%05u]:%s\n", count_2, name_list[count_2].name);
		mema_remove_all(&name_count, ((void **) &name_list));
		STR_EMIT_CharLine('-', 78, NULL, NULL);
	}

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	for (count_1 = 2; count_1 < ((unsigned int) argc); count_1++) {
		fprintf(stderr, "Getting user table list for database '%s' --- ",
			argv[count_1]);
		if ((return_code = DBC_SYB_GetUserTableName(argv[1], argv[count_1],
			&name_count, &name_list, error_text)) != DBC_SUCCESS)
			goto EXIT_FUNCTION;
		fprintf(stderr, "%u user tables found.\n", name_count);
		for (count_2 = 0; count_2 < name_count; count_2++)
			printf("[%05u]:%s\n", count_2, name_list[count_2].name);
		mema_remove_all(&name_count, ((void **) &name_list));
		STR_EMIT_CharLine('-', 78, NULL, NULL);
	}

EXIT_FUNCTION:

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

