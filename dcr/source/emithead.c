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

	Revision History	:	1994-03-14 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2015.
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
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static void DCR_EmitIndexDetail(DCR_CACHE *cache_ptr, 
	void (*output_function)(void *, char *, ...), void *output_control);
#else
static void DCR_EmitIndexDetail();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/

void DCR_EmitHeader(cache_ptr, cache_header_ptr, output_function,
	output_control)
DCR_CACHE         *cache_ptr;
DCR_HEADER  *cache_header_ptr;
#ifndef NARGS
void             (*output_function)(void *, char *, ...);
#else
void             (*output_function)();
#endif /* #ifndef NARGS */
void             *output_control;
{
	unsigned int      count_1;
	unsigned int      count_2;
	DCR_HEADER *tmp_header;
	char              tmp_buffer[256];
	char              tmp_area_name[DCR_MAX_AREA_NAME + 1];

	tmp_header = (cache_header_ptr != NULL) ? cache_header_ptr :
		cache_ptr->saved_header_ptr;

	STR_EMIT_CharLine('*', 78, output_function, output_control);

	STR_EMIT_CharLine('=', 78, output_function, output_control);
	(*output_function)(output_control, "Basic Cache Header Data\n");
	STR_EMIT_CharLine('-', 78, output_function, output_control);
	(*output_function)(output_control,
		"Cache Name                : %s\n",
		tmp_header->cache_name);
	(*output_function)(output_control,
		"Cache Check Sum           : 0X%08lX\n",
		tmp_header->cache_check_sum);
	(*output_function)(output_control,
		"Cache Signature           : 0X%08lX\n",
		tmp_header->cache_signature);
	(*output_function)(output_control,
		"Cache File Version        : %s\n",
		DCR_GetVersionCache(tmp_header->cache_version, tmp_buffer));
	(*output_function)(output_control,
		"Cache Library Version     : %s\n",
		DCR_GetVersionLibrary(tmp_buffer));
	(*output_function)(output_control,
		"Cache Writer PID          : %u\n",
		tmp_header->cache_writer_pid);
	(*output_function)(output_control,
		"Cache Writer IP Address   : %u.%u.%u.%u\n",
		((unsigned int) tmp_header->cache_writer_ip_address[0]),
		((unsigned int) tmp_header->cache_writer_ip_address[1]),
		((unsigned int) tmp_header->cache_writer_ip_address[2]),
		((unsigned int) tmp_header->cache_writer_ip_address[3]));
	(*output_function)(output_control,
		"Cache Creation Time       : %s\n",
		SDTIF_Format_timeval(&tmp_header->cache_creation_time,
		tmp_buffer));
	(*output_function)(output_control,
		"Cache Current Status      : %s (0X%08lX = %010lu)\n",
		initcaps(DCR_GetStatusName(tmp_header->cache_status, tmp_buffer)),
		tmp_header->cache_status, tmp_header->cache_status);
	(*output_function)(output_control,
		"Cache Lock Status         : %lu (%s = 0X%08lX = %010lu)\n",
		tmp_header->cache_lock_status.lock_count, initcaps(
		DCR_GetStatusName(tmp_header->cache_lock_status.lock_flag,
		tmp_buffer)), tmp_header->cache_lock_status.lock_flag,
		tmp_header->cache_lock_status.lock_flag);
	STR_EMIT_CharLine('-', 78, output_function, output_control);

	(*output_function)(output_control, "Cache Header DB Data\n");
	STR_EMIT_CharLine('-', 78, output_function, output_control);
	(*output_function)(output_control,
		"Database Name             : %s\n", tmp_header->database_name);
	(*output_function)(output_control,
		"Database Owner            : %s\n", tmp_header->owner_name);
	(*output_function)(output_control,
		"Database Table            : %s\n", tmp_header->table_name);
	(*output_function)(output_control,
		"Database User Name        : %s\n", tmp_header->db_user_name);
	(*output_function)(output_control,
		"Database User Pass Word   : %s\n", tmp_header->db_pass_word);
	STR_EMIT_CharLine('-', 78, output_function, output_control);

	(*output_function)(output_control, "Miscellaneous Cache Header Data\n");
	STR_EMIT_CharLine('-', 78, output_function, output_control);
	(*output_function)(output_control,
		"Indirect Index Flag       : %s\n",
		(DCR_INDEX_IS_INDIRECT(cache_ptr) == DCR_TRUE) ? "TRUE" :
		"FALSE");
	(*output_function)(output_control,
		"Maximum Index Entry Length: %10u\n",
		tmp_header->max_entry_length);
	(*output_function)(output_control,
		"Initial Allocation Size   : %10u\n",
		tmp_header->initial_allocation_size);
	(*output_function)(output_control,
		"Allocation Size           : %10u\n",
		tmp_header->allocation_size);
	(*output_function)(output_control,
		"Maximum Records In Cache  : %10u\n",
		tmp_header->max_records_in_cache);
	(*output_function)(output_control,
		"Current Record Count      : %10u\n",
		tmp_header->record_count);
	(*output_function)(output_control,
		"Allocated Record Count    : %10u\n",
		tmp_header->allocated_record_count);
	(*output_function)(output_control,
		"Actual Data Record Size   : %10u\n",
		tmp_header->actual_data_record_size);
	(*output_function)(output_control,
		"Aligned Data Record Size  : %10u\n",
		tmp_header->data_record_size);
	(*output_function)(output_control,
		"Total Data Record Size    : %10u\n",
		tmp_header->total_record_size);
	STR_EMIT_CharLine('-', 78, output_function, output_control);

	DCR_EmitCallBacks(cache_ptr, output_function, output_control);

	(*output_function)(output_control, "General Cache Header Sizing Data\n");
	STR_EMIT_CharLine('-', 78, output_function, output_control);
	(*output_function)(output_control,
		"Basic Header Size         : %10lu\n",
		tmp_header->basic_header_area_size);
	(*output_function)(output_control,
		"Total Header Size         : %10lu\n",
		tmp_header->header_area_size);
	(*output_function)(output_control,
		"Data Area Offset          : %10lu\n",
		tmp_header->data_area_offset);
	(*output_function)(output_control,
		"Data Area Size            : %10lu\n",
		tmp_header->data_area_size);
	(*output_function)(output_control,
		"Index Area Offset         : %10lu\n",
		tmp_header->index_area_offset);
	(*output_function)(output_control,
		"Index Area Size           : %10lu\n",
		tmp_header->index_area_size);
	(*output_function)(output_control,
		"Cache Size                : %10lu\n",
		tmp_header->total_cache_size);
	STR_EMIT_CharLine('-', 78, output_function, output_control);

	DCR_EmitStats(cache_ptr, tmp_header, output_function,
		output_control);

	for (count_1 = 0; count_1 < DCR_AREA_COUNT; count_1++) {
		(*output_function)(output_control, "Cache %s Area Description\n",
			strcpy(tmp_buffer, initcaps(DCR_GetAreaName(((int) count_1),
			tmp_area_name))));
		STR_EMIT_CharLine('-', 78, output_function, output_control);
/*
		for (count_2 = 0; count_2 < strlen(tmp_area_name); count_2++)
			tmp_buffer[count_2] = (isspace(tmp_buffer[count_2])) ?
				tmp_buffer[count_2] : '-';
		(*output_function)(output_control, "%s\n", tmp_buffer);
*/
		(*output_function)(output_control, "%-36.36s: %10u\n",
			strcat(strcpy(tmp_buffer, tmp_area_name), " Item Count"),
			tmp_header->area_list[count_1].count);
		(*output_function)(output_control, "%-36.36s: %10u\n",
			strcat(strcpy(tmp_buffer, tmp_area_name), " Item Size"),
			tmp_header->area_list[count_1].item_size);
		(*output_function)(output_control, "%-36.36s: %10u\n",
			strcat(strcpy(tmp_buffer, tmp_area_name), " Area Offset"),
			tmp_header->area_list[count_1].offset);
		(*output_function)(output_control, "%-36.36s: %10u\n",
			strcat(strcpy(tmp_buffer, tmp_area_name), " Actual Size"),
			tmp_header->area_list[count_1].actual_size);
		(*output_function)(output_control, "%-36.36s: %10u\n",
			strcat(strcpy(tmp_buffer, tmp_area_name), " Total Size"),
			tmp_header->area_list[count_1].total_size);
		if (count_1 < (DCR_AREA_COUNT - 1))
			STR_EMIT_CharLine('-', 78, output_function, output_control);
	}

	STR_EMIT_CharLine('=', 78, output_function, output_control);
	(*output_function)(output_control, "Field Data\n");
	STR_EMIT_CharLine('-', 78, output_function, output_control);
	for (count_1 = 0; count_1 < cache_ptr->field_count; count_1++) {
		(*output_function)(output_control,
			"Field Number           : %u\n", count_1);
		(*output_function)(output_control,
			"Logical Name           : %s\n",
			cache_ptr->field_list[count_1].logical_name);
		(*output_function)(output_control,
			"Field Name             : %s\n",
			cache_ptr->field_list[count_1].field_name);
		(*output_function)(output_control,
			"Database Column Name   : %s\n",
			cache_ptr->field_list[count_1].db_column_name);
/*
	CODE NOTE: To be removed.
		(*output_function)(output_control,
			"Field Logical Type ID  : %d\n",
			cache_ptr->field_list[count_1].type_id);
		(*output_function)(output_control,
			"Field Logical Type Name: %s\n",
			cache_ptr->field_list[count_1].type_name);
*/
		(*output_function)(output_control,
			"Field Offset           : %u\n",
			cache_ptr->field_list[count_1].data_offset);
		(*output_function)(output_control,
			"Field Length           : %u\n",
			cache_ptr->field_list[count_1].data_length);
		if (count_1 < (cache_ptr->field_count - 1))
			STR_EMIT_CharLine('-', 78, output_function, output_control);
	}
	STR_EMIT_CharLine('=', 78, output_function, output_control);

	STR_EMIT_CharLine('=', 78, output_function, output_control);
	(*output_function)(output_control, "Index Data\n");
	STR_EMIT_CharLine('-', 78, output_function, output_control);
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		(*output_function)(output_control,
			"Index Number           : %u\n", count_1);
		(*output_function)(output_control,
			"Index Name             : %s\n",
			cache_ptr->index_list[count_1].index_name);
		(*output_function)(output_control,
			"Embedded Entry Size    : %u\n",
			cache_ptr->index_list[count_1].index_entry_size);
		(*output_function)(output_control,
			"Embedded Pointer Offset: %u\n",
			cache_ptr->index_list[count_1].index_pointer_offset);
		for (count_2 = 0;
			count_2 < cache_ptr->index_list[count_1].field_count; count_2++)
			(*output_function)(output_control,
				"%s %s\n",
				(!count_2) ? "Index Field List       :" :
				"                        ",
				cache_ptr->field_list[cache_ptr->index_field_list[cache_ptr->
				index_list[count_1].field_index + count_2]].field_name);
		if (count_1 < (cache_ptr->index_count - 1))
			STR_EMIT_CharLine('-', 78, output_function, output_control);
	}
	STR_EMIT_CharLine('=', 78, output_function, output_control);

	STR_EMIT_CharLine('*', 78, output_function, output_control);
}
/*	***********************************************************************	*/

