/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Attempts to find the specified ADF area.

	Revision History	:	1994-06-15 --- Creation.
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

#include <string.h>

#include "adf.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	***********************************************************************	*/
COMPAT_EXTERN_DATA_DECL const ADF_AREA ADF_AreaNameList[];
/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
const ADF_AREA *ADF_FIND_AreaByName(const char *area_name,
	unsigned int *found_index)
#else
const ADF_AREA *ADF_FIND_AreaByName(area_name, found_index)
const char   *area_name;
unsigned int *found_index;
#endif /* #ifndef NARGS */
{
	const ADF_AREA *return_ptr = NULL;
	unsigned int    count_1;

	for (count_1 = 0; count_1 < ADF_AREA_COUNT; count_1++) {
		if (!stricmp(area_name, ADF_AreaNameList[count_1].area_tag)) {
			if (found_index != NULL)
				*found_index = count_1;
			return_ptr = ADF_AreaNameList + count_1;
			break;
		}
	}

	return(return_ptr);
}
/*	***********************************************************************	*/

