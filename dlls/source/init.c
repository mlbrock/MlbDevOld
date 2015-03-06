/* *********************************************************************** */
/* *********************************************************************** */
/*	Doubly-Linked List Support (DLLS) Library Module Source File				*/
/* *********************************************************************** */
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes a doubly-linked list.

	Revision History	:	1987-03-11 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1987 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/* *********************************************************************** */

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Necessary include files . . .															*/
/*	***********************************************************************	*/

#include <memory.h>

#include "dllsi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
DLLS *DLLS_Init(DLLS *dlls_ptr)
{
	memset(dlls_ptr, '\0', sizeof(*dlls_ptr));

	dlls_ptr->signature  = DLLS_SIGNATURE_VALID;
	dlls_ptr->first_ptr  = NULL;
	dlls_ptr->last_ptr   = NULL;
	dlls_ptr->node_count = 0;
	dlls_ptr->data_ptr   = NULL;
	dlls_ptr->free_func  = NULL;

	return(dlls_ptr);
}
/*	***********************************************************************	*/

