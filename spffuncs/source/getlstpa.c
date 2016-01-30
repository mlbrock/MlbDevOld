/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Gets the interior of a parse item.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_GetListParseDef(const SPF_PARSE *parse_ptr,
	unsigned long *current_line, unsigned int *parse_count,
	SPF_PARSE **parse_list, char *error_text)
#else
int SPF_GetListParseDef(parse_ptr, current_line, parse_count, parse_list,
	error_text)
const SPF_PARSE  *parse_ptr;
unsigned long    *current_line;
unsigned int     *parse_count;
SPF_PARSE       **parse_list;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = SPF_GetListParse(parse_ptr->length, parse_ptr->text,
		parse_ptr->file, current_line, parse_count, parse_list, error_text)) ==
		SPF_SUCCESS) {
		if (parse_ptr->flags) {
			if ((return_code = SPF_ALLC_ParseList(*parse_count, *parse_list,
				error_text)) != SPF_SUCCESS)
				SPF_FREE_ParseList(parse_count, parse_list);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_GetListParseString(const char *def_string, const char *file_name,
	unsigned long *current_line, unsigned int *parse_count,
	SPF_PARSE **parse_list, char *error_text)
#else
int SPF_GetListParseString(def_string, file_name, current_line, parse_count,
	parse_list, error_text)
const char     *def_string;
const char     *file_name;
unsigned long  *current_line;
unsigned int   *parse_count;
SPF_PARSE     **parse_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	return(SPF_GetListParse(strlen(def_string), def_string, file_name,
		current_line, parse_count, parse_list, error_text));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_GetListParse(unsigned int def_length, const char *def_string,
	const char *file_name, unsigned long *current_line,
	unsigned int *parse_count, SPF_PARSE **parse_list, char *error_text)
#else
int SPF_GetListParse(def_length, def_string, file_name, current_line,
	parse_count, parse_list, error_text)
unsigned int    def_length;
const char     *def_string;
const char     *file_name;
unsigned long  *current_line;
unsigned int   *parse_count;
SPF_PARSE     **parse_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code    = SPF_SUCCESS;
	char          *start_parse    = NULL;
	int            in_string_flag = SPF_FALSE;
	char          *tmp_ptr_1      = ((char *) def_string);
	unsigned int   parend_depth;
	char          *open_parend_ptr;
	unsigned long  start_line;
	SPF_PARSE      tmp_parse;

	*parse_count = 0;
	*parse_list  = NULL;

	file_name    = (file_name == NULL) ? SPF_PARSE_FILE_FAKE_NAME : file_name;

	while (def_length) {
		while (isspace(*tmp_ptr_1) && def_length) {
			*current_line += ((unsigned long) ((*tmp_ptr_1 == '\n') ? 1 : 0));
			def_length--;
			tmp_ptr_1++;
		}
		if (*tmp_ptr_1 == '#') {
			while (*tmp_ptr_1 && (*tmp_ptr_1 != '\n') && def_length) {
				def_length--;
				tmp_ptr_1++;
			}
			if (*tmp_ptr_1 == '\n') {
				(*current_line)++;
				def_length--;
				tmp_ptr_1++;
			}
			continue;
		}
		if ((*tmp_ptr_1 == ',') && (*parse_count)) {
			def_length--;
			tmp_ptr_1++;
			continue;
		}
		if (!def_length)
			break;
		else if (*tmp_ptr_1 != '@') {
			sprintf(error_text,
				"Non-definition text encountered on line %lu ('%c').",
				*current_line, *tmp_ptr_1);
			return_code = SPF_PARSE_FAILURE;
			break;
		}
		else if ((open_parend_ptr =
			((char *) STRFUNCS_SHIM_memmem(def_length, tmp_ptr_1, 1, "("))) ==
			NULL) {
			sprintf(error_text,
				"Expected an open parenthesis ('(') on line %lu.", *current_line);
			return_code = SPF_PARSE_FAILURE;
			break;
		}
		else {
			start_parse    = tmp_ptr_1;
			def_length    -= ((unsigned int) (open_parend_ptr - tmp_ptr_1)) + 1;
			tmp_ptr_1      = open_parend_ptr + 1;
			parend_depth   = 1;
			start_line     = *current_line;
			in_string_flag = SPF_FALSE;
			while (def_length) {
				if (*tmp_ptr_1 == '(')
					parend_depth++;
				else if (*tmp_ptr_1 == ')') {
					if (!--parend_depth)
						break;
				}
				else if (*tmp_ptr_1 == '\"') {
					def_length--;
					tmp_ptr_1++;
					in_string_flag = SPF_TRUE;
					while (def_length) {
						if ((*tmp_ptr_1 == '\\') && (*(tmp_ptr_1 + 1) == '\"') &&
							(def_length > 1)) {
							def_length--;
							tmp_ptr_1++;
						}
						else if (*tmp_ptr_1 == '\"') {
							in_string_flag = SPF_FALSE;
							break;
						}
						def_length--;
						tmp_ptr_1++;
					}
					if (in_string_flag == SPF_TRUE) {
						sprintf(error_text,
							"Unterminated string constant on line %lu.",
							*current_line);
						return_code = SPF_PARSE_FAILURE;
						break;
					}
				}
				else if (*tmp_ptr_1 == '\n')
					(*current_line)++;
				def_length--;
				tmp_ptr_1++;
			}
			if (parend_depth) {
				sprintf(error_text,
					"Unterminated parenthetical expression on line %lu.",
					start_line);
				return_code = SPF_PARSE_FAILURE;
				break;
			}
			SPF_INIT_Parse(&tmp_parse);
			tmp_parse.file       = file_name;
			tmp_parse.line       = start_line;
			tmp_parse.length     = ((unsigned int) (tmp_ptr_1 - start_parse)) + 1;
			tmp_parse.text       = start_parse;
			tmp_parse.spec_type  = SPF_TYPE_NONE;
			tmp_parse.spec_index = 0;
			tmp_parse.list_index = *parse_count;
			tmp_parse.flags      = SPF_FALSE;
			if (mema_append(parse_count, ((void **) parse_list), &tmp_parse,
				sizeof(tmp_parse)) != STRFUNCS_SUCCESS) {
				SPF_FREE_Parse(&tmp_parse);
				STR_AllocMsgList(*parse_count + 1, sizeof(tmp_parse), error_text,
					"%s %lu",
					"Unable to allocate memory for a definition parse on line",
					*current_line);
				return_code = SPF_MEMORY_FAILURE;
				break;
			}
			def_length--;
			tmp_ptr_1++;
		}
	}

	if (return_code != SPF_SUCCESS)
		SPF_FREE_ParseList(parse_count, parse_list);

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <string.h>

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

static char         *TestList[] = {
	" @def(@A(X)) ",
	"@def(@A(X))",
	"@def(   \f @item_1(\"text\"), \n @item_2(9999), \f @item_3(TRUE) \t    )",
	"@def(   @item_1(\"text\"), @item_2(9999), @item_3(TRUE)    )",
	"   @def(  @item_1(\"text\"), @item_2(9999), @item_3(TRUE)  )   ",
	"@nested_def(@item_1(stuff), @item_2(@sub_item_1(ZZ),@sub_item_2(Z)))"
};

static unsigned int  TestCount = sizeof(TestList) / sizeof(TestList[0]);

COMPAT_FN_DECL(int main, (int, char **));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int           return_code = SPF_SUCCESS;
	char         *file_buffer = NULL;
	unsigned int  count_1;
	unsigned int  count_2;
	unsigned int  count_3;
	unsigned int  parse_count_1;
	SPF_PARSE    *parse_list_1;
	unsigned int  parse_count_2;
	SPF_PARSE    *parse_list_2;
	unsigned long current_line;
	SPF_PARSE     tmp_parse;
	char          error_text[SPF_MAX_ERROR_TEXT];

	STR_EMIT_CharLine('=', 78, NULL, NULL);
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	fprintf(stderr, "Test routine for function 'SPF_GetListParse()'\n");
	fprintf(stderr, "---- ------- --- -------- --------------------\n");

	STR_EMIT_CharLine('=', 78, NULL, NULL);

	printf("Internal Test\n");
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	for (count_1 = 0; count_1 < TestCount; count_1++) {
		printf("INPUT :[%s]\n", TestList[count_1]);
		current_line = 1L;
		if ((return_code = SPF_GetListParseString(TestList[count_1], "FILENAME",
			&current_line, &parse_count_1, &parse_list_1, error_text)) !=
			SPF_SUCCESS)
			goto EXIT_FUNCTION;
		for (count_2 = 0; count_2 < parse_count_1; count_2++) {
			printf("OUTPUT:[%-*.*s]\n",
				((int) parse_list_1[count_2].length),
				((int) parse_list_1[count_2].length),
				parse_list_1[count_2].text);
			if ((return_code = SPF_GetSubParse(parse_list_1 + count_2,
				&tmp_parse, error_text)) != SPF_SUCCESS) {
				SPF_FREE_ParseList(&parse_count_1, &parse_list_1);
				goto EXIT_FUNCTION;
			}
			printf("      :INPUT :[%-*.*s]\n",
				((int) tmp_parse.length), ((int) tmp_parse.length),
				tmp_parse.text);
			if ((return_code = SPF_GetListParseDef(&tmp_parse, &current_line,
				&parse_count_2, &parse_list_2, error_text)) != SPF_SUCCESS) {
				SPF_FREE_ParseList(&parse_count_1, &parse_list_1);
				SPF_FREE_Parse(&tmp_parse);
				goto EXIT_FUNCTION;
			}
			for (count_3 = 0; count_3 < parse_count_2; count_3++)
				printf("      :OUTPUT:[%-*.*s]\n",
					((int) parse_list_2[count_3].length),
					((int) parse_list_2[count_3].length),
					parse_list_2[count_3].text);
			SPF_FREE_ParseList(&parse_count_2, &parse_list_2);
			SPF_FREE_Parse(&tmp_parse);
		}
		SPF_FREE_ParseList(&parse_count_1, &parse_list_1);
		STR_EMIT_CharLine('-', 78, NULL, NULL);
	}
	STR_EMIT_CharLine('=', 78, NULL, NULL);

	if (argc == 1)
		goto EXIT_FUNCTION;

	printf("Command-Line Test\n");
	STR_EMIT_CharLine('=', 78, NULL, NULL);
	for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
		printf("FILE  :[%s]\n", argv[count_1]);
		if ((return_code = SPF_ReadDefFile(argv[count_1], NULL,
			&file_buffer, error_text)) != SPF_SUCCESS)
			goto EXIT_FUNCTION;
		printf("INPUT :[%s]\n", file_buffer);
		current_line = 1L;
		if ((return_code = SPF_GetListParseString(file_buffer, argv[count_1],
      	&current_line, &parse_count_1, &parse_list_1, error_text)) !=
         SPF_SUCCESS)
			break;
		free(file_buffer);
		file_buffer = NULL;
		for (count_2 = 0; count_2 < parse_count_1; count_2++) {
			printf("OUTPUT:[%-*.*s]\n",
				((int) parse_list_1[count_2].length),
				((int) parse_list_1[count_2].length),
				parse_list_1[count_2].text);
			if ((return_code = SPF_GetSubParse(parse_list_1 + count_2,
				&tmp_parse, error_text)) != SPF_SUCCESS) {
				SPF_FREE_ParseList(&parse_count_1, &parse_list_1);
				break;
			}
			printf("      :INPUT :[%-*.*s]\n",
				((int) tmp_parse.length),
				((int) tmp_parse.length), tmp_parse.text);
			if ((return_code = SPF_GetListParseDef(&tmp_parse, &current_line,
				&parse_count_2, &parse_list_2, error_text)) != SPF_SUCCESS) {
				SPF_FREE_ParseList(&parse_count_1, &parse_list_1);
				SPF_FREE_Parse(&tmp_parse);
				goto EXIT_FUNCTION;
			}
			for (count_3 = 0; count_3 < parse_count_2; count_3++)
				printf("      :OUTPUT:[%-*.*s]\n",
					((int) parse_list_2[count_3].length),
					((int) parse_list_2[count_3].length),
					parse_list_2[count_3].text);
			SPF_FREE_ParseList(&parse_count_2, &parse_list_2);
			SPF_FREE_Parse(&tmp_parse);
		}
		SPF_FREE_ParseList(&parse_count_1, &parse_list_1);
		if (return_code != SPF_SUCCESS)
			break;
		STR_EMIT_CharLine('-', 78, NULL, NULL);
	}
	if (file_buffer != NULL) {
		free(file_buffer);
		file_buffer = NULL;
	}
	STR_EMIT_CharLine('=', 78, NULL, NULL);

EXIT_FUNCTION:

	if (return_code != SPF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

