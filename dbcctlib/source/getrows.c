/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase CT-Library Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the retrieval of rows from a Sybase database
								for the Sybase CT-LIB facility.

	Revision History	:	1996-06-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>
#include <string.h>

#include "dbcctlii.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_GetRows

   SYNOPSIS    :	return_code = DBC_CTLIB_GetRows(dbc_control_ptr,
							member_count, member_list, sql_command, table_name,
							out_row_count, out_row_list, out_row_size, data_row_size,
							data_row_offset, max_row_count, alloc_granularity,
							error_text);

						int            return_code;

						DBC_CTLIB     *dbc_control_ptr;

						unsigned int   member_count;

						const MDDL    *member_list;

						const char    *sql_command;

						const char    *table_name;

						unsigned int  *out_row_count;

						void         **out_row_list;

						size_t         out_row_size;

						size_t         data_row_size;

						size_t         data_row_offset;

						unsigned int   max_row_count;

						unsigned int   alloc_granularity;

						char          *error_text;

   DESCRIPTION :	Sends an SQL statement to a Sybase database server and
						retrieves the resulting rows.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_CTLIB'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_CTLIB_Initialize`` and that a connection to a
						Sybase database has been performed by ``DBC_CTLIB_Open``.

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is an array of ''MDDL'' structures
						which describe the columns to be bound by the function
						``DBC_CTLIB_BindMembers``.

						(.) ``sql_command`` is the SQL statement to be sent to the
						Sybase database server using the function
						``DBC_CTLIB_DoSQLCommand``.

						(.) ``table_name`` is the name of the table (or view) for
						the retrieval. It is used only in the function
						``DBC_CTLIB_BindMembers`` in error messages, so it may be
						passed as ''NULL''.

						(.) ``out_row_count`` is a pointer to an ''unsigned int''
						into which this function will place the number of rows
						received from the Sybase server and allocated in the memory
						area to which the ``out_row_list`` parameter points.

						(.) ``out_row_list`` is a pointer to a ''void *'' pointer
						for which this function will allocate memory for the
						rows received from the Sybase server.

						(.) ``out_row_size`` is the total size of the row to be
						allocated for row storage.

						(.) ``data_row_size`` is the size of the portion of
						``out_row_size`` used to store the columns indicated by
						``member_list``. It can not be less than ``out_row_size``.

						(.) ``data_row_offset`` is the offset of the beginning of
						of ``data_row_size`` within ``out_row_size``.

						(-) Use of ``out_row_size``, ``data_row_size``, and
						``data_row_offset`` permits the application programmer to
						have rows received from Sybase embedded within a larger
						structure. If you do not need to make use of this feature,
						do the following:

						(..) Pass ``out_row_size`` equal to ``data_row_size``.

						(..) Pass ``data_row_offset`` equal to ''0''.

						(.) ``max_row_count`` specifies the maximum number of rows
						desired.

						(-) If ``max_row_count`` is ''0'', this function will
						return all rows sent by the Sybase server.

						(-) If ``max_row_count`` is greater than ''0'', than this
						function will return no more rows than the number specified.

						(.) ``alloc_granularity`` specifies the granularity with
						which memory is to be allocated for the storage of rows in
						``out_row_list``. That is, allocation of row memory will be
						made in chunks of:

						<->``out_row_size`` * ``alloc_granularity``

						(-) If ``alloc_granularity`` is passed to this function as
						''0'', it will be set to ''1''.

						(-) Regardless of the value of ``alloc_granularity``, this
						function will re-allocate ``out_row_list`` for the exact
						amount of memory to hold the rows received from Sybase
						before returning.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''DBC_MAX_ERROR_TEXT'' characters in length.

   RETURNS     :	This function returns a DBC return codes manifest constant:

						(.) ''DBC_SUCCESS'' if the function completes without
						error.

						(.) One of the defined non-zero DBC return codes indicative
						of error.

   NOTES       :	

   CAVEATS     :	

   SEE ALSO    :	DBC_DBLIB_GetRows

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_GetRows
						DBC Sybase CT-LIB Functions:DBC_CTLIB_GetRows
						DBC Functions:Row Retrieval Functions:DBC_CTLIB_GetRows

   PUBLISH XREF:	DBC_CTLIB_GetRows

   PUBLISH NAME:	DBC_CTLIB_GetRows

	ENTRY CLASS	:	DBC Functions:Row Retrieval Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_CTLIB_GetRows(DBC_CTLIB *dbc_control_ptr, unsigned int member_count,
	const MDDL *member_list, const char *sql_command, const char *table_name,
	unsigned int *out_row_count, void **out_row_list, size_t out_row_size,
	size_t data_row_size, size_t data_row_offset, unsigned int max_row_count,
	unsigned int alloc_granularity, char *error_text)
