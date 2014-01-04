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

		Copyright Michael L. Brock 1994 - 2014.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
static int DCR_CreateFieldList(unsigned int member_count,
	const GEN_MEMBER *member_list, unsigned int *field_count,
	DCR_FIELD **field_list, unsigned int *field_name_count,
	DCR_FIELD_NAME **field_name_list, unsigned int *column_name_count,
	DCR_COLUMN_NAME **column_name_list, char *error_text);
static int DCR_DoAddedFields(unsigned int added_field_count,
	char **added_field_list, unsigned int *field_count,
	DCR_FIELD **field_list, unsigned int *field_name_count,
	DCR_FIELD_NAME **field_name_list, char *error_text);
static int DCR_AlignFields(unsigned int field_count,
	DCR_FIELD *field_list, unsigned int *data_record_size,
	unsigned int *field_align_count, GEN_ALIGN **field_align_list,
	char *error_text);
static int DCR_CreateIndexSpec(unsigned int in_index_spec_count,
	char **in_index_spec_list, unsigned int field_count,
	const DCR_FIELD *field_list, unsigned int field_align_count,
	const GEN_ALIGN *field_align_list, unsigned int field_name_count,
	const DCR_FIELD_NAME *field_name_list, unsigned int *index_count,
	DCR_INDEX **index_list, unsigned int *index_name_count,
	DCR_INDEX_NAME **index_name_list, unsigned int *index_field_count,
	unsigned int **index_field_list, unsigned int *index_align_count,
	GEN_ALIGN **index_align_list, unsigned int *max_entry_length,
	char *error_text);
static int DCR_AppendIndexSpec(unsigned int in_index_spec_count,
	char **in_index_spec_list, unsigned int field_count,
	const DCR_FIELD *field_list, unsigned int field_align_count,
	const GEN_ALIGN *field_align_list, unsigned int field_name_count,
	const DCR_FIELD_NAME *field_name_list, unsigned int *index_count,
	DCR_INDEX **index_list, unsigned int *index_name_count,
	DCR_INDEX_NAME **index_name_list, unsigned int *index_field_count,
	unsigned int **index_field_list, unsigned int *index_align_count,
	GEN_ALIGN **index_align_list, unsigned int *max_entry_length,
	char *error_text);
#else
static int DCR_CreateFieldList();
static int DCR_DoAddedFields();
static int DCR_AlignFields();
static int DCR_CreateIndexSpec();
static int DCR_AppendIndexSpec();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

int DCR_MakeHeader(cache_name, db_spec_string, server_name, database_name,
	owner_name, user_name, pass_word, table_name, initial_allocation_size,
	allocation_size, indirect_index_flag, member_count, member_list,
	added_field_count, added_field_list, in_index_spec_count,
	in_index_spec_list, cache_header_ptr, error_text)
