#include "adf.h"

#ifndef NARGS
int  ADF_CMP_EntryDataList(const ADF_ENTRY_DATA *entry_data_list_1,
	const ADF_ENTRY_DATA *entry_data_list_2, unsigned int *diff_area_index,
	unsigned int *diff_para_index);
int  ADF_CMP_EntryData(const ADF_ENTRY_DATA *entry_data_ptr_1,
	const ADF_ENTRY_DATA *entry_data_ptr_2, unsigned int *diff_para_index);
#else
int  ADF_CMP_EntryDataList();
int  ADF_CMP_EntryData();
#endif /* #ifndef NARGS */

#ifndef NARGS
int  ADF_COPY_EntryDataList(const ADF_ENTRY_DATA *in_entry_data_list,
	ADF_ENTRY_DATA *out_entry_data_list, char *error_text);
int  ADF_COPY_EntryData(const ADF_ENTRY_DATA *in_entry_data_ptr,
	ADF_ENTRY_DATA *out_entry_data_ptr, char *error_text);
#else
int  ADF_COPY_EntryDataList();
int  ADF_COPY_EntryData();
#endif /* #ifndef NARGS */

#ifndef NARGS
void ADF_FREE_AreaDataList(ADF_ENTRY_DATA *entry_data_list);
void ADF_FREE_AreaData(ADF_ENTRY_DATA *entry_data_ptr);
#else
void ADF_FREE_AreaDataList();
void ADF_FREE_AreaData();
#endif /* #ifndef NARGS */

#ifndef NARGS
void ADF_INIT_AreaDataList(ADF_ENTRY_DATA *entry_data_list);
void ADF_INIT_AreaData(ADF_ENTRY_DATA *entry_data_ptr);
#else
void ADF_INIT_AreaDataList();
void ADF_INIT_AreaData();
#endif /* #ifndef NARGS */

#ifndef NARGS
int  ADF_COPY_ParaDataList(unsigned int in_para_count,
	const ADF_PARA_DATA *in_para_list, unsigned int *out_para_count,
	ADF_PARA_DATA **out_para_list, char *error_text);
int  ADF_COPY_ParaData(const ADF_PARA_DATA *in_para_ptr,
	ADF_PARA_DATA *out_para_ptr, char *error_text);
#else
int  ADF_COPY_ParaDataList();
int  ADF_COPY_ParaData();
#endif /* #ifndef NARGS */

#ifndef NARGS
void ADF_FREE_ParaDataList(unsigned int *para_count,
	ADF_PARA_DATA **para_list);
void ADF_FREE_ParaData(ADF_PARA_DATA *para_ptr);
#else
void ADF_FREE_ParaDataList();
void ADF_FREE_ParaData();
#endif /* #ifndef NARGS */

#ifndef NARGS
void ADF_INIT_ParaDataList(unsigned int para_count, ADF_PARA_DATA *para_list);
void ADF_INIT_ParaData(ADF_PARA_DATA *para_ptr);
#else
void ADF_INIT_ParaDataList();
void ADF_INIT_ParaData();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/
	/* In 'cmentryd.c'. */
#include <string.h>
int ADF_CMP_EntryDataList(entry_data_list_1, entry_data_list_2,
	diff_area_index, diff_para_index)
