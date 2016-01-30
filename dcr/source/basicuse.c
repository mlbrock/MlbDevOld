/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Constructs usage text for a variety of cache-related
								command-line parameters.

	Revision History	:	1994-12-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1994 - 2016.
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
#include <math.h>
#include <string.h>

#include "dcr.h"

/*	***********************************************************************	*/

int DCR_BUSE_AddedFields(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         = "-ADD[ED]_FIELD[S]=<field-spec>";
	static char       *arg_usage_list[] = {
	"		Specifies a non-database field to be included in the cache.",
	"\n",
	"		The <field-spec> component of this parameter has the following \
syntax:",
	"\n",
	"			<field-name>:[<short-name>]:[<count>]:<type-spec>",
	"\n",
	"		The sub-components of the <field-spec> component have the following \
semantics:",
	"\n",
	"			o The <field-name> sub-component specifies the name by which \
this field be identified within the cache.",
	"\n",
	"			o The <short-name> sub-component specifies an alias for the \
<field-name> sub-component. If not specified, the <field-name> will be \
copied into the <short-name>.",
	"\n",
	"			o The optional <count> sub-component specifies the number of \
<type-spec> sub-components of which this field will be comprised. The \
minimum value is '1'. If not specified, it defaults to '1'.",
	"\n",
	"			o The <type-spec> sub-component specifies the \
architecture-specific types which are to constitute the field. It consists \
of one or more member definitions, separated by commas (','). Each member \
definition has the following form:",
	"\n",
	"			  {b|c|C|s|S|i|I|l|L|f|d}",
	"\n",
	"			Where the letters specify 'unsigned byte', 'signed char', \
'unsigned char', 'signed short', 'unsigned short', 'signed int', 'unsigned \
int', 'signed long', 'unsigned long', 'float', and 'double'.",
	"\n",
	"			A member definition may be followed by an optional array \
specifier in the form:",
	"\n",
	"			  <member-definition>[<array-length>]",
	"\n",
	"		The optional <array-length> sub-component of this parameter \
specifies the number of elements the added field is to have. The minimum \
value is '1' and maximum value is '32767'.",
	"\n",
	"		For example, to create two added fields to store a text string \
32 characters in length and a double, you would use the following \
parameters:",
	"\n",
	"			-ADDED_FIELD=text_field_name::32:schar",
	"			-ADDED_FIELD=numeric_value:::double",
	"\n",
	"		This parameter is effective only if the cache is to be created for \
the first time. If the cache already exists, it is ignored.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_Alloc(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         = "-ALLOC[ATION]=<number>";
	static char       *arg_usage_list[] = {
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
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_CacheFile(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         = "-CACHE_FILE[_NAME]=<file-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the name of the cache file to be opened.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_CacheName(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         = "-CACHE_NAME=<cache-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the name of the cache (NOT the cache file-name).",
	"\n",
	"		This parameter is required if the cache is to be created for the \
first time. If the cache already exists, it is ignored.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_ClearAddedFields(base_arg_ptr, optional_flag,
	extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-{CLEAR|DELETE|REMOVE}_ADD[ED]_FIELD[S]=<boolean>";
	static char       *arg_usage_list[] = {
	"		If encountered on the command-line, any fields specified so far \
by the '-ADDED_FIELDS=' parameter will be cleared.",
	"\n",
	"		The <boolean> component of this parameter has the following syntax:",
	"\n",
	"			{ ON | OFF | TRUE | FALSE | YES | NO }",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_ClearIndexSpec(base_arg_ptr, optional_flag,
	extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-{CLEAR|DELETE|REMOVE}_INDEX_SPEC[IFICATION][S]=<boolean>";
	static char       *arg_usage_list[] = {
	"		If encountered on the command-line, any fields specified so far \
by the '-INDEX_SPECIFICATION=' parameter will be cleared.",
	"\n",
	"		The <boolean> component of this parameter has the following syntax:",
	"\n",
	"			{ ON | OFF | TRUE | FALSE | YES | NO }",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_DBDatabaseName(base_arg_ptr, optional_flag,
	extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-{DB|DATA[_]BASE}[_NAME]=<database-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the database in which the table to be cached resides.",
	"\n",
	"		This parameter is required if the cache is to be created for the \
first time. If the cache already exists, it is ignored.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_DBLoadGran(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-{DB|DATA[_]BASE}_LOAD_GRAN[ULAR[ITY]]=<number>";
	static char       *arg_usage_list[] = {
	"		Specifies the memory-mapped allocation granularity to be used when \
allocating space for rows loded from the database.",
	"\n",
	"		If the <number> component of this parameter is not present or is \
equal to zero ('0') the system will use the default allocation granularity. \
At present, this 10,000 rows.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_DBOwnerName(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-{DB|DATA[_]BASE}_OWNER[_NAME]=<owner-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the owner of the table to be cached.",
	"\n",
	"		This parameter is required if the cache is to be created for the \
first time. If the cache already exists, it is ignored.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_DBPassword(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-{DB|DATA[_]BASE}_PASS[W[OR]D][_NAME]=<db-pass-word>";
	static char       *arg_usage_list[] = {
	"		Specifies the password which is to be used for login to the \
databases used in the operation of the program.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_DBTableName(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-{DB|DATA[_]BASE}_TABLE[_NAME]=<table-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the name of the table to be cached.",
	"\n",
	"		This parameter is required if the cache is to be created for the \
first time. If the cache already exists, it is ignored.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_DBUserName(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-{DB|DATA[_]BASE}_USER[_NAME]=<db-user-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the user name which is to be used for login to the \
databases used in the operation of the program.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_IndexSpec(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-INDEX_SPEC[IFICATION][S]=<index-spec>";
	static char       *arg_usage_list[] = {
	"		Specifies the fields which are to be used to construct a cache \
index. The <index-spec> component of this parameter has the following \
structure:",
	"\n",
	"			<index-spec> := <index-name>:<field-name>[,<field-name> . . .]",
	"\n",
	"		At least one '-INDEX_SPECIFICATION=' parameter is required if the \
cache is to be created for the first time. It is ignored if the cache \
already exists.",
	"\n",
	"		This parameter may occur multiple times on the command-line; if it \
does, each instance is taken as specifing the creation of a different index. \
Note, however, that each <index-name> must be unique.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_IndexType(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-INDEX_TYPE[S]={INDIRECT|EMBED[DED]}[_IND{EX[[E]S]|ICES}]";
	static char       *arg_usage_list[] = {
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
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_IndirectIndex(base_arg_ptr, optional_flag,
	extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-INDIRECT_IND{EX[[E]S]|ICES}={ ON | OFF | TRUE | FALSE | YES | NO }";
	static char       *arg_usage_list[] = {
	"		Specifies whether the cache is to be created using indirect \
indices.",
	"\n",
	"		This parameter duplicates the functionality of the '-INDEX_TYPE=' \
paramter (see above).",
	"\n",
	"		The default for this parameter is 'ON' (that is, indirect indices).",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_InitialAlloc(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         = "-INITIAL_ALLOC[ATION]=<number>";
	static char       *arg_usage_list[] = {
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
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_LoadFromDB(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-LOAD_FROM_DB={ ON | OFF | TRUE | FALSE | YES | NO }";
	static char       *arg_usage_list[] = {
	"		Specifies whether the cache is to be created with data populated \
from the database.",
	"\n",
	"		The default for this parameter is 'ON'.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_MaxRows(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-MAX[IMUM]_{ROW[S]|RECORD[S]}[_COUNT]=<max-row-count>";
	static char       *arg_usage_list[] = {
	"		Specifies the maximum number of rows to be read from the database \
during the initial create, refresh, or update database load. If the \
<max-row-count> component of the option is not present or is equal to zero \
('0'), no maximum will be imposed while perfoming the such loads.",
	"\n",
/*
	"		This parameter is effective only if the cache is to be created for \
the first time. If the cache already exists, it is ignored.",
	"\n",
*/
	"		The default for this option is '0'.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_OperationMode(base_arg_ptr, optional_flag,
	extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-OPERATI{ON|NG}[_MODE]={CREATE|RE[_]{FRESH|LOAD}|UPDATE}[_CACHE]";
	static char       *arg_usage_list[] = {
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
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_RefreshSeconds(base_arg_ptr, optional_flag,
	extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-UPDATE_RE[_]{FRESH|LOAD}_SECOND[S]=<time-in-seconds>";
	static char       *arg_usage_list[] = {
	"		Specifies the time in seconds between automated updates of the \
cache from the database.",
	"\n",
	"		If this parameter is specified as a positive non-zero value, the \
cache will be refreshed with records from the database having an \
'updatedate' column equal to or greater than the most-recent 'updatedate' \
in the cache. The refresh will be performed every <time-in-seconds> seconds.",
	"\n",
	"		If the <time-in-seconds> component of this parameter is not \
present or is equal to zero ('0') the system will not refresh the cache from \
the database automatically.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_SQLGroupBy(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-[SQL_]GROUP_BY[_CLAUSE]=<group-by-clause>";
	static char       *arg_usage_list[] = {
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
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_SQLOrderBy(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-[SQL_]ORDER_BY[_CLAUSE]=<order-by-clause>";
	static char       *arg_usage_list[] = {
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
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_SQLWhere(base_arg_ptr, optional_flag, extra_usage_list,
	usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-[SQL_]WHERE[_CLAUSE]=<where-clause>";
	static char       *arg_usage_list[] = {
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
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_UpdateDateField(base_arg_ptr, optional_flag,
	extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
		"-UPDATE_DATE_{FIELD|COLUMN}[_NAME]=<db-column-name>";
	static char       *arg_usage_list[] = {
	"		Specifies the column name to use when refreshing cache records \
from the database according to the database update-date.",
	"\n",
	"		If this parameter is not specified and updates of the cache from \
the database are to be performed, the default update-date column name will \
be used ('updatedate').",
	"\n",
	"		It is an error if the specified column name is not in the cache.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

int DCR_BUSE_UpdateMaxRows(base_arg_ptr, optional_flag,
	extra_usage_list, usage_count, usage_list, error_text)
const char     *base_arg_ptr;
int             optional_flag;
char          **extra_usage_list;
unsigned int   *usage_count;
char         ***usage_list;
char           *error_text;
{
	static const char *arg_name         =
"-UPDATE_RE[_]{FRESH|LOAD}_MAX[IMUM]_{ROW[S]|RECORD[S]}[_COUNT]=<max-row-count>";
	static char       *arg_usage_list[] = {
	"		Specifies the maximum number of rows to be read from the database \
during the update database loads. If the <max-row-count> component of the \
option is not present or is equal to zero ('0'), no maximum will be imposed \
while perfoming the such loads.",
	"\n",
	"		This parameter is effective only if the cache is to be refreshed \
from the database periodically (as specified by the \
'-UPDATE_REFRESH_SECONDS=' parameter).",
	"\n",
	"		The default for this option is '0'.",
	"\n",
	NULL
};

	return(GEN_BUSE_BasicConstruct(base_arg_ptr, arg_name, optional_flag,
		arg_usage_list, extra_usage_list, usage_count, usage_list, error_text));
}
/*	***********************************************************************	*/