static void DCR_EmitIndexDetail(cache_ptr, output_function,
	output_control)
DCR_CACHE  *cache_ptr;
#ifndef NARGS
void      (*output_function)(void *, char *, ...);
#else
void      (*output_function)();
#endif /* #ifndef NARGS */
void       *output_control;
{
	unsigned int count_1;
	unsigned int count_2;

	STR_EMIT_CharLine('=', 78, output_function, output_control);
	(*output_function)(output_control, "Index Data Detail\n");
	STR_EMIT_CharLine('-', 78, output_function, output_control);
	for (count_1 = 0; count_1 < cache_ptr->index_count; count_1++) {
		(*output_function)(output_control,
			"Index Number           : %u\n", count_1);
		(*output_function)(output_control,
			"Index Name             : %s\n",
			cache_ptr->index_list[count_1].index_name);
		(*output_function)(output_control,
			"Embedded Entry Size    : %u\n",
			cache_ptr->index_list[count_1].index_entry_size);
		(*output_function)(output_control,
			"Embedded Pointer Offset: %u\n",
			cache_ptr->index_list[count_1].index_pointer_offset);
		for (count_2 = 0;
			count_2 < cache_ptr->index_list[count_1].field_count; count_2++)
			(*output_function)(output_control,
				"%s: %s\n",
				(!count_2) ? "Index Field List       :" :
				"                        ",
				cache_ptr->field_list[cache_ptr->index_field_list[cache_ptr->
				index_list[count_1].field_index + count_2]].db_column_name);
		if (count_1 < (cache_ptr->index_count - 1))
			STR_EMIT_CharLine('-', 78, output_function, output_control);
	}
	STR_EMIT_CharLine('=', 78, output_function, output_control);
}
/*	***********************************************************************	*/

