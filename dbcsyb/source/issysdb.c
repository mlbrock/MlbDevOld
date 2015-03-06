/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Determines whether a database name is a Sybase system
								database.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

#include <string.h>

#include "dbcsybi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
/* *********************************************************************** */
/* This list is searched using a binary search. It must, therefore, be		*/
/*	maintained in sorted order.															*/
/* *********************************************************************** */
COMPAT_EXTERN_DATA_DEF const char         *DBC_SYB_SystemDBList[] = {
	"master",
	"model",
#ifdef CS_PUBLIC
	"sybsecurity",
	"sybsyntax",
	"sybsystemprocs",
#endif /* #ifdef CS_PUBLIC */
	"tempdb"
};
COMPAT_EXTERN_DATA_DEF const unsigned int  DBC_SYB_SystemDBCount  =
	sizeof(DBC_SYB_SystemDBList) / sizeof(DBC_SYB_SystemDBList[0]);
/* *********************************************************************** */

/* *********************************************************************** */
#ifndef NARGS
int DBC_SYB_IsSystemDatabase(const char *database_name)
#else
int DBC_SYB_IsSystemDatabase(database_name)
const char *database_name;
#endif /* #ifndef NARGS */
{
	return((strl_find(DBC_SYB_SystemDBCount, ((char **) DBC_SYB_SystemDBList),
		database_name, NULL) == STRFUNCS_ITEM_FOUND) ? DBC_TRUE : DBC_FALSE);
}
/* *********************************************************************** */

