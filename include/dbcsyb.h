/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Header File						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Include file for the generic Sybase support functions
								library.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

#ifndef h__DBCSYB_H__h

#define h__DBCSYB_H__h						1

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

/*	***********************************************************************	*/
#define DBC_SYB_MAX_ANY_NAME_LEN			DBMAXNAME
#define DBC_SYB_MAX_DB_NAME_LEN			DBC_SYB_MAX_ANY_NAME_LEN
#define DBC_SYB_MAX_COL_NAME_LEN			DBC_SYB_MAX_ANY_NAME_LEN
#define DBC_SYB_MAX_TBL_NAME_LEN			DBC_SYB_MAX_ANY_NAME_LEN
#define DBC_SYB_MAX_SRV_NAME_LEN			DBC_SYB_MAX_ANY_NAME_LEN
#define DBC_SYB_MAX_IDX_NAME_LEN			DBC_SYB_MAX_ANY_NAME_LEN
#define DBC_SYB_MAX_OWN_NAME_LEN			DBC_SYB_MAX_ANY_NAME_LEN
#define DBC_SYB_MAX_SEG_NAME_LEN			DBC_SYB_MAX_ANY_NAME_LEN
#define DBC_SYB_MAX_TYP_NAME_LEN			DBC_SYB_MAX_ANY_NAME_LEN
#define DBC_SYB_MAX_DEF_NAME_LEN			DBC_SYB_MAX_ANY_NAME_LEN
#define DBC_SYB_MAX_RUL_NAME_LEN			DBC_SYB_MAX_ANY_NAME_LEN
#define DBC_SYB_MAX_BND_NAME_LEN			DBC_SYB_MAX_ANY_NAME_LEN
/*	***********************************************************************	*/

#define DBC_SYB_MAX_IDX_COLS				16

typedef struct {
   char name[DBC_SYB_MAX_ANY_NAME_LEN + 1];
} DBC_SYB_NAME;

/*
	From the columns in 'master.dbo.sysdatabases' of the same names.
*/
typedef struct {
	char       name[DBC_SYB_MAX_DB_NAME_LEN + 1];
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
} DBC_SYB_DB_DB;

typedef struct {
	char       name[DBC_SYB_MAX_DB_NAME_LEN + 1];
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
} DBC_SYB_DB;

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
									If 'SYBVARCHAR', then 'SYBCHAR'
									If 'SYBVARBINARY', then 'SYBBINARY'
									If 'SYBDATETIMN', then 'SYBDATETIME'
									If 'SYBMONEYN', then 'SYBMONEY'
									If 'SYBFLTN', then 'SYBFLT8'
									If 'SYBINTN' and length=1, then 'SYBINT1'
									If 'SYBINTN' and length=2, then 'SYBINT2'
									If 'SYBINTN' and length=4, then 'SYBINT4'
									Otherwise, same as 'type'.
*/
typedef struct {
	unsigned char type;
	unsigned char table_type;
	short         user_type;
   char          name[DBC_SYB_MAX_COL_NAME_LEN + 1];
	unsigned char length;
	char          type_name[DBC_SYB_MAX_TYP_NAME_LEN + 1];
	short         offset;
	char          default_name[DBC_SYB_MAX_DEF_NAME_LEN + 1];
	char          rule_name[DBC_SYB_MAX_RUL_NAME_LEN + 1];
	unsigned char status;
	int           basic_type;
} DBC_SYB_DB_COL;

typedef struct {
	char             name[DBC_SYB_MAX_COL_NAME_LEN + 1];
	char             type_name[DBC_SYB_MAX_TYP_NAME_LEN + 1];
	char             bind_name[DBC_SYB_MAX_BND_NAME_LEN + 1];
	int              type;
	int              length;
	int              array_length;
	int              vary;
	int              nullable_flag;
	unsigned int     flag_bit_position;
	unsigned int     type_count;
	char             type_spec[31 + 1];
	DBC_SYB_DB_COL column_data;
} DBC_SYB_COL;

