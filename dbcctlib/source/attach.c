/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	DBC Sybase CT-Library Support Functions Library Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Performs a generalized attachment to the Sybase
								CT-LIB facility.

	Revision History	:	1996-06-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1996 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "dbcctlii.h"

/*	***********************************************************************	*/

/*
	ADF NOTE:	Documented in the header file 'dbc.h'.
*/
/*	***********************************************************************	*/
#ifndef NARGS
void DBC_AttachFacility(DBC_FUNCS *funcs_ptr)
#else
void DBC_AttachFacility(funcs_ptr)
DBC_FUNCS *funcs_ptr;
#endif /* #ifndef NARGS */
{
	DBC_CTLIB_AttachFacility(funcs_ptr);
}
/*	***********************************************************************	*/

