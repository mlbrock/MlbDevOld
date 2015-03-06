/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Converts an 'RVUTIL_SNAME_WORK' structure into an
								'RVUTIL_SNAME_FLAT' structure.

	Revision History	:	1996-01-12 --- Creation
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <memory.h>

#include <strfuncs.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
RVUTIL_SNAME_FLAT *RVUTIL_WorkToFlat(const RVUTIL_SNAME_WORK *work_ptr,
	RVUTIL_SNAME_FLAT *flat_ptr)
{
	unsigned int count_1;

	memset(flat_ptr, '\0', sizeof(*flat_ptr));

	flat_ptr->element_count = work_ptr->element_count;

	for (count_1 = 0; count_1 < work_ptr->element_count; count_1++)
		nstrcpy(flat_ptr->element_list[count_1],
			work_ptr->element_list[count_1],
			sizeof(*flat_ptr->element_list) - 1);

	return(flat_ptr);
}
/*	***********************************************************************	*/

