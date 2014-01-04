/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Initializes an 'MRG_FIL' structure.

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

	NAME			:	MRG_InitFil

	SYNOPSIS		:	void MRG_InitFil(fil_ptr);

						MRG_FIL *fil_ptr;

	DESCRIPTION	:	Initializes the members of an ''MRG_FIL'' structure
						to their default values.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``fil_ptr`` points to the ''MRG_FIL'' structure
						to be initialized by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_InitCtl
						MRG_InitReg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	MRG_InitFil
						Initialization Functions:MRG_InitFil

	PUBLISH XREF:	MRG_InitFil

	PUBLISH NAME:	MRG_InitFil

	ENTRY CLASS	:	Initialization Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MRG_InitFil(MRG_FIL *fil_ptr)
#else
void MRG_InitFil(fil_ptr)
MRG_FIL *fil_ptr;
#endif /* #ifndef NARGS */
{
	memset(fil_ptr, '\0', sizeof(*fil_ptr));

	fil_ptr->signature       = MRG_SIGNATURE_NONE;
	fil_ptr->file_name       = NULL;
	fil_ptr->open_mode       = ((MRG_OPEN_MODE) 0);
	fil_ptr->os_open_mode    = ((MRG_OPEN_MODE_OS) 0);
	fil_ptr->file_handle     = MMI_FILE_HANDLE_CLOSED;
	fil_ptr->file_length     = ((MMI_LENGTH) 0);
	fil_ptr->allocated_count = 0;
	fil_ptr->region_count    = 0;
	fil_ptr->region_list     = NULL;
	fil_ptr->parent_ptr      = NULL;
}
/*	***********************************************************************	*/

