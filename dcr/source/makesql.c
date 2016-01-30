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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_MakeSQL(cache_ptr, update_flag, update_column, update_date,
	sql_command, error_text)
DCR_CACHE  *cache_ptr;
int         update_flag;
char       *update_column;
DTIME      *update_date;
char      **sql_command;
char       *error_text;
{
	int          return_code = DCR_SUCCESS;
	unsigned int count_1;
	unsigned int sql_length;
	char         buffer[100];

	*sql_command  = NULL;


	sql_length    = ((sizeof(cache_ptr->field_list->db_column_name) + 10) *
		cache_ptr->field_count) + ((update_flag == DCR_TRUE) ?
		(sizeof(cache_ptr->field_list->db_column_name) + 100) : 0) + 1000;
	sql_length   += (cache_ptr->sql_where_clause == NULL)    ? 0 :
		strlen(cache_ptr->sql_where_clause);
	sql_length   += (cache_ptr->sql_group_by_clause == NULL) ? 0 :
		strlen(cache_ptr->sql_group_by_clause);
	sql_length   += (cache_ptr->sql_order_by_clause == NULL) ? 0 :
		strlen(cache_ptr->sql_order_by_clause);

	if ((update_flag == DCR_TRUE) &&
		((update_column == NULL) || (!(*update_column)))) {
		strcpy(error_text,
			"The update flag is set, but the update date column name is empty.");
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if ((update_flag == DCR_TRUE) && (update_date == NULL)) {
		strcpy(error_text,
			"The update flag is set, but the update date is NULL.");
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if ((update_flag == DCR_TRUE) &&
		(DCR_FIND_FIELD_NAME(cache_ptr->field_name_count,
		cache_ptr->field_name_list, update_column, NULL) !=
		STRFUNCS_ITEM_FOUND)) {
		sprintf(error_text, "%s ('%-.500s') is not in the list of fields.",
			"The specified update date column name", update_column);
		return_code = DCR_BAD_ARGS_FAILURE;
	}
	else if ((*sql_command = ((char *) malloc(sql_length * sizeof(char)))) ==
		NULL) {
		sprintf(error_text, "%s (%u bytes required).",
			"Attempt to allocate memory for a database SQL statement failed",
			sql_length);
		return_code = DCR_MEMORY_FAILURE;
	}
	else {
		strcpy(*sql_command, "SELECT ");
		for (count_1 = 0; count_1 < cache_ptr->field_count; count_1++) {
			if (cache_ptr->field_list[count_1].db_column_name[0])
				strcat(strcat(*sql_command, (count_1) ? "," : ""),
					cache_ptr->field_list[count_1].db_column_name);
		}
		sprintf(*sql_command + strlen(*sql_command), " FROM %s.%s.%s",
			cache_ptr->header_ptr->database_name,
			cache_ptr->header_ptr->owner_name,
			cache_ptr->header_ptr->table_name);
		if ((update_flag == DCR_TRUE) ||
			(cache_ptr->sql_where_clause != NULL)) {
			strcat(*sql_command, " WHERE ");
			if (cache_ptr->sql_where_clause != NULL)
				sprintf(*sql_command + strlen(*sql_command), "(%s)%s",
					cache_ptr->sql_where_clause, (update_flag != DCR_TRUE) ? "" :
					" AND ");
			if (update_flag == DCR_TRUE)
				sprintf(*sql_command + strlen(*sql_command), "(%s >= \"%s\")",
					update_column, DTIME_FormatDate(update_date, NULL, buffer));
		}
		if (cache_ptr->sql_group_by_clause != NULL)
			sprintf(*sql_command + strlen(*sql_command), " GROUP BY %s",
				cache_ptr->sql_group_by_clause);
		if (cache_ptr->sql_order_by_clause != NULL)
			sprintf(*sql_command + strlen(*sql_command), " ORDER BY %s",
				cache_ptr->sql_order_by_clause);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_CreateDBDeleteSQL(cache_ptr, database_name, owner_name,
	table_name, record_ptr, primary_key_count, primary_key_list, sql_command,
	error_text)
const DCR_CACHE *cache_ptr;
const char      *database_name;
const char      *owner_name;
const char      *table_name;
const char      *record_ptr;
unsigned int     primary_key_count;
unsigned int    *primary_key_list;
char            *sql_command;
char            *error_text;
{
	int  return_code = DCR_SUCCESS;
	char tmp_error_text[DCR_MAX_ERROR_TEXT];

	sprintf(sql_command, "DELETE FROM %s.%s.%s", database_name, owner_name,
		table_name);

	if ((return_code = DCR_CreateDBWhereClause(cache_ptr, record_ptr,
		primary_key_count, primary_key_list, sql_command + strlen(sql_command),
		tmp_error_text)) != DCR_SUCCESS)
		sprintf(error_text, "%s for cache file '%-.500s': %s",
			"Error occurred while constructing an SQL 'DELETE' statement",
			cache_ptr->cache_file_name, tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_CreateDBInsertSQL(cache_ptr, database_name, owner_name,
	table_name, record_ptr, sql_command, error_text)
const DCR_CACHE *cache_ptr;
const char      *database_name;
const char      *owner_name;
const char      *table_name;
const char      *record_ptr;
char            *sql_command;
char            *error_text;
{
	int          return_code     = DCR_SUCCESS;
	unsigned int db_column_count = 0;
	unsigned int count_1;
	char         tmp_error_text[DCR_MAX_ERROR_TEXT];

	sprintf(sql_command, "INSERT INTO %s.%s.%s", database_name, owner_name,
		table_name);

	for (count_1 = 0; count_1 < cache_ptr->field_count; count_1++) {
		if (*cache_ptr->field_list[count_1].db_column_name) {
			strcat(strcat(sql_command, (!count_1) ? " (" : ", "),
				cache_ptr->field_list[count_1].db_column_name);
			db_column_count++;
		}
	}
	strcat(sql_command, ") VALUES");

	if (!db_column_count) {
		strcpy(tmp_error_text, "The cache file has no database columns.");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	for (count_1 = 0; count_1 < cache_ptr->field_count; count_1++) {
		if (*cache_ptr->field_list[count_1].db_column_name) {
			strcat(sql_command, (!db_column_count) ? " (" : ", ");
			if ((return_code = DBC_SYB_FMT_Data_SQL(cache_ptr->
				field_list[count_1].db_type, cache_ptr->field_list[count_1].
				data_length, record_ptr + cache_ptr->field_list[count_1].
				data_offset, sql_command + strlen(sql_command),
				tmp_error_text)) != DCR_SUCCESS) {
				sprintf(error_text, "Error in database column name '%s' ---  %s",
					cache_ptr->field_list[count_1].db_column_name, tmp_error_text);
				strcpy(tmp_error_text, error_text);
				break;
			}
		}
	}
	strcat(sql_command, ")");

EXIT_FUNCTION:

	if (return_code != DCR_SUCCESS)
		sprintf(error_text, "%s for cache file '%-.500s': %s",
			"Error occurred while constructing an SQL 'INSERT' statement",
			cache_ptr->cache_file_name, tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_CreateDBUpdateSQL(cache_ptr, database_name, owner_name,
	table_name, record_ptr, primary_key_count, primary_key_list, sql_command,
	error_text)
const DCR_CACHE *cache_ptr;
const char      *database_name;
const char      *owner_name;
const char      *table_name;
const char      *record_ptr;
unsigned int     primary_key_count;
unsigned int    *primary_key_list;
char            *sql_command;
char            *error_text;
{
	int          return_code     = DCR_SUCCESS;
	unsigned int db_column_count = 0;
	unsigned int count_1;
	char         tmp_error_text[DCR_MAX_ERROR_TEXT];

	sprintf(sql_command, "UPDATE %s.%s.%s", database_name, owner_name,
		table_name);

	for (count_1 = 0; count_1 < cache_ptr->field_count; count_1++) {
		if (*cache_ptr->field_list[count_1].db_column_name) {
			strcat(strcat(strcat(sql_command, (!db_column_count) ? "SET " :
				", "), cache_ptr->field_list[count_1].db_column_name), " = ");
			if ((return_code = DBC_SYB_FMT_Data_SQL(cache_ptr->
				field_list[count_1].db_type, cache_ptr->field_list[count_1].
				data_length, record_ptr + cache_ptr->field_list[count_1].
				data_offset, sql_command + strlen(sql_command),
				tmp_error_text)) != DCR_SUCCESS) {
				sprintf(error_text, "Error in database column name '%s' ---  %s",
					cache_ptr->field_list[count_1].db_column_name, tmp_error_text);
				strcpy(tmp_error_text, error_text);
				goto EXIT_FUNCTION;
			}
			db_column_count++;
		}
	}
	strcat(sql_command, ")");

	if (!db_column_count) {
		strcpy(tmp_error_text, "The cache file has no database columns.");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}

	return_code = DCR_CreateDBWhereClause(cache_ptr, record_ptr,
		primary_key_count, primary_key_list, sql_command + strlen(sql_command),
		tmp_error_text);

EXIT_FUNCTION:

	if (return_code != DCR_SUCCESS)
		sprintf(error_text, "%s for cache file '%-.500s': %s",
			"Error occurred while constructing an SQL 'UPDATE' statement",
			cache_ptr->cache_file_name, tmp_error_text);

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_CreateDBWhereClause(cache_ptr, record_ptr, primary_key_count,
	primary_key_list, sql_command, error_text)
const DCR_CACHE *cache_ptr;
const char      *record_ptr;
unsigned int     primary_key_count;
unsigned int    *primary_key_list;
char            *sql_command;
char            *error_text;
{
	int          return_code = DCR_SUCCESS;
	unsigned int count_1;
	char         tmp_error_text[DCR_MAX_ERROR_TEXT];

	for (count_1 = 0; count_1 < primary_key_count; count_1++) {
		if (primary_key_list[count_1] >= cache_ptr->field_count) {
			sprintf(error_text, "%s %s (%s %u of %u %s): %s (%u) %s (%u).",
				"Error occurred while constructing an SQL 'WHERE' clause on a",
				"portion of the primary key", "index component element", count_1,
				primary_key_count, "components", "the specified field index",
				primary_key_list[count_1],
				"is not less than the total number of fields in the cache",
				cache_ptr->field_count);
			return_code = DCR_FAILURE;
			break;
		}
		else if (!(*cache_ptr->field_list[primary_key_list[count_1]].
			db_column_name)) {
			sprintf(error_text, "%s %s (%s %u of %u %s, %s '%s'): %s",
				"Error occurred while constructing an SQL 'WHERE' clause on a",
				"portion of the primary key", "index component element", count_1,
				primary_key_count, "components", "field name", 
				cache_ptr->field_list[primary_key_list[count_1]].field_name,
				"this cache field is not a database column");
			return_code = DCR_FAILURE;
			break;
		}
		strcat(strcat(strcat(sql_command, (!count_1) ? " WHERE (" : ") AND ("),
			cache_ptr->field_list[primary_key_list[count_1]].db_column_name),
			" = ");
		if ((return_code = DBC_SYB_FMT_Data_SQL(cache_ptr->
			field_list[primary_key_list[count_1]].db_type,
			cache_ptr->field_list[primary_key_list[count_1]].data_length,
			record_ptr + cache_ptr->field_list[primary_key_list[count_1]].
			data_offset, sql_command + strlen(sql_command), tmp_error_text)) !=
			DCR_SUCCESS) {
			sprintf(error_text, "%s %s (%s %u of %u %s, %s '%s'): %s",
				"Error occurred while constructing an SQL 'WHERE' clause on a",
				"portion of the primary key", "index component element", count_1,
				primary_key_count, "components", "database column name", 
				cache_ptr->field_list[primary_key_list[count_1]].db_column_name,
				tmp_error_text);
			break;
		}
	}
	strcat(sql_command, ")");

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_AllocSQLString(cache_ptr, sql_command, error_text)
const DCR_CACHE  *cache_ptr;
char            **sql_command;
char             *error_text;
{
	int          return_code;
	unsigned int sql_length;

	*sql_command = NULL;

	if ((return_code = DCR_GetSQLLength(cache_ptr, &sql_length,
		error_text)) == DCR_SUCCESS) {
		if ((*sql_command = ((char *) calloc(sql_length, sizeof(char)))) ==
			NULL) {
			sprintf(error_text, "%s '%-.500s' (%u bytes required).",
				"Unable to allocate memory for an SQL command string for cache",
				cache_ptr->cache_file_name, sql_length);
			return_code = DCR_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_GetSQLLength(cache_ptr, sql_length, error_text)
const DCR_CACHE *cache_ptr;
unsigned int    *sql_length;
char            *error_text;
{
	int          return_code     = DCR_SUCCESS;
	unsigned int db_column_count = 0;
	unsigned int tmp_sql_length  = 4096;
	unsigned int count_1;

	*sql_length = 0;

	for (count_1 = 0; count_1 < cache_ptr->field_count; count_1++) {
		if (*cache_ptr->field_list[count_1].db_column_name) {
			db_column_count++;
			tmp_sql_length +=
				(sizeof(cache_ptr->field_list[count_1].db_column_name) * 2) +
				(cache_ptr->field_list[count_1].data_length * 2);
		}
	}

	if (db_column_count)
		*sql_length = tmp_sql_length;
	else {
		sprintf(error_text, "The cache file '%-.500s' has no database columns.",
			cache_ptr->cache_file_name);
		return_code = DCR_FAILURE;
	}

	return(return_code);
}
/*	***********************************************************************	*/

