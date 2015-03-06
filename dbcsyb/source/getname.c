/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets a DBNAME datum from Sybase.

	Revision History	:	1994-06-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Required include files . . .                                           	*/
/*	***********************************************************************	*/

#include <memory.h>

#include "dbcsybi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const MDDL   DBC_SYB_GetNameMemberList[] = {
	{
		"name",
		STR_sizeof(DBC_SYB_NAME, name) - 1,
		STR_sizeof(DBC_SYB_NAME, name),
		offsetof(DBC_SYB_NAME, name),
		STR_sizeof(DBC_SYB_NAME, name) - 1,
		"c",
		0,
		MDDL_DTA_EMPTY_LIST,
		0,
		NULL,
		SYBCHAR,
		DBC_SYB_SetDisplayLength,
		DBC_SYB_DumpField,
		0,
		0,
		NULL,
		NULL
	}
};
COMPAT_EXTERN_DATA_DEF const unsigned int DBC_SYB_GetNameMemberCount  =
	sizeof(DBC_SYB_GetNameMemberList) /
	sizeof(DBC_SYB_GetNameMemberList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
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

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetName(const char *spec_string, const char *sql_command,
	unsigned int *name_count, DBC_SYB_NAME *name_ptr, char *error_text)
#else
int DBC_SYB_GetName(spec_string, sql_command, name_count, name_ptr,
	error_text)
const char   *spec_string;
const char   *sql_command;
unsigned int *name_count;
DBC_SYB_NAME *name_ptr;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetName",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code = DBC_SYB_GetNameBasic(dbc_context_data.dbc_control_ptr,
			sql_command, name_count, name_ptr, error_text);
		DBC_Close(&dbc_context_data);
	}
	else {
		*name_count = 0;
		memset(name_ptr, '\0', sizeof(*name_ptr));
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
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

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetNameBasic(void *dbc_control_ptr, const char *sql_command,
	unsigned int *name_count, DBC_SYB_NAME *name_ptr, char *error_text)
#else
int DBC_SYB_GetNameBasic(dbc_control_ptr, sql_command, name_count, name_ptr,
	error_text)
void         *dbc_control_ptr;
const char   *sql_command;
unsigned int *name_count;
DBC_SYB_NAME *name_ptr;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code;
	DBC_SYB_NAME *name_list;

	memset(name_ptr, '\0', sizeof(*name_ptr));

	if ((return_code = DBC_SYB_GetNameListBasic(dbc_control_ptr,
		sql_command, name_count, &name_list, 1, error_text)) ==
		DBC_SUCCESS) {
		if (*name_count) {
			*name_ptr = *name_list;
			free(name_list);
		}
	}

	return(return_code);
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

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetNameList(const char *spec_string, const char *sql_command,
	unsigned int *name_count, DBC_SYB_NAME **name_list,
	unsigned int max_row_count, char *error_text)
#else
int DBC_SYB_GetNameList(spec_string, sql_command, name_count, name_list,
	max_row_count, error_text)
const char    *spec_string;
const char    *sql_command;
unsigned int  *name_count;
DBC_SYB_NAME **name_list;
unsigned int   max_row_count;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetNameList",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code = DBC_SYB_GetNameListBasic(dbc_context_data.dbc_control_ptr,
			sql_command, name_count, name_list, max_row_count, error_text);
		DBC_Close(&dbc_context_data);
	}
	else {
		*name_count = 0;
		*name_list  = NULL;
	}

	return(return_code);
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

	COPYRIGHT	:	Copyright 1994 - 2015 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetNameListBasic(void *dbc_control_ptr, const char *sql_command,
	unsigned int *name_count, DBC_SYB_NAME **name_list,
	unsigned int max_row_count, char *error_text)
#else
int DBC_SYB_GetNameListBasic(dbc_control_ptr, sql_command, name_count,
	name_list, max_row_count, error_text)
void          *dbc_control_ptr;
const char    *sql_command;
unsigned int  *name_count;
DBC_SYB_NAME **name_list;
unsigned int   max_row_count;
char          *error_text;
#endif /* #ifndef NARGS */
{
	DBC_FUNCS dbc_funcs;

	DBC_AttachFacility(&dbc_funcs);

	return((*dbc_funcs.get_rows)(dbc_control_ptr, DBC_SYB_GetNameMemberCount,
		DBC_SYB_GetNameMemberList, sql_command, NULL, name_count,
		((void **) name_list), sizeof(**name_list), sizeof(**name_list), 0,
		max_row_count, 1000, error_text));
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <genfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

static const char *UsageString = "<connection-spec>";

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = DBC_SUCCESS;
	unsigned int  row_count   = 0;
	DBC_SYB_NAME *row_list    = NULL;
	unsigned int  count_1;
	char          error_text[DBC_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DBC_SYB_GetNameList()'\n");
	fprintf(stderr, "---- ------- --- -----------------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H")))
			GEN_DoSimpleUsage(DBC_SUCCESS, argv[0],
				"Help request with '-HELP' noted . . .", UsageString);
	}

	if (argc < 3)
		GEN_DoSimpleUsage(DBC_FAILURE, argv[0],
			"Invalid command line encountered . . .", UsageString);

	DBC_AttachFacility(NULL);

	if ((return_code = DBC_SYB_GetNameList(argv[1],
		"SELECT name FROM sysobjects WHERE (type = \"U\") ORDER BY name",
		&row_count, &row_list, 0, error_text)) == DBC_SUCCESS) {
		for (count_1 = 0; count_1 < row_count; count_1++)
			printf("[%05u]:%s\n", count_1, row_list[count_1].name);
		if (row_list != NULL)
			free(row_list);
	}

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

