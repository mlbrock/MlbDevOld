/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Allocates memory for a single 'MRG_FIL' structure.

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

	NAME			:	MRG_AllocateFil

	SYNOPSIS		:	return_code = MRG_AllocateFil(fil_ptr, error_text);

						int       return_code;

						MRG_FIL **fil_ptr;

						char     *error_text;


	DESCRIPTION	:	Allocates memory for a single ''MRG_FIL'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``fil_ptr`` points to the pointer to an ''MRG_FIL''
						structure to be allocated by this function.

						(.) ``error_text`` points to a string into which this
						function will place text descriptive of any error which
						might occur.

						(-) The string allocated for this purpose should be at least
						''MRG_MAX_ERROR_TEXT'' characters in length.

						(-) The ``error_text`` parameter may be ''NULL'', in which
						case this function will not de-reference it.

	RETURNS		:	Returns from this function are as follow:

						(.) ''MRG_SUCCESS'' if the function completes without
						error. ''MRG_SUCCESS'' is guaranteed to be equal to
						zero (0).

						(.) One of the defined non-zero MREGION return codes
						indicative of error.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_AllocateFilArray
						MRG_InitFil
						MRG_AllocateItem
						MRG_AllocateCtl
						MRG_AllocateReg

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2015 Michael L. Brock

	OUTPUT INDEX:	MRG_AllocateFil
						Memory Management Functions:MRG_AllocateFil

	PUBLISH XREF:	MRG_AllocateFil

	PUBLISH NAME:	MRG_AllocateFil

	ENTRY CLASS	:	Memory Management Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MRG_AllocateFil(MRG_FIL **fil_ptr, char *error_text)
#else
int MRG_AllocateFil(fil_ptr, error_text)
MRG_FIL **fil_ptr;
char     *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MRG_AllocateItem("MRG_FIL", sizeof(**fil_ptr),
		((void **) fil_ptr), error_text)) == MRG_SUCCESS) {
		MRG_InitFil(*fil_ptr);
		(*fil_ptr)->signature = MRG_SIGNATURE_FIL;
		if ((return_code =
			MRG_AllocateFilArray(*fil_ptr, MRG_ARRAY_ALLOC_GRAN, error_text)) !=
			MRG_SUCCESS)
			MRG_CloseFil(*fil_ptr);
	}

	return(return_code);
}
/*	***********************************************************************	*/

