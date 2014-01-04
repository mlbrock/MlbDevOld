/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Header File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the Microsoft SQL Server DBC DB-LIB
								support functions library.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCMSSQL_H__h

#define h__DBCMSSQL_H__h					1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <mbcompat.h>

#include <windows.h>

#include <sqlfront.h>
#include <sqldb.h>

#include "dbcfuncs.h"

#include "dbcmsbas.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_FACILITY_NAME

   DESCRIPTION :	The ''DBC_MSSQL_FACILITY_NAME'' manifest constant specifies
						the DBC facility name string for the DB-LIB facility.

						''DBC_MSSQL_FACILITY_NAME'' is equal to the string value
						''Facility:Microsoft SQL Server DB-LIB''.

   NOTES       :	The DBC facility name can be retrieved by calling the
						``get_id`` function member of the ''DBC_FUNCS'' structure
						attached to your application. This function is implemented
						in the DBC DB-LIB facility by the function
						``DBC_MSSQL_GetID``.

   CAVEATS     :	The string length of this macro should not exceed the value
						of the manifest constant ''DBC_FACILITY_NAME_LENGTH''. If it
						does, it will be truncated to that length by the function
						``DBC_MSSQL_GetID``.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_FACILITY_NAME
						DBC Macros and Manifest Constants:DBC_MSSQL_FACILITY_NAME
						DBC DB-LIB Macros and Manifest Constants:DBC_MSSQL_FACILITY_NAME
						Macros and Manifest Constants:DBC_MSSQL_FACILITY_NAME
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_MSSQL_FACILITY_NAME

   PUBLISH NAME:	DBC_MSSQL_FACILITY_NAME

	ENTRY CLASS	:	Macros and Manifest Constants

EOH */
/*	***********************************************************************	*/
#define DBC_MSSQL_FACILITY_NAME			"Facility:Microsoft SQL Server DB-LIB"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	ADF NOTE: Needed here. */
/*	***********************************************************************	*/
#define DBC_MSSQL_VENDOR_NAME				"Microsoft SQL Server"
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DBC DB-LIB Library Version Number

   NAME        :	DBC DB-LIB Library Version Number

   DESCRIPTION :	The DBC DB-LIB library version number manifest constants
						together define the current version number of the DBC DB-LIB
						library as a whole.

						(.) ''DBC_MSSQL_VERSION_MAJOR'' represents the major
						component of the library version number.

						(.) ''DBC_MSSQL_VERSION_MINOR'' represents the minor
						component of the library version number.

						(.) ''DBC_MSSQL_VERSION_RELEASE'' represents the release
						component of the library version number.

						(.) ''DBC_MSSQL_VERSION_BUILD'' represents the build
						level component the of library version number.

   SEE ALSO    :	STR_VERSION

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_VERSION_MAJOR
						DBC_MSSQL_VERSION_MINOR
						DBC_MSSQL_VERSION_RELEASE
						DBC_MSSQL_VERSION_BUILD
						DBC DB-LIB Version Numbers:Library Version Number
						DBC DB-LIB Library Version Number:DBC_MSSQL_VERSION_MAJOR
						DBC DB-LIB Library Version Number:DBC_MSSQL_VERSION_MINOR
						DBC DB-LIB Library Version Number:DBC_MSSQL_VERSION_RELEASE
						DBC DB-LIB Library Version Number:DBC_MSSQL_VERSION_BUILD
						DBC Macros and Manifest Constants:DBC_MSSQL_VERSION_MAJOR
						DBC Macros and Manifest Constants:DBC_MSSQL_VERSION_MINOR
						DBC Macros and Manifest Constants:DBC_MSSQL_VERSION_RELEASE
						DBC Macros and Manifest Constants:DBC_MSSQL_VERSION_BUILD
						DBC DB-LIB Macros and Manifest Constants:DBC_MSSQL_VERSION_MAJOR
						DBC DB-LIB Macros and Manifest Constants:DBC_MSSQL_VERSION_MINOR
						DBC DB-LIB Macros and Manifest Constants:DBC_MSSQL_VERSION_RELEASE
						DBC DB-LIB Macros and Manifest Constants:DBC_MSSQL_VERSION_BUILD
						Macros and Manifest Constants:DBC_MSSQL_VERSION_MAJOR
						Macros and Manifest Constants:DBC_MSSQL_VERSION_MINOR
						Macros and Manifest Constants:DBC_MSSQL_VERSION_RELEASE
						Macros and Manifest Constants:DBC_MSSQL_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_MSSQL_VERSION_MAJOR
						DBC_MSSQL_VERSION_MINOR
						DBC_MSSQL_VERSION_RELEASE
						DBC_MSSQL_VERSION_BUILD
						DBC DB-LIB Library Version Number
						DBC DB-LIB library version number
						DBC DB-LIB Library Version
						DBC DB-LIB library version
						DBC DB-LIB Version Number
						DBC DB-LIB version number
						DBC DB-LIB Version
						DBC DB-LIB version

   PUBLISH NAME:	DBC_MSSQL_VERSION_MAJOR
						DBC_MSSQL_VERSION_MINOR
						DBC_MSSQL_VERSION_RELEASE
						DBC_MSSQL_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						DBC DB-LIB Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define DBC_MSSQL_VERSION_MAJOR			((unsigned char) 1)
