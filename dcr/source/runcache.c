/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Executable Module									*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:

	Revision History	:	1994-06-06 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <limits.h>
#include <locale.h>
#include <math.h>
#include <memory.h>
#include <string.h>
#include <sys/param.h>

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#define DCR_RUN_VERSION_NUMBER "01.01.01A"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static const unsigned long DCR_RUN_CallBackMask =
	DCR_CB_BULK_INSERT   |
	DCR_CB_BULK_SEARCH   |
	DCR_CB_INDEX_CACHE   |
	DCR_CB_RESIZE_CACHE  |
	DCR_CB_INITIAL_LOAD  |
	DCR_CB_RELOAD        |
	DCR_CB_UPDATE        |
	DCR_CB_ALLOC_CHUNK   |
	DCR_CB_CHECK_INDEX_1 |
	DCR_CB_CHECK_INDEX_2;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

typedef struct {
	char               *program_name;
	char               *short_program_name;
	char               *syslog_program_name;
	STR_VERSION         system_version_number;
	STR_VERSION         version_number;
	char                system_version_string[STR_VERSION_NUMBER_LENGTH + 1];
	char                version_string[STR_VERSION_NUMBER_LENGTH + 1];
	int                 process_id;
	char                host_name[MAXHOSTNAMELEN + 1];
	char                current_directory[MAXPATHLEN + 1];
	int                 help_flag;
	int                 version_flag;
	int                 operating_mode;
	struct timeval      start_time;
	struct timeval      end_time;
	struct timeval      overhead_end_time;
	int                 signal_received_flag;
	int                 queue_signal_flag;
	int                 shut_down_flag;
	int                 db_debugging_flag;
	int                 sql_debugging_flag;
	unsigned long       refresh_seconds;
	DCR_CONTROL   cache_control_data;
	DCR_CACHE          *cache_ptr;
	unsigned int        cache_index;
	char               *cache_file_name;
	char               *cache_name;
	char               *log_file_directory;
	char               *log_file_name;
	MFILE              *log_file_mfile_ptr;
	MFILE_LOG_CONTEXT   log_context;
	char               *meta_data_db_string;
	char               *safe_meta_data_db_string;
	char               *database_name;
	char               *owner_name;
	char               *table_name;
	char               *db_user_name;
	char               *db_pass_word;
	char               *sql_where_clause;
	char               *sql_group_by_clause;
	char               *sql_order_by_clause;
	char               *update_date_field_name;
	unsigned int        maximum_row_count;
	unsigned int        added_field_count;
	char              **added_field_list;
	unsigned int        index_spec_count;
	char              **index_spec_list;
	int                 indirect_index_flag;
	int                 load_data_flag;
	unsigned int        initial_allocation_size;
	unsigned int        allocation_size;
	unsigned int        db_load_granularity;
} DCR_RUN_CONTROL;

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#ifndef NARGS
int main(int argc, char **argv);
#else
int main();
#endif /* #ifndef NARGS */

#ifndef NARGS
static int  DCR_RUN_StartCreate(DCR_RUN_CONTROL *control_ptr,
	const void **user_data_ptr_list, char *error_text);
static int  DCR_RUN_StartReload(DCR_RUN_CONTROL *control_ptr,
	const void **user_data_ptr_list, char *error_text);
static int  DCR_RUN_StartUpdate(DCR_RUN_CONTROL *control_ptr,
	const void **user_data_ptr_list, char *error_text);
static int  DCR_RUN_UpdateLoop(DCR_RUN_CONTROL *control_ptr,
	char *error_text);
static int  DCR_RUN_GetParams(DCR_RUN_CONTROL *control_ptr,
	unsigned int argc, char **argv, char *error_text);
static int  DCR_RUN_CheckParams(DCR_RUN_CONTROL *control_ptr,
	char *error_text);
static int  DCR_RUN_OpenLogFile(DCR_RUN_CONTROL *control_ptr,
	char *error_text);
static void DCR_RUN_ShowSettings(DCR_RUN_CONTROL *control_ptr);
static int  DCR_RUN_Parse(DCR_RUN_CONTROL *control_ptr, unsigned int argc,
	char **argv, int call_flag, unsigned int current_arg,
	const char *this_arg, char *error_text);
static void DCR_RUN_Init(DCR_RUN_CONTROL *control_ptr);
static void DCR_RUN_End(DCR_RUN_CONTROL *control_ptr,
	int signal_number, int *exit_code_ptr, const char *message_buffer);
static int  DCR_RUN_CallBack(DCR_CACHE *cache_ptr,
	unsigned long call_back_type, int post_operation_flag,
	unsigned int index_method, int operation_flags,
	unsigned int operation_count, void *operation_ptr,
	DCR_STAT *stat_ptr, int return_code, char *error_text);
static int  DCR_RUN_CriticalCallBack(DCR_CACHE *cache_ptr,
	unsigned long call_back_type, int post_operation_flag, int operation_flags,
	unsigned int operation_count, void *operation_ptr, int return_code,
	char *error_text);
