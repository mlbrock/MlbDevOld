/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Finds a subject by Rendezvous listen identifier.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
RVUTIL_SUB *RVUTIL_FindSubByListenID(const RVUTIL_ENV *env_ptr,
	rv_ListenId listen_id, unsigned int *found_index)
{
	RVUTIL_SUB *tmp_ptr = NULL;

	unsigned int count_1;

	for (count_1 = 0; count_1 < env_ptr->sub_count; count_1++) {
		if (env_ptr->sub_list[count_1].listen_id == listen_id) {
			tmp_ptr = ((RVUTIL_SUB *) env_ptr->sub_list) + count_1;
			if (found_index != NULL)
				*found_index = count_1;
			break;
		}
	}

	return(tmp_ptr);
}
/*	***********************************************************************	*/

