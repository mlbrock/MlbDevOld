/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets information about the indices on a specified
								Sybase table.

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

#include <memory.h>
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

	COPYRIGHT	:	Copyright 1995 - 2018 Michael L. Brock

	OUTPUT IDX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetIndex(const char *spec_string, const char *in_table_name,
	unsigned int *index_count, DBC_SYB_IDX **index_list, char *error_text)
#else
int DBC_SYB_GetIndex(spec_string, in_table_name, index_count, index_list,
	error_text)
const char    *spec_string;
const char    *in_table_name;
unsigned int  *index_count;
DBC_SYB_IDX  **index_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int         return_code;
	DBC_CONTEXT dbc_context_data;

	if ((return_code = DBC_Open(&dbc_context_data, NULL, "DBC:GetIdxs",
		spec_string, NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		return_code = DBC_SYB_GetIndexBasic(dbc_context_data.dbc_control_ptr,
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

	OUTPUT IDX:	

	PUBLISH XREF:	

	PUBLISH NAME:	

EOH */
/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_GetIndexBasic(void *dbc_control_ptr, const char *in_table_name,
	unsigned int *index_count, DBC_SYB_IDX **index_list, char *error_text)
#else
int DBC_SYB_GetIndexBasic(dbc_control_ptr, in_table_name, index_count,
	index_list, error_text)
void          *dbc_control_ptr;
const char    *in_table_name;
unsigned int  *index_count;
DBC_SYB_IDX  **index_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code    = DBC_SUCCESS;
	unsigned int    column_count   = 0;
   DBC_SYB_COL    *column_list    = NULL;
	unsigned int    db_index_count = 0;
	DBC_SYB_DB_IDX *db_index_list  = NULL;
	DBC_SYB_DB_IDX *db_index_ptr;
	DBC_SYB_IDX     index_data;
	unsigned int    count_1;
	unsigned int    count_2;
	int             found_flag;
	char            database_name[DBC_SYB_MAX_DB_NAME_LEN + 1];
	char            owner_name[DBC_SYB_MAX_OWN_NAME_LEN + 1];
	char            table_name[DBC_SYB_MAX_TBL_NAME_LEN + 1];

	*index_count = 0;
	*index_list  = NULL;

	if (((return_code = DBC_SYB_BreakTableName(in_table_name, database_name,
		owner_name, table_name, error_text)) == DBC_SUCCESS) &&
		(!(*table_name))) {
		sprintf(error_text,
			"The table name component is empty in specification '%s'.",
			in_table_name);
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = DBC_SYB_GetColumnBasic(dbc_control_ptr, in_table_name,
		&column_count, &column_list, error_text)) == DBC_SUCCESS) {
		if (((return_code = DBC_SYB_GetDBIndexBasic(dbc_control_ptr,
			in_table_name, &db_index_count, &db_index_list, error_text)) ==
			DBC_SUCCESS) && db_index_count) {
			memset(&index_data, '\0', sizeof(index_data));
			db_index_ptr                    = db_index_list;
			index_data.index_id             = db_index_ptr->index_id;
			index_data.key_count            = db_index_ptr->key_count;
			index_data.status               = db_index_ptr->status;
			index_data.unique_index_flag    =
				(db_index_ptr->status & 0X02) ? DBC_TRUE : DBC_FALSE;
			index_data.clustered_index_flag =
				(db_index_ptr->index_id == 1) ? DBC_TRUE : DBC_FALSE;
			index_data.ignore_dup_key_flag  =
				(db_index_ptr->status & 0X01) ? DBC_TRUE : DBC_FALSE;
			index_data.ignore_dup_row_flag  =
				(db_index_ptr->status & 0X04) ? DBC_TRUE : DBC_FALSE;
			index_data.allow_dup_row_flag   =
				(db_index_ptr->status & 0X40) ? DBC_TRUE : DBC_FALSE;
			index_data.segment_number       = db_index_ptr->segment_number;
			index_data.fill_factor          = 0;
			index_data.column_count         = 0;
			nstrcpy(index_data.index_name, db_index_ptr->index_name,
				sizeof(index_data.index_name) - 1);
			nstrcpy(index_data.segment_name, db_index_ptr->segment_name,
				sizeof(index_data.segment_name) - 1);
			for (count_1 = 0; count_1 < db_index_count; count_1++) {
				if (strcmp(db_index_list[count_1].index_name,
					db_index_ptr->index_name)) {
					if (mema_append(index_count, ((void **) index_list),
						&index_data, sizeof(index_data)) != STRFUNCS_SUCCESS) {
						sprintf(error_text, "%s for table '%s.%s.%s'.",
							"Unable to allocate memory for an index definition list",
							database_name, owner_name, table_name);
						return_code = DBC_FAILURE;
						break;
					}
					memset(&index_data, '\0', sizeof(index_data));
					db_index_ptr                    = db_index_list + count_1;
					index_data.index_id             = db_index_ptr->index_id;
					index_data.key_count            = db_index_ptr->key_count;
					index_data.status               = db_index_ptr->status;
					index_data.unique_index_flag    =
						(db_index_ptr->status & 0X02) ? DBC_TRUE : DBC_FALSE;
					index_data.clustered_index_flag =
						(db_index_ptr->index_id == 1) ? DBC_TRUE : DBC_FALSE;
					index_data.ignore_dup_key_flag  =
						(db_index_ptr->status & 0X01) ? DBC_TRUE : DBC_FALSE;
					index_data.ignore_dup_row_flag  =
						(db_index_ptr->status & 0X04) ? DBC_TRUE : DBC_FALSE;
					index_data.allow_dup_row_flag   =
						(db_index_ptr->status & 0X40) ? DBC_TRUE : DBC_FALSE;
					index_data.segment_number       = db_index_ptr->segment_number;
					index_data.fill_factor          = 0;
					index_data.column_count         = 0;
					nstrcpy(index_data.index_name, db_index_ptr->index_name,
						sizeof(index_data.index_name) - 1);
					nstrcpy(index_data.segment_name, db_index_ptr->segment_name,
						sizeof(index_data.segment_name) - 1);
				}
				if (index_data.column_count == DBC_SYB_MAX_IDX_COLS) {
					sprintf(error_text, "%s '%s' for table '%s.%s.%s' %s (%d).",
						"The number of columns specified in index",
						index_data.index_name, database_name, owner_name,
						table_name, "exceeds the maximum",
						DBC_SYB_MAX_IDX_COLS);
					return_code = DBC_FAILURE;
					break;
				}
				found_flag = DBC_FALSE;
				for (count_2 = 0; count_2 < column_count; count_2++) {
					if (!strcmp(db_index_list[count_1].column_name,
						column_list[count_2].name)) {
						index_data.column_list[index_data.column_count++] =
							column_list[count_2];
						found_flag = DBC_TRUE;
						break;
					}
				}
				if (found_flag != DBC_TRUE) {
					sprintf(error_text,
				"%s ('%s.%s.%s') %s %u (named '%s') --- %s (named '%s') %s.",
						"Attempt to get a index definition for the table",
						database_name, owner_name, table_name,
						"failed on index number", count_1 + 1,
						db_index_list[count_1].index_name,
						"a column specified in the index",
						db_index_list[count_1].column_name,
						"was not located in the list of all table columns");
					return_code = DBC_FAILURE;
					break;
				}
			}
			if ((return_code == DBC_SUCCESS) && (mema_append(index_count,
				((void **) index_list), &index_data, sizeof(index_data)) !=
				STRFUNCS_SUCCESS)) {
				sprintf(error_text, "%s for table '%s.%s.%s'.",
					"Unable to allocate memory for an index definition list",
					database_name, owner_name, table_name);
				return_code = DBC_FAILURE;
			}
			if (db_index_list != NULL)
				free(db_index_list);
		}
		if (return_code != DBC_SUCCESS) {
			if (*index_list != NULL)
				free(*index_list);
			*index_count = 0;
			*index_list  = NULL;
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

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
	int           return_code = DBC_SUCCESS;
	unsigned int  index_count = 0;
	DBC_SYB_IDX  *index_list  = NULL;
	unsigned int  count_1;
	char          error_text[DBC_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DBC_SYB_GetIndex()'\n");
	fprintf(stderr, "---- ------- --- --------------------\n");

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
		if ((return_code = DBC_SYB_GetIndex(argv[1], argv[count_1],
			&index_count, &index_list, error_text)) != DBC_SUCCESS)
			break;
		fprintf(stderr, "%u indices in table\n", index_count);
		DBC_SYB_EMIT_IndexListIdx(index_count, index_list, NULL, NULL);
		mema_remove_all(&index_count, ((void **) &index_list));
	}

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

