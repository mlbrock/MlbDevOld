/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads an SPF definition file.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include <genfuncs.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int SPF_PARSE_IncludeFile, (SPF_CONTEXT *context_ptr,
	const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	SPF_SPEC_FUNCS *funcs_ptr, unsigned int spec_count,
	const SPF_SPEC *spec_list, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_File(SPF_CONTEXT *context_ptr, const char *file_name,
	const char *def_string, SPF_SPEC_FUNCS *funcs_ptr, unsigned int spec_count,
   const SPF_SPEC *spec_list, char *error_text)
#else
int SPF_PARSE_File(context_ptr, file_name, def_string, funcs_ptr,
	spec_count, spec_list, error_text)
SPF_CONTEXT    *context_ptr;
const char     *file_name;
const char     *def_string;
SPF_SPEC_FUNCS *funcs_ptr;
unsigned int    spec_count;
const SPF_SPEC *spec_list;
char           *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code;
	char           *tmp_file_name      = NULL;
	char           *fake_file_name     = SPF_PARSE_FILE_FAKE_NAME;
	int             include_added_flag = SPF_FALSE;
	unsigned int    parse_count        = 0;
	SPF_PARSE      *parse_list         = NULL;
	unsigned int   *spec_count_list    = NULL;
	unsigned long   current_line       = 1L;
	int             found_flag;
	unsigned int    old_current_file_index;
	unsigned int    unparsed_count;
	const SPF_SPEC *tmp_spec_ptr;
	unsigned int    count_1;
	unsigned int    count_2;
   unsigned int    found_index;
	SPF_PARSE       tmp_parse;
	unsigned int    tmp_spec_count_list[256];
	char            gen_error_text[GENFUNCS_MAX_ERROR_TEXT];
	char            tmp_error_text[SPF_MAX_ERROR_TEXT];

	SPF_INIT_Parse(&tmp_parse);
	SPF_SetContextParse(context_ptr, &tmp_parse);

	old_current_file_index = context_ptr->current_file_index;

	if (!spec_count) {
		sprintf(error_text,
			"No 'SPF_SPEC' items in list for definition file '%-.500s'.",
			file_name);
		return_code = SPF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (file_name == NULL)
		tmp_file_name = fake_file_name;
	else if ((return_code = GEN_ExpandToFullPathName(file_name, &tmp_file_name,
		gen_error_text)) != GENFUNCS_SUCCESS) {
		nstrcat(strcpy(error_text,
			"Unable to expand definition include file name: "), gen_error_text,
			SPF_MAX_ERROR_TEXT - 100);
		return_code = SPF_MAP_ERROR_GEN(return_code);
		goto EXIT_FUNCTION;
	}
	else {
		for (count_1 = 0; count_1 < context_ptr->include_count; count_1++) {
			if (!strcmp(tmp_file_name, context_ptr->include_list[count_1])) {
				sprintf(error_text, "Definition include file '%-.500s' %s.",
					tmp_file_name, "may not be included more than once");
				return_code = SPF_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
		if (strl_append(&context_ptr->include_count, &context_ptr->include_list,
			tmp_file_name) != STRFUNCS_SUCCESS) {
			STR_AllocMsgItem(strlen(tmp_file_name) + 1, error_text,
				"%s '%-.500s' %s ", "Unable to add the definition include file",
				tmp_file_name, "to the stack of included files");
			return_code = SPF_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		include_added_flag = SPF_TRUE;
		found_flag         = SPF_FALSE;
		for (count_1 = 0; count_1 < context_ptr->file_count; count_1++) {
			if (!strcmp(tmp_file_name, context_ptr->file_list[count_1])) {
				context_ptr->current_file_index = count_1;
				found_flag                      = SPF_TRUE;
				break;
			}
		}
		if (found_flag != SPF_TRUE) {
			if (strl_append(&context_ptr->file_count, &context_ptr->file_list,
				tmp_file_name) != STRFUNCS_SUCCESS) {
				STR_AllocMsgItem(strlen(tmp_file_name) + 1, error_text,
					"%s '%-.500s' %s ", "Unable to add the definition file name",
					tmp_file_name, "to the list of files");
				return_code = SPF_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			context_ptr->current_file_index = context_ptr->file_count - 1;
		}
		SPF_SetContextParse(context_ptr, &tmp_parse);
	}

	if (spec_count <= (sizeof(tmp_spec_count_list) / sizeof(unsigned int)))
		spec_count_list = tmp_spec_count_list;
	else if ((spec_count_list = ((unsigned int *) malloc(spec_count *
		sizeof(unsigned int)))) == NULL) {
		STR_AllocMsgList(spec_count, sizeof(unsigned int), error_text,
			"%s for the definition file '%-.500s'.",
			"Unable to allocate memory for the list of definition counts",
			tmp_file_name);
		return_code = SPF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < spec_count; count_1++)
		spec_count_list[count_1] = 0;

	if ((return_code = SPF_GetListParseString(def_string, tmp_file_name,
		&current_line, &parse_count, &parse_list, error_text)) != SPF_SUCCESS)
		goto EXIT_FUNCTION;
	SPF_SetContextParseList(context_ptr, parse_count, parse_list);
	unparsed_count = parse_count;

	for (count_1 = 0; count_1 < spec_count; count_1++) {
		tmp_spec_ptr = spec_list + count_1;
		while (SPF_FIND_Spec(tmp_spec_ptr, parse_count, parse_list,
			&found_index) == STRFUNCS_ITEM_FOUND) {
			parse_list[found_index].spec_type = tmp_spec_ptr->type;
			if (spec_count_list[count_1] == tmp_spec_ptr->max_count) {
				sprintf(error_text, "The %s '%s()' %s (%u) %s '%-.500s'.",
					"definition item", tmp_spec_ptr->name,
					"specifier occurs more than than the maximum number of times",
					tmp_spec_ptr->max_count, "in definition file", tmp_file_name);
				return_code = SPF_PARSE_FAILURE;
				goto EXIT_FUNCTION;
			}
			spec_count_list[count_1]++;
			if (tmp_spec_ptr->type == SPF_TYPE_INCLUDE_FILE) {
				if ((return_code = SPF_PARSE_IncludeFile(context_ptr,
					tmp_spec_ptr, parse_list + found_index, funcs_ptr, spec_count,
					spec_list, error_text)) != SPF_SUCCESS)
					goto EXIT_FUNCTION;
			}
			else if (funcs_ptr->parse == NULL) {
				if ((return_code = SPF_PARSE_Basic(context_ptr, tmp_spec_ptr,
					parse_list + found_index, NULL, error_text)) != SPF_SUCCESS)
					goto EXIT_FUNCTION;
			}
			else if ((return_code = (*funcs_ptr->parse)(context_ptr,
				tmp_spec_ptr, parse_list + found_index, NULL, error_text)) !=
				SPF_SUCCESS)
				goto EXIT_FUNCTION;
			SPF_FREE_Parse(parse_list + found_index);
			unparsed_count--;
			if (found_index < (parse_count - 1)) {
				for (count_2 = found_index; count_2 < (parse_count - 1); count_2++)
					parse_list[count_2] = parse_list[count_2 + 1];
				SPF_INIT_Parse(parse_list + (parse_count - 1));
			}
		}
		if (spec_count_list[count_1] < tmp_spec_ptr->min_count) {
			sprintf(error_text,
				"%s '%s()' %s %s '%-.500s' %u times, %s %u times.",
				"The definition item", tmp_spec_ptr->name, "was found in the",
				"definition file", tmp_file_name, spec_count_list[count_1],
				"but is required at least", tmp_spec_ptr->min_count);
			return_code = SPF_PARSE_FAILURE;
			goto EXIT_FUNCTION;
		}
		if (!unparsed_count)
			break;
	}

	if (unparsed_count) {
		sprintf(error_text,
			"There %s %u %s%s %s '%-.500s' --- %s %s '%-.*s' %s.",
			(unparsed_count == 1) ? "is" : "are", unparsed_count,
			"unparsed item", (unparsed_count == 1) ? " in the" : "s in the",
			"definition file", tmp_file_name,
			(unparsed_count == 1) ?  "it" : "the first", "is the string",
			(parse_list->length > 500) ? 500 : ((int) parse_list->length),
			parse_list->text, SPF_GetLocationLineFile(parse_list, 500,
			tmp_error_text));
		return_code = SPF_PARSE_FAILURE;
	}

EXIT_FUNCTION:

	context_ptr->current_file_index = old_current_file_index;

	if ((tmp_file_name != NULL) && (tmp_file_name != fake_file_name))
		free(tmp_file_name);

	if (include_added_flag == SPF_TRUE)
		strl_remove(&context_ptr->include_count, &context_ptr->include_list,
			context_ptr->include_count - 1, 1);

	SPF_FREE_ParseList(&parse_count, &parse_list);
	SPF_FREE_Parse(&tmp_parse);

	if ((spec_count_list != NULL) && (spec_count_list != tmp_spec_count_list))
		free(spec_count_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int SPF_PARSE_IncludeFile(SPF_CONTEXT *context_ptr,
	const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	SPF_SPEC_FUNCS *funcs_ptr, unsigned int spec_count,
	const SPF_SPEC *spec_list, char *error_text)
#else
static int SPF_PARSE_IncludeFile(context_ptr, spec_ptr, parse_ptr, funcs_ptr,
	spec_count, spec_list, error_text)
SPF_CONTEXT     *context_ptr;
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
SPF_SPEC_FUNCS  *funcs_ptr;
unsigned int     spec_count;
const SPF_SPEC  *spec_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int       return_code;
	char     *tmp_file_name     = NULL;
	char     *include_file_name = NULL;
	char     *def_string        = NULL;
	SPF_SPEC  tmp_spec;
	char      gen_error_text[GENFUNCS_MAX_ERROR_TEXT];
	char      tmp_error_text[SPF_MAX_ERROR_TEXT];

	tmp_spec            = *spec_ptr;
	tmp_spec.min_length = 1;
	tmp_spec.max_length = UINT_MAX;

	if ((return_code = SPF_PARSE_String(&tmp_spec, parse_ptr, &tmp_file_name,
		error_text)) != SPF_SUCCESS)
		goto EXIT_FUNCTION;

	if ((return_code = GEN_ExpandToFullPathName(tmp_file_name,
		&include_file_name, gen_error_text)) != GENFUNCS_SUCCESS) {
		SPF_GetLocationLineFile(parse_ptr, 500, tmp_error_text);
		sprintf(error_text, "%s specified %s: %-.*s",
			"Error on attempt to expand the definition include file name",
			tmp_error_text, SPF_MAX_ERROR_TEXT - (100 + 500), gen_error_text);
		return_code = SPF_MAP_ERROR_GEN(return_code);
		goto EXIT_FUNCTION;
	}

	if ((return_code = SPF_ReadDefFile(include_file_name, NULL, &def_string,
		tmp_error_text)) != SPF_SUCCESS) {
		strcpy(error_text,
	"Error on attempt to expand the definition include file name specified ");
		nstrcat(strcat(SPF_GetLocationLineFile(parse_ptr, 500,
			error_text + strlen(error_text)), ": "), tmp_error_text,
			SPF_MAX_ERROR_TEXT - (100 + 500));
	}
	else
		return_code = SPF_PARSE_File(context_ptr, include_file_name, def_string,
			funcs_ptr, spec_count, spec_list, error_text);

EXIT_FUNCTION:

	if (tmp_file_name != NULL)
		free(tmp_file_name);

	if (include_file_name != NULL)
		free(include_file_name);

	if (def_string != NULL)
		free(def_string);

	return(return_code);
}
/*	***********************************************************************	*/

