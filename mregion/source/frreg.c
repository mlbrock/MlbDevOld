/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	MREGION Memory-mapped Region Library Source Code Module						*/
/*	***********************************************************************	*/
/*
	File Name  			:	%M%

	File Version      :	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Frees an 'MRG_REG' structure.

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

#include "mregioni.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	BOH

	NAME			:	MRG_FreeReg

	SYNOPSIS		:	void MRG_FreeReg(reg_ptr);

						MRG_REG *reg_ptr;

	DESCRIPTION	:	Frees the members of an ''MRG_REG'' structure.

	PARAMETERS	:	Parameters to this function are as follow:

						(.) ``reg_ptr`` points to the ''MRG_REG'' structure
						to be freed by this function.

	RETURNS		:	Void.

	NOTES			:	

	CAVEATS		:	

	SEE ALSO		:	MRG_InitReg
						MRG_FreeFil
						MRG_FreeCtl

	EXAMPLES		:	

	AUTHOR		:	Michael L. Brock

	COPYRIGHT	:	Copyright 1992 - 2014 Michael L. Brock

	OUTPUT INDEX:	MRG_FreeReg
						Memory Management Functions:MRG_FreeReg

	PUBLISH XREF:	MRG_FreeReg

	PUBLISH NAME:	MRG_FreeReg

	ENTRY CLASS	:	Memory Management Functions

EOH */
/*	***********************************************************************	*/
#ifndef NARGS
void MRG_FreeReg(MRG_REG *reg_ptr)
#else
void MRG_FreeReg(reg_ptr)
MRG_REG *reg_ptr;
#endif /* #ifndef NARGS */
{
	free(reg_ptr);
}
/*	***********************************************************************	*/

