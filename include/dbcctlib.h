/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase CT-Library Support Functions Library Header File					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the DBC Sybase CT-LIB support
								functions library.

	Revision History	:	1996-06-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCCTLIB_H__h

#define h__DBCCTLIB_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#ifdef __MSDOS__
#elif _Windows
# ifdef _MSC_VER
#  if _MSC_VER >= 1300
#   pragma warning(disable:4255 4668)
#   include <windows.h>
#   include <sybfront.h>
#   include <sybdb.h>
#   pragma warning(default:4255 4668)
#  elif _MSC_VER >= 1200
#   pragma warning(disable:4115)
#   include <windows.h>
#   include <sybfront.h>
#   include <sybdb.h>
#   pragma warning(default:4115)
#  else
#   pragma warning(disable:4115 4201 4214 4514)
#   include <windows.h>
#   include <sybfront.h>
#   include <sybdb.h>
#   pragma warning(default:4115 4201 4214)
# 	endif /* #  if _MSC_VER >= 1200 */
# else
#  include <windows.h>
#  include <sybfront.h>
#  include <sybdb.h>
# endif /* # ifdef _MSC_VER */
#else
# include <sybfront.h>
# include <sybdb.h>
#endif /* #ifdef __MSDOS__ */

#include <ctpublic.h>

#include "dbcfuncs.h"

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DBC_CTLIB_SERVER_NAME				0
#define DBC_CTLIB_DB_NAME					1
#define DBC_CTLIB_OWNER_NAME				2
#define DBC_CTLIB_USER_NAME				3
#define DBC_CTLIB_PASS_WORD				4
#define DBC_CTLIB_CONN_SPEC_COUNT		5
/*	***********************************************************************	*/


/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_CTLIB

   DESCRIPTION :	The ''DBC_CTLIB'' structure contains the complete
						state necessary to the operation of the DBC Sybase CT-LIB
						facility library.

						The ''DBC_CTLIB'' structure is declared as follows:

{|@|}typedef struct {
	DBC_CONTEXT    *dbc_context_ptr;
	DBC_FUNCS       dbc_funcs;
	CS_CONTEXT     *context_ptr;
	CS_CONNECTION  *connection_ptr;
	CS_COMMAND     *command_ptr;
	MLOG           *mlog_ptr;
	DBC_FLAG        flags;
	unsigned int    conn_count;
	char          **conn_list;
	char            server_msg[DBC_MAX_ERROR_TEXT];
	char            client_msg[DBC_MAX_ERROR_TEXT];
	void           *user_data_ptr;
} DBC_CTLIB;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``dbc_funcs`` is a ''DBC_FUNCS'' structure which will
						be used to store the results of invoking the function
						``DBC_CTLIB_AttachFacility``.

						(.) ``context_ptr`` is a pointer to the initialized Sybase
						CT-LIB context which will be used by the facility.

						(.) ``connection_ptr`` is a pointer to the initialized
						Sybase CT-LIB connection which will be used by the facility.

						(.) ``command_ptr`` is a pointer to the initialized Sybase
						CT-LIB command which will be used by the facility.

						(.) ``mlog_ptr`` is a pointer to the
						''MLOG'' structure to be used for logging
						during operation of the facility.

						(.) ``db_debug_flag`` is an indication as to whether all
						Sybase CT-LIB server and client messages returned to the
						application program are to be logged using the
						``mlog_ptr`` member.

						(-) If ``db_debug_flag`` is non-zero, such logging will be
						performed by the facility.

						(.) ``sql_debug_flag`` is an indication as to whether all
						SQL statements sent to the database server are to be logged
						using the ``mlog_ptr`` member.

						(-) If ``sql_debug_flag`` is non-zero, such logging will be
						performed by the facility.

						(.) ``server_msg`` is an array of ''char'' which contains
						the last server message received by the DBC Sybase CT-LIB
						facility library. It is ''DBC_MAX_ERROR_TEXT'' characters in
						length.

						(.) ``client_msg`` is is an array of ''char'' which contains
						the last client message received by the DBC Sybase CT-LIB
						facility library. It is ''DBC_MAX_ERROR_TEXT'' characters in
						length.

						(.) ``user_data_ptr`` is reserved for application programmer
						use.

   NOTES       :	A ''DBC_CTLIB'' structure may be created and
						initialized by calling the ``init`` function member of
						the ''DBC_FUNCS'' structure attached to your application.
						A ''DBC_CTLIB'' structure may be closed and its
						resources freed by calling the ``free`` function member of
						the ''DBC_FUNCS'' structure attached to your application.
						These functions are implemented in the DBC Sybase CT-LIB
						facility by the functions ``DBC_CTLIB_Initialize`` and
						``DBC_CTLIB_Close``, respectively.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1996 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_CTLIB
						DBC Structures and Data Types:DBC_CTLIB
						DBC Sybase CT-LIB Structures and Data Types:DBC_CTLIB
						Structures and Data Types:DBC_CTLIB

   PUBLISH XREF:	DBC_CTLIB

   PUBLISH NAME:	DBC_CTLIB

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	DBC_CONTEXT    *dbc_context_ptr;
	DBC_FUNCS       dbc_funcs;
	CS_CONTEXT     *context_ptr;
	CS_CONNECTION  *connection_ptr;
	CS_COMMAND     *command_ptr;
	MLOG           *mlog_ptr;
	DBC_FLAG        flags;
	unsigned int    conn_count;
	char          **conn_list;
	char            server_msg[DBC_MAX_ERROR_TEXT];
	char            client_msg[DBC_MAX_ERROR_TEXT];
	void           *user_data_ptr;
} DBC_CTLIB;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sybase CT-LIB attachment function prototype . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_CTLIB_AttachFacility, (DBC_FUNCS *funcs_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sybase CT-LIB facility exposed function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int          DBC_CTLIB_BindMembers,
	(DBC_CTLIB *dbc_control_ptr, unsigned int member_count,
	const MDDL *member_list, const char *table_name, void *bind_buffer,
	char *error_text));