const ADF_ENTRY_DATA *entry_data_list_1;
const ADF_ENTRY_DATA *entry_data_list_2;
unsigned int         *diff_area_index;
unsigned int         *diff_para_index;
{
	int          cmp_code = 0;
	unsigned int count_1;

	if (diff_area_index != NULL)
		*diff_area_index = 0;
	if (diff_para_index != NULL)
		*diff_para_index = 0;

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		if ((cmp_code = ADF_CMP_EntryData(entry_data_list_1 + count_1,
			entry_data_list_2 + count_1, diff_para_index)) != 0) {
			if (diff_area_index != NULL)
				*diff_area_index = count_1;
			break;
		}
	}

	return(cmp_code);
}
int ADF_CMP_EntryData(entry_data_ptr_1, entry_data_ptr_2, diff_para_index)
const ADF_ENTRY_DATA *entry_data_ptr_1;
const ADF_ENTRY_DATA *entry_data_ptr_2;
unsigned int         *diff_para_index;
{
	int          cmp_code = 0;
	unsigned int count_1;

	if (entry_data_ptr_1->para_count != entry_data_ptr_2->para_count) {
		if (diff_para_index != NULL)
			*diff_para_index = UINT_MAX;
		cmp_code         =
			(entry_data_ptr_1->para_count > entry_data_ptr_2->para_count) ?
			1 : -1;
	}
	else {
		if (diff_para_index != NULL)
			*diff_para_index = 0;
		for (count_1 = 0; count_1 < entry_data_ptr_1->para_count; count_1++) {
			if ((cmp_code = strcmp(entry_data_ptr_1->para_list[count_1].text_ptr,
				entry_data_ptr_2->para_list[count_1].text_ptr)) != 0) {
				if (diff_para_index != NULL)
					*diff_para_index = 0;
				break;
			}
		}
	}

	return(cmp_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
	/* In 'cpentryd.c'. */
#include <strfuncs.h>
#include <genfuncs.h>
int ADF_COPY_EntryDataList(in_entry_data_list, out_entry_data_list,
	error_text)
const ADF_ENTRY_DATA *in_entry_data_list;
ADF_ENTRY_DATA       *out_entry_data_list;
char                 *error_text;
{
	int          return_code;
	unsigned int count_1;

	ADF_INIT_AreaDataList(out_entry_data_list);

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		if ((return_code = ADF_COPY_EntryData(in_entry_data_list + count_1,
			out_entry_data_list + count_1, error_text)) != ADF_SUCCESS)
			break;
	}

	if (return_code != ADF_SUCCESS)
		ADF_FREE_AreaDataList(out_entry_data_list);

	return(return_code);
}
	/* In 'cpentryd.c'. */
int ADF_COPY_EntryData(in_entry_data_ptr, out_entry_data_ptr, error_text)
const ADF_ENTRY_DATA *in_entry_data_ptr;
ADF_ENTRY_DATA       *out_entry_data_ptr;
char                 *error_text;
{
	int return_code = ADF_SUCCESS;

	ADF_INIT_AreaData(out_entry_data_ptr);

	if ((in_entry_data_ptr->section_name != NULL) &&
		((out_entry_data_ptr->section_name =
		strdup(in_entry_data_ptr->section_name)) == NULL)) {
		GEN_AllocMsgItem(strlen(in_entry_data_ptr->section_name) + 1,
			error_text, "Unable to copy an ADF entry area section name");
		return_code = ADF_MEMORY_FAILURE;
	}
	else if ((return_code =
		ADF_COPY_ParaDataList(in_entry_data_ptr->para_count,
		in_entry_data_ptr->para_list, &out_entry_data_ptr->para_count,
		&out_entry_data_ptr->para_list, error_text)) != ADF_SUCCESS)
		ADF_FREE_AreaData(out_entry_data_ptr);

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
	/* In 'frentryd.c'. */
#include <stdlib.h>
void ADF_FREE_AreaDataList(entry_data_list)
ADF_ENTRY_DATA *entry_data_list;
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++)
		ADF_FREE_AreaData(entry_data_list + count_1);
}
	/* In 'frentryd.c'. */
void ADF_FREE_AreaData(entry_data_ptr)
ADF_ENTRY_DATA *entry_data_ptr;
{
	if (entry_data_ptr->section_name != NULL)
		free(entry_data_ptr->section_name);

	ADF_FREE_ParaDataList(&entry_data_ptr->para_count,
		&entry_data_ptr->para_list);

	ADF_INIT_AreaData(entry_data_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
	/* In 'inentryd.c'. */
#include <memory.h>
void ADF_INIT_AreaDataList(entry_data_list)
ADF_ENTRY_DATA *entry_data_list;
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++)
		ADF_INIT_AreaData(entry_data_list + count_1);
}
	/* In 'inentryd.c'. */
