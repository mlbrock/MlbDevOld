/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a specified attachment to the Microsoft SQL
								Server DB-LIB facility.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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

   NAME        :	DBC_DBLIB_AttachFacility

   SYNOPSIS    :	void DBC_DBLIB_AttachFacility(funcs_ptr);

						DBC_FUNCS *funcs_ptr;

   DESCRIPTION :	Populates a ''DBC_FUNCS'' structure with pointers to the
						functions which implement the DBC Microsoft SQL Server
						DB-LIB facility.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``funcs_ptr`` points to the ''DBC_FUNCS'' structure to
						be populated by this function.

						(-) If ``funcs_ptr`` is ''NULL'', no action is taken by
						this function. This behavior is intended to support the
						forcing of the linker to include the DBC facility functions
						in the executable.

   RETURNS     :	Void.

   NOTES       :	If the DBC Microsoft SQL Server DB-LIB facility library
						``dbcmssql.a`` has been linked into the executable, then
						this function will be called by the generic DBC attach
						function ``DBC_AttachFacility``.

   CAVEATS     :	Not all functions will be implemented in all facilities. It
						is, therefore, possible that some of the function pointers
						in the ``funcs_ptr`` parameter will be set to ''NULL''.
						The application programmer must be sure to test for this
						condition before invoking any facility function.

   SEE ALSO    :	DBC_AttachFacility

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2015 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_AttachFacility
						DBC Microsoft SQL Server DB-LIB Functions:DBC_DBLIB_AttachFacility
						DBC Functions:Attach Functions:DBC_DBLIB_AttachFacility

   PUBLISH XREF:	DBC_DBLIB_AttachFacility

   PUBLISH NAME:	DBC_DBLIB_AttachFacility

	ENTRY CLASS	:	DBC Functions:Attach Functions

EOH */
/*	***********************************************************************	*/
void DBC_MSSQL_AttachFacility(funcs_ptr)
DBC_FUNCS *funcs_ptr;
{
	if (funcs_ptr != NULL) {
		DBC_INIT_DBCFuncs(funcs_ptr);
		funcs_ptr->bind               =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, unsigned int member_count,
			const MDDL *member_list, const char *table_name, void *bind_buffer,
			char *error_text), DBC_MSSQL_BindMembers);
		funcs_ptr->cancel             =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, char *error_text),
			DBC_MSSQL_Cancel);
		funcs_ptr->cancel_all         =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, char *error_text),
			DBC_MSSQL_CancelAll);
		funcs_ptr->cancel_query       =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, char *error_text),
			DBC_MSSQL_CancelQuery);
		funcs_ptr->close              =
			COMPAT_FN_CAST(void, (void **dbc_control_ptr), DBC_MSSQL_Close);
		funcs_ptr->do_sql             =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, const char *sql_command,
			char *error_text), DBC_MSSQL_DoSQLCommand);
		funcs_ptr->get_id             = DBC_MSSQL_GetID;
		funcs_ptr->get_rows           =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, unsigned int member_count,
			const MDDL *member_list, const char *sql_command,
			const char *table_name, unsigned int *out_row_count,
			void **out_row_list, unsigned int out_row_size,
			unsigned int data_row_size, unsigned int data_row_offset,
			unsigned int max_row_count, unsigned int alloc_granularity,
			char *error_text), DBC_MSSQL_GetRows);
		funcs_ptr->get_rows_basic     =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr,
			const DBC_GETROWS *get_rows_ptr, unsigned int *out_row_count,
			void **out_row_list, char *error_text), DBC_MSSQL_GetRowsBasic);
		funcs_ptr->get_vendor_name    = DBC_MSSQL_GetVendorName;
		funcs_ptr->get_version        = DBC_MSSQL_GetVersion;
		funcs_ptr->get_version_string = DBC_MSSQL_GetVersionString;
		funcs_ptr->init               = DBC_MSSQL_Initialize;
		funcs_ptr->open               =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, const char *conn_type,
			const char *conn_string, MLOG *mlog_ptr, DBC_FLAG flags,
			void *user_data_ptr, char *error_text), DBC_MSSQL_Open);
		funcs_ptr->parse_conn         = DBC_MSSQL_ParseConn;
		funcs_ptr->table_to_members   = DBC_MSSQL_TableToMembers;
		funcs_ptr->set_display_length = DBC_MSSQL_SetDisplayLength;
		funcs_ptr->dump_field         = DBC_MSSQL_DumpField;
		funcs_ptr->map_type_to_mddl   = DBC_MSSQL_MapTypeToMDDL;
		funcs_ptr->format_type        = DBC_MSSQL_FMT_Data;
		funcs_ptr->format_type_sql    = DBC_MSSQL_FMT_Data_SQL;
		funcs_ptr->double_to_number   = DBC_MSSQL_DoubleToNumber;
		funcs_ptr->number_to_double   = DBC_MSSQL_NumberToDouble;
		funcs_ptr->dtime_to_date      = DBC_MSSQL_DTIMEToDate;
		funcs_ptr->date_to_dtime      = DBC_MSSQL_DateToDTIME;
		funcs_ptr->dtime_to_time      = DBC_MSSQL_DTIMEToTime;
		funcs_ptr->time_to_dtime      = DBC_MSSQL_TimeToDTIME;
		funcs_ptr->is_number          = DBC_MSSQL_IsNumber;
		funcs_ptr->min_number         = DBC_MSSQL_MinNumber;
		funcs_ptr->max_number         = DBC_MSSQL_MaxNumber;
		funcs_ptr->cmp_number         = DBC_MSSQL_CMP_Number;
		funcs_ptr->scmp_number        = DBC_MSSQL_SCMP_Number;
		funcs_ptr->is_date            = DBC_MSSQL_IsDate;
		funcs_ptr->min_date           = DBC_MSSQL_MinDate;
		funcs_ptr->max_date           = DBC_MSSQL_MaxDate;
		funcs_ptr->cmp_date           = DBC_MSSQL_CMP_Date;
		funcs_ptr->scmp_date          = DBC_MSSQL_SCMP_Date;
		funcs_ptr->is_time            = DBC_MSSQL_IsTime;
		funcs_ptr->min_time           = DBC_MSSQL_MinTime;
		funcs_ptr->max_time           = DBC_MSSQL_MaxTime;
		funcs_ptr->cmp_time           = DBC_MSSQL_CMP_Time;
		funcs_ptr->scmp_time          = DBC_MSSQL_SCMP_Time;
	}
}
/*	***********************************************************************	*/

