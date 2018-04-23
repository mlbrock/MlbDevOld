/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Returns the name of a cache compare type.

	Revision History	:	1994-07-19 --- Creation.
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

#include "dcr.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/

static char *DCR_CmpTypeNameList[DCR_COMPARE_TYPE_COUNT] = {
	"equal",
	"greater than or equal",
	"greater than",
	"less than or equal",
	"less than",
	"not equal"
};

/*	***********************************************************************	*/

char *DCR_GetCmpTypeName(compare_type, compare_type_name)
unsigned int  compare_type;
char         *compare_type_name;
{
	return(nstrcpy(compare_type_name,
		(compare_type >= DCR_COMPARE_TYPE_COUNT) ?
		"*** INVALID ***" : DCR_CmpTypeNameList[compare_type],
		DCR_MAX_COMPARE_TYPE_NAME));
}
/*	***********************************************************************	*/

