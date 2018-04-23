/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Internal Null Support Functions Library Header File							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the null DBC support functions
								library.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCNULL_H__h

#define h__DBCNULL_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include "dbcfuncs.h"

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DBC_NULL_SERVER_NAME				0
#define DBC_NULL_DB_NAME					1
#define DBC_NULL_OWNER_NAME				2
#define DBC_NULL_USER_NAME					3
#define DBC_NULL_PASS_WORD					4
#define DBC_NULL_CONN_SPEC_COUNT			5
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_NULL

   DESCRIPTION :	The ''DBC_NULL'' structure contains the complete
						state necessary to the operation of the DBC Internal NULL
						facility library.

						The ''DBC_NULL'' structure is declared as follows:

{|@|}typedef struct {
	DBC_CONTEXT   *dbc_context_ptr;
	DBC_FUNCS      dbc_funcs;
	LOGINREC      *server_ptr;
	DBPROCESS     *database_ptr;
	MLOG          *mlog_ptr;
	DBC_FLAG       flags;
	unsigned int   conn_count;
	char         **conn_list;
	void          *user_data_ptr;
} DBC_NULL;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``dbc_funcs`` is a ''DBC_FUNCS'' structure which will
						be used to store the results of invoking the function
						``DBC_NULL_AttachFacility``.

						(.) ``server_ptr`` is the pointer to the Internal ''LOGINREC''
						structure resulting from a call to ``dblogin()``.

						(.) ``database_ptr`` is the pointer to the Internal
						''DBPROCESS'' structure resulting from a call to
						``dbopen()``.

						(.) ``mlog_ptr`` is a pointer to the
						''MLOG'' structure to be used for logging
						during operation of the facility.

						(.) ``db_debug_flag`` is an indication as to whether all
						Internal NULL server and client messages returned to the
						application program are to be logged using the
						``mlog_ptr`` member.

						(-) If ``db_debug_flag`` is non-zero, such logging will be
						performed by the facility.

						(.) ``sql_debug_flag`` is an indication as to whether all
						SQL statements sent to the database server are to be logged
						using the ``mlog_ptr`` member.

						(-) If ``sql_debug_flag`` is non-zero, such logging will be
						performed by the facility.

						(.) ``user_data_ptr`` is reserved for application programmer
						use.

   NOTES       :	A ''DBC_NULL'' structure may be created and
						initialized by calling the ``init`` function member of
						the ''DBC_FUNCS'' structure attached to your application.
						A ''DBC_NULL'' structure may be closed and its
						resources freed by calling the ``free`` function member of
						the ''DBC_FUNCS'' structure attached to your application.
						These functions are implemented in the DBC Internal NULL
						facility by the functions ``DBC_NULL_Initialize`` and
						``DBC_NULL_Close``, respectively.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_NULL
						DBC Structures and Data Types:DBC_NULL
						DBC Internal NULL Structures and Data Types:DBC_NULL
						Structures and Data Types:DBC_NULL

   PUBLISH XREF:	DBC_NULL

   PUBLISH NAME:	DBC_NULL

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	DBC_CONTEXT   *dbc_context_ptr;
	DBC_FUNCS      dbc_funcs;
	MLOG          *mlog_ptr;
	DBC_FLAG       flags;
	unsigned int   conn_count;
	char         **conn_list;
	void          *user_data_ptr;
} DBC_NULL;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Internal NULL attachment function prototype . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_NULL_AttachFacility, (DBC_FUNCS *funcs_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Internal NULL facility exposed function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int          DBC_NULL_BindMembers,
	(DBC_NULL *dbc_control_ptr, unsigned int member_count,
	const MDDL *member_list, const char *table_name, void *bind_buffer,
	char *error_text));
COMPAT_FN_DECL(int          DBC_NULL_Cancel,
	(DBC_NULL *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_NULL_CancelAll,
	(DBC_NULL *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_NULL_CancelQuery,
	(DBC_NULL *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(void         DBC_NULL_Close,
	(DBC_NULL **dbc_control_ptr));
COMPAT_FN_DECL(int          DBC_NULL_DoSQLCommand,
	(DBC_NULL *dbc_control_ptr, const char *sql_command,
	char *error_text));
COMPAT_FN_DECL(char        *DBC_NULL_GetID,
	(char *id_string));
COMPAT_FN_DECL(int          DBC_NULL_GetRows,
	(DBC_NULL *dbc_control_ptr, unsigned int member_count,
	const MDDL *member_list, const char *sql_command, const char *table_name,
	unsigned int *out_row_count, void **out_row_list,
	unsigned int out_row_size, unsigned int data_row_size,
	unsigned int data_row_offset, unsigned int max_row_count,
	unsigned int alloc_granularity, char *error_text));
COMPAT_FN_DECL(int          DBC_NULL_GetRowsBasic,
	(DBC_NULL *dbc_control_ptr, const DBC_GETROWS *get_rows_ptr,
	unsigned int *out_row_count, void **out_row_list, char *error_text));
COMPAT_FN_DECL(char        *DBC_NULL_GetVendorName,
	(char *vendor_name));
COMPAT_FN_DECL(STR_VERSION *DBC_NULL_GetVersion,
	(STR_VERSION *version_number));
COMPAT_FN_DECL(char        *DBC_NULL_GetVersionString,
	(char *version_string));
COMPAT_FN_DECL(int          DBC_NULL_Initialize,
	(DBC_CONTEXT *dbc_context_ptr, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_NULL_Open,
	(DBC_CONTEXT *dbc_context_ptr, const char *conn_type,
	const char *conn_string, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCNULL_H__h */