#define DBC_MSSQL_VERSION_MINOR			((unsigned char) 0)
#define DBC_MSSQL_VERSION_RELEASE		((unsigned char) 0)
#define DBC_MSSQL_VERSION_BUILD			((unsigned char) 'A')
/*	***********************************************************************	*/

/*
	ADF NOTE:	No ADF.
*/
/*	***********************************************************************	*/
#define DBC_MSSQL_SERVER_NAME				0
#define DBC_MSSQL_DB_NAME					1
#define DBC_MSSQL_OWNER_NAME				2
#define DBC_MSSQL_USER_NAME				3
#define DBC_MSSQL_PASS_WORD				4
#define DBC_MSSQL_CONN_SPEC_COUNT		5
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_CONTROL

   DESCRIPTION :	The ''DBC_MSSQL_CONTROL'' structure contains the complete
						state necessary to the operation of the DBC DB-LIB facility
						library.

						The ''DBC_MSSQL_CONTROL'' structure is declared as follows:

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
} DBC_MSSQL_CONTROL;

	MEMBERS		:	The members of this structure are as follow:

						(.) ``dbc_funcs`` is a ''DBC_FUNCS'' structure which will
						be used to store the results of invoking the function
						``DBC_MSSQL_AttachFacility``.

						(.) ``server_ptr`` is the pointer to the Microsoft SQL Server ''LOGINREC''
						structure resulting from a call to ``dblogin()``.

						(.) ``database_ptr`` is the pointer to the Microsoft SQL Server
						''DBPROCESS'' structure resulting from a call to
						``dbopen()``.

						(.) ``mlog_ptr`` is a pointer to the
						''MLOG'' structure to be used for logging
						during operation of the facility.

						(.) ``db_debug_flag`` is an indication as to whether all
						Microsoft SQL Server DB-LIB server and client messages returned to the
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

   NOTES       :	A ''DBC_MSSQL_CONTROL'' structure may be created and
						initialized by calling the ``init`` function member of
						the ''DBC_FUNCS'' structure attached to your application.
						A ''DBC_MSSQL_CONTROL'' structure may be closed and its
						resources freed by calling the ``free`` function member of
						the ''DBC_FUNCS'' structure attached to your application.
						These functions are implemented in the DBC DB-LIB facility
						by the functions ``DBC_MSSQL_Initialize`` and
						``DBC_MSSQL_Close``, respectively.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_CONTROL
						DBC Structures and Data Types:DBC_MSSQL_CONTROL
						DBC DB-LIB Structures and Data Types:DBC_MSSQL_CONTROL
						Structures and Data Types:DBC_MSSQL_CONTROL

   PUBLISH XREF:	DBC_MSSQL_CONTROL

   PUBLISH NAME:	DBC_MSSQL_CONTROL

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
} DBC_MSSQL_CONTROL;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

   NAME        :	DBC_MSSQL_MSG

   DESCRIPTION :	The structure ''DBC_MSSQL_MSG'' supports the implementation
						of a stack of Microsoft SQL Server DB-LIB error and message handlers.

						The implementation of this structure is made necessary by
						the fact that there can be only one handler of either type
						active within a single process using DB-LIB.

						''DBC_MSSQL_MSG'' is declared as follows:

{|@|}typedef struct {
	int  (*err_handler)(DBPROCESS *, int, int, int, char *,
				char *);
	// ***** Declarations differ across Microsoft SQL Server versions . . . *****
#ifndef CS_PUBLIC
	int  (*msg_handler)(DBPROCESS *, DBINT, int, int, char *,
				char *, char *, DBUSMALLINT);
#else
	int  (*msg_handler)(DBPROCESS *, DBINT, int, int, char *,
				char *, char *, int);
#endif // # ifndef CS_PUBLIC
	MLOG  *mlog_ptr;
	int    db_debug_flag;
	char   msg_text[DBC_MAX_ERROR_TEXT];
	char   err_text[DBC_MAX_ERROR_TEXT];
} DBC_MSSQL_MSG;

						Note the '#ifndef CS_PUBLIC' block. This is necessary
						because DB-LIB prior to Microsoft SQL Server System 10 (such as 4.9.2)
						declared the last parameter of message handlers to be of
						type ''DBUSMALLINT'', whereas System 10 and subsequent
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
						Microsoft SQL Server DB-LIB server and client messages returned to the
						application program are to be logged using the
						``mlog_ptr`` member.

						(.) ``msg_text`` is an array of ''char'' in which is stored
						the text descriptive of the last message received by the
						message handler function.

						(.) ``err_text`` is an array of ''char'' in which is stored
						the text descriptive of the last message received by the
						error handler function.

   AUTHOR      :	Michael L. Brock

	COPYRIGHT	:	Copyright 1995 - 2014 Michael L. Brock

   OUTPUT INDEX:	DBC_MSSQL_MSG
						DBC Structures and Data Types:DBC_MSSQL_MSG
						DBC DB-LIB Structures and Data Types:DBC_MSSQL_MSG
						Structures and Data Types:DBC_MSSQL_MSG

   PUBLISH XREF:	DBC_MSSQL_MSG

   PUBLISH NAME:	DBC_MSSQL_MSG

	ENTRY CLASS	:	Structures and Data Types

EOH */
/*	***********************************************************************	*/
typedef struct {
#ifndef NARGS
	int  (*err_handler)(DBPROCESS *, int, int, int, char *,
				char *);
	/* ***** Declarations differ across Microsoft SQL Server versions . . . ***** */
# ifndef CS_PUBLIC
	int  (*msg_handler)(DBPROCESS *, DBINT, int, int, char *,
				char *, char *, DBUSMALLINT);
# else
	int  (*msg_handler)(DBPROCESS *, DBINT, int, int, char *,
				char *, char *, int);
# endif /* # ifndef CS_PUBLIC */
#else
	int  (*err_handler)();
	int  (*msg_handler)();
#endif /* #ifndef NARGS */
	MLOG  *mlog_ptr;
	int    db_debug_flag;
	char   msg_text[DBC_MAX_ERROR_TEXT];
	char   err_text[DBC_MAX_ERROR_TEXT];
} DBC_MSSQL_MSG;
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DB-LIB attachment function prototype . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_MSSQL_AttachFacility, (DBC_FUNCS *funcs_ptr));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DB-LIB facility exposed function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int          DBC_MSSQL_BindMembers,
	(DBC_MSSQL_CONTROL *dbc_control_ptr, unsigned int member_count,
	const MDDL *member_list, const char *table_name, void *bind_buffer,
	char *error_text));