#else
int DBC_CTLIB_GetRows(dbc_control_ptr, member_count, member_list, sql_command,
	table_name, out_row_count, out_row_list, out_row_size, data_row_size,
	data_row_offset, max_row_count, alloc_granularity, error_text)
DBC_CTLIB     *dbc_control_ptr;
unsigned int   member_count;
const MDDL    *member_list;
const char    *sql_command;
const char    *table_name;
unsigned int  *out_row_count;
void         **out_row_list;
size_t         out_row_size;
size_t         data_row_size;
size_t         data_row_offset;
unsigned int   max_row_count;
unsigned int   alloc_granularity;
char          *error_text;
#endif /* #ifndef NARGS */
{
	DBC_GETROWS get_rows;

	DBC_INIT_DBCGetRows(&get_rows);

	*out_row_count             = 0;
	*out_row_list              = NULL;

	get_rows.member_count      = member_count;
	get_rows.member_list       = member_list;
	get_rows.sql_command       = ((char *) sql_command);
	get_rows.table_name        = ((char *) table_name);
	get_rows.out_row_size      = out_row_size;
	get_rows.data_row_size     = data_row_size;
	get_rows.data_row_offset   = data_row_offset;
	get_rows.max_row_count     = max_row_count;
	get_rows.alloc_granularity = alloc_granularity;
	get_rows.alloc_control_ptr = NULL;
	get_rows.user_data_ptr     = NULL;
	get_rows.per_row           = NULL;
	get_rows.alloc             =
		((int (*)(void *, void **, unsigned int)) DBC_MEMORY_ALLOC_Rows);
	get_rows.realloc           =
		((int (*)(void *, void **, unsigned int, unsigned int))
		DBC_MEMORY_REALLOC_Rows);
	get_rows.free              =
		((void (*)(void *, void **, unsigned int)) DBC_MEMORY_FREE_Rows);
	get_rows.per_row_free      = NULL;

	return(DBC_CTLIB_GetRowsBasic(dbc_control_ptr, &get_rows, out_row_count,
		out_row_list, error_text));
}
/* *********************************************************************** */

/*
	ADF NOTE: ADF NEEDED HERE
*/
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_CTLIB_GetRowsBasic(DBC_CTLIB *dbc_control_ptr,
	const DBC_GETROWS *get_rows_ptr, unsigned int *out_row_count,
	void **out_row_list, char *error_text)
#else
int DBC_CTLIB_GetRowsBasic(dbc_control_ptr, get_rows_ptr, out_row_count,
	out_row_list, error_text)
