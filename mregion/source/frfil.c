/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees an 'MRG_FIL' structure.

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

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MRG_FreeFil

	SYNOPSIS		:	void MRG_FreeFil(fil_ptr);

						MRG_FIL *fil_ptr;

	DESCRIPTION	:	Frees the members of an ''MRG_FIL'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``fil_ptr`` points to the ''MRG_FIL'' structure
						to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_InitFil
						MRG_FreeCtl
						MRG_FreeReg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2016 Michael L. Brock

	OUTPUT INDEX:	MRG_FreeFil
						Memory Management Functions:MRG_FreeFil

	PUBLISH XREF:	MRG_FreeFil

	PUBLISH NAME:	MRG_FreeFil

	ENTRY CLASS	:	Memory Management Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MRG_FreeFil(MRG_FIL *fil_ptr)
#else
void MRG_FreeFil(fil_ptr)
MRG_FIL *fil_ptr;
#endif /* #ifndef NARGS */
{
	while (fil_ptr->region_count)
		MRG_FreeReg(fil_ptr->region_list[--fil_ptr->region_count]);

	if (fil_ptr->file_name != NULL)
		free(fil_ptr->file_name);

	if (fil_ptr->region_list != NULL)
		free(fil_ptr->region_list);

	free(fil_ptr);
}
/*	***********************************************************************	*/