const char        *cache_name;
const char        *db_spec_string;
const char        *server_name;
const char        *database_name;
const char        *owner_name;
const char        *user_name;
const char        *pass_word;
const char        *table_name;
unsigned int       initial_allocation_size;
unsigned int       allocation_size;
int                indirect_index_flag;
unsigned int       member_count;
const GEN_MEMBER  *member_list;
unsigned int       added_field_count;
char             **added_field_list;
unsigned int       in_index_spec_count;
char             **in_index_spec_list;
DCR_HEADER **cache_header_ptr;
char              *error_text;
{
	int              return_code       = DCR_SUCCESS;
	unsigned int     field_name_count  = 0;
	DCR_FIELD_NAME  *field_name_list   = NULL;
	unsigned int     column_name_count = 0;
	DCR_COLUMN_NAME *column_name_list  = NULL;
	unsigned int     field_align_count = 0;
	GEN_ALIGN       *field_align_list  = NULL;
	unsigned int     field_count       = 0;
	DCR_FIELD       *field_list        = NULL;
	unsigned int     index_count       = 0;
	DCR_INDEX       *index_list        = NULL;
	unsigned int     index_name_count  = 0;
	DCR_INDEX_NAME  *index_name_list   = NULL;
	unsigned int     index_field_count = 0;
	unsigned int    *index_field_list  = NULL;
	unsigned int     index_align_count = 0;
	GEN_ALIGN       *index_align_list  = NULL;
	void            *area_list[DCR_AREA_COUNT];
	unsigned int     count_1;
	unsigned int     max_entry_length;
	unsigned int     data_record_size;
	DCR_HEADER       tmp_cache_header;
	DCR_STAT         tmp_stat;

	memset(&tmp_stat, '\0', sizeof(tmp_stat));

	DCR_StatStartTime(&tmp_stat);

	*cache_header_ptr       = NULL;

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Fix-up the allocation sizes . . .									*/
	/*	**************************************************************	*/
	allocation_size         = (!allocation_size) ?
		DCR_DEFAULT_ALLOC_SIZE : allocation_size;
	allocation_size         = (allocation_size < DCR_MIN_ALLOC_SIZE) ?
		DCR_MIN_ALLOC_SIZE : (allocation_size > DCR_MAX_ALLOC_SIZE) ?
		DCR_MAX_ALLOC_SIZE : allocation_size;
	initial_allocation_size = (initial_allocation_size < allocation_size) ?
		allocation_size : (initial_allocation_size > DCR_MAX_ALLOC_SIZE) ?
		DCR_MAX_ALLOC_SIZE : initial_allocation_size;
	/*	**************************************************************	*/

	memset(&tmp_cache_header, '\0', sizeof(tmp_cache_header));

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Check the reasonableness of the parameters . . .				*/
	/*	**************************************************************	*/
	if ((db_spec_string == NULL) || (!(*db_spec_string))) {
		strcpy(error_text,
			"The the database specification stringis not specified.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (strlen(db_spec_string) >
		(STR_sizeof(DCR_HEADER, db_spec_string) - 1)) {
		sprintf(error_text, "%s '%-.500s' (%u) %s (%u).",
			"The length of the specified database specification string",
			db_spec_string, strlen(db_spec_string),
			"exceeds the maximum characters allowed",
			STR_sizeof(DCR_HEADER, db_spec_string) - 1);
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
/*
	else if ((database_name == NULL) || (!(*database_name))) {
		strcpy(error_text, "The database name is not specified.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (strlen(database_name) >
		(STR_sizeof(DCR_HEADER, database_name) - 1)) {
		sprintf(error_text, "%s '%-.500s' (%u) %s (%u).",
			"The length of the specified database name", database_name,
			strlen(database_name), "exceeds the maximum characters allowed",
			STR_sizeof(DCR_HEADER, database_name) - 1);
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((owner_name == NULL) || (!(*owner_name))) {
		strcpy(error_text, "The owner name is not specified.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (strlen(owner_name) >
		(STR_sizeof(DCR_HEADER, owner_name) - 1)) {
		sprintf(error_text, "%s '%-.500s' (%u) %s (%u).",
			"The length of the specified owner name", owner_name,
			strlen(owner_name), "exceeds the maximum characters allowed",
			STR_sizeof(DCR_HEADER, owner_name) - 1);
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((table_name == NULL) || (!(*table_name))) {
		strcpy(error_text, "The table name is not specified.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (strlen(table_name) >
		(STR_sizeof(DCR_HEADER, table_name) - 1)) {
		sprintf(error_text, "%s '%-.500s' (%u) %s (%u).",
			"The length of the specified table name", table_name,
			strlen(table_name), "exceeds the maximum characters allowed",
			STR_sizeof(DCR_HEADER, table_name) - 1);
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((user_name != NULL) && (strlen(user_name) >
		(STR_sizeof(DCR_HEADER, db_user_name) - 1))) {
		sprintf(error_text, "%s '%-.500s' (%u) %s (%u).",
			"The length of the specified database user name", user_name,
			strlen(user_name), "exceeds the maximum characters allowed",
			STR_sizeof(DCR_HEADER, db_user_name) - 1);
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((pass_word != NULL) && (strlen(pass_word) >
		(STR_sizeof(DCR_HEADER, db_pass_word) - 1))) {
		sprintf(error_text, "%s '%-.500s' (%u) %s (%u).",
			"The length of the specified database password name", pass_word,
			strlen(pass_word), "exceeds the maximum characters allowed",
			STR_sizeof(DCR_HEADER, db_pass_word) - 1);
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
*/
	else if ((!member_count) && (!added_field_count)) {
		strcpy(error_text, "No columns or added fields were specified.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (!in_index_spec_count) {
		strcpy(error_text, "No indices were specified.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((!strlen(cache_name)) ||
		(strlen(cache_name) > (sizeof(tmp_cache_header.cache_name) - 1))) {
		sprintf(error_text, "%s (%u) --- %s 1 to %u, inclusive.",
			"Invalid cache name length", strlen(cache_name),
			"the cache name length must be in the range",
			sizeof(tmp_cache_header.cache_name) - 1);
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Create a list of all of the table columns in table column	*/
	/*	order . . .																		*/
	/*	**************************************************************	*/
	if ((return_code = DCR_CreateFieldList(member_count, member_list,
		&field_count, &field_list, &field_name_count, &field_name_list,
		&column_name_count, &column_name_list, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Add any additional (that is, user-defined) fields to the		*/
	/* lists of cache fields . . .												*/
	/*	**************************************************************	*/
	if ((return_code = DCR_DoAddedFields(added_field_count, added_field_list,
		&field_count, &field_list, &field_name_count, &field_name_list,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		At least one field must be specified for a cache, and no		*/
	/* more than the maximum.														*/
	/*	**************************************************************	*/
	if (!field_count) {
		strcpy(error_text, "No meta-data or added fields were specified.");
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (field_count > DCR_MAX_FIELD_COUNT) {
		sprintf(error_text, "%s (%u) exceeds the cache maximum fields (%u).",
			"The number of fields specified", field_count,
			DCR_MAX_FIELD_COUNT);
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Create field descriptions . . .										*/
	/*	**************************************************************	*/
	if ((return_code = DCR_AlignFields(field_count, field_list,
		&data_record_size, &field_align_count, &field_align_list,
		error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Create index data . . .													*/
	/*	**************************************************************	*/
	if ((return_code = DCR_CreateIndexSpec(in_index_spec_count,
		in_index_spec_list, field_count, field_list, field_align_count,
		field_align_list, field_name_count, field_name_list, &index_count,
		&index_list, &index_name_count, &index_name_list, &index_field_count,
		&index_field_list, &index_align_count, &index_align_list,
		&max_entry_length, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*	**************************************************************	*/
	if (index_count > DCR_MAX_INDEX_COUNT) {
		sprintf(error_text, "%s (%u) exceeds the cache maximum indices (%u).",
			"The number of indices specified", index_count,
			DCR_MAX_INDEX_COUNT);
		return_code = DCR_BAD_ARGS_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*	**************************************************************	*/
	strcpy(tmp_cache_header.cache_name, cache_name);
	strcpy(tmp_cache_header.db_spec_string,
		(db_spec_string == NULL) ? "" : db_spec_string);
	strcpy(tmp_cache_header.server_name,
		(server_name == NULL) ? "" : server_name);
	strcpy(tmp_cache_header.database_name,
		(database_name == NULL) ? "" : database_name);
	strcpy(tmp_cache_header.owner_name,
		(owner_name == NULL) ? "" : owner_name);
	strcpy(tmp_cache_header.table_name, table_name);
	strcpy(tmp_cache_header.db_user_name,
		(user_name == NULL) ? "" : user_name);
	strcpy(tmp_cache_header.db_pass_word,
		(pass_word == NULL) ? "" : pass_word);
	tmp_cache_header.cache_check_sum              = 0L;
	tmp_cache_header.cache_signature              = DCR_SIGNATURE;
	tmp_cache_header.cache_version                = DCR_VERSION_CACHE;
	tmp_cache_header.cache_writer_pid             = 0;
	tmp_cache_header.cache_writer_ip_address[0]   = 0;
	tmp_cache_header.cache_writer_ip_address[1]   = 0;
	tmp_cache_header.cache_writer_ip_address[2]   = 0;
	tmp_cache_header.cache_writer_ip_address[3]   = 0;
	tmp_cache_header.cache_lock_status.lock_count = 0L;
	tmp_cache_header.cache_lock_status.lock_flag  = DCR_STATUS_BUILDING |
		DCR_STATUS_CRITICAL;
	tmp_cache_header.cache_status                 = DCR_STATUS_BUILDING |
		DCR_STATUS_CRITICAL;
	tmp_cache_header.indirect_index_flag          = indirect_index_flag;
	tmp_cache_header.max_entry_length             = max_entry_length;
	tmp_cache_header.initial_allocation_size      = initial_allocation_size;
	tmp_cache_header.allocation_size              = allocation_size;
	tmp_cache_header.max_records_in_cache         = 0;
	tmp_cache_header.record_count                 = 0;
	tmp_cache_header.allocated_record_count       = 0;
	tmp_cache_header.actual_data_record_size      = data_record_size;
	tmp_cache_header.data_record_size             = data_record_size;
	tmp_cache_header.data_record_size             = ((unsigned int)
		STRFUNCS_ADJUST_SIZE(tmp_cache_header.data_record_size, DCR_ALIGNMENT_SIZE));
	tmp_cache_header.total_record_size            =
		tmp_cache_header.data_record_size + sizeof(DCR_LOCK);
	tmp_cache_header.total_record_size            = ((unsigned int)
		STRFUNCS_ADJUST_SIZE(tmp_cache_header.total_record_size, DCR_ALIGNMENT_SIZE));
	tmp_cache_header.allocation_granularity       =
		allocation_size * tmp_cache_header.total_record_size;
	tmp_cache_header.basic_header_area_size       = sizeof(tmp_cache_header);
	tmp_cache_header.header_area_size             =
		STRFUNCS_ADJUST_SIZE(tmp_cache_header.basic_header_area_size,
		DCR_HEADER_PAGE_SIZE);
	tmp_cache_header.data_area_offset             = 0L;
	tmp_cache_header.data_area_size               = 0L;
	tmp_cache_header.index_area_offset            = 0L;
	tmp_cache_header.index_area_size              = 0L;

	tmp_cache_header.area_list[DCR_AREA_FIELD].count           =
		field_count;
	tmp_cache_header.area_list[DCR_AREA_FIELD].item_size       =
		sizeof(*field_list);
	area_list[DCR_AREA_FIELD]                                  =
		field_list;
	tmp_cache_header.area_list[DCR_AREA_FIELD_NAME].count      =
		field_name_count;
	tmp_cache_header.area_list[DCR_AREA_FIELD_NAME].item_size  =
		sizeof(*field_name_list);
	area_list[DCR_AREA_FIELD_NAME]                             =
		field_name_list;
	tmp_cache_header.area_list[DCR_AREA_COLUMN_NAME].count     =
		column_name_count;
	tmp_cache_header.area_list[DCR_AREA_COLUMN_NAME].item_size =
		sizeof(*column_name_list);
	area_list[DCR_AREA_COLUMN_NAME]                            =
		column_name_list;
	tmp_cache_header.area_list[DCR_AREA_FIELD_ALIGN].count     =
		field_align_count;
	tmp_cache_header.area_list[DCR_AREA_FIELD_ALIGN].item_size =
		sizeof(*field_align_list);
	area_list[DCR_AREA_FIELD_ALIGN]                            =
		field_align_list;
	tmp_cache_header.area_list[DCR_AREA_INDEX].count           =
		index_count;
	tmp_cache_header.area_list[DCR_AREA_INDEX].item_size       =
		sizeof(*index_list);
	area_list[DCR_AREA_INDEX]                                  =
		index_list;
	tmp_cache_header.area_list[DCR_AREA_INDEX_NAME].count      =
		index_name_count;
	tmp_cache_header.area_list[DCR_AREA_INDEX_NAME].item_size  =
		sizeof(*index_name_list);
	area_list[DCR_AREA_INDEX_NAME]                             =
		index_name_list;
	tmp_cache_header.area_list[DCR_AREA_INDEX_FIELD].count     =
		index_field_count;
	tmp_cache_header.area_list[DCR_AREA_INDEX_FIELD].item_size =
		sizeof(*index_field_list);
	area_list[DCR_AREA_INDEX_FIELD]                            =
		index_field_list;
	tmp_cache_header.area_list[DCR_AREA_INDEX_ALIGN].count     =
		index_align_count;
	tmp_cache_header.area_list[DCR_AREA_INDEX_ALIGN].item_size =
		sizeof(*index_align_list);
	area_list[DCR_AREA_INDEX_ALIGN]                            =
		index_align_list;

	tmp_cache_header.area_list[0].offset      =
		tmp_cache_header.basic_header_area_size;
	tmp_cache_header.area_list[0].actual_size =
		tmp_cache_header.area_list[0].count *
		tmp_cache_header.area_list[0].item_size;
	tmp_cache_header.area_list[0].total_size  =
		STRFUNCS_ADJUST_SIZE(tmp_cache_header.area_list[0].actual_size,
		DCR_ALIGNMENT_SIZE);
	for (count_1 = 1; count_1 < DCR_AREA_COUNT; count_1++) {
		tmp_cache_header.area_list[count_1].offset      =
			tmp_cache_header.area_list[count_1 - 1].offset +
			tmp_cache_header.area_list[count_1 - 1].total_size;
		tmp_cache_header.area_list[count_1].actual_size =
			tmp_cache_header.area_list[count_1].count *
			tmp_cache_header.area_list[count_1].item_size;
		tmp_cache_header.area_list[count_1].total_size  =
			STRFUNCS_ADJUST_SIZE(tmp_cache_header.area_list[count_1].actual_size,
				DCR_ALIGNMENT_SIZE);
	}

	tmp_cache_header.header_area_size =
		tmp_cache_header.area_list[DCR_AREA_COUNT - 1].offset +
		tmp_cache_header.area_list[DCR_AREA_COUNT - 1].total_size;
	tmp_cache_header.header_area_size =
		STRFUNCS_ADJUST_SIZE(tmp_cache_header.header_area_size,
		DCR_HEADER_PAGE_SIZE);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*	**************************************************************	*/
	tmp_cache_header.total_cache_size = tmp_cache_header.header_area_size +
		tmp_cache_header.data_area_size +
		tmp_cache_header.index_area_size;
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Allocate memory for the complete cache header area and		*/
	/*	populate it with data . . .												*/
	/*	**************************************************************	*/
	if ((*cache_header_ptr = ((DCR_HEADER *)
		malloc(((unsigned int) tmp_cache_header.header_area_size)))) == NULL) {
		STR_AllocMsgItem(((unsigned int) tmp_cache_header.header_area_size),
			error_text,
			"Unable to allocate memory to store the complete cache header");
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	else {
		memset(*cache_header_ptr, '\0',
			((unsigned int) tmp_cache_header.header_area_size));
		**cache_header_ptr = tmp_cache_header;
		for (count_1 = 0; count_1 < DCR_AREA_COUNT; count_1++) {
			if (tmp_cache_header.area_list[count_1].count)
				memcpy(((char *) *cache_header_ptr) +
					((unsigned int) tmp_cache_header.area_list[count_1].offset),
					area_list[count_1], ((unsigned int) tmp_cache_header.
					area_list[count_1].actual_size));
		}
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Calculate the maximum number of record which can be fit		*/
	/*	into this cache . . .														*/
	/*	**************************************************************	*/
	if ((return_code =
		DCR_CalculateMaxRecords((*cache_header_ptr)->header_area_size,
		(*cache_header_ptr)->total_record_size,
		(*cache_header_ptr)->indirect_index_flag,
		index_count, index_list, &(*cache_header_ptr)->allocation_size,
		&(*cache_header_ptr)->max_records_in_cache, error_text)) != DCR_SUCCESS)
		goto EXIT_FUNCTION;
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Calculate the initial sizes and offsets for the various		*/
	/*	cache areas . . .																*/
	/*	**************************************************************	*/
	if ((return_code =
		DCR_CalculateSizes((*cache_header_ptr)->header_area_size,
		(*cache_header_ptr)->initial_allocation_size,
		(*cache_header_ptr)->max_records_in_cache,
		(*cache_header_ptr)->total_record_size,
		(*cache_header_ptr)->indirect_index_flag,
		index_count, index_list, &(*cache_header_ptr)->allocated_record_count,
		&(*cache_header_ptr)->data_area_offset,
		&(*cache_header_ptr)->data_area_size,
		&(*cache_header_ptr)->index_area_offset,
		&(*cache_header_ptr)->index_area_size,
		&(*cache_header_ptr)->total_cache_size,
		error_text)) == DCR_SUCCESS) {
		for (count_1 = 0; count_1 < index_count; count_1++) {
			index_list[count_1].index_area_offset      =
				index_list[count_1].tmp_index_area_offset;
			index_list[count_1].index_area_size        =
				index_list[count_1].tmp_index_area_size;
			index_list[count_1].actual_index_area_size =
				index_list[count_1].tmp_actual_index_area_size;
		}
	}
	/*	**************************************************************	*/

EXIT_FUNCTION:

	mema_remove_all(&field_count,       ((void **) &field_list));
	mema_remove_all(&field_name_count,  ((void **) &field_name_list));
	mema_remove_all(&column_name_count, ((void **) &column_name_list));
	mema_remove_all(&field_align_count, ((void **) &field_align_list));
	mema_remove_all(&index_count,       ((void **) &index_list));
	mema_remove_all(&index_name_count,  ((void **) &index_name_list));
	mema_remove_all(&index_field_count, ((void **) &index_field_list));
	mema_remove_all(&index_align_count, ((void **) &index_align_list));

	if (return_code == DCR_SUCCESS) {
		DCR_StatEndTime(&tmp_stat, 1L);
		(*cache_header_ptr)->stat_list[DCR_STAT_MAKE_HEADER] = tmp_stat;
	}
	else {
		if (*cache_header_ptr != NULL) {
			free(*cache_header_ptr);
			*cache_header_ptr = NULL;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_CreateFieldList(member_count, member_list, field_count,
	field_list, field_name_count, field_name_list, column_name_count,
	column_name_list, error_text)
unsigned int       member_count;
const GEN_MEMBER  *member_list;
unsigned int      *field_count;
DCR_FIELD        **field_list;
unsigned int      *field_name_count;
DCR_FIELD_NAME   **field_name_list;
unsigned int      *column_name_count;
DCR_COLUMN_NAME  **column_name_list;
char              *error_text;
{
	int          return_code = DCR_SUCCESS;
	unsigned int count_1;
  	DCR_FIELD    tmp_field;

	*field_count       = 0;
	*field_list        = NULL;
	*field_name_count  = 0;
	*field_name_list   = NULL;
	*column_name_count = 0;
	*column_name_list  = NULL;

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Create a list of the fields ordered by the database column	*/
	/* order.																			*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < member_count; count_1++) {
		memset(&tmp_field,  '\0', sizeof(tmp_field));
		tmp_field.db_table_order = count_1;
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Set the cache field field-related members . . .				*/
		/*	***********************************************************	*/
		tmp_field.primitive_type_count =
			member_list[count_1].type_count;
		nstrcpy(tmp_field.logical_name,
			member_list[count_1].name,
			sizeof(tmp_field.logical_name) - 1);
		nstrcpy(tmp_field.field_name,
			member_list[count_1].name,
			sizeof(tmp_field.field_name) - 1);
		nstrcpy(tmp_field.db_column_name,
			member_list[count_1].name,
			sizeof(tmp_field.db_column_name) - 1);
		nstrcpy(tmp_field.primitive_type_spec,
			member_list[count_1].type_spec,
			sizeof(tmp_field.primitive_type_spec) - 1);
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Initialize some other members of the structure.				*/
		/*	***********************************************************	*/
		tmp_field.db_type              = member_list[count_1].dbc_type;
		tmp_field.primitive_list_index = 0;
		tmp_field.primitive_list_count = 0;
		tmp_field.data_offset          = 0;
		tmp_field.data_length          = 0;
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Insert the cache field into the complete list of all		*/
		/*	cache fields . . .														*/
		/*	***********************************************************	*/
		if (mema_append(field_count, ((void **) field_list), &tmp_field,
			sizeof(tmp_field)) != STRFUNCS_SUCCESS) {
			STR_AllocMsgList(*field_count + 1, sizeof(tmp_field), error_text,
				"Unable to allocate memory for the list of fields by order");
			return_code = DCR_MEMORY_FAILURE;
			break;
		}
		/*	***********************************************************	*/
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Create a list of all of the cache field names sorted by		*/
	/*	the field name.																*/
	/*	**************************************************************	*/
	if (return_code == DCR_SUCCESS) {
		if ((*field_name_list = ((DCR_FIELD_NAME *)
			calloc(*field_count, sizeof(DCR_FIELD_NAME)))) == NULL) {
			STR_AllocMsgList(*field_count, sizeof(DCR_FIELD_NAME), error_text,
				"Unable to allocate memory for the list of fields by name");
			return_code = DCR_MEMORY_FAILURE;
		}
		else {
			*field_name_count = *field_count;
			for (count_1 = 0; count_1 < *field_count; count_1++) {
				(*field_name_list)[count_1].field_number = count_1;
				nstrcpy((*field_name_list)[count_1].field_name,
					(*field_list)[count_1].field_name,
					sizeof((*field_name_list)[count_1].field_name) - 1);
			}
#ifndef NARGS
			STR_ARRAY_qsort(NULL, *field_name_count, *field_name_list,
				sizeof(**field_name_list),
				((int (*)(void *, const void *, const void *, size_t))
				DCR_CMP_FIELD_NAME));
#else
			STR_ARRAY_qsort(NULL, *field_name_count, *field_name_list,
				sizeof(**field_name_list), DCR_CMP_FIELD_NAME);
#endif /* #ifndef NARGS */
		}
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Create a list of all of the active column names sorted by	*/
	/*	the column name.																*/
	/*	**************************************************************	*/
	if (return_code == DCR_SUCCESS) {
		if ((*column_name_list = ((DCR_COLUMN_NAME *)
			calloc(*field_count, sizeof(DCR_COLUMN_NAME)))) == NULL) {
			STR_AllocMsgList(*field_count, sizeof(DCR_COLUMN_NAME), error_text,
				"Unable to allocate memory for the list of columns by name");
			return_code = DCR_MEMORY_FAILURE;
		}
		else {
			*column_name_count = *field_count;
			for (count_1 = 0; count_1 < *field_count; count_1++) {
				(*column_name_list)[count_1].field_number = count_1;
				nstrcpy((*column_name_list)[count_1].column_name,
					(*field_list)[count_1].db_column_name,
					sizeof((*column_name_list)[count_1].column_name) - 1);
			}
#ifndef NARGS
			STR_ARRAY_qsort(NULL, *column_name_count, *column_name_list,
				sizeof(**column_name_list),
				((int (*)(void *, const void *, const void *, size_t))
				DCR_CMP_COLUMN_NAME));
#else
			STR_ARRAY_qsort(NULL, *column_name_count, *column_name_list,
				sizeof(**column_name_list), DCR_CMP_COLUMN_NAME);
#endif /* #ifndef NARGS */
		}
	}
	/*	**************************************************************	*/

EXIT_FUNCTION:

	if (return_code != DCR_SUCCESS) {
		mema_remove_all(field_count,       ((void **) field_list));
		mema_remove_all(field_name_count,  ((void **) field_name_list));
		mema_remove_all(column_name_count, ((void **) column_name_list));
	}

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_DoAddedFields(added_field_count, added_field_list,
	field_count, field_list, field_name_count, field_name_list, error_text)
unsigned int     added_field_count;
char           **added_field_list;
unsigned int    *field_count;
DCR_FIELD      **field_list;
unsigned int    *field_name_count;
DCR_FIELD_NAME **field_name_list;
char            *error_text;
{
	int             return_code     = DCR_SUCCESS;
	unsigned int    tmp_field_count = 0;
	DCR_FIELD      *tmp_field_list  = NULL;
	unsigned int    count_1;
	unsigned int    found_index;
	DCR_FIELD_NAME  tmp_field_name;

	if ((return_code = DCR_GetAddedFieldList(added_field_count,
		added_field_list, &tmp_field_count, &tmp_field_list, error_text)) ==
		DCR_SUCCESS) {
		for (count_1 = 0; count_1 < tmp_field_count; count_1++) {
			if (DCR_FIND_FIELD_NAME(*field_name_count, *field_name_list,
				tmp_field_list[count_1].field_name, &found_index) ==
				STRFUNCS_ITEM_FOUND) {
				sprintf(error_text, "%s '%s' %s.",
					"The added field", tmp_field_list[count_1].field_name,
					"is already in the list of cache fields");
				return_code = DCR_FAILURE;
				break;
			}
			if (mema_append(field_count, ((void **) field_list),
				tmp_field_list + count_1, sizeof(*tmp_field_list)) !=
				STRFUNCS_SUCCESS) {
				STR_AllocMsgList(*field_count + 1, sizeof(*tmp_field_list),
					error_text,
					"Unable to allocate memory for the added field list");
				return_code = DCR_MEMORY_FAILURE;
				break;
			}
			memset(&tmp_field_name, '\0', sizeof(tmp_field_name));
			tmp_field_name.field_number = *field_count - 1;
			nstrcpy(tmp_field_name.field_name,
				tmp_field_list[count_1].field_name,
				sizeof(tmp_field_name.field_name) - 1);
			if (mema_insert(field_name_count, ((void **) field_name_list),
				&tmp_field_name, sizeof(tmp_field_name), found_index) !=
				STRFUNCS_SUCCESS) {
				STR_AllocMsgList(*field_name_count + 1, sizeof(tmp_field_name),
					error_text,
					"Unable to allocate memory for the field name list");
				return_code = DCR_MEMORY_FAILURE;
				break;
			}
		}
		mema_remove_all(&tmp_field_count, ((void **) &tmp_field_list));
	}

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_AlignFields(field_count, field_list, data_record_size,
	field_align_count, field_align_list, error_text)
unsigned int   field_count;
DCR_FIELD     *field_list;
unsigned int  *data_record_size;
unsigned int  *field_align_count;
GEN_ALIGN    **field_align_list;
char          *error_text;
{
	int           return_code     = DCR_SUCCESS;
	unsigned int  total_length    = 0;
	unsigned int  tmp_align_count = 0;
	GEN_ALIGN    *tmp_align_list  = NULL;
	unsigned int  count_1;
	unsigned int  count_2;
	int           gen_return_code;
	char          tmp_string[DCR_MAX_ERROR_TEXT];
	char          genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*data_record_size  = 0;
	*field_align_count = 0;
	*field_align_list  = NULL;

	for (count_1 = 0; count_1 < field_count; count_1++) {
		field_list[count_1].primitive_type_count =
			(!field_list[count_1].primitive_type_count) ? 1 :
			field_list[count_1].primitive_type_count;
		field_list[count_1].primitive_list_index = *field_align_count;
		field_list[count_1].primitive_list_count = 0;
		if ((gen_return_code = GEN_ALIGN_GetFieldAlignList(
			((unsigned int) field_list[count_1].primitive_type_count),
			field_list[count_1].primitive_type_spec, GENFUNCS_TRUE,
			&field_list[count_1].data_length, &tmp_align_count, &tmp_align_list,
			genfuncs_error_text)) != GENFUNCS_SUCCESS) {
			if (field_list[count_1].db_column_name[0])
				sprintf(tmp_string, "the database column named '%s'",
					field_list[count_1].db_column_name);
			else
				sprintf(tmp_string, "%s '%s'",
					"the added field named", field_list[count_1].field_name);
			sprintf(error_text, "%s %s '%s' of length %u for %s: %-.500s",
				"An error occurred while attempting to parse the primitive type",
				"specification", field_list[count_1].primitive_type_spec,
				field_list[count_1].primitive_type_count, tmp_string,
				genfuncs_error_text);
			return_code = DCR_MAP_TRUTH_GEN_TO_DCR(gen_return_code);
			goto EXIT_FUNCTION;
		}
		else if (field_list[count_1].data_length > DCR_MAX_FIELD_SIZE) {
			if (field_list[count_1].db_column_name[0])
				sprintf(tmp_string, "the database column named '%s'",
					field_list[count_1].db_column_name);
			else
				sprintf(tmp_string, "%s '%s'",
					"the added field named", field_list[count_1].field_name);
			sprintf(error_text,
				"%s %s '%s' of length %u for %s: %s (%u) %s (%u).",
				"An error occurred while attempting to parse the primitive type",
				"specification", field_list[count_1].primitive_type_spec,
				field_list[count_1].primitive_type_count, tmp_string,
				"the calculated length of the field",
				field_list[count_1].data_length, "exceeds the cache maximum",
				DCR_MAX_FIELD_SIZE);
			return_code = DCR_FAILURE;
			goto EXIT_FUNCTION;
		}
		else if (mema_add(tmp_align_count, tmp_align_list,
			sizeof(*tmp_align_list), field_align_count,
			((void **) field_align_list)) != STRFUNCS_SUCCESS) {
			if (field_list[count_1].db_column_name[0])
				sprintf(tmp_string, "the database column named '%s'",
					field_list[count_1].db_column_name);
			else
				sprintf(tmp_string, "%s '%s'",
					"the added field named", field_list[count_1].field_name);
			STR_AllocMsgList(*field_align_count + tmp_align_count,
				sizeof(*tmp_align_list), error_text,
				"Unable to allocate memory for the field alignment list for %s",
				tmp_string);
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		field_list[count_1].primitive_list_count = tmp_align_count;
		mema_remove_all(&tmp_align_count, ((void **) &tmp_align_list));
		if ((total_length += field_list[count_1].data_length) >
			DCR_MAX_RECORD_SIZE) {
			sprintf(error_text,
				"The total length of all cache fields exceeds the maximum (%u).",
				DCR_MAX_RECORD_SIZE);
			return_code = DCR_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Create an array of alignment items for the record . . .		*/
	/*	**************************************************************	*/
	if (GEN_ALIGN_Align(data_record_size, *field_align_count,
		*field_align_list, genfuncs_error_text) != GENFUNCS_SUCCESS) {
		nstrcat(strcat(strcpy(error_text,
			"Attempt to create an alignment list for the fields failed"), ": "),
			genfuncs_error_text, DCR_MAX_ERROR_TEXT - 100);
		return_code = DCR_MAP_TRUTH_GEN_TO_DCR(return_code);
		goto EXIT_FUNCTION;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Set the field data length and offset . . .						*/
	/*	**************************************************************	*/
	for (count_1 = 0; count_1 < field_count; count_1++) {
		field_list[count_1].data_offset =
			(*field_align_list)[field_list[count_1].primitive_list_index].offset;
		field_list[count_1].data_length = 0;
		for (count_2 = 0; count_2 < field_list[count_1].primitive_list_count;
			count_2++)
			field_list[count_1].data_length +=
				(*field_align_list)[field_list[count_1].primitive_list_index +
				count_2].length;
	}
	/*	**************************************************************	*/

EXIT_FUNCTION:

	mema_remove_all(&tmp_align_count, ((void **) &tmp_align_list));

	if (return_code != DCR_SUCCESS)
		mema_remove_all(field_align_count, ((void **) field_align_list));

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_CreateIndexSpec(in_index_spec_count, in_index_spec_list,
	field_count, field_list, field_align_count, field_align_list,
	field_name_count, field_name_list, index_count, index_list,
	index_name_count, index_name_list, index_field_count, index_field_list,
	index_align_count, index_align_list, max_entry_length, error_text)
unsigned int           in_index_spec_count;
char                 **in_index_spec_list;
unsigned int           field_count;
const DCR_FIELD       *field_list;
unsigned int           field_align_count;
const GEN_ALIGN       *field_align_list;
unsigned int           field_name_count;
const DCR_FIELD_NAME  *field_name_list;
unsigned int          *index_count;
DCR_INDEX            **index_list;
unsigned int          *index_name_count;
DCR_INDEX_NAME       **index_name_list;
unsigned int          *index_field_count;
unsigned int         **index_field_list;
unsigned int          *index_align_count;
GEN_ALIGN            **index_align_list;
unsigned int          *max_entry_length;
char                  *error_text;
{
	*index_count       = 0;
	*index_list        = NULL;
	*index_name_count  = 0;
	*index_name_list   = NULL;
	*index_field_count = 0;
	*index_field_list  = NULL;
	*index_align_count = 0;
	*index_align_list  = NULL;

	return(DCR_AppendIndexSpec(in_index_spec_count, in_index_spec_list,
		field_count, field_list, field_align_count, field_align_list,
		field_name_count, field_name_list, index_count, index_list,
		index_name_count, index_name_list, index_field_count, index_field_list,
		index_align_count, index_align_list, max_entry_length, error_text));
}
/*	***********************************************************************	*/

static int DCR_AppendIndexSpec(in_index_spec_count, in_index_spec_list,
	field_count, field_list, field_align_count, field_align_list,
	field_name_count, field_name_list, index_count, index_list,
	index_name_count, index_name_list, index_field_count, index_field_list,
	index_align_count, index_align_list, max_entry_length, error_text)
unsigned int           in_index_spec_count;
char                 **in_index_spec_list;
unsigned int           field_count;
const DCR_FIELD       *field_list;
unsigned int           field_align_count;
const GEN_ALIGN       *field_align_list;
unsigned int           field_name_count;
const DCR_FIELD_NAME  *field_name_list;
unsigned int          *index_count;
DCR_INDEX            **index_list;
unsigned int          *index_name_count;
DCR_INDEX_NAME       **index_name_list;
unsigned int          *index_field_count;
unsigned int         **index_field_list;
unsigned int          *index_align_count;
GEN_ALIGN            **index_align_list;
unsigned int          *max_entry_length;
char                  *error_text;
{
	int                    return_code          = DCR_SUCCESS;
	char                  *tmp_string           = NULL;
	unsigned int           ordered_name_count   = 0;
	char                 **ordered_name_list    = NULL;
	unsigned int           column_count         = 0;
	char                 **column_list          = NULL;
	unsigned int           ordered_column_count = 0;
	char                 **ordered_column_list  = NULL;
	unsigned int           tmp_align_count      = 0;
	GEN_ALIGN             *tmp_align_list       = NULL;
	unsigned int           original_index_count;
	unsigned int           original_index_field_count;
	unsigned int           original_index_align_count;
	unsigned int           count_1;
	unsigned int           count_2;
	unsigned int           found_index;
	unsigned int           field_index;
	int                    strfuncs_code;
	char                  *tmp_ptr;
	DCR_INDEX        tmp_index;
	DCR_INDEX_NAME   tmp_index_name;
	GEN_ALIGN             *tmp_align_ptr;
   char                   tmp_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*max_entry_length          = 0;

	original_index_count       = *index_count;
	original_index_field_count = *index_field_count;
	original_index_align_count = *index_align_count;

	memset(&tmp_index, '\0', sizeof(tmp_index));

	for (count_1 = 0; count_1 < *index_count; count_1++) {
		if (strl_append(&ordered_name_count, &ordered_name_list,
			(*index_list)[count_1].index_name) == STRFUNCS_ERROR) {
			strcpy(error_text,
				"Unable to allocate memory for the ordered list of indices.");
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
	}

	strl_sort(ordered_name_count, ordered_name_list);
	strl_uniq(&ordered_name_count, &ordered_name_list);

	for (count_1 = 0; count_1 < in_index_spec_count; count_1++) {
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Attempt to make copy of the index specification string.	*/
		/*	***********************************************************	*/
		if ((tmp_string = strdup(in_index_spec_list[count_1])) == NULL) {
			STR_AllocMsgItem(strlen(in_index_spec_list[count_1]) + 1, error_text,
				"Unable to copy index specification number %u ('%-500s')",
				count_1, in_index_spec_list[count_1]);
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Ensure that the index specification string is not empty	*/
		/* after removing white-space and other garbage . . .				*/
		/*	***********************************************************	*/
		else if (((tmp_ptr = strchr(trim(nocontrl(noblank(tmp_string))),
			'=')) == NULL) || (tmp_ptr == tmp_string) ||
			(!(*(tmp_ptr + 1)))) {
			sprintf(error_text, "%s %u ('%-.500s') --- %s.",
				"Invalid index specification number", count_1,
				in_index_spec_list[count_1],
				"expected <index-name>=<column-name>[,<column-name> . . .]");
			return_code = DCR_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		The name of the index in the index specification string	*/
		/*	may not exceed the space defined for it . . .					*/
		/*	***********************************************************	*/
		else if ((tmp_ptr - tmp_string) > (sizeof(tmp_index.index_name) - 1)) {
			sprintf(error_text, "%s %u ('%-.500s') --- %s (%u).",
				"Invalid index specification number", count_1,
				in_index_spec_list[count_1],
				"the index name length exceeds the maximum allowable",
				sizeof(tmp_index.index_name) - 1);
			return_code = DCR_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Unspecified column names in the index specification		*/
		/*	string are not allowed . . .											*/
		/*	***********************************************************	*/
		else if ((*(tmp_ptr + 1) == ',') ||
			(tmp_ptr[strlen(tmp_ptr) - 1] == ',') ||
			(strstr(tmp_ptr, ",,") != NULL)) {
			sprintf(error_text, "%s %u ('%-.500s') --- %s --- %s.",
				"Invalid index specification number", count_1,
				in_index_spec_list[count_1], "empty column name encountered",
				"expected <index-name>=<column-name>[,<column-name> . . .]");
			return_code = DCR_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Attempt to add the name of the index to the list of all	*/
		/*	index names encountered so far.										*/
		/*																					*/
		/*		As the name of the index may not be be duplicated, it is	*/
		/*	an error if we find it in the list.									*/
		/*	***********************************************************	*/
		else if ((strfuncs_code = strln_search(&ordered_name_count,
			&ordered_name_list, tmp_string, ((size_t) (tmp_ptr - tmp_string)),
			&found_index)) == STRFUNCS_ERROR) {
			sprintf(error_text, "%s (%u bytes required).",
				"Unable to add index name to the list of indices",
				(ordered_name_count + 1) *
				(sizeof(char *) + sizeof(tmp_index.index_name)));
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		else if (strfuncs_code == STRFUNCS_ITEM_FOUND) {
			sprintf(error_text, "%s %u ('%-.500s') %s %s %u.",
				"The index specification number", count_1,
				in_index_spec_list[count_1],
				"has an index name which is duplicated in existing index",
				"specification number", found_index);
			return_code = DCR_BAD_ARGS_FAILURE;
			goto EXIT_FUNCTION;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Break the comma-separated list of column names which		*/
		/*	comprise the index specification string into an array of		*/
		/*	pointers to char.															*/
		/*	***********************************************************	*/
		else if (sepwordx(tmp_ptr + 1, ",", &column_count, &column_list) !=
			STRFUNCS_SUCCESS) {
			sprintf(error_text, "%s %u ('%-.500s') %s (%u bytes required).",
				"Unable to allocate memory for the index specification number",
				count_1, in_index_spec_list[count_1], "list of columns",
				(chrcnt(tmp_ptr + 1, ',') * (sizeof(char *) + 1)) +
				strlen(tmp_ptr + 1));
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		nstrcpy(tmp_index.index_name, tmp_string,
			((size_t) (tmp_ptr - tmp_string)));
		tmp_index.field_count        = 0;
		tmp_index.field_index        = *index_field_count;
		tmp_index.record_align_count = 0;
		tmp_index.record_align_index = *index_align_count;
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		for (count_2 = 0; count_2 < column_count; count_2++) {
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		A field name may appear only once in a particular	*/
			/*	index specification.												*/
			/*	*****************************************************	*/
			if ((strfuncs_code = strl_search(&ordered_column_count,
				&ordered_column_list, column_list[count_2], &found_index)) ==
				STRFUNCS_ITEM_FOUND) {
				sprintf(error_text, "%s '%s' %s %u ('%-.500s').",
					"The column name", column_list[count_2],
					"occurs more than once in index specification number",
					count_1, in_index_spec_list[count_1]);
				return_code = DCR_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			else if (strfuncs_code != STRFUNCS_ITEM_NOT_FOUND) {
				sprintf(error_text, "%s %u ('%-.500s') %s (%u bytes required).",
					"Unable to allocate memory for the index specification number",
					count_1, in_index_spec_list[count_1],
					"ordered list of columns", strlen(column_list[count_2]) + 1);
				return_code = DCR_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		The current column component of the index must		*/
			/*	exist in the list of table columns . . .					*/
			/*	*****************************************************	*/
			if (DCR_FIND_FIELD_NAME(field_name_count, field_name_list,
				column_list[count_2], &found_index) ==
				STRFUNCS_ITEM_NOT_FOUND) {
				sprintf(error_text, "%s '%s' %s %u ('%-.500s') %s.",
					"The column name", column_list[count_2],
					"in index specification number", count_1,
					in_index_spec_list[count_1], "is not a valid field name");
				return_code = DCR_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
			field_index = field_name_list[found_index].field_number;
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		Add the current column component of the index to	*/
			/*	list of columns . . .											*/
			/*	*****************************************************	*/
			if (mema_append(index_field_count, ((void **) index_field_list),
				&field_index, sizeof(unsigned int)) != STRFUNCS_SUCCESS) {
				STR_AllocMsgList(*index_field_count, sizeof(field_index),
					error_text, "Unable to expand the list of %s %u ('%-.500s')",
					"index field names for index specification number", count_1,
					in_index_spec_list[count_1]);
				return_code = DCR_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		Add the align list for the current column component*/
			/*	of this index to the list of align elements . . .		*/
			/*	*****************************************************	*/
			tmp_align_ptr = ((GEN_ALIGN *) ((!(*index_align_count)) ?
				malloc(field_list[field_index].primitive_list_count *
				sizeof(GEN_ALIGN)) :
				realloc(*index_align_list, (*index_align_count +
				field_list[field_index].primitive_list_count) *
				sizeof(GEN_ALIGN))));
			if (tmp_align_ptr == NULL) {
				sprintf(error_text, "%s %s %u ('%-.500s').",
					"Unable to expand the list of field align elements for index",
					"specification number", count_1, in_index_spec_list[count_1]);
				return_code = DCR_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			/*	*****************************************************	*/
			/*	*****************************************************	*/
			/*		Update the data for this index descriptor . . .		*/
			/*	*****************************************************	*/
			memcpy(tmp_align_ptr + *index_align_count,
				field_align_list + field_list[field_index].primitive_list_index,
				field_list[field_index].primitive_list_count *
				sizeof(GEN_ALIGN));
			tmp_index.field_count++;
			tmp_index.record_align_count +=
				field_list[field_index].primitive_list_count;
			*index_align_count           +=
				field_list[field_index].primitive_list_count;
			*index_align_list             = tmp_align_ptr;
			/*	*****************************************************	*/
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Create a list of align elements which describes the data	*/
		/* fields within an embedded (that is, non-indirect) index.		*/
		/*																					*/
		/*		We do this in the following steps:								*/
		/*																					*/
		/*		1)	Allocate memory for the array. The length of the		*/
		/*			array is equal to the number of align elements in the	*/
		/*			align list which describes the fields which comprise	*/
		/*			an index plus one for the 'unsigned long' which is		*/
		/*			the offset of the data record.								*/
		/*																					*/
		/*		2)	Copy the field align list and initialize the align		*/
		/*			list element for the data record offset.					*/
		/*																					*/
		/*		3)	Determine the size and alignment requirements of the	*/
		/*			embedded index entry.											*/
		/*																					*/
		/*		4)	Add the align list to the master list of index align	*/
		/*			elements.															*/
		/*	***********************************************************	*/
		if ((tmp_align_list = ((GEN_ALIGN *)
			calloc(tmp_index.record_align_count + 1,
			sizeof(GEN_ALIGN)))) == NULL) {
			sprintf(error_text, "%s %s %u ('%-.500s').",
				"Unable to allocate memory for the list of align elements which",
				"describe the embedded index data for index specification number",
				count_1, in_index_spec_list[count_1]);
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		memcpy(tmp_align_list,
			*index_align_list + tmp_index.record_align_index,
			tmp_index.record_align_count * sizeof(GEN_ALIGN));
		tmp_align_count                                  =
			tmp_index.record_align_count + 1;
		tmp_align_list[tmp_align_count - 1].type         =
			GEN_C_ALIGN_unsigned_long;
		tmp_align_list[tmp_align_count - 1].array_length = 1;
		if (GEN_ALIGN_Align(&tmp_index.index_entry_size, tmp_align_count,
			tmp_align_list, tmp_error_text) != GENFUNCS_SUCCESS) {
			nstrcat(strcat(strcpy(error_text,
				"Attempt to create an alignment list for the indices failed"),
				": "), tmp_error_text, DCR_MAX_ERROR_TEXT - 100);
			return_code = DCR_FAILURE;
			goto EXIT_FUNCTION;
		}
		tmp_index.index_pointer_offset =
			tmp_align_list[tmp_align_count - 1].offset;
		tmp_index.index_align_count    = tmp_align_count - 1;
		tmp_index.index_align_index    = *index_align_count;
		if ((tmp_align_ptr = ((GEN_ALIGN *) realloc(*index_align_list,
			(*index_align_count + tmp_align_count) *
			sizeof(GEN_ALIGN)))) == NULL) {
			sprintf(error_text, "%s %s %u ('%-.500s').",
				"Unable to expand the list of index align elements for index",
				"specification number", count_1, in_index_spec_list[count_1]);
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		memcpy(tmp_align_ptr + *index_align_count, tmp_align_list,
			tmp_align_count * sizeof(GEN_ALIGN));
		*index_align_count += tmp_align_count;
		*index_align_list   = tmp_align_ptr;
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Set the maximum length of an embedded index entry . . .	*/
		/*	***********************************************************	*/
		*max_entry_length = (*max_entry_length < tmp_index.index_entry_size) ?
			tmp_index.index_entry_size : *max_entry_length;
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		The list of fields in an index specification may not be	*/
		/* the same as that in any other index . . .							*/
		/*	***********************************************************	*/
		for (count_2 = 0; count_2 < *index_count; count_2++) {
			if (((*index_list)[count_2].record_align_count ==
				tmp_index.record_align_count) &&
				(!memcmp(*index_align_list +
				(*index_list)[count_2].record_align_index,
				*index_align_list + tmp_index.record_align_index,
				tmp_index.record_align_count * sizeof(GEN_ALIGN)))) {
				sprintf(error_text, "%s %u ('%-.500s') %s %s %u.",
					"The index specification number", count_1,
					in_index_spec_list[count_1],
					"has a field list which is duplicated in existing index",
					"specification number", count_2);
				return_code = DCR_BAD_ARGS_FAILURE;
				goto EXIT_FUNCTION;
			}
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Add this index descriptor to the list of all indices.		*/
		/*	***********************************************************	*/
		if (mema_append(index_count, ((void **) index_list), &tmp_index,
			sizeof(tmp_index)) != STRFUNCS_SUCCESS) {
			STR_AllocMsgList(*index_count + 1, sizeof(tmp_index), error_text,
				"Unable to allocate memory for the expanded list of indices");
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Add this index name to the list of index names ordered	*/
		/*	name.																			*/
		/*	***********************************************************	*/
		memset(&tmp_index_name, '\0', sizeof(tmp_index_name));
		DCR_FIND_INDEX_NAME(*index_name_count, *index_name_list,
			tmp_index.index_name, &found_index);
		tmp_index_name.index_number = *index_count - 1;
		nstrcpy(tmp_index_name.index_name, tmp_index.index_name,
			sizeof(tmp_index_name.index_name) - 1);
		if (mema_insert(index_name_count, ((void **) index_name_list),
			&tmp_index_name, sizeof(tmp_index_name), found_index) !=
			STRFUNCS_SUCCESS) {
			STR_AllocMsgList(*index_name_count + 1, sizeof(tmp_index_name),
				error_text,
		"Unable to allocate memory for the list of indices by index name");
			return_code = DCR_MEMORY_FAILURE;
			goto EXIT_FUNCTION;
		}
		/*	***********************************************************	*/
		/*	***********************************************************	*/
		/*		Free up the temporary data for use in parsing the next	*/
		/*	index specification string . . .										*/
		/*	***********************************************************	*/
		free(tmp_string);
		tmp_string = NULL;
		strl_remove_all(&column_count, &column_list);
		strl_remove_all(&ordered_column_count, &ordered_column_list);
		mema_remove_all(&tmp_align_count, ((void **) &tmp_align_list));
		/*	***********************************************************	*/
	}

EXIT_FUNCTION:

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Free up the temporary data . . .											*/
	/*	*****************************************************************	*/
	if (tmp_string != NULL)
		free(tmp_string);
	strl_remove_all(&ordered_name_count, &ordered_name_list);
	strl_remove_all(&column_count, &column_list);
	strl_remove_all(&ordered_column_count, &ordered_column_list);
	mema_remove_all(&tmp_align_count, ((void **) &tmp_align_list));
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		If we failed to append the specified indices, restore the		*/
	/*	arrays defining the pre-exisiting indices to their original state.*/
	/*	*****************************************************************	*/
	if (return_code != DCR_SUCCESS) {
		mema_remove(index_count,       ((void **) index_list),
			sizeof(**index_list), original_index_count,
			*index_count);
		mema_remove(index_field_count, ((void **) index_field_list),
			sizeof(**index_field_list), original_index_field_count,
			*index_field_count);
		mema_remove(index_align_count, ((void **) index_align_list),
			sizeof(**index_align_list), original_index_align_count,
			*index_align_count);
	}
	/*	*****************************************************************	*/

	return(return_code);
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
	int           return_code;
	unsigned int  count_1;
	DCR_HEADER   *cache_header_ptr = NULL;
	DCR_CACHE     cache_data;
	char          error_text[DCR_MAX_ERROR_TEXT];

	fprintf(stderr, "Test routine for 'DCR_MakeHeader()'\n");
	fprintf(stderr, "---- ------- --- ------------------\n\n");

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
		fprintf(stderr, "Running %u times . . .", TEST_COUNT);
		for (count_1 = 0; count_1 < TEST_COUNT; count_1++) {
			if ((return_code = DCR_MakeHeader("TEST_CACHE_NAME",
				"TEST_SERVER,TEST_DB,TEST_OWNER,mlds,mlds", "TEST_SERVER",
				"TEST_DB", "TEST_OWNER", "mlds", "mlds", "TEST_TABLE", 4096, 4096,
				DCR_TRUE, MemberCount, MemberList, 0, NULL, IndexSpecCount,
				IndexSpecList, &cache_header_ptr, error_text)) != DCR_SUCCESS) {
				fprintf(stderr, "ERROR ON ITERATION %u: %s\n", count_1,
					error_text);
				break;
			}
			else
				free(cache_header_ptr);
		}
		fprintf(stderr, " done\n\n");
	}

	return(return_code);
}

#endif /* #ifdef TEST_MAIN */