#else
static int  DCR_RUN_StartCreate();
static int  DCR_RUN_StartReload();
static int  DCR_RUN_StartUpdate();
static int  DCR_RUN_UpdateLoop();
static int  DCR_RUN_GetParams();
static int  DCR_RUN_CheckParams();
static int  DCR_RUN_OpenLogFile();
static void DCR_RUN_ShowSettings();
static int  DCR_RUN_Parse();
static void DCR_RUN_Init();
static void DCR_RUN_End();
static int  DCR_RUN_CallBack();
static int  DCR_RUN_CriticalCallBack();
#endif /* #ifndef NARGS */

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static const char *UsageList[] = {
	"Usage:",
	"------",
	"	runcache [<a mixture of '-' options, and '@' commands]",
	"\n",
	"Description:",
	"------------",
	"	This program manages the creation and update of the contents of an \
DCR cache file.",
	"\n",
	"	Invocation of the program may include any number of parameters \
which may be used to specify the nature of the resulting program operation. \
There are two types of parameters:",
	"\n",
	"		o  '-'-prefaced options, which specify any one of a number of \
options (which are described in the 'Options', below); and,",
	"\n",
	"		o  '@'-prefaced file names, which indicate that the indicated \
file name is to be parsed for parameters.",
	"\n",
	"Operation:",
	"----------",
	"	Program operation is as follows:",
	"\n",
	"		o The program initializes itself to the default settings.",
	"\n",
	"		o The command line is scanned for options.",
	"\n",
	"		o Every time a valid parameter is encountered, it immediately \
becomes active.  If the same parameter is encountered multiple times, \
the most-recent instance of the parameter becomes effective.",
"\n",
	"		o If an '@' option is encountered, the indicated file is read \
as if its lines had been placed on the command line UNLESS the \
indicated file is in the current hierarchy of '@' files, in which \
case it is ignored.",
	"\n",
	"Options:",
	"--------",
	"	[-H[ELP]]",
	"		Displays this text. Note that if this parameter appears on the \
command-line, the program will exit after displaying the help text.",
	"\n",
	"	[-V[ER[SION][S]]]]",
	"		Displays the version of this program.",
	"\n",
	"		If this parameter appears on the command line, any subsequent \
parameters will be parsed for validity and the program will exit.",
	"\n",
	"	[-OPERATI{ON|NG}[_MODE]={CREATE|RE[_]{FRESH|LOAD}|UPDATE}[_CACHE]]",
	"		Specifies the operating mode of the program. The meaning of the \
operating modes are as follows:",
	"\n",
	"		o CREATE[_CACHE]",
	"			Indicates that the cache is to be created. If the cache file \
specified by the '-CACHE_FILE_NAME=' parameter already exists, it will be \
over-written.",
	"\n",
	"		o RE[_]{FRESH|LOAD}[_CACHE]",
	"			Indicates that the cache file which was specified by the \
'-CACHE_FILE_NAME=' parameter already exists and is to be refreshed by \
loading all rows from the database into the cache.",
	"\n",
	"		o UPDATE[_CACHE]",
	"			Indicates that the cache file which was specified by the \
'-CACHE_FILE_NAME=' parameter already exists and is to be updated. All rows \
in the database which have an 'updatedate' column equal to or greater than \
the highest 'updatedate' already in the cache will be loaded from the \
database into the cache.",
	"\n",
	"	The default operating mode is 'CREATE_CACHE'.",
	"\n",
	"	-CACHE_FILE[_NAME]=<file-name>",
	"		Specifies the name of the cache file to be opened.",
	"\n",
	"	-CACHE_NAME=<cache-name>",
	"		Specifies the name of the cache (NOT the cache file-name).",
	"\n",
	"		This parameter is required if the cache is to be created for the \
first time. If the cache already exists, it is ignored.",
	"\n",
	"	[-UPDATE_RE[_]{FRESH|LOAD}_SECOND[S]=<time-in-seconds>]",
	"		Specifies the time in seconds between automated updates of the \
cache from the database.",
	"\n",
	"		If this parameter is specified as a positive non-zero value, the \
cache will be refreshed with records from the database having an \
'updatedate' column equal to or greater than the most-recent 'updatedate' \
in the cache. The refresh will be performed every <time-in-seconds> seconds.",
	"\n",
	"		If the <time-in-seconds> component of this parameter is not \
present or is equal to zero ('0') the system will not \
refresh the cache from the database automatically.",
	"\n",
	"	[-UPDATE_DATE_{FIELD|COLUMN}[_NAME]=<db-column-name>]",
	"		Specifies the column name to use when refreshing cache records \
from the database according to the database update-date.",
	"\n",
	"		If this parameter is not specified and updates of the cache from \
the database are to be performed, the default update-date column name will \
be used ('updatedate').",
	"\n",
	"		It is an error if the specified column name is not in the cache.",
	"\n",
	"	[-{DB|DATA[_]BASE}_LOAD_GRAN[ULAR[ITY]]=<number>]",
	"		Specifies the memory-mapped allocation granularity to be used when \
allocating space for rows loded from the database.",
	"\n",
	"		If the <number> component of this parameter is not present or is \
equal to zero ('0') the system will use the default allocation granularity. \
At present, this 10,000 rows.",
	"\n",
	"	[-{CLEAR|DELETE|REMOVE}_ADD[ED]_FIELD[S]=<boolean>]",
	"		If encountered on the command-line, any fields specified so far \
by the '-ADDED_FIELDS=' parameter will be cleared.",
	"\n",
	"		The <boolean> component of this parameter has the following syntax:",
	"\n",
	"		{ ON | OFF | TRUE | FALSE | YES | NO }",
	"\n",
	"	[-{CLEAR|DELETE|REMOVE}_INDEX_SPEC[IFICATION][S]=<boolean>]",
	"		If encountered on the command-line, any fields specified so far \
by the '-INDEX_SPECIFICATION=' parameter will be cleared.",
	"\n",
	"		The <boolean> component of this parameter has the following syntax:",
	"\n",
	"		{ ON | OFF | TRUE | FALSE | YES | NO }",
	"\n",
	"	[-LOG[GING]_DIR[RECTORY]=<log-file-dir-name>]",
	"		Specifies the directory within which the log file is to be created.",
	"\n",
	"		If this parameter is not specified, the log file will be created \
in the current directory ('./').",
	"\n",
	"	-META{_DB|_DATA[_BASE]}[_NAME]=<db-spec>",
	"		Specifies the database server, database, and login parameters to \
be used to read the meta-data used to specify the table fields known by the \
program. The <db-spec> component of this parameter has the following \
structure:",
	"\n",
	"			<db-spec> := <server>,[<database>],[<owner>],<user>,[<pass-word>]",
	"\n",
	"	-{DB|DATA_BASE}[_NAME]=<database-name>",
	"		Specifies the database in which the table to be cached resides.",
	"\n",
	"		This parameter is required if the cache is to be created for the \
first time. If the cache already exists, it is ignored.",
	"\n",
	"	-{DB_|DATA_BASE_]OWNER[_NAME]=<owner-name>",
	"		Specifies the owner of the table to be cached.",
	"\n",
	"		This parameter is required if the cache is to be created for the \
first time. If the cache already exists, it is ignored.",
	"\n",
	"	-[DB_|DATA_BASE_]TABLE[_NAME]=<table-name>",
	"		Specifies the name of the table to be cached.",
	"\n",
	"		This parameter is required if the cache is to be created for the \
first time. If the cache already exists, it is ignored.",
	"\n",
	"	-[DB_|DATA_BASE_]USER[_NAME]=<db-user-name>",
	"		Specifies the user name which is to be used for login to the \
databases used in the operation of the program.",
	"\n",
	"	-[DB_|DATA_BASE_]PASSWORD=<db-pass-word>",
	"		Specifies the password which is to be used for login to the \
databases used in the operation of the program.",
	"\n",
	"	[-INDEX_TYPE[S]={INDIRECT|EMBED[DED]}[_IND{EX[[E]S]|ICES}]]",
	"		Specifies the type of index to be used when creating the cache. \
The types of index supported are as follow:",
	"\n",
	"		o INDIRECT[_IND{EX[[E]S]|ICES}]",
	"			Indicates that the cache will be created using indirect indices.",
	"\n",
	"		o EMBED[DED][_IND{EX[[E]S]|ICES}]",
	"			Indicates that the cache will be created using embedded indices.",
	"\n",
	"		The default for this parameter is 'INDIRECT_INDICES'.",
	"\n",
	"	[-INDIRECT_IND{EX[[E]S]|ICES}={ ON | OFF | TRUE | FALSE | YES | NO }]",
	"		Specifies whether the cache is to be created using indirect \
indices.",
	"\n",
	"		This parameter duplicates the functionality of the '-INDEX_TYPE=' \
paramter (see above).",
	"\n",
	"		The default for this parameter is 'ON' (that is, indirect indices).",
	"\n",
	"	[-LOAD_FROM_DB={ ON | OFF | TRUE | FALSE | YES | NO }]",
	"		Specifies whether the cache is to be created with data populated \
from the database.",
	"\n",
	"		The default for this parameter is 'ON'.",
	"\n",
	"	[-ADD[ED]_FIELD[S]=<field-spec>]",
	"		Specifies a non-database field to be included in the cache. The \
<field-spec> component of this parameter has the following structure:",
	"\n",
	"			<field-spec> := <field-name>,<meta-data-type>[,<array-length>]",
	"\n",
	"		The <field-name> sub-component is the name by which the added \
field will be identified within the cache.",
	"\n",
	"		The <meta-data-type> is the name of an existing SPS meta-data \
type (such as 'signed char' or 'unsigned int'). The meta-data type short \
names are also permitted in this context (for example, 'schar' or 'uint').",
	"\n",
	"		The optional <array-length> sub-component of this parameter \
specifies the number of elements the added field is to have. The minimum \
value is '1' and maximum value is '32767'.",
	"\n",
	"		For example, to create two added fields to store a text string \
32 characters in length and a double, you would use the following \
parameters:",
	"\n",
	"			-ADDED_FIELD=text_field_name,schar,32",
	"			-ADDED_FIELD=numeric_value,double",
	"\n",
	"		This parameter is effective only if the cache is to be created for \
the first time. If the cache already exists, it is ignored.",
	"\n",
	"	-INDEX_SPEC[IFICATION][S]=<index-spec>",
	"		Specifies the fields which are to be used to construct a cache \
index. The <index-spec> component of this parameter has the following \
structure:",
	"\n",
	"			<index-spec> := <index-name>=<field-name>[,<field-name> . . .]",
	"\n",
	"		At least one '-INDEX_SPECIFICATION=' parameter is required if the \
cache is to be created for the first time. It is ignored if the cache \
already exists.",
	"\n",
	"		This parameter may occur multiple times on the command-line; if it \
does, each instance is taken as specifing the creation of a different index. \
Note, however, that each <index-name> must be unique.",
	"\n",
	"	[-INITIAL_ALLOC[ATION]=<number>]",
	"		Specifies the cache allocation granularity to be used the first \
time a cache is populated with data.",
	"\n",
	"		If the <number> component of this parameter is not present or is \
empty, the system will use the allocation granularity specified by the \
'-ALLOCATION=' parameter (see below).",
	"\n",
	"		If an '-INITIAL_ALLOCATION=' parameter specifies a value less than \
that specified by an 'ALLOCATION=' parameter, the '-ALLOCATION=' parameter \
value will be used.",
	"\n",
	"		In all cases, whether this parameter is specified or defaulted, \
the program may round the value up to a multiple of the internal page size.",
	"\n",
	"		This parameter is effective only if the cache is to be created for \
the first time. If the cache already exists, it is ignored.",
	"\n",
	"	[-ALLOC[ATION]=<number>]",
	"		Specifies the cache allocation granularity to be used when \
expanding the size of the cache.",
	"\n",
	"		If the <number> component of this parameter is not present or is \
equal to zero ('0') the system will use the default allocation granularity.",
	"\n",
	"		In all cases, whether this parameter is specified or defaulted, \
the program may round the value up to a multiple of the internal page size.",
	"\n",
	"		This parameter is effective only if the cache is to be created for \
the first time. If the cache already exists, it is ignored.",
	"\n",
	"	[-[SQL_]GROUP_BY[_CLAUSE]=<group-by-clause>]",
	"		Specifies an SQL 'GROUP BY' clause to be used when retrieving rows \
for the database into a cache.",
	"\n",
	"		The text 'GROUP BY' should not appear in the <group-by-clause> \
component of this parameter as it will be added by the cache library at the \
time the SQL statement is constructed.",
	"\n",
	"		Certain characters permitted in SQL 'GROUP BY' clauses may be \
interpolated by the shell. It is recommended that you escape fully any \
such characters.",
	"\n",
	"	[-[SQL_]ORDER_BY[_CLAUSE]=<order-by-clause>]",
	"		Specifies an SQL 'ORDER BY' clause to be used when retrieving rows \
for the database into a cache.",
	"\n",
	"		The text 'ORDER BY' should not appear in the <order-by-clause> \
component of this parameter as it will be added by the cache library at the \
time the SQL statement is constructed.",
	"\n",
	"		Certain characters permitted in SQL 'ORDER BY' clauses may be \
interpolated by the shell. It is recommended that you escape fully any \
such characters.",
	"\n",
	"	[-[SQL_]WHERE[_CLAUSE]=<where-clause>]",
	"		Specifies an SQL 'WHERE' clause to be used when retrieving rows \
for the database into a cache.",
	"\n",
	"		The text 'WHERE' should not appear in the <where-clause> \
component of this parameter as it will be added by the cache library at the \
time the SQL statement is constructed.",
	"\n",
	"		Certain characters permitted in SQL 'WHERE' clauses may be \
interpolated by the shell. It is recommended that you escape fully any \
such characters.",
	"\n",
	"	[-MAX[IMUM]_{ROW[S]|RECORD[S]}[_COUNT]=<max-row-count>]",
	"		Specifies the maximum number of rows to be read from the database \
during the initial create, refresh, or update database load. If the \
<max-row-count> component of the option is not present or is equal to zero \
('0'), no maximum will be imposed while perfoming the such loads.",
	"\n",
	"		The default for this option is '0'.",
	"\n",
	"	[-{DB|DATA[_]BASE}_DEBUG[GING][_FLAG]=<boolean>]",
	"		Specifies whether the program is to log all messages and errors \
returned from the database server in the log file.",
	"\n",
	"		The <boolean> component of this parameter has the following syntax:",
	"\n",
	"			{ ON | OFF | TRUE | FALSE | YES | NO }",
	"\n",
	"		The default for this parameter is 'OFF'.",
	"\n",
	"	[-SQL_DEBUG[GING][_FLAG]=<boolean>]",
	"		Specifies whether the program is to log all SQL statements set to \
the database server in the log file.",
	"\n",
	"		The <boolean> component of this parameter has the following syntax:",
	"\n",
	"			{ ON | OFF | TRUE | FALSE | YES | NO }",
	"\n",
	"		The default for this parameter is 'OFF'.",
	"\n",
	"	[@<parameter-include-file-name>]",
	"		Specifies the name of a parameter include file from which are to \
be read parameters to this program. Parameter include files may themselves \
contain parameter include file specifications.",
	"\n",
	"		When a parameter include file is encountered on the command line, \
the program will attempt to open it for reading. It is an error if the file \
so specified does not exist or can not be read.",
	"\n",
	"		Each line of the parameter include file is parsed for its \
parameters just as if those parameters were entered on the command line \
except for the following rules:",
	"\n",
	"			o A line in which the first non-whitespace character is a \
number-sign ('#') is considered to be the start of a comment and is ignored.",
	"\n",
	"			o Blank lines (that is, lines which are empty or which consist \
wholly of whitespace) are ignored.",
	"\n",
	NULL
};

