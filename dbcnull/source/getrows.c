/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Internal Null Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the retrieval of rows from a Internal database
								for the Internal NULL facility.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
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

#include "dbcnulli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_NULL_GetRows

   SYNOPSIS    :	return_code = DBC_NULL_GetRows(dbc_control_ptr,
							member_count, member_list, sql_command, table_name,
							out_row_count, out_row_list, out_row_size, data_row_size,
							data_row_offset, max_row_count, alloc_granularity,
							error_text);

						int                 return_code;

						DBC_NULL  *dbc_control_ptr;

						unsigned int        member_count;

						const MDDL   *member_list;

						const char         *sql_command;

						const char         *table_name;

						unsigned int       *out_row_count;

						void              **out_row_list;

						size_t              out_row_size;

						size_t              data_row_size;

						size_t              data_row_offset;

						unsigned int        max_row_count;

						unsigned int        alloc_granularity;

						char               *error_text;

   DESCRIPTION :	Sends an SQL statement to a Internal database server and
						retrieves the resulting rows.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_NULL'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_NULL_Initialize`` and that a connection to a
						Internal database has been performed by ``DBC_NULL_Open``.

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is an array of ''MDDL'' structures
						which describe the columns to be bound by the function
						``DBC_NULL_BindMembers``.

						(.) ``sql_command`` is the SQL statement to be sent to the
						Internal database server using the function
						``DBC_NULL_DoSQLCommand``.

						(.) ``table_name`` is the name of the table (or view) for
						the retrieval. It is used only in the function
						``DBC_NULL_BindMembers`` in error messages, so it may be
						passed as ''NULL''.

						(.) ``out_row_count`` is a pointer to an ''unsigned int''
						into which this function will place the number of rows
						received from the Internal server and allocated in the memory
						area to which the ``out_row_list`` parameter points.

						(.) ``out_row_list`` is a pointer to a ''void *'' pointer
						for which this function will allocate memory for the
						rows received from the Internal server.

						(.) ``out_row_size`` is the total size of the row to be
						allocated for row storage.

						(.) ``data_row_size`` is the size of the portion of
						``out_row_size`` used to store the columns indicated by
						``member_list``. It can not be less than ``out_row_size``.

						(.) ``data_row_offset`` is the offset of the beginning of
						of ``data_row_size`` within ``out_row_size``.

						(-) Use of ``out_row_size``, ``data_row_size``, and
						``data_row_offset`` permits the application programmer to
						have rows received from Internal embedded within a larger
						structure. If you do not need to make use of this feature,
						do the following:

						(..) Pass ``out_row_size`` equal to ``data_row_size``.

						(..) Pass ``data_row_offset`` equal to ''0''.

						(.) ``max_row_count`` specifies the maximum number of rows
						desired.

						(-) If ``max_row_count`` is ''0'', this function will
						return all rows sent by the Internal server.

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
						amount of memory to hold the rows received from Internal
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

   SEE ALSO    :	DBC_CTLIB_GetRows

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_NULL_GetRows
						DBC Internal NULL Functions:DBC_NULL_GetRows
						DBC Functions:Row Retrieval Functions:DBC_NULL_GetRows

   PUBLISH XREF:	DBC_NULL_GetRows

   PUBLISH NAME:	DBC_NULL_GetRows

	ENTRY CLASS	:	DBC Functions:Row Retrieval Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_NULL_GetRows(DBC_NULL *dbc_control_ptr, unsigned int member_count,
	const MDDL *member_list, const char *sql_command, const char *table_name,
	unsigned int *out_row_count, void **out_row_list, size_t out_row_size,
	size_t data_row_size, size_t data_row_offset, unsigned int max_row_count,
	unsigned int alloc_granularity, char *error_text)
#else
int DBC_NULL_GetRows(dbc_control_ptr, member_count, member_list, sql_command,
	table_name, out_row_count, out_row_list, out_row_size, data_row_size,
	data_row_offset, max_row_count, alloc_granularity, error_text)
DBC_NULL      *dbc_control_ptr;
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
	strcat(strcpy(error_text, DBC_NULL_BASE_ERROR_TEXT),
		"'DBC_NULL_GetRows()' failed.");

	return(DBC_FAILURE);
}
/* *********************************************************************** */

/*
	ADF NOTE: ADF NEEDED HERE
*/
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_NULL_GetRowsBasic(DBC_NULL *dbc_control_ptr,
	const DBC_GETROWS *get_rows_ptr, unsigned int *out_row_count,
	void **out_row_list, char *error_text)
#else
int DBC_NULL_GetRowsBasic(dbc_control_ptr, get_rows_ptr, out_row_count,
	out_row_list, error_text)
DBC_NULL           *dbc_control_ptr;
const DBC_GETROWS  *get_rows_ptr;
unsigned int       *out_row_count;
void              **out_row_list;
char               *error_text;
#endif /* #ifndef NARGS */
{
	strcat(strcpy(error_text, DBC_NULL_BASE_ERROR_TEXT),
		"'DBC_NULL_GetRowsBasic()' failed.");

	return(DBC_FAILURE);
}
/* *********************************************************************** */

