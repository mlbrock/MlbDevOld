/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*	Parse Configuration File Facility (PCFF) Library Module Source File		*/
/*	***********************************************************************	*/
/*
	File Name			:	%M%

	File Version		:	%I%

	Last Extracted		:	%D%	%T%

	Last Updated		:	%E%	%U%

	File Description	:	Deletes a item from a configuration.

	Revision History	:	1999-11-03 --- Creation.
									Michael L. Brock

		Copyright Michael L. Brock 1999 - 2015.
		Distributed under the Boost Software License, Version 1.0.
		(See accompanying file LICENSE_1_0.txt or copy at
		http://www.boost.org/LICENSE_1_0.txt)

*/
/*	***********************************************************************	*/

/*	***********************************************************************	*/
/*	***********************************************************************	*/
/*		Required include files . . .														*/
/*	***********************************************************************	*/

#include <stdio.h>

#include "pcffi.h"

/*	***********************************************************************	*/

/* *********************************************************************** */
int PCFF_DeleteItem(PCFF_CFG *cfg_ptr, unsigned int item_index,
	char *error_text)
{
	int return_code = PCFF_SUCCESS;

	if (item_index >= cfg_ptr->item_count) {
		sprintf(error_text, "%s (%u) --- %s %u.",
			"Invalid item element index specified for removal", item_index,
			"value should be less than", cfg_ptr->item_count);
		return_code = PCFF_FAILURE;
	}
	else {
		PCFF_FreeItem(cfg_ptr->item_list + item_index);
		mema_remove(&cfg_ptr->item_count, ((void **) &cfg_ptr->item_list),
			sizeof(*cfg_ptr->item_list), item_index, 1);
	}

	return(return_code);
}
/* *********************************************************************** */


