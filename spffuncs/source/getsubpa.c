/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Decomposes an SPF specification sub-item.

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

#include <stdlib.h>
#include <string.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_GetSubParse(const SPF_PARSE *in_parse, SPF_PARSE *out_parse,
	char *error_text)
#else
int SPF_GetSubParse(in_parse, out_parse, error_text)
const SPF_PARSE *in_parse;
SPF_PARSE       *out_parse;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = SPF_SUCCESS;
	unsigned int   in_length;
	unsigned long  out_line;
	char          *tmp_ptr_1;
	char          *tmp_ptr_2;
	SPF_PARSE      tmp_parse;
	char           tmp_error_text[SPF_MAX_ERROR_TEXT];

	in_length = in_parse->length;
	out_line  = in_parse->line;
	tmp_ptr_1 = in_parse->text;
	tmp_ptr_2 = tmp_ptr_1 + (in_parse->length - 1);

	SPF_INIT_Parse(out_parse);

	while (in_length) {
		while (isspace(*tmp_ptr_1) && in_length) {
			out_line += ((unsigned long) ((*tmp_ptr_1 == '\n') ? 1 : 0));
			in_length--;
			tmp_ptr_1++;
		}
		if (*tmp_ptr_1 == '#') {
			while (*tmp_ptr_1 && (*tmp_ptr_1 != '\n') && in_length) {
				in_length--;
				tmp_ptr_1++;
			}
			if (*tmp_ptr_1 == '\n') {
				out_line++;
				in_length--;
				tmp_ptr_1++;
			}
			continue;
		}
		if ((*tmp_ptr_1 == '(') || (!in_length))
			break;
		in_length--;
		tmp_ptr_1++;
	}

	if ((*tmp_ptr_1 != '(') || (!in_length)) {
		tmp_parse      = *in_parse;
		tmp_parse.line = out_line;
		strcpy(error_text,
			"No opening parenthesis in definition item beginning ");
		chrcat(SPF_GetLocationLineFile(&tmp_parse, 500,
			error_text + strlen(error_text)), '.');
		return_code = SPF_PARSE_FAILURE;
	}
	else if (*tmp_ptr_2 != ')') {
		tmp_parse      = *in_parse;
		tmp_parse.line = out_line;
		strcpy(error_text,
			"No terminating parenthesis in definition item beginning ");
		chrcat(SPF_GetLocationLineFile(&tmp_parse, 500,
			error_text + strlen(error_text)), '.');
		return_code = SPF_PARSE_FAILURE;
	}
	else {
		tmp_ptr_1++;
		tmp_ptr_2--;
		while (isspace(*tmp_ptr_1)) {
			out_line += ((unsigned long) ((*tmp_ptr_1 == '\n') ? 1 : 0));
			tmp_ptr_1++;
		}
		while (isspace(*tmp_ptr_2) && (tmp_ptr_2 > tmp_ptr_1))
			tmp_ptr_2--;
		if (tmp_ptr_2 < tmp_ptr_1) {
			tmp_parse      = *in_parse;
			tmp_parse.line = out_line;
			strcpy(error_text,
		"Empty definition inside parenthesis in definition item beginning ");
			chrcat(SPF_GetLocationLineFile(&tmp_parse, 500,
				error_text + strlen(error_text)), '.');
			return_code = SPF_PARSE_FAILURE;
		}
		else if (!in_parse->flags) {
			out_parse->file   = in_parse->file;
			out_parse->line   = out_line;
			out_parse->length = ((unsigned int) (tmp_ptr_2 - tmp_ptr_1)) + 1;
			out_parse->text   = tmp_ptr_1;
			out_parse->flags  = SPF_FALSE;
		}
		else if ((out_parse->text = strndup(tmp_ptr_1,
			((unsigned int) (tmp_ptr_2 - tmp_ptr_1)) + 1)) == NULL) {
			tmp_parse        = *in_parse;
			tmp_parse.line   = out_line;
			tmp_parse.text   = tmp_ptr_1;
			tmp_parse.length = ((unsigned int) (tmp_ptr_2 - tmp_ptr_1)) + 1;
			STR_AllocMsgItem(((unsigned int) (tmp_ptr_2 - tmp_ptr_1)) + 1 + 1,
				error_text, "%s beginning %s ('%-.*s')",
				"Unable to allocate memory for the definition sub-item",
				SPF_GetLocationLineFile(&tmp_parse, 500, tmp_error_text),
				(tmp_parse.length > 500) ? 500 : ((int) tmp_parse.length),
				tmp_parse.text);
			return_code = SPF_MEMORY_FAILURE;
		}
		else {
			out_parse->file   = in_parse->file;
			out_parse->line   = out_line;
			out_parse->length = ((unsigned int) (tmp_ptr_2 - tmp_ptr_1)) + 1;
			out_parse->flags  = SPF_TRUE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

