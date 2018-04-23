/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
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

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include "dbcfunci.h"

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/* *********************************************************************** */
#ifndef NARGS
int DBC_TableToMembers(DBC_CONTEXT *dbc_context_ptr, const char *in_table_name,
	unsigned int *structure_size, unsigned int *member_count, MDDL **member_list,
	char *error_text)
#else
int DBC_TableToMembers(dbc_context_ptr, in_table_name, structure_size,
	member_count, member_list, error_text)
DBC_CONTEXT   *dbc_context_ptr;
const char    *in_table_name;
unsigned int  *structure_size;
unsigned int  *member_count;
MDDL         **member_list;
char          *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.table_to_members),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.table_to_members)
			(dbc_context_ptr->dbc_control_ptr, in_table_name, structure_size,
			member_count, member_list, error_text);

	return(return_code);
}
/* *********************************************************************** */

#ifdef TEST_MAIN

#include <memory.h>
#include <stdio.h>
#include <string.h>

#include <genfuncs.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

static const char *UsageString =
	"<connection-spec> [-OUTPUT={OFF|ON}] <table-name> [<table-name> . . .]";

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code   = DBC_SUCCESS;
	unsigned int  member_count  = 0;
	MDDL         *member_list   = NULL;
	int           output_flag   = DBC_FALSE;
	unsigned int  out_row_count = 0;
	void         *out_row_list  = NULL;
	unsigned int  count_1;
	unsigned int  structure_size;
	DBC_CONTEXT   dbc_context;
	char          sql_command[1024];
	char          error_text[DBC_MAX_ERROR_TEXT];
	char          gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DBC_TableToMembers()'\n");
	fprintf(stderr, "---- ------- --- ----------------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	DBC_AttachFacility(NULL);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H")))
			GEN_DoSimpleUsage(DBC_SUCCESS, argv[0],
				"Help request with '-HELP' noted . . .", UsageString);
	}

	if (argc < 3)
		GEN_DoSimpleUsage(DBC_BAD_ARGS_FAILURE, argv[0],
			"Invalid command line encountered . . .", UsageString);

	if ((return_code = DBC_Open(&dbc_context, NULL, "DBC:GetCols",
		argv[1], NULL, DBC_FLAG_NONE, NULL, error_text)) == DBC_SUCCESS) {
		for (count_1 = 2; count_1 < ((unsigned int) argc); count_1++) {
			if (!stricmp(argv[count_1], "-OUTPUT=ON")) {
				output_flag = DBC_TRUE;
				continue;
			}
			else if (!stricmp(argv[count_1], "-OUTPUT=OFF")) {
				output_flag = DBC_FALSE;
				continue;
			}
			fprintf(stderr, "Table Name  : %s --- ", argv[count_1]);
			if ((return_code =
				DBC_TableToMembers(&dbc_context,
				argv[count_1], &structure_size, &member_count, &member_list,
				error_text)) != DBC_SUCCESS)
				break;
			fprintf(stderr, "%u columns in table (structure size = %u).\n",
				member_count, structure_size);
			MDDL_EmitMemberListIdx(member_count, member_list, NULL, NULL);
			if (output_flag == DBC_TRUE) {
				strcat(strcpy(sql_command, "SELECT * FROM "), argv[count_1]);
				if ((return_code = (*dbc_context.dbc_funcs.get_rows)
					(dbc_context.dbc_control_ptr, member_count, member_list,
					sql_command, argv[count_1], &out_row_count, &out_row_list,
					structure_size, structure_size, 0, 0, 1000, error_text)) !=
					DBC_SUCCESS)
					break;
				if ((return_code = MDDL_SetDisplayLengthList(0, NULL,
					member_count, member_list, GENFUNCS_TRUE, strlen("*NULL*"),
					strlen("-"), NULL, error_text)) != GENFUNCS_SUCCESS) {
					nstrcpy(error_text, gen_error_text, DBC_MAX_ERROR_TEXT - 1);
					return_code = DBC_MAP_ERROR_GEN_TO_DBC(return_code);
					break;
				}
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				if ((return_code = MDDL_DumpText(0, NULL, member_count,
					member_list, out_row_count, ((const char *) out_row_list),
					structure_size, GENFUNCS_TRUE, GENFUNCS_FALSE,
					GENFUNCS_TRUE, 0, 64, "*NULL*", " ", "-", "*", "\f", NULL,
					"\n", NULL, NULL, NULL, NULL, NULL, NULL, NULL,
					gen_error_text)) != GENFUNCS_SUCCESS) {
					nstrcpy(error_text, gen_error_text, DBC_MAX_ERROR_TEXT - 1);
					return_code = DBC_MAP_ERROR_GEN_TO_DBC(return_code);
					break;
				}
				if (out_row_list != NULL)
					free(out_row_list);
				out_row_list = NULL;
				STR_EMIT_CharLine('=', 78, NULL, NULL);
			}
			MDDL_FreeMemberList(&member_count, &member_list);
		}
		DBC_Close(&dbc_context);
	}

	if (out_row_list != NULL)
		free(out_row_list);

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

