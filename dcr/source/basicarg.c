/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses a variety of cache-related command-line
								parameters.

	Revision History	:	1994-12-21 --- Creation.
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

#include <limits.h>
#include <math.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_BARG_AddedFields(in_arg_ptr, in_arg_length, in_data_ptr,
	added_field_count, added_field_list, error_code, error_text)
const char     *in_arg_ptr;
unsigned int   *in_arg_length;
char          **in_data_ptr;
unsigned int   *added_field_count;
char         ***added_field_list;
int            *error_code;
char           *error_text;
{
	int            return_code;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if ((return_code = GEN_ArgParse(in_arg_ptr, arg_length, data_ptr,
		"-ADD_FIELD=", "-ADD_FIELDS=", "-ADDED_FIELD=", "-ADDED_FIELDS=",
		NULL)) == GENFUNCS_TRUE) {
		if (!(**data_ptr)) {
			GEN_BARG_BadComponentMsg(in_arg_ptr, *arg_length, *data_ptr,
				"a valid added field specification", error_text);
			*error_code = GENFUNCS_BAD_ARGS_FAILURE;
		}
		else if (strl_append(added_field_count, added_field_list, *data_ptr) !=
			STRFUNCS_SUCCESS) {
			sprintf(error_text,
				"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
				"Unable to allocate memory for the", ((int) *arg_length),
				((int) *arg_length), in_arg_ptr, *data_ptr,
				strlen(*data_ptr) + 1);
			*error_code = GENFUNCS_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_Alloc(in_arg_ptr, in_arg_length, in_data_ptr,
	allocation_size, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
unsigned int  *allocation_size;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	double         tmp_double;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-ALLOC=",
		"-ALLOCATION=", NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (!(**data_ptr))
			*allocation_size = 0;
		else {
			tmp_double = atof(*data_ptr);
			if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
				(tmp_double > ((double) UINT_MAX))) {
				sprintf(error_text,
					"%s '%-*.*s' ('%.500s') --- %s 0 to %u, inclusive.",
					"Invalid", ((int) *arg_length), ((int) *arg_length),
					in_arg_ptr, *data_ptr,
					"expected an integer value in the range of", UINT_MAX);
				*error_code = DCR_BAD_ARGS_FAILURE;
			}
			else
				*allocation_size = ((unsigned int) tmp_double);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_CacheFile(in_arg_ptr, in_arg_length, in_data_ptr,
	cache_file_name, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **cache_file_name;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-CACHE_FILE=",
		"-CACHE_FILE_NAME=", NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (*cache_file_name != NULL) {
			fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
				"The cache file name specification has changed", *cache_file_name,
				*data_ptr);
			free(*cache_file_name);
			*cache_file_name = NULL;
		}
		*error_code = GEN_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
			*data_ptr, cache_file_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_CacheName(in_arg_ptr, in_arg_length, in_data_ptr,
	cache_name, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **cache_name;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-CACHE_NAME=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (strlen(*data_ptr) >= STR_sizeof(DCR_HEADER, cache_name)) {
			sprintf(error_text,
				"%s '%-*.*s' parameter ('%-.500s' = %u bytes) %s (%u).",
				"The length of the cache name specified with the",
				((int) *arg_length), ((int) *arg_length), in_arg_ptr, *data_ptr,
				strlen(*data_ptr), "exceeds the maximum length of a cache name",
				STR_sizeof(DCR_HEADER, cache_name) - 1);
			*error_code = DCR_BAD_ARGS_FAILURE;
		}
		else {
			if (*cache_name != NULL) {
				fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
					"The cache name specification has changed", *cache_name,
					*data_ptr);
				free(*cache_name);
				*cache_name = NULL;
			}
			*error_code = GEN_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
				*data_ptr, cache_name, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_ClearAddedFields(in_arg_ptr, in_arg_length, in_data_ptr,
	added_field_count, added_field_list, error_code, error_text)
const char     *in_arg_ptr;
unsigned int   *in_arg_length;
char          **in_data_ptr;
unsigned int   *added_field_count;
char         ***added_field_list;
int            *error_code;
char           *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	int            tmp_flag;
	int            error_flag;
	char           genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, &tmp_flag,
		genfuncs_error_text, arg_length, data_ptr, "-CLEAR_ADD_FIELD=",
		"-CLEAR_ADD_FIELDS=", "-CLEAR_ADDED_FIELD=", "-CLEAR_ADDED_FIELDS=",
		"-DELETE_ADD_FIELD=", "-DELETE_ADD_FIELDS=", "-DELETE_ADDED_FIELD=",
		"-DELETE_ADDED_FIELDS=", "-REMOVE_ADD_FIELD=", "-REMOVE_ADD_FIELDS=",
		"-REMOVE_ADDED_FIELD=", "-REMOVE_ADDED_FIELDS=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (error_flag == GENFUNCS_TRUE) {
			nstrcpy(error_text, genfuncs_error_text, DCR_MAX_ERROR_TEXT - 1);
			*error_code = DCR_BAD_ARGS_FAILURE;
		}
		else
			strl_remove_all(added_field_count, added_field_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_ClearIndexSpec(in_arg_ptr, in_arg_length, in_data_ptr,
	index_spec_count, index_spec_list, error_code, error_text)
const char     *in_arg_ptr;
unsigned int   *in_arg_length;
char          **in_data_ptr;
unsigned int   *index_spec_count;
char         ***index_spec_list;
int            *error_code;
char           *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	int            tmp_flag;
	int            error_flag;
	char           genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, &tmp_flag,
		genfuncs_error_text, arg_length, data_ptr, "-CLEAR_INDEX_SPEC=",
		"-CLEAR_INDEX_SPECS=", "-CLEAR_INDEX_SPECIFICATION=",
		"-CLEAR_INDEX_SPECIFICATIONS=", "-DELETE_INDEX_SPEC=",
		"-DELETE_INDEX_SPECS=", "-DELETE_INDEX_SPECIFICATION=",
		"-DELETE_INDEX_SPECIFICATIONS=", "-REMOVE_INDEX_SPEC=",
		"-REMOVE_INDEX_SPECS=", "-REMOVE_INDEX_SPECIFICATION=",
		"-REMOVE_INDEX_SPECIFICATIONS=", NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (error_flag == GENFUNCS_TRUE) {
			nstrcpy(error_text, genfuncs_error_text, DCR_MAX_ERROR_TEXT - 1);
			*error_code = DCR_BAD_ARGS_FAILURE;
		}
		else
			strl_remove_all(index_spec_count, index_spec_list);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_DBDatabaseName(in_arg_ptr, in_arg_length, in_data_ptr,
	db_database_name, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **db_database_name;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-DB=", "-DB_NAME=",
		"-DATA_BASE=", "-DATA_BASE_NAME=", "-DATABASE=", "-DATABASE_NAME=",
		NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (*db_database_name != NULL) {
			fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
				"The database name specification has changed", *db_database_name,
				*data_ptr);
			free(*db_database_name);
			*db_database_name = NULL;
		}
		*error_code = GEN_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
			*data_ptr, db_database_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_DBLoadGran(in_arg_ptr, in_arg_length, in_data_ptr,
	db_load_granularity, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
unsigned int  *db_load_granularity;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	double         tmp_double;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-DB_LOAD_GRAN=",
		"-DB_LOAD_GRANULAR=", "-DB_LOAD_GRANULARITY=",
		"-DATA_BASE_LOAD_GRAN=", "-DATA_BASE_LOAD_GRANULAR=",
		"-DATA_BASE_LOAD_GRANULARITY=", "-DATABASE_LOAD_GRAN=",
		"-DATABASE_LOAD_GRANULAR=", "-DATABASE_LOAD_GRANULARITY=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (!(**data_ptr))
			*db_load_granularity = 0;
		else {
			tmp_double = atof(*data_ptr);
			if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
				(tmp_double > ((double) UINT_MAX))) {
				sprintf(error_text,
					"%s '%-*.*s' ('%.500s') --- %s 0 to %u, inclusive.",
					"Invalid", ((int) *arg_length), ((int) *arg_length),
					in_arg_ptr, *data_ptr,
					"expected an integer value in the range of", UINT_MAX);
				*error_code = DCR_BAD_ARGS_FAILURE;
			}
			else
				*db_load_granularity = ((unsigned int) tmp_double);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_DBOwnerName(in_arg_ptr, in_arg_length, in_data_ptr,
	db_owner_name, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **db_owner_name;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-DB_OWNER=",
		"-DB_OWNER_NAME=", "-DATA_BASE_OWNER=", "-DATA_BASE_OWNER_NAME=",
		"-DATABASE_OWNER=", "-DATABASE_OWNER_NAME=", NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (*db_owner_name != NULL) {
			fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
				"The database owner name specification has changed",
				*db_owner_name, *data_ptr);
			free(*db_owner_name);
			*db_owner_name = NULL;
		}
		*error_code = GEN_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
			*data_ptr, db_owner_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_DBPassword(in_arg_ptr, in_arg_length, in_data_ptr,
	db_pass_word, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **db_pass_word;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-DB_PASS=",
		"-DB_PASSWD=", "-DB_PASSWORD=", "-DB_PASS_NAME=", "-DB_PASSWD_NAME=",
		"-DB_PASSWORD_NAME=", "-DATA_BASE_PASS=", "-DATA_BASE_PASSWD=",
		"-DATA_BASE_PASSWORD=", "-DATA_BASE_PASS_NAME=",
		"-DATA_BASE_PASSWD_NAME=", "-DATA_BASE_PASSWORD_NAME=",
		"-DATABASE_PASS=", "-DATABASE_PASSWD=", "-DATABASE_PASSWORD=",
		"-DATABASE_PASS_NAME=", "-DATABASE_PASSWD_NAME=",
		"-DATABASE_PASSWORD_NAME=", NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (*db_pass_word != NULL) {
			fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
				"The database user password specification has changed",
				*db_pass_word, *data_ptr);
			free(*db_pass_word);
			*db_pass_word = NULL;
		}
		*error_code = GEN_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
			*data_ptr, db_pass_word, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_DBTableName(in_arg_ptr, in_arg_length, in_data_ptr,
	db_table_name, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **db_table_name;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-DB_TABLE=",
		"-DB_TABLE_NAME=", "-DATA_BASE_TABLE=", "-DATA_BASE_TABLE_NAME=",
		"-DATABASE_TABLE=", "-DATABASE_TABLE_NAME=", NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (*db_table_name != NULL) {
			fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
				"The database table name specification has changed",
				*db_table_name, *data_ptr);
			free(*db_table_name);
			*db_table_name = NULL;
		}
		*error_code = GEN_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
			*data_ptr, db_table_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_DBUserName(in_arg_ptr, in_arg_length, in_data_ptr,
	db_user_name, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **db_user_name;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-DB_USER=",
		"-DB_USER_NAME=", "-DATA_BASE_USER=", "-DATA_BASE_USER_NAME=",
		"-DATABASE_USER=", "-DATABASE_USER_NAME=", NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (*db_user_name != NULL) {
			fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
				"The database user name specification has changed",
				*db_user_name, *data_ptr);
			free(*db_user_name);
			*db_user_name = NULL;
		}
		*error_code = GEN_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
			*data_ptr, db_user_name, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_IndexSpec(in_arg_ptr, in_arg_length, in_data_ptr,
	index_spec_count, index_spec_list, error_code, error_text)
const char     *in_arg_ptr;
unsigned int   *in_arg_length;
char          **in_data_ptr;
unsigned int   *index_spec_count;
char         ***index_spec_list;
int            *error_code;
char           *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-INDEX_SPEC=",
		"-INDEX_SPECS=", "-INDEX_SPECIFICATION=", "-INDEX_SPECIFICATIONS=",
		NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (!(**data_ptr))
			fprintf(stderr, "%s '%-*.*s' parameter encountered --- ignored.\n",
				"Empty index specification", ((int) *arg_length),
				((int) *arg_length), in_arg_ptr);
		else if (strl_append(index_spec_count, index_spec_list, *data_ptr) !=
			STRFUNCS_SUCCESS) {
			sprintf(error_text, "%s '%-*.*s' ('%-.500s') --- %u bytes required.",
				"Unable to allocate memory for the", ((int) *arg_length),
				((int) *arg_length), in_arg_ptr, *data_ptr,
				strlen(*data_ptr) + 1);
			*error_code = DCR_MEMORY_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_IndexType(in_arg_ptr, in_arg_length, in_data_ptr,
	indirect_index_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *indirect_index_flag;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-INDEX_TYPE=",
		"-INDEX_TYPES=", NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if ((!stricmp("INDIRECT", *data_ptr))        ||
			(!stricmp("INDIRECT_INDEX", *data_ptr))   ||
			(!stricmp("INDIRECT_INDEXES", *data_ptr)) ||
			(!stricmp("INDIRECT_INDEXS", *data_ptr))  ||
			(!stricmp("INDIRECT_INDICES", *data_ptr)))
			*indirect_index_flag = DCR_TRUE;
			if ((!stricmp("EMBED", *data_ptr))           ||
				(!stricmp("EMBED_INDEX", *data_ptr))      ||
				(!stricmp("EMBED_INDEXES", *data_ptr))    ||
				(!stricmp("EMBED_INDEXS", *data_ptr))     ||
				(!stricmp("EMBED_INDICES", *data_ptr))    ||
				(!stricmp("EMBEDDED", *data_ptr))         ||
				(!stricmp("EMBEDDED_INDEX", *data_ptr))   ||
				(!stricmp("EMBEDDED_INDEXES", *data_ptr)) ||
				(!stricmp("EMBEDDED_INDEXS", *data_ptr))  ||
				(!stricmp("EMBEDDED_INDICES", *data_ptr)))
			*indirect_index_flag = DCR_FALSE;
		else {
			sprintf(error_text,
				"%s '%-*.*s' parameter ('%-.500s') --- expected '%s'.",
				"Invalid", ((int) *arg_length), ((int) *arg_length), in_arg_ptr,
				*data_ptr, "{INDIRECT|EMBED[DED]}[_IND{EX[[E]S]|ICES}]");
			*error_code = DCR_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_IndirectIndex(in_arg_ptr, in_arg_length, in_data_ptr,
	indirect_index_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *indirect_index_flag;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	int            error_flag;
	char           genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, indirect_index_flag,
		genfuncs_error_text, arg_length, data_ptr, "-INDIRECT_INDEX=",
		"-INDIRECT_INDICES=", "-INDIRECT_INDEXES=", "-INDIRECT_INDEXS=",
		NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (error_flag == GENFUNCS_TRUE) {
			nstrcpy(error_text, genfuncs_error_text, DCR_MAX_ERROR_TEXT - 1);
			*error_code = DCR_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_InitialAlloc(in_arg_ptr, in_arg_length, in_data_ptr,
	initial_allocation_size, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
unsigned int  *initial_allocation_size;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	double         tmp_double;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-INITIAL_ALLOC=",
		"-INITIAL_ALLOCATION=", NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (!(**data_ptr))
			*initial_allocation_size = 0;
		else {
			tmp_double = atof(*data_ptr);
			if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
				(tmp_double > ((double) UINT_MAX))) {
				sprintf(error_text,
					"%s '%-*.*s' ('%.500s') --- %s 0 to %u, inclusive.",
					"Invalid", ((int) *arg_length), ((int) *arg_length),
					in_arg_ptr, *data_ptr,
					"expected an integer value in the range of", UINT_MAX);
				*error_code = DCR_BAD_ARGS_FAILURE;
			}
			else
				*initial_allocation_size = ((unsigned int) tmp_double);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_LoadFromDB(in_arg_ptr, in_arg_length, in_data_ptr,
	load_data_flag, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *load_data_flag;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	int            error_flag;
	char           genfuncs_error_text[GENFUNCS_MAX_ERROR_TEXT];

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParseTruth(in_arg_ptr, &error_flag, load_data_flag,
		genfuncs_error_text, arg_length, data_ptr, "-LOAD_FROM_DB=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (error_flag == GENFUNCS_TRUE) {
			nstrcpy(error_text, genfuncs_error_text, DCR_MAX_ERROR_TEXT - 1);
			*error_code = DCR_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_MaxRows(in_arg_ptr, in_arg_length, in_data_ptr,
	maximum_row_count, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
unsigned int  *maximum_row_count;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	double         tmp_double;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-MAX_ROW=",
		"-MAX_ROW_COUNT=", "-MAX_ROWS=", "-MAX_ROWS_COUNT=",
		"-MAX_RECORD=", "-MAX_RECORD_COUNT=", "-MAX_RECORDS=",
		"-MAX_RECORDS_COUNT=", "-MAXIMUM_ROW=",
		"-MAXIMUM_ROW_COUNT=", "-MAXIMUM_ROWS=", "-MAXIMUM_ROWS_COUNT=",
		"-MAXIMUM_RECORD=", "-MAXIMUM_RECORD_COUNT=", "-MAXIMUM_RECORDS=",
		"-MAXIMUM_RECORDS_COUNT=", NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (!(**data_ptr))
			*maximum_row_count = 0;
		else {
			tmp_double = atof(*data_ptr);
			if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
				(tmp_double > ((double) UINT_MAX))) {
				sprintf(error_text,
					"%s '%-*.*s' ('%.500s') --- %s 0 to %u, inclusive.",
					"Invalid", ((int) *arg_length), ((int) *arg_length),
					in_arg_ptr, *data_ptr,
					"expected an integer value in the range of", UINT_MAX);
				*error_code = DCR_BAD_ARGS_FAILURE;
			}
			else
				*maximum_row_count = ((unsigned int) tmp_double);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_OperationMode(in_arg_ptr, in_arg_length, in_data_ptr,
	operating_mode, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
int           *operating_mode;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-OPERATION=",
		"-OPERATING=", "-OPERATION_MODE=", "-OPERATING_MODE=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if ((!stricmp("CREATE", *data_ptr)) ||
			(!stricmp("CREATE_CACHE", *data_ptr)))
			*operating_mode = DCR_OP_CREATE;
		else if ((!stricmp("RELOAD", *data_ptr))  ||
			(!stricmp("RE_LOAD", *data_ptr))       ||
			(!stricmp("REFRESH", *data_ptr))       ||
			(!stricmp("RE_FRESH", *data_ptr))      ||
			(!stricmp("RELOAD_CACHE", *data_ptr))  ||
			(!stricmp("RE_LOAD_CACHE", *data_ptr)) ||
			(!stricmp("REFRESH_CACHE", *data_ptr)) ||
			(!stricmp("RE_FRESH_CACHE", *data_ptr)))
			*operating_mode = DCR_OP_RELOAD;
		else if ((!stricmp("UPDATE", *data_ptr)) ||
			(!stricmp("UPDATE_CACHE", *data_ptr)))
			*operating_mode = DCR_OP_UPDATE;
		else {
			sprintf(error_text,
				"%s '%-*.*s' parameter ('%-.500s') --- expected '%s'.",
				"Invalid", ((int) *arg_length), ((int) *arg_length), in_arg_ptr,
				*data_ptr, "{CREATE|RE[_]{FRESH|LOAD}|UPDATE}[_CACHE]");
			*error_code = DCR_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_RefreshSeconds(in_arg_ptr, in_arg_length, in_data_ptr,
	refresh_seconds, error_code, error_text)
const char     *in_arg_ptr;
unsigned int   *in_arg_length;
char          **in_data_ptr;
unsigned long  *refresh_seconds;
int            *error_code;
char           *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	double         tmp_double;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr,
		"-UPDATE_REFRESH_SECOND=", "-UPDATE_REFRESH_SECONDS=",
		"-UPDATE_RE_FRESH_SECOND=", "-UPDATE_RE_FRESH_SECONDS=",
		"-UPDATE_RELOAD_SECOND=", "-UPDATE_RELOAD_SECONDS=",
		"-UPDATE_RE_LOAD_SECOND=", "-UPDATE_RE_LOAD_SECONDS=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (!(**data_ptr))
			*refresh_seconds = 0L;
		else {
			tmp_double = atof(*data_ptr);
			if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
				(tmp_double > ((double) LONG_MAX))) {
				sprintf(error_text,
					"%s '%-*.*s' ('%.500s') --- %s 0 to %lu, inclusive.",
					"Invalid", ((int) *arg_length), ((int) *arg_length),
					in_arg_ptr, *data_ptr,
					"expected an integer value in the range of", LONG_MAX);
				*error_code = DCR_BAD_ARGS_FAILURE;
			}
			else
				*refresh_seconds = ((unsigned long) tmp_double);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_SQLGroupBy(in_arg_ptr, in_arg_length, in_data_ptr,
	sql_group_by_clause, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **sql_group_by_clause;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-GROUP_BY=",
		"-GROUP_BY_CLAUSE=", "-SQL_GROUP_BY=", "-SQL_GROUP_BY_CLAUSE=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (*sql_group_by_clause != NULL) {
			fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
				"The SQL 'GROUP BY' clause has changed", *sql_group_by_clause,
				*data_ptr);
			free(*sql_group_by_clause);
			*sql_group_by_clause = NULL;
		}
		*error_code = GEN_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
			*data_ptr, sql_group_by_clause, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_SQLOrderBy(in_arg_ptr, in_arg_length, in_data_ptr,
	sql_order_by_clause, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **sql_order_by_clause;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-ORDER_BY=",
		"-ORDER_BY_CLAUSE=", "-SQL_ORDER_BY=", "-SQL_ORDER_BY_CLAUSE=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (*sql_order_by_clause != NULL) {
			fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
				"The SQL 'ORDER BY' clause has changed", *sql_order_by_clause,
				*data_ptr);
			free(*sql_order_by_clause);
			*sql_order_by_clause = NULL;
		}
		*error_code = GEN_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
			*data_ptr, sql_order_by_clause, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_SQLWhere(in_arg_ptr, in_arg_length, in_data_ptr,
	sql_where_clause, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **sql_where_clause;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-WHERE=",
		"-WHERE_CLAUSE=", "-SQL_WHERE=", "-SQL_WHERE_CLAUSE=", NULL) ==
		GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (*sql_where_clause != NULL) {
			fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
				"The SQL 'WHERE' clause has changed", *sql_where_clause,
				*data_ptr);
			free(*sql_where_clause);
			*sql_where_clause = NULL;
		}
		*error_code = GEN_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
			*data_ptr, sql_where_clause, error_text);
	}

	return(return_code);
}
/*	***********************************************************************	*/

int DCR_BARG_UpdateDateField(in_arg_ptr, in_arg_length, in_data_ptr,
	update_date_field_name, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
char         **update_date_field_name;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if (GEN_ArgParse(in_arg_ptr, arg_length, data_ptr, "-UPDATE_DATE_FIELD=",
		"-UPDATE_DATE_FIELD_NAME=", "-UPDATE_DATE_COLUMN=",
		"-UPDATE_DATE_COLUMN_NAME=", NULL) == GENFUNCS_TRUE) {
		return_code = DCR_TRUE;
		if (strlen(*data_ptr) >= STR_sizeof(DCR_FIELD, field_name)) {
			sprintf(error_text,
				"%s '%-*.*s' parameter ('%-.500s' = %u bytes) %s (%u).",
				"The length of the update-date column name specified with the",
				((int) *arg_length), ((int) *arg_length), in_arg_ptr, *data_ptr,
				strlen(*data_ptr), "exceeds the maximum length of a column name",
				STR_sizeof(DCR_FIELD, field_name) - 1);
			*error_code = DCR_BAD_ARGS_FAILURE;
		}
		else {
			if (*update_date_field_name != NULL) {
				fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
					"The update-date column name specification has changed",
					*update_date_field_name, *data_ptr);
				free(*update_date_field_name);
				*update_date_field_name = NULL;
			}
			*error_code = GEN_BARG_BasicParamAlloc(in_arg_ptr, *arg_length,
				*data_ptr, update_date_field_name, error_text);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

/*
	NOTE: we've broken-up the parsing of the parameter into separate function
			calls because some compilers may not be able to handle a very large
			number of parameters.
*/
int DCR_BARG_UpdateMaxRows(in_arg_ptr, in_arg_length, in_data_ptr,
	update_max_row_count, error_code, error_text)
const char    *in_arg_ptr;
unsigned int  *in_arg_length;
char         **in_data_ptr;
unsigned int  *update_max_row_count;
int           *error_code;
char          *error_text;
{
	int            return_code = DCR_FALSE;
	unsigned int   tmp_arg_length;
	char          *tmp_data_ptr;
	unsigned int  *arg_length;
	char         **data_ptr;
	double         tmp_double;

	*error_code = DCR_FALSE;
	arg_length  = (in_arg_length == NULL) ? &tmp_arg_length : in_arg_length;
	data_ptr    = (in_data_ptr   == NULL) ? &tmp_data_ptr   : in_data_ptr;

	if ((GEN_ArgParse(in_arg_ptr, arg_length, data_ptr,
		"-UPDATE_RE_FRESH_MAX_ROW=", "-UPDATE_RE_FRESH_MAX_ROW_COUNT=",
		"-UPDATE_RE_FRESH_MAX_ROWS=", "-UPDATE_RE_FRESH_MAX_ROWS_COUNT=",
		"-UPDATE_RE_FRESH_MAX_RECORD=", "-UPDATE_RE_FRESH_MAX_RECORD_COUNT=",
		"-UPDATE_RE_FRESH_MAX_RECORDS=", "-UPDATE_RE_FRESH_MAX_RECORDS_COUNT=",
		"-UPDATE_RE_FRESH_MAXIMUM_ROW=", "-UPDATE_RE_FRESH_MAXIMUM_ROW_COUNT=",
		"-UPDATE_RE_FRESH_MAXIMUM_ROWS=",
		"-UPDATE_RE_FRESH_MAXIMUM_ROWS_COUNT=",
		"-UPDATE_RE_FRESH_MAXIMUM_RECORD=",
		"-UPDATE_RE_FRESH_MAXIMUM_RECORD_COUNT=",
		"-UPDATE_RE_FRESH_MAXIMUM_RECORDS=",
		"-UPDATE_RE_FRESH_MAXIMUM_RECORDS_COUNT=", "-UPDATE_REFRESH_MAX_ROW=",
		NULL) == GENFUNCS_TRUE) ||
		(GEN_ArgParse(in_arg_ptr, arg_length, data_ptr,
		"-UPDATE_REFRESH_MAX_ROW_COUNT=", "-UPDATE_REFRESH_MAX_ROWS=",
		"-UPDATE_REFRESH_MAX_ROWS_COUNT=", "-UPDATE_REFRESH_MAX_RECORD=",
		"-UPDATE_REFRESH_MAX_RECORD_COUNT=", "-UPDATE_REFRESH_MAX_RECORDS=",
		"-UPDATE_REFRESH_MAX_RECORDS_COUNT=", "-UPDATE_REFRESH_MAXIMUM_ROW=",
		"-UPDATE_REFRESH_MAXIMUM_ROW_COUNT=", "-UPDATE_REFRESH_MAXIMUM_ROWS=",
		"-UPDATE_REFRESH_MAXIMUM_ROWS_COUNT=",
		"-UPDATE_REFRESH_MAXIMUM_RECORD=",
		"-UPDATE_REFRESH_MAXIMUM_RECORD_COUNT=",
		"-UPDATE_REFRESH_MAXIMUM_RECORDS=",
		"-UPDATE_REFRESH_MAXIMUM_RECORDS_COUNT=",
		NULL) == GENFUNCS_TRUE) ||
		(GEN_ArgParse(in_arg_ptr, arg_length, data_ptr,
		"-UPDATE_RE_LOAD_MAX_ROW=", "-UPDATE_RE_LOAD_MAX_ROW_COUNT=",
		"-UPDATE_RE_LOAD_MAX_ROWS=", "-UPDATE_RE_LOAD_MAX_ROWS_COUNT=",
		"-UPDATE_RE_LOAD_MAX_RECORD=", "-UPDATE_RE_LOAD_MAX_RECORD_COUNT=",
		"-UPDATE_RE_LOAD_MAX_RECORDS=", "-UPDATE_RE_LOAD_MAX_RECORDS_COUNT=",
		"-UPDATE_RE_LOAD_MAXIMUM_ROW=", "-UPDATE_RE_LOAD_MAXIMUM_ROW_COUNT=",
		"-UPDATE_RE_LOAD_MAXIMUM_ROWS=", "-UPDATE_RE_LOAD_MAXIMUM_ROWS_COUNT=",
		"-UPDATE_RE_LOAD_MAXIMUM_RECORD=",
		"-UPDATE_RE_LOAD_MAXIMUM_RECORD_COUNT=",
		"-UPDATE_RE_LOAD_MAXIMUM_RECORDS=",
		"-UPDATE_RE_LOAD_MAXIMUM_RECORDS_COUNT=",
		NULL) == GENFUNCS_TRUE) ||
		(GEN_ArgParse(in_arg_ptr, arg_length, data_ptr,
		"-UPDATE_RELOAD_MAX_ROW=", "-UPDATE_RELOAD_MAX_ROW_COUNT=",
		"-UPDATE_RELOAD_MAX_ROWS=", "-UPDATE_RELOAD_MAX_ROWS_COUNT=",
		"-UPDATE_RELOAD_MAX_RECORD=", "-UPDATE_RELOAD_MAX_RECORD_COUNT=",
		"-UPDATE_RELOAD_MAX_RECORDS=", "-UPDATE_RELOAD_MAX_RECORDS_COUNT=",
		"-UPDATE_RELOAD_MAXIMUM_ROW=", "-UPDATE_RELOAD_MAXIMUM_ROW_COUNT=",
		"-UPDATE_RELOAD_MAXIMUM_ROWS=", "-UPDATE_RELOAD_MAXIMUM_ROWS_COUNT=",
		"-UPDATE_RELOAD_MAXIMUM_RECORD=",
		"-UPDATE_RELOAD_MAXIMUM_RECORD_COUNT=",
		"-UPDATE_RELOAD_MAXIMUM_RECORDS=",
		"-UPDATE_RELOAD_MAXIMUM_RECORDS_COUNT=",
		NULL) == GENFUNCS_TRUE)) {
		return_code = DCR_TRUE;
		if (!(**data_ptr))
			*update_max_row_count = 0;
		else {
			tmp_double = atof(*data_ptr);
			if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
				(tmp_double > ((double) UINT_MAX))) {
				sprintf(error_text,
					"%s '%-*.*s' ('%.500s') --- %s 0 to %u, inclusive.",
					"Invalid", ((int) *arg_length), ((int) *arg_length),
					in_arg_ptr, *data_ptr,
					"expected an integer value in the range of", UINT_MAX);
				*error_code = DCR_BAD_ARGS_FAILURE;
			}
			else
				*update_max_row_count = ((unsigned int) tmp_double);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