COMPAT_FN_DECL(int          DBC_MSSQL_Cancel,
	(DBC_MSSQL_CONTROL *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_MSSQL_CancelAll,
	(DBC_MSSQL_CONTROL *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_MSSQL_CancelQuery,
	(DBC_MSSQL_CONTROL *dbc_control_ptr, char *error_text));
COMPAT_FN_DECL(void         DBC_MSSQL_Close,
	(DBC_MSSQL_CONTROL **dbc_control_ptr));
COMPAT_FN_DECL(int          DBC_MSSQL_Connect,
	(DBC_MSSQL_CONTROL *dbc_control_ptr, const char *app_name,
	const char *server_name, const char *database_name, const char *owner_name,
	const char *user_name, const char *pass_word, char *error_text));
COMPAT_FN_DECL(int          DBC_MSSQL_DoSQLCommand,
	(DBC_MSSQL_CONTROL *dbc_control_ptr, const char *sql_command,
	char *error_text));
COMPAT_FN_DECL(char        *DBC_MSSQL_GetID,
	(char *id_string));
COMPAT_FN_DECL(int          DBC_MSSQL_GetRows,
	(DBC_MSSQL_CONTROL *dbc_control_ptr, unsigned int member_count,
	const MDDL *member_list, const char *sql_command, const char *table_name,
	unsigned int *out_row_count, void **out_row_list,
	unsigned int out_row_size, unsigned int data_row_size,
	unsigned int data_row_offset, unsigned int max_row_count,
	unsigned int alloc_granularity, char *error_text));
COMPAT_FN_DECL(int          DBC_MSSQL_GetRowsBasic,
	(DBC_MSSQL_CONTROL *dbc_control_ptr, const DBC_GETROWS *get_rows_ptr,
	unsigned int *out_row_count, void **out_row_list, char *error_text));
COMPAT_FN_DECL(char        *DBC_MSSQL_GetVendorName,
	(char *vendor_name));
COMPAT_FN_DECL(STR_VERSION *DBC_MSSQL_GetVersion,
	(STR_VERSION *version_number));
COMPAT_FN_DECL(char        *DBC_MSSQL_GetVersionString,
	(char *version_string));
COMPAT_FN_DECL(int          DBC_MSSQL_Initialize,
	(DBC_CONTEXT *dbc_context_ptr, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(int          DBC_MSSQL_Open,
	(DBC_CONTEXT *dbc_context_ptr, const char *conn_type,
	const char *conn_string, MLOG *mlog_ptr, DBC_FLAG flags,
	void *user_data_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DB-LIB facility private function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int            DBC_MSSQL_MSG_DefaultHandler,
	(DBC_MSSQL_CONTROL *dbc_control_ptr, char *error_text));
	/* ***** Declarations differ across Microsoft SQL Server versions . . . ***** */
# ifndef CS_PUBLIC
COMPAT_FN_DECL(int            DBC_MSSQL_MSG_PushHandler,
	(int (*err_handler)(DBPROCESS *, int, int, int, char *, char *),
	int (*msg_handler)(DBPROCESS *, DBINT, int, int, char *, char *, char *,
		DBUSMALLINT), char *error_text));
# else
COMPAT_FN_DECL(int            DBC_MSSQL_MSG_PushHandler,
	(int (*err_handler)(DBPROCESS *, int, int, int, char *, char *),
	int (*msg_handler)(DBPROCESS *, DBINT, int, int, char *, char *, char *,
		int), char *error_text));
# endif /* # ifndef CS_PUBLIC */
COMPAT_FN_DECL(void           DBC_MSSQL_MSG_PopHandler,
	(void));
COMPAT_FN_DECL(void           DBC_MSSQL_MSG_ClearHandler,
	(void));
COMPAT_FN_DECL(DBC_MSSQL_MSG *DBC_MSSQL_MSG_GetHandlerPtr,
	(void));
COMPAT_FN_DECL(char          *DBC_MSSQL_MSG_GetHandlerMessage,
	(char *text_buffer));
COMPAT_FN_DECL(char          *DBC_MSSQL_MSG_GetHandlerMSGMessage,
	(char *text_buffer));
COMPAT_FN_DECL(char          *DBC_MSSQL_MSG_GetHandlerERRMessage,
	(char *text_buffer));
COMPAT_FN_DECL(int            DBC_MSSQL_MSG_HandleERR,
	(DBPROCESS *db_proc, int severity, int db_err, int os_err,
	char *db_err_string, char *os_err_string));
	/* ***** Declarations differ across Microsoft SQL Server versions . . . ***** */
# ifndef CS_PUBLIC
COMPAT_FN_DECL(int            DBC_MSSQL_MSG_HandleMSG,
	(DBPROCESS *db_proc, DBINT msg_number, int msg_state, int severity,
	char *msg_text, char *server_name, char *proc_name,
	DBUSMALLINT line_number));
# else
COMPAT_FN_DECL(int            DBC_MSSQL_MSG_HandleMSG,
	(DBPROCESS *db_proc, DBINT msg_number, int msg_state, int severity,
	char *msg_text, char *server_name, char *proc_name, int line_number));
# endif /* # ifndef CS_PUBLIC */
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCMSSQL_H__h */

