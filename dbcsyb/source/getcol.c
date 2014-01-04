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

		Copyright Michael L. Brock 1993 - 2014.
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

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetColumn(const char *spec_string, const char *in_table_name,
	unsigned int *column_count, DBC_SYB_COL **column_list, char *error_text)
#else
int DBC_SYB_GetColumn(spec_string, in_table_name, column_count, column_list,
	error_text)
const char    *spec_string;
const char    *in_table_name;
unsigned int  *column_count;
DBC_SYB_COL  **column_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetCols",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code = DBC_SYB_GetColumnBasic(dbc_context_data.dbc_control_ptr,
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

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

	OUTPUT INDEX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetColumnBasic(void *dbc_control_ptr, const char *in_table_name,
	unsigned int *column_count, DBC_SYB_COL **column_list, char *error_text)
#else
int DBC_SYB_GetColumnBasic(dbc_control_ptr, in_table_name, column_count,
	column_list, error_text)
void          *dbc_control_ptr;
const char    *in_table_name;
unsigned int  *column_count;
DBC_SYB_COL  **column_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int                 return_code     = DBC_SUCCESS;
	unsigned int        db_column_count = 0;
	DBC_SYB_DB_COL     *db_column_list  = NULL;
	unsigned int        count_1;
	char                database_name[DBC_SYB_MAX_DB_NAME_LEN + 1];
	char                owner_name[DBC_SYB_MAX_OWN_NAME_LEN + 1];
	char                table_name[DBC_SYB_MAX_TBL_NAME_LEN + 1];
	const DBC_SYB_TYPE *type_ptr;

	*column_count = 0;
	*column_list  = NULL;

	if (((return_code = DBC_SYB_BreakTableName(in_table_name, database_name,
		owner_name, table_name, error_text)) == DBC_SUCCESS) &&
		(!(*table_name))) {
		sprintf(error_text,
			"The table name component is empty in specification '%s'.",
			in_table_name);
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = DBC_SYB_GetDBColumnBasic(dbc_control_ptr, in_table_name,
		&db_column_count, &db_column_list, error_text)) == DBC_SUCCESS) {
		if ((*column_list = ((DBC_SYB_COL *) calloc(db_column_count,
			sizeof(DBC_SYB_COL)))) == NULL) {
			STR_AllocMsgList(db_column_count, sizeof(DBC_SYB_COL),
				error_text, "%s data base table '%s'",
				"Unable to allocate memory for the column description of the",
				in_table_name);
			return_code = DBC_MEMORY_FAILURE;
		}
		else {
			*column_count = db_column_count;
			for (count_1 = 0; count_1 < *column_count; count_1++) {
				(*column_list)[count_1].column_data       =
					db_column_list[count_1];
				(*column_list)[count_1].type              =
					db_column_list[count_1].basic_type;
				(*column_list)[count_1].vary              =
					(db_column_list[count_1].offset < 0) ? DBC_TRUE :
					DBC_FALSE;
				(*column_list)[count_1].length            =
					db_column_list[count_1].length;
				(*column_list)[count_1].nullable_flag     =
					(db_column_list[count_1].status == 8) ? DBC_TRUE :
					DBC_FALSE;
				(*column_list)[count_1].flag_bit_position =
					(db_column_list[count_1].type != SYBBIT) ? 0 :
					db_column_list[count_1].status;
				nstrcpy((*column_list)[count_1].name,
					db_column_list[count_1].name,
					sizeof((*column_list)[count_1].name) - 1);
				if ((type_ptr =
					DBC_SYB_FIND_TypeByType((*column_list)[count_1].type,
					NULL)) != NULL) {
					(*column_list)[count_1].array_length =
						(*column_list)[count_1].length / type_ptr->type_length;
					(*column_list)[count_1].type_count   =
						(type_ptr->type_count) ? type_ptr->type_count :
						(*column_list)[count_1].array_length;
					nstrcpy((*column_list)[count_1].type_name, type_ptr->name,
						sizeof((*column_list)[count_1].type_name) - 1);
					nstrcpy((*column_list)[count_1].bind_name, type_ptr->bind,
						sizeof((*column_list)[count_1].bind_name) - 1);
					nstrcpy((*column_list)[count_1].type_spec,
						type_ptr->type_spec,
						sizeof((*column_list)[count_1].type_spec) - 1);
				}
				else {
					free(*column_list);
					*column_count = 0;
					*column_list  = NULL;
					sprintf(error_text,
			"%s ('%s.%s.%s') %s %u (named '%s') --- %s %d (named '%s') %s.",
						"Attempt to get a column definition for the table",
						database_name, owner_name, table_name,
						"failed on column number", count_1 + 1,
						db_column_list[count_1].name, "Sybase type id",
						db_column_list[count_1].type,
						db_column_list[count_1].type_name,
						"was not located in the internal library list of types");
					return_code = DBC_FAILURE;
					break;
				}
			}
		}
		free(db_column_list);
		db_column_count = 0;
		db_column_list  = NULL;
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

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code  = DBC_SUCCESS;
	unsigned int  column_count = 0;
	DBC_SYB_COL  *column_list  = NULL;
	unsigned int  count_1;
	char          error_text[DBC_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DBC_SYB_GetColumn()'\n");
	fprintf(stderr, "---- ------- --- ---------------------\n");

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
		fprintf(stderr, "Table Name  : %s --- ", argv[count_1]);
		if ((return_code = DBC_SYB_GetColumn(argv[1], argv[count_1],
			&column_count, &column_list, error_text)) != DBC_SUCCESS)
			break;
		fprintf(stderr, "%u columns in table.\n", column_count);
		DBC_SYB_EMIT_ColumnListIdx(column_count, column_list, NULL, NULL);
		mema_remove_all(&column_count, ((void **) &column_list));
	}

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

