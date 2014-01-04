/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Header File				*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the generic Microsoft SQL Server
								support functions library.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCMSBAS_H__h

#define h__DBCMSBAS_H__h						1

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Include necessary header files . . .												*/
/*	***********************************************************************	*/

#ifdef _Windows
# include <windows.h>
#endif /* #ifdef _Windows */

#include <sqlfront.h>
#include <sqldb.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	BASE NAME	:	DBC Microsoft SQL Server Library Version Number

   NAME        :	DBC Microsoft SQL Server Library Version Number

   DESCRIPTION :	The DBC Microsoft SQL Server library version number manifest constants
						together define the current version number of the DBC Microsoft SQL Server
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
						DBC Microsoft SQL Server Version Numbers:Library Version Number
						DBC Microsoft SQL Server Library Version Number:DBC_MSSQL_VERSION_MAJOR
						DBC Microsoft SQL Server Library Version Number:DBC_MSSQL_VERSION_MINOR
						DBC Microsoft SQL Server Library Version Number:DBC_MSSQL_VERSION_RELEASE
						DBC Microsoft SQL Server Library Version Number:DBC_MSSQL_VERSION_BUILD
						DBC Macros and Manifest Constants:DBC_MSSQL_VERSION_MAJOR
						DBC Macros and Manifest Constants:DBC_MSSQL_VERSION_MINOR
						DBC Macros and Manifest Constants:DBC_MSSQL_VERSION_RELEASE
						DBC Macros and Manifest Constants:DBC_MSSQL_VERSION_BUILD
						DBC Microsoft SQL Server Macros and Manifest Constants:DBC_MSSQL_VERSION_MAJOR
						DBC Microsoft SQL Server Macros and Manifest Constants:DBC_MSSQL_VERSION_MINOR
						DBC Microsoft SQL Server Macros and Manifest Constants:DBC_MSSQL_VERSION_RELEASE
						DBC Microsoft SQL Server Macros and Manifest Constants:DBC_MSSQL_VERSION_BUILD
						Macros and Manifest Constants:DBC_MSSQL_VERSION_MAJOR
						Macros and Manifest Constants:DBC_MSSQL_VERSION_MINOR
						Macros and Manifest Constants:DBC_MSSQL_VERSION_RELEASE
						Macros and Manifest Constants:DBC_MSSQL_VERSION_BUILD
						Defines:See Macros and Manifest Constants

   PUBLISH XREF:	DBC_MSSQL_VERSION_MAJOR
						DBC_MSSQL_VERSION_MINOR
						DBC_MSSQL_VERSION_RELEASE
						DBC_MSSQL_VERSION_BUILD
						DBC Microsoft SQL Server Library Version Number
						DBC Microsoft SQL Server library version number
						DBC Microsoft SQL Server Library Version
						DBC Microsoft SQL Server library version
						DBC Microsoft SQL Server Version Number
						DBC Microsoft SQL Server version number
						DBC Microsoft SQL Server Version
						DBC Microsoft SQL Server version

   PUBLISH NAME:	DBC_MSSQL_VERSION_MAJOR
						DBC_MSSQL_VERSION_MINOR
						DBC_MSSQL_VERSION_RELEASE
						DBC_MSSQL_VERSION_BUILD

	ENTRY CLASS	:	Macros and Manifest Constants:Library Version Number
						DBC Microsoft SQL Server Version Numbers:Library Version Number