/*	***********************************************************************	*/

int main(argc, argv)
int    argc;
char **argv;
{
	int                    return_code;
	DCR_RUN_CONTROL  control_data;
	void                  *user_data_ptr_list[DCR_USER_DATA_PTR_COUNT];
	char                   error_text[DCR_MAX_ERROR_TEXT];

	memset(&control_data,       '\0', sizeof(control_data));
	memset(&user_data_ptr_list, '\0', sizeof(user_data_ptr_list));

	if ((return_code = DCR_RUN_GetParams(&control_data,
		((unsigned int) argc), argv, error_text)) == DCR_SUCCESS) {
		user_data_ptr_list[0] = &control_data;
		SDTIF_GetTimeUSecs(&control_data.overhead_end_time);
		if ((control_data.help_flag != DCR_TRUE) &&
			(control_data.version_flag != DCR_TRUE)) {
			if (control_data.operating_mode == DCR_OP_CREATE)
				return_code = DCR_RUN_StartCreate(&control_data,
					((const void **) user_data_ptr_list), error_text);
			else if (control_data.operating_mode == DCR_OP_RELOAD)
				return_code = DCR_RUN_StartReload(&control_data,
					((const void **) user_data_ptr_list), error_text);
			else if (control_data.operating_mode == DCR_OP_UPDATE)
				return_code = DCR_RUN_StartUpdate(&control_data,
					((const void **) user_data_ptr_list), error_text);
			else {
				sprintf(error_text, "Invalid cache operating mode (%d).",
					control_data.operating_mode);
				return_code = DCR_FAILURE;
			}
			if (return_code != DCR_SUCCESS) {
				MFILE_LogMessageContext(&control_data.log_context, NULL, LOG_ERR,
					MFILE_FALSE, "Error occurred in cache start-up: %s\n",
					error_text);
				if ((control_data.cache_ptr != NULL) &&
					(control_data.operating_mode == DCR_OP_CREATE)) {
					MFILE_LogMessageContext(&control_data.log_context, NULL,
						LOG_INFO, MFILE_FALSE,
						"Closing and unlinking the cache file '%s'.\n",
						control_data.cache_ptr->cache_file_name);
					DCR_CloseOneCache(control_data.cache_ptr);
					control_data.cache_ptr = NULL;
					unlink(control_data.cache_file_name);
				}
			}
			else if ((return_code == DCR_SUCCESS) &&
				control_data.refresh_seconds)
				return_code = DCR_RUN_UpdateLoop(&control_data, error_text);
		}
		DCR_RUN_End(&control_data, 0, NULL, NULL);
		GEN_SIGNAL_SignalDefault();
	}

	if (return_code != DCR_SUCCESS)
		fprintf(stderr, "\n\nERROR: %s\n\n%s", error_text,
			(return_code != DCR_BAD_ARGS_FAILURE) ? "" :
			"       Help is available with the '-HELP' parameter.\n\n");

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_RUN_StartCreate(control_ptr, user_data_ptr_list,
	error_text)
DCR_RUN_CONTROL  *control_ptr;
const void            **user_data_ptr_list;
char                   *error_text;
{
	return(DCR_CreateCache(&control_ptr->cache_control_data,
		control_ptr->cache_file_name, control_ptr->cache_name,
		control_ptr->meta_data_db_string, control_ptr->table_name,
		control_ptr->maximum_row_count, control_ptr->db_load_granularity,
		control_ptr->initial_allocation_size, control_ptr->allocation_size,
		control_ptr->load_data_flag, control_ptr->indirect_index_flag,
		control_ptr->added_field_count, control_ptr->added_field_list,
		control_ptr->index_spec_count, control_ptr->index_spec_list,
		control_ptr->sql_group_by_clause, control_ptr->sql_order_by_clause,
		control_ptr->sql_where_clause, &DCR_RUN_CallBackMask,
		DCR_RUN_CallBack, user_data_ptr_list, &control_ptr->cache_ptr,
		&control_ptr->cache_index, error_text));
}
/*	***********************************************************************	*/

static int DCR_RUN_StartReload(control_ptr, user_data_ptr_list,
	error_text)
DCR_RUN_CONTROL  *control_ptr;
const void            **user_data_ptr_list;
char                   *error_text;
{
	int           return_code;
	unsigned long call_back_mask;

	if ((return_code = DCR_OpenWrite(&control_ptr->cache_control_data,
		control_ptr->cache_file_name, &control_ptr->cache_ptr,
		&control_ptr->cache_index, error_text)) == DCR_SUCCESS) {
		if ((control_ptr->sql_group_by_clause != NULL) &&
			((DCR_SetSQLGroupByClause(control_ptr->cache_ptr,
			control_ptr->sql_group_by_clause, error_text)) != DCR_SUCCESS))
			goto EXIT_FUNCTION;
		else if ((control_ptr->sql_order_by_clause != NULL) &&
			((DCR_SetSQLOrderByClause(control_ptr->cache_ptr,
			control_ptr->sql_order_by_clause, error_text)) != DCR_SUCCESS))
			goto EXIT_FUNCTION;
		else if ((control_ptr->sql_where_clause != NULL) &&
			((DCR_SetSQLWhereClause(control_ptr->cache_ptr,
			control_ptr->sql_where_clause, error_text)) != DCR_SUCCESS))
			goto EXIT_FUNCTION;
		DCR_SetCriticalCallBack(control_ptr->cache_ptr,
			DCR_RUN_CriticalCallBack);
		memcpy(&control_ptr->cache_ptr->user_data_ptr_list, user_data_ptr_list,
			sizeof(control_ptr->cache_ptr->user_data_ptr_list));
		DCR_SetUserCallBack(control_ptr->cache_ptr,
			&DCR_RUN_CallBackMask, DCR_RUN_CallBack);
		if (!control_ptr->cache_ptr->record_count) {
			call_back_mask =
				DCR_RUN_CallBackMask | DCR_CB_SORT_CACHE;
			DCR_SetUserCallBack(control_ptr->cache_ptr, &call_back_mask,
				NULL);
		}
		return_code = DCR_DoCacheReload(control_ptr->cache_ptr,
			DCR_INSERT_ALLOC_FULL, DCR_TRUE, DCR_FALSE, NULL, NULL,
			control_ptr->maximum_row_count, control_ptr->db_load_granularity,
			error_text);
		DCR_SetUserCallBack(control_ptr->cache_ptr,
			&DCR_RUN_CallBackMask, NULL);
		if ((control_ptr->signal_received_flag == GENFUNCS_TRUE) &&
			(return_code == DCR_SUCCESS)) {
			sprintf(error_text, "PROCESS ABORTED BY SIGNAL");
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_ERR,
				MFILE_FALSE, "%s\n", error_text);
			return_code = DCR_FAILURE;
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_RUN_StartUpdate(control_ptr, user_data_ptr_list,
	error_text)
DCR_RUN_CONTROL  *control_ptr;
const void            **user_data_ptr_list;
char                   *error_text;
{
	int           return_code;
	unsigned long call_back_mask;

	if ((return_code = DCR_OpenWrite(&control_ptr->cache_control_data,
		control_ptr->cache_file_name, &control_ptr->cache_ptr,
		&control_ptr->cache_index, error_text)) == DCR_SUCCESS) {
		if ((control_ptr->sql_group_by_clause != NULL) &&
			((DCR_SetSQLGroupByClause(control_ptr->cache_ptr,
			control_ptr->sql_group_by_clause, error_text)) != DCR_SUCCESS))
			goto EXIT_FUNCTION;
		else if ((control_ptr->sql_order_by_clause != NULL) &&
			((DCR_SetSQLOrderByClause(control_ptr->cache_ptr,
			control_ptr->sql_order_by_clause, error_text)) != DCR_SUCCESS))
			goto EXIT_FUNCTION;
		else if ((control_ptr->sql_where_clause != NULL) &&
			((DCR_SetSQLWhereClause(control_ptr->cache_ptr,
			control_ptr->sql_where_clause, error_text)) != DCR_SUCCESS))
			goto EXIT_FUNCTION;
		DCR_SetCriticalCallBack(control_ptr->cache_ptr,
			DCR_RUN_CriticalCallBack);
		memcpy(&control_ptr->cache_ptr->user_data_ptr_list, user_data_ptr_list,
			sizeof(control_ptr->cache_ptr->user_data_ptr_list));
		DCR_SetUserCallBack(control_ptr->cache_ptr,
			&DCR_RUN_CallBackMask, DCR_RUN_CallBack);
		if (!control_ptr->cache_ptr->record_count) {
			call_back_mask =
				DCR_RUN_CallBackMask | DCR_CB_SORT_CACHE;
			DCR_SetUserCallBack(control_ptr->cache_ptr, &call_back_mask,
				NULL);
		}
		return_code = DCR_DoCacheUpdate(control_ptr->cache_ptr,
			DCR_INSERT_ALLOC_FULL, control_ptr->update_date_field_name, 0,
			control_ptr->db_load_granularity, error_text);
		DCR_SetUserCallBack(control_ptr->cache_ptr,
			&DCR_RUN_CallBackMask, NULL);
		if ((control_ptr->signal_received_flag == GENFUNCS_TRUE) &&
			(return_code == DCR_SUCCESS)) {
			sprintf(error_text, "PROCESS ABORTED BY SIGNAL");
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_ERR,
				MFILE_FALSE, "%s\n", error_text);
			return_code = DCR_FAILURE;
		}
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_RUN_UpdateLoop(control_ptr, error_text)
DCR_RUN_CONTROL *control_ptr;
char            *error_text;
{
	int           return_code = DCR_SUCCESS;
	unsigned long call_back_mask;
	time_t        tmp_time_t;
	char          buffer[100];

	if ((control_ptr->sql_group_by_clause != NULL) &&
		((DCR_SetSQLGroupByClause(control_ptr->cache_ptr,
		control_ptr->sql_group_by_clause, error_text)) != DCR_SUCCESS))
		goto EXIT_FUNCTION;
	else if ((control_ptr->sql_order_by_clause != NULL) &&
		((DCR_SetSQLOrderByClause(control_ptr->cache_ptr,
		control_ptr->sql_order_by_clause, error_text)) != DCR_SUCCESS))
		goto EXIT_FUNCTION;
	else if ((control_ptr->sql_where_clause != NULL) &&
		((DCR_SetSQLWhereClause(control_ptr->cache_ptr,
		control_ptr->sql_where_clause, error_text)) != DCR_SUCCESS))
		goto EXIT_FUNCTION;

	while (1) {
		tmp_time_t = time(NULL) + ((time_t) control_ptr->refresh_seconds);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "%s %s . . . sleeping . . .\n",
			"Will start the automated cache update at",
			SDTIF_Format_time_t(&tmp_time_t, buffer));
		sleep(control_ptr->refresh_seconds);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Starting automated cache update . . .\n");
		if (!control_ptr->cache_ptr->record_count) {
			call_back_mask =
				DCR_RUN_CallBackMask | DCR_CB_SORT_CACHE;
			DCR_SetUserCallBack(control_ptr->cache_ptr, &call_back_mask,
				NULL);
		}
		if ((return_code = DCR_DoCacheUpdate(control_ptr->cache_ptr,
			DCR_INSERT_ALLOC_FULL, control_ptr->update_date_field_name, 0,
			control_ptr->db_load_granularity, error_text)) != DCR_SUCCESS) {
			DCR_SetUserCallBack(control_ptr->cache_ptr,
				&DCR_RUN_CallBackMask, NULL);
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE,
				"Error occurred performing automated cache update: %s\n",
				error_text);
			break;
		}
		DCR_SetUserCallBack(control_ptr->cache_ptr,
			&DCR_RUN_CallBackMask, NULL);
	}

EXIT_FUNCTION:

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_RUN_GetParams(control_ptr, argc, argv, error_text)
DCR_RUN_CONTROL  *control_ptr;
unsigned int            argc;
char                  **argv;
char                   *error_text;
{
	int  return_code;
	char gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	DCR_RUN_Init(control_ptr);

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Catch signals . . .															*/
	/*	*****************************************************************	*/
#ifndef NARGS
	GEN_SIGNAL_SignalInit(&control_ptr->signal_received_flag,
		&control_ptr->queue_signal_flag, control_ptr,
		&control_ptr->log_context.mfile_ptr,
		((int (*)(const void *, size_t, size_t, void *)) mwrite),
		((void (*)(void *, int, int *, const char *)) DCR_RUN_End));
#else
	GEN_SIGNAL_SignalInit(&control_ptr->signal_received_flag,
		&control_ptr->queue_signal_flag, control_ptr,
		&control_ptr->log_context.mfile_ptr, mwrite, DCR_RUN_End);
#endif /* #ifndef NARGS */
	GEN_SIGNAL_SignalSet();
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Get the process start time (or an approximation thereof). We	*/
	/*	initially set the overhead end time to the start time so that a	*/
	/*	premature exit results in reasonable numbers . . .						*/
	/*	*****************************************************************	*/
	SDTIF_GetTimeUSecs(&control_ptr->start_time);
	control_ptr->overhead_end_time = control_ptr->start_time;
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Operating system process identifier.									*/
	/*	*****************************************************************	*/
	control_ptr->process_id = getpid();
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		We want to start from a known state . . .								*/
	/*	*****************************************************************	*/
	if (setlocale(LC_ALL, "C") == NULL) {
		strcpy(error_text, "Attempt to 'setlocale(LC_ALL, \"C\")' failed.");
		return_code = DCR_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Don't want to run out of stack space, or something . . .			*/
	/*	*****************************************************************	*/
	if ((return_code = GEN_SetResourceLimitsToMax(gen_error_text)) !=
		GENFUNCS_SUCCESS) {
		nstrcpy(error_text, gen_error_text, DCR_MAX_ERROR_TEXT - 1);
		return_code = DCR_MAP_ERROR_GEN_TO_DCR(return_code);
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Here we get the full path name of the program --- if one has	*/
	/*	multiple versions lying about in your 'PATH', one might want to	*/
	/*	know from whence this instance came.										*/
	/*																							*/
	/*		We also get the 'short' name here --- that is, the program		*/
	/*	name without any directory information. This is useful for error	*/
	/*	messages and the like.															*/
	/*																							*/
	/*		Finally, we get the 'syslog()' program name. This value is the	*/
	/*	string which will be used by the program on calls to 'openlog()'.	*/
	/*	All messages sent to the operating 'syslog()' facility will be		*/
	/*	prefaced with this string.														*/
	/*	*****************************************************************	*/
	if ((return_code = GEN_ExpandToFullPathName(argv[0],
		&control_ptr->program_name, gen_error_text)) != GENFUNCS_SUCCESS) {
		sprintf(error_text, "Unable to expand the program name: %s.",
			gen_error_text);
		nstrcpy(error_text, gen_error_text, DCR_MAX_ERROR_TEXT - 1);
		return_code = DCR_MAP_ERROR_GEN_TO_DCR(return_code);
		goto EXIT_FUNCTION;
	}
	else if ((control_ptr->short_program_name =
		strdup(extract_file_name(control_ptr->program_name))) == NULL) {
		STR_AllocMsgItem(strlen(extract_file_name(control_ptr->program_name))+1,
			error_text, "Unable to allocate memory for the short program name");
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	else if ((control_ptr->syslog_program_name = ((char *)
		calloc(strlen("DCR") + 1 +
		strlen(control_ptr->short_program_name) + 1, sizeof(char)))) == NULL) {
		STR_AllocMsgItem(strlen("DCR") + 1 +
			strlen(control_ptr->short_program_name) + 1, error_text,
			"Unable to allocate memory for the 'syslog()' program name");
		return_code = DCR_MEMORY_FAILURE;
		goto EXIT_FUNCTION;
	}
	strcat(chrcat(strcpy(control_ptr->syslog_program_name, "DCR"),
		':'), control_ptr->short_program_name);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Try to initialize operating system logging . . .					*/
	/*	*****************************************************************	*/
	openlog(control_ptr->syslog_program_name, LOG_PID | LOG_CONS | LOG_NDELAY,
		LOG_USER);
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		On what host is the program running?									*/
	/*	*****************************************************************	*/
	if ((return_code = GEN_DetermineHostName(control_ptr->host_name,
		gen_error_text)) != GENFUNCS_SUCCESS) {
		nstrcat(error_text, gen_error_text, DCR_MAX_ERROR_TEXT - 1);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		What's our current working directory?									*/
	/*	*****************************************************************	*/
	if (getcwd(control_ptr->current_directory,
		sizeof(control_ptr->current_directory) - 2) == NULL) {
		strcpy(error_text, "Unable to determine the current directory: ");
		DCR_GEN_AppendLastErrorString(error_text);
		return_code = DCR_SYSTEM_FAILURE;
		goto EXIT_FUNCTION;
	}
	/*	*****************************************************************	*/

	if ((return_code =
		DCR_AllocCacheControl(&control_ptr->cache_control_data, 100,
		error_text)) == DCR_SUCCESS) {
#ifndef NARGS
		if ((return_code = GEN_GetParams(control_ptr, ((unsigned int) argc),
			argv, &control_ptr->help_flag, &control_ptr->version_flag,
			((int (*)(void *, unsigned int, char **, int, unsigned int,
			const char *, char *)) DCR_RUN_Parse), error_text)) == DCR_SUCCESS) {
#else
		if ((return_code = GEN_GetParams(control_ptr, ((unsigned int) argc),
			argv, &control_ptr->help_flag, &control_ptr->version_flag,
			DCR_RUN_Parse, error_text)) == DCR_SUCCESS) {
#endif /* #ifndef NARGS */
			if (control_ptr->help_flag == DCR_TRUE) {
				DCR_RUN_End(control_ptr, 0, NULL, NULL);
				GEN_DoFormatUsage(return_code, argv[0],
					"Help request with '-HELP' noted . . .", UsageList);
			}
			else if (control_ptr->version_flag == DCR_TRUE) {
				DCR_RUN_End(control_ptr, 0, NULL, NULL);
				fprintf(stderr, "%s Version Number %s\n", argv[0],
					DCR_RUN_VERSION_NUMBER);
				exit(0);
			}
			else if ((return_code = DCR_RUN_CheckParams(control_ptr,
				error_text)) == DCR_SUCCESS) {
				if ((return_code = DCR_RUN_OpenLogFile(control_ptr,
					error_text)) == DCR_SUCCESS) {
					if (control_ptr->db_debugging_flag == DCR_TRUE) {
/*
	CODE NOTE: What goes here?
*/
						;
					}
					if (control_ptr->sql_debugging_flag == DCR_TRUE)
/*
	CODE NOTE: What goes here?
*/
						;
				}
			}
		}
		if (return_code != DCR_SUCCESS)
			DCR_RUN_End(control_ptr, 0, NULL, NULL);
	}

EXIT_FUNCTION:

	/*	*****************************************************************	*/
	/*	*****************************************************************	*/
	/*		Now we know the real overhead end time . . .							*/
	/*	*****************************************************************	*/
	SDTIF_GetTimeUSecs(&control_ptr->overhead_end_time);
	/*	*****************************************************************	*/

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_RUN_CheckParams(control_ptr, error_text)
DCR_RUN_CONTROL *control_ptr;
char                  *error_text;
{
	int return_code = DCR_BAD_ARGS_FAILURE;

	if (control_ptr->cache_file_name == NULL)
		strcpy(error_text, "The cache file name was not specified.");
	else if (control_ptr->operating_mode == DCR_OP_CREATE) {
		if (control_ptr->cache_name == NULL)
			strcpy(error_text, "The cache name was not specified.");
		else if (control_ptr->meta_data_db_string == NULL)
			strcpy(error_text, "The meta-data DB spec was not specified.");
		else if (control_ptr->database_name == NULL)
			strcpy(error_text, "The table database name was not specified.");
		else if (control_ptr->owner_name == NULL)
			strcpy(error_text, "The table owner name was not specified.");
		else if (control_ptr->table_name == NULL)
			strcpy(error_text, "The table name was not specified.");
		else if (control_ptr->db_user_name == NULL)
			strcpy(error_text, "The database user name was not specified.");
		else if (control_ptr->db_pass_word == NULL)
			strcpy(error_text, "The database pass word was not specified.");
		else
			return_code = DCR_SUCCESS;
	}
	else
		return_code = DCR_SUCCESS;

	return(return_code);
}
/*	***********************************************************************	*/

static int DCR_RUN_OpenLogFile(control_ptr, error_text)
DCR_RUN_CONTROL *control_ptr;
char                  *error_text;
{
	int          return_code = DCR_SUCCESS;
	unsigned int count_1;
	char         cache_name[STR_sizeof(DCR_HEADER, cache_name)];
	char         time_buffer[100];
	char         buffer[4096 + STR_sizeof(DCR_HEADER, cache_name)];

	SDTIF_Format_time_t(&control_ptr->start_time.tv_sec, time_buffer);
	time_buffer[10] = '.';
	time_buffer[13] = '.';
	time_buffer[16] = '.';
	upper(trim(nstrcpy(cache_name,
		(control_ptr->operating_mode == DCR_OP_CREATE) ?
		control_ptr->cache_name : "REOPENED", sizeof(cache_name) - 1)));
	for (count_1 = 0; count_1 < strlen(cache_name); count_1++) {
		if (!isalnum(cache_name[count_1]))
			cache_name[count_1] = '_';
	}

	if ((control_ptr->log_file_directory == NULL) &&
		((control_ptr->log_file_directory = strdup(".")) == NULL)) {
		strcpy(error_text,
			"Unable to copy the default log file directory '.'.");
		return_code = DCR_MEMORY_FAILURE;
	}
	else {
		sprintf(buffer, "%s/%s.DCR_LOG.%s.%s.%u",
			control_ptr->log_file_directory, time_buffer, cache_name,
			control_ptr->host_name, control_ptr->process_id);
		if ((control_ptr->log_file_name = strdup(buffer)) == NULL) {
			strcpy(error_text, "Unable to copy the name of the log file.");
			return_code = DCR_MEMORY_FAILURE;
		}
		else if ((control_ptr->log_context.mfile_ptr =
			mopen(control_ptr->log_file_name, "w")) == NULL) {
			sprintf(error_text, "%s '%-.500s' for writing --- ",
				"Unable to open the log file", control_ptr->log_file_name);
			DCR_GEN_AppendLastErrorString(error_text);
			return_code = DCR_FAILURE;
		}
		else {
			control_ptr->log_file_mfile_ptr =
				control_ptr->log_context.mfile_ptr;
			DCR_RUN_ShowSettings(control_ptr);
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

static void DCR_RUN_ShowSettings(control_ptr)
DCR_RUN_CONTROL *control_ptr;
{
	unsigned int count_1;
	char         buffer[100];

	MFILE_LogSepStartLogContext(&control_ptr->log_context);

	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Program Name       : %s\n",
		control_ptr->program_name);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Version Number     : %s\n",
		DCR_RUN_VERSION_NUMBER);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Host Name          : %s\n", control_ptr->host_name);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Process ID         : %u\n",
		control_ptr->process_id);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Operating Mode     : %s\n",
		(control_ptr->operating_mode == DCR_OP_CREATE) ?
		"CREATE CACHE" :
		(control_ptr->operating_mode == DCR_OP_RELOAD) ?
		"REFRESH CACHE" : "UPDATE CACHE");
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Cache File Name    : %s\n",
		control_ptr->cache_file_name);
	if (control_ptr->operating_mode == DCR_OP_CREATE) {
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Cache Name         : %s\n",
			control_ptr->cache_name);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Meta-data Spec     : %s\n",
			control_ptr->safe_meta_data_db_string);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Database Name      : %s\n",
			control_ptr->database_name);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Owner Name         : %s\n",
			control_ptr->owner_name);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Table Name         : %s\n",
			control_ptr->table_name);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "DB User Name       : %s\n",
			control_ptr->db_user_name);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Load Data Flag     : %s\n",
			(control_ptr->load_data_flag == DCR_TRUE) ? "TRUE" : "FALSE");
		sprintf(buffer, "%10u", control_ptr->initial_allocation_size);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Initial Alloc      : %s\n",
			(control_ptr->initial_allocation_size) ? buffer : "DEFAULT");
		sprintf(buffer, "%10u", control_ptr->allocation_size);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Allocation Size    : %s\n",
			(control_ptr->allocation_size) ? buffer : "DEFAULT");
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Index Type         : %s\n",
			(control_ptr->indirect_index_flag == DCR_TRUE) ? "INDIRECT" :
			"EMBEDDED");
		for (count_1 = 0; count_1 < control_ptr->added_field_count; count_1++) {
			sprintf(buffer, "Added Field %u", count_1);
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "%-19.19s: %s\n", buffer,
				control_ptr->added_field_list[count_1]);
		}
		for (count_1 = 0; count_1 < control_ptr->index_spec_count; count_1++) {
			sprintf(buffer, "Index Spec %u", count_1);
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "%-19.19s: %s\n", buffer,
				control_ptr->index_spec_list[count_1]);
		}
	}
	sprintf(buffer, "%10u", control_ptr->maximum_row_count);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Maximum Records    : %s\n",
		(control_ptr->maximum_row_count) ? buffer : "ALL");
	sprintf(buffer, "%10u", control_ptr->db_load_granularity);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "DB Load Granularity: %s\n",
		(control_ptr->db_load_granularity) ? buffer : "DEFAULT");
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "SQL GROUP BY Clause: %s\n",
		(control_ptr->sql_group_by_clause == NULL) ? "*** N/A ***" :
		control_ptr->sql_group_by_clause);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "SQL ORDER BY Clause: %s\n",
		(control_ptr->sql_order_by_clause == NULL) ? "*** N/A ***" :
		control_ptr->sql_order_by_clause);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "SQL WHERE Clause   : %s\n",
		(control_ptr->sql_where_clause == NULL) ? "*** N/A ***" :
		control_ptr->sql_where_clause);
	if (control_ptr->refresh_seconds)
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Auto Refresh       : %s\n",
			SDTIF_FormatInterval_time_t(((time_t *) &control_ptr->refresh_seconds),
			buffer));
	if ((control_ptr->operating_mode == DCR_OP_UPDATE) ||
		control_ptr->refresh_seconds) {
		if (control_ptr->update_date_field_name == NULL)
			sprintf(buffer, "%s (DEFAULT)", DCR_DEFAULT_UPDATE_NAME);
		else
			strcpy(buffer, control_ptr->update_date_field_name);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Update Date Column : %s\n", buffer);
	}
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "DB Debugging Flag  : %s\n",
		GEN_GetBooleanString(control_ptr->db_debugging_flag, buffer));
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "SQL Debugging Flag : %s\n",
		GEN_GetBooleanString(control_ptr->sql_debugging_flag, buffer));
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Current Dir        : %s\n",
		control_ptr->current_directory);
	MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
		MFILE_FALSE, "Log File Name      : %s\n",
		control_ptr->log_file_name);

	MFILE_LogSepEqualCharContext(&control_ptr->log_context);
}
/*	***********************************************************************	*/