typedef struct {
	int          type;
	int          type_length;
	char         name[DBC_SYB_MAX_TYP_NAME_LEN + 1];
	char         bind[DBC_SYB_MAX_BND_NAME_LEN + 1];
	unsigned int type_count;
	char         type_spec[31 + 1];
} DBC_SYB_TYPE;

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
	char          index_name[DBC_SYB_MAX_IDX_NAME_LEN + 1];
	short         index_id;
	short         key_count;
	char          column_name[DBC_SYB_MAX_COL_NAME_LEN + 1];
	unsigned char column_order;
	unsigned char column_id;
	short         status;
	short         segment_number;
	char          segment_name[DBC_SYB_MAX_SEG_NAME_LEN + 1];
} DBC_SYB_DB_IDX;

typedef struct {
	char              index_name[DBC_SYB_MAX_IDX_NAME_LEN + 1];
	int               index_id;
	int               key_count;
	int               status;
	int               unique_index_flag;
	int               clustered_index_flag;
	int               ignore_dup_key_flag;
	int               ignore_dup_row_flag;
	int               allow_dup_row_flag;
	int               segment_number;
	char              segment_name[DBC_SYB_MAX_SEG_NAME_LEN + 1];
	unsigned int      fill_factor;
	unsigned int      column_count;
	DBC_SYB_COL column_list[DBC_SYB_MAX_IDX_COLS];
} DBC_SYB_IDX;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

COMPAT_EXTERN_DATA_DECL const DBC_SYB_TYPE  DBC_SYB_TypeList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_SYB_TypeCount;

COMPAT_EXTERN_DATA_DECL const MDDL          DBC_SYB_GetNameMemberList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_SYB_GetNameMemberCount;

COMPAT_EXTERN_DATA_DECL const MDDL          DBC_SYB_GetDBColMemberList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_SYB_GetDBColMemberCount;

COMPAT_EXTERN_DATA_DECL const MDDL          DBC_SYB_GetDBIdxMemberList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_SYB_GetDBIdxMemberCount;

COMPAT_EXTERN_DATA_DECL const MDDL          DBC_SYB_GetDBDBMemberList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_SYB_GetDBDBMemberCount;

COMPAT_EXTERN_DATA_DECL const char         *DBC_SYB_SystemDBList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_SYB_SystemDBCount;

