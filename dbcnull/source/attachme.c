/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Internal Null Support Functions Library Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a specified attachment to the Internal
								NULL facility.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2016.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dbcnulli.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_NULL_AttachFacility

   SYNOPSIS    :	void DBC_NULL_AttachFacility(funcs_ptr);

						DBC_FUNCS *funcs_ptr;

   DESCRIPTION :	Populates a ''DBC_FUNCS'' structure with pointers to the
						functions which implement the DBC Internal NULL facility.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``funcs_ptr`` points to the ''DBC_FUNCS'' structure to
						be populated by this function.

						(-) If ``funcs_ptr`` is ''NULL'', no action is taken by
						this function. This behavior is intended to support the
						forcing of the linker to include the DBC facility functions
						in the executable.

   RETURNS     :	Void.

   NOTES       :	If the DBC Internal NULL facility library ``dbcdblib.a`` has
						been linked into the executable, then this function will be
						called by the generic DBC attach function
						``DBC_AttachFacility``.

   CAVEATS     :	Not all functions will be implemented in all facilities. It
						is, therefore, possible that some of the function pointers
						in the ``funcs_ptr`` parameter will be set to ''NULL''.
						The application programmer must be sure to test for this
						condition before invoking any facility function.

   SEE ALSO    :	DBC_AttachFacility
						DBC_CTLIB_AttachFacility

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2016 Michael L. Brock

   OUTPUT INDEX:	DBC_NULL_AttachFacility
						DBC Internal NULL Functions:DBC_NULL_AttachFacility
						DBC Functions:Attach Functions:DBC_NULL_AttachFacility

   PUBLISH XREF:	DBC_NULL_AttachFacility

   PUBLISH NAME:	DBC_NULL_AttachFacility

	ENTRY CLASS	:	DBC Functions:Attach Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_NULL_AttachFacility(DBC_FUNCS *funcs_ptr)
#else
void DBC_NULL_AttachFacility(funcs_ptr)
DBC_FUNCS *funcs_ptr;
#endif /* #ifndef NARGS */
{
	if (funcs_ptr != NULL) {
		DBC_INIT_DBCFuncs(funcs_ptr);
		funcs_ptr->bind               =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, unsigned int member_count,
			const MDDL *member_list, const char *table_name, void *bind_buffer,
			char *error_text), DBC_NULL_BindMembers);
		funcs_ptr->cancel             =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, char *error_text),
			DBC_NULL_Cancel);
		funcs_ptr->cancel_all         =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, char *error_text),
			DBC_NULL_CancelAll);
		funcs_ptr->cancel_query       =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, char *error_text),
			DBC_NULL_CancelQuery);
		funcs_ptr->close              =
			COMPAT_FN_CAST(void, (void **dbc_control_ptr), DBC_NULL_Close);
		funcs_ptr->do_sql             =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, const char *sql_command,
			char *error_text), DBC_NULL_DoSQLCommand);
		funcs_ptr->get_id             = DBC_NULL_GetID;
		funcs_ptr->get_rows           =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, unsigned int member_count,
			const MDDL *member_list, const char *sql_command,
			const char *table_name, unsigned int *out_row_count,
			void **out_row_list, unsigned int out_row_size,
			unsigned int data_row_size, unsigned int data_row_offset,
			unsigned int max_row_count, unsigned int alloc_granularity,
			char *error_text), DBC_NULL_GetRows);
		funcs_ptr->get_rows_basic     =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr,
			const DBC_GETROWS *get_rows_ptr, unsigned int *out_row_count,
			void **out_row_list, char *error_text), DBC_NULL_GetRowsBasic);
		funcs_ptr->get_vendor_name    = DBC_NULL_GetVendorName;
		funcs_ptr->get_version        = DBC_NULL_GetVersion;
		funcs_ptr->get_version_string = DBC_NULL_GetVersionString;
		funcs_ptr->init               = DBC_NULL_Initialize;
		funcs_ptr->open               =
			COMPAT_FN_CAST(int, (void *dbc_control_ptr, const char *conn_type,
			const char *conn_string, MLOG *mlog_ptr, DBC_FLAG flags,
			void *user_data_ptr, char *error_text), DBC_NULL_Open);
		funcs_ptr->parse_conn         = NULL;
		funcs_ptr->table_to_members   = NULL;
		funcs_ptr->set_display_length = NULL;
		funcs_ptr->dump_field         = NULL;
		funcs_ptr->map_type_to_mddl   = DBC_NULL_MapTypeToMDDL;
		funcs_ptr->format_type        = NULL;
		funcs_ptr->format_type_sql    = NULL;
		funcs_ptr->double_to_number   = NULL;
		funcs_ptr->number_to_double   = NULL;
		funcs_ptr->dtime_to_date      = NULL;
		funcs_ptr->date_to_dtime      = NULL;
		funcs_ptr->dtime_to_time      = NULL;
		funcs_ptr->time_to_dtime      = NULL;
		funcs_ptr->is_number          = NULL;
		funcs_ptr->min_number         = NULL;
		funcs_ptr->max_number         = NULL;
		funcs_ptr->cmp_number         = NULL;
		funcs_ptr->scmp_number        = NULL;
		funcs_ptr->is_date            = NULL;
		funcs_ptr->min_date           = NULL;
		funcs_ptr->max_date           = NULL;
		funcs_ptr->cmp_date           = NULL;
		funcs_ptr->scmp_date          = NULL;
		funcs_ptr->is_time            = NULL;
		funcs_ptr->min_time           = NULL;
		funcs_ptr->max_time           = NULL;
		funcs_ptr->cmp_time           = NULL;
		funcs_ptr->scmp_time          = NULL;
	}
}
/*	***********************************************************************	*/

