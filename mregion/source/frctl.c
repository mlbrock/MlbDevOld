/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees an 'MRG_CTL' structure.

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

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MRG_FreeCtl

	SYNOPSIS		:	void MRG_FreeCtl(ctl_ptr);

						MRG_CTL *ctl_ptr;

	DESCRIPTION	:	Frees the members of an ''MRG_CTL'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``ctl_ptr`` points to the ''MRG_CTL'' structure
						to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_InitCtl
						MRG_FreeFil
						MRG_FreeReg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	MRG_FreeCtl
						Memory Management Functions:MRG_FreeCtl

	PUBLISH XREF:	MRG_FreeCtl

	PUBLISH NAME:	MRG_FreeCtl

	ENTRY CLASS	:	Memory Management Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MRG_FreeCtl(MRG_CTL *ctl_ptr)
#else
void MRG_FreeCtl(ctl_ptr)
MRG_CTL *ctl_ptr;
#endif /* #ifndef NARGS */
{
	while (ctl_ptr->file_count)
		MRG_FreeFil(ctl_ptr->file_list[--ctl_ptr->file_count]);

	if (ctl_ptr->file_list != NULL)
		free(ctl_ptr->file_list);

	free(ctl_ptr);
}
/*	***********************************************************************	*/