COMPAT_EXTERN_DATA_DECL const char         *DBC_SYB_SystemTableList[];
COMPAT_EXTERN_DATA_DECL const unsigned int  DBC_SYB_SystemTableCount;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Function prototypes . . .															*/
/*	***********************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_TYPE function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(const DBC_SYB_TYPE *DBC_SYB_FIND_TypeByType,
	(int in_type, unsigned int *found_index));
COMPAT_FN_DECL(const DBC_SYB_TYPE *DBC_SYB_FIND_TypeByNames,
	(const char *in_name, const char *in_bind, unsigned int *found_index));
COMPAT_FN_DECL(const DBC_SYB_TYPE *DBC_SYB_FIND_TypeByTypeSpec,
	(const char *in_type_spec, unsigned int *found_index));
COMPAT_FN_DECL(int DBC_SYB_MapTypeToMDDL, (DBC_BASIC_TYPE dbc_basic_type,
	MDDL *mddl_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_DB_COL retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_GetDBColumn, (const char *spec_string,
	const char *table_name, unsigned int *column_count,
	DBC_SYB_DB_COL **column_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetDBColumnBasic, (void *dbc_control_ptr,
	const char *table_name, unsigned int *column_count,
	DBC_SYB_DB_COL **column_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_COL retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_GetColumn, (const char *spec_string,
	const char *table_name, unsigned int *column_count,
	DBC_SYB_COL **column_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetColumnBasic, (void *dbc_control_ptr,
	const char *table_name, unsigned int *column_count,
	DBC_SYB_COL **column_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_DB_IDX retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_GetDBIndex, (const char *spec_string,
	const char *table_name, unsigned int *index_count,
	DBC_SYB_DB_IDX **index_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetDBIndexBasic, (void *dbc_control_ptr,
	const char *table_name, unsigned int *index_count,
	DBC_SYB_DB_IDX **index_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_IDX retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_GetIndex, (const char *spec_string,
	const char *table_name, unsigned int *index_count,
	DBC_SYB_IDX **index_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetIndexBasic, (void *dbc_control_ptr,
	const char *table_name, unsigned int *index_count,
	DBC_SYB_IDX **index_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_DB_DB retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_GetDBDB, (const char *spec_string,
	unsigned int *database_count, DBC_SYB_DB_DB **database_list,
	char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetDBDBBasic, (void *dbc_control_ptr,
	unsigned int *database_count, DBC_SYB_DB_DB **database_list,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_DB retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_GetDB, (const char *spec_string,
	unsigned int *database_count, DBC_SYB_DB **database_list,
	char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetDBBasic, (void *dbc_control_ptr,
	unsigned int *database_count, DBC_SYB_DB **database_list,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_NAME retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_GetName, (const char *spec_string,
	const char *sql_command, unsigned int *name_count, DBC_SYB_NAME *name_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetNameBasic, (void *dbc_control_ptr,
	const char *sql_command, unsigned int *name_count, DBC_SYB_NAME *name_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetNameList, (const char *spec_string,
	const char *sql_command, unsigned int *name_count,
	DBC_SYB_NAME **name_list, unsigned int max_row_count, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetNameListBasic, (void *dbc_control_ptr,
	const char *sql_command, unsigned int *name_count,
	DBC_SYB_NAME **name_list, unsigned int max_row_count, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_NAME table retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_GetTableName, (const char *spec_string,
	const char *in_database_name, unsigned int *name_count,
	DBC_SYB_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetTableNameBasic, (void *dbc_control_ptr,
	const char *in_database_name, unsigned int *name_count,
	DBC_SYB_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetUserTableName, (const char *spec_string,
	const char *in_database_name, unsigned int *name_count,
	DBC_SYB_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetUserTableNameBasic, (void *dbc_control_ptr,
	const char *in_database_name, unsigned int *name_count,
	DBC_SYB_NAME **name_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_NAME database retrieval function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_GetDBName, (const char *spec_string,
	unsigned int *name_count, DBC_SYB_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetDBNameBasic, (void *dbc_control_ptr,
	unsigned int *name_count, DBC_SYB_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetUserDBName, (const char *spec_string,
	unsigned int *name_count, DBC_SYB_NAME **name_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_GetUserDBNameBasic, (void *dbc_control_ptr,
	unsigned int *name_count, DBC_SYB_NAME **name_list, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_DB_COL emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBColumnList, (unsigned int count,
	const DBC_SYB_DB_COL *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBColumnListIdx, (unsigned int count,
	const DBC_SYB_DB_COL *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBColumn, (const DBC_SYB_DB_COL *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBColumnHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBColumnTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_COL emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_SYB_EMIT_ColumnList, (unsigned int count,
	const DBC_SYB_COL *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_ColumnListIdx, (unsigned int count,
	const DBC_SYB_COL *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_Column, (const DBC_SYB_COL *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_ColumnHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_ColumnTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_DB_IDX emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBIndexList, (unsigned int count,
	const DBC_SYB_DB_IDX *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBIndexListIdx, (unsigned int count,
	const DBC_SYB_DB_IDX *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBIndex, (const DBC_SYB_DB_IDX *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBIndexHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBIndexTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_IDX emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_SYB_EMIT_IndexList, (unsigned int count,
	const DBC_SYB_IDX *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_IndexListIdx, (unsigned int count,
	const DBC_SYB_IDX *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_Index, (const DBC_SYB_IDX *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_IndexHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_IndexTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_DB_DB emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBDBList, (unsigned int count,
	const DBC_SYB_DB_DB *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBDBListIdx, (unsigned int count,
	const DBC_SYB_DB_DB *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBDB, (const DBC_SYB_DB_DB *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBDBHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBDBTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC_SYB_DB emit function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBList, (unsigned int count,
	const DBC_SYB_DB *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBListIdx, (unsigned int count,
	const DBC_SYB_DB *list, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DB, (const DBC_SYB_DB *ptr,
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBHeader, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
COMPAT_FN_DECL(void DBC_SYB_EMIT_DBTrailer, (
	STR_FUNC_TYPE_fprintf output_function, void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Database and table name function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_BreakDatabaseName, (const char *in_database_name,
	char *out_database_name, char *out_owner_name, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_BreakTableName, (const char *in_table_name,
	char *out_database_name, char *out_owner_name, char *out_table_name,
	char *error_text));
COMPAT_FN_DECL(int DBC_SYB_DefaultDatabaseName,
	(const char *in_database_name, const char *default_database_name,
	const char *default_owner_name, char *out_database_name,
	char *out_owner_name, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_DefaultTableName,
	(const char *in_table_name, const char *default_database_name,
	const char *default_owner_name, char *out_database_name,
	char *out_owner_name, char *out_table_name, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Miscellaneous function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_ColumnsToMembers, (unsigned int column_count,
	const DBC_SYB_COL *column_list, unsigned int *structure_size,
	unsigned int *member_count, MDDL **member_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_ParseConn, (const char *conn_type,
	const char *conn_string, unsigned int *parsed_count, char ***parsed_list,
	char *error_text));
COMPAT_FN_DECL(int DBC_SYB_TableToMembers, (void *dbc_control_ptr,
	const char *in_table_name, unsigned int *structure_size,
	unsigned int *member_count, MDDL **member_list, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_IsSystemDatabase, (const char *database_name));
COMPAT_FN_DECL(int DBC_SYB_IsSystemTable, (const char *table_name));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Miscellaneous function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(STR_VERSION *DBC_SYB_GetVersion, (STR_VERSION *version_number));
COMPAT_FN_DECL(char        *DBC_SYB_GetVersionString, (char *version_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		MDDL function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int  DBC_SYB_SetDisplayLength, (unsigned int type_count,
	const DTA_TYPE *type_list, MDDL *member_ptr, int header_flag,
	unsigned int null_string_length, unsigned int intra_field_sep_length,
	void *user_data_ptr, char *error_text));
COMPAT_FN_DECL(void DBC_SYB_DumpField, (unsigned int type_count,
	const DTA_TYPE *type_list, const MDDL *member_ptr,
	const void *record_ptr, int null_flag, const char *null_string,
	const char *intra_field_sep, const char *overflow_char,
	void *user_data_ptr, STR_FUNC_TYPE_fprintf output_function,
	void *output_control));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sybase date comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_CMP_DBDATETIME4, (const DBDATETIME4 *ptr_1,
	const DBDATETIME4 *ptr_2));
COMPAT_FN_DECL(int DBC_SYB_CMP_DBDATETIME, (const DBDATETIME *ptr_1,
	const DBDATETIME *ptr_2));
COMPAT_FN_DECL(int DBC_SYB_SCMP_DBDATETIME4, (void *control_ptr,
	const DBDATETIME4 *ptr_1, const DBDATETIME4 *ptr_2, size_t data_length));
COMPAT_FN_DECL(int DBC_SYB_SCMP_DBDATETIME, (void *control_ptr,
	const DBDATETIME *ptr_1, const DBDATETIME *ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sybase date conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(DBDATETIME4 *DBC_SYB_DTIMEToSybase4,
	(const DTIME *in_date, DBDATETIME4 *out_date));
COMPAT_FN_DECL(DBDATETIME  *DBC_SYB_DTIMEToSybase8,
	(const DTIME *in_date, DBDATETIME *out_date));
COMPAT_FN_DECL(DTIME       *DBC_SYB_Sybase4ToDTIME,
	(const DBDATETIME4 *in_date, DTIME *out_date));
COMPAT_FN_DECL(DTIME       *DBC_SYB_Sybase8ToDTIME,
	(const DBDATETIME *in_date, DTIME *out_date));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sybase money type conversion functions . . .
		*****************************************************************	*/