static int DCR_RUN_Parse(control_ptr, argc, argv, call_flag, current_arg,
	this_arg, error_text)
DCR_RUN_CONTROL  *control_ptr;
unsigned int      argc;
char            **argv;
int               call_flag;
unsigned int      current_arg;
const char       *this_arg;
char             *error_text;
{
	int           return_code = DCR_SUCCESS;
	char         *data_ptr;
	unsigned int  arg_length;
	double        tmp_double;
	int           error_flag;
	char          gen_error_text[GENFUNCS_MAX_ERROR_TEXT];

	if (!call_flag) {
		if ((!stricmp(this_arg, "-V")) || (!stricmp(this_arg, "-VER")) ||
			(!stricmp(this_arg, "-VERS")) || (!stricmp(this_arg, "-VERSION")) ||
			(!stricmp(this_arg, "-VERSIONS")))
			control_ptr->version_flag = DCR_TRUE;
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-OPERATION=", "-OPERATING=", "-OPERATION_MODE=",
			"-OPERATING_MODE=", NULL) == GENFUNCS_TRUE) {
			if ((!stricmp("CREATE", data_ptr)) ||
				(!stricmp("CREATE_CACHE", data_ptr)))
				control_ptr->operating_mode = DCR_OP_CREATE;
			else if ((!stricmp("RELOAD", data_ptr))  ||
				(!stricmp("RE_LOAD", data_ptr))       ||
				(!stricmp("REFRESH", data_ptr))       ||
				(!stricmp("RE_FRESH", data_ptr))      ||
				(!stricmp("RELOAD_CACHE", data_ptr))  ||
				(!stricmp("RE_LOAD_CACHE", data_ptr)) ||
				(!stricmp("REFRESH_CACHE", data_ptr)) ||
				(!stricmp("RE_FRESH_CACHE", data_ptr)))
				control_ptr->operating_mode = DCR_OP_RELOAD;
			else if ((!stricmp("UPDATE", data_ptr)) ||
				(!stricmp("UPDATE_CACHE", data_ptr)))
				control_ptr->operating_mode = DCR_OP_UPDATE;
			else {
				sprintf(error_text,
					"%s '%-*.*s' parameter ('%-.500s') --- expected '%s'.",
					"Invalid", ((int) arg_length), ((int) arg_length), this_arg,
					data_ptr, "{CREATE|RE[_]{FRESH|LOAD}|UPDATE}[_CACHE]");
				return_code = DCR_BAD_ARGS_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-CACHE_FILE=", "-CACHE_FILE_NAME=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->cache_file_name != NULL) {
				fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
					"The cache file name specification has changed",
					control_ptr->cache_file_name, data_ptr);
				free(control_ptr->cache_file_name);
				control_ptr->cache_file_name = NULL;
			}
			if ((control_ptr->cache_file_name = strdup(data_ptr)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr, "-CACHE_NAME=",
			NULL) == GENFUNCS_TRUE) {
			if (strlen(data_ptr) >= STR_sizeof(DCR_HEADER, cache_name)) {
				sprintf(error_text,
					"%s '%-*.*s' parameter ('%-.500s' = %u bytes) %s (%u).",
					"The length of the cache name specified with the",
					((int) arg_length), ((int) arg_length), this_arg, data_ptr,
					strlen(data_ptr), "exceeds the maximum length of a cache name",
					STR_sizeof(DCR_HEADER, cache_name) - 1);
				return_code = DCR_BAD_ARGS_FAILURE;
			}
			else {
				if (control_ptr->cache_name != NULL) {
					fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
						"The cache name specification has changed",
						control_ptr->cache_name, data_ptr);
					free(control_ptr->cache_name);
					control_ptr->cache_name = NULL;
				}
				if ((control_ptr->cache_name = strdup(data_ptr)) == NULL) {
					sprintf(error_text,
						"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
						"Unable to allocate memory for the", ((int) arg_length),
						((int) arg_length), this_arg, data_ptr,
						strlen(data_ptr) + 1);
					return_code = DCR_MEMORY_FAILURE;
				}
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-UPDATE_REFRESH_SECOND=", "-UPDATE_REFRESH_SECONDS=",
			"-UPDATE_RE_FRESH_SECOND=", "-UPDATE_RE_FRESH_SECONDS=",
			"-UPDATE_RELOAD_SECOND=", "-UPDATE_RELOAD_SECONDS=",
			"-UPDATE_RE_LOAD_SECOND=", "-UPDATE_RE_LOAD_SECONDS=", NULL) ==
			GENFUNCS_TRUE) {
			if (!(*data_ptr))
				control_ptr->refresh_seconds = 0L;
			else {
				tmp_double = atof(data_ptr);
				if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
					(tmp_double > LONG_MAX)) {
					sprintf(error_text,
						"%s '%-*.*s' ('%.500s') --- %s 0 to %lu, inclusive.",
						"Invalid", ((int) arg_length), ((int) arg_length), this_arg,
						data_ptr, "expected an integer value in the range of",
						LONG_MAX);
					return_code = DCR_BAD_ARGS_FAILURE;
				}
				else
					control_ptr->refresh_seconds = ((unsigned long) tmp_double);
			}
		}
		else if (DCR_BARG_SQLGroupBy(this_arg, &arg_length, &data_ptr,
			&control_ptr->sql_group_by_clause, &return_code, error_text) ==
			DCR_TRUE)
			;
		else if (DCR_BARG_SQLOrderBy(this_arg, &arg_length, &data_ptr,
			&control_ptr->sql_order_by_clause, &return_code, error_text) ==
			DCR_TRUE)
			;
		else if (DCR_BARG_SQLWhere(this_arg, &arg_length, &data_ptr,
			&control_ptr->sql_where_clause, &return_code, error_text) ==
			DCR_TRUE)
			;
		else if (DCR_BARG_DBLoadGran(this_arg, &arg_length, &data_ptr,
			&control_ptr->db_load_granularity, &return_code, error_text) ==
			DCR_TRUE)
			;
		else if (DCR_BARG_UpdateDateField(this_arg, &arg_length,
			&data_ptr, &control_ptr->update_date_field_name, &return_code,
			error_text) == DCR_TRUE)
			;
		else if (DCR_BARG_ClearAddedFields(this_arg, &arg_length,
			&data_ptr, &control_ptr->added_field_count,
			&control_ptr->added_field_list, &return_code, error_text) ==
			DCR_TRUE)
			;
		else if (DCR_BARG_ClearIndexSpec(this_arg, &arg_length,
			&data_ptr, &control_ptr->index_spec_count,
			&control_ptr->index_spec_list,  &return_code, error_text) ==
			DCR_TRUE)
			;
		else if (GEN_BARG_DBDebugFlag(this_arg, &arg_length, &data_ptr,
			&control_ptr->db_debugging_flag, &return_code, error_text) ==
			DCR_TRUE)
			;
		else if (GEN_BARG_SQLDebugFlag(this_arg, &arg_length, &data_ptr,
			&control_ptr->sql_debugging_flag, &return_code, error_text) ==
			DCR_TRUE)
			;
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-INDEX_TYPE=", "-INDEX_TYPES=", NULL) == GENFUNCS_TRUE) {
			if ((!stricmp("INDIRECT", data_ptr))        ||
				(!stricmp("INDIRECT_INDEX", data_ptr))   ||
				(!stricmp("INDIRECT_INDEXES", data_ptr)) ||
				(!stricmp("INDIRECT_INDEXS", data_ptr))  ||
				(!stricmp("INDIRECT_INDICES", data_ptr)))
				control_ptr->indirect_index_flag = DCR_TRUE;
				if ((!stricmp("EMBED", data_ptr))           ||
					(!stricmp("EMBED_INDEX", data_ptr))      ||
					(!stricmp("EMBED_INDEXES", data_ptr))    ||
					(!stricmp("EMBED_INDEXS", data_ptr))     ||
					(!stricmp("EMBED_INDICES", data_ptr))    ||
					(!stricmp("EMBEDDED", data_ptr))         ||
					(!stricmp("EMBEDDED_INDEX", data_ptr))   ||
					(!stricmp("EMBEDDED_INDEXES", data_ptr)) ||
					(!stricmp("EMBEDDED_INDEXS", data_ptr))  ||
					(!stricmp("EMBEDDED_INDICES", data_ptr)))
				control_ptr->indirect_index_flag = DCR_FALSE;
			else {
				sprintf(error_text,
					"%s '%-*.*s' parameter ('%-.500s') --- expected '%s'.",
					"Invalid", ((int) arg_length), ((int) arg_length), this_arg,
					data_ptr, "{INDIRECT|EMBED[DED]}[_IND{EX[[E]S]|ICES}]");
				return_code = DCR_BAD_ARGS_FAILURE;
			}
		}
		else if (GEN_ArgParseTruth(this_arg, &error_flag,
			&control_ptr->indirect_index_flag, gen_error_text, &arg_length,
			&data_ptr, "-INDIRECT_INDEX=", "-INDIRECT_INDICES=",
			"-INDIRECT_INDEXES=", "-INDIRECT_INDEXS=", NULL) == GENFUNCS_TRUE) {
			if (error_flag == GENFUNCS_TRUE) {
				nstrcpy(error_text, gen_error_text, DCR_MAX_ERROR_TEXT - 1);
				return_code = DCR_BAD_ARGS_FAILURE;
			}
		}
		else if (GEN_ArgParseTruth(this_arg, &error_flag,
			&control_ptr->load_data_flag, gen_error_text, &arg_length,
			&data_ptr, "-LOAD_FROM_DB=", NULL) == GENFUNCS_TRUE) {
			if (error_flag == GENFUNCS_TRUE) {
				nstrcpy(error_text, gen_error_text, DCR_MAX_ERROR_TEXT - 1);
				return_code = DCR_BAD_ARGS_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-LOG_DIR=", "-LOG_DIRECTORY=", "-LOGGING_DIR=",
			"-LOGGING_DIRECTORY=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->log_file_directory != NULL) {
				fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
					"The log file directory name has changed",
					control_ptr->log_file_directory, this_arg + arg_length);
				free(control_ptr->log_file_directory);
				control_ptr->log_file_directory = NULL;
			}
			if ((control_ptr->log_file_directory =
				strdup(this_arg + arg_length)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, this_arg + arg_length,
					strlen(this_arg + arg_length) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-META=", "-META_NAME=", "-META_DB=", "-META_DB_NAME=",
			"-META_DATA=", "-META_DATA_NAME=", "-META_DATA_BASE=",
			"-META_DATA_BASE_NAME=", NULL) == GENFUNCS_TRUE) {
			if (!(*data_ptr)) {
				sprintf(error_text, "The '%-*.*s' %s.", ((int) arg_length),
					((int) arg_length), this_arg,
					"parameter has an empty meta-data db specification");
				return_code = DCR_BAD_ARGS_FAILURE;
			}
			else {
				if (control_ptr->meta_data_db_string != NULL) {
					fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
						"The meta-data server/database specification has changed",
						control_ptr->meta_data_db_string, data_ptr);
					free(control_ptr->meta_data_db_string);
					free(control_ptr->safe_meta_data_db_string);
					control_ptr->meta_data_db_string      = NULL;
					control_ptr->safe_meta_data_db_string = NULL;
				}
				if (((control_ptr->meta_data_db_string = strdup(data_ptr)) ==
					NULL) || ((control_ptr->safe_meta_data_db_string =
					strdup(data_ptr)) == NULL)) {
					sprintf(error_text,
						"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
						"Unable to allocate memory for the", ((int) arg_length),
						((int) arg_length), this_arg, data_ptr,
						strlen(data_ptr) + 1);
					return_code = DCR_MEMORY_FAILURE;
				}
				else if ((chrcnt(data_ptr, ',') == 4) &&
					(data_ptr[strlen(data_ptr) - 1] != ',')) {
					while (data_ptr[strlen(data_ptr) - 1] != ',')
						data_ptr[strlen(data_ptr) - 1] = '\0';
					data_ptr[strlen(data_ptr)] = '?';
					strcpy(control_ptr->safe_meta_data_db_string, data_ptr);
				}
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr, "-DB=",
			"-DB_NAME=", "-DATA_BASE=", "-DATA_BASE=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->database_name != NULL) {
				fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
					"The table database name specification has changed",
					control_ptr->database_name, data_ptr);
				free(control_ptr->database_name);
				control_ptr->database_name = NULL;
			}
			if ((control_ptr->database_name = strdup(data_ptr)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr, "-DB_OWNER=",
			"-DB_OWNER_NAME=", "-DATA_BASE_OWNER=", "-DATA_BASE_OWNER_NAME=",
			"-OWNER=", "-OWNER_NAME=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->owner_name != NULL) {
				fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
					"The table owner name specification has changed",
					control_ptr->owner_name, data_ptr);
				free(control_ptr->owner_name);
				control_ptr->owner_name = NULL;
			}
			if ((control_ptr->owner_name = strdup(data_ptr)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr, "-DB_TABLE=",
			"-DB_TABLE_NAME=", "-DATA_BASE_TABLE=", "-DATA_BASE_TABLE_NAME=",
			"-TABLE=", "-TABLE_NAME=", NULL) == GENFUNCS_TRUE) {
			if (control_ptr->table_name != NULL) {
				fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
					"The table name specification has changed",
					control_ptr->table_name, data_ptr);
				free(control_ptr->table_name);
				control_ptr->table_name = NULL;
			}
			if ((control_ptr->table_name = strdup(data_ptr)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-DB_USER=", "-DB_USER_NAME=", "-DATA_BASE_USER=",
			"-DATA_BASE_USER_NAME=", "-USER=", "-USER_NAME=", NULL) ==
			GENFUNCS_TRUE) {
			if (control_ptr->db_user_name != NULL) {
				fprintf(stderr, "WARNING: %s from '%s' to '%s'.\n",
					"The server/database user name specification has changed",
					control_ptr->db_user_name, data_ptr);
				free(control_ptr->db_user_name);
				control_ptr->db_user_name = NULL;
			}
			if ((control_ptr->db_user_name = strdup(data_ptr)) == NULL) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-DB_PASSWORD=", "-DATA_BASE_PASSWORD=", "-PASSWORD=", NULL) ==
			GENFUNCS_TRUE) {
			if (control_ptr->db_pass_word != NULL) {
				fprintf(stderr, "WARNING: %s from '?' to '?'.\n",
					"The server/database password specification has changed");
				free(control_ptr->db_pass_word);
				control_ptr->db_pass_word = NULL;
			}
			if ((control_ptr->db_pass_word = strdup(data_ptr)) == NULL) {
				sprintf(error_text, "%s '%-*.*s' password ('?').",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg);
				return_code = DCR_MEMORY_FAILURE;
			}
			*data_ptr++ = '?';
			while (*data_ptr)
				*data_ptr++ = '\0';
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-INITIAL_ALLOC=", "-INITIAL_ALLOCATION=", NULL) == GENFUNCS_TRUE) {
			if (!(*data_ptr))
				control_ptr->initial_allocation_size = 0;
			else {
				tmp_double = atof(data_ptr);
				if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
					(tmp_double > UINT_MAX)) {
					sprintf(error_text,
						"%s '%-*.*s' ('%.500s') --- %s 0 to %u, inclusive.",
						"Invalid", ((int) arg_length), ((int) arg_length), this_arg,
						data_ptr, "expected an integer value in the range of",
						UINT_MAX);
					return_code = DCR_BAD_ARGS_FAILURE;
				}
				else
					control_ptr->initial_allocation_size =
						((unsigned int) tmp_double);
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr, "-ALLOC=",
			"-ALLOCATION=", NULL) == GENFUNCS_TRUE) {
			if (!(*data_ptr))
				control_ptr->allocation_size = 0;
			else {
				tmp_double = atof(data_ptr);
				if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
					(tmp_double > UINT_MAX)) {
					sprintf(error_text,
						"%s '%-*.*s' ('%.500s') --- %s 0 to %u, inclusive.",
						"Invalid", ((int) arg_length), ((int) arg_length), this_arg,
						data_ptr, "expected an integer value in the range of",
						UINT_MAX);
					return_code = DCR_BAD_ARGS_FAILURE;
				}
				else
					control_ptr->allocation_size = ((unsigned int) tmp_double);
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-ADD_FIELD=", "-ADD_FIELDS=", "-ADDED_FIELD=", "-ADDED_FIELDS=",
			NULL) == GENFUNCS_TRUE) {
			if (!(*data_ptr))
				fprintf(stderr, "%s '%s' parameter encountered --- ignored.\n",
					"Empty added field specification", this_arg);
			else if (strl_append(&control_ptr->added_field_count,
				&control_ptr->added_field_list, data_ptr) != STRFUNCS_SUCCESS) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr,
			"-INDEX_SPEC=", "-INDEX_SPECS=", "-INDEX_SPECIFICATION=",
			"-INDEX_SPECIFICATIONS=", NULL) == GENFUNCS_TRUE) {
			if (!(*data_ptr))
				fprintf(stderr, "%s '%s' parameter encountered --- ignored.\n",
					"Empty index specification", this_arg);
			else if (strl_append(&control_ptr->index_spec_count,
				&control_ptr->index_spec_list, data_ptr) != STRFUNCS_SUCCESS) {
				sprintf(error_text,
					"%s '%-*.*s' ('%-.500s') --- %u bytes required.",
					"Unable to allocate memory for the", ((int) arg_length),
					((int) arg_length), this_arg, data_ptr, strlen(data_ptr) + 1);
				return_code = DCR_MEMORY_FAILURE;
			}
		}
		else if (GEN_ArgParse(this_arg, &arg_length, &data_ptr, "-MAX_ROW=",
			"-MAX_ROW_COUNT=", "-MAX_ROWS=", "-MAX_ROWS_COUNT=",
			"-MAX_RECORD=", "-MAX_RECORD_COUNT=", "-MAX_RECORDS=",
			"-MAX_RECORDS_COUNT=", "-MAXIMUM_ROW=",
			"-MAXIMUM_ROW_COUNT=", "-MAXIMUM_ROWS=", "-MAXIMUM_ROWS_COUNT=",
			"-MAXIMUM_RECORD=", "-MAXIMUM_RECORD_COUNT=", "-MAXIMUM_RECORDS=",
			"-MAXIMUM_RECORDS_COUNT=", NULL) == GENFUNCS_TRUE) {
			if (!(*data_ptr))
				control_ptr->maximum_row_count = 0;
			else {
				tmp_double = atof(data_ptr);
				if ((tmp_double < 0.0) || (tmp_double != floor(tmp_double)) ||
					(tmp_double > UINT_MAX)) {
					sprintf(error_text,
						"%s '%-*.*s' ('%.500s') --- %s 0 to %u, inclusive.",
						"Invalid", ((int) arg_length), ((int) arg_length), this_arg,
						data_ptr, "expected an integer value in the range of",
						UINT_MAX);
					return_code = DCR_BAD_ARGS_FAILURE;
				}
				else
					control_ptr->maximum_row_count = ((unsigned int) tmp_double);
			}
		}
		else {
			sprintf(error_text,
				"Invalid command-line argument encountered ('%-.500s%s').",
				this_arg, (strlen(this_arg) > 500) ? "<<<MORE>>>" : "");
			return_code = DCR_BAD_ARGS_FAILURE;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

static void DCR_RUN_Init(control_ptr)
DCR_RUN_CONTROL *control_ptr;
{
	memset(control_ptr, '\0', sizeof(*control_ptr));

	control_ptr->program_name             = NULL;
	control_ptr->short_program_name       = NULL;
	control_ptr->syslog_program_name      = NULL;
	control_ptr->system_version_number    = STR_VERSION_NUMBER_NULL;
	control_ptr->version_number           = STR_VERSION_NUMBER_NULL;
	control_ptr->system_version_string[0] = '\0';
	control_ptr->version_string[0]        = '\0';
	control_ptr->process_id               = 0;
	control_ptr->host_name[0]             = '\0';
	control_ptr->current_directory[0]     = '\0';
	control_ptr->help_flag                = DCR_FALSE;
	control_ptr->version_flag             = DCR_FALSE;
	control_ptr->operating_mode           = DCR_OP_CREATE;
	control_ptr->signal_received_flag     = GENFUNCS_FALSE;
	control_ptr->queue_signal_flag        = GENFUNCS_FALSE;
	control_ptr->shut_down_flag           = GENFUNCS_FALSE;
	control_ptr->db_debugging_flag        = DCR_FALSE;
	control_ptr->sql_debugging_flag       = DCR_FALSE;
	control_ptr->refresh_seconds          = 0L;
	control_ptr->cache_ptr                = NULL;
	control_ptr->cache_index              = 0;
	control_ptr->cache_file_name          = NULL;
	control_ptr->cache_name               = NULL;
	control_ptr->log_file_directory       = NULL;
	control_ptr->log_file_name            = NULL;
	control_ptr->log_file_mfile_ptr       = NULL;
	control_ptr->meta_data_db_string      = NULL;
	control_ptr->safe_meta_data_db_string = NULL;
	control_ptr->database_name            = NULL;
	control_ptr->owner_name               = NULL;
	control_ptr->table_name               = NULL;
	control_ptr->db_user_name             = NULL;
	control_ptr->db_pass_word             = NULL;
	control_ptr->sql_where_clause         = NULL;
	control_ptr->sql_group_by_clause      = NULL;
	control_ptr->sql_order_by_clause      = NULL;
	control_ptr->update_date_field_name   = NULL;
	control_ptr->maximum_row_count        = 0;
	control_ptr->added_field_count        = 0;
	control_ptr->added_field_list         = NULL;
	control_ptr->index_spec_count         = 0;
	control_ptr->index_spec_list          = NULL;
	control_ptr->indirect_index_flag      = DCR_TRUE;
	control_ptr->load_data_flag           = DCR_TRUE;
	control_ptr->db_load_granularity      = 0;
	control_ptr->initial_allocation_size  = 0;
	control_ptr->allocation_size          = 0;
}
/*	***********************************************************************	*/

static void DCR_RUN_End(control_ptr, signal_number, exit_code_ptr,
	message_buffer)
DCR_RUN_CONTROL *control_ptr;
int                    signal_number;
int                   *exit_code_ptr;
const char            *message_buffer;
{
	unsigned int   count_1;
	unsigned long  total_usecs;
	struct timeval overhead_interval;
	struct timeval total_interval;
	struct rusage  rusage_data;
	char           tmp_buffer[512];
	char           tmp_interval[256];
	char           tmp_stat_name[DCR_MAX_STAT_NAME + 1];

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Get the end time of the program . . .								*/
	/*	**************************************************************	*/
	SDTIF_GetTimeUSecs(&control_ptr->end_time);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Inform the user that we're bailing out . . .						*/
	/*	**************************************************************	*/
	if (control_ptr->log_context.mfile_ptr != NULL) {
		MFILE_LogSepEqualCharContext(&control_ptr->log_context);
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Exiting . . .\n");
	}
	else if ((control_ptr->log_context.file_flag != MFILE_TRUE) &&
		(control_ptr->help_flag != DCR_TRUE) &&
		(control_ptr->version_flag != DCR_TRUE))
		fprintf(stderr, "Exiting . . .\n");
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Show cache statistics . . .											*/
	/*	**************************************************************	*/
	if ((control_ptr->cache_ptr != NULL) &&
		(control_ptr->log_file_mfile_ptr != NULL)) {
		MFILE_LogSepEqualCharContext(&control_ptr->log_context);
		for (count_1 = 0; count_1 < DCR_STAT_COUNT; count_1++) {
			sprintf(tmp_buffer, "%s Time",
				strcpy(tmp_stat_name,
				initcaps(DCR_GetStatName(((int) count_1), tmp_stat_name))));
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "%-28.28s: %s\n", tmp_buffer,
				SDTIF_FormatInterval_timeval(&((DCR_HEADER *) control_ptr->
				cache_ptr->header_ptr)->stat_list[count_1].total_interval,
				tmp_interval));
		}
		MFILE_LogSepEqualCharContext(&control_ptr->log_context);
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Show timing statistics . . .											*/
	/*	**************************************************************	*/
	MFILE_ShowExecTime(&control_ptr->start_time, &control_ptr->end_time,
		&control_ptr->overhead_end_time, &control_ptr->log_context);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Show system resource usage . . .										*/
	/*	**************************************************************	*/
	MFILE_ShowExecRUsage(&control_ptr->log_context);
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Free the memory allocated to store the program name . . .	*/
	/*	**************************************************************	*/
	if (control_ptr->program_name != NULL) {
		free(control_ptr->program_name);
		control_ptr->program_name = NULL;
	}
	if (control_ptr->short_program_name != NULL) {
		free(control_ptr->short_program_name);
		control_ptr->short_program_name = NULL;
	}
	if (control_ptr->syslog_program_name != NULL) {
		free(control_ptr->syslog_program_name);
		control_ptr->syslog_program_name = NULL;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Free database-specific data . . .									*/
	/*	**************************************************************	*/
	if (control_ptr->meta_data_db_string != NULL) {
		free(control_ptr->meta_data_db_string);
		control_ptr->meta_data_db_string = NULL;
	}
	if (control_ptr->safe_meta_data_db_string != NULL) {
		free(control_ptr->safe_meta_data_db_string);
		control_ptr->safe_meta_data_db_string = NULL;
	}
	if (control_ptr->database_name != NULL) {
		free(control_ptr->database_name);
		control_ptr->database_name = NULL;
	}
	if (control_ptr->owner_name != NULL) {
		free(control_ptr->owner_name);
		control_ptr->owner_name = NULL;
	}
	if (control_ptr->table_name != NULL) {
		free(control_ptr->table_name);
		control_ptr->table_name = NULL;
	}
	if (control_ptr->db_user_name != NULL) {
		free(control_ptr->db_user_name);
		control_ptr->db_user_name = NULL;
	}
	if (control_ptr->db_pass_word != NULL) {
		free(control_ptr->db_pass_word);
		control_ptr->db_pass_word = NULL;
	}
	/*	**************************************************************	*/

	strl_remove_all(&control_ptr->added_field_count,
		&control_ptr->added_field_list);

	strl_remove_all(&control_ptr->index_spec_count,
		&control_ptr->index_spec_list);

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		If we were in the middle of performing a cache re-load or	*/
	/*	update, we remove the temporary file in which the records were	*/
	/*	stored . . .																	*/
	/*	**************************************************************	*/
	if ((control_ptr->cache_ptr != NULL) &&
		(control_ptr->cache_ptr->reload_mfile_ptr != NULL)) {
		if (control_ptr->log_file_mfile_ptr != NULL)
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE,
		"Closing the temporary re-load/update database record file '%s'.\n",
				control_ptr->cache_ptr->reload_mfile_ptr->file_name);
		munlink(control_ptr->cache_ptr->reload_mfile_ptr);
		control_ptr->cache_ptr->reload_mfile_ptr = NULL;
	}
	/*	**************************************************************	*/

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*	**************************************************************	*/
	if (control_ptr->cache_ptr != NULL) {
		if (control_ptr->log_file_mfile_ptr != NULL)
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Closing the cache file '%s'.\n",
				control_ptr->cache_ptr->cache_file_name);
		DCR_CloseAllCaches(&control_ptr->cache_control_data);
		control_ptr->cache_ptr = NULL;
	}
	/*	**************************************************************	*/

	if (control_ptr->sql_where_clause != NULL) {
		free(control_ptr->sql_where_clause);
		control_ptr->sql_where_clause = NULL;
	}

	if (control_ptr->sql_group_by_clause != NULL) {
		free(control_ptr->sql_group_by_clause);
		control_ptr->sql_group_by_clause = NULL;
	}

	if (control_ptr->sql_order_by_clause != NULL) {
		free(control_ptr->sql_order_by_clause);
		control_ptr->sql_order_by_clause = NULL;
	}

	if (control_ptr->update_date_field_name != NULL) {
		free(control_ptr->update_date_field_name);
		control_ptr->update_date_field_name = NULL;
	}

	if (control_ptr->cache_file_name != NULL) {
		free(control_ptr->cache_file_name);
		control_ptr->cache_file_name = NULL;
	}

	if (control_ptr->cache_name != NULL) {
		free(control_ptr->cache_name);
		control_ptr->cache_name = NULL;
	}

	/*	**************************************************************	*/
	/*	**************************************************************	*/
	/*		Close the log file (if open) and free-up any memory which	*/
	/*	associated with it . . .													*/
	/*	**************************************************************	*/
	if (control_ptr->log_context.mfile_ptr != NULL) {
		MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
			MFILE_FALSE, "Closing the log file '%s'.\n",
			control_ptr->log_file_name);
		MFILE_LogSepEndLogContext(&control_ptr->log_context);
		control_ptr->log_file_mfile_ptr->file_size =
			control_ptr->log_file_mfile_ptr->current_offset;
		mclose(control_ptr->log_context.mfile_ptr);
		control_ptr->log_context.mfile_ptr = NULL;
		control_ptr->log_context.file_ptr  = NULL;
	}
	if (control_ptr->log_file_directory != NULL) {
		free(control_ptr->log_file_directory);
		control_ptr->log_file_directory = NULL;
	}
	if (control_ptr->log_file_name != NULL) {
		free(control_ptr->log_file_name);
		control_ptr->log_file_name = NULL;
	}
	/*	**************************************************************	*/

	DCR_RUN_Init(control_ptr);
}
/*	***********************************************************************	*/