void ADF_INIT_AreaData(entry_data_ptr)
ADF_ENTRY_DATA *entry_data_ptr;
{
	memset(entry_data_ptr, '\0', sizeof(*entry_data_ptr));

	entry_data_ptr->area_index    = 0;
	entry_data_ptr->section_order = 0;
	entry_data_ptr->actual_order  = 0;
	entry_data_ptr->section_name  = NULL;
	entry_data_ptr->para_count    = 0;
	entry_data_ptr->para_list     = NULL;
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
	/*	In 'cpparad.c'. */
#include <stdlib.h>

#include <genfuncs.h>
int ADF_COPY_ParaDataList(in_para_count, in_para_list, out_para_count,
	out_para_list, error_text)
unsigned int          in_para_count;
const ADF_PARA_DATA  *in_para_list;
unsigned int         *out_para_count;
ADF_PARA_DATA       **out_para_list;
char                 *error_text;
{
	int          return_code = ADF_SUCCESS;
	unsigned int count_1;

	*out_para_count = 0;
	*out_para_list  = NULL;

	if (in_para_count && ((*out_para_list = ((ADF_PARA_DATA *)
		calloc(in_para_count, sizeof(ADF_PARA_DATA)))) == NULL)) {
		GEN_AllocMsgList(in_para_count, sizeof(ADF_PARA_DATA), error_text,
			"Unable to copy an ADF entry area paragraph list");
		return_code = ADF_MEMORY_FAILURE;
	}
	else {
		*out_para_count = in_para_count;
		ADF_INIT_ParaDataList(*out_para_count, *out_para_list);
		for (count_1 = 0; count_1 < in_para_count; count_1++) {
			if ((return_code = ADF_COPY_ParaData(in_para_list + count_1,
				*out_para_list + count_1, error_text)) != ADF_SUCCESS)
				break;
		}
	}

	if (return_code != ADF_SUCCESS)
		ADF_FREE_ParaDataList(out_para_count, out_para_list);
		
	return(return_code);
}
	/*	In 'cpparad.c'. */
int ADF_COPY_ParaData(in_para_ptr, out_para_ptr, error_text)
const ADF_PARA_DATA *in_para_ptr;
ADF_PARA_DATA       *out_para_ptr;
char                *error_text;
{
	int return_code = ADF_SUCCESS;

	*out_para_ptr = *in_para_ptr;

	if ((in_para_ptr->text_ptr != NULL) &&
		((out_para_ptr->text_ptr = strdup(in_para_ptr->text_ptr)) == NULL)) {
		ADF_INIT_ParaData(out_para_ptr);
		GEN_AllocMsgItem(strlen(in_para_ptr->text_ptr) + 1, error_text,
			"Unable to copy an ADF entry area paragraph");
		return_code = ADF_MEMORY_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
	/*	In 'frparad.c'. */
#include <stdlib.h>
void ADF_FREE_ParaDataList(para_count, para_list)
unsigned int   *para_count;
ADF_PARA_DATA **para_list;
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < *para_count; count_1++)
		ADF_FREE_ParaData(*para_list + count_1);

	if (*para_list != NULL)
		free(*para_list);

	*para_count = 0;
	*para_list  = NULL;
}
	/*	In 'frparad.c'. */
void ADF_FREE_ParaData(para_ptr)
ADF_PARA_DATA *para_ptr;
{
	if (para_ptr->text_ptr != NULL)
		free(para_ptr->text_ptr);

	ADF_INIT_ParaData(para_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
	/*	In 'inparad.c'. */
#include <memory.h>
void ADF_INIT_ParaDataList(para_count, para_list)
unsigned int   para_count;
ADF_PARA_DATA *para_list;
{
	unsigned int count_1;

	memset(para_list, '\0', para_count * sizeof(*para_list));

	for (count_1 = 0; count_1 < para_count; count_1++)
		ADF_INIT_ParaData(para_list + count_1);
}
	/*	In 'inparad.c'. */
void ADF_INIT_ParaData(para_ptr)
ADF_PARA_DATA *para_ptr;
{
	para_ptr->para_format.pformat_flag    = ADF_FALSE;
	para_ptr->para_format.format_type     = 0;
	para_ptr->para_format.indent_level    = 0;
	para_ptr->para_format.numeric_value   = 0;
	para_ptr->para_format.small_font_flag = ADF_FALSE;
	para_ptr->para_format.first_count     = 0;
	para_ptr->para_format.last_count      = 0;
	para_ptr->text_ptr                    = NULL;
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#include <memory.h>

#ifdef __MSDOS__
extern unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

int main(argc, argv)
int    argc;
char **argv;
{
	int              return_code = ADF_SUCCESS;
	unsigned int     count_1;
	ADF_CONTROL      control_data;
	ADF_ENTRY_DATA   entry_data_list_1[ADF_AREA_COUNT];
	ADF_ENTRY_DATA   entry_data_list_2[ADF_AREA_COUNT];
	char             error_text[ADF_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for new entry comparison logic\n");
	fprintf(stderr, "---- ------- --- --- ----- ---------- -----\n\n");

	ADF_INIT_Control(&control_data);

	ADF_INIT_AreaDataList(entry_data_list_1);
	ADF_INIT_AreaDataList(entry_data_list_2);

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
				ADF_INIT_AreaDataList(entry_data_list_1);
				ADF_FREE_AreaDataList(entry_data_list_2);
				if ((return_code = ADF_GetEntry(&control_data,
					control_data.in_entry_order_list[count_1], entry_data_list_1,
					error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				if ((return_code = ADF_COPY_EntryDataList(entry_data_list_1,
					entry_data_list_2, error_text)) != ADF_SUCCESS)
					goto EXIT_FUNCTION;
				if (ADF_CMP_EntryDataList(entry_data_list_1, entry_data_list_2,
					NULL, NULL) != 0)
					fprintf(stderr, "Differences in %s(%s)\n",
						control_data.in_entry_order_list[count_1]->file_name,
						control_data.in_entry_order_list[count_1]->base_name);
			}
		}
	}

EXIT_FUNCTION:

	ADF_FREE_Control(&control_data);

	ADF_INIT_AreaDataList(entry_data_list_1);
	ADF_FREE_AreaDataList(entry_data_list_2);

	if (return_code != ADF_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

