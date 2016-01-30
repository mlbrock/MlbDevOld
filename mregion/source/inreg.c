/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes an 'MRG_REG' structure.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2016.
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

	NAME			:	MRG_InitReg

	SYNOPSIS		:	void MRG_InitReg(reg_ptr);

						MRG_REG *reg_ptr;

	DESCRIPTION	:	Initializes the members of an ''MRG_REG'' structure
						to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``reg_ptr`` points to the ''MRG_REG'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_InitCtl
						MRG_InitFil

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

	OUTPUT INDEX:	MRG_InitReg
						Initialization Functions:MRG_InitReg

	PUBLISH XREF:	MRG_InitReg

	PUBLISH NAME:	MRG_InitReg

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MRG_InitReg(MRG_REG *reg_ptr)
#else
void MRG_InitReg(reg_ptr)
MRG_REG *reg_ptr;
#endif /* #ifndef NARGS */
{
	memset(reg_ptr, '\0', sizeof(*reg_ptr));

	reg_ptr->signature      = MRG_SIGNATURE_NONE;
	reg_ptr->base_address   = NULL;
	reg_ptr->mmap_ptr       = NULL;
	reg_ptr->mmap_length    = ((MMI_LENGTH) 0);
	reg_ptr->mmap_offset    = ((MMI_OFFSET) 0);
	reg_ptr->mmap_flags     = ((MMI_FLAG) 0);
	reg_ptr->prot_flags     = ((MMI_FLAG) 0);
	reg_ptr->os_mmap_handle = MMI_MMAP_HANDLE_OS_CLOSED;
	reg_ptr->current_offset = 0L;
	reg_ptr->parent_ptr     = NULL;
}
/*	***********************************************************************	*/

