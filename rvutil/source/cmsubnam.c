/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compares a subject by name.

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

#include "rvutili.h"

/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/*	***********************************************************************	*/
int RVUTIL_CompareSubByName(void *control_ptr, const RVUTIL_SUB *ptr_1,
	const RVUTIL_SUB *ptr_2, size_t data_length)
{
	return(strcmp(ptr_1->subject_name, ptr_2->subject_name));
}
/*	***********************************************************************	*/
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

