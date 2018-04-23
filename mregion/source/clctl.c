/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes an 'MRG_CTL' structure.

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
/* 	Include necessary header files . . .											*/
/*	***********************************************************************	*/

#include <memory.h>

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MRG_CloseCtl

	SYNOPSIS		:	void MRG_CloseCtl(ctl_ptr);

						MRG_CTL *ctl_ptr;

	DESCRIPTION	:	Closes an ''MRG_CTL'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ctl_ptr`` points to the ''MRG_CTL'' structure
						to be closed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_FreeCtl
						MRG_CloseFil
						MRG_CloseReg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	MRG_CloseCtl
						Close Functions:MRG_CloseCtl

	PUBLISH XREF:	MRG_CloseCtl

	PUBLISH NAME:	MRG_CloseCtl

	ENTRY CLASS	:	Close Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MRG_CloseCtl(MRG_CTL *ctl_ptr)
#else
void MRG_CloseCtl(ctl_ptr)
MRG_CTL *ctl_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < ctl_ptr->file_count; count_1++) {
		if (ctl_ptr->file_list[count_1] != NULL) {
			MRG_CloseFil(ctl_ptr->file_list[count_1]);
			ctl_ptr->file_list[count_1] = NULL;
		}
	}

	MRG_FreeCtl(ctl_ptr);
}
/*	***********************************************************************	*/

