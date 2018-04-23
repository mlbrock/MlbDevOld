/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Tib/Rendezvous Utility Library Source Module										*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes a subject.

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

#include <memory.h>

#include "rvutili.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
void RVUTIL_InitSub(RVUTIL_SUB *sub_ptr)
{
	memset(sub_ptr, '\0', sizeof(*sub_ptr));

	sub_ptr->subject_name[0]    = '\0';
	sub_ptr->call_back_function = NULL;
	sub_ptr->listen_id          = NULL;
}
/*	***********************************************************************	*/

