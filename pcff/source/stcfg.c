/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Sorts the items in a configuration.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2018.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include "pcffi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
void PCFF_SortCfgByName(PCFF_CFG *cfg_ptr)
{
	STR_ARRAY_qsort(NULL, cfg_ptr->item_count, cfg_ptr->item_list,
		sizeof(*cfg_ptr->item_list),
		STR_CMP_FUNC_CAST(PCFF_ItemCompareName));
}
/* *********************************************************************** */

/* *********************************************************************** */
void PCFF_SortCfgByOrder(PCFF_CFG *cfg_ptr)
{
	STR_ARRAY_qsort(NULL, cfg_ptr->item_count, cfg_ptr->item_list,
		sizeof(*cfg_ptr->item_list),
		STR_CMP_FUNC_CAST(PCFF_ItemCompareOrder));
}
/* *********************************************************************** */


