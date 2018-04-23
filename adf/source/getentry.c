/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Loads an entry from an ADF database.

	Revision History	:	1995-05-20 --- Creation.
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

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_FN_DECL_STATIC(void ADF_FixParaList,
	(unsigned int para_count, ADF_PARA_DATA *para_list));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_GetEntry(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_list, char *error_text)
#else
int ADF_GetEntry(control_ptr, entry_ptr, entry_data_list, error_text)
ADF_CONTROL     *control_ptr;
const ADF_ENTRY *entry_ptr;
ADF_ENTRY_DATA  *entry_data_list;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int                  return_code;
	unsigned int         count_1;
	unsigned int         count_2;
	ADF_SOURCE_DATA      area_list[ADF_AREA_COUNT];
	unsigned int         para_count;
	unsigned int         para_index;
	ADF_PARA_DATA       *para_ptr;
	ADF_SOURCE_DATA     *in_entry_ptr;
	ADF_ENTRY_DATA_FILE  file_entry_data;
	ADF_ENTRY_DATA      *entry_data_ptr;
	char                *tmp_ptr;
   char                 buffer[2048];

	ADF_INIT_AreaDataList(entry_data_list);

	if ((return_code = ADF_ReadEntry(control_ptr, entry_ptr, &file_entry_data,
		area_list, error_text)) != ADF_SUCCESS)
		goto EXIT_FUNCTION;

	if (control_ptr->in_entry_para_count < file_entry_data.paragraph_count) {
		para_count = (file_entry_data.paragraph_count < 100) ? 100 :
			file_entry_data.paragraph_count;
		para_ptr   = ((ADF_PARA_DATA *) ((!control_ptr->in_entry_para_count) ?
			malloc(para_count * sizeof(ADF_PARA_DATA)) :
			realloc(control_ptr->in_entry_para_list,
			para_count * sizeof(ADF_PARA_DATA))));
		if (para_ptr == NULL) {
			STR_AllocMsgList(para_count, sizeof(ADF_PARA_DATA),
				error_text,	"Unable to allocate memory for the paragraph list");
			return_code = ADF_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		control_ptr->in_entry_para_count = para_count;
		control_ptr->in_entry_para_list  = para_ptr;
	}

	ADF_INIT_ParaDataList(control_ptr->in_entry_para_count,
		control_ptr->in_entry_para_list);

	para_index = 0;

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		entry_data_ptr             = entry_data_list + count_1;
		entry_data_ptr->area_index = count_1;
		if (area_list[count_1].line_data == NULL)
			continue;
		in_entry_ptr                   = area_list + count_1;
		para_count                     =
			chrcnt(in_entry_ptr->line_data, '\n') + 1;
		entry_data_ptr->section_order  = in_entry_ptr->section_index;
		entry_data_ptr->actual_order   = in_entry_ptr->line_number;
		entry_data_ptr->section_name   = in_entry_ptr->section_name;
		entry_data_ptr->para_count     = para_count;
		entry_data_ptr->para_list      = control_ptr->in_entry_para_list +
			para_index;
		para_index                    += para_count;
		tmp_ptr                        = in_entry_ptr->line_data;
		for (count_2 = 0; count_2 < para_count; count_2++) {
			para_ptr = entry_data_ptr->para_list + count_2;
			/*	***********************************************************	*/
			/*	***********************************************************	*/
			/*	Unpack a paragraph format specifier from ADF database format*/
			/*	***********************************************************	*/
			if (*tmp_ptr == ADF_PFORMAT_MARKER_CHAR) {
				para_ptr->para_format.pformat_flag      = ADF_TRUE;
				para_ptr->para_format.pformat_index     = atoi(tmp_ptr + 2) %
					ADF_PFORMAT_COUNT;
				para_ptr->para_format.char_format_flag  = (atoi(tmp_ptr + 6)) ?
					ADF_TRUE : ADF_FALSE;
				para_ptr->para_format.small_font_flag   = (atoi(tmp_ptr + 8)) ?
					ADF_TRUE : ADF_FALSE;
				para_ptr->para_format.indent_level      = atoi(tmp_ptr + 10) %
					ADF_PFORMAT_LEVEL_COUNT;
				para_ptr->para_format.format_type       = atoi(tmp_ptr + 12) %
					ADF_PFORMAT_TYPE_COUNT;
				para_ptr->para_format.begin_rule_flag   = (atoi(tmp_ptr + 14)) ?
					ADF_TRUE : ADF_FALSE;
				para_ptr->para_format.end_rule_flag     = (atoi(tmp_ptr + 16)) ?
					ADF_TRUE : ADF_FALSE;
				para_ptr->para_format.numeric_value     = 0L;
				para_ptr->para_format.first_count       = 0;
				para_ptr->para_format.last_count        = 0;
				tmp_ptr                                += ADF_PFORMAT_LENGTH;
			}
			/*	***********************************************************	*/
			para_ptr->text_ptr = tmp_ptr;
			if ((tmp_ptr = strchr(tmp_ptr, '\n')) != NULL)
				*tmp_ptr++ = '\0';
			else
				break;
		}
		for (count_2 = 0; count_2 < para_count; count_2++) {
			while ((tmp_ptr = strchr(entry_data_ptr->para_list[count_2].text_ptr,
				'\r')) != NULL)
				*tmp_ptr = '\n';
		}
		if ((count_1 == ADF_AREA_SEE_ALSO) &&
			(control_ptr->keep_bad_see_also_flag != ADF_TRUE)) {
			for (count_2 = 0; count_2 < entry_data_ptr->para_count; ) {
				para_ptr = entry_data_ptr->para_list + count_2;
				if (ADF_FIND_FindHTextByText(control_ptr->in_htext_count,
					control_ptr->in_htext_list, para_ptr->text_ptr, NULL) !=
					STRFUNCS_ITEM_FOUND) {
					sprintf(buffer, "'SEE ALSO' item '%-.256s' in ",
						para_ptr->text_ptr);
					ADF_DescribeInEntry(entry_ptr, control_ptr->in_file_list +
						entry_ptr->file_index, buffer + strlen(buffer));
					strcat(buffer, " could not be located.");
					if (control_ptr->log_flag == ADF_TRUE)
						MLOG_LogWarn(control_ptr->mlog_ptr, "%s\n", buffer);
					else
						fprintf(stderr, "WARNING: %s\n", buffer);
					if (count_2 < (entry_data_ptr->para_count - 1))
						entry_data_ptr->para_list[count_2] =
							entry_data_ptr->para_list[entry_data_ptr->para_count - 1];
					entry_data_ptr->para_count--;
				}
				else
					count_2++;
			}
		}
		ADF_FixParaList(entry_data_ptr->para_count, entry_data_ptr->para_list);
	}

