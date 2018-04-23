/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits an ADF entry in 'ASCII' format.

	Revision History	:	1995-05-28 --- Creation.
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

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(int ADF_ASCII_OutputBasic,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int ADF_ASCII_OutputSection,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	int format_flag, unsigned int in_next_line_pad,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DECL const ADF_AREA ADF_AreaNameList[];
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_ASCII_OutputByEntry(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, char *error_text)
#else
int ADF_ASCII_OutputByEntry(control_ptr, entry_ptr, error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	unsigned int   alloc_length;
	ADF_ENTRY_DATA entry_data_list[ADF_AREA_COUNT];

	if (control_ptr->quiet_flag != ADF_TRUE)
		fprintf(stderr, "%s(%s) --- ", entry_ptr->base_name,
			entry_ptr->file_name);

	alloc_length = ((control_ptr->output_dir == NULL) ? 0 :
		strlen(control_ptr->output_dir)) + strlen(entry_ptr->base_name) + 256;

	if ((return_code = ADF_OUT_AllocFileString(control_ptr, alloc_length,
		error_text)) == ADF_SUCCESS) {
		sprintf(control_ptr->output_file_name, "%s%s%s.txt",
			(control_ptr->output_dir == NULL) ? "" : control_ptr->output_dir,
			(control_ptr->output_dir == NULL) ? "" : "/", entry_ptr->base_name);
		ADF_OUT_CleanName(control_ptr->output_file_name);
		if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
			error_text)) == ADF_SUCCESS) {
			if ((return_code = ADF_GetEntry(control_ptr, entry_ptr,
				entry_data_list, error_text)) == ADF_SUCCESS) {
				return_code = ADF_ASCII_OutputBasic(control_ptr, entry_ptr,
					entry_data_list, STR_FUNC_TYPE_fprintf_CAST(fprintf),
					control_ptr->output_file_ptr, error_text);
				ADF_INIT_AreaDataList(entry_data_list);
			}
			fclose(control_ptr->output_file_ptr);
			control_ptr->output_file_ptr = NULL;
			if ((control_ptr->log_flag == ADF_TRUE) &&
				(return_code == ADF_SUCCESS))
				ADF_OUT_LogOutputFile(control_ptr, entry_ptr,
					control_ptr->output_file_name);
		}
	}

	if (control_ptr->quiet_flag != ADF_TRUE) {
		if (return_code != ADF_SUCCESS)
			fprintf(stderr, "ERROR: %s\n", error_text);
		else
			fprintf(stderr, "OK\n");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_ASCII_OutputToStdout(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text)
#else
int ADF_ASCII_OutputToStdout(control_ptr, entry_ptr, output_date, error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
const time_t    *output_date;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code;
	ADF_ENTRY_DATA entry_data_list[ADF_AREA_COUNT];

	if (control_ptr->quiet_flag != ADF_TRUE)
		fprintf(stderr, "%s(%s) --- ", entry_ptr->base_name,
			entry_ptr->file_name);

	if ((return_code = ADF_GetEntry(control_ptr, entry_ptr, entry_data_list,
		error_text)) == ADF_SUCCESS) {
		return_code = ADF_ASCII_OutputBasic(control_ptr, entry_ptr,
			entry_data_list, STR_FUNC_TYPE_fprintf_CAST(fprintf), stdout,
			error_text);
		ADF_INIT_AreaDataList(entry_data_list);
		if ((control_ptr->log_flag == ADF_TRUE) && (return_code == ADF_SUCCESS))
			ADF_OUT_LogOutputFile(control_ptr, entry_ptr, NULL);
	}

	if (control_ptr->quiet_flag != ADF_TRUE) {
		if (return_code != ADF_SUCCESS)
			fprintf(stderr, "ERROR: %s\n", error_text);
		else
			fprintf(stderr, "OK\n");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_ASCII_OutputByFile(ADF_CONTROL *control_ptr, unsigned int *entry_index,
	char *error_text)
#else
int ADF_ASCII_OutputByFile(control_ptr, entry_index, error_text)
ADF_CONTROL  *control_ptr;
unsigned int *entry_index;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code = ADF_SUCCESS;
	char           *core_name;
	unsigned int    in_entry_index;
	unsigned int    alloc_length;
	ADF_ENTRY      *entry_ptr;
	ADF_ENTRY_DATA  entry_data_list[ADF_AREA_COUNT];

	in_entry_index = *entry_index;
	entry_ptr      = control_ptr->in_entry_order_list[*entry_index];
	core_name      = entry_ptr->core_name;

	alloc_length   = ((control_ptr->output_dir == NULL) ? 0 :
		strlen(control_ptr->output_dir)) + strlen(core_name) + 256;

	for ( ; (*entry_index < control_ptr->in_entry_order_count) &&
		(!strcmp(control_ptr->in_entry_order_list[*entry_index]->core_name,
		core_name)); (*entry_index)++) {
		entry_ptr = control_ptr->in_entry_order_list[*entry_index];
		if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr, "%s(%s) --- ", entry_ptr->file_name,
				entry_ptr->base_name);
		if (*entry_index == in_entry_index) {
			if ((return_code = ADF_OUT_AllocFileString(control_ptr, alloc_length,
				error_text)) != ADF_SUCCESS)
				break;
			sprintf(control_ptr->output_file_name, "%s%s%s.txt",
				(control_ptr->output_dir == NULL) ? "" : control_ptr->output_dir,
				(control_ptr->output_dir == NULL) ? "" : "/", core_name);
			ADF_OUT_CleanName(control_ptr->output_file_name);
			if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
				error_text)) != ADF_SUCCESS)
				break;
		}
		if ((return_code = ADF_GetEntry(control_ptr, entry_ptr, entry_data_list,
			error_text)) != ADF_SUCCESS)
			break;
		return_code = ADF_ASCII_OutputBasic(control_ptr, entry_ptr,
			entry_data_list, STR_FUNC_TYPE_fprintf_CAST(fprintf),
			control_ptr->output_file_ptr, error_text);
		ADF_INIT_AreaDataList(entry_data_list);
		if (return_code != ADF_SUCCESS)
			break;
		if (control_ptr->quiet_flag != ADF_TRUE)
			fprintf(stderr, "OK\n");
		if ((control_ptr->log_flag == ADF_TRUE) && (return_code == ADF_SUCCESS))
			ADF_OUT_LogOutputFile(control_ptr, entry_ptr,
				control_ptr->output_file_name);
	}

	if (control_ptr->output_file_ptr != NULL) {
		fclose(control_ptr->output_file_ptr);
		control_ptr->output_file_ptr = NULL;
	}

	if ((control_ptr->quiet_flag != ADF_TRUE) && (return_code != ADF_SUCCESS))
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_ASCII_OutputBasic(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_ASCII_OutputBasic(control_ptr, entry_ptr, entry_data_list,
	output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code = ADF_SUCCESS;
	unsigned int     count_1;
	ADF_ENTRY_DATA  *entry_data_ptr;
	const ADF_AREA  *area_ptr;
	char             area_name[ADF_AREA_NAME_LENGTH + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Order the sections of the entry as specified . . .					*/
	/*	*****************************************************************	*/
	if (control_ptr->area_order_type != ADF_AREA_ORDER_TYPE_INTERNAL)
		ADF_SORT_EntrySections(control_ptr->area_order_type, entry_data_list);
	/*	*****************************************************************	*/

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		entry_data_ptr = entry_data_list + count_1;
		area_ptr       = ADF_AreaNameList + entry_data_ptr->area_index;
		if ((area_ptr->output_flag != ADF_TRUE) ||
			(!entry_data_ptr->para_count))
			continue;
		ADF_GetOutputAreaName(control_ptr->area_name_type,
			entry_data_ptr->area_index, control_ptr->area_name_list,
			entry_data_ptr->section_name, sizeof(area_name) - 1, area_name);
		(*output_function)(output_control, "%s\n", area_name);
		if (entry_data_ptr->area_index == ADF_AREA_CODE_SYNTAX) {
			STR_EMIT_Char(' ', ADF_MAN_MARGIN_PADDING, output_function,
				output_control);
			STR_EMIT_CharLine('-', 80 - (ADF_MAN_MARGIN_PADDING + 2),
				output_function, output_control);
			if ((return_code = ADF_ASCII_OutputSection(control_ptr, entry_ptr,
				entry_data_ptr, ADF_FALSE, 3, output_function, output_control,
				error_text)) != ADF_SUCCESS)
				break;
			STR_EMIT_Char(' ', ADF_MAN_MARGIN_PADDING, output_function,
				output_control);
			STR_EMIT_CharLine('-', 80 - (ADF_MAN_MARGIN_PADDING + 2),
				output_function, output_control);
			(*output_function)(output_control, "\n");
		}
		else if (entry_data_ptr->area_index == ADF_AREA_SEE_ALSO) {
			if ((return_code = ADF_ASCII_OutputSection(control_ptr, entry_ptr,
				entry_data_ptr, ADF_FALSE, 0, output_function, output_control,
				error_text)) != ADF_SUCCESS)
				break;
			(*output_function)(output_control, "\n");
		}
		else {
			if ((return_code = ADF_ASCII_OutputSection(control_ptr, entry_ptr,
				entry_data_ptr, area_ptr->pformat_flag, 0, output_function,
				output_control, error_text)) != ADF_SUCCESS)
				break;
			if (area_ptr->pformat_flag != ADF_TRUE)
				(*output_function)(output_control, "\n");
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_ASCII_OutputSection(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	int format_flag, unsigned int in_next_line_pad,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_ASCII_OutputSection(control_ptr, entry_ptr, entry_data_ptr,
	format_flag, in_next_line_pad, output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_ptr;
int                    format_flag;
unsigned int           in_next_line_pad;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	unsigned int   count_1;
	unsigned int   count_2;
	unsigned int   margin_width;
	unsigned int   added_margin;
	unsigned int   line_width_1;
	unsigned int   line_width_2;
	unsigned int   next_line_pad;
	int            cformat_flag;
   int            strip_flag;
	int            begin_rule_flag;
	int            end_rule_flag;
	int            current_col;
	int            tab_count;
	char           last_char;
	ADF_PARA_DATA *para_ptr;
	unsigned int   para_line_count;
	char          *primary_leader;
	const char    *tmp_ptr;
	char           tmp_buffer[2048];
	char           leader_buffer[1024];

/*
	CODE NOTE: Should use the value in the ADF database entry.
*/
unsigned int tab_setting = 3;

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		para_ptr         = entry_data_ptr->para_list + count_1;
		margin_width     = ADF_MAN_MARGIN_PADDING;
		line_width_1     = 80 - (margin_width + 2);
		line_width_2     = line_width_1;
		primary_leader   = NULL;
		next_line_pad    = in_next_line_pad;
		cformat_flag     = ADF_TRUE;
		strip_flag       = 1;
		begin_rule_flag  = ADF_FALSE;
		end_rule_flag    = ADF_FALSE;
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr, para_ptr,
			0, error_text)) != ADF_SUCCESS)
			break;
		if (para_ptr->para_format.pformat_flag == ADF_TRUE) {
			switch (para_ptr->para_format.format_type) {
				case ADF_PFORMAT_TYPE_NONE	:
					primary_leader  = NULL;
					next_line_pad   = in_next_line_pad;
					added_margin    = para_ptr->para_format.indent_level * 4;
					margin_width    = ADF_MAN_MARGIN_PADDING + added_margin;
					line_width_1    = 80 - (margin_width + 2);
					cformat_flag    = para_ptr->para_format.char_format_flag;
					begin_rule_flag = para_ptr->para_format.begin_rule_flag;
					end_rule_flag   = para_ptr->para_format.end_rule_flag;
					break;
				case ADF_PFORMAT_TYPE_BB	:
					primary_leader  = " o  ";
					next_line_pad   = in_next_line_pad + 4;
					added_margin    = (para_ptr->para_format.indent_level * 4) - 4;
					margin_width    = ADF_MAN_MARGIN_PADDING + added_margin;
					line_width_1    = 80 - (margin_width + 4 + 2);
					cformat_flag    = para_ptr->para_format.char_format_flag;
					begin_rule_flag = para_ptr->para_format.begin_rule_flag;
					end_rule_flag   = para_ptr->para_format.end_rule_flag;
					break;
				case ADF_PFORMAT_TYPE_IN	:
					primary_leader  = NULL;
					next_line_pad   = in_next_line_pad;
					added_margin    = para_ptr->para_format.indent_level * 4;
					margin_width    = ADF_MAN_MARGIN_PADDING + added_margin;
					line_width_1    = 80 - (margin_width + 2);
					cformat_flag    = para_ptr->para_format.char_format_flag;
					begin_rule_flag = para_ptr->para_format.begin_rule_flag;
					end_rule_flag   = para_ptr->para_format.end_rule_flag;
					break;
				case ADF_PFORMAT_TYPE_NM	:
					primary_leader  = leader_buffer;
					next_line_pad   = in_next_line_pad + 4;
					added_margin    = (para_ptr->para_format.indent_level * 4) - 4;
					margin_width    = ADF_MAN_MARGIN_PADDING + added_margin;
					line_width_1    = 80 - (margin_width + 4 + 2);
					cformat_flag    = para_ptr->para_format.char_format_flag;
					begin_rule_flag = para_ptr->para_format.begin_rule_flag;
					end_rule_flag   = para_ptr->para_format.end_rule_flag;
					sprintf(leader_buffer, "%3lu ",
						para_ptr->para_format.numeric_value % 1000L);
					break;
				default							:
					break;
			}
			line_width_2 = line_width_1;
		}
		else if (next_line_pad)
			line_width_2 -= next_line_pad;
		current_col                     = 0;
		tab_count                       = 0;
		control_ptr->out_para_buffer[0] = '\0';
		tmp_ptr                         = control_ptr->out_para_buffer;
		if (begin_rule_flag == ADF_TRUE) {
			STR_EMIT_Char(' ', margin_width, output_function,
				output_control);
			STR_EMIT_CharLine('-', 80 - (margin_width + 2),
				output_function, output_control);
		}
		if (cformat_flag != ADF_TRUE) {
			strip_flag   = 0;
			line_width_1 = sizeof(tmp_buffer) - 1;
			line_width_2 = sizeof(tmp_buffer) - 1;
		}
		for (count_2 = 0; count_2 < control_ptr->current_para_line_count;
			count_2++) {
			if (control_ptr->in_para_line_list[count_2].length) {
				nstrcpy(((char *) tmp_ptr),
					control_ptr->in_para_line_list[count_2].ptr,
					control_ptr->in_para_line_list[count_2].length);
				tmp_ptr += control_ptr->in_para_line_list[count_2].length;
			}
		}
		tmp_ptr         = control_ptr->out_para_buffer;
		para_line_count = 0;
		while (*tmp_ptr && ((tmp_ptr = strwrap(tmp_ptr, &current_col,
			(!para_line_count) ? line_width_1 : line_width_2, &tab_count,
			tab_setting, strip_flag, &last_char, tmp_buffer)) != NULL)) {
			STR_EMIT_Char(' ', margin_width, output_function, output_control);
			if ((!para_line_count) && (primary_leader != NULL))
				(*output_function)(output_control, "%s", primary_leader);
			else if (para_line_count && next_line_pad)
				STR_EMIT_Char(' ', next_line_pad, output_function,
					output_control);
			(*output_function)(output_control, "%s\n", tmp_buffer);
			para_line_count++;
		}
		if (end_rule_flag == ADF_TRUE) {
			STR_EMIT_Char(' ', margin_width, output_function, output_control);
			STR_EMIT_CharLine('-', 80 - (margin_width + 2),
				output_function, output_control);
		}
		if ((format_flag == ADF_TRUE) && para_line_count)
			(*output_function)(output_control, "\n");
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

COMPAT_FN_DECL(int main, (int argc, char **argv));

#ifndef NARGS
int main(int argc, char **argv)
#else
int main(argc, argv)
int    argc;
char **argv;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;
	ADF_CONTROL  control_data;
	char         error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'ADF_ASCII_OutputToStdout()'\n");
	fprintf(stderr, "---- ------- --- ----------------------------\n\n");

	ADF_INIT_Control(&control_data);

	control_data.cont_on_error_flag     = ADF_TRUE;
	control_data.sort_order_type        = ADF_SORT_ENTRY_BASE_NAME;
	control_data.hyper_text_flag        = ADF_FALSE;
	control_data.keep_bad_see_also_flag = ADF_TRUE;
	control_data.area_name_type         = ADF_AREA_NAME_TYPE_INTERNAL;
	control_data.area_order_type        = ADF_AREA_ORDER_TYPE_INTERNAL;

	if (argc < 2) {
		sprintf(error_text, "Invalid command line encountered.");
		fprintf(stderr,
			"USAGE:\n   %s <adf-db-file-name> [<adf-db-file-name>...]\n",
			argv[0]);
		return_code = ADF_BAD_ARGS_FAILURE;
	}
	else {
		for (count_1 = 1; count_1 < argc; count_1++) {
			fprintf(stderr, "File: %s\n", argv[count_1]);
			if ((return_code = ADF_OpenADFFileIn(&control_data, argv[count_1],
				error_text)) != ADF_SUCCESS) {
				if (return_code != ADF_PARSE_FAILURE)
					break;
				fprintf(stderr, "%s\n", error_text);
				return_code = ADF_SUCCESS;
			}
		}
		if (return_code == ADF_SUCCESS) {
			if ((return_code = ADF_FinalizeEntries(&control_data, error_text)) !=
				ADF_SUCCESS)
				goto EXIT_FUNCTION;
			for (count_1 = 0; count_1 < control_data.in_entry_order_count;
				count_1++) {
				STR_EMIT_Char('=', 78, NULL, NULL);
				if ((return_code = ADF_ASCII_OutputToStdout(&control_data,
					control_data.in_entry_order_list[count_1], NULL,
					error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				fprintf(stderr, ".");
				STR_EMIT_Char('=', 78, NULL, NULL);
			}
			fprintf(stderr, "\n\n");
		}
	}

EXIT_FUNCTION:

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