static int DCR_RUN_CallBack(cache_ptr, call_back_type,
	post_operation_flag, index_method, operation_flags, operation_count,
	operation_ptr, stat_ptr, return_code, error_text)
DCR_CACHE      *cache_ptr;
unsigned long   call_back_type;
int             post_operation_flag;
unsigned int    index_method;
int             operation_flags;
unsigned int    operation_count;
void           *operation_ptr;
DCR_STAT *stat_ptr;
int             return_code;
char           *error_text;
{
	DCR_RUN_CONTROL *control_ptr;
	struct timeval         tmp_timeval;
	char                   tmp_buffer_1[100];
	char                   tmp_buffer_2[100];

	control_ptr = DCR_GetUserDataPtr(cache_ptr, 0);

	if (call_back_type == DCR_CB_BULK_INSERT) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Bulk inserted %u records in %s time (%s %s).\n",
				operation_count,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_BULK_SEARCH) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE,
				"Bulk searched %u records (%u %s, %u %s) in %s time (%s %s).\n",
				operation_count, cache_ptr->last_search_update_count, "inserted",
				cache_ptr->last_search_insert_count, "updated",
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_INDEX_CACHE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Indexed %u %s %u in %s time (%s %s).\n",
				operation_count, "records on index number", index_method,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_SORT_CACHE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Indexed %u %s %u in %s time (%s %s).\n",
				operation_count, "records on index number", index_method,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_RESIZE_CACHE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Re-sized the cache file to %lu bytes.\n",
				((DCR_HEADER *) cache_ptr->header_ptr)->total_cache_size);
	}
	else if (call_back_type == DCR_CB_INITIAL_LOAD) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Performed an database initial load of %u records.\n",
				operation_count);
	}
	else if (call_back_type == DCR_CB_RELOAD) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Performed an database re-load of %u records.\n",
				operation_count);
	}
	else if (call_back_type == DCR_CB_UPDATE) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "%s %u %s '%s' %s '%s'.\n",
				"Performed an database update load of", operation_count,
				"records with an", cache_ptr->update_date_field_name,
				"column greater than or equal to",
				DBC_SYB_FMT_SYBDATETIME_SQL(&cache_ptr->old_max_update_date,
					tmp_buffer_1));
	}
	else if (call_back_type == DCR_CB_ALLOC_CHUNK) {
		;
	}
	else if (call_back_type == DCR_CB_CHECK_INDEX_1) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Checked %u %s %u in %s time (%s %s).\n",
				operation_count, "index entries on index number", index_method,
				SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}
	else if (call_back_type == DCR_CB_CHECK_INDEX_2) {
		if ((post_operation_flag == DCR_TRUE) && (return_code == DCR_SUCCESS) &&
			(stat_ptr != NULL))
			MFILE_LogMessageContext(&control_ptr->log_context, NULL, LOG_INFO,
				MFILE_FALSE, "Checked %u %s %u in %s time (%s %s).\n",
				operation_count, "index entries and records on index number",
				index_method, SDTIF_FormatInterval_timeval(&stat_ptr->last_interval,
				tmp_buffer_1),
				SDTIF_FormatInterval_timeval(SDTIF_GetPerInterval_timeval(
				&stat_ptr->last_interval, stat_ptr->last_count, &tmp_timeval),
				tmp_buffer_2), "per record");
	}

	return(DCR_SUCCESS);
}
/*	***********************************************************************	*/

static int DCR_RUN_CriticalCallBack(cache_ptr, call_back_type,
	post_operation_flag, operation_flags, operation_count, operation_ptr,
	return_code, error_text)
DCR_CACHE     *cache_ptr;
unsigned long  call_back_type;
int            post_operation_flag;
int            operation_flags;
unsigned int   operation_count;
void          *operation_ptr;
int            return_code;
char          *error_text;
{
	DCR_RUN_CONTROL *control_ptr;

	control_ptr = DCR_GetUserDataPtr(cache_ptr, 0);

	if (post_operation_flag == DCR_FALSE)
		control_ptr->queue_signal_flag = GENFUNCS_TRUE;
	else if (control_ptr->signal_received_flag == GENFUNCS_TRUE) {
		DCR_RUN_End(control_ptr, 0, NULL, error_text);
		exit(-1);
	}
	else
		control_ptr->queue_signal_flag = GENFUNCS_FALSE;

	return(DCR_SUCCESS);
}
/*	***********************************************************************	*/

