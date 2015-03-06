/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether a table name is a Microsoft SQL
								Server system table.

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

/* *********************************************************************** */
/* *********************************************************************** */
/* *********************************************************************** */
COMPAT_EXTERN_DATA_DEF const char         *DBC_MSSQL_SystemTableList[] = {
	"sysalternates",
#ifdef CS_PUBLIC
	"sysauditoptions",
#endif /* #ifdef CS_PUBLIC --- Sysbase System 10 +: 'sybsecurity' Database	*/
#ifdef CS_PUBLIC
	"sysaudits",
#endif /* #ifdef CS_PUBLIC --- Sysbase System 10 +: 'sybsecurity' Database	*/
	"syscharsets",
	"syscolumns",
	"syscomments",
	"sysconfigures",
#ifdef CS_PUBLIC
	"sysconstraints",
#endif /* #ifdef CS_PUBLIC --- Sysbase System 10 +									*/
	"syscurconfigs",
	"sysdatabases",
	"sysdepends",
	"sysdevices",
	"sysengines",
#ifndef CS_PUBLIC
	"sysgams",
#endif /* #ifndef CS_PUBLIC --- Microsoft SQL Server 4.9.2						*/
	"sysindexes",
	"syskeys",
#ifdef CS_PUBLIC
	"syslabels",
#endif /* #ifdef CS_PUBLIC --- Sysbase System 10 +									*/
	"syslanguages",
	"syslocks",
#ifdef CS_PUBLIC
	"sysloginroles",
#endif /* #ifdef CS_PUBLIC --- Sysbase System 10 +									*/
	"syslogins",
	"syslogs",
	"sysmessages",
#ifndef CS_PUBLIC
	"sysmonitors",
#endif /* #ifndef CS_PUBLIC --- Microsoft SQL Server 4.9.2						*/
	"sysobjects",
	"sysprocedures",
	"sysprocesses",
	"sysprotects",
	"sysremotelogins",
#ifdef CS_PUBLIC
	"sysroles",
#endif /* #ifdef CS_PUBLIC --- Sysbase System 10 + 								*/
	"syssegments",
	"sysservers",
#ifdef CS_PUBLIC
	"syssrvroles",
#endif /* #ifdef CS_PUBLIC --- Sysbase System 10 +									*/
#ifndef CS_PUBLIC
	"systestlog",
#endif /* #ifndef CS_PUBLIC --- Microsoft SQL Server 4.9.2						*/
#ifdef CS_PUBLIC
	"systhresholds",
#endif /* #ifdef CS_PUBLIC --- Sysbase System 10 +									*/
	"systypes",
	"sysusages",
	"sysusermessages",
	"sysusers"
};
COMPAT_EXTERN_DATA_DEF const unsigned int  DBC_MSSQL_SystemTableCount  =
	sizeof(DBC_MSSQL_SystemTableList) / sizeof(DBC_MSSQL_SystemTableList[0]);
/* *********************************************************************** */

/* *********************************************************************** */
int DBC_MSSQL_IsSystemTable(table_name)
const char *table_name;
{
	return((strl_find(DBC_MSSQL_SystemTableCount,
		((char **) DBC_MSSQL_SystemTableList), table_name, NULL) ==
		STRFUNCS_ITEM_FOUND) ? DBC_TRUE : DBC_FALSE);
}
/* *********************************************************************** */

