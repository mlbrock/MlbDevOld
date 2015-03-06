/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes an 'MRG_CTL' structure.

	Revision History	:	1992-03-21 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1992 - 2015.
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

	NAME			:	MRG_InitCtl

	SYNOPSIS		:	void MRG_InitCtl(ctl_ptr);

						MRG_CTL *ctl_ptr;

	DESCRIPTION	:	Initializes the members of an ''MRG_CTL'' structure
						to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ctl_ptr`` points to the ''MRG_CTL'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_InitFil
						MRG_InitReg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	MRG_InitCtl
						Initialization Functions:MRG_InitCtl

	PUBLISH XREF:	MRG_InitCtl

	PUBLISH NAME:	MRG_InitCtl

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MRG_InitCtl(MRG_CTL *ctl_ptr)
#else
void MRG_InitCtl(ctl_ptr)
MRG_CTL *ctl_ptr;
#endif /* #ifndef NARGS */
{
	memset(ctl_ptr, '\0', sizeof(*ctl_ptr));

	ctl_ptr->signature       = MRG_SIGNATURE_NONE;
	ctl_ptr->allocated_count = 0;
	ctl_ptr->file_count      = 0;
	ctl_ptr->file_list       = NULL;
}
/*	***********************************************************************	*/

