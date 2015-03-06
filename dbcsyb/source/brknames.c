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

		Copyright Michael L. Brock 1993 - 2015.
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

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Prototypes for functions private to this module . . .							*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int DBC_SYB_BreakNames,
	(const char *name_type, const char *in_name, char *out_database_name,
	char *out_owner_name, char *out_table_name, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_BreakDatabaseName(const char *in_name, char *out_database_name,
	char *out_owner_name, char *error_text)
#else
int DBC_SYB_BreakDatabaseName(in_name, out_database_name, out_owner_name,
	error_text)
const char *in_name;
char       *out_database_name;
char       *out_owner_name;
char       *error_text;
#endif /* #ifndef NARGS */
{
	unsigned int  point_count;
	const char   *tmp_in_ptr;
	char          tmp_in_name[((DBC_SYB_MAX_ANY_NAME_LEN * 3) + 2) + 1];
	char          tmp_out_name[DBC_SYB_MAX_ANY_NAME_LEN + 1];

	if ((in_name != NULL) && *in_name &&
		(strlen(in_name) < ((DBC_SYB_MAX_ANY_NAME_LEN * 2) + 2)) &&
		((point_count = chrcnt(in_name, '.')) < 2))
		tmp_in_ptr = strcat(strcpy(tmp_in_name, in_name),
			(!point_count) ? "..X" : ".X");
	else
		tmp_in_ptr = in_name;

	return(DBC_SYB_BreakNames("database", tmp_in_ptr, out_database_name,
		out_owner_name, tmp_out_name, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int DBC_SYB_BreakTableName(const char *in_name, char *out_database_name,
	char *out_owner_name, char *out_table_name, char *error_text)
#else
int DBC_SYB_BreakTableName(in_name, out_database_name, out_owner_name,
	out_table_name, error_text)
const char *in_name;
char       *out_database_name;
char       *out_owner_name;
char       *out_table_name;
char       *error_text;
#endif /* #ifndef NARGS */
{
	return(DBC_SYB_BreakNames("table", in_name, out_database_name,
		out_owner_name, out_table_name, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int DBC_SYB_BreakNames(const char *name_type, const char *in_name,
	char *out_database_name, char *out_owner_name, char *out_table_name,
	char *error_text)
#else
static int DBC_SYB_BreakNames(name_type, in_name, out_database_name,
	out_owner_name, out_table_name, error_text)
const char *name_type;
const char *in_name;
char       *out_database_name;
char       *out_owner_name;
char       *out_table_name;
char       *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = DBC_FAILURE;
	char         *tmp_ptr[3];
	unsigned int  point_count;
	char          tmp_name[((DBC_SYB_MAX_ANY_NAME_LEN * 3) + 2) + 1];
	char          tmp_error_text[DBC_MAX_ERROR_TEXT];

	*out_database_name = '\0';
	*out_owner_name    = '\0';
	*out_table_name    = '\0';

	if ((in_name == NULL) || (!(*in_name)))
		sprintf(tmp_error_text, "The %s name string is empty.", name_type);
	else if (strlen(in_name) > ((DBC_SYB_MAX_ANY_NAME_LEN * 3) + 2))
		sprintf(tmp_error_text,
			"%s %s %s ('%s', length = %u) exceeds the maximum allowable (%u).",
			"The total length of the", name_type, "name string", in_name,
			strlen(in_name), (DBC_SYB_MAX_ANY_NAME_LEN * 3) + 2);
	else if ((point_count =
		chrcnt(strcpy(tmp_name, in_name), '.')) > 2)
		sprintf(tmp_error_text, "Invalid number of component separators (%u).",
			point_count);
	else {
		if (!point_count) {
			tmp_ptr[0] = "";
			tmp_ptr[1] = "";
			tmp_ptr[2] = tmp_name;
		}
		else if (point_count == 1) {
			tmp_ptr[0]     = "";
			tmp_ptr[1]     = tmp_name;
			tmp_ptr[2]     = strchr(tmp_ptr[1], '.') + 1;
			tmp_ptr[2][-1] = '\0';
		}
		else {
			tmp_ptr[0]     = tmp_name;
			tmp_ptr[1]     = strchr(tmp_name, '.') + 1;
			tmp_ptr[2]     = strchr(tmp_ptr[1], '.') + 1;
			tmp_ptr[1][-1] = '\0';
			tmp_ptr[2][-1] = '\0';
		}
		if (strlen(tmp_ptr[0]) > DBC_SYB_MAX_ANY_NAME_LEN)
			sprintf(tmp_error_text,
				"%s ('%s', length = %u) exceeds the maximum allowable (%u).",
				"The length of the database name component", tmp_ptr[0],
				strlen(tmp_ptr[0]), DBC_SYB_MAX_ANY_NAME_LEN);
		else if (strlen(tmp_ptr[1]) > DBC_SYB_MAX_ANY_NAME_LEN)
			sprintf(tmp_error_text,
				"%s ('%s', length = %u) exceeds the maximum allowable (%u).",
				"The length of the owner name component", tmp_ptr[1],
				strlen(tmp_ptr[1]), DBC_SYB_MAX_ANY_NAME_LEN);
		else if (strlen(tmp_ptr[2]) > DBC_SYB_MAX_ANY_NAME_LEN)
			sprintf(tmp_error_text,
				"%s ('%s', length = %u) exceeds the maximum allowable (%u).",
				"The length of the table name component", tmp_ptr[2],
				strlen(tmp_ptr[2]), DBC_SYB_MAX_ANY_NAME_LEN);
		else {
			strcpy(out_database_name, tmp_ptr[0]);
			strcpy(out_owner_name,    tmp_ptr[1]);
			strcpy(out_table_name,    tmp_ptr[2]);
			return_code = DBC_SUCCESS;
		}
	}

	if (return_code != DBC_SUCCESS)
		sprintf(error_text,
			"Invalid %s name specification --- expected '%s': %s", name_type,
			(!strcmp(name_type, "table")) ?
			"[<data-base-name>.][<owner-name>.]<table-name>" :
			"<data-base-name>[.<owner-name>]", tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <memory.h>

#include <genfuncs.h>

typedef struct {
	char source[(DBC_SYB_MAX_ANY_NAME_LEN * 3) + 1];
	char database_name[DBC_SYB_MAX_ANY_NAME_LEN + 1];
	char owner_name[DBC_SYB_MAX_ANY_NAME_LEN + 1];
	char table_name[DBC_SYB_MAX_ANY_NAME_LEN + 1];
} TEST_TEXT;

static const TEST_TEXT    TEST_TextList[][2] = {
	{
		{	"A.B.C",	"A",	"B",	"C"	},
		{	"A.B.C",	"A",	"B",	""		}
	},
	{
		{	"A.B",	"",	"A",	"B"	},
		{	"A.B",	"A",	"B",	""		}
	},
	{
		{	"A",		"",	"",	"A"	},
		{	"A",		"A",	"",	""		}
	},
	{
		{	"A.B.",	"A",	"B",	""		},
		{	"A.B.",	"A",	"B",	""		}
	},
	{
		{	"A.",		"",	"A",	""		},
		{	"A.",		"A",	"",	""		}
	},
	{
		{	"A..",	"A",	"",	""		},
		{	"A..",	"A",	"",	""		}
	},
	{
		{	".A.B",	"",	"A",	"B"	},
		{	".A.B",	"",	"A",	""		}
	},
	{
		{	".A",		"",	"",	"A"	},
		{	".A",		"",	"A",	""		}
	},
	{
		{	"..A",	"",	"",	"A"	},
		{	"..A",	"",	"",	""		}
	}
};

static const unsigned int  TEST_TextCount     =
	sizeof(TEST_TextList) / sizeof(TEST_TextList[0]);

static const char *UsageString = "<table-spec> [<table-spec> . . .]";

COMPAT_FN_DECL(int main, (int argc, char **argv));

COMPAT_FN_DECL_STATIC(int TEST_CheckResults,
	(const TEST_TEXT *test_ptr, const char *out_database_name,
	const char *out_owner_name, const char *out_table_name, char *error_text));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int              return_code = DBC_SUCCESS;
	unsigned int     count_1;
	char             database_name[DBC_SYB_MAX_ANY_NAME_LEN + 1];
	char             owner_name[DBC_SYB_MAX_ANY_NAME_LEN + 1];
	char             table_name[DBC_SYB_MAX_ANY_NAME_LEN + 1];
	const TEST_TEXT *test_ptr;
	char             error_text[DBC_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for 'DBC_SYB_BreakTableName()'\n");
	fprintf(stderr, "                 'DBC_SYB_BreakDatabaseName()'\n");
	fprintf(stderr, "---- ------- --- --------------------------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		if ((!stricmp(argv[count_1], "-HELP")) ||
			(!stricmp(argv[count_1], "-H")))
			GEN_DoSimpleUsage(DBC_SUCCESS, argv[0],
				"Help request with '-HELP' noted . . .", UsageString);
	}

	if (argc == 1) {
		for (count_1 = 0; count_1 < TEST_TextCount; count_1++) {
			test_ptr = &TEST_TextList[count_1][0];
			if (*test_ptr->source) {
				printf("Source Text   : %s\n", test_ptr->source);
				if (DBC_SYB_BreakTableName(test_ptr->source, database_name,
					owner_name, table_name, error_text) == DBC_SUCCESS)
					printf("Break Table   : [%s][%s][%s]\n",
						database_name, owner_name, table_name);
				else
					printf("ERROR Table   : %s\n", error_text);
				if (TEST_CheckResults(test_ptr, database_name,
					owner_name, table_name, error_text) != DBC_SUCCESS)
					return_code = DBC_FAILURE;
			}
			test_ptr = &TEST_TextList[count_1][1];
			if (*test_ptr->source) {
				*table_name = '\0';
				if (DBC_SYB_BreakDatabaseName(test_ptr->source, database_name,
					owner_name, error_text) == DBC_SUCCESS)
					printf("Break Database: [%s][%s][%s]\n",
						database_name, owner_name, table_name);
				else
					printf("ERROR Database: %s\n", error_text);
				if (TEST_CheckResults(test_ptr, database_name,
					owner_name, table_name, error_text) != DBC_SUCCESS)
					return_code = DBC_FAILURE;
			}
			STR_EMIT_CharLine('-', 78, NULL, NULL);
		}
	}
	else {
		for (count_1 = 2; count_1 < ((unsigned int) argc); count_1++) {
			printf("Source Text   : %s\n", argv[count_1]);
			if (DBC_SYB_BreakTableName(argv[count_1], database_name,
				owner_name, table_name, error_text) == DBC_SUCCESS)
				printf("Break Table   : [%s][%s][%s]\n",
					database_name, owner_name, table_name);
			else
				printf("ERROR Table   : %s\n", error_text);
			if (DBC_SYB_BreakDatabaseName(argv[count_1], database_name,
				owner_name, error_text) == DBC_SUCCESS)
				printf("Break Database: [%s][%s][%s]\n",
					database_name, owner_name, table_name);
			else
				printf("ERROR Database: %s\n", error_text);
			STR_EMIT_CharLine('-', 78, NULL, NULL);
		}
	}

	if (return_code != DBC_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	return(return_code);
}

#ifndef NARGS
static int TEST_CheckResults(const TEST_TEXT *test_ptr,
	const char *database_name, const char *owner_name, const char *table_name,
	char *error_text)
#else
static int TEST_CheckResults(test_ptr, database_name, owner_name, table_name,
	error_text)
const TEST_TEXT *test_ptr;
const char      *database_name;
const char      *owner_name;
const char      *table_name;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int return_code = DBC_SUCCESS;

	if (strcmp(test_ptr->database_name, database_name)) {
		printf("SOURCE ERROR: Expected database name '%s', got '%s'.\n",
			test_ptr->database_name, database_name);
		return_code = DBC_FAILURE;
	}
	if (strcmp(test_ptr->owner_name, owner_name)) {
		printf("SOURCE ERROR  : Expected owner name '%s', got '%s'.\n",
			test_ptr->owner_name, owner_name);
		return_code = DBC_FAILURE;
	}
	if (strcmp(test_ptr->table_name, table_name)) {
		printf("SOURCE ERROR  : Expected table name '%s', got '%s'.\n",
			test_ptr->table_name, table_name);
		return_code = DBC_FAILURE;
	}

	if (return_code != DBC_SUCCESS)
		strcpy(error_text, "One or more regression tests failed.");
	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

