/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Finds a subject by name.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
RVUTIL_SUB *RVUTIL_FindSubByName(const RVUTIL_ENV *env_ptr,
	const char *subject_name, unsigned int *found_index)
{
	RVUTIL_SUB   *tmp_ptr = NULL;
	RVUTIL_SUB    tmp_sub;
	unsigned int  tmp_found_index;

	if ((subject_name != NULL) &&
		(strlen(subject_name) < sizeof(tmp_sub.subject_name))) {
		found_index = (found_index == NULL) ? &tmp_found_index : found_index;
		strcpy(tmp_sub.subject_name, subject_name);
		tmp_ptr = (STR_ARRAY_find(env_ptr->sub_count, env_ptr->sub_list,
			&tmp_sub, sizeof(RVUTIL_SUB), found_index,
			((int (*)(void *, const void *, const void *, size_t))
			RVUTIL_CompareSubByName)) != STRFUNCS_ITEM_FOUND) ? NULL :
			(env_ptr->sub_list + *found_index);
	}

	return(tmp_ptr);
}
/*	***********************************************************************	*/