COMPAT_FN_DECL(int          DBC_CTLIB_Cancel,
	(DBC_CTLIB *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_CTLIB_CancelAll,
	(DBC_CTLIB *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_CTLIB_CancelQuery,
	(DBC_CTLIB *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(void         DBC_CTLIB_Close,
	(DBC_CTLIB **dbc_control_ptr));
COMPAT_FN_DECL(int          DBC_CTLIB_DoSQLCommand,
	(DBC_CTLIB *dbc_control_ptr, const char *sql_command,
	char *error_text));
COMPAT_FN_DECL(char        *DBC_CTLIB_GetID,
	(char *id_string));
COMPAT_FN_DECL(int          DBC_CTLIB_GetRows,
	(DBC_CTLIB *dbc_control_ptr, unsigned int member_count,
	const MDDL *member_list, const char *sql_command, const char *table_name,
	unsigned int *out_row_count, void **out_row_list,
	unsigned int out_row_size, unsigned int data_row_size,
	unsigned int data_row_offset, unsigned int max_row_count,
	unsigned int alloc_granularity, char *error_text));
COMPAT_FN_DECL(int          DBC_CTLIB_GetRowsBasic,
	(DBC_CTLIB *dbc_control_ptr, const DBC_GETROWS *get_rows_ptr,
	unsigned int *out_row_count, void **out_row_list, char *error_text));
COMPAT_FN_DECL(char        *DBC_CTLIB_GetVendorName,
	(char *vendor_name));
COMPAT_FN_DECL(STR_VERSION *DBC_CTLIB_GetVersion,
	(STR_VERSION *version_number));
COMPAT_FN_DECL(char        *DBC_CTLIB_GetVersionString,
	(char *version_string));
COMPAT_FN_DECL(int          DBC_CTLIB_Initialize,
	(DBC_CONTEXT *dbc_context_ptr, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_CTLIB_Open,
	(DBC_CONTEXT *dbc_context_ptr, const char *conn_type,
	const char *conn_string, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sybase CT-LIB facility private function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void        DBC_CTLIB_MSG_ClearMsg,
	(DBC_CTLIB *dbc_control_ptr));
COMPAT_FN_DECL(char       *DBC_CTLIB_MSG_GetCombinedMsg,
	(DBC_CTLIB *dbc_control_ptr, char *text_buffer));
COMPAT_FN_DECL(char       *DBC_CTLIB_MSG_GetServerMsg,
	(DBC_CTLIB *dbc_control_ptr, char *text_buffer));
COMPAT_FN_DECL(char       *DBC_CTLIB_MSG_GetClientMsg,
	(DBC_CTLIB *dbc_control_ptr, char *text_buffer));
COMPAT_FN_DECL(CS_RETCODE  DBC_CTLIB_ServerMsgCB,
	(CS_CONTEXT *context, CS_CONNECTION *connection, CS_SERVERMSG *message));
COMPAT_FN_DECL(CS_RETCODE  DBC_CTLIB_ClientMsgCB,
	(CS_CONTEXT *context, CS_CONNECTION *connection, CS_CLIENTMSG *message));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCCTLIB_H__h */

