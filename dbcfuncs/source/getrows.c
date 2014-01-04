/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generalized Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the retrieval of rows from a facility
								database.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dbcfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_GetRows

   SYNOPSIS    :	return_code = DBC_GetRows(dbc_context_ptr,
							member_count, member_list, sql_command, table_name,
							out_row_count, out_row_list, out_row_size, data_row_size,
							data_row_offset, max_row_count, alloc_granularity,
							error_text);

						int            return_code;

						DBC_CONTEXT   *dbc_context_ptr;

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

   DESCRIPTION :	Sends an SQL statement to a facility database server and
						retrieves the resulting rows.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_context_ptr`` is a pointer to the
						''DBC_CONTEXT'' structure to be used to manage
						communication with the database server.

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is an array of ''MDDL'' structures
						which describe the columns of the rows to be retrieved.

						(.) ``sql_command`` is the SQL statement to be sent to the
						facility database server.

						(.) ``table_name`` is the name of the table (or view) for
						the retrieval. It is used only in the function in error
						messages, so it may be passed as ''NULL''.

						(.) ``out_row_count`` is a pointer to an ''unsigned int''
						into which this function will place the number of rows
						received from the facility database server and allocated
						in the memory area to which the ``out_row_list`` parameter
						points.

						(.) ``out_row_list`` is a pointer to a ''void *'' pointer
						for which this function will allocate memory for the
						rows received from the facility database server.

						(.) ``out_row_size`` is the total size of the row to be
						allocated for row storage.

						(.) ``data_row_size`` is the size of the portion of
						``out_row_size`` used to store the columns indicated by
						``member_list``. It can not be less than ``out_row_size``.

						(.) ``data_row_offset`` is the offset of the beginning of
						of ``data_row_size`` within ``out_row_size``.

						(-) Use of ``out_row_size``, ``data_row_size``, and
						``data_row_offset`` permits the application programmer to
						have rows received from the facility database server
						embedded within a larger structure.

						(-) If you do not need to make use of this feature,
						do the following:

						(..) Pass ``out_row_size`` equal to ``data_row_size``.

						(..) Pass ``data_row_offset`` equal to ''0''.

						(.) ``max_row_count`` specifies the maximum number of rows
						desired.

						(-) If ``max_row_count`` is ''0'', this function will
						return all rows sent by the facility database server.

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
						amount of memory to hold the rows received from facility
						database server before returning.

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

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_GetRows
						Database Functions:Facility Functions:DBC_GetRows
						DBC Functions:Row Retrieval Functions:DBC_GetRows

   PUBLISH XREF:	DBC_GetRows

   PUBLISH NAME:	DBC_GetRows

	ENTRY CLASS	:	Database Functions:Facility Functions
						DBC Functions:Row Retrieval Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_GetRows(DBC_CONTEXT *dbc_context_ptr, unsigned int member_count,
	const MDDL *member_list, const char *sql_command, const char *table_name,
	unsigned int *out_row_count, void **out_row_list, size_t out_row_size,
	size_t data_row_size, size_t data_row_offset, unsigned int max_row_count,
	unsigned int alloc_granularity, char *error_text)
#else
int DBC_GetRows(dbc_context_ptr, member_count, member_list, sql_command,
	table_name, out_row_count, out_row_list, out_row_size, data_row_size,
	data_row_offset, max_row_count, alloc_granularity, error_text)
DBC_CONTEXT   *dbc_context_ptr;
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
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.get_rows), error_text)) ==
		DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.get_rows)
			(dbc_context_ptr->dbc_control_ptr, member_count, member_list,
			sql_command, table_name, out_row_count, out_row_list, out_row_size,
			data_row_size, data_row_offset, max_row_count, alloc_granularity,
			error_text);

	return(return_code);
}
/* *********************************************************************** */

/*
	ADF NOTE: ADF NEEDED HERE
*/
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_GetRowsBasic(DBC_CONTEXT *dbc_context_ptr,
	const DBC_GETROWS *get_rows_ptr, unsigned int *out_row_count,
	void **out_row_list, char *error_text)
#else
int DBC_GetRowsBasic(dbc_context_ptr, get_rows_ptr, out_row_count,
	out_row_list, error_text)
DBC_CONTEXT        *dbc_context_ptr;
const DBC_GETROWS  *get_rows_ptr;
unsigned int       *out_row_count;
void              **out_row_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = DBC_CheckFunction(dbc_context_ptr,
		((const void **) &dbc_context_ptr->dbc_funcs.get_rows_basic),
		error_text)) == DBC_SUCCESS)
		return_code = (*dbc_context_ptr->dbc_funcs.get_rows_basic)
			(dbc_context_ptr->dbc_control_ptr, get_rows_ptr, out_row_count,
			out_row_list, error_text);

	return(return_code);
}
/* *********************************************************************** */

