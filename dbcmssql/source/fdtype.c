/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Retrieves information about the columns which
								comprise a specified table.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <string.h>

#include "dbcmssql.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const DBC_MSSQL_TYPE DBC_MSSQL_TypeList[] = {
	{	SQLBINARY,		1,	"DBBINARY",		"BINARYBIND",			0,	"B",	},
	{	SQLBIT,			1,	"DBBIT",			"BITBIND",				1,	"B"	},
	{	SQLCHAR,			1,	"DBCHAR",		"NTBSTRINGBIND",		0,	"c"	},
	{	SQLTEXT,			1,	"DBCHAR",		"CHARBIND",				0,	"c"	},
	{	SQLIMAGE,		1,	"DBBINARY",		"BINARYBIND",			0,	"B"	},
	{	SQLINT1,			1,	"DBTINYINT",	"TINYBIND",				1,	"C"	},
	{	SQLINT2,			2,	"DBSMALLINT",	"SMALLBIND",			1,	"s"	},
	{	SQLINT4,			4,	"DBINT",			"INTBIND",				1,	"l"	},
	{	SQLFLT4,			4,	"DBFLT4",		"FLT4BIND",				1,	"f"	},
	{	SQLFLT8,			8,	"DBFLT8",		"FLT8BIND",				1,	"d"	},
	{	SQLMONEY,		8,	"DBMONEY",		"MONEYBIND",			1,	"l,L"	},
	{	SQLMONEY4,		4,	"DBMONEY4",		"SMALLMONEYBIND",		1,	"l"	},
	{	SQLDATETIME,	8,	"DBDATETIME",	"DATETIMEBIND",		1,	"l,l"	},
	{	SQLDATETIM4,	4,	"DBDATETIM4",	"SMALLDATETIBIND",	1,	"S,S"	}
};
COMPAT_EXTERN_DATA_DEF const unsigned int    DBC_MSSQL_TypeCount  =
	sizeof(DBC_MSSQL_TypeList) / sizeof(DBC_MSSQL_TypeList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
const DBC_MSSQL_TYPE *DBC_MSSQL_FIND_TypeByType(in_type, found_index)
int           in_type;
unsigned int *found_index;
{
	unsigned int        count_1;
	const DBC_MSSQL_TYPE *type_ptr = NULL;

	for (count_1 = 0; count_1 < DBC_MSSQL_TypeCount; count_1++) {
		if (in_type == DBC_MSSQL_TypeList[count_1].type) {
			if (found_index != NULL)
				*found_index = count_1;
			type_ptr = DBC_MSSQL_TypeList + count_1;
			break;
		}
	}

	return(type_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
const DBC_MSSQL_TYPE *DBC_MSSQL_FIND_TypeByNames(in_name, in_bind,
	found_index)
const char   *in_name;
const char   *in_bind;
unsigned int *found_index;
{
	unsigned int        count_1;
	const DBC_MSSQL_TYPE *type_ptr = NULL;

	for (count_1 = 0; count_1 < DBC_MSSQL_TypeCount; count_1++) {
		if ((!strcmp(in_name, DBC_MSSQL_TypeList[count_1].name)) &&
			(!strcmp(in_bind, DBC_MSSQL_TypeList[count_1].bind))) {
			if (found_index != NULL)
				*found_index = count_1;
			type_ptr = DBC_MSSQL_TypeList + count_1;
			break;
		}
	}

	return(type_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
const DBC_MSSQL_TYPE *DBC_MSSQL_FIND_TypeByTypeSpec(in_type_spec, found_index)
const char   *in_type_spec;
unsigned int *found_index;
{
	unsigned int        count_1;
	const DBC_MSSQL_TYPE *type_ptr = NULL;

	for (count_1 = 0; count_1 < DBC_MSSQL_TypeCount; count_1++) {
		if (!strcmp(in_type_spec, DBC_MSSQL_TypeList[count_1].type_spec)) {
			if (found_index != NULL)
				*found_index = count_1;
			type_ptr = DBC_MSSQL_TypeList + count_1;
			break;
		}
	}

	return(type_ptr);
}
/*	***********************************************************************	*/