EOH */
/*	***********************************************************************	*/
#define DBC_MSSQL_VERSION_MAJOR			((unsigned char) 1)
#define DBC_MSSQL_VERSION_MINOR			((unsigned char) 0)
#define DBC_MSSQL_VERSION_RELEASE		((unsigned char) 0)
#define DBC_MSSQL_VERSION_BUILD			((unsigned char) 'A')
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#define DBC_MSSQL_MAX_ANY_NAME_LEN			MAXNAME
#define DBC_MSSQL_MAX_DB_NAME_LEN			DBC_MSSQL_MAX_ANY_NAME_LEN
#define DBC_MSSQL_MAX_COL_NAME_LEN			MAXCOLNAMELEN
#define DBC_MSSQL_MAX_TBL_NAME_LEN			MAXTABLENAME
#define DBC_MSSQL_MAX_SRV_NAME_LEN			MAXSERVERNAME
#define DBC_MSSQL_MAX_IDX_NAME_LEN			DBC_MSSQL_MAX_ANY_NAME_LEN
#define DBC_MSSQL_MAX_OWN_NAME_LEN			DBC_MSSQL_MAX_ANY_NAME_LEN
#define DBC_MSSQL_MAX_SEG_NAME_LEN			DBC_MSSQL_MAX_ANY_NAME_LEN
#define DBC_MSSQL_MAX_TYP_NAME_LEN			DBC_MSSQL_MAX_ANY_NAME_LEN
#define DBC_MSSQL_MAX_DEF_NAME_LEN			DBC_MSSQL_MAX_ANY_NAME_LEN
#define DBC_MSSQL_MAX_RUL_NAME_LEN			DBC_MSSQL_MAX_ANY_NAME_LEN
#define DBC_MSSQL_MAX_BND_NAME_LEN			DBC_MSSQL_MAX_ANY_NAME_LEN
/*	***********************************************************************	*/

#define DBC_MSSQL_MAX_IDX_COLS				16

typedef struct {
   char name[DBC_MSSQL_MAX_ANY_NAME_LEN + 1];
} DBC_MSSQL_NAME;

/*
	From the columns in 'master.dbo.sysdatabases' of the same names.
*/
typedef struct {
	char       name[DBC_MSSQL_MAX_DB_NAME_LEN + 1];
	short      dbid;
	short      suid;
/*
	The 'mode' column is not in 'master.dbo.sysdatabases' in System 10.
	short      mode;
*/
	short      status;
	short      version;
	long       logptr;
	DBDATETIME crdate;
	DBDATETIME dumptrdate;
} DBC_MSSQL_DB_DB;

typedef struct {
	char       name[DBC_MSSQL_MAX_DB_NAME_LEN + 1];
	short      id;
	short      user_id;
/*
	The 'mode' column is not in 'master.dbo.sysdatabases' in System 10.
	int        mode;
*/
	short      status;
	short      version;
	long       log_ptr;
	DBDATETIME creation_date;
	DBDATETIME dumptr_date;
	int        select_into_flag;
	int        truncate_on_chkpoint_flag;
	int        no_chkpoint_on_recovery_flag;
	int        crashed_while_loading_flag;
	int        suspect_flag;
	int        read_only_flag;
	int        owner_only_flag;
	int        single_user_flag;
	int        name_changed_flag;
} DBC_MSSQL_DB;

/*
	ADF NOTE: To be included.
type			 ---> <database>.dbo.systypes.type
table_type	 ---> <database>.dbo.syscolumns.type
user_type	 ---> <database>.dbo.syscolumns.usertype
name			 ---> <database>.dbo.syscolumns.name
length		 ---> <database>.dbo.syscolumns.length
type_name	 ---> <database>.dbo.systypes.name
offset		 ---> <database>.dbo.syscolumns.offset
default_name ---> object_name(<database>.dbo.syscolumns.cdefault)
rule_name	 ---> object_name(<database>.dbo.syscolumns.domain)
status		 ---> <database>.dbo.syscolumns.status
basic_type   ---> Is a calculated value mapped from 'type':
									If 'SQLVARCHAR', then 'SQLCHAR'
									If 'SQLVARBINARY', then 'SQLBINARY'
									If 'SQLDATETIMN', then 'SQLDATETIME'
									If 'SQLMONEYN', then 'SQLMONEY'
									If 'SQLFLTN', then 'SQLFLT8'
									If 'SQLINTN' and length=1, then 'SQLINT1'
									If 'SQLINTN' and length=2, then 'SQLINT2'
									If 'SQLINTN' and length=4, then 'SQLINT4'
									Otherwise, same as 'type'.
*/
typedef struct {
	unsigned char type;
	unsigned char table_type;
	short         user_type;
   char          name[DBC_MSSQL_MAX_COL_NAME_LEN + 1];
	unsigned char length;
	char          type_name[DBC_MSSQL_MAX_TYP_NAME_LEN + 1];
	short         offset;
	char          default_name[DBC_MSSQL_MAX_DEF_NAME_LEN + 1];
	char          rule_name[DBC_MSSQL_MAX_RUL_NAME_LEN + 1];
	unsigned char status;
	int           basic_type;
} DBC_MSSQL_DB_COL;

