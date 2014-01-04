/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	TFREAD Text File Reading Functions Library Source Module						*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Manages the interface for loading files into memory
								using the 'FILE' facility.

	Revision History	:	1991-04-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1991 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Necessary include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>

#include "tfreadi.h"

/*	***********************************************************************	*/

/*	***********************************************************************	*/
#ifndef NARGS
const STR_CFILE_FUNCS *TFREAD_GetDefDataFILE(STR_CFILE_FUNCS *tfread_ptr)
#else
const STR_CFILE_FUNCS *TFREAD_GetDefDataFILE(tfread_ptr)
STR_CFILE_FUNCS *tfread_ptr;
#endif /* #ifndef NARGS */
{
	return(STR_EMIT_GetDefaultsCFILE_FUNCS(tfread_ptr));
}
/*	***********************************************************************	*/


