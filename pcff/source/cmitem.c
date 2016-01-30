/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Compares items.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2016.
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
int PCFF_ItemCompareName(void *control_ptr, PCFF_ITEM *ptr_1,
	PCFF_ITEM *ptr_2, size_t data_length)
{
	return(stricmp(ptr_1->name, ptr_2->name));
}
/* *********************************************************************** */
#ifdef _MSC_VER
# pragma warning(default:4100)
#endif /* # ifdef _MSC_VER */

/* *********************************************************************** */
int PCFF_ItemCompareOrder(void *control_ptr, PCFF_ITEM *ptr_1,
	PCFF_ITEM *ptr_2, size_t data_length)
{
	int cmp;

	if ((cmp = ((ptr_1->order < ptr_2->order) ? -1 :
		((ptr_1->order > ptr_2->order) ? 1 : 0))) == 0)
		cmp = PCFF_ItemCompareName(control_ptr, ptr_1, ptr_2, data_length);

	return(cmp);
}
/* *********************************************************************** */