COMPAT_FN_DECL(double    DBC_SYB_DBMONEYToDouble,
	(const DBMONEY *in_dbmoney));
COMPAT_FN_DECL(double    DBC_SYB_DBMONEY4ToDouble,
	(const DBMONEY4 *in_dbmoney4));
COMPAT_FN_DECL(DBMONEY  *DBC_SYB_DoubleToDBMONEY,
	(double in_double, DBMONEY *out_dbmoney));
COMPAT_FN_DECL(DBMONEY4 *DBC_SYB_DoubleToDBMONEY4,
	(double in_double, DBMONEY4 *out_dbmoney4));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC numeric-to-generic conversion functions prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_DoubleToNumber, (int dbc_type, double double_value,
	void *number_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_NumberToDouble, (int dbc_type,
	const void *number_ptr, double *double_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC date-to-generic conversion functions prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_DTIMEToDate, (int dbc_type, const DTIME *dtime_ptr,
	void *date_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_DateToDTIME, (int dbc_type, const void *date_ptr,
	DTIME *dtime_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC time-to-generic conversion functions prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_DTIMEToTime, (int dbc_type, const DTIME *dtime_ptr,
	void *time_ptr, char *error_text));
COMPAT_FN_DECL(int DBC_SYB_TimeToDTIME, (int dbc_type, const void *time_ptr,
	DTIME *dtime_ptr, char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC miscellaneous generic numeric function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_IsNumber, (int dbc_type));
COMPAT_FN_DECL(int DBC_SYB_MinNumber, (int dbc_type, double *double_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_SYB_MaxNumber, (int dbc_type, double *double_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC miscellaneous generic date function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_IsDate, (int dbc_type));
COMPAT_FN_DECL(int DBC_SYB_MinDate, (int dbc_type, DTIME *dtime_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_SYB_MaxDate, (int dbc_type, DTIME *dtime_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC miscellaneous generic time function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_IsTime, (int dbc_type));
COMPAT_FN_DECL(int DBC_SYB_MinTime, (int dbc_type, DTIME *dtime_ptr,
	char *error_text));
COMPAT_FN_DECL(int DBC_SYB_MaxTime, (int dbc_type, DTIME *dtime_ptr,
	char *error_text));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC generic numeric comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_CMP_Number, (int dbc_type, const void *ptr_1,
	const void *ptr_2));
COMPAT_FN_DECL(int DBC_SYB_SCMP_Number, (void *control_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC generic date comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_CMP_Date, (int dbc_type, const void *ptr_1,
	const void *ptr_2));
COMPAT_FN_DECL(int DBC_SYB_SCMP_Date, (void *control_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		DBC generic time comparison function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int DBC_SYB_CMP_Time, (int dbc_type, const void *ptr_1,
	const void *ptr_2));
COMPAT_FN_DECL(int DBC_SYB_SCMP_Time, (void *control_ptr, const void *ptr_1,
	const void *ptr_2, size_t data_length));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sybase data-type SQL conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int   DBC_SYB_FMT_Data_SQL, (int sybase_type,
	unsigned int data_length, const void *data_ptr, char *out_string,
	char *error_text));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBBINARY_SQL, (unsigned int data_length,
	const void *data_ptr, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBIMAGE_SQL, (unsigned int data_length,
	const void *data_ptr, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBBIT_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBCHAR_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBTEXT_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBINT1_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBINT2_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBINT4_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBREAL_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBFLT8_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBMONEY_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBMONEY4_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBDATETIME_SQL, (const void *data_ptr,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBDATETIME4_SQL, (const void *data_ptr,
	char *out_string));
	/*	*****************************************************************	*/

	/*	*****************************************************************
		*****************************************************************
		Sybase data-type general conversion function prototypes . . .
		*****************************************************************	*/
COMPAT_FN_DECL(int   DBC_SYB_FMT_Data, (int sybase_type,
	unsigned int data_length, const void *data_ptr, unsigned int min_length,
	unsigned int max_length, int right_justify_flag,
	unsigned int decimal_places, char *out_string, char *error_text));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBBINARY, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBIMAGE, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBBIT, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, const char *true_string, const char *false_string,
	char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBCHAR, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBTEXT, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBINT1, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBINT2, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBINT4, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBREAL, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, unsigned int decimal_places, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBFLT8, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, unsigned int decimal_places, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBMONEY, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, unsigned int decimal_places, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBMONEY4, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, unsigned int decimal_places, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBDATETIME, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, const char *date_format, char *out_string));
COMPAT_FN_DECL(char *DBC_SYB_FMT_SYBDATETIME4, (unsigned int data_length,
	const void *data_ptr, unsigned int min_length, unsigned int max_length,
	int right_justify_flag, const char *date_format, char *out_string));
	/*	*****************************************************************	*/

/*	***********************************************************************	*/

#endif /* #ifndef h__DBCSYB_H__h */

