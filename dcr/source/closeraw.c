/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Data Cache Repository (DCR) Library Module										*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	

	Revision History	:	1994-05-03 --- Creation.
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

#include "dcr.h"

/*	***********************************************************************	*/

void DCR_CloseRaw(file_handle, mmap_ptr, mmap_size)
int            *file_handle;
volatile void **mmap_ptr;
unsigned long  *mmap_size;
{
	if (*mmap_ptr != NULL)
		munmap(((void *) *mmap_ptr), ((int) *mmap_size));

	if (*file_handle > -1)
		close(*file_handle);

	*file_handle = -1;
	*mmap_ptr    = NULL;
	*mmap_size   = 0L;
}
/*	***********************************************************************	*/

