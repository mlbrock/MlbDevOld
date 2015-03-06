/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses 'STR_VERSION' definitions.

	Revision History	:	1995-08-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2015.
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

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static const SPF_SPEC SPF_STR_VersionSpecList[] = {
	{
		"@Major",
		{	"@Maj"	},
		SPF_TYPE_U_CHAR_INT,
		1,		1,
		0,		UINT_MAX,
		0.0,	((double) UCHAR_MAX),
		offsetof(STR_VERSION, major),
		0,
		{	NULL,	NULL	}
	},
	{
		"@Minor",
		{	"@Min"	},
		SPF_TYPE_U_CHAR_INT,
		1,		1,
		0,		UINT_MAX,
		0.0,	((double) UCHAR_MAX),
		offsetof(STR_VERSION, minor),
		0,
		{	NULL,	NULL	}
	},
	{
		"@Release",
		{	"@Rel"	},
		SPF_TYPE_U_CHAR_INT,
		1,		1,
		0,		UINT_MAX,
		0.0,	((double) UCHAR_MAX),
		offsetof(STR_VERSION, release),
		0,
		{	NULL,	NULL	}
	},
	{
		"@Build",
		{	""	},
		SPF_TYPE_U_CHAR_INT,
		1,		1,
		0,		UINT_MAX,
		0.0,	((double) UCHAR_MAX),
		offsetof(STR_VERSION, build),
		0,
		{	NULL,	NULL	}
	}
};

static unsigned int   SPF_STR_VersionSpecCount  =
	sizeof(SPF_STR_VersionSpecList) / sizeof(SPF_STR_VersionSpecList[0]);

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_STRVersion(SPF_CONTEXT *context_ptr, const SPF_SPEC *spec_ptr,
	const SPF_PARSE *parse_ptr, STR_VERSION *version_ptr, char *error_text)
#else
int SPF_PARSE_STRVersion(context_ptr, spec_ptr, parse_ptr, version_ptr,
	error_text)
SPF_CONTEXT     *context_ptr;
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
STR_VERSION     *version_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	*version_ptr = STR_VERSION_NUMBER_NULL;

	return(SPF_PARSE_Complex(context_ptr, spec_ptr, parse_ptr,
		SPF_STR_VersionSpecCount, SPF_STR_VersionSpecList, NULL, version_ptr,
		error_text));
}
/*	***********************************************************************	*/

