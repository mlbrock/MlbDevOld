/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Closes an 'MRG_FIL' structure.

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

#include <mbcompat.h>

#include <memory.h>

#ifdef _Windows
# include <io.h>
#else
# include <unistd.h>
#endif /* #ifdef _Windows */

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MRG_CloseFil

	SYNOPSIS		:	void MRG_CloseFil(fil_ptr);

						MRG_FIL *fil_ptr;

	DESCRIPTION	:	Closes an ''MRG_FIL'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``fil_ptr`` points to the ''MRG_FIL'' structure
						to be closed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_FreeFil
						MRG_CloseCtl
						MRG_CloseReg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	MRG_CloseFil
						Close Functions:MRG_CloseFil

	PUBLISH XREF:	MRG_CloseFil

	PUBLISH NAME:	MRG_CloseFil

	ENTRY CLASS	:	Close Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MRG_CloseFil(MRG_FIL *fil_ptr)
#else
void MRG_CloseFil(fil_ptr)
MRG_FIL *fil_ptr;
#endif /* #ifndef NARGS */
{
	unsigned int count_1;

	for (count_1 = 0; count_1 < fil_ptr->region_count; count_1++) {
		if (fil_ptr->region_list[count_1] != NULL) {
			MRG_CloseReg(fil_ptr->region_list[count_1]);
			fil_ptr->region_list[count_1] = NULL;
		}
	}

	if (fil_ptr->file_handle != MMI_FILE_HANDLE_CLOSED)
		close(fil_ptr->file_handle);

	MRG_FreeFil(fil_ptr);
}
/*	***********************************************************************	*/

