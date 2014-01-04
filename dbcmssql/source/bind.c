/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a Microsoft SQL Server bind using a
								description of the structure to which the bind is to
								be made.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_BindMembers

   SYNOPSIS    :	return_code = DBC_MSSQL_BindMembers(dbc_control_ptr,
							member_count, member_list, table_name, bind_buffer,
							error_text);

						int                return_code;

						DBC_MSSQL_CONTROL *dbc_control_ptr;

						unsigned int       member_count;

						const MDDL  *member_list;

						const char        *table_name;

						void              *bind_buffer;

						char              *error_text;

   DESCRIPTION :	Binds one or more columns to a memory buffer.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is a pointer to the
						''DBC_MSSQL_CONTROL'' structure to be used to manage
						communication with the database. It is assumed by this
						function that the structure has been properly initialized
						by ``DBC_MSSQL_Initialize`` and that a connection to a
						Microsoft SQL Server database has been performed by ``DBC_MSSQL_Connect``.

						(.) ``member_count`` is the number of elements in the array
						``member_list``.

						(.) ``member_list`` is an array of ''MDDL'' structures
						which describe the columns to be bound by this function.

						(.) ``table_name`` is the name of the table (or view) for
						the bind. It is used only in error messages, so it may be
						passed as ''NULL''.

						(.) ``bind_buffer`` points to the area of memory to which
						the bind is to be performed. 

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

   NOTES       :	This function is called by ``DBC_MSSQL_GetRows``. There is
						little need for application programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_CTLIB_BindMembers

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_BindMembers
						DBC DB-LIB Functions:DBC_MSSQL_BindMembers
						DBC Functions:Bind Functions:DBC_MSSQL_BindMembers

   PUBLISH XREF:	DBC_MSSQL_BindMembers

   PUBLISH NAME:	DBC_MSSQL_BindMembers

	ENTRY CLASS	:	DBC Functions:Bind Functions

EOH */
/*	***********************************************************************	*/
int DBC_MSSQL_BindMembers(dbc_control_ptr, member_count, member_list,
	table_name, bind_buffer, error_text)
DBC_MSSQL_CONTROL *dbc_control_ptr;
unsigned int       member_count;
const MDDL  *member_list;
const char        *table_name;
void              *bind_buffer;
char              *error_text;
{
	int          return_code = DBC_SUCCESS;
	unsigned int count_1;
	char         error_buffer[DBC_MAX_ERROR_TEXT];

	if ((return_code = DBC_MSSQL_MSG_DefaultHandler(dbc_control_ptr,
		error_text)) != DBC_SUCCESS)
		goto EXIT_FUNCTION;

	for (count_1 = 0; count_1 < member_count; count_1++) {
		switch (member_list[count_1].dbc_type) {
			case SQLBINARY :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1, 
					BINARYBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLBIT :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					BITBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLCHAR :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					NTBSTRINGBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLTEXT :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					CHARBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLIMAGE :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					BINARYBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLINT1 :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					TINYBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLINT2 :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					SMALLBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLINT4 :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					INTBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLFLT4 :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					FLT4BIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLFLT8 :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					FLT8BIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLMONEY :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					MONEYBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLMONEY4 :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					SMALLMONEYBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLDATETIME :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					DATETIMEBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			case SQLDATETIM4 :
				if (dbbind(dbc_control_ptr->database_ptr, ((int) count_1) + 1,
					SMALLDATETIBIND, ((int) member_list[count_1].length),
					((unsigned char *) bind_buffer) +
					member_list[count_1].offset) != SUCCEED)
					return_code = DBC_DB_FAILURE;
				break;
			default :
				sprintf(error_text, "%s '%s' %s %u (%s '%s') --- %s (%d).",
					"Unable to perform a 'dbbind()' for table",
					((table_name != NULL) && (*table_name)) ? table_name : "?",
					"structure member index number", count_1,
					"database column name", member_list[count_1].name,
					"this member has an unsupported Microsoft SQL Server data-type",
					member_list[count_1].dbc_type);
				return_code = DBC_FAILURE;
				break;
		}
		if (return_code != DBC_SUCCESS)
			break;
	}

	if (return_code == DBC_DB_FAILURE)
		sprintf(error_text, "%s '%s' in table '%s': %s.",
			"Error occurred while attempting to bind column",
			member_list[count_1].name,
			((table_name != NULL) && (*table_name)) ? table_name : "?",
			DBC_MSSQL_MSG_GetHandlerMessage(error_buffer));

	DBC_MSSQL_MSG_PopHandler();

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

