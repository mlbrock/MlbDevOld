/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs matched string in HTML format.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for static functions . . .								*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void KML_EmitHTML, (const char *in_ptr,
	unsigned int in_length, unsigned int tab_setting, unsigned int *current_col,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void KML_OutputHTML(KML_CONTROL *control_ptr, const char *file_name,
	unsigned int tab_setting, const char *in_string,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void KML_OutputHTML(control_ptr, file_name, tab_setting, in_string,
	output_function, output_control)
KML_CONTROL           *control_ptr;
const char            *file_name;
unsigned int           tab_setting;
const char            *in_string;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int     current_col = 0;
	const char      *in_ptr;
	unsigned int     in_length;
	unsigned int     tmp_length;
	const KML_MATCH *match_ptr;
	const KML_MATCH *old_match_ptr;
	const char      *leading_text;
	const char      *trailing_text;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	(*output_function)(output_control, "<HTML>\n");
	(*output_function)(output_control, "<HEAD>\n");
	if ((file_name != NULL) && *file_name) {
		(*output_function)(output_control, "<TITLE>");
		KML_EmitHTML(file_name, strlen(file_name), tab_setting, &current_col,
			output_function, output_control);
		(*output_function)(output_control, "</TITLE>\n");
	}
	(*output_function)(output_control, "</HEAD>\n");
	(*output_function)(output_control, "<BODY>\n");
	(*output_function)(output_control, "<PRE WIDTH=80>");

	in_ptr      = in_string;
	in_length   = strlen(in_string);
	match_ptr   = control_ptr->match_list;
	current_col = 0;

	while (*in_ptr) {
		if (match_ptr == NULL) {
			KML_EmitHTML(in_ptr, in_length, tab_setting, &current_col,
				output_function, output_control);
			break;
		}
		else if (in_ptr < match_ptr->ptr) {
			KML_EmitHTML(in_ptr,
				tmp_length = ((unsigned int) (match_ptr->ptr - in_ptr)),
				tab_setting, &current_col, output_function, output_control);
			in_ptr    += tmp_length;
			in_length -= tmp_length;
		}                                      
		else {
			switch (match_ptr->type) {
				case KML_TYPE_STRING		:
					leading_text  = "<FONT COLOR=#0000FF>";
					trailing_text = "<FONT COLOR=#000000>";
					break;                
				case KML_TYPE_COMMENT	:
					leading_text  = "<FONT COLOR=#000080><I>";
					trailing_text = "</I><FONT COLOR=#000000>";
					break;
				case KML_TYPE_KEYWORD	:
					leading_text  = "<B>";
					trailing_text = "</B>";
					break;
				case KML_TYPE_SYMBOL		:
					leading_text  = "";
					trailing_text = "";
					break;
				case KML_TYPE_BLOCK		:
					leading_text  = "";
					trailing_text = "";
					break;
				case KML_TYPE_NAME		:
					leading_text  = "";
					trailing_text = "";
					break;
				case KML_TYPE_NUMBER		:
					leading_text  = "";
					trailing_text = "";
					break;
				case KML_TYPE_OPERATOR	:
					leading_text  = "";
					trailing_text = "";
					break;
				default						:
					leading_text  = "";
					trailing_text = "";
					break;
			}
			(*output_function)(output_control, "%s", leading_text);
			KML_EmitHTML(match_ptr->ptr, match_ptr->length, tab_setting,
				&current_col, output_function, output_control);
			(*output_function)(output_control, "%s", trailing_text);
			in_ptr        += match_ptr->length;
			in_length     -= match_ptr->length;
			old_match_ptr  = match_ptr;
			/*
				Just in case matches are contained within other matches.
			*/
			while ((match_ptr == old_match_ptr) || ((match_ptr != NULL) &&
				(match_ptr->ptr < (old_match_ptr->ptr + old_match_ptr->length))))
				match_ptr  = (match_ptr <
					(control_ptr->match_list + (control_ptr->match_count - 1))) ?
					(match_ptr + 1) : NULL;
		}
	}

	(*output_function)(output_control, "</PRE>\n");
	(*output_function)(output_control, "</BODY>\n");
	(*output_function)(output_control, "</HTML>\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void KML_EmitHTML(const char *in_ptr, unsigned int in_length,
	unsigned int tab_setting, unsigned int *current_col,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void KML_EmitHTML(in_ptr, in_length, tab_setting, current_col,
	output_function, output_control)
const char            *in_ptr;
unsigned int           in_length;
unsigned int           tab_setting;
unsigned int          *current_col;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int space_count;

	while (*in_ptr && in_length) {
		if (*in_ptr == '\"') {
			(*output_function)(output_control, "&quot;");
			(*current_col)++;
		}
		else if (*in_ptr == '&') {
			(*output_function)(output_control, "&amp;");
			(*current_col)++;
		}
		else if (*in_ptr == '<') {
			(*output_function)(output_control, "&lt;");
			(*current_col)++;
		}
		else if (*in_ptr == '>') {
			(*output_function)(output_control, "&gt;");
			(*current_col)++;
		}
		else if (*in_ptr == '\t') {
			if (tab_setting) {
				space_count   = tab_setting - (*current_col % tab_setting);
				*current_col += space_count;
				while (space_count--)
					(*output_function)(output_control, " ");
			}
		}
		else if ((*in_ptr == '\n') || (*in_ptr == '\r')) {
			if ((*in_ptr == '\r') && ((in_length > 1) &&
				(*(in_ptr + 1) == '\n'))) {
				in_ptr++;
				in_length--;
			}
			*current_col = 0;
			(*output_function)(output_control, "\n");
		}
		else {
			(*output_function)(output_control, "%c", *in_ptr);
			(*current_col)++;
		}
		in_ptr++;               
		in_length--;
	}
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int               return_code;
	unsigned int      count_1;
	KML_CONTROL       control_data;
	const KML_DOMAIN *domain_ptr;
	const char       *file_type;
	char             *file_buffer;
	char              error_text[KMLFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'KML_OutputHTML()'\n");
	fprintf(stderr, "---- ------- --- ------------------\n\n");

	if (argc == 1) {
		sprintf(error_text, "USAGE:\n   %s <source-file> [<source-file> ...]",
			argv[0]);
		return_code = KMLFUNCS_BAD_ARGS_FAILURE;
	}
	else if ((return_code = KML_TEST_InitializeControl(&control_data,
		error_text)) == KMLFUNCS_SUCCESS) {
		for (count_1 = 1; count_1 < ((unsigned int) argc); count_1++) {
			if (((file_type = strrchr(argv[count_1], '.')) != NULL) &&
				*file_type)
				fprintf(stderr, "File: %s (using extension '%s')",
					argv[count_1], ++file_type);
			else
				fprintf(stderr, "File: %s (no extension, using '%s')",
					argv[count_1], file_type = "c");
			if ((domain_ptr = KML_FIND_ControlDomainByType(&control_data,
				file_type)) == NULL)
				fprintf(stderr,
					": Unable to locate a domain for file extension '%s'.",
					file_type);
			else
				fprintf(stderr, ": Found domain name '%s', description '%s'.\n",
					domain_ptr->domain_name, domain_ptr->domain_description);
			if ((return_code = KML_TFREAD_ReadFileBuffer(argv[count_1], NULL,
				&file_buffer, error_text)) != KMLFUNCS_SUCCESS)
				break;
			if ((domain_ptr != NULL) && ((return_code =
				KML_MatchAll(&control_data, domain_ptr, file_buffer,
				KML_TYPE_STRING | KML_TYPE_COMMENT | KML_TYPE_KEYWORD,
				error_text)) != KMLFUNCS_SUCCESS))
				break;
			KML_OutputHTML(&control_data, argv[count_1], 3, file_buffer,
				NULL, NULL);
			free(file_buffer);
			KML_ClearMatchList(&control_data);
		}              
		KML_FREE_Control(&control_data);
	}

	if (return_code != KMLFUNCS_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

