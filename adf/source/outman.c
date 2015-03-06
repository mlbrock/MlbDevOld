/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits an ADF entry in Unix 'man' page format.

	Revision History	:	1995-05-28 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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
COMPAT_FN_DECL_STATIC(void ADF_MAN_DoHeaderByEntry,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void ADF_MAN_DoHeaderByFile,
	(const ADF_CONTROL *control_ptr,
	unsigned int entry_index, const time_t *output_date,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(int  ADF_MAN_OutputBasic,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_MAN_OutputSection,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	int format_flag, unsigned int in_next_line_pad,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(int  ADF_MAN_OutputCodeSyntax,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text));
COMPAT_FN_DECL_STATIC(void ADF_MAN_DoComment,
	(const char *in_string, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL_STATIC(void ADF_MAN_DoCommentsFloating,
	(const char *in_string_1, const char *in_string_2,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL_STATIC(void ADF_MAN_DoBorder,
	(STR_FUNC_TYPE_fprintf output_function, void *output_control));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_MAN_OutputByEntry(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	char *error_text)
#else
int ADF_MAN_OutputByEntry(control_ptr, entry_ptr, error_text)
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
		strlen(control_ptr->output_dir)) + strlen(entry_ptr->man_page) +
		strlen(entry_ptr->base_name) + 256;

	if ((return_code = ADF_OUT_AllocFileString(control_ptr, alloc_length,
		error_text)) == ADF_SUCCESS) {
		sprintf(control_ptr->output_file_name, "%s/man/man%c/%s.%s",
			(control_ptr->output_dir == NULL) ? "." : control_ptr->output_dir,
			*entry_ptr->man_page, entry_ptr->base_name, entry_ptr->man_page);
		ADF_OUT_CleanName(control_ptr->output_file_name);
		if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
			error_text)) == ADF_SUCCESS) {
			if ((return_code = ADF_GetEntry(control_ptr, entry_ptr,
				entry_data_list, error_text)) == ADF_SUCCESS) {
				return_code = ADF_MAN_OutputBasic(control_ptr, entry_ptr,
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
int ADF_MAN_OutputToStdout(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, const time_t *output_date, char *error_text)
#else
int ADF_MAN_OutputToStdout(control_ptr, entry_ptr, output_date, error_text)
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
		return_code = ADF_MAN_OutputBasic(control_ptr, entry_ptr,
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
int ADF_MAN_OutputByFile(ADF_CONTROL *control_ptr, unsigned int *entry_index,
	char *error_text)
#else
int ADF_MAN_OutputByFile(control_ptr, entry_index, error_text)
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
		strlen(control_ptr->output_dir)) + strlen(entry_ptr->man_page) +
		strlen(core_name) + 256;

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
			sprintf(control_ptr->output_file_name, "%s/man/man%c/%s.%s",
				(control_ptr->output_dir == NULL) ? "." : control_ptr->output_dir,
				*entry_ptr->man_page, core_name, entry_ptr->man_page);
			ADF_OUT_CleanName(control_ptr->output_file_name);
			if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
				error_text)) != ADF_SUCCESS)
				break;
			time(&output_date);
			if (control_ptr->output_comment_flag == ADF_TRUE)
				ADF_MAN_DoHeaderByFile(control_ptr, *entry_index, &output_date,
					STR_FUNC_TYPE_fprintf_CAST(fprintf), control_ptr->output_file_ptr);
		}
		else
			fprintf(control_ptr->output_file_ptr, "\n");
		if ((return_code = ADF_GetEntry(control_ptr, entry_ptr, entry_data_list,
			error_text)) != ADF_SUCCESS)
			break;
		return_code = ADF_MAN_OutputBasic(control_ptr, entry_ptr,
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
static void ADF_MAN_DoHeaderByEntry(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_MAN_DoHeaderByEntry(control_ptr, entry_ptr, entry_data_list,
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

	ADF_MAN_DoBorder(output_function, output_control);
	ADF_MAN_DoBorder(output_function, output_control);
	ADF_MAN_DoCommentsFloating("Documentation for ", entry_ptr->base_name,
		output_function, output_control);
	ADF_MAN_DoComment("", output_function, output_control);
	ADF_MAN_DoComment(
		"   Created by the Automated Documentation Facility (ADF)",
		output_function, output_control);
	ADF_MAN_DoBorder(output_function, output_control);

	ADF_MAN_DoComment("", output_function, output_control);
	ADF_MAN_DoCommentsFloating("Entry Name          : ", entry_ptr->base_name,
		output_function, output_control);
	ADF_MAN_DoComment("", output_function, output_control);
	ADF_MAN_DoCommentsFloating("Source File Name    : ", entry_ptr->file_name,
		output_function, output_control);

	ADF_MAN_DoComment("", output_function, output_control);
	ADF_MAN_DoCommentsFloating("Source File Date    : ",
		strcat(SDTIF_Format_time_t_GMT(&entry_ptr->file_date, date_data),
		" GMT/UTC"), output_function, output_control);
	time_t_data = entry_ptr->file_date;
	tm_data     = *SDTIF_GetTimeLocal(&time_t_data, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_MAN_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&entry_ptr->file_date, date_data),
		time_zone_data), output_function, output_control);

	ADF_MAN_DoComment("", output_function, output_control);
	ADF_MAN_DoCommentsFloating("ADF Preparation Date: ",
		strcat(SDTIF_Format_time_t_GMT(&entry_ptr->prep_date, date_data),
		" GMT/UTC"), output_function, output_control);
	time_t_data = entry_ptr->prep_date;
	tm_data     = *SDTIF_GetTimeLocal(&time_t_data, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_MAN_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&entry_ptr->prep_date, date_data),
		time_zone_data), output_function, output_control);

	ADF_MAN_DoComment("", output_function, output_control);
	ADF_MAN_DoCommentsFloating("Output Date         : ",
		strcat(SDTIF_Format_time_t_GMT(&tmp_output_date, date_data), " GMT/UTC"),
		output_function, output_control);
	tm_data = *SDTIF_GetTimeLocal(&tmp_output_date, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_MAN_DoCommentsFloating("                    : ",
		strcat(SDTIF_Format_time_t(&tmp_output_date, date_data), time_zone_data),
		output_function, output_control);

	ADF_MAN_DoComment("", output_function, output_control);
	ADF_MAN_DoBorder(output_function, output_control);

	if ((ADF_GetAreaList(control_ptr, entry_ptr, entry_data_list +
		ADF_AREA_COPYRIGHTS, &tmp_count, &tmp_list, error_text) ==
		ADF_SUCCESS) && tmp_count) {
		ADF_MAN_DoBorder(output_function, output_control);
		ADF_MAN_DoBorder(output_function, output_control);
		for (count_1 = 0; count_1 < tmp_count; count_1++)
			ADF_MAN_DoCommentsFloating("", tmp_list[count_1],
				output_function, output_control);
		ADF_MAN_DoBorder(output_function, output_control);
		strl_remove_all(&tmp_count, &tmp_list);
	}
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_MAN_DoHeaderByFile(const ADF_CONTROL *control_ptr,
	unsigned int entry_index, const time_t *output_date,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_MAN_DoHeaderByFile(control_ptr, entry_index, output_date,
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

	ADF_MAN_DoBorder(output_function, output_control);
	ADF_MAN_DoBorder(output_function, output_control);
	ADF_MAN_DoCommentsFloating("Documentation for Entries in Source File ",
		control_ptr->in_entry_order_list[entry_index]->file_name,
		output_function, output_control);
	ADF_MAN_DoComment("", output_function, output_control);
	ADF_MAN_DoComment(
		"   Created by the Automated Documentation Facility (ADF)",
		output_function, output_control);
	ADF_MAN_DoBorder(output_function, output_control);
	ADF_MAN_DoComment("", output_function, output_control);
	ADF_MAN_DoCommentsFloating("Output Date: ",
		strcat(SDTIF_Format_time_t_GMT(&tmp_output_date, date_data), " GMT/UTC"),
		output_function, output_control);
	tm_data = *SDTIF_GetTimeLocal(&tmp_output_date, &tm_data);
	strftime(time_zone_data, sizeof(time_zone_data) - 1, " %Z", &tm_data);
	ADF_MAN_DoCommentsFloating("           : ",
		strcat(SDTIF_Format_time_t(&tmp_output_date, date_data), time_zone_data),
		output_function, output_control);
	ADF_MAN_DoComment("", output_function, output_control);

	for (count_1 = entry_index;
		(count_1 < control_ptr->in_entry_order_count) &&
		(!strcmp(control_ptr->in_entry_order_list[entry_index]->file_name,
		control_ptr->in_entry_order_list[count_1]->file_name)); count_1++)
		ADF_MAN_DoCommentsFloating((!count_1) ?
			"Entry Name : " : "           : ",
			control_ptr->in_entry_order_list[count_1]->base_name,
			output_function, output_control);
	ADF_MAN_DoComment("", output_function, output_control);
	ADF_MAN_DoBorder(output_function, output_control);
	(*output_function)(output_control, "\n");
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_MAN_OutputBasic(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_MAN_OutputBasic(control_ptr, entry_ptr, entry_data_list,
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
	int              return_code = ADF_SUCCESS;
	unsigned int     count_1;
	ADF_ENTRY_DATA  *entry_data_ptr;
	const ADF_AREA  *area_ptr;
	time_t           tmp_output_date;
	char             area_name[ADF_AREA_NAME_LENGTH + 1];
	char             date_buffer[100];
	char            *section_name;
	char             section_buffer[256];

	STR_EMIT_SetDefaults(&output_function, &output_control);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Emit descriptive comments for the entry . . .						*/
	/*	*****************************************************************	*/
	tmp_output_date = (output_date == NULL) ? time(NULL) : *output_date;
	SDTIF_Format_time_t(&tmp_output_date, date_buffer);
	date_buffer[10] = ' ';
	if (control_ptr->output_comment_flag == ADF_TRUE)
		ADF_MAN_DoHeaderByEntry(control_ptr, entry_ptr, entry_data_list,
			&tmp_output_date, output_function, output_control);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Order the sections of the entry as specified . . .					*/
	/*	*****************************************************************	*/
	if (control_ptr->area_order_type != ADF_AREA_ORDER_TYPE_INTERNAL)
		ADF_SORT_EntrySections(control_ptr->area_order_type, entry_data_list);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Initialize the man page owner name variable . . .					*/
	/*	*****************************************************************	*/
	if (control_ptr->man_data.owner_name != NULL) {
		ADF_MAN_DoComment("Initialize the owner name . . .",
			output_function, output_control);
		(*output_function)(output_control, ".ds ]W %s\n",
			control_ptr->man_data.owner_name);
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Set-up the man page header . . .											*/
	/*	*****************************************************************	*/
	section_name = (control_ptr->man_data.section_name != NULL) ?
		control_ptr->man_data.section_name :
		ADF_GetDefaultManSection(entry_ptr->man_page, section_buffer);
	if (section_name != NULL) {
		ADF_MAN_DoBorder(output_function, output_control);
		ADF_MAN_DoComment("Set-up the man page header . . .",
			output_function, output_control);
		(*output_function)(output_control, ".de }H\n");
		(*output_function)(output_control, ".ev 1\n");
		(*output_function)(output_control, ".}C\n");
		(*output_function)(output_control, "'sp .5i\n");
		(*output_function)(output_control, ".ft 1\n");
		(*output_function)(output_control, ".ps 10\n");
		(*output_function)(output_control, ".tl \7%s\7\7\\\\*(]H\7\n",
			section_name);
		(*output_function)(output_control, "'sp .5i\n");
		(*output_function)(output_control, ".ev\n");
		(*output_function)(output_control, ".ns\n");
		(*output_function)(output_control, "..\n");
		ADF_MAN_DoBorder(output_function, output_control);
	}
	/*	*****************************************************************	*/

	SDTIF_Format_time_t(&entry_ptr->file_date, date_buffer);
	date_buffer[10] = '\0';
	(*output_function)(output_control, ".TH \"%s\" %s \"%s\"\n",
		entry_ptr->base_name, entry_ptr->man_page, date_buffer);

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		entry_data_ptr = entry_data_list + count_1;
		area_ptr       = ADF_AreaNameList + entry_data_ptr->area_index;
		if ((area_ptr->output_flag != ADF_TRUE) ||
			(!entry_data_ptr->para_count))
			continue;
		ADF_GetOutputAreaName(control_ptr->area_name_type,
			entry_data_ptr->area_index, control_ptr->area_name_list,
			entry_data_ptr->section_name, sizeof(area_name) - 1, area_name);
		(*output_function)(output_control, ".SH \"%s\"\n", area_name);
		if (entry_data_ptr->area_index == ADF_AREA_CODE_SYNTAX) {
			if ((return_code = ADF_MAN_OutputCodeSyntax(control_ptr, entry_ptr,
				entry_data_ptr, output_function, output_control,
				error_text)) != ADF_SUCCESS)
				break;
		}
		else if ((return_code = ADF_MAN_OutputSection(control_ptr, entry_ptr,
			entry_data_ptr, area_ptr->pformat_flag, 0, output_function,
			output_control, error_text)) != ADF_SUCCESS)
			break;
		if (area_ptr->pformat_flag != ADF_TRUE)
			(*output_function)(output_control, "\n");
	}

	if (return_code == ADF_SUCCESS) {
		if (control_ptr->output_comment_flag == ADF_TRUE) {
			ADF_MAN_DoBorder(output_function, output_control);
			ADF_MAN_DoCommentsFloating("End of Man Page Text for ",
				entry_ptr->base_name, output_function, output_control);
			ADF_MAN_DoBorder(output_function, output_control);
			ADF_MAN_DoBorder(output_function, output_control);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_MAN_OutputSection(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	int format_flag, unsigned int in_next_line_pad,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_MAN_OutputSection(control_ptr, entry_ptr, entry_data_ptr,
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
   unsigned int   count_3;
	unsigned int   added_margin;
	unsigned int   cformat_type;
	unsigned int   current_col;
	unsigned int   space_count;
	ADF_PARA_DATA *para_ptr;
	unsigned int   in_length;
	char          *in_ptr;
	unsigned int   para_line_count;
	char          *primary_leader;
	char          *tmp_ptr;
	char           tmp_buffer_1[100];
	char           tmp_buffer_2[100];
	char           leader_buffer[1024];

/*
	CODE NOTE: Should use the value in the ADF database entry.
*/
unsigned int tab_setting = 3;

	cformat_type = (format_flag == ADF_TRUE) ? ADF_MAN_CFORMAT_TYPE : 0;

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		para_ptr       = entry_data_ptr->para_list + count_1;
		primary_leader = NULL;
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr, para_ptr,
			cformat_type, error_text)) != ADF_SUCCESS)
			break;
		para_ptr->para_format.indent_level =
			(para_ptr->para_format.indent_level >= ADF_PFORMAT_LEVEL_COUNT) ?
			(ADF_PFORMAT_LEVEL_COUNT - 1) : para_ptr->para_format.indent_level;
		added_margin                       =
			(para_ptr->para_format.indent_level * 4) -
			(((para_ptr->para_format.format_type == ADF_PFORMAT_TYPE_BB) ||
			(para_ptr->para_format.format_type == ADF_PFORMAT_TYPE_NM)) ?
			4 : 0);
		if (para_ptr->para_format.begin_rule_flag == ADF_TRUE) {
			(*output_function)(output_control, ".RE\n");
			(*output_function)(output_control, ".RS %u\n", added_margin);
			(*output_function)(output_control, ".cu\n");
			STR_EMIT_CharLine('_', 75 - added_margin, output_function,
				output_control);
			(*output_function)(output_control, ".LP\n");
			(*output_function)(output_control, ".cs 1\n");
			(*output_function)(output_control, ".fi\n");
		}
		if ((para_ptr->para_format.pformat_flag == ADF_TRUE) &&
			(format_flag == ADF_TRUE)) {
			switch (para_ptr->para_format.format_type) {
				case ADF_PFORMAT_TYPE_BB	:
					added_margin   = (para_ptr->para_format.indent_level * 4) - 4;
					primary_leader = leader_buffer;
					sprintf(leader_buffer, ".RE\n.RS %u\n.IP o\n", added_margin);
					break;
				case ADF_PFORMAT_TYPE_IN	:
					primary_leader = NULL;
					added_margin   = para_ptr->para_format.indent_level * 4;
					(*output_function)(output_control, ".RE\n.RS %u\n",
						added_margin);
					break;
/*
	CODE NOTE: To be removed.
				case ADF_PFORMAT_TYPE_LN	:
					primary_leader = NULL;
					added_margin   = para_ptr->para_format.indent_level * 4;
					(*output_function)(output_control, ".RE\n");
					(*output_function)(output_control, ".RS %u\n", added_margin);
					(*output_function)(output_control, ".cu\n");
					STR_EMIT_CharLine('_', 75 - added_margin, output_function,
						output_control);
					(*output_function)(output_control, ".LP\n");
					(*output_function)(output_control, ".LP\n");
					break;
*/
				case ADF_PFORMAT_TYPE_NM	:
					primary_leader = leader_buffer;
					added_margin   = (para_ptr->para_format.indent_level * 4) - 4;
					*tmp_buffer_2  = '\0';
					sprintf(tmp_buffer_1, "%3lu",
						para_ptr->para_format.numeric_value % 1000L);
					for (count_2 = 0; count_2 < (3 - strlen(tmp_buffer_1));
						count_2++)
						strcat(tmp_buffer_2, "\\0");
					sprintf(leader_buffer, ".RE\n.RS %u\n.IP %s%lu\n",
						added_margin, tmp_buffer_2,
						para_ptr->para_format.numeric_value % 1000L);
					break;
				default							:
					break;
			}
/*	CODE NOTE: To be included in the structure.
			if (para_ptr->para_format.format_flag != ADF_TRUE)
				format_flag = ADF_FALSE;
*/
		}
		control_ptr->out_para_buffer[0] = '\0';
		tmp_ptr                         = control_ptr->out_para_buffer;
		if (para_ptr->para_format.char_format_flag != ADF_TRUE) {
			(*output_function)(output_control, ".cs 1 18\n");
			(*output_function)(output_control, ".nf\n");
			for (count_2 = 0; count_2 < control_ptr->current_para_line_count;
				count_2++) {
				in_length = control_ptr->in_para_line_list[count_2].length;
				in_ptr    = control_ptr->in_para_line_list[count_2].ptr;
				STR_EMIT_String("\\ ", added_margin, output_function,
					output_control);
				if (control_ptr->in_para_line_list[count_2].cformat_type !=
					ADF_CFORMAT_CHAR_NONE)
					continue;
				current_col = 0;
				for (count_3 = 0; count_3 < in_length; count_3++, in_ptr++) {
					if (*in_ptr == '\t') {
						space_count  = tab_setting - (current_col % tab_setting);
						current_col += space_count;
						STR_EMIT_String("\\ ", space_count, output_function,
							output_control);
					}
					else if (*in_ptr == ' ') {
						(*output_function)(output_control, "\\ ");
						current_col++;
					}
					else if (*in_ptr == '\\') {
						(*output_function)(output_control, "\\");
						current_col++;
					}
					else if (*in_ptr == '\n') {
						(*output_function)(output_control, "\n");
						current_col = 0;
					}
					else {
						(*output_function)(output_control, "%c", *in_ptr);
						current_col++;
					}
				}
				(*output_function)(output_control, "\n");
			}
		}
		else {
			if (primary_leader != NULL)
				(*output_function)(output_control, "%s", primary_leader);
			for (count_2 = 0; count_2 < control_ptr->current_para_line_count;
				count_2++) {
				in_length = control_ptr->in_para_line_list[count_2].length;
				in_ptr    = control_ptr->in_para_line_list[count_2].ptr;
				if (control_ptr->in_para_line_list[count_2].cformat_type !=
					ADF_CFORMAT_CHAR_NONE) {
					if (format_flag == ADF_TRUE) {
						switch (control_ptr->in_para_line_list[count_2].
							cformat_type) {
							case ADF_CFORMAT_CHAR_BOLD_1			:
								(*output_function)(output_control, "\\fB");
								break;
							case ADF_CFORMAT_CHAR_ITALIC_1		:
								(*output_function)(output_control, "\\fI");
								break;
							case ADF_CFORMAT_CHAR_SUBSCRIPT_1	:
							case ADF_CFORMAT_CHAR_SUPERSCRIPT_2	:
								(*output_function)(output_control, "\\u");
								break;
							case ADF_CFORMAT_CHAR_SUBSCRIPT_2	:
							case ADF_CFORMAT_CHAR_SUPERSCRIPT_1	:
								(*output_function)(output_control, "\\d");
								break;
							case ADF_CFORMAT_CHAR_BOLD_2			:
							case ADF_CFORMAT_CHAR_ITALIC_2		:
								(*output_function)(output_control, "\\fP");
								break;
							default										:
								break;
						}
					}
					continue;
				}
				else if ((in_length) && (in_ptr != NULL)) {
					for (count_3 = 0; count_3 < in_length; count_3++) {
						if ((!count_1) && ((*in_ptr == '.') || (*in_ptr == '\'')))
							(*output_function)(output_control, "\\&");
						if ((in_ptr[count_3] == '\\') || ((format_flag != ADF_TRUE) &&
							(in_ptr[count_3] == ' ')))
							(*output_function)(output_control, "\\");
						(*output_function)(output_control, "%c", in_ptr[count_3]);
					}
				}
			}
			(*output_function)(output_control, "\n");
			if (format_flag != ADF_TRUE) {
				(*output_function)(output_control, ".cs 1\n");
				(*output_function)(output_control, ".fi\n");
			}
			else
				(*output_function)(output_control, ".LP\n");
		}
		if (para_ptr->para_format.end_rule_flag == ADF_TRUE) {
			(*output_function)(output_control, ".RE\n");
			(*output_function)(output_control, ".RS %u\n", added_margin);
			(*output_function)(output_control, ".cu\n");
			STR_EMIT_CharLine('_', 75 - added_margin, output_function,
				output_control);
			(*output_function)(output_control, ".LP\n");
			(*output_function)(output_control, ".cs 1\n");
			(*output_function)(output_control, ".fi\n\n");
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static int ADF_MAN_OutputCodeSyntax(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control,
	char *error_text)
#else
static int ADF_MAN_OutputCodeSyntax(control_ptr, entry_ptr, entry_data_ptr,
	output_function, output_control, error_text)
ADF_CONTROL           *control_ptr;
const ADF_ENTRY       *entry_ptr;
ADF_ENTRY_DATA        *entry_data_ptr;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
char                  *error_text;
#endif /* #ifndef NARGS */
{
	int             return_code = ADF_SUCCESS;
	unsigned int    line_count  = 0;
	char          **line_list   = NULL;
	int             current_col;
	int             tab_count;
	unsigned int    count_1;
	unsigned int    count_2;
   unsigned int    count_3;
	ADF_PARA_DATA  *para_ptr;
	unsigned int    in_length;
	char           *in_ptr;
	char           *tmp_ptr;
	char            last_char;

	(*output_function)(output_control, ".cs 1 18\n");
	(*output_function)(output_control, ".nf\n");
	(*output_function)(output_control, ".cu\n");
	STR_EMIT_CharLine('_', 70, output_function, output_control);

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		para_ptr = entry_data_ptr->para_list + count_1;
		if ((return_code = ADF_FixParagraph(control_ptr, entry_ptr, para_ptr,
			0, error_text)) != ADF_SUCCESS)
			goto EXIT_FUNCTION;
		for (count_2 = 0; count_2 < control_ptr->current_para_line_count;
			count_2++) {
			in_length   = control_ptr->in_para_line_list[count_2].length;
			in_ptr      = control_ptr->in_para_line_list[count_2].ptr;
			current_col = 0;
			tab_count   = 0;
			if (strlwrap(in_ptr, &current_col, 70, &tab_count, 3, STRFUNCS_TRUE,
				&last_char, &line_count, &line_list) != STRFUNCS_SUCCESS) {
				strcpy(error_text, "Unable to allocate string wrap list.");
				return_code = ADF_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			for (count_3 = 0; count_3 < line_count; count_3++) {
				(*output_function)(output_control, ".cs 1 18\n");
				(*output_function)(output_control, ".nf\n");
				if (count_3)
					(*output_function)(output_control, "\\ \\ \\ ");
				tmp_ptr = line_list[count_3];
				while (*tmp_ptr) {
					if ((tmp_ptr == line_list[count_3]) &&
						((*tmp_ptr == '.') || (*tmp_ptr == '\'')))
						(*output_function)(output_control, "\\&");
					if ((*tmp_ptr == '\\') || (*tmp_ptr == ' '))
						(*output_function)(output_control, "\\");
					(*output_function)(output_control, "%c", *tmp_ptr);
					tmp_ptr++;
				}
				(*output_function)(output_control, "\n");
				(*output_function)(output_control, ".cs 1\n");
				(*output_function)(output_control, ".fi\n");
			}
			strl_remove_all(&line_count, &line_list);
		}
	}

	(*output_function)(output_control, ".cu\n");
	STR_EMIT_CharLine('_', 70, output_function, output_control);
	(*output_function)(output_control, ".LP\n");
	(*output_function)(output_control, ".cs 1\n");
	(*output_function)(output_control, ".fi\n\n");

EXIT_FUNCTION:

	return(return_code);
}

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_MAN_DoComment(const char *in_string,
	STR_FUNC_TYPE_fprintf output_function, void *output_control)
#else
static void ADF_MAN_DoComment(in_string, output_function, output_control)
const char            *in_string;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	(*output_function)(output_control, ".\\\" * %-*.*s *\n", 70, 70,
		in_string);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_MAN_DoCommentsFloating(const char *in_string_1,
	const char *in_string_2, STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_MAN_DoCommentsFloating(in_string_1, in_string_2,
	output_function, output_control)
const char            *in_string_1;
const char            *in_string_2;
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	char buffer[70 + 1];

	if ((strlen(in_string_1) + strlen(in_string_2)) <= 70)
		(*output_function)(output_control, ".\\\" * %-*.*s *\n", 70, 70,
			strcat(strcpy(buffer, in_string_1), in_string_2));
	else
		(*output_function)(output_control, ".\\\" * %s%s *\n",
			in_string_1, in_string_2);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_MAN_DoBorder(STR_FUNC_TYPE_fprintf output_function,
	void *output_control)
#else
static void ADF_MAN_DoBorder(output_function, output_control)
STR_FUNC_TYPE_fprintf  output_function;
void                  *output_control;
#endif /* #ifndef NARGS */
{
	(*output_function)(output_control, ".\\\" * ");
	STR_EMIT_Char('*', 70, output_function, output_control);
	(*output_function)(output_control, " *\n");
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

	fprintf(stderr, "Test routine for 'ADF_MAN_OutputToStdout()'\n");
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
			for (count_1 = 0; count_1 < control_data.in_entry_order_count;
				count_1++) {
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				if ((return_code = ADF_MAN_OutputToStdout(&control_data,
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

