/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Specification Parse Facility (SPF) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Parses an SPF boolean string.

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

#include <stdio.h>
#include <string.h>

#include <strfuncs.h>

#include "spffunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static const SPF_ENUM     SPF_BooleanList[] = {
	{	"TRUE",	((unsigned long) SPF_TRUE)		},
	{	"ON",		((unsigned long) SPF_TRUE)		},
	{	"YES",	((unsigned long) SPF_TRUE)		},
	{	"T",		((unsigned long) SPF_TRUE)		},
	{	"Y",		((unsigned long) SPF_TRUE)		},
	{	"1",		((unsigned long) SPF_TRUE)		},
	{	"FALSE",	((unsigned long) SPF_FALSE)	},
	{	"OFF",	((unsigned long) SPF_FALSE)	},
	{	"NO",		((unsigned long) SPF_FALSE)	},
	{	"F",		((unsigned long) SPF_FALSE)	},
	{	"N",		((unsigned long) SPF_FALSE)	},
	{	"0",		((unsigned long) SPF_FALSE)	}
};

static const unsigned int SPF_BooleanCount  =
	sizeof(SPF_BooleanList) / sizeof(SPF_BooleanList[0]);

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int SPF_PARSE_Boolean(const SPF_SPEC *spec_ptr, const SPF_PARSE *parse_ptr,
	int *boolean_ptr, char *error_text)
#else
int SPF_PARSE_Boolean(spec_ptr, parse_ptr, boolean_ptr, error_text)
const SPF_SPEC  *spec_ptr;
const SPF_PARSE *parse_ptr;
int             *boolean_ptr;
char            *error_text;
#endif /* #ifndef NARGS */
{
	int          return_code;
	unsigned int found_index;

	if ((return_code = SPF_PARSE_Enum(spec_ptr, parse_ptr, SPF_BooleanCount,
		SPF_BooleanList, &found_index, error_text)) == SPF_SUCCESS)
		*boolean_ptr = ((int) SPF_BooleanList[found_index].value);

	return(return_code);
}
/*	***********************************************************************	*/

