/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MRG Memory-mapped Region Library Source Code Module							*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Memory-maps a region to a file.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
int MRG_MapRegToFil(MRG_FIL *fil_ptr, MMI_ADDRESS base_address,
	MMI_LENGTH mmap_length, MMI_OFFSET mmap_offset, MMI_FLAG mmap_flags,
	MMI_FLAG prot_flags, char *error_text)
#else
int MRG_MapRegToFil(fil_ptr, base_address, mmap_length, mmap_offset,
	mmap_flags, prot_flags, error_text)
MRG_FIL      *fil_ptr;
MMI_ADDRESS   base_address;
MMI_LENGTH    mmap_length;
MMI_OFFSET    mmap_offset;
MMI_FLAG      mmap_flags;
MMI_FLAG      prot_flags;
char         *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MRG_CheckFil(fil_ptr, error_text)) == MRG_SUCCESS) {
		if ((fil_ptr->region_count < fil_ptr->allocated_count) ||
			((return_code = MRG_AllocateFilArray(fil_ptr,
			fil_ptr->region_count + 1, error_text)) == MRG_SUCCESS)) {
			if ((return_code = MRG_MapReg(fil_ptr->file_handle, base_address,
				mmap_length, mmap_offset, mmap_flags, prot_flags,
				fil_ptr->region_list + fil_ptr->region_count, error_text)) ==
				MRG_SUCCESS)
				fil_ptr->region_count++;
		}
	}

	return(return_code);
}
/*	***********************************************************************	*/

