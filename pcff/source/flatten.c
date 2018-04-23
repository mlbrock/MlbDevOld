/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Flattens the source list associated with the items
								in a configuration.

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
void PCFF_FlattenItems(PCFF_CFG *cfg_ptr)
{
	unsigned int count_1;
	unsigned int count_2;

	for (count_1 = 0; count_1 < cfg_ptr->item_count; count_1++) {
		if (cfg_ptr->item_list[count_1].src_count > 1) {
			for (count_2 = 1;
				count_2 < cfg_ptr->item_list[count_1].src_count; count_2++)
				PCFF_FreeSrc(cfg_ptr->item_list[count_1].src_list + count_2);
			mema_remove(&cfg_ptr->item_list[count_1].src_count,
				((void **) &cfg_ptr->item_list[count_1].src_list),
				sizeof(*cfg_ptr->item_list[count_1].src_list), 1,
				cfg_ptr->item_list[count_1].src_count - 1);
		}
	}
}
/* *********************************************************************** */