EXIT_FUNCTION:

	if (return_code != ADF_SUCCESS)
		ADF_INIT_AreaDataList(entry_data_list);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
static void ADF_FixParaList(unsigned int para_count, ADF_PARA_DATA *para_list)
#else
static void ADF_FixParaList(para_count, para_list)
unsigned int   para_count;
ADF_PARA_DATA *para_list;
#endif /* #ifndef NARGS */
{
	unsigned int   count_1;
	unsigned int   count_2;
	unsigned int   count_3;
	ADF_PFORMAT   *pfmt_ptr;
	ADF_PFORMAT   *pfmt_flag[ADF_PFORMAT_LEVEL_COUNT][ADF_PFORMAT_TYPE_COUNT];
	unsigned long  numeric_value[ADF_PFORMAT_LEVEL_COUNT];

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Clear the list of active paragraphs . . .								*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < ADF_PFORMAT_LEVEL_COUNT; count_1++) {
		for (count_2 = 0; count_2 < ADF_PFORMAT_TYPE_COUNT; count_2++)
			pfmt_flag[count_1][count_2] = NULL;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Loop through the list of paragraphs to determine the logical	*/
	/*	order of indented paragraphs . . .											*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < para_count; count_1++) {
		pfmt_ptr = &para_list[count_1].para_format;
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		If the current paragraph is not formatted, then any		*/
		/*	outstanding active paragraphs must be ended.						*/
		/*	***********************************************************	*/
		if (pfmt_ptr->pformat_flag != ADF_TRUE) {
			for (count_2 = 0; count_2 < ADF_PFORMAT_LEVEL_COUNT; count_2++) {
				for (count_3 = 0; count_3 < ADF_PFORMAT_TYPE_COUNT; count_3++) {
					if (pfmt_flag[count_2][count_3] != NULL) {
						pfmt_flag[count_2][count_3]->last_count++;
						pfmt_flag[count_2][count_3] = NULL;
					}
				}
			}
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		If the current paragraph has an indent level, then any	*/
		/*	active paragraph types having a higher indent must be ended.*/
		/*	***********************************************************	*/
		else {
			if (pfmt_flag[pfmt_ptr->indent_level][pfmt_ptr->format_type] == NULL)
				pfmt_ptr->first_count++;
			pfmt_flag[pfmt_ptr->indent_level][pfmt_ptr->format_type] = pfmt_ptr;
			for (count_2 = pfmt_ptr->indent_level + 1;
				count_2 < ADF_PFORMAT_LEVEL_COUNT; count_2++) {
				for (count_3 = 0; count_3 < ADF_PFORMAT_TYPE_COUNT; count_3++) {
					if (pfmt_flag[count_2][count_3] != NULL) {
						pfmt_flag[count_2][count_3]->last_count++;
						pfmt_flag[count_2][count_3] = NULL;
					}
				}
			}
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		And any outstanding active paragraphs . . .							*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < ADF_PFORMAT_LEVEL_COUNT; count_1++) {
		for (count_2 = 0; count_2 < ADF_PFORMAT_TYPE_COUNT; count_2++) {
			if (pfmt_flag[count_1][count_2] != NULL) {
				pfmt_flag[count_1][count_2]->last_count++;
				pfmt_flag[count_1][count_2] = NULL;
			}
		}
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now assign the numeric values to numeric paragraphs . . .		*/
	/*	*****************************************************************	*/
	for (count_1 = 0; count_1 < para_count; count_1++) {
		pfmt_ptr = &para_list[count_1].para_format;
		if ((pfmt_ptr->pformat_flag == ADF_TRUE) &&
			(pfmt_ptr->format_type == ADF_PFORMAT_TYPE_NM)) {
			if (pfmt_ptr->first_count) {
				pfmt_ptr->numeric_value               = 1L;
				numeric_value[pfmt_ptr->indent_level] = 1L;
			}
			else if (pfmt_ptr->last_count) {
				pfmt_ptr->numeric_value               =
					++numeric_value[pfmt_ptr->indent_level];
				numeric_value[pfmt_ptr->indent_level] = 1L;
			}
			else
				pfmt_ptr->numeric_value =
					++numeric_value[pfmt_ptr->indent_level];
		}
	}
	/*	*****************************************************************	*/
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <memory.h>

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
	int              return_code = ADF_SUCCESS;
	unsigned int     count_1;
	unsigned int     count_2;
	unsigned int     count_3;
	unsigned int     count_4;
	int              current_col;
	int              tab_count;
	char             last_char;
	unsigned int     tmp_count;
	char           **tmp_list;
	ADF_CONTROL      control_data;
	ADF_ENTRY_DATA   entry_data_list[ADF_AREA_COUNT];
	ADF_PARA_DATA   *para_ptr;
	char             area_name[ADF_AREA_NAME_LENGTH + 1];
	char            *definition_name;
	char             error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'ADF_GetEntry()'\n");
	fprintf(stderr, "---- ------- --- ----------------\n\n");

	ADF_INIT_Control(&control_data);

	control_data.cont_on_error_flag     = ADF_TRUE;
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
				if ((return_code = ADF_GetEntry(&control_data,
					control_data.in_entry_order_list[count_1], entry_data_list,
					error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				for (count_2 = 0; count_2 < ADF_AREA_COUNT; count_2++) {
					if (!entry_data_list[count_2].para_count)
						continue;
					definition_name =
						(entry_data_list[count_2].section_name == NULL) ?
						"*** NULL ***" : entry_data_list[count_2].section_name;
					printf("%s:%s\n",
						initcaps(ADF_GetAreaName(count_2, area_name)),
						definition_name);
					for (count_3 = 0;
						count_3 < entry_data_list[count_2].para_count; count_3++) {
						para_ptr    = entry_data_list[count_2].para_list + count_3;
						current_col = 0;
						tab_count   = 0;
						if (strlwrap(para_ptr->text_ptr, &current_col, 70,
							&tab_count, 3, 1, &last_char, &tmp_count, &tmp_list) !=
							STRFUNCS_SUCCESS) {
							strcpy(error_text, "Unable to copy paragraph lines.");
							ADF_INIT_AreaDataList(entry_data_list);
							return_code = ADF_MEMORY_FAILURE;
							goto EXIT_FUNCTION;
						}
						for (count_4 = 0; count_4 < tmp_count; count_4++)
							printf("        %s\n", tmp_list[count_4]);
						printf("\n");
						strl_remove_all(&tmp_count, &tmp_list);
					}
				}
				STR_EMIT_CharLine('=', 78, NULL, NULL);
				ADF_INIT_AreaDataList(entry_data_list);
			}
		}
	}

EXIT_FUNCTION:

	ADF_FREE_Control(&control_data);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