typedef struct {
	char             name[DBC_MSSQL_MAX_COL_NAME_LEN + 1];
	char             type_name[DBC_MSSQL_MAX_TYP_NAME_LEN + 1];
	char             bind_name[DBC_MSSQL_MAX_BND_NAME_LEN + 1];
	int              type;
	int              length;
	int              array_length;
	int              vary;
	int              nullable_flag;
	unsigned int     flag_bit_position;
	unsigned int     type_count;
	char             type_spec[31 + 1];
	DBC_MSSQL_DB_COL column_data;
} DBC_MSSQL_COL;

typedef struct {
	int          type;
	int          type_length;
	char         name[DBC_MSSQL_MAX_TYP_NAME_LEN + 1];
	char         bind[DBC_MSSQL_MAX_BND_NAME_LEN + 1];
	unsigned int type_count;
	char         type_spec[31 + 1];
} DBC_MSSQL_TYPE;

/*
	ADF NOTE: To be included.
index_name		---> <database>.dbo.sysindexes.name
index_id			---> <database>.dbo.sysindexes.indid
key_count		---> <database>.dbo.sysindexes.keycnt
column_name		---> <database>.dbo.syscolumns.name
column_order	---> Calculated starting at '1'.
column_id		---> <database>.dbo.syscolumns.colid
status			---> <database>.dbo.sysindexes.status
segment_number	---> <database>.dbo.syssegments.segment
segment_name	---> <database>.dbo.syssegments.name
*/
typedef struct {
	char          index_name[DBC_MSSQL_MAX_IDX_NAME_LEN + 1];
	short         index_id;
	short         key_count;
	char          column_name[DBC_MSSQL_MAX_COL_NAME_LEN + 1];
	unsigned char column_order;
	unsigned char column_id;
	short         status;
	short         segment_number;
	char          segment_name[DBC_MSSQL_MAX_SEG_NAME_LEN + 1];
} DBC_MSSQL_DB_IDX;

typedef struct {
	char              index_name[DBC_MSSQL_MAX_IDX_NAME_LEN + 1];
	int               index_id;
	int               key_count;
	int               status;
	int               unique_index_flag;
	int               clustered_index_flag;
	int               ignore_dup_key_flag;
	int               ignore_dup_row_flag;
	int               allow_dup_row_flag;
	int               segment_number;
	char              segment_name[DBC_MSSQL_MAX_SEG_NAME_LEN + 1];
	unsigned int      fill_factor;
	unsigned int      column_count;
	DBC_MSSQL_COL column_list[DBC_MSSQL_MAX_IDX_COLS];
} DBC_MSSQL_IDX;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

COMPAT_EXTERN_DATA_DECL const DBC_MSSQL_TYPE  DBC_MSSQL_TypeList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_MSSQL_TypeCount;

COMPAT_EXTERN_DATA_DECL const MDDL          DBC_MSSQL_GetNameMemberList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_MSSQL_GetNameMemberCount;

COMPAT_EXTERN_DATA_DECL const MDDL          DBC_MSSQL_GetDBColMemberList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_MSSQL_GetDBColMemberCount;

COMPAT_EXTERN_DATA_DECL const MDDL          DBC_MSSQL_GetDBIdxMemberList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_MSSQL_GetDBIdxMemberCount;

COMPAT_EXTERN_DATA_DECL const MDDL          DBC_MSSQL_GetDBDBMemberList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_MSSQL_GetDBDBMemberCount;

COMPAT_EXTERN_DATA_DECL const char         *DBC_MSSQL_SystemDBList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_MSSQL_SystemDBCount;

COMPAT_EXTERN_DATA_DECL const char         *DBC_MSSQL_SystemTableList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_MSSQL_SystemTableCount;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_TYPE function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(const DBC_MSSQL_TYPE *DBC_MSSQL_FIND_TypeByType,
	(int in_type, unsigned int *found_index));
COMPAT_FN_DECL(const DBC_MSSQL_TYPE *DBC_MSSQL_FIND_TypeByNames,
	(const char *in_name, const char *in_bind, unsigned int *found_index));
COMPAT_FN_DECL(const DBC_MSSQL_TYPE *DBC_MSSQL_FIND_TypeByTypeSpec,
	(const char *in_type_spec, unsigned int *found_index));
