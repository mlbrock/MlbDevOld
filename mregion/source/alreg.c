/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Allocates memory for a single 'MRG_REG' structure.

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

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MRG_AllocateReg

	SYNOPSIS		:	return_code = MRG_AllocateReg(reg_ptr, error_text);

						int       return_code;

						MRG_REG **reg_ptr;

						char     *error_text;


	DESCRIPTION	:	Allocates memory for a single ''MRG_REG'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``reg_ptr`` points to the pointer to an ''MRG_REG''
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

	SEE ALSO		:	MRG_InitReg
						MRG_AllocateItem
						MRG_AllocateFil
						MRG_AllocateCtl

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2018 Michael L. Brock

	OUTPUT INDEX:	MRG_AllocateReg
						Memory Management Functions:MRG_AllocateReg

	PUBLISH XREF:	MRG_AllocateReg

	PUBLISH NAME:	MRG_AllocateReg

	ENTRY CLASS	:	Memory Management Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
int MRG_AllocateReg(MRG_REG **reg_ptr, char *error_text)
#else
int MRG_AllocateReg(reg_ptr, error_text)
MRG_REG **reg_ptr;
char     *error_text;
#endif /* #ifndef NARGS */
{
	int return_code;

	if ((return_code = MRG_AllocateItem("MRG_REG", sizeof(**reg_ptr),
		((void **) reg_ptr), error_text)) == MRG_SUCCESS) {
		MRG_InitReg(*reg_ptr);
		(*reg_ptr)->signature = MRG_SIGNATURE_REG;
	}

	return(return_code);
}
/*	***********************************************************************	*/

