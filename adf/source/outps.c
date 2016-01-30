/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Emits an ADF entry in 'PostScript' format.

	Revision History	:	1995-12-31 --- Creation.
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
COMPAT_FN_DECL_STATIC(int  ADF_PS_OutputBasic,
	(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text));
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_PS_OutputByEntry(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	char *error_text)
#else
int ADF_PS_OutputByEntry(control_ptr, entry_ptr, error_text)
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
		sprintf(control_ptr->output_file_name, "%s%s%s.ps",
			(control_ptr->output_dir == NULL) ? "" : control_ptr->output_dir,
			(control_ptr->output_dir == NULL) ? "" : "/", entry_ptr->base_name);
		ADF_OUT_CleanName(control_ptr->output_file_name);
		if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
			error_text)) == ADF_SUCCESS) {
			if ((return_code = ADF_GetEntry(control_ptr, entry_ptr,
				entry_data_list, error_text)) == ADF_SUCCESS) {
				return_code = ADF_PS_OutputBasic(control_ptr, entry_ptr,
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
int ADF_PS_OutputToStdout(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	const time_t *output_date, char *error_text)
#else
int ADF_PS_OutputToStdout(control_ptr, entry_ptr, output_date, error_text)
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
		return_code = ADF_PS_OutputBasic(control_ptr, entry_ptr,
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
int ADF_PS_OutputByFile(ADF_CONTROL *control_ptr, unsigned int *entry_index,
	char *error_text)
#else
int ADF_PS_OutputByFile(control_ptr, entry_index, error_text)
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
			sprintf(control_ptr->output_file_name, "%s%s%s.ps",
				(control_ptr->output_dir == NULL) ? "" : control_ptr->output_dir,
				(control_ptr->output_dir == NULL) ? "" : "/", core_name);
			ADF_OUT_CleanName(control_ptr->output_file_name);
			if ((return_code = ADF_OUT_OpenOutputFile(control_ptr,
				error_text)) != ADF_SUCCESS)
				break;
			time(&output_date);
		}
		if ((return_code = ADF_GetEntry(control_ptr, entry_ptr, entry_data_list,
			error_text)) != ADF_SUCCESS)
			break;
		return_code = ADF_PS_OutputBasic(control_ptr, entry_ptr,
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
static int ADF_PS_OutputBasic(ADF_CONTROL *control_ptr,
	const ADF_ENTRY *entry_ptr, ADF_ENTRY_DATA *entry_data_list,
	const time_t *output_date, STR_FUNC_TYPE_fprintf output_function,
	void *output_control, char *error_text)
#else
static int ADF_PS_OutputBasic(control_ptr, entry_ptr, entry_data_list,
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
	STR_EMIT_SetDefaults(&output_function, &output_control);

	return(ADF_SUCCESS);
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

	fprintf(stderr, "Test routine for 'ADF_PS_OutputToStdout()'\n");
	fprintf(stderr, "---- ------- --- -------------------------\n\n");

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
				if ((return_code = ADF_PS_OutputToStdout(&control_data,
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

