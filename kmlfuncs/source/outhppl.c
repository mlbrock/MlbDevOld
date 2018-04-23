/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Outputs matched string in HPPL (Hewlett Packard
								Printer Language) format.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2018.
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

#include <sdtif.h>
#include <genfuncs.h>

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
#define KML_HPPL_DATA_WIDTH				198
#define KML_HPPL_DATA_LENGTH				 89

#if 0
#define KML_HPPL_LINE_VBAR					179
#define KML_HPPL_LINE_HBAR					196
#define KML_HPPL_LINE_ULCORN				218
#define KML_HPPL_LINE_URCORN				191
#define KML_HPPL_LINE_LLCORN				192
#define KML_HPPL_LINE_LRCORN				217
#define KML_HPPL_LINE_UTEE					194
#define KML_HPPL_LINE_LTEE					193
#else
#define KML_HPPL_LINE_VBAR					186
#define KML_HPPL_LINE_HBAR					205
#define KML_HPPL_LINE_ULCORN				201
#define KML_HPPL_LINE_URCORN				187
#define KML_HPPL_LINE_LLCORN				200
#define KML_HPPL_LINE_LRCORN				188
#define KML_HPPL_LINE_UTEE					203
#define KML_HPPL_LINE_LTEE					202
#endif /* #if 0 */
	  
