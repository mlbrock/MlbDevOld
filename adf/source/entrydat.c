/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Utility routines to support 'adfout'.

	Revision History	:	1996-09-16 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
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
#ifndef NARGS
int ADF_GetAreaList(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_ptr, unsigned int *out_count, char ***out_list,
	char *error_text)
#else
int ADF_GetAreaList(control_ptr, entry_ptr, entry_data_ptr, out_count,
	out_list, error_text)
ADF_CONTROL       *control_ptr;
const ADF_ENTRY   *entry_ptr;
ADF_ENTRY_DATA    *entry_data_ptr;
unsigned int      *out_count;
char            ***out_list;
char              *error_text;
#endif /* #ifndef NARGS */
{
	int   return_code;
	char *tmp_string = NULL;

	*out_count = 0;
	*out_list  = NULL;

	if ((return_code = ADF_GetAreaString(control_ptr, entry_ptr,
		entry_data_ptr, &tmp_string, error_text)) == ADF_SUCCESS) {
		if (tmp_string != NULL) {
			if (sepwordx_keep(tmp_string, "\n", out_count, out_list) !=
				STRFUNCS_SUCCESS) {
				strcpy(error_text, "Unable to copy paragraph list.");
				return_code = ADF_MEMORY_FAILURE;
			}
			free(tmp_string);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int ADF_GetAreaString(ADF_CONTROL *control_ptr, const ADF_ENTRY *entry_ptr,
	ADF_ENTRY_DATA *entry_data_ptr, char **out_string, char *error_text)
#else
int ADF_GetAreaString(control_ptr, entry_ptr, entry_data_ptr, out_string,
	error_text)
ADF_CONTROL      *control_ptr;
const ADF_ENTRY  *entry_ptr;
ADF_ENTRY_DATA   *entry_data_ptr;
char            **out_string;
char             *error_text;
#endif /* #ifndef NARGS */
{
	int                  return_code = ADF_SUCCESS;
	unsigned int         count_1;
	unsigned int         count_2;
	ADF_PARA_DATA       *para_ptr;
	const ADF_PARA_TEXT *para_line_ptr;
	char                *tmp_ptr;

	*out_string = NULL;

	for (count_1 = 0; count_1 < entry_data_ptr->para_count; count_1++) {
		para_ptr = entry_data_ptr->para_list + count_1;
		if ((return_code = ADF_FixParagraphWrap(control_ptr, entry_ptr,
			para_ptr, (control_ptr->hyper_text_flag != ADF_TRUE) ? 0 :
			ADF_CFORMAT_TYPE_NONE, 78, 3, 0, error_text)) != ADF_SUCCESS)
			break;
		para_line_ptr = control_ptr->in_para_line_list;
		for (count_2 = 0; count_2 < control_ptr->current_para_line_count;
			count_2++, para_line_ptr++) {
			if (!para_line_ptr->length)
				continue;
			if ((tmp_ptr = strnvacat(out_string, para_line_ptr->length,
				para_line_ptr->ptr, NULL)) == NULL) {
				strcpy(error_text, "Unable to copy paragraph data.");
				return_code = ADF_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
		if ((count_1 < (entry_data_ptr->para_count - 1)) &&
			((tmp_ptr = strvacat(out_string, "\n", NULL)) == NULL)) {
			strcpy(error_text, "Unable to copy paragraph data.");
			return_code = ADF_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

EXIT_FUNCTION:

	if ((return_code != ADF_SUCCESS) && (*out_string != NULL)) {
		free(*out_string);
		*out_string = NULL;
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 24000;
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
	int             return_code = ADF_SUCCESS;
	char           *out_string  = NULL;
	unsigned int    count_1;
	ADF_CONTROL     control_data;
	ADF_ENTRY_DATA  entry_data_list[ADF_AREA_COUNT];
	char            error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'ADF_GetAreaString'\n");
	fprintf(stderr, "---- ------- --- -------------------\n\n");

	ADF_INIT_Control(&control_data);

	control_data.cont_on_error_flag     = ADF_TRUE;
	control_data.sort_order_type        = ADF_SORT_ENTRY_BASE_NAME;
	control_data.hyper_text_flag        = ADF_FALSE;
	control_data.keep_bad_see_also_flag = ADF_TRUE;
	control_data.area_name_type         = ADF_AREA_NAME_TYPE_INTERNAL;
	control_data.area_order_type        = ADF_AREA_ORDER_TYPE_INTERNAL;
	control_data.hyper_text_flag        = ADF_TRUE;

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
					control_data.in_entry_order_list[count_1],
					entry_data_list, error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				if ((return_code = ADF_GetAreaString(&control_data,
					control_data.in_entry_order_list[count_1],
#if 0
					entry_data_list + ADF_AREA_DESCRIPTION, &out_string,
#else
					entry_data_list + ADF_AREA_COPYRIGHTS, &out_string,
#endif /* #if 0 */
					error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				printf("%s:",
					control_data.in_entry_order_list[count_1]->base_name);
				if (out_string != NULL) {
					printf("[%s]\n", out_string);
					free(out_string);
					out_string = NULL;
				}
				else
					printf("[]\n");
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

