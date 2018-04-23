/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Reads an ADF domain definition file.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>
#include <stdlib.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_Complex(SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, unsigned int spec_count,
	const SPF_SPEC *spec_list, void *parent_ptr, void *this_ptr,
	char *error_text)
#else
int SPF_PARSE_Complex(context_ptr, spec_ptr, parse_ptr, spec_count, spec_list,
	parent_ptr, this_ptr, error_text)
SPF_CONTEXT     *context_ptr;
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
unsigned int     spec_count;
const SPF_SPEC  *spec_list;
void            *parent_ptr;
void            *this_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code;
	unsigned int    parse_count     = 0;
	SPF_PARSE      *parse_list      = NULL;
	unsigned int   *spec_count_list = NULL;
	unsigned int    unparsed_count;
	const SPF_SPEC *tmp_spec_ptr;
	unsigned long   current_line;
	unsigned int    count_1;
	unsigned int    count_2;
   unsigned int    found_index;
	SPF_PARSE       tmp_parse;
	unsigned int    tmp_spec_count_list[256];
	char            tmp_error_text_1[SPF_MAX_ERROR_TEXT];
	char            tmp_error_text_2[SPF_MAX_ERROR_TEXT];

	SPF_INIT_Parse(&tmp_parse);
	SPF_SetContextParse(context_ptr, &tmp_parse);

	if (!spec_count) {
		sprintf(error_text, "No 'SPF_SPEC' items in list for '%s()'.",
			spec_ptr->name);
		return_code = SPF_FAILURE;
		goto EXIT_FUNCTION;
	}

	if (spec_count <= (sizeof(tmp_spec_count_list) / sizeof(unsigned int)))
		spec_count_list = tmp_spec_count_list;
	else if ((spec_count_list = ((unsigned int *) malloc(spec_count *
		sizeof(unsigned int)))) == NULL) {
		STR_AllocMsgList(spec_count, sizeof(unsigned int), error_text,
			"%s for the '%s()' definition beginning on line %lu",
			"Unable to allocate memory for the list of definition counts",
			spec_ptr->name, parse_ptr->line);
		return_code = SPF_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < spec_count; count_1++)
		spec_count_list[count_1] = 0;

	if ((return_code = SPF_GetSubParse(parse_ptr, &tmp_parse, error_text)) !=
		SPF_SUCCESS)
		goto EXIT_FUNCTION;

	current_line = tmp_parse.line;
	if ((return_code = SPF_GetListParseDef(&tmp_parse, &current_line,
		&parse_count, &parse_list, error_text)) != SPF_SUCCESS)
		goto EXIT_FUNCTION;
	unparsed_count = parse_count;

	for (count_1 = 0; count_1 < spec_count; count_1++) {
		tmp_spec_ptr = spec_list + count_1;
		while (SPF_FIND_Spec(tmp_spec_ptr, parse_count, parse_list,
			&found_index) == STRFUNCS_ITEM_FOUND) {
			parse_list[found_index].spec_type = tmp_spec_ptr->type;
			if (spec_count_list[count_1] == tmp_spec_ptr->max_count) {
				sprintf(error_text, "The '%s()' %s '%s()' %s (%u).",
					spec_ptr->name, "definition item", tmp_spec_ptr->name,
					"specifier occurs more than than the maximum number of times",
					tmp_spec_ptr->max_count);
				return_code = SPF_PARSE_FAILURE;
				goto EXIT_FUNCTION;
			}
			spec_count_list[count_1]++;
			if (spec_ptr->funcs.parse == NULL) {
				if ((return_code = SPF_PARSE_Basic(context_ptr, tmp_spec_ptr,
					parse_list + found_index, this_ptr, error_text)) !=
					SPF_SUCCESS)
					goto EXIT_FUNCTION;
			}
			else if ((return_code = (*spec_ptr->funcs.parse)(context_ptr,
				tmp_spec_ptr, parse_list + found_index, this_ptr, error_text)) !=
				SPF_SUCCESS)
				goto EXIT_FUNCTION;
			if ((spec_ptr->funcs.post_parse != NULL) && ((return_code =
				(*spec_ptr->funcs.post_parse)(context_ptr, tmp_spec_ptr,
				parse_list + found_index, parent_ptr, this_ptr, error_text)) !=
				SPF_SUCCESS))
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
			sprintf(error_text, "%s '%s()' %s '%s()' %s %u times, %s %u times.",
				"The definition item", tmp_spec_ptr->name, "was found in this",
				spec_ptr->name, "definition", spec_count_list[count_1],
				"but is required at least", tmp_spec_ptr->min_count);
			return_code = SPF_PARSE_FAILURE;
			goto EXIT_FUNCTION;
		}
		if (!unparsed_count)
			break;
	}

	if (unparsed_count) {
		sprintf(error_text,
			"There %s %u %s%s '%s()' %s %s --- %s %s '%-.*s' %s.",
			(unparsed_count == 1) ? "is" : "are", unparsed_count,
			"unparsed item", (unparsed_count == 1) ? " in the" : "s in the",
			spec_ptr->name, "definition", SPF_GetLocationLineFile(parse_ptr, 250,
			tmp_error_text_1),
			(unparsed_count == 1) ?  "it" : "the first", "is the string",
			(parse_list->length > 500) ? 500 : ((int) parse_list->length),
			parse_list->text, SPF_GetLocationLineFile(parse_list, 250,
			tmp_error_text_2));
		return_code = SPF_PARSE_FAILURE;
	}

EXIT_FUNCTION:

	SPF_FREE_ParseList(&parse_count, &parse_list);
	SPF_FREE_Parse(&tmp_parse);

	if ((spec_count_list != NULL) && (spec_count_list != tmp_spec_count_list))
		free(spec_count_list);

	return(return_code);
}
/*	***********************************************************************	*/

