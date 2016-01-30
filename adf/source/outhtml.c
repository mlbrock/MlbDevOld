/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits an ADF entry in Hyper Text Mark-up Language
								(HTML) format.

	Revision History	:	1995-07-25 --- Creation.
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
#ifndef __MSDOS__
static const char *ADF_HTML_CharRefString =
	"<>&\"";
#else
static const char *ADF_HTML_CharRefString =
	"<>&\"€‚ƒ„…†‡ˆ‰Š‹ŒŽ‘’“”•–—˜™š›œ ¡¢£¤¥¨ª«¬­®¯³ñöúý";
#endif /* #ifndef __MSDOS__ */

static const char *ADF_HTML_CharRefList[] = {
	"lt",		"gt",			"amp",		"quot",	"#182",		"#167",		"Ccedil",
	"uuml",	"eacute",	"acirc",		"auml",	"agrave",	"aring",		"ccedil",
	"ecirc",	"euml",		"egrave",	"iuml",	"icirc",		"igrave",	"Auml",
	"Aring",	"Eacute",	"aelig",		"AElig",	"ocirc",		"ouml",		"ograve",
	"ucirc",	"ugrave",	"yuml",		"Ouml",	"Uuml",		"#162",		"#163",
	"#165",	"aacute",	"iacute",	"oacute","uacute",	"ntilde",	"Ntilde",
	"#191",	"#172",		"#189",		"#188",	"#161",		"#171",		"#187",
	"#166",	"#177",		"#247",		"#183",	"#178"
};
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void  ADF_HTML_DoHeaderByEntry,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_HTML_DoHeaderByFile,
	(const ADF_CONTROL *control_ptr,
	unsigned int entry_index, const time_t *output_date,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(int   ADF_HTML_OutputBasic,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_HTML_OutputSection,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	int format_flag, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_HTML_OutputCodeSyntax,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_HTML_OutputSeeAlso,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_HTML_EmitParaText,
	(ADF_CONTROL *control_ptr,
	unsigned int area_index, const ADF_ENTRY *entry_ptr,
	unsigned int para_line_count, const ADF_PARA_TEXT *para_line_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_HTML_EmitPlainParaText,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int para_line_count,
	const ADF_PARA_TEXT *para_line_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(void  ADF_HTML_OutputString,
	(const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_HTML_OutputText,
	(unsigned int out_length,
	const char *out_text, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(int   ADF_HTML_EmitAnchor,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int htext_index, int external_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int   ADF_HTML_DoAutoLink,
	(ADF_CONTROL *control_ptr,
	unsigned int area_index, unsigned int in_length, const char *in_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(char *ADF_HTML_MakePostText,
	(unsigned int indent_level,
	ADF_PFORMAT *pfmt_flag[ADF_PFORMAT_LEVEL_COUNT][ADF_PFORMAT_TYPE_COUNT],
	char *post_text));
COMPAT_FN_DECL_STATIC(int   ADF_HTML_EmitIndexList,
	(ADF_CONTROL *control_ptr,
	unsigned int index_item_count, const ADF_INDEX_ITEM *index_item_list,
	unsigned int indent, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL_STATIC(void  ADF_HTML_DoComment,
	(const char *in_string, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_HTML_DoCommentsFloating,
	(const char *in_string_1, const char *in_string_2,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void  ADF_HTML_DoBorder,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_HTML_OutputByEntry(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, char *error_text)
#else
int ADF_HTML_OutputByEntry(control_ptr, entry_ptr, error_text)
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
		sprintf(control_ptr->output_file_name, "%s%s%s.html",
			(control_ptr->output_dir == NULL) ? "" : control_ptr->output_dir,
			(control_ptr->output_dir == NULL) ? "" : "/", entry_ptr->base_name);
		ADF_OUT_CleanName(control_ptr->output_file_name);
		if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
			error_text)) == ADF_SUCCESS) {
			if ((return_code = ADF_GetEntry(control_ptr, entry_ptr,
				entry_data_list, error_text)) == ADF_SUCCESS) {
				return_code = ADF_HTML_OutputBasic(control_ptr, entry_ptr,
					entry_data_list, NULL, STR_FUNC_TYPE_fprintf_CAST(fprintf),
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
int ADF_HTML_OutputToStdout(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text)
#else
int ADF_HTML_OutputToStdout(control_ptr, entry_ptr, output_date, error_text)
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
		return_code = ADF_HTML_OutputBasic(control_ptr, entry_ptr,
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
int ADF_HTML_OutputByFile(ADF_CONTROL *control_ptr, unsigned int *entry_index,
	char *error_text)
#else
int ADF_HTML_OutputByFile(control_ptr, entry_index, error_text)
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
			if ((return_code = ADF_OUT_AllocFileString(control_ptr, alloc_length,
				error_text)) != ADF_SUCCESS)
				break;
			sprintf(control_ptr->output_file_name, "%s%s%s.html",
				(control_ptr->output_dir == NULL) ? "" : control_ptr->output_dir,
				(control_ptr->output_dir == NULL) ? "" : "/", core_name);
			ADF_OUT_CleanName(control_ptr->output_file_name);
			if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
				error_text)) != ADF_SUCCESS)
				break;
			time(&output_date);
			if (control_ptr->output_comment_flag == ADF_TRUE)
				ADF_HTML_DoHeaderByFile(control_ptr, *entry_index, &output_date,
					STR_FUNC_TYPE_fprintf_CAST(fprintf), control_ptr->output_file_ptr);
		}
		else
			fprintf(control_ptr->output_file_ptr, "\n");
		if ((return_code = ADF_GetEntry(control_ptr, entry_ptr, entry_data_list,
			error_text)) != ADF_SUCCESS)
			break;
		return_code = ADF_HTML_OutputBasic(control_ptr, entry_ptr,
			entry_data_list, &output_date, STR_FUNC_TYPE_fprintf_CAST(fprintf),
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
int ADF_HTML_OutputTOC(ADF_CONTROL *control_ptr, char *error_text)
#else
int ADF_HTML_OutputTOC(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	unsigned char  last_char   = UCHAR_MAX;
	unsigned int   count_1;
	unsigned int   found_index;
	ADF_ENTRY     *entry_ptr;
	STR_FUNC_TYPE_fprintf  output_function;
	void                  *output_control;
   char            tmp_buffer[256];
	char            date_buffer[100 + ADF_AREA_NAME_LENGTH + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	SDTIF_Format_time_t(NULL, date_buffer);
	date_buffer[10] = '\0';

	if (control_ptr->output_comment_flag == ADF_TRUE) {
		ADF_HTML_DoBorder(output_function, output_control);
		ADF_HTML_DoComment("Documentation Table of Contents", output_function,
			output_control);
		ADF_HTML_DoComment("", output_function, output_control);
		ADF_HTML_DoComment(
			"   Created by the Automated Documentation Facility (ADF)",
			output_function, output_control);
		ADF_HTML_DoBorder(output_function, output_control);
		ADF_HTML_DoComment("", output_function, output_control);
		sprintf(tmp_buffer, "Creation Date: %s", date_buffer);
		ADF_HTML_DoComment(tmp_buffer, output_function, output_control);
		sprintf(tmp_buffer, "Creation Time:   %s", date_buffer + 11);
		ADF_HTML_DoComment(tmp_buffer, output_function, output_control);
		ADF_HTML_DoComment("", output_function, output_control);
		ADF_HTML_DoBorder(output_function, output_control);
	}

	(*output_function)(output_control, "<HTML>\n");
	(*output_function)(output_control, "<HEAD>\n");
	(*output_function)(output_control,
		"<TITLE>Documentation Table of Contents</TITLE>\n");
	(*output_function)(output_control, "</HEAD>\n");
	(*output_function)(output_control, "<HR>\n");

	for (count_1 = 0; count_1 < control_ptr->in_entry_order_count; count_1++) {
		entry_ptr = control_ptr->in_entry_order_list[count_1];
		if (last_char != ADF_DICT_ORDER_CHAR(*entry_ptr->base_name)) {
			(*output_function)(output_control, "<P>\n");
			last_char = ADF_DICT_ORDER_CHAR(*entry_ptr->base_name);
		}
		if ((ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
			control_ptr->in_htext_list, entry_ptr->base_name, &found_index) ==
			STRFUNCS_ITEM_FOUND) && (entry_ptr->file_index ==
			control_ptr->in_htext_list[found_index].file_index) &&
			(entry_ptr->entry_index ==
			control_ptr->in_htext_list[found_index].entry_index)) {
			if ((return_code = ADF_HTML_EmitAnchor(control_ptr, NULL,
				found_index, ADF_TRUE, 	output_function, output_control,
				error_text)) != ADF_SUCCESS)
				break;
			ADF_HTML_OutputString(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "</A><BR>\n");
		}
		else {
			ADF_HTML_OutputString(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "<BR>\n");
		}
	}

	(*output_function)(output_control, "<HR>\n");
	(*output_function)(output_control, "</BODY>\n</HTML>\n");

	if (control_ptr->output_comment_flag == ADF_TRUE) {
		ADF_HTML_DoBorder(output_function, output_control);
		ADF_HTML_DoComment("End of HTML Table of Contents", output_function,
			output_control);
		ADF_HTML_DoBorder(output_function, output_control);
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
int ADF_HTML_OutputClassTOC(ADF_CONTROL *control_ptr, char *error_text)
#else
int ADF_HTML_OutputClassTOC(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code;
	unsigned int     count_1;
	unsigned int     index_item_count;
	ADF_INDEX_ITEM  *index_item_list;
	unsigned char    last_char = UCHAR_MAX;
	STR_FUNC_TYPE_fprintf  output_function;
	void                  *output_control;
	int              ignore_section_list[ADF_AREA_COUNT];
   char             tmp_buffer[256];
	char             date_buffer[100 + ADF_AREA_NAME_LENGTH + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	SDTIF_Format_time_t(NULL, date_buffer);
	date_buffer[10] = '\0';

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Save the old state of the ignore section flags, and set all		*/
	/*	of them to 'TRUE' (except for the required sections and the index	*/
	/*	section).																			*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		ignore_section_list[count_1] =
			control_ptr->ignore_section_list[count_1];
		control_ptr->ignore_section_list[count_1] =
			((count_1 != ADF_AREA_ENTRY_CLASS_NAME) &&
			(ADF_AreaNameList[count_1].required_flag != ADF_TRUE)) ? ADF_TRUE :
			ADF_FALSE;
	}
	/*	*****************************************************************	*/

	if ((return_code = ADF_BuildClassTOCItemList(control_ptr,
		&index_item_count, &index_item_list, error_text)) == ADF_SUCCESS) {
		if (control_ptr->output_comment_flag == ADF_TRUE) {
			ADF_HTML_DoBorder(output_function, output_control);
			ADF_HTML_DoComment("Documentation Class Table of Contents",
				output_function, output_control);
			ADF_HTML_DoComment("", output_function, output_control);
			ADF_HTML_DoComment(
				"   Created by the Automated Documentation Facility (ADF)",
				output_function, output_control);
			ADF_HTML_DoBorder(output_function, output_control);
			ADF_HTML_DoComment("", output_function, output_control);
			sprintf(tmp_buffer, "Creation Date: %s", date_buffer);
			ADF_HTML_DoComment(tmp_buffer, output_function, output_control);
			sprintf(tmp_buffer, "Creation Time:   %s", date_buffer + 11);
			ADF_HTML_DoComment(tmp_buffer, output_function, output_control);
			ADF_HTML_DoComment("", output_function, output_control);
			ADF_HTML_DoBorder(output_function, output_control);
		}
		(*output_function)(output_control, "<HTML>\n");
		(*output_function)(output_control, "<HEAD>\n");
		(*output_function)(output_control,
			"<TITLE>Document Class Table of Contents</TITLE>\n");
		(*output_function)(output_control, "</HEAD>\n");
		(*output_function)(output_control, "<HR>\n");
		for (count_1 = 0; count_1 < index_item_count; count_1++) {
			if (last_char != index_item_list[count_1].item_order) {
				last_char = index_item_list[count_1].item_order;
				if (last_char == '\0')
					(*output_function)(output_control,
						"<A HREF=\"#%s\">Symbols</A>\n",
						"__INTERNAL_INDEX_SYMBOL__");
				else if (last_char == '\1')
					(*output_function)(output_control,
						"<A HREF=\"#%s\">Numerics</A>\n",
						"__INTERNAL_INDEX_NUMERIC__");
				else
					(*output_function)(output_control,
						"<A HREF=\"#%s_%c__\">%c</A>\n",
						"__INTERNAL_INDEX_CHARACTER", last_char, last_char);
			}
		}
		(*output_function)(output_control, "<HR>\n");
		if ((return_code = ADF_HTML_EmitIndexList(control_ptr, index_item_count,
			index_item_list, 0, output_function, output_control, error_text)) ==
			ADF_SUCCESS) {
			(*output_function)(output_control, "<HR>\n");
			(*output_function)(output_control, "</BODY>\n</HTML>\n");
			if (control_ptr->output_comment_flag == ADF_TRUE) {
				ADF_HTML_DoBorder(output_function, output_control);
				ADF_HTML_DoComment("End of HTML Class Table of Contents",
					output_function, output_control);
				ADF_HTML_DoBorder(output_function, output_control);
			}
		}
		ADF_FreeIndexItemList(&index_item_count, &index_item_list);
	}

	if (control_ptr->quiet_flag != ADF_TRUE) {
		if (return_code != ADF_SUCCESS)
			fprintf(stderr, "ERROR: %s\n", error_text);
		else
			fprintf(stderr, "OK\n");
	}


	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Restore the original ignore section flags.							*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++)
		control_ptr->ignore_section_list[count_1] =
			ignore_section_list[count_1];
	/*	*****************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_HTML_OutputTOF(ADF_CONTROL *control_ptr, char *error_text)
#else
int ADF_HTML_OutputTOF(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code = ADF_SUCCESS;
	unsigned int   count_1;
	unsigned int   found_index;
	ADF_ENTRY     *entry_ptr;
	char          *file_name;
	STR_FUNC_TYPE_fprintf  output_function;
	void                  *output_control;
   char            tmp_buffer[256];
	char            date_buffer[100 + ADF_AREA_NAME_LENGTH + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	file_name       = "";

	SDTIF_Format_time_t(NULL, date_buffer);
	date_buffer[10] = '\0';

	if (control_ptr->output_comment_flag == ADF_TRUE) {
		ADF_HTML_DoBorder(output_function, output_control);
		ADF_HTML_DoComment("Documentation Table of Files", output_function,
			output_control);
		ADF_HTML_DoComment("", output_function, output_control);
		ADF_HTML_DoComment(
			"   Created by the Automated Documentation Facility (ADF)",
			output_function, output_control);
		ADF_HTML_DoBorder(output_function, output_control);
		ADF_HTML_DoComment("", output_function, output_control);
		sprintf(tmp_buffer, "Creation Date: %s", date_buffer);
		ADF_HTML_DoComment(tmp_buffer, output_function, output_control);
		sprintf(tmp_buffer, "Creation Time:   %s", date_buffer + 11);
		ADF_HTML_DoComment(tmp_buffer, output_function, output_control);
		ADF_HTML_DoComment("", output_function, output_control);
		ADF_HTML_DoBorder(output_function, output_control);
	}

	(*output_function)(output_control, "<HTML>\n");
	(*output_function)(output_control, "<HEAD>\n");
	(*output_function)(output_control,
		"<TITLE>Documentation Table of Files</TITLE>\n");
	(*output_function)(output_control, "</HEAD>\n");
	(*output_function)(output_control, "<HR>\n");

	for (count_1 = 0; count_1 < control_ptr->in_entry_order_count; ) {
		file_name = control_ptr->in_entry_order_list[count_1]->file_name;
		(*output_function)(output_control, "<P>%s<P>\n<UL>\n", file_name);
		for ( ; (count_1 < control_ptr->in_entry_order_count) &&
			(!strcmp(control_ptr->in_entry_order_list[count_1]->file_name,
			file_name)); count_1++) {
			entry_ptr = control_ptr->in_entry_order_list[count_1];
			(*output_function)(output_control, "<LI>");
			if ((ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
				control_ptr->in_htext_list, entry_ptr->base_name, &found_index) ==
				STRFUNCS_ITEM_FOUND) && (entry_ptr->file_index ==
				control_ptr->in_htext_list[found_index].file_index) &&
				(entry_ptr->entry_index ==
				control_ptr->in_htext_list[found_index].entry_index)) {
				if ((return_code = ADF_HTML_EmitAnchor(control_ptr, NULL,
					found_index, ADF_TRUE, 	output_function, output_control,
					error_text)) != ADF_SUCCESS)
					break;
				ADF_HTML_OutputString(entry_ptr->base_name, output_function,
					output_control);
				(*output_function)(output_control, "</A><BR>\n");
			}
			else {
				ADF_HTML_OutputString(entry_ptr->base_name, output_function,
					output_control);
				(*output_function)(output_control, "<BR>\n");
			}
		}
		(*output_function)(output_control, "</UL>\n");
	}

	(*output_function)(output_control, "<HR>\n");
	(*output_function)(output_control, "</BODY>\n</HTML>\n");

	if (control_ptr->output_comment_flag == ADF_TRUE) {
		ADF_HTML_DoBorder(output_function, output_control);
		ADF_HTML_DoComment("End of HTML Table of Files", output_function,
			output_control);
		ADF_HTML_DoBorder(output_function, output_control);
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
int ADF_HTML_OutputIndex(ADF_CONTROL *control_ptr, char *error_text)
#else
int ADF_HTML_OutputIndex(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code;
	unsigned int     count_1;
	unsigned int     index_item_count;
	ADF_INDEX_ITEM  *index_item_list;
	unsigned char    last_char = UCHAR_MAX;
	STR_FUNC_TYPE_fprintf  output_function;
	void                  *output_control;
	int              ignore_section_list[ADF_AREA_COUNT];
   char             tmp_buffer[256];
	char             date_buffer[100 + ADF_AREA_NAME_LENGTH + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	SDTIF_Format_time_t(NULL, date_buffer);
	date_buffer[10] = '\0';

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Save the old state of the ignore section flags, and set all		*/
	/*	of them to 'TRUE' (except for the required sections and the index	*/
	/*	section).																			*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		ignore_section_list[count_1] =
			control_ptr->ignore_section_list[count_1];
		control_ptr->ignore_section_list[count_1] =
			((count_1 != ADF_AREA_OUTPUT_INDEX) &&
			(ADF_AreaNameList[count_1].required_flag != ADF_TRUE)) ? ADF_TRUE :
			ADF_FALSE;
	}
	/*	*****************************************************************	*/

	if ((return_code = ADF_BuildIndexItemList(control_ptr, &index_item_count,
		&index_item_list, error_text)) == ADF_SUCCESS) {
		if (control_ptr->output_comment_flag == ADF_TRUE) {
			ADF_HTML_DoBorder(output_function, output_control);
			ADF_HTML_DoComment("Documentation Index", output_function,
				output_control);
			ADF_HTML_DoComment("", output_function, output_control);
			ADF_HTML_DoComment(
				"   Created by the Automated Documentation Facility (ADF)",
				output_function, output_control);
			ADF_HTML_DoBorder(output_function, output_control);
			ADF_HTML_DoComment("", output_function, output_control);
			sprintf(tmp_buffer, "Creation Date: %s", date_buffer);
			ADF_HTML_DoComment(tmp_buffer, output_function, output_control);
			sprintf(tmp_buffer, "Creation Time:   %s", date_buffer + 11);
			ADF_HTML_DoComment(tmp_buffer, output_function, output_control);
			ADF_HTML_DoComment("", output_function, output_control);
			ADF_HTML_DoBorder(output_function, output_control);
		}
		(*output_function)(output_control, "<HTML>\n");
		(*output_function)(output_control, "<HEAD>\n");
		(*output_function)(output_control,
			"<TITLE>Documentation Index</TITLE>\n");
		(*output_function)(output_control, "</HEAD>\n");
		(*output_function)(output_control, "<HR>\n");
		for (count_1 = 0; count_1 < index_item_count; count_1++) {
			if (last_char != index_item_list[count_1].item_order) {
				last_char = index_item_list[count_1].item_order;
				if (last_char == '\0')
					(*output_function)(output_control,
						"<A HREF=\"#%s\">Symbols</A>\n",
						"__INTERNAL_INDEX_SYMBOL__");
				else if (last_char == '\1')
					(*output_function)(output_control,
						"<A HREF=\"#%s\">Numerics</A>\n",
						"__INTERNAL_INDEX_NUMERIC__");
				else
					(*output_function)(output_control,
						"<A HREF=\"#%s_%c__\">%c</A>\n",
						"__INTERNAL_INDEX_CHARACTER", last_char, last_char);
			}
		}
		(*output_function)(output_control, "<HR>\n");
		if ((return_code = ADF_HTML_EmitIndexList(control_ptr, index_item_count,
			index_item_list, 0, output_function, output_control, error_text)) ==
			ADF_SUCCESS) {
			(*output_function)(output_control, "<HR>\n");
			(*output_function)(output_control, "</BODY>\n</HTML>\n");
			if (control_ptr->output_comment_flag == ADF_TRUE) {
				ADF_HTML_DoBorder(output_function, output_control);
				ADF_HTML_DoComment("End of HTML Index", output_function,
					output_control);
				ADF_HTML_DoBorder(output_function, output_control);
			}
		}
		ADF_FreeIndexItemList(&index_item_count, &index_item_list);
	}

	if (control_ptr->quiet_flag != ADF_TRUE) {
		if (return_code != ADF_SUCCESS)
			fprintf(stderr, "ERROR: %s\n", error_text);
		else
			fprintf(stderr, "OK\n");
	}


	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Restore the original ignore section flags.							*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++)
		control_ptr->ignore_section_list[count_1] =
			ignore_section_list[count_1];
	/*	*****************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_HTML_OutputPermIndex(ADF_CONTROL *control_ptr, char *error_text)
#else
int ADF_HTML_OutputPermIndex(control_ptr, error_text)
ADF_CONTROL *control_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     index_item_count;
	ADF_PERM_INDEX  *index_item_list;
	unsigned int     found_index;
	unsigned char    last_char = UCHAR_MAX;
	ADF_ENTRY       *entry_ptr;
	STR_FUNC_TYPE_fprintf  output_function;
	void                  *output_control;
   char             tmp_buffer[256];
	char             date_buffer[100 + ADF_AREA_NAME_LENGTH + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	SDTIF_Format_time_t(NULL, date_buffer);
	date_buffer[10] = '\0';

	if ((return_code = ADF_BuildPermIndex(control_ptr, &index_item_count,
		&index_item_list, error_text)) == ADF_SUCCESS) {
		if (control_ptr->output_comment_flag == ADF_TRUE) {
			ADF_HTML_DoBorder(output_function, output_control);
			ADF_HTML_DoComment("Documentation Permutated Index", output_function,
				output_control);
			ADF_HTML_DoComment("", output_function, output_control);
			ADF_HTML_DoComment(
				"   Created by the Automated Documentation Facility (ADF)",
				output_function, output_control);
			ADF_HTML_DoBorder(output_function, output_control);
			ADF_HTML_DoComment("", output_function, output_control);
			sprintf(tmp_buffer, "Creation Date: %s", date_buffer);
			ADF_HTML_DoComment(tmp_buffer, output_function, output_control);
			sprintf(tmp_buffer, "Creation Time:   %s", date_buffer + 11);
			ADF_HTML_DoComment(tmp_buffer, output_function, output_control);
			ADF_HTML_DoComment("", output_function, output_control);
			ADF_HTML_DoBorder(output_function, output_control);
		}
		(*output_function)(output_control, "<HTML>\n");
		(*output_function)(output_control, "<HEAD>\n");
		(*output_function)(output_control,
			"<TITLE>Documentation Permutated Index</TITLE>\n");
		(*output_function)(output_control, "</HEAD>\n");
		(*output_function)(output_control, "<HR>\n");
		for (count_1 = 0; count_1 < index_item_count; count_1++) {
			if (last_char != index_item_list[count_1].item_order) {
				last_char = index_item_list[count_1].item_order;
				if (last_char == '\0')
					(*output_function)(output_control,
						"<A HREF=\"#%s\">Symbols</A>\n",
						"__INTERNAL_INDEX_SYMBOL__");
				else if (last_char == '\1')
					(*output_function)(output_control,
						"<A HREF=\"#%s\">Numerics</A>\n",
						"__INTERNAL_INDEX_NUMERIC__");
				else
					(*output_function)(output_control,
						"<A HREF=\"#%s_%c__\">%c</A>\n",
						"__INTERNAL_INDEX_CHARACTER", last_char, last_char);
			}
		}
		(*output_function)(output_control, "<HR>\n");
		last_char = UCHAR_MAX;
		for (count_1 = 0; count_1 < index_item_count; count_1++) {
			entry_ptr = control_ptr->in_entry_list +
				index_item_list[count_1].entry_index;
			if (last_char != index_item_list[count_1].item_order) {
				(*output_function)(output_control, "<P>\n");
				last_char = index_item_list[count_1].item_order;
				if (last_char == '\0')
					(*output_function)(output_control,
						"<A NAME=\"%s\"></A><B>--- Symbols ---</B><BR>\n",
						"__INTERNAL_INDEX_SYMBOL__");
				else if (last_char == '\1')
					(*output_function)(output_control,
						"<A NAME=\"%s\"></A><B>--- Numerics ---</B><BR>\n",
						"__INTERNAL_INDEX_NUMERIC__");
				else
					(*output_function)(output_control,
						"<A NAME=\"%s_%c__\"></A><B>--- %c ---</B><BR>\n",
						"__INTERNAL_INDEX_CHARACTER", last_char, last_char);
			}
			if ((ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
				control_ptr->in_htext_list, entry_ptr->base_name, &found_index) !=
				STRFUNCS_ITEM_FOUND) || (entry_ptr->file_index !=
				control_ptr->in_htext_list[found_index].file_index) ||
				(entry_ptr->entry_index !=
				control_ptr->in_htext_list[found_index].entry_index))
				continue;
			if ((return_code = ADF_HTML_EmitAnchor(control_ptr, NULL,
				found_index, ADF_TRUE, output_function, output_control,
				error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			ADF_HTML_OutputString(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "</A><BR>\n");
			(*output_function)(output_control, "<UL>\n");
			for (count_2 = 0; count_2 < index_item_list[count_1].ref_count;
				count_2++) {
				entry_ptr = control_ptr->in_entry_list +
					index_item_list[count_1].ref_list[count_2];
				if ((ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
					control_ptr->in_htext_list, entry_ptr->base_name,
					&found_index) != STRFUNCS_ITEM_FOUND) ||
					(entry_ptr->file_index !=
					control_ptr->in_htext_list[found_index].file_index) ||
					(entry_ptr->entry_index !=
					control_ptr->in_htext_list[found_index].entry_index))
					continue;
				if ((return_code = ADF_HTML_EmitAnchor(control_ptr, NULL,
					found_index, ADF_TRUE, output_function, output_control,
					error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				ADF_HTML_OutputString(entry_ptr->base_name, output_function,
					output_control);
				(*output_function)(output_control, "</A><BR>\n");
			}
			(*output_function)(output_control, "</UL>\n");
		}
		(*output_function)(output_control, "<HR>\n");
		(*output_function)(output_control, "</BODY>\n</HTML>\n");
		if (control_ptr->output_comment_flag == ADF_TRUE) {
			ADF_HTML_DoBorder(output_function, output_control);
			ADF_HTML_DoComment("End of HTML Permutated Index",
				output_function, output_control);
			ADF_HTML_DoBorder(output_function, output_control);
		}
	}

	if (control_ptr->quiet_flag != ADF_TRUE) {
		if (return_code != ADF_SUCCESS)
			fprintf(stderr, "ERROR: %s\n", error_text);
		else
			fprintf(stderr, "OK\n");
	}

EXIT_FUNCTION:

	ADF_FreePermIndexList(&index_item_count, &index_item_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_HTML_DoHeaderByEntry(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_HTML_DoHeaderByEntry(control_ptr, entry_ptr, entry_data_list,
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

	ADF_HTML_DoBorder(output_function, output_control);
	ADF_HTML_DoBorder(output_function, output_control);
	ADF_HTML_DoCommentsFloating("Documentation for ", entry_ptr->base_name,
		output_function, output_control);
	ADF_HTML_DoComment("", output_function, output_control);
	ADF_HTML_DoComment(
		"   Created by the Automated Documentation Facility (ADF)",
		output_function, output_control);
	ADF_HTML_DoBorder(output_function, output_control);

	ADF_HTML_DoComment("", output_function, output_control);
	ADF_HTML_DoCommentsFloating("Entry Name          : ",
		entry_ptr->base_name, output_function, output_control);
	ADF_HTML_DoComment("", output_function, output_control);
	ADF_HTML_DoCommentsFloating("Source File Name    : ",
		entry_ptr->file_name, output_function, output_control);

	ADF_HTML_DoComment("", output_function, output_control);
	ADF_HTML_DoCommentsFloating("Source File Date    : ",
		strcat(SDTIF_Format_time_t_GMT(&entry_ptr->file_date, date_data),
		" GMT/UTC"), output_function, output_control);
	time_t_data = entry_ptr->file_date;
	tm_data     = *SDTIF_GetTimeLocal(&time_t_data, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_HTML_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&entry_ptr->file_date, date_data),
		time_zone_data), output_function, output_control);

	ADF_HTML_DoComment("", output_function, output_control);
	ADF_HTML_DoCommentsFloating("ADF Preparation Date: ",
		strcat(SDTIF_Format_time_t_GMT(&entry_ptr->prep_date, date_data),
		" GMT/UTC"), output_function, output_control);
	time_t_data = entry_ptr->prep_date;
	tm_data     = *SDTIF_GetTimeLocal(&time_t_data, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_HTML_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&entry_ptr->prep_date, date_data),
		time_zone_data), output_function, output_control);

	ADF_HTML_DoComment("", output_function, output_control);
	ADF_HTML_DoCommentsFloating("Output Date         : ",
		strcat(SDTIF_Format_time_t_GMT(&tmp_output_date, date_data), " GMT/UTC"),
		output_function, output_control);
	tm_data = *SDTIF_GetTimeLocal(&tmp_output_date, &tm_data);

	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_HTML_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&tmp_output_date, date_data), time_zone_data),
		output_function, output_control);

	ADF_HTML_DoComment("", output_function, output_control);
	ADF_HTML_DoBorder(output_function, output_control);
	(*output_function)(output_control, "\n");

	if ((ADF_GetAreaList(control_ptr, entry_ptr, entry_data_list +
		ADF_AREA_COPYRIGHTS, &tmp_count, &tmp_list, error_text) ==
		ADF_SUCCESS) && tmp_count) {
		ADF_HTML_DoBorder(output_function, output_control);
		ADF_HTML_DoBorder(output_function, output_control);
		for (count_1 = 0; count_1 < tmp_count; count_1++)
			ADF_HTML_DoCommentsFloating("", tmp_list[count_1],
				output_function, output_control);
		ADF_HTML_DoBorder(output_function, output_control);
		strl_remove_all(&tmp_count, &tmp_list);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_HTML_DoHeaderByFile(const ADF_CONTROL *control_ptr,
	unsigned int entry_index, const time_t *output_date,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_HTML_DoHeaderByFile(control_ptr, entry_index, output_date,
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

	ADF_HTML_DoBorder(output_function, output_control);
	ADF_HTML_DoBorder(output_function, output_control);
	ADF_HTML_DoCommentsFloating("Documentation for Entries in Source File ",
		control_ptr->in_entry_order_list[entry_index]->file_name,
		output_function, output_control);
	ADF_HTML_DoComment("", output_function, output_control);
	ADF_HTML_DoComment(
		"   Created by the Automated Documentation Facility (ADF)",
		output_function, output_control);
	ADF_HTML_DoBorder(output_function, output_control);
	ADF_HTML_DoComment("", output_function, output_control);
	ADF_HTML_DoCommentsFloating("Output Date: ",
		strcat(SDTIF_Format_time_t_GMT(&tmp_output_date, date_data), " GMT/UTC"),
		output_function, output_control);
	tm_data = *SDTIF_GetTimeLocal(&tmp_output_date, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_HTML_DoCommentsFloating("           : ",
		strcat(SDTIF_Format_time_t(&tmp_output_date, date_data), time_zone_data),
		output_function, output_control);
	ADF_HTML_DoComment("", output_function, output_control);

	for (count_1 = entry_index;
		(count_1 < control_ptr->in_entry_order_count) &&
		(!strcmp(control_ptr->in_entry_order_list[entry_index]->file_name,
		control_ptr->in_entry_order_list[count_1]->file_name)); count_1++)
		ADF_HTML_DoCommentsFloating((!count_1) ?
			"Entry Name : " : "           : ",
			control_ptr->in_entry_order_list[count_1]->base_name,
			output_function, output_control);
	ADF_HTML_DoComment("", output_function, output_control);
	ADF_HTML_DoBorder(output_function, output_control);
	(*output_function)(output_control, "\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_HTML_OutputBasic(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_HTML_OutputBasic(control_ptr, entry_ptr, entry_data_list,
	output_date, output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_list;
const time_t          *output_date;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int              return_code     = ADF_SUCCESS;
	unsigned int     area_name_count = 0;
	unsigned int     count_1;
	ADF_ENTRY_DATA  *entry_data_ptr;
	const ADF_AREA  *area_ptr;
	char             area_name[ADF_AREA_NAME_LENGTH + 1];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Emit descriptive comments for the entry . . .						*/
	/*	*****************************************************************	*/
	if (control_ptr->output_comment_flag == ADF_TRUE)
		ADF_HTML_DoHeaderByEntry(control_ptr, entry_ptr, entry_data_list,
			output_date, output_function, output_control);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Order the sections of the entry as specified . . .					*/
	/*	*****************************************************************	*/
	if (control_ptr->area_order_type != ADF_AREA_ORDER_TYPE_INTERNAL)
		ADF_SORT_EntrySections(control_ptr->area_order_type, entry_data_list);
	/*	*****************************************************************	*/

	(*output_function)(output_control, "<HTML>\n");

	(*output_function)(output_control, "<HEAD>\n");
	(*output_function)(output_control, "<TITLE>%s</TITLE>\n",
		entry_ptr->base_name);
	(*output_function)(output_control, "</HEAD>\n");

	(*output_function)(output_control, "<BODY>\n");

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		entry_data_ptr = entry_data_list + count_1;
		area_ptr       = ADF_AreaNameList + entry_data_ptr->area_index;
		if ((area_ptr->output_flag != ADF_TRUE) ||
			(!entry_data_ptr->para_count))
			continue;
		if ((control_ptr->hyper_text_flag == ADF_TRUE) &&
			(entry_data_ptr->area_index == ADF_AREA_NAME)) {
			(*output_function)(output_control, "<A NAME=\"");
			ADF_HTML_OutputString(entry_ptr->base_name, output_function,
				output_control);
			(*output_function)(output_control, "\"></A>\n");
		}
		(*output_function)(output_control, "%s<H%s>",
			(area_name_count++) ? "<P>\n" : "",
			control_ptr->html_data.html_heading_level);
		ADF_GetOutputAreaName(control_ptr->area_name_type,
			entry_data_ptr->area_index, control_ptr->area_name_list,
			entry_data_ptr->section_name, sizeof(area_name) - 1, area_name);
		if (entry_data_ptr->area_index == ADF_AREA_CODE_SYNTAX) {
			ADF_HTML_OutputString(area_name, output_function, output_control);
			(*output_function)(output_control, "</H%s><HR><PRE WIDTH=80>",
				control_ptr->html_data.html_heading_level);
			if ((return_code = ADF_HTML_OutputCodeSyntax(control_ptr, entry_ptr,
				entry_data_ptr, output_function, output_control, error_text)) !=
				ADF_SUCCESS)
				break;
			(*output_function)(output_control, "</PRE><HR>");
			continue;
		}
		else if (entry_data_ptr->area_index == ADF_AREA_SEE_ALSO) {
			ADF_HTML_OutputString(area_name, output_function, output_control);
			(*output_function)(output_control, "</H%s>\n",
				control_ptr->html_data.html_heading_level);
			if ((return_code = ADF_HTML_OutputSeeAlso(control_ptr, entry_ptr,
				entry_data_ptr, output_function, output_control, error_text)) !=
				ADF_SUCCESS)
				break;
			continue;
		}
		ADF_HTML_OutputString(area_name, output_function, output_control);
		(*output_function)(output_control, "</H%s>\n",
			control_ptr->html_data.html_heading_level);
		if ((return_code = ADF_HTML_OutputSection(control_ptr, entry_ptr,
			entry_data_ptr, area_ptr->pformat_flag, output_function,
			output_control, error_text)) != ADF_SUCCESS)
			break;
	}

	if (return_code == ADF_SUCCESS) {
		(*output_function)(output_control, "\n</BODY>\n</HTML>\n");
		if (control_ptr->output_comment_flag == ADF_TRUE) {
			ADF_HTML_DoBorder(output_function, output_control);
			ADF_HTML_DoCommentsFloating("End of HTML Script for ",
				entry_ptr->base_name, output_function, output_control);
			ADF_HTML_DoBorder(output_function, output_control);
			ADF_HTML_DoBorder(output_function, output_control);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_HTML_OutputSection(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	int format_flag, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_HTML_OutputSection(control_ptr, entry_ptr, entry_data_ptr,
	format_flag, output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_ptr;
int                    format_flag;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int            return_code      = ADF_SUCCESS;
	int            char_format_flag = ADF_TRUE;
	unsigned int   count_1;
	unsigned int   count_2;
	unsigned int   cformat_type;
	ADF_PARA_DATA *para_ptr;
	char          *primary_leader;
	char          *para_trailer;
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

	cformat_type = (format_flag == ADF_TRUE) ? ADF_HTML_CFORMAT_TYPE :
		((control_ptr->hyper_text_flag != ADF_TRUE) ? 0 :
		ADF_CFORMAT_TYPE_HTEXT);

	if ((cformat_type & ADF_CFORMAT_TYPE_HTEXT) &&
		(control_ptr->hyper_text_flag != ADF_TRUE))
		cformat_type ^= ADF_CFORMAT_TYPE_HTEXT;

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		para_ptr       = entry_data_ptr->para_list + count_1;
		pfmt_ptr       = &para_ptr->para_format;
		primary_leader = NULL;
		para_trailer   = NULL;
		*post_text     = '\0';
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr, para_ptr,
			cformat_type, error_text)) != ADF_SUCCESS)
			break;
		if ((pfmt_ptr->pformat_flag != ADF_TRUE) || (format_flag != ADF_TRUE)) {
			(*output_function)(output_control, "%s%s", ADF_HTML_MakePostText(0,
				pfmt_flag, post_text), "<P>");
			*post_text       = '\0';
			para_trailer     = ((pfmt_ptr->pformat_flag == ADF_TRUE) &&
				(pfmt_ptr->end_rule_flag == ADF_TRUE))   ? "<HR>" : NULL;
			char_format_flag = (pfmt_ptr->pformat_flag != ADF_TRUE) ? ADF_TRUE :
				pfmt_ptr->char_format_flag;
			if ((pfmt_ptr->pformat_flag == ADF_TRUE) &&
				(pfmt_ptr->begin_rule_flag == ADF_TRUE))
				(*output_function)(output_control, "<HR>");
			if ((pfmt_ptr->pformat_flag == ADF_TRUE) &&
				(pfmt_ptr->char_format_flag != ADF_TRUE) &&
				(pfmt_ptr->small_font_flag == ADF_TRUE)) {
				(*output_function)(output_control, "<PRE WIDTH=80>");
				para_trailer = (pfmt_ptr->end_rule_flag == ADF_TRUE) ?
					"</PRE><HR>" : "</PRE>";
			}
		}
		else {
			pfmt_flag[pfmt_ptr->indent_level][pfmt_ptr->format_type] = pfmt_ptr;
			switch (pfmt_ptr->format_type) {
				case ADF_PFORMAT_TYPE_NONE	:
					ADF_HTML_MakePostText(pfmt_ptr->indent_level, pfmt_flag,
						post_text);
					(*output_function)(output_control, "%s<P>", post_text);
					*post_text       = '\0';
					primary_leader   = NULL;
					para_trailer     = (pfmt_ptr->end_rule_flag == ADF_TRUE) ?
						"<HR>" : NULL;
					char_format_flag = pfmt_ptr->char_format_flag;
					if (pfmt_ptr->begin_rule_flag == ADF_TRUE)
						(*output_function)(output_control, "<HR>");
					if ((pfmt_ptr->char_format_flag != ADF_TRUE) &&
						(pfmt_ptr->small_font_flag == ADF_TRUE)) {
						(*output_function)(output_control, "<PRE WIDTH=80>");
						para_trailer = (pfmt_ptr->end_rule_flag == ADF_TRUE) ?
							"</PRE><HR>" : "</PRE>";
					}
					break;
				case ADF_PFORMAT_TYPE_BB	:
					ADF_HTML_MakePostText(pfmt_ptr->indent_level, pfmt_flag,
						post_text);
					(*output_function)(output_control, "%s%s", post_text,
						(pfmt_ptr->first_count) ? "<UL>\n" : "");
					*post_text       = '\0';
					primary_leader   = "<LI>";
					para_trailer     = (pfmt_ptr->end_rule_flag == ADF_TRUE) ?
						"<HR>" : NULL;
					char_format_flag = pfmt_ptr->char_format_flag;
					if (pfmt_ptr->begin_rule_flag == ADF_TRUE)
						(*output_function)(output_control, "<HR>");
					if ((pfmt_ptr->char_format_flag != ADF_TRUE) &&
						(pfmt_ptr->small_font_flag == ADF_TRUE)) {
						(*output_function)(output_control, "<PRE WIDTH=80>");
						para_trailer = (pfmt_ptr->end_rule_flag == ADF_TRUE) ?
							"</PRE><HR>" : "</PRE>";
					}
					break;
				case ADF_PFORMAT_TYPE_IN	:
					ADF_HTML_MakePostText(pfmt_ptr->indent_level, pfmt_flag,
						post_text);
					(*output_function)(output_control, "%s<P>", post_text);
					*post_text       = '\0';
					primary_leader   = NULL;
					para_trailer     = (pfmt_ptr->end_rule_flag == ADF_TRUE) ?
						"<HR>" : NULL;
					char_format_flag = pfmt_ptr->char_format_flag;
					if (pfmt_ptr->begin_rule_flag == ADF_TRUE)
						(*output_function)(output_control, "<HR>");
					if ((pfmt_ptr->char_format_flag != ADF_TRUE) &&
						(pfmt_ptr->small_font_flag == ADF_TRUE)) {
						(*output_function)(output_control, "<PRE WIDTH=80>");
						para_trailer = (pfmt_ptr->end_rule_flag == ADF_TRUE) ?
							"</PRE><HR>" : "</PRE>";
					}
					break;
				case ADF_PFORMAT_TYPE_NM	:
					ADF_HTML_MakePostText(pfmt_ptr->indent_level, pfmt_flag,
						post_text);
					(*output_function)(output_control, "%s%s", post_text,
						(pfmt_ptr->first_count) ? "<OL>\n" : "");
					*post_text       = '\0';
					primary_leader   = "<LI>";
					para_trailer     = (pfmt_ptr->end_rule_flag == ADF_TRUE) ?
						"<HR>" : NULL;
					char_format_flag = pfmt_ptr->char_format_flag;
					if (pfmt_ptr->begin_rule_flag == ADF_TRUE)
						(*output_function)(output_control, "<HR>");
					if ((pfmt_ptr->char_format_flag != ADF_TRUE) &&
						(pfmt_ptr->small_font_flag == ADF_TRUE)) {
						(*output_function)(output_control, "<PRE WIDTH=80>");
						para_trailer = (pfmt_ptr->end_rule_flag == ADF_TRUE) ?
							"</PRE><HR>" : "</PRE>";
					}
					break;
				default							:
					break;
			}
/*	CODE NOTE: To be included in the structure.
			if (pfmt_ptr->format_flag != ADF_TRUE)
				format_flag = ADF_FALSE;
*/
		}
		control_ptr->out_para_buffer[0] = '\0';
		if (primary_leader != NULL)
			(*output_function)(output_control, "%s", primary_leader);
		if (char_format_flag == ADF_TRUE) {
			if ((return_code = ADF_HTML_EmitParaText(control_ptr,
				entry_data_ptr->area_index, entry_ptr,
				control_ptr->current_para_line_count,
				control_ptr->in_para_line_list, 	output_function, output_control,
				error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
		}
		else if ((return_code = ADF_HTML_EmitPlainParaText(control_ptr,
			entry_ptr, control_ptr->current_para_line_count,
			control_ptr->in_para_line_list, output_function, output_control,
			error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		if (para_trailer != NULL)
			(*output_function)(output_control, "%s", para_trailer);
		(*output_function)(output_control, "\n");
		(*output_function)(output_control, post_text);
	}

	(*output_function)(output_control, "%s",
		ADF_HTML_MakePostText(0, pfmt_flag, post_text));

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_HTML_OutputCodeSyntax(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_HTML_OutputCodeSyntax(control_ptr, entry_ptr, entry_data_ptr,
	output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	unsigned int         return_code = ADF_SUCCESS;
	unsigned int         count_1;
	unsigned int         count_2;
	const ADF_PARA_TEXT *para_line_ptr;

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		if ((return_code = ADF_FixParagraphWrap(control_ptr, entry_ptr,
			entry_data_ptr->para_list + count_1,
			(control_ptr->hyper_text_flag != ADF_TRUE) ? 0 :
			ADF_CFORMAT_TYPE_HTEXT, 78, 3, 3, error_text)) != ADF_SUCCESS)
			break;
		para_line_ptr = control_ptr->in_para_line_list;
		for (count_2 = 0; count_2 < control_ptr->current_para_line_count;
			count_2++, para_line_ptr++) {
			if (para_line_ptr->cformat_type == ADF_CFORMAT_CHAR_HTEXT_1) {
				if ((return_code = ADF_HTML_EmitAnchor(control_ptr, entry_ptr,
					para_line_ptr->htext_index, ADF_FALSE, output_function,
					output_control, error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				continue;
			}
			else if (para_line_ptr->cformat_type == ADF_CFORMAT_CHAR_HTEXT_2) {
				(*output_function)(output_control, "</A>");
				continue;
			}
			ADF_HTML_OutputText(para_line_ptr->length, para_line_ptr->ptr,
				output_function, output_control);
		}
		if (count_1 < (entry_data_ptr->para_count - 1))
			(*output_function)(output_control, "\n");
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_HTML_OutputSeeAlso(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_HTML_OutputSeeAlso(control_ptr, entry_ptr, entry_data_ptr,
	output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr,
			entry_data_ptr->para_list + count_1,
			(control_ptr->hyper_text_flag == ADF_TRUE) ? ADF_CFORMAT_TYPE_HTEXT :
			ADF_CFORMAT_TYPE_NONE, error_text)) != ADF_SUCCESS)
			break;
		else if ((return_code = ADF_HTML_EmitParaText(control_ptr,
			entry_data_ptr->area_index, entry_ptr,
			control_ptr->current_para_line_count, control_ptr->in_para_line_list,
			output_function, output_control, error_text)) != ADF_SUCCESS)
			break;
		(*output_function)(output_control, "<BR>\n");
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_HTML_EmitParaText(ADF_CONTROL *control_ptr,
	unsigned int area_index, const ADF_ENTRY *entry_ptr,
	unsigned int para_line_count, const ADF_PARA_TEXT *para_line_list,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_HTML_EmitParaText(control_ptr, area_index, entry_ptr,
	para_line_count, para_line_list, output_function, output_control,
	error_text)
ADF_CONTROL           *control_ptr;
unsigned int           area_index;
const ADF_ENTRY       *entry_ptr;
unsigned int           para_line_count;
const ADF_PARA_TEXT   *para_line_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
	int           link_active = ADF_FALSE;
	unsigned int  count_1;
	unsigned int  in_length;
	char         *in_ptr;
   int           auto_link;

	for (count_1 = 0; count_1 < para_line_count; count_1++) {
		in_length = para_line_list[count_1].length;
		in_ptr    = para_line_list[count_1].ptr;
		if (para_line_list[count_1].cformat_type != ADF_CFORMAT_CHAR_NONE) {
			switch (para_line_list[count_1].cformat_type) {
				case ADF_CFORMAT_CHAR_BOLD_1			:
					(*output_function)(output_control, "<B>");
					break;
				case ADF_CFORMAT_CHAR_ITALIC_1		:
					(*output_function)(output_control, "<I>");
					break;
				case ADF_CFORMAT_CHAR_ULINED_1		:
					(*output_function)(output_control, "<U>");
					break;
				case ADF_CFORMAT_CHAR_STHRU_1			:
					(*output_function)(output_control, "<STRIKE>");
					break;
				case ADF_CFORMAT_CHAR_SUBSCRIPT_1	:
					(*output_function)(output_control, "<SUB>");
					break;
				case ADF_CFORMAT_CHAR_SUPERSCRIPT_1	:
					(*output_function)(output_control, "<SUP>");
					break;
				case ADF_CFORMAT_CHAR_HTEXT_1			:
					if ((return_code = ADF_HTML_EmitAnchor(control_ptr, entry_ptr,
						para_line_list[count_1].htext_index, ADF_FALSE,
						output_function, output_control, error_text)) !=
						ADF_SUCCESS)
						goto EXIT_FUNCTION;
					link_active = ADF_TRUE;
					break;
				case ADF_CFORMAT_CHAR_BOLD_2			:
					(*output_function)(output_control, "</B>");
					break;
				case ADF_CFORMAT_CHAR_ITALIC_2		:
					(*output_function)(output_control, "</I>");
					break;
				case ADF_CFORMAT_CHAR_ULINED_2		:
					(*output_function)(output_control, "</U>");
					break;
				case ADF_CFORMAT_CHAR_STHRU_2			:
					(*output_function)(output_control, "</STRIKE>");
					break;
				case ADF_CFORMAT_CHAR_SUBSCRIPT_2	:
					(*output_function)(output_control, "</SUB>");
					break;
				case ADF_CFORMAT_CHAR_SUPERSCRIPT_2	:
					(*output_function)(output_control, "</SUP>");
					break;
				case ADF_CFORMAT_CHAR_HTEXT_2			:
					(*output_function)(output_control, "</A>");
					link_active = ADF_FALSE;
					break;
				default										:
					break;
			}
			continue;
		}
		else if ((in_length) && (in_ptr != NULL)) {
			if ((link_active != ADF_TRUE) &&
				(((area_index == ADF_AREA_AUTHORS) &&
				control_ptr->html_data.author_link_count) ||
				((area_index == ADF_AREA_COPYRIGHTS) &&
				control_ptr->html_data.copyright_link_count)))
				auto_link = ADF_HTML_DoAutoLink(control_ptr, area_index,
					in_length, in_ptr, output_function, output_control);
			else
				auto_link = ADF_FALSE;
			ADF_HTML_OutputText(in_length, in_ptr, output_function,
				output_control);
			if (auto_link == ADF_TRUE)
				(*output_function)(output_control, "</A>");
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_HTML_EmitPlainParaText(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int para_line_count,
	const ADF_PARA_TEXT *para_line_list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_HTML_EmitPlainParaText(control_ptr, entry_ptr,
	para_line_count, para_line_list, output_function, output_control,
	error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
unsigned int           para_line_count;
const ADF_PARA_TEXT   *para_line_list;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = ADF_SUCCESS;
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
		if (para_line_list[count_1].cformat_type ==
			ADF_CFORMAT_CHAR_HTEXT_1) {
			if ((return_code = ADF_HTML_EmitAnchor(control_ptr, entry_ptr,
				para_line_list[count_1].htext_index, ADF_FALSE,
				output_function, output_control, error_text)) !=
				ADF_SUCCESS)
				goto EXIT_FUNCTION;
			continue;
		}
		else if (para_line_list[count_1].cformat_type ==
			ADF_CFORMAT_CHAR_HTEXT_2) {
			(*output_function)(output_control, "</A>");
			continue;
		}
		else if ((!in_length) || (in_ptr == NULL) ||
			(para_line_list[count_1].cformat_type != ADF_CFORMAT_CHAR_NONE))
			continue;
		for ( ; in_length; in_length--, in_ptr++) {
			if (*in_ptr == '\n') {
				(*output_function)(output_control, "\n");
				current_col = 0;
			}
			else if (*in_ptr == '\t') {
				space_count  = tab_setting - (current_col % tab_setting);
				current_col += space_count;
				STR_EMIT_Char(' ', space_count, output_function, output_control);
			}
			else {
				ADF_HTML_OutputText(1, in_ptr, output_function, output_control);
				current_col++;
			}
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_HTML_OutputString(const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_HTML_OutputString(out_text, output_function, output_control)
const char            *out_text;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	ADF_HTML_OutputText(strlen(out_text), out_text, output_function,
		output_control);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_HTML_OutputText(unsigned int out_length, const char *out_text,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_HTML_OutputText(out_length, out_text, output_function,
	output_control)
unsigned int           out_length;
const char            *out_text;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	int char_index;

	for ( ; out_length; out_length--, out_text++) {
		if ((char_index = idxchr(ADF_HTML_CharRefString, *out_text)) > -1)
			(*output_function)(output_control, "&%s;",
				ADF_HTML_CharRefList[char_index]);
		else
			(*output_function)(output_control, "%c", *out_text);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_HTML_EmitAnchor(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, unsigned int htext_index, int external_flag,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_HTML_EmitAnchor(control_ptr, entry_ptr, htext_index,
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
	ADF_HTEXT    *htext_ptr;
	ADF_ENTRY    *htext_entry_ptr;
	char         *output_dir;

	htext_ptr       = control_ptr->in_htext_list + htext_index;
	htext_entry_ptr = control_ptr->in_entry_list + htext_ptr->in_entry_index;
/*
	CODE NOTE: To be validated pending removal.
	output_dir      =
		(control_ptr->in_file_list[htext_entry_ptr->file_index].href_string ==
		NULL) ? control_ptr->output_dir :
		control_ptr->in_file_list[htext_entry_ptr->file_index].href_string;
*/

	output_dir      =
		(control_ptr->in_file_list[htext_entry_ptr->file_index].href_string ==
		NULL) ? control_ptr->output_dir_basic :
		control_ptr->in_file_list[htext_entry_ptr->file_index].href_string;

	alloc_length    = ((output_dir == NULL) ? 0 : strlen(output_dir)) +
		strlen(htext_entry_ptr->base_name) +
		strlen(htext_entry_ptr->core_name) + strlen(htext_ptr->hyper_text) +
		256;

	if ((external_flag != ADF_TRUE) &&
		((control_ptr->output_to_stdout_flag == ADF_TRUE) ||
		((entry_ptr->file_index == htext_entry_ptr->file_index) &&
		(!strcmp(entry_ptr->core_name, htext_entry_ptr->core_name)) &&
		(control_ptr->output_by_file_flag == ADF_TRUE))))
		(*output_function)(output_control, "<A HREF=\"#%s\">",
			htext_entry_ptr->base_name);
	else if (control_ptr->output_by_file_flag != ADF_TRUE) {
		if ((return_code = ADF_OUT_AllocHTextString(control_ptr, alloc_length,
			error_text)) == ADF_SUCCESS) {
			if ((entry_ptr != NULL) &&
				(htext_entry_ptr->file_index == entry_ptr->file_index))
				strcat(strcpy(control_ptr->htext_link_name,
					htext_entry_ptr->base_name), ".html");
			else
				sprintf(control_ptr->htext_link_name, "%s%s%s.html",
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
			if ((entry_ptr != NULL) &&
				(htext_entry_ptr->file_index == entry_ptr->file_index))
				strcat(strcpy(control_ptr->htext_link_name,
					htext_entry_ptr->core_name), ".html");
			else
				sprintf(control_ptr->htext_link_name, "%s%s%s.html",
					(output_dir == NULL) ? "" : output_dir,
					(output_dir == NULL) ? "" : "/", htext_entry_ptr->core_name);
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
static int ADF_HTML_DoAutoLink(ADF_CONTROL *control_ptr,
	unsigned int area_index, unsigned int in_length, const char *in_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static int ADF_HTML_DoAutoLink(control_ptr, area_index, in_length, in_ptr,
	output_function, output_control)
ADF_CONTROL           *control_ptr;
unsigned int           area_index;
unsigned int           in_length;
const char            *in_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	int              return_flag = ADF_FALSE;
	unsigned int     count;
	ADF_STRING_PAIR *list;

	if (((area_index == ADF_AREA_AUTHORS) &&
		control_ptr->html_data.author_link_count) ||
		((area_index == ADF_AREA_COPYRIGHTS) &&
		control_ptr->html_data.copyright_link_count)) {
		count = (area_index == ADF_AREA_AUTHORS) ?
			control_ptr->html_data.author_link_count :
			(area_index == ADF_AREA_COPYRIGHTS) ?
			control_ptr->html_data.copyright_link_count : 0;
		list  = (area_index == ADF_AREA_AUTHORS) ?
			control_ptr->html_data.author_link_list :
			(area_index == ADF_AREA_COPYRIGHTS) ?
			control_ptr->html_data.copyright_link_list : NULL;
		while (count) {
			count--;
			if ((list[count].ptr_2 == NULL) ||
				(STRFUNCS_SHIM_memmem(in_length, in_ptr, strlen(list[count].ptr_2),
				list[count].ptr_2) != NULL)) {
				(*output_function)(output_control, "<A HREF=\"%s\">",
					list[count].ptr_1);
				return_flag = ADF_TRUE;
				break;
			}
		}
	}

	return(return_flag);

}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static char *ADF_HTML_MakePostText(unsigned int indent_level,
	ADF_PFORMAT *pfmt_flag[ADF_PFORMAT_LEVEL_COUNT][ADF_PFORMAT_TYPE_COUNT],
	char *post_text)
#else
static char *ADF_HTML_MakePostText(indent_level, pfmt_flag, post_text)
unsigned int  indent_level;
ADF_PFORMAT  *pfmt_flag[ADF_PFORMAT_LEVEL_COUNT][ADF_PFORMAT_TYPE_COUNT];
char         *post_text;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	unsigned int count_2;

	*post_text = '\0';

	for (count_1 = indent_level + 1; count_1 < ADF_PFORMAT_LEVEL_COUNT;
		count_1++) {
		for (count_2 = 0; count_2 < ADF_PFORMAT_TYPE_COUNT; count_2++) {
			if (pfmt_flag[count_1][count_2] != NULL) {
				if (pfmt_flag[count_1][count_2]->format_type ==
					ADF_PFORMAT_TYPE_BB)
					strcat(post_text, "</UL>\n");
				else if (pfmt_flag[count_1][count_2]->format_type ==
					ADF_PFORMAT_TYPE_NM)
					strcat(post_text, "</OL>\n");
				pfmt_flag[count_1][count_2] = NULL;
			}
		}
	}

	return(post_text);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_HTML_EmitIndexList(ADF_CONTROL *control_ptr,
	unsigned int index_item_count, const ADF_INDEX_ITEM *index_item_list,
	unsigned int indent, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_HTML_EmitIndexList(control_ptr, index_item_count,
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
					"<A NAME=\"%s\"></A><B>--- Symbols ---</B><BR>\n",
					"__INTERNAL_INDEX_SYMBOL__");
			else if (last_char == '\1')
				(*output_function)(output_control,
					"<A NAME=\"%s\"></A><B>--- Numerics ---</B><BR>\n",
					"__INTERNAL_INDEX_NUMERIC__");
			else
				(*output_function)(output_control,
					"<A NAME=\"%s_%c__\"></A><B>--- %c ---</B><BR>\n",
					"__INTERNAL_INDEX_CHARACTER", last_char, last_char);
		}
		if (index_item_list[count_1].entry_flag == ADF_TRUE) {
			if ((return_code = ADF_HTML_EmitAnchor(control_ptr, NULL,
				index_item_list[count_1].htext_index, ADF_TRUE,
				output_function, output_control, error_text)) != ADF_SUCCESS)
				goto EXIT_FUNCTION;
			ADF_HTML_OutputString(index_item_list[count_1].item_name,
				output_function, output_control);
			(*output_function)(output_control, "</A><BR>\n");
		}
		else {
			ADF_HTML_OutputString(index_item_list[count_1].item_name,
				output_function, output_control);
			(*output_function)(output_control, "<BR>\n");
		}
		if (index_item_list[count_1].index_item_count) {
			(*output_function)(output_control, "<UL>\n");
			if ((return_code = ADF_HTML_EmitIndexList(control_ptr,
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
static void ADF_HTML_DoComment(const char *in_string,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_HTML_DoComment(in_string, output_function, output_control)
const char            *in_string;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	(*output_function)(output_control, "<!-- %-*.*s -->\n", 69, 69, in_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_HTML_DoCommentsFloating(const char *in_string_1,
	const char *in_string_2, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_HTML_DoCommentsFloating(in_string_1, in_string_2,
	output_function, output_control)
const char            *in_string_1;
const char            *in_string_2;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	char buffer[69 + 1];

	if ((strlen(in_string_1) + strlen(in_string_2)) <= 69)
		(*output_function)(output_control, "<!-- %-*.*s -->\n", 69, 69,
			strcat(strcpy(buffer, in_string_1), in_string_2));
	else
		(*output_function)(output_control, "<!-- %s%s -->\n",
			in_string_1, in_string_2);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_HTML_DoBorder(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_HTML_DoBorder(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	(*output_function)(output_control, "<!-- ");
	STR_EMIT_Char('*', 69, output_function, output_control);
	(*output_function)(output_control, " -->\n");
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

	fprintf(stderr, "Test routine for 'ADF_HTML_OutputToStdout()'\n");
	fprintf(stderr, "---- ------- --- ---------------------------\n\n");

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
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				if ((return_code = ADF_HTML_OutputToStdout(&control_data,
					control_data.in_entry_order_list[count_1], NULL,
					error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				fprintf(stderr, ".");
				STR_EMIT_CharLine('=', 78, NULL, NULL);
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

