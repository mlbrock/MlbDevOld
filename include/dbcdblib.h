/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase DB-Library Support Functions Library Header File					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Sybase DBC Sybase DB-LIB support
								functions library.

	Revision History	:	1993-07-07 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCDBLIB_H__h

#define h__DBCDBLIB_H__h					1

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

#include "dbcfuncs.h"

/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DBC_DBLIB_SERVER_NAME				0
#define DBC_DBLIB_DB_NAME					1
#define DBC_DBLIB_OWNER_NAME				2
#define DBC_DBLIB_USER_NAME				3
#define DBC_DBLIB_PASS_WORD				4
#define DBC_DBLIB_CONN_SPEC_COUNT		5
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB

   DESCRIPTION :	The ''DBC_DBLIB'' structure contains the complete
						state necessary to the operation of the DBC Sybase DB-LIB
						facility library.

						The ''DBC_DBLIB'' structure is declared as follows:

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
} DBC_DBLIB;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``dbc_funcs`` is a ''DBC_FUNCS'' structure which will
						be used to store the results of invoking the function
						``DBC_DBLIB_AttachFacility``.

						(.) ``server_ptr`` is the pointer to the Sybase ''LOGINREC''
						structure resulting from a call to ``dblogin()``.

						(.) ``database_ptr`` is the pointer to the Sybase
						''DBPROCESS'' structure resulting from a call to
						``dbopen()``.

						(.) ``mlog_ptr`` is a pointer to the
						''MLOG'' structure to be used for logging
						during operation of the facility.

						(.) ``db_debug_flag`` is an indication as to whether all
						Sybase DB-LIB server and client messages returned to the
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

   NOTES       :	A ''DBC_DBLIB'' structure may be created and
						initialized by calling the ``init`` function member of
						the ''DBC_FUNCS'' structure attached to your application.
						A ''DBC_DBLIB'' structure may be closed and its
						resources freed by calling the ``free`` function member of
						the ''DBC_FUNCS'' structure attached to your application.
						These functions are implemented in the DBC Sybase DB-LIB
						facility by the functions ``DBC_DBLIB_Initialize`` and
						``DBC_DBLIB_Close``, respectively.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB
						DBC Structures and Data Types:DBC_DBLIB
						DBC Sybase DB-LIB Structures and Data Types:DBC_DBLIB
						Structures and Data Types:DBC_DBLIB

   PUBLISH XREF:	DBC_DBLIB

   PUBLISH NAME:	DBC_DBLIB

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	DBC_CONTEXT   *dbc_context_ptr;
	DBC_FUNCS      dbc_funcs;
	LOGINREC      *server_ptr;
	DBPROCESS     *database_ptr;
	MLOG          *mlog_ptr;
	DBC_FLAG       flags;
	unsigned int   conn_count;
	char         **conn_list;
	void          *user_data_ptr;
} DBC_DBLIB;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_DBLIB_MSG

   DESCRIPTION :	The structure ''DBC_DBLIB_MSG'' supports the implementation
						of a stack of Sybase DB-LIB error and message handlers.

						The implementation of this structure is made necessary by
						the fact that there can be only one handler of either type
						active within a single process using Sybase DB-LIB.

						''DBC_DBLIB_MSG'' is declared as follows:

{|@|}typedef struct {
	// ***** Declarations differ across Sybase versions . . . *****
#ifdef CS_PUBLIC
	EHANDLEFUNC   err_handler;
	MHANDLEFUNC   msg_handler;
#else
# ifndef NARGS
	int         (*err_handler)(DBPROCESS *, int, int, int, char *,
					char *);
	int         (*msg_handler)(DBPROCESS *, DBINT, int, int, char *,
					char *, char *, DBUSMALLINT);
# else
	int         (*err_handler)();
	int         (*msg_handler)();
# endif // #ifndef NARGS
#endif // #ifdef CS_PUBLIC
	MLOG         *mlog_ptr;
	int           db_debug_flag;
	char          msg_text[DBC_MAX_ERROR_TEXT];
	char          err_text[DBC_MAX_ERROR_TEXT];
} DBC_DBLIB_MSG;

						Note the '#ifdef CS_PUBLIC' block. This is necessary
						because Sybase DB-LIB prior to Sybase System 10 (such as
						4.9.2) declared the last parameter of message handlers to
						be of type ''DBUSMALLINT'', whereas System 10 and subsequent
						releases declared it to be of type ''int''.

	MEMBERS		:	The members of this structure are as follow:

						(.) ``err_handler`` is the saved pointer to the previous
						error handler function.

						(.) ``msg_handler`` is the saved pointer to the previous
						message handler function.

						(.) ``mlog_ptr`` is a pointer to the
						''MLOG'' structure to be used for logging
						when the message handler or error handler is invoked.

						(.) ``db_debug_flag`` is an indication as to whether all
						Sybase DB-LIB server and client messages returned to the
						application program are to be logged using the
						``mlog_ptr`` member.

						(.) ``msg_text`` is an array of ''char'' in which is stored
						the text descriptive of the last message received by the
						message handler function.

						(.) ``err_text`` is an array of ''char'' in which is stored
						the text descriptive of the last message received by the
						error handler function.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1993 - 2018 Michael L. Brock

   OUTPUT INDEX:	DBC_DBLIB_MSG
						DBC Structures and Data Types:DBC_DBLIB_MSG
						DBC Sybase DB-LIB Structures and Data Types:DBC_DBLIB_MSG
						Structures and Data Types:DBC_DBLIB_MSG

   PUBLISH XREF:	DBC_DBLIB_MSG

   PUBLISH NAME:	DBC_DBLIB_MSG

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
	/* ***** Declarations differ across Sybase versions . . . ***** */
#ifdef CS_PUBLIC
	EHANDLEFUNC   err_handler;
	MHANDLEFUNC   msg_handler;
#else
# ifndef NARGS
	int         (*err_handler)(DBPROCESS *, int, int, int, char *,
					char *);
	int         (*msg_handler)(DBPROCESS *, DBINT, int, int, char *,
					char *, char *, DBUSMALLINT);
# else
	int         (*err_handler)();
	int         (*msg_handler)();
# endif /* #ifndef NARGS */
#endif /* #ifdef CS_PUBLIC */
	MLOG         *mlog_ptr;
	int           db_debug_flag;
	char          msg_text[DBC_MAX_ERROR_TEXT];
	char          err_text[DBC_MAX_ERROR_TEXT];
} DBC_DBLIB_MSG;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sybase DB-LIB attachment function prototype . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_DBLIB_AttachFacility, (DBC_FUNCS *funcs_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sybase DB-LIB facility exposed function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int          DBC_DBLIB_BindMembers,
	(DBC_DBLIB *dbc_control_ptr, unsigned int member_count,
	const MDDL *member_list, const char *table_name, void *bind_buffer,
	char *error_text));
