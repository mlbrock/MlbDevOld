/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes an 'MRG_REG' structure.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <memory.h>

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MRG_CloseReg

	SYNOPSIS		:	void MRG_CloseReg(reg_ptr);

						MRG_REG *reg_ptr;

	DESCRIPTION	:	Closes an ''MRG_REG'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``reg_ptr`` points to the ''MRG_REG'' structure
						to be closed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_FreeReg
						MRG_CloseFil
						MRG_CloseCtl

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	MRG_CloseReg
						Close Functions:MRG_CloseReg

	PUBLISH XREF:	MRG_CloseReg

	PUBLISH NAME:	MRG_CloseReg

	ENTRY CLASS	:	Close Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MRG_CloseReg(MRG_REG *reg_ptr)
#else
void MRG_CloseReg(reg_ptr)
MRG_REG *reg_ptr;
#endif /* #ifndef NARGS */
{
	if ((reg_ptr->mmap_ptr != NULL) && reg_ptr->mmap_length) {
		if (reg_ptr->mmap_flags & MMI_FLAG_PROT_WRITE)
			MMI_Sync(reg_ptr->mmap_ptr, reg_ptr->mmap_length, MMI_FLAG_SYNC_SYNC,
				NULL);
		MMI_Unmap(reg_ptr->mmap_ptr, reg_ptr->mmap_length, NULL);
	}

	MRG_FreeReg(reg_ptr);
}
/*	***********************************************************************	*/

