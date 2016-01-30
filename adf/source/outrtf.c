/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits an ADF entry in Rich Text Format (RTF) format.

	Revision History	:	1995-12-02 --- Creation.
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

#include <memory.h>
#include <stdlib.h>
#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DECL const ADF_AREA ADF_AreaNameList[];
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
const char         *ADF_RTF_BasicHeaderList[] = {
	"{\\rtf1\\ansi \\deff4\\deflang1033",
	"{\\fonttbl\
{\\f1\\froman\\fcharset2\\fprq2 Symbol;}\
{\\f4\\froman\\fcharset0\\fprq2 Times New Roman;}\
{\\f11\\fmodern\\fcharset0\\fprq1 Courier New;}}",
	"{\\colortbl;\
\\red0\\green0\\blue0;\
\\red0\\green0\\blue255;\
\\red0\\green255\\blue255;\
\\red0\\green255\\blue0;\
\\red255\\green0\\blue255;\
\\red255\\green0\\blue0;\
\\red255\\green255\\blue0;\
\\red255\\green255\\blue255;\
\\red0\\green0\\blue128;\
\\red0\\green128\\blue128;\
\\red0\\green128\\blue0;\
\\red128\\green0\\blue128;\
\\red128\\green0\\blue0;\
\\red128\\green128\\blue0;\
\\red128\\green128\\blue128;\
\\red192\\green192\\blue192;}"
};
const unsigned int  ADF_RTF_BasicHeaderCount  =
	sizeof(ADF_RTF_BasicHeaderList) / sizeof(ADF_RTF_BasicHeaderList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
const char         *ADF_RTF_BasicStyleList[] = {
	"{\\f4\\fs20 \\snext0 Normal;}",
	"{\\s1\\sb240\\sa60\\keepn \\b\\f5\\fs28\\kerning28 \\sbasedon0\\snext0 heading 1;}",
	"{\\s2\\sb240\\sa60\\keepn \\b\\i\\f5 \\sbasedon0\\snext0 heading 2;}",
	"{\\*\\cs10 \\additive Default Paragraph Font;}",
	"{\\s15\\sb120\\sa120 \\b\\f4 \\sbasedon0\\snext15 ADF_Section;}",
	"{\\s16\\li720\\sb120\\sa120 \\f4\\fs20\\lang1024 \\snext16 ADF_NormalParagraph;}",
	"{\\s17\\li360\\sb120\\sa120 \\f4\\fs20\\lang1024 \\sbasedon16\\snext17 ADF_NameTOC;}",
	"{\\s18\\li360\\sb120\\sa120 \\f4\\fs20 \\snext18 ADF_Basic;}",
	"{\\s20\\fi-360\\li720\\box\\brdrs\\brdrw15\\brsp20 \\f11\\fs16\\lang1024 \\snext20 CodeSyntax;}",
	"{\\s30\\li360 \\f4\\fs20 \\sbasedon18\\snext30 ADF_SeeAlso;}",
	"{\\s41\\sb120\\pagebb \\b\\f4 \\sbasedon15\\snext41 ADF_Entry;}",
	"{\\s44\\li360\\sb120\\sa120 \\f4\\fs20\\lang1024 \\sbasedon18\\snext44 ADF_EntryName;}"
};
const unsigned int  ADF_RTF_BasicStyleCount  =
	sizeof(ADF_RTF_BasicStyleList) / sizeof(ADF_RTF_BasicStyleList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void  ADF_RTF_DoHeaderByEntry,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_RTF_DoHeaderByFile,
	(const ADF_CONTROL *control_ptr,
	unsigned int entry_index, const time_t *output_date,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(int   ADF_RTF_OutputBasic,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_RTF_OutputSection,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	int format_flag, unsigned int in_next_line_pad,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_RTF_OutputCodeSyntax,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_RTF_OutputSeeAlso,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_RTF_EmitParaText,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int para_line_count,
	const ADF_PARA_TEXT *para_line_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL_STATIC(void  ADF_RTF_EmitPlainParaText,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int para_line_count,
	const ADF_PARA_TEXT *para_line_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(int   ADF_RTF_OutputEntryIndex,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const ADF_ENTRY_DATA *index_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(void  ADF_RTF_OutputEmbeddedIndex,
	(unsigned int para_line_count,
	const ADF_PARA_TEXT *para_line_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_RTF_OutputBookMark,
	(const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_RTF_OutputIndexString,
	(const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_RTF_OutputString,
	(const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_RTF_OutputText,
	(unsigned int out_length,
	const char *out_text, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(int   ADF_RTF_EmitAnchor,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int htext_index, int external_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_RTF_EmitIndexList,
	(ADF_CONTROL *control_ptr,
	unsigned int index_item_count, const ADF_INDEX_ITEM *index_item_list,
	unsigned int indent, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL_STATIC(void  ADF_RTF_DoComment,
	(const char *in_string, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_RTF_DoCommentsFloating,
	(const char *in_string_1,
	const char *in_string_2, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_RTF_DoBorder,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_RTF_OutputInit(ADF_CONTROL *control_ptr, char *error_text)
#else
int ADF_RTF_OutputInit(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int                    return_code = ADF_SUCCESS;
	unsigned int           count_1;
	const ADF_PFORMAT_DEF *pformat_ptr;
	char                   buffer[1024];

	if (control_ptr->rtf_para_style_list_flag != ADF_TRUE) {
		for (count_1 = 0; count_1 < ADF_PFORMAT_COUNT; count_1++) {
			pformat_ptr = ADF_GetParaFormat(count_1);
			if (pformat_ptr->supported_flag != ADF_TRUE)
				continue;
			sprintf(buffer,
				"\\s%u%s\\li%04u\\sb120\\sa120%s%s%s%s%s",
				1000 + count_1,
				((pformat_ptr->format_type == ADF_PFORMAT_TYPE_BB) ||
				 (pformat_ptr->format_type == ADF_PFORMAT_TYPE_NM)) ?
				"\\fi-360" : "",
/*
	CODE NOTE: The aesthetics are to be decided . . .
				720 + (pformat_ptr->indent_level * 360),
*/
				360 + (pformat_ptr->indent_level * 360),
				(pformat_ptr->char_format_flag == ADF_TRUE) ?
				"\\hyphpar1" : "\\hyphpar0\\nowidctlpar",
				(pformat_ptr->begin_rule_flag == ADF_TRUE) ?
				" \\brdrt\\brdrs\\brdrw15\\brsp20" : "",
				(pformat_ptr->end_rule_flag == ADF_TRUE) ?
				" \\brdrb\\brdrs\\brdrw15\\brsp20" : "",
				(pformat_ptr->format_type == ADF_PFORMAT_TYPE_BB) ?
"{\\*\\pn \\pnlvl11\\pnf1\\pnstart1\\pnindent360\\pnhang{\\pntxtb \\'b7}}" :
				(pformat_ptr->format_type == ADF_PFORMAT_TYPE_NM) ?
"{\\*\\pn \\pnlvl10\\pndec\\pnstart1\\pnindent360\\pnhang{\\pntxta )}}" : "",
				(pformat_ptr->small_font_flag == ADF_TRUE) ?
				"\\f11\\fs16" : "\\f4\\fs20");
			if ((control_ptr->rtf_para_style_list[count_1] = strdup(buffer)) ==
				NULL) {
				while (count_1) {
					if (control_ptr->rtf_para_style_list[count_1 - 1] != NULL) {
						free(control_ptr->rtf_para_style_list[count_1 - 1]);
						control_ptr->rtf_para_style_list[count_1 - 1] = NULL;
					}
					count_1--;
				}
				strcpy(error_text, "Unable to create RTF paragraph format list.");
				return_code = ADF_MEMORY_FAILURE;
			}
		}
		control_ptr->rtf_para_style_list_flag = ADF_TRUE;
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_RTF_OutputByEntry(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	char *error_text)
#else
int ADF_RTF_OutputByEntry(control_ptr, entry_ptr, error_text)
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
		sprintf(control_ptr->output_file_name, "%s%s%s.rtf",
			(control_ptr->output_dir == NULL) ? "" : control_ptr->output_dir,
			(control_ptr->output_dir == NULL) ? "" : "/", entry_ptr->base_name);
		ADF_OUT_CleanName(control_ptr->output_file_name);
		if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
			error_text)) == ADF_SUCCESS) {
			if ((return_code = ADF_GetEntry(control_ptr, entry_ptr,
				entry_data_list, error_text)) == ADF_SUCCESS) {
				ADF_RTF_OutputStart(control_ptr, entry_ptr->base_name, NULL,
					STR_FUNC_TYPE_fprintf_CAST(fprintf),
					control_ptr->output_file_ptr);
				return_code = ADF_RTF_OutputBasic(control_ptr, entry_ptr,
					entry_data_list, NULL, STR_FUNC_TYPE_fprintf_CAST(fprintf),
					control_ptr->output_file_ptr, error_text);
				ADF_RTF_OutputEnd(control_ptr,
					STR_FUNC_TYPE_fprintf_CAST(fprintf),
					control_ptr->output_file_ptr);
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
int ADF_RTF_OutputToStdout(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text)
#else
int ADF_RTF_OutputToStdout(control_ptr, entry_ptr, output_date, error_text)
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
		return_code = ADF_RTF_OutputBasic(control_ptr, entry_ptr,
			entry_data_list, output_date, STR_FUNC_TYPE_fprintf_CAST(fprintf),
			stdout, error_text);
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
int ADF_RTF_OutputByFile(ADF_CONTROL *control_ptr, unsigned int *entry_index,
	char *error_text)
#else
int ADF_RTF_OutputByFile(control_ptr, entry_index, error_text)
ADF_CONTROL  *control_ptr;
unsigned int *entry_index;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code = ADF_SUCCESS;
	char           *core_name;
	unsigned int    file_entry_count = 0;
	unsigned int    in_entry_index;
	unsigned int    alloc_length;
	ADF_ENTRY      *entry_ptr;
	ADF_ENTRY_DATA  entry_data_list[ADF_AREA_COUNT];
	time_t          output_date;

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
			file_entry_count = 0;
			if ((return_code = ADF_OUT_AllocFileString(control_ptr, alloc_length,
				error_text)) != ADF_SUCCESS)
				break;
			sprintf(control_ptr->output_file_name, "%s%s%s.rtf",
				(control_ptr->output_dir == NULL) ? "" : control_ptr->output_dir,
				(control_ptr->output_dir == NULL) ? "" : "/", core_name);
			ADF_OUT_CleanName(control_ptr->output_file_name);
			if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
				error_text)) != ADF_SUCCESS)
				break;
			time(&output_date);
			if (control_ptr->output_comment_flag == ADF_TRUE)
				ADF_RTF_OutputStart(control_ptr, entry_ptr->file_name, NULL,
					STR_FUNC_TYPE_fprintf_CAST(fprintf),
					control_ptr->output_file_ptr);
				ADF_RTF_DoHeaderByFile(control_ptr, *entry_index, &output_date,
					STR_FUNC_TYPE_fprintf_CAST(fprintf),
					control_ptr->output_file_ptr);
		}
		if ((return_code = ADF_GetEntry(control_ptr, entry_ptr, entry_data_list,
			error_text)) != ADF_SUCCESS)
			break;
		return_code = ADF_RTF_OutputBasic(control_ptr, entry_ptr,
			entry_data_list, &output_date, STR_FUNC_TYPE_fprintf_CAST(fprintf),
			control_ptr->output_file_ptr,
			error_text);
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
		ADF_RTF_OutputEnd(control_ptr, STR_FUNC_TYPE_fprintf_CAST(fprintf),
			control_ptr->output_file_ptr);
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
void ADF_RTF_OutputStart(ADF_CONTROL *control_ptr, const char *output_name,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
void ADF_RTF_OutputStart(control_ptr, output_name, output_date,
	output_function, output_control)
ADF_CONTROL           *control_ptr;
const char            *output_name;
const time_t          *output_date;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int           count_1;
	unsigned int           count_2;
	time_t                 tmp_output_date;
	struct tm              tm_data;
	char                   date_data[100];
	char                   time_zone_data[100];
	const ADF_PFORMAT_DEF *pformat_ptr;

	STR_EMIT_SetDefaults(&output_function, &output_control);

	tmp_output_date = (output_date == NULL) ? time(NULL)   : *output_date;

	for (count_1 = 0; count_1 < ADF_RTF_BasicHeaderCount; count_1++)
		(*output_function)(output_control, "%s\n",
			ADF_RTF_BasicHeaderList[count_1]);

	(*output_function)(output_control, "{\\stylesheet");
	for (count_1 = 0; count_1 < ADF_RTF_BasicStyleCount; count_1++)
		(*output_function)(output_control, "%s\n",
			ADF_RTF_BasicStyleList[count_1]);

	for (count_1 = 0; count_1 < ADF_PFORMAT_COUNT; count_1++) {
		if (control_ptr->rtf_para_style_list[count_1] != NULL) {
			pformat_ptr = ADF_GetParaFormat(count_1);
			(*output_function)(output_control,
				"{%s \\snext%u ADF_%s_%s%s%s%s_%u;}\n",
				control_ptr->rtf_para_style_list[count_1],
				1000 + count_1,
				(pformat_ptr->format_type == ADF_PFORMAT_TYPE_BB) ? "BB" :
				(pformat_ptr->format_type == ADF_PFORMAT_TYPE_IN) ? "IN" :
				(pformat_ptr->format_type == ADF_PFORMAT_TYPE_NM) ? "NM" : "NO",
				(pformat_ptr->char_format_flag == ADF_TRUE)       ? "F"  : "U",
				(pformat_ptr->small_font_flag == ADF_TRUE)        ? "S"  : "N",
				(pformat_ptr->begin_rule_flag == ADF_TRUE)        ? "Y"  : "N",
				(pformat_ptr->end_rule_flag == ADF_TRUE)          ? "Y"  : "N",
				pformat_ptr->indent_level);
		}
	}

	(*output_function)(output_control, "}\n");

	(*output_function)(output_control, "{\\info\n");
	(*output_function)(output_control, "{\\title ");
	ADF_RTF_OutputString(output_name, output_function, output_control);
	(*output_function)(output_control, "}\n");
	(*output_function)(output_control, "{\\subject ");
	ADF_RTF_OutputString(output_name, output_function, output_control);
	(*output_function)(output_control, "}\n");
	(*output_function)(output_control,
		"{\\author Automated Documentation Facility (ADF)}\n");
	(*output_function)(output_control, "{\\keywords }\n");
	(*output_function)(output_control, "{\\doccomm }\n");
	(*output_function)(output_control,
		"{\\operator Automated Documentation Facility (ADF)}\n");
	SDTIF_Format_time_t_GMT(&tmp_output_date, date_data);
	(*output_function)(output_control,
		"{\\creatim\\yr%-.4s\\mo%-.2s\\dy%-.2s\\hr%-.2s\\min%-.2s}\n",
		date_data, date_data + 5, date_data + 8, date_data + 11, date_data + 14);
	SDTIF_Format_time_t_GMT(&tmp_output_date, date_data);
	(*output_function)(output_control,
		"{\\revtim\\yr%-.4s\\mo%-.2s\\dy%-.2s\\hr%-.2s\\min%-.2s}\n",
		date_data, date_data + 5, date_data + 8, date_data + 11, date_data + 14);
	(*output_function)(output_control, "{\\version1}\n");
	(*output_function)(output_control, "{\\edmins0}\n");
	(*output_function)(output_control, "{\\nofpages0}\n");
	(*output_function)(output_control, "{\\nofwords0}\n");
	(*output_function)(output_control, "{\\nofchars2095}\n");
	(*output_function)(output_control, "{\\vern0}}\n");

	(*output_function)(output_control, "%s\n",
		"\\widowctrl\\ftnbj\\aenddoc\\makebackup\\hyphcaps0\\formshade \
\\fet0\\sectd \\linex0\\endnhere \
{\\*\\pnseclvl1\\pnucrm\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}\
{\\*\\pnseclvl2\\pnucltr\\pnstart1\\pnindent720\\pnhang{\\pntxta .}}\
{\\*\\pnseclvl3\\pndec\\pnstart1\\pnindent720\\pnhang");
	(*output_function)(output_control, "%s\n",
		"{\\pntxta .}}{\\*\\pnseclvl4\\pnlcltr\\pnstart1\\pnindent720\\pnhang\
{\\pntxta )}}{\\*\\pnseclvl5\\pndec\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}\
{\\pntxta )}}{\\*\\pnseclvl6\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}\
{\\pntxta )}}{\\*\\pnseclvl7");
	(*output_function)(output_control, "%s\n",
		"\\pnlcrm\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}\
{\\*\\pnseclvl8\\pnlcltr\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}\
{\\*\\pnseclvl9\\pnlcrm\\pnstart1\\pnindent720\\pnhang{\\pntxtb (}{\\pntxta )}}");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
void ADF_RTF_OutputEnd(ADF_CONTROL *control_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
void ADF_RTF_OutputEnd(control_ptr, output_function, output_control)
ADF_CONTROL  *control_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Get the default values for the output specifiers . . .			*/
	/*	*****************************************************************	*/
	output_function = (output_function != NULL) ? output_function :
		STR_FUNC_TYPE_fprintf_CAST(fprintf);
	output_control  = (output_control  != NULL) ? output_control  : stdout;
	/*	*****************************************************************	*/

	(*output_function)(output_control, "\n}");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RTF_DoHeaderByEntry(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_RTF_DoHeaderByEntry(control_ptr, entry_ptr, entry_data_list,
	output_date, output_function, output_control)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_list;
const time_t          *output_date;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int   tmp_count = 0;
	char         **tmp_list  = NULL;
	unsigned int   count_1;
	time_t         tmp_output_date;
	time_t         time_t_data;
	struct tm      tm_data;
   char           date_data[100];
	char           time_zone_data[100];
	char           error_text[ADF_MAX_ERROR_TEXT];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	tmp_output_date = (output_date == NULL) ? time(NULL)   : *output_date;

	ADF_RTF_DoBorder(output_function, output_control);
	ADF_RTF_DoBorder(output_function, output_control);
	ADF_RTF_DoCommentsFloating("Documentation for ", entry_ptr->base_name,
		output_function, output_control);
	ADF_RTF_DoComment("", output_function, output_control);
	ADF_RTF_DoComment(
		"   Created by the Automated Documentation Facility (ADF)",
		output_function, output_control);
	ADF_RTF_DoBorder(output_function, output_control);

	ADF_RTF_DoComment("", output_function, output_control);
	ADF_RTF_DoCommentsFloating("Entry Name          : ", entry_ptr->base_name,
		output_function, output_control);
	ADF_RTF_DoComment("", output_function, output_control);
	ADF_RTF_DoCommentsFloating("Source File Name    : ", entry_ptr->file_name,
		output_function, output_control);

	ADF_RTF_DoComment("", output_function, output_control);
	ADF_RTF_DoCommentsFloating("Source File Date    : ",
		strcat(SDTIF_Format_time_t_GMT(&entry_ptr->file_date, date_data),
		" GMT/UTC"), output_function, output_control);
	time_t_data = entry_ptr->file_date;
	tm_data     = *SDTIF_GetTimeLocal(&time_t_data, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_RTF_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&entry_ptr->file_date, date_data),
		time_zone_data), output_function, output_control);

	ADF_RTF_DoComment("", output_function, output_control);
	ADF_RTF_DoCommentsFloating("ADF Preparation Date: ",
		strcat(SDTIF_Format_time_t_GMT(&entry_ptr->prep_date, date_data),
		" GMT/UTC"), output_function, output_control);
	time_t_data = entry_ptr->prep_date;
	tm_data     = *SDTIF_GetTimeLocal(&time_t_data, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_RTF_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&entry_ptr->prep_date, date_data),
		time_zone_data), output_function, output_control);

	ADF_RTF_DoComment("", output_function, output_control);
	ADF_RTF_DoCommentsFloating("Output Date         : ",
		strcat(SDTIF_Format_time_t_GMT(&tmp_output_date, date_data), " GMT/UTC"),
		output_function, output_control);
	tm_data = *SDTIF_GetTimeLocal(&tmp_output_date, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_RTF_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&tmp_output_date, date_data), time_zone_data),
		output_function, output_control);

	ADF_RTF_DoComment("", output_function, output_control);
	ADF_RTF_DoBorder(output_function, output_control);
	(*output_function)(output_control, "\n");

	if ((ADF_GetAreaList(control_ptr, entry_ptr, entry_data_list +
		ADF_AREA_COPYRIGHTS, &tmp_count, &tmp_list, error_text) ==
		ADF_SUCCESS) && tmp_count) {
		ADF_RTF_DoBorder(output_function, output_control);
		ADF_RTF_DoBorder(output_function, output_control);
		for (count_1 = 0; count_1 < tmp_count; count_1++)
			ADF_RTF_DoCommentsFloating("", tmp_list[count_1],
				output_function, output_control);
		ADF_RTF_DoBorder(output_function, output_control);
		strl_remove_all(&tmp_count, &tmp_list);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RTF_DoHeaderByFile(const ADF_CONTROL *control_ptr,
	unsigned int entry_index, const time_t *output_date,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_RTF_DoHeaderByFile(control_ptr, entry_index, output_date,
	output_function, output_control)
const ADF_CONTROL     *control_ptr;
unsigned int           entry_index;
const time_t          *output_date;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	time_t       tmp_output_date;
	struct tm    tm_data;
   char         date_data[100];
	char         time_zone_data[100];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	tmp_output_date = (output_date == NULL) ? time(NULL) : *output_date;

	ADF_RTF_DoBorder(output_function, output_control);
	ADF_RTF_DoBorder(output_function, output_control);
	ADF_RTF_DoCommentsFloating("Documentation for Entries in Source File ",
		control_ptr->in_entry_order_list[entry_index]->file_name,
		output_function, output_control);
	ADF_RTF_DoComment("", output_function, output_control);
	ADF_RTF_DoComment(
		"   Created by the Automated Documentation Facility (ADF)",
		output_function, output_control);
	ADF_RTF_DoBorder(output_function, output_control);
	ADF_RTF_DoComment("", output_function, output_control);
	ADF_RTF_DoCommentsFloating("Output Date: ",
		strcat(SDTIF_Format_time_t_GMT(&tmp_output_date, date_data), " GMT/UTC"),
		output_function, output_control);
	tm_data = *SDTIF_GetTimeLocal(&tmp_output_date, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_RTF_DoCommentsFloating("           : ",
		strcat(SDTIF_Format_time_t(&tmp_output_date, date_data), time_zone_data),
		output_function, output_control);
	ADF_RTF_DoComment("", output_function, output_control);

	for (count_1 = entry_index;
		(count_1 < control_ptr->in_entry_order_count) &&
		(!strcmp(control_ptr->in_entry_order_list[entry_index]->file_name,
		control_ptr->in_entry_order_list[count_1]->file_name)); count_1++)
		ADF_RTF_DoCommentsFloating((!count_1) ?
			"Entry Name : " : "           : ",
			control_ptr->in_entry_order_list[count_1]->base_name,
			output_function, output_control);
	ADF_RTF_DoComment("", output_function, output_control);
	ADF_RTF_DoBorder(output_function, output_control);
	(*output_function)(output_control, "\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RTF_OutputBasic(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_RTF_OutputBasic(control_ptr, entry_ptr, entry_data_list,
	output_date, output_function, output_control, error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
ADF_ENTRY_DATA   *entry_data_list;
const time_t     *output_date;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code     = ADF_SUCCESS;
	unsigned int     area_name_count = 0;
	const ADF_AREA  *last_area_ptr   = NULL;
	unsigned int     count_1;
	ADF_ENTRY_DATA  *entry_data_ptr;
	const ADF_AREA  *area_ptr;
	unsigned int     tmp_length;
	ADF_ENTRY_DATA   index_data;
	char             area_name[ADF_AREA_NAME_LENGTH + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Emit descriptive comments for the entry . . .						*/
	/*	*****************************************************************	*/
	if (control_ptr->output_comment_flag == ADF_TRUE)
		ADF_RTF_DoHeaderByEntry(control_ptr, entry_ptr, entry_data_list,
			output_date, output_function, output_control);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Order the sections of the entry as specified, but first save	*/
	/*	the output index and publish areas . . .									*/
	/*	*****************************************************************	*/
	index_data = entry_data_list[ADF_AREA_OUTPUT_INDEX];
	if (control_ptr->area_order_type != ADF_AREA_ORDER_TYPE_INTERNAL)
		ADF_SORT_EntrySections(control_ptr->area_order_type, entry_data_list);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Find the last area to be output for this entry . . .				*/
	/*	*****************************************************************	*/
	for (count_1 = ADF_AREA_COUNT; count_1; ) {
		count_1--;
		if (entry_data_list[count_1].para_count &&
			(ADF_AreaNameList[entry_data_list[count_1].area_index].output_flag ==
			ADF_TRUE)) {
			last_area_ptr =
				ADF_AreaNameList + entry_data_list[count_1].area_index;
			break;
		}
	}
	/*	*****************************************************************	*/

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		entry_data_ptr = entry_data_list + count_1;
		area_ptr       = ADF_AreaNameList + entry_data_ptr->area_index;
		if ((area_ptr->output_flag != ADF_TRUE) ||
			(!entry_data_ptr->para_count))
			continue;
		(*output_function)(output_control, "%s ", (!area_name_count) ?
			"\\pard\\plain \\s41\\sb120\\pagebb \\b\\f4" :
			"\\pard\\plain \\s15\\sb120 \\b\\f4");
		ADF_GetOutputAreaName(control_ptr->area_name_type,
			entry_data_ptr->area_index, control_ptr->area_name_list,
			entry_data_ptr->section_name, sizeof(area_name) - 1, area_name);
		ADF_RTF_OutputString(area_name, output_function, output_control);
		if (!area_name_count++) {
			(*output_function)(output_control, "\n{\\*\\bkmkstart ADF_BKMK_");
			ADF_RTF_OutputBookMark(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "}");
			(*output_function)(output_control,
				"\n{\\pard\\plain \\s18 \\v\\f4 {\\xe {");
			ADF_RTF_OutputIndexString(entry_ptr->file_name, output_function,
				output_control);
			(*output_function)(output_control, "\\:");
			ADF_RTF_OutputIndexString(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "\\xef102}{\\rxe ADF_BKMK_");
			ADF_RTF_OutputBookMark(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "}}}");
			if ((return_code = ADF_RTF_OutputEntryIndex(control_ptr, entry_ptr,
				&index_data, output_function, output_control, error_text)) !=
				ADF_SUCCESS)
				break;
			(*output_function)(output_control,
				"\n{\\pard\\plain \\s18 \\v\\f4 {\\tc {");
			ADF_RTF_OutputString(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "}}}");
		}
		(*output_function)(output_control, "\n\\par ");
		if (entry_data_ptr->area_index == ADF_AREA_NAME) {
			(*output_function)(output_control,
				"\\pard\\plain \\s44\\li360\\sb120\\sa120 \\f4\\fs20\\lang1024 ");
			ADF_RTF_OutputString(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "\n\\par ");
		}
		else if (entry_data_ptr->area_index == ADF_AREA_CODE_SYNTAX) {
			if ((return_code = ADF_RTF_OutputCodeSyntax(control_ptr, entry_ptr,
				entry_data_ptr, output_function, output_control, error_text)) !=
				ADF_SUCCESS)
				break;
		}
		else if (entry_data_ptr->area_index == ADF_AREA_SEE_ALSO) {
			if ((return_code = ADF_RTF_OutputSeeAlso(control_ptr, entry_ptr,
				entry_data_ptr, output_function, output_control, error_text)) !=
				ADF_SUCCESS)
				break;
		}
		else if ((return_code = ADF_RTF_OutputSection(control_ptr, entry_ptr,
			entry_data_ptr, area_ptr->pformat_flag, 0, output_function,
			output_control, error_text)) != ADF_SUCCESS)
			break;
		if (area_ptr == last_area_ptr) {
			(*output_function)(output_control, "\n{\\*\\bkmkend ADF_BKMK_");
			ADF_RTF_OutputBookMark(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "}");
			break;
		}
	}

	if (return_code == ADF_SUCCESS) {
		if (control_ptr->output_comment_flag == ADF_TRUE) {
			(*output_function)(output_control, "\n");
			ADF_RTF_DoBorder(output_function, output_control);
			ADF_RTF_DoCommentsFloating("End of RTF Script for ",
				entry_ptr->base_name, output_function, output_control);
			ADF_RTF_DoBorder(output_function, output_control);
			ADF_RTF_DoBorder(output_function, output_control);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RTF_OutputSection(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	int format_flag, unsigned int in_next_line_pad,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_RTF_OutputSection(control_ptr, entry_ptr, entry_data_ptr,
	format_flag, in_next_line_pad, output_function, output_control, error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
ADF_ENTRY_DATA   *entry_data_ptr;
int               format_flag;
unsigned int      in_next_line_pad;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	unsigned int   count_1;
	unsigned int   count_2;
	unsigned int   added_margin;
	unsigned int   cformat_type;
	int            char_format_flag;
	ADF_PARA_DATA *para_ptr;
	char          *primary_leader;
	char           post_text[256];
	ADF_PFORMAT   *pfmt_ptr;
	ADF_PFORMAT   *pfmt_flag[ADF_PFORMAT_LEVEL_COUNT][ADF_PFORMAT_TYPE_COUNT];

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Clear the list of active paragraphs . . .								*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < ADF_PFORMAT_LEVEL_COUNT; count_1++) {
		for (count_2 = 0; count_2 < ADF_PFORMAT_TYPE_COUNT; count_2++)
			pfmt_flag[count_1][count_2] = NULL;
	}
	/*	*****************************************************************	*/

	cformat_type = (format_flag == ADF_TRUE) ? ADF_RTF_CFORMAT_TYPE : 0;

	if ((cformat_type & ADF_CFORMAT_TYPE_HTEXT) &&
		(control_ptr->hyper_text_flag != ADF_TRUE))
		cformat_type ^= ADF_CFORMAT_TYPE_HTEXT;

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		para_ptr       = entry_data_ptr->para_list + count_1;
		pfmt_ptr       = &para_ptr->para_format;
		primary_leader = NULL;
		*post_text     = '\0';
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr, para_ptr,
			cformat_type, error_text)) != ADF_SUCCESS)
			break;
		if ((pfmt_ptr->pformat_flag != ADF_TRUE) || (format_flag != ADF_TRUE) ||
			(control_ptr->rtf_para_style_list[pfmt_ptr->pformat_index] == NULL))
			pfmt_ptr->pformat_index = 0;
		(*output_function)(output_control, "\\pard\\plain %s ",
			control_ptr->rtf_para_style_list[pfmt_ptr->pformat_index]);
		char_format_flag = (pfmt_ptr->pformat_flag != ADF_TRUE) ? ADF_TRUE :
			pfmt_ptr->char_format_flag;
		if (char_format_flag == ADF_TRUE) {
			if ((return_code = ADF_RTF_EmitParaText(control_ptr, entry_ptr,
				control_ptr->current_para_line_count,
				control_ptr->in_para_line_list, output_function, output_control,
				error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
		}
		else
			ADF_RTF_EmitPlainParaText(control_ptr, entry_ptr,
				control_ptr->current_para_line_count,
				control_ptr->in_para_line_list, output_function, output_control);
		(*output_function)(output_control, "\n\\par ");
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RTF_OutputCodeSyntax(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_RTF_OutputCodeSyntax(control_ptr, entry_ptr, entry_data_ptr,
	output_function, output_control, error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
ADF_ENTRY_DATA   *entry_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;
	unsigned int count_2;

	(*output_function)(output_control, "%s",
		"\\pard\\plain \\s20\\fi-360\\li720\\brdrt\\brdrs\\brdrw15\\brsp20 \
\\brdrb\\brdrs\\brdrw15\\brsp20 \\f11\\fs16\\lang1024 ");

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr,
			entry_data_ptr->para_list + count_1, 0, error_text)) != ADF_SUCCESS)
			break;
		for (count_2 = 0; count_2 < control_ptr->current_para_line_count;
			count_2++) {
			if ((control_ptr->in_para_line_list[count_2].ptr == NULL) ||
				(*control_ptr->in_para_line_list[count_2].ptr ==
				ADF_CFORMAT_MARKER_CHAR))
				continue;
			ADF_RTF_OutputString(control_ptr->in_para_line_list[count_2].ptr,
				output_function, output_control);
		}
		(*output_function)(output_control, "\n\\par ");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RTF_OutputSeeAlso(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_RTF_OutputSeeAlso(control_ptr, entry_ptr, entry_data_ptr,
	output_function, output_control, error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
ADF_ENTRY_DATA   *entry_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;
   unsigned int found_index;
	char         buffer[1024];

	(*output_function)(output_control, "%s",
		"\\pard\\plain \\s30\\li360 \\f4\\fs20 ");

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
/*
	CODE NOTE: Not to be implemented unless hyper-text is to be
				  supported by the ADF RTF functionality.
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr,
			entry_data_ptr->para_list + count_1,
			(control_ptr->hyper_text_flag == ADF_TRUE) ? ADF_CFORMAT_TYPE_HTEXT :
			ADF_CFORMAT_TYPE_NONE, error_text)) != ADF_SUCCESS)
			break;
*/
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr,
			entry_data_ptr->para_list + count_1, ADF_CFORMAT_TYPE_NONE,
			error_text)) != ADF_SUCCESS)
			break;
		else if ((return_code = ADF_RTF_EmitParaText(control_ptr, entry_ptr,
			control_ptr->current_para_line_count, control_ptr->in_para_line_list,
			output_function, output_control, error_text)) != ADF_SUCCESS)
			break;
/*
	CODE NOTE: To be removed.
		if (control_ptr->in_para_line_list->length >= sizeof(buffer))
			nstrcpy(buffer, control_ptr->in_para_line_list->ptr,
				sizeof(buffer) - 1);
		else if (control_ptr->in_para_line_list->length)
			nstrcpy(buffer, control_ptr->in_para_line_list->ptr,
				control_ptr->in_para_line_list->length);
*/
		if (control_ptr->in_para_line_list->length &&
			(control_ptr->in_para_line_list->ptr != NULL)) {
			nstrcpy(buffer, control_ptr->in_para_line_list->ptr,
				(control_ptr->in_para_line_list->length >= sizeof(buffer)) ?
				(sizeof(buffer) - 1) : control_ptr->in_para_line_list->length);
			if (ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
				control_ptr->in_htext_list, buffer, &found_index) ==
				STRFUNCS_ITEM_FOUND) {
				(*output_function)(output_control, " on page number ");
				(*output_function)(output_control,
					"{\\field{\\*\\fldinst PAGEREF ADF_BKMK_");
				ADF_RTF_OutputBookMark(control_ptr->in_entry_list
					[control_ptr->in_htext_list[found_index].in_entry_index].
					base_name, output_function, output_control);
				 (*output_function)(output_control,
					" \\\\* MERGEFORMAT }{\\fldrslt 0}}");
			}
		}
		(*output_function)(output_control, "\n\\par ");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RTF_EmitParaText(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int para_line_count,
	const ADF_PARA_TEXT *para_line_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_RTF_EmitParaText(control_ptr, entry_ptr, para_line_count,
	para_line_list, output_function, output_control, error_text)
ADF_CONTROL          *control_ptr;
const ADF_ENTRY      *entry_ptr;
unsigned int          para_line_count;
const ADF_PARA_TEXT  *para_line_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                 *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
	unsigned int  in_length;
	char         *in_ptr;

	for (count_1 = 0; count_1 < para_line_count; count_1++) {
		in_length = para_line_list[count_1].length;
		in_ptr    = para_line_list[count_1].ptr;
		if (para_line_list[count_1].cformat_type != ADF_CFORMAT_CHAR_NONE) {
			switch (para_line_list[count_1].cformat_type) {
				case ADF_CFORMAT_CHAR_BOLD_1			:
					(*output_function)(output_control, "{\\b ");
					break;
				case ADF_CFORMAT_CHAR_ITALIC_1		:
					(*output_function)(output_control, "{\\i ");
					break;
				case ADF_CFORMAT_CHAR_ULINED_1		:
					(*output_function)(output_control, "{\\ul ");
					break;
				case ADF_CFORMAT_CHAR_STHRU_1			:
					(*output_function)(output_control, "{\\strike ");
					break;
				case ADF_CFORMAT_CHAR_EINDEX_1		:
					ADF_RTF_OutputEmbeddedIndex(para_line_count - (count_1 + 1),
						para_line_list + count_1 + 1, output_function,
						output_control);
					break;
				case ADF_CFORMAT_CHAR_SUBSCRIPT_1	:
					(*output_function)(output_control, "{\\sub ");
					break;
				case ADF_CFORMAT_CHAR_SUPERSCRIPT_1	:
					(*output_function)(output_control, "{\\up6\\super ");
					break;
				case ADF_CFORMAT_CHAR_HTEXT_1			:
/*
					if ((return_code = ADF_RTF_EmitAnchor(control_ptr, entry_ptr,
						para_line_list[count_1].htext_index, ADF_FALSE,
						output_function, output_control, error_text)) !=
						ADF_SUCCESS)
						goto EXIT_FUNCTION;
*/
					break;
				case ADF_CFORMAT_CHAR_BOLD_2			:
					(*output_function)(output_control, "}");
					break;
				case ADF_CFORMAT_CHAR_ITALIC_2		:
					(*output_function)(output_control, "}");
					break;
				case ADF_CFORMAT_CHAR_ULINED_2		:
					(*output_function)(output_control, "}");
					break;
				case ADF_CFORMAT_CHAR_STHRU_2			:
					(*output_function)(output_control, "}");
					break;
				case ADF_CFORMAT_CHAR_EINDEX_2		:
					break;
				case ADF_CFORMAT_CHAR_SUBSCRIPT_2	:
					(*output_function)(output_control, "}");
					break;
				case ADF_CFORMAT_CHAR_SUPERSCRIPT_2	:
					(*output_function)(output_control, "}");
					break;
				case ADF_CFORMAT_CHAR_HTEXT_2			:
/*
					(*output_function)(output_control, "</A>");
*/
					break;
				default										:
					break;
			}
			continue;
		}
		else if ((in_length) && (in_ptr != NULL))
			ADF_RTF_OutputText(in_length, in_ptr, output_function,
				output_control);
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RTF_EmitPlainParaText(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int para_line_count,
	const ADF_PARA_TEXT *para_line_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_RTF_EmitPlainParaText(control_ptr, entry_ptr, para_line_count,
	para_line_list, output_function, output_control)
ADF_CONTROL          *control_ptr;
const ADF_ENTRY      *entry_ptr;
unsigned int          para_line_count;
const ADF_PARA_TEXT  *para_line_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int  current_col = 0;
	unsigned int  space_count;
	unsigned int  count_1;
	unsigned int  in_length;
	char         *in_ptr;

/*
	CODE NOTE: Should use the value in the ADF database entry.
*/
unsigned int tab_setting = 3;

	for (count_1 = 0; count_1 < para_line_count; count_1++) {
		in_length = para_line_list[count_1].length;
		in_ptr    = para_line_list[count_1].ptr;
		if ((para_line_list[count_1].cformat_type != ADF_CFORMAT_CHAR_NONE) ||
			(!in_length) || (in_ptr == NULL))
			continue;
		for ( ; in_length; in_length--, in_ptr++) {
			if ((*in_ptr == '\\') || (*in_ptr == '{') || (*in_ptr == '}')) {
				(*output_function)(output_control, "\\%c", *in_ptr);
				current_col++;
			}
			else if (*in_ptr == '\n') {
				(*output_function)(output_control, "\n\\line ");
				current_col = 0;
			}
			else if (*in_ptr == '\t') {
				space_count  = tab_setting - (current_col % tab_setting);
				current_col += space_count;
				STR_EMIT_Char(' ', space_count, output_function, output_control);
			}
			else {
				(*output_function)(output_control, "%c", *in_ptr);
				current_col++;
			}
		}
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RTF_OutputEntryIndex(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const ADF_ENTRY_DATA *index_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_RTF_OutputEntryIndex(control_ptr, entry_ptr, index_data_ptr,
	output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
const ADF_ENTRY_DATA  *index_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  count_1;
   unsigned int  found_index;
	int           strfuncs_code;
	char         *tmp_ptr;
	char          buffer[1024];

	for (count_1 = 0; count_1 < index_data_ptr->para_count; count_1++) {
		nstrcpy(buffer, index_data_ptr->para_list[count_1].text_ptr,
			sizeof(buffer) - 1);
		if ((tmp_ptr = strrchr(buffer, ':')) == NULL) {
			if (ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
				control_ptr->in_htext_list, buffer, &found_index) ==
				STRFUNCS_ITEM_FOUND) {
				if ((entry_ptr->file_index ==
					control_ptr->in_htext_list[found_index].file_index) &&
					(entry_ptr->entry_index ==
					control_ptr->in_htext_list[found_index].entry_index)) {
					(*output_function)(output_control,
						"\n{\\pard\\plain \\s18 \\v\\f4 {\\xe {");
					ADF_RTF_OutputIndexString(buffer, output_function,
						output_control);
					(*output_function)(output_control, "}{\\rxe ADF_BKMK_");
					ADF_RTF_OutputBookMark(entry_ptr->base_name, output_function,
						output_control);
					(*output_function)(output_control, "}}}");
				}
			}
/*
	CODE NOTE: Should put a warning message here.
			else {
			}
*/
		}
		else if (ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
			control_ptr->in_htext_list, tmp_ptr + 1, &found_index) ==
			STRFUNCS_ITEM_FOUND) {
			if ((entry_ptr->file_index ==
				control_ptr->in_htext_list[found_index].file_index) &&
				(entry_ptr->entry_index ==
				control_ptr->in_htext_list[found_index].entry_index)) {
				(*output_function)(output_control,
					"\n{\\pard\\plain \\s18 \\v\\f4 {\\xe {");
				ADF_RTF_OutputIndexString(buffer, output_function, output_control);
				(*output_function)(output_control, "}{\\rxe ADF_BKMK_");
				ADF_RTF_OutputBookMark(entry_ptr->base_name, output_function,
					output_control);
				(*output_function)(output_control, "}}}");
			}
		}
		else if ((strfuncs_code = strl_search(&control_ptr->non_ref_index_count,
			&control_ptr->non_ref_index_list, buffer, &found_index)) ==
			STRFUNCS_FAILURE) {
			strcpy(error_text,
				"Unable to add a string to list of non-referential index entries.");
			return_code = ADF_MEMORY_FAILURE;
		}
		else if (strfuncs_code == STRFUNCS_ITEM_NOT_FOUND) {
			*tmp_ptr++ = '\0';
			(*output_function)(output_control,
				"\n{\\pard\\plain \\s18 \\v\\f4 {\\xe {");
			ADF_RTF_OutputIndexString(buffer, output_function,
				output_control);
			(*output_function)(output_control, "}{\\txe ");
			ADF_RTF_OutputString(tmp_ptr, output_function, output_control);
			(*output_function)(output_control, "}}}");
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RTF_OutputEmbeddedIndex(unsigned int para_line_count,
	const ADF_PARA_TEXT *para_line_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_RTF_OutputEmbeddedIndex(para_line_count, para_line_list,
	output_function, output_control)
unsigned int           para_line_count;
const ADF_PARA_TEXT   *para_line_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	(*output_function)(output_control, "{\\pard\\plain \\s18 \\v\\f4 {\\xe {");

	for (count_1 = 0; count_1 < para_line_count; count_1++) {
		if (para_line_list[count_1].cformat_type == ADF_CFORMAT_CHAR_EINDEX_2)
			break;
		if ((para_line_list[count_1].cformat_type == ADF_CFORMAT_CHAR_NONE) &&
			para_line_list[count_1].length &&
			(para_line_list[count_1].ptr != NULL))
			ADF_RTF_OutputText(para_line_list[count_1].length,
				para_line_list[count_1].ptr, output_function, output_control);
	}

	(*output_function)(output_control, "}}}");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RTF_OutputBookMark(const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_RTF_OutputBookMark(out_text, output_function,
	output_control)
const char            *out_text;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	while (*out_text) {
		if (!iscsym(*out_text))
			(*output_function)(output_control, "_", *out_text++);
		else
			(*output_function)(output_control, "%c", *out_text++);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RTF_OutputIndexString(const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_RTF_OutputIndexString(out_text, output_function,
	output_control)
const char  *out_text;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	while (*out_text) {
		if ((*out_text == '\\') || (*out_text == '{') || (*out_text == '}') ||
			(*out_text == ':'))
			(*output_function)(output_control, "\\%c", *out_text++);
		else
			(*output_function)(output_control, "%c", *out_text++);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RTF_OutputString(const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_RTF_OutputString(out_text, output_function, output_control)
const char  *out_text;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	ADF_RTF_OutputText(strlen(out_text), out_text, output_function,
		output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RTF_OutputText(unsigned int out_length, const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_RTF_OutputText(out_length, out_text, output_function,
	output_control)
unsigned int  out_length;
const char   *out_text;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	for ( ; out_length; out_length--, out_text++) {
		if ((*out_text == '\\') || (*out_text == '{') || (*out_text == '}'))
			(*output_function)(output_control, "\\%c", *out_text);
		else
			(*output_function)(output_control, "%c", *out_text);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RTF_EmitAnchor(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int htext_index, int external_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_RTF_EmitAnchor(control_ptr, entry_ptr, htext_index,
	external_flag, output_function, output_control, error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
unsigned int      htext_index;
int               external_flag;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned int  alloc_length;
	char         *tmp_ptr;
	ADF_HTEXT    *htext_ptr;
	ADF_ENTRY    *htext_entry_ptr;
	char         *output_dir;

	htext_ptr       = control_ptr->in_htext_list + htext_index;
	htext_entry_ptr = control_ptr->in_entry_list + htext_ptr->in_entry_index;
/*
	CODE NOTE: To be validated  pending removal.
	output_dir      = (htext_entry_ptr->href_flag == ADF_TRUE) ?
		control_ptr->in_file_list[htext_entry_ptr->file_index].href_string :
		control_ptr->output_dir;
*/
	output_dir      =
		(control_ptr->in_file_list[htext_entry_ptr->file_index].href_string ==
		NULL) ? control_ptr->output_dir :
		control_ptr->in_file_list[htext_entry_ptr->file_index].href_string;

	alloc_length    = ((output_dir == NULL) ? 0 : strlen(output_dir)) +
		strlen(htext_entry_ptr->base_name) +
		strlen(htext_entry_ptr->file_name) + strlen(htext_ptr->hyper_text) +
		256;

	if ((external_flag != ADF_TRUE) &&
		((control_ptr->output_to_stdout_flag == ADF_TRUE) ||
		((entry_ptr->file_index == htext_entry_ptr->file_index) &&
		(!strcmp(entry_ptr->file_name, htext_entry_ptr->file_name)) &&
		(control_ptr->output_by_file_flag == ADF_TRUE))))
		(*output_function)(output_control, "<A HREF=\"#%s\">",
			htext_entry_ptr->base_name);
	else if (control_ptr->output_by_file_flag != ADF_TRUE) {
		if ((return_code = ADF_OUT_AllocHTextString(control_ptr, alloc_length,
			error_text)) == ADF_SUCCESS) {
			if (htext_entry_ptr->file_index == entry_ptr->file_index)
				sprintf(control_ptr->htext_link_name, "%s.rtf",
					htext_entry_ptr->base_name);
			else
				sprintf(control_ptr->htext_link_name, "%s%s%s.rtf",
					(output_dir == NULL) ? "" : output_dir,
					(output_dir == NULL) ? "" : "/", htext_entry_ptr->base_name);
			ADF_OUT_CleanName(control_ptr->htext_link_name);
			(*output_function)(output_control, "<A HREF=\"%s#%s\">",
				control_ptr->htext_link_name, htext_entry_ptr->base_name);
		}
	}
	else {
		if ((return_code = ADF_OUT_AllocHTextString(control_ptr, alloc_length,
			error_text)) == ADF_SUCCESS) {
			if (htext_entry_ptr->file_index == entry_ptr->file_index)
				sprintf(control_ptr->htext_link_name, "%s",
					htext_entry_ptr->file_name);
			else
				sprintf(control_ptr->htext_link_name, "%s%s%s",
					(output_dir == NULL) ? "" : output_dir,
					(output_dir == NULL) ? "" : "/", htext_entry_ptr->file_name);
			if (strrchr(htext_entry_ptr->file_name, '.') != NULL) {
				tmp_ptr = control_ptr->htext_link_name +
					(strlen(control_ptr->htext_link_name) - 1);
				while (*tmp_ptr != '.')
					tmp_ptr--;
				*tmp_ptr = '\0';
			}
			strcat(control_ptr->htext_link_name, ".rtf");
			ADF_OUT_CleanName(control_ptr->htext_link_name);
			(*output_function)(output_control, "<A HREF=\"%s#%s\">",
				control_ptr->htext_link_name, htext_entry_ptr->base_name);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_RTF_EmitIndexList(ADF_CONTROL *control_ptr,
	unsigned int index_item_count, const ADF_INDEX_ITEM *index_item_list,
	unsigned int indent, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_RTF_EmitIndexList(control_ptr, index_item_count,
	index_item_list, indent, output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
unsigned int           index_item_count;
const ADF_INDEX_ITEM  *index_item_list;
unsigned int           indent;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	unsigned char last_char   = UCHAR_MAX;
	unsigned int  count_1;

	for (count_1 = 0; count_1 < index_item_count; count_1++) {
		if ((!indent) && (last_char != index_item_list[count_1].item_order)) {
			(*output_function)(output_control, "<P>\n");
			last_char = index_item_list[count_1].item_order;
			if (last_char == '\0')
				(*output_function)(output_control,
					"<A NAME=\"%s\"></A><B>Symbols</B><BR>\n",
					"__INTERNAL_INDEX_SYMBOL__");
			else if (last_char == '\1')
				(*output_function)(output_control,
					"<A NAME=\"%s\"></A><B>Numerics</B><BR>\n",
					"__INTERNAL_INDEX_NUMERIC__");
			else
				(*output_function)(output_control,
					"<A NAME=\"%s_%c__\"></A><B>%c</B><BR>\n",
					"__INTERNAL_INDEX_CHARACTER", last_char, last_char);
		}
		if (index_item_list[count_1].entry_flag == ADF_TRUE) {
			if ((return_code = ADF_RTF_EmitAnchor(control_ptr,
				index_item_list[count_1].entry_ptr,
				index_item_list[count_1].htext_index, ADF_TRUE,
				output_function, output_control, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			(*output_function)(output_control, "%s</A><BR>\n",
				index_item_list[count_1].item_name);
		}
		else
			(*output_function)(output_control, "%s<BR>\n",
				index_item_list[count_1].item_name);
		if (index_item_list[count_1].index_item_count) {
			(*output_function)(output_control, "<UL>\n");
			if ((return_code = ADF_RTF_EmitIndexList(control_ptr,
				index_item_list[count_1].index_item_count,
				index_item_list[count_1].index_item_list, indent + 3,
				output_function, output_control, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			(*output_function)(output_control, "</UL>\n");
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RTF_DoComment(const char *in_string,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_RTF_DoComment(in_string, output_function, output_control)
const char  *in_string;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	(*output_function)(output_control, "{\\comment %-*.*s}\n", 68, 68,
		in_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RTF_DoCommentsFloating(const char *in_string_1,
	const char *in_string_2, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_RTF_DoCommentsFloating(in_string_1, in_string_2,
	output_function, output_control)
const char  *in_string_1;
const char  *in_string_2;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	char buffer[68 + 1];

	if ((strlen(in_string_1) + strlen(in_string_2)) <= 68)
		ADF_RTF_DoComment(strcat(strcpy(buffer, in_string_1), in_string_2),
			output_function, output_control);
	else
		(*output_function)(output_control, "{\\comment %s%s}\n",
			in_string_1, in_string_2);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_RTF_DoBorder(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_RTF_DoBorder(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	(*output_function)(output_control, "{\\comment ");
	STR_EMIT_Char('*', 68, output_function, output_control);
	(*output_function)(output_control, "}\n");
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

	fprintf(stderr, "Test routine for 'ADF_RTF_OutputToStdout()'\n");
	fprintf(stderr, "---- ------- --- --------------------------\n\n");

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
			if ((return_code = ADF_RTF_OutputInit(&control_data,
				error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			ADF_RTF_OutputStart(&control_data, "Output to <stdout>", NULL,
				STR_FUNC_TYPE_fprintf_CAST(fprintf), stdout);
			for (count_1 = 0; count_1 < control_data.in_entry_order_count;
				count_1++) {
/*
				STR_EMIT_CharLine('=', 78, NULL, NULL);
*/
				if ((return_code = ADF_RTF_OutputToStdout(&control_data,
					control_data.in_entry_order_list[count_1], NULL,
					error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				fprintf(stderr, ".");
/*
				STR_EMIT_CharLine('=', 78, NULL, NULL);
*/
			}
			ADF_RTF_OutputEnd(&control_data, STR_FUNC_TYPE_fprintf_CAST(fprintf),
				stdout);
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

