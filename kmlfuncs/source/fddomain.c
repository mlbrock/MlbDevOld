/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Keyword Matching Logic (KMLFUNCS) Program Module								*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Finds 'KML_DOMAIN' structures.

	Revision History	:	1998-03-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1998 - 2016.
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

#include "kmlfunci.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
const KML_DOMAIN *KML_FIND_ControlDomainByType(const KML_CONTROL *control_ptr,
	const char *file_type)
#else
const KML_DOMAIN *KML_FIND_ControlDomainByType(control_ptr, file_type)
const KML_CONTROL *control_ptr;
const char        *file_type;
#endif /* #ifndef NARGS */
{                              
	unsigned int      found_index;
	const KML_DOMAIN *domain_ptr = NULL;

	if (KML_FIND_DomainByType(control_ptr->domain_count,
		control_ptr->domain_list, file_type, &found_index) == KML_TRUE)
		domain_ptr = control_ptr->domain_list + found_index;

	return(domain_ptr);
}
/* *********************************************************************** */

/*	***********************************************************************	*/
#ifndef NARGS
int KML_FIND_DomainByType(unsigned int in_count, const KML_DOMAIN *in_list,
	const char *file_type, unsigned int *found_index)
#else
int KML_FIND_DomainByType(in_count, in_list, file_type, found_index)
unsigned int      in_count;
const KML_DOMAIN *in_list;
const char       *file_type;
unsigned int     *found_index;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;
	unsigned int count_2;

	for (count_1 = 0; count_1 < in_count; count_1++) {
		for (count_2 = 0; count_2 < in_list[count_1].type_count; count_2++) {
			if (!stricmp(in_list[count_1].type_list[count_2], file_type)) {
				if (found_index != NULL)
					*found_index = count_1;
				return(KML_TRUE);
			}
		}
	}

	return(KML_FALSE);
}
/* *********************************************************************** */

