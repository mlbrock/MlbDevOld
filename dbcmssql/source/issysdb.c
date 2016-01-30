/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Microsoft SQL Server Support Functions Library Module					*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether a database name is a Microsoft
								SQL Server system database.

	Revision History	:	1995-12-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2016.
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
COMPAT_EXTERN_DATA_DEF const char         *DBC_MSSQL_SystemDBList[] = {
	"master",
	"model",
#ifdef CS_PUBLIC
	"sybsecurity",
	"sybsyntax",
	"sybsystemprocs",
#endif /* #ifdef CS_PUBLIC */
	"tempdb"
};
COMPAT_EXTERN_DATA_DEF const unsigned int  DBC_MSSQL_SystemDBCount  =
	sizeof(DBC_MSSQL_SystemDBList) / sizeof(DBC_MSSQL_SystemDBList[0]);
/* *********************************************************************** */

/* *********************************************************************** */
int DBC_MSSQL_IsSystemDatabase(database_name)
const char *database_name;
{
	return((strl_find(DBC_MSSQL_SystemDBCount, ((char **) DBC_MSSQL_SystemDBList),
		database_name, NULL) == STRFUNCS_ITEM_FOUND) ? DBC_TRUE : DBC_FALSE);
}
/* *********************************************************************** */

