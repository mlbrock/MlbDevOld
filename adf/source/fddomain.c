/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Automated Documentation Facility (ADF) Program Module							*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Attempts to find the specified ADF domain.

	Revision History	:	1995-04-27 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1995 - 2014.
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
#ifndef NARGS
const ADF_DOMAIN *ADF_FIND_Domain(unsigned int domain_count,
	const ADF_DOMAIN *domain_list, const char *file_type,
	unsigned int *found_index)
#else
const ADF_DOMAIN *ADF_FIND_Domain(domain_count, domain_list, file_type,
	found_index)
unsigned int      domain_count;
const ADF_DOMAIN *domain_list;
const char       *file_type;
unsigned int     *found_index;
#endif /* #ifndef NARGS */
{
	const ADF_DOMAIN *return_ptr = NULL;
	unsigned int      count_1;
	unsigned int      count_2;

	for (count_1 = 0; count_1 < domain_count; count_1++) {
		for (count_2 = 0; count_2 < domain_list[count_1].file_type_count;
			count_2++) {
			if (!stricmp(file_type,
				domain_list[count_1].file_type_list[count_2])) {
				return_ptr = domain_list + count_1;
				if (found_index != NULL)
					*found_index = count_1;
				break;
			}
		}
	}

	return(return_ptr);
}
/*	***********************************************************************	*/

