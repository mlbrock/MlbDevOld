/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase CT-Library Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes a Sybase CT-LIB facility handle.

	Revision History	:	1996-06-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
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

   NAME        :	DBC_CTLIB_Initialize

   SYNOPSIS    :	return_code = DBC_CTLIB_Initialize(dbc_control_ptr,
							mlog_ptr, db_debug_flag, sql_debug_flag,
							error_text);

						int         return_code;

						DBC_CTLIB **dbc_control_ptr;

						MLOG       *mlog_ptr;

						int         db_debug_flag;

						int         sql_debug_flag;

						char       *error_text;

   DESCRIPTION :	Allocates memory for a ''DBC_CTLIB'' structure and
						initializes its members.

   PARAMETERS  :	Parameters to this function are as follow:

						(.) ``dbc_control_ptr`` is the doubly-indirect
						''DBC_CTLIB'' pointer structure to be allocated
						and initialized.

						(.) ``mlog_ptr`` points to a structure of type
						''MLOG'' which describes the particulars of
						how the DBC Sybase CT-LIB facility is to perform logging. The
						value of this parameter is copied to the ``mlog_ptr``
						member of the ''DBC_CTLIB'' structure initialized
						by this function.

						(-) If ``mlog_ptr`` is ''NULL'' the facility will
						not perform any logging.

						(.) ``db_debug_flag`` is an indication as to whether all
						Sybase CT-LIB server and client messages returned to the
						application program are to be logged using the
						``mlog_ptr`` member. The value of this parameter is
						copied to the ``mlog_ptr`` member of the
						''DBC_CTLIB'' structure initialized by this
						function.

						(-) If ``db_debug_flag`` is non-zero, such logging will be
						performed by the facility.

						(.) ``sql_debug_flag`` is an indication as to whether all
						SQL statements sent to the database server are to be logged
						using the ``mlog_ptr`` member.  The value of this
						parameter is copied to the ``mlog_ptr`` member of
						the ''DBC_CTLIB'' structure initialized by this
						function.

						(-) If ``sql_debug_flag`` is non-zero, such logging will be
						performed by the facility.

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

   SEE ALSO    :	DBC_DBLIB_Initialize

   EXAMPLES    :	

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB_Initialize
						DBC Sybase CT-LIB Functions:DBC_CTLIB_Initialize
						DBC Functions:Initialization Functions:DBC_CTLIB_Initialize

   PUBLISH XREF:	DBC_CTLIB_Initialize

   PUBLISH NAME:	DBC_CTLIB_Initialize

	ENTRY CLASS	:	DBC Functions:Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int DBC_CTLIB_Initialize(DBC_CONTEXT *dbc_context_ptr, MLOG *mlog_ptr,
	DBC_FLAG flags, void *user_data_ptr, char *error_text)
#else
int DBC_CTLIB_Initialize(dbc_context_ptr, mlog_ptr, flags, user_data_ptr,
	error_text)
DBC_CONTEXT *dbc_context_ptr;
MLOG        *mlog_ptr;
DBC_FLAG     flags;
void        *user_data_ptr;
char        *error_text;
#endif /* #ifndef NARGS */
{
	int                return_code;
	DBC_CTLIB *ptr;

	if (dbc_context_ptr->dbc_control_ptr != NULL) {
		sprintf(error_text, "%s 0x%lx.",
			"The DBC Sybase CT-LIB facility is already initialized at address",
			((unsigned long) dbc_context_ptr->dbc_control_ptr));
		return_code = DBC_FAILURE;
	}
	else if ((dbc_context_ptr->dbc_control_ptr = ((DBC_CTLIB *)
		calloc(1, sizeof(DBC_CTLIB)))) == NULL) {
		STR_AllocMsgItem(sizeof(DBC_CTLIB), error_text,
			"Unable to allocate memory for the 'DBC_CTLIB' structure");
		return_code = DBC_MEMORY_FAILURE;
	}
	else {
		ptr                  = ((DBC_CTLIB *) dbc_context_ptr->dbc_control_ptr);
		ptr->dbc_context_ptr = dbc_context_ptr;
		ptr->dbc_funcs       = dbc_context_ptr->dbc_funcs;
		ptr->context_ptr     = NULL;
		ptr->connection_ptr  = NULL;
		ptr->command_ptr     = NULL;
		ptr->mlog_ptr        = mlog_ptr;
		ptr->flags           = flags;
		ptr->user_data_ptr   = user_data_ptr;
		return_code          = DBC_SUCCESS;
	}

	return(return_code);
}
/*	***********************************************************************	*/