COMPAT_FN_DECL(int          DBC_DBLIB_Cancel,
	(DBC_DBLIB *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_DBLIB_CancelAll,
	(DBC_DBLIB *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_DBLIB_CancelQuery,
	(DBC_DBLIB *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(void         DBC_DBLIB_Close,
	(DBC_DBLIB **dbc_control_ptr));
COMPAT_FN_DECL(int          DBC_DBLIB_DoSQLCommand,
	(DBC_DBLIB *dbc_control_ptr, const char *sql_command,
	char *error_text));
COMPAT_FN_DECL(char        *DBC_DBLIB_GetID,
	(char *id_string));
COMPAT_FN_DECL(int          DBC_DBLIB_GetRows,
	(DBC_DBLIB *dbc_control_ptr, unsigned int member_count,
	const MDDL *member_list, const char *sql_command, const char *table_name,
	unsigned int *out_row_count, void **out_row_list,
	unsigned int out_row_size, unsigned int data_row_size,
	unsigned int data_row_offset, unsigned int max_row_count,
	unsigned int alloc_granularity, char *error_text));
COMPAT_FN_DECL(int          DBC_DBLIB_GetRowsBasic,
	(DBC_DBLIB *dbc_control_ptr, const DBC_GETROWS *get_rows_ptr,
	unsigned int *out_row_count, void **out_row_list, char *error_text));
COMPAT_FN_DECL(char        *DBC_DBLIB_GetVendorName,
	(char *vendor_name));
COMPAT_FN_DECL(STR_VERSION *DBC_DBLIB_GetVersion,
	(STR_VERSION *version_number));
COMPAT_FN_DECL(char        *DBC_DBLIB_GetVersionString,
	(char *version_string));
COMPAT_FN_DECL(int          DBC_DBLIB_Initialize,
	(DBC_CONTEXT *dbc_context_ptr, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_DBLIB_Open,
	(DBC_CONTEXT *dbc_context_ptr, const char *conn_type,
	const char *conn_string, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sybase DB-LIB facility private function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int            DBC_DBLIB_MSG_DefaultHandler,
	(DBC_DBLIB *dbc_control_ptr, char *error_text));
	/*	*****************************************************************
		*****************************************************************
		Declarations differ across Sybase versions . . .
		*****************************************************************	*/
#ifdef CS_PUBLIC
COMPAT_FN_DECL(int            DBC_DBLIB_MSG_PushHandler,
	(EHANDLEFUNC err_handler, MHANDLEFUNC msg_handler, char *error_text));
#else
# ifndef NARGS
COMPAT_FN_DECL(int            DBC_DBLIB_MSG_PushHandler,
	(int (*err_handler)(DBPROCESS *, int, int, int, char *, char *),
	int (*msg_handler)(DBPROCESS *, DBINT, int, int, char *, char *, char *,
		DBUSMALLINT), char *error_text));
# else
COMPAT_FN_DECL(int            DBC_DBLIB_MSG_PushHandler,
	(int (*err_handler)(), int (*msg_handler)(), char *error_text));
# endif /* #ifndef NARGS */
#endif /* #ifdef CS_PUBLIC */
	/*	*****************************************************************	*/
COMPAT_FN_DECL(void           DBC_DBLIB_MSG_PopHandler,
	(void));
COMPAT_FN_DECL(void           DBC_DBLIB_MSG_ClearHandler,
	(void));
COMPAT_FN_DECL(DBC_DBLIB_MSG *DBC_DBLIB_MSG_GetHandlerPtr,
	(void));
COMPAT_FN_DECL(char          *DBC_DBLIB_MSG_GetHandlerMessage,
	(char *text_buffer));
COMPAT_FN_DECL(char          *DBC_DBLIB_MSG_GetHandlerMSGMessage,
	(char *text_buffer));
COMPAT_FN_DECL(char          *DBC_DBLIB_MSG_GetHandlerERRMessage,
	(char *text_buffer));
COMPAT_FN_DECL(int            DBC_DBLIB_MSG_HandleERR,
	(DBPROCESS *db_proc, int severity, int db_err, int os_err,
	char *db_err_string, char *os_err_string));
	/*	*****************************************************************
		*****************************************************************
		Declarations differ across Sybase versions . . .
		*****************************************************************	*/
#ifdef CS_PUBLIC
COMPAT_FN_DECL(int            DBC_DBLIB_MSG_HandleMSG,
	(DBPROCESS *db_proc, DBINT msg_number, int msg_state, int severity,
	char *msg_text, char *server_name, char *proc_name, int line_number));
#else
COMPAT_FN_DECL(int            DBC_DBLIB_MSG_HandleMSG,
	(DBPROCESS *db_proc, DBINT msg_number, int msg_state, int severity,
	char *msg_text, char *server_name, char *proc_name,
	DBUSMALLINT line_number));
#endif /* # ifdef CS_PUBLIC */
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCDBLIB_H__h */