COMPAT_FN_DECL(int DBC_MSSQL_MapTypeToMDDL, (DBC_BASIC_TYPE dbc_basic_type,
	MDDL *mddl_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_DB_COL retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_GetDBColumn, (const char *spec_string,
	const char *table_name, unsigned int *column_count,
	DBC_MSSQL_DB_COL **column_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetDBColumnBasic, (void *dbc_control_ptr,
	const char *table_name, unsigned int *column_count,
	DBC_MSSQL_DB_COL **column_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_COL retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_GetColumn, (const char *spec_string,
	const char *table_name, unsigned int *column_count,
	DBC_MSSQL_COL **column_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetColumnBasic, (void *dbc_control_ptr,
	const char *table_name, unsigned int *column_count,
	DBC_MSSQL_COL **column_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_DB_IDX retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_GetDBIndex, (const char *spec_string,
	const char *table_name, unsigned int *index_count,
	DBC_MSSQL_DB_IDX **index_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetDBIndexBasic, (void *dbc_control_ptr,
	const char *table_name, unsigned int *index_count,
	DBC_MSSQL_DB_IDX **index_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_IDX retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_GetIndex, (const char *spec_string,
	const char *table_name, unsigned int *index_count,
	DBC_MSSQL_IDX **index_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetIndexBasic, (void *dbc_control_ptr,
	const char *table_name, unsigned int *index_count,
	DBC_MSSQL_IDX **index_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_DB_DB retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_GetDBDB, (const char *spec_string,
	unsigned int *database_count, DBC_MSSQL_DB_DB **database_list,
	char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetDBDBBasic, (void *dbc_control_ptr,
	unsigned int *database_count, DBC_MSSQL_DB_DB **database_list,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_DB retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_GetDB, (const char *spec_string,
	unsigned int *database_count, DBC_MSSQL_DB **database_list,
	char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetDBBasic, (void *dbc_control_ptr,
	unsigned int *database_count, DBC_MSSQL_DB **database_list,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_NAME retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_GetName, (const char *spec_string,
	const char *sql_command, unsigned int *name_count, DBC_MSSQL_NAME *name_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetNameBasic, (void *dbc_control_ptr,
	const char *sql_command, unsigned int *name_count, DBC_MSSQL_NAME *name_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetNameList, (const char *spec_string,
	const char *sql_command, unsigned int *name_count,
	DBC_MSSQL_NAME **name_list, unsigned int max_row_count, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetNameListBasic, (void *dbc_control_ptr,
	const char *sql_command, unsigned int *name_count,
	DBC_MSSQL_NAME **name_list, unsigned int max_row_count, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_NAME table retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_GetTableName, (const char *spec_string,
	const char *in_database_name, unsigned int *name_count,
	DBC_MSSQL_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetTableNameBasic, (void *dbc_control_ptr,
	const char *in_database_name, unsigned int *name_count,
	DBC_MSSQL_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetUserTableName, (const char *spec_string,
	const char *in_database_name, unsigned int *name_count,
	DBC_MSSQL_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetUserTableNameBasic, (void *dbc_control_ptr,
	const char *in_database_name, unsigned int *name_count,
	DBC_MSSQL_NAME **name_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_NAME database retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_GetDBName, (const char *spec_string,
	unsigned int *name_count, DBC_MSSQL_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetDBNameBasic, (void *dbc_control_ptr,
	unsigned int *name_count, DBC_MSSQL_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetUserDBName, (const char *spec_string,
	unsigned int *name_count, DBC_MSSQL_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_GetUserDBNameBasic, (void *dbc_control_ptr,
	unsigned int *name_count, DBC_MSSQL_NAME **name_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_DB_COL emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBColumnList, (unsigned int count,
	const DBC_MSSQL_DB_COL *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBColumnListIdx, (unsigned int count,
	const DBC_MSSQL_DB_COL *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBColumn, (const DBC_MSSQL_DB_COL *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBColumnHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBColumnTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_COL emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_ColumnList, (unsigned int count,
	const DBC_MSSQL_COL *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_ColumnListIdx, (unsigned int count,
	const DBC_MSSQL_COL *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_Column, (const DBC_MSSQL_COL *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_ColumnHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_ColumnTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_DB_IDX emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBIndexList, (unsigned int count,
	const DBC_MSSQL_DB_IDX *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBIndexListIdx, (unsigned int count,
	const DBC_MSSQL_DB_IDX *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBIndex, (const DBC_MSSQL_DB_IDX *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBIndexHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBIndexTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_IDX emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_IndexList, (unsigned int count,
	const DBC_MSSQL_IDX *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_IndexListIdx, (unsigned int count,
	const DBC_MSSQL_IDX *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_Index, (const DBC_MSSQL_IDX *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_IndexHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_IndexTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_DB_DB emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBDBList, (unsigned int count,
	const DBC_MSSQL_DB_DB *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBDBListIdx, (unsigned int count,
	const DBC_MSSQL_DB_DB *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBDB, (const DBC_MSSQL_DB_DB *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBDBHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBDBTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_MSSQL_DB emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBList, (unsigned int count,
	const DBC_MSSQL_DB *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBListIdx, (unsigned int count,
	const DBC_MSSQL_DB *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DB, (const DBC_MSSQL_DB *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_MSSQL_EMIT_DBTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Database and table name function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_BreakDatabaseName, (const char *in_database_name,
	char *out_database_name, char *out_owner_name, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_BreakTableName, (const char *in_table_name,
	char *out_database_name, char *out_owner_name, char *out_table_name,
	char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_DefaultDatabaseName,
	(const char *in_database_name, const char *default_database_name,
	const char *default_owner_name, char *out_database_name,
	char *out_owner_name, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_DefaultTableName,
	(const char *in_table_name, const char *default_database_name,
	const char *default_owner_name, char *out_database_name,
	char *out_owner_name, char *out_table_name, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Miscellaneous function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_ColumnsToMembers, (unsigned int column_count,
	const DBC_MSSQL_COL *column_list, unsigned int *structure_size,
	unsigned int *member_count, MDDL **member_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_ParseConn, (const char *conn_type,
	const char *conn_string, unsigned int *parsed_count, char ***parsed_list,
	char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_TableToMembers, (void *dbc_control_ptr,
	const char *in_table_name, unsigned int *structure_size,
	unsigned int *member_count, MDDL **member_list, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_IsSystemDatabase, (const char *database_name));
COMPAT_FN_DECL(int DBC_MSSQL_IsSystemTable, (const char *table_name));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Miscellaneous function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(STR_VERSION *DBC_MSSQL_GetVersion, (STR_VERSION *version_number));
COMPAT_FN_DECL(char        *DBC_MSSQL_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MDDL function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int  DBC_MSSQL_SetDisplayLength, (unsigned int type_count,
	const DTA_TYPE *type_list, MDDL *member_ptr, int header_flag,
	unsigned int null_string_length, unsigned int intra_field_sep_length,
	void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(void DBC_MSSQL_DumpField, (unsigned int type_count,
	const DTA_TYPE *type_list, const MDDL *member_ptr,
	const void *record_ptr, int null_flag, const char *null_string,
	const char *intra_field_sep, const char *overflow_char,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Microsoft SQL Server date comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_CMP_DBDATETIME4, (const DBDATETIM4 *ptr_1,
	const DBDATETIM4 *ptr_2));
COMPAT_FN_DECL(int DBC_MSSQL_CMP_DBDATETIME, (const DBDATETIME *ptr_1,
	const DBDATETIME *ptr_2));
COMPAT_FN_DECL(int DBC_MSSQL_SCMP_DBDATETIME4, (void *control_ptr,
	const DBDATETIM4 *ptr_1, const DBDATETIM4 *ptr_2, size_t data_length));
COMPAT_FN_DECL(int DBC_MSSQL_SCMP_DBDATETIME, (void *control_ptr,
	const DBDATETIME *ptr_1, const DBDATETIME *ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Microsoft SQL Server date conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(DBDATETIM4 *DBC_MSSQL_DTIMEToMSSQL4,
	(const DTIME *in_date, DBDATETIM4 *out_date));
COMPAT_FN_DECL(DBDATETIME *DBC_MSSQL_DTIMEToMSSQL8,
	(const DTIME *in_date, DBDATETIME *out_date));
COMPAT_FN_DECL(DTIME      *DBC_MSSQL_MSSQL4ToDTIME,
	(const DBDATETIM4 *in_date, DTIME *out_date));
COMPAT_FN_DECL(DTIME      *DBC_MSSQL_MSSQL8ToDTIME,
	(const DBDATETIME *in_date, DTIME *out_date));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Microsoft SQL Server money type conversion functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(double    DBC_MSSQL_DBMONEYToDouble,
	(const DBMONEY *in_dbmoney));
COMPAT_FN_DECL(double    DBC_MSSQL_DBMONEY4ToDouble,
	(const DBMONEY4 *in_dbmoney4));
COMPAT_FN_DECL(DBMONEY  *DBC_MSSQL_DoubleToDBMONEY,
	(double in_double, DBMONEY *out_dbmoney));
COMPAT_FN_DECL(DBMONEY4 *DBC_MSSQL_DoubleToDBMONEY4,
	(double in_double, DBMONEY4 *out_dbmoney4));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC numeric-to-generic conversion functions prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_DoubleToNumber, (int dbc_type, double double_value,
	void *number_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_NumberToDouble, (int dbc_type,
	const void *number_ptr, double *double_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC date-to-generic conversion functions prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_DTIMEToDate, (int dbc_type, const DTIME *dtime_ptr,
	void *date_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_DateToDTIME, (int dbc_type, const void *date_ptr,
	DTIME *dtime_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC time-to-generic conversion functions prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_DTIMEToTime, (int dbc_type, const DTIME *dtime_ptr,
	void *time_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_TimeToDTIME, (int dbc_type, const void *time_ptr,
	DTIME *dtime_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC miscellaneous generic numeric function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_IsNumber, (int dbc_type));
COMPAT_FN_DECL(int DBC_MSSQL_MinNumber, (int dbc_type, double *double_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_MaxNumber, (int dbc_type, double *double_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC miscellaneous generic date function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_IsDate, (int dbc_type));
COMPAT_FN_DECL(int DBC_MSSQL_MinDate, (int dbc_type, DTIME *dtime_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_MaxDate, (int dbc_type, DTIME *dtime_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC miscellaneous generic time function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_IsTime, (int dbc_type));
COMPAT_FN_DECL(int DBC_MSSQL_MinTime, (int dbc_type, DTIME *dtime_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_MSSQL_MaxTime, (int dbc_type, DTIME *dtime_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC generic numeric comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_CMP_Number, (int dbc_type, const void *ptr_1,
	const void *ptr_2));
COMPAT_FN_DECL(int DBC_MSSQL_SCMP_Number, (void *control_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC generic date comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_CMP_Date, (int dbc_type, const void *ptr_1,
	const void *ptr_2));
COMPAT_FN_DECL(int DBC_MSSQL_SCMP_Date, (void *control_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC generic time comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_MSSQL_CMP_Time, (int dbc_type, const void *ptr_1,
	const void *ptr_2));
COMPAT_FN_DECL(int DBC_MSSQL_SCMP_Time, (void *control_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Microsoft SQL Server data-type SQL conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int   DBC_MSSQL_FMT_Data_SQL, (int sybase_type,
	unsigned int data_length, const void *data_ptr, char *out_string,
	char *error_text));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLBINARY_SQL, (unsigned int data_length,
	const void *data_ptr, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLIMAGE_SQL, (unsigned int data_length,
	const void *data_ptr, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLBIT_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLCHAR_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLTEXT_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLINT1_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLINT2_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLINT4_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLREAL_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLFLT8_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLMONEY_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLMONEY4_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLDATETIME_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLDATETIME4_SQL, (const void *data_ptr,
	char *out_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Microsoft SQL Server data-type general conversion function
		prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int   DBC_MSSQL_FMT_Data, (int sybase_type,
	unsigned int data_length, const void *data_ptr, unsigned int min_length,
	unsigned int max_length, int right_justify_flag,
	unsigned int decimal_places, char *out_string, char *error_text));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLBINARY, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLIMAGE, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLBIT, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, const char *true_string, const char *false_string,
	char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLCHAR, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLTEXT, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLINT1, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLINT2, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLINT4, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLREAL, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, unsigned int decimal_places, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLFLT8, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, unsigned int decimal_places, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLMONEY, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, unsigned int decimal_places, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLMONEY4, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, unsigned int decimal_places, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLDATETIME, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, const char *date_format, char *out_string));
COMPAT_FN_DECL(char *DBC_MSSQL_FMT_SQLDATETIME4, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, const char *date_format, char *out_string));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCMSBAS_H__h */

