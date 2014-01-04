/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compares 'PCFF_PARAM' structures.

	Revision History	:	2001-05-19 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 2001 - 2014.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <string.h>

#include "pcffi.h"

/*	***********************************************************************	*/

#ifdef _MSC_VER
# pragma warning(disable:4100)
#endif /* # ifdef _MSC_VER */
/* *********************************************************************** */
int PCFF_ParamCompare(void *control_ptr, PCFF_PARAM *ptr_1,
	PCFF_PARAM *ptr_2, size_t data_length)
{
	int cmp;

	if ((cmp = stricmp(ptr_1->param_name, ptr_2->param_name)) == 0)
		cmp = stricmp(ptr_1->member_name, ptr_2->member_name);

	return(cmp);
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

