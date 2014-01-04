/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Generic Sybase Support Functions Library Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Retrieves information about the columns which
								comprise a specified table.

	Revision History	:	1993-08-13 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1993 - 2014.
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

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DEF const DBC_SYB_TYPE DBC_SYB_TypeList[] = {
	{	SYBBINARY,		1,	"DBBINARY",		"BINARYBIND",			0,	"B",	},
	{	SYBBIT,			1,	"DBBIT",			"BITBIND",				1,	"B"	},
	{	SYBCHAR,			1,	"DBCHAR",		"NTBSTRINGBIND",		0,	"c"	},
	{	SYBTEXT,			1,	"DBCHAR",		"CHARBIND",				0,	"c"	},
	{	SYBIMAGE,		1,	"DBBINARY",		"BINARYBIND",			0,	"B"	},
	{	SYBINT1,			1,	"DBTINYINT",	"TINYBIND",				1,	"C"	},
	{	SYBINT2,			2,	"DBSMALLINT",	"SMALLBIND",			1,	"s"	},
	{	SYBINT4,			4,	"DBINT",			"INTBIND",				1,	"l"	},
	{	SYBREAL,			4,	"DBREAL",		"REALBIND",				1,	"f"	},
	{	SYBFLT8,			8,	"DBFLT8",		"FLT8BIND",				1,	"d"	},
	{	SYBMONEY,		8,	"DBMONEY",		"MONEYBIND",			1,	"l,L"	},
	{	SYBMONEY4,		4,	"DBMONEY4",		"SMALLMONEYBIND",		1,	"l"	},
	{	SYBDATETIME,	8,	"DBDATETIME",	"DATETIMEBIND",		1,	"l,l"	},
	{	SYBDATETIME4,	4,	"DBDATETIME4",	"SMALLDATETIMEBIND",	1,	"S,S"	}
};
COMPAT_EXTERN_DATA_DEF const unsigned int    DBC_SYB_TypeCount  =
	sizeof(DBC_SYB_TypeList) / sizeof(DBC_SYB_TypeList[0]);
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
const DBC_SYB_TYPE *DBC_SYB_FIND_TypeByType(int in_type,
	unsigned int *found_index)
#else
const DBC_SYB_TYPE *DBC_SYB_FIND_TypeByType(in_type, found_index)
int           in_type;
unsigned int *found_index;
#endif /* #ifndef NARGS */
{
	unsigned int        count_1;
	const DBC_SYB_TYPE *type_ptr = NULL;

	for (count_1 = 0; count_1 < DBC_SYB_TypeCount; count_1++) {
		if (in_type == DBC_SYB_TypeList[count_1].type) {
			if (found_index != NULL)
				*found_index = count_1;
			type_ptr = DBC_SYB_TypeList + count_1;
			break;
		}
	}

	return(type_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
const DBC_SYB_TYPE *DBC_SYB_FIND_TypeByNames(const char *in_name,
	const char *in_bind, unsigned int *found_index)
#else
const DBC_SYB_TYPE *DBC_SYB_FIND_TypeByNames(in_name, in_bind,
	found_index)
const char   *in_name;
const char   *in_bind;
unsigned int *found_index;
#endif /* #ifndef NARGS */
{
	unsigned int        count_1;
	const DBC_SYB_TYPE *type_ptr = NULL;

	for (count_1 = 0; count_1 < DBC_SYB_TypeCount; count_1++) {
		if ((!strcmp(in_name, DBC_SYB_TypeList[count_1].name)) &&
			(!strcmp(in_bind, DBC_SYB_TypeList[count_1].bind))) {
			if (found_index != NULL)
				*found_index = count_1;
			type_ptr = DBC_SYB_TypeList + count_1;
			break;
		}
	}

	return(type_ptr);
}
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
const DBC_SYB_TYPE *DBC_SYB_FIND_TypeByTypeSpec(const char *in_type_spec,
	unsigned int *found_index)
#else
const DBC_SYB_TYPE *DBC_SYB_FIND_TypeByTypeSpec(in_type_spec, found_index)
const char   *in_type_spec;
unsigned int *found_index;
#endif /* #ifndef NARGS */
{
	unsigned int        count_1;
	const DBC_SYB_TYPE *type_ptr = NULL;

	for (count_1 = 0; count_1 < DBC_SYB_TypeCount; count_1++) {
		if (!strcmp(in_type_spec, DBC_SYB_TypeList[count_1].type_spec)) {
			if (found_index != NULL)
				*found_index = count_1;
			type_ptr = DBC_SYB_TypeList + count_1;
			break;
		}
	}

	return(type_ptr);
}
/*	***********************************************************************	*/

