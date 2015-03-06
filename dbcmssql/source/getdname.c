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

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DBC_MSSQL_GetDBName(spec_string, name_count, name_list, error_text)
const char    *spec_string;
unsigned int  *name_count;
DBC_MSSQL_NAME **name_list;
char          *error_text;
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetDBNames",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code = DBC_MSSQL_GetDBNameBasic(dbc_context_data.dbc_control_ptr,
			name_count, name_list, error_text);
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

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DBC_MSSQL_GetDBNameBasic(dbc_control_ptr, name_count, name_list, error_text)
void          *dbc_control_ptr;
unsigned int  *name_count;
DBC_MSSQL_NAME **name_list;
char          *error_text;
{
	return(DBC_MSSQL_GetNameListBasic(dbc_control_ptr,
		"SELECT name FROM master.dbo.sysdatabases ORDER BY name", name_count,
		name_list, 0, error_text));
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

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DBC_MSSQL_GetUserDBName(spec_string, name_count, name_list, error_text)
const char    *spec_string;
unsigned int  *name_count;
DBC_MSSQL_NAME **name_list;
char          *error_text;
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetUserDBNames",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code =
			DBC_MSSQL_GetUserDBNameBasic(dbc_context_data.dbc_control_ptr,
			name_count, name_list, error_text);
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

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
int DBC_MSSQL_GetUserDBNameBasic(dbc_control_ptr, name_count, name_list,
	error_text)
void          *dbc_control_ptr;
unsigned int  *name_count;
DBC_MSSQL_NAME **name_list;
char          *error_text;
{
	int          return_code;
	unsigned int count_1;

	if ((return_code = DBC_MSSQL_GetDBNameBasic(dbc_control_ptr, name_count,
		name_list, error_text)) == DBC_SUCCESS) {
		for (count_1 = 0; count_1 < *name_count; ) {
			if (DBC_MSSQL_IsSystemDatabase((*name_list)[count_1].name))
				mema_remove(name_count, ((void **) name_list),
					sizeof(**name_list), count_1, 1);
			else
				count_1++;
		}
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
	int           return_code = DBC_SUCCESS;
	unsigned int  name_count  = 0;
	DBC_MSSQL_NAME *name_list   = NULL;
	unsigned int  count_1;
	char          error_text[DBC_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DBC_MSSQL_GetDBName()'\n");
	fprintf(stderr, "---- ------- --- ---------------------\n");

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
	if ((return_code = DBC_MSSQL_GetDBName(argv[1], &name_count, &name_list,
		error_text)) != DBC_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "%u databases found.\n", name_count);
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	for (count_1 = 0; count_1 < name_count; count_1++)
		printf("[%05u]:%s\n", count_1, name_list[count_1].name);
	mema_remove_all(&name_count, ((void **) &name_list));

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Getting user database list --- ");
	if ((return_code = DBC_MSSQL_GetUserDBName(argv[1], &name_count, &name_list,
		error_text)) != DBC_SUCCESS)
		goto EXIT_FUNCTION;
	fprintf(stderr, "%u user databases found.\n", name_count);
	STR_EMIT_CharLine('-', 78, NULL, NULL);
	for (count_1 = 0; count_1 < name_count; count_1++)
		printf("[%05u]:%s\n", count_1, name_list[count_1].name);
	mema_remove_all(&name_count, ((void **) &name_list));

EXIT_FUNCTION:

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