#ifdef TEST_MAIN

#ifdef __MSDOS__
COMPAT_EXTERN_DATA_DECL unsigned int _stklen = 16384;
#endif /* __MSDOS__ */

#define TEST_COUNT	100

#include "datatest.h"						/* For the test meta-data . . .		*/

#ifndef NARGS
int main(void);
#else
int main();
#endif /* #ifndef NARGS */

int main()
{
	int               return_code;
	DCR_HEADER *cache_header_ptr = NULL;
	DCR_CACHE         cache_data;
	char              error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'DCR_EmitHeader()'\n");
	fprintf(stderr, "---- ------- --- ------------------------\n\n");

	if ((return_code = DCR_MakeHeader("TEST_CACHE_NAME",
		"TEST_SERVER,TEST_DB,TEST_OWNER,mlds,mlds", "TEST_SERVER",
		"TEST_DB", "TEST_OWNER", "mlds", "mlds", "TEST_TABLE", 4096, 4096,
		DCR_TRUE, MemberCount, MemberList, 0, NULL,
		IndexSpecCount, IndexSpecList, &cache_header_ptr, error_text)) !=
		DCR_SUCCESS)
		fprintf(stderr, "ERROR: %s\n", error_text);
	else {
		memset(&cache_data, '\0', sizeof(cache_data));
		if ((return_code = DCR_AllocCache(&cache_data, cache_header_ptr,
			error_text)) != DCR_SUCCESS)
			fprintf(stderr, "ERROR: %s\n", error_text);
		else {
#ifndef NARGS
			DCR_EmitHeader(&cache_data, NULL,
				((void (*)(void *, char *, ...)) fprintf), stdout);
#else
			DCR_EmitHeader(&cache_data, NULL, fprintf, stdout);
#endif /* #ifndef NARGS */
			free(cache_data.index_data_list);
		}
		free(cache_header_ptr);
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

