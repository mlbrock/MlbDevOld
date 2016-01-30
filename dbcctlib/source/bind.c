/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase CT-Library Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a Sybase bind using a description of the
								structure to which the bind is to be made for the
								Sybase CT-LIB facility.

	Revision History	:	1996-06-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dbcctlii.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB_BindMembers

   SYNOPSIS    :	return_code = DBC_CTLIB_BindMembers(dbc_control_ptr,
							member_count, member_list, table_name, bind_buffer,
							error_text);

						int           return_code;

						DBC_CTLIB    *dbc_control_ptr;

						unsigned int  member_count;

						const MDDL   *member_list;

						const char   *table_name;

						void         *bind_buffer;

						char         *error_text;

   DESCRIPTION :	Binds one or more columns to a memory buffer.

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

   NOTES       :	This function is called by ``DBC_CTLIB_GetRows``. There is
						little need for application programmers to call it directly.

   CAVEATS     :	

   SEE ALSO    :	DBC_DBLIB_BindMembers

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_BindMembers
						DBC Sybase CT-LIB Functions:DBC_CTLIB_BindMembers
						DBC Functions:Bind Functions:DBC_CTLIB_BindMembers

   PUBLISH XREF:	DBC_CTLIB_BindMembers

   PUBLISH NAME:	DBC_CTLIB_BindMembers

	ENTRY CLASS	:	DBC Functions:Bind Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_CTLIB_BindMembers(DBC_CTLIB *dbc_control_ptr,
	unsigned int member_count, const MDDL *member_list, const char *table_name,
	void *bind_buffer, char *error_text)
#else
int DBC_CTLIB_BindMembers(dbc_control_ptr, member_count, member_list,
	table_name, bind_buffer, error_text)
DBC_CTLIB    *dbc_control_ptr;
unsigned int  member_count;
const MDDL   *member_list;
const char   *table_name;
void         *bind_buffer;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int           return_code = DBC_SUCCESS;
	unsigned int  count_1;
	CS_DATAFMT    tmp_datafmt;
	char          error_buffer[DBC_MAX_ERROR_TEXT];

	tmp_datafmt.scale     = CS_SRC_VALUE;
	tmp_datafmt.precision = CS_SRC_VALUE;
	tmp_datafmt.count     = 1;
	tmp_datafmt.locale    = NULL;

	DBC_CTLIB_MSG_ClearMsg(dbc_control_ptr);

	for (count_1 = 0; count_1 < member_count; count_1++) {
		tmp_datafmt.maxlength = member_list[count_1].length;
		switch (member_list[count_1].dbc_type) {
			case SYBBINARY :
				tmp_datafmt.datatype = CS_BINARY_TYPE;
				tmp_datafmt.format   = CS_FMT_PADNULL;
				break;
			case SYBBIT :
				tmp_datafmt.datatype = CS_BIT_TYPE;
				tmp_datafmt.format   = CS_FMT_UNUSED;
				break;
			case SYBCHAR :
				tmp_datafmt.datatype = CS_CHAR_TYPE;
				tmp_datafmt.format   = CS_FMT_NULLTERM;
				break;
			case SYBTEXT :
				tmp_datafmt.datatype = CS_TEXT_TYPE;
				tmp_datafmt.format   = CS_FMT_NULLTERM;
				break;
			case SYBIMAGE :
				tmp_datafmt.datatype = CS_IMAGE_TYPE;
				tmp_datafmt.format   = CS_FMT_PADNULL;
				break;
			case SYBINT1 :
				tmp_datafmt.datatype = CS_TINYINT_TYPE;
				tmp_datafmt.format   = CS_FMT_UNUSED;
				break;
			case SYBINT2 :
				tmp_datafmt.datatype = CS_SMALLINT_TYPE;
				tmp_datafmt.format   = CS_FMT_UNUSED;
				break;
			case SYBINT4 :
				tmp_datafmt.datatype = CS_INT_TYPE;
				tmp_datafmt.format   = CS_FMT_UNUSED;
				break;
			case SYBREAL :
				tmp_datafmt.datatype = CS_REAL_TYPE;
				tmp_datafmt.format   = CS_FMT_UNUSED;
				break;
			case SYBFLT8 :
				tmp_datafmt.datatype = CS_FLOAT_TYPE;
				tmp_datafmt.format   = CS_FMT_UNUSED;
				break;
			case SYBMONEY :
				tmp_datafmt.datatype = CS_MONEY_TYPE;
				tmp_datafmt.format   = CS_FMT_UNUSED;
				break;
			case SYBMONEY4 :
				tmp_datafmt.datatype = CS_MONEY4_TYPE;
				tmp_datafmt.format   = CS_FMT_UNUSED;
				break;
			case SYBDATETIME :
				tmp_datafmt.datatype = CS_DATETIME_TYPE;
				tmp_datafmt.format   = CS_FMT_UNUSED;
				break;
			case SYBDATETIME4 :
				tmp_datafmt.datatype = CS_DATETIME4_TYPE;
				tmp_datafmt.format   = CS_FMT_UNUSED;
				break;
			default :
				sprintf(error_text, "%s '%s' %s %u (%s '%s') --- %s (%d).",
					"Unable to perform a 'ct_bind()' for table",
					((table_name != NULL) && (*table_name)) ? table_name : "?",
					"structure member index number", count_1,
					"database column name", member_list[count_1].name,
					"this member has an unsupported Sybase data-type",
					member_list[count_1].dbc_type);
				return_code = DBC_FAILURE;
				break;
		}
		if (return_code != DBC_SUCCESS)
			break;
		else if (ct_bind(dbc_control_ptr->command_ptr, ((CS_INT) (count_1 + 1)),
			&tmp_datafmt, ((unsigned char *) bind_buffer) +
			member_list[count_1].offset, NULL, NULL) != CS_SUCCEED) {
			sprintf(error_text, "%s '%s' in table '%s': %s.",
				"Error occurred while attempting to bind column",
				member_list[count_1].name,
				((table_name != NULL) && (*table_name)) ? table_name : "?",
				DBC_CTLIB_MSG_GetCombinedMsg(dbc_control_ptr, error_buffer));
			return_code = DBC_DB_FAILURE;
			break;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