DBC_CTLIB          *dbc_control_ptr;
const DBC_GETROWS  *get_rows_ptr;
unsigned int       *out_row_count;
void              **out_row_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code    = DBC_DB_FAILURE;
	void         *bind_buffer    = NULL;
	size_t        old_alloc_size = 0;
	unsigned int  count_1;
	DBC_GETROWS   tmp_get_rows;
	size_t        new_alloc_size;
	CS_INT        results_type;
	CS_RETCODE    ct_code;
	char          error_buffer[DBC_MAX_ERROR_TEXT];

	*out_row_count                 = 0;
	*out_row_list                  = NULL;
	tmp_get_rows                   = *get_rows_ptr;
	tmp_get_rows.table_name        = (tmp_get_rows.table_name == NULL) ? "" :
		tmp_get_rows.table_name;
	tmp_get_rows.alloc_granularity = (!tmp_get_rows.alloc_granularity) ? 1 :
		tmp_get_rows.alloc_granularity;

	if (!tmp_get_rows.member_count) {
		strcpy(error_text, "Number of members for row retrieval is '0'.");
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (tmp_get_rows.member_list == NULL) {
		strcpy(error_text, "Member list pointer for row retrieval is 'NULL'.");
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (!tmp_get_rows.out_row_size) {
		strcpy(error_text, "Total row size is zero (0).");
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (!tmp_get_rows.data_row_size) {
		strcpy(error_text, "Data row size is zero (0).");
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (tmp_get_rows.out_row_size < tmp_get_rows.data_row_size) {
		sprintf(error_text,
			"The total row size (%u) is less than the data row size (%u).",
			tmp_get_rows.out_row_size, tmp_get_rows.data_row_size);
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (tmp_get_rows.data_row_offset >= tmp_get_rows.out_row_size) {
		sprintf(error_text,
			"The data row offset (%u) is not less than the total row size (%u).",
			tmp_get_rows.data_row_offset, tmp_get_rows.out_row_size);
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((tmp_get_rows.data_row_offset + tmp_get_rows.data_row_size) >
		tmp_get_rows.out_row_size) {
		sprintf(error_text, "%s (%u) %s (%u) %s (%u) --- %u.",
			"The total row size", tmp_get_rows.out_row_size,
			"is less than the sum of the data row offset",
			tmp_get_rows.data_row_offset, "and the data row size",
			tmp_get_rows.data_row_size, tmp_get_rows.data_row_offset +
			tmp_get_rows.data_row_size);
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (tmp_get_rows.alloc == NULL) {
		strcpy(error_text, "The pointer to the allocation function is 'NULL'.");
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (tmp_get_rows.realloc == NULL) {
		strcpy(error_text,
			"The pointer to the re-allocation function is 'NULL'.");
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (tmp_get_rows.free == NULL) {
		strcpy(error_text, "The pointer to the free function is 'NULL'.");
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((tmp_get_rows.sql_command == NULL) ||
		(!(*tmp_get_rows.sql_command))) {
		strcpy(error_text, "The SQL command string is empty.");
		return_code = DBC_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((bind_buffer = calloc(tmp_get_rows.out_row_size, sizeof(char))) ==
		NULL) {
		sprintf(error_text, "%s (%u bytes required).",
			"Unable to allocate temporary database row binding area",
			tmp_get_rows.out_row_size * sizeof(char));
		return_code = DBC_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code = DBC_CTLIB_DoSQLCommand(dbc_control_ptr,
		tmp_get_rows.sql_command, error_text)) != DBC_SUCCESS)
		goto EXIT_FUNCTION;

	DBC_CTLIB_MSG_ClearMsg(dbc_control_ptr);

	if (ct_results(dbc_control_ptr->command_ptr, &results_type) !=
		CS_SUCCEED) {
		strcat(strcpy(error_text, "Call to 'ct_results()' failed --- "),
			DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_buffer));
		ct_cancel(dbc_control_ptr->connection_ptr, NULL, CS_CANCEL_ALL);
		ct_cancel(NULL, dbc_control_ptr->command_ptr, CS_CANCEL_CURRENT);
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (results_type == CS_CMD_FAIL) {
		strcat(strcpy(error_text,
			"Call to 'ct_results()' resulted in 'CS_CMD_FAIL' --- "),
			DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_buffer));
		ct_cancel(dbc_control_ptr->connection_ptr, NULL, CS_CANCEL_ALL);
		ct_cancel(NULL, dbc_control_ptr->command_ptr, CS_CANCEL_CURRENT);
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if (results_type != CS_ROW_RESULT) {
		return_code = DBC_SUCCESS;
		goto EXIT_FUNCTION;
	}

	if ((return_code = DBC_CTLIB_BindMembers(dbc_control_ptr,
		tmp_get_rows.member_count, tmp_get_rows.member_list,
		tmp_get_rows.table_name, bind_buffer, error_text)) != DBC_SUCCESS) {
		ct_cancel(dbc_control_ptr->connection_ptr, NULL, CS_CANCEL_ALL);
		ct_cancel(NULL, dbc_control_ptr->command_ptr, CS_CANCEL_CURRENT);
		goto EXIT_FUNCTION;
	}

	*error_buffer  = '\0';

	while ((ct_code = ct_fetch(dbc_control_ptr->command_ptr, CS_UNUSED,
		CS_UNUSED, CS_UNUSED, NULL)) == CS_SUCCEED) {
		if (!(*out_row_count % tmp_get_rows.alloc_granularity)) {
			new_alloc_size =
				((*out_row_count / tmp_get_rows.alloc_granularity) + 1) *
				tmp_get_rows.alloc_granularity * tmp_get_rows.out_row_size;
			if (!(*out_row_count))
				return_code = (*tmp_get_rows.alloc)
					(tmp_get_rows.alloc_control_ptr, out_row_list, new_alloc_size);
			else
				return_code = (*tmp_get_rows.realloc)
					(tmp_get_rows.alloc_control_ptr, out_row_list, old_alloc_size,
					new_alloc_size);
			if (return_code != DBC_SUCCESS) {
				STR_AllocMsgList(new_alloc_size / tmp_get_rows.out_row_size,
					tmp_get_rows.out_row_size, error_text,
					 "Unable to %sallocate memory for a list of database rows",
					(*out_row_list == NULL) ? "" : "re-");
				ct_cancel(dbc_control_ptr->connection_ptr, NULL,
					CS_CANCEL_ALL);
				ct_cancel(NULL, dbc_control_ptr->command_ptr,
					CS_CANCEL_CURRENT);
				return_code = DBC_MEMORY_FAILURE;
				goto EXIT_FUNCTION;
			}
			old_alloc_size = new_alloc_size;
		}
		memcpy(((char *) *out_row_list) + ((*out_row_count)++ *
			tmp_get_rows.out_row_size), bind_buffer, tmp_get_rows.out_row_size);
		if ((tmp_get_rows.per_row != NULL) && ((return_code =
			(*tmp_get_rows.per_row)(dbc_control_ptr, &tmp_get_rows,
			*out_row_count, *out_row_list, error_text)) != DBC_SUCCESS)) {
			ct_cancel(dbc_control_ptr->connection_ptr, NULL, CS_CANCEL_ALL);
			ct_cancel(NULL, dbc_control_ptr->command_ptr, CS_CANCEL_CURRENT);
			goto EXIT_FUNCTION;
		}
		if (tmp_get_rows.max_row_count &&
			(*out_row_count == tmp_get_rows.max_row_count)) {
			ct_cancel(dbc_control_ptr->connection_ptr, NULL, CS_CANCEL_ALL);
			ct_cancel(NULL, dbc_control_ptr->command_ptr, CS_CANCEL_CURRENT);
			break;
		}
	}
	ct_cancel(dbc_control_ptr->connection_ptr, NULL, CS_CANCEL_ALL);

	if (ct_code != CS_END_DATA) {
		sprintf(error_text,
			"Call to 'ct_results()' resulted in code '%ld': %s", ct_code,
		DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_buffer));
		return_code = DBC_DB_FAILURE;
		goto EXIT_FUNCTION;
	}

	if ((return_code == DBC_SUCCESS) &&
		(*out_row_count % tmp_get_rows.alloc_granularity)) {
		if ((return_code = (*tmp_get_rows.realloc)
			(tmp_get_rows.alloc_control_ptr, out_row_list, old_alloc_size,
			*out_row_count * tmp_get_rows.out_row_size)) != DBC_SUCCESS) {
			sprintf(error_text,
				"%s %s %u to %u (%s %u * %s %u = %u total bytes).",
				"Unable to re-allocate memory for a list of rows from",
				"the allocated size with granularity of",
				old_alloc_size, *out_row_count * tmp_get_rows.out_row_size,
				"row count", *out_row_count, "row size", tmp_get_rows.out_row_size,
				*out_row_count * tmp_get_rows.out_row_size);
			return_code = DBC_MEMORY_FAILURE;
		}
	}

EXIT_FUNCTION:

	if (return_code != DBC_SUCCESS) {
		if (*out_row_count) {
			if (tmp_get_rows.per_row_free != NULL) {
				for (count_1 = 0; count_1 < *out_row_count; count_1++)
					(*tmp_get_rows.per_row_free)(dbc_control_ptr, &tmp_get_rows,
						count_1, ((char *) *out_row_list) +
						(count_1 * tmp_get_rows.out_row_size));
			}
			(*tmp_get_rows.free)(tmp_get_rows.alloc_control_ptr, out_row_list,
				old_alloc_size);
		}
		*out_row_count = 0;
		*out_row_list  = NULL;
	}

	if (bind_buffer != NULL)
		free(bind_buffer);

	return(return_code);
}
/* *********************************************************************** */

