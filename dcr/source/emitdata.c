/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:

	Revision History	:	1994-05-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
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

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_EmitData(cache_ptr, index_method, reverse_flag, header_flag,
	max_records, lines_per_page, inter_field_separator, intra_field_separator,
	page_separator, record_leader, record_trailer, field_spec_count,
	field_spec_list, page_count, format_line_count, data_line_count,
	output_function, output_control, error_text)
DCR_CACHE      *cache_ptr;
unsigned int    index_method;
int             reverse_flag;
unsigned int    max_records;
int             header_flag;
unsigned int    lines_per_page;
char           *inter_field_separator;
char           *intra_field_separator;
char           *page_separator;
char           *record_leader;
char           *record_trailer;
unsigned int    field_spec_count;
char          **field_spec_list;
unsigned int   *page_count;
unsigned int   *format_line_count;
unsigned int   *data_line_count;
#ifndef NARGS
void          (*output_function)(void *, char *, ...);
#else
void          (*output_function)();
#endif /* #ifndef NARGS */
void           *output_control;
char           *error_text;
{
	int               return_code = DCR_SUCCESS;
	unsigned int      line_count  = 0;
	unsigned int      count_1;
	unsigned int      count_2;
	unsigned int      header_length;
	unsigned int      header_count;
	char            **header_list;
	unsigned int     *data_length_list;
	unsigned int     *total_length_list;
	void             *record_ptr;
	unsigned int      tmp_page_count;
	unsigned int      tmp_format_line_count;
	unsigned int      tmp_data_line_count;
	unsigned int      index_element;
	int               index_increment;
   unsigned int      out_field_count;
	DCR_FIELD  *out_field_list;

	index_element          = (reverse_flag != DCR_TRUE) ? 0 :
		cache_ptr->record_count - 1;
	index_increment        = (reverse_flag != DCR_TRUE) ? 1 : -1;

	page_count             = (page_count == NULL) ?
		&tmp_page_count : page_count;
	format_line_count      = (format_line_count == NULL) ?
		&tmp_format_line_count : format_line_count;
	data_line_count        = (data_line_count == NULL) ?
		&tmp_data_line_count : data_line_count;

	*page_count            = 0;
	*format_line_count     = 0;
	*data_line_count       = 0;

	inter_field_separator  = (inter_field_separator == NULL) ? "" :
		inter_field_separator;
	intra_field_separator  = (intra_field_separator == NULL) ? "" :
		intra_field_separator;
	page_separator         = (page_separator        == NULL) ? "" :
		page_separator;
	record_leader          = (record_leader         == NULL) ? "" :
		record_leader;
	record_trailer         = (record_trailer        == NULL) ? "" :
		record_trailer;

	if ((return_code = DCR_GetSpecifiedFieldList(cache_ptr->field_count,
		cache_ptr->field_list, cache_ptr->field_name_count,
		cache_ptr->field_name_list, field_spec_count, field_spec_list,
		&out_field_count, &out_field_list, error_text)) == DCR_SUCCESS) {
		if ((return_code = DCR_GetEmitControlData(out_field_count,
			out_field_list, cache_ptr->field_align_count,
			cache_ptr->field_align_list, header_flag, inter_field_separator,
			intra_field_separator, &header_length, &header_count, &header_list,
			&data_length_list, &total_length_list, error_text)) == DCR_SUCCESS) {
			if (header_flag == DCR_TRUE) {
				for (count_1 = 0; count_1 < header_count; count_1++)
					(*output_function)(output_control, "%s%s%s",
						record_leader, header_list[count_1], record_trailer);
				(*format_line_count) = header_count;
				line_count           = header_count;
			}
			*page_count = 1;
			for (count_1 = 0; count_1 < cache_ptr->record_count; count_1++) {
				record_ptr     = DCR_IELE_TO_RPTR(cache_ptr, index_method,
					index_element);
				index_element += index_increment;
				(*output_function)(output_control, "%s", record_leader);
				DCR_EmitRecord(out_field_count, out_field_list,
					cache_ptr->field_align_list, data_length_list,
					total_length_list, inter_field_separator,
					intra_field_separator, record_ptr, output_function,
					output_control);
				(*output_function)(output_control, "%s", record_trailer);
				if (lines_per_page && count_1 && (!(count_1 % lines_per_page)) &&
					((count_1 + 1) < cache_ptr->record_count)) {
					if (header_flag == DCR_TRUE) {
						(*output_function)(output_control, "%s%s%s",
							record_leader, header_list[header_count - 1],
							record_trailer);
						(*format_line_count)++;
						line_count++;
					}
					(*output_function)(output_control, page_separator);
					(*page_count)++;
					if (header_flag == DCR_TRUE) {
						for (count_2 = 0; count_2 < header_count; count_2++)
							(*output_function)(output_control, "%s%s%s",
								record_leader, header_list[count_2], record_trailer);
						(*format_line_count) += header_count;
						line_count           += header_count;
					}
				}
				++(*data_line_count);
				if (max_records && (*data_line_count >= max_records))
					break;
			}
			if (header_flag == DCR_TRUE) {
				(*output_function)(output_control, "%s%s%s",
					record_leader, header_list[header_count - 1], record_trailer);
				(*format_line_count)++;
			}
			strl_remove_all(&header_count, &header_list);
			free(data_length_list);
			free(total_length_list);
		}
		mema_remove_all(&out_field_count, ((void **) &out_field_list));
	}

	return(return_code);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

#include <memory.h>
#include <string.h>

#ifndef NARGS
int main(void);
#else
int main();
#endif /* #ifndef NARGS */

#include "datatest.h"						/* For the test meta-data . . .		*/

int main()
{
	int                return_code;
	unsigned int       count_1;
	unsigned int       count_2;
	unsigned int       page_count;
	unsigned int       format_line_count;
	unsigned int       data_line_count;
	DCR_HEADER  *cache_header_ptr = NULL;
	char              *data_list        = NULL;
	void             **index_list       = NULL;
	char              *field_list;
	DCR_CACHE          cache_data;
	char               error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'DCR_EmitData()'\n");
	fprintf(stderr, "---- ------- --- ----------------------\n\n");

	memset(&cache_data, '\0', sizeof(cache_data));

	if ((return_code = DCR_MakeHeader("TEST_CACHE_NAME",
		"TEST_SERVER,TEST_DB,TEST_OWNER,mlds,mlds", "TEST_SERVER",
		"TEST_DB", "TEST_OWNER", "mlds", "mlds", "TEST_TABLE", 8192, 4096,
		DCR_FALSE, MemberCount, MemberList, 0, NULL,
		IndexSpecCount, IndexSpecList, &cache_header_ptr, error_text)) !=
		DCR_SUCCESS)
		goto EXIT_FUNCTION;
	else if ((return_code = DCR_AllocCache(&cache_data, cache_header_ptr,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;

	cache_header_ptr->record_count = DataCount;
	DCR_BindHeader(&cache_data, cache_header_ptr);

	if ((data_list = ((char *) calloc(cache_data.record_count,
		cache_data.total_record_size))) == NULL) {
		sprintf(error_text, "%s (%u elements * %u size = %u total bytes).",
			"Unable to allocate the complete record lists",
			cache_data.record_count, cache_data.total_record_size,
			cache_data.record_count * cache_data.total_record_size);
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	cache_data.data_area_offset = 0L;
	cache_data.mmap_ptr         = data_list;
	cache_data.record_mmap_ptr  = data_list;

	for (count_1 = 0; count_1 < cache_data.record_count; count_1++)
		memcpy(data_list + (count_1 * cache_data.total_record_size),
			DataList + count_1, sizeof(DataList[0]));

	if ((index_list = ((void **) calloc(cache_data.index_count,
		sizeof(void **)))) == NULL) {
		sprintf(error_text, "%s (%u indices * %u size = %u total bytes).",
			"Unable to allocate the array of pointers to index lists",
			cache_data.index_count, sizeof(void *),
			cache_data.index_count * sizeof(void *));
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
		if ((index_list[count_1] = calloc(cache_data.record_count,
			DCR_INDEX_ENTRY_SIZE(&cache_data, count_1))) == NULL) {
			sprintf(error_text,
				"%s %u (%u records * %u size = %u total bytes).",
				"Unable to allocate index list number", count_1,
				cache_data.record_count, DCR_INDEX_ENTRY_SIZE(&cache_data,
				count_1), cache_data.record_count *
				DCR_INDEX_ENTRY_SIZE(&cache_data, count_1));
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Because we allocate memory for this test instead of using a	*/
	/*	memory-mapped file, we have to fix-up the index area offsets.	*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
		cache_data.index_list[count_1].index_area_offset       = 0L;
		cache_data.index_data_list[count_1].index_entry_offset = 0L;
		cache_data.index_data_list[count_1].index_entry_list   =
			index_list[count_1];
		cache_data.index_data_list[count_1].mmap_ptr           =
      	index_list[count_1];
	}
	/*	**************************************************************	*/

	DCR_IndexCache(&cache_data);

	field_list = "issue_key,issue_id_type,issue_id_value";
	printf(
		"NOTE: Only emitting issue_key, issue_id_type, and issue_id_value\n");
	printf("=======================================================\n");
	for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
		if (count_1)
			printf("-------------------------------------------------------\n");
		printf("Index Number %u (", count_1);
		for (count_2 = 0; count_2 < cache_data.index_list[count_1].field_count;
			count_2++)
			printf("%s%s", cache_data.field_list[cache_data.
				index_field_list[cache_data.index_list[count_1].field_index +
				count_2]].db_column_name,
				(count_2 < (cache_data.index_list[count_1].field_count - 1)) ?
				", " : ")\n");
		printf("-------------------------------------------------------\n");
		printf("ASCENDING ORDER\n");
		printf("-------------------------------------------------------\n");
#ifndef NARGS
		if ((return_code = DCR_EmitData(&cache_data, count_1, DCR_FALSE,
			DCR_TRUE, 0, 60, " ", "-", "\f", "", "\n", 1, &field_list,
			&page_count, &format_line_count, &data_line_count,
			((void (*)(void *, char *, ...)) fprintf), stdout, error_text)) !=
			DCR_SUCCESS)
#else
		if ((return_code = DCR_EmitData(&cache_data, count_1, DCR_FALSE,
			DCR_TRUE, 0, 60, " ", "-", "\f", "", "\n", 1, &field_list,
			&page_count, &format_line_count, &data_line_count, fprintf, stdout,
			error_text)) != DCR_SUCCESS)
#endif /* #ifndef NARGS */
			break;
		printf("-------------------------------------------------------\n");
		printf("DESCENDING ORDER\n");
		printf("-------------------------------------------------------\n");
#ifndef NARGS
		if ((return_code = DCR_EmitData(&cache_data, count_1, DCR_TRUE,
			DCR_TRUE, 0, 60, " ", "-", "\f", "", "\n", 1, &field_list,
			&page_count, &format_line_count, &data_line_count,
			((void (*)(void *, char *, ...)) fprintf), stdout, error_text)) !=
			DCR_SUCCESS)
#else
		if ((return_code = DCR_EmitData(&cache_data, count_1, DCR_TRUE,
			DCR_TRUE, 0, 60, " ", "-", "\f", "", "\n", 1, &field_list,
			&page_count, &format_line_count, &data_line_count, fprintf, stdout,
			error_text)) != DCR_SUCCESS)
#endif /* #ifndef NARGS */
			break;
		printf("-------------------------------------------------------\n");
		printf("Format Line Count: %u\n", format_line_count);
		printf("Data Line Count  : %u\n", data_line_count);
		printf("Page Count       : %u\n", page_count);
	}
	printf("=======================================================\n");

EXIT_FUNCTION:

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);

	if (data_list != NULL)
		free(data_list);

	if (index_list != NULL) {
		for (count_1 = 0; count_1 < cache_data.index_count; count_1++) {
			if (index_list[count_1] != NULL)
				free(index_list[count_1]);
		}
		free(index_list);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