typedef struct {
	unsigned int  data_width;
	unsigned int  data_length;
	unsigned int  data_center;
	unsigned int  header_line;
	unsigned int  footer_line;
	unsigned int  first_line;
	unsigned int  each_width;
	unsigned int  page_margin;
	unsigned int  page_width;
	unsigned int  page_length;
	unsigned int  current_page;
	unsigned int  current_line;
	unsigned int  current_col;
	const char   *file_name;  
	char          print_date[128];
	char          header[(KML_HPPL_DATA_WIDTH * 2) + 1];
} KML_HPPL;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes for static functions . . .								*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void KML_EmitHPPL, (KML_HPPL *hppl_ptr,
	const char *html_ptr, unsigned int html_length, unsigned int tab_setting,
	const char *leading_text, const char *trailing_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void KML_DoNewHPPLLine, (KML_HPPL *hppl_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void KML_DoNewHPPLPage, (KML_HPPL *hppl_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void KML_DoHPPLPageHeader, (KML_HPPL *hppl_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void KML_DoHPPLPageFooter, (KML_HPPL *hppl_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void KML_DoHPPLOutputEnd, (KML_HPPL *hppl_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void KML_MakeHeader, (KML_HPPL *hppl_ptr));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		RESET PRINTER COMMAND														*/
	/*		CLEAR MARGIN																	*/
	/*		PUSH POSITION																	*/
	/*		PRIMARY SYMBOL SET    = IBM-PC (USA)									*/
	/*		PRIMARY SPACING       = FIXED												*/
	/*		PRIMARY STYLE         = UPRIGHT											*/
	/*		PRIMARY STROKE WEIGHT = MEDIUM											*/
	/*		UNDERLINE             = OFF												*/
	/*		END-OF-LINE-WRAP      = DISABLED											*/
	/*		NUMBER OF COPIES      = 1													*/
	/*		PERFORATION SKIP      = ENABLED											*/
	/*		LINE TERMINATION      = CR=CR, LF=LF, and FF=FF						*/
	/*		POP POSITION																	*/
	/*	*****************************************************************	*/
/*
#define KML_HPPL_INIT						\
	"\033E\0339\033&f0S\033&l2A\033&l1O\033(10U\033(s0P\033(s0S\033(s0B\033&d@\033&s1C\033&l1X\033&l1L\033&k0G\033(s19H\033(s3T\033&l12D\033&f1S"
*/
#define KML_HPPL_INIT						\
	"\033E\033\071\033&f0S\033&l2A\033&l1O\033(10U\033(s0P\033(s0S\033(s0B\033&d@\033&s1C\033&l1X\033&l1L\033&k0G\033(s19H\033(s3T\033&l12D\033&f1S"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void KML_OutputHPPL(KML_CONTROL *control_ptr, const char *file_name,
	long file_time, unsigned int tab_setting, const char *in_string,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void KML_OutputHPPL(control_ptr, file_name, file_time, tab_setting, in_string,
	output_function, output_control)
KML_CONTROL           *control_ptr;
const char            *file_name;
long                   file_time;
unsigned int           tab_setting;
const char            *in_string;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	const char      *in_ptr;
	unsigned int     in_length;
	unsigned int     tmp_length;
	const KML_MATCH *match_ptr;
	const KML_MATCH *old_match_ptr;
	const char      *leading_text  = "";
	const char      *trailing_text = "";
	KML_HPPL         hppl_data;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	memset(&hppl_data, '\0', sizeof(hppl_data));

	hppl_data.data_width   = (KML_HPPL_DATA_WIDTH % 2) ?
		KML_HPPL_DATA_WIDTH : (KML_HPPL_DATA_WIDTH - 1);
	hppl_data.data_length  = KML_HPPL_DATA_LENGTH;
	hppl_data.data_center  = (hppl_data.data_width / 2) + 1;
	hppl_data.header_line  = 2;
	hppl_data.footer_line  = hppl_data.data_length - 1;
	hppl_data.first_line   = hppl_data.header_line + 2;
	hppl_data.each_width   = hppl_data.data_center - 1;
	hppl_data.page_margin  = 2;
	hppl_data.page_width   = hppl_data.each_width - (hppl_data.page_margin * 2);
	hppl_data.page_length  = hppl_data.data_length - 
		((hppl_data.data_length - hppl_data.footer_line) + 1 +
		hppl_data.header_line + 1 + 1 + 1);
	hppl_data.current_page = 0;
	hppl_data.current_line = 0;
	hppl_data.current_col  = 0;
	hppl_data.file_name    = ((file_name != NULL) && *file_name) ?
		file_name : "<stdin>";
	SDTIF_Format_time_t(&file_time, hppl_data.print_date);

	KML_MakeHeader(&hppl_data);

	KML_EmitHPPL(&hppl_data, "", 0, tab_setting, "", "", output_function,
		output_control);

	if (!(*in_string))
		goto EXIT_FUNCTION;

	in_ptr    = in_string;
	in_length = strlen(in_string);
	match_ptr = control_ptr->match_list;

	while (*in_ptr) {
		if (match_ptr == NULL) {
			KML_EmitHPPL(&hppl_data, in_ptr, in_length, tab_setting,
				leading_text, trailing_text, output_function, output_control);
			break;
		}
		else if (in_ptr < match_ptr->ptr) {
			KML_EmitHPPL(&hppl_data, in_ptr,
				tmp_length = ((unsigned int) (match_ptr->ptr - in_ptr)),
				tab_setting, leading_text, trailing_text, output_function,
				output_control);
			in_ptr    += tmp_length;
			in_length -= tmp_length;
		}                                      
		else {
			switch (match_ptr->type) {
				case KML_TYPE_STRING		:
					leading_text  = "\033&d0D";
					trailing_text = "\033&d@";
					break;                
				case KML_TYPE_COMMENT	:
					leading_text  = "\033(s1S";
					trailing_text = "\033(s0S";
					break;
				case KML_TYPE_KEYWORD	:
					leading_text  = "\033(s3B";
					trailing_text = "\033(s0B";
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
			KML_EmitHPPL(&hppl_data, match_ptr->ptr, match_ptr->length,
				tab_setting, leading_text, trailing_text, output_function,
				output_control);
			(*output_function)(output_control, "%s", trailing_text);
			leading_text   = "";
			trailing_text  = "";
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

EXIT_FUNCTION:

	KML_DoHPPLOutputEnd(&hppl_data, output_function, output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void KML_EmitHPPL(KML_HPPL *hppl_ptr, const char *in_ptr,
	unsigned int in_length, unsigned int tab_setting, const char *leading_text,
	const char *trailing_text, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void KML_EmitHPPL(hppl_ptr, in_ptr, in_length, tab_setting,
	leading_text, trailing_text, output_function, output_control)
KML_HPPL              *hppl_ptr;
const char            *in_ptr;
unsigned int           in_length;
unsigned int           tab_setting;
const char            *leading_text;
const char            *trailing_text;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int space_count;
	unsigned int space_length;
	unsigned int eol_char_count;
	char         tab_buffer[512];

	if (!hppl_ptr->current_page)
		KML_DoNewHPPLPage(hppl_ptr, output_function, output_control);

	while (in_length && *in_ptr) {
		if ((eol_char_count = STRFUNCS_MEMPTR_IS_EOL(in_ptr, in_length)) > 0) {
			in_ptr    += eol_char_count - 1;
			in_length -= eol_char_count - 1;
			(*output_function)(output_control, "%s", trailing_text);
			KML_DoNewHPPLLine(hppl_ptr, output_function, output_control);
			(*output_function)(output_control, "%s", leading_text);
		}                                                  
		else if (*in_ptr == '\f')
			KML_DoNewHPPLPage(hppl_ptr, output_function, output_control);
		else {
			if (hppl_ptr->current_col == (hppl_ptr->page_width - 1)) {
				(*output_function)(output_control, "%s", trailing_text);
				KML_DoNewHPPLLine(hppl_ptr, output_function, output_control);
				(*output_function)(output_control, "%s", leading_text);
			}  
			else if (*in_ptr == '\t') {
				if (tab_setting) {
					space_count =
						tab_setting - (hppl_ptr->current_col % tab_setting);
					while (space_count) {
						space_length = (space_count < sizeof(tab_buffer)) ?
							space_count : (sizeof(tab_buffer) - 1);
						memset(tab_buffer, ' ', space_length);
						KML_EmitHPPL(hppl_ptr, tab_buffer, space_length,
							tab_setting, leading_text, trailing_text,
							output_function, output_control);
						space_count -= space_length;
					}     
				}
			}
			else if (*in_ptr < '\040') {                                  
				(*output_function)(output_control, "\033&p1X%c", *in_ptr);
				hppl_ptr->current_col++;
			}
			else {
				(*output_function)(output_control, "%c", *in_ptr);
				hppl_ptr->current_col++;
			}
		}
		in_ptr++;               
		in_length--;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void KML_DoNewHPPLLine(KML_HPPL *hppl_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void KML_DoNewHPPLLine(hppl_ptr, output_function, output_control)
KML_HPPL              *hppl_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	if ((hppl_ptr->current_line + 1) == hppl_ptr->page_length) {
		KML_DoNewHPPLPage(hppl_ptr, output_function, output_control);
		hppl_ptr->current_line = 0;
		hppl_ptr->current_col  = 0;
	}                                   
	else {
		hppl_ptr->current_line++;
		(*output_function)(output_control, "\033&a%uR\033&a%uC",
			hppl_ptr->header_line + 2 + hppl_ptr->current_line,
			(hppl_ptr->current_page % 2) ? hppl_ptr->page_margin :
			(hppl_ptr->each_width + hppl_ptr->page_margin));
		hppl_ptr->current_col = 0;
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void KML_DoNewHPPLPage(KML_HPPL *hppl_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void KML_DoNewHPPLPage(hppl_ptr, output_function, output_control)
KML_HPPL              *hppl_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	if (!hppl_ptr->current_page) {
		(*output_function)(output_control, "%s", KML_HPPL_INIT);
		KML_DoHPPLPageHeader(hppl_ptr, output_function, output_control);
	}                    
	else {
		if (!(hppl_ptr->current_page % 2)) {
			KML_DoHPPLPageFooter(hppl_ptr, output_function, output_control);
			(*output_function)(output_control, "\f");
			KML_DoHPPLPageHeader(hppl_ptr, output_function, output_control);
		}                                
	}

	hppl_ptr->current_line = 0;
	hppl_ptr->current_col  = 0;

	(*output_function)(output_control, "\033&a%uR\033&a%uC",
		hppl_ptr->header_line + 2,
		(++hppl_ptr->current_page % 2) ? hppl_ptr->page_margin :
		(hppl_ptr->each_width + hppl_ptr->page_margin));
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void KML_DoHPPLPageHeader(KML_HPPL *hppl_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void KML_DoHPPLPageHeader(hppl_ptr, output_function, output_control)
KML_HPPL              *hppl_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	(*output_function)(output_control, "\033&a%uR\033&a0C",
		hppl_ptr->header_line);
	(*output_function)(output_control, "%s", hppl_ptr->header);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void KML_DoHPPLPageFooter(KML_HPPL *hppl_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void KML_DoHPPLPageFooter(hppl_ptr, output_function, output_control)
KML_HPPL              *hppl_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	char         horizontal[KML_HPPL_DATA_WIDTH];

	memset(horizontal, KML_HPPL_LINE_HBAR, sizeof(horizontal));
	horizontal[sizeof(horizontal) - 1] = '\0';

	/*
		*********************************************************
		Draw the upper horizontal bar . . .
	*/
	(*output_function)(output_control, "\033&a%uR\033&a0C",
		hppl_ptr->header_line + 1);
	(*output_function)(output_control, "%c%-*.*s", KML_HPPL_LINE_ULCORN,
		hppl_ptr->each_width - 1,
		hppl_ptr->each_width - 1, horizontal);
	if (hppl_ptr->current_page % 2)
		(*output_function)(output_control, "%c", KML_HPPL_LINE_URCORN);
	else
		(*output_function)(output_control, "%c%-*.*s%c", KML_HPPL_LINE_UTEE,
			hppl_ptr->each_width - 1,
			hppl_ptr->each_width - 1, horizontal, KML_HPPL_LINE_URCORN);

	/*
		*********************************************************
		Draw the lower horizontal bar . . .
	*/
	(*output_function)(output_control, "\033&a%uR\033&a0C",
		hppl_ptr->footer_line - 2);
	(*output_function)(output_control, "%c%-*.*s", KML_HPPL_LINE_LLCORN,
		hppl_ptr->each_width - 1,
		hppl_ptr->each_width - 1, horizontal);
	if (hppl_ptr->current_page % 2)
		(*output_function)(output_control, "%c", KML_HPPL_LINE_LRCORN);
	else
		(*output_function)(output_control, "%c%-*.*s%c", KML_HPPL_LINE_LTEE,
			hppl_ptr->each_width - 1,
			hppl_ptr->each_width - 1, horizontal, KML_HPPL_LINE_LRCORN);

	/*
		*********************************************************
		Draw the vertical bars . . .
	*/
	for (count_1 = hppl_ptr->first_line;
		count_1 < (hppl_ptr->footer_line - 2); count_1++) {
		(*output_function)(output_control, "\033&a%uR\033&a%uC%c",
			count_1, 0, KML_HPPL_LINE_VBAR);
		(*output_function)(output_control, "\033&a%uR\033&a%uC%c",
			count_1, hppl_ptr->data_center - 1, KML_HPPL_LINE_VBAR);
		if (!(hppl_ptr->current_page % 2))
			(*output_function)(output_control, "\033&a%uR\033&a%uC%c",
				count_1, hppl_ptr->data_width - 1, KML_HPPL_LINE_VBAR);
	}

	(*output_function)(output_control, "\033&a87R\033&a0C");
	if (hppl_ptr->current_page % 2)
		(*output_function)(output_control, "\033(s7BPage: %11u\033(s0B",
			hppl_ptr->current_page);
	else
		(*output_function)(output_control,
			"\033(s7BPage: %11u%-*.*sPage: %11u\033(s0B",
			hppl_ptr->current_page - 1,
			hppl_ptr->data_width - (6 + 11 + 6 + 11),
			hppl_ptr->data_width - (6 + 11 + 6 + 11), " ",
			hppl_ptr->current_page);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void KML_DoHPPLOutputEnd(KML_HPPL *hppl_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void KML_DoHPPLOutputEnd(hppl_ptr, output_function, output_control)
KML_HPPL              *hppl_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	KML_DoHPPLPageFooter(hppl_ptr, output_function, output_control);
	(*output_function)(output_control, "\033E");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void KML_MakeHeader(KML_HPPL *hppl_ptr)
#else
static void KML_MakeHeader(hppl_ptr)
KML_HPPL *hppl_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int max_file_name_length;
	unsigned int file_name_length;

	max_file_name_length = hppl_ptr->data_width -
		(6 + 1 + 6 + strlen(hppl_ptr->print_date));
	file_name_length     = strlen(hppl_ptr->file_name);

	if (file_name_length <= max_file_name_length)
		sprintf(hppl_ptr->header,
			"\033(s3BFile: %-*.*s Date: %s\033(s0B",
			((int) max_file_name_length), ((int) max_file_name_length),
			hppl_ptr->file_name, hppl_ptr->print_date);
	else
		sprintf(hppl_ptr->header,
			"\033(s3BFile: %-*.*s%s Date: %s\033(s0B",
			((int) max_file_name_length) - 3, ((int) max_file_name_length) - 3,
			hppl_ptr->file_name, "\033(s0B\033(s1S???\033(s0S\033(s3B",
			hppl_ptr->print_date);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>

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
	struct stat       stat_data;
	char              error_text[KMLFUNCS_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'KML_OutputHPPL()'\n");
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
			if (stat(argv[count_1], &stat_data) != 0) {
				sprintf(error_text, "Unable to 'stat()' file '%-500s': ",
					argv[count_1]);
				GEN_AppendLastErrorString(0, KML_MAX_ERROR_TEXT - 1,
					error_text);
				return_code = KML_SYSTEM_FAILURE;
				break;
			}
			if ((domain_ptr != NULL) && ((return_code =
				KML_MatchAll(&control_data, domain_ptr, file_buffer,
				KML_TYPE_STRING | KML_TYPE_COMMENT | KML_TYPE_KEYWORD,
				error_text)) != KMLFUNCS_SUCCESS))
				break;
			KML_OutputHPPL(&control_data, argv[count_1], stat_data.st_mtime, 3,
				file_buffer, NULL, NULL);
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

